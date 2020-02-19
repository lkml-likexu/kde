#### [PATCH] KVM: apic: rename apic_lvt_vector and apic_lvt_enabled
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11387801
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D7BAE930
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 03:15:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C23EB215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 03:15:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726327AbgBRDPk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 22:15:40 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:10198 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726237AbgBRDPk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Feb 2020 22:15:40 -0500
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 4B052C1E9CC183D1A83D;
        Tue, 18 Feb 2020 11:15:37 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS410-HUB.china.huawei.com
 (10.3.19.210) with Microsoft SMTP Server id 14.3.439.0; Tue, 18 Feb 2020
 11:15:29 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: apic: rename apic_lvt_vector and apic_lvt_enabled
Date: Tue, 18 Feb 2020 11:17:05 +0800
Message-ID: <1581995825-11239-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

As the func apic_lvt_enabled() is only used once with APIC_LVTT as the
second argument, we can eliminate the argument and hardcode lvt_type as
APIC_LVTT. And also rename apic_lvt_enabled() to apic_lvtt_enabled() to
indicates it's used for APIC_LVTT only. Similar as apic_lvt_vector().

Suggested-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/lapic.c | 13 ++++++-------
 1 file changed, 6 insertions(+), 7 deletions(-)

```
#### [PATCH v6 01/22] KVM: x86: Allocate new rmap and large page tracking when moving memslot
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11389661
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ADCDC159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 21:09:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 988FD2464E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 21:09:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727901AbgBRVJb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 16:09:31 -0500
Received: from mga07.intel.com ([134.134.136.100]:6395 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726339AbgBRVHq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 16:07:46 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Feb 2020 13:07:44 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,457,1574150400";
   d="scan'208";a="253856393"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga002.jf.intel.com with ESMTP; 18 Feb 2020 13:07:44 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Janosch Frank <frankja@linux.ibm.com>, David Hildenbrand <david@redhat.com>,
 Cornelia Huck <cohuck@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Marc Zyngier <maz@kernel.org>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, linux-mips@vger.kernel.org,
 kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 linux-kernel@vger.kernel.org, Christoffer Dall <christoffer.dall@arm.com>,
 Peter Xu <peterx@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH v6 01/22] KVM: x86: Allocate new rmap and large page tracking
 when moving memslot
Date: Tue, 18 Feb 2020 13:07:15 -0800
Message-Id: <20200218210736.16432-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200218210736.16432-1-sean.j.christopherson@intel.com>
References: <20200218210736.16432-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reallocate a rmap array and recalcuate large page compatibility when
moving an existing memslot to correctly handle the alignment properties
of the new memslot.  The number of rmap entries required at each level
is dependent on the alignment of the memslot's base gfn with respect to
that level, e.g. moving a large-page aligned memslot so that it becomes
unaligned will increase the number of rmap entries needed at the now
unaligned level.

Not updating the rmap array is the most obvious bug, as KVM accesses
garbage data beyond the end of the rmap.  KVM interprets the bad data as
pointers, leading to non-canonical #GPs, unexpected #PFs, etc...

  general protection fault: 0000 [#1] SMP
  CPU: 0 PID: 1909 Comm: move_memory_reg Not tainted 5.4.0-rc7+ #139
  Hardware name: QEMU Standard PC (Q35 + ICH9, 2009), BIOS 0.0.0 02/06/2015
  RIP: 0010:rmap_get_first+0x37/0x50 [kvm]
  Code: <48> 8b 3b 48 85 ff 74 ec e8 6c f4 ff ff 85 c0 74 e3 48 89 d8 5b c3
  RSP: 0018:ffffc9000021bbc8 EFLAGS: 00010246
  RAX: ffff00617461642e RBX: ffff00617461642e RCX: 0000000000000012
  RDX: ffff88827400f568 RSI: ffffc9000021bbe0 RDI: ffff88827400f570
  RBP: 0010000000000000 R08: ffffc9000021bd00 R09: ffffc9000021bda8
  R10: ffffc9000021bc48 R11: 0000000000000000 R12: 0030000000000000
  R13: 0000000000000000 R14: ffff88827427d700 R15: ffffc9000021bce8
  FS:  00007f7eda014700(0000) GS:ffff888277a00000(0000) knlGS:0000000000000000
  CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
  CR2: 00007f7ed9216ff8 CR3: 0000000274391003 CR4: 0000000000162eb0
  Call Trace:
   kvm_mmu_slot_set_dirty+0xa1/0x150 [kvm]
   __kvm_set_memory_region.part.64+0x559/0x960 [kvm]
   kvm_set_memory_region+0x45/0x60 [kvm]
   kvm_vm_ioctl+0x30f/0x920 [kvm]
   do_vfs_ioctl+0xa1/0x620
   ksys_ioctl+0x66/0x70
   __x64_sys_ioctl+0x16/0x20
   do_syscall_64+0x4c/0x170
   entry_SYSCALL_64_after_hwframe+0x44/0xa9
  RIP: 0033:0x7f7ed9911f47
  Code: <48> 3d 01 f0 ff ff 73 01 c3 48 8b 0d 21 6f 2c 00 f7 d8 64 89 01 48
  RSP: 002b:00007ffc00937498 EFLAGS: 00000246 ORIG_RAX: 0000000000000010
  RAX: ffffffffffffffda RBX: 0000000001ab0010 RCX: 00007f7ed9911f47
  RDX: 0000000001ab1350 RSI: 000000004020ae46 RDI: 0000000000000004
  RBP: 000000000000000a R08: 0000000000000000 R09: 00007f7ed9214700
  R10: 00007f7ed92149d0 R11: 0000000000000246 R12: 00000000bffff000
  R13: 0000000000000003 R14: 00007f7ed9215000 R15: 0000000000000000
  Modules linked in: kvm_intel kvm irqbypass
  ---[ end trace 0c5f570b3358ca89 ]---

The disallow_lpage tracking is more subtle.  Failure to update results
in KVM creating large pages when it shouldn't, either due to stale data
or again due to indexing beyond the end of the metadata arrays, which
can lead to memory corruption and/or leaking data to guest/userspace.

Note, the arrays for the old memslot are freed by the unconditional call
to kvm_free_memslot() in __kvm_set_memory_region().

Fixes: 05da45583de9b ("KVM: MMU: large page support")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH] KVM: LAPIC: Recalculate apic map in batch
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11388213
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B4B181580
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 10:49:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 841CF2464E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 10:49:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="E+2uQ4ni"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726391AbgBRKtw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 05:49:52 -0500
Received: from mail-pj1-f66.google.com ([209.85.216.66]:53635 "EHLO
        mail-pj1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726327AbgBRKtw (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 05:49:52 -0500
Received: by mail-pj1-f66.google.com with SMTP id n96so852541pjc.3;
        Tue, 18 Feb 2020 02:49:51 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=ZwXivltq9VoAXejggh89BFZy9ScZgEpF2WpWI6wMpU4=;
        b=E+2uQ4nijbX4BFETPvwXHMwdxG8LYJFauYq3EJKmOCb3TWx/c43SiQ/f09MQNBcseS
         2VP85i7A+rv4n6lObhzePOJi8fcwjWd0igNNVbzFM1h0fdZ6p+jvp75MCL1Y2wqcLQn5
         UBGKW+CVigvmhxi7LXKI1wlTtnmz6GfAlkfGNbx9RkKkn3KbdxRjTfWy5UPcgEpgc3XX
         8bjiLUqpb7evaoO1Ha1ByBubL+mPRiRK94BKJ1dMGHTUUg0STtVe+dp3lRzbQiY2oS/S
         Xzbbcf+ppAQEHOwnBTU7z0aCJcfRg/rlbgeBEtEQk8C+O76u+foq5YEgIxDLGKfAH/5g
         3VhQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=ZwXivltq9VoAXejggh89BFZy9ScZgEpF2WpWI6wMpU4=;
        b=la5Nu0x909fvDLZ6Pz1NNcChpjfAUYY0tTIpGGLyA+LnzAwHKBF+68SfgHqj8px5VB
         Gk6RUrxkVTxeyAA7WEknasevANjyCER6nWV/7HRXVXoLG7HNTuCSHS9sSeps7d13rpoC
         wL28YeLlFEE6ulYtSA+F3mPQXXReNXYF5gFjsLbLj/GMWWhQamagrkaWQGJV1cdqlhEH
         G0q6c7lkT48MPmXmOpFV52wH/Fm3lnR0YoeGHEGL0vgiT4z72zyO6JxSna9MhG6npaW6
         OiSOMFeOo9tU4MD1/z76YPezK/gGB1QkjfVkNfN6+eZrfcF11aicsDmt3G2L/fnb27Hn
         gIOg==
X-Gm-Message-State: APjAAAXfdAKklCBvEJ2392vcgcuvKzHDtsgZ5bRv29By35192dB+WKKA
        OVhcz8t0pAcCqslTTkx5OQWycw0HE9N3Sg==
X-Google-Smtp-Source: 
 APXvYqxulRqIFiu35irh0tZxsuWonzlGA9ktIbBv5lXHrYNTqdehtS0gacQLirO4tb0w3/CnhXsunQ==
X-Received: by 2002:a17:90b:3109:: with SMTP id
 gc9mr1950518pjb.30.1582022990740;
        Tue, 18 Feb 2020 02:49:50 -0800 (PST)
Received: from kernel.DHCP ([120.244.140.205])
        by smtp.googlemail.com with ESMTPSA id
 c184sm3812950pfa.39.2020.02.18.02.49.35
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Tue, 18 Feb 2020 02:49:50 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH] KVM: LAPIC: Recalculate apic map in batch
Date: Tue, 18 Feb 2020 18:47:09 +0800
Message-Id: <1582022829-27032-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

In the vCPU reset and set APIC_BASE MSR path, the apic map will be recalculated 
several times, each time it will consume 10+ us observed by ftrace in my 
non-overcommit environment since the expensive memory allocate/mutex/rcu etc 
operations. This patch optimizes it by recaluating apic map in batch, I hope 
this can benefit the serverless scenario which can frequently create/destroy 
VMs.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 74 ++++++++++++++++++++++++++++++++++------------------
 arch/x86/kvm/lapic.h |  3 ++-
 arch/x86/kvm/x86.c   |  3 ++-
 3 files changed, 53 insertions(+), 27 deletions(-)

```
#### [PATCH] KVM: Suppress warning in __kvm_gfn_to_hva_cache_initFrom: Oliver Upton <oupton@google.com>
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11389287
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 41C1992A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 18:48:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 181EB24656
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 18:48:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="pziMD2Js"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726446AbgBRSsG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 13:48:06 -0500
Received: from mail-pg1-f202.google.com ([209.85.215.202]:37998 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726225AbgBRSsF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 13:48:05 -0500
Received: by mail-pg1-f202.google.com with SMTP id x16so13910255pgg.5
        for <kvm@vger.kernel.org>; Tue, 18 Feb 2020 10:48:03 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=mUCg79WyMDbLxcG7uSEM7XFzy4Eo8iAxs3oCavIjWFs=;
        b=pziMD2Jsu2b0vq9lw2bBmxIrkSUC8VKVp/8B4Pw7kAdkCfYavMg8imPAlC9/8VuRrm
         NPmdmDGRkk4fWlUBsM5KeJPrpxYrCH9N50jlSPcxwEvSq6akDdnw0vKVRmYoz9lP4W5w
         ngOcUKBRmQ7djFvnnoLaa9uEAtd4VBp4jJ8MfthW5Pua2dHBgNLkSs5pzZk8HmcoCzu6
         Pg7oU+k/9koDkl0a0mmI92DAHI7KpuKoSTkge/ufq2GVjEZXbYA3nFqyAz1w5eODnmAo
         VnSVNybD7CQWJJY5dGAlZUU6dSGR1e+u+W/WFMu0/EVhIC/gjr+P/iNg/S4bebRZMFep
         UKxQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=mUCg79WyMDbLxcG7uSEM7XFzy4Eo8iAxs3oCavIjWFs=;
        b=iFT9vd+MEOWJIaECOHgtWwI0EnFm4ZMp+jeSqLtezRdC3uWqnOzO63HoSR76O/xeSm
         cd2015ggFJHN3N4EgRneZ8M80kAT0giQ1l/QKP3YCCJrdvGYwNi8c0OmVJNqOPAjE4wR
         HkkwKc26ZlzneqzTxImRDGqvuOnp6PI0+5w04SUeY5YdEky08IvOwJ5dVWiydqZ+PChD
         Q7Hkmlc1dWpKSFR1ni25Tpj0kExVOU9jnb4W6770jgx3GKMZKNCwkp1970cyjefL0Qjm
         QTB7rtUzOQvlUOPquPIApAyYzTF/tGnC5gghOU2ae4GUO9mt/KXoCJhRCToGAIIe3qM0
         oPwA==
X-Gm-Message-State: APjAAAUzlR4mJgyr4cqHS7Y4dS/SzPZAgCwfntzQ91T/tZm9pqpVlgEj
        HtzfmKtreV9YzFpm2ZAHgXfIdMgORMDbBLpX3uKqqqB2hbS9WuR0vRP+3fYhdwYYNNlAORcj1sE
        nvFOTi6x02eNs0jLL49Oaqu2UPZpKTqlBDjMVjveOoUWgO0BTBDgYls+VUg==
X-Google-Smtp-Source: 
 APXvYqx3zhzxSNKOn5ldYpofPbZr1gJcux2SG8syIhC/e+izLZEQHemLW8fagUtzeQZA3Q9d2crvbdfTVb4=
X-Received: by 2002:a63:5826:: with SMTP id
 m38mr24858005pgb.191.1582051683115;
 Tue, 18 Feb 2020 10:48:03 -0800 (PST)
Date: Tue, 18 Feb 2020 10:47:56 -0800
Message-Id: <20200218184756.242904-1-oupton@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
Subject: [PATCH] KVM: Suppress warning in __kvm_gfn_to_hva_cache_init
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Oliver Upton <oupton@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Particularly draconian compilers warn of a possible uninitialized use of
the nr_pages_avail variable. Silence this warning by initializing it to
zero.

Signed-off-by: Oliver Upton <oupton@google.com>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: VMX: replace "fall through" with "return true" to indicate different case
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11387805
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6EFB692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 03:38:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5520E24655
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 03:38:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726296AbgBRDiC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 22:38:02 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:10199 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726245AbgBRDiC (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Feb 2020 22:38:02 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id AB648AC856EDC6C2B8F1;
        Tue, 18 Feb 2020 11:37:59 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS404-HUB.china.huawei.com
 (10.3.19.204) with Microsoft SMTP Server id 14.3.439.0; Tue, 18 Feb 2020
 11:37:52 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: VMX: replace "fall through" with "return true" to
 indicate different case
Date: Tue, 18 Feb 2020 11:39:28 +0800
Message-ID: <1581997168-20350-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The second "/* fall through */" in rmode_exception() makes code harder to
read. Replace it with "return true" to indicate they are different cases
and also this improves the readability.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: enable dirty log gradually in small chunks
##### From: Jay Zhou <jianjay.zhou@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Zhoujian (jay)" <jianjay.zhou@huawei.com>
X-Patchwork-Id: 11388227
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1FF40924
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 11:00:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 052C8206E2
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 11:00:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726496AbgBRLAb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 06:00:31 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:10637 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726403AbgBRLAa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 06:00:30 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id B6052C161B520BB25B62;
        Tue, 18 Feb 2020 19:00:23 +0800 (CST)
Received: from localhost (10.133.205.84) by DGGEMS403-HUB.china.huawei.com
 (10.3.19.203) with Microsoft SMTP Server id 14.3.439.0; Tue, 18 Feb 2020
 19:00:17 +0800
From: Jay Zhou <jianjay.zhou@huawei.com>
To: <kvm@vger.kernel.org>
CC: <pbonzini@redhat.com>, <peterx@redhat.com>,
        <wangxinxin.wang@huawei.com>, <linfeng23@huawei.com>,
        <weidong.huang@huawei.com>, <jianjay.zhou@huawei.com>
Subject: [PATCH] KVM: x86: enable dirty log gradually in small chunks
Date: Tue, 18 Feb 2020 19:00:13 +0800
Message-ID: <20200218110013.15640-1-jianjay.zhou@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.133.205.84]
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

1. Set all the bits of the first dirty bitmap to 1 when enabling
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
 arch/x86/kvm/vmx/vmx.c   |  5 +++++
 include/linux/kvm_host.h |  5 +++++
 virt/kvm/kvm_main.c      | 10 ++++++++--
 3 files changed, 18 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/3] KVM: x86: Add EMULTYPE_PF when emulation is triggered by a page fault
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11389917
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9E42992A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 23:03:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8080824655
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 23:03:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727833AbgBRXDQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 18:03:16 -0500
Received: from mga02.intel.com ([134.134.136.20]:57150 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727298AbgBRXDN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 18:03:13 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Feb 2020 15:03:11 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,458,1574150400";
   d="scan'208";a="239504570"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga006.jf.intel.com with ESMTP; 18 Feb 2020 15:03:10 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/3] KVM: x86: Add EMULTYPE_PF when emulation is triggered
 by a page fault
Date: Tue, 18 Feb 2020 15:03:08 -0800
Message-Id: <20200218230310.29410-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200218230310.29410-1-sean.j.christopherson@intel.com>
References: <20200218230310.29410-1-sean.j.christopherson@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a new emulation type flag to explicitly mark emulation related to a
page fault.  Move the propation of the GPA into the emulator from the
page fault handler into x86_emulate_instruction, using EMULTYPE_PF as an
indicator that cr2 is valid.  Similarly, don't propagate cr2 into the
exception.address when it's *not* valid.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h | 12 +++++++++---
 arch/x86/kvm/mmu/mmu.c          | 10 ++--------
 arch/x86/kvm/x86.c              | 25 +++++++++++++++++++------
 3 files changed, 30 insertions(+), 17 deletions(-)

```
#### [PATCH] mm/hugetlb: avoid get wrong ptep caused by race
##### From: "Longpeng(Mike)" <longpeng2@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Longpeng(Mike)" <longpeng2@huawei.com>
X-Patchwork-Id: 11388307
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 37B7B924
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 12:10:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1E7B52173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 12:10:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726477AbgBRMKw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 07:10:52 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:10208 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726043AbgBRMKv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 07:10:51 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id E589135BE54F3A0B3135;
        Tue, 18 Feb 2020 20:10:47 +0800 (CST)
Received: from localhost (10.177.246.209) by DGGEMS403-HUB.china.huawei.com
 (10.3.19.203) with Microsoft SMTP Server id 14.3.439.0; Tue, 18 Feb 2020
 20:10:39 +0800
From: "Longpeng(Mike)" <longpeng2@huawei.com>
To: <mike.kravetz@oracle.com>, <akpm@linux-foundation.org>
CC: <longpeng2@huawei.com>, <linux-mm@kvack.org>,
        <linux-kernel@vger.kernel.org>, <arei.gonglei@huawei.com>,
        <weidong.huang@huawei.com>, <weifuqiang@huawei.com>,
        <kvm@vger.kernel.org>
Subject: [PATCH] mm/hugetlb: avoid get wrong ptep caused by race
Date: Tue, 18 Feb 2020 20:10:25 +0800
Message-ID: <1582027825-112728-1-git-send-email-longpeng2@huawei.com>
X-Mailer: git-send-email 1.8.4.msysgit.0
MIME-Version: 1.0
X-Originating-IP: [10.177.246.209]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Our machine encountered a panic after run for a long time and
the calltrace is:
RIP: 0010:[<ffffffff9dff0587>]  [<ffffffff9dff0587>] hugetlb_fault+0x307/0xbe0
RSP: 0018:ffff9567fc27f808  EFLAGS: 00010286
RAX: e800c03ff1258d48 RBX: ffffd3bb003b69c0 RCX: e800c03ff1258d48
RDX: 17ff3fc00eda72b7 RSI: 00003ffffffff000 RDI: e800c03ff1258d48
RBP: ffff9567fc27f8c8 R08: e800c03ff1258d48 R09: 0000000000000080
R10: ffffaba0704c22a8 R11: 0000000000000001 R12: ffff95c87b4b60d8
R13: 00005fff00000000 R14: 0000000000000000 R15: ffff9567face8074
FS:  00007fe2d9ffb700(0000) GS:ffff956900e40000(0000) knlGS:0000000000000000
CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
CR2: ffffd3bb003b69c0 CR3: 000000be67374000 CR4: 00000000003627e0
DR0: 0000000000000000 DR1: 0000000000000000 DR2: 0000000000000000
DR3: 0000000000000000 DR6: 00000000fffe0ff0 DR7: 0000000000000400
Call Trace:
 [<ffffffff9df9b71b>] ? unlock_page+0x2b/0x30
 [<ffffffff9dff04a2>] ? hugetlb_fault+0x222/0xbe0
 [<ffffffff9dff1405>] follow_hugetlb_page+0x175/0x540
 [<ffffffff9e15b825>] ? cpumask_next_and+0x35/0x50
 [<ffffffff9dfc7230>] __get_user_pages+0x2a0/0x7e0
 [<ffffffff9dfc648d>] __get_user_pages_unlocked+0x15d/0x210
 [<ffffffffc068cfc5>] __gfn_to_pfn_memslot+0x3c5/0x460 [kvm]
 [<ffffffffc06b28be>] try_async_pf+0x6e/0x2a0 [kvm]
 [<ffffffffc06b4b41>] tdp_page_fault+0x151/0x2d0 [kvm]
 [<ffffffffc075731c>] ? vmx_vcpu_run+0x2ec/0xc80 [kvm_intel]
 [<ffffffffc0757328>] ? vmx_vcpu_run+0x2f8/0xc80 [kvm_intel]
 [<ffffffffc06abc11>] kvm_mmu_page_fault+0x31/0x140 [kvm]
 [<ffffffffc074d1ae>] handle_ept_violation+0x9e/0x170 [kvm_intel]
 [<ffffffffc075579c>] vmx_handle_exit+0x2bc/0xc70 [kvm_intel]
 [<ffffffffc074f1a0>] ? __vmx_complete_interrupts.part.73+0x80/0xd0 [kvm_intel]
 [<ffffffffc07574c0>] ? vmx_vcpu_run+0x490/0xc80 [kvm_intel]
 [<ffffffffc069f3be>] vcpu_enter_guest+0x7be/0x13a0 [kvm]
 [<ffffffffc06cf53e>] ? kvm_check_async_pf_completion+0x8e/0xb0 [kvm]
 [<ffffffffc06a6f90>] kvm_arch_vcpu_ioctl_run+0x330/0x490 [kvm]
 [<ffffffffc068d919>] kvm_vcpu_ioctl+0x309/0x6d0 [kvm]
 [<ffffffff9deaa8c2>] ? dequeue_signal+0x32/0x180
 [<ffffffff9deae34d>] ? do_sigtimedwait+0xcd/0x230
 [<ffffffff9e03aed0>] do_vfs_ioctl+0x3f0/0x540
 [<ffffffff9e03b0c1>] SyS_ioctl+0xa1/0xc0
 [<ffffffff9e53879b>] system_call_fastpath+0x22/0x27

( The kernel we used is older, but we think the latest kernel also has this
  bug after dig into this problem. )

For 1G hugepages, huge_pte_offset() wants to return NULL or pudp, but it
may return a wrong 'pmdp' if there is a race. Please look at the following
code snippet:
    ...
    pud = pud_offset(p4d, addr);
    if (sz != PUD_SIZE && pud_none(*pud))
        return NULL;
    /* hugepage or swap? */
    if (pud_huge(*pud) || !pud_present(*pud))
        return (pte_t *)pud;

    pmd = pmd_offset(pud, addr);
    if (sz != PMD_SIZE && pmd_none(*pmd))
        return NULL;
    /* hugepage or swap? */
    if (pmd_huge(*pmd) || !pmd_present(*pmd))
        return (pte_t *)pmd;
    ...

The following sequence would trigger this bug:
1. CPU0: sz = PUD_SIZE and *pud = 0 , continue
1. CPU0: "pud_huge(*pud)" is false
2. CPU1: calling hugetlb_no_page and set *pud to xxxx8e7(PRESENT)
3. CPU0: "!pud_present(*pud)" is false, continue
4. CPU0: pmd = pmd_offset(pud, addr) and maybe return a wrong pmdp
However, we want CPU0 to return NULL or pudp.

We can avoid this race by read the pud only once.

Signed-off-by: Longpeng(Mike) <longpeng2@huawei.com>
---
 mm/hugetlb.c | 34 ++++++++++++++++++----------------
 1 file changed, 18 insertions(+), 16 deletions(-)

```
#### [RFC v2 1/4] X86: Update mmu_cr4_features during identification
##### From: John Andersen <john.s.andersen@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Andersen <john.s.andersen@intel.com>
X-Patchwork-Id: 11389809
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4314517EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 21:58:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2CAA9207FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 21:58:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728008AbgBRV6c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 16:58:32 -0500
Received: from mga02.intel.com ([134.134.136.20]:52969 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727982AbgBRV6b (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 16:58:31 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Feb 2020 13:58:31 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,458,1574150400";
   d="scan'208";a="436004637"
Received: from gza.jf.intel.com ([10.54.75.28])
  by fmsmga006.fm.intel.com with ESMTP; 18 Feb 2020 13:58:30 -0800
From: John Andersen <john.s.andersen@intel.com>
To: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        pbonzini@redhat.com
Cc: hpa@zytor.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        liran.alon@oracle.com, luto@kernel.org, joro@8bytes.org,
        rick.p.edgecombe@intel.com, kristen@linux.intel.com,
        arjan@linux.intel.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, John Andersen <john.s.andersen@intel.com>
Subject: [RFC v2 1/4] X86: Update mmu_cr4_features during identification
Date: Tue, 18 Feb 2020 13:58:59 -0800
Message-Id: <20200218215902.5655-2-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20200218215902.5655-1-john.s.andersen@intel.com>
References: <20200218215902.5655-1-john.s.andersen@intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In identify_cpu when setting up SMEP/SMAP/UMIP call
cr4_set_bits_and_update_boot instead of cr4_set_bits. This ensures that
mmu_cr4_features contains those bits, and does not disable those
protections when in hibernation asm.

setup_arch updates mmu_cr4_features to save what identified features are
supported for later use in hibernation asm when cr4 needs to be modified
to toggle PGE. cr4 writes happen in restore_image and restore_registers.
setup_arch occurs before identify_cpu, this leads to mmu_cr4_features
not containing some of the cr4 features which were enabled via
identify_cpu when hibernation asm is executed.

On CPU bringup when cr4_set_bits_and_update_boot is called
mmu_cr4_features will now be written to. For the boot CPU,
the __ro_after_init on mmu_cr4_features does not cause a fault. However,
__ro_after_init was removed due to it triggering faults on non-boot
CPUs.

Signed-off-by: John Andersen <john.s.andersen@intel.com>
---
 arch/x86/kernel/cpu/common.c | 6 +++---
 arch/x86/kernel/setup.c      | 4 ++--
 2 files changed, 5 insertions(+), 5 deletions(-)

```
#### [RFC PATCH 01/11] vfio: Remove Calxeda XGMAC reset driver
##### From: Rob Herring <robh@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Rob Herring <robh@kernel.org>
X-Patchwork-Id: 11389125
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 82A2B138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 17:15:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 59BF92464E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 17:15:07 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1582046107;
	bh=LePWQPdw0yLe3gcSpPm0E4sHYbV16oulKoL2D/G26dk=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=yn54fe0qs/3SxIwkkPCWuhsQb8EWPGHPly793k9KID4ItIyER6+jP73F3GSjGQi7W
	 LijLSLMZ0bUZVctfVlUVOOSnubWq/Cj4s++AASRIXWvQTltZIRYxQ3T6TGxPR77JdY
	 H9kEn84hczgxyq8Ld1cNt/bc3LWFP9J853GG1Apc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726795AbgBRRN0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 12:13:26 -0500
Received: from mail-ot1-f68.google.com ([209.85.210.68]:45975 "EHLO
        mail-ot1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726750AbgBRRN0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 12:13:26 -0500
Received: by mail-ot1-f68.google.com with SMTP id 59so20239284otp.12;
        Tue, 18 Feb 2020 09:13:25 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=4LxZR/H/qWaW6PLZe7czUDlSa5Ov9S/K1kfsaVdcFug=;
        b=Y+eIkOh/8pk4ibBhldw3l0arntaaYotKXwiF29K9P325mXl//DMJJ5zkNVaug/4nYL
         QxyS2BT+5uhwcpZtmXSQu1FoKhp0nGrIregfSKKiL08DsKekbeVrf7y2hwFGGm+4DrYo
         RHHY3XwWgBgA7d+t4bgLWfob/LcH7cJqxt6wR4zwByA4gPE13GNyqyRfOTZ8WrimDQqH
         NYgxtWncTVZP+7d/AE6vBllHbSITaEnfafPlsLurijhLCx0/L59iEL8CPkFQ3GA+2E9c
         NyzHyiIEWshdjhFRa2oJhP3OPTD42OkWPS2qTSwTfqs5WKXla0V8vUr27tdnwNMs54Yx
         nGYw==
X-Gm-Message-State: APjAAAXtoWxEyliSONOWPlZayTiwMT1c2rBDm8UveOkJaugQbWyFOT0R
        ei2xdoRadJxzUeyHpFYHMA==
X-Google-Smtp-Source: 
 APXvYqzcQiA7Kz1hw5DSMbv4x/r+JIz0TrIbtjHbvB5jqm2ONigiZ49RPglyPaLbn09y6q4zITnNIw==
X-Received: by 2002:a05:6830:1f0c:: with SMTP id
 u12mr16226750otg.253.1582046005180;
        Tue, 18 Feb 2020 09:13:25 -0800 (PST)
Received: from xps15.herring.priv (24-155-109-49.dyn.grandenetworks.net.
 [24.155.109.49])
        by smtp.googlemail.com with ESMTPSA id
 y25sm1545755oto.27.2020.02.18.09.13.23
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 18 Feb 2020 09:13:24 -0800 (PST)
From: Rob Herring <robh@kernel.org>
To: linux-arm-kernel@lists.infradead.org, linux-kernel@vger.kernel.org,
        soc@kernel.org, Andre Przywara <andre.przywara@arm.com>,
        Robert Richter <rrichter@marvell.com>,
        Jon Loeliger <jdl@jdl.com>, Alexander Graf <graf@amazon.com>,
        Matthias Brugger <mbrugger@suse.com>,
        Mark Langsdorf <mlangsdo@redhat.com>
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Cornelia Huck <cohuck@redhat.com>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        "David S. Miller" <davem@davemloft.net>,
        devicetree@vger.kernel.org, Eric Auger <eric.auger@redhat.com>,
        iommu@lists.linux-foundation.org,
        James Morse <james.morse@arm.com>,
        Jens Axboe <axboe@kernel.dk>, Joerg Roedel <joro@8bytes.org>,
        kvm@vger.kernel.org, linux-clk@vger.kernel.org,
        linux-edac@vger.kernel.org, linux-ide@vger.kernel.org,
        linux-pm@vger.kernel.org,
        Mauro Carvalho Chehab <mchehab@kernel.org>,
        netdev@vger.kernel.org, "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Robin Murphy <robin.murphy@arm.com>,
        Stephen Boyd <sboyd@kernel.org>,
        Tony Luck <tony.luck@intel.com>,
        Viresh Kumar <viresh.kumar@linaro.org>,
        Will Deacon <will@kernel.org>
Subject: [RFC PATCH 01/11] vfio: Remove Calxeda XGMAC reset driver
Date: Tue, 18 Feb 2020 11:13:11 -0600
Message-Id: <20200218171321.30990-2-robh@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200218171321.30990-1-robh@kernel.org>
References: <20200218171321.30990-1-robh@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cc: Eric Auger <eric.auger@redhat.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Rob Herring <robh@kernel.org>
---
Do not apply yet.

 drivers/vfio/platform/reset/Kconfig           |  8 --
 drivers/vfio/platform/reset/Makefile          |  2 -
 .../reset/vfio_platform_calxedaxgmac.c        | 74 -------------------
 3 files changed, 84 deletions(-)
 delete mode 100644 drivers/vfio/platform/reset/vfio_platform_calxedaxgmac.c

--
2.20.1

```
#### [PATCH RESEND v2 1/2] KVM: Introduce pv check helpers
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11387725
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 67522924
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 01:12:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 48089208C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 01:12:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="SgnErVfo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726171AbgBRBMR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 20:12:17 -0500
Received: from mail-pl1-f194.google.com ([209.85.214.194]:46041 "EHLO
        mail-pl1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726069AbgBRBMR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Feb 2020 20:12:17 -0500
Received: by mail-pl1-f194.google.com with SMTP id b22so7380381pls.12;
        Mon, 17 Feb 2020 17:12:16 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=ZxKP5V2Mq8nq1NJT8kCExycpnJ7xXGIEe62BmBC6pgo=;
        b=SgnErVfo7B0izjblZdA7Xjs+KoiIHz/UwsemL9I+V5sI8Tnr8cHyqoLbYLkmJFBJy4
         5nbmHMJpaHep+xoxexfAbnCpnLXgE8flUzIKz2viz/FWFiSlBVuFskCxoo9H9Y60CwQJ
         acNe1VUdIpPRPamEDEkTyllDVGSXre11aHOpSF13dbhLRzpqaxmjEREmt5kAZnh1cFzk
         N47zcEDYxVpMEsAAg29OK5hkNncjuDzvGZKO2sQyS92MW/H9Vmt7/IiUKSlEBfRjlB3q
         VpA32+S67p8kmm/PavGgILWqVeg7xr2t7Hw0SZgOLuAZu5LEUHR15C9k6jmC4HmnmAQo
         fkUg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=ZxKP5V2Mq8nq1NJT8kCExycpnJ7xXGIEe62BmBC6pgo=;
        b=iI0+UtxWccX7phl8UMbd84fwT+iyAqy/dE9ZvaupdwaY9Znlj5z0TqYJv0OW10WRiW
         tBJ+PbObZSjUJdK/R08iVA2lINt3cmyiciKrnIbanx1Qh/wknoSkUQKJ30kQwbuClA8w
         qN8M2CWPX8FSjAK0tX5yQMIbmqaKGH9vLlZ8qg/JcSPrt/QtePf5wwrRs0vuXSQMUpd5
         7MpMYBniPuhWlVxckXQb79mcQA05uDWSUmdYN6Thdk7MFaXOaBfSRVGqz5EOuYk0S6qu
         X/0qlFqR8n6vXTuJcItfIfJI2ph40ENrtXrF0e/cKRGVGjqdFLfAYPPZem2WK+Zkwjrn
         CFxA==
X-Gm-Message-State: APjAAAVWryNJCJolhV/JU0ysUGtwIgszwPPyxLa6eJZwzZHPBizIJG4+
        Is+NK3jQfadXy2SmT6XGoQPfNNMGtshHpg==
X-Google-Smtp-Source: 
 APXvYqwHq705bhIBaKvXNiyqjqNYqnBThSAuV9Rof4MWuNkr6sKJSMR5/LOIEjIYURud6plj7bvurA==
X-Received: by 2002:a17:90a:a88d:: with SMTP id
 h13mr2085017pjq.48.1581988336244;
        Mon, 17 Feb 2020 17:12:16 -0800 (PST)
Received: from kernel.DHCP ([120.244.140.205])
        by smtp.googlemail.com with ESMTPSA id
 x23sm2074774pge.89.2020.02.17.17.11.10
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Mon, 17 Feb 2020 17:12:15 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH RESEND v2 1/2] KVM: Introduce pv check helpers
Date: Tue, 18 Feb 2020 09:08:23 +0800
Message-Id: <1581988104-16628-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Introduce some pv check helpers for consistency.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kernel/kvm.c | 34 ++++++++++++++++++++++++----------
 1 file changed, 24 insertions(+), 10 deletions(-)

```
#### [PATCH RFC] target/i386: filter out VMX_PIN_BASED_POSTED_INTR when enabling SynIC
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11388757
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7D9D892A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 14:44:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5DDA6208C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 14:44:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="A1gm0B5O"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726698AbgBROoW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 09:44:22 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:41791 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726605AbgBROoW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 18 Feb 2020 09:44:22 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1582037061;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=fhZ0I3YWrEhOWa29fWSP+eeinOmrWp9ss357sd3bjMY=;
        b=A1gm0B5OEgRFKCyeLpv0QWqLP65mpR6mzRjjKDbcGP+qQiyPQmY79W3zN/zk3exG1tAjqF
        W71VzQRuy9pMCZpXgs3QmuInru0QTjqGlK/y8j43Gp6CBz13CxZVhfVPL9ild8FSSXPE9Z
        kWccAZ8SIFHLAuT8OxGZJWLC9vLsUu4=
Received: from mail-wm1-f72.google.com (mail-wm1-f72.google.com
 [209.85.128.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-24-cAWyZ9CYP0yMuDtEywkuTg-1; Tue, 18 Feb 2020 09:44:19 -0500
X-MC-Unique: cAWyZ9CYP0yMuDtEywkuTg-1
Received: by mail-wm1-f72.google.com with SMTP id g26so149163wmk.6
        for <kvm@vger.kernel.org>; Tue, 18 Feb 2020 06:44:19 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=fhZ0I3YWrEhOWa29fWSP+eeinOmrWp9ss357sd3bjMY=;
        b=bzEVfnXmjyzPjG8mxwC70wzBU7IEoFDLJ1TfSRvvd6RitMPRg/w7JlPkI1BBxGj8z4
         Ns2G8g+TNKLTfRG7F9VBwzawr+8/OnoEjceXeEcn9Pg6hDeysCCJsXzRlhJmvAvmSlb/
         6fZAyVgnyjLKEw1+nxTcvExlmFOPaNPj6Sr0FoRGFiHNTfE6xnlIeeYnoOUT6hYMTN9b
         J1xzEKIe+oza0H4F7YM3fDxvu2H6YZ5d+V3GI7gzwL15GARf2+Rpe2sc42JvXN/XmA/M
         vOm+YNteX/wWwkdkZssBDwBcf8Wyao2b5+2YPgSmeK0e4dk+FjCP30IY6N0lTgT5qvHx
         U9HQ==
X-Gm-Message-State: APjAAAUXebmLltXKSDzSbls1lrsKo5JuGeH6zTH1xTP9ZA1mzO21eQ94
        n5UYjPZDxOcwH5cqdUM9YzfeF7RXT68Rz45hXOSqrTiIE9lBZ4uYu/HVBmTaChZ56n4hEl3asFn
        ANDNCGwl/T8dQ
X-Received: by 2002:a1c:7717:: with SMTP id t23mr3688914wmi.17.1582037058139;
        Tue, 18 Feb 2020 06:44:18 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwqyat2sqLbmEAil4KU1aSm4DesjlvwfePK23mCqjFAU6F67Sm42Y9pWvOTl46vSBYIORUf+A==
X-Received: by 2002:a1c:7717:: with SMTP id t23mr3688887wmi.17.1582037057826;
        Tue, 18 Feb 2020 06:44:17 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 l15sm6201826wrv.39.2020.02.18.06.44.16
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 18 Feb 2020 06:44:17 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: qemu-devel@nongnu.org
Cc: Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Liran Alon <liran.alon@oracle.com>,
        Roman Kagan <rkagan@virtuozzo.com>, kvm@vger.kernel.org
Subject: [PATCH RFC] target/i386: filter out VMX_PIN_BASED_POSTED_INTR when
 enabling SynIC
Date: Tue, 18 Feb 2020 15:44:15 +0100
Message-Id: <20200218144415.94722-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When a multi-vCPU guest is created with hv_synic, secondary vCPUs fail
to initialize with

qemu-system-x86_64: error: failed to set MSR 0x48d to 0xff00000016

This is caused by SynIC enablement on the boot CPU: when we do this
KVM disables apicv for the whole guest so we can't set
VMX_PIN_BASED_POSTED_INTR bit in MSR_IA32_VMX_TRUE_PINBASED_CTLS anymore.
(see nested_vmx_setup_ctls_msrs() in KVM).

This used to work before fine-grained VMX feature enablement because
we were not setting VMX MSRs.

Fix the issue by filtering out VMX_PIN_BASED_POSTED_INTR when enabling
SynIC. We also need to re-order kvm_init_msrs() with hyperv_init_vcpu()
so filtering on secondary CPUs happens before.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
RFC: This is somewhat similar to eVMCS breakage and it is likely possible
to fix this in KVM. I decided to try QEMU first as this is a single
control and unlike eVMCS we don't need to keep a list of things to disable.
---
 target/i386/kvm.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH v2.1] KVM: s390: protvirt: Add initial vm and cpu lifecycle handling
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11388005
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 72AB7924
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 08:40:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4BB7122527
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 08:40:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726246AbgBRIkA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 03:40:00 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:39020 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726193AbgBRIkA (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 18 Feb 2020 03:40:00 -0500
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01I8YF5L129047;
        Tue, 18 Feb 2020 03:39:55 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2y6dntffpg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 18 Feb 2020 03:39:55 -0500
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01I8YW86129728;
        Tue, 18 Feb 2020 03:39:55 -0500
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2y6dntffp4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 18 Feb 2020 03:39:54 -0500
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01I8ZHfT015915;
        Tue, 18 Feb 2020 08:39:54 GMT
Received: from b03cxnp08028.gho.boulder.ibm.com
 (b03cxnp08028.gho.boulder.ibm.com [9.17.130.20])
        by ppma04wdc.us.ibm.com with ESMTP id 2y68968gfn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 18 Feb 2020 08:39:54 +0000
Received: from b03ledav002.gho.boulder.ibm.com
 (b03ledav002.gho.boulder.ibm.com [9.17.130.233])
        by b03cxnp08028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01I8doTB65536440
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 18 Feb 2020 08:39:50 GMT
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 494F213604F;
        Tue, 18 Feb 2020 08:39:50 +0000 (GMT)
Received: from b03ledav002.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 491A4136051;
        Tue, 18 Feb 2020 08:39:49 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b03ledav002.gho.boulder.ibm.com (Postfix) with ESMTP;
        Tue, 18 Feb 2020 08:39:49 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: borntraeger@de.ibm.com
Cc: Ulrich.Weigand@de.ibm.com, cohuck@redhat.com, david@redhat.com,
        frankja@linux.ibm.com, frankja@linux.vnet.ibm.com,
        gor@linux.ibm.com, imbrenda@linux.ibm.com, kvm@vger.kernel.org,
        linux-s390@vger.kernel.org, mimu@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v2.1] KVM: s390: protvirt: Add initial vm and cpu lifecycle
 handling
Date: Tue, 18 Feb 2020 03:39:46 -0500
Message-Id: <20200218083946.44720-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200214222658.12946-10-borntraeger@de.ibm.com>
References: <20200214222658.12946-10-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-18_01:2020-02-17,2020-02-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxlogscore=999 clxscore=1015
 malwarescore=0 impostorscore=0 lowpriorityscore=0 bulkscore=0 spamscore=0
 adultscore=0 suspectscore=4 mlxscore=0 phishscore=0 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2001150001
 definitions=main-2002180070
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Janosch Frank <frankja@linux.ibm.com>

This contains 3 main changes:
1. changes in SIE control block handling for secure guests
2. helper functions for create/destroy/unpack secure guests
3. KVM_S390_PV_COMMAND ioctl to allow userspace dealing with secure
machines

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
[borntraeger@de.ibm.com: patch merging, splitting, fixing]
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
2->2.1  - combine CREATE/DESTROY CPU/VM into ENABLE DISABLE
	- rework locking and check locks with lockdep
	- I still have the PV_COMMAND_CPU in here for later use in
	  the SET_IPL_PSW ioctl. If wanted I can move
	- change CAP number

 arch/s390/include/asm/kvm_host.h |  24 ++-
 arch/s390/include/asm/uv.h       |  69 ++++++++
 arch/s390/kvm/Makefile           |   2 +-
 arch/s390/kvm/kvm-s390.c         | 231 ++++++++++++++++++++++++++-
 arch/s390/kvm/kvm-s390.h         |  35 +++++
 arch/s390/kvm/pv.c               | 262 +++++++++++++++++++++++++++++++
 include/uapi/linux/kvm.h         |  35 +++++
 7 files changed, 654 insertions(+), 4 deletions(-)
 create mode 100644 arch/s390/kvm/pv.c

```
#### [PATCH v4 1/2] KVM: X86: Less kvmclock sync induced vmexits after VM boots
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11387729
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9079E924
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 01:19:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 70A3E20836
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 01:19:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="ayxtwJaJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726293AbgBRBTc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 20:19:32 -0500
Received: from mail-pg1-f195.google.com ([209.85.215.195]:44771 "EHLO
        mail-pg1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726097AbgBRBTc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Feb 2020 20:19:32 -0500
Received: by mail-pg1-f195.google.com with SMTP id g3so9970574pgs.11;
        Mon, 17 Feb 2020 17:19:31 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=wdl63vLkZeTCO6cEhD7wb/Lt5+ras5GaQCOoaNINnOw=;
        b=ayxtwJaJbgP+QbO48qMs3x/NxRg1vDVDmL+gjWbxxaU3tI1Qh0trNJeYSdUeIkwXV4
         o4kD+UFWcT1uRG+LyO5jEAYfnr7gicrHdPZKy5hAORerM3yZ3dDeEGG4tkPmKL9YNKCk
         SjzmUR+5goMb7yJGKwPp3qarq9+Po7GmxbG000fR3pdqpp77U3BiGO422VbQB2zaCRPE
         vK7YImQV8c47x9QWXmB6GiS8+mQbMwv0qn+9RBfh3i0LZhGUedl/CgzinjFL6jeimtwj
         OhqHvDPE/+ofCJO6OceQIJeYQj8MgTOgY9vwIJy00Yg7FmzRnIBB6dGAmW9+4IsH3Ml7
         4SLg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=wdl63vLkZeTCO6cEhD7wb/Lt5+ras5GaQCOoaNINnOw=;
        b=OoGDXkMYUuF7S+0h8u5MYYB7Ce2vN4hUK1cDkbrpK1eQklWkQ6FQGZLB2dqq1GU6ep
         0WpxU7L1gLLQbty50Bnvq5hojJ9KT5p+i1vxlrRyAZq818vVOcu++bquy6AoCpWF90Sl
         s0wJd1FdLdyJfRiR16qLLDWurmT4QFwOrlBbZy0DjI8Dw/nACpd9VCmMM24TuoZKj/Eh
         G+FIuyZPiA7M5lQWAu4MzLiuITURs5U19MveksBL4yS0IWn0zr5jYb91wkq8CV4l+JVG
         H+tYpXcILhibxErLGG0U0hq0rJAzKGQzfqvUql7/gFPa7G/QAOpqmDyPM/YHrSgVwmiS
         H4HQ==
X-Gm-Message-State: APjAAAVoYC+nTW6hOB0kwM/SB5P/T9Z4QWzh29HrygmB3YbexBdDiS6G
        95SaI+7JaYtRaXUxHtuOk6Ldhx9YlnUEZQ==
X-Google-Smtp-Source: 
 APXvYqx5VtdeS9U5CVkgXTZIeohJKxNEj2BmCVl/+Xi8BV5uynYvo/WGPRsqNJSsSroxYkw0Q5MYrQ==
X-Received: by 2002:a63:38b:: with SMTP id 133mr20234538pgd.153.1581988771240;
        Mon, 17 Feb 2020 17:19:31 -0800 (PST)
Received: from kernel.DHCP ([120.244.140.205])
        by smtp.googlemail.com with ESMTPSA id
 g13sm1519511pfo.169.2020.02.17.17.19.26
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Mon, 17 Feb 2020 17:19:30 -0800 (PST)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Subject: [PATCH v4 1/2] KVM: X86: Less kvmclock sync induced vmexits after VM
 boots
Date: Tue, 18 Feb 2020 09:17:09 +0800
Message-Id: <1581988630-19182-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

In the progress of vCPUs creation, it queues a kvmclock sync worker to the global 
workqueue before each vCPU creation completes. Each worker will be scheduled 
after 300 * HZ delay and request a kvmclock update for all vCPUs and kick them 
out. This is especially worse when scaling to large VMs due to a lot of vmexits. 
Just one worker as a leader to trigger the kvmclock sync request for all vCPUs is 
enough.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v3 -> v4:
 * check vcpu->vcpu_idx

 arch/x86/kvm/x86.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
