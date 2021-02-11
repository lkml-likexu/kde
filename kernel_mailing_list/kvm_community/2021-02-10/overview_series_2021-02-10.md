#### [PATCH] KVM: selftests: Add missing header file needed by xAPIC IPI tests
##### From: Sean Christopherson <seanjc@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12079625
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 9A784C433DB
	for <kvm@archiver.kernel.org>; Wed, 10 Feb 2021 01:19:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 594F964E05
	for <kvm@archiver.kernel.org>; Wed, 10 Feb 2021 01:19:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234806AbhBJBTZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 20:19:25 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41306 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234272AbhBJBSi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Feb 2021 20:18:38 -0500
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9AA1BC061788
        for <kvm@vger.kernel.org>; Tue,  9 Feb 2021 17:17:51 -0800 (PST)
Received: by mail-yb1-xb49.google.com with SMTP id k7so596718ybm.13
        for <kvm@vger.kernel.org>; Tue, 09 Feb 2021 17:17:51 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=4sl8hCVYIIQXoKXiaYQxzYCkEmKowx44CLAZnUGYVQs=;
        b=YkvoF37IrAacD5AjBdQZFGuE+sqb+HPbZ0qhtTS0gmDv1XP1r2Hv/AcFIZDnnN5WJd
         26pLWViCA7wdm7H4/QmSnpJlDhz2I44y8JE0eaKfu7gI3P+eGMGr7oiNnfkKbH0CBDMA
         o8xzlyXdUNogp1VR6BudLfgdj2bSrtGM1eh6/PUUu3zcKNCwguYUP+b3dWUxIwSPMPDg
         Qp1hJzmmVjnqYPcCevN7qAa3kub9UbdJxV9tlDtIqppBtIfB+tZNbUimxnqX2LzCkq3W
         5feHA8oRk/rKWYPS+nXzyb2btxspxoTY/a6QjiwFd1oTC9C1q3D7gMrhZNMg98fLyBO6
         DsZA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=4sl8hCVYIIQXoKXiaYQxzYCkEmKowx44CLAZnUGYVQs=;
        b=eJNGpDxRdJtJMCkWGDIYCFLO1/Y9RBspm/uwh10wfsDZ6FKBWIdKRNc6aTrr6Cx+72
         kSUclNfkSZGGsvoFvy5lXCSFGzEhZ7d7r4BEmta6NQfyTYimJ4ec6ROY2jp9C83eaN3z
         ZWFDS3vBto/z8J08k0YHs78Vqo7o+kc5TYzt1qf9Omn3RoVO7P3alBj4BNV6kt/hJYOF
         9ob+jRDztprPvWzCvSkHrEJWN5Urs9g05nE0iKIDzqBhPN3wXiTGSHKMpcTHxyfj5TdC
         SOjfG7PGnhhJmWH1YFdN0ccN39N4YBb+jns1FkIDoKrDGxBGWO1fWTPlwpWOlemOEyTs
         XvUA==
X-Gm-Message-State: AOAM533UENIh4cOVvbj2OV/HIQkevmngr0WvQcfIGQ45sMw6IbxU6J5x
        EF/de6s20TvvZ1q6evCOfowylT5Yilg=
X-Google-Smtp-Source: 
 ABdhPJzPRKyyxJdYxkBjVQkd0UxE8M40kpQxENvRuhzY8gYI83CdYVh2q9wUF/UDyg08fHP70sxnxbDTjcM=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:1513:9e6:21c3:30d3])
 (user=seanjc job=sendgmr) by 2002:a25:e787:: with SMTP id
 e129mr889657ybh.478.1612919870827;
 Tue, 09 Feb 2021 17:17:50 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  9 Feb 2021 17:17:47 -0800
Message-Id: <20210210011747.240913-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH] KVM: selftests: Add missing header file needed by xAPIC IPI
 tests
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Andrew Jones <drjones@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Sean Christopherson <seanjc@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Shier <pshier@google.com>

Fixes: 678e90a349a4 ("KVM: selftests: Test IPI to halted vCPU in xAPIC while backing page moves")
Cc: Andrew Jones <drjones@redhat.com>
Cc: Jim Mattson <jmattson@google.com>
Signed-off-by: Peter Shier <pshier@google.com>
Signed-off-by: Sean Christopherson <seanjc@google.com>
---

Delta patch taken verbatim from Peter's original submission.  Applying the
original patch directly is mildly annoying due to conflicts with kvm/next
in other files.

 tools/testing/selftests/kvm/include/numaif.h | 55 ++++++++++++++++++++
 1 file changed, 55 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/include/numaif.h

diff --git a/tools/testing/selftests/kvm/include/numaif.h b/tools/testing/selftests/kvm/include/numaif.h
new file mode 100644
index 000000000000..b020547403fd
--- /dev/null
+++ b/tools/testing/selftests/kvm/include/numaif.h
@@ -0,0 +1,55 @@
+/* SPDX-License-Identifier: GPL-2.0-only */
+/*
+ * tools/testing/selftests/kvm/include/numaif.h
+ *
+ * Copyright (C) 2020, Google LLC.
+ *
+ * This work is licensed under the terms of the GNU GPL, version 2.
+ *
+ * Header file that provides access to NUMA API functions not explicitly
+ * exported to user space.
+ */
+
+#ifndef SELFTEST_KVM_NUMAIF_H
+#define SELFTEST_KVM_NUMAIF_H
+
+#define __NR_get_mempolicy 239
+#define __NR_migrate_pages 256
+
+/* System calls */
+long get_mempolicy(int *policy, const unsigned long *nmask,
+		   unsigned long maxnode, void *addr, int flags)
+{
+	return syscall(__NR_get_mempolicy, policy, nmask,
+		       maxnode, addr, flags);
+}
+
+long migrate_pages(int pid, unsigned long maxnode,
+		   const unsigned long *frommask,
+		   const unsigned long *tomask)
+{
+	return syscall(__NR_migrate_pages, pid, maxnode, frommask, tomask);
+}
+
+/* Policies */
+#define MPOL_DEFAULT	 0
+#define MPOL_PREFERRED	 1
+#define MPOL_BIND	 2
+#define MPOL_INTERLEAVE	 3
+
+#define MPOL_MAX MPOL_INTERLEAVE
+
+/* Flags for get_mem_policy */
+#define MPOL_F_NODE	    (1<<0)  /* return next il node or node of address */
+				    /* Warning: MPOL_F_NODE is unsupported and
+				     * subject to change. Don't use.
+				     */
+#define MPOL_F_ADDR	    (1<<1)  /* look up vma using address */
+#define MPOL_F_MEMS_ALLOWED (1<<2)  /* query nodes allowed in cpuset */
+
+/* Flags for mbind */
+#define MPOL_MF_STRICT	     (1<<0) /* Verify existing pages in the mapping */
+#define MPOL_MF_MOVE	     (1<<1) /* Move pages owned by this process to conform to mapping */
+#define MPOL_MF_MOVE_ALL     (1<<2) /* Move every page to conform to mapping */
+
+#endif /* SELFTEST_KVM_NUMAIF_H */
```
#### [PATCH] KVM: selftests: Add operand to vmsave/vmload/vmrun in svm.cFrom: Ricardo Koller <ricarkol@google.com>
##### From: Ricardo Koller <ricarkol@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ricardo Koller <ricarkol@google.com>
X-Patchwork-Id: 12079721
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BCF70C433E0
	for <kvm@archiver.kernel.org>; Wed, 10 Feb 2021 03:18:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8376E64E3F
	for <kvm@archiver.kernel.org>; Wed, 10 Feb 2021 03:18:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231398AbhBJDSP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Feb 2021 22:18:15 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38604 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229703AbhBJDSO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Feb 2021 22:18:14 -0500
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 245BFC061574
        for <kvm@vger.kernel.org>; Tue,  9 Feb 2021 19:17:28 -0800 (PST)
Received: by mail-qk1-x74a.google.com with SMTP id r15so514025qke.5
        for <kvm@vger.kernel.org>; Tue, 09 Feb 2021 19:17:28 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=MAgnKOR63Vcbcr0Q3TwMb9QZTto3ra+JOzUzTYPtlnU=;
        b=NwTUueZoXliqack72iXTFwL1gnkNW6k3ZRqDYuiBGQsjNCeUi+pOm8jVnO+jWcdGdW
         dNRqkrMg/R3xscTgyY2sogn0pEoXXGsPlmxXakd/PdvFctE5rCzcCtfUe3BS9uZxopBr
         8kJBGa3+3AF3Ec3YdU6Hn5ydF74JPygNJ07ek21hvQKtYaFpHxk+iyRGgJHeq96zWICB
         6j7+HsU8aHQJgpes9N7MpXFQrByFYK2C/AvPXC7WtKeipnq0+Ft90pGNCwxezHtjZH0v
         lOrZ+gvceKl2dTFHjyP5M2kZxDEhwNlCzyxwoDAe54YRSVCc7jYYIXzZfHm58PMWJVMd
         n9/g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=MAgnKOR63Vcbcr0Q3TwMb9QZTto3ra+JOzUzTYPtlnU=;
        b=P53Vv77+uQThBOiHz3zwrFisCmpNX65DRWvES5aR4jZRaJ9mr8RlaBo2fCi2idhNW9
         U1inrgeJys0pQ8lM8LU9fgf8zvT/i3AIVgxvgp0J67p0kDP8GBTfes+HAd45zQ1nR9mt
         MgMnfB6EhFCtTDE96O1q/cLvM1dvLrrV7Jt9rJ23zgBbkElRlDW+Pjfk1i5OBnL7YP7w
         tw1nxyIKzP3T9kAX+lTui7bN7v/GfmsrmLtZyJHZ5qDNBlMjp5/d0rJdvcf1ILH1wraV
         RRf2hEAuLWhtZctjQBtynT3FMvHk/KGAkw0bydyAtzH6EvglI2L/51AMCjb6X/I50Iix
         XtkQ==
X-Gm-Message-State: AOAM533uj/WxgB7s32FRk1E9mTLHYNKFKjnqbioN29geI3nYeLFAGQzS
        mz9ByksR9+sBWMWSrlpTNkwgowiaZTPx9Zve6o6wlq5RbfKNMZOTAuIVKO3JMN4a0vbuaKxEIiZ
        efKh/IXbe3+o2kMFLQUMmTlX0UYLDbDqUfL/EUUcTg0VVH6jUMO1w1sShWwE4Ay4=
X-Google-Smtp-Source: 
 ABdhPJznceEJmYN2lSndCVF1dYbLmr7yfbOdiiTIgbipZwEQS+eD1zbdVyodcuyqit3PqhUyC6hn3730h4QgLQ==
Sender: "ricarkol via sendgmr" <ricarkol@ricarkol2.c.googlers.com>
X-Received: from ricarkol2.c.googlers.com
 ([fda3:e722:ac3:10:24:72f4:c0a8:62fe])
 (user=ricarkol job=sendgmr) by 2002:a0c:e14c:: with SMTP id
 c12mr1008982qvl.54.1612927047140; Tue, 09 Feb 2021 19:17:27 -0800 (PST)
Date: Wed, 10 Feb 2021 03:17:19 +0000
Message-Id: <20210210031719.769837-1-ricarkol@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH] KVM: selftests: Add operand to vmsave/vmload/vmrun in svm.c
From: Ricardo Koller <ricarkol@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Nathan Chancellor <nathan@kernel.org>,
        Ricardo Koller <ricarkol@google.com>,
        Sean Christopherson <seanjc@google.com>,
        Jim Mattson <jmattson@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Building the KVM selftests with LLVM's integrated assembler fails with:

  $ CFLAGS=-fintegrated-as make -C tools/testing/selftests/kvm CC=clang
  lib/x86_64/svm.c:77:16: error: too few operands for instruction
          asm volatile ("vmsave\n\t" : : "a" (vmcb_gpa) : "memory");
                        ^
  <inline asm>:1:2: note: instantiated into assembly here
          vmsave
          ^
  lib/x86_64/svm.c:134:3: error: too few operands for instruction
                  "vmload\n\t"
                  ^
  <inline asm>:1:2: note: instantiated into assembly here
          vmload
          ^
This is because LLVM IAS does not currently support calling vmsave,
vmload, or vmload without an explicit %rax operand.

Add an explicit operand to vmsave, vmload, and vmrum in svm.c. Fixing
this was suggested by Sean Christopherson.

Tested: building without this error in clang 11. The following patch
(not queued yet) needs to be applied to solve the other remaining error:
"selftests: kvm: remove reassignment of non-absolute variables".

Suggested-by: Sean Christopherson <seanjc@google.com>
Link: https://lore.kernel.org/kvm/X+Df2oQczVBmwEzi@google.com/
Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Ricardo Koller <ricarkol@google.com>
Reviewed-by: Nathan Chancellor <nathan@kernel.org>
---
 tools/testing/selftests/kvm/lib/x86_64/svm.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
