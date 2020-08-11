#### [kvm-unit-tests PATCH 1/7] x86: Makefile: Allow division on x86_64-elf binutils
##### From: Roman Bolshakov <r.bolshakov@yadro.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Roman Bolshakov <r.bolshakov@yadro.com>
X-Patchwork-Id: 11707385
Return-Path: <SRS0=x1XU=BU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ECEA9109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 13:06:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D54A92073A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 13:06:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=yadro.com header.i=@yadro.com
 header.b="S6AqCDnV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726819AbgHJNGi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Aug 2020 09:06:38 -0400
Received: from mta-02.yadro.com ([89.207.88.252]:47970 "EHLO mta-01.yadro.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726582AbgHJNGh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Aug 2020 09:06:37 -0400
Received: from localhost (unknown [127.0.0.1])
        by mta-01.yadro.com (Postfix) with ESMTP id 616844C8A9;
        Mon, 10 Aug 2020 13:06:35 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=yadro.com; h=
        content-type:content-type:content-transfer-encoding:mime-version
        :references:in-reply-to:x-mailer:message-id:date:date:subject
        :subject:from:from:received:received:received; s=mta-01; t=
        1597064793; x=1598879194; bh=wUN5jHU/zBYZJQjo7ncYgKjE4TFXDiYyECm
        cEyGlvTw=; b=S6AqCDnVKm+zYVsyyqJIeaCXl+mnCRs4tJMlAa+x9VBIB2IqoEd
        gtGocw6qsdK8gyU9F2MjD2aGcUoXFSev6pPm8F621ybMmIHH2tnVzYVJEBsvxb0C
        ywX2st9IT5AoKCRPs6Q49lBDkb7nMhZc7Ywq5e0Lm+0PhhqAkzCh+y38=
X-Virus-Scanned: amavisd-new at yadro.com
Received: from mta-01.yadro.com ([127.0.0.1])
        by localhost (mta-01.yadro.com [127.0.0.1]) (amavisd-new, port 10024)
        with ESMTP id X6ktgHB82ZA5; Mon, 10 Aug 2020 16:06:33 +0300 (MSK)
Received: from T-EXCH-02.corp.yadro.com (t-exch-02.corp.yadro.com
 [172.17.10.102])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-SHA384 (256/256 bits))
        (No client certificate requested)
        by mta-01.yadro.com (Postfix) with ESMTPS id E45D54C890;
        Mon, 10 Aug 2020 16:06:33 +0300 (MSK)
Received: from localhost (172.17.204.212) by T-EXCH-02.corp.yadro.com
 (172.17.10.102) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384_P384) id 15.1.669.32; Mon, 10
 Aug 2020 16:06:33 +0300
From: Roman Bolshakov <r.bolshakov@yadro.com>
To: <kvm@vger.kernel.org>
CC: Roman Bolshakov <r.bolshakov@yadro.com>,
        Cameron Esfahani <dirty@apple.com>
Subject: [kvm-unit-tests PATCH 1/7] x86: Makefile: Allow division on
 x86_64-elf binutils
Date: Mon, 10 Aug 2020 16:06:12 +0300
Message-ID: <20200810130618.16066-2-r.bolshakov@yadro.com>
X-Mailer: git-send-email 2.26.1
In-Reply-To: <20200810130618.16066-1-r.bolshakov@yadro.com>
References: <20200810130618.16066-1-r.bolshakov@yadro.com>
MIME-Version: 1.0
X-Originating-IP: [172.17.204.212]
X-ClientProxiedBy: T-EXCH-01.corp.yadro.com (172.17.10.101) To
 T-EXCH-02.corp.yadro.com (172.17.10.102)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For compatibility with other SVR4 assemblers, '/' starts a comment on
*-elf binutils target and thus division operator is not allowed [1][2].
That breaks cstart64.S build:

  x86/cstart64.S: Assembler messages:
  x86/cstart64.S:294: Error: unbalanced parenthesis in operand 1.

The option is ignored on the Linux target of GNU binutils.

1. https://sourceware.org/binutils/docs/as/i386_002dChars.html
2. https://sourceware.org/binutils/docs/as/i386_002dOptions.html#index-_002d_002ddivide-option_002c-i386

Cc: Cameron Esfahani <dirty@apple.com>
Signed-off-by: Roman Bolshakov <r.bolshakov@yadro.com>
---
 x86/Makefile | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v2 1/8] KVM: x86: Add ioctl for accepting a userspace provided MSR list
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11708107
Return-Path: <SRS0=x1XU=BU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 50600739
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 20:11:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3046A20678
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 20:11:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="i59gTdRa"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726396AbgHJULr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Aug 2020 16:11:47 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51418 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726143AbgHJULr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Aug 2020 16:11:47 -0400
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 46197C061756
        for <kvm@vger.kernel.org>; Mon, 10 Aug 2020 13:11:47 -0700 (PDT)
Received: by mail-pj1-x1049.google.com with SMTP id s4so535058pjq.8
        for <kvm@vger.kernel.org>; Mon, 10 Aug 2020 13:11:47 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=5oAjokWOZe4cAdJFgfr8j682KuQkIW1okam8n6z5dy8=;
        b=i59gTdRapHyeCjEIgC6k7Z6BefmKEkcLk0+1v8FF7cm2ERlx1uHnIQGWOkDdO2e4j9
         TA6kjushKsVVelS0Gfx/Q7ybyzqloGYVNDLuH4Fc08tQpejJrrbJA59wtIW4OiSLPWH3
         ur+T82okRpFkuz+lPAkddiP8njjUZl3edbZ92bXK2P13p60m1F15aGYNkk6VEk8oBBb3
         Rv680oVKT81RW4hDrYoras8S3pY3YsB/F5AckzuuKDSyCJDyuEdM3XlyvrvsGgNOeKdm
         32pZ3yCJwiJR6UCZqBD5suGRD2DGW85wDrUC9uLipWq0VgV88vEhwKL2chEK0lXmEiWy
         tpPg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=5oAjokWOZe4cAdJFgfr8j682KuQkIW1okam8n6z5dy8=;
        b=PGE32LilIaOowaxX7fqpwXH4S17v3KEIHq3/az7TGog+p99LGhaFzaUExnZCZnynSs
         TIKOzDBTwFa7veheO9ZoX2NLm1cfrsRMxVhS3EgBKfxHquav1eTxrK8Y5gWIbf8LBVhK
         PMTyh+PikhS2sOyrxCSnwzXUbfEmFUDs537MZ0URPRM9Mv40NpCw4qVTh5KEtkk3JZwE
         Q4tyXTSt4g4Twpfjsm3mrngaP9paevo5UEw36Eg6PdqzFPcDTvBdFCLC8mkHNqzgz8+N
         chH8RmgwBBvgqgTIhxWiTIwbdpkn1cBvNYm8Hreho+lBA2aXKDq9D9YrZByZkJQflwAa
         JrGw==
X-Gm-Message-State: AOAM5321fB2McDDHDUyTqfHr1ZK8KzBcPc3TKTuyWq4WEAqY09Olsshf
        xAtg8Nqu3mW35fxvGpjqKFuW00yikRvgFhNE
X-Google-Smtp-Source: 
 ABdhPJwdJ6t5/vb3IuTDPqMyfW341aPpIqq/ytFj+8mB54vEu+1b3PjuQ0LgzRAdIR/5dEZ1HWnMNmT+YELWCvnU
X-Received: by 2002:a17:90a:2110:: with SMTP id
 a16mr1027012pje.104.1597090306166;
 Mon, 10 Aug 2020 13:11:46 -0700 (PDT)
Date: Mon, 10 Aug 2020 13:11:27 -0700
In-Reply-To: <20200810201134.2031613-1-aaronlewis@google.com>
Message-Id: <20200810201134.2031613-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20200810201134.2031613-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [PATCH v2 1/8] KVM: x86: Add ioctl for accepting a userspace provided
 MSR list
From: Aaron Lewis <aaronlewis@google.com>
To: jmattson@google.com, graf@amazon.com
Cc: pshier@google.com, oupton@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add KVM_SET_EXIT_MSRS ioctl to allow userspace to pass in a list of MSRs
that force an exit to userspace when rdmsr or wrmsr are used by the
guest.

KVM_SET_EXIT_MSRS will need to be called before any vCPUs are
created to protect the 'user_exit_msrs' list from being mutated while
vCPUs are running.

Add KVM_CAP_SET_MSR_EXITS to identify the feature exists.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Oliver Upton <oupton@google.com>
---
 Documentation/virt/kvm/api.rst  | 24 +++++++++++++++++++
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/x86.c              | 41 +++++++++++++++++++++++++++++++++
 include/uapi/linux/kvm.h        |  2 ++
 4 files changed, 69 insertions(+)

```
#### [PATCH] KVM: nSVM: Test combinations of EFER.LME, CR0.PG, CR4.PAE, CR0.PE and CS register on VMRUN of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11708339
Return-Path: <SRS0=x1XU=BU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CCB52913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 22:40:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B232E206DA
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 22:40:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="AsB9aKMn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726778AbgHJWkU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Aug 2020 18:40:20 -0400
Received: from userp2130.oracle.com ([156.151.31.86]:33088 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726634AbgHJWkU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Aug 2020 18:40:20 -0400
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07AMVnvu139859;
        Mon, 10 Aug 2020 22:40:17 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id; s=corp-2020-01-29;
 bh=UXEW9jo2ubap1L0jIA9ExRp2jPQwMgBNiy7G8DeReJI=;
 b=AsB9aKMnLmneYcWroWuDeTzSve6gJqZKs5OK6OgyWDhBXNQl9YwmuZlY/o0TyPdZBSWI
 nE+fuz5hOKCLzZ7yELYouwliL/aPFD5a80EJ5YK3aDhkIvDd+7dG+0zqeinVCRaJDZ7f
 s1oWLo+rkal4984clkiwyVVcxDUOAZZwfi2RGv4R9vFLJB/i1i9fGO1lw8s/qAjOgjM/
 wtMhwqItRgnee5uK/oLjgrXVJFifON5LDYyEw1qmu65BrgZhFSesMLELSe/hTohxQqUe
 ahAEahRCeuNoDkuGG7LeuzJ/qeRiYx0U9GExFG9BdEMpD1bGIRA5lsL4fj+l770M237Z XA==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2130.oracle.com with ESMTP id 32t2ydfrnk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 10 Aug 2020 22:40:16 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 07AMcMwG092600;
        Mon, 10 Aug 2020 22:40:16 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by userp3030.oracle.com with ESMTP id 32t5yxkjvk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 Aug 2020 22:40:16 +0000
Received: from abhmp0010.oracle.com (abhmp0010.oracle.com [141.146.116.16])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 07AMeFto021275;
        Mon, 10 Aug 2020 22:40:15 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 10 Aug 2020 22:40:07 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH] KVM: nSVM: Test combinations of EFER.LME, CR0.PG, CR4.PAE,
 CR0.PE and CS register on VMRUN of nested guests
Date: Mon, 10 Aug 2020 22:39:27 +0000
Message-Id: <20200810223927.82895-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9709
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 malwarescore=0
 mlxscore=0 phishscore=0
 bulkscore=0 adultscore=0 spamscore=0 suspectscore=1 mlxlogscore=918
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2008100155
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9709
 signatures=668679
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=894
 priorityscore=1501
 malwarescore=0 impostorscore=0 lowpriorityscore=0 mlxscore=0 bulkscore=0
 suspectscore=1 phishscore=0 adultscore=0 spamscore=0 clxscore=1015
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2008100154
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Canonicalization and Consistency Checks" in APM vol. 2
the following guest state combinations are illegal:

	* EFER.LME and CR0.PG are both set and CR4.PAE is zero.
	* EFER.LME and CR0.PG are both non-zero and CR0.PE is zero.
	* EFER.LME, CR0.PG, CR4.PAE, CS.L, and CS.D are all non-zero

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/svm_tests.c | 44 ++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 44 insertions(+)

```
#### [PATCH] KVM: PPC: Book3S HV: XICS: Replace the 'destroy' method by a 'release' method
##### From: Greg Kurz <groug@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 11707225
Return-Path: <SRS0=x1XU=BU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD26E618
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 10:08:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B7D5420709
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 10:08:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726401AbgHJKIP convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Aug 2020 06:08:15 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:20124 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726092AbgHJKIP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Aug 2020 06:08:15 -0400
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-474-KOYHSci-PpmpWRVer1iS1A-1; Mon, 10 Aug 2020 06:08:09 -0400
X-MC-Unique: KOYHSci-PpmpWRVer1iS1A-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3056FE919;
        Mon, 10 Aug 2020 10:08:08 +0000 (UTC)
Received: from bahia.lan (ovpn-112-38.ams2.redhat.com [10.36.112.38])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7CFA88FA3E;
        Mon, 10 Aug 2020 10:08:06 +0000 (UTC)
Subject: [PATCH] KVM: PPC: Book3S HV: XICS: Replace the 'destroy' method by a
 'release' method
From: Greg Kurz <groug@kaod.org>
To: Paul Mackerras <paulus@ozlabs.org>
Cc: David Gibson <david@gibson.dropbear.id.au>, =?utf-8?q?C=C3=A9dric_Le_Goa?=
	=?utf-8?q?ter?= <clg@kaod.org>, kvm-ppc@vger.kernel.org, kvm@vger.kernel.org
Date: Mon, 10 Aug 2020 12:08:05 +0200
Message-ID: <159705408550.1308430.10165736270896374279.stgit@bahia.lan>
User-Agent: StGit/0.21
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Authentication-Results: relay.mimecast.com;
        auth=pass smtp.auth=CUSA124A263 smtp.mailfrom=groug@kaod.org
X-Mimecast-Spam-Score: 0
X-Mimecast-Originator: kaod.org
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Similarly to what was done with XICS-on-XIVE and XIVE native KVM devices
with commit 5422e95103cf ("KVM: PPC: Book3S HV: XIVE: Replace the 'destroy'
method by a 'release' method"), convert the historical XICS KVM device to
implement the 'release' method. This is needed to run nested guests with
an in-kernel IRQ chip. A typical POWER9 guest can select XICS or XIVE
during boot, which requires to be able to destroy and to re-create the
KVM device. Only the historical XICS KVM device is available under pseries
at the current time and it still uses the legacy 'destroy' method.

Switching to 'release' means that vCPUs might still be running when the
device is destroyed. In order to avoid potential use-after-free, the
kvmppc_xics structure is allocated on first usage and kept around until
the VM exits. The same pointer is used each time a KVM XICS device is
being created, but this is okay since we only have one per VM.

Clear the ICP of each vCPU with vcpu->mutex held. This ensures that the
next time the vCPU resumes execution, it won't be going into the XICS
code anymore.

Signed-off-by: Greg Kurz <groug@kaod.org>
---
 arch/powerpc/include/asm/kvm_host.h |    1 
 arch/powerpc/kvm/book3s.c           |    4 +-
 arch/powerpc/kvm/book3s_xics.c      |   86 ++++++++++++++++++++++++++++-------
 3 files changed, 72 insertions(+), 19 deletions(-)

```
#### [PATCH] kvm: selftests: fix spelling mistake: "missmatch" -> "missmatch"
##### From: Colin King <colin.king@canonical.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Colin Ian King <colin.king@canonical.com>
X-Patchwork-Id: 11707245
Return-Path: <SRS0=x1XU=BU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C4508913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 10:16:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B4AE22073A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 10:16:55 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726430AbgHJKQw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Aug 2020 06:16:52 -0400
Received: from youngberry.canonical.com ([91.189.89.112]:54904 "EHLO
        youngberry.canonical.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725846AbgHJKQv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Aug 2020 06:16:51 -0400
Received: from 1.general.cking.uk.vpn ([10.172.193.212] helo=localhost)
        by youngberry.canonical.com with esmtpsa
 (TLS1.2:ECDHE_RSA_AES_128_GCM_SHA256:128)
        (Exim 4.86_2)
        (envelope-from <colin.king@canonical.com>)
        id 1k54rI-0007Lc-2U; Mon, 10 Aug 2020 10:16:48 +0000
From: Colin King <colin.king@canonical.com>
To: Paolo Bonzini <pbonzini@redhat.com>, Shuah Khan <shuah@kernel.org>,
        kvm@vger.kernel.org, linux-kselftest@vger.kernel.org
Cc: kernel-janitors@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] kvm: selftests: fix spelling mistake: "missmatch" ->
 "missmatch"
Date: Mon, 10 Aug 2020 11:16:47 +0100
Message-Id: <20200810101647.62039-1-colin.king@canonical.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Colin Ian King <colin.king@canonical.com>

There is a spelling mistake in an error message. Fix it.

Signed-off-by: Colin Ian King <colin.king@canonical.com>
---
 tools/testing/selftests/kvm/lib/sparsebit.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH kvmtool] update_headers.sh: Remove arm architecture
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11707563
Return-Path: <SRS0=x1XU=BU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 49DAB1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 15:25:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 34EA122D02
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 15:25:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727885AbgHJPZL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Aug 2020 11:25:11 -0400
Received: from foss.arm.com ([217.140.110.172]:57218 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727897AbgHJPZI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Aug 2020 11:25:08 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 6A8261063;
        Mon, 10 Aug 2020 08:25:08 -0700 (PDT)
Received: from monolith.localdoman (arm6-cctv-system.cambridge.arm.com
 [10.37.12.8])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 921F53F575;
        Mon, 10 Aug 2020 08:25:07 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com,
        andre.przyware@arm.com
Subject: [PATCH kvmtool] update_headers.sh: Remove arm architecture
Date: Mon, 10 Aug 2020 16:25:56 +0100
Message-Id: <20200810152556.214896-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM host support for the arm architecture was removed in commit
541ad0150ca4 ("arm: Remove 32bit KVM host support"). When trying to sync
KVM headers we get this error message:

$ util/update_headers.sh /path/to/linux
cp: cannot stat '/path/to/linux/arch/arm/include/uapi/asm/kvm.h': No such file or directory

Do not attempting to copy KVM headers for that architecture.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 util/update_headers.sh | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH kvmtool] update_headers.sh: Remove arm architecture
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11707587
Return-Path: <SRS0=x1XU=BU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E605314E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 15:37:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D147122D6F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 15:37:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728266AbgHJPhh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Aug 2020 11:37:37 -0400
Received: from foss.arm.com ([217.140.110.172]:57618 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728036AbgHJPhf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Aug 2020 11:37:35 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id B2FF21063;
        Mon, 10 Aug 2020 08:37:34 -0700 (PDT)
Received: from monolith.localdoman (arm6-cctv-system.cambridge.arm.com
 [10.37.12.8])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 0A3623F575;
        Mon, 10 Aug 2020 08:37:33 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org
Cc: will@kernel.org, julien.thierry.kdev@gmail.com
Subject: [PATCH kvmtool] update_headers.sh: Remove arm architecture
Date: Mon, 10 Aug 2020 16:38:28 +0100
Message-Id: <20200810153828.216821-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM host support for the arm architecture was removed in commit
541ad0150ca4 ("arm: Remove 32bit KVM host support"). When trying to sync
KVM headers we get this error message:

$ util/update_headers.sh /path/to/linux
cp: cannot stat '/path/to/linux/arch/arm/include/uapi/asm/kvm.h': No such file or directory

Do not attempting to copy KVM headers for that architecture.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 util/update_headers.sh | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH v3] s390x: Ultravisor guest API test
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11707635
Return-Path: <SRS0=x1XU=BU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7339A1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 15:45:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4CB5420866
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 15:45:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="HDSBOPMM"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727003AbgHJPpy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Aug 2020 11:45:54 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:34866 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726406AbgHJPpy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 Aug 2020 11:45:54 -0400
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 07AFVikc065629;
        Mon, 10 Aug 2020 11:45:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=D+ASZcqKtcFDX3Oet0jclC1hytDntn4V5JUbCOXSux8=;
 b=HDSBOPMMAsd4mT/eOYpkj/nTHbx+dRa+MfIhMM/ifse6KeQQdn8ppopmjdVMcZ1qQ3o6
 MTZoLKwIGWyKBCVaq0upZ2SrVYoiU3nTcmlUEF1p3BQCwzAITJ1pEebOOW4PGOYF8WF6
 r0rPsyitU9yctrXGrul8pZ0hBR3e5yDXAGln/E4YIfPuotqLdDI2jBtgczw1EJ0T2qpw
 8zKKRn0OUiHH7rwS6v/LCZ6wbCjIMBUlhl0H8o+MDsZAiN4Fp9fnv2iigzDrohmKVykZ
 4ZN7mtMzx0Y2pc+5kjV+n8ZlQg9GdtkNy9Z6G+wm2njiu7o4wERaVnkE2dH1vBpOmYQk iw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32src0ytew-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Aug 2020 11:45:52 -0400
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 07AFcnFB088490;
        Mon, 10 Aug 2020 11:45:52 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0b-001b2d01.pphosted.com with ESMTP id 32src0yte0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Aug 2020 11:45:52 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 07AFdqkg009418;
        Mon, 10 Aug 2020 15:45:50 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma03fra.de.ibm.com with ESMTP id 32skp81fu0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Aug 2020 15:45:49 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 07AFjl7g30278132
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 Aug 2020 15:45:47 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1CD3EA4054;
        Mon, 10 Aug 2020 15:45:47 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4E41AA405F;
        Mon, 10 Aug 2020 15:45:46 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 10 Aug 2020 15:45:46 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, linux-s390@vger.kernel.org, david@redhat.com,
        borntraeger@de.ibm.com, cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v3] s390x: Ultravisor guest API test
Date: Mon, 10 Aug 2020 11:45:41 -0400
Message-Id: <20200810154541.32974-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200810173205.2daaaca1.cohuck@redhat.com>
References: <20200810173205.2daaaca1.cohuck@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-10_11:2020-08-06,2020-08-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 mlxlogscore=999 malwarescore=0 priorityscore=1501 impostorscore=0
 spamscore=0 phishscore=0 mlxscore=0 bulkscore=0 adultscore=0
 suspectscore=3 clxscore=1015 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2008100113
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Test the error conditions of guest 2 Ultravisor calls, namely:
     * Query Ultravisor information
     * Set shared access
     * Remove shared access

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Acked-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 lib/s390x/asm/uv.h  |  74 ++++++++++++++++++++++
 s390x/Makefile      |   1 +
 s390x/unittests.cfg |   3 +
 s390x/uv-guest.c    | 150 ++++++++++++++++++++++++++++++++++++++++++++
 4 files changed, 228 insertions(+)
 create mode 100644 lib/s390x/asm/uv.h
 create mode 100644 s390x/uv-guest.c

diff --git a/lib/s390x/asm/uv.h b/lib/s390x/asm/uv.h
new file mode 100644
index 0000000..4c2fc48
--- /dev/null
+++ b/lib/s390x/asm/uv.h
@@ -0,0 +1,74 @@
+/*
+ * s390x Ultravisor related definitions
+ *
+ * Copyright (c) 2020 IBM Corp
+ *
+ * Authors:
+ *  Janosch Frank <frankja@linux.ibm.com>
+ *
+ * This code is free software; you can redistribute it and/or modify it
+ * under the terms of the GNU General Public License version 2.
+ */
+#ifndef UV_H
+#define UV_H
+
+#define UVC_RC_EXECUTED		0x0001
+#define UVC_RC_INV_CMD		0x0002
+#define UVC_RC_INV_STATE	0x0003
+#define UVC_RC_INV_LEN		0x0005
+#define UVC_RC_NO_RESUME	0x0007
+
+#define UVC_CMD_QUI			0x0001
+#define UVC_CMD_SET_SHARED_ACCESS	0x1000
+#define UVC_CMD_REMOVE_SHARED_ACCESS	0x1001
+
+/* Bits in installed uv calls */
+enum uv_cmds_inst {
+	BIT_UVC_CMD_QUI = 0,
+	BIT_UVC_CMD_SET_SHARED_ACCESS = 8,
+	BIT_UVC_CMD_REMOVE_SHARED_ACCESS = 9,
+};
+
+struct uv_cb_header {
+	u16 len;
+	u16 cmd;	/* Command Code */
+	u16 rc;		/* Response Code */
+	u16 rrc;	/* Return Reason Code */
+} __attribute__((packed))  __attribute__((aligned(8)));
+
+struct uv_cb_qui {
+	struct uv_cb_header header;
+	u64 reserved08;
+	u64 inst_calls_list[4];
+	u64 reserved30[15];
+} __attribute__((packed))  __attribute__((aligned(8)));
+
+struct uv_cb_share {
+	struct uv_cb_header header;
+	u64 reserved08[3];
+	u64 paddr;
+	u64 reserved28;
+} __attribute__((packed))  __attribute__((aligned(8)));
+
+static inline int uv_call(unsigned long r1, unsigned long r2)
+{
+	int cc;
+
+	/*
+	 * The brc instruction will take care of the cc 2/3 case where
+	 * we need to continue the execution because we were
+	 * interrupted. The inline assembly will only return on
+	 * success/error i.e. cc 0/1.
+	*/
+	asm volatile(
+		"0:	.insn rrf,0xB9A40000,%[r1],%[r2],0,0\n"
+		"		brc	3,0b\n"
+		"		ipm	%[cc]\n"
+		"		srl	%[cc],28\n"
+		: [cc] "=d" (cc)
+		: [r1] "a" (r1), [r2] "a" (r2)
+		: "memory", "cc");
+	return cc;
+}
+
+#endif
```
#### [PATCH RESEND for-5.9] MIPS: KVM: Convert a fallthrough comment to fallthrough
##### From: Jiaxun Yang <jiaxun.yang@flygoat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiaxun Yang <jiaxun.yang@flygoat.com>
X-Patchwork-Id: 11706867
Return-Path: <SRS0=x1XU=BU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D4EC13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 01:18:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 64CEC206A5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Aug 2020 01:18:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=flygoat.com header.i=@flygoat.com header.b="EEsH19KD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726426AbgHJBSH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 9 Aug 2020 21:18:07 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47664 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726398AbgHJBSG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 9 Aug 2020 21:18:06 -0400
Received: from vultr.net.flygoat.com (vultr.net.flygoat.com
 [IPv6:2001:19f0:6001:3633:5400:2ff:fe8c:553])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 954DAC061756;
        Sun,  9 Aug 2020 18:18:06 -0700 (PDT)
Received: from localhost.localdomain (unknown
 [IPv6:2001:da8:20f:4430:250:56ff:fe9a:7470])
        by vultr.net.flygoat.com (Postfix) with ESMTPSA id 424221FEB9;
        Mon, 10 Aug 2020 01:18:04 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple; d=flygoat.com; s=vultr;
        t=1597022285; bh=8jQ64yO0EFa1VJiLGME1MgLg11GF98tS7gIUdOBhOiQ=;
        h=From:To:Cc:Subject:Date:From;
        b=EEsH19KDnT1uEf4a0B9NIhWOOU6stKWgPIlQlNyf1tFohCU6+sDlevBNZYeoIXnKu
         jBb12KbUfFWx0XytP/6KnJaSstuzquOS8M1HxxCsFvQM+tBJPoKsuyaHTxd/nKLMzE
         Qlsj8iOkPey4IxTTBE+05/3pg3Yab/5j4pH1J6PkM6l/U+hkMn/lLxaEs+Er24Qhtv
         XvGkfcteTSjL1KvWZyakXbSsdbpgzczz8JbhvbYeE5G2ktAbl+/XDxEs3DdBhHO5P2
         dboxNGj0cLxEOjieFR/q6Fv8Zjez89fVeKns9Thb97wfvOoKTSW0BVzp4Le7/Ln44Y
         VkbbCAyyckmRQ==
From: Jiaxun Yang <jiaxun.yang@flygoat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Huacai Chen <chenhc@lemote.com>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        linux-mips@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH RESEND for-5.9] MIPS: KVM: Convert a fallthrough comment to
 fallthrough
Date: Mon, 10 Aug 2020 09:17:49 +0800
Message-Id: <20200810011749.3211128-1-jiaxun.yang@flygoat.com>
X-Mailer: git-send-email 2.28.0.rc1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There is a fallthrough comment being forgotten,
GCC complains about it:

arch/mips/kvm/emulate.c: In function kvm_mips_emulate_load:
arch/mips/kvm/emulate.c:1936:21: error: this statement may fall through
 1936 |   vcpu->mmio_needed = 1; /* unsigned */
      |   ~~~~~~~~~~~~~~~~~~^~~
arch/mips/kvm/emulate.c:1939:2: note: here
 1939 |  case lw_op:

Just fix it.

Signed-off-by: Jiaxun Yang <jiaxun.yang@flygoat.com>
Reviewed-by: Huacai Chen <chenhc@lemote.com>
---
This is blocking KVM MIPS from build, so it needs to get into 5.9.
---
 arch/mips/kvm/emulate.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
