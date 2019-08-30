#### [PATCH 1/2] target/i386: Add support for save PEBS registers
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kang, Luwei" <luwei.kang@intel.com>
X-Patchwork-Id: 11120303
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 23D4318EC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 05:27:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0E70522CED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 05:27:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727318AbfH2F1A (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 01:27:00 -0400
Received: from mga01.intel.com ([192.55.52.88]:2694 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725970AbfH2F07 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 01:26:59 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 28 Aug 2019 22:26:59 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,442,1559545200";
   d="scan'208";a="171783713"
Received: from icl-2s.bj.intel.com ([10.240.193.48])
  by orsmga007.jf.intel.com with ESMTP; 28 Aug 2019 22:26:57 -0700
From: Luwei Kang <luwei.kang@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org,
        Luwei Kang <luwei.kang@intel.com>
Subject: [PATCH 1/2] target/i386: Add support for save PEBS registers
Date: Thu, 29 Aug 2019 13:22:54 +0800
Message-Id: <1567056175-14275-1-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel processor introduce some hardware extensions that output PEBS record
to Intel PT buffer instead of DS area, so PEBS can be enabled in KVM guest
by PEBS output Intel PT. This patch adds a section for PEBS which use for
saves PEBS registers when the value is no-zero.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 target/i386/cpu.h     |  8 ++++++++
 target/i386/machine.c | 41 +++++++++++++++++++++++++++++++++++++++++
 2 files changed, 49 insertions(+)

```
#### [PATCH v3 1/2] KVM: x86: always stop emulation on page faultThread-Topic: [PATCH v3 1/2] KVM: x86: always stop emulation on page fault
##### From: Jan Dakinevich <jan.dakinevich@virtuozzo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jan Dakinevich <jan.dakinevich@virtuozzo.com>
X-Patchwork-Id: 11120631
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2A2EE1399
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 08:23:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F3EC923405
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 08:23:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=virtuozzo.com header.i=@virtuozzo.com
 header.b="vrJPFubX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726990AbfH2IXY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 04:23:24 -0400
Received: from mail-eopbgr10099.outbound.protection.outlook.com
 ([40.107.1.99]:44097
        "EHLO EUR02-HE1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726009AbfH2IXX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 04:23:23 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Od3qtFFEvH8suqN+s0IzbC14P+J67AIvxkvnQbRakBBvH0rWbYfSQPfFjQey+ua0Blbjo/8FkuUcSBLZPm7ZdnsKs0BSapwdwuL/NAG+Ip/SmHBermth9NUdIwd44ME5X17R1axBhw2q+hKJ5JgTcw2x6D4rPP2lP8oz5nTojlFrK04wB6/BtkOclxCTL2kERe5lLC6Ro55bARwGCh4H2VRIAQye1fqRnyVu/TnUehxYNpNA0oq7iPyaKAM9rPXnTpLjfTq3ypPZNAMp1IAa9BO8bptRqQv6IcsOoRgELP8xhLt6a8HqqrL/P9fyckNY1YP/DDz3Lid5jXSrJbQ/KQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=eHXtOLU+RACRHQmWlmEgJKIwDrd/jAecnZx3zuIg0xo=;
 b=ngzMRjaN/AXzAcbTM8VYbQOpRByemwam8p8Utwm4ITH1kNiZF8Dq0TaVczbUO9NglDRL7OcpQ7tABgkq2poyC8g0j59w86b5QaPRfmE3x9YzI0kZYfzbqrx0sMCIJmwHb0Lf2uSQGtT42KOKPMYb7QXUZjjp3asBGt6v8qN7Yd4MoiMjhdlFxm5nOPx6QYQ8PJIayYtPaOMZnq4iHkeK7Qvcl9lCRPUF7wiDJQyh9PweZxf6hvbB7rCiZ9uAYKc1w8FFHD+fa03PtqX4qU3GG8wyCSUaHUNjdvCH0owq1zbsfdM2j8z8sX3Nu2Tm8brZkCQvY2GbmZyYKKMCbJFrxA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=eHXtOLU+RACRHQmWlmEgJKIwDrd/jAecnZx3zuIg0xo=;
 b=vrJPFubXtL/fDLGwFFpJ3hFeasbwbGaTKdwK2vbvl6gn+Kwa9D3cYc7Eg8Z9PynGk9dS0BXs8ROqczCP5wM/37vTkJWOKlTgjwCkPdNah7j3YabLlzsz9WnuFYa46bHczBkHpTKz9pjo8jaD0ScoWzlt8HNe7SnmvdwIw5kByk0=
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com (10.170.236.143) by
 VI1PR08MB3342.eurprd08.prod.outlook.com (52.134.31.141) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2220.18; Thu, 29 Aug 2019 08:23:19 +0000
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a]) by VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a%3]) with mapi id 15.20.2178.023; Thu, 29 Aug 2019
 08:23:19 +0000
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
Subject: [PATCH v3 1/2] KVM: x86: always stop emulation on page fault
Thread-Topic: [PATCH v3 1/2] KVM: x86: always stop emulation on page fault
Thread-Index: AQHVXkMDq0PAUucu1Uu9lgvhCNDIuA==
Date: Thu, 29 Aug 2019 08:23:18 +0000
Message-ID: <1567066988-23376-2-git-send-email-jan.dakinevich@virtuozzo.com>
References: <1567066988-23376-1-git-send-email-jan.dakinevich@virtuozzo.com>
In-Reply-To: <1567066988-23376-1-git-send-email-jan.dakinevich@virtuozzo.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: HE1PR05CA0274.eurprd05.prod.outlook.com
 (2603:10a6:3:fc::26) To VI1PR08MB2782.eurprd08.prod.outlook.com
 (2603:10a6:802:19::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=jan.dakinevich@virtuozzo.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.1.4
x-originating-ip: [185.231.240.5]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 6fb81dd3-e3ba-4c87-9d38-08d72c5a258a
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(5600166)(711020)(4605104)(1401327)(4534185)(4627221)(201703031133081)(201702281549075)(8990200)(2017052603328)(7193020);SRVR:VI1PR08MB3342;
x-ms-traffictypediagnostic: VI1PR08MB3342:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <VI1PR08MB3342253857F0A0472F9462438AA20@VI1PR08MB3342.eurprd08.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:1284;
x-forefront-prvs: 0144B30E41
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(136003)(346002)(39850400004)(396003)(366004)(376002)(199004)(189003)(66476007)(66946007)(66556008)(50226002)(64756008)(66446008)(2351001)(2501003)(36756003)(14454004)(8936002)(86362001)(66066001)(81156014)(81166006)(6436002)(5640700003)(6512007)(71200400001)(71190400001)(44832011)(486006)(476003)(6916009)(5660300002)(52116002)(54906003)(14444005)(53936002)(102836004)(99286004)(2906002)(6486002)(478600001)(8676002)(6506007)(386003)(446003)(11346002)(2616005)(26005)(76176011)(186003)(7416002)(305945005)(4326008)(3846002)(25786009)(7736002)(256004)(6116002)(316002);DIR:OUT;SFP:1102;SCL:1;SRVR:VI1PR08MB3342;H:VI1PR08MB2782.eurprd08.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: virtuozzo.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 NeKDJeqHRiHmvuCnX3OTwR7mKNfIyvzDCXwB5comj5tJgkH9v60ZCWzBLPnQhjrA8fBMGOOeGQYB1ez8PoqlbWrQO6wKaWqDhf1KGw9D9QrOGpykkU6m1ILj07s3OjnP8lI+eHGP+QaRlTjmB/9B2ZcDKWGrYhd6HNXb6GFoUuFxBaL32r7MqzAfdYoHZ9SJOMQD/NXplgo9WdvlpIaVe5+rEuSiobiTnaeSwL8E+cGp6DHy61fDjJP5vqOk8mtOMgDU2PH2NQw0Oa7w3lstyM4kTzUvi+rP97W8N0zO11Ay98nVFK9IOIuBAcRPQ/50iCNhC+3HntLfQjV8MzztsdHgOkKOVeuQ3/u5XoWNbIEIzUHQK6j7pdvX5yh56WyVzbY456BRkfUvU5mTQc0owzMfjU8nQXhdlpk5STQW7Ck=
Content-Type: text/plain; charset="iso-8859-2"
MIME-Version: 1.0
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 6fb81dd3-e3ba-4c87-9d38-08d72c5a258a
X-MS-Exchange-CrossTenant-originalarrivaltime: 29 Aug 2019 08:23:18.8812
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 sJTEFkoGsF6iMO4LXMCJZjPrn2Km0lpqcYabnpuJNN7PSsPwsBMFr3pCh+7AhsCsYa0tkpSwOyPod6kznWes9D8RwmUUdpAFytI3v2HMGFM=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: VI1PR08MB3342
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
 arch/x86/kvm/x86.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/6] mdev: Introduce sha1 based mdev alias
##### From: Parav Pandit <parav@mellanox.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Parav Pandit <parav@mellanox.com>
X-Patchwork-Id: 11121051
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F40B514F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 11:19:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D370D23403
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 11:19:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727252AbfH2LTr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 07:19:47 -0400
Received: from mail-il-dmz.mellanox.com ([193.47.165.129]:43748 "EHLO
        mellanox.co.il" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728162AbfH2LTU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 07:19:20 -0400
Received: from Internal Mail-Server by MTLPINE1 (envelope-from
 parav@mellanox.com)
        with ESMTPS (AES256-SHA encrypted); 29 Aug 2019 14:19:13 +0300
Received: from sw-mtx-036.mtx.labs.mlnx (sw-mtx-036.mtx.labs.mlnx
 [10.12.150.149])
        by labmailer.mlnx (8.13.8/8.13.8) with ESMTP id x7TBJ8v2020002;
        Thu, 29 Aug 2019 14:19:11 +0300
From: Parav Pandit <parav@mellanox.com>
To: alex.williamson@redhat.com, jiri@mellanox.com,
        kwankhede@nvidia.com, cohuck@redhat.com, davem@davemloft.net
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        netdev@vger.kernel.org, Parav Pandit <parav@mellanox.com>
Subject: [PATCH v2 1/6] mdev: Introduce sha1 based mdev alias
Date: Thu, 29 Aug 2019 06:18:59 -0500
Message-Id: <20190829111904.16042-2-parav@mellanox.com>
X-Mailer: git-send-email 2.19.2
In-Reply-To: <20190829111904.16042-1-parav@mellanox.com>
References: <20190826204119.54386-1-parav@mellanox.com>
 <20190829111904.16042-1-parav@mellanox.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some vendor drivers want an identifier for an mdev device that is
shorter than the UUID, due to length restrictions in the consumers of
that identifier.

Add a callback that allows a vendor driver to request an alias of a
specified length to be generated for an mdev device. If generated,
that alias is checked for collisions.

It is an optional attribute.
mdev alias is generated using sha1 from the mdev name.

Signed-off-by: Parav Pandit <parav@mellanox.com>
---
Changelog:
v1->v2:
 - Kept mdev_device naturally aligned
 - Added error checking for crypt_*() calls
 - Corrected a typo from 'and' to 'an'
 - Changed return type of generate_alias() from int to char*
v0->v1:
 - Moved alias length check outside of the parent lock
 - Moved alias and digest allocation from kvzalloc to kzalloc
 - &alias[0] changed to alias
 - alias_length check is nested under get_alias_length callback check
 - Changed comments to start with an empty line
 - Fixed cleaunup of hash if mdev_bus_register() fails
 - Added comment where alias memory ownership is handed over to mdev device
 - Updated commit log to indicate motivation for this feature
---
 drivers/vfio/mdev/mdev_core.c    | 123 ++++++++++++++++++++++++++++++-
 drivers/vfio/mdev/mdev_private.h |   5 +-
 drivers/vfio/mdev/mdev_sysfs.c   |  13 ++--
 include/linux/mdev.h             |   4 +
 4 files changed, 135 insertions(+), 10 deletions(-)

```
#### Is: Default governor regardless of cpuidle driver Was: [PATCH v2] cpuidle-haltpoll: vcpu hotplug support
##### From: Joao Martins <joao.m.martins@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joao Martins <joao.m.martins@oracle.com>
X-Patchwork-Id: 11122105
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 47D991398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 17:17:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 105A522CF5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 17:17:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="je3kftSx"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727364AbfH2RRq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 13:17:46 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:53804 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727270AbfH2RRq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 13:17:46 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7THDj1p103579;
        Thu, 29 Aug 2019 17:16:13 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=subject : to : cc :
 references : from : message-id : date : mime-version : in-reply-to :
 content-type : content-transfer-encoding; s=corp-2019-08-05;
 bh=ZdWf5nAKch2sAxvuPQKTnzRVXVUZevXhS0HZrqLFMAc=;
 b=je3kftSxptgJIpWxFn1l6IvYKMirQ/nXSXbrQHs6R3kHlwtm5+htT8dzIn438Mu61l0C
 R2lNW+mFAeEbTjlghAY5KYqB8Q4vQEZF+e61obUOe0G0vuW3a59mLvizN1vkFjCZH2zp
 LEtaLf+mC85Lit0Pb5qZ5tbqhzsgcZtOWkGUFd1PPPIjRQAf+emvrP/UIRRNhNw/k/i+
 uvLTtICXl5eSwVFvAeqMVuxekjTIJpuikYxzc5LJQnhFzjDXCcS8tpY00WK4sGRNbDuY
 RqL2vbh00Tv1O695LxqY8Di+BLhqqdF9l58QEuwUZd+GIxwU9udXk575AXkXK//4EUjV eg==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2130.oracle.com with ESMTP id 2upjss82qt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Aug 2019 17:16:13 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7THCw8M145631;
        Thu, 29 Aug 2019 17:16:13 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by userp3030.oracle.com with ESMTP id 2unvu0aarh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Aug 2019 17:16:13 +0000
Received: from abhmp0008.oracle.com (abhmp0008.oracle.com [141.146.116.14])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x7THGBkE006501;
        Thu, 29 Aug 2019 17:16:11 GMT
Received: from [10.175.160.184] (/10.175.160.184)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 29 Aug 2019 10:16:10 -0700
Subject: Is: Default governor regardless of cpuidle driver Was: [PATCH v2]
 cpuidle-haltpoll: vcpu hotplug support
To: Marcelo Tosatti <mtosatti@redhat.com>,
        "Rafael J. Wysocki" <rjw@rjwysocki.net>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Daniel Lezcano <daniel.lezcano@linaro.org>, linux-pm@vger.kernel.org,
 Boris Ostrovsky <boris.ostrovsky@oracle.com>
References: <20190829151027.9930-1-joao.m.martins@oracle.com>
From: Joao Martins <joao.m.martins@oracle.com>
Message-ID: <c8cf8dcc-76a3-3e15-f514-2cb9df1bbbdc@oracle.com>
Date: Thu, 29 Aug 2019 18:16:05 +0100
MIME-Version: 1.0
In-Reply-To: <20190829151027.9930-1-joao.m.martins@oracle.com>
Content-Type: text/plain; charset=utf-8
Content-Language: en-US
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9364
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1908290182
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9364
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1908290183
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On 8/29/19 4:10 PM, Joao Martins wrote:
> When cpus != maxcpus cpuidle-haltpoll will fail to register all vcpus
> past the online ones and thus fail to register the idle driver.
> This is because cpuidle_add_sysfs() will return with -ENODEV as a
> consequence from get_cpu_device() return no device for a non-existing
> CPU.
> 
> Instead switch to cpuidle_register_driver() and manually register each
> of the present cpus through cpuhp_setup_state() callback and future
> ones that get onlined. This mimmics similar logic that intel_idle does.
> 
> Fixes: fa86ee90eb11 ("add cpuidle-haltpoll driver")
> Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
> Signed-off-by: Boris Ostrovsky <boris.ostrovsky@oracle.com>
> ---

While testing the above, I found out another issue on the haltpoll series.
But I am not sure what is best suited to cpuidle framework, hence requesting
some advise if below is a reasonable solution or something else is preferred.

Essentially after haltpoll governor got introduced and regardless of the cpuidle
driver the default governor is gonna be haltpoll for a guest (given haltpoll
governor doesn't get registered for baremetal). Right now, for a KVM guest, the
idle governors have these ratings:

 * ladder            -> 10
 * teo               -> 19
 * menu              -> 20
 * haltpoll          -> 21
 * ladder + nohz=off -> 25

When a guest is booted with MWAIT and intel_idle is probed and sucessfully
registered, we will end up with a haltpoll governor being used as opposed to
'menu' (which used to be the default case). This would prevent IIUC that other
C-states get used other than poll_state (state 0) and state 1.

Given that haltpoll governor is largely only useful with a cpuidle-haltpoll
it doesn't look reasonable to be the default? What about using haltpoll governor
as default when haltpoll idle driver registers or modloads.

My idea to achieve the above would be to decrease the rating to 9 (before the
lowest rated governor) and retain old defaults before haltpoll. Then we would
allow a cpuidle driver to define a preferred governor to switch on idle driver
registration. Naturally all of would be ignored if overidden by
cpuidle.governor=.

The diff below the scissors line is an example of that.

Thoughts?

---------------------------------- >8 --------------------------------

From: Joao Martins <joao.m.martins@oracle.com>
Subject: [PATCH] cpuidle: switch to prefered governor on registration

Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
---
 drivers/cpuidle/cpuidle-haltpoll.c   |  1 +
 drivers/cpuidle/cpuidle.h            |  1 +
 drivers/cpuidle/driver.c             | 26 ++++++++++++++++++++++++++
 drivers/cpuidle/governor.c           |  6 +++---
 drivers/cpuidle/governors/haltpoll.c |  2 +-
 include/linux/cpuidle.h              |  3 +++
 6 files changed, 35 insertions(+), 4 deletions(-)

```
#### [PATCH 2/2] target/i386: Add support for put/get PEBS registers
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kang, Luwei" <luwei.kang@intel.com>
X-Patchwork-Id: 11120305
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 44529184E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 05:27:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2ED5A23405
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 05:27:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727328AbfH2F1E (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 01:27:04 -0400
Received: from mga01.intel.com ([192.55.52.88]:2694 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725970AbfH2F1E (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 01:27:04 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 28 Aug 2019 22:27:03 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,442,1559545200";
   d="scan'208";a="171783751"
Received: from icl-2s.bj.intel.com ([10.240.193.48])
  by orsmga007.jf.intel.com with ESMTP; 28 Aug 2019 22:27:02 -0700
From: Luwei Kang <luwei.kang@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org,
        Luwei Kang <luwei.kang@intel.com>
Subject: [PATCH 2/2] target/i386: Add support for put/get PEBS registers
Date: Thu, 29 Aug 2019 13:22:55 +0800
Message-Id: <1567056175-14275-2-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1567056175-14275-1-git-send-email-luwei.kang@intel.com>
References: <1567056175-14275-1-git-send-email-luwei.kang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch add a new feature words for IA32_PERF_CAPABILITIES (RO)
register that serve to expose PEBS output Intel PT feature.
The registers relate with PEBS need to be set/get when PEBS output
Intel PT is supported in guest.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 target/i386/cpu.c | 20 ++++++++++++++++++++
 target/i386/cpu.h |  4 ++++
 target/i386/kvm.c | 36 ++++++++++++++++++++++++++++++++++++
 3 files changed, 60 insertions(+)

```
#### [PATCH 1/4] KVM: nVMX: Check GUEST_DEBUGCTL on vmentry of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11122467
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7B01814DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 21:25:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5644F2189D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 21:25:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="Q16FXCFq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727885AbfH2VZl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 17:25:41 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:56734 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726245AbfH2VZl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 17:25:41 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7TLOZG7165754;
        Thu, 29 Aug 2019 21:25:19 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=wVDqbmLrKTAkpRjeNGztEjifnnn+iGuNAymJH5EX+6I=;
 b=Q16FXCFq0kqzmQnFl11IbQ27oaTjay6BnlnLEIzlZWliszxeWLznKVKfIZMFzmx35O2P
 F9hGe4f+OWmEv8ZzswgE+wnperewQVvlMsXmMvxSqAHiMfpLYX3srwGKR621sS0tKA5a
 RZ13ok1UdXyIBKKHfHTEE9faGJWFvzvcLjJi8bli7O/V57l9guH0UW6im+ks7/EzyNNr
 +g1ob2iHOgVUi12EQstR+HQsVVl2zisNddFxOhl/crItm40ir9OBPyQqA3Ed3afmHAxq
 etuqFhI4laSzFzrgIVJUOnBY3EOpuRX63b7oXPZkOXQU8QlMJho1/QI6gVLPXa6RXKkn mw==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 2uppjc00fh-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Aug 2019 21:25:19 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7TLE5Xo085106;
        Thu, 29 Aug 2019 21:25:19 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 2uphaub0fj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Aug 2019 21:25:19 +0000
Received: from abhmp0018.oracle.com (abhmp0018.oracle.com [141.146.116.24])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id x7TLPIBF032402;
        Thu, 29 Aug 2019 21:25:18 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 29 Aug 2019 14:25:17 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: rkrcmar@redhat.com, pbonzini@redhat.com, jmattson@google.com
Subject: [PATCH 1/4] KVM: nVMX: Check GUEST_DEBUGCTL on vmentry of nested
 guests
Date: Thu, 29 Aug 2019 16:56:32 -0400
Message-Id: <20190829205635.20189-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190829205635.20189-1-krish.sadhukhan@oracle.com>
References: <20190829205635.20189-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9364
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=800
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1908290214
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9364
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=870 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1908290215
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Checks on Guest Control Registers, Debug Registers, and
and MSRs" in Intel SDM vol 3C, the following checks are performed on vmentry
of nested guests:

    If the "load debug controls" VM-entry control is 1, bits reserved in the
    IA32_DEBUGCTL MSR must be 0 in the field for that register. The first
    processors to support the virtual-machine extensions supported only the
    1-setting of this control and thus performed this check unconditionally.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 4 ++++
 arch/x86/kvm/x86.h        | 6 ++++++
 2 files changed, 10 insertions(+)

```
#### [PATCH v6 01/21] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG interfaceThread-Topic: [PATCH v6 01/21] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11121357
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A798D14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 13:55:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7C084215EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 13:55:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="nBK7Z0Sj";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="UF/+Kt8W"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727684AbfH2NzY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 09:55:24 -0400
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:35007 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727594AbfH2NzX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 09:55:23 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1567086923; x=1598622923;
  h=from:to:cc:subject:date:message-id:references:
   in-reply-to:content-transfer-encoding:mime-version;
  bh=p9HJqoz3LbanyMT//HPJGrEo8pSsdeciqqPDTK4TfEw=;
  b=nBK7Z0Sjp1un2zryuPUj+xFaMDUqL9rz+YYwgw7rfKlOueZ5j/ohZak7
   H+LG+yxpJvRnjYj3NwqxFOrSERAnJhnVRVwir6YcUMntqEyW/dHYhEBiJ
   GYrMH9ZJrYIO4AAaq5LCicanEx0zwgeMMgDjYVc+W3jlBMqPWMtADxoi5
   1MFhUzkrJZZXBqRrsa5bWOHdKxFffugr7PkF1kJ8l/qwFRD3gT2FMZoMW
   0vVp2GbmT4zNSP0X0WJpU7Frq1or3sm7/qlHI9QSU7uXYX/48U07YngPz
   xcml0KPAs1gHii8sHMjIZpe8XD9Hqiu1VAjbafG2s34dYwOlcLvARBMsK
   Q==;
IronPort-SDR: 
 IM89Hb//nIeQHHjiL5qFVdMMm7je0ta8pvoLtJjGhyACTZ7lTzTmh98cCtRenviUhBIO2gqKMp
 XzDeQUCa2pTk+PiFXFvItPmzkPby6PQzsG7seL/adnFW7K7Aw9OeIlkOz62xBaDeP6FI5+XySv
 W/7gPsWN13WsW+y3kycDFPogGaRCbERa5ZGo+4PgATQu+JtaCRUmfXW5BZnHDRH3kBRRw1Obr5
 qRMIX3Pge5JzY0rzJN8aXlslY4sNo+xHaW1oxmVW1qQeJcOEZrLSoZmXv4y5AS6bCKcbtX3cbX
 Puw=
X-IronPort-AV: E=Sophos;i="5.64,443,1559491200";
   d="scan'208";a="116951585"
Received: from mail-by2nam05lp2051.outbound.protection.outlook.com (HELO
 NAM05-BY2-obe.outbound.protection.outlook.com) ([104.47.50.51])
  by ob1.hgst.iphmx.com with ESMTP; 29 Aug 2019 21:55:21 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=HxAQHJoHp5rQ7zHqeGwWrYHPHkmX9QLDPSUXAX8lX2NabE1m5BXKp6R3xIEEBoLvH0vChsqMNj2V12QF0YnuthV7kdD4JJuHRaJwJzTgZ9UdFVOCVjy3NXfkjlxA1gy+jQDVYWbX0fk71bb6a/MdIP6MSQaOYsXYuIMbl++4KEAo3qqmczPddvZ8ZU7awWQJP0D1TnBRaIrvdQi91PTjMTb1keeYfB+YWce2LqmmDhaKDz5fI+UapLDxlkZcxuTeq3HqJLc9CozbzTa4r7WQPARbEc8veP53YFKrmiyqIqZnKFx/ZxmaoOH1DhBz0I6nWwo6T1ZnuJGKKWPhMMlzrQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=dDc/jViVNgdkanOMCtGdfLYq+yZEgQWGotyo/fOBKOo=;
 b=Dh223L0uosat88PMVr77YbVLivWvmx7eXJp3YZ375ev+MtJiZe5kVZ9C3MRjIvgGmVREPznyGfpgKFdbLgHTIZx28fxfzmchJEDjSiS88ygBb4tKp6VPNhy7441F3hzneLPU6EpYHSM3Mt6ZrfbnbuF7492g23OV50BI06V7kzptJQutNFj53eJZDjgADe2RqNKHxXWXy1jxO9OIUbMAUktjFgVq5HbWnWaNcClV3+sjcoq1IdjeotebIp4RJUnRZoMBrJX6rHFkZ6xUdmkQeNipesuaap7W68busUSARKT0efiRtspPCdmL32GCZCBYna2vMwGBn5KoncfMCySSlQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=dDc/jViVNgdkanOMCtGdfLYq+yZEgQWGotyo/fOBKOo=;
 b=UF/+Kt8W+5Pe4kXgZpqP4LGvnhjZAN98tfF7fTEXDyhyhRPHh/GKyYX8bngHN+XoYncHXo7heynZ8bruXnBPPFyuZ9ggsii5g3tt7hsP+Rn3GxRI4MymNAQEzfyFmFezowqzaFAXbHD+/edjGcWMNbN89oLZrX/UEkdTmngjKwM=
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (20.178.246.15) by
 MN2PR04MB5616.namprd04.prod.outlook.com (20.179.22.29) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2199.21; Thu, 29 Aug 2019 13:55:19 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::e1a5:8de2:c3b1:3fb0]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::e1a5:8de2:c3b1:3fb0%7]) with mapi id 15.20.2220.013; Thu, 29 Aug 2019
 13:55:19 +0000
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
Subject: [PATCH v6 01/21] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG interface
Thread-Topic: [PATCH v6 01/21] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG
 interface
Thread-Index: AQHVXnFlxmD3uFKGaEWHEErG4PUOPg==
Date: Thu, 29 Aug 2019 13:55:19 +0000
Message-ID: <20190829135427.47808-2-anup.patel@wdc.com>
References: <20190829135427.47808-1-anup.patel@wdc.com>
In-Reply-To: <20190829135427.47808-1-anup.patel@wdc.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: MAXPR0101CA0072.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:a00:e::34) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [49.207.51.114]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 9456a0b7-bc51-448b-ad35-08d72c888755
x-ms-office365-filtering-ht: Tenant
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(4534185)(7168020)(4627221)(201703031133081)(201702281549075)(8990200)(5600166)(711020)(4605104)(1401327)(4618075)(2017052603328)(7193020);SRVR:MN2PR04MB5616;
x-ms-traffictypediagnostic: MN2PR04MB5616:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MN2PR04MB561647D235EBC13242E727268DA20@MN2PR04MB5616.namprd04.prod.outlook.com>
wdcipoutbound: EOP-TRUE
x-ms-oob-tlc-oobclassifiers: OLM:147;
x-forefront-prvs: 0144B30E41
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(39860400002)(136003)(366004)(376002)(346002)(396003)(189003)(199004)(7416002)(52116002)(81166006)(316002)(6506007)(386003)(25786009)(7736002)(81156014)(305945005)(2906002)(36756003)(4744005)(71190400001)(14454004)(99286004)(1076003)(256004)(4326008)(66946007)(76176011)(66446008)(64756008)(66556008)(66476007)(102836004)(6116002)(50226002)(55236004)(476003)(6512007)(3846002)(71200400001)(5660300002)(26005)(186003)(44832011)(86362001)(66066001)(6436002)(446003)(8936002)(6486002)(110136005)(54906003)(2616005)(486006)(53936002)(11346002)(478600001)(8676002);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB5616;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 KVprQ3PWFdw+dmbfM7vwy+ukOZoLY2GcUVbECwYe1BX07r4ogG0VcNCwxPSN++4oArXdUEvOZg0KWNIv/bgAsd2Z2kJ7bTEaX1MJLPlEttxB5K+r2xCDxbsIGf+0A0mw68WD16uPbeEcafWinrXHU6Q6HlFKlUShr4Ud3UxQMXN3Su4DlFH7YldWbNkNtgs87Q/E3GcQ4dNvtaFtCMjKRGI3qZ5x8Hhcu4k2RD9hW8Ir7qDcVN2QyVOnZ36iY8FhkIhfAwJfbbRpmmD4Ya65A2YgfAiA7gL5pLSGRLgCGHaPLCsgKdhSt99A01cFyFgP6zeGpxWIcdoQ9GAhKiuw1/Sp8FCc7v5Lu3q2OW7oC581fTgVd+RUJ1EAcTEEZfk+MODwBEyF6E77SpVn0IZEPMloy2DyZgdmK5XeyXUeHKw=
Content-Type: text/plain; charset="iso-8859-1"
MIME-Version: 1.0
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 9456a0b7-bc51-448b-ad35-08d72c888755
X-MS-Exchange-CrossTenant-originalarrivaltime: 29 Aug 2019 13:55:19.7915
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 vkheH0Sb7iXbxgjl1O5wEI87GDrNWR/fyjCyDgh92XXN/Wu9YRGJBGAXVT8BUY9kQ3ZEsZbDAEFNgd9LsDCKDg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB5616
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We will be using ONE_REG interface accessing VCPU registers from
user-space hence we add KVM_REG_RISCV for RISC-V VCPU registers.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Alexander Graf <graf@amazon.com>
---
 include/uapi/linux/kvm.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: s390: improve documentation for S390_MEM_OP
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 11121305
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 20D9A174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 12:47:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 08FD7233FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 12:47:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727066AbfH2Mry (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 08:47:54 -0400
Received: from mx1.redhat.com ([209.132.183.28]:53560 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726518AbfH2Mry (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 08:47:54 -0400
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 4759C8980F3;
        Thu, 29 Aug 2019 12:47:54 +0000 (UTC)
Received: from localhost (dhcp-192-222.str.redhat.com [10.33.192.222])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 9B1125C1D6;
        Thu, 29 Aug 2019 12:47:51 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>, kvm@vger.kernel.org
Cc: David Hildenbrand <david@redhat.com>,
        Heiko Carstens <heiko.carstens@de.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Thomas Huth <thuth@redhat.com>, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH] KVM: s390: improve documentation for S390_MEM_OP
Date: Thu, 29 Aug 2019 14:47:46 +0200
Message-Id: <20190829124746.28665-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.67]);
 Thu, 29 Aug 2019 12:47:54 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Explicitly specify the valid ranges for size and ar, and reword
buf requirements a bit.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
supposed to go on top of "KVM: s390: Test for bad access register and
size at the start of S390_MEM_OP" (<20190829122517.31042-1-thuth@redhat.com>)
---
 Documentation/virt/kvm/api.txt | 14 ++++++++------
 1 file changed, 8 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: s390: Test for bad access register at the start of S390_MEM_OP
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11120997
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 807A414DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 10:54:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 60DAF2341B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 10:54:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728642AbfH2KyG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 06:54:06 -0400
Received: from mx1.redhat.com ([209.132.183.28]:3732 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727075AbfH2KyG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 06:54:06 -0400
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id BE03C3C93E;
        Thu, 29 Aug 2019 10:54:05 +0000 (UTC)
Received: from thuth.com (ovpn-116-53.ams2.redhat.com [10.36.116.53])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 676CD5C1D6;
        Thu, 29 Aug 2019 10:54:00 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>, kvm@vger.kernel.org
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Heiko Carstens <heiko.carstens@de.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: s390: Test for bad access register at the start of
 S390_MEM_OP
Date: Thu, 29 Aug 2019 12:53:56 +0200
Message-Id: <20190829105356.27805-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.39]);
 Thu, 29 Aug 2019 10:54:05 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the KVM_S390_MEM_OP ioctl is called with an access register >= 16,
then there is certainly a bug in the calling userspace application.
We check for wrong access registers, but only if the vCPU was already
in the access register mode before (i.e. the SIE block has recorded
it). The check is also buried somewhere deep in the calling chain (in
the function ar_translation()), so this is somewhat hard to find.

It's better to always report an error to the userspace in case this
field is set wrong, and it's safer in the KVM code if we block wrong
values here early instead of relying on a check somewhere deep down
the calling chain, so let's add another check to kvm_s390_guest_mem_op()
directly.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: selftests: Add a test for the KVM_S390_MEM_OP ioctl
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11120849
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 858D41395
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 10:21:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 66B2223407
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 10:21:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727344AbfH2KVA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 06:21:00 -0400
Received: from mx1.redhat.com ([209.132.183.28]:57672 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725782AbfH2KU7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 06:20:59 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 015E785536;
        Thu, 29 Aug 2019 10:20:59 +0000 (UTC)
Received: from thuth.com (ovpn-116-53.ams2.redhat.com [10.36.116.53])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8AB011001284;
        Thu, 29 Aug 2019 10:20:54 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>
Cc: linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org,
 David Hildenbrand <david@redhat.com>, Cornelia Huck <cohuck@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Subject: [PATCH] KVM: selftests: Add a test for the KVM_S390_MEM_OP ioctl
Date: Thu, 29 Aug 2019 12:20:50 +0200
Message-Id: <20190829102050.26703-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.28]);
 Thu, 29 Aug 2019 10:20:59 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Check that we can write and read the guest memory with this s390x
ioctl, and that some error cases are handled correctly.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 This test uses the ucall() interface, so this patch needs to be applied
 on top of my "Implement ucall() for s390x" patch (which is not merged to
 master yet)

 tools/testing/selftests/kvm/Makefile      |   1 +
 tools/testing/selftests/kvm/s390x/memop.c | 155 ++++++++++++++++++++++
 2 files changed, 156 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/s390x/memop.c

```
#### [PATCH v2 1/4] KVM: selftests: Move vm type into _vm_create() internally
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11120207
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 43F4F184E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 02:21:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2DBA52173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 02:21:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727008AbfH2CVg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 28 Aug 2019 22:21:36 -0400
Received: from mx1.redhat.com ([209.132.183.28]:43278 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727005AbfH2CVf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 28 Aug 2019 22:21:35 -0400
Received: from mail-pl1-f198.google.com (mail-pl1-f198.google.com
 [209.85.214.198])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id EC8F03B738
        for <kvm@vger.kernel.org>; Thu, 29 Aug 2019 02:21:34 +0000 (UTC)
Received: by mail-pl1-f198.google.com with SMTP id u24so1112546plq.22
        for <kvm@vger.kernel.org>; Wed, 28 Aug 2019 19:21:34 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=qq7LOeTMvAm3jyuMi4wh7zBYPMaFFoNWn+mmSJ8a4xo=;
        b=ehKkYCkyyZoKfUuJJtOopn+KCcABnRhG0BJ3xOZaCzeqPTzvOVBzptmOzn5XMfIoW/
         l8IgWNuDtaMd2nq5pGusMRXvN0HLStENmqOsfUQzAEaPxfZ2g2/87uCb8QKQQy8w9Fyz
         Zt1qkz6ttAwOInm/GHpFp/Qfy0urlpYelh0W/EoJ1GLc0NrIecDV9zcSLQR/ZMHkSpNM
         wnFPnMmyDTTxhIeJrnVGVEbvVKJRvIiPyaqd0VFhmjtl8bvpECqVehTiOKO+3GOJjzqA
         GZ7sNOV8YgkPl3K7rLY1WaUVuGXAK7hmr3GD2VAMhelYXs6ZHIXBc8nYJ8p/BJ65/cRp
         3yYQ==
X-Gm-Message-State: APjAAAWEubJGNGve/TBAf9WUNNns9ML2IInFArqSohUTlM0LggZZvI7X
        IbN4QMOxunsKACnILEofvKGtZSmumteno+QLk6q0iLV9Dw+n53Q/jXtfS5gAZOfFaxv7AiIGZww
        k7P1yuZepd/HA
X-Received: by 2002:aa7:8814:: with SMTP id c20mr8246426pfo.87.1567045294369;
        Wed, 28 Aug 2019 19:21:34 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqyLModn3+xEip4lnvaDVhJ+kNU0sZ7K/GfG106UEbF5i3YTiJO3tlCAHgpmfut3j7MVILz9Tg==
X-Received: by 2002:aa7:8814:: with SMTP id c20mr8246414pfo.87.1567045294104;
        Wed, 28 Aug 2019 19:21:34 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 j187sm750140pfg.178.2019.08.28.19.21.29
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 28 Aug 2019 19:21:33 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Thomas Huth <thuth@redhat.com>, Andrew Jones <drjones@redhat.com>,
 peterx@redhat.com
Subject: [PATCH v2 1/4] KVM: selftests: Move vm type into _vm_create()
 internally
Date: Thu, 29 Aug 2019 10:21:14 +0800
Message-Id: <20190829022117.10191-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20190829022117.10191-1-peterx@redhat.com>
References: <20190829022117.10191-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rather than passing the vm type from the top level to the end of vm
creation, let's simply keep that as an internal of kvm_vm struct and
decide the type in _vm_create().  Several reasons for doing this:

- The vm type is only decided by physical address width and currently
  only used in aarch64, so we've got enough information as long as
  we're passing vm_guest_mode into _vm_create(),

- This removes a loop dependency between the vm->type and creation of
  vms.  That's why now we need to parse vm_guest_mode twice sometimes,
  once in run_test() and then again in _vm_create().  The follow up
  patches will move on to clean up that as well so we can have a
  single place to decide guest machine types and so.

Note that this patch will slightly change the behavior of aarch64
tests in that previously most vm_create() callers will directly pass
in type==0 into _vm_create() but now the type will depend on
vm_guest_mode, however it shouldn't affect any user because all
vm_create() users of aarch64 will be using VM_MODE_DEFAULT guest
mode (which is VM_MODE_P40V48_4K) so at last type will still be zero.

Signed-off-by: Peter Xu <peterx@redhat.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/dirty_log_test.c  | 13 +++---------
 .../testing/selftests/kvm/include/kvm_util.h  |  3 +--
 tools/testing/selftests/kvm/lib/kvm_util.c    | 21 ++++++++++++-------
 3 files changed, 17 insertions(+), 20 deletions(-)

```
#### [kvm-unit-tests PATCH] Update travis.yml to use bionic instead of trusty
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11120439
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DEA7E1399
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 06:27:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C837C2189D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 06:27:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725973AbfH2G07 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 02:26:59 -0400
Received: from mx1.redhat.com ([209.132.183.28]:49184 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725782AbfH2G07 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 02:26:59 -0400
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 879778980F6
        for <kvm@vger.kernel.org>; Thu, 29 Aug 2019 06:26:59 +0000 (UTC)
Received: from thuth.com (ovpn-116-53.ams2.redhat.com [10.36.116.53])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 17FBC194B9;
        Thu, 29 Aug 2019 06:26:53 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>, =?utf-8?b?UmFk?=
	=?utf-8?b?aW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Drew Jones <drjones@redhat.com>, Laurent Vivier <lvivier@redhat.com>,
 David Hildenbrand <david@redhat.com>
Subject: [kvm-unit-tests PATCH] Update travis.yml to use bionic instead of
 trusty
Date: Thu, 29 Aug 2019 08:26:50 +0200
Message-Id: <20190829062650.19325-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.67]);
 Thu, 29 Aug 2019 06:26:59 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Ubuntu "trusty" is out of service, and at least for me, the Travis
jobs for kvm-unit-tests are failing because they can not find the
repositories anymore. Thus use a newer version of Ubuntu to do the
CI testing.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 .travis.yml | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC v1 1/9] KVM: x86: Add base address parameter for get_fixed_pmc function
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kang, Luwei" <luwei.kang@intel.com>
X-Patchwork-Id: 11120325
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B48F01395
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 05:38:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9D4E4233FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 05:38:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727380AbfH2Fiy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 01:38:54 -0400
Received: from mga05.intel.com ([192.55.52.43]:33970 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725847AbfH2Fiy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 01:38:54 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 28 Aug 2019 22:38:53 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,442,1559545200";
   d="scan'208";a="210416115"
Received: from icl-2s.bj.intel.com ([10.240.193.48])
  by fmsmga002.fm.intel.com with ESMTP; 28 Aug 2019 22:38:47 -0700
From: Luwei Kang <luwei.kang@intel.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com
Cc: sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        x86@kernel.org, ak@linux.intel.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Luwei Kang <luwei.kang@intel.com>
Subject: [RFC v1 1/9] KVM: x86: Add base address parameter for get_fixed_pmc
 function
Date: Thu, 29 Aug 2019 13:34:01 +0800
Message-Id: <1567056849-14608-2-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1567056849-14608-1-git-send-email-luwei.kang@intel.com>
References: <1567056849-14608-1-git-send-email-luwei.kang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

PEBS output Inte PT introduces some new MSRs (MSR_RELOAD_FIXED_CTRx)
for fixed function counters that use for autoload the preset value
after writing out a PEBS event.

Introduce base MSRs address parameter to make this function can get
performance monitor counter structure by MSR_RELOAD_FIXED_CTRx registers.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/kvm/pmu.h           |  5 ++---
 arch/x86/kvm/vmx/pmu_intel.c | 14 +++++++++-----
 2 files changed, 11 insertions(+), 8 deletions(-)

```
#### [PATCH kernel v3 1/5] powerpc/powernv/ioda: Split out TCE invalidation from TCE updates
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexey Kardashevskiy <aik@ozlabs.ru>
X-Patchwork-Id: 11120667
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A8CAB1398
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 08:53:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 90875215EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 08:53:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727017AbfH2Iw7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 04:52:59 -0400
Received: from ozlabs.ru ([107.173.13.209]:49770 "EHLO ozlabs.ru"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726009AbfH2Iw7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 04:52:59 -0400
Received: from fstn1-p1.ozlabs.ibm.com (localhost [IPv6:::1])
        by ozlabs.ru (Postfix) with ESMTP id ADD2FAE800AD;
        Thu, 29 Aug 2019 04:52:34 -0400 (EDT)
From: Alexey Kardashevskiy <aik@ozlabs.ru>
To: linuxppc-dev@lists.ozlabs.org
Cc: David Gibson <david@gibson.dropbear.id.au>,
        kvm-ppc@vger.kernel.org, kvm@vger.kernel.org,
        Alistair Popple <alistair@popple.id.au>,
        Alex Williamson <alex.williamson@redhat.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Alexey Kardashevskiy <aik@ozlabs.ru>
Subject: [PATCH kernel v3 1/5] powerpc/powernv/ioda: Split out TCE
 invalidation from TCE updates
Date: Thu, 29 Aug 2019 18:52:48 +1000
Message-Id: <20190829085252.72370-2-aik@ozlabs.ru>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20190829085252.72370-1-aik@ozlabs.ru>
References: <20190829085252.72370-1-aik@ozlabs.ru>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

At the moment updates in a TCE table are made by iommu_table_ops::exchange
which update one TCE and invalidates an entry in the PHB/NPU TCE cache
via set of registers called "TCE Kill" (hence the naming).
Writing a TCE is a simple xchg() but invalidating the TCE cache is
a relatively expensive OPAL call. Mapping a 100GB guest with PCI+NPU
passed through devices takes about 20s.

Thankfully we can do better. Since such big mappings happen at the boot
time and when memory is plugged/onlined (i.e. not often), these requests
come in 512 pages so we call call OPAL 512 times less which brings 20s
from the above to less than 10s. Also, since TCE caches can be flushed
entirely, calling OPAL for 512 TCEs helps skiboot [1] to decide whether
to flush the entire cache or not.

This implements 2 new iommu_table_ops callbacks:
- xchg_no_kill() to update a single TCE with no TCE invalidation;
- tce_kill() to invalidate multiple TCEs.
This uses the same xchg_no_kill() callback for IODA1/2.

This implements 2 new wrappers on top of the new callbacks similar to
the existing iommu_tce_xchg().

This does not use the new callbacks yet, the next patches will;
so this should not cause any behavioral change.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
 arch/powerpc/include/asm/iommu.h          | 17 ++++++++++++++
 arch/powerpc/kernel/iommu.c               | 27 +++++++++++++++++++++++
 arch/powerpc/platforms/powernv/pci-ioda.c | 12 ++++++++++
 3 files changed, 56 insertions(+)

```
#### [kvm-unit-tests PATCH 1/6] s390x: Use interrupts in SCLP and add locking
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11121267
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 682D214DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 12:15:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 46DDE22CF5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 12:15:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727565AbfH2MP0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 08:15:26 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:25300 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727176AbfH2MPZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 29 Aug 2019 08:15:25 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7TC744q076301
        for <kvm@vger.kernel.org>; Thu, 29 Aug 2019 08:15:25 -0400
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2upd9vavuy-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Thu, 29 Aug 2019 08:15:23 -0400
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Thu, 29 Aug 2019 13:15:21 +0100
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Thu, 29 Aug 2019 13:15:18 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7TCFHMD41615832
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Aug 2019 12:15:17 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A0D2B5205F;
        Thu, 29 Aug 2019 12:15:17 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.55.105])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 610285204E;
        Thu, 29 Aug 2019 12:15:16 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH 1/6] s390x: Use interrupts in SCLP and add
 locking
Date: Thu, 29 Aug 2019 14:14:54 +0200
X-Mailer: git-send-email 2.17.0
In-Reply-To: <20190829121459.1708-1-frankja@linux.ibm.com>
References: <20190829121459.1708-1-frankja@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19082912-0020-0000-0000-000003653F41
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082912-0021-0000-0000-000021BA977E
Message-Id: <20190829121459.1708-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-29_06:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908290135
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We need to properly implement interrupt handling for SCLP, because on
z/VM and LPAR SCLP calls are not synchronous!

Also with smp CPUs have to compete for sclp. Let's add some locking,
so they execute sclp calls in an orderly fashion and don't compete for
the data buffer.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/interrupt.h |  2 ++
 lib/s390x/interrupt.c     | 12 +++++++--
 lib/s390x/sclp-console.c  |  2 ++
 lib/s390x/sclp.c          | 54 +++++++++++++++++++++++++++++++++++++--
 lib/s390x/sclp.h          |  3 +++
 5 files changed, 69 insertions(+), 4 deletions(-)

```
#### [PATCH v2] cpuidle-haltpoll: Enable kvm guest polling when dedicated physical CPUs are available
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11120659
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 591EE14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 08:50:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 359D6233FF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 08:50:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="it190hsU"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727136AbfH2IuG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 04:50:06 -0400
Received: from mail-pg1-f195.google.com ([209.85.215.195]:38495 "EHLO
        mail-pg1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726070AbfH2IuF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 04:50:05 -0400
Received: by mail-pg1-f195.google.com with SMTP id e11so1232783pga.5;
        Thu, 29 Aug 2019 01:50:05 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=llEqJbQquZmg44EVVsIz+rUKn+1paMeV1ggm5tExqbs=;
        b=it190hsUfuvXSmKudgY2NAWTdypFmbgxNqPExPyVrNNFS0MisuUL9cTukpxI8olh9l
         UFmT2BD3K1Vkf/Kdj/pZrsvkHOsCS1Z2nkobny+wyXTG43LbF7JNCuhmdlePewYzBUHG
         XBZCI4fQgeIkafqYzQcG9U0KXkJquef7+a61Nf/IG0mTExZ02Lvr9IDAhYmYJVRNllyL
         zEH+8LKep0lVzXoRyflI3hpv625uucMeNUFOOOnt5TLtJQ1kNKYyvUVW6VF6LgP8c9IE
         klPnqnO/3RK4pTexPkiNRdGRpOawGvmiSn+IXtXBexs3gwAgIzsVv1ByY3uCAa4wdMfe
         6esQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=llEqJbQquZmg44EVVsIz+rUKn+1paMeV1ggm5tExqbs=;
        b=fpLID5M+NDVyt6TFNrnevbKgBSiG2jLfmT6y6BQX0Iu51/YzuEnovSe+8kGc44EpXp
         5cFLZnYqiShmSRqU9lIATmWjnrOZXkplD6eHSj2BJ99x6H3W9nV3d1w7tWTeSGKjeHiN
         C3ulWv2RLhIITCuqZd3JSQ8o/LqUnUsIvkJfdS/gmeWVJH0QOSUFf5C9ZCshtiLfgPon
         ZUeJwxKx5Qyb7fxkpDglxKRs8aXsniGHk6sS5682ihllAIINZ8pYaS5hcHfOrfCuO4/g
         ycABbw0rJdgCGsx3fUR+6hh3uIdnD7Pn7Jf01Oy9rihTKOIy1XcZV4HAobev7pr8+tu9
         JiLg==
X-Gm-Message-State: APjAAAVga2cKjz32PTrKwE8w6PMKOKnRSx2kfk3Hrtn7DNfeRfIzV4Ai
        pxVbg0dq9pljPrmlrT80/55B2GjN
X-Google-Smtp-Source: 
 APXvYqybYVCW4WKSbwOvYFr3ALtr+sJj+BYwgH4cZhlDpcD/yLnjfIWTxgcxAOjUwbQteavkBdSJ3w==
X-Received: by 2002:a17:90a:e392:: with SMTP id
 b18mr8352385pjz.140.1567068605013;
        Thu, 29 Aug 2019 01:50:05 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 t6sm1591693pjy.18.2019.08.29.01.50.02
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Thu, 29 Aug 2019 01:50:04 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 "Rafael J . Wysocki" <rafael.j.wysocki@intel.com>
Subject: [PATCH v2] cpuidle-haltpoll: Enable kvm guest polling when dedicated
 physical CPUs are available
Date: Thu, 29 Aug 2019 16:49:57 +0800
Message-Id: <1567068597-22419-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

The downside of guest side polling is that polling is performed even 
with other runnable tasks in the host. However, even if poll in kvm 
can aware whether or not other runnable tasks in the same pCPU, it 
can still incur extra overhead in over-subscribe scenario. Now we can 
just enable guest polling when dedicated pCPUs are available.

Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Cc: Rafael J. Wysocki <rafael.j.wysocki@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * export kvm_arch_para_hints to fix haltpoll driver build as module error
 * just disable haltpoll driver instead of both driver and governor 
   since KVM_HINTS_REALTIME is not defined in other arches, and governor 
   doesn't depend on x86, to fix the warning on powerpc

 arch/x86/kernel/kvm.c              | 1 +
 drivers/cpuidle/cpuidle-haltpoll.c | 3 ++-
 2 files changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v2] cpuidle-haltpoll: vcpu hotplug support
##### From: Joao Martins <joao.m.martins@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joao Martins <joao.m.martins@oracle.com>
X-Patchwork-Id: 11121653
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8D15A14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 15:13:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 62E7720644
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 15:13:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="QsmxoNNJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727403AbfH2PNY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 11:13:24 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:36522 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727144AbfH2PNY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 11:13:24 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7TF9Ea7185188;
        Thu, 29 Aug 2019 15:10:39 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-type :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=CKit7+Ighkvtwrce/t6NZ2djJ2x69q1/2NpRpmKU0Ns=;
 b=QsmxoNNJdYXGkfCwBAdxnOds9NtfKOWPhM7yWMYkqJsjLZio52x1F0o1a0MLl6PBSHm+
 eW10j8QgmTkIntRVG6Kdnpn6JmDkBu4y8Y05Vx8RJO7ANs8reggGPtY9fOuVF+leYvCp
 J4X/4VyJm1XgoU/IKSdydUFznlYLmZNkmHVC2blDERn8Ce+P556P48iXFQF4Ypqk1hOJ
 SUhHqgzh9coxKr30qoXfquUOksXPaEqJP0mwAggdsfczqlb9M+NXXra/cvXDFXINgC6D
 nKmmtBq+deAGIJW3lwK6zOgGhiChBBBJ9dVs4YLLbKtG5vEjGsG1QB9GKY5q+p3VJtLl 5w==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2120.oracle.com with ESMTP id 2uph30g0gw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Aug 2019 15:10:39 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7TF9TPI137674;
        Thu, 29 Aug 2019 15:10:38 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3030.oracle.com with ESMTP id 2unvu049sd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 29 Aug 2019 15:10:38 +0000
Received: from abhmp0019.oracle.com (abhmp0019.oracle.com [141.146.116.25])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x7TFAaxG030672;
        Thu, 29 Aug 2019 15:10:36 GMT
Received: from paddy.uk.oracle.com (/10.175.160.184)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 29 Aug 2019 08:10:35 -0700
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
Subject: [PATCH v2] cpuidle-haltpoll: vcpu hotplug support
Date: Thu, 29 Aug 2019 16:10:27 +0100
Message-Id: <20190829151027.9930-1-joao.m.martins@oracle.com>
X-Mailer: git-send-email 2.11.0
MIME-Version: 1.0
Content-Type: text/plain; charset=utf-8
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9363
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=3
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=996
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1908290164
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9363
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=3 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1908290164
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
of the present cpus through cpuhp_setup_state() callback and future
ones that get onlined. This mimmics similar logic that intel_idle does.

Fixes: fa86ee90eb11 ("add cpuidle-haltpoll driver")
Signed-off-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Reviewed-by: Marcelo Tosatti <mtosatti@redhat.com>
---
v2:
* move cpus_read_unlock() right after unregistering all cpuidle_devices;
(Marcello Tosatti)
* redundant usage of cpuidle_unregister() when only
cpuidle_unregister_driver() suffices; (Marcelo Tosatti)
* cpuhp_setup_state() returns a state (> 0) on success with CPUHP_AP_ONLINE_DYN
thus we set @ret to 0
---
 arch/x86/include/asm/cpuidle_haltpoll.h |  4 +-
 arch/x86/kernel/kvm.c                   | 18 +++----
 drivers/cpuidle/cpuidle-haltpoll.c      | 67 +++++++++++++++++++++++--
 include/linux/cpuidle_haltpoll.h        |  4 +-
 4 files changed, 72 insertions(+), 21 deletions(-)

```
#### [PATCH v2] KVM: s390: Test for bad access register and size at the start of S390_MEM_OP
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11121281
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 373C614E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 12:25:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 200EE21726
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 12:25:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727223AbfH2MZ0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 08:25:26 -0400
Received: from mx1.redhat.com ([209.132.183.28]:50806 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725990AbfH2MZ0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 08:25:26 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id AFF0930832DA;
        Thu, 29 Aug 2019 12:25:25 +0000 (UTC)
Received: from thuth.com (ovpn-116-53.ams2.redhat.com [10.36.116.53])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0396310016EB;
        Thu, 29 Aug 2019 12:25:20 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>, kvm@vger.kernel.org
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Heiko Carstens <heiko.carstens@de.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2] KVM: s390: Test for bad access register and size at the
 start of S390_MEM_OP
Date: Thu, 29 Aug 2019 14:25:17 +0200
Message-Id: <20190829122517.31042-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.44]);
 Thu, 29 Aug 2019 12:25:25 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the KVM_S390_MEM_OP ioctl is called with an access register >= 16,
then there is certainly a bug in the calling userspace application.
We check for wrong access registers, but only if the vCPU was already
in the access register mode before (i.e. the SIE block has recorded
it). The check is also buried somewhere deep in the calling chain (in
the function ar_translation()), so this is somewhat hard to find.

It's better to always report an error to the userspace in case this
field is set wrong, and it's safer in the KVM code if we block wrong
values here early instead of relying on a check somewhere deep down
the calling chain, so let's add another check to kvm_s390_guest_mem_op()
directly.

We also should check that the "size" is non-zero here (thanks to Janosch
Frank for the hint!). If we do not check the size, we could call vmalloc()
with this 0 value, and this will cause a kernel warning.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 v2: Check mop->size to be non-zero

 arch/s390/kvm/kvm-s390.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: selftests: Add a test for the KVM_S390_MEM_OP ioctl
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11121263
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CE1C6112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 12:14:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id ACB782080F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 12:14:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727454AbfH2MOV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 08:14:21 -0400
Received: from mx1.redhat.com ([209.132.183.28]:64869 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726983AbfH2MOV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 08:14:21 -0400
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 6EB8B3082145;
        Thu, 29 Aug 2019 12:14:20 +0000 (UTC)
Received: from thuth.com (ovpn-116-53.ams2.redhat.com [10.36.116.53])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5024060CD0;
        Thu, 29 Aug 2019 12:14:16 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>
Cc: linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org,
 David Hildenbrand <david@redhat.com>, Cornelia Huck <cohuck@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Subject: [PATCH v2] KVM: selftests: Add a test for the KVM_S390_MEM_OP ioctl
Date: Thu, 29 Aug 2019 14:14:12 +0200
Message-Id: <20190829121412.30194-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.42]);
 Thu, 29 Aug 2019 12:14:20 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Check that we can write and read the guest memory with this s390x
ioctl, and that some error cases are handled correctly.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 v2: Check the ioctl also with "size" set to 0

 tools/testing/selftests/kvm/Makefile      |   1 +
 tools/testing/selftests/kvm/s390x/memop.c | 165 ++++++++++++++++++++++
 2 files changed, 166 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/s390x/memop.c

```
#### [PATCH v3] KVM: selftests: Add a test for the KVM_S390_MEM_OP ioctl
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11121317
Return-Path: <SRS0=pZ1+=WZ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A2B0D112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 13:07:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 81FE6206BB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 29 Aug 2019 13:07:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728053AbfH2NHo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 29 Aug 2019 09:07:44 -0400
Received: from mx1.redhat.com ([209.132.183.28]:41016 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725990AbfH2NHm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 29 Aug 2019 09:07:42 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 7AA35308FB82;
        Thu, 29 Aug 2019 13:07:41 +0000 (UTC)
Received: from thuth.com (ovpn-116-53.ams2.redhat.com [10.36.116.53])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3CE1110016EB;
        Thu, 29 Aug 2019 13:07:35 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>
Cc: linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org,
 David Hildenbrand <david@redhat.com>, Cornelia Huck <cohuck@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Subject: [PATCH v3] KVM: selftests: Add a test for the KVM_S390_MEM_OP ioctl
Date: Thu, 29 Aug 2019 15:07:32 +0200
Message-Id: <20190829130732.580-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.43]);
 Thu, 29 Aug 2019 13:07:41 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Check that we can write and read the guest memory with this s390x
ioctl, and that some error cases are handled correctly.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 v3:
 - Replaced wrong copy-n-pasted report string with a proper one
 - Check for errno after calling the ioctl with size = 0
 
 tools/testing/selftests/kvm/Makefile      |   1 +
 tools/testing/selftests/kvm/s390x/memop.c | 166 ++++++++++++++++++++++
 2 files changed, 167 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/s390x/memop.c

```
