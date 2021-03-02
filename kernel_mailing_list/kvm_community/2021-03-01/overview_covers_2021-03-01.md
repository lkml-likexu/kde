

#### [RFC PATCH v3 0/7] KVM: selftests: some improvement and a new test
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Mon Mar  1 06:59:08 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12108837
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2C85CC433DB
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 07:01:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E0C4060234
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 07:01:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232262AbhCAHBc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 02:01:32 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:12958 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232167AbhCAHBR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Mar 2021 02:01:17 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4Dprgc5BCnzjShq;
        Mon,  1 Mar 2021 14:58:04 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Mon, 1 Mar 2021 14:59:18 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kselftest@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Paolo Bonzini <pbonzini@redhat.com>,
        Ben Gardon <bgardon@google.com>,
        "Sean Christopherson" <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Peter Xu <peterx@redhat.com>, Marc Zyngier <maz@kernel.org>,
        Ingo Molnar <mingo@kernel.org>,
        Adrian Hunter <adrian.hunter@intel.com>,
        Jiri Olsa <jolsa@redhat.com>,
        "Arnaldo Carvalho de Melo" <acme@redhat.com>,
        Arnd Bergmann <arnd@arndb.de>,
        Michael Kerrisk <mtk.manpages@gmail.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        <wanghaibin.wang@huawei.com>, <yezengruan@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v3 0/7] KVM: selftests: some improvement and a new test
 for kvm page table
Date: Mon, 1 Mar 2021 14:59:08 +0800
Message-ID: <20210301065916.11484-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,
This v3 series can mainly include two parts.
Based on kvm queue branch: https://git.kernel.org/pub/scm/virt/kvm/kvm.git/log/?h=queue
Links of v1: https://lore.kernel.org/lkml/20210208090841.333724-1-wangyanan55@huawei.com/
Links of v2: https://lore.kernel.org/lkml/20210225055940.18748-1-wangyanan55@huawei.com/

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

v2->v3:
- Add tags of Suggested-by, Reviewed-by in the patches
- Add a generic micro to get hugetlb page sizes
- Some changes for suggestions about v2 series

v1->v2:
- Add a patch to sync header files
- Add helpers to get granularity of different backing src types
- Some changes for suggestions about v1 series

---

Yanan Wang (7):
  tools headers: sync headers of asm-generic/hugetlb_encode.h
  tools headers: Add a macro to get HUGETLB page sizes for mmap
  KVM: selftests: Use flag CLOCK_MONOTONIC_RAW for timing
  KVM: selftests: Make a generic helper to get vm guest mode strings
  KVM: selftests: Add a helper to get system configured THP page size
  KVM: selftests: List all hugetlb src types specified with page sizes
  KVM: selftests: Adapt vm_userspace_mem_region_add to new helpers
  KVM: selftests: Add a test for kvm page table code

 include/uapi/linux/mman.h                     |   2 +
 tools/include/asm-generic/hugetlb_encode.h    |   3 +
 tools/include/uapi/linux/mman.h               |   2 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../selftests/kvm/demand_paging_test.c        |   8 +-
 .../selftests/kvm/dirty_log_perf_test.c       |  14 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +-
 .../testing/selftests/kvm/include/test_util.h |  21 +-
 .../selftests/kvm/kvm_page_table_test.c       | 476 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  59 ++-
 tools/testing/selftests/kvm/lib/test_util.c   |  92 +++-
 tools/testing/selftests/kvm/steal_time.c      |   4 +-
 12 files changed, 628 insertions(+), 60 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/kvm_page_table_test.c
```
#### [PATCH 00/25] KVM SGX virtualization support
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Mon Mar  1 09:44:08 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12109283
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 42743C433E0
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 09:45:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F2F8564E3F
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 09:45:32 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234078AbhCAJpR (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 04:45:17 -0500
Received: from mga18.intel.com ([134.134.136.126]:59762 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234055AbhCAJpO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 1 Mar 2021 04:45:14 -0500
IronPort-SDR: 
 cP6QF051E+zHJurv2bT4EeiqfS/Fdja5+Zs9GEwvAIv3o/5AoxDNFuUXXYnMstDWOINOB1ENah
 BK060BAlv+2A==
X-IronPort-AV: E=McAfee;i="6000,8403,9909"; a="174046470"
X-IronPort-AV: E=Sophos;i="5.81,215,1610438400";
   d="scan'208";a="174046470"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Mar 2021 01:44:32 -0800
IronPort-SDR: 
 +YgmYuPFNEhKo28m17pGTA+znN2qrayg6lsxhGtmo9GliqKg2kOh52g9KXdkbT4HJuzAIwGWtn
 hu3EviFiP8sg==
X-IronPort-AV: E=Sophos;i="5.81,215,1610438400";
   d="scan'208";a="599267263"
Received: from jscomeax-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.252.139.76])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Mar 2021 01:44:22 -0800
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-sgx@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, seanjc@google.com, jarkko@kernel.org,
        luto@kernel.org, dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        jethro@fortanix.com, b.thiel@posteo.de, jmattson@google.com,
        joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        corbet@lwn.net
Subject: [PATCH 00/25] KVM SGX virtualization support
Date: Mon,  1 Mar 2021 22:44:08 +1300
Message-Id: <cover.1614590788.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds KVM SGX virtualization support. The first 14 patches starting
with x86/sgx or x86/cpu.. are necessary changes to x86 and SGX core/driver to
support KVM SGX virtualization, while the rest are patches to KVM subsystem.

This series is based against latest upstream kernel master branch (v5.12-rc1).

You can also get the code from upstream branch of kvm-sgx repo on github:

        https://github.com/intel/kvm-sgx.git upstream

It also requires Qemu changes to create VM with SGX support. You can find Qemu
repo here:

	https://github.com/intel/qemu-sgx.git upstream

Please refer to README.md of above qemu-sgx repo for detail on how to create
guest with SGX support. At meantime, for your quick reference you can use below
command to create SGX guest:

	#qemu-system-x86_64 -smp 4 -m 2G -drive file=<your_vm_image>,if=virtio \
		-cpu host,+sgx_provisionkey \
		-sgx-epc id=epc1,memdev=mem1 \
		-object memory-backend-epc,id=mem1,size=64M,prealloc

Please note that the SGX relevant part is:

		-cpu host,+sgx_provisionkey \
		-sgx-epc id=epc1,memdev=mem1 \
		-object memory-backend-epc,id=mem1,size=64M,prealloc

And you can change other parameters of your qemu command based on your needs.

=========
Changelog:

(Changelog here is for global changes. Please see each patch's changelog for
 changes made to specific patch.)

RFC->v1:

 - Refined patch (x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()) to print
   error msg that EPC page is leaked when EREMOVE failed, requested by Dave.
 - Changelog history of all RFC series is removed in both this cover letter
   and each individual patch, since majority of x86 part patches already got
   Acked-by from Dave and Jarkko. And the changelogs are not quite useful from
   my perspective.

=========
KVM SGX virtualization Overview

- Virtual EPC

SGX enclave memory is special and is reserved specifically for enclave use.
In bare-metal SGX enclaves, the kernel allocates enclave pages, copies data
into the pages with privileged instructions, then allows the enclave to start.
In this scenario, only initialized pages already assigned to an enclave are
mapped to userspace.

In virtualized environments, the hypervisor still needs to do the physical
enclave page allocation.  The guest kernel is responsible for the data copying
(among other things).  This means that the job of starting an enclave is now
split between hypervisor and guest.

This series introduces a new misc device: /dev/sgx_vepc.  This device allows
the host to map *uninitialized* enclave memory into userspace, which can then
be passed into a guest.

While it might be *possible* to start a host-side enclave with /dev/sgx_enclave
and pass its memory into a guest, it would be wasteful and convoluted.

Implement the *raw* EPC allocation in the x86 core-SGX subsystem via
/dev/sgx_vepc rather than in KVM.  Doing so has two major advantages:

  - Does not require changes to KVM's uAPI, e.g. EPC gets handled as
    just another memory backend for guests.

  - EPC management is wholly contained in the SGX subsystem, e.g. SGX
    does not have to export any symbols, changes to reclaim flows don't
    need to be routed through KVM, SGX's dirty laundry doesn't have to
    get aired out for the world to see, and so on and so forth.

The virtual EPC pages allocated to guests are currently not reclaimable.
Reclaiming EPC page used by enclave requires a special reclaim mechanism
separate from normal page reclaim, and that mechanism is not supported
for virutal EPC pages.  Due to the complications of handling reclaim
conflicts between guest and host, reclaiming virtual EPC pages is 
significantly more complex than basic support for SGX virtualization.

- Support SGX virtualization without SGX Flexible Launch Control

SGX hardware supports two "launch control" modes to limit which enclaves can
run.  In the "locked" mode, the hardware prevents enclaves from running unless
they are blessed by a third party.  In the unlocked mode, the kernel is in
full control of which enclaves can run.  The bare-metal SGX code refuses to
launch enclaves unless it is in the unlocked mode.

This sgx_virt_epc driver does not have such a restriction.  This allows guests
which are OK with the locked mode to use SGX, even if the host kernel refuses
to.

- Support exposing SGX2

Due to the same reason above, SGX2 feature detection is added to core SGX code
to allow KVM to expose SGX2 to guest, even currently SGX driver doesn't support
SGX2, because SGX2 can work just fine in guest w/o any interaction to host SGX
driver.

- Restricit SGX guest access to provisioning key

To grant guest being able to fully use SGX, guest needs to be able to access
provisioning key.  The provisioning key is sensitive, and accessing to it should
be restricted. In bare-metal driver, allowing enclave to access provisioning key
is restricted by being able to open /dev/sgx_provision.

Add a new KVM_CAP_SGX_ATTRIBUTE to KVM uAPI to extend above mechanism to KVM
guests as well.  When userspace hypervisor creates a new VM, the new cap is only
added to VM when userspace hypervisior is able to open /dev/sgx_provision,
following the same role as in bare-metal driver.  KVM then traps ECREATE from
guest, and only allows ECREATE with provisioning key bit to run when guest
supports KVM_CAP_SGX_ATTRIBUTE.



Jarkko Sakkinen (1):
  x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()

Kai Huang (3):
  x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
  x86/sgx: Initialize virtual EPC driver even when SGX driver is
    disabled
  x86/sgx: Add helper to update SGX_LEPUBKEYHASHn MSRs

Sean Christopherson (21):
  x86/cpufeatures: Add SGX1 and SGX2 sub-features
  x86/sgx: Add SGX_CHILD_PRESENT hardware error code
  x86/sgx: Introduce virtual EPC for use by KVM guests
  x86/cpu/intel: Allow SGX virtualization without Launch Control support
  x86/sgx: Expose SGX architectural definitions to the kernel
  x86/sgx: Move ENCLS leaf definitions to sgx.h
  x86/sgx: Add SGX2 ENCLS leaf definitions (EAUG, EMODPR and EMODT)
  x86/sgx: Add encls_faulted() helper
  x86/sgx: Add helpers to expose ECREATE and EINIT to KVM
  x86/sgx: Move provisioning device creation out of SGX driver
  KVM: x86: Export kvm_mmu_gva_to_gpa_{read,write}() for SGX (VMX)
  KVM: x86: Define new #PF SGX error code bit
  KVM: x86: Add support for reverse CPUID lookup of scattered features
  KVM: x86: Add reverse-CPUID lookup support for scattered SGX features
  KVM: VMX: Add basic handling of VM-Exit from SGX enclave
  KVM: VMX: Frame in ENCLS handler for SGX virtualization
  KVM: VMX: Add SGX ENCLS[ECREATE] handler to enforce CPUID restrictions
  KVM: VMX: Add emulation of SGX Launch Control LE hash MSRs
  KVM: VMX: Add ENCLS[EINIT] handler to support SGX Launch Control (LC)
  KVM: VMX: Enable SGX virtualization for SGX1, SGX2 and LC
  KVM: x86: Add capability to grant VM access to privileged SGX
    attribute

 Documentation/virt/kvm/api.rst                |  23 +
 arch/x86/Kconfig                              |  12 +
 arch/x86/include/asm/cpufeatures.h            |   2 +
 arch/x86/include/asm/kvm_host.h               |   5 +
 .../cpu/sgx/arch.h => include/asm/sgx.h}      |  50 +-
 arch/x86/include/asm/vmx.h                    |   1 +
 arch/x86/include/uapi/asm/vmx.h               |   1 +
 arch/x86/kernel/cpu/cpuid-deps.c              |   3 +
 arch/x86/kernel/cpu/feat_ctl.c                |  69 ++-
 arch/x86/kernel/cpu/scattered.c               |   2 +
 arch/x86/kernel/cpu/sgx/Makefile              |   1 +
 arch/x86/kernel/cpu/sgx/driver.c              |  17 -
 arch/x86/kernel/cpu/sgx/encl.c                |  28 +-
 arch/x86/kernel/cpu/sgx/encls.h               |  30 +-
 arch/x86/kernel/cpu/sgx/ioctl.c               |  23 +-
 arch/x86/kernel/cpu/sgx/main.c                |  92 +++-
 arch/x86/kernel/cpu/sgx/sgx.h                 |  13 +-
 arch/x86/kernel/cpu/sgx/virt.c                | 355 +++++++++++++
 arch/x86/kvm/Makefile                         |   2 +
 arch/x86/kvm/cpuid.c                          |  89 +++-
 arch/x86/kvm/cpuid.h                          |  50 +-
 arch/x86/kvm/vmx/nested.c                     |  28 +-
 arch/x86/kvm/vmx/nested.h                     |   5 +
 arch/x86/kvm/vmx/sgx.c                        | 465 ++++++++++++++++++
 arch/x86/kvm/vmx/sgx.h                        |  34 ++
 arch/x86/kvm/vmx/vmcs12.c                     |   1 +
 arch/x86/kvm/vmx/vmcs12.h                     |   4 +-
 arch/x86/kvm/vmx/vmx.c                        | 102 +++-
 arch/x86/kvm/vmx/vmx.h                        |   2 +
 arch/x86/kvm/x86.c                            |  23 +
 include/uapi/linux/kvm.h                      |   1 +
 tools/testing/selftests/sgx/defines.h         |   2 +-
 32 files changed, 1419 insertions(+), 116 deletions(-)
 rename arch/x86/{kernel/cpu/sgx/arch.h => include/asm/sgx.h} (89%)
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.c
 create mode 100644 arch/x86/kvm/vmx/sgx.c
 create mode 100644 arch/x86/kvm/vmx/sgx.h
```
#### [kvm-unit-tests PATCH v4 0/6] CSS Mesurement Block
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Mon Mar  1 11:46:59 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12109525
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 32E7AC433E6
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 11:48:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C7E764E09
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 11:48:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234232AbhCALsM (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 06:48:12 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:28036 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234206AbhCALr5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 1 Mar 2021 06:47:57 -0500
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 121BblMx032412
        for <kvm@vger.kernel.org>; Mon, 1 Mar 2021 06:47:14 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=FMygeHcg7EQMrlWf+owqbybxpRxFeDKvqbBpl0XLMfY=;
 b=ZY6OloeoY017ULFazCT1mkV/sP530cYXITUde3MT2AWgB00DuYbpnLc+Ct9sUFHHYBoD
 58cC57eaOe2h1UNNoDxjeNzteR3gvktrazvXjMypkb9d0955Wjw4jznqSNBFnsW3dMzm
 eEKghtUx0xa4ZBgnfAz8Vrdoz/mPPTTUWoMElbg6THSrPF+iWsQDhKohbhTDWOEGg8mL
 29UBHy4ocQ9ZzvJINC1z0PbardVEtT1A1FSKc2W5Vgqe9k7WyQvbk3ktDSwXmpcBHbWC
 4s9HSPdyltFb2/3w8TgzJHqqwcqYC+7/zE5sWzIyAaldC+XTHHMOjcLnjQn7zONiv72a Cg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 370ve8euv5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 01 Mar 2021 06:47:14 -0500
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 121Bbu6I033221
        for <kvm@vger.kernel.org>; Mon, 1 Mar 2021 06:47:12 -0500
Received: from ppma04fra.de.ibm.com (6a.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.106])
        by mx0a-001b2d01.pphosted.com with ESMTP id 370ve8euua-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 01 Mar 2021 06:47:12 -0500
Received: from pps.filterd (ppma04fra.de.ibm.com [127.0.0.1])
        by ppma04fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 121Bhr0x024762;
        Mon, 1 Mar 2021 11:47:10 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma04fra.de.ibm.com with ESMTP id 36ydq88xg7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 01 Mar 2021 11:47:09 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 121Bl6D257606560
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 1 Mar 2021 11:47:07 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DE65BAE053;
        Mon,  1 Mar 2021 11:47:06 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8293FAE051;
        Mon,  1 Mar 2021 11:47:06 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.52.26])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  1 Mar 2021 11:47:06 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v4 0/6] CSS Mesurement Block
Date: Mon,  1 Mar 2021 12:46:59 +0100
Message-Id: <1614599225-17734-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-01_06:2021-02-26,2021-03-01 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 malwarescore=0 suspectscore=0 mlxscore=0 spamscore=0 impostorscore=0
 phishscore=0 bulkscore=0 priorityscore=1501 mlxlogscore=999 adultscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103010098
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We tests the update of the Mesurement Block (MB) format 0
and format 1 using a serie of senseid requests.

*Warning*: One of the tests for format-1 will unexpectedly fail for QEMU elf
unless the QEMU patch "css: SCHIB measurement block origin must be aligned"
is applied.
With Protected Virtualization, the PGM is correctly recognized.

The MB format 1 is only provided if the Extended mesurement Block
feature is available.

This feature is exposed by the CSS characteristics general features
stored by the Store Channel Subsystem Characteristics CHSC command,
consequently, we implement the CHSC instruction call and the SCSC CHSC
command.

In order to ease the writing of new tests using:
- interrupt
- enablement of a subchannel
- multiple I/O on a subchannel

We do the following simplifications:
- we create a CSS initialization routine
- we register the I/O interrupt handler on CSS initialization
- we do not enable or disable a subchannel in the senseid test,
  assuming this test is done after the enable test, this allows
  to create traffic using the SSCH used by senseid.
- we add a css_enabled() function to test if a subchannel is enabled.

@Connie, I restructured the patches but I did not modify the
functionalities, so I kept your R-B, I hope you are OK with this.

Regards,
Pierre

Pierre Morel (6):
  s390x: css: Store CSS Characteristics
  s390x: css: simplifications of the tests
  s390x: css: extending the subchannel modifying functions
  s390x: css: implementing Set CHannel Monitor
  s390x: css: testing measurement block format 0
  s390x: css: testing measurement block format 1

 lib/s390x/css.h     | 116 +++++++++++++++++++++-
 lib/s390x/css_lib.c | 232 +++++++++++++++++++++++++++++++++++++++++---
 s390x/css.c         | 228 +++++++++++++++++++++++++++++++++++++++----
 3 files changed, 542 insertions(+), 34 deletions(-)
```
#### [kvm-unit-tests PATCH v3 0/3] s390x: mvpg test
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Mon Mar  1 18:28:27 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12110467
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CE0F7C433DB
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 18:34:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9EF5C64E4E
	for <kvm@archiver.kernel.org>; Mon,  1 Mar 2021 18:34:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240168AbhCASeY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 1 Mar 2021 13:34:24 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:16648 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S238228AbhCAS3c (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 1 Mar 2021 13:29:32 -0500
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 121I4POv081043
        for <kvm@vger.kernel.org>; Mon, 1 Mar 2021 13:28:36 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=YbG2OBL2N5PMXDb2+dtY5EXRge19HsWuqPlyqbRvF3A=;
 b=LB8ATkuhTPkBCA2aUJSFAGIH9xHfB5+PxLtpJ2NyTtghfCHw/Lk7O4OEhCTbne/4zV13
 ThyjOwiffsxB4IV7hLL2Zyck4lidKZkdYxpV2UypvCad9xoCSbj26fkFVf07LcfUXSfU
 tpkb9wRAZ5nF4x4PbIpxO3mxRLPKj2lyLrX/NTgggtBPHBPX3w18WzFlev2oMZAwqCBg
 TwvqWhLSatgXCPBWHf2RbW4Sf2CUL3OUe1E1JV+XLAJv1Zvqme80m2EX7gWo5sgWAP+H
 dJbwxJGiSf+eg82MmG35tCtoTt16y9LKBxHcDZ2n4tEaEqJEP2yNjiXWLdjW1DmHRPE0 Pw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37142k3cxj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 01 Mar 2021 13:28:36 -0500
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 121IHRtZ147161
        for <kvm@vger.kernel.org>; Mon, 1 Mar 2021 13:28:36 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37142k3cx4-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 01 Mar 2021 13:28:36 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 121ISYKu015267;
        Mon, 1 Mar 2021 18:28:34 GMT
Received: from b06cxnps3075.portsmouth.uk.ibm.com
 (d06relay10.portsmouth.uk.ibm.com [9.149.109.195])
        by ppma06ams.nl.ibm.com with ESMTP id 370c59s61b-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 01 Mar 2021 18:28:34 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 121ISVhx45613504
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 1 Mar 2021 18:28:31 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 285E642047;
        Mon,  1 Mar 2021 18:28:31 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B838642042;
        Mon,  1 Mar 2021 18:28:30 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.10.194])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  1 Mar 2021 18:28:30 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: david@redhat.com, thuth@redhat.com, frankja@linux.ibm.com,
        cohuck@redhat.com, pmorel@linux.ibm.com, borntraeger@de.ibm.com
Subject: [kvm-unit-tests PATCH v3 0/3] s390x: mvpg test
Date: Mon,  1 Mar 2021 19:28:27 +0100
Message-Id: <20210301182830.478145-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-01_12:2021-03-01,2021-03-01 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 phishscore=0
 bulkscore=0 priorityscore=1501 malwarescore=0 adultscore=0 mlxlogscore=869
 spamscore=0 clxscore=1015 suspectscore=0 lowpriorityscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103010146
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A simple unit test for the MVPG instruction.

The timeout is set to 10 seconds because the test should complete in a
fraction of a second even on busy machines. If the test is run in VSIE
and the host of the host is not handling MVPG properly, the test will
probably hang.

Testing MVPG behaviour in VSIE is the main motivation for this test.

Anything related to storage keys is not tested.

v2->v3
* fix copyright (2020 is over!)
* add the third patch to skip some known issues when running in TCG

v1->v2
* droppped patch 2 which introduced is_pgm();
* patch 1: replace a hardcoded value with the new macro SVC_LEAVE_PSTATE
* patch 2: clear_pgm_int() returns the old value, use that instad of is_pgm()

Claudio Imbrenda (3):
  s390x: introduce leave_pstate to leave userspace
  s390x: mvpg: simple test
  s390x: mvpg: skip some tests when using TCG

 s390x/Makefile           |   1 +
 lib/s390x/asm/arch_def.h |   7 +
 lib/s390x/interrupt.c    |  12 +-
 s390x/mvpg.c             | 273 +++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg      |   4 +
 5 files changed, 295 insertions(+), 2 deletions(-)
 create mode 100644 s390x/mvpg.c
```
