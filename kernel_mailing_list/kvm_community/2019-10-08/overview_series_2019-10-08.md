#### [PATCH v2 1/5] KVM: arm64: pmu: Fix cycle counter truncation
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11179817
Return-Path: <SRS0=25+t=YB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B878214DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 16:01:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9A31620815
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 16:01:57 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1570550517;
	bh=V53P7Vn0aPiKYwrOMap7wcByveXMeM32VmJKA4bI76s=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=JE4xlvTyRdquKnep0SfVqS2wW06ouKxuH6NqrtCBxFIKt7wS1lEbA+GwkZB1snsrG
	 L5glHbmxLbjZmMGzW3r2aesUixvCgLlI243NqZmUxQZZ+veqph/x14oI3hgvV099KI
	 V6zFv3mP4YSI5w1TECaf8FQKaj7Mh98BbBnnfdSE=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728352AbfJHQB4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Oct 2019 12:01:56 -0400
Received: from inca-roads.misterjones.org ([213.251.177.50]:34689 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728081AbfJHQB4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 8 Oct 2019 12:01:56 -0400
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iHrvs-0001rs-VO; Tue, 08 Oct 2019 18:01:53 +0200
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Andrew Murray <andrew.murray@arm.com>
Subject: [PATCH v2 1/5] KVM: arm64: pmu: Fix cycle counter truncation
Date: Tue,  8 Oct 2019 17:01:24 +0100
Message-Id: <20191008160128.8872-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191008160128.8872-1-maz@kernel.org>
References: <20191008160128.8872-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, will@kernel.org,
 mark.rutland@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, andrew.murray@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a counter is disabled, its value is sampled before the event
is being disabled, and the value written back in the shadow register.

In that process, the value gets truncated to 32bit, which is adequate
for any counter but the cycle counter (defined as a 64bit counter).

This obviously results in a corrupted counter, and things like
"perf record -e cycles" not working at all when run in a guest...
A similar, but less critical bug exists in kvm_pmu_get_counter_value.

Make the truncation conditional on the counter not being the cycle
counter, which results in a minor code reorganisation.

Fixes: 80f393a23be6 ("KVM: arm/arm64: Support chained PMU counters")
Reviewed-by: Andrew Murray <andrew.murray@arm.com>
Reported-by: Julien Thierry <julien.thierry.kdev@gmail.com>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/arm/pmu.c | 22 ++++++++++++----------
 1 file changed, 12 insertions(+), 10 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: svm: run svm.flat unit tests with -cpu host
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11179877
Return-Path: <SRS0=25+t=YB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 31CD0139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 16:38:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1C67120815
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 16:38:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727691AbfJHQid (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Oct 2019 12:38:33 -0400
Received: from mx1.redhat.com ([209.132.183.28]:48924 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726320AbfJHQid (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Oct 2019 12:38:33 -0400
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id E0CEB80F7C;
        Tue,  8 Oct 2019 16:38:32 +0000 (UTC)
Received: from vitty.brq.redhat.com (ovpn-204-35.brq.redhat.com
 [10.40.204.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 6FAFA5C1D4;
        Tue,  8 Oct 2019 16:38:31 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, Jack Wang <jack.wang.usish@gmail.com>,
        Nadav Amit <nadav.amit@gmail.com>
Subject: [PATCH kvm-unit-tests] x86: svm: run svm.flat unit tests with -cpu
 host
Date: Tue,  8 Oct 2019 18:38:29 +0200
Message-Id: <20191008163829.1003-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.27]);
 Tue, 08 Oct 2019 16:38:32 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

With -cpu qemu64 we skip many good tests (next_rip, npt_*) and
tsc_adjust is failing. VMX tests already use '-cpu host'.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 x86/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC PATCH] mm: set memory section offline when all its pages are offline.
##### From: lantianyu1986@gmail.com

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tianyu Lan <lantianyu1986@gmail.com>
X-Patchwork-Id: 11179691
Return-Path: <SRS0=25+t=YB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC8261575
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 14:37:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BF26F2173B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 14:37:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="mz4tTuSo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725953AbfJHOhH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Oct 2019 10:37:07 -0400
Received: from mail-pg1-f196.google.com ([209.85.215.196]:40258 "EHLO
        mail-pg1-f196.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725795AbfJHOhH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Oct 2019 10:37:07 -0400
Received: by mail-pg1-f196.google.com with SMTP id d26so10348098pgl.7;
        Tue, 08 Oct 2019 07:37:06 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=/LkLNZyXllVODaNA4v6SjRbRTQO3k0FhwJL3ACT+pc8=;
        b=mz4tTuSopA61Uk2c4cwTxPD1ttgQPVt23a8s2ab5wZNvSsN58+xofcbe8p2AlOqMvb
         q0ClxaWzdCAX/ZztkYIusI1VP7spYpRsUEOay6if9370EKjvHasB+I5mypjmn9UPxdYJ
         4nCJ0s1uvUBHMfthAvg+E+SrYLAfbZwlB+3K/THlXoNXtIuQf3UBLxuGPnnpoSZO0TRh
         /4pEiyVn8CBlYUBVgJloR5A405qAtMBHasSYUesTHSYrn7qfIqt9AihFG2SMmHG0J6jj
         7BIY5SQiUQvIAUaGSCYbHkSsTWihgp/2ggOh3m7dISP6JA9Q7Jyy5LXLyFjyRjSpxWih
         R/og==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=/LkLNZyXllVODaNA4v6SjRbRTQO3k0FhwJL3ACT+pc8=;
        b=iWDSQd7LYvFcCOdYNpSrHvSp3VsY4rAGISEYANchJIgLL69QRHv2/YTE+ZGay6JQuo
         CtZHjnCBvvTGO6qcuCnSwLNPOYupVOYsi4lMwTbUUsQDh0iK3Sd++nVb8wdZQkBa7XUu
         AjCeCDZmvpHflVW/x/ot62Nf9AfCEx5RNNxUIAR5Yj+2vgRKvOvfdjSHAJprqJY2vdK1
         7lziHxp5rUfJrmYVqjSs66q8CSPp4HPo722PSalV/UfPULAvXSkc7MymA9WKO8udu4IA
         sCPSZFZU+MkrtrSJApGBkzzkJESIN4DXDihCig6eeEsmxPE3ZHyHcpLpmbimiQDEq9oN
         affw==
X-Gm-Message-State: APjAAAVo5px36GXSMEkd1IHz5oikgkWsBSkLQgNtggqy29zWjYwjmqio
        cwWEBpNsnxSNZmjbMiNcryY=
X-Google-Smtp-Source: 
 APXvYqzVmLYxVnf7lMb8Y0OcU8us4+UeXkrqpUjxJeb+iLiGDzZdEaRy3btAdo69l4i1EIElQVrmLw==
X-Received: by 2002:a63:a48:: with SMTP id z8mr19160809pgk.328.1570545426091;
        Tue, 08 Oct 2019 07:37:06 -0700 (PDT)
Received: from localhost.corp.microsoft.com ([167.220.255.39])
        by smtp.googlemail.com with ESMTPSA id
 74sm20603109pfy.78.2019.10.08.07.36.55
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Tue, 08 Oct 2019 07:37:05 -0700 (PDT)
From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
To: pbonzini@redhat.com, rkrcmar@redhat.com, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, hpa@zytor.com, x86@kernel.org,
        dave.hansen@linux.intel.com, luto@kernel.org, peterz@infradead.org,
        kys@microsoft.com, haiyangz@microsoft.com, sthemmin@microsoft.com,
        sashal@kernel.org, akpm@linux-foundation.org, rppt@linux.ibm.com,
        jgross@suse.com, mhocko@suse.com, paul.burton@mips.com,
        m.mizuma@jp.fujitsu.com, huang.zijiang@zte.com.cn,
        karahmed@amazon.de, dan.j.williams@intel.com, bhelgaas@google.com,
        osalvador@suse.de, rdunlap@infradead.org,
        richardw.yang@linux.intel.com, david@redhat.com,
        pavel.tatashin@microsoft.com, cai@lca.pw, arunks@codeaurora.org,
        vbabka@suse.cz, mgorman@techsingularity.net,
        alexander.h.duyck@linux.intel.com, glider@google.com,
        logang@deltatee.com, bsingharora@gmail.com, bhe@redhat.com,
        Tianyu.Lan@microsoft.com, michael.h.kelley@microsoft.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-hyperv@vger.kernel.org, linux-mm@kvack.org,
        vkuznets@redhat.com
Subject: [RFC PATCH] mm: set memory section offline when all its pages are
 offline.
Date: Tue,  8 Oct 2019 22:36:48 +0800
Message-Id: <20191008143648.11882-1-Tianyu.Lan@microsoft.com>
X-Mailer: git-send-email 2.14.5
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tianyu Lan <Tianyu.Lan@microsoft.com>

If size of offline memory region passed to offline_pages() is
not aligned with PAGES_PER_SECTION, memory section will be set
to offline in the offline_mem_sections() with some pages of
memory section online. Fix it, Update memory section status after
marking offline pages as "reserved" in __offline_isolated_pages()
and check all pages in memory are reserved or not before setting
memory section offline.

Signed-off-by: Tianyu Lan <Tianyu.Lan@microsoft.com>
---
This patch is to prepare for hot remove memory function in Hyper-V
balloon driver. It requests to offline memory with random size.
---
 mm/page_alloc.c |  3 ++-
 mm/sparse.c     | 10 ++++++++++
 2 files changed, 12 insertions(+), 1 deletion(-)

```
#### [PATCH RFC] selftests: kvm: fix sync_regs_test with newer gccs
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11179737
Return-Path: <SRS0=25+t=YB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AD7101709
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 14:57:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9838B21871
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 14:57:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727695AbfJHO5U (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Oct 2019 10:57:20 -0400
Received: from mx1.redhat.com ([209.132.183.28]:55290 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725939AbfJHO5U (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Oct 2019 10:57:20 -0400
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id CC763300C22E;
        Tue,  8 Oct 2019 14:57:19 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.43.2.155])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 7B4C419C69;
        Tue,  8 Oct 2019 14:57:18 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH RFC] selftests: kvm: fix sync_regs_test with newer gccs
Date: Tue,  8 Oct 2019 16:57:17 +0200
Message-Id: <20191008145717.17841-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.47]);
 Tue, 08 Oct 2019 14:57:19 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 204c91eff798a ("KVM: selftests: do not blindly clobber registers in
 guest asm") was intended to make test more gcc-proof, however, the result
is exactly the opposite: on newer gccs (e.g. 8.2.1)  the test breaks with

==== Test Assertion Failure ====
  x86_64/sync_regs_test.c:168: run->s.regs.regs.rbx == 0xBAD1DEA + 1
  pid=14170 tid=14170 - Invalid argument
     1	0x00000000004015b3: main at sync_regs_test.c:166 (discriminator 6)
     2	0x00007f413fb66412: ?? ??:0
     3	0x000000000040191d: _start at ??:?
  rbx sync regs value incorrect 0x1.

Disassembly show the following:

00000000004019e0 <guest_code>:
  4019e0:       55                      push   %rbp
  4019e1:       89 dd                   mov    %ebx,%ebp
  4019e3:       53                      push   %rbx
  4019e4:       48 83 ec 08             sub    $0x8,%rsp
  4019e8:       0f 1f 84 00 00 00 00    nopl   0x0(%rax,%rax,1)
  4019ef:       00
  4019f0:       31 c9                   xor    %ecx,%ecx
  4019f2:       ba 10 90 40 00          mov    $0x409010,%edx
  4019f7:       be 02 00 00 00          mov    $0x2,%esi
  4019fc:       31 c0                   xor    %eax,%eax
  4019fe:       bf 01 00 00 00          mov    $0x1,%edi
  401a03:       83 c5 01                add    $0x1,%ebp
  401a06:       e8 15 2b 00 00          callq  404520 <ucall>
  401a0b:       89 eb                   mov    %ebp,%ebx
  401a0d:       eb e1                   jmp    4019f0 <guest_code+0x10>
  401a0f:       90                      nop

and apparently this is broken. If we add 'volatile' qualifier to 'stage'
we get the following code:

00000000004019e0 <guest_code>:
  4019e0:       53                      push   %rbx
  4019e1:       0f 1f 80 00 00 00 00    nopl   0x0(%rax)
  4019e8:       31 c9                   xor    %ecx,%ecx
  4019ea:       ba 10 90 40 00          mov    $0x409010,%edx
  4019ef:       be 02 00 00 00          mov    $0x2,%esi
  4019f4:       31 c0                   xor    %eax,%eax
  4019f6:       bf 01 00 00 00          mov    $0x1,%edi
  4019fb:       83 c3 01                add    $0x1,%ebx
  4019fe:       e8 1d 2b 00 00          callq  404520 <ucall>
  401a03:       eb e3                   jmp    4019e8 <guest_code+0x8>
  401a05:       66 66 2e 0f 1f 84 00    data16 nopw %cs:0x0(%rax,%rax,1)
  401a0c:       00 00 00 00

and everything seems to work. The only problem is that I now get a new
warning from gcc:

x86_64/sync_regs_test.c: In function ‘guest_code’:
x86_64/sync_regs_test.c:25:6: warning: optimization may eliminate reads
 and/or writes to register variables [-Wvolatile-register-var]

checkpatch.pl doesn't like me either:

"WARNING: Use of volatile is usually wrong: see
 Documentation/process/volatile-considered-harmful.rst"

I can think of an 'ultimate' solution to open code ucall() in a single
asm block making sure the register we need is preserved but this looks
like an overkill.

Fixes: 204c91eff798a ("KVM: selftests: do not blindly clobber registers in guest asm")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/x86_64/sync_regs_test.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] selftests: kvm: fix sync_regs_test with newer gccs
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11180009
Return-Path: <SRS0=25+t=YB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6EADB14DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 18:08:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 531F121871
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 18:08:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729750AbfJHSIM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Oct 2019 14:08:12 -0400
Received: from mx1.redhat.com ([209.132.183.28]:41808 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726138AbfJHSIM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Oct 2019 14:08:12 -0400
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 064547BDD2;
        Tue,  8 Oct 2019 18:08:12 +0000 (UTC)
Received: from vitty.brq.redhat.com (ovpn-204-35.brq.redhat.com
 [10.40.204.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 24EBD60BE0;
        Tue,  8 Oct 2019 18:08:09 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH] selftests: kvm: fix sync_regs_test with newer gccs
Date: Tue,  8 Oct 2019 20:08:08 +0200
Message-Id: <20191008180808.14181-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.26]);
 Tue, 08 Oct 2019 18:08:12 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 204c91eff798a ("KVM: selftests: do not blindly clobber registers in
 guest asm") was intended to make test more gcc-proof, however, the result
is exactly the opposite: on newer gccs (e.g. 8.2.1) the test breaks with

==== Test Assertion Failure ====
  x86_64/sync_regs_test.c:168: run->s.regs.regs.rbx == 0xBAD1DEA + 1
  pid=14170 tid=14170 - Invalid argument
     1	0x00000000004015b3: main at sync_regs_test.c:166 (discriminator 6)
     2	0x00007f413fb66412: ?? ??:0
     3	0x000000000040191d: _start at ??:?
  rbx sync regs value incorrect 0x1.

Apparently, compile is still free to play games with registers even
when they have variables attaches.

Re-write guest code with 'asm volatile' by embedding ucall there and
making sure rbx is preserved.

Fixes: 204c91eff798a ("KVM: selftests: do not blindly clobber registers in guest asm")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 .../selftests/kvm/x86_64/sync_regs_test.c     | 21 ++++++++++---------
 1 file changed, 11 insertions(+), 10 deletions(-)

```
#### [PATCH 1/3] selftests: kvm: vmx_set_nested_state_test: don't check for VMX support twice
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11180043
Return-Path: <SRS0=25+t=YB=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6EA4F1709
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 19:43:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 58A4A21721
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  8 Oct 2019 19:43:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730549AbfJHTno (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 8 Oct 2019 15:43:44 -0400
Received: from mx1.redhat.com ([209.132.183.28]:48104 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728465AbfJHTno (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 8 Oct 2019 15:43:44 -0400
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 4955C10C0946;
        Tue,  8 Oct 2019 19:43:44 +0000 (UTC)
Received: from vitty.brq.redhat.com (ovpn-204-92.brq.redhat.com
 [10.40.204.92])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 77E595D6A7;
        Tue,  8 Oct 2019 19:43:42 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH 1/3] selftests: kvm: vmx_set_nested_state_test: don't check
 for VMX support twice
Date: Tue,  8 Oct 2019 21:43:36 +0200
Message-Id: <20191008194338.24159-2-vkuznets@redhat.com>
In-Reply-To: <20191008194338.24159-1-vkuznets@redhat.com>
References: <20191008194338.24159-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.66]);
 Tue, 08 Oct 2019 19:43:44 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmx_set_nested_state_test() checks if VMX is supported twice: in the very
beginning (and skips the whole test if it's not) and before doing
test_vmx_nested_state(). One should be enough.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 .../selftests/kvm/x86_64/vmx_set_nested_state_test.c       | 7 +------
 1 file changed, 1 insertion(+), 6 deletions(-)

```
