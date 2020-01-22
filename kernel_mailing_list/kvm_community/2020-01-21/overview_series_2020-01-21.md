#### [GIT PULL] Please pull my kvm-ppc-next-5.6-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11343057
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD152109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 03:33:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9C24C24125
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 03:33:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="Ao6jUWwj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728843AbgAUDdd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jan 2020 22:33:33 -0500
Received: from ozlabs.org ([203.11.71.1]:50947 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728826AbgAUDdd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Jan 2020 22:33:33 -0500
Received: by ozlabs.org (Postfix, from userid 1003)
        id 481vJW2dw3z9sRG; Tue, 21 Jan 2020 14:33:31 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1579577611; bh=suGKrrg/HU8kzRkaVjlEcVNshSTs5/ByjJdeu2rWCsY=;
        h=Date:From:To:Cc:Subject:From;
        b=Ao6jUWwjePqBeumuL87dDPMvkXJTJ6rHz4AauGtQzeX/uN9NEqSZNo/H3RvHSSsVB
         uo0BTg/ZAYXlzW8FKQ1RS4B+dPww6ue/OdIh+nSDzb7LZwMKVml+IWJZsWfpBnt0G3
         Q/gH5NUahrqmhDP74D1ok8BNQfafzwytuVxJPFrWhLDRdjFtAewBa+d15TTp4BZQvj
         NxMcm/DUYUBswUQiRmmak4JLWq7Mh2ZDGRvbw9qWHPxvXRIRsUbskekVK6iTpEKLhh
         DWw5jUB+fQN9j4b8p7VKsWNtQlXzn01/NV00c5OrpmMRIE7cH3WjHATPaa8P3GZ1Kl
         ERZL3WDSHrh3w==
Date: Tue, 21 Jan 2020 14:33:26 +1100
From: Paul Mackerras <paulus@ozlabs.org>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 kvm-ppc@vger.kernel.org
Subject: [GIT PULL] Please pull my kvm-ppc-next-5.6-1 tag
Message-ID: <20200121033326.GA23311@blackberry>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.5.24 (2015-08-30)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo,

Please do a pull from my kvm-ppc-next-5.6-1 tag to get a PPC KVM
update for 5.6.

Thanks,
Paul.

The following changes since commit c79f46a282390e0f5b306007bf7b11a46d529538:

  Linux 5.5-rc5 (2020-01-05 14:23:27 -0800)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.6-1

for you to fetch changes up to 3a43970d55e9fd5475d3c4e5fe398ab831ec6c3a:

  KVM: PPC: Book3S HV: Implement H_SVM_INIT_ABORT hcall (2020-01-17 15:08:31 +1100)

----------------------------------------------------------------
KVM PPC update for 5.6

* Add a hypercall to be used by the ultravisor when secure VM
  initialization fails.

* Minor code cleanups.

----------------------------------------------------------------
Leonardo Bras (2):
      KVM: PPC: Book3S: Replace current->mm by kvm->mm
      KVM: PPC: Book3E: Replace current->mm by kvm->mm

Sukadev Bhattiprolu (2):
      KVM: PPC: Add skip_page_out parameter to uvmem functions
      KVM: PPC: Book3S HV: Implement H_SVM_INIT_ABORT hcall

zhengbin (1):
      KVM: PPC: Remove set but not used variable 'ra', 'rs', 'rt'

 Documentation/powerpc/ultravisor.rst        | 60 +++++++++++++++++++++++++++++
 arch/powerpc/include/asm/hvcall.h           |  1 +
 arch/powerpc/include/asm/kvm_book3s_uvmem.h | 10 ++++-
 arch/powerpc/include/asm/kvm_host.h         |  1 +
 arch/powerpc/kvm/book3s_64_mmu_hv.c         |  4 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c      |  2 +-
 arch/powerpc/kvm/book3s_64_vio.c            | 10 +++--
 arch/powerpc/kvm/book3s_hv.c                | 15 +++++---
 arch/powerpc/kvm/book3s_hv_uvmem.c          | 32 ++++++++++++++-
 arch/powerpc/kvm/booke.c                    |  2 +-
 arch/powerpc/kvm/emulate_loadstore.c        |  5 ---
 11 files changed, 119 insertions(+), 23 deletions(-)
```
#### [PATCH] KVM: async_pf: drop kvm_arch_async_page_present wrappers
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11343971
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C2CEA17EA
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:48:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9FEF124125
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:48:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="R1pRTr7a"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729263AbgAUNsP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 08:48:15 -0500
Received: from mail-wr1-f65.google.com ([209.85.221.65]:44590 "EHLO
        mail-wr1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728992AbgAUNsM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jan 2020 08:48:12 -0500
Received: by mail-wr1-f65.google.com with SMTP id q10so3227055wrm.11;
        Tue, 21 Jan 2020 05:48:10 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=V4U+PI2PAOqbzfWZBcXXcxH5L3R8mP6ogQR4djjn9y4=;
        b=R1pRTr7a3ZtUe266qoFQlXBnmPdzSwJGCjQTmfGzEKfE2pUSq7003XYG07n+q/gyOk
         tdnvbMcO6KAQW6c+JrcQipTqeTYd+P2aj/sfxq/om1SBktNzJ/cTgidhl/aC7wnBaqBs
         oALXS3IJBUX5of3MbyqvUY4hdGKwl6VxFv3wRCIZ25OccOIZBvSaFYFUH4AP+6eGGdGl
         E8hPi8mPpHPrU5ESpf4Lw0gC/1qKv36CekvAnMk3IERAFgyz+X34qr6zFOZ7YkEXSpC5
         EdAP4ZGBZPdQUNSCMZYxf9Kwk51j1nokpmrLG2BmmuF0OjeeOcRaxlGLgUEw+w4IRlQx
         lLrw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=V4U+PI2PAOqbzfWZBcXXcxH5L3R8mP6ogQR4djjn9y4=;
        b=MKKBorZASEYbLtNrrrIlXTrzXTdCHo/Arw48W1sp5T9gaSNRgy5wag47z5/Lr7PQ9L
         2QeTcrh9L1WLDhrwYRlr9jEcy+M0T5wxs9A6VLGVxU+CGSg6c36WuFc75NOQMQQOtJh9
         i+lFU7i2fhNyyJyi6LT34KyDCvZ2JgHpAlfRnvhH7vMMVuzXwPU3rKETDmKrUy/dJdzI
         jUz63jqrqLkKKHeFCKqrcPV67uT1/opSwZS9feYLJdi98HvOP6XCyZYjTStF9MaD9+kZ
         szBkK9CoCzAopzTXDE3mPKmPeFJm+sGAlr8fXxDPHwV1OOLz8Fk5hudspNjNaMH4xydt
         3RCQ==
X-Gm-Message-State: APjAAAVioxxc/1aMLLxuXURcZWSuxnppcdZPuV1zrthioaJmuaPGfLSj
        FOp3dSQtKl16slgN+vRmijwxSvIV
X-Google-Smtp-Source: 
 APXvYqzmp8LbMs7hHnOYiuZmZpxV40ascEfcwEQqdeSNbfwYvK8vXWWwErHsLEe7Tcw+zDLv45iTUQ==
X-Received: by 2002:adf:a746:: with SMTP id e6mr5340508wrd.329.1579614489944;
        Tue, 21 Jan 2020 05:48:09 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 b17sm51975006wrp.49.2020.01.21.05.48.09
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 21 Jan 2020 05:48:09 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Andy Lutomirski <luto@kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [PATCH] KVM: async_pf: drop kvm_arch_async_page_present wrappers
Date: Tue, 21 Jan 2020 14:48:06 +0100
Message-Id: <1579614487-44583-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The wrappers make it less clear that the position of the call
to kvm_arch_async_page_present depends on the architecture, and
that only one of the two call sites will actually be active.
Remove them.

Cc: Andy Lutomirski <luto@kernel.org>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 virt/kvm/async_pf.c | 21 ++++-----------------
 1 file changed, 4 insertions(+), 17 deletions(-)

```
#### [PATCH v5 01/19] KVM: x86: Allocate new rmap and large page tracking when moving memslot
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11344655
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0AEA26C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 22:33:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E5F5024653
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 22:33:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728863AbgAUWcF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 17:32:05 -0500
Received: from mga14.intel.com ([192.55.52.115]:1733 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726796AbgAUWcE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jan 2020 17:32:04 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 21 Jan 2020 14:32:02 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,347,1574150400";
   d="scan'208";a="244845098"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga002.jf.intel.com with ESMTP; 21 Jan 2020 14:32:02 -0800
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
Subject: [PATCH v5 01/19] KVM: x86: Allocate new rmap and large page tracking
 when moving memslot
Date: Tue, 21 Jan 2020 14:31:39 -0800
Message-Id: <20200121223157.15263-2-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200121223157.15263-1-sean.j.christopherson@intel.com>
References: <20200121223157.15263-1-sean.j.christopherson@intel.com>
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
#### [PATCH kvm-unit-tests 1/3] arm/arm64: Improve memory region management
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11343829
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 80E0E1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:17:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 55A6121569
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:17:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="M9phjKZr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728799AbgAUNRz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 08:17:55 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:41703 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725890AbgAUNRz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 21 Jan 2020 08:17:55 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579612673;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=OwXlzBEQhwCa8wParpIDpsxijVGaBsk9N2BIUCVw5x0=;
        b=M9phjKZrh86I3bUJchHV2cjmR6co4A2pIC4Mi7CmdSeD4ku+bU37Sw5sdjT2oHDdJRa5FI
        sOusQQQJeDRDpkETWzQsfnNMJ7eC4w4u20FeZOOVIM2KuEEjvupouHOJetLZf9HSaDEKZW
        4X2UNJ6aR5is83QHqahAfdIADOSwgpY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-100-HZWepzHeN9uLTece5MYilQ-1; Tue, 21 Jan 2020 08:17:50 -0500
X-MC-Unique: HZWepzHeN9uLTece5MYilQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 7C34B108BD0D;
        Tue, 21 Jan 2020 13:17:49 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4711110002A2;
        Tue, 21 Jan 2020 13:17:48 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com, alexandru.elisei@arm.com
Subject: [PATCH kvm-unit-tests 1/3] arm/arm64: Improve memory region
 management
Date: Tue, 21 Jan 2020 14:17:43 +0100
Message-Id: <20200121131745.7199-2-drjones@redhat.com>
In-Reply-To: <20200121131745.7199-1-drjones@redhat.com>
References: <20200121131745.7199-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add expected I/O regions and provide a way to check memory region
properties of a physical address. We also bump the initial number
of regions and even prepare for a unit test to reallocate for
growth if necessary.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 lib/arm/asm/setup.h |  8 +++++--
 lib/arm/mmu.c       | 24 ++++++-------------
 lib/arm/setup.c     | 56 +++++++++++++++++++++++++++++++++------------
 3 files changed, 55 insertions(+), 33 deletions(-)

```
#### [PATCH kvm-unit-tests] expect python3 in the path
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11344223
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B9F6992A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 16:21:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8DCAE22525
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 16:21:50 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="PCrAL/FH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728978AbgAUQVt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 11:21:49 -0500
Received: from mail-wm1-f65.google.com ([209.85.128.65]:37991 "EHLO
        mail-wm1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726555AbgAUQVt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jan 2020 11:21:49 -0500
Received: by mail-wm1-f65.google.com with SMTP id u2so3778569wmc.3
        for <kvm@vger.kernel.org>; Tue, 21 Jan 2020 08:21:47 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=fgORcTRcVPOjE/nYJxVcLMJmNeQKeZ0Sup420dt6Jog=;
        b=PCrAL/FH5qencx0LrGU3u9Yh6X5lWm9V9VKXvVnZ1jVEA6w4wAg+mKhY8/nNUBdq9n
         oeQ2VAMhScDi+RrrVjU6W4g6YjMbAUxHPdmoeFe2m1vG/kR+OmywXCRNv45syVu83pCm
         5cnTJKD+rF1MCGGeJ7DYEEOEk53mm86V8wFgXHjERHY8CxX8FWxKQbn/rUFGK5m2j4HL
         QoXhqzv+gztzZ3NUx3NjfDf4QYM93Oc6zzwW1nDAxVQoucy75I5UoDz298FsxKmPjXwC
         /Be02OO2vIHfTdfmQgI2nkfNIScFAEJyNTZ68WU5Sg4IR/vCNw1wQkwH6FfdU212vlVp
         fMkA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=fgORcTRcVPOjE/nYJxVcLMJmNeQKeZ0Sup420dt6Jog=;
        b=lTMhBEGj0QwzQmYr9Jk0vltyHnK0xJE0/ZoY0Q2nH1Rph2dYQr8UurstOW6VZoh6I4
         8taWrv0QzFPEiVmKa/BSxGNyaaF/fQmcmLkwKWK9t1KBD9kWqKd5MkkqXY2rxpk0aWfy
         guQmY/dqhjUFsAVrQ4Ah/6z4N1YWGHJyQJ60HDvLZ59IiVktw7W/WoW5rPWBrKWqAPHK
         yEtQe520TC59SZqg6x9pKN62UoTRIB8z9BDc1or+QpIJJ5e3+FzHWK5AdDGAUG2Tex3c
         iCTUZ6ed/v2ZZTWlYkR2ak4OkRK5ueypEkNhqsINyz+PWrJ4x212qeD/K8hblfGPFprt
         5Kfg==
X-Gm-Message-State: APjAAAUighebKeUqDXYCoMdGyiSVj6HA/gUx+iwszzVuZCSPq8YpLRKK
        lxGQecZDwBd9DwjJPOU1BGh0Uf+I
X-Google-Smtp-Source: 
 APXvYqz/UKnYGWmtfHbB84TAU5f+EvGdCI/grBxh8Q+zYCzWcipZK9MaYheojZmabTYHQmu6gB8Xsw==
X-Received: by 2002:a1c:66d6:: with SMTP id
 a205mr5230193wmc.171.1579623707100;
        Tue, 21 Jan 2020 08:21:47 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 h17sm54983664wrs.18.2020.01.21.08.21.46
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 21 Jan 2020 08:21:46 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com
Subject: [PATCH kvm-unit-tests] expect python3 in the path
Date: Tue, 21 Jan 2020 17:21:45 +0100
Message-Id: <1579623705-51801-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Some systems that only have Python 3.x installed will not have
a "python" binary in the path.  Since pretty_print_stacks.py
is a Python 3 program, we can use an appropriate shebang.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Thomas Huth <thuth@redhat.com>
---
 scripts/pretty_print_stacks.py | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] Remove the old api folder
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11344319
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CD7F16C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 17:47:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8391322522
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 17:47:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="X7A2Sp1S"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729108AbgAURrf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 12:47:35 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:51609 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728186AbgAURrf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 21 Jan 2020 12:47:35 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579628852;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=HUNMzzxVAlR6g9kNXd/ndiK3/R2+uQjCx0o0JDfEGGU=;
        b=X7A2Sp1SFBvAvok5q4ZIrUDbAQsEVJMQWR2xLNjZBY6WwlTjfNZUJq1PC5wHfhbRfUI6sh
        +XBTbmJo4uwQiCAxoJp8uPB1Ib1fK0h3KCPyBf+WmsjIy3pqXLALjCiKsYxrxHcUM/I+3J
        oJsctyGrSxQdG3MQegXHOh0zI96Ympk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-415-61hUpcTyPoGWcGwf2ReaBA-1; Tue, 21 Jan 2020 12:47:30 -0500
X-MC-Unique: 61hUpcTyPoGWcGwf2ReaBA-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C9F39800D4C
        for <kvm@vger.kernel.org>; Tue, 21 Jan 2020 17:47:27 +0000 (UTC)
Received: from thuth.com (unknown [10.36.118.148])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 776DC86C54;
        Tue, 21 Jan 2020 17:47:23 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Drew Jones <drjones@redhat.com>,
        David Hildenbrand <david@redhat.com>
Subject: [kvm-unit-tests PATCH] Remove the old api folder
Date: Tue, 21 Jan 2020 18:47:19 +0100
Message-Id: <20200121174719.31156-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The api tests are quite neglected - the tests work for 32-bit i386 only
and there hasn't been any change in this folder since more than 2.5 years.
Additionally, there is nowadays another way of testing the KVM API - the
KVM selftests (as part of the Linux kernel sources) have a much higher
traction and feature much more tests already, so it's unlikely that the
API tests in the kvm-unit-tests repository will get much more attention
in the future. Thus let's delete the api folder now to remove the burder
from the kvm-unit-test maintainers of dragging this code along.
If someone still wants to run the dirty-log-perf test for example, they
can check out an older state of the repository (and then e.g. port the
code to the KVM selftests framework instead).

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 Makefile              |   2 -
 api/api-sample.cc     |  30 -------
 api/dirty-log-perf.cc | 146 -------------------------------
 api/dirty-log.cc      |  84 ------------------
 api/exception.cc      |  33 -------
 api/exception.hh      |  19 ----
 api/identity.cc       | 120 -------------------------
 api/identity.hh       |  45 ----------
 api/kvmxx.cc          | 199 ------------------------------------------
 api/kvmxx.hh          |  86 ------------------
 api/memmap.cc         |  96 --------------------
 api/memmap.hh         |  43 ---------
 configure             |  17 ----
 x86/Makefile.common   |  19 +---
 14 files changed, 1 insertion(+), 938 deletions(-)
 delete mode 100644 api/api-sample.cc
 delete mode 100644 api/dirty-log-perf.cc
 delete mode 100644 api/dirty-log.cc
 delete mode 100644 api/exception.cc
 delete mode 100644 api/exception.hh
 delete mode 100644 api/identity.cc
 delete mode 100644 api/identity.hh
 delete mode 100644 api/kvmxx.cc
 delete mode 100644 api/kvmxx.hh
 delete mode 100644 api/memmap.cc
 delete mode 100644 api/memmap.hh

```
#### [PATCH] KVM: VMX: remove duplicated segment cache clear
##### From: Miaohe Lin <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Miaohe Lin <linmiaohe@huawei.com>
X-Patchwork-Id: 11343037
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E5C8B921
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 02:17:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CD90B2253D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 02:17:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728512AbgAUCQu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 20 Jan 2020 21:16:50 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:9673 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726890AbgAUCQu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 20 Jan 2020 21:16:50 -0500
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id D0602624C87E6C663BEB;
        Tue, 21 Jan 2020 10:16:47 +0800 (CST)
Received: from huawei.com (10.175.104.201) by DGGEMS414-HUB.china.huawei.com
 (10.3.19.214) with Microsoft SMTP Server id 14.3.439.0; Tue, 21 Jan 2020
 10:16:41 +0800
From: Miaohe Lin <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: VMX: remove duplicated segment cache clear
Date: Tue, 21 Jan 2020 10:15:18 -0500
Message-ID: <20200121151518.27530-1-linmiaohe@huawei.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
X-Originating-IP: [10.175.104.201]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vmx_set_segment() clears segment cache unconditionally, so we should not
clear it again by calling vmx_segment_cache_clear().

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH] KVM: x86: avoid incorrect writes to host MSR_IA32_SPEC_CTRL
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11343969
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 254BE139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:48:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 036AF2070C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:48:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="Txu8TGOy"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729305AbgAUNsP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 08:48:15 -0500
Received: from mail-wm1-f67.google.com ([209.85.128.67]:37479 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728811AbgAUNsN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jan 2020 08:48:13 -0500
Received: by mail-wm1-f67.google.com with SMTP id f129so3089191wmf.2;
        Tue, 21 Jan 2020 05:48:11 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=WQU1L9qQCnv53A9YDExCWzfCFNaPEWQjRccNAKJ2zmI=;
        b=Txu8TGOyS8OPQNLR6tXwLOgwDR+Im7w00WRyDlz8xB5OxBEXnRxDZkhIw3P0Lqn+M3
         8B6+FHDUWxR9LDV7VJP/20pNXCjNFF0iUnkZO+AZMf9K8LIqxfWyiGS+EPMmhOeRUGQy
         A8VTluZhGcWSQ7KWXcugoryJHxxhcpdH0A7f2pvxcXcNCUayWV3jIqVgSUehmELl/WPn
         7pmX8ZpuNPbweNeSn8BuxTda2wwbtVHHIXiR268Yk2p1RkISghkIkusAEYxtLc9Kgo3D
         hue85W7U0xK6dH2CCOwcKjlc5ii8NxGRiS5eLcrnNIxLFAHcLbRm3B0cf3SlmJMF24K8
         qA/Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=WQU1L9qQCnv53A9YDExCWzfCFNaPEWQjRccNAKJ2zmI=;
        b=aYL96jh4cCaKuSJ1PAg822xccpCTimwg1pGln3iOLoE7CZsCJcPK4Oi9P+h+wHiWOg
         mjwOs8NICYbneJYIXGhMht5O+10E1FICvaq7fJQolsnu7BZn5SxPxZjb819Ux7S+u5gl
         64dPw6aG6+GtFrAj2SvGS53epcjVvIr82lUzk8Je+a5prOPYgLIGJHaJv8z1qyxhiJOA
         /1rNvwcrx/7J1CD7hK01bzeeXMLrs/HGjVqpUtrpKArtr3KD7ruKL1+BSa9C0eYNu6xY
         BsSy05qcww/o09ZSsXSLVxHhkIdvWP9BwaPRRQKlL8pu1IZt3sOh0/vQtcKeCRjBmSkA
         AHAA==
X-Gm-Message-State: APjAAAV8brlJhucaG2jafeofuMEGrp84aEWyrUZUbl6mY4/StZuQrQum
        bb057Bfpf1TL9FeiAlW6iZCYEU5N
X-Google-Smtp-Source: 
 APXvYqxNNxkdhYczKoAl5tWzFetoCTLwgnvio8xmm0blTvhT9l2deTBSP+qiBDrtoX426Ku9nPC86Q==
X-Received: by 2002:a1c:1d02:: with SMTP id d2mr4630528wmd.185.1579614490829;
        Tue, 21 Jan 2020 05:48:10 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 b17sm51975006wrp.49.2020.01.21.05.48.10
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 21 Jan 2020 05:48:10 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@redhat.com>
Subject: [PATCH] KVM: x86: avoid incorrect writes to host MSR_IA32_SPEC_CTRL
Date: Tue, 21 Jan 2020 14:48:07 +0100
Message-Id: <1579614487-44583-3-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If the guest is configured to have SPEC_CTRL but the host does not
(which is a nonsensical configuration but these are not explicitly
forbidden) then a host-initiated MSR write can write vmx->spec_ctrl
(respectively svm->spec_ctrl) and trigger a #GP when KVM tries to
restore the host value of the MSR.  Add a more comprehensive check
for valid bits of SPEC_CTRL, covering host CPUID flags and,
since we are at it and it is more correct that way, guest CPUID
flags too.

For AMD, remove the unnecessary is_guest_mode check around setting
the MSR interception bitmap, so that the code looks the same as
for Intel.

Cc: Jim Mattson <jmattson@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm.c     |  9 +++------
 arch/x86/kvm/vmx/vmx.c |  7 +++----
 arch/x86/kvm/x86.c     | 22 ++++++++++++++++++++++
 arch/x86/kvm/x86.h     |  1 +
 4 files changed, 29 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: x86: fix overlap between SPTE_MMIO_MASK and generation
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11344211
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 173E592A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 16:11:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E966A24653
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 16:11:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="Hf/MOqfv"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729037AbgAUQLF (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 11:11:05 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:45091 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726555AbgAUQLF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jan 2020 11:11:05 -0500
Received: by mail-wr1-f66.google.com with SMTP id j42so3823091wrj.12;
        Tue, 21 Jan 2020 08:11:04 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=cEr4BWLn2p/pqLCf/UdrHd/9NDMtfKcezkWAo2kyLx8=;
        b=Hf/MOqfv+5cVe4ENG6tOBbFYEaa3uuETBmTH8Ez1+4Sqyh8fZ0P/sjK/VtDQv+srKR
         1h15GfkXfW28dpL7hmJKoDDidFMjRBBztIPvFkS8T9ORn/lRine2u4Vg2FYz1OTvb+vy
         jBy98yGh1oXOBbEOhajZEIiKsp20RFE284UlKyf9+Pplv2g1T3edsIOz86PGS5eV9JXG
         C1aQLh+6YhCQmZ9DLzTit1uUYMLrVCg9i8Ot0ButQz5N7+PxwNEQ5BvganAcXcO5x3Vi
         7U1f0gyRXJ+icMcIlVynGpo30EWmbJ9UBsFuaID1Tc6pHAwGZ8l1GQOT2sLKF1XZ0IAg
         y4YA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=cEr4BWLn2p/pqLCf/UdrHd/9NDMtfKcezkWAo2kyLx8=;
        b=IVCp+nMAWtIyPCu1HmOkZVS749EWMiRjfvwn/VIAO3enjWRiB8f0+sWa1Swn8z4NV6
         BcFAXZrPqDE9/KnSfWHR36NeuZbL6gd3vI9+I/gDsMQm09N68DxNu73Z/Sf6ObvK7WCW
         kfw7T27n9H4W3JfUBLsF2D9fNbZMXIbUSIdWMJbHmcdmDAWJN81NhyNknoRp1ZD0Wsb/
         Wm3DoorDWWvkqZ6kJgZwdugp5BSRaAKNUjNbBn9voa7tMoB3kuYfr5ouTc5fveVn2gzV
         KJ4LrtdF1LZNXk9lwkfuLFSeO5Q92szbKw6fI4mmUOH8IrVMwU0GSkcEZ8LszPKf5OcW
         bWAw==
X-Gm-Message-State: APjAAAVshAH1yNi8Hb15ATYjfLHQiqLJ0QDUQ2XIdnpME1T975/ogfYk
        dxu+YciRhpk3SHrv3lALlsndlluv
X-Google-Smtp-Source: 
 APXvYqwE/Z+q/9o7JJLQM99fbmsXu0/Hhy4yrgNDn1lvUXCMIqIUWWpau4XkB0Ki3Gn/WvkZM1aHSg==
X-Received: by 2002:adf:f5cb:: with SMTP id k11mr6221918wrp.71.1579623063434;
        Tue, 21 Jan 2020 08:11:03 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 p17sm4372742wmk.30.2020.01.21.08.11.02
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 21 Jan 2020 08:11:02 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        bgardon@google.com
Subject: [PATCH] KVM: x86: fix overlap between SPTE_MMIO_MASK and generation
Date: Tue, 21 Jan 2020 17:11:01 +0100
Message-Id: <1579623061-47141-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The SPTE_MMIO_MASK overlaps with the bits used to track MMIO
generation number.  A high enough generation number would overwrite the
SPTE_SPECIAL_MASK region and cause the MMIO SPTE to be misinterpreted;
likewise, setting bits 52 and 53 would also cause an incorrect generation
number to be read from the PTE.

Fixes: 6eeb4ef049e7 ("KVM: x86: assign two bits to track SPTE kinds")
Reported-by: Ben Gardon <bgardon@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: inline memslot_valid_for_gpte
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11344213
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 34F8013A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 16:11:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 128AC24653
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 16:11:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="o8ADRwsz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729398AbgAUQLL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 11:11:11 -0500
Received: from mail-wm1-f66.google.com ([209.85.128.66]:39879 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726555AbgAUQLL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jan 2020 11:11:11 -0500
Received: by mail-wm1-f66.google.com with SMTP id 20so3714930wmj.4;
        Tue, 21 Jan 2020 08:11:09 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id;
        bh=0r9HTQo0HlkDjaCMRvg6avAGNtQXXo1BGS+PSpMF/rg=;
        b=o8ADRwszU8umz6tgcM1h3UdSiPzo+mhb6aukx2pasJOBSGTU3zMsRqdHVJfIWBiqX1
         Bfw46uRQ2EmUosxSyJeoOPjE5Hxwdf0sSEo7MiU1EBQMaHEVDpHLVWgmIIVzcsyZB8tr
         91Rwk0x9EFfNnh4Df39hN9XK1G+loTMHr7mq0xldzz655I3T3j84pQwX7cjkxHTsOexB
         laYIDvmaqat3QODRpUAaJs1lwcVK+YCf+DccwGh6qKa4OjXfgQ7TgrHYAlZOkqIZJRO/
         eq115/iNAA/75Cq/VpNQ1/c4KQuFg/rVaXbSPH6r9KSTuR7YMdWIliJKgUu+TKGkappr
         D8Bw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id;
        bh=0r9HTQo0HlkDjaCMRvg6avAGNtQXXo1BGS+PSpMF/rg=;
        b=feRnbM+KNpzjrtdUJdVg3oRubF7NyQT5eaTFsrb8Qz3/MRNHggFvsHF1hCADNYCt9Q
         Lv272LMEg8GcMO07AVeb4k/15MIojcSCa0pBt5ul+7EFdy56C9AtUOrTuOWOSAJMzwxL
         BsnaHm6wtCZNYTymLH8gOiLML6LEC380s81cb88GrvUqaTsJrah5f5ulQw8nIARGzCcQ
         bDePtEvT/8NhTcfQEITOw+cBdXdUU2ZS3C5dcA6IWLWOrVfbv7ue6Qc2gEinGOfgjdHV
         T4GJF4duHKuH6HWECgsjpVVO+nC6n9ZunXN2aUFNESbSOJnmmk2OR0dRWaw7/HbnEPgm
         eHMQ==
X-Gm-Message-State: APjAAAXYW8N8wiG4XU4i8g5Tva+/FETD2l7054wx/AjmH4tdTZe6QaXb
        44sWRLM9StBlY9yC8MJSH+tYJ9vZ
X-Google-Smtp-Source: 
 APXvYqzVexiF8edJY6JhT2eTC61P3ZXm04IQoJfkwi4v0wI6o/A9Rh/EFnhCXkqXNUYu13FSve02nw==
X-Received: by 2002:a05:600c:298:: with SMTP id
 24mr4931157wmk.141.1579623068933;
        Tue, 21 Jan 2020 08:11:08 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 l6sm4648584wmf.21.2020.01.21.08.11.08
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 21 Jan 2020 08:11:08 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86: inline memslot_valid_for_gpte
Date: Tue, 21 Jan 2020 17:11:07 +0100
Message-Id: <1579623067-47221-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The function now has a single caller, so there is no point
in keeping it separate.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c | 17 ++++-------------
 1 file changed, 4 insertions(+), 13 deletions(-)

```
#### [PATCH] KVM: x86: list MSR_IA32_UCODE_REV as an emulated MSR
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11343963
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F2B09139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:48:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D14EA2253D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:48:14 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="et4rDCDC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729094AbgAUNsL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 08:48:11 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:52650 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728811AbgAUNsL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jan 2020 08:48:11 -0500
Received: by mail-wm1-f68.google.com with SMTP id p9so3027503wmc.2;
        Tue, 21 Jan 2020 05:48:10 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id;
        bh=FZjCfdCwsLgD1MIWUQtYRR8hOJhqjphscHVRCJxvEAE=;
        b=et4rDCDCIEejNLTYKWnB7T64LDOz0nUySgRJ2whWdx6FTDx+fU1BYPsgI/fY9/8Bgi
         90e/RE1F5lqUDl2NigBVuF0aAF1LadwjJiG5C1VWdO7FTDfZYupmvQWH/IjHV0MmhGSP
         gFyXqEPhHnIBL5yxkD932+GNvsxjoj7VYWuXfTQt0fV4SAdHG7y1RrFw7cZHF3JkpIf7
         Xq6e5oUjg38yDd4M4M7NkLrzOoffEp31M746keTKJPMq6c/GIiH/GDiEs/7H4pVpKU+H
         XgYKLtImL4jd+oXzKGVMqKB/MQxwm6tJEHu+Mxdx2qfPfCXYy16afCfWYMBbOQ/apdWW
         6kmg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id;
        bh=FZjCfdCwsLgD1MIWUQtYRR8hOJhqjphscHVRCJxvEAE=;
        b=hvD87kpver75Cj1qOL0YNdxS2MTZ3Mp42vbPRSktjAQN0u3yBxu8+Sj3GvT+SjHASf
         oyfI1KWrNvqBcbS3LlM1ujmhPaxtXD4n1vp4ZKMNclhrz9/Qq/IC81Mlqqx5C31f0dhR
         n2Nk2nqKxGM3BYZ1fA9oNe9a1aa2eIwFqj8yHHZUEKYfgboeBLaM81PUsSPUvQE80TkD
         Hc/YqqTftL8j+WYuH1Gz5pid0yGLBKU2qlyJOlbpA/n9qS4+DRf7tNe70/Ox3sXaranS
         GYb6b9e+QXLWW4ho+5Xh7wzH2fsIFIOmNceBJNXrlSxxuO+1EjqypfgbaZyeoH7BJWT5
         mUKA==
X-Gm-Message-State: APjAAAWlcvQPGfrkrCDuSRlVZhTpQLKmx7XbxMARhYmb4B/LsOkn+pGp
        aphjp0l5zbzmak4h6eEyVeoFPS3D
X-Google-Smtp-Source: 
 APXvYqy+s2vCZ/TdTgraG4Nc6LKsnRVP6bkYC6XS72xKihGczMaMO4ER/PgAvwCBhaaRo4JKC9yngg==
X-Received: by 2002:a1c:a745:: with SMTP id q66mr4232830wme.167.1579614489036;
        Tue, 21 Jan 2020 05:48:09 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 b17sm51975006wrp.49.2020.01.21.05.48.08
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 21 Jan 2020 05:48:08 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86: list MSR_IA32_UCODE_REV as an emulated MSR
Date: Tue, 21 Jan 2020 14:48:05 +0100
Message-Id: <1579614487-44583-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Even if it's read-only, it can still be written to by userspace.  Let
them know by adding it to KVM_GET_MSR_INDEX_LIST.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v2 09/10] accel: Replace current_machine->accelerator by current_accel() wrapper
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 11343549
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 55C92109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 11:05:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3525024653
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 11:05:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="i0oIASQj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728899AbgAULFc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 06:05:32 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:35983 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728748AbgAULFc (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 21 Jan 2020 06:05:32 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1579604731;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=iNuoGr5oPJiuWEZoZePQ9BsL70DcUB2WguHzKK55cpE=;
        b=i0oIASQjfC6SBaFXZjprEgIgMac0ULh3WqCuwtSVQRYkPUq+B19KLe8Qp9LTDizcZTK1dq
        0AJLDanTkQ8HxJjD4xB4JG9CgJrfjkDTVFBBGfgp3EU9dXrw+m5bd9TH1SApnfTrVHBkGD
        tMsCO68DyKzJAVa4+KdaAnYZFOWXr6s=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-254-JQqfRcGaOUKmLMIdFS6tiQ-1; Tue, 21 Jan 2020 06:05:29 -0500
X-MC-Unique: JQqfRcGaOUKmLMIdFS6tiQ-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 363F6DBA3;
        Tue, 21 Jan 2020 11:05:28 +0000 (UTC)
Received: from x1w.redhat.com (ovpn-205-38.brq.redhat.com [10.40.205.38])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 13C98811F8;
        Tue, 21 Jan 2020 11:05:21 +0000 (UTC)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: Peter Maydell <peter.maydell@linaro.org>,
 Marcelo Tosatti <mtosatti@redhat.com>, Cornelia Huck <cohuck@redhat.com>,
 David Gibson <david@gibson.dropbear.id.au>, qemu-s390x@nongnu.org,
 David Hildenbrand <david@redhat.com>, qemu-ppc@nongnu.org,
 Eduardo Habkost <ehabkost@redhat.com>, Like Xu <like.xu@linux.intel.com>,
 Markus Armbruster <armbru@redhat.com>, qemu-arm@nongnu.org,
 Paolo Bonzini <pbonzini@redhat.com>, Richard Henderson <rth@twiddle.net>,
	=?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Alistair Francis <alistair.francis@wdc.com>,
 kvm@vger.kernel.org (open list:Overall KVM CPUs)
Subject: [PATCH v2 09/10] accel: Replace current_machine->accelerator by
 current_accel() wrapper
Date: Tue, 21 Jan 2020 12:03:48 +0100
Message-Id: <20200121110349.25842-10-philmd@redhat.com>
In-Reply-To: <20200121110349.25842-1-philmd@redhat.com>
References: <20200121110349.25842-1-philmd@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We actually want to access the accelerator, not the machine, so
use the current_accel() wrapper instead.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Alistair Francis <alistair.francis@wdc.com>
Signed-off-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
v2:
- Reworded description
- Remove unused include in arm/kvm64
---
 accel/kvm/kvm-all.c | 4 ++--
 accel/tcg/tcg-all.c | 2 +-
 memory.c            | 2 +-
 target/arm/kvm64.c  | 5 ++---
 target/i386/kvm.c   | 2 +-
 target/ppc/kvm.c    | 2 +-
 vl.c                | 2 +-
 7 files changed, 9 insertions(+), 10 deletions(-)

```
#### [kvm-unit-tests PATCH v4 1/9] s390x: smp: Cleanup smp.c
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11343929
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 098CE1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:43:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E62DB2253D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 13:43:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729126AbgAUNnT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 08:43:19 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:15906 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728984AbgAUNnS (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 21 Jan 2020 08:43:18 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 00LDgg8T127992
        for <kvm@vger.kernel.org>; Tue, 21 Jan 2020 08:43:17 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2xnnn6pc5x-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 21 Jan 2020 08:43:16 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Tue, 21 Jan 2020 13:43:15 -0000
Received: from b06avi18878370.portsmouth.uk.ibm.com (9.149.26.194)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Tue, 21 Jan 2020 13:43:13 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 00LDhCJq38207756
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 21 Jan 2020 13:43:12 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 42199A4067;
        Tue, 21 Jan 2020 13:43:12 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 55981A405C;
        Tue, 21 Jan 2020 13:43:11 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.211])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Tue, 21 Jan 2020 13:43:11 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, borntraeger@de.ibm.com,
        linux-s390@vger.kernel.org, david@redhat.com, cohuck@redhat.com
Subject: [kvm-unit-tests PATCH v4 1/9] s390x: smp: Cleanup smp.c
Date: Tue, 21 Jan 2020 08:42:46 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200121134254.4570-1-frankja@linux.ibm.com>
References: <20200121134254.4570-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 20012113-4275-0000-0000-000003999AF3
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20012113-4276-0000-0000-000038ADA382
Message-Id: <20200121134254.4570-2-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-01-21_04:2020-01-21,2020-01-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 mlxlogscore=993
 spamscore=0 impostorscore=0 phishscore=0 priorityscore=1501 bulkscore=0
 suspectscore=1 lowpriorityscore=0 clxscore=1015 mlxscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-1910280000
 definitions=main-2001210114
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's remove a lot of badly formatted code by introducing the
wait_for_flag() and set_flag functions.

Also let's remove some stray spaces and always set the tesflag before
using it.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 s390x/smp.c | 55 ++++++++++++++++++++++++++++++++---------------------
 1 file changed, 33 insertions(+), 22 deletions(-)

```
#### [virtio-dev] [PATCH v2 1/5] virtio-mmio: Add feature bit for MMIO notification
##### From: Jing Liu <jing2.liu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Liu <jing2.liu@linux.intel.com>
X-Patchwork-Id: 11343095
Return-Path: <SRS0=HGec=3K=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E02236C1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 06:20:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BD52421734
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 21 Jan 2020 06:20:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728827AbgAUGTr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 21 Jan 2020 01:19:47 -0500
Received: from mga14.intel.com ([192.55.52.115]:33355 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728783AbgAUGTr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 21 Jan 2020 01:19:47 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 20 Jan 2020 22:19:47 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,344,1574150400";
   d="scan'208";a="278301891"
Received: from hyperv-sh3.bj.intel.com ([10.240.193.95])
  by fmsmga001.fm.intel.com with ESMTP; 20 Jan 2020 22:19:45 -0800
From: Jing Liu <jing2.liu@linux.intel.com>
To: virtio-dev@lists.oasis-open.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        qemu-devel@nongnu.org, Jing Liu <jing2.liu@linux.intel.com>,
        Chao Peng <chao.p.peng@linux.intel.com>,
        Liu Jiang <gerry@linux.alibaba.com>,
        Zha Bin <zhabin@linux.alibaba.com>
Subject: [virtio-dev] [PATCH v2 1/5] virtio-mmio: Add feature bit for MMIO
 notification
Date: Tue, 21 Jan 2020 21:54:29 +0800
Message-Id: <1579614873-21907-2-git-send-email-jing2.liu@linux.intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1579614873-21907-1-git-send-email-jing2.liu@linux.intel.com>
References: <1579614873-21907-1-git-send-email-jing2.liu@linux.intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

All the queues notifications use the same register on MMIO transport
layer. Add a feature bit (39) for enhancing the notification capability.
The detailed mechanism would be in next patch.

Co-developed-by: Chao Peng <chao.p.peng@linux.intel.com>
Signed-off-by: Chao Peng <chao.p.peng@linux.intel.com>
Co-developed-by: Liu Jiang <gerry@linux.alibaba.com>
Signed-off-by: Liu Jiang <gerry@linux.alibaba.com>
Co-developed-by: Zha Bin <zhabin@linux.alibaba.com>
Signed-off-by: Zha Bin <zhabin@linux.alibaba.com>
Signed-off-by: Jing Liu <jing2.liu@linux.intel.com>
---
 content.tex | 9 +++++++++
 1 file changed, 9 insertions(+)

```
