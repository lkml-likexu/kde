

#### [PATCH 0/3] fix emulation error on Windows bootup
##### From: Jan Dakinevich <jan.dakinevich@virtuozzo.com>

```c
From patchwork Tue Aug 27 13:07:00 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jan Dakinevich <jan.dakinevich@virtuozzo.com>
X-Patchwork-Id: 11116895
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4B3114F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:07:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B188A2186A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:07:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=virtuozzo.com header.i=@virtuozzo.com
 header.b="BCFXjOq9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728312AbfH0NHF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 09:07:05 -0400
Received: from mail-eopbgr30119.outbound.protection.outlook.com
 ([40.107.3.119]:35904
        "EHLO EUR03-AM5-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726054AbfH0NHF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 09:07:05 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jaxrAeu/92hH+I9ljpJBFUrFshz4LtBLqPwbWU2I4FuZ590iX+lkyWRSvYm3bC/EKAXpohjOj9YRCpR/BVYouMWbkP5LMRyHxRKrY3VF+2p9m6W0F2nYkqhgJQNjZ4y8PMjov6ECnhl2lfy3Kx2/odBko7Pagye1b/X4ocWvHLevsvdYjhdocbOOGZg47hg9+0q+wH2v5Vqtu8nMzMbkRQuVkfQ77nO0S0HtgG5s+EVXePEMOYgueBxEZzc4BD1OzbFuhNZqCNgnhwSvNwMa6JXhuof0v8dfEQl/2OuC/cnrRmdlzjgoapZPWXN42PIUqA+1cXzkHRiI1h9EWE51Ew==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=pzUMO09cKYplP4IdSQB+IMq/dBJWErbTK/AcBdGhAbk=;
 b=bO8hhM5MFhRLDW/Tjfx16UgI1ajckICMfTKv2ZiDISrMQA5TLUt2fZmzLeLnAp0NoaopNHqMHCa53aSNElZr0x0avfp454v4RBy95nXtChW0q2VH+q9KtwQkrb3QkS7mpVtJbgnq5Gt7hD1uVHjx+FVY8g2tqwMa4nDcKPlKGrRNw760u2H9n/klCoqnCAvRoF+PKwQxUgUIpuxg1dO2R6CaQy6Cwmbhmg/cQKY8ieZ7C4v4bXaetq8xh8vXr1lwWyikeL63yvAYV278UHEaV+TZSYTqjq8tWccFmbtMfzia1p9Flr06NjNVayLrJOsroGiS0Yt2+QR9R+CvXsdlcQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=pzUMO09cKYplP4IdSQB+IMq/dBJWErbTK/AcBdGhAbk=;
 b=BCFXjOq9axO7P/mR1P7gHjwrf7lptRLsu3cnvF5sJsO93M5tKgwpPqCLNYv5MqqV3Icyh7jcO/AX/H8YC87VKogRL6e7XKSTJylfvEXfcOnTGjfIvFS6MLhHltqybI6V5htrM0wvPdtgndCqNxcQloZ9AdyURWiVaSQSP9q+xSM=
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com (10.170.236.143) by
 VI1PR08MB3471.eurprd08.prod.outlook.com (20.177.59.25) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2199.21; Tue, 27 Aug 2019 13:07:01 +0000
Received: from VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a]) by VI1PR08MB2782.eurprd08.prod.outlook.com
 ([fe80::2969:e370:fb70:71a%3]) with mapi id 15.20.2178.023; Tue, 27 Aug 2019
 13:07:01 +0000
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
Subject: [PATCH 0/3] fix emulation error on Windows bootup
Thread-Topic: [PATCH 0/3] fix emulation error on Windows bootup
Thread-Index: AQHVXNhQlPTN3PT6WEuOH2XmT3iwQg==
Date: Tue, 27 Aug 2019 13:07:00 +0000
Message-ID: <1566911210-30059-1-git-send-email-jan.dakinevich@virtuozzo.com>
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
x-ms-office365-filtering-correlation-id: 04175519-7c1e-494f-f058-08d72aef72d2
x-microsoft-antispam: 
 BCL:0;PCL:0;RULEID:(2390118)(7020095)(4652040)(8989299)(4534185)(4627221)(201703031133081)(201702281549075)(8990200)(5600166)(711020)(4605104)(1401327)(2017052603328)(7193020);SRVR:VI1PR08MB3471;
x-ms-traffictypediagnostic: VI1PR08MB3471:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <VI1PR08MB34717DE33508136B250D9F2C8AA00@VI1PR08MB3471.eurprd08.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:9508;
x-forefront-prvs: 0142F22657
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(39840400004)(396003)(376002)(366004)(346002)(136003)(199004)(189003)(25786009)(54906003)(6436002)(6512007)(5660300002)(64756008)(7736002)(26005)(4744005)(66946007)(36756003)(66446008)(186003)(66556008)(102836004)(7416002)(305945005)(50226002)(2906002)(52116002)(486006)(476003)(2616005)(6506007)(386003)(44832011)(256004)(66066001)(99286004)(316002)(66476007)(53936002)(14454004)(5640700003)(2501003)(81156014)(6116002)(6486002)(71200400001)(2351001)(81166006)(6916009)(4326008)(86362001)(3846002)(8676002)(71190400001)(478600001)(8936002);DIR:OUT;SFP:1102;SCL:1;SRVR:VI1PR08MB3471;H:VI1PR08MB2782.eurprd08.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: virtuozzo.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam-message-info: 
 /qrFORhe4WnyjEpah2+wjJshltj9p7PEf6pqDU38YXXyZoIzyx1eKU38HAv2he9b+0qrsU7HbgRKzNpiVv6g4zKse+nR01oSxcZyjH322nVRsqj85vIBN1U/J3BCTmyFGk1F84l+bTYd4DPTFPySAckBMUmaLvxutENWZ7oXHBPOmEt4xdbTwps7slz5aDlXqP7zzvSgR4uPrXG9PFk6rhKNozz+hyuEVgnBvNsJVXpFCaPH4f5+sZ81H4vFrNvzPJK0vsvg7hcSk8/AonA281j1fNNE3JnHe6e5G3vjEgL9jlLZMzJLm5KTz76ityNBUoOjszhwkzfToq6E6wRpLX8Ep+CNVm+sDjkmxhwDAAOOASPnq+IZPWqR+KshiYZ/XsWRf5RXMpZKadHB7NufV9VVqbJ6keLLzaV4khZ/qq0=
Content-Type: text/plain; charset="iso-8859-2"
MIME-Version: 1.0
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 04175519-7c1e-494f-f058-08d72aef72d2
X-MS-Exchange-CrossTenant-originalarrivaltime: 27 Aug 2019 13:07:01.0870
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 LWC8ng8kkDo/0oYWTtxBfjVtTxanGEaQUSXPZm/JI5PAdpvCrGEJrZmLpgPDFAPM15ifux2jQwyqkE3tbEyhBS4tDHzE5cv7VReX354H6Wg=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: VI1PR08MB3471
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series intended to fix (again) a bug that was a subject of the 
following change:

  6ea6e84 ("KVM: x86: inject exceptions produced by x86_decode_insn")

Suddenly, that fix had a couple mistakes. First, ctxt->have_exception was 
not set if fault happened during instruction decoding. Second, returning 
value of inject_emulated_instruction was used to make the decision to 
reenter guest, but this could happen iff on nested page fault, that is not 
the scope where this bug could occur.

However, I have still deep doubts about 3rd commit in the series. Could
you please, make me an advise if it is the correct handling of guest page 
fault?

Jan Dakinevich (3):
  KVM: x86: fix wrong return code
  KVM: x86: set ctxt->have_exception in x86_decode_insn()
  KVM: x86: always stop emulation on page fault

 arch/x86/kvm/emulate.c | 4 +++-
 arch/x86/kvm/x86.c     | 4 +++-
 2 files changed, 6 insertions(+), 2 deletions(-)
```
#### [PATCH 0/4] KVM: selftests: Introduce VM_MODE_PXXV48_4K
##### From: Peter Xu <peterx@redhat.com>

```c
From patchwork Tue Aug 27 13:10:11 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11116903
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4975614F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:10:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2F57F2077B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:10:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729377AbfH0NKa (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 09:10:30 -0400
Received: from mx1.redhat.com ([209.132.183.28]:48020 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728030AbfH0NK3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 09:10:29 -0400
Received: from mail-pg1-f200.google.com (mail-pg1-f200.google.com
 [209.85.215.200])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 2D5557DD11
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 13:10:29 +0000 (UTC)
Received: by mail-pg1-f200.google.com with SMTP id h5so11764947pgq.23
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 06:10:29 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=WB5qdqTIX9xVQw8FeHTpQkMeJp+LDnsJufUnItqkzHg=;
        b=h8QL6TcoznsTCIjtF59i+P1hiJQxdWy1RQAFjERX8YSN0LRTl0+3i27ccUZzTtz4Z9
         foa/Yx03dEl7n5EltoeSkQOESGDEDrpEBWzzPsi2+JtE7dGwDBSz0SHqYHj0j9EiqHgK
         AJZWZ6LfmTCZ34fm+L6kv7pGkq7NOgZ5DD+4efFACrCTb0Ux6orG0Vro69zRdJS9rh9O
         +1AQtOf3SEoTlHKwukqR388dlmBZOTKRxWCzZW3UDRCwJjazgCQrWcElfZKZRfzoESgs
         sY+8KgKNbrReJ+nGQuOw+LPKEkNUsFBXQk7+Nd75Bpmjdvxtlw74RnTY5HnkPebhYKCT
         kJRA==
X-Gm-Message-State: APjAAAU5np2umqapCp13rmtZX73kJLNFXzEYr3jb9/okWZWi1jFIl4Fy
        lZldXG6liguN8WT8vRtcrr34NrPGwnagw8OAhbcEcvduhhKoVfJkwaI2lO4SNoazfcT5zU7tAAt
        rzq5afwZPdnFr
X-Received: by 2002:a62:82cb:: with SMTP id
 w194mr25027630pfd.181.1566911428158;
        Tue, 27 Aug 2019 06:10:28 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqyT2Tx2jarPm3ooBXfwx3j891SdrFGJX1PrAnh/JG2qbesp+yVlka5LV5rjOpYbvkIW1i/ogw==
X-Received: by 2002:a62:82cb:: with SMTP id
 w194mr25027592pfd.181.1566911427881;
        Tue, 27 Aug 2019 06:10:27 -0700 (PDT)
Received: from xz-x1.redhat.com ([209.132.188.80])
        by smtp.gmail.com with ESMTPSA id
 o67sm24393050pfb.39.2019.08.27.06.10.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 27 Aug 2019 06:10:27 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Thomas Huth <thuth@redhat.com>, Andrew Jones <drjones@redhat.com>,
 peterx@redhat.com
Subject: [PATCH 0/4] KVM: selftests: Introduce VM_MODE_PXXV48_4K
Date: Tue, 27 Aug 2019 21:10:11 +0800
Message-Id: <20190827131015.21691-1-peterx@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The work is based on Thomas's s390 port for dirty_log_test.

This series originates from "[PATCH] KVM: selftests: Detect max PA
width from cpuid" [1] and one of Drew's comments - instead of keeping
the hackish line to overwrite guest_pa_bits all the time, this series
introduced the new mode VM_MODE_PXXV48_4K for x86_64 platform.

The major issue is that even all the x86_64 kvm selftests are
currently using the guest mode VM_MODE_P52V48_4K, many x86_64 hosts
are not using 52 bits PA (and in most cases, far less).  If with luck
we could be having 48 bits hosts, but it's more adhoc (I've observed 3
x86_64 systems, they are having different PA width of 36, 39, 48).  I
am not sure whether this is happening to the other archs as well, but
it probably makes sense to bring the x86_64 tests to the real world on
always using the correct PA bits.

A side effect of this series is that it will also fix the crash we've
encountered on Xeon E3-1220 as mentioned [1] due to the
differenciation of PA width.

With [1], we've observed AMD host issues when with NPT=off.  However a
funny fact is that after I reworked into this series, the tests can
instead pass on both NPT=on/off.  It could be that the series changes
vm->pa_bits or other fields so something was affected.  I didn't dig
more on that though, considering we should not lose anything.

Any kind of smoke test would be greatly welcomed (especially on s390
or ARM).  Same to comments.  Thanks,

[1] https://lkml.org/lkml/2019/8/26/141

Peter Xu (4):
  KVM: selftests: Move vm type into _vm_create() internally
  KVM: selftests: Create VM earlier for dirty log test
  KVM: selftests: Introduce VM_MODE_PXXV48_4K
  KVM: selftests: Remove duplicate guest mode handling

 tools/testing/selftests/kvm/dirty_log_test.c  | 78 +++++--------------
 .../testing/selftests/kvm/include/kvm_util.h  | 17 +++-
 .../selftests/kvm/lib/aarch64/processor.c     |  3 +
 tools/testing/selftests/kvm/lib/kvm_util.c    | 77 ++++++++++++++----
 .../selftests/kvm/lib/x86_64/processor.c      |  8 +-
 5 files changed, 107 insertions(+), 76 deletions(-)
```
#### [kvm-unit-tests PATCH 0/3] s390x: Add skey removal facility test
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Tue Aug 27 13:49:33 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11117031
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 666D116B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:49:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4E3D72186A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 13:49:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729999AbfH0Nty (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 09:49:54 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:22712 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729873AbfH0Nty (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 27 Aug 2019 09:49:54 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x7RDm1vj016534
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 09:49:53 -0400
Received: from e06smtp03.uk.ibm.com (e06smtp03.uk.ibm.com [195.75.94.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2un4fu49f3-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 09:49:52 -0400
Received: from localhost
        by e06smtp03.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 27 Aug 2019 14:49:50 +0100
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp03.uk.ibm.com (192.168.101.133) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 27 Aug 2019 14:49:48 +0100
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x7RDnlDi26280232
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 27 Aug 2019 13:49:47 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6F62A52052;
        Tue, 27 Aug 2019 13:49:47 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id AF94652057;
        Tue, 27 Aug 2019 13:49:46 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH 0/3] s390x: Add skey removal facility test
Date: Tue, 27 Aug 2019 15:49:33 +0200
X-Mailer: git-send-email 2.17.0
X-TM-AS-GCONF: 00
x-cbid: 19082713-0012-0000-0000-000003437E2D
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19082713-0013-0000-0000-0000217DB71E
Message-Id: <20190827134936.1705-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-08-27_02:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=993 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1908270149
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The storage key removal facility (skrf) is an anti-facility, which
makes skey related instructions result in a special operation
exception when they handle storage keys. E.g. pfmf in clearing mode
does not result in an exception, but pfmf key setting does.

The skrf is always active in protected virtualization guests and can
be emulated by KVM (expected to be upstreamed with the remaining hpage
patches).

Janosch Frank (3):
  s390x: Move pfmf to lib and make address void
  s390x: Storage key library functions now take void ptr addresses
  s390x: Add storage key removal facility

 lib/s390x/asm/mem.h |  40 ++++++++++++--
 s390x/Makefile      |   1 +
 s390x/pfmf.c        |  77 +++++++++++---------------
 s390x/skey.c        |  29 +++++-----
 s390x/skrf.c        | 130 ++++++++++++++++++++++++++++++++++++++++++++
 5 files changed, 212 insertions(+), 65 deletions(-)
 create mode 100644 s390x/skrf.c
```
#### [PATCH 0/3] KVM: x86: fix a couple of issues with Enlightened VMCS
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue Aug 27 16:04:01 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11117235
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E0AB31395
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 16:04:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C8C1B2189D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 16:04:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729626AbfH0QEJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 12:04:09 -0400
Received: from mx1.redhat.com ([209.132.183.28]:31955 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726735AbfH0QEJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 12:04:09 -0400
Received: from mail-wr1-f69.google.com (mail-wr1-f69.google.com
 [209.85.221.69])
        (using TLSv1.2 with cipher ECDHE-RSA-AES128-GCM-SHA256 (128/128 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id D043012A2
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 16:04:08 +0000 (UTC)
Received: by mail-wr1-f69.google.com with SMTP id t9so11678550wrx.9
        for <kvm@vger.kernel.org>; Tue, 27 Aug 2019 09:04:08 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=wTmTh7xa6ZjBJ+aMQDQrAGuc/LFXChDSJhLsWUK+WTw=;
        b=n41V3yLiYJRY3/KFMIQXU/2F3O7ZGA4zWi3pA7g1se+L6w1Ev3/41462yN503+BLe6
         vIiE8yi+bTCl0Q2QlFquOS8dPMoNgZ4YcBC1zr9SXaGnEUvDu1c7LRC2MTdLQSEVxgjI
         GidWgw0Ij/cl0OZ/AhMphlaYNgI1UpptodMTTTa3zXWQsVAD/P50YU6TncAD89h/1D1y
         wFrwzsi+vzfVtsmoJs4BFXPFfItpt1TGRmfO2wdYwAR2IDjQ6ZMrDw6G2cySebDGR8XT
         0YD4aGZEVf72Ln58IgfLDaHADo/9L9yq2f4NNDuLnkGbv0I5JpB+Mvj6WUGoZ8236mqX
         y2SA==
X-Gm-Message-State: APjAAAVXRTmkaS9fbpNXqeW860na6q1iU2hprCDEllzvDJkubrq0uVUJ
        kWVenuRYEOT+IN3sNp2JU1MFzJAP9gnecODN7dkmie4s/NT6wuhnCLWc7CcA9SQjFTxscarDsxT
        w77Rhxf+SkzzS
X-Received: by 2002:a1c:c5c4:: with SMTP id
 v187mr29313150wmf.30.1566921847299;
        Tue, 27 Aug 2019 09:04:07 -0700 (PDT)
X-Google-Smtp-Source: 
 APXvYqzJHNnJawjO+y0F2tak8NF6NDyr9x8KCsDnGG8but4Gv7XNoZibGMzwkLEL53g+R/qOWuQihw==
X-Received: by 2002:a1c:c5c4:: with SMTP id
 v187mr29313126wmf.30.1566921847093;
        Tue, 27 Aug 2019 09:04:07 -0700 (PDT)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 n8sm13461246wro.89.2019.08.27.09.04.06
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 27 Aug 2019 09:04:06 -0700 (PDT)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Joerg Roedel <joro@8bytes.org>, Jim Mattson <jmattson@google.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Roman Kagan <rkagan@virtuozzo.com>
Subject: [PATCH 0/3] KVM: x86: fix a couple of issues with Enlightened VMCS
 enablement
Date: Tue, 27 Aug 2019 18:04:01 +0200
Message-Id: <20190827160404.14098-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It was discovered that:
- hyperv_cpuid test fails on AMD
- hyperv_cpuid test crashes kernel on Intel when nested=0
The test itself is good, we need to fix the issues.

Vitaly Kuznetsov (3):
  KVM: x86: hyper-v: don't crash on KVM_GET_SUPPORTED_HV_CPUID when
    kvm_intel.nested is disabled
  KVM: x86: svm: remove unneeded nested_enable_evmcs() hook
  KVM: x86: announce KVM_CAP_HYPERV_ENLIGHTENED_VMCS support only when
    it is available

 arch/x86/kvm/hyperv.c  |  5 ++++-
 arch/x86/kvm/svm.c     | 17 ++---------------
 arch/x86/kvm/vmx/vmx.c |  1 +
 arch/x86/kvm/x86.c     |  3 ++-
 4 files changed, 9 insertions(+), 17 deletions(-)
```
#### [PATCH v1 0/5] Introduce variable length mdev alias
##### From: Parav Pandit <parav@mellanox.com>

```c
From patchwork Tue Aug 27 19:16:49 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Parav Pandit <parav@mellanox.com>
X-Patchwork-Id: 11117389
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0D5C71800
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 19:17:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E418622CED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 19:17:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730633AbfH0TRD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 15:17:03 -0400
Received: from mail-il-dmz.mellanox.com ([193.47.165.129]:38838 "EHLO
        mellanox.co.il" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728972AbfH0TRC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 15:17:02 -0400
Received: from Internal Mail-Server by MTLPINE1 (envelope-from
 parav@mellanox.com)
        with ESMTPS (AES256-SHA encrypted); 27 Aug 2019 22:16:59 +0300
Received: from sw-mtx-036.mtx.labs.mlnx (sw-mtx-036.mtx.labs.mlnx
 [10.12.150.149])
        by labmailer.mlnx (8.13.8/8.13.8) with ESMTP id x7RJGuGq026842;
        Tue, 27 Aug 2019 22:16:57 +0300
From: Parav Pandit <parav@mellanox.com>
To: alex.williamson@redhat.com, jiri@mellanox.com,
        kwankhede@nvidia.com, cohuck@redhat.com, davem@davemloft.net
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        netdev@vger.kernel.org, Parav Pandit <parav@mellanox.com>
Subject: [PATCH v1 0/5] Introduce variable length mdev alias
Date: Tue, 27 Aug 2019 14:16:49 -0500
Message-Id: <20190827191654.41161-1-parav@mellanox.com>
X-Mailer: git-send-email 2.19.2
In-Reply-To: <20190826204119.54386-1-parav@mellanox.com>
References: <20190826204119.54386-1-parav@mellanox.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To have consistent naming for the netdevice of a mdev and to have
consistent naming of the devlink port [1] of a mdev, which is formed using
phys_port_name of the devlink port, current UUID is not usable because
UUID is too long.

UUID in string format is 36-characters long and in binary 128-bit.
Both formats are not able to fit within 15 characters limit of netdev
name.

It is desired to have mdev device naming consistent using UUID.
So that widely used user space framework such as ovs [2] can make use
of mdev representor in similar way as PCIe SR-IOV VF and PF representors.

Hence,
(a) mdev alias is created which is derived using sha1 from the mdev name.
(b) Vendor driver describes how long an alias should be for the child mdev
created for a given parent.
(c) Mdev aliases are unique at system level.
(d) alias is created optionally whenever parent requested.
This ensures that non networking mdev parents can function without alias
creation overhead.

This design is discussed at [3].

An example systemd/udev extension will have,

1. netdev name created using mdev alias available in sysfs.

mdev UUID=83b8f4f2-509f-382f-3c1e-e6bfe0fa1001
mdev 12 character alias=cd5b146a80a5

netdev name of this mdev = enmcd5b146a80a5
Here en = Ethernet link
m = mediated device

2. devlink port phys_port_name created using mdev alias.
devlink phys_port_name=pcd5b146a80a5

This patchset enables mdev core to maintain unique alias for a mdev.

Patch-1 Introduces mdev alias using sha1.
Patch-2 Ensures that mdev alias is unique in a system.
Patch-3 Exposes mdev alias in a sysfs hirerchy.
Patch-4 Extends mtty driver to optionally provide alias generation.
This also enables to test UUID based sha1 collision and trigger
error handling for duplicate sha1 results.

In future when networking driver wants to use mdev alias, mdev_alias()
API will be added to derive devlink port name.

[1] http://man7.org/linux/man-pages/man8/devlink-port.8.html
[2] https://docs.openstack.org/os-vif/latest/user/plugins/ovs.html
[3] https://patchwork.kernel.org/cover/11084231/
---
Changelog:

v0->v1:
 - Addressed comments from Alex Williamson, Cornelia Hunk and Mark Bloch
 - Moved alias length check outside of the parent lock
 - Moved alias and digest allocation from kvzalloc to kzalloc
 - &alias[0] changed to alias
 - alias_length check is nested under get_alias_length callback check
 - Changed comments to start with an empty line
 - Added comment where alias memory ownership is handed over to mdev device
 - Fixed cleaunup of hash if mdev_bus_register() fails
 - Updated documentation for new sysfs alias file
 - Improved commit logs to make description more clear
 - Fixed inclusiong of alias for NULL check
 - Added ratelimited debug print for sha1 hash collision error

Parav Pandit (5):
  mdev: Introduce sha1 based mdev alias
  mdev: Make mdev alias unique among all mdevs
  mdev: Expose mdev alias in sysfs tree
  mdev: Update sysfs documentation
  mtty: Optionally support mtty alias

 .../driver-api/vfio-mediated-device.rst       |   5 +
 drivers/vfio/mdev/mdev_core.c                 | 117 +++++++++++++++++-
 drivers/vfio/mdev/mdev_private.h              |   5 +-
 drivers/vfio/mdev/mdev_sysfs.c                |  26 +++-
 include/linux/mdev.h                          |   4 +
 samples/vfio-mdev/mtty.c                      |  10 ++
 6 files changed, 157 insertions(+), 10 deletions(-)
```
#### [PATCH v2 00/14] KVM: x86: Remove emulation_result enums
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Aug 27 21:40:26 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11117553
Return-Path: <SRS0=KFyJ=WX=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5EF2C14D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 21:42:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4999F214DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 27 Aug 2019 21:42:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730540AbfH0Vkr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 27 Aug 2019 17:40:47 -0400
Received: from mga04.intel.com ([192.55.52.120]:50844 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726735AbfH0Vkr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 27 Aug 2019 17:40:47 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Aug 2019 14:40:46 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,438,1559545200";
   d="scan'208";a="182919738"
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
Subject: [PATCH v2 00/14] KVM: x86: Remove emulation_result enums
Date: Tue, 27 Aug 2019 14:40:26 -0700
Message-Id: <20190827214040.18710-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Rework the emulator and its users to handle failure scenarios entirely
within the emulator.

{x86,kvm}_emulate_instruction() currently returns a tri-state value to
indicate success/continue, userspace exit needed, and failure.  The
intent of returning EMULATE_FAIL is to let the caller handle failure in
a manner that is appropriate for the current context.  In practice,
the emulator has ended up with a mixture of failure handling, i.e.
whether or not the emulator takes action on failure is dependent on the
specific flavor of emulation.

The mixed handling has proven to be rather fragile, e.g. many flows
incorrectly assume their specific flavor of emulation cannot fail or
that the emulator sets state to report the failure back to userspace.

Move everything inside the emulator, piece by piece, so that the
emulation routines can return '0' for exit to userspace and '1' for
resume the guest, just like every other VM-Exit handler.

Patch 13/14 is a tangentially related bug fix that conflicts heavily with
this series, so I tacked it on here.

Patch 14/14 documents the emulation types.  I added it as a separate
patch at the very end so that the comments could reference the final
state of the code base, e.g. incorporate the rule change for using
EMULTYPE_SKIP that is introduced in patch 13/14.

v1:
  - https://patchwork.kernel.org/cover/11110331/

v2:
  - Collect reviews. [Vitaly and Liran]
  - Squash VMware emultype changes into a single patch. [Liran]
  - Add comments in VMX/SVM for VMware #GP handling. [Vitaly]
  - Tack on the EPT misconfig bug fix.
  - Add a patch to comment/document the emultypes. [Liran]

Sean Christopherson (14):
  KVM: x86: Relocate MMIO exit stats counting
  KVM: x86: Clean up handle_emulation_failure()
  KVM: x86: Refactor kvm_vcpu_do_singlestep() to remove out param
  KVM: x86: Don't attempt VMWare emulation on #GP with non-zero error
    code
  KVM: x86: Move #GP injection for VMware into x86_emulate_instruction()
  KVM: x86: Add explicit flag for forced emulation on #UD
  KVM: x86: Move #UD injection for failed emulation into emulation code
  KVM: x86: Exit to userspace on emulation skip failure
  KVM: x86: Handle emulation failure directly in kvm_task_switch()
  KVM: x86: Move triple fault request into RM int injection
  KVM: VMX: Remove EMULATE_FAIL handling in handle_invalid_guest_state()
  KVM: x86: Remove emulation_result enums, EMULATE_{DONE,FAIL,USER_EXIT}
  KVM: VMX: Handle single-step #DB for EMULTYPE_SKIP on EPT misconfig
  KVM: x86: Add comments to document various emulation types

 arch/x86/include/asm/kvm_host.h |  40 +++++++--
 arch/x86/kvm/mmu.c              |  16 +---
 arch/x86/kvm/svm.c              |  62 ++++++--------
 arch/x86/kvm/vmx/vmx.c          | 147 +++++++++++++-------------------
 arch/x86/kvm/x86.c              | 133 ++++++++++++++++-------------
 arch/x86/kvm/x86.h              |   2 +-
 6 files changed, 195 insertions(+), 205 deletions(-)
```
