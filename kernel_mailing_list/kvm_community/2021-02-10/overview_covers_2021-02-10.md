

#### [PATCH 0/7] x86/seves: Support 32-bit boot path and other updates
##### From: Joerg Roedel <joro@8bytes.org>
From: Joerg Roedel <jroedel@suse.de>

```c
From patchwork Wed Feb 10 10:21:28 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12080465
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EE72DC433DB
	for <kvm@archiver.kernel.org>; Wed, 10 Feb 2021 10:26:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A5FF964E3B
	for <kvm@archiver.kernel.org>; Wed, 10 Feb 2021 10:26:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231208AbhBJKZ6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Feb 2021 05:25:58 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:44856 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230362AbhBJKWj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Feb 2021 05:22:39 -0500
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 130B6C061574;
        Wed, 10 Feb 2021 02:21:59 -0800 (PST)
Received: from cap.home.8bytes.org (p549adcf6.dip0.t-ipconnect.de
 [84.154.220.246])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id E7E49310;
        Wed, 10 Feb 2021 11:21:54 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH 0/7] x86/seves: Support 32-bit boot path and other updates
Date: Wed, 10 Feb 2021 11:21:28 +0100
Message-Id: <20210210102135.30667-1-joro@8bytes.org>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Hi,

these patches add support for the 32-bit boot in the decompressor
code. This is needed to boot an SEV-ES guest on some firmware and grub
versions. The patches also add the necessary CPUID sanity checks and a
32-bit version of the C-bit check.

Other updates included here:

	1. Add code to shut down exception handling in the
	   decompressor code before jumping to the real kernel.
	   Once in the real kernel it is not safe anymore to jump
	   back to the decompressor code via exceptions.

	2. Replace open-coded hlt loops with proper calls to
	   sev_es_terminate().

Please review.

Thanks,

	Joerg

Joerg Roedel (7):
  x86/boot/compressed/64: Cleanup exception handling before booting
    kernel
  x86/boot/compressed/64: Reload CS in startup_32
  x86/boot/compressed/64: Setup IDT in startup_32 boot path
  x86/boot/compressed/64: Add 32-bit boot #VC handler
  x86/boot/compressed/64: Add CPUID sanity check to 32-bit boot-path
  x86/boot/compressed/64: Check SEV encryption in 32-bit boot-path
  x86/sev-es: Replace open-coded hlt-loops with sev_es_terminate()

 arch/x86/boot/compressed/head_64.S     | 168 ++++++++++++++++++++++++-
 arch/x86/boot/compressed/idt_64.c      |  14 +++
 arch/x86/boot/compressed/mem_encrypt.S | 114 ++++++++++++++++-
 arch/x86/boot/compressed/misc.c        |   7 +-
 arch/x86/boot/compressed/misc.h        |   6 +
 arch/x86/boot/compressed/sev-es.c      |  12 +-
 arch/x86/kernel/sev-es-shared.c        |  10 +-
 7 files changed, 307 insertions(+), 24 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/5] CSS Mesurement Block
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Wed Feb 10 13:20:09 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12080851
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 4D47EC433DB
	for <kvm@archiver.kernel.org>; Wed, 10 Feb 2021 13:21:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F7FC64E0D
	for <kvm@archiver.kernel.org>; Wed, 10 Feb 2021 13:21:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231345AbhBJNVm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Feb 2021 08:21:42 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:19696 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231569AbhBJNVN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 10 Feb 2021 08:21:13 -0500
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11AD3mbY036043;
        Wed, 10 Feb 2021 08:20:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=mYikVEhh903OGim8+L+O1oJur66x4sXVBL9fgpSjVyE=;
 b=j9WB20GbqQ48KOzLeRD0SRf7F4HlgQCWFqESCh95hzc7QkgPn2Uwb/hI/mjFpwBIRbi9
 8dXIhYdcAfdHmQWaQg2veLXFv1Za/6nf+soXfEHBcWmw1aTE5w8E6Tj8dwSpQPkYzbGN
 GMpIWOPGvg4wRz20zVP3GtfEiMTnEr0xkUzTB4bc9AZAZUfx0+oRsgHfAcZh+6oOVwa3
 hGkcAHnE/98+o6mLQsVsH/WCPswKf8U2tbitNvo972yRHZPAOCqsV0Kubyy7cIcL91I0
 TcdH47xnEofEPPr5sd1mEaG3poNFUP5mjKeHFmXzYr4330jIBfVSAGKQDbA4y36n4jul 6g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36mfejsqm2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Feb 2021 08:20:21 -0500
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11AD46LM037712;
        Wed, 10 Feb 2021 08:20:20 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36mfejsqk0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Feb 2021 08:20:20 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11ADH7MU012089;
        Wed, 10 Feb 2021 13:20:18 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma06ams.nl.ibm.com with ESMTP id 36j94wm1uu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 10 Feb 2021 13:20:18 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11ADKF5n52560354
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 10 Feb 2021 13:20:15 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 90E054C04E;
        Wed, 10 Feb 2021 13:20:15 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 33B694C044;
        Wed, 10 Feb 2021 13:20:15 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.174.85])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 10 Feb 2021 13:20:15 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 0/5] CSS Mesurement Block
Date: Wed, 10 Feb 2021 14:20:09 +0100
Message-Id: <1612963214-30397-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.737
 definitions=2021-02-10_05:2021-02-10,2021-02-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 clxscore=1015
 priorityscore=1501 bulkscore=0 mlxscore=0 impostorscore=0
 lowpriorityscore=0 phishscore=0 adultscore=0 suspectscore=0
 mlxlogscore=999 malwarescore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2102100126
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We tests the update of the Mesurement Block (MB) format 0
and format 1 using a serie of senseid requests.

The MB format 1 is only provided if the Extended mesurement Block
feature is available.
This feature is exposed by the CSS characteristics general features
stored by the Store Channel Subsystem Characteristics CHSC command,
consequently, we implement the CHSC instruction call and the SCSC CHSC
command.

In order to ease the writing of new tests using:
- interrupt
- enablement of a subchannel
- multiple I/O on a subchannel

We do the following simplifications:
- we create a CSS initialization routine
- we register the I/O interrupt handler on CSS initialization
- we do not enable or disable a subchannel in the senseid test,
  assuming this test is done after the enable test, this allows
  to create traffic using the SSCH used by senseid.
- we add a css_enabled() function to test if a subchannel is enabled.

Regards,
Pierre

Pierre Morel (5):
  s390x: css: Store CSS Characteristics
  s390x: css: simplifications of the tests
  s390x: css: implementing Set CHannel Monitor
  s390x: css: testing measurement block format 0
  s390x: css: testing measurement block format 1

 lib/s390x/css.h     | 117 ++++++++++++++++++++++-
 lib/s390x/css_lib.c | 223 +++++++++++++++++++++++++++++++++++++++++---
 s390x/css.c         | 186 ++++++++++++++++++++++++++++++++----
 3 files changed, 493 insertions(+), 33 deletions(-)
```
#### [PATCH 0/5]  KVM: x86/xen: Selftest fixes and a cleanup
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Wed Feb 10 18:26:04 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12081585
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3DCA9C433E0
	for <kvm@archiver.kernel.org>; Wed, 10 Feb 2021 18:29:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 10F7E64E0B
	for <kvm@archiver.kernel.org>; Wed, 10 Feb 2021 18:29:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233998AbhBJS3C (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 10 Feb 2021 13:29:02 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36192 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234142AbhBJS0z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 10 Feb 2021 13:26:55 -0500
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 06931C06178C
        for <kvm@vger.kernel.org>; Wed, 10 Feb 2021 10:26:15 -0800 (PST)
Received: by mail-qt1-x84a.google.com with SMTP id t5so2264949qti.5
        for <kvm@vger.kernel.org>; Wed, 10 Feb 2021 10:26:14 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=q+sIuVQJ6KcFkT5QFvyQWYzcdJ2lh3h/xyy/iLNsRYQ=;
        b=di8qVqiUnwbZq+drUX5B4zxZ1i2Q93eORZ9i+xxj1lYzZzLPlYGgYljubSs5OY3tFS
         mYD3hl33pPNMC+maQ5KN8CfmbqqmoOQYr0E/fFKZip9vd/CscLrYAvff2xvLEnyk0loB
         gNG1WQhQKEBKiOuRQsD9xqjogNHt61/i5hpz573lRwpLmGRmDBbLQPcoRkZJl9Kr7k5j
         nofOLI/uzrLCKrM8gP6jpHO0hnJ6+OjFb9N4T+r2vsAkErDblZIns4dJ3fPOA8da1WvX
         B1RsREoFbnqXDGw0hRBspd9eIXSNxDO0rYqXl3HpEaPV2PYejQ65w2po74pXslOOvlNl
         l3rA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=q+sIuVQJ6KcFkT5QFvyQWYzcdJ2lh3h/xyy/iLNsRYQ=;
        b=kKb7rf6Zk4Sgdg0k3FMvGCshKxvzN94EnNA4pKXnQFD3Cwm8CrO+9/cNhJNE7SjfPs
         z8OR2G7FyVN3C1qSKDj5uPsbmsbdI2Wu05gJNq7TvbNxX2Es2VIeJAfL7xwkinrkeX4V
         gxOzxt4jduWLsPZwFAaJT6fgbi0G+J82n5xcZyWpjUF9+ZLEjquo4zsV/df7/MWkp+sE
         QVP1LHOL9DXePUIHl22EyjXV3IGPwDPUSTCvDwH/WpbE7spViRJvKwWPgEpC+3yfQ4J6
         WfrQPlqu5c03Sp0rs04P/GC5JJB9TniKwcWRkIrZEepxFBAredXf7Rp/GfWoL0RhNJaD
         Riag==
X-Gm-Message-State: AOAM5338GnGsx0hAsMGif6a97Qhn+EXxwU/c1hyjh0Q2UwWnHMrL4uak
        T7eFL28B0J6WiCtSbtrQ2XtNiaLP3ew=
X-Google-Smtp-Source: 
 ABdhPJwWYtIBmeRMFFyrmnZp1CUY6dAfZLe3CPlBHlBdXORhWl9XfX/dsq8lvN1lhUh4QsJWeuA70xZbYLA=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:11fc:33d:bf1:4cb8])
 (user=seanjc job=sendgmr) by 2002:a0c:fdec:: with SMTP id
 m12mr3978002qvu.11.1612981574160;
 Wed, 10 Feb 2021 10:26:14 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Wed, 10 Feb 2021 10:26:04 -0800
Message-Id: <20210210182609.435200-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH 0/5]  KVM: x86/xen: Selftest fixes and a cleanup
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, David Woodhouse <dwmw@amazon.co.uk>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix a '40' vs '0x40' bug in the new Xen shinfo selftest, and clean up some
other oddities that made root causing the problem far more painful than it
needed to be.

Note, Paolo already queued a patch from Vitaly that adds the tests to
.gitignore[*], i.e. patch 01 can likely be dropped.  I included it here
for completeness.

[*] https://lkml.kernel.org/r/20210129161821.74635-1-vkuznets@redhat.com

Sean Christopherson (5):
  KVM: selftests: Ignore recently added Xen tests' build output
  KVM: selftests: Fix size of memslots created by Xen tests
  KVM: selftests: Fix hex vs. decimal snafu in Xen test
  KVM: sefltests: Don't bother mapping GVA for Xen shinfo test
  KVM: x86/xen: Explicitly pad struct compat_vcpu_info to 64 bytes

 arch/x86/kvm/xen.h                                   | 11 ++++++-----
 tools/testing/selftests/kvm/.gitignore               |  2 ++
 tools/testing/selftests/kvm/x86_64/xen_shinfo_test.c | 12 +++++-------
 tools/testing/selftests/kvm/x86_64/xen_vmcall_test.c |  3 +--
 4 files changed, 14 insertions(+), 14 deletions(-)
```
