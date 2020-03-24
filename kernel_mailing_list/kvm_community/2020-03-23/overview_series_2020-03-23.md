#### [PATCH] KVM: SVM: Use __packed shorthard
##### From: Borislav Petkov <bp@alien8.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Borislav Petkov <bp@alien8.de>
X-Patchwork-Id: 11452965
Return-Path: <SRS0=toc3=5I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D88D414B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 13:23:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B26D620735
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 13:23:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=alien8.de header.i=@alien8.de
 header.b="Mh0hkLpI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728380AbgCWNXY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Mar 2020 09:23:24 -0400
Received: from mail.skyhub.de ([5.9.137.197]:40558 "EHLO mail.skyhub.de"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728372AbgCWNXY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Mar 2020 09:23:24 -0400
Received: from zn.tnic (p200300EC2F04F900B1314F6DF04CED4B.dip0.t-ipconnect.de
 [IPv6:2003:ec:2f04:f900:b131:4f6d:f04c:ed4b])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.skyhub.de (SuperMail on ZX Spectrum 128k) with ESMTPSA id
 028CE1EC0C68;
        Mon, 23 Mar 2020 14:23:21 +0100 (CET)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=alien8.de; s=dkim;
        t=1584969802;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:in-reply-to:in-reply-to:
  references:references;
        bh=xW0/HOW9n0qQhxLBUQ2kpOFSlOwhGdDkXLxiBO1huwU=;
        b=Mh0hkLpItJ3GqPbFtp3Zs3wYWNJ6OyGdo9cNRHVORoSYUH3E1Y++GM6WGUkA11+ulapHcJ
        0ONe1jWO6b9GKgjTjuXcU+WiwgDLLtd59L7MWC8zWdX3CfEeB1YkEOJRimSpiK2R/QUr5M
        Q15J8b+p5WjOAtRzFfDaZsS+mbb8Rxo=
Date: Mon, 23 Mar 2020 14:23:15 +0100
From: Borislav Petkov <bp@alien8.de>
To: Joerg Roedel <joro@8bytes.org>
Cc: x86@kernel.org, hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Thomas Hellstrom <thellstrom@vmware.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        Joerg Roedel <jroedel@suse.de>
Subject: [PATCH] KVM: SVM: Use __packed shorthard
Message-ID: <20200323132315.GB4649@zn.tnic>
References: <20200319091407.1481-1-joro@8bytes.org>
 <20200319091407.1481-2-joro@8bytes.org>
MIME-Version: 1.0
Content-Disposition: inline
In-Reply-To: <20200319091407.1481-2-joro@8bytes.org>
User-Agent: Mutt/1.10.1 (2018-07-13)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I guess we can do that ontop.
---
From: Borislav Petkov <bp@suse.de>
Date: Mon, 23 Mar 2020 14:20:08 +0100

... to make it more readable.

No functional changes.

Signed-off-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/svm.h | 16 ++++++++--------
 1 file changed, 8 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: VMX: don't allow memory operands for inline asm that modifies SP
##### From: Nick Desaulniers <ndesaulniers@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nick Desaulniers <ndesaulniers@google.com>
X-Patchwork-Id: 11453731
Return-Path: <SRS0=toc3=5I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A803D1731
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 19:20:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 86C8C206F8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 19:20:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="frWZZr05"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727826AbgCWTUG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Mar 2020 15:20:06 -0400
Received: from mail-qv1-f74.google.com ([209.85.219.74]:56873 "EHLO
        mail-qv1-f74.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727179AbgCWTUG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Mar 2020 15:20:06 -0400
Received: by mail-qv1-f74.google.com with SMTP id ee5so13664597qvb.23
        for <kvm@vger.kernel.org>; Mon, 23 Mar 2020 12:20:05 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=EuEgHEvOOlLZGILEOt39luhrShhjhA+dXySCvlN5S/w=;
        b=frWZZr05u+jNrEcB3GH0499Ea350wyE93JmIJPfup0N2Iea+YPd3q6/qiz0WC7FuIP
         WBoyPuMVzyQ4O0/YDSAKhAYkgwpj2nq/kGj7IXWW8nzOpSAWmDkEmkHZBHhOdIb7x4pd
         qlvurUUNUqAF0ALylfTDWTBWNPTw17zbfsbVbCkiBao+3wRoTcRnmjsmmCReJ48hIwth
         B68OT7qccAkZcNrdsb1H/LUCmoznz/xEpUxBHTQXSMH4jktAFRqwWvBTNfrNypJtUtaF
         YcA+zNaafJAhGeMyIFSuEJaN92/9bAes2ovUyOw85AoB7NNsikFkTqC7SY5py2h97KEV
         vWNg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=EuEgHEvOOlLZGILEOt39luhrShhjhA+dXySCvlN5S/w=;
        b=atIe8vZNk1mTXfLkx2xgX4sKQTNFeuyHHTsJ2QOx2xJs3w57czyHeV1fHM0nbOnzj1
         JrDgkmYyTZ+o+SYCFwkWy1+nw3jXHKMBPXOod152Dk4IMWFlrRooTGPgd1MWhvJ7EXxT
         Ox+mGLjqJzPNeIfl/XPH08jAS94lWFU7nBi/xg/jMlIQjfEcwz4V1lp4rpfZjMIr3izA
         VcAjiIQ1wYZIGsR+sdt/GfbhNUjA6sz+2WWShVwztSlhR6B5WOiMYVlPtHrmeTIFOXAM
         LG8rz7Gba8KKWyfDPBeIR6ksvA0op5h+XrCAIDS0kkYjQn52b1Xb+Q8uSUf4/RKtEwDJ
         uARw==
X-Gm-Message-State: ANhLgQ1Cb6t66na2xMAsPwig0lxKrIn8qTsV+wG64cEmhlOQknQNFcNc
        pLW+0QxYbs4YOrelBuWa3/WIlpuiVO08dN1nTqM=
X-Google-Smtp-Source: 
 ADFU+vvHiSEJBBT42wVNqrw/x1QVUgfHCyw0l5oYHfNcWj0WqOy/M8fE1DC3Ojv4iFuGiQeAk5S8n+b6TA1pOtTBh1A=
X-Received: by 2002:a0c:fd85:: with SMTP id p5mr6095302qvr.205.1584991205290;
 Mon, 23 Mar 2020 12:20:05 -0700 (PDT)
Date: Mon, 23 Mar 2020 12:12:43 -0700
In-Reply-To: 
 <CAKwvOdn10Ts_AU6i+7toj7NkMwK-+0yr5wTrN0XEDudBWS0sPQ@mail.gmail.com>
Message-Id: <20200323191243.30002-1-ndesaulniers@google.com>
Mime-Version: 1.0
References: 
 <CAKwvOdn10Ts_AU6i+7toj7NkMwK-+0yr5wTrN0XEDudBWS0sPQ@mail.gmail.com>
X-Mailer: git-send-email 2.25.1.696.g5e7596f4ac-goog
Subject: [PATCH] KVM: VMX: don't allow memory operands for inline asm that
 modifies SP
From: Nick Desaulniers <ndesaulniers@google.com>
To: pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: ndesaulniers@google.com, bp@alien8.de,
        clang-built-linux@googlegroups.com, dvyukov@google.com,
        glider@google.com, hpa@zytor.com, jmattson@google.com,
        joro@8bytes.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        mingo@redhat.com,
        syzbot+3f29ca2efb056a761e38@syzkaller.appspotmail.com,
        syzkaller-bugs@googlegroups.com, tglx@linutronix.de,
        vkuznets@redhat.com, wanpengli@tencent.com, x86@kernel.org
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

THUNK_TARGET defines [thunk_target] as having "rm" input constraints
when CONFIG_RETPOLINE is not set, which isn't constrained enough for
this specific case.

For inline assembly that modifies the stack pointer before using this
input, the underspecification of constraints is dangerous, and results
in an indirect call to a previously pushed flags register.

In this case `entry`'s stack slot is good enough to satisfy the "m"
constraint in "rm", but the inline assembly in
handle_external_interrupt_irqoff() modifies the stack pointer via
push+pushf before using this input, which in this case results in
calling what was the previous state of the flags register, rather than
`entry`.

Be more specific in the constraints by requiring `entry` be in a
register, and not a memory operand.

Reported-by: Dmitry Vyukov <dvyukov@google.com>
Reported-by: syzbot+3f29ca2efb056a761e38@syzkaller.appspotmail.com
Debugged-by: Alexander Potapenko <glider@google.com>
Debugged-by: Paolo Bonzini <pbonzini@redhat.com>
Debugged-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Nick Desaulniers <ndesaulniers@google.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Expose fast short REP MOV for supported cpuid
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenyu Wang <zhenyuw@linux.intel.com>
X-Patchwork-Id: 11452511
Return-Path: <SRS0=toc3=5I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ACA9192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 09:22:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 959282077D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 09:22:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727724AbgCWJWj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Mar 2020 05:22:39 -0400
Received: from mga06.intel.com ([134.134.136.31]:24184 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727669AbgCWJWj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Mar 2020 05:22:39 -0400
IronPort-SDR: 
 k80O12gl9ZmleMzebJ7i65jnN96s7xZtTZ6/oBwxLOOsqPTDJF21i67WIrCbJzEDGXLse9DqjI
 Br8ZJIXwcoAA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 23 Mar 2020 02:22:37 -0700
IronPort-SDR: 
 RhJ5hieVCYUCJbFJYb6x+p0rqKHXTvL9ZT8VPk037JG8vrByh6vuzmSJlQU9YtVSol7DT0me2B
 mTsK+GRcwg/g==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,295,1580803200";
   d="scan'208";a="445744294"
Received: from jieliu-mobl1.ccr.corp.intel.com (HELO
 dell-xps.ccr.corp.intel.com) ([10.255.31.30])
  by fmsmga005.fm.intel.com with ESMTP; 23 Mar 2020 02:22:36 -0700
From: Zhenyu Wang <zhenyuw@linux.intel.com>
To: pbonzini@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: Expose fast short REP MOV for supported cpuid
Date: Mon, 23 Mar 2020 17:22:36 +0800
Message-Id: <20200323092236.3703-1-zhenyuw@linux.intel.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

For CPU supporting fast short REP MOV (XF86_FEATURE_FSRM) e.g Icelake,
Tigerlake, expose it in KVM supported cpuid as well.

Signed-off-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/3] target/i386: Rename CORE_CAPABILITY to CORE_CAPABILITIES
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11452221
Return-Path: <SRS0=toc3=5I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1E4617D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 03:14:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8BBBA20732
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 03:14:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727063AbgCWDOl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 22 Mar 2020 23:14:41 -0400
Received: from mga11.intel.com ([192.55.52.93]:48945 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726979AbgCWDOl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 22 Mar 2020 23:14:41 -0400
IronPort-SDR: 
 nR0e1RPjKV7of4bnnfQqMSE+M0HdX+E54ZY0Z7uOoQ8bE+GTVmvXXBzq4TU2zrPYDczozlOT7a
 aQ88ds83WkHg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 22 Mar 2020 20:14:40 -0700
IronPort-SDR: 
 pRX5EL3s7jKlUC0DyiWxWVCif4V9kHdzoAikBRqVPuPVWdDrntlbDIQIGRJvr185g3LRvS86fT
 K8iiw9uLqCUQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,294,1580803200";
   d="scan'208";a="292453683"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.161])
  by FMSMGA003.fm.intel.com with ESMTP; 22 Mar 2020 20:14:38 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Eduardo Habkost <ehabkost@redhat.com>
Cc: kvm@vger.kernel.org, qemu-devel@nongnu.org,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH 1/3] target/i386: Rename CORE_CAPABILITY to CORE_CAPABILITIES
Date: Mon, 23 Mar 2020 10:56:56 +0800
Message-Id: <20200323025658.4540-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200323025658.4540-1-xiaoyao.li@intel.com>
References: <20200323025658.4540-1-xiaoyao.li@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel SDM updates the name of MSR CORE_CAPABILITY to CORE_CAPABILITIES,
so updating it QEMU.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 target/i386/cpu.c | 12 ++++++------
 target/i386/cpu.h |  6 +++---
 target/i386/kvm.c |  6 +++---
 3 files changed, 12 insertions(+), 12 deletions(-)

```
#### [PATCH kernel v2 1/7] powerpc/powernv/ioda: Move TCE bypass base to PE
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexey Kardashevskiy <aik@ozlabs.ru>
X-Patchwork-Id: 11452427
Return-Path: <SRS0=toc3=5I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B57C015AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 08:01:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8760520736
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Mar 2020 08:01:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727511AbgCWIBB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Mar 2020 04:01:01 -0400
Received: from 107-174-27-60-host.colocrossing.com ([107.174.27.60]:50654
 "EHLO
        ozlabs.ru" rhost-flags-OK-FAIL-OK-OK) by vger.kernel.org with ESMTP
        id S1727505AbgCWIBB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Mar 2020 04:01:01 -0400
Received: from fstn1-p1.ozlabs.ibm.com (localhost [IPv6:::1])
        by ozlabs.ru (Postfix) with ESMTP id D46A5AE80062;
        Mon, 23 Mar 2020 03:52:17 -0400 (EDT)
From: Alexey Kardashevskiy <aik@ozlabs.ru>
To: linuxppc-dev@lists.ozlabs.org
Cc: David Gibson <david@gibson.dropbear.id.au>,
        kvm-ppc@vger.kernel.org, kvm@vger.kernel.org,
        Alistair Popple <alistair@popple.id.au>,
        Fabiano Rosas <farosas@linux.ibm.com>,
        Alexey Kardashevskiy <aik@ozlabs.ru>
Subject: [PATCH kernel v2 1/7] powerpc/powernv/ioda: Move TCE bypass base to
 PE
Date: Mon, 23 Mar 2020 18:53:48 +1100
Message-Id: <20200323075354.93825-2-aik@ozlabs.ru>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200323075354.93825-1-aik@ozlabs.ru>
References: <20200323075354.93825-1-aik@ozlabs.ru>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We are about to allow another location for the second DMA window and
we will need to advertise it outside of the powernv platform code.

This moves bypass base address to iommu_table_group so drivers such as
VFIO SPAPR TCE can see it.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
 arch/powerpc/include/asm/iommu.h          |  1 +
 arch/powerpc/platforms/powernv/pci.h      |  1 -
 arch/powerpc/platforms/powernv/npu-dma.c  |  1 +
 arch/powerpc/platforms/powernv/pci-ioda.c | 26 ++++++++++-------------
 4 files changed, 13 insertions(+), 16 deletions(-)

```
#### [PATCH 1/9] vfio/fsl-mc: Add VFIO framework skeleton for fsl-mc devices
##### From: Diana Craciun <diana.craciun@oss.nxp.com>

```c
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Bharat Bhushan <Bharat.Bhushan@nxp.com>

DPAA2 (Data Path Acceleration Architecture) consists in
mechanisms for processing Ethernet packets, queue management,
accelerators, etc.

The Management Complex (mc) is a hardware entity that manages the DPAA2
hardware resources. It provides an object-based abstraction for software
drivers to use the DPAA2 hardware. The MC mediates operations such as
create, discover, destroy of DPAA2 objects.
The MC provides memory-mapped I/O command interfaces (MC portals) which
DPAA2 software drivers use to operate on DPAA2 objects.

A DPRC is a container object that holds other types of DPAA2 objects.
Each object in the DPRC is a Linux device and bound to a driver.
The MC-bus driver is a platform driver (different from PCI or platform
bus). The DPRC driver does runtime management of a bus instance. It
performs the initial scan of the DPRC and handles changes in the DPRC
configuration (adding/removing objects).

All objects inside a container share the same hardware isolation
context, meaning that only an entire DPRC can be assigned to
a virtual machine.
When a container is assigned to a virtual machine, all the objects
within that container are assigned to that virtual machine.
The DPRC container assigned to the virtual machine is not allowed
to change contents (add/remove objects) by the guest. The restriction
is set by the host and enforced by the mc hardware.

The DPAA2 objects can be directly assigned to the guest. However
the MC portals (the memory mapped command interface to the MC) need
to be emulated because there are commands that configure the
interrupts and the isolation IDs which are virtual in the guest.

Example:
echo vfio-fsl-mc > /sys/bus/fsl-mc/devices/dprc.2/driver_override
echo dprc.2 > /sys/bus/fsl-mc/drivers/vfio-fsl-mc/bind

The dprc.2 is bound to the VFIO driver and all the objects within
dprc.2 are going to be bound to the VFIO driver.

This patch adds the infrastructure for VFIO support for fsl-mc
devices. Subsequent patches will add support for binding and secure
assigning these devices using VFIO.

More details about the DPAA2 objects can be found here:
Documentation/networking/device_drivers/freescale/dpaa2/overview.rst

Signed-off-by: Bharat Bhushan <Bharat.Bhushan@nxp.com>
Signed-off-by: Diana Craciun <diana.craciun@oss.nxp.com>
---
 MAINTAINERS                               |   6 +
 drivers/vfio/Kconfig                      |   1 +
 drivers/vfio/Makefile                     |   1 +
 drivers/vfio/fsl-mc/Kconfig               |   9 ++
 drivers/vfio/fsl-mc/Makefile              |   2 +
 drivers/vfio/fsl-mc/vfio_fsl_mc.c         | 161 ++++++++++++++++++++++
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h |  14 ++
 include/uapi/linux/vfio.h                 |   1 +
 8 files changed, 195 insertions(+)
 create mode 100644 drivers/vfio/fsl-mc/Kconfig
 create mode 100644 drivers/vfio/fsl-mc/Makefile
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc.c
 create mode 100644 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h

```
