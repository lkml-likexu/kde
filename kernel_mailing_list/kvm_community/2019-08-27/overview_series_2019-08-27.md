#### [PATCH 1/3] KVM: x86: fix wrong return codeThread-Topic: [PATCH 1/3] KVM: x86: fix wrong return code
##### From: Jan Dakinevich <jan.dakinevich@virtuozzo.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jan Dakinevich <jan.dakinevich@virtuozzo.com>
X-Patchwork-Id: 11116901
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC45714DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:07:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AFD9E2189D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:07:29 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=virtuozzo.com header.i=@virtuozzo.com
 header.b="Ubt7/bPO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726278AbfH0NHJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 09:07:09 -0400
Received: from mail-eopbgr30119.outbound.protection.outlook.com
 ([40.107.3.119]:35904
        "EHLO EUR03-AM5-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726170AbfH0NHG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 09:07:06 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=E9gtfSZk9QPeRHJrMrgZ4WFRMOUEvOSqGikHLrOQ4zR+atZB6TCIFN5nvFMMGj0+s+1zULE48HLM4nsM6SzWojHq6cR3sDe6jC9fZFUHVTKaMalfsiUWiXjaGLlUu6jEWkxCVwBNqrp6RjHOr+wN3EAwMlB+VawW/UIP909f7gf2QprsJFb7DIrn18835JvN7ypqUZWJC57pYrBLfKGZY9F2Yd1FqUsPBF1AbXGcG2iHoyiZ4PgooUUmBlYJsUWnz8pqvlSa0KRGAi8xmf/SlVXGVr3Cz2TvD+KSITWB4zW10nTSQ5kUxI7Rr47o7bSageNvE8ghzg0QkizpDBkc2A==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=svMO617yxV9WjSTdFYoLpdoZVKjKefsZQpgPhyC5Fp4=;
 b=MpudOCttzB2+S2WFE9mHf+5/c+xn85Z5vgNzRlvNaq+lSfqHJX4ZhfiWftdUOnUoiMeQ+2xtOMVjQnR6m+b1Ao4ACvqae/FbuBSXSmoP3JZBHj8n3mZjaWaFwd45lXv5mCwILkvucDuNV+x7SB0ZS2Gbpvjyau6rQ9D98aEZFbCCFCn4mMXSVjBGboYpzVQReBu6DCL0klhqYBpypS5+wfz2s7tz6bdSoTGXir3mO3MUjwv906Xm2F48tKjFI3bmqBIrudjfb/XqgLgmNcqix3lCSKljcnPF2BT3bG4f2Q4aC7UGE0EpDGzne9GsZLR7VaAYSGXRivWA51H3mAefMg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=svMO617yxV9WjSTdFYoLpdoZVKjKefsZQpgPhyC5Fp4=;
 b=Ubt7/bPO+Xm038/qVDR8KdiZpA3fzuP4i3EbBtXLCO8qfVcV1sEdWkkF7IGi8qO/RTqpIx3nX3lVLVisr0yEFgxy/ZHyTq3Qp2HJtHnCjm51TJRY2MVMo5huLLJugnAADV0qNIOYXeBcd5+HdEwjyGW9K3tCp/4/8nOtespXBo4=
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com (10.170.236.143) by
 VI1PR08MB3471.eurprd08.prod.outlook.com (20.177.59.25) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2199.21; Tue, 27 Aug 2019 13:07:04 +0000
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a]) by VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a%3]) with mapi id 15.20.2178.023; Tue, 27 Aug 2019
 13:07:04 +0000
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
Subject: [PATCH 1/3] KVM: x86: fix wrong return code
Thread-Topic: [PATCH 1/3] KVM: x86: fix wrong return code
Thread-Index: AQHVXNhSm57U5w68n0a9k1WFYt6uIw==
Date: Tue, 27 Aug 2019 13:07:04 +0000
Message-ID: <1566911210-30059-2-git-send-email-jan.dakinevich@virtuozzo.com>
References: <1566911210-30059-1-git-send-email-jan.dakinevich@virtuozzo.com>
In-Reply-To: <1566911210-30059-1-git-send-email-jan.dakinevich@virtuozzo.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: HE1PR0802CA0004.eurprd08.prod.outlook.com
 (2603:10a6:3:bd::14) To VI1PR08MB2782.eurprd08.prod.outlook.com
 (2603:10a6:802:19::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=jan.dakinevich@virtuozzo.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.1.4
x-originating-ip: [185.231.240.5]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: bb45f6f4-cc33-4b60-90ff-08d72aef74f6
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(4534185)(4627221)(201703031133081)(201702281549075)(8990200)(5600166)(711020)(4605104)(1401327)(2017052603328)(7193020);SRVR:VI1PR08MB3471;
x-ms-traffictypediagnostic: VI1PR08MB3471:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <VI1PR08MB3471FF0F88E640E8371AD4C08AA00@VI1PR08MB3471.eurprd08.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:6790;
x-forefront-prvs: 0142F22657
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(39840400004)(396003)(376002)(366004)(346002)(136003)(199004)(189003)(25786009)(54906003)(6436002)(6512007)(5660300002)(64756008)(7736002)(26005)(4744005)(66946007)(36756003)(66446008)(186003)(66556008)(102836004)(7416002)(305945005)(50226002)(2906002)(52116002)(11346002)(486006)(476003)(2616005)(14444005)(6506007)(386003)(44832011)(76176011)(446003)(256004)(66066001)(99286004)(316002)(66476007)(53936002)(14454004)(5640700003)(2501003)(81156014)(6116002)(6486002)(71200400001)(2351001)(81166006)(6916009)(4326008)(86362001)(3846002)(8676002)(71190400001)(478600001)(8936002);DIR:OUT;SFP:1102;SCL:1;SRVR:VI1PR08MB3471;H:VI1PR08MB2782.eurprd08.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: virtuozzo.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 PMJObK75TD/Un6nmv5QMkeoE11yAPQQOaRm2D3fBt+UtVTclu5GkeoklEerNgqdDmGuv5cQsK+UNirnN1G5Kx8j6nmPd6T3CUtk3AvqItB/wX4xfdWSJf8RdTdxU/Cv347PxRjRCyxervG5xk5KWjQh/pGFXgK95l7JEWxmO+f0BjocQeg1PphaBo6UIKTwQl+/nkDId5qdWsgRrkDFKNHJM23jQmdl74JbUo34nWmMJ1wUrcIW1f6OXW1yJ446ZkfSuZQRomTdN3kxRFQfze26sCD/oYz7xNRdavKHsr1M9RdsKZ5iVeiYFkPtKC9CCPAc/rkvJ/MccWBppJUMqhckdmFhA5aXoC0KwV2f7/Hncs7fp0nTnhkZ1zp/YT8+fd2cwP+Bq849uzoj3zgCiux02XtPWYTQTUjaAZv2riEE=
Content-Type: text/plain; charset="iso-8859-2"
MIME-Version: 1.0
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 bb45f6f4-cc33-4b60-90ff-08d72aef74f6
X-MS-Exchange-CrossTenant-originalarrivaltime: 27 Aug 2019 13:07:04.7828
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 1YneTsPm869tBdRtWEp5o2kfweg3PnVCiAupsk0onmZtt9VD0+9lf0gG5Y/pxR7AjSKWYtxHGlzevps5ft+/0dIrHlqlCxRYTvuQUuWVeNU=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: VI1PR08MB3471
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

x86_emulate_instruction(), the caller of x86_decode_insn(), expects
that x86_decode_insn()'s returning value belongs to EMULATION_* name
space. However, this function may return value from X86EMUL_* name
space.

Although, the code behaves properly (because both X86EMUL_CONTINUE and
EMULATION_OK are equal to 0) this change makes code more consistent and
it is required for further fixes.

Cc: Denis Lunev <den@virtuozzo.com>
Cc: Roman Kagan <rkagan@virtuozzo.com>
Cc: Denis Plotnikov <dplotnikov@virtuozzo.com>
Signed-off-by: Jan Dakinevich <jan.dakinevich@virtuozzo.com>
---
 arch/x86/kvm/emulate.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [GIT PULL] Please pull my kvm-ppc-fixes-5.3-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11116527
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A092B112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 09:53:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 773102186A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 09:53:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="drvcqPoX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729523AbfH0Jxq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 05:53:46 -0400
Received: from ozlabs.org ([203.11.71.1]:58623 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728883AbfH0Jxp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 05:53:45 -0400
Received: by ozlabs.org (Postfix, from userid 1003)
        id 46Hkj34P0Dz9sBF; Tue, 27 Aug 2019 19:53:43 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1566899623; bh=t6/73EjuF6lJD3vndlHCMS7wuROyK8CMl9+AMLeKESY=;
        h=Date:From:To:Cc:Subject:From;
        b=drvcqPoXL2O5q/SiHCsJcM00v3xX/xRnF6GtGEbpZR+8fhkU+8EnAxFSaumKWmc/Q
         7AdQdmdRGr2Xl1yLRuq0kVGQJ/zPB6NXghY8zJmYaJBeBn6BBmxwar02Z0ZFRVMlTJ
         qjZArhmMIeOig0++PCIr3kV+Q1VzdpLJYSbGkk6k6cJLSqWBp/4tTmlrtcwtazL5lH
         lm4TYBAu9YPdS+EyuYZwPBAH+7+oH+8I294253uidNQ/fVRqi02pxnnPf1CaAQjoQK
         bVYu4hoc8mSEFi8OFkx2L2df6gJWcfz7W9Fjfg552ptlZ/1vRix3OGMF3GYxPmkYU5
         6U2zPqPMKKy8w==
Date: Tue, 27 Aug 2019 19:53:38 +1000
From: Paul Mackerras <paulus@ozlabs.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org, David Gibson <david@gibson.dropbear.id.au>
Subject: [GIT PULL] Please pull my kvm-ppc-fixes-5.3-1 tag
Message-ID: <20190827095338.GA22875@blackberry>
MIME-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Content-Disposition: inline
User-Agent: Mutt/1.5.24 (2015-08-30)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo or Radim,

Please do a pull from my kvm-ppc-fixes-5.3-1 tag to get one small
commit which I would like to go to Linus for 5.3 if possible, since it
fixes a bug where a malicious guest could cause host CPUs to hang
hard.  The fix is small and obviously correct.

Thanks,
Paul.

The following changes since commit e4427372398c31f57450565de277f861a4db5b3b:

  selftests/kvm: make platform_info_test pass on AMD (2019-08-21 19:08:18 +0200)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-fixes-5.3-1

for you to fetch changes up to ddfd151f3def9258397fcde7a372205a2d661903:

  KVM: PPC: Book3S: Fix incorrect guest-to-user-translation error handling (2019-08-27 10:59:30 +1000)

----------------------------------------------------------------
KVM/PPC fix for 5.3

- Fix bug which could leave locks locked in the host on return
  to a guest.

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      KVM: PPC: Book3S: Fix incorrect guest-to-user-translation error handling

 arch/powerpc/kvm/book3s_64_vio.c    | 6 ++++--
 arch/powerpc/kvm/book3s_64_vio_hv.c | 6 ++++--
 2 files changed, 8 insertions(+), 4 deletions(-)
```
#### [PATCH v1 1/5] mdev: Introduce sha1 based mdev alias
##### From: Parav Pandit <parav@mellanox.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Parav Pandit <parav@mellanox.com>
X-Patchwork-Id: 11117397
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 355A014E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 19:17:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1762E2186A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 19:17:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730992AbfH0TRI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 15:17:08 -0400
Received: from mail-il-dmz.mellanox.com ([193.47.165.129]:38863 "EHLO
        mellanox.co.il" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730958AbfH0TRI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 15:17:08 -0400
Received: from Internal Mail-Server by MTLPINE1 (envelope-from
 parav@mellanox.com)
        with ESMTPS (AES256-SHA encrypted); 27 Aug 2019 22:17:01 +0300
Received: from sw-mtx-036.mtx.labs.mlnx (sw-mtx-036.mtx.labs.mlnx
 [10.12.150.149])
        by labmailer.mlnx (8.13.8/8.13.8) with ESMTP id x7RJGuGr026842;
        Tue, 27 Aug 2019 22:16:59 +0300
From: Parav Pandit <parav@mellanox.com>
To: alex.williamson@redhat.com, jiri@mellanox.com,
        kwankhede@nvidia.com, cohuck@redhat.com, davem@davemloft.net
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        netdev@vger.kernel.org, Parav Pandit <parav@mellanox.com>
Subject: [PATCH v1 1/5] mdev: Introduce sha1 based mdev alias
Date: Tue, 27 Aug 2019 14:16:50 -0500
Message-Id: <20190827191654.41161-2-parav@mellanox.com>
X-Mailer: git-send-email 2.19.2
In-Reply-To: <20190827191654.41161-1-parav@mellanox.com>
References: <20190826204119.54386-1-parav@mellanox.com>
 <20190827191654.41161-1-parav@mellanox.com>
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
 drivers/vfio/mdev/mdev_core.c    | 110 ++++++++++++++++++++++++++++++-
 drivers/vfio/mdev/mdev_private.h |   5 +-
 drivers/vfio/mdev/mdev_sysfs.c   |  13 ++--
 include/linux/mdev.h             |   4 ++
 4 files changed, 122 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Check for MMU ready on piggybacked virtual cores
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11115925
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5CA561398
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 01:35:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 25FE720850
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 01:35:46 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="jy39pw7g"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728372AbfH0Bfp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 21:35:45 -0400
Received: from bilbo.ozlabs.org ([203.11.71.1]:37169 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727646AbfH0Bfp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 21:35:45 -0400
Received: by ozlabs.org (Postfix, from userid 1003)
        id 46HWfQ70K5z9sBF; Tue, 27 Aug 2019 11:35:42 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1566869742; bh=9E9V0XgWnpOd14JVRGHFpTnEq0jq/mMU+nBl6t5zops=;
        h=Date:From:To:Cc:Subject:From;
        b=jy39pw7gkEi0bqbY6XV+ca45NcPu8pBdAS0qqKmFxEeAU7plvOSWeLa/zISu5VJnw
         hGJt7sWhLl4JPJzN3k0sQ9e9aja7tLOWsfmgieOUlj+YZNWe+tu2/aXHonwyd8Mkcl
         ifDmw8tuFvV0Z/M2OAqt/LWLjaCAbP0csddV6z6AVPA3Dt5iQ9+Po5X/02yk+KAXF6
         6DlF/Ibw5SMeGPL5k6Hh++606GDAhVy43nkdEnjyVdNa6p2gh/I/kp2+Fu4pRyTnfz
         6TFmBGqpCg0B9iZOEve2KZtP3jrqKyFebvJ4GdHQta1cNyM49hYtw8a0vJgLJknssN
         t/esBTEcY+upA==
Date: Tue, 27 Aug 2019 11:31:37 +1000
From: Paul Mackerras <paulus@ozlabs.org>
To: kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org, David Gibson <david@gibson.dropbear.id.au>
Subject: [PATCH] KVM: PPC: Book3S HV: Check for MMU ready on piggybacked
 virtual cores
Message-ID: <20190827013137.GB16075@blackberry>
MIME-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Content-Disposition: inline
User-Agent: Mutt/1.5.24 (2015-08-30)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When we are running multiple vcores on the same physical core, they
could be from different VMs and so it is possible that one of the
VMs could have its arch.mmu_ready flag cleared (for example by a
concurrent HPT resize) when we go to run it on a physical core.
We currently check the arch.mmu_ready flag for the primary vcore
but not the flags for the other vcores that will be run alongside
it.  This adds that check, and also a check when we select the
secondary vcores from the preempted vcores list.

Cc: stable@vger.kernel.org # v4.14+
Fixes: 38c53af85306 ("KVM: PPC: Book3S HV: Fix exclusion between HPT resizing and other HPT updates")
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_hv.c | 15 ++++++++++-----
 1 file changed, 10 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Don't lose pending doorbell request on migration on P9
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11115927
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6C1C414DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 01:35:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 419EB217F5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 01:35:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="rjA0+iXl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728324AbfH0Bfp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 26 Aug 2019 21:35:45 -0400
Received: from ozlabs.org ([203.11.71.1]:39169 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726257AbfH0Bfp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 26 Aug 2019 21:35:45 -0400
Received: by ozlabs.org (Postfix, from userid 1003)
        id 46HWfQ58YLz9sDB; Tue, 27 Aug 2019 11:35:42 +1000 (AEST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1566869742; bh=5tkDZ0zmgPynefhNwg4H1TzlSKE/xtMuzKvCKr0zR50=;
        h=Date:From:To:Cc:Subject:From;
        b=rjA0+iXlcGHmpOPwTgpWCEYWJS6Jg6uYQapAlN3JHrbwqVsNuzLFvEs5e/aevxycv
         xqGhv+AdLGJZRtxNixTfI6LPL9fzwIskV6TAVCyVTnBYV9vBi7tPdXgljWdxHmBRGu
         wmN7lfwmD2g6z0e9o8al9XwF4qvXyuLZ6CWlOgMGVOPPLgmk95C9sbxh/NYpnIuSyk
         fkxBHtoDWOdwSOo+0WJwRMCLF7eClt6lkJt2ZuFXDoiHRtov/SZYCyML/Ew+dh7a40
         /W/clBUy9HxfVHf5cOrCEl5VAXLP1AasQHKykLmO6nVeo6ml/oLqp/5a7bF/XF6SzU
         0OrVMxr6t3LBQ==
Date: Tue, 27 Aug 2019 11:35:40 +1000
From: Paul Mackerras <paulus@ozlabs.org>
To: kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org, David Gibson <david@gibson.dropbear.id.au>
Subject: [PATCH] KVM: PPC: Book3S HV: Don't lose pending doorbell request on
 migration on P9
Message-ID: <20190827013540.GC16075@blackberry>
MIME-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Content-Disposition: inline
User-Agent: Mutt/1.5.24 (2015-08-30)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On POWER9, when userspace reads the value of the DPDES register on a
vCPU, it is possible for 0 to be returned although there is a doorbell
interrupt pending for the vCPU.  This can lead to a doorbell interrupt
being lost across migration.  If the guest kernel uses doorbell
interrupts for IPIs, then it could malfunction because of the lost
interrupt.

This happens because a newly-generated doorbell interrupt is signalled
by setting vcpu->arch.doorbell_request to 1; the DPDES value in
vcpu->arch.vcore->dpdes is not updated, because it can only be updated
when holding the vcpu mutex, in order to avoid races.

To fix this, we OR in vcpu->arch.doorbell_request when reading the
DPDES value.

Cc: stable@vger.kernel.org # v4.13+
Fixes: 579006944e0d ("KVM: PPC: Book3S HV: Virtualize doorbell facility on POWER9")
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
Tested-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
 arch/powerpc/kvm/book3s_hv.c | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH 1/4] KVM: selftests: Move vm type into _vm_create() internally
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11116911
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 446F914F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:11:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 22E802184D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:11:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729695AbfH0NKe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 09:10:34 -0400
Received: from mx1.redhat.com ([209.132.183.28]:56760 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727138AbfH0NKd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 09:10:33 -0400
Received: from mail-pl1-f197.google.com (mail-pl1-f197.google.com
 [209.85.214.197])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id DC2B291764
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 13:10:32 +0000 (UTC)
Received: by mail-pl1-f197.google.com with SMTP id g9so11978071plo.21
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 06:10:32 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=aWwznrHbktCysNaadwrasS9SqCvefDZhspO3NcJLJag=;
        b=sTHaPjpZBaZPMoh/yK/cCPTZrdvnvMZQl4h4cBo+YvqHyTjnQYAgxRkmY35FDjVsar
         Ia7vmOw1wfIY/DfhKHXREVUJ20dygCoBp3BgQ9wWGSwHF1LIRUqlqmGftLyqtcQFSuUi
         +aRMmnSLo5NZ6xYiyYL6ro1Jjj1gpju9WUfwDuw3vIWGK6sy4kFJ19siHJI4HBotHGgs
         xKUj38XnutGFXNMtyxoi/LKDRN3ohRT4Cd8v3e4b6ydeFO/2yI9xOjrjb+4gCVMK1B7T
         8JsgQ5ShKZHUtEoBl3MaiCsxR/sDBH5Bkf3D7T8WvT01Yrtc5gmEwy7nwobW9e8QsY/B
         E5MA==
X-Gm-Message-State: APjAAAUg3P2mR02IV5JKfeB202rJ5AzA0nezfDCTfHH04edMVUuks4mL
        iun6DQFuq6RTCwGGhKA377Z5abuHTgYU0rmtS35m9re76JuUhOGGwT9XDeDrtDd1zlIx+5emEoC
        P8n0tHj2tL0kr
X-Received: by 2002:aa7:92d1:: with SMTP id
 k17mr14949042pfa.160.1566911432417;
        Tue, 27 Aug 2019 06:10:32 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqx48z0+CCC4eCbKlPab7hOWex06NfVdp+8FiKZGqLijkMIxQzf/mIKsGnead5K0rz9xsUdHIQ==
X-Received: by 2002:aa7:92d1:: with SMTP id
 k17mr14949023pfa.160.1566911432195;
        Tue, 27 Aug 2019 06:10:32 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 o67sm24393050pfb.39.2019.08.27.06.10.28
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 27 Aug 2019 06:10:31 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Thomas Huth <thuth@redhat.com>, Andrew Jones <drjones@redhat.com>,
 peterx@redhat.com
Subject: [PATCH 1/4] KVM: selftests: Move vm type into _vm_create() internally
Date: Tue, 27 Aug 2019 21:10:12 +0800
Message-Id: <20190827131015.21691-2-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20190827131015.21691-1-peterx@redhat.com>
References: <20190827131015.21691-1-peterx@redhat.com>
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
---
 tools/testing/selftests/kvm/dirty_log_test.c  | 12 +++--------
 .../testing/selftests/kvm/include/kvm_util.h  |  2 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    | 20 ++++++++++++-------
 3 files changed, 17 insertions(+), 17 deletions(-)

```
#### [kvm-unit-tests PATCH] s390x: Diag288 test
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11116255
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F96914D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 07:46:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1D94920828
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 07:46:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728632AbfH0Hqt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 03:46:49 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:52422 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726333AbfH0Hqt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 27 Aug 2019 03:46:49 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7R7hJ67089983
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 03:46:48 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2umxkvuedx-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 03:46:48 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 27 Aug 2019 08:46:46 +0100
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 27 Aug 2019 08:46:43 +0100
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7R7kgIP35258782
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 27 Aug 2019 07:46:42 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4505EA404D;
        Tue, 27 Aug 2019 07:46:42 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 80101A4053;
        Tue, 27 Aug 2019 07:46:41 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 27 Aug 2019 07:46:41 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH] s390x: Diag288 test
Date: Tue, 27 Aug 2019 09:46:31 +0200
X-Mailer: git-send-email 2.17.0
In-Reply-To: <4855e0bd-2808-ff44-482e-ecc96c7e69ed@redhat.com>
References: <4855e0bd-2808-ff44-482e-ecc96c7e69ed@redhat.com>
X-TM-AS-GCONF: 00
x-cbid: 19082707-4275-0000-0000-0000035DCF26
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082707-4276-0000-0000-0000386FFEA0
Message-Id: <20190827074631.7184-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-26_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908270086
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A small test for the watchdog via diag288.

Minimum timer value is 15 (seconds) and the only supported action with
QEMU is restart.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
Disclaimer: Written without coffee, but tested
---
 lib/s390x/asm/arch_def.h |   1 +
 s390x/Makefile           |   1 +
 s390x/diag288.c          | 114 +++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg      |   4 ++
 4 files changed, 120 insertions(+)
 create mode 100644 s390x/diag288.c

```
#### [PATCH 1/3] KVM: x86: hyper-v: don't crash on KVM_GET_SUPPORTED_HV_CPUID when kvm_intel.nested is disabled
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11117239
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BE55A1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 16:04:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A67012173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 16:04:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730017AbfH0QEM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 12:04:12 -0400
Received: from mx1.redhat.com ([209.132.183.28]:42056 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729671AbfH0QEL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 12:04:11 -0400
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 888332A09AB
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 16:04:10 +0000 (UTC)
Received: by mail-wm1-f72.google.com with SMTP id u21so1251026wml.4
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 09:04:10 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=VhVONP1yOZ9qqPvIKZXfSIL1EWyqy2BDr9yNoXDMCHw=;
        b=EHmNeSx45OpPCG7zpjVVgC1B2inGdu+3oGC2JPh3hyfJi+L04QQLzM4IBLmOCdVFZe
         SqQ6yEHYtLuBF5BOyBWRH2O0u590Bj9YVwT0t3wlp9+UyhVz3p/xxxKwI4OZt6Lzp8P1
         V4uXa2qcO3lI4HvLs0GebY0QyVzuXmRT0mkxVygjU+NgDWjOZ3sUEvErkBhB7UA89Ykt
         V0oHCenXPWwNa0idH5u5O4hQ9B8IATJrCvF1o7dVQVAzUXuODUGNrpfj/CUas42z7fjh
         ludOikRpR3WuayC7YHVoEYODccqLPrYN+wGix1W+wI44rUhliTaWhu3RKWVgWNfBtxan
         Vduw==
X-Gm-Message-State: APjAAAXTw7ajOFzceHIV7CP51Kub2ROa18T/+SWb0lv/CYCaSbhpeYCE
        O1MjVqYt7dOSJyo4FEpiBDse+d7RcCLvBheCvLg8K9+lHedFHFK1B7rx+ltWyJqIASIRLhWghlp
        oae4MhwjNdtlR
X-Received: by 2002:a1c:f110:: with SMTP id p16mr28612684wmh.59.1566921848499;
        Tue, 27 Aug 2019 09:04:08 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqwQuwukGsraHaatE4hAj0LDnedGOIKHMZOGMIdh4CEFhBseJtI9ADNJhCCUprGZX99+Uaeilg==
X-Received: by 2002:a1c:f110:: with SMTP id p16mr28612666wmh.59.1566921848295;
        Tue, 27 Aug 2019 09:04:08 -0700 (PDT)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 n8sm13461246wro.89.2019.08.27.09.04.07
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 27 Aug 2019 09:04:07 -0700 (PDT)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Joerg Roedel <joro@8bytes.org>, Jim Mattson <jmattson@google.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Roman Kagan <rkagan@virtuozzo.com>
Subject: [PATCH 1/3] KVM: x86: hyper-v: don't crash on
 KVM_GET_SUPPORTED_HV_CPUID when kvm_intel.nested is disabled
Date: Tue, 27 Aug 2019 18:04:02 +0200
Message-Id: <20190827160404.14098-2-vkuznets@redhat.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190827160404.14098-1-vkuznets@redhat.com>
References: <20190827160404.14098-1-vkuznets@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If kvm_intel is loaded with nested=0 parameter an attempt to perform
KVM_GET_SUPPORTED_HV_CPUID results in OOPS as nested_get_evmcs_version hook
in kvm_x86_ops is NULL (we assign it in nested_vmx_hardware_setup() and
this only happens in case nested is enabled).

Check that kvm_x86_ops->nested_get_evmcs_version is not NULL before
calling it. With this, we can remove the stub from svm as it is no
longer needed.

Fixes: e2e871ab2f02 ("x86/kvm/hyper-v: Introduce nested_get_evmcs_version() helper")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/hyperv.c  | 5 ++++-
 arch/x86/kvm/svm.c     | 8 +-------
 arch/x86/kvm/vmx/vmx.c | 1 +
 3 files changed, 6 insertions(+), 8 deletions(-)

```
#### [PATCH v2 01/14] KVM: x86: Relocate MMIO exit stats counting
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11117551
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4A709112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 21:42:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 35005206E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 21:42:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731397AbfH0VmF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 17:42:05 -0400
Received: from mga04.intel.com ([192.55.52.120]:50844 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729626AbfH0Vkr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 17:40:47 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Aug 2019 14:40:46 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,438,1559545200";
   d="scan'208";a="182919739"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by orsmga003.jf.intel.com with ESMTP; 27 Aug 2019 14:40:45 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Liran Alon <liran.alon@oracle.com>
Subject: [PATCH v2 01/14] KVM: x86: Relocate MMIO exit stats counting
Date: Tue, 27 Aug 2019 14:40:27 -0700
Message-Id: <20190827214040.18710-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
In-Reply-To: <20190827214040.18710-1-sean.j.christopherson@intel.com>
References: <20190827214040.18710-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move the stat.mmio_exits update into x86_emulate_instruction().  This is
both a bug fix, e.g. the current update flows will incorrectly increment
mmio_exits on emulation failure, and a preparatory change to set the
stage for eliminating EMULATE_DONE and company.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu.c     | 2 --
 arch/x86/kvm/vmx/vmx.c | 1 -
 arch/x86/kvm/x86.c     | 2 ++
 3 files changed, 2 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH 1/3] s390x: Move pfmf to lib and make address void
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11117033
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 92AB11398
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:49:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 72CD52186A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:49:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730058AbfH0Nt5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 09:49:57 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:4974 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730021AbfH0Nt5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 27 Aug 2019 09:49:57 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7RDm5kn026883
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 09:49:56 -0400
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2un2cj0u8q-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 09:49:56 -0400
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 27 Aug 2019 14:49:52 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 27 Aug 2019 14:49:49 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7RDnQfx13435332
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 27 Aug 2019 13:49:26 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5E48652050;
        Tue, 27 Aug 2019 13:49:48 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 9E78852059;
        Tue, 27 Aug 2019 13:49:47 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH 1/3] s390x: Move pfmf to lib and make address
 void
Date: Tue, 27 Aug 2019 15:49:34 +0200
X-Mailer: git-send-email 2.17.0
In-Reply-To: <20190827134936.1705-1-frankja@linux.ibm.com>
References: <20190827134936.1705-1-frankja@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19082713-0008-0000-0000-0000030DDCE9
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082713-0009-0000-0000-00004A2C1978
Message-Id: <20190827134936.1705-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-27_02:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=889 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908270149
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It's needed by other tests soon.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 lib/s390x/asm/mem.h | 31 ++++++++++++++++++++++
 s390x/pfmf.c        | 63 ++++++++++++++-------------------------------
 2 files changed, 50 insertions(+), 44 deletions(-)

```
#### [PATCH] x86: KVM: svm: Fix a check in nested_svm_vmrun()
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dan Carpenter <dan.carpenter@oracle.com>
X-Patchwork-Id: 11116497
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D9CD71399
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 09:41:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B7E3B2173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 09:41:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="KTtCNst+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729090AbfH0JlD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 05:41:03 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:58852 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726833AbfH0JlD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 05:41:03 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7R9Xg5R004723;
        Tue, 27 Aug 2019 09:39:09 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=date : from : to : cc
 : subject : message-id : mime-version : content-type; s=corp-2019-08-05;
 bh=JPkF6lzK/+T4qsG8ilfaNhkWn7WfY/fvZi21ug4KTpw=;
 b=KTtCNst+5DV96n4tlt6SkpbwYvOOHOzFrOjGjZkL4TajEsTNmPEmJSUKN0VPxayReGzX
 +xuaYnBxNVUsnlExsHP/HfiHVRfM/R2+mfEPEEgisabXo74Y3nZW0OYzd+1rGSqWXvIL
 oCm+DyN2f/IDYU4LEko1uOmhBq5oGxEx9yI+2bTAi3u4Yx9BCWQvPm2OsihifpeYlsr2
 yqEsDoRsYugltFGKaqpbITPEv451r4LsZ/xBORrS3UoT+vW93/nlKWA9qqKcUhPS3wDj
 nSDaY190K3DwWMJOjSl3xcZpcXfnaKoUm3ceb9zNlFbw5dNjwYy4JuCxeMU4PQfy+iER bg==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 2un1sh04jx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 27 Aug 2019 09:39:09 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7R9cFNH089851;
        Tue, 27 Aug 2019 09:39:08 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 2umhu8h6js-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 27 Aug 2019 09:39:08 +0000
Received: from abhmp0004.oracle.com (abhmp0004.oracle.com [141.146.116.10])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id x7R9d1Ed003849;
        Tue, 27 Aug 2019 09:39:01 GMT
Received: from mwanda (/41.57.98.10)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 27 Aug 2019 02:39:01 -0700
Date: Tue, 27 Aug 2019 12:38:52 +0300
From: Dan Carpenter <dan.carpenter@oracle.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Wanpeng Li <wanpengli@tencent.com>, Jim Mattson <jmattson@google.com>,
 Joerg Roedel <joro@8bytes.org>, Thomas Gleixner <tglx@linutronix.de>,
 Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
 "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org, kvm@vger.kernel.org,
 kernel-janitors@vger.kernel.org
Subject: [PATCH] x86: KVM: svm: Fix a check in nested_svm_vmrun()
Message-ID: <20190827093852.GA8443@mwanda>
MIME-Version: 1.0
Content-Type: text/plain; charset=us-ascii
Content-Disposition: inline
X-Mailer: git-send-email haha only kidding
User-Agent: Mutt/1.10.1 (2018-07-13)
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9361
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1908270109
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9361
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1011
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1908270108
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We refactored this code a bit and accidentally deleted the "-" character
from "-EINVAL".  The kvm_vcpu_map() function never returns positive
EINVAL.

Fixes: c8e16b78c614 ("x86: KVM: svm: eliminate hardcoded RIP advancement from vmrun_interception()")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
From static analysis.  I don't really know the impact.


 arch/x86/kvm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
