#### [FYI PATCH 1/3] KVM: nVMX: Don't emulate instructions in guest mode
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11401413
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4E45417E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 18:56:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2E0FE218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 18:56:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="LPoqAQiy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727996AbgBXS4l (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Feb 2020 13:56:41 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:46132 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727483AbgBXS4l (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 24 Feb 2020 13:56:41 -0500
Received: by mail-wr1-f66.google.com with SMTP id g4so5330103wro.13;
        Mon, 24 Feb 2020 10:56:40 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=ikUxpzI8l8qLhpgwUreS4zCEikhxIlpjQqZTs40gy+Q=;
        b=LPoqAQiyQUYmQEjLUtNJRXXF95mlhD6culiLLXq2+V48pb7tcg8xVE1JVzOsCZzR3q
         6ZoTNMn44iYy8n99BLwbZLIGRbvu+pVbHnf8hlO4b9mcu7zTzZZVM6hOz/0Rs+ufMsaj
         7fJaejhn3uOoMLoMYoBVLiBJoOEXDSYLVvjBl5zWuepRBfYBVrupHMPgCOpv9NZ8rsBv
         1tclil5HeWMM/VS1O3l0vmAAfSFx8gqN2ctGN7zjIYbfwDxaALv7IZNtlEqqK/MghrWh
         Qc/GxcmQavOeD/r5R6LoQU//usivbBx/NShEm/Sbic64RkW19ObPjKT3VOvtxhMYpqqz
         foeA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=ikUxpzI8l8qLhpgwUreS4zCEikhxIlpjQqZTs40gy+Q=;
        b=kTnPfGda3SW5D6Hq7ZmydUHjW5G3MRkEbDK1Ludhqym2qG4IrPsi90moF4fy8juiV1
         fQNzD+gM9m19y2+cthMDk0FM9ZD1D0TlLf5DPW88PII7l0snTQ5tmUkC28SpZdGZLmZe
         MZDN3NWxkRARS5Y5s5Ov2JVeIU9H+xR6u9dE3xqcvyTGyTqcSNH9oz9dV9k+1eOyyFmu
         qbDzaSx8ToCDFcy2RzTFcCbOBExsqpHhgnVRBzAotVly3ZMXbA2meY6wdyPy699fdeh0
         Vxmg6uwLrgbY5/NnU0nDydcmJc1ZP+uZIFDkOVINVhIdhoVZqeEpl+9o/oKgzFga1xQC
         rE/w==
X-Gm-Message-State: APjAAAXS+cBPO5HWrFsMt1H8j3Qy1Id6NqJ7hz/hy7/KirPE9k/+eNTA
        rTFkIO2YmSesNQ1dkkF4XYjLJqi8
X-Google-Smtp-Source: 
 APXvYqzcRZQ6vWYKezVnQ0bBJdnNMViVoXcqthvKgokYnE68Ic9fZmFLOIM6SSm7tYQMGARVOgYmAA==
X-Received: by 2002:a5d:4acb:: with SMTP id
 y11mr39392176wrs.111.1582570599273;
        Mon, 24 Feb 2020 10:56:39 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 z8sm19900838wrv.74.2020.02.24.10.56.38
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 24 Feb 2020 10:56:38 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: oupton@google.com, stable@vger.kernel.org
Subject: [FYI PATCH 1/3] KVM: nVMX: Don't emulate instructions in guest mode
Date: Mon, 24 Feb 2020 19:56:34 +0100
Message-Id: <1582570596-45387-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1582570596-45387-1-git-send-email-pbonzini@redhat.com>
References: <1582570596-45387-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmx_check_intercept is not yet fully implemented. To avoid emulating
instructions disallowed by the L1 hypervisor, refuse to emulate
instructions by default.

Cc: stable@vger.kernel.org
[Made commit, added commit msg - Oliver]
Signed-off-by: Oliver Upton <oupton@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/1] KVM: s390: rstify new ioctls in api.rst
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11400141
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 24B47924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 10:16:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0C3502084E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 10:16:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727275AbgBXKQI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Feb 2020 05:16:08 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:22886 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727183AbgBXKQH (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 24 Feb 2020 05:16:07 -0500
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01OAEcss092132
        for <kvm@vger.kernel.org>; Mon, 24 Feb 2020 05:16:06 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2yb1ar9mh1-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 24 Feb 2020 05:16:06 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Mon, 24 Feb 2020 10:16:04 -0000
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 24 Feb 2020 10:16:01 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01OAG0Po43647394
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 24 Feb 2020 10:16:00 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 344E452052;
        Mon, 24 Feb 2020 10:16:00 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTPS id 218B45204F;
        Mon, 24 Feb 2020 10:16:00 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id D96C3E0320; Mon, 24 Feb 2020 11:15:59 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>
Subject: [PATCH 1/1] KVM: s390: rstify new ioctls in api.rst
Date: Mon, 24 Feb 2020 11:15:59 +0100
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20200224101559.27405-1-borntraeger@de.ibm.com>
References: <20200224101559.27405-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20022410-0008-0000-0000-00000355E089
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20022410-0009-0000-0000-00004A76F888
Message-Id: <20200224101559.27405-2-borntraeger@de.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-24_02:2020-02-21,2020-02-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 priorityscore=1501 mlxlogscore=636 malwarescore=0 mlxscore=0 adultscore=0
 phishscore=0 bulkscore=0 clxscore=1015 impostorscore=0 spamscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002240088
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We also need to rstify the new ioctls that we added in parallel to the
rstification of the kvm docs.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 Documentation/virt/kvm/api.rst | 33 ++++++++++++++++++---------------
 1 file changed, 18 insertions(+), 15 deletions(-)

```
#### [GIT PULL] KVM changes for Linux 5.6-rc4
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11401417
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9FA861871
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 18:57:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7ED8621744
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 18:57:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="ThSS+lG1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727730AbgBXS5x (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Feb 2020 13:57:53 -0500
Received: from mail-wm1-f66.google.com ([209.85.128.66]:39765 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727108AbgBXS5x (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 24 Feb 2020 13:57:53 -0500
Received: by mail-wm1-f66.google.com with SMTP id c84so430163wme.4;
        Mon, 24 Feb 2020 10:57:51 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=aQRhD9hViNOdfqkPRzFwHAM04jgTQv3FSxcn1Z2TBAs=;
        b=ThSS+lG1FnRduPHMNFueF2fpUzcUWyQB63bcTouvvVJWxUMYRapCmy1E2wZoXY+sP6
         6+ZtkFX+4eflwMBDBUD4ULb2iNtnvaASIjzFJMFM7+VCjNRJC5wSFtfhed3Yaqd12uJ7
         T3kaKUXcVSBu7pJcE/12OMpu5RHpzy7hxwNBgdAjTee1KsGAIjrf4XGBu4jFrhy39A/d
         TYdYnOZITlZEH66ZZeSk72PJWC9qPoXQ5pLnOAYMmmpZJf1p0ho3ndKBOQquHsuD88zA
         z645dLZIEjvHmHjL4Oz47jSpHN2EmBASD+33w1nB0evjJsOp9ys5SuS2fah5LO4+lZK+
         /9dQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=aQRhD9hViNOdfqkPRzFwHAM04jgTQv3FSxcn1Z2TBAs=;
        b=CQdTzlmxBor/+b3yaN0QJfF1+pS1d3y8XTCSOyQ38QAu9XDPas/MaGw+OY4rP+KdKc
         x3+yL6Phe9TfEnNT0lWv0HYNuwFRGFUW/mtWr4S2LEjpFoHaHGiMObvdQ6bVPo4XBDat
         HnQRt34h7LcvGyCh/e7VGqjdz5h/2PXbwqI35pkPt/62k8Bpau+o9uCGLGR7huOnaBza
         mi1DbT0nKEgxCkIvT7HSGppvzVADENJ9WWKP2Jlq//JlowE3n8NQqu25P0e3kcjNiIid
         b5ji2JxUV4NAVTJo2UfY4FEJVUW3Tsnxi/gVV897YnOLO8TcKMq9t/Fv8j3VpRU07mNy
         TqRw==
X-Gm-Message-State: APjAAAVYJ8SkRaQF2+GAdRHqkWXoZ4zUuNfaha3XhHEZsJEX/Hh3MCm6
        pSkh0IwTz2BVGtDyz6joR6AWSvf9
X-Google-Smtp-Source: 
 APXvYqwXtl93vM0GQoS/Inue+qM/b3QuF68VzbSt9SrrlANF/Xx786+GjGcyrQ6vVHF4Ij4wEx7x5A==
X-Received: by 2002:a1c:44d:: with SMTP id 74mr431615wme.53.1582570671045;
        Mon, 24 Feb 2020 10:57:51 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 a16sm20491965wrx.87.2020.02.24.10.57.50
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 24 Feb 2020 10:57:50 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.6-rc4
Date: Mon, 24 Feb 2020 19:57:49 +0100
Message-Id: <1582570669-45822-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 120881b9e888689cbdb90a1dd1689684d8bc95f3:

  docs: virt: guest-halt-polling.txt convert to ReST (2020-02-12 20:10:08 +0100)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to a93236fcbe1d0248461b29c0f87cb0b510c94e6f:

  KVM: s390: rstify new ioctls in api.rst (2020-02-24 19:28:40 +0100)

----------------------------------------------------------------
Bugfixes, including the fix for CVE-2020-2732 and a few
issues found by "make W=1".

----------------------------------------------------------------
Christian Borntraeger (1):
      KVM: s390: rstify new ioctls in api.rst

Li RongQing (1):
      KVM: fix error handling in svm_hardware_setup

Miaohe Lin (4):
      KVM: nVMX: Fix some obsolete comments and grammar error
      KVM: x86: don't notify userspace IOAPIC on edge-triggered interrupt EOI
      KVM: apic: avoid calculating pending eoi from an uninitialized val
      KVM: SVM: Fix potential memory leak in svm_cpu_init()

Oliver Upton (3):
      KVM: nVMX: Emulate MTF when performing instruction emulation
      KVM: nVMX: Refactor IO bitmap checks into helper function
      KVM: nVMX: Check IO instruction VM-exit conditions

Paolo Bonzini (4):
      KVM: x86: enable -Werror
      KVM: x86: fix missing prototypes
      KVM: x86: fix incorrect comparison in trace event
      KVM: nVMX: Don't emulate instructions in guest mode

Qian Cai (1):
      kvm/emulate: fix a -Werror=cast-function-type

Suravee Suthikulpanit (1):
      kvm: x86: svm: Fix NULL pointer dereference when AVIC not enabled

Vitaly Kuznetsov (2):
      KVM: nVMX: handle nested posted interrupts when apicv is disabled for L1
      KVM: nVMX: clear PIN_BASED_POSTED_INTR from nested pinbased_ctls only when apicv is globally disabled

Xiaoyao Li (1):
      KVM: VMX: Add VMX_FEATURE_USR_WAIT_PAUSE

wanpeng li (1):
      KVM: nVMX: Hold KVM's srcu lock when syncing vmcs12->shadow

 Documentation/virt/kvm/api.rst     |  33 +++++-----
 arch/x86/include/asm/kvm_emulate.h |  13 +++-
 arch/x86/include/asm/kvm_host.h    |   3 +-
 arch/x86/include/asm/vmx.h         |   2 +-
 arch/x86/include/asm/vmxfeatures.h |   1 +
 arch/x86/include/uapi/asm/kvm.h    |   1 +
 arch/x86/kvm/Makefile              |   1 +
 arch/x86/kvm/emulate.c             |  36 ++++------
 arch/x86/kvm/irq_comm.c            |   2 +-
 arch/x86/kvm/lapic.c               |   9 ++-
 arch/x86/kvm/mmutrace.h            |   2 +-
 arch/x86/kvm/svm.c                 |  65 ++++++++++---------
 arch/x86/kvm/vmx/capabilities.h    |   1 +
 arch/x86/kvm/vmx/nested.c          |  89 ++++++++++++++++++-------
 arch/x86/kvm/vmx/nested.h          |  10 ++-
 arch/x86/kvm/vmx/vmx.c             | 130 +++++++++++++++++++++++++++++++------
 arch/x86/kvm/vmx/vmx.h             |   3 +
 arch/x86/kvm/x86.c                 |   2 +
 include/linux/kvm_host.h           |   2 +
 19 files changed, 284 insertions(+), 121 deletions(-)
```
#### [PATCH] KVM: nVMX: Consolidate nested MTF checks to helper functionFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11401481
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 42E82138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 20:28:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1553A20CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 20:28:53 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="FK/RPxPL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727267AbgBXU2w (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Feb 2020 15:28:52 -0500
Received: from mail-pg1-f201.google.com ([209.85.215.201]:34871 "EHLO
        mail-pg1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726722AbgBXU2w (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 24 Feb 2020 15:28:52 -0500
Received: by mail-pg1-f201.google.com with SMTP id b25so5205331pgn.2
        for <kvm@vger.kernel.org>; Mon, 24 Feb 2020 12:28:50 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=7Fee0MJe75CVUNxUnX//8PMYb8v5cLgBeoeqeunSi1E=;
        b=FK/RPxPLKSX4XeteJoTIxSFPcOExcYrHvgIDSswypm3cFViRFGMTDjhCjEvqMWbO8l
         Ll2mEE7p11jz1HQE+JkReYGVvvKis5XlxJGLE5g5zCiLabZ83AucY7in813h5ySUyBM/
         A31XQejjUYNAeEMvR6/8RNXJw1wxY6T2KA0bd4QZoF+CaZgzYd3EfxLVgqGOP4W6uD4p
         c2uxRnCbvmHsjWyXhIQfKQnUmzNMJ9QWq1TI1hg9ajJHY54RyH8K3WmefbM50W0j0fcS
         QUAWk3hGYbdvUZfn5gAQRAJQE7RjVHJjQjiYa8JQLuaUuDW9F/lsEebts102z/OFsNCG
         01kg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=7Fee0MJe75CVUNxUnX//8PMYb8v5cLgBeoeqeunSi1E=;
        b=M1KMRpImJXnH1T4DxA1vI72bK9HDzdtsziI51iP3J/LuhAZ7A8ifhM30bfDSXJ//u0
         PEHfeQr59ABnztahLgBnBQqthC2dDZI7pCtdXe5AMM87Y22FX7xEQBpn6IhUUtafA1wJ
         T1JFco0TjRe2ZLX2vnFjtrKxhjmxOa2wfjI0uyGK0gbP7YZV6mJwkW231PERJszfrvjS
         HWJn4gVA1Rtc7eQiOQbSJSsc11Gzt1msgFVP46bhHklLjey9BR4lYu445Gj7ugryAspT
         OWY3jYAr3wc4/VSa5CDy0DlXo8947gebAZdD3sfl0Sa4MQg149Ng4p6FrRko9b+omsAq
         Lhog==
X-Gm-Message-State: APjAAAVlDh26UGqpKdJvmcdCqsOyCrX5AP+cXTtlcQTQEbRxn7Cur+Sh
        6fx4QJHbpQRaQOus6mN96T9+OBCkKD7XreS5Cj49C5wiUiF+0fPlRmquDPuVPphrqgWbUClosZy
        AU48o+TtaWaYbX36ZEA6JvBthFwqo+eQVBsIUlHMVqXFp824SG0ovWpQgNg==
X-Google-Smtp-Source: 
 APXvYqznFg0G2Ryxr2LBw29a8dzFYY15AHH4Op3ch4qh7QgD8dhynrPwBa+6vGk86OCjP41zTRhG65wiMCI=
X-Received: by 2002:a63:8c12:: with SMTP id
 m18mr54300231pgd.192.1582576129988;
 Mon, 24 Feb 2020 12:28:49 -0800 (PST)
Date: Mon, 24 Feb 2020 12:27:44 -0800
Message-Id: <20200224202744.221487-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [PATCH] KVM: nVMX: Consolidate nested MTF checks to helper function
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

commit 5ef8acbdd687 ("KVM: nVMX: Emulate MTF when performing
instruction emulation") introduced a helper to check the MTF
VM-execution control in vmcs12. Change pre-existing check in
nested_vmx_exit_reflected() to instead use the helper.

Signed-off-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v4 01/36] mm/gup/writeback: add callbacks for inaccessible pages
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11400287
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1B5EA1871
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 11:46:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 046F320CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 11:46:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727689AbgBXLqR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Feb 2020 06:46:17 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:17442 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727673AbgBXLqR (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 24 Feb 2020 06:46:17 -0500
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01OBclDL107748;
        Mon, 24 Feb 2020 06:46:13 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2yb18ukkg7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 24 Feb 2020 06:46:13 -0500
Received: from m0098404.ppops.net (m0098404.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01OBdEkn109251;
        Mon, 24 Feb 2020 06:46:12 -0500
Received: from ppma03wdc.us.ibm.com (ba.79.3fa9.ip4.static.sl-reverse.com
 [169.63.121.186])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2yb18ukkfm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 24 Feb 2020 06:46:12 -0500
Received: from pps.filterd (ppma03wdc.us.ibm.com [127.0.0.1])
        by ppma03wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01OBZA7U015270;
        Mon, 24 Feb 2020 11:41:11 GMT
Received: from b01cxnp22033.gho.pok.ibm.com (b01cxnp22033.gho.pok.ibm.com
 [9.57.198.23])
        by ppma03wdc.us.ibm.com with ESMTP id 2yaux6330y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 24 Feb 2020 11:41:11 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp22033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 01OBf9mH55116216
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 24 Feb 2020 11:41:09 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9E5DA28058;
        Mon, 24 Feb 2020 11:41:09 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 82CC22805A;
        Mon, 24 Feb 2020 11:41:09 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon, 24 Feb 2020 11:41:09 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        Andrew Morton <akpm@linux-foundation.org>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        Ulrich Weigand <Ulrich.Weigand@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Michael Mueller <mimu@linux.ibm.com>,
        Vasily Gorbik <gor@linux.ibm.com>,
        Andrea Arcangeli <aarcange@redhat.com>, linux-mm@kvack.org,
        Will Deacon <will@kernel.org>
Subject: [PATCH v4 01/36] mm/gup/writeback: add callbacks for inaccessible
 pages
Date: Mon, 24 Feb 2020 06:40:32 -0500
Message-Id: <20200224114107.4646-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200224114107.4646-1-borntraeger@de.ibm.com>
References: <20200224114107.4646-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-24_02:2020-02-21,2020-02-24 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 phishscore=0
 spamscore=0 suspectscore=2 bulkscore=0 malwarescore=0 mlxscore=0
 mlxlogscore=815 impostorscore=0 adultscore=0 lowpriorityscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002240099
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Claudio Imbrenda <imbrenda@linux.ibm.com>

With the introduction of protected KVM guests on s390 there is now a
concept of inaccessible pages. These pages need to be made accessible
before the host can access them.

While cpu accesses will trigger a fault that can be resolved, I/O
accesses will just fail.  We need to add a callback into architecture
code for places that will do I/O, namely when writeback is started or
when a page reference is taken.

This is not only to enable paging, file backing etc, it is also
necessary to protect the host against a malicious user space. For
example a bad QEMU could simply start direct I/O on such protected
memory.  We do not want userspace to be able to trigger I/O errors and
thus we the logic is "whenever somebody accesses that page (gup) or
doing I/O, make sure that this page can be accessed. When the guest
tries to access that page we will wait in the page fault handler for
writeback to have finished and for the page_ref to be the expected
value.

On s390x the function is not supposed to fail, so it is ok to use a
WARN_ON on failure. If we ever need some more finegrained handling
we can tackle this when we know the details.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Acked-by: Will Deacon <will@kernel.org>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 include/linux/gfp.h |  6 ++++++
 mm/gup.c            | 15 ++++++++++++---
 mm/page-writeback.c |  5 +++++
 3 files changed, 23 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: selftests: Fix unknown ucall command asserts
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11400895
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4904A14BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 16:10:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1E7F821556
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 16:10:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZCqwpGdR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728047AbgBXQKz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Feb 2020 11:10:55 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:36338 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728031AbgBXQKz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 24 Feb 2020 11:10:55 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582560653;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=GUN7E8uNuAW1Kbn7TsNWpzUqCroekYM2b6TqEf2CkXM=;
        b=ZCqwpGdRcdqis2MZENvwJP0EPozGXC9oFlAgtrdXMErSMeC2xV5UntP0vZBnfJASwBbEuz
        gCMmO5jiF65kADAq6W3OVav+h/j3JHlXKWonmOVRBWiGwrkZn4jMDhfQBf7KIrq3K7Nuwq
        +QI70QuPA3XKIdFhGorFuFNiPBNAgfc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-208-1rjv36JnOA-QYWqKQr30uA-1; Mon, 24 Feb 2020 11:10:52 -0500
X-MC-Unique: 1rjv36JnOA-QYWqKQr30uA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 484A2800D5B
        for <kvm@vger.kernel.org>; Mon, 24 Feb 2020 16:10:51 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 64E4A8B755;
        Mon, 24 Feb 2020 16:10:50 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH] KVM: selftests: Fix unknown ucall command asserts
Date: Mon, 24 Feb 2020 17:10:49 +0100
Message-Id: <20200224161049.18545-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The TEST_ASSERT in x86_64/platform_info_test.c would have print 'ucall'
instead of 'uc.cmd'. Also fix all uc.cmd format types.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/x86_64/cr4_cpuid_sync_test.c       | 2 +-
 tools/testing/selftests/kvm/x86_64/evmcs_test.c                | 2 +-
 tools/testing/selftests/kvm/x86_64/platform_info_test.c        | 3 +--
 tools/testing/selftests/kvm/x86_64/state_test.c                | 2 +-
 .../testing/selftests/kvm/x86_64/vmx_close_while_nested_test.c | 2 +-
 tools/testing/selftests/kvm/x86_64/vmx_dirty_log_test.c        | 2 +-
 tools/testing/selftests/kvm/x86_64/vmx_tsc_adjust_test.c       | 2 +-
 7 files changed, 7 insertions(+), 8 deletions(-)

```
#### [PATCH 1/2] kvm: vmx: Use basic exit reason to check if it's the specific VM EXIT
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11399179
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4C5B14BC
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 02:13:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 843582067D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 02:13:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727261AbgBXCNG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 23 Feb 2020 21:13:06 -0500
Received: from mga06.intel.com ([134.134.136.31]:24747 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727151AbgBXCNF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 23 Feb 2020 21:13:05 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 23 Feb 2020 18:13:05 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,478,1574150400";
   d="scan'208";a="255437187"
Received: from lxy-dell.sh.intel.com ([10.239.13.109])
  by orsmga002.jf.intel.com with ESMTP; 23 Feb 2020 18:13:02 -0800
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 1/2] kvm: vmx: Use basic exit reason to check if it's the
 specific VM EXIT
Date: Mon, 24 Feb 2020 10:07:50 +0800
Message-Id: <20200224020751.1469-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.23.0
In-Reply-To: <20200224020751.1469-1-xiaoyao.li@intel.com>
References: <20200224020751.1469-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current kvm uses the 32-bit exit reason to check if it's any specific VM
EXIT, however only the low 16-bit of VM EXIT REASON acts as the basic
exit reason.

Introduce Macro basic(exit_reaso) to help retrieve the basic exit reason
from VM EXIT REASON, and use the basic exit reason for checking and
indexing the exit hanlder.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 44 ++++++++++++++++++++++--------------------
 arch/x86/kvm/vmx/vmx.h |  2 ++
 2 files changed, 25 insertions(+), 21 deletions(-)

```
#### [PATCH RESEND] KVM: X86: eliminate obsolete KVM_GET_CPUID2 ioctl
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11399217
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5D1DF14D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 03:45:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4642C20836
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 03:45:57 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727252AbgBXDpx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 23 Feb 2020 22:45:53 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:10674 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727215AbgBXDpx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 23 Feb 2020 22:45:53 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id B7642D7FA239ADBD3D93;
        Mon, 24 Feb 2020 11:45:50 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS404-HUB.china.huawei.com
 (10.3.19.204) with Microsoft SMTP Server id 14.3.439.0; Mon, 24 Feb 2020
 11:45:40 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH RESEND] KVM: X86: eliminate obsolete KVM_GET_CPUID2 ioctl
Date: Mon, 24 Feb 2020 11:47:12 +0800
Message-ID: <1582516032-5161-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

KVM_GET_CPUID2 ioctl is straight up broken and not used anywhere. Remove
it directly.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/cpuid.c           | 20 --------------------
 arch/x86/kvm/cpuid.h           |  3 ---
 arch/x86/kvm/x86.c             | 17 -----------------
 include/uapi/linux/kvm.h       |  1 -
 tools/include/uapi/linux/kvm.h |  1 -
 5 files changed, 42 deletions(-)

```
#### [PATCH v3 1/7] vfio: allow external user to get vfio group from device
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11399537
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4EA4E138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 08:56:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 38A1224650
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 08:56:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727459AbgBXI4J (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 24 Feb 2020 03:56:09 -0500
Received: from mga12.intel.com ([192.55.52.136]:40096 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726925AbgBXI4I (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 24 Feb 2020 03:56:08 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga106.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 24 Feb 2020 00:56:08 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,479,1574150400";
   d="scan'208";a="231068681"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by fmsmga008.fm.intel.com with ESMTP; 24 Feb 2020 00:56:06 -0800
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com
Cc: zhenyuw@linux.intel.com, intel-gvt-dev@lists.freedesktop.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, kevin.tian@intel.com, peterx@redhat.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [PATCH v3 1/7] vfio: allow external user to get vfio group from
 device
Date: Mon, 24 Feb 2020 03:46:41 -0500
Message-Id: <20200224084641.31696-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200224084350.31574-1-yan.y.zhao@intel.com>
References: <20200224084350.31574-1-yan.y.zhao@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

external user is able to
1. add a device into an vfio group
2. call vfio_group_get_external_user_from_dev() with the device pointer
to get vfio_group associated with this device and increments the container
user counter to prevent the VFIO group from disposal before KVM exits.
3. When the external KVM finishes, it calls vfio_group_put_external_user()
to release the VFIO group.

Suggested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
---
 drivers/vfio/vfio.c  | 37 +++++++++++++++++++++++++++++++++++++
 include/linux/vfio.h |  2 ++
 2 files changed, 39 insertions(+)

```
#### [PATCH v3] KVM: apic: avoid calculating pending eoi from an uninitialized val
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11399215
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4591314D5
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 03:45:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2E98E20828
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 03:45:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727207AbgBXDpL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 23 Feb 2020 22:45:11 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:46188 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727168AbgBXDpL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 23 Feb 2020 22:45:11 -0500
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id CBD40889192361505E60;
        Mon, 24 Feb 2020 11:45:08 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS410-HUB.china.huawei.com
 (10.3.19.210) with Microsoft SMTP Server id 14.3.439.0; Mon, 24 Feb 2020
 11:45:02 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH v3] KVM: apic: avoid calculating pending eoi from an
 uninitialized val
Date: Mon, 24 Feb 2020 11:46:33 +0800
Message-ID: <1582515993-5098-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

When pv_eoi_get_user() fails, 'val' may remain uninitialized and the return
value of pv_eoi_get_pending() becomes random.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/lapic.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v3] KVM: x86: enable dirty log gradually in small chunks
##### From: Jay Zhou <jianjay.zhou@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jay Zhou <jianjay.zhou@huawei.com>
X-Patchwork-Id: 11399201
Return-Path: <SRS0=NYzf=4M=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5F07492A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 03:26:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2FACF2071C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 24 Feb 2020 03:26:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727168AbgBXD0b (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 23 Feb 2020 22:26:31 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:11102 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727156AbgBXD0a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 23 Feb 2020 22:26:30 -0500
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 9D51EF99E702EC59DF86;
        Mon, 24 Feb 2020 11:26:24 +0800 (CST)
Received: from localhost (10.173.228.206) by DGGEMS405-HUB.china.huawei.com
 (10.3.19.205) with Microsoft SMTP Server id 14.3.439.0; Mon, 24 Feb 2020
 11:26:16 +0800
From: Jay Zhou <jianjay.zhou@huawei.com>
To: <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <peterx@redhat.com>,
        <sean.j.christopherson@intel.com>, <wangxinxin.wang@huawei.com>,
        <weidong.huang@huawei.com>, <jianjay.zhou@huawei.com>,
        <liu.jinsong@huawei.com>
Subject: [PATCH v3] KVM: x86: enable dirty log gradually in small chunks
Date: Mon, 24 Feb 2020 11:25:58 +0800
Message-ID: <20200224032558.2728-1-jianjay.zhou@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.228.206]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

It could take kvm->mmu_lock for an extended period of time when
enabling dirty log for the first time. The main cost is to clear
all the D-bits of last level SPTEs. This situation can benefit from
manual dirty log protect as well, which can reduce the mmu_lock
time taken. The sequence is like this:

1. Initialize all the bits of the dirty bitmap to 1 when enabling
   dirty log for the first time
2. Only write protect the huge pages
3. KVM_GET_DIRTY_LOG returns the dirty bitmap info
4. KVM_CLEAR_DIRTY_LOG will clear D-bit for each of the leaf level
   SPTEs gradually in small chunks

Under the Intel(R) Xeon(R) Gold 6152 CPU @ 2.10GHz environment,
I did some tests with a 128G windows VM and counted the time taken
of memory_global_dirty_log_start, here is the numbers:

VM Size        Before    After optimization
128G           460ms     10ms

Signed-off-by: Jay Zhou <jianjay.zhou@huawei.com>
---
v3:
  * add kvm_manual_dirty_log_init_set helper, add testcase on top and
    keep old behavior for KVM_MEM_READONLY [Peter]
  * tweak logic at enabling KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2 [Sean, Peter]

v2:
  * add new bit to KVM_ENABLE_CAP for KVM_CAP_MANUAL_DIRTY_LOG_PROTECT2 [Paolo]
  * support non-PML path [Peter]
  * delete the unnecessary ifdef and make the initialization of bitmap
    more clear [Sean]
  * document the new bits and tweak the testcase

 Documentation/virt/kvm/api.rst  | 16 +++++++++++++---
 arch/x86/include/asm/kvm_host.h |  3 ++-
 arch/x86/kvm/mmu/mmu.c          |  7 ++++---
 arch/x86/kvm/vmx/vmx.c          |  3 ++-
 arch/x86/kvm/x86.c              | 18 +++++++++++++++---
 include/linux/kvm_host.h        |  9 ++++++++-
 virt/kvm/kvm_main.c             | 30 +++++++++++++++++++++++-------
 7 files changed, 67 insertions(+), 19 deletions(-)

```
