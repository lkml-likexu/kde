#### [RFC patch 01/15] entry: Provide generic syscall entry functionalityReferences: <20190919150314.054351477@linutronix.de>
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11152795
Return-Path: <SRS0=FKxr=XO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 27CC414ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 15:11:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 10C8C2196F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 15:11:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391099AbfISPLI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Sep 2019 11:11:08 -0400
Received: from Galois.linutronix.de ([193.142.43.55]:50056 "EHLO
        Galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1732034AbfISPJv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Sep 2019 11:09:51 -0400
Received: from localhost ([127.0.0.1] helo=nanos.tec.linutronix.de)
        by Galois.linutronix.de with esmtp (Exim 4.80)
        (envelope-from <tglx@linutronix.de>)
        id 1iAy3w-0006n4-LB; Thu, 19 Sep 2019 17:09:40 +0200
Message-Id: <20190919150808.521907403@linutronix.de>
User-Agent: quilt/0.65
Date: Thu, 19 Sep 2019 17:03:15 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, Peter Zijlstra <peterz@infradead.org>,
        Andy Lutomirski <luto@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        Mark Rutland <mark.rutland@arm.com>,
        Marc Zyngier <maz@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        linux-arch@vger.kernel.org
Subject: [RFC patch 01/15] entry: Provide generic syscall entry functionality
References: <20190919150314.054351477@linutronix.de>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On syscall entry certain work needs to be done conditionally like tracing,
seccomp etc. This code is duplicated in all architectures.

Provide a generic version.

Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
---
 arch/Kconfig                 |    3 +
 include/linux/entry-common.h |  122 +++++++++++++++++++++++++++++++++++++++++++
 kernel/Makefile              |    1 
 kernel/entry/Makefile        |    3 +
 kernel/entry/common.c        |   33 +++++++++++
```
#### [PATCH] kvm: svm: Intercept RDPRUFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11153553
Return-Path: <SRS0=FKxr=XO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7DBF014DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 22:59:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5BF0E217D6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 22:59:31 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="AUA17vzQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392180AbfISW7a (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Sep 2019 18:59:30 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:33034 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390868AbfISW7a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Sep 2019 18:59:30 -0400
Received: by mail-pf1-f202.google.com with SMTP id z4so3299860pfn.0
        for <kvm@vger.kernel.org>; Thu, 19 Sep 2019 15:59:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=6Zlr8wuycCBeL7Zrxw1psZnttExi5o85U5sXHuZaYoc=;
        b=AUA17vzQNnBlrNdpzLcSAVQAKoY3dolcqBXnoXQa9U0d01UijWP5dZWHusLICv2eWz
         lbctqJbdXYpgx2LT7tKh6WFY9rgs4SxahbX2+BSQtbIeGirCUlUQ8PvFOV4VQPu/7OTZ
         1Z4J0fHxFXu4MCzq7gAZO00ntHaul85mZWoFyidOX86i4bkFmhnkp2ZytihEGXp2vERV
         rg9qJuUJBYW0wDtbfxzlzsTB5CCJNM55WxXTaLH3to+VE/YmCQf+8Vu7VEcjPhUyQ+3N
         oFUQqCNmWgE4rZmEcmbhBAFvFpU1ees4a/Ro5c0Ro6pir1dZsZkUYFGm7mucyF3z41JS
         CGeQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=6Zlr8wuycCBeL7Zrxw1psZnttExi5o85U5sXHuZaYoc=;
        b=keAcJro/sf2CAmST3GsfByR6xLbvwjvR+6OmCU4ZjwIrb5VBZ+yQfj0wrGSSTNZbzJ
         SbB1tD1rZu7/3wPmmepvQnO40PLlC2xKuYCeDewwddbHwByQdiAwzAD9nuqd4RZFn2Bo
         3B9xUEFQ+HderQuJdzZIk+Q2Y+RVZLJjxZ1J3ofAm5+CMDYclLxVBXPPxbB+U3CMKzNm
         OrBcyywkP23Rc6AxlCIze9l7sMBdLzmhvn5NX/YdiHLCyiGHBRBGxhhl3c2MI33lOcBS
         X7wNxN+cpctpFweFpBSqTFdBoFrxo6w9SpU2QX4Qr0TlQ1e9r0zynucQM/8JnpIb7e+6
         mTUQ==
X-Gm-Message-State: APjAAAXTiLop6uaVPWD85+c0gSJk7bzRPhk7YMmsfiyhwifC3s1iJWKa
        QlYfosJvDqBGooBlEU9Fry45ht5758NDO6YUIxgnHkqyQd7YdgYVK23dS+eByP5X+9CAPcSk+R6
        5etaIDliRa7cLPBCaSVqUdw/AqOXiHcNfUmuYrlPJwxHcvvXOiXdLQwjrXl+FqNQ=
X-Google-Smtp-Source: 
 APXvYqz1hDTKHONDLD0Id+mic4R7iXpqOirlGHtpF3j7qi9/HVjNHOx6r6Ool7so4f0UTrNRvn8fJMhbYgCsFg==
X-Received: by 2002:a63:a0d:: with SMTP id 13mr10354462pgk.99.1568933968821;
 Thu, 19 Sep 2019 15:59:28 -0700 (PDT)
Date: Thu, 19 Sep 2019 15:59:17 -0700
Message-Id: <20190919225917.36641-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.351.gc4317032e6-goog
Subject: [PATCH] kvm: svm: Intercept RDPRU
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Drew Schmitt <dasch@google.com>,
        Jacob Xu <jacobhxu@google.com>, Peter Shier <pshier@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The RDPRU instruction gives the guest read access to the IA32_APERF
MSR and the IA32_MPERF MSR. According to volume 3 of the APM, "When
virtualization is enabled, this instruction can be intercepted by the
Hypervisor. The intercept bit is at VMCB byte offset 10h, bit 14."
Since we don't enumerate the instruction in KVM_SUPPORTED_CPUID,
intercept it and synthesize #UD.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Drew Schmitt <dasch@google.com>
Reviewed-by: Jacob Xu <jacobhxu@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/include/asm/svm.h      | 1 +
 arch/x86/include/uapi/asm/svm.h | 1 +
 arch/x86/kvm/svm.c              | 8 ++++++++
 3 files changed, 10 insertions(+)

```
#### [kvm-unit-tests PATCH 1/1] x86: setjmp: check expected value of "i" to give better feedback
##### From: Bill Wendling <morbo@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Bill Wendling <morbo@google.com>
X-Patchwork-Id: 11153507
Return-Path: <SRS0=FKxr=XO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D3E7713BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 22:31:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B3031217D6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 22:31:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="So8jPdlG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404159AbfISWPH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Sep 2019 18:15:07 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:35382 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2406071AbfISWPH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Sep 2019 18:15:07 -0400
Received: by mail-pf1-f202.google.com with SMTP id r7so3229160pfg.2
        for <kvm@vger.kernel.org>; Thu, 19 Sep 2019 15:15:06 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=sXbhgwagHRA9ISvIc6zPNxVwv36dHM1scEFF+Wpapbg=;
        b=So8jPdlGSRnHRVjCp2bwt3RbuIXHPdOaAoJ9haGRGEsSGcfDN2R2qHlpjzSnfxw5as
         BOp4KWBf3Md5tfD03sNX8BG4AWnzaMKVQ+pEBsHdt0FndnIcxZ13Ve2Difg91Qwz688Z
         XlqpX7U/Ux02VlUfT0Ai2LvfznJbkGMOhyxz1jsFWWPryKo3IsGHoFDHOkvWO65o74nb
         u4Mf0ztR0YEZ4CBJ88xOSBYU1cGWrJshR6nhzHxls+xaN4zr9ZkupOBl4BzCe6kzuq7X
         SbkNzjL4irMwxd4+IGJvMcgaSqaUP91OBgGoaZAcM24nKX57euNSq26eDLJhL2cNOEaf
         HSYg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=sXbhgwagHRA9ISvIc6zPNxVwv36dHM1scEFF+Wpapbg=;
        b=ZYPhI07Lbyzi8TFa75mbXN9//GPSZxXpVYBu1SfSRrz5Ly6eVzuH4mMIGGeLGnG/9x
         jLSnrEm0UpQkINT+MI0KRdhOtFUsbWv0YoIMCh8hjtFh56LzvCEjN10eTeDrTIeJQ2lz
         JSBGo7r+pqkurKbPOaVD1smFig3wf1b41FcfWT6nulK+QIiBIfJOKB+ysEQ1O2d4wEAr
         0nt6VYY1Qyo0KY6SYAHDh9zqMzXxHmdBolHngurRQOh4ACENJTYDVXnTKm52Y2yWGA5a
         bA9bvTvPYRLTR6jeucHvicWL4CpeOWkwik8fWhc2klUIIv8kNzZ9VqCZvEnDkwdkDnMR
         wCIQ==
X-Gm-Message-State: APjAAAWZLSwCcf2WOayoK0RR79aWWdI5FDuZIi4SZ1Hz4EyHPst4OoBm
        glamHc3bmKXjdhr7lNjssZu1gYRurGGEm3H/Q+Ps2tcSJKXpK+tn4ldHEyvBZJkFQ2sBSTwhpBQ
        BaL90BOTgg8oXmp+31FHh3vnajRlLgENp0N3HdoT0GK7QXO7iyRGT1w==
X-Google-Smtp-Source: 
 APXvYqwIe3hvcFfOdbRemLw/Ge2iH8lV94rFOCM7gxFJHTbPnqs2t7jw/MikDEUTshHS/CPpdwTcrBAuqw==
X-Received: by 2002:a63:505:: with SMTP id 5mr11053190pgf.297.1568931305825;
 Thu, 19 Sep 2019 15:15:05 -0700 (PDT)
Date: Thu, 19 Sep 2019 15:14:53 -0700
In-Reply-To: <20190919203919.GF30495@linux.intel.com>
Message-Id: <20190919221453.130213-1-morbo@google.com>
Mime-Version: 1.0
References: <20190919203919.GF30495@linux.intel.com>
X-Mailer: git-send-email 2.23.0.351.gc4317032e6-goog
Subject: [kvm-unit-tests PATCH 1/1] x86: setjmp: check expected value of "i"
 to give better feedback
From: Bill Wendling <morbo@google.com>
To: kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        Bill Wendling <morbo@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use a list of expected values instead of printing out numbers, which
aren't very meaningful. This prints only if the expected and actual
values differ.

Signed-off-by: Bill Wendling <morbo@google.com>
---
 x86/setjmp.c | 23 +++++++++++++++--------
 1 file changed, 15 insertions(+), 8 deletions(-)

```
#### [kvm-unit-tests PATCH] kvm-unit-test: x86: Add RDPRU testFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jim Mattson <jmattson@google.com>
X-Patchwork-Id: 11153557
Return-Path: <SRS0=FKxr=XO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA3FB112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 23:02:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B867820640
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 23:02:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="FF9l9HQK"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404482AbfISXCd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Sep 2019 19:02:33 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:33060 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2390172AbfISXCd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Sep 2019 19:02:33 -0400
Received: by mail-pf1-f202.google.com with SMTP id z4so3307706pfn.0
        for <kvm@vger.kernel.org>; Thu, 19 Sep 2019 16:02:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=3dI2aAeHuXV9dcgvDwt653/mfpUM3BDLO9nXnPwcIA8=;
        b=FF9l9HQK+45Pl3gCa+8h7zVqzKPzH0YcpY1nuWQq1BaA9OdnOXDmJU7GzJNxRyXTUX
         hEll1q4qLpIcKI7D8xa1+erFRevw+Hh7Xxtt+5H/7lLW5HrQyvDTK11de/2dJKyM0cMI
         HZtCdsmqgjcKdIdQT5AkvzflQMza0CyD9TNaXuuxZlOiThy1lWzDrXbQuq9U9K8XW/cw
         6+yOwKFijnJJfOLNI8o6S2d/kKT79g5juCC6WJGyK08Fyrgs/NwjZfFTbIybM9THVAav
         n6Cw3YODmOW9Vss9Jr+AUTfG2SuWNp1epyHFfUyvCNkEjqoYyxLgdncXU6QSyrUWrqoV
         3asw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=3dI2aAeHuXV9dcgvDwt653/mfpUM3BDLO9nXnPwcIA8=;
        b=ZleBHjh9ggvlCY17lC9p3HmS+Zm98t619jW5ZMD8PryLhHDrj2/Sn2lPZ4McpfdKyT
         dvAcmIC8GQEgowjsJXlx1uodU2LSdqTcn3SER74PB8Z7iFuvEKqDc0YaQDgQPKMRCa4o
         8XVKLFyQTQdbwSoTCGO6s9Ctx0eXY91bxLiEWKjxeOnPGPB2YhMKeh/KAgXJj8Sd1XpM
         68JEOkq4OWRV5PkRWLbVKQNdXKRvwHeYYB9sYiZsx8AojQxHYQGKk4c233OU/xo8NbS6
         GYjbAOIvNGCso2oVgISmW4bfSP+G0k50q3PHUVQiVYByvsGVhIsz1/hjnBxLTbczBBG+
         bcTQ==
X-Gm-Message-State: APjAAAU55Xv3049zS5NGlIoH96UkX6blyOY2AZ3N7TWWTzlJYI1PUPhP
        cJTBqtze9QyBGdkErxdskhHaBrAkmrSeLFxZ6EkJk2HhkWgVaRzK7PNgaELTsFkiSh6n73mJuel
        PNMY+pBMknL9MV1l+6xp3+qS8Q45BfmhdcqYepEPgyFmIg7lzio5PtA0WMk4w4dA=
X-Google-Smtp-Source: 
 APXvYqxgHc7uq5o4T8efx7CKrNZfcHJJsNVHyS3s28ovcwCBU3TzR6qCjHV3cBIJpTmZWeugwrvl/mU3iZgbOA==
X-Received: by 2002:a63:1045:: with SMTP id 5mr11444857pgq.165.1568934151159;
 Thu, 19 Sep 2019 16:02:31 -0700 (PDT)
Date: Thu, 19 Sep 2019 16:02:25 -0700
Message-Id: <20190919230225.37796-1-jmattson@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.351.gc4317032e6-goog
Subject: [kvm-unit-tests PATCH] kvm-unit-test: x86: Add RDPRU test
From: Jim Mattson <jmattson@google.com>
To: kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>, Peter Shier <pshier@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Ensure that support for RDPRU is not enumerated in the guest's CPUID
and that the RDPRU instruction raises #UD.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 lib/x86/processor.h |  1 +
 x86/Makefile.x86_64 |  1 +
 x86/rdpru.c         | 23 +++++++++++++++++++++++
 x86/unittests.cfg   |  5 +++++
 4 files changed, 30 insertions(+)
 create mode 100644 x86/rdpru.c

```
#### [PATCH kvm-unit-tests 1/8] x86: vmx: Refactor init of VMX caps to separate function
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11152295
Return-Path: <SRS0=FKxr=XO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0707B13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 12:52:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D9B7821907
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 19 Sep 2019 12:52:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="NMGULGaF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390285AbfISMw4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 19 Sep 2019 08:52:56 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:57068 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389611AbfISMwz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 19 Sep 2019 08:52:55 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x8JCnNcQ192172;
        Thu, 19 Sep 2019 12:52:32 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=GPM0gON8cO+0laMNOFmmLm7oLFNmncDUeC8XuWlpioc=;
 b=NMGULGaFwdrwGO/WYqLiN0kHToX4L1DJdap9pVzlM2lM7xcp6dIsIYazagL06hxhVih0
 A418m/YawBaZvfE36z9Gf7QO2bhBL9U51w1tRviAl3qkLR8/8mV8UrwjO93vGolJjoN8
 VVHnmSghZ8lFV7ZxDS0I1jhLpHfQq7zDxAIx7SIjl1niH00o+YmXFGrG90ZJ2H0QbILK
 R8Jwvvh5NbtroLl0/SK6ywfpY3/Hbr+UVoixSAGf2O1kTLh9zCy1B+B1at7CatzX2T1w
 gAZXAj+YNUibJKvJQ/3iKMs/aiP8L554u6SRyWYBekwROd+tK1lxDLIHFLNAlgGcqG18 MQ==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 2v3vb4uqpe-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 19 Sep 2019 12:52:32 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x8JCmDTn178779;
        Thu, 19 Sep 2019 12:52:31 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by aserp3030.oracle.com with ESMTP id 2v3vbs1ke3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 19 Sep 2019 12:52:31 +0000
Received: from abhmp0011.oracle.com (abhmp0011.oracle.com [141.146.116.17])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id x8JCqUdN012185;
        Thu, 19 Sep 2019 12:52:30 GMT
Received: from spark.ravello.local (/213.57.127.2)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 19 Sep 2019 05:52:29 -0700
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Nikita Leshenko <nikita.leshchenko@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>
Subject: [PATCH kvm-unit-tests 1/8] x86: vmx: Refactor init of VMX caps to
 separate function
Date: Thu, 19 Sep 2019 15:52:04 +0300
Message-Id: <20190919125211.18152-2-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190919125211.18152-1-liran.alon@oracle.com>
References: <20190919125211.18152-1-liran.alon@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9384
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1908290000 definitions=main-1909190121
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9384
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1908290000
 definitions=main-1909190121
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is done as a preparation to future patches that will
introduce ability to run VMX on CPUs other than BSP.

Reviewed-by: Nikita Leshenko <nikita.leshchenko@oracle.com>
Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 x86/vmx.c | 30 ++++++++++++++++++------------
 1 file changed, 18 insertions(+), 12 deletions(-)

```
