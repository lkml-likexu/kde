#### [Bug 205171] kernel panic during windows 10pro start
##### From: bugzilla-daemon@bugzilla.kernel.org

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: bugzilla-daemon@bugzilla.kernel.org
X-Patchwork-Id: 11188081
Return-Path: <SRS0=utul=YH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0610A912
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 09:08:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DA67120854
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 09:08:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730684AbfJNJIb convert rfc822-to-8bit (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 05:08:31 -0400
Received: from mail.kernel.org ([198.145.29.99]:36228 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730655AbfJNJIa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 05:08:30 -0400
From: bugzilla-daemon@bugzilla.kernel.org
To: kvm@vger.kernel.org
Subject: [Bug 205171] kernel panic during windows 10pro start
Date: Mon, 14 Oct 2019 09:08:29 +0000
X-Bugzilla-Reason: None
X-Bugzilla-Type: changed
X-Bugzilla-Watch-Reason: AssignedTo virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Product: Virtualization
X-Bugzilla-Component: kvm
X-Bugzilla-Version: unspecified
X-Bugzilla-Keywords: 
X-Bugzilla-Severity: normal
X-Bugzilla-Who: vkuznets@redhat.com
X-Bugzilla-Status: NEW
X-Bugzilla-Resolution: 
X-Bugzilla-Priority: P1
X-Bugzilla-Assigned-To: virtualization_kvm@kernel-bugs.osdl.org
X-Bugzilla-Flags: 
X-Bugzilla-Changed-Fields: 
Message-ID: <bug-205171-28872-YCF28yxjs3@https.bugzilla.kernel.org/>
In-Reply-To: <bug-205171-28872@https.bugzilla.kernel.org/>
References: <bug-205171-28872@https.bugzilla.kernel.org/>
X-Bugzilla-URL: https://bugzilla.kernel.org/
Auto-Submitted: auto-generated
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

https://bugzilla.kernel.org/show_bug.cgi?id=205171

--- Comment #2 from vkuznets@redhat.com ---
bugzilla-daemon@bugzilla.kernel.org writes:

> https://bugzilla.kernel.org/show_bug.cgi?id=205171
>
>             Bug ID: 205171
>            Summary: kernel panic during windows 10pro start
>            Product: Virtualization
>            Version: unspecified
>     Kernel Version: 4.19.74 and higher
>           Hardware: All
>                 OS: Linux
>               Tree: Mainline
>             Status: NEW
>           Severity: normal
>           Priority: P1
>          Component: kvm
>           Assignee: virtualization_kvm@kernel-bugs.osdl.org
>           Reporter: dront78@gmail.com
>         Regression: No
>
> works fine on 4.19.73
>
> [ 5829.948945] BUG: unable to handle kernel NULL pointer dereference at
> 0000000000000000
> [ 5829.948951] PGD 0 P4D 0 
> [ 5829.948954] Oops: 0002 [#1] SMP NOPTI
> [ 5829.948957] CPU: 3 PID: 1699 Comm: CPU 0/KVM Tainted: G           OE    
> 4.19.78-2-lts #1
> [ 5829.948958] Hardware name: Micro-Star International Co., Ltd. GE62
> 6QF/MS-16J4, BIOS E16J4IMS.117 01/18/2018
> [ 5829.948989] RIP: 0010:kvm_write_guest_virt_system+0x1e/0x40 [kvm]

It seems 4.19 stable backport is broken, upstream commit f7eea636c3d50
has:

@@ -4588,7 +4589,8 @@ static int handle_vmread(struct kvm_vcpu *vcpu)
                                vmx_instruction_info, true, len, &gva))
                        return 1;
                /* _system ok, nested_vmx_check_permission has verified cpl=0
*/
-               kvm_write_guest_virt_system(vcpu, gva, &field_value, len,
NULL);
+               if (kvm_write_guest_virt_system(vcpu, gva, &field_value, len,
&e))
+                       kvm_inject_page_fault(vcpu, &e);
        }

and it's 4.19 counterpart (73c31bd92039):

@@ -8798,8 +8799,10 @@ static int handle_vmread(struct kvm_vcpu *vcpu)
                                vmx_instruction_info, true, &gva))
                        return 1;
                /* _system ok, nested_vmx_check_permission has verified cpl=0
*/
-               kvm_write_guest_virt_system(vcpu, gva, &field_value,
-                                           (is_long_mode(vcpu) ? 8 : 4),
NULL);
+               if (kvm_write_guest_virt_system(vcpu, gva, &field_value,
+                                               (is_long_mode(vcpu) ? 8 : 4),
+                                               NULL))
+                       kvm_inject_page_fault(vcpu, &e);
        }

(note the last argument to kvm_write_guest_virt_system() - it's NULL
instead of &e.

And v4.19.74 has 6e60900cfa3e (541ab2aeb282 upstream):

@@ -5016,6 +5016,13 @@ int kvm_write_guest_virt_system(struct kvm_vcpu *vcpu,
gva_t addr, void *val,
        /* kvm_write_guest_virt_system can pull in tons of pages. */
        vcpu->arch.l1tf_flush_l1d = true;

+       /*
+        * FIXME: this should call handle_emulation_failure if
X86EMUL_IO_NEEDED
+        * is returned, but our callers are not ready for that and they blindly
+        * call kvm_inject_page_fault.  Ensure that they at least do not leak
+        * uninitialized kernel stack memory into cr2 and error code.
+        */
+       memset(exception, 0, sizeof(*exception));
        return kvm_write_guest_virt_helper(addr, val, bytes, vcpu,
                                           PFERR_WRITE_MASK, exception);
 }

This all results in memset(NULL). (also, 6e60900cfa3e should come
*after* f7eea636c3d50 and not before but oh well..)

The following will likely fix the problem (untested):


I can send a patch to stable@ if needed.

```
#### [PATCH] KVM: X86: Make fpu allocation a common function
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11189109
Return-Path: <SRS0=utul=YH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0641B76
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 16:37:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E532821927
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 16:37:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388151AbfJNQhx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 12:37:53 -0400
Received: from mga04.intel.com ([192.55.52.120]:2181 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1732550AbfJNQhx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 12:37:53 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga003.jf.intel.com ([10.7.209.27])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 14 Oct 2019 09:37:52 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,296,1566889200";
   d="scan'208";a="198343502"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.57])
  by orsmga003.jf.intel.com with ESMTP; 14 Oct 2019 09:37:50 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Jim Mattson <jmattson@google.com>
Cc: Xiaoyao Li <xiaoyao.li@intel.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: X86: Make fpu allocation a common function
Date: Tue, 15 Oct 2019 00:22:47 +0800
Message-Id: <20191014162247.61461-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

They are duplicated codes to create vcpu.arch.{user,guest}_fpu in VMX
and SVM. Make them common functions.

No functional change intended.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/svm.c     | 20 +++-----------------
 arch/x86/kvm/vmx/vmx.c | 20 +++-----------------
 arch/x86/kvm/x86.h     | 26 ++++++++++++++++++++++++++
 3 files changed, 32 insertions(+), 34 deletions(-)

```
#### [kvm-unit-tests PATCH 1/4] x86: emulator: use "SSE2" for the targetFrom: Bill Wendling <morbo@google.com>
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11189347
Return-Path: <SRS0=utul=YH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8032914DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 19:24:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 57DBF21721
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 19:24:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="pKZBHc1s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388698AbfJNTYl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 15:24:41 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:32784 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388526AbfJNTYl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 14 Oct 2019 15:24:41 -0400
Received: by mail-pf1-f202.google.com with SMTP id z4so14060799pfn.0
        for <kvm@vger.kernel.org>; Mon, 14 Oct 2019 12:24:40 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=XTuI7th3+9dwO3nKtBiY4qgOMbcjEb2zppHYOAbpHRc=;
        b=pKZBHc1sL0Aihc9J58KstqL1tdK75TYWZt7T71dQgixvTRjPWy9eR23YCkK01QQJPB
         R5KoV9l0kqeqeBua/Z4Qdf+BuSOSU14p/a7aMs2abKFLIbttKmOY5UwaSPSPgrGpfIp3
         d/cnBJgGdm+w47On2ZNxE5ANbC2gVOKM8Huh3JlTMV+34cpcn1OCVZcd+ggU5cmA5xjs
         vGDi3M1x6uv53yUXXqSOQhl4yC6QSQOqeHSHJBTElArrpVa5p82ru3AtNpjdB3EYbCzN
         cPLrQnUuTD68SaxxmPD8FrfmhyQIlbSDPO6WZrbcVLRX6x6DpEPNsfxE3XQCd9Z++jpE
         w9YQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=XTuI7th3+9dwO3nKtBiY4qgOMbcjEb2zppHYOAbpHRc=;
        b=WOjSIWoAIDloPSjXReMQ4eNm9KyYnXD8rFgtAEcEOvDyfux4P8DEsDUzdCPOIyhPiT
         KAqjT2kf1T7s9X2+jC31t1258Fn/s3fDQbHYPDp0FUvVOTT/T6iPinlb9jblu+r1ddYp
         W1FB25V17WIxC1p+eN27QjBvCUjmBjIocMkems7pYrkpjfBNYoNEeo5u0giCh33y2kSf
         DdXO/KjWepVa6d/6Jou68dE5lM4KFeM73GfkbK3y+Zi/CaBtKQp7GVZ8ESc2uoKx39Dx
         CZRiyxxKS32+48O+OCh3ucZXk4FswYXtJX6JGUwEQSVEPxVaekL6vsgjFtbFP/wpRJgA
         FVbQ==
X-Gm-Message-State: APjAAAXWFocgWlVM7g184AESWNOTryMa8Pa4zNcbfkGOnIOk//hmWe7x
        qq3h/N2AqUH1mYZ8dD4pQJky8cphIzvvUiFHFYXn3jXWzEdCAtbw2P6+i/Cr6qGWwvWpxk2wjhC
        8qLgNIR9OD5Czym6TyuLyqhiKe03kAjXpR6CuvJKoIfSOtLwScm6ncA==
X-Google-Smtp-Source: 
 APXvYqxCB2n5bex1Ri2jT7GzX+W5F0ZSg6NXeJUsVz8u3rrbkJVfjA+XO97PtqaauyILz5uDxV2w/LEHCA==
X-Received: by 2002:a65:4c03:: with SMTP id u3mr34809021pgq.440.1571081080141;
 Mon, 14 Oct 2019 12:24:40 -0700 (PDT)
Date: Mon, 14 Oct 2019 12:24:28 -0700
In-Reply-To: <20191014192431.137719-1-morbo@google.com>
Message-Id: <20191014192431.137719-2-morbo@google.com>
Mime-Version: 1.0
References: <20191010183506.129921-1-morbo@google.com>
 <20191014192431.137719-1-morbo@google.com>
X-Mailer: git-send-email 2.23.0.700.g56cf767bdb-goog
Subject: [kvm-unit-tests PATCH 1/4] x86: emulator: use "SSE2" for the target
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: jmattson@google.com, sean.j.christopherson@intel.com,
        Bill Wendling <morbo@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The movdqu and movapd instructions are SSE2 instructions. Clang
interprets the __attribute__((target("sse"))) as allowing SSE only
instructions. Using SSE2 instructions cause an error.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/emulator.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC PATCH 1/4] vfio-ccw: Refactor how the traces are built
##### From: Eric Farman <farman@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11189273
Return-Path: <SRS0=utul=YH=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BBB7315AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 18:09:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A6E5321835
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 14 Oct 2019 18:09:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388496AbfJNSJG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 14 Oct 2019 14:09:06 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:54076 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1732682AbfJNSJG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 14 Oct 2019 14:09:06 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9EHvmV6054858
        for <kvm@vger.kernel.org>; Mon, 14 Oct 2019 14:09:04 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2vmwfr16n8-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 14 Oct 2019 14:09:04 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <farman@linux.ibm.com>;
        Mon, 14 Oct 2019 19:09:03 +0100
Received: from b06cxnps3074.portsmouth.uk.ibm.com (9.149.109.194)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 14 Oct 2019 19:09:00 +0100
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9EI8xIv46465254
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 14 Oct 2019 18:08:59 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0F6714C059;
        Mon, 14 Oct 2019 18:08:59 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EE93D4C04E;
        Mon, 14 Oct 2019 18:08:58 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon, 14 Oct 2019 18:08:58 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 9D16EE0184; Mon, 14 Oct 2019 20:08:58 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Jason Herne <jjherne@linux.ibm.com>,
        Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [RFC PATCH 1/4] vfio-ccw: Refactor how the traces are built
Date: Mon, 14 Oct 2019 20:08:52 +0200
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20191014180855.19400-1-farman@linux.ibm.com>
References: <20191014180855.19400-1-farman@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19101418-0016-0000-0000-000002B7FE9D
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19101418-0017-0000-0000-000033191992
Message-Id: <20191014180855.19400-2-farman@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-14_09:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910140149
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 3cd90214b70f ("vfio: ccw: add tracepoints for interesting error
paths") added a quick trace point to determine where a channel program
failed while being processed.  It's a great addition, but adding more
traces to vfio-ccw is more cumbersome than it needs to be.

Let's refactor how this is done, so that additional traces are easier
to add and can exist outside of the FSM if we ever desire.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/Makefile         |  4 ++--
 drivers/s390/cio/vfio_ccw_cp.h    |  1 +
 drivers/s390/cio/vfio_ccw_fsm.c   |  3 ---
 drivers/s390/cio/vfio_ccw_trace.c | 12 ++++++++++++
 drivers/s390/cio/vfio_ccw_trace.h |  2 ++
 5 files changed, 17 insertions(+), 5 deletions(-)
 create mode 100644 drivers/s390/cio/vfio_ccw_trace.c

```
