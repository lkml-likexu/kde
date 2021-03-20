

#### [PATCH v3 00/25] KVM SGX virtualization support
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Fri Mar 19 07:29:27 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12150283
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2551BC433DB
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 07:30:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EE6C264F6B
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 07:30:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234082AbhCSH3z (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Mar 2021 03:29:55 -0400
Received: from mga18.intel.com ([134.134.136.126]:35336 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S233937AbhCSH3o (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Mar 2021 03:29:44 -0400
IronPort-SDR: 
 RmAKuftnLEbZTnIz3BxLLXkrZZa6czLG2vd2/qi9+P+d2IlfGR26Umw2+bMVTex4nSobYSPrbE
 peyoMbAheGSQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9927"; a="177432613"
X-IronPort-AV: E=Sophos;i="5.81,261,1610438400";
   d="scan'208";a="177432613"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga106.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Mar 2021 00:29:44 -0700
IronPort-SDR: 
 kHcZXQXwpAehLrcZlq+42+ldbr6qdepsskkQClPqELIS2ABqCmu+n6mXidRpNaBXnWaVmgfAT8
 knW0hf+KvO2w==
X-IronPort-AV: E=Sophos;i="5.81,261,1610438400";
   d="scan'208";a="413411837"
Received: from dlmeisen-mobl1.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.255.229.165])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Mar 2021 00:29:34 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-sgx@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, seanjc@google.com, jarkko@kernel.org,
        luto@kernel.org, dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        jethro@fortanix.com, b.thiel@posteo.de, jmattson@google.com,
        joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        corbet@lwn.net
Subject: [PATCH v3 00/25] KVM SGX virtualization support
Date: Fri, 19 Mar 2021 20:29:27 +1300
Message-Id: <cover.1616136307.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds KVM SGX virtualization support. The first 14 patches starting
with x86/sgx or x86/cpu.. are necessary changes to x86 and SGX core/driver to
support KVM SGX virtualization, while the rest are patches to KVM subsystem.

This series is based against latest tip/x86/sgx, which has Jarkko's NUMA
allocation support.

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

v2->v3:

 - No big change in design, structure of patch series, etc.
 - Rebased to lastest tip/x86/sgx, to resolve merge conflict of patch 3
   (x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()).
 - Addressed some Nit issues found by Sean in v2.
 - Also addressed some Nit issues reported by checkpatch.pl. Now there's no
   checkpatch issues.
 - Updated patch 3 (x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()):
   - Removed Jarkko from author, per request.
   - Changed to replace all call sites of sgx_free_epc_page() with new
     sgx_encl_free_epc_page(), to make this patch doesn't have functional
     changes (except a WARN upon EREMOVE failure requestd by Dave).
   - Rebased to tip/x86/sgx, which has Jarkko's NUMA allocation.
   - Added Jarkko's Acked-by.
 - Updated patch 8 (x86/sgx: Expose SGX architectural definitions to the
   kernel) to add MAINTAINER file update to include new introduced asm/sgx.h.
 - Updated patch 13 (x86/sgx: Add helpers to expose ECREATE and EINIT to KVM)
   to use addr and size directly in access_ok()s (which won't be triggered
   anyway).

v1->v2:

 - No big change in design, structural of patch series, etc.
 - Addressed Boris's comments regarding to suppressing both SGX1 and SGX2 in
   /proc/cpuinfo, and improvement in feat_ctl.c when enabling SGX (patch 2
   and 6).
 - Addressed Sean's comments for both x86 part patches and KVM patches (patch 3,
   5, 9, 12, 19, 21).
 - Addressed Dave's comments in RFC v6 series (patch 13).

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


Kai Huang (4):
  x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
  x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()
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
 MAINTAINERS                                   |   1 +
 arch/x86/Kconfig                              |  12 +
 arch/x86/include/asm/cpufeatures.h            |   2 +
 arch/x86/include/asm/kvm_host.h               |   5 +
 .../cpu/sgx/arch.h => include/asm/sgx.h}      |  50 +-
 arch/x86/include/asm/vmx.h                    |   1 +
 arch/x86/include/uapi/asm/vmx.h               |   1 +
 arch/x86/kernel/cpu/cpuid-deps.c              |   3 +
 arch/x86/kernel/cpu/feat_ctl.c                |  71 ++-
 arch/x86/kernel/cpu/scattered.c               |   2 +
 arch/x86/kernel/cpu/sgx/Makefile              |   1 +
 arch/x86/kernel/cpu/sgx/driver.c              |  17 -
 arch/x86/kernel/cpu/sgx/encl.c                |  42 +-
 arch/x86/kernel/cpu/sgx/encl.h                |   1 +
 arch/x86/kernel/cpu/sgx/encls.h               |  30 +-
 arch/x86/kernel/cpu/sgx/ioctl.c               |  29 +-
 arch/x86/kernel/cpu/sgx/main.c                |  96 +++-
 arch/x86/kernel/cpu/sgx/sgx.h                 |  13 +-
 arch/x86/kernel/cpu/sgx/virt.c                | 369 ++++++++++++++
 arch/x86/kvm/Makefile                         |   2 +
 arch/x86/kvm/cpuid.c                          |  89 +++-
 arch/x86/kvm/cpuid.h                          |  50 +-
 arch/x86/kvm/vmx/nested.c                     |  28 +-
 arch/x86/kvm/vmx/nested.h                     |   5 +
 arch/x86/kvm/vmx/sgx.c                        | 481 ++++++++++++++++++
 arch/x86/kvm/vmx/sgx.h                        |  34 ++
 arch/x86/kvm/vmx/vmcs12.c                     |   1 +
 arch/x86/kvm/vmx/vmcs12.h                     |   4 +-
 arch/x86/kvm/vmx/vmx.c                        | 109 +++-
 arch/x86/kvm/vmx/vmx.h                        |   2 +
 arch/x86/kvm/x86.c                            |  23 +
 include/uapi/linux/kvm.h                      |   1 +
 tools/testing/selftests/sgx/defines.h         |   2 +-
 34 files changed, 1476 insertions(+), 124 deletions(-)
 rename arch/x86/{kernel/cpu/sgx/arch.h => include/asm/sgx.h} (89%)
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.c
 create mode 100644 arch/x86/kvm/vmx/sgx.c
 create mode 100644 arch/x86/kvm/vmx/sgx.h
```
#### [kvm-unit-tests PATCH 0/4] RFC: Minor arm/arm64 MMU fixes and checks
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
From patchwork Fri Mar 19 12:24:10 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 12150957
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 1EED1C433DB
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 12:25:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E112F64F7E
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 12:25:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229903AbhCSMY5 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Mar 2021 08:24:57 -0400
Received: from foss.arm.com ([217.140.110.172]:48398 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229927AbhCSMYb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Mar 2021 08:24:31 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 4AC5BED1;
        Fri, 19 Mar 2021 05:24:31 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 8FEA73F70D;
        Fri, 19 Mar 2021 05:24:30 -0700 (PDT)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: drjones@redhat.com, alexandru.elisei@arm.com,
        Nikos Nikoleris <nikos.nikoleris@arm.com>
Subject: [kvm-unit-tests PATCH 0/4] RFC: Minor arm/arm64 MMU fixes and checks
Date: Fri, 19 Mar 2021 12:24:10 +0000
Message-Id: <20210319122414.129364-1-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Prior to this set of fixes, the code in setup() which we call to
initialize the system has a circular dependency. cpu_init()
(eventually) calls spin_lock() and __mmu_enabled(). However, at this
point, __mmu_enabled() may have undefined behavior as we haven't
initialized the current thread_info (cpu field). Moving
thread_info_init() above cpu_init() is not possible as it relies on
mpidr_to_cpu() which won't return the right results before cpu_init().
In addition, mem_init() also calls __mmu_enabled() and therefore
suffers from the same problem. Right now, everything works as
thread_info maps to memory which is implicitly initialized to 0 (cpu =
0) and makes the assumption that the cpu that runs setup() will be the
first cpu in the DT.

This set of patches changes the code slightly and avoids this
assumptions. In addition, it adds assertions to catch problems like
the above. The current solution relies on the thread_info() of the cpu
that setup() run to be initialized to zero (should we make it
explicit?).

There are a couple of options I considered in addressing this issue
which didn't seem satisfactory:

- Change the mmu_disabled_count global variable to mmu_enabled_count
  to count the number of active mmu's and bypass __mmu_enabled() when
  it's 0. This is a global variable and at the momement all write to
  it are protected by a lock but it's rather fragile and could easily
  cause issues in the future.
- Explicitly initialize current_thread_info()->cpu = 0 in setup()
  before anything else or make the first call of thread_info_init() a
  special case and avoid looking up mpidr_to_cpu(). This way we can
  move thread_info_init() to the top of setup(). If the CPU setup is
  running on is not the first that appears in the DT then this
  solution won't work.

Thanks,

Nikos

Nikos Nikoleris (4):
  arm/arm64: Avoid calling cpumask_test_cpu for CPUs above nr_cpu
  arm/arm64: Read system registers to get the state of the MMU
  arm/arm64: Track whether thread_info has been initialized
  arm/arm64: Add sanity checks to the cpumask API

 lib/arm/asm/cpumask.h     |  7 ++++++-
 lib/arm/asm/mmu-api.h     |  7 +------
 lib/arm/asm/processor.h   |  7 +++++++
 lib/arm/asm/thread_info.h |  1 +
 lib/arm64/asm/processor.h |  1 +
 lib/arm/mmu.c             | 16 ++++++++--------
 lib/arm/processor.c       | 10 ++++++++--
 lib/arm64/processor.c     | 10 ++++++++--
 8 files changed, 40 insertions(+), 19 deletions(-)
```
#### [PATCH v1 0/2] s390/kvm: VSIE: fix prefixing and MSO for MVPG
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
From patchwork Fri Mar 19 19:33:52 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12151797
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F3270C433E9
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 19:34:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CF1886196B
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 19:34:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231156AbhCSTeV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Mar 2021 15:34:21 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:41326 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230467AbhCSTeB (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Mar 2021 15:34:01 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12JJXJI7161488;
        Fri, 19 Mar 2021 15:34:01 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=QiNxQUHTB+LUXXdMQbtriTAifyLUm8O4BBI9qJujYMs=;
 b=HPbRBdlaHS/zn30j9Spu03Pktsbaruqrul2VLvWrOEc5s1xXPB4AG7t8yZ4r7WukJ4tX
 TzR326l1Qx6vyJTr6d14pJWNUZCihsN06XkIQsDk/anK8ifWwGqaXzjqXpdqvcefzMZl
 Yq3QVmDGQ9zKg6zQ/3YH2lKvKp4iRV5RnoZPfC+Kb4xuBA5qlavgvFxPZFmNmc8BwwBA
 FVk7lUvSI9Z2jee3h+QKc1gHvW98CZV3QrJ1q0ONK1ICUP0KuMb+qLvf8KJ9zqgMSTWh
 VhdhIL4+JPWPsE1TozTOqscbT+yMnB22hnkllMXeqPZaSsEcIhdXfo/Ux0ISDU1A+Ucs 1Q==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37c7m74ctf-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 19 Mar 2021 15:34:01 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12JJY1Vt165196;
        Fri, 19 Mar 2021 15:34:01 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37c7m74csy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 19 Mar 2021 15:34:00 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12JJW3tG016919;
        Fri, 19 Mar 2021 19:33:58 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03ams.nl.ibm.com with ESMTP id 378n18p00a-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 19 Mar 2021 19:33:58 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12JJXt2A16384384
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 19 Mar 2021 19:33:55 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4619BA4054;
        Fri, 19 Mar 2021 19:33:55 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D9D62A405B;
        Fri, 19 Mar 2021 19:33:54 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.2.56])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 19 Mar 2021 19:33:54 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org, linux-s390@vger.kernel.org
Subject: [PATCH v1 0/2] s390/kvm: VSIE: fix prefixing and MSO for MVPG
Date: Fri, 19 Mar 2021 20:33:52 +0100
Message-Id: <20210319193354.399587-1-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-19_10:2021-03-19,2021-03-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 phishscore=0 spamscore=0
 suspectscore=0 adultscore=0 mlxlogscore=880 lowpriorityscore=0
 priorityscore=1501 clxscore=1015 bulkscore=0 impostorscore=0
 malwarescore=0 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103190130
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The guest real address needs to pass through prefixing in order to yield
the absolute address.

The absolute address needs to be offset by the MSO in order to get the
host virtual address.

Claudio Imbrenda (2):
  s390/kvm: split kvm_s390_real_to_abs
  s390/kvm: VSIE: fix MVPG handling for prefixing and MSO

 arch/s390/kvm/gaccess.h | 23 +++++++++++++++++------
 arch/s390/kvm/vsie.c    | 10 +++++++---
 2 files changed, 24 insertions(+), 9 deletions(-)
```
