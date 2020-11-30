#### [PATCH v2 1/4] KVM: PPC: Allow nested guest creation when L0 hv_guest_state > L1
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 11927941
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E0D83C64E7A
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 11:01:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9072E20782
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 11:01:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="DaiASXbl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732429AbgKXLA7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 24 Nov 2020 06:00:59 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:3188 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1732421AbgKXLA7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 24 Nov 2020 06:00:59 -0500
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AOAVulv162750;
        Tue, 24 Nov 2020 06:00:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=BC5+8LRYhpSa2f8/Hw83GNqklL+HJD3GODekfOgtol4=;
 b=DaiASXblsWr6t3x9qwIxM3xOjWMT+2lhDBbsvjBPOpUlfSzV2pUh+f7BtIhBWyQOCoV6
 aAPpo1LT3lxAr+ONeKP6iw5MKE8qFkwt255wn+6Iy6GJyLu6CjOdxaanwmVkQnly1dRK
 WN7WEg9dVbVcS4qFZ4GYwTHB3QWnY1tSZr6WLkYdIA1Ez2qwyd7pSzx18tZIxhyuzexJ
 SRfUVh5t8LOTazRLYDffGcgm2pa5s7/R/onpuavTK/pqg6qjSTeZ/SqZvFyqKDu7H2i9
 zv/No3U0VzDKcwc8TKvmU5lBZHugwgtaPxIvQJh+In0++yllvGcW5QJO0yqRF2I5VION xQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 350pdq2tae-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 06:00:30 -0500
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AOAWPL7164594;
        Tue, 24 Nov 2020 06:00:22 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 350pdq2t8d-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 06:00:22 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AOAqBYC002556;
        Tue, 24 Nov 2020 11:00:20 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma06ams.nl.ibm.com with ESMTP id 34xt5hbhh7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 11:00:20 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0AOB0HNC37159332
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 24 Nov 2020 11:00:18 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C79944206E;
        Tue, 24 Nov 2020 11:00:14 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 3A78F4203F;
        Tue, 24 Nov 2020 11:00:12 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.32.189])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 24 Nov 2020 11:00:12 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: mpe@ellerman.id.au, paulus@samba.org
Cc: ravi.bangoria@linux.ibm.com, mikey@neuling.org, npiggin@gmail.com,
        leobras.c@gmail.com, pbonzini@redhat.com, christophe.leroy@c-s.fr,
        jniethe5@gmail.com, kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linuxppc-dev@lists.ozlabs.org
Subject: [PATCH v2 1/4] KVM: PPC: Allow nested guest creation when L0
 hv_guest_state > L1
Date: Tue, 24 Nov 2020 16:29:50 +0530
Message-Id: <20201124105953.39325-2-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201124105953.39325-1-ravi.bangoria@linux.ibm.com>
References: <20201124105953.39325-1-ravi.bangoria@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-24_04:2020-11-24,2020-11-23 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 suspectscore=0
 mlxlogscore=999 spamscore=0 priorityscore=1501 mlxscore=0 phishscore=0
 clxscore=1015 impostorscore=0 bulkscore=0 adultscore=0 lowpriorityscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011240061
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On powerpc, L1 hypervisor takes help of L0 using H_ENTER_NESTED
hcall to load L2 guest state in cpu. L1 hypervisor prepares the
L2 state in struct hv_guest_state and passes a pointer to it via
hcall. Using that pointer, L0 reads/writes that state directly
from/to L1 memory. Thus L0 must be aware of hv_guest_state layout
of L1. Currently it uses version field to achieve this. i.e. If
L0 hv_guest_state.version != L1 hv_guest_state.version, L0 won't
allow nested kvm guest.

This restriction can be loosen up a bit. L0 can be taught to
understand older layout of hv_guest_state, if we restrict the
new member to be added only at the end. i.e. we can allow
nested guest even when L0 hv_guest_state.version > L1
hv_guest_state.version. Though, the other way around is not
possible.

Signed-off-by: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
---
 arch/powerpc/include/asm/hvcall.h   | 17 +++++++--
 arch/powerpc/kvm/book3s_hv_nested.c | 53 ++++++++++++++++++++++++-----
 2 files changed, 59 insertions(+), 11 deletions(-)

```
#### [kvm-unit-tests][RFC PATCH] x86: Add a new test case for ret/iret with a nullified segment
##### From: Bin Meng <bmeng.cn@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bin Meng <bmeng.cn@gmail.com>
X-Patchwork-Id: 11927425
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 86EAAC63777
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 08:33:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3368F20782
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 08:33:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="FoUNVPwN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730690AbgKXIdJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 24 Nov 2020 03:33:09 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44042 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730476AbgKXIdJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Nov 2020 03:33:09 -0500
Received: from mail-il1-x143.google.com (mail-il1-x143.google.com
 [IPv6:2607:f8b0:4864:20::143])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 54061C0613CF
        for <kvm@vger.kernel.org>; Tue, 24 Nov 2020 00:33:09 -0800 (PST)
Received: by mail-il1-x143.google.com with SMTP id t13so18501038ilp.2
        for <kvm@vger.kernel.org>; Tue, 24 Nov 2020 00:33:09 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=D+4ljYp5ekAR8JD2FAt/grYOdgFuxJ9VMOxQc5QIChM=;
        b=FoUNVPwNEDJCIPJXL9qPHaOQEvDP44TszPSk3/mH98HJxtrTynFLR0c1yfwBnrcpwY
         xPD2avNVH8qJPyRz01xHBTCv/u/WdsZDT/QSf94eYXcKy6Nz0f77JssgSHeFTrMlQxJr
         yYkvP3dTwGzdbLFFLaUjT7sr9KKUdk4rvTIVsWKmR+3a8MqfoLMP28yB+OQo9Vc1C6Cg
         x0Xa1elVjSM73pGK7L234QTWHrZjm1TCj1zUz0lEjqkn8YnLpgMnw1cKoTeTFye3/JsZ
         2AQ1oSpmzWvU5h5AacTaViBvxnHdYcXS5diNrYLEoTSzrLI6UjyjIsNVcwIfBVfIF6Id
         55rA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=D+4ljYp5ekAR8JD2FAt/grYOdgFuxJ9VMOxQc5QIChM=;
        b=jNz2CcRUNo9ggOzhWxUQeaEAnRWHOUEKWXqa6QkqAfkeb2YpZtnJtgISfyXo313Zn/
         XYGm3ktQvaqGrOCRuhByjVJv4MReTZtNrq06+13PDBeiZ2IvY0HTqMJSGSYzwoApTYW7
         E8luBTNrNyl+UpSsCJ+eqbOMov1K9fnw1ov+GI+WtiqezNcJcgp8MB9UpAS2AZ4IgVKv
         qhEmLbmjgxpdkGj2b0o4WiA3hcsvl3CeFTOAXq9BZCO0FKJfx7iFvzr446hryenoMGng
         7ivHHk2BgtkFTW/oObFC2VyvPf8WXewMqyUcnmE0XJEDlAWXfn1OnSmpRvnfCdDmF655
         zTgQ==
X-Gm-Message-State: AOAM532j1sLvKc1iJYfLzBzvxThzh5cj7tNwE2zCRpbNJt584xmRt/M/
        dgjgZTP/ug6EFbdx+dMiFvqF7iJNLt4=
X-Google-Smtp-Source: 
 ABdhPJw/7A17eNwDMgOxftUlbqx73eCEW6HQFC/qaUwUhiIjZJy6RMkfvQ+H4GszAQeTklFP0x53iQ==
X-Received: by 2002:a92:c50d:: with SMTP id r13mr1630559ilg.160.1606206788800;
        Tue, 24 Nov 2020 00:33:08 -0800 (PST)
Received: from pek-vx-bsp2.wrs.com (unknown-124-94.windriver.com.
 [147.11.124.94])
        by smtp.gmail.com with ESMTPSA id
 f8sm9299753ile.11.2020.11.24.00.33.06
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 24 Nov 2020 00:33:08 -0800 (PST)
From: Bin Meng <bmeng.cn@gmail.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Bin Meng <bin.meng@windriver.com>
Subject: [kvm-unit-tests][RFC PATCH] x86: Add a new test case for ret/iret
 with a nullified segment
Date: Tue, 24 Nov 2020 16:33:00 +0800
Message-Id: <1606206780-80123-1-git-send-email-bmeng.cn@gmail.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bin Meng <bin.meng@windriver.com>

This makes up the test case for the following QEMU patch:
http://patchwork.ozlabs.org/project/qemu-devel/patch/1605261378-77971-1-git-send-email-bmeng.cn@gmail.com/

Note the test case only fails on an unpatched QEMU with "accel=tcg".

Signed-off-by: Bin Meng <bin.meng@windriver.com>
---
Sending this as RFC since I am new to kvm-unit-tests

 x86/emulator.c | 38 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 38 insertions(+)

```
#### [RFC v2 1/1] vfio/platform: add support for msi
##### From: Vikas Gupta <vikas.gupta@broadcom.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vikas Gupta <vikas.gupta@broadcom.com>
X-Patchwork-Id: 11929339
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,MIME_HEADER_CTYPE_ONLY,
	SPF_HELO_NONE,SPF_PASS,T_TVD_MIME_NO_HEADERS,UNWANTED_LANGUAGE_BODY,
	URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 09FA7C63777
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 16:18:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7696D20715
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 16:17:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=broadcom.com header.i=@broadcom.com
 header.b="XIU4EjXo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390317AbgKXQRj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 24 Nov 2020 11:17:39 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60040 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390310AbgKXQRj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 24 Nov 2020 11:17:39 -0500
Received: from mail-pg1-x532.google.com (mail-pg1-x532.google.com
 [IPv6:2607:f8b0:4864:20::532])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1D5A4C0613D6
        for <kvm@vger.kernel.org>; Tue, 24 Nov 2020 08:17:39 -0800 (PST)
Received: by mail-pg1-x532.google.com with SMTP id t37so17813407pga.7
        for <kvm@vger.kernel.org>; Tue, 24 Nov 2020 08:17:39 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=broadcom.com; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=EUaEAh5RbswSMLVe0Ayi7F9d7go/9s1hSln3XKNdXZ0=;
        b=XIU4EjXoCIVfr4aiXXZgNqSVg4LUaLZDwT/+4gVEck4w0AiWq+bc9rrbWQzLyDxi7Q
         BZf62995MWaJqvkdM5KjkknySVnqyZfzWz7w+vkG+eTcC7gWI3aBX5dQCtFr4utsHP8v
         jFdj+OFHdAG5VOZ1W3Vbejcno0dZi9dmeoJ3I=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references;
        bh=EUaEAh5RbswSMLVe0Ayi7F9d7go/9s1hSln3XKNdXZ0=;
        b=cP29OLbdHRskAp77wHJWhiuvjgZFraWG+TtVl68KexN8G+/Lfxhol2RlU8NhJc5RKC
         2vz+7cl0Yj/BSkWDY+hWZRgZnsPSQGKU7lBscuAErD8mXnGAdg2BWmD75vEBq0MqwmS5
         Igl5fPprp+AoGlKqwD811EZI25NrvqEsjyfGxs0355qz14s4o/0ME3+aBdSSvcQ5sFAl
         A6n4wa9UNYg4CtSgOuKEhfQpG0QgqIixkgJaDFXxPikiQNwEgK+mos494H54bYnofHE1
         wHkkRAVyCiBuTnhAX/PDC54pLthQ3Muvi9hNH8GGoXzajrlHnMXNz7VS5TuEK8exzHut
         Q4Jw==
X-Gm-Message-State: AOAM532OIJQgOIaL7fd1gMv4EM+sYLT+Y7nV1wdpHC274FERkayWVP/Q
        bOU39pJV6gfG0w/EJY+Nq1FFQw==
X-Google-Smtp-Source: 
 ABdhPJwTOkdJG78KMA1cbkpd58ybVbgWE4Yb28gKrWNb5KLR35/nvFh/fXM+WeFFZWYUKW90TuTKiQ==
X-Received: by 2002:a17:90a:4482:: with SMTP id
 t2mr5624483pjg.44.1606234658442;
        Tue, 24 Nov 2020 08:17:38 -0800 (PST)
Received: from rahul_yocto_ubuntu18.ibn.broadcom.net ([192.19.234.250])
        by smtp.gmail.com with ESMTPSA id
 t9sm2798549pfq.39.2020.11.24.08.17.34
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 24 Nov 2020 08:17:37 -0800 (PST)
From: Vikas Gupta <vikas.gupta@broadcom.com>
To: eric.auger@redhat.com, alex.williamson@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: vikram.prakash@broadcom.com, srinath.mannam@broadcom.com,
        ashwin.kamath@broadcom.com, zachary.schroff@broadcom.com,
        manish.kurup@broadcom.com, Vikas Gupta <vikas.gupta@broadcom.com>
Subject: [RFC v2 1/1] vfio/platform: add support for msi
Date: Tue, 24 Nov 2020 21:46:46 +0530
Message-Id: <20201124161646.41191-2-vikas.gupta@broadcom.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20201124161646.41191-1-vikas.gupta@broadcom.com>
References: <20201112175852.21572-1-vikas.gupta@broadcom.com>
 <20201124161646.41191-1-vikas.gupta@broadcom.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

MSI support for platform devices.

Signed-off-by: Vikas Gupta <vikas.gupta@broadcom.com>
---
 drivers/vfio/platform/vfio_platform_common.c  |  99 ++++++-
 drivers/vfio/platform/vfio_platform_irq.c     | 260 +++++++++++++++++-
 drivers/vfio/platform/vfio_platform_private.h |  16 ++
 include/uapi/linux/vfio.h                     |  43 +++
 4 files changed, 401 insertions(+), 17 deletions(-)

```
#### [PATCH v12 01/17] s390/vfio-ap: move probe and remove callbacks to vfio_ap_ops.c
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 11929899
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 65440C64E75
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 21:40:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 22E3720866
	for <kvm@archiver.kernel.org>; Tue, 24 Nov 2020 21:40:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="LAkYKbBK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732995AbgKXVkh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 24 Nov 2020 16:40:37 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:13974 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732911AbgKXVkg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 24 Nov 2020 16:40:36 -0500
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0AOLXHiX097163;
        Tue, 24 Nov 2020 16:40:30 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=yioDEj+M63jDuENENQ9FqNpqiIxNZdtbtF02M66jVDY=;
 b=LAkYKbBK1M+6e8GXxLyCPTdxWI0wivKJmtAMQ1saF+MxNw0PMpfV2WjzjyP5Bnt0zdU4
 Hp57hRhJjUWW+86ZkVGY/9Acfup06iLHDf3Ye6jjHHterfRx7Ngkzm1QiWonni9Yu6ga
 podp/HPuEuxcIZ+oEbKGOxd7377U6iv7NALcKJpk6VyjRr39YvLvPXMGH0LOT06b8DtD
 mKJI3oI2+ie3iPGuaFxWRQb8V//Y6JfN0tBEQVJPz0iWTAlvNqSjdZskCuiZGsuOw1Y7
 lbfg1c2Rg6KXZ5jqLK3CyZDLm6sKwj3dB7hZ6oLB1mTNTy/yBYEWcgS9jrMOTR2Pdlqa cg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34ygtubm2u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 16:40:30 -0500
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0AOLXxAS102386;
        Tue, 24 Nov 2020 16:40:30 -0500
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0a-001b2d01.pphosted.com with ESMTP id 34ygtubm2h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 16:40:29 -0500
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0AOLccji009152;
        Tue, 24 Nov 2020 21:40:29 GMT
Received: from b01cxnp22033.gho.pok.ibm.com (b01cxnp22033.gho.pok.ibm.com
 [9.57.198.23])
        by ppma04wdc.us.ibm.com with ESMTP id 34xth92m83-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 24 Nov 2020 21:40:29 +0000
Received: from b01ledav005.gho.pok.ibm.com (b01ledav005.gho.pok.ibm.com
 [9.57.199.110])
        by b01cxnp22033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 0AOLeRcX10027566
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 24 Nov 2020 21:40:27 GMT
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B1D45AE05C;
        Tue, 24 Nov 2020 21:40:27 +0000 (GMT)
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E1CB3AE060;
        Tue, 24 Nov 2020 21:40:26 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.195.249])
        by b01ledav005.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue, 24 Nov 2020 21:40:26 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: freude@linux.ibm.com, borntraeger@de.ibm.com, cohuck@redhat.com,
        mjrosato@linux.ibm.com, pasic@linux.ibm.com,
        alex.williamson@redhat.com, kwankhede@nvidia.com,
        fiuczy@linux.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        hca@linux.ibm.com, gor@linux.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v12 01/17] s390/vfio-ap: move probe and remove callbacks to
 vfio_ap_ops.c
Date: Tue, 24 Nov 2020 16:40:00 -0500
Message-Id: <20201124214016.3013-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20201124214016.3013-1-akrowiak@linux.ibm.com>
References: <20201124214016.3013-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-11-24_08:2020-11-24,2020-11-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 clxscore=1015
 mlxscore=0 impostorscore=0 malwarescore=0 mlxlogscore=999 suspectscore=11
 bulkscore=0 spamscore=0 phishscore=0 lowpriorityscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2011240125
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's move the probe and remove callbacks into the vfio_ap_ops.c
file to keep all code related to managing queues in a single file. This
way, all functions related to queue management can be removed from the
vfio_ap_private.h header file defining the public interfaces for the
vfio_ap device driver.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_drv.c     | 45 ++-----------------------
 drivers/s390/crypto/vfio_ap_ops.c     | 47 +++++++++++++++++++++++++--
 drivers/s390/crypto/vfio_ap_private.h |  7 ++--
 3 files changed, 50 insertions(+), 49 deletions(-)

```
