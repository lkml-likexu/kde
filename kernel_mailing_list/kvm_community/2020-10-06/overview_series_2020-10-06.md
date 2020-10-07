#### [PATCH 1/4 v3] KVM: nSVM: CR3 MBZ bits are only 63:52
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11819079
Return-Path: <SRS0=4WRu=DN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8AA4714F7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  6 Oct 2020 19:07:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 61A88206F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  6 Oct 2020 19:07:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="KpQv3zNS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727007AbgJFTHJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 6 Oct 2020 15:07:09 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:57522 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727002AbgJFTHJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Oct 2020 15:07:09 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 096IxRiZ088708;
        Tue, 6 Oct 2020 19:07:04 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=708udkJmuvBzBN+G7FJxjGzlQoGjWc2P1e/kMUoa7m0=;
 b=KpQv3zNSkeMp7sI5gCTTalhXiJSrjBikdOgL0LPig0Jhh9edmy/AaWrXHHTiJMPMJ0Mt
 MYBRILaBDr8yrPB5Ik4aRlMUWG1mq8yk+nWMYpxx9yS/AjKQkn+UkVGB6ZIm1FDTj7aK
 TD6ktCojLtaHouHB1sUbtYST+jMTGWp+/sYHRsc4WU1YSSutHOfKEL0vRBAY61s6I3be
 Pj/2GLBvcN/Wzetfm2QNxQkJgkM34DjHmFy/e7AAfqXIH8XO/nG3x/xwkiJL4dDo0ZZJ
 5IfR2WznrIWOcBOrLdg4KezIQsdNL85G7XASe9UU6k3NE8uiInRG5zBfxoajtKsvRIOB zw==
Received: from userp3020.oracle.com (userp3020.oracle.com [156.151.31.79])
        by userp2120.oracle.com with ESMTP id 33xhxmwuqb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Tue, 06 Oct 2020 19:07:04 +0000
Received: from pps.filterd (userp3020.oracle.com [127.0.0.1])
        by userp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 096J1BeH095817;
        Tue, 6 Oct 2020 19:07:04 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3020.oracle.com with ESMTP id 33yyjg2kyx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 06 Oct 2020 19:07:03 +0000
Received: from abhmp0015.oracle.com (abhmp0015.oracle.com [141.146.116.21])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 096J72Y8025555;
        Tue, 6 Oct 2020 19:07:02 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 06 Oct 2020 12:07:02 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 1/4 v3] KVM: nSVM: CR3 MBZ bits are only 63:52
Date: Tue,  6 Oct 2020 19:06:51 +0000
Message-Id: <20201006190654.32305-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20201006190654.32305-1-krish.sadhukhan@oracle.com>
References: <20201006190654.32305-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9766
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 adultscore=0 bulkscore=0
 phishscore=0 mlxlogscore=999 mlxscore=0 spamscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2010060123
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9766
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 malwarescore=0 bulkscore=0
 impostorscore=0 lowpriorityscore=0 suspectscore=1 phishscore=0
 mlxlogscore=999 adultscore=0 clxscore=1015 spamscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2010060123
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 761e4169346553c180bbd4a383aedd72f905bc9a created a wrong mask for the
CR3 MBZ bits. According to APM vol 2, only the upper 12 bits are MBZ.

(Fixes 761e4169346553c180bbd4a383aedd72f905bc9a)

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/svm/svm.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: vmx: add regression test for posted interrupts
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11819251
Return-Path: <SRS0=4WRu=DN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 15A536CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  6 Oct 2020 21:26:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E7EDE208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  6 Oct 2020 21:26:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="ALiWkA7i"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727424AbgJFV0A (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 6 Oct 2020 17:26:00 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43468 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727334AbgJFV0A (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Oct 2020 17:26:00 -0400
Received: from mail-pl1-x649.google.com (mail-pl1-x649.google.com
 [IPv6:2607:f8b0:4864:20::649])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 73BA5C061755
        for <kvm@vger.kernel.org>; Tue,  6 Oct 2020 14:26:00 -0700 (PDT)
Received: by mail-pl1-x649.google.com with SMTP id b5so4045plk.2
        for <kvm@vger.kernel.org>; Tue, 06 Oct 2020 14:26:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=m7ttRV8rxTRBgNYSIiZwVYKNAnTImX3Y55fX7B/kzUI=;
        b=ALiWkA7iJQTTIVU6uDzu/Vdsbxuffb31jdFBEG5EMHztgBWCVSbo+afuYKzdfIpQWQ
         a/6WpG9Zwdp+kC4Js3uX8VJP1ibbKM+49VHj45bV7BHCgWcihg4+Sc9ShfxwHage4ahO
         EjE7VJQzVqZNq0iuK0cWu+MyxSXXJ8Uz15V1S/j4Sri2Ph0FI8MBNab1Z7cgSmpcW5xk
         cTHKmkjfA5GiH2KgdrF0Nnj5JyNpnU+ib80YyaJpFq7l0J6B7dOzx7CjoRakgp+zog2m
         81Kf0BHMzr/vkYl8wPNCZ1aqW3iN6uzAd2C8RgEEmyyQDnh/w4919++P6JW4+XolotO2
         TaqA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=m7ttRV8rxTRBgNYSIiZwVYKNAnTImX3Y55fX7B/kzUI=;
        b=TsJJR15Y78X3Yx11BgkTVWxGQAknuof7FkVfoWyhSNAf5+zoNHaVfaulIAQqtF8Dq7
         1IOjnelchF8MZa5KtOY3M6nvybLggJMwzhWQvelPgOjdJO7IP4Is1WZgSoerrYYf53Cr
         dTWNnfbL1b6gCXc8EbJFMBsetyHJhOq6C6Pp8G0bpdJFGcUJ6c63JZuLoSbXaUbov5dS
         /8/WSCaeimvj9HaDlq0tZMT2Do+5p+oDuhH4wDqbbWSXqnwOzwZxLt196zxkKGuyj60F
         QiRpbTTuOuYU9y8I07CqfpLsqzLFEUOupSRzic6sk0hjzqgxqN/f323QgNzhOoJbMOPQ
         F/wg==
X-Gm-Message-State: AOAM531Q7nwMpJ1wVA/jAT0sAWE6lnQ2l7QqQWAtzkYEx9dMKjOkMQH6
        2MjpBYrs/uewhiLs8ACd5Fzz2VbBdSiG2KLKjqEEYunG3ZOE3IAOkn0je9hxeMOoBis/uO9lIIT
        ss01nDDgQ0jL+gEMbPxofwngtL0bMoERDYzT2eHuSmD92ZdaAGvSG0MxnAw==
X-Google-Smtp-Source: 
 ABdhPJylZ8fFG2yjs/EezQopTT1eYnCvaEcVFpyYUxDY/BlpHzBRr2kIpLRO5v10ibzhxWcCFJDCsBDCAfg=
Sender: "oupton via sendgmr" <oupton@oupton.sea.corp.google.com>
X-Received: from oupton.sea.corp.google.com
 ([2620:15c:100:202:f693:9fff:fef5:7be1])
 (user=oupton job=sendgmr) by 2002:a17:90a:1188:: with SMTP id
 e8mr58668pja.61.1602019559785; Tue, 06 Oct 2020 14:25:59 -0700 (PDT)
Date: Tue,  6 Oct 2020 14:25:56 -0700
Message-Id: <20201006212556.882066-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.806.g8561365e88-goog
Subject: [kvm-unit-tests PATCH] x86: vmx: add regression test for posted
 interrupts
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If a guest blocks interrupts for the entirety of running in root mode
(RFLAGS.IF=0), a pending interrupt corresponding to the posted-interrupt
vector set in the VMCS should result in an interrupt posting to the vIRR
at VM-entry. However, on KVM this is not the case. The pending interrupt
is not recognized as the posted-interrupt vector and instead results in
an external interrupt VM-exit.

Add a regression test to exercise this issue.

Signed-off-by: Oliver Upton <oupton@google.com>
---
 lib/x86/asm/bitops.h |  8 +++++
 x86/vmx_tests.c      | 76 ++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 84 insertions(+)

```
#### [PATCH 1/4] selftests: kvm: Fix the segment descriptor layout to match the actual layout
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11819231
Return-Path: <SRS0=4WRu=DN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 81BDB14D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  6 Oct 2020 21:04:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B81520897
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  6 Oct 2020 21:04:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="jMx5D4b3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727398AbgJFVE4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 6 Oct 2020 17:04:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40208 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727396AbgJFVE4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 6 Oct 2020 17:04:56 -0400
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CD19DC061755
        for <kvm@vger.kernel.org>; Tue,  6 Oct 2020 14:04:54 -0700 (PDT)
Received: by mail-pj1-x1049.google.com with SMTP id f9so2071548pjp.1
        for <kvm@vger.kernel.org>; Tue, 06 Oct 2020 14:04:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:in-reply-to:message-id:mime-version:references:subject
         :from:to:cc;
        bh=wmYneUmReevw5Pig2V/tCQ1QYvT7hoDCFpGFyyX8HMk=;
        b=jMx5D4b31/HZQNBv3S4nKM7itXd9++V5P0R3U6G/z9sZgEjK8YGhJouYdz67Oj+z+v
         rpIq93I5dCKyob0R78ScFpTopgcEeN7PTl7u2Ad53E06FODAMdSVo/W1NAlRRdpuuqqE
         6+e74MXJqjSWcCRLsoRMkvFK7kwrbFTWDIo8lNeQkIw+Un8KmkSDD68T6ylQZtzE+onl
         6GWt4mbkbU7odbhO/ijc/dK+LQUlZchdwTWNZ0jV50/dROsjfralzYtYfOQk9SJO/rQ0
         3mnuJQht8qdCgAxnKwG+vHqTE91TXs8IOxEjuls+KIwpXdI35Hhoe15kpN5r92hczpLa
         3BSA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=wmYneUmReevw5Pig2V/tCQ1QYvT7hoDCFpGFyyX8HMk=;
        b=gDV0bPwkDp7PfyoVjQtfGRXmTI8LsTTfcyNLKdW434kmPQLDtpcRBXI05mxOw7NSuI
         Gx7w2ceVUJxGgy2J7sDuT5XDVTlAfwMFliTcy7XQZexc9hV6xA4vxR2lUcChCUEfcQYk
         aDH3lNO+VkSm28ZVm10O2qU7o4LAOKsbpORzeHbPz2KN+F8mXQa8myPbE8SK3VRsf+62
         iH1qcmxxdKlHKpn+7bnLpSybo+3Kbq72OlwdN+E7MQiTilfKBpwz05uH/f/Hv6g5Xdmv
         S/xnx83o74Kcr7MOBYOHOVq2sPDkTe4frCINiYdRgp68rmhoEAhYcZ9JZzKdT/AGJxWA
         YLcQ==
X-Gm-Message-State: AOAM533ulDmpPj086WdQ9ixGzM3LaIA9BMTr1mxGtY7BXL2Ubhr/Vxfh
        XAS7HRLV1LFI3uvnY6rN4R/A4DNw78GnHAv6
X-Google-Smtp-Source: 
 ABdhPJyxgr0bpMMNTHMjf4WLJJCvA+/4wjgsPYU1+6fXUK5fzWw2dIHr2WXJT+sagYEbC6YlaO1sCcfMzpQwM8HG
Sender: "aaronlewis via sendgmr" <aaronlewis@aaronlewis1.sea.corp.google.com>
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:a28c:fdff:fed8:8d46])
 (user=aaronlewis job=sendgmr) by 2002:a17:90b:ed4:: with SMTP id
 gz20mr24624pjb.92.1602018294314; Tue, 06 Oct 2020 14:04:54 -0700 (PDT)
Date: Tue,  6 Oct 2020 14:04:41 -0700
In-Reply-To: <20201006210444.1342641-1-aaronlewis@google.com>
Message-Id: <20201006210444.1342641-2-aaronlewis@google.com>
Mime-Version: 1.0
References: <20201006210444.1342641-1-aaronlewis@google.com>
X-Mailer: git-send-email 2.28.0.806.g8561365e88-goog
Subject: [PATCH 1/4] selftests: kvm: Fix the segment descriptor layout to
 match the actual layout
From: Aaron Lewis <aaronlewis@google.com>
To: graf@amazon.com
Cc: pshier@google.com, jmattson@google.com, kvm@vger.kernel.org,
        Aaron Lewis <aaronlewis@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the layout of 'struct desc64' to match the layout described in the
SDM Vol 3, Chapter 3 "Protected-Mode Memory Management", section 3.4.5
"Segment Descriptors", Figure 3-8 "Segment Descriptor".  The test added
later in this series relies on this and crashes if this layout is not
correct.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 tools/testing/selftests/kvm/include/x86_64/processor.h | 2 +-
 tools/testing/selftests/kvm/lib/x86_64/processor.c     | 3 ++-
 2 files changed, 3 insertions(+), 2 deletions(-)

```
