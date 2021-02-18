

#### [PATCH 0/3] x86/sev-es: Check for trusted regs->sp in
##### From: Joerg Roedel <joro@8bytes.org>
From: Joerg Roedel <jroedel@suse.de>

```c
From patchwork Wed Feb 17 12:01:40 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12091503
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 026E9C433E0
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 12:03:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C20B464E5B
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 12:03:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232549AbhBQMDb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Feb 2021 07:03:31 -0500
Received: from 8bytes.org ([81.169.241.247]:55946 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232583AbhBQMDA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Feb 2021 07:03:00 -0500
Received: from cap.home.8bytes.org (p549adcf6.dip0.t-ipconnect.de
 [84.154.220.246])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id 2E8D9246;
        Wed, 17 Feb 2021 13:02:08 +0100 (CET)
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
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH 0/3] x86/sev-es: Check for trusted regs->sp in
 __sev_es_ist_enter()
Date: Wed, 17 Feb 2021 13:01:40 +0100
Message-Id: <20210217120143.6106-1-joro@8bytes.org>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Hi,

here are some changes to the Linux SEV-ES code to check whether the
value in regs->sp can be trusted, before checking whether it points to
the #VC IST stack.

Andy Lutomirski reported that it is entirely possible to reach this
function with a regs->sp value which was set by user-space. So check
for this condition and don't use regs->sp if it can't be trusted.

Also improve the comments around __sev_es_ist_enter/exit() to better
explain what these function do and why they are there.

Please review.

Thanks,

	Joerg

Joerg Roedel (3):
  x86/sev-es: Introduce from_syscall_gap() helper
  x86/sev-es: Check if regs->sp is trusted before adjusting #VC IST
    stack
  x86/sev-es: Improve comments in and around __sev_es_ist_enter/exit()

 arch/x86/include/asm/ptrace.h |  8 ++++++++
 arch/x86/kernel/sev-es.c      | 27 +++++++++++++++++++--------
 arch/x86/kernel/traps.c       |  3 +--
 3 files changed, 28 insertions(+), 10 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/8] s390x: Cleanup exception register
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Wed Feb 17 14:41:08 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12091723
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 93876C433E9
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 14:43:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 65A4F64E4A
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 14:43:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233562AbhBQOnJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Feb 2021 09:43:09 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:55700 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233542AbhBQOnI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Feb 2021 09:43:08 -0500
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11HEZNrC189774;
        Wed, 17 Feb 2021 09:42:26 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=a3IxyveesgxYnc4x6l6ab0vsfXg8aBqrZpXFqDRJyHI=;
 b=QstLV2069QV9bb88iYCBwYAM/Z8QXJvPr8HcYu0Hgl0LixW+UjVFxYNnto0nF1T2jV21
 nn5eN+Neh4T8uaJQEnSWEYrSFvk8o+W3bex9Z1RxxUMcjgPnr7s55/XTuz+T8oYvbi6J
 k01hKotcm7N13dr7uSirCwe8n4KLZ/e6ABVuQVf63t7qCf0gpy8VO6MM+vZBV8v37T2V
 VW/9UQZd8Y9AJx60fQ6yiq9Uw8ywN4rPO1E7U/sruQQpOjbUVM+is4cflsfZBPeNf28r
 lxDRZ/HhCQfSHo5UfZHIr24bagDzXV+xEXg95yElv8LOsb/4wiW+j2a2cahir1u6Wlx5 rA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36s3ew3ska-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Feb 2021 09:42:25 -0500
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11HEZvda192795;
        Wed, 17 Feb 2021 09:42:25 -0500
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36s3ew3shq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Feb 2021 09:42:25 -0500
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11HEgMHn023514;
        Wed, 17 Feb 2021 14:42:22 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma04fra.de.ibm.com with ESMTP id 36p6d89yan-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Feb 2021 14:42:22 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11HEgJSi38732092
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 17 Feb 2021 14:42:19 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8040F11C04C;
        Wed, 17 Feb 2021 14:42:19 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CC79F11C054;
        Wed, 17 Feb 2021 14:42:18 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 17 Feb 2021 14:42:18 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        pmorel@linux.ibm.com, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 0/8] s390x: Cleanup exception register
 save/restore and implement backtrace
Date: Wed, 17 Feb 2021 09:41:08 -0500
Message-Id: <20210217144116.3368-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-17_12:2021-02-16,2021-02-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0
 mlxlogscore=999 priorityscore=1501 lowpriorityscore=0 clxscore=1015
 spamscore=0 phishscore=0 impostorscore=0 mlxscore=0 malwarescore=0
 adultscore=0 bulkscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102170113
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Having two sets of macros for saving and restoring registers on
exceptions doesn't seem optimal to me. Therefore this patch set
removes the old macros that use the lowcore as storage in favor of the
stack using ones. At the same time we move over to generated offsets
instead of subtracting from the stack piece by piece. Changes to the
stack struct are easier that way.

Additionally let's add backtrace support and print the GRs on
exception so we get a bit more information when something goes wrong.

v2:
	* Added full CR saving to fix diag308 test
	* Added rev-bys

Janosch Frank (8):
  s390x: Fix fpc store address in RESTORE_REGS_STACK
  s390x: Fully commit to stack save area for exceptions
  RFC: s390x: Define STACK_FRAME_INT_SIZE macro
  s390x: Introduce and use CALL_INT_HANDLER macro
  s390x: Provide preliminary backtrace support
  s390x: Print more information on program exceptions
  s390x: Move diag308_load_reset to stack saving
  s390x: Remove SAVE/RESTORE_stack

 lib/s390x/asm-offsets.c   | 15 +++++--
 lib/s390x/asm/arch_def.h  | 29 ++++++++++---
 lib/s390x/asm/interrupt.h |  4 +-
 lib/s390x/interrupt.c     | 43 +++++++++++++++---
 lib/s390x/stack.c         | 20 ++++++---
 s390x/Makefile            |  1 +
 s390x/cpu.S               |  6 ++-
 s390x/cstart64.S          | 25 +++--------
 s390x/macros.S            | 91 +++++++++++++++++++--------------------
 9 files changed, 140 insertions(+), 94 deletions(-)
```
#### [PATCH 0/7] KVM: random nested fixes
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Wed Feb 17 14:57:11 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12091745
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 17A8FC433DB
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 14:59:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BCC8B64E28
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 14:59:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233651AbhBQO6z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Feb 2021 09:58:55 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:48003 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233493AbhBQO6x (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Feb 2021 09:58:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613573846;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=/nfMcV36HhAE2XwGrmtu/12blU+jhydqABEFlCZsevo=;
        b=IvV108WgulYFq/yixRc49kNK1M9pLxX17eiYX+aCOg1r1ANWOeICEhjwY1Al7M2qBpHD+p
        XzRDSod9qwJ97ESJTQXC2eMBwhbACI0LgSiRfo7tO7MI5oQ/+zL9zkucqwJSe2G33AIFiT
        Iv1B/5lWaSOd03lR3J9iRCJTirpT+wk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-334-IRJ5lmrRPEe9OkOERklwfw-1; Wed, 17 Feb 2021 09:57:24 -0500
X-MC-Unique: IRJ5lmrRPEe9OkOERklwfw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C71E518A0837;
        Wed, 17 Feb 2021 14:57:22 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.33])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1797E10016F0;
        Wed, 17 Feb 2021 14:57:18 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jim Mattson <jmattson@google.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Thomas Gleixner <tglx@linutronix.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Ingo Molnar <mingo@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/7] KVM: random nested fixes
Date: Wed, 17 Feb 2021 16:57:11 +0200
Message-Id: <20210217145718.1217358-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a set of mostly random fixes I have in my patch queue.

- Patches 1,2 are minor tracing fixes from a patch series I sent
  some time ago which I don't want to get lost in the noise.

- Patches 3,4 are for fixing a theoretical bug in VMX with ept=0, but also to
  allow to move nested_vmx_load_cr3 call a bit, to make sure that update to
  .inject_page_fault is not lost while entering a nested guest.

- Patch 5 fixes running nested guests with npt=0 on host, which is sometimes
  useful for debug and such (especially nested).

- Patch 6 fixes the (mostly theoretical) issue with PDPTR loading on VMX after
  nested migration.

- Patch 7 is hopefully the correct fix to eliminate a L0 crash in some rare
  cases when a HyperV guest is migrated.

This was tested with kvm_unit_tests on both VMX and SVM,
both native and in a VM.
Some tests fail on VMX, but I haven't observed new tests failing
due to the changes.

This patch series was also tested by doing my nested migration with:
    1. npt/ept disabled on the host
    2. npt/ept enabled on the host and disabled in the L1
    3. npt/ept enabled on both.

In case of npt/ept=0 on the host (both on Intel and AMD),
the L2 eventually crashed but I strongly suspect a bug in shadow mmu,
which I track separately.
(see below for full explanation).

This patch series is based on kvm/queue branch.

Best regards,
	Maxim Levitsky

PS: The shadow mmu bug which I spent most of this week on:

In my testing I am not able to boot win10 (without nesting, HyperV or
anything special) on either Intel nor AMD without two dimensional paging
enabled (ept/npt).
It always crashes in various ways during the boot.

I found out (accidentally) that if I make KVM's shadow mmu not unsync last level
shadow pages, it starts working.
In addition to that, as I mentioned above this bug can happen on Linux as well,
while stressing the shadow mmu with repeated migrations
(and again with the same shadow unsync hack it just works).

While running without two dimensional paging is very obsolete by now, a
bug in shadow mmu is relevant to nesting, since it uses it as well.

Maxim Levitsky (7):
  KVM: VMX: read idt_vectoring_info a bit earlier
  KVM: nSVM: move nested vmrun tracepoint to enter_svm_guest_mode
  KVM: x86: add .complete_mmu_init arch callback
  KVM: nVMX: move inject_page_fault tweak to .complete_mmu_init
  KVM: nSVM: fix running nested guests when npt=0
  KVM: nVMX: don't load PDPTRS right after nested state set
  KVM: nSVM: call nested_svm_load_cr3 on nested state load

 arch/x86/include/asm/kvm-x86-ops.h |  1 +
 arch/x86/include/asm/kvm_host.h    |  2 +
 arch/x86/kvm/mmu/mmu.c             |  2 +
 arch/x86/kvm/svm/nested.c          | 84 +++++++++++++++++++-----------
 arch/x86/kvm/svm/svm.c             |  9 ++++
 arch/x86/kvm/svm/svm.h             |  1 +
 arch/x86/kvm/vmx/nested.c          | 22 ++++----
 arch/x86/kvm/vmx/nested.h          |  1 +
 arch/x86/kvm/vmx/vmx.c             | 13 ++++-
 9 files changed, 92 insertions(+), 43 deletions(-)
```
