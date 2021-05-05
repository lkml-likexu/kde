

#### [PATCH v7 0/1] qapi: introduce 'query-cpu-model-cpuid' action
##### From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>

```c
From patchwork Tue May  4 12:26:38 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
X-Patchwork-Id: 12238017
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E62ECC43470
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 12:26:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B8146613CA
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 12:26:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230333AbhEDM1u (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 08:27:50 -0400
Received: from mail-eopbgr80103.outbound.protection.outlook.com
 ([40.107.8.103]:31395
        "EHLO EUR04-VI1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S230293AbhEDM1t (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 May 2021 08:27:49 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=lwHVfn45COyOzQGJp//XwvhnL7eQ0uUjqJi9HSHhYUin2inu5uwlla7MRzYJlkMNF1P3VhB3xrQ4aWhcsB2O/ib6oDKoZCo3FbTsmTq2/KSJkCwctlp9UcJIqjOf0OEZXE8QeeKQU7VI7F48H48iWoFIFCudiupA6GTNkcHzM76ZgXB86/a6cUraFPxy58fFjMcw4XRbiQU1GfkwsEZV5WhxRI/29z31lIK7soP0UiUklu9WqRnaZVtv4FMSgtFQVt7KylS8QOtrPE9uSTC5oktw8JHK/Ac/TOxtH51tE2/l7QwfOujtqSXu/6ML7AGiB8mKU2LZCXbMbbXKmmDHoQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=dy9TocU303aflyHSa+2gYdVGUNgQTkBiJtVrqZ8jY+w=;
 b=dyLxc0LW9JYQ4+cBiP6ml5wn2RFKfJmEvWO50qSaDdnZoh/Mmwc5B15w12RX+pu1TZGKdfgaSgvEATu4GxRXtupFt7bs3SGgkl75FeoNADCjYgY1AcnNQdO6WhiWOv8vhDkfZJCjGmB55bdIT00crIV5nAdkOvavmfoG9XFCNtBtHlW/a1l/xzplG8J47p8GsL39rL0m14caYFY4HzmUJurnHMDzQC0bY+TTaBY9uVKEDJ4v6K195VTwWHCYQBC60/RUiLlPkLFdwqTjVqGAJVz9vImUmfJj97KCdQlgipmWQlPpF62AQ/HCb+UjDZcVPWCVEeqIwliTd14fEqM4og==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=virtuozzo.com; dmarc=pass action=none
 header.from=virtuozzo.com; dkim=pass header.d=virtuozzo.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=virtuozzo.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=dy9TocU303aflyHSa+2gYdVGUNgQTkBiJtVrqZ8jY+w=;
 b=ppPiAAOoqN6xDwX2Et2oUDFGXhhEK1dhRqknCKV/mbFF74r9mNRw9Lh8BQn4lUgHH/T3rXZTgA3u0euaCOGfswIA6pkXJWzx6RRWPpoVQeGdEoPk3WLADYgxS1CCQxASD4jiJ1MDKdXsKxmUmLPxoSp+YJeyhKYP4qZQSvCMnII=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=virtuozzo.com;
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com (2603:10a6:20b:283::19)
 by AM9PR08MB6998.eurprd08.prod.outlook.com (2603:10a6:20b:419::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4087.25; Tue, 4 May
 2021 12:26:52 +0000
Received: from AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f]) by AM9PR08MB5988.eurprd08.prod.outlook.com
 ([fe80::7d3f:e291:9411:c50f%7]) with mapi id 15.20.4087.044; Tue, 4 May 2021
 12:26:52 +0000
From: Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
To: qemu-devel@nongnu.org
Cc: Eduardo Habkost <ehabkost@redhat.com>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Eric Blake <eblake@redhat.com>,
        Markus Armbruster <armbru@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Richard Henderson <richard.henderson@linaro.org>,
        Thomas Huth <thuth@redhat.com>,
        Laurent Vivier <lvivier@redhat.com>, kvm@vger.kernel.org,
        Denis Lunev <den@openvz.org>,
        Vladimir Sementsov-Ogievskiy <vsementsov@virtuozzo.com>,
        Valeriy Vdovin <valeriy.vdovin@virtuozzo.com>
Subject: [PATCH v7 0/1] qapi: introduce 'query-cpu-model-cpuid' action
Date: Tue,  4 May 2021 15:26:38 +0300
Message-Id: <20210504122639.18342-1-valeriy.vdovin@virtuozzo.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [176.106.247.78]
X-ClientProxiedBy: AM0P190CA0027.EURP190.PROD.OUTLOOK.COM
 (2603:10a6:208:190::37) To AM9PR08MB5988.eurprd08.prod.outlook.com
 (2603:10a6:20b:283::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from localhost.localdomain (176.106.247.78) by
 AM0P190CA0027.EURP190.PROD.OUTLOOK.COM (2603:10a6:208:190::37) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4108.24 via Frontend
 Transport; Tue, 4 May 2021 12:26:51 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: c48174f7-1b43-49ca-a5ed-08d90ef7e5de
X-MS-TrafficTypeDiagnostic: AM9PR08MB6998:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <AM9PR08MB6998AA78684651E5DF1F83BA875A9@AM9PR08MB6998.eurprd08.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:5797;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 /+GZ2nIeBmjRfbrDsAQAd8d62Vw9G89XZEeG3iSYTeYBqGORxl8u0/BU/eGx5pLQMHtogb+FAoPDCoZh3MrfsFxFDCIJQqA+WRbVxFRSIY1fF4N2VGeitMQFcZYXiBoAA3zuttfeukDltx+cCNvs3+/V09l3BVixK3PDRRxTisIK3IzuakoHKCBzVaQ2MUk/RyoSQHt2UwQnvaL8V87NF6338k2gZQTunWiNTI5HHCoJ/Q56Q2JU99SGn3z6Cb6aMr9Vl0OEd4nETcKCIIZx8jfGVPKeLLkjefpC1N/eKhr5UtVYW+UTtdHdjjhVOZ0F+LJPkYB2iRImNK6+kUvxv8ezHv4dOkLPTGAiW8dTy9rm3V/VG+u+/C5fGuLHMArhTazd5uvYG3rWFG+e3DGOtTEkjEOQfIvTmE2NiD2Isismb8DfiAY3HWqZ4m6wTr1LBPVJF/vW9mmduGHtT21+Zkyji1wmr4fMGZx0w77g1nUZqOEk3WvSzvWP2VkDjQqHw9NxTLgsPUXYsPtvxdv8iNzNzQZIAyHkqpb9qEUTjweBILUTNMoKlfUZI/kDUePykU7kZtRb7HPPO2tdWg+GzN6KP1ye72eGSL4spcEVHHsxqJ+Kl7OLtpMpTefrFS8WY0cWrymBteylgnmo+Qpknr3cEPaXhyoJzxeaun8T7AtMeWc257+UUyQlAK5bDP0WfqFJGkipz9ypgTOL5oNCRPdlnKL7AbBy5Rt5ISrDmbZmUaRMw5NpVI41fTXnqmZpgyjzHUpkaNtWyD9T7XraQA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:AM9PR08MB5988.eurprd08.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(39830400003)(346002)(136003)(366004)(376002)(38350700002)(6666004)(186003)(16526019)(478600001)(44832011)(4326008)(52116002)(66556008)(36756003)(66946007)(38100700002)(66476007)(2616005)(6506007)(107886003)(956004)(83380400001)(54906003)(966005)(6512007)(6486002)(2906002)(26005)(8936002)(7416002)(316002)(5660300002)(8676002)(6916009)(86362001)(1076003)(69590400013);DIR:OUT;SFP:1102;
X-MS-Exchange-AntiSpam-MessageData: 
 XQehwhkZCynCF38D7pjBBJdelfzy6TkN+BD+33c89KaTHOI99xx+2UHWaADj1xX+P0af8LGXTYac27WHKZuBvAq54/1dEek48jWpvSArQiBf1b/D1tXpFSDws0Z1On88ghkTE1N+ADjQQes51tnM8fLzECmID9DXhM565FD0Brz2M4eResDVB25sUt8x92tl0LU3rHqn5GmPoFg1pCbAaJrwWBm5xNtZbP/Ynn2FP2YjFBwYO2Y8Cetvhewqge84MCkRopefGtAVtJzCHaMlNFzHKTdZCJmwgIWV2rvRw5HuHRACVnhN0aqLDTr6L3lbByTkJj1Ha7l28FS/59Oc8Z+PV62pppj8We60ffRQhOUWiG2Nh01DSbJaeXs9NSZ+FemKeraB0SRbCnuNhmu3xntyR6O2vUC8jCARTNJRvWonOJPLr5D53iaTMxZWdQk4kzDun+Pb1E/5AapXt42oXV4aqdowdVF3U+KqzY+1cAwjaIwjR2Wzn/GihFe20mHw/R1/EUTtfMQDY+FKs7qziEIUOSHoflbNTZHaUtEdXehwd4gV7RZzz2xtsEXU0c1DGwyPtwc9/7dYfBGBX24FqmXS92fARxXWnhpT67w4aVWuebMYRADjaG3IVorTMU/5zUh4+4nU5t65yF01HtgWDl5DW5rntFR7dgfIoAodik59VcyfNiM6nz+JErQryhsj6xsW1IJMMiEyyO2yA6PgVDjojH+uIxy+HuENK1G3aBV4EoTTZRtoF6W9QdVbby7/ZR0IAqkNTW1VXscLhD5gQqjXknMpZ0DH1JJ6pgL7vTNn1/fxgBdJAatuELC7u1e0xeu0TrmcIlbTKzJxw4JpdHgWFkmV618+JR2iO3DxyzR/bscDxz7d4/oYEn9fsFnh2ln+4Ub9hLMNfZRnUfE1Yt/ZSaBl0TdO4SqOEq4GlcZJnU92LhrfdbhkSwhOfAynnpZlqYz9yWjnLV4evIWQO2eXSBIqJm7a+aDSHd0qzzaLtH2Kz6ue8fu2ybmauWv3gT0PjvlT4gePm5pwg46VnCOk+Kbjjf+qAZ2Bkw5mGpbQoHSA5vyMPCsXATfs1Uy9sLQRufYcOb5dr7Fp/eCyvZsN7e7lDa2E3Y5gLKARcpcDUzUfofVhBaO5Rmj8vTfDn9fJ7Almxw6bwh1P+q/RH40GeAIdD2AavqQrnVXXGmG2SexHv1jL6JNxd01o8aB+/h6v3NiGB3CgFdVRSpzZiq8Nn2vAWiAs5ZNYze5CU62SJe7mzRcmPeMMP573PNQF4mKoFCMS/JOWLUnacCuC8zF2vMxYLj1c9Jc4FIIWaxxFYSIm/0mqPe1mXIuBmFGA
X-OriginatorOrg: virtuozzo.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c48174f7-1b43-49ca-a5ed-08d90ef7e5de
X-MS-Exchange-CrossTenant-AuthSource: AM9PR08MB5988.eurprd08.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 04 May 2021 12:26:52.7852
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 0bc7f26d-0264-416e-a6fc-8352af79c58f
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 6eBF+jfc3JjXpEUOpY8ctCsS2J40Jlu3fY5UeA7MIqYXl516yirg2chv0H9LD5T9XLLJi4ngnikU+922unV7jV/BX30priCf/gV4n0ipmUI=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: AM9PR08MB6998
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In version 7 of the subject patch, I wanted to try to implement this qmp
method with the help of existing kvm ioctl KVM_GET_CPUID2. The reasoning
behind my decision is the fact that QEMU uses KVM_SET_CPUID2 to set full
cpuid response table to the virtual cpu, and KVM_GET_CPUID2 is a convenient
and complementary method for extracting the same cpuid entry table back
from the kernel.

So I've pushed a patch into Linux KVM subtree to fine tune ioctl
KVM_GET_CPUID2 for this type of application. This has triggered a small
discussion.
One of the responses here https://lkml.org/lkml/2021/5/4/109 is from
Paolo Bonzini. There he suggests to cache the the whole cpuid entries
table that we pass to the kernel via KVM_SET_CPUID2 and later just output
this cached data instead of calling the same table via KVM_GET_CPUID2.
Current patch is the reflection of that idea.

Valeriy Vdovin (1):
  qapi: introduce 'query-cpu-model-cpuid' action

 qapi/machine-target.json   | 51 ++++++++++++++++++++++++++++++++++++++
 target/i386/kvm/kvm.c      | 45 ++++++++++++++++++++++++++++++---
 tests/qtest/qmp-cmd-test.c |  1 +
 3 files changed, 93 insertions(+), 4 deletions(-)
```
#### [PATCH v2 0/2] KVM: nSVM: few fixes for the nested migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Tue May  4 14:39:34 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12238161
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BFA4AC433ED
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 14:40:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 90F39613B3
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 14:40:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231410AbhEDOlW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 10:41:22 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:55973 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231336AbhEDOlW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 4 May 2021 10:41:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620139227;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=kY1X0Ob5QnrkMKpSaPxZa/1lEOOAKUMTFQRU2EjHhsk=;
        b=G2a6YiYRdlKOwmDSQwYRg+MZwA64X8T8XotTQ3Mfkm4LQ77pJ3cytWNMD/cteH0LCX4xZt
        myDTAOz851x1UaTU4TdVqS1pw1bycS/UYXb/Lm8lEy0GnKFYQ/Lc4bolrPqydZC/mc1D4k
        tpJFW2jhTZVzNtePkqSpPYlzidGhxPs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-319-89l2iu_RNkaN05qwuDjWFg-1; Tue, 04 May 2021 10:40:25 -0400
X-MC-Unique: 89l2iu_RNkaN05qwuDjWFg-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4D9F6824FAE;
        Tue,  4 May 2021 14:40:23 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.40.193.27])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8141F5D9DE;
        Tue,  4 May 2021 14:39:38 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        linux-kernel@vger.kernel.org, Cathy Avery <cavery@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 0/2] KVM: nSVM: few fixes for the nested migration
Date: Tue,  4 May 2021 17:39:34 +0300
Message-Id: <20210504143936.1644378-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Those are few fixes for issues I uncovered by doing variants of a
synthetic migration test I just created:

I modified the qemu, such that on each vm pause/resume cycle,
just prior to resuming a vCPU, qemu reads its KVM state,
then (optionaly) resets this state by uploading a
dummy reset state to KVM, and then it uploads back to KVM,
the state that this vCPU had before.

V2: those are only last 2 patches from V1,
updated with review feedback from Paolo (Thanks!).

Best regards,
	Maxim Levitsky

Maxim Levitsky (2):
  KVM: nSVM: always restore the L1's GIF on migration
  KVM: nSVM: remove a warning about vmcb01 VM exit reason

 arch/x86/kvm/svm/nested.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)
```
#### [PATCH 00/15] KVM: x86: RDPID/RDTSCP fixes and uret MSR cleanups
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Tue May  4 17:17:19 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12238339
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4D3D1C433B4
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 17:17:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 21524613B4
	for <kvm@archiver.kernel.org>; Tue,  4 May 2021 17:17:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232035AbhEDRSi (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 4 May 2021 13:18:38 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39536 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231704AbhEDRSi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 4 May 2021 13:18:38 -0400
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 7A427C06174A
        for <kvm@vger.kernel.org>; Tue,  4 May 2021 10:17:43 -0700 (PDT)
Received: by mail-qt1-x849.google.com with SMTP id
 t14-20020ac8588e0000b02901bc2b5853b1so4020621qta.16
        for <kvm@vger.kernel.org>; Tue, 04 May 2021 10:17:43 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=2xWZdvogf0ze6g50j9Z7ywuPrceLwwW3g11yg2g3TOs=;
        b=SmbCPjuSQLSJNYSCAdiifnXtT/H2AqQdTpZINcEF/GfIcUtCzvYZjSYKvxQr4162hD
         kj9ZAGJTnxgB3dSb0COCqb10XIlyOqpmfOj5LZcjJB8vHUp+siIFwCfaViiQ5IV3++xp
         xrVcVf8esLJnkhfNGkLSdivxNqkxVFWaXP5fbP63rQ+8AW3I0lNo2g/f5ypcM/ij+pYI
         5Z/iIv0+hgMICMEkPSt1Pkrk62Ji5SooQ33z8NC9lcbU8EiW7tRJ8M6BFvJXEpvdifJT
         RKhi+zeuiI2+Wj1RfEzML/Eolp6rKf+/Sg+yu5osyK9toW9SL4x055MzPOj0z2sr19uc
         6lqg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=2xWZdvogf0ze6g50j9Z7ywuPrceLwwW3g11yg2g3TOs=;
        b=Z1ZMT4Vkgy2mq4zvZMXZvF8VAiSuDaYCQ/Jx1GO6093ywuGZ21iCwSEWOjS2MUYK8r
         ESa5xl9qOyyGMpVonXzV7F+6c2ZG/xItE//Edru7IZSpXCdLgIFBYWn2S8wgPuTpMdPL
         KmQNU0EIWXwnNffQDKvjvuRlf7MA9XjKZgzgcjfmetzRAbBEZxrRMeYr4IwI5reLhhsi
         927SlkiV94lUU40D34rHOMoZ0VJleTDrEjJGPNBFrJwIyGYd/RMLyqUfZjejTX/FL9YV
         qHj4/GI4NRNdPCNB+JrIWEaA/18hqwSAtNrd4OXW0xiKkyj6+sx77huLE6GO9qpP5NkC
         iEWw==
X-Gm-Message-State: AOAM533O/8i6te8qaKoBSh/xAMNgaCPuugzoep10+GR1oxdAehn0iSSt
        0dkuWnIofnjvWFt4CkJVDSdpf2U6rS0=
X-Google-Smtp-Source: 
 ABdhPJwt+/Q+KjHniWgBRhccJXjTUe7IsrkwWMn8aXCHIW6G12CoJJY+nIbZ5i4yEccmX/qSaYnPw8KZxKU=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:df57:48cb:ea33:a156])
 (user=seanjc job=sendgmr) by 2002:a0c:c488:: with SMTP id
 u8mr26264785qvi.47.1620148662633;
 Tue, 04 May 2021 10:17:42 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  4 May 2021 10:17:19 -0700
Message-Id: <20210504171734.1434054-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.527.g47e6f16901-goog
Subject: [PATCH 00/15] KVM: x86: RDPID/RDTSCP fixes and uret MSR cleanups
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>,
        Reiji Watanabe <reijiw@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a continuation of a less ambitious effort to unify MSR_TSC_AUX
handling across SVM and VMX.  Reiji pointed out that MSR_TSC_AUX exists if
RDTSCP *or* RDPID is supported, and things went downhill from there. 

The first half of this series fixes a variety of RDTSCP and RDPID related
bugs.

The second half of the series cleans up VMX's user return MSR framework
and consolidates more of the uret logic into common x86.

The last two patches leverage the uret MSR cleanups to move MSR_TSC_AUX
handling to common x86 and add sanity checks to guard against misreporting
of RDPID and/or RDTSCP support.

This will conflict with my vCPU RESET/INIT cleanup series.  Feel free to
punt the conflicts to me.

Other "fun" things to tackle:

 - The kernel proper also botches RDPID vs. RDTSCP, as MSR_TSC_AUX is
   configured if RDTSCP is supported, but is consumed if RDPID is
   supported.  I'll send this fix separately.

 - Commit 844d69c26d83 ("KVM: SVM: Delay restoration of host MSR_TSC_AUX
   until return to userspace") unwittingly fixed a bug where KVM would
   write MSR_TSC_AUX with the guest's value when svm->guest_state_loaded
   is false, which could lead to running the host with the guest's value.
   The bug only exists in 5.12 (maybe 5.11 too?), so crafting a fix for
   stable won't be too awful.

Sean Christopherson (15):
  KVM: VMX: Do not adverise RDPID if ENABLE_RDTSCP control is
    unsupported
  KVM: x86: Emulate RDPID only if RDTSCP is supported
  KVM: SVM: Inject #UD on RDTSCP when it should be disabled in the guest
  KVM: x86: Move RDPID emulation intercept to its own enum
  KVM: VMX: Disable preemption when probing user return MSRs
  KVM: SVM: Probe and load MSR_TSC_AUX regardless of RDTSCP support in
    host
  KVM: x86: Add support for RDPID without RDTSCP
  KVM: VMX: Configure list of user return MSRs at module init
  KVM: VMX: Use flag to indicate "active" uret MSRs instead of sorting
    list
  KVM: VMX: Use common x86's uret MSR list as the one true list
  KVM: VMX: Disable loading of TSX_CTRL MSR the more conventional way
  KVM: x86: Export the number of uret MSRs to vendor modules
  KVM: x86: Move uret MSR slot management to common x86
  KVM: x86: Tie Intel and AMD behavior for MSR_TSC_AUX to guest CPU
    model
  KVM: x86: Hide RDTSCP and RDPID if MSR_TSC_AUX probing failed

 arch/x86/include/asm/kvm_host.h |   9 +-
 arch/x86/kvm/cpuid.c            |  18 ++-
 arch/x86/kvm/emulate.c          |   2 +-
 arch/x86/kvm/kvm_emulate.h      |   1 +
 arch/x86/kvm/svm/svm.c          |  50 +++-----
 arch/x86/kvm/vmx/vmx.c          | 217 ++++++++++++++++----------------
 arch/x86/kvm/vmx/vmx.h          |  12 +-
 arch/x86/kvm/x86.c              | 101 ++++++++++++---
 8 files changed, 245 insertions(+), 165 deletions(-)
```
