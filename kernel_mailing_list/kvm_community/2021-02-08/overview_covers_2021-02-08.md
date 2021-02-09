

#### [RFC PATCH 0/2] Add a test for kvm page table code
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Mon Feb  8 09:08:39 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12074493
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 21F63C43381
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 09:12:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E7A8964E85
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 09:12:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230249AbhBHJMP (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 04:12:15 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:12487 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231255AbhBHJJt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 04:09:49 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4DZ0Xf3KJhzjL2G;
        Mon,  8 Feb 2021 17:07:30 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.498.0; Mon, 8 Feb 2021 17:08:43 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: <kvm@vger.kernel.org>, <linux-kselftest@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: Paolo Bonzini <pbonzini@redhat.com>, Shuah Khan <shuah@kernel.org>,
        "Andrew Jones" <drjones@redhat.com>, Marc Zyngier <maz@kernel.org>,
        Ben Gardon <bgardon@google.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Aaron Lewis <aaronlewis@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH 0/2] Add a test for kvm page table code
Date: Mon, 8 Feb 2021 17:08:39 +0800
Message-ID: <20210208090841.333724-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This test is added to serve as a performance tester and a bug reproducer
for kvm page table code (GPA->HPA mappings), it gives guidance for the
people trying to make some improvement for kvm.

The following explains what we can exactly do through this test.
And a RFC is sent for comments, thanks.

The function guest_code() is designed to cover conditions where a single vcpu
or multiple vcpus access guest pages within the same memory range, in three
VM stages(before dirty-logging, during dirty-logging, after dirty-logging).
Besides, the backing source memory type(ANONYMOUS/THP/HUGETLB) of the tested
memory region can be specified by users, which means normal page mappings or
block mappings can be chosen by users to be created in the test.

If use of ANONYMOUS memory is specified, kvm will create page mappings for the
tested memory region before dirty-logging, and update attributes of the page
mappings from RO to RW during dirty-logging. If use of THP/HUGETLB memory is
specified, kvm will create block mappings for the tested memory region before
dirty-logging, and split the blcok mappings into page mappings during
dirty-logging, and coalesce the page mappings back into block mappings after
dirty-logging is stopped.

So in summary, as a performance tester, this test can present the performance
of kvm creating/updating normal page mappings, or the performance of kvm
creating/splitting/recovering block mappings, through execution time.

When we need to coalesce the page mappings back to block mappings after dirty
logging is stopped, we have to firstly invalidate *all* the TLB entries for the
page mappings right before installation of the block entry, because a TLB conflict
abort error could occur if we can't invalidate the TLB entries fully. We have
hit this TLB conflict twice on aarch64 software implementation and fixed it.
As this test can imulate process from dirty-logging enabled to dirty-logging
stopped of a VM with block mappings, so it can also reproduce this TLB conflict
abort due to inadequate TLB invalidation when coalescing tables.

Links about the TLB conflict abort:
https://lore.kernel.org/lkml/20201201201034.116760-3-wangyanan55@huawei.com/
---

Here are some test examples of this test:
platform: HiSilicon Kunpeng920 (aarch64, FWB not supported)
host kernel: Linux mainline

(1) Based on v5.11-rc6

cmdline: ./kvm_page_table_test -m 4 -t 0 -g 4K -s 1G -v 1
	   (1 vcpu, 1G memory, page mappings(granule 4K))
KVM_CREATE_MAPPINGS: 0.8196s 0.8260s 0.8258s 0.8169s 0.8190s
KVM_UPDATE_MAPPINGS: 1.1930s 1.1949s 1.1940s 1.1934s 1.1946s

cmdline: ./kvm_page_table_test -m 4 -t 0 -g 4K -s 1G -v 20
	   (20 vcpus, 1G memory, page mappings(granule 4K))
KVM_CREATE_MAPPINGS: 23.4028s 23.8015s 23.6702s 23.9437s 22.1646s
KVM_UPDATE_MAPPINGS: 16.9550s 16.4734s 16.8300s 16.9621s 16.9402s

cmdline: ./kvm_page_table_test -m 4 -t 2 -g 1G -s 20G -v 1
	   (1 vcpu, 20G memory, block mappings(granule 1G))
KVM_CREATE_MAPPINGS: 3.7040s 3.7053s 3.7047s 3.7061s 3.7068s
KVM_ADJUST_MAPPINGS: 2.8264s 2.8266s 2.8272s 2.8259s 2.8283s

cmdline: ./kvm_page_table_test -m 4 -t 2 -g 1G -s 20G -v 20
	   (20 vcpus, 20G memory, block mappings(granule 1G))
KVM_CREATE_MAPPINGS: 52.8338s 52.8327s 52.8336s 52.8255s 52.8303s
KVM_ADJUST_MAPPINGS: 52.0466s 52.0473s 52.0550s 52.0518s 52.0467s

(2) I have post a patch series to improve efficiency of stage2 page table code,
    so test the performance changes.

cmdline: ./kvm_page_table_test -m 4 -t 2 -g 1G -s 20G -v 20
 	   (20 vcpus, 20G memory, block mappings(granule 1G))
Before patch: KVM_CREATE_MAPPINGS: 52.8338s 52.8327s 52.8336s 52.8255s 52.8303s
After  patch: KVM_CREATE_MAPPINGS:  3.7022s  3.7031s  3.7028s  3.7012s  3.7024s

Before patch: KVM_ADJUST_MAPPINGS: 52.0466s 52.0473s 52.0550s 52.0518s 52.0467s
After  patch: KVM_ADJUST_MAPPINGS:  0.3008s  0.3004s  0.2974s  0.2917s  0.2900s

cmdline: ./kvm_page_table_test -m 4 -t 2 -g 1G -s 20G -v 40
	   (40 vcpus, 20G memory, block mappings(granule 1G))
Before patch: KVM_CREATE_MAPPINGS: 104.560s 104.556s 104.554s 104.556s 104.550s
After  patch: KVM_CREATE_MAPPINGS:  3.7011s  3.7103s  3.7005s  3.7024s  3.7106s

Before patch: KVM_ADJUST_MAPPINGS: 103.931s 103.936s 103.927s 103.942s 103.927s
After  patch: KVM_ADJUST_MAPPINGS:  0.3541s  0.3694s  0.3656s  0.3693s  0.3687s

---

Yanan Wang (2):
  KVM: selftests: Add a macro to get string of vm_mem_backing_src_type
  KVM: selftests: Add a test for kvm page table code

 tools/testing/selftests/kvm/Makefile          |   3 +
 .../testing/selftests/kvm/include/kvm_util.h  |   3 +
 .../selftests/kvm/kvm_page_table_test.c       | 518 ++++++++++++++++++
 tools/testing/selftests/kvm/lib/kvm_util.c    |   8 +
 4 files changed, 532 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/kvm_page_table_test.c
```
#### [RFC PATCH v4 00/26] KVM SGX virtualization support
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Mon Feb  8 10:53:40 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12074979
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 809B9C433E0
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 10:57:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2150964E7D
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 10:57:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232708AbhBHK5F (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 05:57:05 -0500
Received: from mga11.intel.com ([192.55.52.93]:21330 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232539AbhBHKzA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 05:55:00 -0500
IronPort-SDR: 
 FYVZfdAcDtYwpIm0fwOzpp2YVOgKQBeJ8bCuuiO1Q7iX7Pz3YBDitb3d2XRS+PKBVBaqAaEwdS
 gkawK97U6AcQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9888"; a="178183999"
X-IronPort-AV: E=Sophos;i="5.81,161,1610438400";
   d="scan'208";a="178183999"
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Feb 2021 02:54:09 -0800
IronPort-SDR: 
 PXQvJK6Gw/eBbQDGUkKYiieFR7tl0tTQFQaSnzcgcQrq/bylTGKK0UM+uczX1UqTe+4tdhLkhZ
 EkqsZFwWGMeA==
X-IronPort-AV: E=Sophos;i="5.81,161,1610438400";
   d="scan'208";a="374450925"
Received: from jaeminha-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.251.11.62])
  by orsmga002-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Feb 2021 02:54:04 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        jethro@fortanix.com, b.thiel@posteo.de, jmattson@google.com,
        joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        corbet@lwn.net
Subject: [RFC PATCH v4 00/26] KVM SGX virtualization support
Date: Mon,  8 Feb 2021 23:53:40 +1300
Message-Id: <cover.1612777752.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

--- Disclaimer ---

These patches were originally written by Sean Christopherson while at Intel.
Now that Sean has left Intel, I (Kai) have taken over getting them upstream.
This series needs more review before it can be merged.  It is being posted
publicly and under RFC so Sean and others can review it. X86 Maintainers are
safe ignoring it for now.

------------------

Hi all,

This series adds KVM SGX virtualization support. The first 14 patches starting
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

v3->v4:

 - Removed Jarkko's first patch, which removes WARN() against EPC page's
   SGX_EPC_PAGE_RECLAIMER_TRACKED flag. Dave and Sean were not convinced, and
   Sean "tripped more than once in the past during one of the many rebases of
   the virtual EPC and EPC cgroup branches".
 - Switched the patch to introduce SGX1/SGX2 feature bits, and the patch to move
   SGX_LC to cpuid_deps[] table, per Jarkko. Now SGX_LC patch can be applied to
   existing upstream code directly, if needed.
 - Fixed two problems in one KVM patch (trap ECREATE) after review from Rick and
   Sean.
 - Some other minor changes, i.e. update new file's copyright to 2021.

Hi Dave, Sean, Paolo, Rick, and others,
 
 Btw, in last review, we identified that malicious guest can cause KVM to access
 EPC, which will trigger "page abort", which drops on write, and returns all
 ones on read. If I understand correctly, we agreed that a better option is to
 make memremap() deny EPC. However so far this series doesn't contain this work,
 since looks more discussion is required, and this work can be done
 independently from KVM SGX series.

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

Jarkko Sakkinen (1):
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
 arch/x86/kernel/cpu/feat_ctl.c                |  69 ++-
 arch/x86/kernel/cpu/scattered.c               |   2 +
 arch/x86/kernel/cpu/sgx/Makefile              |   1 +
 arch/x86/kernel/cpu/sgx/driver.c              |  17 -
 arch/x86/kernel/cpu/sgx/encl.c                |  22 +-
 arch/x86/kernel/cpu/sgx/encls.h               |  30 +-
 arch/x86/kernel/cpu/sgx/ioctl.c               |  23 +-
 arch/x86/kernel/cpu/sgx/main.c                |  93 +++-
 arch/x86/kernel/cpu/sgx/sgx.h                 |  13 +-
 arch/x86/kernel/cpu/sgx/virt.c                | 353 +++++++++++++
 arch/x86/kvm/Makefile                         |   2 +
 arch/x86/kvm/cpuid.c                          |  89 +++-
 arch/x86/kvm/cpuid.h                          |  50 +-
 arch/x86/kvm/vmx/nested.c                     |  70 ++-
 arch/x86/kvm/vmx/nested.h                     |   5 +
 arch/x86/kvm/vmx/sgx.c                        | 466 ++++++++++++++++++
 arch/x86/kvm/vmx/sgx.h                        |  34 ++
 arch/x86/kvm/vmx/vmcs12.c                     |   1 +
 arch/x86/kvm/vmx/vmcs12.h                     |   4 +-
 arch/x86/kvm/vmx/vmx.c                        | 171 +++++--
 arch/x86/kvm/vmx/vmx.h                        |  27 +-
 arch/x86/kvm/x86.c                            |  24 +
 include/uapi/linux/kvm.h                      |   1 +
 tools/testing/selftests/sgx/defines.h         |   2 +-
 33 files changed, 1499 insertions(+), 156 deletions(-)
 create mode 100644 arch/x86/include/asm/sgx.h
 rename arch/x86/{kernel/cpu/sgx/arch.h => include/asm/sgx_arch.h} (96%)
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.c
 create mode 100644 arch/x86/kvm/vmx/sgx.c
 create mode 100644 arch/x86/kvm/vmx/sgx.h
```
#### [RFC PATCH 0/4] KVM: arm64: Improve efficiency of stage2 page table
##### From: Yanan Wang <wangyanan55@huawei.com>

```c
From patchwork Mon Feb  8 11:22:46 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yanan Wang <wangyanan55@huawei.com>
X-Patchwork-Id: 12075143
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 63536C433E0
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 11:27:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0C39F64E6E
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 11:27:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233204AbhBHL05 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 06:26:57 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:12898 "EHLO
        szxga06-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233039AbhBHLXn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 06:23:43 -0500
Received: from DGGEMS411-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga06-in.huawei.com (SkyGuard) with ESMTP id 4DZ3Wk0320zjK2N;
        Mon,  8 Feb 2021 19:21:54 +0800 (CST)
Received: from DESKTOP-TMVL5KK.china.huawei.com (10.174.187.128) by
 DGGEMS411-HUB.china.huawei.com (10.3.19.211) with Microsoft SMTP Server id
 14.3.498.0; Mon, 8 Feb 2021 19:22:52 +0800
From: Yanan Wang <wangyanan55@huawei.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        "Catalin Marinas" <catalin.marinas@arm.com>,
        James Morse <james.morse@arm.com>,
        "Julien Thierry" <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Gavin Shan <gshan@redhat.com>,
        Quentin Perret <qperret@google.com>,
        <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: <wanghaibin.wang@huawei.com>, <zhukeqian1@huawei.com>,
        <yuzenghui@huawei.com>, Yanan Wang <wangyanan55@huawei.com>
Subject: [RFC PATCH 0/4] KVM: arm64: Improve efficiency of stage2 page table
Date: Mon, 8 Feb 2021 19:22:46 +0800
Message-ID: <20210208112250.163568-1-wangyanan55@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.128]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This series makes some efficiency improvement of stage2 page table code,
and there are some test results to present the performance changes, which
were tested by a kvm selftest [1] that I have post:
[1] https://lore.kernel.org/lkml/20210208090841.333724-1-wangyanan55@huawei.com/ 

About patch 1:
We currently uniformly clean dcache in user_mem_abort() before calling the
fault handlers, if we take a translation fault and the pfn is cacheable.
But if there are concurrent translation faults on the same page or block,
clean of dcache for the first time is necessary while the others are not.

By moving clean of dcache to the map handler, we can easily identify the
conditions where CMOs are really needed and avoid the unnecessary ones.
As it's a time consuming process to perform CMOs especially when flushing
a block range, so this solution reduces much load of kvm and improve the
efficiency of creating mappings.

Test results:
(1) when 20 vCPUs concurrently access 20G ram (all 1G hugepages):
KVM create block mappings time: 52.83s -> 3.70s
KVM recover block mappings time(after dirty-logging): 52.0s -> 2.87s

(2) when 40 vCPUs concurrently access 20G ram (all 1G hugepages):
KVM creating block mappings time: 104.56s -> 3.70s
KVM recover block mappings time(after dirty-logging): 103.93s -> 2.96s

About patch 2, 3:
When KVM needs to coalesce the normal page mappings into a block mapping,
we currently invalidate the old table entry first followed by invalidation
of TLB, then unmap the page mappings, and install the block entry at last.

It will cost a lot of time to unmap the numerous page mappings, which means
the table entry will be left invalid for a long time before installation of
the block entry, and this will cause many spurious translation faults.

So let's quickly install the block entry at first to ensure uninterrupted
memory access of the other vCPUs, and then unmap the page mappings after
installation. This will reduce most of the time when the table entry is
invalid, and avoid most of the unnecessary translation faults.

Test results based on patch 1:
(1) when 20 vCPUs concurrently access 20G ram (all 1G hugepages):
KVM recover block mappings time(after dirty-logging): 2.87s -> 0.30s

(2) when 40 vCPUs concurrently access 20G ram (all 1G hugepages):
KVM recover block mappings time(after dirty-logging): 2.96s -> 0.35s

So combined with patch 1, it makes a big difference of KVM creating mappings
and recovering block mappings with not much code change.

About patch 4:
A new method to distinguish cases of memcache allocations is introduced.
By comparing fault_granule and vma_pagesize, cases that require allocations
from memcache and cases that don't can be distinguished completely.
---

Details of test results
platform: HiSilicon Kunpeng920 (FWB not supported)
host kernel: Linux mainline (v5.11-rc6)

(1) performance change of patch 1
cmdline: ./kvm_page_table_test -m 4 -t 2 -g 1G -s 20G -v 20
	   (20 vcpus, 20G memory, block mappings(granule 1G))
Before patch: KVM_CREATE_MAPPINGS: 52.8338s 52.8327s 52.8336s 52.8255s 52.8303s
After  patch: KVM_CREATE_MAPPINGS:  3.7022s  3.7031s  3.7028s  3.7012s  3.7024s

Before patch: KVM_ADJUST_MAPPINGS: 52.0466s 52.0473s 52.0550s 52.0518s 52.0467s
After  patch: KVM_ADJUST_MAPPINGS:  2.8787s  2.8781s  2.8785s  2.8742s  2.8759s

cmdline: ./kvm_page_table_test -m 4 -t 2 -g 1G -s 20G -v 40
	   (40 vcpus, 20G memory, block mappings(granule 1G))
Before patch: KVM_CREATE_MAPPINGS: 104.560s 104.556s 104.554s 104.556s 104.550s
After  patch: KVM_CREATE_MAPPINGS:  3.7011s  3.7103s  3.7005s  3.7024s  3.7106s

Before patch: KVM_ADJUST_MAPPINGS: 103.931s 103.936s 103.927s 103.942s 103.927s
After  patch: KVM_ADJUST_MAPPINGS:  2.9621s  2.9648s  2.9474s  2.9587s  2.9603s

(2) performance change of patch 2, 3(based on patch 1)
cmdline: ./kvm_page_table_test -m 4 -t 2 -g 1G -s 20G -v 1
	   (1 vcpu, 20G memory, block mappings(granule 1G))
Before patch: KVM_ADJUST_MAPPINGS: 2.8241s 2.8234s 2.8245s 2.8230s 2.8652s
After  patch: KVM_ADJUST_MAPPINGS: 0.2444s 0.2442s 0.2423s 0.2441s 0.2429s

cmdline: ./kvm_page_table_test -m 4 -t 2 -g 1G -s 20G -v 20
	   (20 vcpus, 20G memory, block mappings(granule 1G))
Before patch: KVM_ADJUST_MAPPINGS: 2.8787s 2.8781s 2.8785s 2.8742s 2.8759s
After  patch: KVM_ADJUST_MAPPINGS: 0.3008s 0.3004s 0.2974s 0.2917s 0.2900s

cmdline: ./kvm_page_table_test -m 4 -t 2 -g 1G -s 20G -v 40
	   (40 vcpus, 20G memory, block mappings(granule 1G))
Before patch: KVM_ADJUST_MAPPINGS: 2.9621s 2.9648s 2.9474s 2.9587s 2.9603s
After  patch: KVM_ADJUST_MAPPINGS: 0.3541s 0.3694s 0.3656s 0.3693s 0.3687s

---

Yanan Wang (4):
  KVM: arm64: Move the clean of dcache to the map handler
  KVM: arm64: Add an independent API for coalescing tables
  KVM: arm64: Install the block entry before unmapping the page mappings
  KVM: arm64: Distinguish cases of memcache allocations completely

 arch/arm64/include/asm/kvm_mmu.h | 16 -------
 arch/arm64/kvm/hyp/pgtable.c     | 82 +++++++++++++++++++++-----------
 arch/arm64/kvm/mmu.c             | 39 ++++++---------
 3 files changed, 69 insertions(+), 68 deletions(-)
```
#### [PATCH v18 0/7] KVM: arm64: Add host/guest KVM-PTP support
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Mon Feb  8 13:40:22 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 12075389
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 22B2CC433E0
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 13:41:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CEA1764E3F
	for <kvm@archiver.kernel.org>; Mon,  8 Feb 2021 13:41:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230295AbhBHNlW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Feb 2021 08:41:22 -0500
Received: from mail.kernel.org ([198.145.29.99]:59002 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229611AbhBHNlQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Feb 2021 08:41:16 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 7B8746186A;
        Mon,  8 Feb 2021 13:40:35 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1l96mH-00Cn0C-9k; Mon, 08 Feb 2021 13:40:33 +0000
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
Subject: [PATCH v18 0/7] KVM: arm64: Add host/guest KVM-PTP support
Date: Mon,  8 Feb 2021 13:40:22 +0000
Message-Id: <20210208134029.3269384-1-maz@kernel.org>
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

 Documentation/virt/kvm/api.rst              |  9 ++
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
 25 files changed, 442 insertions(+), 78 deletions(-)
 create mode 100644 Documentation/virt/kvm/arm/ptp_kvm.rst
 create mode 100644 drivers/firmware/smccc/kvm_guest.c
 create mode 100644 drivers/ptp/ptp_kvm_arm.c
 rename drivers/ptp/{ptp_kvm.c => ptp_kvm_common.c} (60%)
 create mode 100644 drivers/ptp/ptp_kvm_x86.c
 create mode 100644 include/linux/clocksource_ids.h
 create mode 100644 include/linux/ptp_kvm.h
```
