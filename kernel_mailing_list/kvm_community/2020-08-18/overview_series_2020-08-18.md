#### [PATCH v2 1/2] clocksource: arm_arch_timer: Use stable count reader in erratum sne
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 11719731
Return-Path: <SRS0=3jrS=B4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 65FC614E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 03:28:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 57F93207DE
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 03:28:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726620AbgHRD23 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 23:28:29 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:9826 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726422AbgHRD22 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 23:28:28 -0400
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id 65EAAF6D45FC0316F09F;
        Tue, 18 Aug 2020 11:28:25 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.22) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.487.0; Tue, 18 Aug 2020 11:28:17 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>, Steven Price <steven.price@arm.com>,
        "Andrew Jones" <drjones@redhat.com>,
        Catalin Marinas <catalin.marinas@arm.com>,
        "Will Deacon" <will@kernel.org>, James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH v2 1/2] clocksource: arm_arch_timer: Use stable count reader
 in erratum sne
Date: Tue, 18 Aug 2020 11:28:13 +0800
Message-ID: <20200818032814.15968-2-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
In-Reply-To: <20200818032814.15968-1-zhukeqian1@huawei.com>
References: <20200818032814.15968-1-zhukeqian1@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.174.187.22]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In commit 0ea415390cd3 ("clocksource/arm_arch_timer: Use arch_timer_read_counter
to access stable counters"), we separate stable and normal count reader to omit
unnecessary overhead on systems that have no timer erratum.

However, in erratum_set_next_event_tval_generic(), count reader becomes normal
reader. This converts it to stable reader.

Fixes: 0ea415390cd3 ("clocksource/arm_arch_timer: Use
       arch_timer_read_counter to access stable counters")
Signed-off-by: Keqian Zhu <zhukeqian1@huawei.com>
---
 drivers/clocksource/arm_arch_timer.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: nVMX: Update VMCS02 when L2 PAE PDPTE updates detectedFrom: Peter Shier <pshier@google.com>
##### From: Peter Shier <pshier@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Shier <pshier@google.com>
X-Patchwork-Id: 11719635
Return-Path: <SRS0=3jrS=B4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 288F8739
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 00:43:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 079CF2078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 00:43:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="KrEYMFT2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726585AbgHRAnX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 20:43:23 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35404 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726314AbgHRAnX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 20:43:23 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id AF7B5C061389
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 17:43:22 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id w11so20281480ybi.23
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 17:43:22 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=xsihmYEi0cy/CSZ0Xb7y6TGtb2M86BbKpaGP6G3YVvk=;
        b=KrEYMFT2I3BsS/bTX6pLvk96k4+26Ne8DE+PP41/zz9iQ76VNIm9JCRCxJRWwYb+m3
         fHOcM+LhjLyCKSCL4FTlaXp8/La60CCzB/N3s8DzDRuAwqicwBwCUCS3Rf4Oj0eR4rkJ
         J1IUZ/dzPuXtMAvROOVI0lNS6jxA7zK9b+lLbmfGhUgYxsbZpVOZOjOvNMZ6/fBVGvlT
         ZOFkE3l7EH2CU1vffY7LrBOW7IroqPn8QoV7ep/KVseTTNLcmJR4vJpDfoNW4m5jWYca
         FbE9166SG1TSc2pzIjDuhVlWyXhQQqQjO2ttWAwpJoOdwr5WeAgas/GbK8lzEy5BSFhS
         gpEw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=xsihmYEi0cy/CSZ0Xb7y6TGtb2M86BbKpaGP6G3YVvk=;
        b=H9ipraccE8joL/nrKzrLegU9msLJkxI0Jg/akjeTtFwgsoFoTpl4G7e8dCPqEiDi4w
         VWHl4FhFChdnsynp37NVblQUfc8VbXu0Pg/AZXqo55yym0b/lgwUZqMrtXzLi/sjCPj4
         MsCZCRKjsuOF6UJCYv7F/sCyxrzRq/x+INerdc1X/HqdZ9F4VI48p5KW0x05g4QefMPX
         DuS+sJ1XgzfsO2BD0NUduDBeeTkKez1tgmYWGv1yB084pNK/CO0Jg5QrU9sldJJ90c36
         oRWx+/Gu4oTUiICFnMK8nhOJK5BCA/v4o/l5Ytwb64M6Rv+oPZGXKWgmdEeUPgtjAakT
         zYOA==
X-Gm-Message-State: AOAM5322iiEwFTJ6mt5jfiz3SulAayrygzuV74JPRMB/R/9WSoqL1W0C
        Wl1dZ62VM436afs/+6MK2hSry/4D4w61pwQl2cscIWERNxy5WUjtDCc0gXaAR0Vv+e1GbGdwv1m
        uRAT4mgVa+thETUx4xfD5DW4qCY8qSghbtbWVN2u/E7Am9j2dQ8MAfcW0gw==
X-Google-Smtp-Source: 
 ABdhPJxQXfMFUJRbY8Jbi5/vqsjKYj1kpLhnXPTHgUHOBp9BKHX/nqK8ihL1Ar95JokdcirYmlG18OcliT8=
X-Received: by 2002:a25:e015:: with SMTP id x21mr23229287ybg.1.1597711401685;
 Mon, 17 Aug 2020 17:43:21 -0700 (PDT)
Date: Mon, 17 Aug 2020 17:43:14 -0700
Message-Id: <20200818004314.216856-1-pshier@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.220.ged08abb693-goog
Subject: [PATCH] KVM: nVMX: Update VMCS02 when L2 PAE PDPTE updates detected
From: Peter Shier <pshier@google.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When L2 uses PAE, L0 intercepts of L2 writes to CR0/CR3/CR4 call
load_pdptrs to read the possibly updated PDPTEs from the guest
physical address referenced by CR3.  It loads them into
vcpu->arch.walk_mmu->pdptrs[] and sets VCPU_EXREG_PDPTR in
vcpu->arch.regs_dirty.

At the subsequent assumed reentry into L2, the mmu will call
vmx_load_mmu_pgd which calls ept_load_pdptrs. ept_load_pdptrs sees
VCPU_EXREG_PDPTR set in vcpu->arch.regs_dirty and loads
VMCS02.GUEST_PDPTRn from vcpu->arch.walk_mmu->pdptrs[]. This all works
if the L2 CRn write intercept always resumes L2.

The resume path calls vmx_check_nested_events which checks for
exceptions, MTF, and expired VMX preemption timers. If
vmx_check_nested_events finds any of these conditions pending it will
reflect the corresponding exit into L1. Live migration at this point
would also cause a missed immediate reentry into L2.

After L1 exits, vmx_vcpu_run calls vmx_register_cache_reset which
clears VCPU_EXREG_PDPTR in vcpu->arch.regs_dirty.  When L2 next
resumes, ept_load_pdptrs finds VCPU_EXREG_PDPTR clear in
vcpu->arch.regs_dirty and does not load VMCS02.GUEST_PDPTRn from
vcpu->arch.walk_mmu->pdptrs[]. prepare_vmcs02 will then load
VMCS02.GUEST_PDPTRn from vmcs12->pdptr0/1/2/3 which contain the stale
values stored at last L2 exit. A repro of this bug showed L2 entering
triple fault immediately due to the bad VMCS02.GUEST_PDPTRn values.

Add a new x86 op to enable vendor-specific code to process the PDPTE
updates. For Intel, when in guest mode using PAE, update
VMCS02.GUEST_PDPTRn from the newly loaded values.

Tested:
kvm-unit-tests with new directed test: vmx_mtf_pdpte_test.
Verified that test fails without the fix.

Also ran Google internal VMM with an Ubuntu 16.04 4.4.0-83 guest
running a custom hypervisor with a 32-bit Windows XP L2 guest using
PAE. Prior to fix would repro readily. Ran with fix for 13 hours
booting 14 simultaneous L2s with no failures.

Signed-off-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/vmx/vmx.c          | 11 +++++++++++
 arch/x86/kvm/x86.c              |  2 ++
 3 files changed, 14 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: vmx: Add test for MTF on a guest MOV-to-CR0 that enables PAE
##### From: Peter Shier <pshier@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Shier <pshier@google.com>
X-Patchwork-Id: 11719633
Return-Path: <SRS0=3jrS=B4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E2B20138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 00:26:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BA54E20789
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 00:26:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Kh+APvoW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726878AbgHRA0E (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Aug 2020 20:26:04 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:60904 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726592AbgHRA0B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Aug 2020 20:26:01 -0400
Received: from mail-pj1-x1049.google.com (mail-pj1-x1049.google.com
 [IPv6:2607:f8b0:4864:20::1049])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2CC12C061389
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 17:26:01 -0700 (PDT)
Received: by mail-pj1-x1049.google.com with SMTP id gf16so11316031pjb.7
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 17:26:01 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=8e+ox54HeK88rWVSIgwtx//BruEjCGyJapM29hBKsLs=;
        b=Kh+APvoW+7VppqIfU0DKewAtfFxv/pb4x3K8GZBVNs3LprUDdDaDUhSrfaOdIjYLQv
         DMJfUL71DMo1EiUbmHR9VAWo6NYtD94AtenYyp4j34gHOo/jv8QlOrVc7jCfkcfOyG+C
         6lor/JoAOHm0G4Lw6pfzR58wadYJmcEvSgG0YbyOsuVMvTN3U6gRRICQKs+dNgInGwjC
         VgtPAzq2sW40wXNTkG3emGLTMVhBfI/sis1GJ8HCIhV3OPv8YvHLxyj+pbU3v27Kr+QN
         wL9Kimxd9W4Dgqm+coiP8YQMByZOLQly3rjkLHVp7hKlQBGmcXJ0KXlaFReRt6ZpNFGJ
         zevg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=8e+ox54HeK88rWVSIgwtx//BruEjCGyJapM29hBKsLs=;
        b=JCB9/wZCQ/o/fkeLFiFsl27A17jiRWAAtrHx0onH+TJO7kEMwRzACaqrekePMjSdHe
         MMCesvW4nBo9iCta+ZUpRRsyzWBzCYBqpGiKEvL/JLPKgJhywbqcZCGf3oTtJm9ZyWEt
         SmHm01fINC+ip/LsYpF3tEy/xN3sbio2/DZvgUoNZb3xjjoLgLF3HRJ2AfTX0WPloSkb
         ZcAFFVHfqhV3Z8zmQmiIjNFNraNrNQyvniiyEcMC1LZ9Vz4U0/EEBW+tpzvhLLmNA4bf
         oOYlELaL3qTlxY0fn2c/vXo2SdIb1Gxh8izgSISjksaIERxYYsF3BTu2PjAnMmf1tI60
         watg==
X-Gm-Message-State: AOAM5338KM+njCVxa4cdfX+dBjtzyUXM5Rgat7yEA5kHEBMubJTPefyP
        REF5Dr2EKf5iuqmXdJKdbZSCVKv5eQCoTfL2TpdFaNFVbOaiPYj07JMRKIh7Eh+ehNnrfN4208f
        U8RQ8K0EhvSRLmEbDKgdqskwGk3T+fHtBTgHQ9YuglWmLqs0PBbINITPHlQ==
X-Google-Smtp-Source: 
 ABdhPJwqh6wVv3hpbQdwkFV2FcUx5H3CMt90SRBihCQuFvk5n/4I9GB8rDMIMxJ7TB+z9a7ekRGflmBGUdk=
X-Received: by 2002:a63:6a47:: with SMTP id
 f68mr11669331pgc.358.1597710360297;
 Mon, 17 Aug 2020 17:26:00 -0700 (PDT)
Date: Mon, 17 Aug 2020 17:25:37 -0700
Message-Id: <20200818002537.207910-1-pshier@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.28.0.220.ged08abb693-goog
Subject: [kvm-unit-tests PATCH] x86: vmx: Add test for MTF on a guest
 MOV-to-CR0 that enables PAE
From: Peter Shier <pshier@google.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Peter Shier <pshier@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Verify that when L2 guest enables PAE paging and L0 intercept of L2
MOV to CR0 reflects MTF exit to L1, subsequent resume to L2 correctly
preserves PDPTE array specified by L2 CR3.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by:   Peter Shier <pshier@google.com>
Signed-off-by: Peter Shier <pshier@google.com>
---
 lib/x86/asm/page.h |   8 +++
 x86/vmx_tests.c    | 171 +++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 179 insertions(+)

```
#### [PATCH V2 1/2] Add new flush_iotlb_range and handle freelists when using iommu_unmap_fast
##### From: Tom Murphy <murphyt7@tcd.ie>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Murphy <murphyt7@tcd.ie>
X-Patchwork-Id: 11720009
Return-Path: <SRS0=3jrS=B4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 69A36138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 06:04:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 435272075B
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Aug 2020 06:04:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=tcd-ie.20150623.gappssmtp.com
 header.i=@tcd-ie.20150623.gappssmtp.com header.b="iQoP9q5a"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726763AbgHRGE3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Aug 2020 02:04:29 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56444 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726228AbgHRGEY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Aug 2020 02:04:24 -0400
Received: from mail-pg1-x542.google.com (mail-pg1-x542.google.com
 [IPv6:2607:f8b0:4864:20::542])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 31E81C061342
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 23:04:24 -0700 (PDT)
Received: by mail-pg1-x542.google.com with SMTP id j21so9250487pgi.9
        for <kvm@vger.kernel.org>; Mon, 17 Aug 2020 23:04:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=tcd-ie.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=y5qrCdJ/OE387CTmjzbFa6dLZo1LR3W3T8lBKPh7CDY=;
        b=iQoP9q5antePhXxIUKN+7dG0Ir/SPsXZuUb6eA/NM4CU/YeC8HipTQIguDfSVhzQ+g
         xqkB1/BT8jYAqB8iwXP9RpwwggWal6sOcg/u3CRFGwl6KGEVD4hzQYttoLqNEhzEP365
         tsZ1njUX0JhwzXy4rNETnE+NDErOKqFORD6KSoXvoGNYzZvRDh9l5tfTxfT4g1BS3MCF
         cQNv3hI5MkRUXsmdgCYkBkwRLY3V5zRUifo/KP/7bqx92yCXOC4jC9mecL6H6bqyWJhX
         qYvROS8V7rC+EKPT265AJS86rWnfWWSvrk4Psg3EsT0P0KHWA3Iab4YNyinb/KjxN3RF
         0dUg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=y5qrCdJ/OE387CTmjzbFa6dLZo1LR3W3T8lBKPh7CDY=;
        b=TizNUAozQe9dHA7YgGk7GrVqLtA3rgxHzuM/XYPWPKgNw4Ei82TM+eGTeh5g4VuF/k
         P1uXraQEbuc8UaeH6I0J4JjHXfXiRYTow45hCiBLLrECG9a8lBfeNRcMq6PyJPr23Ttm
         ofBVN8ocwveGQbp+QXV7gFZmiOcUgBj5byP8jJJRIKkeTvPBPMvKTp4FmazUX8ppGsAN
         n+iWV/o32ojFl34IE8QsYPaT3h/YWwAWd/A3lEDRgRROikU/x4Ghy1hoNW0+buRebb30
         lflc4RnhhKzL87367Hbf3IbwBTIntzaePfqzmRMzcWB24jUUBIDqSv2TWlDEUtASjzjw
         XS8w==
X-Gm-Message-State: AOAM530TrSlsGlnga7jxNHi2Z55k2VX2FWkTIJXYPTwF7R4KAfTlmWWM
        xmYkVyFAtaVrztylOjxIB/JoYA==
X-Google-Smtp-Source: 
 ABdhPJxjoS3Y9Z503jTVnOBc9Q7Gd6hLH0HTSCioGxcvSuQNdF5T8D8Q2PNvxTJu//iHHK+qutliPA==
X-Received: by 2002:a63:eb14:: with SMTP id t20mr3420641pgh.236.1597730663463;
        Mon, 17 Aug 2020 23:04:23 -0700 (PDT)
Received: from tom-ThinkPad-X1-Carbon-5th.teksavvy.com ([69.172.145.184])
        by smtp.googlemail.com with ESMTPSA id
 v10sm7102985pjy.3.2020.08.17.23.04.21
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 17 Aug 2020 23:04:22 -0700 (PDT)
From: Tom Murphy <murphyt7@tcd.ie>
To: iommu@lists.linux-foundation.org
Cc: Tom Murphy <murphyt7@tcd.ie>, Joerg Roedel <joro@8bytes.org>,
        Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Marek Szyprowski <m.szyprowski@samsung.com>,
        Kukjin Kim <kgene@kernel.org>,
        Krzysztof Kozlowski <krzk@kernel.org>,
        David Woodhouse <dwmw2@infradead.org>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        Andy Gross <agross@kernel.org>,
        Bjorn Andersson <bjorn.andersson@linaro.org>,
        Matthias Brugger <matthias.bgg@gmail.com>,
        Rob Clark <robdclark@gmail.com>,
        Heiko Stuebner <heiko@sntech.de>,
        Matthew Rosato <mjrosato@linux.ibm.com>,
        Gerald Schaefer <gerald.schaefer@linux.ibm.com>,
        Maxime Ripard <mripard@kernel.org>,
        Chen-Yu Tsai <wens@csie.org>,
        Thierry Reding <thierry.reding@gmail.com>,
        Jonathan Hunter <jonathanh@nvidia.com>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        linux-samsung-soc@vger.kernel.org, linux-arm-msm@vger.kernel.org,
        linux-mediatek@lists.infradead.org,
        linux-rockchip@lists.infradead.org, linux-s390@vger.kernel.org,
        linux-tegra@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Subject: [PATCH V2 1/2] Add new flush_iotlb_range and handle freelists when
 using iommu_unmap_fast
Date: Tue, 18 Aug 2020 07:04:13 +0100
Message-Id: <20200818060415.19522-1-murphyt7@tcd.ie>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a flush_iotlb_range to allow flushing of an iova range instead of a
full flush in the dma-iommu path.

Allow the iommu_unmap_fast to return newly freed page table pages and
pass the freelist to queue_iova in the dma-iommu ops path.

This patch is useful for iommu drivers (in this case the intel iommu
driver) which need to wait for the ioTLB to be flushed before newly
free/unmapped page table pages can be freed. This way we can still batch
ioTLB free operations and handle the freelists.

Change-log:
V2:
-fix missing parameter in mtk_iommu_v1.c

Signed-off-by: Tom Murphy <murphyt7@tcd.ie>
---
 drivers/iommu/amd/iommu.c       | 14 ++++++++-
 drivers/iommu/arm-smmu-v3.c     |  3 +-
 drivers/iommu/arm-smmu.c        |  3 +-
 drivers/iommu/dma-iommu.c       | 45 ++++++++++++++++++++-------
 drivers/iommu/exynos-iommu.c    |  3 +-
 drivers/iommu/intel/iommu.c     | 54 +++++++++++++++++++++------------
 drivers/iommu/iommu.c           | 25 +++++++++++----
 drivers/iommu/ipmmu-vmsa.c      |  3 +-
 drivers/iommu/msm_iommu.c       |  3 +-
 drivers/iommu/mtk_iommu.c       |  3 +-
 drivers/iommu/mtk_iommu_v1.c    |  3 +-
 drivers/iommu/omap-iommu.c      |  3 +-
 drivers/iommu/qcom_iommu.c      |  3 +-
 drivers/iommu/rockchip-iommu.c  |  3 +-
 drivers/iommu/s390-iommu.c      |  3 +-
 drivers/iommu/sun50i-iommu.c    |  3 +-
 drivers/iommu/tegra-gart.c      |  3 +-
 drivers/iommu/tegra-smmu.c      |  3 +-
 drivers/iommu/virtio-iommu.c    |  3 +-
 drivers/vfio/vfio_iommu_type1.c |  2 +-
 include/linux/iommu.h           | 21 +++++++++++--
 21 files changed, 150 insertions(+), 56 deletions(-)

```
