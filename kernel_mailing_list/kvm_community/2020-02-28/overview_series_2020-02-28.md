#### [PATCH] KVM: allow disabling -Werror
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11411937
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 462B313A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 09:56:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 26671246AA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 09:56:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="AjGi9oKX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726778AbgB1J4I (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Feb 2020 04:56:08 -0500
Received: from mail-wm1-f66.google.com ([209.85.128.66]:50758 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726536AbgB1J4I (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Feb 2020 04:56:08 -0500
Received: by mail-wm1-f66.google.com with SMTP id a5so2543118wmb.0;
        Fri, 28 Feb 2020 01:56:07 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=zKGXK9SAs0Ecacz7HFCrkRE8+zApqJ5J3A2oMtz1fqU=;
        b=AjGi9oKXYefDfw5yebzDzw4qIkTe3S/U2jkj5sanwnGoPZKDcclQeuZ+7tC2KDV73Z
         x2M0soNYFSdHwsQNzRbtFt+ukkVKkkqKGo/wxqaze688veIAJLqslmFLLwZ6nxm7IjVZ
         w34vMJLgBC5R9ESLI35r8CT2b7X5PfnJyq1L7G1VZvgN7tXI6sLOaK5aayN/mfKZyVoy
         XHCNIHcBfMHqbqUISLmm0aBO/e80qaEKZvyuOuezzy2KmdVhcKPkj/IRVRP2t+5ClFV6
         PX7vqfHU2pI6SWmbrbAXQRp6fYmcTtQb0USv32sArRPGt/S9BVPyve4GpULxers20YS/
         P1cw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=zKGXK9SAs0Ecacz7HFCrkRE8+zApqJ5J3A2oMtz1fqU=;
        b=s+GGq6qVcSCY/Q55VxrRWarLJ+ZvzQWcDENL1x0tJvgaK5SfAZc+OfzFqy0yNG9RYm
         ACqejSY3jO0+2a2LijvUyxpwaMQP3mI/ggZVUxmp4s8eM6yIlsFcXqMwwXgJG2/i16TF
         lZzwCGdzZupp/yBvKE21WK3mimde1CTFXAzrwhWPbd7BHXsNFA0MLeXJ5N7A4HjiQgbL
         4sDMGZcLPGTeyDTj+zo3Yw9iJPPVbkaAzsACpFi/X6CelDyq5M9E5XxdbKr1vpaHv8YX
         ZlzzX8bLNUz3rYIMCtDm1jkGaGZISc6eiKZk4vSKh4tyVW/3sznD6h6eeeOO/kG56Aee
         aW+w==
X-Gm-Message-State: APjAAAV4lJZ+tRAeQzj/4ZFZsBPLN4pCmY8OpGras2N1AkW7NEX9pR30
        nAfXDwq2+KtGOHmwxrCsWH/XnE/A
X-Google-Smtp-Source: 
 APXvYqxwIh2KTYZXXyArYgBQzV4t5qeE+7xhHbRZR6CI30Br31D4xn9E18Gc7TX0/GIk1PDqBEnUIQ==
X-Received: by 2002:a7b:c119:: with SMTP id w25mr4150009wmi.116.1582883766312;
        Fri, 28 Feb 2020 01:56:06 -0800 (PST)
Received: from 640k.localdomain ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 t3sm11664565wrx.38.2020.02.28.01.56.05
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 28 Feb 2020 01:56:05 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: hch@lst.de
Subject: [PATCH] KVM: allow disabling -Werror
Date: Fri, 28 Feb 2020 10:56:03 +0100
Message-Id: <1582883764-26125-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Restrict -Werror to well-tested configurations and allow disabling it
via Kconfig.

Reported-by: Christoph Hellwig <hch@lst.de>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/Kconfig  | 13 +++++++++++++
 arch/x86/kvm/Makefile |  2 +-
 2 files changed, 14 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: let declaration of kvm_get_running_vcpus match implementation
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11411829
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8E99314BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 08:49:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 774D124695
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 08:49:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726603AbgB1Itt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Feb 2020 03:49:49 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:63550 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726005AbgB1Itt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 28 Feb 2020 03:49:49 -0500
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01S8nici061012
        for <kvm@vger.kernel.org>; Fri, 28 Feb 2020 03:49:47 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2yepy26cv9-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 28 Feb 2020 03:49:47 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Fri, 28 Feb 2020 08:49:46 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 28 Feb 2020 08:49:43 -0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01S8ngR219398664
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 28 Feb 2020 08:49:42 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6DB99A4051;
        Fri, 28 Feb 2020 08:49:42 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5C9D2A4040;
        Fri, 28 Feb 2020 08:49:42 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Fri, 28 Feb 2020 08:49:42 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 1B3DAE01EF; Fri, 28 Feb 2020 09:49:42 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, arc Zyngier <maz@kernel.org>
Subject: [PATCH] KVM: let declaration of kvm_get_running_vcpus match
 implementation
Date: Fri, 28 Feb 2020 09:49:41 +0100
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20022808-0028-0000-0000-000003DECAA7
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20022808-0029-0000-0000-000024A3ECA5
Message-Id: <20200228084941.9362-1-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-28_02:2020-02-26,2020-02-28 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 suspectscore=0 mlxscore=0 spamscore=0 mlxlogscore=863 bulkscore=0
 malwarescore=0 priorityscore=1501 clxscore=1015 adultscore=0 phishscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002280073
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Sparse notices that declaration and implementation do not match:
arch/s390/kvm/../../../virt/kvm/kvm_main.c:4435:17: warning: incorrect type in return expression (different address spaces)
arch/s390/kvm/../../../virt/kvm/kvm_main.c:4435:17:    expected struct kvm_vcpu [noderef] <asn:3> **
arch/s390/kvm/../../../virt/kvm/kvm_main.c:4435:17:    got struct kvm_vcpu *[noderef] <asn:3> *

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 include/linux/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: nVMX: allow compiling with W=1MIME-Version: 1.0
##### From: "Valdis =?utf-8?q?Kl=C4=93tnieks?= " <valdis.kletnieks@vt.edu>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: =?utf-8?q?Valdis_Kl=C4=93tnieks?=
 <Valdis.Kletnieks@vt.edu>
X-Patchwork-Id: 11411445
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DEEED924
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 03:03:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C7CE0246A1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 03:03:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730619AbgB1DDT convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 22:03:19 -0500
Received: from outbound.smtp.vt.edu ([198.82.183.121]:59664 "EHLO
        omr2.cc.vt.edu" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730569AbgB1DDS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Feb 2020 22:03:18 -0500
X-Greylist: delayed 798 seconds by postgrey-1.27 at vger.kernel.org;
 Thu, 27 Feb 2020 22:03:18 EST
Received: from mr5.cc.vt.edu (mail.ipv6.vt.edu
 [IPv6:2607:b400:92:9:0:9d:8fcb:4116])
        by omr2.cc.vt.edu (8.14.4/8.14.4) with ESMTP id 01S2o00C019644
        for <kvm@vger.kernel.org>; Thu, 27 Feb 2020 21:50:00 -0500
Received: from mail-qv1-f72.google.com (mail-qv1-f72.google.com
 [209.85.219.72])
        by mr5.cc.vt.edu (8.14.7/8.14.7) with ESMTP id 01S2ntAd012834
        for <kvm@vger.kernel.org>; Thu, 27 Feb 2020 21:50:00 -0500
Received: by mail-qv1-f72.google.com with SMTP id cn2so1444552qvb.1
        for <kvm@vger.kernel.org>; Thu, 27 Feb 2020 18:50:00 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:mime-version
         :content-id:content-transfer-encoding:date:message-id;
        bh=TMxAIoujXzqS3798HgNWfd0wXc3IAjXqWU595ApRFSw=;
        b=oxOnJz/hnvKBj0svZUOy8bOCo+sP8YFpYZMa4+TnKrNvd8EyA+QUT24gNrMD147q7l
         XClrwXtHitljc6wq1jTLcD7ekXrQevcpu/K1k+Pn6cDW9Vz9t1Qho3HKu9hIhDpbn+db
         IqfrIO9GfMcjF/opFQB1H9nqtFgr0PHwKYi4fbRfkV0ZEkQGUJFJOS5shfb54Ph9bLT3
         RmFKl60QIiuBSl5DSmnfcezeHeMgzyibgSC87pHLpbQYj2cqg0KjFjB/CEI0p2oM0xbM
         xHknkzB7nWH3a1kxpJonlMJ4L8XpVuaF6dZh7AcYCpxP9vanjLLw9TDHXFlUtKuP4kjl
         y2hQ==
X-Gm-Message-State: APjAAAWOd8m21ualukE1YQLBv5F3XrYARGx71rVwRkljOO5qGdQo0BZ1
        GesJJsnGIEU3MWpAtqgXM1rPFLLD7sgs3kApbAYXLtFZIl9PLzobtY+BneI0FYisJ8pHP08HUkC
        QNQTvptkYpB77A2V3juFHpVU=
X-Received: by 2002:a37:6111:: with SMTP id v17mr2544755qkb.210.1582858195018;
        Thu, 27 Feb 2020 18:49:55 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqxqpvtFlPmXpm9FoxRteLLKVlXXhcaTG1YqTU72QLXMBBhjrUVYf45oDs0UAE5r0eZa9rO8Kg==
X-Received: by 2002:a37:6111:: with SMTP id v17mr2544735qkb.210.1582858194753;
        Thu, 27 Feb 2020 18:49:54 -0800 (PST)
Received: from turing-police ([2601:5c0:c001:c9e1::359])
        by smtp.gmail.com with ESMTPSA id
 t4sm4300738qkm.82.2020.02.27.18.49.53
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 27 Feb 2020 18:49:53 -0800 (PST)
From: "Valdis =?utf-8?q?Kl=C4=93tnieks?= " <valdis.kletnieks@vt.edu>
X-Google-Original-From: "Valdis =?utf-8?q?Kl=C4=93tnieks?= "
 <Valdis.Kletnieks@vt.edu>
X-Mailer: exmh version 2.9.0 11/07/2018 with nmh-1.7+dev
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>
cc: x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: nVMX: allow compiling with W=1
MIME-Version: 1.0
Content-ID: <263440.1582858192.1@turing-police>
Date: Thu, 27 Feb 2020 21:49:52 -0500
Message-ID: <263441.1582858192@turing-police>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Compile error with CONFIG_KVM_INTEL=y and W=1:

  CC      arch/x86/kvm/vmx/vmx.o
arch/x86/kvm/vmx/vmx.c:68:32: error: 'vmx_cpu_id' defined but not used [-Werror=unused-const-variable=]
   68 | static const struct x86_cpu_id vmx_cpu_id[] = {
      |                                ^~~~~~~~~~
cc1: all warnings being treated as errors

When building with =y, the MODULE_DEVICE_TABLE macro doesn't generate a
reference to the structure (or any code at all).  This makes W=1 compiles
unhappy.

Wrap both in a #ifdef to avoid the issue.

Signed-off-by: Valdis Kletnieks <valdis.kletnieks@vt.edu>

```
#### [PATCH] KVM: SVM: Inhibit APIC virtualization for X2APIC guestFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11411299
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4A73C14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 00:35:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 239D1246AA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 00:35:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="u1wSsBnw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730223AbgB1Af3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 19:35:29 -0500
Received: from mail-yw1-f73.google.com ([209.85.161.73]:41245 "EHLO
        mail-yw1-f73.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730034AbgB1Af2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Feb 2020 19:35:28 -0500
Received: by mail-yw1-f73.google.com with SMTP id q128so2368821ywb.8
        for <kvm@vger.kernel.org>; Thu, 27 Feb 2020 16:35:28 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=PuYSDpfkod6UnkA/hNIPxRv/jbAeDf/uATgjnhPNCyM=;
        b=u1wSsBnw/72eubi79/mmoedTR6kl05GWhw+696wERJlphxtg2+LkFgJXFDT7WREF2p
         Pj7a6uImQ/X/mYKAwhykXT9EeRPgZUqsywg0aF5xPhu8ASwqBjkxlb/dbOwzIZu7DAfL
         ncx8T57yI56nF+RnZHj+KUkHx2K2e1ebgefwR3FH4INR2bu50lWIDBmaunkZJhfKJdV3
         XiEwYW5D7/GwYiYPhWoM4UUFeS6gPmHrKJEY3FG9Vj/EBWAQHUpmwEIb+SVedmJtPDK6
         RBpIVI16N+zeDK+K2xysSvqIZrcREazXE/39uCGSVcEfigXpM8qK/CYIq6itqFC7EByH
         Fucg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=PuYSDpfkod6UnkA/hNIPxRv/jbAeDf/uATgjnhPNCyM=;
        b=kmPyH/eGKWtnxbReVmFZ3Xt03bPzhlal53IT/paRKTC8hXbsySQAfgl4N728bthUpn
         ApbTd3UBAa07607X2wpjUIfYDi5iN6GwOXk2jEunQCB6EIeHQUbHQSGNg4jafRoUxtso
         ZhMZYANONYt7h9c/lCR5QNrHQvfxQqcQfz3B9BBSeVe7LfZYyWm9FvzytrIUGfrtAwLa
         FLfdTkarxWbonOs8Q+uYTpGSTqVV5JxuPY1fzqeL8l/fgPP73iR0WEeMVWRdnI0jAAWh
         9WX5Py4eM3Ki/v81oQetTQfIohc+3oCj0uQss8g0hP+P1U0b4BPwRSEYTJw9IlGyjgr5
         Zp1Q==
X-Gm-Message-State: APjAAAXxvqBrC6dzur0k45Tl2riSKt8jNe6DnmyVjMATh/9CLhUo32Fd
        ZtUjtfOVQ//AvIhKlDcOifRfl83bGGcuaqh45Ih7g0sEllqubuSJDBn55Q3rZkcTPkso04PK3gI
        Znw0qCBxw6m36yc/8Evx5PBuAVGxGsEH8DXPgKDPSNKR8+BXsHcLU8kdOWQ==
X-Google-Smtp-Source: 
 APXvYqy3/ZmH1e9HDgkRt0Qni8tFP7I/6rx7aZgyWAkVXzPtrfhsDomW4QC0gGikzeW9/QD8rPQc1sEcHgM=
X-Received: by 2002:a81:23c2:: with SMTP id
 j185mr1995486ywj.465.1582850127714;
 Thu, 27 Feb 2020 16:35:27 -0800 (PST)
Date: Thu, 27 Feb 2020 16:35:23 -0800
Message-Id: <20200228003523.114071-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.1.481.gfbce0eb801-goog
Subject: [PATCH] KVM: SVM: Inhibit APIC virtualization for X2APIC guest
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Oliver Upton <oupton@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The AVIC does not support guest use of the x2APIC interface. Currently,
KVM simply chooses to squash the x2APIC feature in the guest's CPUID
If the AVIC is enabled. Doing so prevents KVM from running a guest
with greater than 255 vCPUs, as such a guest necessitates the use
of the x2APIC interface.

Instead, inhibit AVIC enablement on a per-VM basis whenever the x2APIC
feature is set in the guest's CPUID. Since this changes the behavior of
KVM as seen by userspace, add a module parameter, avic_per_vm, to opt-in
for the new behavior. If this parameter is set, report x2APIC as
available on KVM_GET_SUPPORTED_CPUID. Without opt-in, continue to
suppress x2APIC from the guest's CPUID.

Signed-off-by: Oliver Upton <oupton@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---

 Parent commit: a93236fcbe1d ("KVM: s390: rstify new ioctls in api.rst")

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/svm.c              | 19 ++++++++++++++++---
 2 files changed, 17 insertions(+), 3 deletions(-)

```
#### [PATCH kvm-unit-tests] pci: use uint32_t for unsigned long values
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11412037
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 63D901580
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 11:06:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 35D6B2469C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 11:06:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="toIkYrLR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726766AbgB1LGO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Feb 2020 06:06:14 -0500
Received: from mail-wm1-f66.google.com ([209.85.128.66]:35767 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726700AbgB1LGO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Feb 2020 06:06:14 -0500
Received: by mail-wm1-f66.google.com with SMTP id m3so2757422wmi.0
        for <kvm@vger.kernel.org>; Fri, 28 Feb 2020 03:06:12 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=UtzqvagjojyZWesumE++cd2W7FJYGFwxDxrHDY41x2o=;
        b=toIkYrLRBouPK6oizZ7y+SqqNA29vHgT6MhAa2aDvwcsXEr5pQp/AWIlSEiJ6epfBj
         N963yT+TeOcDcHCMwy80Wc5smfySnydA4RnYYv+07pG2oa87l7MTBvPyfFcfqlOtUsrE
         03fvRBPz8yvg8BrhKyTJlg49xi0WCZvN4rh8wrW4O+rixjeTBWj5wJMcS0DRNIcXFenT
         JbMhk31Dg/QDoY2on09xitIl1N5uaOWiUB8C7ebluSV2SZ8RRJXCvEwX0UmBzOTNpss0
         EezuC/9im2sAXaGH6vhBYvRJb0mBbjGcPloGPQOYjxLqEqF6htrhJwD6nDYVtotj2oKb
         FRzQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=UtzqvagjojyZWesumE++cd2W7FJYGFwxDxrHDY41x2o=;
        b=cjSEviPmXpMukA7CfeWOvX6ekV9t3agmyGy9wxH2t3RCvCIEBso0TTLQNFpl0AD1wX
         qBxwYcc/FLcmzFtmVDXyFvBQZ4IUS/1CWsi3El/klTe74eungASUSHUgLQbdy3QTV5Za
         1oI6AEnlxqGdMFunYpIHF5fe8qL08d1xIFWcdhKFRXVswgyVmsie3gVn2ki5/I1jXwSb
         TTDZFvggN8HVSO9/awizJiWqepnlyL9hbhLvOoptzJurjWJIQ4g4cS2Z+WmT2xEkiXti
         W28marNiVsusOuDW5hZ4tCD5HPjw+bmfPk5kOc0zx+bA2wI+UKr7AUDU2/H6j1x6m0TS
         cVtQ==
X-Gm-Message-State: APjAAAVLwAkVVDREUv4Vtbin5fCQv2PU638Oj+OWQRCVx9LQXN7otD05
        oEjrb8jV7UtB9DgP3bJELpOuHNwP
X-Google-Smtp-Source: 
 APXvYqwLkSHBtmJX/D1dgMqT8zMqrKCZTQrT7FKG8xKsTyQaqQVSklvstMEH8b7aE20tUFVHO6XoqQ==
X-Received: by 2002:a1c:7512:: with SMTP id o18mr4392669wmc.110.1582887971806;
        Fri, 28 Feb 2020 03:06:11 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 j14sm12526467wrn.32.2020.02.28.03.06.10
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 28 Feb 2020 03:06:11 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: morbo@google.com
Subject: [PATCH kvm-unit-tests] pci: use uint32_t for unsigned long values
Date: Fri, 28 Feb 2020 12:06:09 +0100
Message-Id: <1582887969-48490-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bill Wendling <morbo@google.com>

The "pci_bar_*" functions use 64-bit masks, but the results are assigned
to 32-bit variables; clang complains. Use signed masks that can be
sign-extended at will.

Reported-by: Bill Wendling <morbo@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 lib/linux/pci_regs.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: VMX: the "noclone" attribute is not needed
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11412041
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 238A614B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 11:16:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EEDE4246A8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 11:16:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="pfKgI+X1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725769AbgB1LQg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Feb 2020 06:16:36 -0500
Received: from mail-wm1-f66.google.com ([209.85.128.66]:37124 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725536AbgB1LQf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Feb 2020 06:16:35 -0500
Received: by mail-wm1-f66.google.com with SMTP id a141so2769311wme.2
        for <kvm@vger.kernel.org>; Fri, 28 Feb 2020 03:16:34 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=VAKXZjZM/wZQW2c0BGuG9pHq04sQRkDdMI+raG9ELUM=;
        b=pfKgI+X1E0Ej49Z+/23UQHdasEGzF8YDWtmUa6yXrWNHptH8SdlPGl3/bxogo41qao
         5SJElK3yInB2eKcYb/j0w94vgjbuhABzPG8hW6DL3HYE2D1+e6Fn1LO4jOakilTQ5Q6v
         8THJmvURUGKpHyY7UyFMBLAtHWOBe260DbPgyVRYsSQ+UzJoix43FANpB3qNmqen8JPt
         llwPE1x4prI6rh+por4o0vBhUFwE/3QMUtdTyNX/VKMpvNhDhtaFY/4LnsJWG9o1TEtk
         OQOM9xJjpCqtOb/HvDt5YIPNCkpRq4cxNJ2wdnJomzfnm4O3W7zu9Zfnq61pz1c0Ix+T
         d8oQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=VAKXZjZM/wZQW2c0BGuG9pHq04sQRkDdMI+raG9ELUM=;
        b=AmYB5wF2+9hSwXBslBqG0n3hJ9Y+EXQApsuKe87MX3YE9UDXViWAWFsR2ZgH9F1n6Q
         p61pEVtDZ/h153ZScd0MKqe7rz8lL3CzaehhOae3KjvwjAHx6TCnv912j2rDhd544mI+
         P/DfUP1F9CnFGQ6F39pq/mB1iGOq40qmu2d6D6OB1cG3sDWncqceqOAP0eQwbeYzgUbe
         pGVuNgIZ3xFUYXt0dem2IAPqWEA+IRxqgBoa6bpnPU/G4MFklUz2duh4nGbSlU5MoXaL
         SZk1Z9h+bzqOuVWVS/nk1Ktgl1ytBNAn+IKhzRWNYX7mQ62mr+EWl7Mpmqnp/PFieHkt
         oTCw==
X-Gm-Message-State: APjAAAVBq5O0VVZFTmQAU7MNeoYqeW/que/LLa1ralLUyoRr/ZBbcgaE
        kKuk0pCsT3W3elrSnpk6ydo/ONCl
X-Google-Smtp-Source: 
 APXvYqzAtJacrRI3km5UGtXuDc+eVJv6TvBBzUqc8W2oKlLVPt8p1O010XmG+KhWdNPR6ZXXmomBhQ==
X-Received: by 2002:a7b:c4cc:: with SMTP id g12mr4743922wmk.68.1582888593596;
        Fri, 28 Feb 2020 03:16:33 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 61sm12041380wrf.65.2020.02.28.03.16.32
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 28 Feb 2020 03:16:33 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: morbo@google.com
Subject: [PATCH kvm-unit-tests] x86: VMX: the "noclone" attribute is not
 needed
Date: Fri, 28 Feb 2020 12:16:31 +0100
Message-Id: <1582888591-51441-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Don't use the "noclone" attribute as it's not needed.
Also, clang does not support it.

Reported-by: Bill Wendling <morbo@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/vmx_tests.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: avoid useless copy of cpufreq policy
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11411935
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 42EBA1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 09:56:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 228DC246AA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 09:56:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="U8YNLw1B"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726974AbgB1J4J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Feb 2020 04:56:09 -0500
Received: from mail-wm1-f67.google.com ([209.85.128.67]:54540 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726563AbgB1J4J (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Feb 2020 04:56:09 -0500
Received: by mail-wm1-f67.google.com with SMTP id z12so2508551wmi.4;
        Fri, 28 Feb 2020 01:56:08 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=hgVcmR7sn/hoLD5sm/7USC3YHt4zWyH2PCKORbufRkw=;
        b=U8YNLw1BklkbHKFSmFrBZRonGw1bCU07mI+9f3gnHLLb9DGHlDa/hp53mIK0w3l2KI
         OItOYdNh0Fv7TFRXvO1EbJzuxEZ9itI7ofYSEKcR3AL1XM9zFH5IZZhED2s8gNmy6+zP
         6pXlNm66fIa7wwaj8qx2UEpO1QOBSisTB9ptYn5Ln1ZwNLOYaaeTX/NnoYOQGX+M8ZR+
         k7M4wGxBMdn5CdJVL2ohqqH8zDezNBpBYhEUC5efPD79VCS/ZmetxmOnRENOS9a7RNn4
         2qhSjjHWLS/efKV8+kyy6II9yx5ZbfTlAHEVW2k0ryZwi2OF8NTHo7tUKUcyytcpSf0u
         K1pg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=hgVcmR7sn/hoLD5sm/7USC3YHt4zWyH2PCKORbufRkw=;
        b=KpKTroTMccisfAsRXsE5X2jkJjlGcIVEIKMkm57hqJpOY10dYnl8kE8FEgt0V7EXKk
         JcHmvlnTWzXbOSaKzk+5OjShb5wi870ajq0TeKzZwa1i9ZJzb5aI6TJxqTUaeMwCCb1a
         gouVsCLftUZCdAvfWiehSryMysghij/tFBv9SOTIQb29SXNcwMVqrY1lFmINcU6XWfad
         6IlUrFNDj6c4MO8bGNeU6yH9cPeKGcRoFFFGqncd/TSI1rK/YaFBC/bIjpKHRhSQuYJc
         dj/Ltl03xQw2kKDhrQW1CkLU5K3ZcEova0ZLXaPtMO+3UZ2CWje6YwR7Hz1r7AF8jWIJ
         NczA==
X-Gm-Message-State: APjAAAUL2WevGLU3rVNHtt/fbOAPnNKQ6nxRtczSrvLPPysZ2kMDIQpn
        77hVKGyuqTTXMCC08VTXyrNTA6ou
X-Google-Smtp-Source: 
 APXvYqyod6TPpE2Xfif+ncMso0qZDZmpwPO/iPMNVJ9e8WNHlmsfErK+Ptw+fDMGTxu/+aMbntbeng==
X-Received: by 2002:a7b:c088:: with SMTP id r8mr4116774wmh.18.1582883767208;
        Fri, 28 Feb 2020 01:56:07 -0800 (PST)
Received: from 640k.localdomain ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 t3sm11664565wrx.38.2020.02.28.01.56.06
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 28 Feb 2020 01:56:06 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: hch@lst.de
Subject: [PATCH] KVM: x86: avoid useless copy of cpufreq policy
Date: Fri, 28 Feb 2020 10:56:04 +0100
Message-Id: <1582883764-26125-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

struct cpufreq_policy is quite big and it is not a good idea
to allocate one on the stack.  Just use cpufreq_cpu_get and
cpufreq_cpu_put which is even simpler.

Reported-by: Christoph Hellwig <hch@lst.de>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH 1/2] KVM: x86/mmu: Ignore guest CR3 on fast root switch for direct MMU
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11413395
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D7A3214B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 22:52:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C1D63246B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 22:52:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726783AbgB1Wwt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Feb 2020 17:52:49 -0500
Received: from mga01.intel.com ([192.55.52.88]:64083 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726277AbgB1Wwm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Feb 2020 17:52:42 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 28 Feb 2020 14:52:42 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,497,1574150400";
   d="scan'208";a="439387486"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga006.fm.intel.com with ESMTP; 28 Feb 2020 14:52:42 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/2] KVM: x86/mmu: Ignore guest CR3 on fast root switch for
 direct MMU
Date: Fri, 28 Feb 2020 14:52:39 -0800
Message-Id: <20200228225240.8646-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200228225240.8646-1-sean.j.christopherson@intel.com>
References: <20200228225240.8646-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Ignore the guest's CR3 when looking for a cached root for a direct MMU,
the guest's CR3 has no impact on the direct MMU's shadow pages (the
role check ensures compatibility with CR0.WP, etc...).

Zero out root_cr3 when allocating the direct roots to make it clear that
it's ignored.

Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu/mmu.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: Remove superfluous brackets in kvm_arch_dev_ioctl()
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11411557
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 189F292A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 05:42:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id EB54E246AA
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 05:42:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726440AbgB1Fml (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Feb 2020 00:42:41 -0500
Received: from mga14.intel.com ([192.55.52.115]:55983 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725911AbgB1Fml (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Feb 2020 00:42:41 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 27 Feb 2020 21:42:40 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,493,1574150400";
   d="scan'208";a="257009675"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.60])
  by orsmga002.jf.intel.com with ESMTP; 27 Feb 2020 21:42:37 -0800
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: Remove superfluous brackets in kvm_arch_dev_ioctl()
Date: Fri, 28 Feb 2020 13:25:27 +0800
Message-Id: <20200228052527.148384-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove unnecessary brackets from the case statements in
kvm_arch_dev_ioctl().

The brackets are visually confusing and error-prone, e.g., brackets of
case KVM_X86_GET_MCE_CAP_SUPPORTED accidently includes case
KVM_GET_MSR_FEATURE_INDEX_LIST and KVM_GET_MSRS.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/x86.c | 33 ++++++++++++++-------------------
 1 file changed, 14 insertions(+), 19 deletions(-)

```
#### [PATCH v2 1/2] KVM: SVM: Inhibit APIC virtualization for X2APIC guestFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11411831
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4DC3213A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 08:59:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 22E5E246A8
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 08:59:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Z0t18VO2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726151AbgB1I7W (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Feb 2020 03:59:22 -0500
Received: from mail-yw1-f74.google.com ([209.85.161.74]:52004 "EHLO
        mail-yw1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726005AbgB1I7V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Feb 2020 03:59:21 -0500
Received: by mail-yw1-f74.google.com with SMTP id a16so3725122ywa.18
        for <kvm@vger.kernel.org>; Fri, 28 Feb 2020 00:59:19 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=o3P8/n3NO+y1mFt3LRRLUFHUv02ncTruiTBoZVHd2vw=;
        b=Z0t18VO20mFKl+fhMEs/z9vvkN/3Aq7WvXT/M2GN2DxBtZW3HkmUlAQLkV3ViReM4+
         umoGHntd1Xq6NLIfe2J+xoho3TQp6fa7ihrvcALCX9jZWTgBiG6/QrKe4aj9pHxKkIl0
         2O4Og+Cbhg56SilJ5hHz6JoNOA3xx8vJIhDvTYcXmN5LlFbxUZ3j2dBg7kf7TUUD4Ejw
         lO6hc8yNg8xLSRAsrKvBhcFn5zrF+cruA0U0qU2UuUTUO/P+FR9iR+azXGleuM9bLyag
         w0MW/h7X8QfKbF0tQktyT6gBUNP7QLjl6SyXBIeBnE7p0lzntqiyBvHlzZOJit7+IITr
         P4BA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=o3P8/n3NO+y1mFt3LRRLUFHUv02ncTruiTBoZVHd2vw=;
        b=PZta6+6x4rpee5RekVS1AAqySIsDb4OxJSlxXxxTrF0nStc2SRxcS3Crq7BpFSQMHc
         dfJ9uB5ArKHFBifAcWrX42oGzmheZMkF+W0qVzvQfEYLKg6fRQa25fT55ye3sLTVJrrF
         OhTvbCYxGo+EX7UvsHZepTvC7ErpvhlwbHt72lipMnHprvQ/Ft9OJkFsWnrkSXOeEF/W
         8z1D0J0hkl3q5kFS9kMoCIBRG7tuIgRUWNtWm4Ysd5HXdBIkG/rqFxGJHAB0HgqsPyxt
         bfRQT4VoJ+iJ9GJy3JAD8SFHSVSC4fzCEt8jaJaBZ0GvrLSYj/dCRFN+RWJeEPOMo2iF
         fOyg==
X-Gm-Message-State: APjAAAXq0y0Klxc9VL90w+SOLWPFfEJot1fBQEDMchCG14ZlAlwPQOCE
        GB+a2b1mS6xZ5CUwaMJwV26mA/j6V+V4rACYskUXEDbpcXgGF0ZG8lLEis5d+pTajRlwcuppmI9
        1Nbxfq2Xa33nqSw0sgJvrIdqYxBE4J0UFBK0/KxdgEEbyz64mJkM3ZmPByQ==
X-Google-Smtp-Source: 
 APXvYqzP3RUnZIVjaQfNcil/MS/vuswAhJ2e1PJwwii/DjJffySzTP6e5msxU1Gn2LHXCVfh0j7NJfpTSdE=
X-Received: by 2002:a81:2e52:: with SMTP id u79mr3698169ywu.70.1582880359137;
 Fri, 28 Feb 2020 00:59:19 -0800 (PST)
Date: Fri, 28 Feb 2020 00:59:04 -0800
Message-Id: <20200228085905.22495-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.1.481.gfbce0eb801-goog
Subject: [PATCH v2 1/2] KVM: SVM: Inhibit APIC virtualization for X2APIC guest
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The AVIC does not support guest use of the x2APIC interface. Currently,
KVM simply chooses to squash the x2APIC feature in the guest's CPUID
If the AVIC is enabled. Doing so prevents KVM from running a guest
with greater than 255 vCPUs, as such a guest necessitates the use
of the x2APIC interface.

Instead, inhibit AVIC enablement on a per-VM basis whenever the x2APIC
feature is set in the guest's CPUID.

Signed-off-by: Oliver Upton <oupton@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---

 Parent commit: a93236fcbe1d ("KVM: s390: rstify new ioctls in api.rst")

 v1 => v2:
  - Adopt Paolo's suggestion to inhibit the AVIC by default rather than
    requiring opt-in
  - Drop now unnecessary module parameter

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/svm.c              | 15 +++++++++------
 2 files changed, 10 insertions(+), 6 deletions(-)

```
#### [PATCH v2] KVM: Remove unnecessary asm/kvm_host.h includes
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11413155
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4CA28924
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 18:30:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 23317246AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 18:30:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="h/Tmda5q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726589AbgB1Sa3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Feb 2020 13:30:29 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:41135 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725769AbgB1Sa3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 28 Feb 2020 13:30:29 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582914626;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=rPZKnbvXl6Mhr7grrs/+4ekdFdBwP31/FLAQ1ju56IY=;
        b=h/Tmda5q3/peW380w8BeJAPbtKHLx8VIFjZ5wgNPPmV248sg5TFt5RyanEjf0uC43dnvQA
        Gbvy1EiEbJXvEzqgoV3XGGJni4uvrdGC2ELJ59feKV6h3ybiK4hD9jIdGNLi0HfBb2igEz
        m+4yVRb7GB74TMpGBQ4vVlbsZngLlfM=
Received: from mail-qk1-f197.google.com (mail-qk1-f197.google.com
 [209.85.222.197]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-230-8RujVEhTPkmh79ocRi3fBQ-1; Fri, 28 Feb 2020 13:30:22 -0500
X-MC-Unique: 8RujVEhTPkmh79ocRi3fBQ-1
Received: by mail-qk1-f197.google.com with SMTP id s18so3629566qkj.6
        for <kvm@vger.kernel.org>; Fri, 28 Feb 2020 10:30:22 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=rPZKnbvXl6Mhr7grrs/+4ekdFdBwP31/FLAQ1ju56IY=;
        b=oo/ewbsn4NlItjZwK0Eg1fCjXkc4uvkF3h95qW0QdPhuQtSC954NhxIkv+jZNv6bb2
         4fZDm61/dqyB9mq+Sn8Q41VSMtuwUNOvbm+u2pdEKZMYkS5XwLCiejA1xJTK2OrUXGCM
         Ad+ITp6pYRuanTCcvzIkW9whjDumyW/4NmXpMkqn7sF+5pEH9jbWkuGtQOYH7eRsh6h9
         UdzvJtiiujVPXb/oLpXThS5pq/JfLvU6FtBs1xm5xAAYAqed8BdCaNHJX2wf0yB8As6O
         rArkgQoTBnSmaIb+fDuoUpwa4rFWYwhRn++x/Hzs6ucwfBUv+xoY08PYKGrfCon4vuc6
         PfVw==
X-Gm-Message-State: APjAAAXi8NgMRL86zwuyPKgACq6Uh/zHX/J8yXu+EPtQkdO++vhJTc2d
        ZBB8DLnHvfQQFDDFHia2inPsZ+Txd5F2qNrP/ZYXGKZz1e+S9zeHcjwZLOXyuLWZTC/Jz8ZxWnh
        UikwNArCGEBsR
X-Received: by 2002:ae9:eb0f:: with SMTP id b15mr5438627qkg.421.1582914622270;
        Fri, 28 Feb 2020 10:30:22 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwNyvKB2WECiHOFTVaTrF27wgcONWYIfPI4oSy+jms0mTZ7zXf5CfKiXZf4wy9iHDS6DFfaUQ==
X-Received: by 2002:ae9:eb0f:: with SMTP id b15mr5438596qkg.421.1582914621990;
        Fri, 28 Feb 2020 10:30:21 -0800 (PST)
Received: from xz-x1.redhat.com ([2607:9880:19c0:32::2])
        by smtp.gmail.com with ESMTPSA id
 k4sm5331572qtj.74.2020.02.28.10.30.20
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 28 Feb 2020 10:30:21 -0800 (PST)
From: Peter Xu <peterx@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com, jianjay.zhou@huawei.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v2] KVM: Remove unnecessary asm/kvm_host.h includes
Date: Fri, 28 Feb 2020 13:30:20 -0500
Message-Id: <20200228183020.398692-1-peterx@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Remove includes of asm/kvm_host.h from files that already include
linux/kvm_host.h to make it more obvious that there is no ordering issue
between the two headers.  linux/kvm_host.h includes asm/kvm_host.h to
pick up architecture specific settings, and this will never change, i.e.
including asm/kvm_host.h after linux/kvm_host.h may seem problematic,
but in practice is simply redundant.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
v2:
- s/unecessary/unnecessary/
- use Sean's suggested commit message
---
 arch/arm/kvm/coproc.c                | 1 -
 arch/arm64/kvm/fpsimd.c              | 1 -
 arch/arm64/kvm/guest.c               | 1 -
 arch/arm64/kvm/hyp/switch.c          | 1 -
 arch/arm64/kvm/sys_regs.c            | 1 -
 arch/arm64/kvm/sys_regs_generic_v8.c | 1 -
 arch/powerpc/kvm/book3s_64_vio.c     | 1 -
 arch/powerpc/kvm/book3s_64_vio_hv.c  | 1 -
 arch/powerpc/kvm/book3s_hv.c         | 1 -
 arch/powerpc/kvm/mpic.c              | 1 -
 arch/powerpc/kvm/powerpc.c           | 1 -
 arch/powerpc/kvm/timing.h            | 1 -
 arch/s390/kvm/intercept.c            | 1 -
 arch/x86/kvm/mmu/page_track.c        | 1 -
 virt/kvm/arm/psci.c                  | 1 -
 15 files changed, 15 deletions(-)

```
#### [PATCH v3] KVM: X86: Just one leader to trigger kvmclock sync request
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11411459
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 962C11395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 03:21:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6D12924695
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 03:21:09 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="XPn2INux"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730722AbgB1DVG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Feb 2020 22:21:06 -0500
Received: from mail-pl1-f196.google.com ([209.85.214.196]:42976 "EHLO
        mail-pl1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730569AbgB1DVG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Feb 2020 22:21:06 -0500
Received: by mail-pl1-f196.google.com with SMTP id u3so650584plr.9;
        Thu, 27 Feb 2020 19:21:05 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=rIXCm5M81d91xnd3Gd+yipbJxz4KGDW+jKNm3v5D9gk=;
        b=XPn2INuxdUtQeXgF2JFagwKBhjD8Xu8RwD86VmOBcImn8OPYR+JMgLyfejr2lHKd+/
         RTCuZ/a57sQcuv5TgR9DV9lQ4aYdZgWEPVyuPstCbC726RYaGUjhA5t/KlSYYOAIPPUb
         E8MKSpqmDjdpIhqi2iEU2OYzirWW1385QP2mFEIjkii/a5EKOniWHB+wkyHzNFaELsGL
         7eYRTXzVFf1612T8a75KvCicWXEn+ukYqvKUo7heiFg3YtpoAE/lNg3IvgKfCYNfglLz
         m8b678AX3VhxQlhH3IXXVkyG/sZUhV5IolwQRNX6r/BrrUNG5aoLm9U2JI8AsnhjKbe1
         v/Pw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=rIXCm5M81d91xnd3Gd+yipbJxz4KGDW+jKNm3v5D9gk=;
        b=lQ6mj8+2rzj7akAVwBd/F0gIymOrIXE2vCily71DFC3pQSEyJMuN7wH3WkK8ogBQNC
         nHAHVqvewlyMUnmO5KbwLVNvn6AKdkqsnNQg8t0lLS6pFaf5/+BBnVqZOjGSV50i9dJG
         Mtsv95WxakDqsXFFnwceoyF/IkNttPSjywX1AUrf/YtbM0tGUW+jW/WsRMIZJ9CcMau3
         o4BmdEODSNjnyVwWdZAK0VPbmBDTJZthsFssIQAZ9D2ESqAmvfEriKWHHB3F3Uua02Iv
         /n1sKavh1iqSPdAxglgyMrM166yY4+fjgXVMHzxix+P8TyU8IHY78PsLnP0XORKU3u6+
         CV0g==
X-Gm-Message-State: APjAAAWzd/+uEFB3jSiNo6Xu+xFQhtiy43e4Bf0nNkETclOlN4MgMCgo
        2184pK8crL9xXgEgeXl8I4m5bP/szQvl8A==
X-Google-Smtp-Source: 
 APXvYqyRTgQvWLHeivT3wAVpwiccEkXlX8bq7fFjVmzw+54PY2Cu3W1F3m7+XFt7JuJPSrLQZCi7AA==
X-Received: by 2002:a17:902:8a8e:: with SMTP id
 p14mr2022551plo.28.1582860064936;
        Thu, 27 Feb 2020 19:21:04 -0800 (PST)
Received: from kernel.DHCP ([120.244.140.54])
        by smtp.googlemail.com with ESMTPSA id
 b6sm8854260pfg.17.2020.02.27.19.20.59
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Thu, 27 Feb 2020 19:21:04 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v3] KVM: X86: Just one leader to trigger kvmclock sync request
Date: Fri, 28 Feb 2020 11:18:41 +0800
Message-Id: <1582859921-11932-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

In the progress of vCPUs creation, it queues a kvmclock sync worker to the global
workqueue before each vCPU creation completes. The workqueue subsystem guarantees 
not to queue the already queued work, however, we can make the logic more clear by 
make just one leader to trigger this kvmclock sync request and save on cacheline 
boucing due to test_and_set_bit.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v2 -> v3:
 * update patch description
v1 -> v2:
 * check vcpu->vcpu_idx

 arch/x86/kvm/x86.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH] x86/kvm: Handle async page faults directly through do_page_fault()
##### From: Andy Lutomirski <luto@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andy Lutomirski <luto@kernel.org>
X-Patchwork-Id: 11413187
Return-Path: <SRS0=X0Od=4Q=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AF5A9924
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 18:43:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 857FE246AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 28 Feb 2020 18:43:02 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1582915382;
	bh=eAl5CYW0aDLQd2hTkXyJKqFnRf+gxtnaW7YBSBf6F3k=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=YjKvbbu8n2vCG19AyjSaTJsmmZL2xYl8gy8v2y/bTJrb+rCo3owmW5AOFdQZjrUrV
	 bGfjTwm6zFYHFZaj126jjAjusgUn4jWHTBEcBocYO25it8c0W+Nsxqf5DLzgJiN7Ss
	 5K5MY++l6SY2Ho8QmXRp6vR6vkBzmMHWZt709Vi4=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726857AbgB1Sm6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 28 Feb 2020 13:42:58 -0500
Received: from mail.kernel.org ([198.145.29.99]:40474 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725730AbgB1Sm6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 28 Feb 2020 13:42:58 -0500
Received: from localhost (c-67-180-165-146.hsd1.ca.comcast.net
 [67.180.165.146])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id BBCE924677;
        Fri, 28 Feb 2020 18:42:56 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1582915376;
        bh=eAl5CYW0aDLQd2hTkXyJKqFnRf+gxtnaW7YBSBf6F3k=;
        h=From:To:Cc:Subject:Date:From;
        b=pCihTVHhkIKLnGn/N6n/O0W/d3KcUxDOoL7RyyzM47k0sjhzpj55zBfjR8tDe5SD2
         a/q10QdaVZgewaEVMYNpAcVi9W8gm2tbbbIDapgKri0TA53DZAZ09W6+7xC8/ooXKr
         wMQ6kXFd1M/jZt4IA3FnyT48FHubHcfvvDewbwhg=
From: Andy Lutomirski <luto@kernel.org>
To: LKML <linux-kernel@vger.kernel.org>, x86@kernel.org,
        kvm list <kvm@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Radim Krcmar <rkrcmar@redhat.com>
Cc: Andy Lutomirski <luto@kernel.org>
Subject: [PATCH] x86/kvm: Handle async page faults directly through
 do_page_fault()
Date: Fri, 28 Feb 2020 10:42:48 -0800
Message-Id: 
 <6bf68d0facc36553324c38ec798b0feebf6742b7.1582915284.git.luto@kernel.org>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM overloads #PF to indicate two types of not-actually-page-fault
events.  Right now, the KVM guest code intercepts them by modifying
the IDT and hooking the #PF vector.  This makes the already fragile
fault code even harder to understand, and it also pollutes call
traces with async_page_fault and do_async_page_fault for normal page
faults.

Clean it up by moving the logic into do_page_fault() using a static
branch.  This gets rid of the platform trap_init override mechanism
completely.

Signed-off-by: Andy Lutomirski <luto@kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/entry/entry_64.S       |  4 ----
 arch/x86/include/asm/kvm_para.h | 17 +++++++++++++++-
 arch/x86/include/asm/x86_init.h |  2 --
 arch/x86/kernel/kvm.c           | 36 +++++++++++++++++++--------------
 arch/x86/kernel/traps.c         |  2 --
 arch/x86/kernel/x86_init.c      |  1 -
 arch/x86/mm/fault.c             | 20 ++++++++++++++++++
 7 files changed, 57 insertions(+), 25 deletions(-)

```
