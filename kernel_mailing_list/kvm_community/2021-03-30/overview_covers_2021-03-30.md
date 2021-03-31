

#### [PATCH v4 0/3] cgroup: New misc cgroup controller
##### From: Vipin Sharma <vipinsh@google.com>

```c
From patchwork Tue Mar 30 04:42:03 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vipin Sharma <vipinsh@google.com>
X-Patchwork-Id: 12171617
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1097CC433E3
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 04:43:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E5428619A9
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 04:43:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230297AbhC3Emm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 00:42:42 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59564 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229501AbhC3EmN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 00:42:13 -0400
Received: from mail-qk1-x74a.google.com (mail-qk1-x74a.google.com
 [IPv6:2607:f8b0:4864:20::74a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id F0CF8C0613D8
        for <kvm@vger.kernel.org>; Mon, 29 Mar 2021 21:42:12 -0700 (PDT)
Received: by mail-qk1-x74a.google.com with SMTP id c7so13671388qka.6
        for <kvm@vger.kernel.org>; Mon, 29 Mar 2021 21:42:12 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=sfHXJbbxb6p3TEWQ8tzYZSEzCbGd5MPRFw754wGnO9M=;
        b=TTKZd5jbX64Rbx+dgGmFRdeRnmF8AD7bOmTLS2z53CveoKd38s4zHorjlWhT7JWttc
         W/4AYxcvnetv6zEBZYnCLLwDw/n0+NMSmznlECeNN386pQMDpBp4tAkUmypuy690YhbX
         MUJZ5LuwMKBNRdfciczq43ArGC3OCKUJ3QO4oD3Y2cx4JDMR46cTE+wD46kDhx1s1eQi
         BCVe4G/w1rxiIqWKYuh9XRd2X4XFgxFOga84xCkanZwHE8wax3F1kzF+jGb1H1j6pCKN
         N/nXSaOUfTOeOvgZgsdJwf4qCgPRhbqT7Cz7dmTglQ23YrQf8/aRU/gRgyKet03i1zWN
         AnpQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=sfHXJbbxb6p3TEWQ8tzYZSEzCbGd5MPRFw754wGnO9M=;
        b=cBxtne4XmjhFpEbMc6vwWfq7WjFzMhNuozIn0NhiGJqNDNZb+NQV6tIaSFWh7HCPFu
         5WuenP3IJiJKmdkPOG5Rolr73/BldFGCD9LD5JyDJbzKsNHJT2uwnYDzO8AF6ctC2yvd
         nW1hk30J1l4vizXRs370+SwqmgAH7xwxXHnbhUvcbVdfSbTqYno9ojAskTyIebiRh460
         e5ZKr+UIlhfkYCaUSz1C/LypExwbono2a+4DTbRbtKITvZdVkbzWOoUA/W1qYEaMlU+/
         q8BRcxhsjkdEc0tBDnzw/XaGvAL2Cmo1/JORwpiYjIA0ambOhEyTgZzIo/ibZI4wj6Ll
         Mg1A==
X-Gm-Message-State: AOAM530Rc8cxLT0L76FVg0xUG38nwwCQgqsU4INVuhuEzOQv9vR6eost
        11UnM+YO6KzKstbXTj/hrZvbLlvHRFpK
X-Google-Smtp-Source: 
 ABdhPJylRYJnJTOM7DmR750oi8GE7FSs9W4+AYIINo16KxJX6XT8zImZVHRhJpr5IS6NAXVIlTlHDO/mEE/V
X-Received: from vipinsh.kir.corp.google.com
 ([2620:0:1008:10:8048:6a12:bd4f:a453])
 (user=vipinsh job=sendgmr) by 2002:a05:6214:906:: with SMTP id
 dj6mr22407836qvb.38.1617079331667; Mon, 29 Mar 2021 21:42:11 -0700 (PDT)
Date: Mon, 29 Mar 2021 21:42:03 -0700
Message-Id: <20210330044206.2864329-1-vipinsh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.0.291.g576ba9dcdaf-goog
Subject: [PATCH v4 0/3] cgroup: New misc cgroup controller
From: Vipin Sharma <vipinsh@google.com>
To: tj@kernel.org, mkoutny@suse.com, jacob.jun.pan@intel.com,
        rdunlap@infradead.org, thomas.lendacky@amd.com,
        brijesh.singh@amd.com, jon.grimm@amd.com, eric.vantassell@amd.com,
        pbonzini@redhat.com, hannes@cmpxchg.org, frankja@linux.ibm.com,
        borntraeger@de.ibm.com
Cc: corbet@lwn.net, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, hpa@zytor.com,
        gingell@google.com, rientjes@google.com, kvm@vger.kernel.org,
        x86@kernel.org, cgroups@vger.kernel.org, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, Vipin Sharma <vipinsh@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hello,

This patch series is creating a new misc cgroup controller for limiting
and tracking of resources which are not abstract like other cgroup
controllers.

This controller was initially proposed as encryption_id but after the
feedbacks and use cases for other resources, it is now changed to misc
cgroup.
https://lore.kernel.org/lkml/20210108012846.4134815-2-vipinsh@google.com/

Most of the cloud infrastructure use cgroups for knowing the host state,
track the resources usage, enforce limits on them, etc. They use this
info to optimize work allocation in the fleet and make sure no rogue job
consumes more than it needs and starves others.

There are resources on a system which are not abstract enough like other
cgroup controllers and are available in a limited quantity on a host.

One of them is Secure Encrypted Virtualization (SEV) ASID on AMD CPU.
SEV ASIDs are used for creating encrypted VMs. SEV is mostly be used by
the cloud providers for providing confidential VMs. Since SEV ASIDs are
limited, there is a need to schedule encrypted VMs in a cloud
infrastructure based on SEV ASIDs availability and also to limit its
usage.

There are similar requirements for other resource types like TDX keys,
IOASIDs and SEID.

Adding these resources to a cgroup controller is a natural choice with
least amount of friction. Cgroup itself says it is a mechanism to
distribute system resources along the hierarchy in a controlled
mechanism and configurable manner. Most of the resources in cgroups are
abstracted enough but there are still some resources which are not
abstract but have limited availability or have specific use cases.

Misc controller is a generic controller which can be used by these
kinds of resources.

One suggestion was to use BPF for this purpose, however, there are
couple of things which might not be addressed with BPF:
1. Which controller to use in v1 case? These are not abstract resources
   so in v1 where each controller have their own hierarchy it might not
   be easy to identify the best controller to use for BPF.

2. Abstracting out a single BPF program which can help with all of the
   resources types might not be possible, because resources we are
   working with are not similar and abstract enough, for example network
   packets, and there will be different places in the source code to use
   these resources.

A new cgroup controller tends to give much easier and well integrated
solution when it comes to scheduling and limiting a resource with
existing tools in a cloud infrastructure.

Changes in RFC v4:
1. Misc controller patch is split into two patches. One for generic misc
   controller and second for adding SEV and SEV-ES resource.
2. Using READ_ONCE and WRITE_ONCE for variable accesses.
3. Updated documentation.
4. Changed EXPORT_SYMBOL to EXPORT_SYMBOL_GPL.
5. Included cgroup header in misc_cgroup.h.
6. misc_cg_reduce_charge changed to misc_cg_cancel_charge.
7. misc_cg set to NULL after uncharge.
8. Added WARN_ON if misc_cg not NULL before charging in SEV/SEV-ES.

Changes in RFC v3:
1. Changed implementation to support 64 bit counters.
2. Print kernel logs only once per resource per cgroup.
3. Capacity can be set less than the current usage.

Changes in RFC v2:
1. Documentation fixes.
2. Added kernel log messages.
3. Changed charge API to treat misc_cg as input parameter.
4. Added helper APIs to get and release references on the cgroup.

[1] https://lore.kernel.org/lkml/20210218195549.1696769-1-vipinsh@google.com
[2] https://lore.kernel.org/lkml/20210302081705.1990283-1-vipinsh@google.com/
[3] https://lore.kernel.org/lkml/20210304231946.2766648-1-vipinsh@google.com/

Vipin Sharma (3):
  cgroup: Add misc cgroup controller
  cgroup: Miscellaneous cgroup documentation.
  svm/sev: Register SEV and SEV-ES ASIDs to the misc controller

 Documentation/admin-guide/cgroup-v1/index.rst |   1 +
 Documentation/admin-guide/cgroup-v1/misc.rst  |   4 +
 Documentation/admin-guide/cgroup-v2.rst       |  73 +++-
 arch/x86/kvm/svm/sev.c                        |  70 ++-
 arch/x86/kvm/svm/svm.h                        |   1 +
 include/linux/cgroup_subsys.h                 |   4 +
 include/linux/misc_cgroup.h                   | 132 ++++++
 init/Kconfig                                  |  14 +
 kernel/cgroup/Makefile                        |   1 +
 kernel/cgroup/misc.c                          | 407 ++++++++++++++++++
 10 files changed, 695 insertions(+), 12 deletions(-)
 create mode 100644 Documentation/admin-guide/cgroup-v1/misc.rst
 create mode 100644 include/linux/misc_cgroup.h
 create mode 100644 kernel/cgroup/misc.c
```
#### [PATCH v6 00/10] KVM: selftests: some improvement and a new test for
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Tue Mar 30 08:08:46 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12171973
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 22CFCC433E0
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 08:09:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D1B9A61985
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 08:09:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230122AbhC3IJN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 04:09:13 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:14958 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229633AbhC3IJI (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 04:09:08 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4F8hqm4qfxzyNHw;
        Tue, 30 Mar 2021 16:07:00 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.498.0; Tue, 30 Mar 2021 16:08:58 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Andrew Jones <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kselftest@vger.kernel.org>, <linux-kernel@vger.kernel.org>
CC: Ben Gardon <bgardon@google.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Peter Xu <peterx@redhat.com>, "Ingo Molnar" <mingo@kernel.org>,
        Adrian Hunter <adrian.hunter@intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        Arnaldo Carvalho de Melo <acme@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Michael Kerrisk <mtk.manpages@gmail.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [PATCH v6 00/10] KVM: selftests: some improvement and a new test for
 kvm page table
Date: Tue, 30 Mar 2021 16:08:46 +0800
Message-ID: <20210330080856.14940-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,
This v6 series can mainly include two parts.
Rebased on kvm queue branch: https://git.kernel.org/pub/scm/virt/kvm/kvm.git/log/?h=queue

In the first part, all the known hugetlb backing src types specified
with different hugepage sizes are listed, so that we can specify use
of hugetlb source of the exact granularity that we want, instead of
the system default ones. And as all the known hugetlb page sizes are
listed, it's appropriate for all architectures. Besides, a helper that
can get granularity of different backing src types(anonumous/thp/hugetlb)
is added, so that we can use the accurate backing src granularity for
kinds of alignment or guest memory accessing of vcpus.

In the second part, a new test is added:
This test is added to serve as a performance tester and a bug reproducer
for kvm page table code (GPA->HPA mappings), it gives guidance for the
people trying to make some improvement for kvm. And the following explains
what we can exactly do through this test.

The function guest_code() can cover the conditions where a single vcpu or
multiple vcpus access guest pages within the same memory region, in three
VM stages(before dirty logging, during dirty logging, after dirty logging).
Besides, the backing src memory type(ANONYMOUS/THP/HUGETLB) of the tested
memory region can be specified by users, which means normal page mappings
or block mappings can be chosen by users to be created in the test.

If ANONYMOUS memory is specified, kvm will create normal page mappings
for the tested memory region before dirty logging, and update attributes
of the page mappings from RO to RW during dirty logging. If THP/HUGETLB
memory is specified, kvm will create block mappings for the tested memory
region before dirty logging, and split the blcok mappings into normal page
mappings during dirty logging, and coalesce the page mappings back into
block mappings after dirty logging is stopped.

So in summary, as a performance tester, this test can present the
performance of kvm creating/updating normal page mappings, or the
performance of kvm creating/splitting/recovering block mappings,
through execution time.

When we need to coalesce the page mappings back to block mappings after
dirty logging is stopped, we have to firstly invalidate *all* the TLB
entries for the page mappings right before installation of the block entry,
because a TLB conflict abort error could occur if we can't invalidate the
TLB entries fully. We have hit this TLB conflict twice on aarch64 software
implementation and fixed it. As this test can imulate process from dirty
logging enabled to dirty logging stopped of a VM with block mappings,
so it can also reproduce this TLB conflict abort due to inadequate TLB
invalidation when coalescing tables.

Links about the TLB conflict abort:
https://lore.kernel.org/lkml/20201201201034.116760-3-wangyanan55@huawei.com/
---

Change logs:

v5->v6:
- Address Andrew Jones's comments for v5 series
- Add Andrew Jones's R-b tags in some patches
- Rebased on newest kvm/queue tree
- v5: https://lore.kernel.org/lkml/20210323135231.24948-1-wangyanan55@huawei.com/

v4->v5:
- Use synchronization(sem_wait) for time measurement
- Add a new patch about TEST_ASSERT(patch 4)
- Address Andrew Jones's comments for v4 series
- Add Andrew Jones's R-b tags in some patches
- v4: https://lore.kernel.org/lkml/20210302125751.19080-1-wangyanan55@huawei.com/

v3->v4:
- Add a helper to get system default hugetlb page size
- Add tags of Reviewed-by of Ben in the patches
- v3: https://lore.kernel.org/lkml/20210301065916.11484-1-wangyanan55@huawei.com/

v2->v3:
- Add tags of Suggested-by, Reviewed-by in the patches
- Add a generic micro to get hugetlb page sizes
- Some changes for suggestions about v2 series
- v2: https://lore.kernel.org/lkml/20210225055940.18748-1-wangyanan55@huawei.com/

v1->v2:
- Add a patch to sync header files
- Add helpers to get granularity of different backing src types
- Some changes for suggestions about v1 series
- v1: https://lore.kernel.org/lkml/20210208090841.333724-1-wangyanan55@huawei.com/

---

Yanan Wang (10):
  tools headers: sync headers of asm-generic/hugetlb_encode.h
  mm/hugetlb: Add a macro to get HUGETLB page sizes for mmap
  KVM: selftests: Use flag CLOCK_MONOTONIC_RAW for timing
  KVM: selftests: Print the errno besides error-string in TEST_ASSERT
  KVM: selftests: Make a generic helper to get vm guest mode strings
  KVM: selftests: Add a helper to get system configured THP page size
  KVM: selftests: Add a helper to get system default hugetlb page size
  KVM: selftests: List all hugetlb src types specified with page sizes
  KVM: selftests: Adapt vm_userspace_mem_region_add to new helpers
  KVM: selftests: Add a test for kvm page table code

 include/uapi/linux/mman.h                     |   2 +
 tools/include/asm-generic/hugetlb_encode.h    |   3 +
 tools/include/uapi/linux/mman.h               |   2 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../selftests/kvm/demand_paging_test.c        |   8 +-
 .../selftests/kvm/dirty_log_perf_test.c       |  14 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +-
 .../testing/selftests/kvm/include/test_util.h |  21 +-
 .../selftests/kvm/kvm_page_table_test.c       | 506 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/assert.c      |   4 +-
 tools/testing/selftests/kvm/lib/kvm_util.c    |  59 +-
 tools/testing/selftests/kvm/lib/test_util.c   | 163 +++++-
 tools/testing/selftests/kvm/steal_time.c      |   4 +-
 14 files changed, 733 insertions(+), 61 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/kvm_page_table_test.c
```
#### [PATCH v3 0/3] ppc: Enable 2nd DAWR support on Power10
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
From patchwork Tue Mar 30 09:53:47 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 12172179
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 58A57C433DB
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 09:55:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1F22D6157F
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 09:55:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231623AbhC3JzK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 05:55:10 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:37278 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231622AbhC3Jyg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 30 Mar 2021 05:54:36 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12U9Z4JR115979;
        Tue, 30 Mar 2021 05:54:09 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : content-transfer-encoding : mime-version; s=pp1;
 bh=g8HSqJyZCcDb656OfNBVeUzttT8XC6QEH/Q3z5IjM58=;
 b=KdB+86KHMwyii5qQDRjWPXboD6GJih1lPUX5rmq7Ta7cOnOHmeFVm06fJnBtvTuR1nLy
 rRClgKJujozw5aeW6WX1BSIUQz90W6IPHG2CLha2MuKi6mlH2ME5kKbBt11BSJZy4i0S
 rvrMMn7ZS3q2mD/C71naGJ9B+fE2zNANFx9QLIe9x1eSjJG67sOJ/SL2dZudhThR9E/m
 BZBCLI2sSL8EWrRRm9wQ9IwEzvwEeib7VUHzgsNZKwPRwWb9RCyTxXIpQCXdzDJ0D0Pk
 n66OJYSzFcBN7RL+hQ4gsTviEu/fFJXhaI6XCVys5HOT19+BQBsafIJuwvQPDL7iKXZ1 bg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37jhsbkrvt-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 30 Mar 2021 05:54:09 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12U9q2aX050971;
        Tue, 30 Mar 2021 05:54:09 -0400
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37jhsbkrux-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 30 Mar 2021 05:54:08 -0400
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12U9s6i1024746;
        Tue, 30 Mar 2021 09:54:06 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma06fra.de.ibm.com with ESMTP id 37huyh9cht-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 30 Mar 2021 09:54:06 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12U9s4AK27001228
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 30 Mar 2021 09:54:04 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 32DBA52054;
        Tue, 30 Mar 2021 09:54:04 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.47.23])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 60E8E5204E;
        Tue, 30 Mar 2021 09:54:01 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: paulus@samba.org, david@gibson.dropbear.id.au
Cc: ravi.bangoria@linux.ibm.com, mpe@ellerman.id.au, mikey@neuling.org,
        pbonzini@redhat.com, mst@redhat.com, clg@kaod.org,
        qemu-ppc@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org,
        cohuck@redhat.com
Subject: [PATCH v3 0/3] ppc: Enable 2nd DAWR support on Power10
Date: Tue, 30 Mar 2021 15:23:47 +0530
Message-Id: <20210330095350.36309-1-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
X-TM-AS-GCONF: 00
X-Proofpoint-ORIG-GUID: 0Ghyj5v7ENFLiFiBxDRHyuITamK7EuvL
X-Proofpoint-GUID: EQ1DvwLAWtzTioj6fj9Cbluu8DoakoM6
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-30_03:2021-03-26,2021-03-30 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 impostorscore=0
 clxscore=1015 adultscore=0 suspectscore=0 lowpriorityscore=0 phishscore=0
 malwarescore=0 mlxscore=0 bulkscore=0 priorityscore=1501 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2103250000
 definitions=main-2103300066
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enables 2nd DAWR support on p10 qemu guest. 2nd
DAWR is new watchpoint added in Power10 processor. Kernel/kvm
patches are already in[1]. Watchpoint on powerpc TCG guest is
not supported and thus 2nd DAWR is not enabled for TCG mode.

Patches apply fine on qemu/master branch (9e2e9fe3df9f).

v2: https://lore.kernel.org/r/20210329041906.213991-1-ravi.bangoria@linux.ibm.com
v2->v3:
  - Don't introduce pa_features_310[], instead, reuse pa_features_300[]
    for 3.1 guests, as there is no difference between initial values of
    them atm.
  - Call gen_spr_book3s_310_dbg() from init_proc_POWER10() instead of
    init_proc_POWER8(). Also, Don't call gen_spr_book3s_207_dbg() from
    gen_spr_book3s_310_dbg() as init_proc_POWER10() already calls it.

v1: https://lore.kernel.org/r/20200723104220.314671-1-ravi.bangoria@linux.ibm.com
[Apologies for long gap]
v1->v2:
  - Introduce machine capability cap-dawr1 to enable/disable
    the feature. By default, 2nd DAWR is OFF for guests even
    when host kvm supports it. User has to manually enable it
    with -machine cap-dawr1=on if he wishes to use it.
  - Split the header file changes into separate patch. (Sync
    headers from v5.12-rc3)

[1] https://git.kernel.org/torvalds/c/bd1de1a0e6eff

Ravi Bangoria (3):
  Linux headers: update from 5.12-rc3
  ppc: Rename current DAWR macros and variables
  ppc: Enable 2nd DAWR support on p10

 hw/ppc/spapr.c                                | 11 ++-
 hw/ppc/spapr_caps.c                           | 32 +++++++
 include/hw/ppc/spapr.h                        |  8 +-
 include/standard-headers/drm/drm_fourcc.h     | 23 ++++-
 include/standard-headers/linux/input.h        |  2 +-
 .../standard-headers/rdma/vmw_pvrdma-abi.h    |  7 ++
 linux-headers/asm-generic/unistd.h            |  4 +-
 linux-headers/asm-mips/unistd_n32.h           |  1 +
 linux-headers/asm-mips/unistd_n64.h           |  1 +
 linux-headers/asm-mips/unistd_o32.h           |  1 +
 linux-headers/asm-powerpc/kvm.h               |  2 +
 linux-headers/asm-powerpc/unistd_32.h         |  1 +
 linux-headers/asm-powerpc/unistd_64.h         |  1 +
 linux-headers/asm-s390/unistd_32.h            |  1 +
 linux-headers/asm-s390/unistd_64.h            |  1 +
 linux-headers/asm-x86/kvm.h                   |  1 +
 linux-headers/asm-x86/unistd_32.h             |  1 +
 linux-headers/asm-x86/unistd_64.h             |  1 +
 linux-headers/asm-x86/unistd_x32.h            |  1 +
 linux-headers/linux/kvm.h                     | 89 +++++++++++++++++++
 linux-headers/linux/vfio.h                    | 27 ++++++
 target/ppc/cpu.h                              |  6 +-
 target/ppc/kvm.c                              | 12 +++
 target/ppc/kvm_ppc.h                          |  7 ++
 target/ppc/translate_init.c.inc               | 19 +++-
 25 files changed, 249 insertions(+), 11 deletions(-)
```
#### [PATCH v19 0/7] KVM: arm64: Add host/guest KVM-PTP support
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Mar 30 14:54:23 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12172813
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DA4B8C433E0
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 14:55:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9AAB4619C8
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 14:55:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231532AbhC3Oy6 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 10:54:58 -0400
Received: from mail.kernel.org ([198.145.29.99]:55388 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231812AbhC3Oyq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 30 Mar 2021 10:54:46 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id A5B6961921;
        Tue, 30 Mar 2021 14:54:45 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1lRFlT-004hoo-ML; Tue, 30 Mar 2021 15:54:43 +0100
From: Marc Zyngier <maz@kernel.org>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com, seanjc@google.com,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, Andre.Przywara@arm.com,
        steven.price@arm.com, lorenzo.pieralisi@arm.com,
        sudeep.holla@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, justin.he@arm.com, jianyong.wu@arm.com,
        kernel-team@android.com
Subject: [PATCH v19 0/7] KVM: arm64: Add host/guest KVM-PTP support
Date: Tue, 30 Mar 2021 15:54:23 +0100
Message-Id: <20210330145430.996981-1-maz@kernel.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: netdev@vger.kernel.org, yangbo.lu@nxp.com,
 john.stultz@linaro.org, tglx@linutronix.de, pbonzini@redhat.com,
 seanjc@google.com, richardcochran@gmail.com, Mark.Rutland@arm.com,
 will@kernel.org, suzuki.poulose@arm.com, Andre.Przywara@arm.com,
 steven.price@arm.com, lorenzo.pieralisi@arm.com, sudeep.holla@arm.com,
 linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, Steve.Capper@arm.com,
 justin.he@arm.com, jianyong.wu@arm.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Given that this series[0] has languished in my Inbox for the best of the
past two years, and in an effort to eventually get it merged, I've
taken the liberty to pick it up and do the changes I wanted to see
instead of waiting to go through yet another round.

All the patches have a link to their original counterpart (though I
have squashed a couple of them where it made sense). Tested both 64
and 32bit guests for a good measure. Of course, I claim full
responsibility for any bug introduced here.

Unless someone screams now, this is going in 5.13, because I'm frankly
fed up with it! ;-)

* From v18 [2]
  - Fix kvm_hypercall2() return type
  - Rebased on top of 5.12-rc3
  - Added RBs

* From v17 [1]:
  - Fixed compilation issue on 32bit systems not selecting
    CONFIG_HAVE_ARM_SMCCC_DISCOVERY
  - Fixed KVM service discovery not properly parsing the reply
    from the hypervisor

* From v16 [0]:
  - Moved the KVM service discovery to its own file, plugged it into
    PSCI instead of the arch code, dropped the inlining, made use of
    asm/hypervisor.h.
  - Tidied-up the namespacing
  - Cleanup the hypercall handler
  - De-duplicate the guest code
  - Tidied-up arm64-specific documentation
  - Dropped the generic PTP documentation as it needs a new location,
    and some cleanup
  - Squashed hypercall documentation and capability into the
    main KVM patch
  - Rebased on top of 5.11-rc4

[0] https://lore.kernel.org/r/20201209060932.212364-1-jianyong.wu@arm.com
[1] https://lore.kernel.org/r/20210202141204.3134855-1-maz@kernel.org
[2] https://lore.kernel.org/r/20210208134029.3269384-1-maz@kernel.org

Jianyong Wu (4):
  ptp: Reorganize ptp_kvm.c to make it arch-independent
  clocksource: Add clocksource id for arm arch counter
  KVM: arm64: Add support for the KVM PTP service
  ptp: arm/arm64: Enable ptp_kvm for arm/arm64

Thomas Gleixner (1):
  time: Add mechanism to recognize clocksource in time_get_snapshot

Will Deacon (2):
  arm/arm64: Probe for the presence of KVM hypervisor
  KVM: arm64: Advertise KVM UID to guests via SMCCC

 Documentation/virt/kvm/api.rst              | 10 +++
 Documentation/virt/kvm/arm/index.rst        |  1 +
 Documentation/virt/kvm/arm/ptp_kvm.rst      | 25 ++++++
 arch/arm/include/asm/hypervisor.h           |  3 +
 arch/arm64/include/asm/hypervisor.h         |  3 +
 arch/arm64/kvm/arm.c                        |  1 +
 arch/arm64/kvm/hypercalls.c                 | 80 +++++++++++++++--
 drivers/clocksource/arm_arch_timer.c        | 36 ++++++++
 drivers/firmware/psci/psci.c                |  2 +
 drivers/firmware/smccc/Makefile             |  2 +-
 drivers/firmware/smccc/kvm_guest.c          | 50 +++++++++++
 drivers/firmware/smccc/smccc.c              |  1 +
 drivers/ptp/Kconfig                         |  2 +-
 drivers/ptp/Makefile                        |  2 +
 drivers/ptp/ptp_kvm_arm.c                   | 28 ++++++
 drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} | 84 +++++-------------
 drivers/ptp/ptp_kvm_x86.c                   | 97 +++++++++++++++++++++
 include/linux/arm-smccc.h                   | 41 +++++++++
 include/linux/clocksource.h                 |  6 ++
 include/linux/clocksource_ids.h             | 12 +++
 include/linux/ptp_kvm.h                     | 19 ++++
 include/linux/timekeeping.h                 | 12 +--
 include/uapi/linux/kvm.h                    |  1 +
 kernel/time/clocksource.c                   |  2 +
 kernel/time/timekeeping.c                   |  1 +
 25 files changed, 443 insertions(+), 78 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/ptp_kvm.rst
 create mode 100644 drivers/firmware/smccc/kvm_guest.c
 create mode 100644 drivers/ptp/ptp_kvm_arm.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (60%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
 create mode 100644 include/linux/ptp_kvm.h
```
#### [PATCH 0/2] KVM: x86: fix lockdep splat due to Xen runstate update
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From patchwork Tue Mar 30 16:59:56 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12173165
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2243CC433E3
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 17:00:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F1D00619CD
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 17:00:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232450AbhC3RAV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 13:00:21 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:45200 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232190AbhC3RAG (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 30 Mar 2021 13:00:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617123606;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=boHgOYjxaOQQWEyS/lxfTaWYnwFmFjR45ql5WkUeRs0=;
        b=ECguLRZ9lu/FlKspCWuuHjTIUPBkB2y2ZDMbqJ8kU9sCAcV4NOg53vw4tf8jovpJsym/jJ
        QA5xLdXWdoia+39PnXbn0O3+ir6QwQbA+nivBncZ2+Ms2iI7JZY3je8/9Ss5z8A01v/8FG
        5VNqPeQKpSgXo/AnW+3Xcdz5Z9yhL00=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-119-N-5MNFv9N-Sw4gxVlCypDA-1; Tue, 30 Mar 2021 13:00:02 -0400
X-MC-Unique: N-5MNFv9N-Sw4gxVlCypDA-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 907D4107ACCD;
        Tue, 30 Mar 2021 16:59:59 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1FF4C59442;
        Tue, 30 Mar 2021 16:59:59 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: mtosatti@redhat.com, vkuznets@redhat.com, dwmw@amazon.co.uk
Subject: [PATCH 0/2] KVM: x86: fix lockdep splat due to Xen runstate update
Date: Tue, 30 Mar 2021 12:59:56 -0400
Message-Id: <20210330165958.3094759-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

pvclock_gtod_sync_lock can be taken with interrupts disabled if the
preempt notifier calls get_kvmclock_ns to update the Xen
runstate information:

   spin_lock include/linux/spinlock.h:354 [inline]
   get_kvmclock_ns+0x25/0x390 arch/x86/kvm/x86.c:2587
   kvm_xen_update_runstate+0x3d/0x2c0 arch/x86/kvm/xen.c:69
   kvm_xen_update_runstate_guest+0x74/0x320 arch/x86/kvm/xen.c:100
   kvm_xen_runstate_set_preempted arch/x86/kvm/xen.h:96 [inline]
   kvm_arch_vcpu_put+0x2d8/0x5a0 arch/x86/kvm/x86.c:4062

So change the users of the spinlock to spin_lock_irqsave and
spin_unlock_irqrestore.  Before doing that, patch 1 just makes
the pvclock_gtod_sync_lock critical sections as small as possible
so that the resulting irq-disabled sections are easier to review.

Paolo

Paolo Bonzini (2):
  KVM: x86: reduce pvclock_gtod_sync_lock critical sections
  KVM: x86: disable interrupts while pvclock_gtod_sync_lock is taken

 arch/x86/kvm/x86.c | 29 +++++++++++++++--------------
 1 file changed, 15 insertions(+), 14 deletions(-)
```
#### [PATCH 0/4] kvm: cpuid: fix cpuid nent field
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
From patchwork Tue Mar 30 18:58:37 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12173579
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-10.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2C41CC433DB
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 18:59:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E41796196A
	for <kvm@archiver.kernel.org>; Tue, 30 Mar 2021 18:59:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232956AbhC3S7I (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 30 Mar 2021 14:59:08 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:29966 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232958AbhC3S6z (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 30 Mar 2021 14:58:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1617130734;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=J6RA/5YBSEXFrib0Mj4ENt+Q2fhHfFS3xUYo5/rYdaw=;
        b=YDFO/vjRZd6lxd4lvkISoWv+cEEdlFHBAXrOXCRhix/ps7z3gFv9yRQD8orj/qg0Qla5hI
        0pY3Bgm88J8KElmqWrF2H/P7ovs7IXJeh3ZTS5p1vjMHcG5GGRNial3K/A7fBzYBJA02/5
        VYsaLOREHkkqF7Cv8MPbHUETSlReHu4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-79-_ODYVjhIMseUViOsni0ADA-1; Tue, 30 Mar 2021 14:58:52 -0400
X-MC-Unique: _ODYVjhIMseUViOsni0ADA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C1617911E3;
        Tue, 30 Mar 2021 18:58:49 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-112-41.ams2.redhat.com
 [10.36.112.41])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1EAC519C44;
        Tue, 30 Mar 2021 18:58:44 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Shuah Khan <shuah@kernel.org>,
        Alexander Graf <graf@amazon.com>,
        Andrew Jones <drjones@redhat.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-kselftest@vger.kernel.org
Subject: [PATCH 0/4] kvm: cpuid: fix cpuid nent field
Date: Tue, 30 Mar 2021 20:58:37 +0200
Message-Id: <20210330185841.44792-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series aims to clarify the behavior of 
KVM_GET_EMULATED_CPUID and KVM_GET_SUPPORTED
ioctls, and fix a corner case where the nent field of the
struct kvm_cpuid2 is matching the amount of entries that kvm returns.

Patch 1 proposes the nent field fix to cpuid.c,
patch 2 updates the ioctl documentation accordingly and 
patches 3 and 4 provide a selftest to check KVM_GET_EMULATED_CPUID
accordingly.

Emanuele Giuseppe Esposito (4):
  kvm: cpuid: adjust the returned nent field of kvm_cpuid2 for
    KVM_GET_SUPPORTED_CPUID and KVM_GET_EMULATED_CPUID
  Documentation: kvm: update KVM_GET_EMULATED_CPUID ioctl description
  selftests: add kvm_get_emulated_cpuid
  selftests: kvm: add get_emulated_cpuid test

 Documentation/virt/kvm/api.rst                |  10 +-
 arch/x86/kvm/cpuid.c                          |   6 +
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/include/x86_64/processor.h  |   1 +
 .../selftests/kvm/lib/x86_64/processor.c      |  33 ++++
 .../selftests/kvm/x86_64/get_emulated_cpuid.c | 183 ++++++++++++++++++
 7 files changed, 229 insertions(+), 6 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/get_emulated_cpuid.c
```
