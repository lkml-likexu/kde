

#### [PATCH v3 0/7]  KVM: x86/mmu: nVMX: 5-level paging cleanup and
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Mar  3 02:02:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11417061
Return-Path: <SRS0=OzDj=4U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 43A9914E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 02:03:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2317724677
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 02:03:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727061AbgCCCCm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 2 Mar 2020 21:02:42 -0500
Received: from mga05.intel.com ([192.55.52.43]:54060 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726773AbgCCCCm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 2 Mar 2020 21:02:42 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga105.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 02 Mar 2020 18:02:41 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,509,1574150400";
   d="scan'208";a="440384923"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by fmsmga006.fm.intel.com with ESMTP; 02 Mar 2020 18:02:40 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 0/7]  KVM: x86/mmu: nVMX: 5-level paging cleanup and
 enabling
Date: Mon,  2 Mar 2020 18:02:33 -0800
Message-Id: <20200303020240.28494-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Clean up MMU code related to 5 level paging, expose 5-level EPT to L1, and
additional clean up on top (mostly renames of functions/variables that
caused me no end of confusion when trying to figure out what was broken
at various times).

v3:
  - Dropped fixes for existing 5-level bugs (merged for 5.6).
  - Use get_guest_pgd() instead of get_guest_cr3_or_eptp(). [Paolo]
  - Add patches to fix MMU role calculation to play nice with 5-level
    paging without requiring additional CR4.LA_57 bit.

v2:
  - Increase the nested EPT array sizes to accomodate 5-level paging in
    the patch that adds support for 5-level nested EPT, not in the bug
    fix for 5-level shadow paging.

Sean Christopherson (7):
  KVM: x86/mmu: Don't drop level/direct from MMU role calculation
  KVM: x86/mmu: Drop kvm_mmu_extended_role.cr4_la57 hack
  KVM: nVMX: Allow L1 to use 5-level page walks for nested EPT
  KVM: nVMX: Rename nested_ept_get_cr3() to nested_ept_get_eptp()
  KVM: nVMX: Rename EPTP validity helper and associated variables
  KVM: x86/mmu: Rename kvm_mmu->get_cr3() to ->get_guest_pgd()
  KVM: nVMX: Drop unnecessary check on ept caps for execute-only

 arch/x86/include/asm/kvm_host.h |  3 +-
 arch/x86/include/asm/vmx.h      | 12 +++++++
 arch/x86/kvm/mmu/mmu.c          | 59 +++++++++++++++++----------------
 arch/x86/kvm/mmu/paging_tmpl.h  |  4 +--
 arch/x86/kvm/svm.c              |  2 +-
 arch/x86/kvm/vmx/nested.c       | 52 ++++++++++++++++++-----------
 arch/x86/kvm/vmx/nested.h       |  4 +--
 arch/x86/kvm/vmx/vmx.c          |  3 +-
 arch/x86/kvm/x86.c              |  2 +-
 9 files changed, 82 insertions(+), 59 deletions(-)
```
#### [PATCH v1 0/3] x86/kvm/hyper-v: add support for synthetic debugger
##### From: Jon Doron <arilou@gmail.com>

```c
From patchwork Tue Mar  3 13:03:53 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11417965
Return-Path: <SRS0=OzDj=4U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7BED2924
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 13:04:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5AFC520873
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 13:04:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="UwUGsP2p"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728963AbgCCNEG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Mar 2020 08:04:06 -0500
Received: from mail-wm1-f67.google.com ([209.85.128.67]:35649 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728602AbgCCNEG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 3 Mar 2020 08:04:06 -0500
Received: by mail-wm1-f67.google.com with SMTP id m3so2774008wmi.0
        for <kvm@vger.kernel.org>; Tue, 03 Mar 2020 05:04:05 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=vBC2YbhZkJ0v6nz38kCdb3gf7pmanp7d2q2V1CxXpg8=;
        b=UwUGsP2peGrcDb+FuDOl36Uomb459AEZ0alK/qYf7ru06yn03UUn/cWusqOO4GCcdE
         KFyRoWEy+kiGPgcFZk/6AVvEaVjvfyQf1pJRc6Bo4ypA3mLnoNRS6TZKizWJ2txKRFWy
         iQjxA+2zl4NaZI6cdAELzHRg3sY0WEO9hW8BjiwA+kdMxJI2tkaiJMTQu/SzrSm2k0vv
         WM+uNp85yE6gtWw2CWrUZZpJVsMW9P4iNhB0v01RU8vF5sJiJNYTIR0vKI9gsOU5UCwF
         SfS3QEaC24GBmTBtNTIcNXYBbP/E6pA2nxGY75CdyvYUjIN1i72/Vc9Bts/FacI0gpEI
         kwPA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=vBC2YbhZkJ0v6nz38kCdb3gf7pmanp7d2q2V1CxXpg8=;
        b=MN6WtCoY8EpqcobDSKWlKgWG7HvyBVmi37+jmfmqfDhw0uN5r7YPmOLbR1MBnwlHHw
         c8tguPHNUrVPVI0OdNz+AVveRMPxq6o0gUZQxWFRI7bt/BFcpW32inEtI5bk5q9EBmVn
         cE+JVlAhyHVod8QvjadHi1Zn6z+WD+Oi1+VQ8Y2m2amANo+YoRGEr/2Lr2Fs6WAghYwR
         MWmLnycO8OuZiv9+TvRZzwUvQpX/LXCfI4N+m9PfO8Bc+FClRalwdu8dNzvqeAda5TAl
         kQsgOVlc1fW3kAluu+CMmh6rZRnv1qjuizWPMfkmtjgbwkgDzfdOKaCHJBAGXIqIgVRk
         Ov8A==
X-Gm-Message-State: ANhLgQ1jWZNQ59UUrY01hVPRv6da/wL6HF/6YhaCiIj8Bn48ioCAUZXX
        Twq0OtwgeAieh8GedIgSTw/y54V0
X-Google-Smtp-Source: 
 ADFU+vseVsSSieQJRa5AneHGAjY4U2GyG1vV+5VztkMR1npYFfitZgwAHoccfLlVnII9dg4y8imQgg==
X-Received: by 2002:a7b:cb97:: with SMTP id m23mr4051638wmi.37.1583240644595;
        Tue, 03 Mar 2020 05:04:04 -0800 (PST)
Received: from linux.local ([199.203.162.213])
        by smtp.gmail.com with ESMTPSA id
 w17sm2171951wrm.92.2020.03.03.05.04.03
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 03 Mar 2020 05:04:04 -0800 (PST)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v1 0/3] x86/kvm/hyper-v: add support for synthetic debugger
Date: Tue,  3 Mar 2020 15:03:53 +0200
Message-Id: <20200303130356.50405-1-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for the synthetic debugger interface of hyper-v, the
synthetic debugger has 2 modes.
1. Use a set of MSRs to send/recv information
2. Use hypercalls

The first mode is based the following MSRs:
1. Control/Status MSRs which either asks for a send/recv .
2. Send/Recv MSRs each holds GPA where the send/recv buffers are.
3. Pending MSR, holds a GPA to a PAGE that simply has a boolean that
   indicates if there is data pending to issue a recv VMEXIT.

In the first patch the first mode is being implemented in the sense that
it simply exits to user-space when a control MSR is being written and
when the pending MSR is being set, then it's up-to userspace to
implement the rest of the logic of sending/recving.

In the second mode instead of using MSRs KNet will simply issue
Hypercalls with the information to send/recv, in this mode the data
being transferred is UDP encapsulated, unlike in the previous mode in
which you get just the data to send.

The new hypercalls will exit to userspace which will be incharge of
re-encapsulating if needed the UDP packets to be sent.

There is an issue though in which KDNet does not respect the hypercall
page and simply issues vmcall/vmmcall instructions depending on the cpu
type expecting them to be handled as it a real hypercall was issued.

Jon Doron (3):
  x86/kvm/hyper-v: Add support for synthetic debugger capability
  x86/kvm/hyper-v: enable hypercalls regardless of hypercall page
  x86/kvm/hyper-v: Add support for synthetic debugger via hypercalls

 arch/x86/include/asm/hyperv-tlfs.h |  21 +++++
 arch/x86/include/asm/kvm_host.h    |  11 +++
 arch/x86/kvm/hyperv.c              | 122 ++++++++++++++++++++++++++++-
 arch/x86/kvm/hyperv.h              |   5 ++
 arch/x86/kvm/trace.h               |  22 ++++++
 arch/x86/kvm/x86.c                 |   8 ++
 include/uapi/linux/kvm.h           |   9 +++
 7 files changed, 197 insertions(+), 1 deletion(-)
```
#### [PATCH 0/2] KVM: x86: avoid using stale x86_emulate_ctxt->intercept
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue Mar  3 14:33:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11418215
Return-Path: <SRS0=OzDj=4U=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DC3E9174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 14:33:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BC15C20CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue,  3 Mar 2020 14:33:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="IfVVnb+f"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729697AbgCCOdr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 3 Mar 2020 09:33:47 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:30033 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729177AbgCCOdY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 3 Mar 2020 09:33:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583246003;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=eKkzvWfCT/rGHHgN9ulO4K42Kuyz8FLmS0u2A3ohfjg=;
        b=IfVVnb+fi5UCYk6JO1Ryzj9zTuzU7/AqQBXrtniN80/j1s35p4y+GQQgDlneMKMhyoSfY4
        pbR9KgUWhAQDoj9l9EB+s/I4NjPTyZ1QVlunoVo3tBFO+Bb2JtwCheOnI3Y+rWy6j5XIHA
        fQ8TmU9XicxJ32WPB+Z5Wh2tYlx6Yjo=
Received: from mail-wr1-f72.google.com (mail-wr1-f72.google.com
 [209.85.221.72]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-192-dgcx_te_OsGsBn7OvKUUow-1; Tue, 03 Mar 2020 09:33:20 -0500
X-MC-Unique: dgcx_te_OsGsBn7OvKUUow-1
Received: by mail-wr1-f72.google.com with SMTP id 72so1298872wrc.6
        for <kvm@vger.kernel.org>; Tue, 03 Mar 2020 06:33:19 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=eKkzvWfCT/rGHHgN9ulO4K42Kuyz8FLmS0u2A3ohfjg=;
        b=HfGgi2zAxXdgOZNg/jwpCsELuRbuCUwEjIWRWZDy9eAprUOoxwU/8H24Uqniw/CreK
         u9UPtvKxVU15BNYUPpwlTVIA3gGcTn3gxLR7nCQVxkJcb8CPq8Hzomi8wCh4hebtb9j+
         jqw8CWGe9y1/UKqsIIDEbkMvNn9o5h36FhEJeFfqeBqz+6Ba+qPAi2Ww5cIm7XlrC7Ul
         56iUYSv4LA7uCRJIeqewMkBSOofLgB+fMTfrnJl8x1Wp1FqLX0/i+dA1r0cwuDhYpdzi
         NXhlT3GAKvSWB7tquJYr0yhr7ckZL9J0zhlfkZSIJe4+tKDyeiIUM99BG3TZPE+6TBxv
         p0rA==
X-Gm-Message-State: ANhLgQ291+ceJcuYA0nqnIwacqADATMC9aP2LWEDfrGO+bCJs4Ip4iCi
        7GuxJ9qgEOAg/fGz/BWBrYuiinJnn+tUJFpsKEy805vskhEzqsEtZnPSecKgYSuNl1kx+JS/Hed
        5GBQlsyBpVVqf
X-Received: by 2002:a05:6000:12d1:: with SMTP id
 l17mr5426139wrx.327.1583245998956;
        Tue, 03 Mar 2020 06:33:18 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vuh4OGE/Mw192/tAEELL/A48sw9lwJA5J10+koNsf1V2Sdz5rHD/kuhdwpWLwvXp6mm2DxkjA==
X-Received: by 2002:a05:6000:12d1:: with SMTP id
 l17mr5426121wrx.327.1583245998726;
        Tue, 03 Mar 2020 06:33:18 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 s5sm32248504wru.39.2020.03.03.06.33.17
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 03 Mar 2020 06:33:17 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Bandan Das <bsd@redhat.com>, Oliver Upton <oupton@google.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH 0/2] KVM: x86: avoid using stale x86_emulate_ctxt->intercept
 value
Date: Tue,  3 Mar 2020 15:33:14 +0100
Message-Id: <20200303143316.834912-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

After commit 07721feee46b ("KVM: nVMX: Don't emulate instructions in guest
mode") Hyper-V guests on KVM stopped booting and tracing shows that we're
trying to emulate an instruction which shouldn't be intercepted. Turns out,
x86_emulate_ctxt may hold a stale 'intercept' value.

This is a regression in 5.6-rc4 and I'm marking PATCH1 for stable@. The
commit 07721feee46b ("KVM: nVMX: Don't emulate instructions in guest mode")
is, however, correct, it just seems to reveal a pre-existing condition.

Vitaly Kuznetsov (2):
  KVM: x86: clear stale x86_emulate_ctxt->intercept value
  KVM: x86: remove stale comment from struct x86_emulate_ctxt

 arch/x86/include/asm/kvm_emulate.h | 1 -
 arch/x86/kvm/emulate.c             | 1 +
 2 files changed, 1 insertion(+), 1 deletion(-)
```
