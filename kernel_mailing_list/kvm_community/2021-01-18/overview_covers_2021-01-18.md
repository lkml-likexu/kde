

#### [RFC PATCH v2 00/26] KVM SGX virtualization support
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Mon Jan 18 03:26:21 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12026353
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AC87FC433E0
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 03:27:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 736E6224B1
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 03:27:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731556AbhARD1g (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sun, 17 Jan 2021 22:27:36 -0500
Received: from mga11.intel.com ([192.55.52.93]:56804 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728602AbhARD1e (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 Jan 2021 22:27:34 -0500
IronPort-SDR: 
 X+FqpUC13dd/F7JBK2Vzv9orRY0eFWBihad8jrJZmnHEK58FySUZj/0RqippuFmoc6yzAqCvvv
 Zr3Hm3Yg96Pg==
X-IronPort-AV: E=McAfee;i="6000,8403,9867"; a="175248934"
X-IronPort-AV: E=Sophos;i="5.79,355,1602572400";
   d="scan'208";a="175248934"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Jan 2021 19:26:52 -0800
IronPort-SDR: 
 0qJW3k5cH5p/4UDmilisfzslTEhgrDpmGmAkvhw618cOMr4VApzPgLyJjDxs+/MlxEVZNnslU7
 9KAgW5YvyjQA==
X-IronPort-AV: E=Sophos;i="5.79,355,1602572400";
   d="scan'208";a="573150681"
Received: from amrahman-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.252.142.253])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 17 Jan 2021 19:26:47 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, haitao.huang@intel.com, pbonzini@redhat.com,
        bp@alien8.de, tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        jethro@fortanix.com, b.thiel@posteo.de, jmattson@google.com,
        joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        corbet@lwn.net
Subject: [RFC PATCH v2 00/26] KVM SGX virtualization support
Date: Mon, 18 Jan 2021 16:26:21 +1300
Message-Id: <cover.1610935432.git.kai.huang@intel.com>
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

This series adds KVM SGX virtualization support. The first 14 patches starting
with x86/sgx or x86/cpu.. are necessary changes to x86 and SGX core/driver to
support KVM SGX virtualization, while the rest are patches to KVM subsystem.

Please help to review this series. Also I'd like to hear what is the proper
way to merge this series, since it contains change to both x86/SGX and KVM
subsystem. Any feedback is highly appreciated. And please let me know if I
forgot to CC anyone, or anyone wants to be removed from CC. Thanks in advance!

This series is based against upstream v5.11-rc3. You can also get the code from
upstream branch of kvm-sgx repo on github:

        https://github.com/intel/kvm-sgx.git upstream

It also requires Qemu changes to create VM with SGX support. You can find Qemu
repo here:

	https://github.com/intel/qemu-sgx.git next

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

KVM part patches are not changed comparing to v1 (except changes due to
X86_FEATURE_SGX1/2 patches). For changes to each x86 patch, please see changelog
in each indudival patch. If no changelog, then no change was made to it.

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

This series introduces a new misc device: /dev/sgx_virt_epc.  This device
allows the host to map *uninitialized* enclave memory into userspace, which
can then be passed into a guest.

While it might be *possible* to start a host-side enclave with /dev/sgx_enclave
and pass its memory into a guest, it would be wasteful and convoluted.

Implement the *raw* EPC allocation in the x86 core-SGX subsystem via
/dev/sgx_virt_epc rather than in KVM.  Doing so has two major advantages:

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



Kai Huang (2):
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

jarkko@kernel.org (2):
  x86/sgx: Remove a warn from sgx_free_epc_page()
  x86/sgx: Wipe out EREMOVE from sgx_free_epc_page()

 Documentation/virt/kvm/api.rst                |  23 +
 arch/x86/Kconfig                              |  12 +
 arch/x86/include/asm/cpufeatures.h            |   2 +
 arch/x86/include/asm/kvm_host.h               |   5 +
 arch/x86/include/asm/sgx.h                    |  19 +
 .../cpu/sgx/arch.h => include/asm/sgx_arch.h} |  20 +
 arch/x86/include/asm/vmx.h                    |   1 +
 arch/x86/include/uapi/asm/vmx.h               |   1 +
 arch/x86/kernel/cpu/cpuid-deps.c              |   3 +
 arch/x86/kernel/cpu/feat_ctl.c                |  63 ++-
 arch/x86/kernel/cpu/scattered.c               |   2 +
 arch/x86/kernel/cpu/sgx/Makefile              |   1 +
 arch/x86/kernel/cpu/sgx/driver.c              |  17 -
 arch/x86/kernel/cpu/sgx/encl.c                |  15 +-
 arch/x86/kernel/cpu/sgx/encls.h               |  29 +-
 arch/x86/kernel/cpu/sgx/ioctl.c               |  23 +-
 arch/x86/kernel/cpu/sgx/main.c                |  67 ++-
 arch/x86/kernel/cpu/sgx/sgx.h                 |   4 +-
 arch/x86/kernel/cpu/sgx/virt.c                | 316 ++++++++++++
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
 34 files changed, 1432 insertions(+), 147 deletions(-)
 create mode 100644 arch/x86/include/asm/sgx.h
 rename arch/x86/{kernel/cpu/sgx/arch.h => include/asm/sgx_arch.h} (96%)
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.c
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.h
 create mode 100644 arch/x86/kvm/vmx/sgx.c
 create mode 100644 arch/x86/kvm/vmx/sgx.h
```
#### [PATCH v2 0/9] Alpine Linux build fix and CI pipeline
##### From: Jiaxun Yang <jiaxun.yang@flygoat.com>

```c
From patchwork Mon Jan 18 06:37:59 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiaxun Yang <jiaxun.yang@flygoat.com>
X-Patchwork-Id: 12026643
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B6FD2C433E0
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 06:39:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 77B922225C
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 06:39:54 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732621AbhARGjh (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 18 Jan 2021 01:39:37 -0500
Received: from wnew4-smtp.messagingengine.com ([64.147.123.18]:54163 "EHLO
        wnew4-smtp.messagingengine.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729956AbhARGj3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 18 Jan 2021 01:39:29 -0500
Received: from compute6.internal (compute6.nyi.internal [10.202.2.46])
        by mailnew.west.internal (Postfix) with ESMTP id 36CDF16A5;
        Mon, 18 Jan 2021 01:38:22 -0500 (EST)
Received: from mailfrontend1 ([10.202.2.162])
  by compute6.internal (MEProxy); Mon, 18 Jan 2021 01:38:23 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=flygoat.com; h=
        from:to:cc:subject:date:message-id:mime-version
        :content-transfer-encoding; s=fm1; bh=DgEncLxHOwju3s3qsQovwzM5MS
        urO/+K7pT6AH/ZnM4=; b=ccWMOF063Ku6MMNGUrlAMjPF9KPsClnCmWNEv2gxFJ
        LHXYvLUKN/6/lyxJbxnhB8vkYgHY6hlFiuLDt8hVJbz0U5Y+ElqsXBXuvyiOfld+
        gzw2H3KEYEorw9Px/yJw6MZzS7xLsyGv3N/dgIq1bVCwo86/EtOuKvyJ0aoEBo0y
        hMSREwiHo9J3JRkF7H7W7uhqCxAeggDwJAL2gMfPWkBDf2ma88Nw4VQzRY9A64LG
        r0m7IrAscxNo9P4821yweTzSAG/Z7JSxju8Siwwjz/2P1zW8MIzcJVWpSXswMFSq
        QIvdVdYFncngMS7tvWYZpTCKUZwvEZs+VRZ6qe2BdwEQ==
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=
        messagingengine.com; h=cc:content-transfer-encoding:date:from
        :message-id:mime-version:subject:to:x-me-proxy:x-me-proxy
        :x-me-sender:x-me-sender:x-sasl-enc; s=fm1; bh=DgEncLxHOwju3s3qs
        QovwzM5MSurO/+K7pT6AH/ZnM4=; b=PlOoDjisa4rhkTAeEfJ3RsmKiRi1CJp/j
        QBz6jvD79OAzrVn+kO2p38KMV0cJtt1fzw2xvkA3DrK0EcEA9UmGKVmBTT3P99ia
        SAKBpcXmpSvHJxta9BFMyk7G5h+XkteSIBf7lCI/Y90Vluq9crgHMf931GN4Hm3V
        a+/ib6owhucEoRsSqVmnZQAIqdAPKHFHwLOu6QaruBJoFU9shd6cgzdMamkNnQt+
        gO1a2Yp0C6SpWeZwqsEhV5YRDEPYZIvEN9ReQKWkDMMrFnM5zs50iOd9NEOVQh2p
        1OlK3OjyshSvqQCeg4nmL1Fgp5mzRvwFbmNzodR1IPrgeWMFjlslg==
X-ME-Sender: <xms:3CwFYPZnlIm_u1iAn_-aPsgdP0k7feH3gYh01eT1ePDpoVddwVcqIg>
    <xme:3CwFYOZjVVwEQAHZKZidXGCj53XOgBWvXU07BM_kGOEQMo_tY7PamVALyrdjWGI3q
    Hox2Aht5XmzNII2RMY>
X-ME-Proxy-Cause: 
 gggruggvucftvghtrhhoucdtuddrgeduledrtdejgdeliecutefuodetggdotefrodftvf
    curfhrohhfihhlvgemucfhrghsthforghilhdpqfgfvfdpuffrtefokffrpgfnqfghnecu
    uegrihhlohhuthemuceftddtnecusecvtfgvtghiphhivghnthhsucdlqddutddtmdenuc
    fjughrpefhvffufffkofgggfestdekredtredttdenucfhrhhomheplfhirgiguhhnucgj
    rghnghcuoehjihgrgihunhdrhigrnhhgsehflhihghhorghtrdgtohhmqeenucggtffrrg
    htthgvrhhnpeehgfdtkefggfetgeffgfeuuedtjeejudekveevfeevjeefgeettdefleet
    gfdvudenucffohhmrghinhepghhithhlrggsrdgtohhmnecukfhppeduudeirddvvdekrd
    ekgedrvdenucevlhhushhtvghrufhiiigvpedtnecurfgrrhgrmhepmhgrihhlfhhrohhm
    pehjihgrgihunhdrhigrnhhgsehflhihghhorghtrdgtohhm
X-ME-Proxy: <xmx:3CwFYB-FhIvTYl22E5U7prntTbIAkVigIumpzLl1HjSL0jtlcrxk0Q>
    <xmx:3CwFYFr0fVb4rO2ztQKeuDlf9XSO8wtNSVGE0e3ErVGG_4Gc1AChIg>
    <xmx:3CwFYKqqZYhwv1Prk61mmqPA5O307gjgeFNXe6eVATbxmK9boI-DVw>
    <xmx:3SwFYObR50qMvbcydSoD8bUFcrqPLgOFZp2BrXBguJZBls6qd9lbZbW_talotIup>
Received: from strike.U-LINK.com (unknown [116.228.84.2])
        by mail.messagingengine.com (Postfix) with ESMTPA id 4F4BD24005B;
        Mon, 18 Jan 2021 01:38:14 -0500 (EST)
From: Jiaxun Yang <jiaxun.yang@flygoat.com>
To: qemu-devel@nongnu.org
Cc: David Gibson <david@gibson.dropbear.id.au>, qemu-ppc@nongnu.org,
 Greg Kurz <groug@kaod.org>, Max Reitz <mreitz@redhat.com>,
 kvm@vger.kernel.org,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>,
 Wainer dos Santos Moschetta <wainersm@redhat.com>,
 Paolo Bonzini <pbonzini@redhat.com>, Fam Zheng <fam@euphon.net>,
 Viktor Prutyanov <viktor.prutyanov@phystech.edu>,
 Alistair Francis <alistair@alistair23.me>, Thomas Huth <thuth@redhat.com>,
 Laurent Vivier <lvivier@redhat.com>,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>, qemu-block@nongnu.org,
 Kevin Wolf <kwolf@redhat.com>, Jiaxun Yang <jiaxun.yang@flygoat.com>
Subject: [PATCH v2 0/9] Alpine Linux build fix and CI pipeline
Date: Mon, 18 Jan 2021 14:37:59 +0800
Message-Id: <20210118063808.12471-1-jiaxun.yang@flygoat.com>
X-Mailer: git-send-email 2.30.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Alpine Linux is a security-oriented, lightweight Linux distribution
based on musl libc and busybox.

It it popular among Docker guests and embedded applications.

Adding it to test against different libc.

Patches pending review at v2 are: 7, 8, 9

Tree avilable at: https://gitlab.com/FlyGoat/qemu/-/commits/alpine_linux_v2
CI All green: https://gitlab.com/FlyGoat/qemu/-/pipelines/242003288

It is known to have checkpatch complains about identation but they're
all pre-existing issues as I'm only doing string replacement. 

v2:
 - Reoreder patches (Wainer)
 - Add shadow to dockerfile (Wainer)
 - Pickup proper signal.h fix (PMM)
 - Correct clock_adjtime title (Thomas Huth)
 - Collect review tags

Jiaxun Yang (8):
  configure: Add sys/timex.h to probe clock_adjtime
  libvhost-user: Include poll.h instead of sys/poll.h
  hw/block/nand: Rename PAGE_SIZE to NAND_PAGE_SIZE
  elf2dmp: Rename PAGE_SIZE to ELF2DMP_PAGE_SIZE
  tests: Rename PAGE_SIZE definitions
  accel/kvm: avoid using predefined PAGE_SIZE
  tests/docker: Add dockerfile for Alpine Linux
  gitlab-ci: Add alpine to pipeline

Michael Forney (1):
  osdep.h: Remove <sys/signal.h> include

 configure                                 |  1 +
 meson.build                               |  1 -
 contrib/elf2dmp/addrspace.h               |  6 +-
 include/qemu/osdep.h                      |  4 --
 subprojects/libvhost-user/libvhost-user.h |  2 +-
 accel/kvm/kvm-all.c                       |  3 +
 contrib/elf2dmp/addrspace.c               |  4 +-
 contrib/elf2dmp/main.c                    | 18 +++---
 hw/block/nand.c                           | 40 ++++++-------
 tests/migration/stress.c                  | 10 ++--
 tests/qtest/libqos/malloc-pc.c            |  4 +-
 tests/qtest/libqos/malloc-spapr.c         |  4 +-
 tests/qtest/m25p80-test.c                 | 54 ++++++++---------
 tests/tcg/multiarch/system/memory.c       |  6 +-
 tests/test-xbzrle.c                       | 70 +++++++++++------------
 .gitlab-ci.d/containers.yml               |  5 ++
 .gitlab-ci.yml                            | 23 ++++++++
 tests/docker/dockerfiles/alpine.docker    | 57 ++++++++++++++++++
 18 files changed, 198 insertions(+), 114 deletions(-)
 create mode 100644 tests/docker/dockerfiles/alpine.docker
```
#### [PATCH 0/1] diag9c forwarding
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From patchwork Mon Jan 18 13:17:38 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 12027321
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5BD49C433E6
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 13:19:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2121C22B49
	for <kvm@archiver.kernel.org>; Mon, 18 Jan 2021 13:19:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2404007AbhARNSs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 18 Jan 2021 08:18:48 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:40972 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2392128AbhARNSh (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 18 Jan 2021 08:18:37 -0500
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10ID3YJB019940;
        Mon, 18 Jan 2021 08:17:47 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=8tkeQGsFBR/19zcWcJgkcGEoGDrufQhBcasXaTGWg7k=;
 b=ByWD7pDIfYf3wyXqbQRR1fzo3SW8h1KBpBYjehTgDt0Guu4/c77prxGgo7f+/pYT4RPy
 twWqFFhrBBE26D1GF9C7Va914vfxt3KxpwRB7390iR2uwWKEt2QRZX6JkQ7K4+uo/6ZG
 YtTgp14O2Fc9Y8fjQlhl175FmJqF83kZ5HuBb8ba7AFkugKoXMArNi2EtIK083fhiAA8
 RLht0u9b4jmcyweiANTf84YXPRZbFiLOr0X9kEa1PY/4rUd9/PPJXhNeffTG+tf1kX6y
 UQ0X7+jRlxypaEwA9NJHg0nwxQKcAm89N30FvIJpYoUH0IuSTKUdhkO/pAs2Z8+685+K 3Q==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36586hchur-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 Jan 2021 08:17:46 -0500
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10ID3u3M023436;
        Mon, 18 Jan 2021 08:17:46 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 36586hchtj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 Jan 2021 08:17:45 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10IDHIup010618;
        Mon, 18 Jan 2021 13:17:43 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma06fra.de.ibm.com with ESMTP id 363qdh92te-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 18 Jan 2021 13:17:42 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10IDHdCk39387466
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 18 Jan 2021 13:17:40 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D844242047;
        Mon, 18 Jan 2021 13:17:39 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C547D42045;
        Mon, 18 Jan 2021 13:17:39 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon, 18 Jan 2021 13:17:39 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 6FDC5E02A3; Mon, 18 Jan 2021 14:17:39 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Pierre Morel <pmorel@linux.ibm.com>,
        Thomas Huth <thuth@redhat.com>
Subject: [PATCH 0/1] diag9c forwarding
Date: Mon, 18 Jan 2021 14:17:38 +0100
Message-Id: <20210118131739.7272-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-18_11:2021-01-18,2021-01-18 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0
 lowpriorityscore=0 phishscore=0 clxscore=1015 adultscore=0
 priorityscore=1501 suspectscore=0 malwarescore=0 mlxscore=0
 mlxlogscore=880 spamscore=0 bulkscore=0 classifier=spam adjust=0
 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101180077
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch will forward the yieldto hypercall (diag9c) if in the host
the target CPU is also not running. As we do not yet have performance
data (and recommendations) the default is turned off, but this can
be changed during runtime.

Pierre Morel (1):
  s390:kvm: diag9c forwarding

 arch/s390/include/asm/kvm_host.h |  1 +
 arch/s390/include/asm/smp.h      |  1 +
 arch/s390/kernel/smp.c           |  1 +
 arch/s390/kvm/diag.c             | 31 ++++++++++++++++++++++++++++---
 arch/s390/kvm/kvm-s390.c         |  6 ++++++
 arch/s390/kvm/kvm-s390.h         |  8 ++++++++
 6 files changed, 45 insertions(+), 3 deletions(-)
```
