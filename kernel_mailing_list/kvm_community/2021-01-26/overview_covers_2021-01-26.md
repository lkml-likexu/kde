

#### [RFC PATCH v3 00/27] KVM SGX virtualization support
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Tue Jan 26 10:10:57 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12046063
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0520EC433E0
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 10:13:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AA45223101
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 10:13:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729998AbhAZKNl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 05:13:41 -0500
Received: from mga12.intel.com ([192.55.52.136]:5511 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2391816AbhAZKMA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 05:12:00 -0500
IronPort-SDR: 
 a1woGj1gVvNX4TVQiXSKGcH+5zvcvH56ebjqBV1IaOEzZfGi0JYxg0+u9HLTGdSg+qVYv/WjWq
 PYbEG8EEELxA==
X-IronPort-AV: E=McAfee;i="6000,8403,9875"; a="159055144"
X-IronPort-AV: E=Sophos;i="5.79,375,1602572400";
   d="scan'208";a="159055144"
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Jan 2021 02:11:18 -0800
IronPort-SDR: 
 v+wzURqulqgtOekyy0QOI65eDYzXmvVWGIsrKKxFAIUflrku5fmIkGFQ/8w+IeGbizcrfvhdGc
 EkqHI1mEOOTg==
X-IronPort-AV: E=Sophos;i="5.79,375,1602572400";
   d="scan'208";a="402693750"
Received: from jaferhus-mobl3.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.254.122.186])
  by fmsmga004-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 26 Jan 2021 02:11:13 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, haitao.huang@intel.com, pbonzini@redhat.com,
        bp@alien8.de, tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        jethro@fortanix.com, b.thiel@posteo.de, jmattson@google.com,
        joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        corbet@lwn.net
Subject: [RFC PATCH v3 00/27] KVM SGX virtualization support
Date: Tue, 26 Jan 2021 23:10:57 +1300
Message-Id: <cover.1611634586.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

--- Disclaimer ---

These patches were originally written by Sean Christopherson while at Intel.
Now that Sean has left Intel, I (Kai) have taken over getting them upstream.
This series needs more review before it can be merged.  It is being posted
publicly and under RFC so Sean and others can review it. Maintainers are safe
ignoring it for now.

------------------

Hi all,

This series adds KVM SGX virtualization support. The first 15 patches starting
with x86/sgx or x86/cpu.. are necessary changes to x86 and SGX core/driver to
support KVM SGX virtualization, while the rest are patches to KVM subsystem.

Please help to review this series. Any feedback is highly appreciated.
Please let me know if I forgot to CC anyone, or anyone wants to be removed from
CC. Thanks in advance!

This series is based against tip/x86/sgx. You can also get the code from
upstream branch of kvm-sgx repo on github:

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

 - Split original "x86/cpufeatures: Add SGX1 and SGX2 sub-features" patch into
   two patches, by splitting moving SGX_LC bit also into cpuid-deps table logic
   into a separate patch 2:
       [RFC PATCH v3 01/27] x86/cpufeatures: Add SGX1 and SGX2 sub-features
       [RFC PATCH v3 02/27] x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
 - Changed from /dev/sgx_virt_epc to /dev/sgx_vepc, per Jarkko. And accordingly,
   changed prefix 'sgx_virt_epc_xx' to 'sgx_vepc_xx' in various functions and
   structures.
 - Changed CONFIG_X86_SGX_VIRTUALIZATION to CONFIG_X86_SGX_KVM, per Dave. Couple
   of x86 patches and KVM patches are changed too due to the renaming.

v1->v2:

 - Refined this cover letter by addressing comments from Dave and Jarkko.
 - The original patch which introduced new X86_FEATURE_SGX1/SGX2 were replaced
   by 3 new patches from Sean, following Boris and Sean's discussion.
       [RFC PATCH v2 01/26] x86/cpufeatures: Add SGX1 and SGX2 sub-features
       [RFC PATCH v2 18/26] KVM: x86: Add support for reverse CPUID lookup of scattered features
       [RFC PATCH v2 19/26] KVM: x86: Add reverse-CPUID lookup support for scattered SGX features
 - The original patch 1
       x86/sgx: Split out adding EPC page to free list to separate helper
   was replaced with 2 new patches from Jarkko
       [RFC PATCH v2 02/26] x86/sgx: Remove a warn from sgx_free_epc_page()
       [RFC PATCH v2 03/26] x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()
   addressing Jarkko's comments.
 - Moved modifying sgx_init() to always initialize sgx_virt_epc_init() out of
   patch
       x86/sgx: Introduce virtual EPC for use by KVM guests
   to a separate patch:
       [RFC PATCH v2 07/26] x86/sgx: Initialize virtual EPC driver even when SGX driver is disabled
   to address Dave's comment that patch ordering can be improved due to before
   patch "Allow SGX virtualization without Launch Control support", all SGX,
   including SGX virtualization, is actually disabled when SGX LC is not
   present.

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

Jarkko Sakkinen (2):
  x86/sgx: Remove a warn from sgx_free_epc_page()
  x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()

Kai Huang (3):
  x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
  x86/sgx: Initialize virtual EPC driver even when SGX driver is
    disabled
  x86/sgx: Add helper to update SGX_LEPUBKEYHASHn MSRs

Sean Christopherson (22):
  x86/cpufeatures: Add SGX1 and SGX2 sub-features
  x86/sgx: Add SGX_CHILD_PRESENT hardware error code
  x86/sgx: Introduce virtual EPC for use by KVM guests
  x86/cpu/intel: Allow SGX virtualization without Launch Control support
  x86/sgx: Expose SGX architectural definitions to the kernel
  x86/sgx: Move ENCLS leaf definitions to sgx_arch.h
  x86/sgx: Add SGX2 ENCLS leaf definitions (EAUG, EMODPR and EMODT)
  x86/sgx: Add encls_faulted() helper
  x86/sgx: Add helpers to expose ECREATE and EINIT to KVM
  x86/sgx: Move provisioning device creation out of SGX driver
  KVM: VMX: Convert vcpu_vmx.exit_reason to a union
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
 arch/x86/include/asm/sgx.h                    |  19 +
 .../cpu/sgx/arch.h => include/asm/sgx_arch.h} |  20 +
 arch/x86/include/asm/vmx.h                    |   1 +
 arch/x86/include/uapi/asm/vmx.h               |   1 +
 arch/x86/kernel/cpu/cpuid-deps.c              |   3 +
 arch/x86/kernel/cpu/feat_ctl.c                |  70 ++-
 arch/x86/kernel/cpu/scattered.c               |   2 +
 arch/x86/kernel/cpu/sgx/Makefile              |   1 +
 arch/x86/kernel/cpu/sgx/driver.c              |  17 -
 arch/x86/kernel/cpu/sgx/encl.c                |  15 +-
 arch/x86/kernel/cpu/sgx/encls.h               |  30 +-
 arch/x86/kernel/cpu/sgx/ioctl.c               |  23 +-
 arch/x86/kernel/cpu/sgx/main.c                |  87 +++-
 arch/x86/kernel/cpu/sgx/sgx.h                 |   4 +-
 arch/x86/kernel/cpu/sgx/virt.c                | 347 +++++++++++++
 arch/x86/kernel/cpu/sgx/virt.h                |  14 +
 arch/x86/kvm/Makefile                         |   2 +
 arch/x86/kvm/cpuid.c                          |  89 +++-
 arch/x86/kvm/cpuid.h                          |  50 +-
 arch/x86/kvm/vmx/nested.c                     |  70 ++-
 arch/x86/kvm/vmx/nested.h                     |   5 +
 arch/x86/kvm/vmx/sgx.c                        | 462 ++++++++++++++++++
 arch/x86/kvm/vmx/sgx.h                        |  34 ++
 arch/x86/kvm/vmx/vmcs12.c                     |   1 +
 arch/x86/kvm/vmx/vmcs12.h                     |   4 +-
 arch/x86/kvm/vmx/vmx.c                        | 171 +++++--
 arch/x86/kvm/vmx/vmx.h                        |  27 +-
 arch/x86/kvm/x86.c                            |  24 +
 include/uapi/linux/kvm.h                      |   1 +
 tools/testing/selftests/sgx/defines.h         |   2 +-
 34 files changed, 1482 insertions(+), 156 deletions(-)
 create mode 100644 arch/x86/include/asm/sgx.h
 rename arch/x86/{kernel/cpu/sgx/arch.h => include/asm/sgx_arch.h} (96%)
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.c
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.h
 create mode 100644 arch/x86/kvm/vmx/sgx.c
 create mode 100644 arch/x86/kvm/vmx/sgx.h
Acked-by: Dave Hansen <dave.hansen@intel.com>
Acked-by: Dave Hansen <dave.hansen@intel.com>
```
#### [RFC PATCH 0/7] kvm: arm64: Implement SW/HW combined dirty log
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Tue Jan 26 12:44:37 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Keqian Zhu <zhukeqian1@huawei.com>
X-Patchwork-Id: 12046537
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A1832C433DB
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 13:15:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7EC8C2311C
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 13:15:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2391777AbhAZNP2 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 08:15:28 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:11502 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2391790AbhAZMp6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 07:45:58 -0500
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DQ5yR2C4WzjDdv;
        Tue, 26 Jan 2021 20:43:59 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.184.42) by
 DGGEMS412-HUB.china.huawei.com (10.3.19.212) with Microsoft SMTP Server id
 14.3.498.0; Tue, 26 Jan 2021 20:45:01 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>, Marc Zyngier <maz@kernel.org>,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Alex Williamson <alex.williamson@redhat.com>,
        Kirti Wankhede <kwankhede@nvidia.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Robin Murphy <robin.murphy@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, <jiangkunkun@huawei.com>,
        <xiexiangyou@huawei.com>, <zhengchuan@huawei.com>,
        <yubihong@huawei.com>
Subject: [RFC PATCH 0/7] kvm: arm64: Implement SW/HW combined dirty log
Date: Tue, 26 Jan 2021 20:44:37 +0800
Message-ID: <20210126124444.27136-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.42]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The intention:

On arm64 platform, we tracking dirty log of vCPU through guest memory abort.
KVM occupys some vCPU time of guest to change stage2 mapping and mark dirty.
This leads to heavy side effect on VM, especially when multi vCPU race and
some of them block on kvm mmu_lock.

DBM is a HW auxiliary approach to log dirty. MMU chages PTE to be writable if
its DBM bit is set. Then KVM doesn't occupy vCPU time to log dirty.

About this patch series:

The biggest problem of apply DBM for stage2 is that software must scan PTs to
collect dirty state, which may cost much time and affect downtime of migration.

This series realize a SW/HW combined dirty log that can effectively solve this
problem (The smmu side can also use this approach to solve dma dirty log tracking).

The core idea is that we do not enable hardware dirty at start (do not add DBM bit).
When a arbitrary PT occurs fault, we execute soft tracking for this PT and enable
hardware tracking for its *nearby* PTs (e.g. Add DBM bit for nearby 16PTs). Then when
sync dirty log, we have known all PTs with hardware dirty enabled, so we do not need
to scan all PTs.

        mem abort point             mem abort point
              ↓                            ↓
---------------------------------------------------------------
        |********|        |        |********|        |        |
---------------------------------------------------------------
             ↑                            ↑
        set DBM bit of               set DBM bit of
     this PT section (64PTEs)      this PT section (64PTEs)

We may worry that when dirty rate is over-high we still need to scan too much PTs.
We mainly concern the VM stop time. With Qemu dirty rate throttling, the dirty memory
is closing to the VM stop threshold, so there is a little PTs to scan after VM stop.

It has the advantages of hardware tracking that minimizes side effect on vCPU,
and also has the advantages of software tracking that controls vCPU dirty rate.
Moreover, software tracking helps us to scan PTs at some fixed points, which
greatly reduces scanning time. And the biggest benefit is that we can apply this
solution for dma dirty tracking.

Test:

Host: Kunpeng 920 with 128 CPU 512G RAM. Disable Transparent Hugepage (Ensure test result
      is not effected by dissolve of block page table at the early stage of migration).
VM:   16 CPU 16GB RAM. Run 4 pair of (redis_benchmark+redis_server).

Each run 5 times for software dirty log and SW/HW conbined dirty log. 

Test result:

Gain 5%~7% improvement of redis QPS during VM migration.
VM downtime is not affected fundamentally.
About 56.7% of DBM is effectively used.

Keqian Zhu (7):
  arm64: cpufeature: Add API to report system support of HWDBM
  kvm: arm64: Use atomic operation when update PTE
  kvm: arm64: Add level_apply parameter for stage2_attr_walker
  kvm: arm64: Add some HW_DBM related pgtable interfaces
  kvm: arm64: Add some HW_DBM related mmu interfaces
  kvm: arm64: Only write protect selected PTE
  kvm: arm64: Start up SW/HW combined dirty log

 arch/arm64/include/asm/cpufeature.h  |  12 +++
 arch/arm64/include/asm/kvm_host.h    |   6 ++
 arch/arm64/include/asm/kvm_mmu.h     |   7 ++
 arch/arm64/include/asm/kvm_pgtable.h |  45 ++++++++++
 arch/arm64/kvm/arm.c                 | 125 ++++++++++++++++++++++++++
 arch/arm64/kvm/hyp/pgtable.c         | 130 ++++++++++++++++++++++-----
 arch/arm64/kvm/mmu.c                 |  47 +++++++++-
 arch/arm64/kvm/reset.c               |   8 +-
 8 files changed, 351 insertions(+), 29 deletions(-)
```
#### [RFC PATCH v1 0/5] Enable CPU TTRem feature for stage-2
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Tue Jan 26 13:41:57 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12046673
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EDB9AC433E0
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 13:50:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C48222255F
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 13:50:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404890AbhAZNto (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 08:49:44 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:11445 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2404850AbhAZNmy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 08:42:54 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4DQ7DT5ZtPzjCXP;
        Tue, 26 Jan 2021 21:41:13 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS406-HUB.china.huawei.com (10.3.19.206) with Microsoft SMTP Server id
 14.3.498.0; Tue, 26 Jan 2021 21:42:04 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, Marc Zyngier <maz@kernel.org>,
        Will Deacon <will@kernel.org>,
        Catalin Marinas <catalin.marinas@arm.com>
CC: Mark Rutland <mark.rutland@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        <wanghaibin.wang@huawei.com>, <yezengruan@huawei.com>,
        <zhukeqian1@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH v1 0/5] Enable CPU TTRem feature for stage-2
Date: Tue, 26 Jan 2021 21:41:57 +0800
Message-ID: <20210126134202.381996-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,
This series enable CPU TTRem feature for stage-2 page table and a RFC is sent
for some comments, thanks.

The ARMv8.4 TTRem feature offers 3 levels of support when changing block
size without changing any other parameters that are listed as requiring use
of break-before-make. And I found that maybe we can use this feature to make
some improvement for stage-2 page table and the following explains what
TTRem exactly does for the improvement.

If migration of a VM with hugepages is canceled midway, KVM will adjust the
stage-2 table mappings back to block mappings. We currently use BBM to replace
the table entry with a block entry. Take adjustment of 1G block mapping as an
example, with BBM procedures, we have to invalidate the old table entry first,
flush TLB and unmap the old table mappings, right before installing the new
block entry.

So there will be a bit long period when the old table entry is invalid before
installation of the new block entry, if other vCPUs access any guest page within
the 1G range during this period and find the table entry invalid, they will all
exit from guest with a translation fault. Actually, these translation faults
are not necessary, because the block mapping will be built later. Besides, KVM
will still try to build 1G block mappings for these spurious translation faults,
and will perform cache maintenance operations, page table walk, etc.

In summary, the spurious faults are caused by invalidation in BBM procedures.
Approaches of TTRem level 1,2 ensure that there will not be a moment when the
old table entry is invalid before installation of the new block entry. However,
level-2 method will possibly lead to a TLB conflict which is bothering, so we
use nT both at level-1 and level-2 case to avoid handling TLB conflict aborts.

For an implementation which meets level 1 or level 2, the CPU has two responses
to choose when accessing a block table entry with nT bit set: Firstly, CPU will
generate a translation fault, the effect of this response is simier to BBM.
Secondly, CPU can use the block entry for translation. So with the second kind
of implementation, the above described spurious translations can be prevented.

Yanan Wang (5):
  KVM: arm64: Detect the ARMv8.4 TTRem feature
  KVM: arm64: Add an API to get level of TTRem supported by hardware
  KVM: arm64: Support usage of TTRem in guest stage-2 translation
  KVM: arm64: Add handling of coalescing tables into a block mapping
  KVM: arm64: Adapt page-table code to new handling of coalescing tables

 arch/arm64/include/asm/cpucaps.h    |  3 +-
 arch/arm64/include/asm/cpufeature.h | 13 ++++++
 arch/arm64/kernel/cpufeature.c      | 10 +++++
 arch/arm64/kvm/hyp/pgtable.c        | 62 +++++++++++++++++++++++------
 4 files changed, 74 insertions(+), 14 deletions(-)
```
#### [PATCH v2 00/15] KVM: x86: Conditional Hyper-V emulation enablement
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Tue Jan 26 13:48:01 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12046711
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 72027C433E6
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 14:00:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4328B22B2C
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 14:00:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405616AbhAZN7e (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 08:59:34 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:35916 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2404918AbhAZNtu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 26 Jan 2021 08:49:50 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1611668903;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=PDlj9UJuoXlG2+dcv/eqawylXilbohUP5Xl1nIN0jeA=;
        b=cjEMLZjCVs+49bwzHd/s2Bl1Jg1T4QJf+z5YxK1EpFlJoiPgfW9zCGYtW1M3HKp8F4V4/a
        TgZCgNirg7E5Ugn8v35yJlKkZ3qAr+/FO3wo8hFDyeflEi733Y29WJFN2FGLn6Sbaj55Js
        qzoyrFNZrtquIQkA9bnATjkGjZRc3Pc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-494-OzhTGYyQMlKCuUCYUX8Uug-1; Tue, 26 Jan 2021 08:48:21 -0500
X-MC-Unique: OzhTGYyQMlKCuUCYUX8Uug-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 29476801AA7;
        Tue, 26 Jan 2021 13:48:20 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.204])
        by smtp.corp.redhat.com (Postfix) with ESMTP id A3CB45D9C2;
        Tue, 26 Jan 2021 13:48:17 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH v2 00/15] KVM: x86: Conditional Hyper-V emulation enablement
Date: Tue, 26 Jan 2021 14:48:01 +0100
Message-Id: <20210126134816.1880136-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Changes since v1 [Sean]:
- Add a few cleanup patches ("Rename vcpu_to_hv_vcpu() to to_hv_vcpu()",
  "Rename vcpu_to_synic()/synic_to_vcpu()", ...)
- Drop unused kvm_hv_vapic_assist_page_enabled()
- Stop shadowing global 'current_vcpu' variable in kvm_hv_flush_tlb()/
  kvm_hv_send_ipi()

Original description:

Hyper-V emulation is enabled in KVM unconditionally even for Linux guests.
This is bad at least from security standpoint as it is an extra attack
surface. Ideally, there should be a per-VM capability explicitly enabled by
VMM but currently it is not the case and we can't mandate one without
breaking backwards compatibility. We can, however, check guest visible CPUIDs
and only enable Hyper-V emulation when "Hv#1" interface was exposed in
HYPERV_CPUID_INTERFACE.

Also (and while on it) per-vcpu Hyper-V context ('struct kvm_vcpu_hv') is
currently part of 'struct kvm_vcpu_arch' and thus allocated unconditionally
for each vCPU. The context, however, quite big and accounts for more than
1/4 of 'struct kvm_vcpu_arch' (e.g. 2912/9512 bytes). Switch to allocating
it dynamically. This may come handy if we ever decide to raise KVM_MAX_VCPUS
(and rumor has it some downstream distributions already have more than '288')

Vitaly Kuznetsov (15):
  selftests: kvm: Move kvm_get_supported_hv_cpuid() to common code
  selftests: kvm: Properly set Hyper-V CPUIDs in evmcs_test
  KVM: x86: hyper-v: Drop unused kvm_hv_vapic_assist_page_enabled()
  KVM: x86: hyper-v: Rename vcpu_to_hv_vcpu() to to_hv_vcpu()
  KVM: x86: hyper-v: Rename vcpu_to_synic()/synic_to_vcpu()
  KVM: x86: hyper-v: Rename vcpu_to_stimer()/stimer_to_vcpu()
  KVM: x86: hyper-v: Rename vcpu_to_hv_syndbg() to to_hv_syndbg()
  KVM: x86: hyper-v: Introduce to_kvm_hv() helper
  KVM: x86: hyper-v: Stop shadowing global 'current_vcpu' variable
  KVM: x86: hyper-v: Always use to_hv_vcpu() accessor to get to 'struct
    kvm_vcpu_hv'
  KVM: x86: hyper-v: Prepare to meet unallocated Hyper-V context
  KVM: x86: hyper-v: Allocate 'struct kvm_vcpu_hv' dynamically
  KVM: x86: hyper-v: Make Hyper-V emulation enablement conditional
  KVM: x86: hyper-v: Allocate Hyper-V context lazily
  KVM: x86: hyper-v: Drop hv_vcpu_to_vcpu() helper

 arch/x86/include/asm/kvm_host.h               |   4 +-
 arch/x86/kvm/cpuid.c                          |   2 +
 arch/x86/kvm/hyperv.c                         | 301 +++++++++++-------
 arch/x86/kvm/hyperv.h                         |  54 ++--
 arch/x86/kvm/lapic.c                          |   5 +-
 arch/x86/kvm/lapic.h                          |   7 +-
 arch/x86/kvm/vmx/vmx.c                        |   9 +-
 arch/x86/kvm/x86.c                            |  19 +-
 .../selftests/kvm/include/x86_64/processor.h  |   3 +
 .../selftests/kvm/lib/x86_64/processor.c      |  33 ++
 .../testing/selftests/kvm/x86_64/evmcs_test.c |  39 ++-
 .../selftests/kvm/x86_64/hyperv_cpuid.c       |  31 +-
 12 files changed, 314 insertions(+), 193 deletions(-)
```
#### [PATCH v3 0/4] Handle #GP for SVM execution instructions
##### From: Wei Huang <wei.huang2@amd.com>

```c
From patchwork Tue Jan 26 08:18:27 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wei Huang <wei.huang2@amd.com>
X-Patchwork-Id: 12047503
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 52C76C4361A
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 17:09:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 380D320848
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 17:09:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389353AbhAZRHP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 12:07:15 -0500
Received: from mail-bn8nam11on2050.outbound.protection.outlook.com
 ([40.107.236.50]:25316
        "EHLO NAM11-BN8-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729376AbhAZITm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 03:19:42 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=ZHGRr9a449dUDhA85ISROZxHRmzBabyyoQStxQ1LSkeVfGUaMwEmnUQwCU5tA/6QFMIOp+YG55i45ZhF3vaujTuk6bIPErwdP1djMekBKWqJoYG7t8sNhk1ku5rfN0cOAIpPlkFYe2WYeafn7VxZQcCfldrX5OMkdfsQn/Jn11DKFs1CInAtgqEdu7ldR/HWaGuX++wyl69375JyBN1rsJQvfrhnd4AjJqJZ7p6z7cmUEhKlqDj6OIDoyYgqDt7wFCrK4KQcSPayH9u5vZPRrhNBMMZWhPPg9yQQcJiBvUcDH3k24Mh8iaRjtumIUqFjTyhOVgoPTmW+vl8jAgGIkA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=0+XvnNVxf6+PJbYtD2Ictziv1gP4qGG0LtehOIgkW/s=;
 b=TJnr1GwymtYD/Td+gew4TDYgU/P0ojHN7oB35j29GyYarQ3yITFAIC8AbbbPgqWVU8hjqAe8d0Vgechcci1sW70DRpFpgDvLL4ONSQq1kzQH9CSGTIrnDZw5FoNkKOLBB0VOiZfUY8Tip9c8F2DQKtXgoZwcEbzrMvZg7Aho8v/BEpZ7LpyknthIsZ3B6xsEoLS5OsL8Spk4rWvDuQ398Gi7Jiirum0JQ3uFwDSGFuNbtBICkk2MsVr3lNPkCm30yvppkqivai/pYSybJAHa1GDoLghVl4brs5qBQbcizMSjmVCJT/ExlRKVTm6ru1t+JRhI/oi0ydTiUhd3j/GLOw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=0+XvnNVxf6+PJbYtD2Ictziv1gP4qGG0LtehOIgkW/s=;
 b=1Eblz/m7ZHraS+a8MHIyfS9ydHXg/JphiHSjY1mdAqccPJWmt68mE1fAcSdg9fg0O/NKwgKmVpkcYbZMb5Vx+VAUjoGVNJYkhj09wscfcVjFdnXkNsuRKMa+hko4ZWRwyvXesAM8fYH50yYfw4ctbgUSPZ/ql7WVLUW8mcndtZk=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from CY4PR12MB1494.namprd12.prod.outlook.com (2603:10b6:910:f::22)
 by CY4PR1201MB0214.namprd12.prod.outlook.com (2603:10b6:910:25::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3763.10; Tue, 26 Jan
 2021 08:18:44 +0000
Received: from CY4PR12MB1494.namprd12.prod.outlook.com
 ([fe80::25d2:a078:e7b:a819]) by CY4PR12MB1494.namprd12.prod.outlook.com
 ([fe80::25d2:a078:e7b:a819%11]) with mapi id 15.20.3784.017; Tue, 26 Jan 2021
 08:18:44 +0000
From: Wei Huang <wei.huang2@amd.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, pbonzini@redhat.com,
        vkuznets@redhat.com, mlevitsk@redhat.com, seanjc@google.com,
        joro@8bytes.org, bp@alien8.de, tglx@linutronix.de,
        mingo@redhat.com, x86@kernel.org, jmattson@google.com,
        wanpengli@tencent.com, bsd@redhat.com, dgilbert@redhat.com,
        luto@amacapital.net, wei.huang2@amd.com
Subject: [PATCH v3 0/4] Handle #GP for SVM execution instructions
Date: Tue, 26 Jan 2021 03:18:27 -0500
Message-Id: <20210126081831.570253-1-wei.huang2@amd.com>
X-Mailer: git-send-email 2.27.0
X-Originating-IP: [66.187.233.206]
X-ClientProxiedBy: MN2PR22CA0023.namprd22.prod.outlook.com
 (2603:10b6:208:238::28) To CY4PR12MB1494.namprd12.prod.outlook.com
 (2603:10b6:910:f::22)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from amd-daytona-06.khw1.lab.eng.bos.redhat.com (66.187.233.206) by
 MN2PR22CA0023.namprd22.prod.outlook.com (2603:10b6:208:238::28) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3784.12 via Frontend
 Transport; Tue, 26 Jan 2021 08:18:42 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: c3bda52b-5a0e-4c47-9bd0-08d8c1d2ff41
X-MS-TrafficTypeDiagnostic: CY4PR1201MB0214:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <CY4PR1201MB02142F402596DAE207B15C14CFBC0@CY4PR1201MB0214.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 HLe0WBl/u5H+uVnlgpSWrAwQIu2otTJ94ThGijzmlH/DMEqrO1Z+9TALEaBlecyRYu/Tae7QUPCJltAV+5ne9qhEWvrV4RqEd09pQeqP/MErCKPBeVUtDFqeYeZMQU3y4EhH3PxrCsIh7M/T1KaqlvKwTQWYNxEcyfPLB8Jh2j/KvBt5LfYMygvWpHL5R4dtlAFUuNXAWSg/FkgbBJPFKVdfmCjoUoqQ4JyTi0MSO7u9V4rA3e/zDqNgwkZ6RH/Ma5qQncTB23Du1uNd4GhB2b5LA74oIzM0W9PiOnpAYBXRSYodK8HTr58Nx/8SqS89eFMMutzvWDfIZiAgEC69Eefskcg01Zg3mpaAylh+uM49gQSZeL1Y3QaloQkYznARJ1tIIVrS45slKkJdvHo/CQ==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:CY4PR12MB1494.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(39860400002)(346002)(376002)(396003)(136003)(36756003)(66556008)(6486002)(8676002)(66476007)(66946007)(52116002)(86362001)(5660300002)(6512007)(2906002)(956004)(186003)(26005)(16526019)(478600001)(6666004)(83380400001)(8936002)(4326008)(6916009)(316002)(6506007)(7416002)(1076003)(2616005);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 W7YTHMLZpNo/S9FPPnGD2qR97phjgYrvoIY/2Gza0qQlXra9rQrRuh1zmxZhPmDMLZrCylc2dY5+6jb7iptwiJ4b4G5CgIM5Fypyw50ycpbPw3kE1ghu4Azl0cjjdzctT+15uIzdfBQGDolKxZ25apEyrH7RWH6kv5M5s+DpGa9wdUuaBiJoxt9A/CwCqbhluqQTePYgvEDNp3Vq3N1rldtKwIkrbUK08pFZLEtjLcw7JFNsTzLYXckSWC1qn5XQYCVtDvRAdbHmt7QTiC8N89mt7pXfdIjPb2pO3fF/+hH1Oaq+Rm5nBLRnBdj1vwhDtegmWXUqIPp6AEFZtfSUlke5jZ0OCQxwH0yFnogoJWaSgC9khC+s/bJskGWnUgfoblaaCcoWoFCt2Ap/T7GSMTs7Qs3cWJxv4t1gUCyTX9dUw00OI+2to27k5WYx0ngM7h/NGXYV1NWnMBi0bn+k7qQttLNTo5vF9KMCFPSCxek428BMSSXSFhJJRw2zPMIWTQ18ZnelIqZW3us8vRDRP/3jeEwPLrWTN3cIJS65TVniNy34IyBSWQEJPD9OKUzIgj1Z/NuTL44CuwZIFM29CnEddC7BWvBYyTUeVRakzm4SWZB0AK70iu5PePDeRqD4D8CJPx5C1l523RHAoKCfJ8C1PFIao/BWouNZRFT/dKRavHLkjd003ydfgleqpybnnHK/rj2JS6/YqlFOHERaHURZ2Jac//RU3+JXwiXsWzCELRJbT8RypOyrDAaSj0CWFxQnUxMth9NcjgXHsOidq7VVgf2ErXL5VXd6G9aqjZP8UfymsKa9w+Lv2cTw3W5OSP9dYFLpWTvKYs4O5r07Rl6Zo2Fpd+mqEIebOFDEysKhqfjCtyPEawBJd8b64cwbBYT3NDrgOBltMEeG+4/VCMHUkW11KH7i/7q4fKkkfcJ+9cdxmhqLmKGrXizKBnNLtj9t46Hp0AiIDJGjsvPP2wKKwJQ0cJDgs1k+pkD+cryRLwEKwsKSImjDhE/AhhaE4aGcIybWzu84C+VM5btlcJ+Y7/NXYZ3Z0pq9VpcFe6vAOoc0Zm826K6V/ffieWtk
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 c3bda52b-5a0e-4c47-9bd0-08d8c1d2ff41
X-MS-Exchange-CrossTenant-AuthSource: CY4PR12MB1494.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 26 Jan 2021 08:18:44.4996
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 R80YpHLyvECw/mIuhhm0FzMOJR9buFRq8qVxDdxadJzteVQz3zC6FJflVPqwLKMp
X-MS-Exchange-Transport-CrossTenantHeadersStamped: CY4PR1201MB0214
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While running SVM related instructions (VMRUN/VMSAVE/VMLOAD), some AMD
CPUs check EAX against reserved memory regions (e.g. SMM memory on host)
before checking VMCB's instruction intercept. If EAX falls into such
memory areas, #GP is triggered before #VMEXIT. This causes unexpected #GP
under nested virtualization. To solve this problem, this patchset makes
KVM trap #GP and emulate these SVM instuctions accordingly.

Also newer AMD CPUs will change this behavior by triggering #VMEXIT
before #GP. This change is indicated by CPUID_0x8000000A_EDX[28]. Under
this circumstance, #GP interception is not required. This patchset supports
the new feature.

This patchset has been verified with vmrun_errata_test and vmware_backdoor
tests of kvm_unit_test on the following configs. Also it was verified that
vmware_backdoor can be turned on under nested on nested.
  * Current CPU: nested, nested on nested
  * New CPU with X86_FEATURE_SVME_ADDR_CHK: nested, nested on nested

v2->v3:
  * Change the decode function name to x86_decode_emulated_instruction()
  * Add a new variable, svm_gp_erratum_intercept, to control interception
  * Turn on VM's X86_FEATURE_SVME_ADDR_CHK feature in svm_set_cpu_caps()
  * Fix instruction emulation for vmware_backdoor under nested-on-nested
  * Minor comment fixes

v1->v2:
  * Factor out instruction decode for sharing
  * Re-org gp_interception() handling for both #GP and vmware_backdoor
  * Use kvm_cpu_cap for X86_FEATURE_SVME_ADDR_CHK feature support
  * Add nested on nested support

Thanks,
-Wei

Wei Huang (4):
  KVM: x86: Factor out x86 instruction emulation with decoding
  KVM: SVM: Add emulation support for #GP triggered by SVM instructions
  KVM: SVM: Add support for SVM instruction address check change
  KVM: SVM: Support #GP handling for the case of nested on nested

 arch/x86/include/asm/cpufeatures.h |   1 +
 arch/x86/kvm/svm/svm.c             | 128 +++++++++++++++++++++++++----
 arch/x86/kvm/x86.c                 |  62 ++++++++------
 arch/x86/kvm/x86.h                 |   2 +
 4 files changed, 152 insertions(+), 41 deletions(-)
```
#### [PATCH v6 0/6] Qemu SEV-ES guest support
##### From: Tom Lendacky <thomas.lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Tue Jan 26 17:36:43 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 12048475
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 03B35C4332E
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 22:38:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BDC0C20575
	for <kvm@archiver.kernel.org>; Tue, 26 Jan 2021 22:38:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729287AbhAZWgg (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 26 Jan 2021 17:36:36 -0500
Received: from mail-co1nam11on2053.outbound.protection.outlook.com
 ([40.107.220.53]:3264
        "EHLO NAM11-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2392492AbhAZRiA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 Jan 2021 12:38:00 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Hx6BJSqImoZVpgnZMkBP8a7Kryj7ebJniOKWLQVviaYBBVwnEAF0xpdzLj1Ag2b6SyAXjjQPtu5420O5zREs8Sq5EXOKkMEm04FHD5qn71wDk34dpsFDtOhDlmhk2nlsQuN5ZnAQKJbZzlMPkLZ4305rRxxesBcVwqeXYURdBOxpGjlVuCRrL1A4OKYNo9quFeFXsacX9KIcQh5LlrSkoGKIs2TW+eesWWLzoawdr246FxdD527lggvA/GanxNQlKoEK3znvat5jwIC48uPtbjm+uqj9n4hUOM8wpeM+r2Afa5ZNFrz0XX8lt/q14/YofhGDCf/uIS5JqL4k46kPlQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=L6MOkBBcpubOvgl4hCEAjOyS4NBnDXd58l2abFH7eNs=;
 b=CWjg2oZGgIdBw2S1XqR7mE9uEkGx84BnhPtHQ8WF3BT83GXfvxC6pBvfn9fqF5DU7k2mHm228F7b63tWnHgmQj+M2SK3qjwo0blrfxWWeKxREO2I5vUcd2p4bBjmn11OYMSVYDf6Olfy+7pZtLVO5AE2YC6ZQseA+KPbv1XdsZ42a46FoahRclM1XTIW/EhgHFanIN2/y9onzGavMpV590PQQTfifuMxKGmLt0NKJuAHFwPUhyn8/D9HYcCZ+okjlczAOA8as3TugA/k3R9SaJOgvemCVke6E4EJkfa7oVAPbzIo3RuWFH9lhrO4RNg3HHFB+uWVcT1zvvMaX1bpdg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=L6MOkBBcpubOvgl4hCEAjOyS4NBnDXd58l2abFH7eNs=;
 b=eedsVTutuTES6NJZ7f2NvBZ/nJE8B3QIR26XYwrSxK8ughLX3bxVHH7V29vVZWl0dVT/kiX3UK5d9+x46d0yhtjF2BbYROsQHRUzBWOvDl5tdSfWO1mQ3qzBpsumyY3+RnIA6r7ppeEczF6QkuE9zDEds+YBrSzWbf/mtyjsXUU=
Authentication-Results: nongnu.org; dkim=none (message not signed)
 header.d=none;nongnu.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4153.namprd12.prod.outlook.com (2603:10b6:5:212::22) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3784.13; Tue, 26 Jan 2021 17:37:05 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::cc15:4b1f:9f84:6914]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::cc15:4b1f:9f84:6914%4]) with mapi id 15.20.3784.019; Tue, 26 Jan 2021
 17:37:04 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: qemu-devel@nongnu.org, kvm@vger.kernel.org
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Dr. David Alan Gilbert" <dgilbert@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>,
        Richard Henderson <rth@twiddle.net>,
        Connor Kuehl <ckuehl@redhat.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>,
        Aurelien Jarno <aurelien@aurel32.net>,
        David Gibson <david@gibson.dropbear.id.au>,
        David Hildenbrand <david@redhat.com>,
        Jiaxun Yang <jiaxun.yang@flygoat.com>,
        Peter Maydell <peter.maydell@linaro.org>,
        Richard Henderson <richard.henderson@linaro.org>
Subject: [PATCH v6 0/6] Qemu SEV-ES guest support
Date: Tue, 26 Jan 2021 11:36:43 -0600
Message-Id: <cover.1611682609.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.30.0
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN6PR04CA0102.namprd04.prod.outlook.com
 (2603:10b6:805:f2::43) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SN6PR04CA0102.namprd04.prod.outlook.com (2603:10b6:805:f2::43) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3805.16 via Frontend
 Transport; Tue, 26 Jan 2021 17:37:03 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 56da634a-aa8a-4cc9-01a9-08d8c220ff11
X-MS-TrafficTypeDiagnostic: DM6PR12MB4153:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB4153244D31AF13197756FE1BECBC9@DM6PR12MB4153.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:4941;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 1Om57hovJUlyALvCSA/3I5q9cel4P3AkBLE3vo9z5daIYv6AWzcGmOdNHrT9IPg5UKv/iWvmVxwrznjvKEZOpmuUuz33ROFV4p6amjHowD3iRygq/GAdRky+bkKJhbSPXcYxYSMhO5OPGAVgMtkhgRKzGSoqm7gm9tkt2RjRyviExYThH0BRmve9hN1fpreHupRZs4yW7/HO+DxMCfy1xG3CRlYUGruEgjX9v6nNOyHcpJHgKrwXT8UgHkxkMQTRJw8zr5NLajbTm4rJHxTuDesxOrkedel0hkr+etVttbr3PvY6bCJ8Itv7StbZ/ib5yJkkRPoNGa/oFdpz16dU1bDhpXbN8wx+qcDyJv9DJq5uu9wUBWFPRYXiGxqEUwjxpH0Bd1vbjomhBXSrvvNnSjeUcOEeoDJQh05pWTZdVbdFw4PDPTJCAXQG3RzvmLilZp4MRYls2Oo35XfEXEezsg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(366004)(39860400002)(376002)(396003)(346002)(136003)(8676002)(7696005)(52116002)(478600001)(6666004)(966005)(7416002)(4326008)(2906002)(66476007)(316002)(54906003)(5660300002)(26005)(2616005)(956004)(86362001)(83380400001)(36756003)(186003)(16526019)(6486002)(66946007)(8936002)(66556008);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 JCvcO06qKEUTTohkc8qMkLa/Tg5XV7sE5cVR6+dYjxjU/qJSaVo6yJqmSCFrxS1mCq6OnQGPzIZynZOMNDFgydwPsTHfL+lYpgD6hiXjyisT6X4s0piHpb0qZo4hNfh05oGJn6+vQ7XNWdpPnchnsoYkYYJNnWG/VN6XnbLQe+nY/6aLocgvPr6nltwMu0YV5hlYoZIV79dk5tNLOFoG5H4P0OF3gMP7AiCH+0MF3ebIgIlTfSgHwtc7RoDE2KVsM5f5FMjPNqFMpkPz0jCkUnMO/xvIT9mD53U90UtseCApMEsb2p/3f5haf2FQbCXOrKdyvwgCYKPqHjfJO/1t765J8pNJ4iT4ebl1IhNd8Knivh9Fupg40ibKTlC7Fw9jxamKNulZsyy/0nEOlsC/KtM/3DlaAIj52qnSNmTZ283ndQztC/B/BiGIJobskYQZrXlyzC350I/bqCl7LjreG4u6bVA2l1XhQ1m6jW8X50vkoOI7JT6PG56Xejg6PJbc5u354/u19Aa8wXhoS1zLb7s4Tr3H13E3XDIIFmwOGL1VfDpL8PD8vIGolBwO1r4rz6lcLKQ0MP8JDMeY5kF4uo0SBuutwC0JQ0xbP2+fIgXPEtTAvcMLJ+N8WnR0vdb2kGplbx5DvXWDuCChsjS77RHMYXaYF676Asm3v48RtVTjlDaeIEpS6+iWi81ese31EAQF5DTsbJcVvRf0iepckVkdgmjFdiaLqlCxmg3FY7Ezj88YM7oxxD/Gg9WhYnRzNmXsXjlqDyTJqgtgvdYA4Y8lBXzesxS1r6I6dKQsA+WeqQhnmBec9/y5exJvBsR1W3LYeyQ/mpKpezeGSn69oiNfsht/iWoG+nesEJZOz10A4paY6518UyE9RdoyNR+pyhes/NUIdwbkJAeMRfhD2cdLIIk1oD1EEFH494etQPMyQ+br4TZx91wdylw7xvyTkvy92XF1gSS9veTepXEyHw75PamS7DIBBb5ac9/jbNy8vR1FF2b/C+oX8+vuWJDScUnLLtXto7Agw0E5T0ptpHJCD323sRHBtrojhGy/4QLKDrR797o924tnKEgkgUoh
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 56da634a-aa8a-4cc9-01a9-08d8c220ff11
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 26 Jan 2021 17:37:04.8321
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 83DCcZb4IzaeJ2nlNqWnMRMIUSqVzjxHArzQsgG3LDipNakIr6pid4i1DsS5VnXfSE3EUgJg4U6ZS6qLaTgViA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4153
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This patch series provides support for launching an SEV-ES guest.

Secure Encrypted Virtualization - Encrypted State (SEV-ES) expands on the
SEV support to protect the guest register state from the hypervisor. See
"AMD64 Architecture Programmer's Manual Volume 2: System Programming",
section "15.35 Encrypted State (SEV-ES)" [1].

In order to allow a hypervisor to perform functions on behalf of a guest,
there is architectural support for notifying a guest's operating system
when certain types of VMEXITs are about to occur. This allows the guest to
selectively share information with the hypervisor to satisfy the requested
function. The notification is performed using a new exception, the VMM
Communication exception (#VC). The information is shared through the
Guest-Hypervisor Communication Block (GHCB) using the VMGEXIT instruction.
The GHCB format and the protocol for using it is documented in "SEV-ES
Guest-Hypervisor Communication Block Standardization" [2].

The main areas of the Qemu code that are updated to support SEV-ES are
around the SEV guest launch process and AP booting in order to support
booting multiple vCPUs.

There are no new command line switches required. Instead, the desire for
SEV-ES is presented using the SEV policy object. Bit 2 of the SEV policy
object indicates that SEV-ES is required.

The SEV launch process is updated in two ways. The first is that a the
KVM_SEV_ES_INIT ioctl is used to initialize the guest instead of the
standard KVM_SEV_INIT ioctl. The second is that before the SEV launch
measurement is calculated, the LAUNCH_UPDATE_VMSA SEV API is invoked for
each vCPU that Qemu has created. Once the LAUNCH_UPDATE_VMSA API has been
invoked, no direct changes to the guest register state can be made.

AP booting poses some interesting challenges. The INIT-SIPI-SIPI sequence
is typically used to boot the APs. However, the hypervisor is not allowed
to update the guest registers. For the APs, the reset vector must be known
in advance. An OVMF method to provide a known reset vector address exists
by providing an SEV information block, identified by UUID, near the end of
the firmware [3]. OVMF will program the jump to the actual reset vector in
this area of memory. Since the memory location is known in advance, an AP
can be created with the known reset vector address as its starting CS:IP.
The GHCB document [2] talks about how SMP booting under SEV-ES is
performed. SEV-ES also requires the use of the in-kernel irqchip support
in order to minimize the changes required to Qemu to support AP booting.

[1] https://www.amd.com/system/files/TechDocs/24593.pdf
[2] https://developer.amd.com/wp-content/resources/56421.pdf
[3] 30937f2f98c4 ("OvmfPkg: Use the SEV-ES work area for the SEV-ES AP reset vector")
    https://github.com/tianocore/edk2/commit/30937f2f98c42496f2f143fe8374ae7f7e684847

Cc: Aleksandar Rikalo <aleksandar.rikalo@syrmia.com>
Cc: Aurelien Jarno <aurelien@aurel32.net>
Cc: David Gibson <david@gibson.dropbear.id.au>
Cc: David Hildenbrand <david@redhat.com>
Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Jiaxun Yang <jiaxun.yang@flygoat.com>
Cc: Marcel Apfelbaum <marcel.apfelbaum@gmail.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Maydell <peter.maydell@linaro.org>
Cc: Richard Henderson <richard.henderson@linaro.org>
---

These patches are based on commit:
9cd69f1a27 ("Merge remote-tracking branch 'remotes/stefanberger/tags/pull-tpm-2021-01-25-1' into staging")

Additionally, these patches pre-req the following patch series that has
not yet been accepted into the Qemu tree:

[PATCH v2 0/2] sev: enable secret injection to a self described area in OVMF
  https://lore.kernel.org/qemu-devel/20201214154429.11023-1-jejb@linux.ibm.com/

A version of the tree can be found at:
https://github.com/AMDESE/qemu/tree/sev-es-v14

Changes since v5:
- Rework the reset prevention patch to not issue the error message if the
  --no-reboot option has been specified for SEV-ES guests.

Changes since v4:
- Add support for an updated Firmware GUID table implementation, that
  is now present in OVMF SEV-ES firmware, when searching for the reset
  vector information. The code will check for the new implementation
  first, followed by the original implementation to maintain backward
  compatibility.

Changes since v3:
- Use the QemuUUID structure for GUID definitions
- Use SEV-ES policy bit definition from target/i386/sev_i386.h
- Update SMM support to a per-VM check in order to check SMM capability
  at the VM level since SEV-ES guests don't currently support SMM
- Make the CPU resettable check an arch-specific check

Changes since v2:
- Add in-kernel irqchip requirement for SEV-ES guests

Changes since v1:
- Fixed checkpatch.pl errors/warnings

Tom Lendacky (6):
  sev/i386: Add initial support for SEV-ES
  sev/i386: Require in-kernel irqchip support for SEV-ES guests
  sev/i386: Allow AP booting under SEV-ES
  sev/i386: Don't allow a system reset under an SEV-ES guest
  kvm/i386: Use a per-VM check for SMM capability
  sev/i386: Enable an SEV-ES guest based on SEV policy

 accel/kvm/kvm-all.c       |  69 +++++++++++++++++++++
 accel/stubs/kvm-stub.c    |   5 ++
 hw/i386/pc_sysfw.c        |  10 ++-
 include/sysemu/cpus.h     |   2 +
 include/sysemu/hw_accel.h |   5 ++
 include/sysemu/kvm.h      |  26 ++++++++
 include/sysemu/sev.h      |   3 +
 softmmu/cpus.c            |   5 ++
 softmmu/runstate.c        |   3 +
 target/arm/kvm.c          |   5 ++
 target/i386/cpu.c         |   1 +
 target/i386/kvm/kvm.c     |  10 ++-
 target/i386/sev-stub.c    |   6 ++
 target/i386/sev.c         | 124 +++++++++++++++++++++++++++++++++++++-
 target/i386/sev_i386.h    |   1 +
 target/mips/kvm.c         |   5 ++
 target/ppc/kvm.c          |   5 ++
 target/s390x/kvm.c        |   5 ++
 18 files changed, 286 insertions(+), 4 deletions(-)
```
