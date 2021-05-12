

#### [PATCH v6 00/16] KVM: x86/pmu: Add *basic* support to enable guest
##### From: Like Xu <like.xu@linux.intel.com>

```c
From patchwork Tue May 11 02:41:58 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 12249553
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 09359C433B4
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 02:43:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B6C0861493
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 02:43:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229961AbhEKCoG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 10 May 2021 22:44:06 -0400
Received: from mga03.intel.com ([134.134.136.65]:7532 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229736AbhEKCoF (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 May 2021 22:44:05 -0400
IronPort-SDR: 
 t90OgSPonnSFugn6KNmpCRaXLXGCw1VrmI6oPV/n6Ex+nQ7HYShStgIaKXZ53HFvTz2K+F48Ys
 hzlIMfgY6ovQ==
X-IronPort-AV: E=McAfee;i="6200,9189,9980"; a="199391164"
X-IronPort-AV: E=Sophos;i="5.82,290,1613462400";
   d="scan'208";a="199391164"
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 10 May 2021 19:42:59 -0700
IronPort-SDR: 
 Z03bXJI/8do50E4Zh/vuxfVx4lcNmGPAzxpCKCVzDAQOxyR7ZK16WbZZ5UGca0UvBrj9eW3gE4
 Mmd+gitL6BwQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.82,290,1613462400";
   d="scan'208";a="468591513"
Received: from clx-ap-likexu.sh.intel.com ([10.239.48.108])
  by fmsmga002.fm.intel.com with ESMTP; 10 May 2021 19:42:55 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, weijiang.yang@intel.com,
        Kan Liang <kan.liang@linux.intel.com>, ak@linux.intel.com,
        wei.w.wang@intel.com, eranian@google.com, liuxiangdong5@huawei.com,
        linux-kernel@vger.kernel.org, x86@kernel.org, kvm@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v6 00/16] KVM: x86/pmu: Add *basic* support to enable guest
 PEBS via DS
Date: Tue, 11 May 2021 10:41:58 +0800
Message-Id: <20210511024214.280733-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A new kernel cycle has begun, and this version looks promising.

The guest Precise Event Based Sampling (PEBS) feature can provide
an architectural state of the instruction executed after the guest
instruction that exactly caused the event. It needs new hardware
facility only available on Intel Ice Lake Server platforms. This
patch set enables the basic PEBS feature for KVM guests on ICX.

We can use PEBS feature on the Linux guest like native:

  # perf record -e instructions:ppp ./br_instr a
  # perf record -c 100000 -e instructions:pp ./br_instr a

To emulate guest PEBS facility for the above perf usages,
we need to implement 2 code paths:

1) Fast path

This is when the host assigned physical PMC has an identical index as
the virtual PMC (e.g. using physical PMC0 to emulate virtual PMC0).
This path is used in most common use cases.

2) Slow path

This is when the host assigned physical PMC has a different index
from the virtual PMC (e.g. using physical PMC1 to emulate virtual PMC0)
In this case, KVM needs to rewrite the PEBS records to change the
applicable counter indexes to the virtual PMC indexes, which would
otherwise contain the physical counter index written by PEBS facility,
and switch the counter reset values to the offset corresponding to
the physical counter indexes in the DS data structure.

The previous version [0] enables both fast path and slow path, which
seems a bit more complex as the first step. In this patchset, we want
to start with the fast path to get the basic guest PEBS enabled while
keeping the slow path disabled. More focused discussion on the slow
path [1] is planned to be put to another patchset in the next step.

Compared to later versions in subsequent steps, the functionality
to support host-guest PEBS both enabled and the functionality to
emulate guest PEBS when the counter is cross-mapped are missing
in this patch set (neither of these are typical scenarios).

With the basic support, the guest can retrieve the correct PEBS
information from its own PEBS records on the Ice Lake servers.
And we expect it should work when migrating to another Ice Lake
and no regression about host perf is expected.

Here are the results of pebs test from guest/host for same workload:

perf report on guest:
# Samples: 2K of event 'instructions:ppp', # Event count (approx.): 1473377250
# Overhead  Command   Shared Object      Symbol
  57.74%  br_instr  br_instr           [.] lfsr_cond
  41.40%  br_instr  br_instr           [.] cmp_end
   0.21%  br_instr  [kernel.kallsyms]  [k] __lock_acquire

perf report on host:
# Samples: 2K of event 'instructions:ppp', # Event count (approx.): 1462721386
# Overhead  Command   Shared Object     Symbol
  57.90%  br_instr  br_instr          [.] lfsr_cond
  41.95%  br_instr  br_instr          [.] cmp_end
   0.05%  br_instr  [kernel.vmlinux]  [k] lock_acquire
   Conclusion: the profiling results on the guest are similar tothat on the host.

A minimum guest kernel version may be v5.4 or a backport version
support Icelake server PEBS.

Please check more details in each commit and feel free to comment.

Previous:
https://lore.kernel.org/kvm/20210415032016.166201-1-like.xu@linux.intel.com/

[0] https://lore.kernel.org/kvm/20210104131542.495413-1-like.xu@linux.intel.com/
[1] https://lore.kernel.org/kvm/20210115191113.nktlnmivc3edstiv@two.firstfloor.org/

V5 -> V6 Changelog:
- Rebased on the latest kvm/queue tree;
- Fix a git rebase issue (Liuxiangdong);
- Adjust the patch sequence 06/07 for bisection (Liuxiangdong);

Like Xu (16):
  perf/x86/intel: Add EPT-Friendly PEBS for Ice Lake Server
  perf/x86/intel: Handle guest PEBS overflow PMI for KVM guest
  perf/x86/core: Pass "struct kvm_pmu *" to determine the guest values
  KVM: x86/pmu: Set MSR_IA32_MISC_ENABLE_EMON bit when vPMU is enabled
  KVM: x86/pmu: Introduce the ctrl_mask value for fixed counter
  KVM: x86/pmu: Add IA32_PEBS_ENABLE MSR emulation for extended PEBS
  KVM: x86/pmu: Reprogram PEBS event to emulate guest PEBS counter
  KVM: x86/pmu: Add IA32_DS_AREA MSR emulation to support guest DS
  KVM: x86/pmu: Add PEBS_DATA_CFG MSR emulation to support adaptive PEBS
  KVM: x86: Set PEBS_UNAVAIL in IA32_MISC_ENABLE when PEBS is enabled
  KVM: x86/pmu: Adjust precise_ip to emulate Ice Lake guest PDIR counter
  KVM: x86/pmu: Move pmc_speculative_in_use() to arch/x86/kvm/pmu.h
  KVM: x86/pmu: Disable guest PEBS temporarily in two rare situations
  KVM: x86/pmu: Add kvm_pmu_cap to optimize perf_get_x86_pmu_capability
  KVM: x86/cpuid: Refactor host/guest CPU model consistency check
  KVM: x86/pmu: Expose CPUIDs feature bits PDCM, DS, DTES64

 arch/x86/events/core.c            |   5 +-
 arch/x86/events/intel/core.c      | 129 ++++++++++++++++++++++++------
 arch/x86/events/perf_event.h      |   5 +-
 arch/x86/include/asm/kvm_host.h   |  16 ++++
 arch/x86/include/asm/msr-index.h  |   6 ++
 arch/x86/include/asm/perf_event.h |   5 +-
 arch/x86/kvm/cpuid.c              |  24 ++----
 arch/x86/kvm/cpuid.h              |   5 ++
 arch/x86/kvm/pmu.c                |  50 +++++++++---
 arch/x86/kvm/pmu.h                |  38 +++++++++
 arch/x86/kvm/vmx/capabilities.h   |  26 ++++--
 arch/x86/kvm/vmx/pmu_intel.c      | 115 +++++++++++++++++++++-----
 arch/x86/kvm/vmx/vmx.c            |  24 +++++-
 arch/x86/kvm/vmx/vmx.h            |   2 +-
 arch/x86/kvm/x86.c                |  14 ++--
 15 files changed, 368 insertions(+), 96 deletions(-)
```
#### [PATCH 0/7] KVM: nVMX: Fixes for nested state migration when eVMCS is
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue May 11 11:19:49 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12250683
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.5 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 923FDC433ED
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 11:20:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5E1966193A
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 11:20:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231393AbhEKLVM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 07:21:12 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:28639 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230483AbhEKLVL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 11 May 2021 07:21:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620732004;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=R2FIcJy0FhG18L85AGaMz34fEcXRgkeJKI2TAP1uabE=;
        b=KlogoGDKO1Pf4EcngUTgAmVTR7MMCzJFJpuK0vh1tHGDIp8ERxAQswpcpyLWU4iF67odJC
        Rg7IhhwVwuntWKR1TRhtAOmL2qHvxd7kRhsyqMOUZOk52kn4C6d8TEM5QjtR6HeBJ69f6K
        zTf1QmCF4wkxZuywY4UUNnRPDJy6LI4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-503-6w7aAOSuOMKj46QWvgFSyw-1; Tue, 11 May 2021 07:20:03 -0400
X-MC-Unique: 6w7aAOSuOMKj46QWvgFSyw-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A94AF8015F3;
        Tue, 11 May 2021 11:20:01 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.2])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 520A163746;
        Tue, 11 May 2021 11:19:57 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: linux-kernel@vger.kernel.org,
        Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/7] KVM: nVMX: Fixes for nested state migration when eVMCS is
 in use
Date: Tue, 11 May 2021 13:19:49 +0200
Message-Id: <20210511111956.1555830-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit f5c7e8425f18 ("KVM: nVMX: Always make an attempt to map eVMCS after
migration") fixed the most obvious reason why Hyper-V on KVM (e.g. Win10
 + WSL2) was crashing immediately after migration. It was also reported
that we have more issues to fix as, while the failure rate was lowered 
signifincatly, it was still possible to observe crashes after several
dozens of migration. Turns out, the issue arises when we manage to issue
KVM_GET_NESTED_STATE right after L2->L2 VMEXIT but before L1 gets a chance
to run. This state is tracked with 'need_vmcs12_to_shadow_sync' flag but
the flag itself is not part of saved nested state. A few other less 
significant issues are fixed along the way.

While there's no proof this series fixes all eVMCS related problems,
Win10+WSL2 was able to survive 500 migrations without crashing in my
testing.

Patches are based on the current kvm/next tree.

Vitaly Kuznetsov (7):
  KVM: nVMX: Introduce nested_evmcs_is_used()
  KVM: nVMX: Release enlightened VMCS on VMCLEAR
  KVM: nVMX: Ignore 'hv_clean_fields' data when eVMCS data is copied in
    vmx_get_nested_state()
  KVM: nVMX: Force enlightened VMCS sync from nested_vmx_failValid()
  KVM: nVMX: Reset eVMCS clean fields data from prepare_vmcs02()
  KVM: nVMX: Request to sync eVMCS from VMCS12 after migration
  KVM: selftests: evmcs_test: Test that KVM_STATE_NESTED_EVMCS is never
    lost

 arch/x86/kvm/vmx/nested.c                     | 99 +++++++++++++------
 .../testing/selftests/kvm/x86_64/evmcs_test.c | 64 +++++++-----
 2 files changed, 109 insertions(+), 54 deletions(-)
```
#### [PATCH v4 0/7] Lazily allocate memslot rmaps
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Tue May 11 17:16:03 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12251565
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 98E6DC433B4
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 17:16:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5922561376
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 17:16:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231549AbhEKRRY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 13:17:24 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:58680 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230315AbhEKRRY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 May 2021 13:17:24 -0400
Received: from mail-pl1-x649.google.com (mail-pl1-x649.google.com
 [IPv6:2607:f8b0:4864:20::649])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id C979BC061574
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 10:16:16 -0700 (PDT)
Received: by mail-pl1-x649.google.com with SMTP id
 g9-20020a170902c989b02900eeeaddbedbso7860890plc.14
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 10:16:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=wrxaJJ4wLpCH56K58T42qTboLrClp3cmD5uAO6GdTRk=;
        b=l76qbi6P/SehrOCp1qoEGbmTbqEjj4eJr4tyEsEw5XLxrzDMoThXR04U+df2NUu/+Y
         E7aAXlcsZLelYuyCoWUXythfKFTbDP/kX9h1dxdNGe/X33qbmPybZLuNOdqwuSUOBXBL
         KeU12UlxGZRDTPCuc08B02zNsly3bT0CWAb9XTVPO83jzjHqSlJfSiGH8wkyUFtqVWIk
         pgZSRZvmJqy7V8YWbO3ipdnnq6G7OxQm5kPFpSVHOzEy77EhsKfa1PuIuad/oq0hTzYV
         XvEcCuuCtefkvI6sYc7KrrsLH1la38zf91sPNYEVUcGokifhJ9ukNA6KFqQLrmpT6OIT
         EX+w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=wrxaJJ4wLpCH56K58T42qTboLrClp3cmD5uAO6GdTRk=;
        b=mr0YDh6ZaO572GHXOBKScGmcFMMef9b+g2Hj61pgfez252l3h/k7nPrgfMPNUJ+egA
         rRpGuMOVpX9PEtEKkWlMx3tE58DtCoH91VS1XMbiecd9LAvKZRKIUu37yewlrCS/LPqr
         MgE0dhNElG4+ybUjU87nkCQALOJv/I8SocyKIC9aou+cn59IfoMxvAG3i0RZZozPz16x
         ORa1MMWhlRIKRgBWWRlk8oH3bctDly2jnv1XzjiOouLAHjacvjun8Zp8e1ch/qugoxw7
         o4+e1d2YZfdGgWenEkVfGl4R9g48KVyjBGy4s1MdJlrXnmO+fWHDU98G5p9Zm+omlxIG
         R0xw==
X-Gm-Message-State: AOAM533ZyCtuF8PyMsHjdapIGS0PRTbt8usQTP8GGfuj24oydKzknGhp
        3Ajea5aX27HG7WDPVJI2LIkm3L5xSYcJ
X-Google-Smtp-Source: 
 ABdhPJwVNckP1kFfI7u/oxNIHTRqrzbcv7RwGflHnvJz47IsbxuNA+DgWKVR71xplchbLOkK0r5aknV/aaeB
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:e050:3342:9ea6:6859])
 (user=bgardon job=sendgmr) by 2002:a62:dd90:0:b029:2bd:f232:16fa with SMTP id
 w138-20020a62dd900000b02902bdf23216famr12666445pff.54.1620753376110; Tue, 11
 May 2021 10:16:16 -0700 (PDT)
Date: Tue, 11 May 2021 10:16:03 -0700
Message-Id: <20210511171610.170160-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH v4 0/7] Lazily allocate memslot rmaps
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Kai Huang <kai.huang@intel.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        David Hildenbrand <david@redhat.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enables KVM to save memory when using the TDP MMU by waiting
to allocate memslot rmaps until they are needed. To do this, KVM tracks
whether or not a shadow root has been allocated. In order to get away
with not allocating the rmaps, KVM must also be sure to skip operations
which iterate over the rmaps. If the TDP MMU is in use and we have not
allocated a shadow root, these operations would essentially be op-ops
anyway. Skipping the rmap operations has a secondary benefit of avoiding
acquiring the MMU lock in write mode in many cases, substantially
reducing MMU lock contention.

This series was tested on an Intel Skylake machine. With the TDP MMU off
and on, this introduced no new failures on kvm-unit-tests or KVM selftests.

Changelog:
v2:
	Incorporated feedback from Paolo and Sean
	Replaced the memslot_assignment_lock with slots_arch_lock, which
	has a larger critical section.

v3:
	Removed shadow_mmu_active as suggested by Sean
	Removed everything except adding a return value to
	kvm_mmu_init_tdp_mmu from patch 1 of v2
	Added RCU protection and better memory ordering for installing the
	memslot rmaps as suggested by Paolo
	Reordered most of the patches

v4:
	Renamed functions to allocate and free memslots based on feedback
	from David.
	Eliminated the goto in memslot_rmap_alloc, as David suggested.
	Eliminated kvm_memslots_have_rmaps and updated comments on uses of
	memslots_have_rmaps. Suggested by Paolo.
	Changed the description on patch 7 to one Paolo suggested.
	Collected Reviewed-by tags from David.
	Dropped the patch to add RCU notations to rmap accesses.

Ben Gardon (7):
  KVM: x86/mmu: Deduplicate rmap freeing
  KVM: x86/mmu: Factor out allocating memslot rmap
  KVM: mmu: Refactor memslot copy
  KVM: mmu: Add slots_arch_lock for memslot arch fields
  KVM: x86/mmu: Add a field to control memslot rmap allocation
  KVM: x86/mmu: Skip rmap operations if rmaps not allocated
  KVM: x86/mmu: Lazily allocate memslot rmaps

 arch/x86/include/asm/kvm_host.h |   8 ++
 arch/x86/kvm/mmu/mmu.c          | 153 +++++++++++++++++++++-----------
 arch/x86/kvm/mmu/tdp_mmu.c      |   6 +-
 arch/x86/kvm/mmu/tdp_mmu.h      |   4 +-
 arch/x86/kvm/x86.c              | 108 ++++++++++++++++++----
 include/linux/kvm_host.h        |   9 ++
 virt/kvm/kvm_main.c             |  54 ++++++++---
 7 files changed, 255 insertions(+), 87 deletions(-)
```
#### [PATCH kvm-unit-tests 0/2] fix long division routines for ARM eabi
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Tue May 11 17:41:04 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12251591
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8373EC433ED
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 17:41:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3CAFD61378
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 17:41:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231551AbhEKRmR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 13:42:17 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36110 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231512AbhEKRmQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 May 2021 13:42:16 -0400
Received: from mail-ed1-x531.google.com (mail-ed1-x531.google.com
 [IPv6:2a00:1450:4864:20::531])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id CB4AAC061574
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 10:41:08 -0700 (PDT)
Received: by mail-ed1-x531.google.com with SMTP id f1so1636189edt.4
        for <kvm@vger.kernel.org>; Tue, 11 May 2021 10:41:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=hb8ENtE+WmEFZrZrZSzUY6de4U1+BMFcRlEGa6h5Kww=;
        b=GuhNGqiQfx1bBZwxc3e/58Q/s8O8u+lNRyWZ3uMocUlpfSUT9EjA44yKwnBq3N7FG3
         CwBZa7cdaZFiBKgJGBBP5z/3ZfFw/VV1osJr0xxG40aN9+dHJJsMdOOapziAxx/3sIsD
         oaTxmGaJtRdGHtE1DgHGdr+JLgaGRFxYW8ZL7mPANmBZMjWLwkwrhX2C9DyOB5X/fxYD
         ALBGoExMZZzEoQUL38pEEESWWS90z2HuSFz8YuJj3xavQ1RxOAPqbk2naB+LnJjQKapN
         lHakbpadYXCVRaF6Q7tE2T2CsWanMAaOyETGE3rjwmC+coa43SFD8VQ9uLwG4AtXa4x9
         kmqQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=hb8ENtE+WmEFZrZrZSzUY6de4U1+BMFcRlEGa6h5Kww=;
        b=hqjea9ySSGjiP2wGahyHcRZzjCq9dW8l7JY+OWoFISfnHAAlO2Zgm1TAZzENVI7sup
         jQwM0hTACcTLJbe3M9CY8MRuQM+MuwsrGlbKgLo0z/qUM4PiC0s9sf6H2s26zRD0Tzbo
         JH1Kt6RUSzGcZch08lGLcWONr0hGbM+MJ/T+y5bLCrGHt1U99Ls/6nq3faTiKpSL9KbB
         iOqcNjJZ05MmvK7M10gMrsJLVB7nJssWtBdcp+/cM62qifEGSxMLvNx0yuoV2EglLc0H
         H0464cMyww3gVmNXaa/J0VJf9/YEOInk8KjOhfeV+KiMg8+1o9lkc1jyG0cT2AJ3Pb89
         RPfA==
X-Gm-Message-State: AOAM532UfqAYAinT5BwIi0dL6lfTELgMxISbx25kv2c0mEyXlEWfBxfJ
        8ebAea8hwY460Awy29dw1StS3ETOIr4=
X-Google-Smtp-Source: 
 ABdhPJzofeBYTmNyTtnxG1sFbqnijrlE7iKupdTiKWGWjfwfYge5LiQVfuqKzMLt4w0WjXuM8qGu3Q==
X-Received: by 2002:a05:6402:11ca:: with SMTP id
 j10mr38115160edw.184.1620754867547;
        Tue, 11 May 2021 10:41:07 -0700 (PDT)
Received: from avogadro.redhat.com ([2001:b07:6468:f312:c8dd:75d4:99ab:290a])
        by smtp.gmail.com with ESMTPSA id
 v23sm15239073eda.8.2021.05.11.10.41.06
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 11 May 2021 10:41:06 -0700 (PDT)
Sender: Paolo Bonzini <paolo.bonzini@gmail.com>
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PATCH kvm-unit-tests 0/2] fix long division routines for ARM eabi
Date: Tue, 11 May 2021 19:41:04 +0200
Message-Id: <20210511174106.703235-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As reported by Alexandru, ARM follows a different convention than
x86 so it needs __aeabi_ldivmod and __aeabi_uldivmod.  Because
it does not use __divdi3 and __moddi3, it also needs __divmoddi4
to build the eabi function upon.

Paolo

Paolo Bonzini (2):
  libcflat: clean up and complete long division routines
  arm: add eabi version of 64-bit division functions

 arm/Makefile.arm  |  1 +
 lib/arm/ldivmod.S | 32 ++++++++++++++++++++++++++++++++
 lib/ldiv32.c      | 28 +++++++++++++++++++++++++---
 3 files changed, 58 insertions(+), 3 deletions(-)
 create mode 100644 lib/arm/ldivmod.S
```
#### [PATCH v6 0/3] vfio-ccw: Fix interrupt handling for HALT/CLEAR
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Tue May 11 19:56:28 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 12251991
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 72125C43603
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 19:56:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4C959617ED
	for <kvm@archiver.kernel.org>; Tue, 11 May 2021 19:56:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229996AbhEKT5w (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 11 May 2021 15:57:52 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:18964 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229934AbhEKT5u (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 11 May 2021 15:57:50 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14BJXsUb171564;
        Tue, 11 May 2021 15:56:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : content-transfer-encoding : mime-version; s=pp1;
 bh=HjLYgEurXkONDxmN71vnc4qpFZfY+USpOrOsSejGVFk=;
 b=cHSk9tjcMXy8eGuSBY9L4Ewr0Km1BXYbTBu8icA+m6/m39VMgxo0Ts14X4oigXelR8xW
 u2oObhNS27XVWhYa3lR55CxddDXC6JGiWQKMVQP5Kk5iU8fd9fTOXImnloeCCHvQdKV8
 eIjHqxO9QBVVDs4wCE5yYSOzySmWpSWBaJEFnPqZlMndstnRbUwn2mRLHfqrmXjrv7S7
 RKoT5pZ6F4abOhfPo5OLx163bAYP6hGiC6IilcAidOcIiraimlHOghE9ufY74oBV6fcA
 Y5gXeHLmu9FH0WozLobvF3A1I5TBXcswjb1DWNrk6GScnqiTTKSZsl4YVJyqYQeDawYu VQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38fw0r6by7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 11 May 2021 15:56:43 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14BJXvLT171857;
        Tue, 11 May 2021 15:56:43 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 38fw0r6bxj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 11 May 2021 15:56:43 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14BJmhsR021962;
        Tue, 11 May 2021 19:56:41 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma04ams.nl.ibm.com with ESMTP id 38dj989u8b-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 11 May 2021 19:56:40 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14BJubpk33358290
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 11 May 2021 19:56:37 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B3CF5A4060;
        Tue, 11 May 2021 19:56:37 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A0981A4054;
        Tue, 11 May 2021 19:56:37 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 11 May 2021 19:56:37 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 5B3DFE0356; Tue, 11 May 2021 21:56:32 +0200 (CEST)
From: Eric Farman <farman@linux.ibm.com>
To: Cornelia Huck <cohuck@redhat.com>,
        Matthew Rosato <mjrosato@linux.ibm.com>,
        Halil Pasic <pasic@linux.ibm.com>
Cc: Jared Rossi <jrossi@linux.ibm.com>, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v6 0/3] vfio-ccw: Fix interrupt handling for HALT/CLEAR
Date: Tue, 11 May 2021 21:56:28 +0200
Message-Id: <20210511195631.3995081-1-farman@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: 28mf0-0GtL4HWlG2eekMsUiDquXYBYU_
X-Proofpoint-GUID: uy3HdWRg9NQrlIE8qDE2thaZJegLT_23
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-11_04:2021-05-11,2021-05-11 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 mlxscore=0
 lowpriorityscore=0 adultscore=0 priorityscore=1501 suspectscore=0
 spamscore=0 mlxlogscore=894 impostorscore=0 phishscore=0 malwarescore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105110130
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Conny, Matt, Halil,

Here's one (last?) update to my proposal for handling the collision
between interrupts for START SUBCHANNEL and HALT/CLEAR SUBCHANNEL.

Only change here is to include Conny's suggestions on patch 3.

Thanks,
Eric

Changelog:
v5->v6:
 - Add a block comment and rename variable in patch 3 [CH]
 - Drop RFC tag [EF]

v4->v5:
 - Applied Conny's r-b to patches 1 and 3
 - Dropped patch 2 and 4
 - Use a "finished" flag in the interrupt completion path

Previous versions:
v5: https://lore.kernel.org/kvm/20210510205646.1845844-1-farman@linux.ibm.com/
v4: https://lore.kernel.org/kvm/20210413182410.1396170-1-farman@linux.ibm.com/
v3: https://lore.kernel.org/kvm/20200616195053.99253-1-farman@linux.ibm.com/
v2: https://lore.kernel.org/kvm/20200513142934.28788-1-farman@linux.ibm.com/
v1: https://lore.kernel.org/kvm/20200124145455.51181-1-farman@linux.ibm.com/

Eric Farman (3):
  vfio-ccw: Check initialized flag in cp_init()
  vfio-ccw: Reset FSM state to IDLE inside FSM
  vfio-ccw: Serialize FSM IDLE state with I/O completion

 drivers/s390/cio/vfio_ccw_cp.c  |  4 ++++
 drivers/s390/cio/vfio_ccw_drv.c | 12 ++++++++++--
 drivers/s390/cio/vfio_ccw_fsm.c |  1 +
 drivers/s390/cio/vfio_ccw_ops.c |  2 --
 4 files changed, 15 insertions(+), 4 deletions(-)
```
