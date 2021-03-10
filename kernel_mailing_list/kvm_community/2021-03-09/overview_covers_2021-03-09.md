

#### [PATCH v2 00/25] KVM SGX virtualization support
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Tue Mar  9 01:38:49 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12123749
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E05F1C433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 01:39:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B7B7665259
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 01:39:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230224AbhCIBjI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 20:39:08 -0500
Received: from mga05.intel.com ([192.55.52.43]:12739 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230252AbhCIBjE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 20:39:04 -0500
IronPort-SDR: 
 qZyKRUAaC+RPF/DrTNZMWXyaUYZVHj/UYz7OHZQ3hdij/iSRJIVV7M6WLpBP0g7M/twCrxp9w/
 l8w1U9t96bAQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9917"; a="273166122"
X-IronPort-AV: E=Sophos;i="5.81,233,1610438400";
   d="scan'208";a="273166122"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Mar 2021 17:39:02 -0800
IronPort-SDR: 
 LQxC6Z98sV7ixDxOqMr/GPTQiFisZHrtBQSudWfurmzYxTCSkXlVEFsaFdhqsqmTwWQ/+9BIry
 njcQ0nY5OdZw==
X-IronPort-AV: E=Sophos;i="5.81,233,1610438400";
   d="scan'208";a="509117184"
Received: from kzliu-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.252.128.38])
  by fmsmga001-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Mar 2021 17:38:57 -0800
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-sgx@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, seanjc@google.com, jarkko@kernel.org,
        luto@kernel.org, dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        jethro@fortanix.com, b.thiel@posteo.de, jmattson@google.com,
        joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        corbet@lwn.net
Subject: [PATCH v2 00/25] KVM SGX virtualization support
Date: Tue,  9 Mar 2021 14:38:49 +1300
Message-Id: <cover.1615250634.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds KVM SGX virtualization support. The first 14 patches starting
with x86/sgx or x86/cpu.. are necessary changes to x86 and SGX core/driver to
support KVM SGX virtualization, while the rest are patches to KVM subsystem.

This series is based against latest upstream kernel master branch.

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
 arch/x86/kernel/cpu/feat_ctl.c                |  71 ++-
 arch/x86/kernel/cpu/scattered.c               |   2 +
 arch/x86/kernel/cpu/sgx/Makefile              |   1 +
 arch/x86/kernel/cpu/sgx/driver.c              |  17 -
 arch/x86/kernel/cpu/sgx/encl.c                |  29 +-
 arch/x86/kernel/cpu/sgx/encls.h               |  30 +-
 arch/x86/kernel/cpu/sgx/ioctl.c               |  23 +-
 arch/x86/kernel/cpu/sgx/main.c                |  94 +++-
 arch/x86/kernel/cpu/sgx/sgx.h                 |  13 +-
 arch/x86/kernel/cpu/sgx/virt.c                | 370 ++++++++++++++
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
 32 files changed, 1460 insertions(+), 118 deletions(-)
 rename arch/x86/{kernel/cpu/sgx/arch.h => include/asm/sgx.h} (89%)
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.c
 create mode 100644 arch/x86/kvm/vmx/sgx.c
 create mode 100644 arch/x86/kvm/vmx/sgx.h
```
#### [PATCH 0/2] Fixups to hide our goofs
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Tue Mar  9 02:18:58 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12123861
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3D4D3C433E6
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 02:20:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 036B1652B2
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 02:20:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230397AbhCICTr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 21:19:47 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:41948 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S230512AbhCICTW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 21:19:22 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id E2101C06174A
        for <kvm@vger.kernel.org>; Mon,  8 Mar 2021 18:19:21 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id 194so15239276ybl.5
        for <kvm@vger.kernel.org>; Mon, 08 Mar 2021 18:19:21 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=LHP3MFoVQ43/Gdu+SGGU2Is+rQZvEboJW+kRfZtIQZg=;
        b=v7urjtWEjHOqyhANz7nFw0kaPm9raBppEFnZDYvx7qFQqJzsK8pdL4gt4ZnZw/bHT9
         Cp9xkaguoC80WQZYY9gWD0/uB8xuBN8vwlY60QiSyE8LI20slrRP/qbxo3PuwcVWciAY
         ng31rfT81AbR94iBpRSLzXwObL/sfr6cIMDSLrlukpe+3PG7Oko6cb3o5+OgccuAdctd
         Fm0iWBv2F/fAsngBn+anutmUzokyADBbBbo2vU9nYH6MpnMOPRnx1QNJy4VUVmWwHmHe
         q8qsUi1C5D/6pAqx+yZIa1pNcyo4oHyqbNeySKRCDdab+bM8r+ZLhAsTrOPmH6DBSM3B
         hx1g==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:reply-to:date:message-id:mime-version
         :subject:from:to:cc;
        bh=LHP3MFoVQ43/Gdu+SGGU2Is+rQZvEboJW+kRfZtIQZg=;
        b=DUBk1eKD/pPNneVqRab7WuerE2F6Tpnb2XJsTeddQfKyLLI3xi/zyAEPJ5OmIkL/Uz
         lEzWUHcoJoYdJgQdeT79/C5e8iZ20/oqVovjo1hO1/NieBaZHBN51r6dA6wJim1OaWHj
         6fJisopJeAj30r655s25a/p1t4zc31CRcLv1PCTwGqHWiLC94tDGI1FYn6/Rs8mOnu9r
         kUSgBnVQkOL8SZZ1R7Fk+7KF92MjKxCAXF79yrftOiZoNMJUDLL0TgPMKrK0iLMeP9dy
         DUEMs6qPnEcQimfWgGtxNCT9JN+R/9lJSsq6x94No0xAQ+AV9ZSksomr2ltY0SOO74d+
         tI8Q==
X-Gm-Message-State: AOAM532aQ0vDpNW2rYfItdnhcqPt+EJVKaiD9Ud2Qr27BRGHEZna7sCY
        1MCkzJiW8INDGyzhkMqeFd/JzUZOTlk=
X-Google-Smtp-Source: 
 ABdhPJyq27oip7hDkYlMjMkztlsUexbcEDv3n7XSxHWiJPIx5Qg3sDA6iE+hYLdwyQZ/M+0JF+uyBqQmSSY=
Sender: "seanjc via sendgmr" <seanjc@seanjc798194.pdx.corp.google.com>
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:8:847a:d8b5:e2cc])
 (user=seanjc job=sendgmr) by 2002:a25:3bc6:: with SMTP id
 i189mr19775166yba.31.1615256361119;
 Mon, 08 Mar 2021 18:19:21 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Mon,  8 Mar 2021 18:18:58 -0800
Message-Id: <20210309021900.1001843-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH 0/2] Fixups to hide our goofs
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Tom Lendacky <thomas.lendacky@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Please squash away our mistakes and hide them from the world. :-)

Stuffed the MMIO generation to start at 0x3ffffffffffffff0 (bits 61:4 set)
and role over into bit 62.  Bit 63 is used for the "update in-progress" so
I'm fairly confident there are no more collisions with other SPTE bits.

For the PCID thing, note that there are two patches with the same changelog.
Not sure what's intended there...

Also, I forgot about adding the PAE root helpers until I tried testing and
PAE didn't work with SME.  I'll get those to you tomorrow.

Sean Christopherson (2):
  KVM: x86: Fixup "Get active PCID only when writing a CR3 value"
  KVM: x86/mmu: Exclude the MMU_PRESENT bit from MMIO SPTE's generation

 arch/x86/kvm/mmu/spte.h | 12 +++++++-----
 arch/x86/kvm/svm/svm.c  |  9 +++++++--
 2 files changed, 14 insertions(+), 7 deletions(-)
```
#### [RFC PATCH v2 0/6] Add IOPF support for VFIO passthrough
##### From: Shenming Lu <lushenming@huawei.com>

```c
From patchwork Tue Mar  9 06:22:01 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Shenming Lu <lushenming@huawei.com>
X-Patchwork-Id: 12124219
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 314DFC433E6
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 06:22:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E8A6165299
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 06:22:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229799AbhCIGWZ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 01:22:25 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:13875 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S229527AbhCIGWY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 01:22:24 -0500
Received: from DGGEMS414-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4DvlSc1YQGz8vRm;
        Tue,  9 Mar 2021 14:20:32 +0800 (CST)
Received: from DESKTOP-7FEPK9S.china.huawei.com (10.174.184.135) by
 DGGEMS414-HUB.china.huawei.com (10.3.19.214) with Microsoft SMTP Server id
 14.3.498.0; Tue, 9 Mar 2021 14:22:11 +0800
From: Shenming Lu <lushenming@huawei.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Will Deacon <will@kernel.org>,
        Robin Murphy <robin.murphy@arm.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jean-Philippe Brucker <jean-philippe@linaro.org>,
        Eric Auger <eric.auger@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <iommu@lists.linux-foundation.org>, <linux-api@vger.kernel.org>
CC: Kevin Tian <kevin.tian@intel.com>, <yi.l.liu@intel.com>,
        Christoph Hellwig <hch@infradead.org>,
        Lu Baolu <baolu.lu@linux.intel.com>,
        Jonathan Cameron <Jonathan.Cameron@huawei.com>,
        Barry Song <song.bao.hua@hisilicon.com>,
        <wanghaibin.wang@huawei.com>, <yuzenghui@huawei.com>,
        <zhukeqian1@huawei.com>, <lushenming@huawei.com>
Subject: [RFC PATCH v2 0/6] Add IOPF support for VFIO passthrough
Date: Tue, 9 Mar 2021 14:22:01 +0800
Message-ID: <20210309062207.505-1-lushenming@huawei.com>
X-Mailer: git-send-email 2.27.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.184.135]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

The static pinning and mapping problem in VFIO and possible solutions
have been discussed a lot [1, 2]. One of the solutions is to add I/O
page fault support for VFIO devices. Different from those relatively
complicated software approaches such as presenting a vIOMMU that provides
the DMA buffer information (might include para-virtualized optimizations),
IOPF mainly depends on the hardware faulting capability, such as the PCIe
PRI extension or Arm SMMU stall model. What's more, the IOPF support in
the IOMMU driver is being implemented in SVA [3]. So we add IOPF support
for VFIO passthrough based on the IOPF part of SVA in this series.

We have measured its performance with UADK [4] (passthrough an accelerator
to a VM) on Hisilicon Kunpeng920 board:

Run hisi_sec_test...
 - with varying message lengths and sending times
 - with/without stage 2 IOPF enabled

when msg_len = 1MB and PREMAP_LEN (in patch 3) = 1:
           speed (KB/s)
 times     w/o IOPF        with IOPF (num of faults)        degradation
 1         325596          119152 (518)                     36.6%
 100       7524985         5804659 (1058)                   77.1%
 1000      8661817         8440209 (1071)                   97.4%
 5000      8804512         8724368 (1216)                   99.1%

If we use the same region to send messages, since page faults occur almost
only when first accessing, more times, less degradation.

when msg_len = 10MB and PREMAP_LEN = 512:
           speed (KB/s)
 times     w/o IOPF        with IOPF (num of faults)        degradation
 1         1012758         682257 (13)                      67.4%
 100       8680688         8374154 (26)                     96.5%
 1000      8860861         8719918 (26)                     98.4%

We see that pre-mapping can help.

And we also measured the performance of host SVA with the same params:

when msg_len = 1MB:
           speed (KB/s)
 times     w/o IOPF        with IOPF (num of faults)        degradation
 1         951672          163866 (512)                     17.2%
 100       8691961         4529971 (1024)                   52.1%
 1000      9158721         8376346 (1024)                   91.5%
 5000      9184532         9008739 (1024)                   98.1%

Besides, the avg time spent in vfio_iommu_dev_fault_handler() (in patch 3)
is little less than iopf_handle_group() (in SVA) (1.6 us vs 2.0 us).

History:

v1 -> v2
 - Numerous improvements following the suggestions. Thanks a lot to all
   of you.

Yet TODO:
 - Add support for PRI.
 - Consider selective-faulting. (suggested by Kevin)
 ...

Links:
[1] Lesokhin I, et al. Page Fault Support for Network Controllers. In ASPLOS,
    2016.
[2] Tian K, et al. coIOMMU: A Virtual IOMMU with Cooperative DMA Buffer Tracking
    for Efficient Memory Management in Direct I/O. In USENIX ATC, 2020.
[3] https://patchwork.kernel.org/project/linux-arm-kernel/cover/20210302092644.2553014-1-jean-philippe@linaro.org/
[4] https://github.com/Linaro/uadk

Any comments and suggestions are very welcome. :-)

Thanks,
Shenming


Shenming Lu (6):
  iommu: Evolve to support more scenarios of using IOPF
  vfio: Add an MMU notifier to avoid pinning
  vfio: Add a page fault handler
  vfio: VFIO_IOMMU_ENABLE_IOPF
  vfio: No need to statically pin and map if IOPF enabled
  vfio: Add nested IOPF support

 .../iommu/arm/arm-smmu-v3/arm-smmu-v3-sva.c   |   3 +-
 drivers/iommu/arm/arm-smmu-v3/arm-smmu-v3.c   |  11 +-
 drivers/iommu/io-pgfault.c                    |   4 -
 drivers/iommu/iommu.c                         |  56 ++-
 drivers/vfio/vfio.c                           | 118 +++++
 drivers/vfio/vfio_iommu_type1.c               | 446 +++++++++++++++++-
 include/linux/iommu.h                         |  21 +-
 include/linux/vfio.h                          |  14 +
 include/uapi/linux/iommu.h                    |   3 +
 include/uapi/linux/vfio.h                     |   6 +
 10 files changed, 661 insertions(+), 21 deletions(-)
```
#### [PATCH v3 0/9] Introduce vfio-pci-core subsystem
##### From: Max Gurtovoy <mgurtovoy@nvidia.com>

```c
From patchwork Tue Mar  9 08:33:48 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Max Gurtovoy <mgurtovoy@nvidia.com>
X-Patchwork-Id: 12124379
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 89DC0C43381
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 08:34:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 50607652A8
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 08:34:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230231AbhCIIeX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 03:34:23 -0500
Received: from mail-dm6nam12on2057.outbound.protection.outlook.com
 ([40.107.243.57]:64038
        "EHLO NAM12-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S229714AbhCIIeH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 03:34:07 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=jvvvBNdtKkyx/sSOZ7MM1hwcbPfCtbieVMg1shK5nIWBeRGt04rP16QKwpWU+it6N8TbZs9Tmr+Pw+YhO8yskczavaLIXdkEaUGbmylRRFFO65xjKfXz3d4B1rGnC1RzhJatO5QoSf1hHC+dS+lozg+BJkBevm1qvu8KBcy4Bt4YxcmsoJjFBZ/F3jX820g7mehwb1VqpyfylnIMlvRg5W/v6DW4scXpZzgLwbd509VNUbBdJJt9jcBXSDJLA9XhKU07dsB+rMLyf7FCTx+Rlq69Z+nD2T9W7xeLNIp0B57pTOFylXsLBEiSCk+WDR5NVKFhJhVSF61xbOjyDcgI8Q==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xjU+RYMaRHbey9D7K97YSu9boAD6syLikz+CAiYlQzk=;
 b=Mlq4b6KL1Okr8jszGhjvQ45oDR+0FmapP2GjI8ExtT950E3Gj6JDki2fsBFmR2c/+PRHGx/+ER7aP6zkLkq/1R+jh7fFwkORc+zWqA6BDH6W5vjuXbFnN5cAJcldYeDsAaoVWBfTVrZjFQZ65eVLZbH8hFuPdHE6FJM1pJij/JxG1rM2Vp+4u9EaGcJGl6ytdDhIfoKfj0LttDqFwgxkXRZqo8pTM9LbpN3W/W1umVjypxDSplKizTa3yyYlAMEgd4aA1Ie1ZKeupenqI6CieTZ19ssexJmEAy1+CSGnaMgSE0Qm6M3NVoVjthSyXa/0DDC3H6G/r/q/wohx2+idrg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass (sender ip is
 216.228.112.35) smtp.rcpttodomain=linux.ibm.com smtp.mailfrom=nvidia.com;
 dmarc=pass (p=none sp=none pct=100) action=none header.from=nvidia.com;
 dkim=none (message not signed); arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=xjU+RYMaRHbey9D7K97YSu9boAD6syLikz+CAiYlQzk=;
 b=amCeK0SWngAoKvazxG+3vFIkxsizrG6Fyin80AdEaEIJDw5JN4/ZexFwJHhXeEqgTA/e+za66C5xClloJrg7gx4HhRIsgjhb5EF29kgwHiANCg0Lv/GDg2cPtd1XWhqi8Dr/1hZi4tkgK9LTqxo79NPJOG4mCiz8tWbVIeUmscRrTuK78SN0e4lFaig2f7iETuCgb55iDKS1MZZQkL72DPMPE2a6BugwaoWLroz8Cnvq8lwK9oqPUUqyAOAxyzZLjLL5ieG+YW9J0VMt4On+47mUXIMhDRetYfutU8bMO6VtBEyepCstE687zQZUrmn3hhFnL5TLihNdFuGTawrkIg==
Received: from DM6PR17CA0032.namprd17.prod.outlook.com (2603:10b6:5:1b3::45)
 by BY5PR12MB4641.namprd12.prod.outlook.com (2603:10b6:a03:1f7::29) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.17; Tue, 9 Mar
 2021 08:34:05 +0000
Received: from DM6NAM11FT067.eop-nam11.prod.protection.outlook.com
 (2603:10b6:5:1b3:cafe::d8) by DM6PR17CA0032.outlook.office365.com
 (2603:10b6:5:1b3::45) with Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.17 via Frontend
 Transport; Tue, 9 Mar 2021 08:34:05 +0000
X-MS-Exchange-Authentication-Results: spf=pass (sender IP is 216.228.112.35)
 smtp.mailfrom=nvidia.com; linux.ibm.com; dkim=none (message not signed)
 header.d=none;linux.ibm.com; dmarc=pass action=none header.from=nvidia.com;
Received-SPF: Pass (protection.outlook.com: domain of nvidia.com designates
 216.228.112.35 as permitted sender) receiver=protection.outlook.com;
 client-ip=216.228.112.35; helo=mail.nvidia.com;
Received: from mail.nvidia.com (216.228.112.35) by
 DM6NAM11FT067.mail.protection.outlook.com (10.13.172.76) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384) id
 15.20.3912.17 via Frontend Transport; Tue, 9 Mar 2021 08:34:05 +0000
Received: from HQMAIL111.nvidia.com (172.20.187.18) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Tue, 9 Mar
 2021 08:34:03 +0000
Received: from r-nvmx02.mtr.labs.mlnx (172.20.145.6) by mail.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server id 15.0.1497.2 via Frontend
 Transport; Tue, 9 Mar 2021 08:33:58 +0000
From: Max Gurtovoy <mgurtovoy@nvidia.com>
To: <jgg@nvidia.com>, <alex.williamson@redhat.com>,
        <cohuck@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>
CC: <liranl@nvidia.com>, <oren@nvidia.com>, <tzahio@nvidia.com>,
        <leonro@nvidia.com>, <yarong@nvidia.com>, <aviadye@nvidia.com>,
        <shahafs@nvidia.com>, <artemp@nvidia.com>, <kwankhede@nvidia.com>,
        <ACurrid@nvidia.com>, <cjia@nvidia.com>, <yishaih@nvidia.com>,
        <mjrosato@linux.ibm.com>, <aik@ozlabs.ru>, <hch@lst.de>,
        Max Gurtovoy <mgurtovoy@nvidia.com>
Subject: [PATCH v3 0/9] Introduce vfio-pci-core subsystem
Date: Tue, 9 Mar 2021 08:33:48 +0000
Message-ID: <20210309083357.65467-1-mgurtovoy@nvidia.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
X-EOPAttributedMessage: 0
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 189f57ac-8b41-41b7-9ee6-08d8e2d6199b
X-MS-TrafficTypeDiagnostic: BY5PR12MB4641:
X-Microsoft-Antispam-PRVS: 
 <BY5PR12MB4641D57B8A7B6F0EF18CF32CDE929@BY5PR12MB4641.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:9508;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 96QLBKwjGcVf74kKudAaiUdZjcQidptvAAv1yuyAoppZOFmF73jk0lEulD7aCPnYg6kXdSGjpXjsZAp7BQUSe4+oEwH7zrhLvEaAiyrqmEWxXJCKkOakdykmddMvlkcV35KKpP1cl9AD6khC49C3wY+eT1zXkd4huvaqFz7x3+sEckQDrXYLHvEcsSqHPIzT9LCUIiQo9mJ3jaULFdHk+zeRQ54hIrb96YDeydVBO8uXoyJIZc9PbltOLBrnC3a3O/b/NrdeMcleXYGoLdc6QlGriyPzt5UrrC6xEPdAKdGOOAJn4HP4Uxor3dE7CdJ1Bx+QTQASL2UADIIQckCqe5eNzEtzPDSGf4KC2XtQMgI4NXLsUpQis5ZBrTw/oHQJzJMUrKKnuNOXsgcfC+3WkydHvAZdDrTM/+tIuXYARmLnOUswAJummVmgsvbkmJceeKs1f1v9PmkOoSPn/wPf784ue6SM7ieD2xJaKZNofKKzrZXxZY59W+yWtqUnctlahT+wUSpHNjqTNoUPzZ0TKGtn9Ub4EJiQn5UOjKx10W86KsFvQQPPYQbN0FWAd4vpsYB6Iio8Kjr/l26NoA4GidRM4QHD7tA2LW2jig/sGspcW6cPDjQPlqpunF8PFlKKDc62cbfmpibP5EeO8x2mm3/gicvljOOtN9yftQDECNsQT3LHxtfizrTzheGIaSZZ9Q+jIXdBPMpDABkPsOUlIIWAzByclxwUQaNSDSMvxuQMglIO+qPuTtSEydR+h9JVckGooYAKDlzGiW1I4OJKPQ==
X-Forefront-Antispam-Report: 
 CIP:216.228.112.35;CTRY:US;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:mail.nvidia.com;PTR:schybrid04.nvidia.com;CAT:NONE;SFS:(4636009)(376002)(346002)(136003)(396003)(39860400002)(46966006)(36840700001)(356005)(7636003)(110136005)(2906002)(316002)(86362001)(186003)(6666004)(36756003)(8936002)(36860700001)(82740400003)(70206006)(5660300002)(4326008)(47076005)(83380400001)(966005)(2616005)(1076003)(478600001)(336012)(70586007)(107886003)(34020700004)(82310400003)(54906003)(8676002)(426003)(26005);DIR:OUT;SFP:1101;
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Mar 2021 08:34:05.2343
 (UTC)
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 189f57ac-8b41-41b7-9ee6-08d8e2d6199b
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-OriginalAttributedTenantConnectingIp: 
 TenantId=43083d15-7273-40c1-b7db-39efd9ccc17a;Ip=[216.228.112.35];Helo=[mail.nvidia.com]
X-MS-Exchange-CrossTenant-AuthSource: 
 DM6NAM11FT067.eop-nam11.prod.protection.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Anonymous
X-MS-Exchange-CrossTenant-FromEntityHeader: HybridOnPrem
X-MS-Exchange-Transport-CrossTenantHeadersStamped: BY5PR12MB4641
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Alex and Cornelia,

This series split the vfio_pci driver into 2 parts: pci drivers and a
subsystem driver that will also be library of code. The main pci driver,
vfio_pci.ko will be used as before and it will bind to the subsystem
driver vfio_pci_core.ko to register to the VFIO subsystem.
New vendor vfio pci drivers were introduced in this series are:
- igd_vfio_pci.ko
- nvlink2gpu_vfio_pci.ko
- npu2_vfio_pci.ko

These drivers also will bind to the subsystem driver vfio_pci_core.ko to
register to the VFIO subsystem. These drivers will also add vendor
specific extensions that are relevant only for the devices that will be
driven by them. This is a typical Linux subsystem framework behaviour.

This series is coming to solve some of the issues that were raised in the
previous attempt for extending vfio-pci for vendor specific
functionality: https://lkml.org/lkml/2020/5/17/376 by Yan Zhao.

This solution is also deterministic in a sense that when a user will
bind to a vendor specific vfio-pci driver, it will get all the special
goodies of the HW. Non-common code will be pushed only to the specific
vfio_pci driver.
 
This subsystem framework will also ease on adding new vendor specific
functionality to VFIO devices in the future by allowing another module
to provide the pci_driver that can setup number of details before
registering to VFIO subsystem (such as inject its own operations).

Below we can see the proposed changes:

+-------------------------------------------------------------------+
|                                                                   |
|                               VFIO                                |
|                                                                   |
+-------------------------------------------------------------------+
                                                             
+-------------------------------------------------------------------+
|                                                                   |
|                           VFIO_PCI_CORE                           |
|                                                                   |
+-------------------------------------------------------------------+

+--------------+ +------------+ +-------------+ +-------------------+
|              | |            | |             | |                   |
|              | |            | |             | |                   |
|   VFIO_PCI   | |IGD_VFIO_PCI| |NPU2_VFIO_PCI| |NVLINK2GPU_VFIO_PCI|
|              | |            | |             | |                   |
|              | |            | |             | |                   |
+--------------+ +------------+ +-------------+ +-------------------+

Patches (1/9) - (4/9) introduce the above changes for vfio_pci and
vfio_pci_core.

Patches (6/9) and (7/9) are a preparation for adding nvlink2 related vfio
pci drivers.

Patch (8/9) introduce new npu2_vfio_pci and nvlink2gpu_vfio_pci drivers
that will drive NVLINK2 capable devices exist today (IBMs emulated PCI
managment device and NVIDIAs NVLINK2 capable GPUs). These drivers add
vendor specific functionality that is related to the IBM NPU2 unit which
is an NVLink2 host bus adapter and to capable NVIDIA GPUs.

Patch (9/9) introduce new igd_vfio_pci driver for adding special extensions
for INTELs Graphics card (GVT-d).

All new 3 vendor specific vfio_pci drivers can be extended easily and
new vendor specific functionality might be added to the needed vendor
drivers. In case there is a vendor specific vfio_pci driver for the
device that a user would like to use, this driver should be bounded to
that device. Otherwise, vfio_pci.ko should be bounded to it (backward
compatability is also supported).

This framework will allow adding more HW specific features such as Live
Migration in the future by extending existing vendor vfio_pci drivers or
creating new ones (e.g. mlx5_vfio_pci.ko that will drive live migration
for mlx5 PCI devices and mlx5_snap_vfio_pci.ko that will drive live
migration for mlx5_snap devices such as mlx5 NVMe and Virtio-BLK SNAP
devices).

Testing:
1. vfio_pci.ko was tested by using 2 VirtIO-BLK physical functions based
   on NVIDIAs Bluefield-2 SNAP technology. These 2 PCI functions were
   passed to a QEMU based VM after binding to vfio_pci.ko and basic FIO
   read/write was issued in the VM to each exposed block device (vda, vdb).
2. igd_vfio_pci.ko was only compiled and loaded/unloaded successfully on x86 server.
3. npu2_vfio_pci.ko and nvlink2gpu_vfio_pci.KO were successfully
   compiled and loaded/unloaded on P9 server + vfio probe/remove of devices (without
   QEMU/VM).

Note: After this series will be approved, a new discovery/matching mechanism
      should be introduced in order to help users to decide which driver should
      be bounded to which device.

changes from v2:
 - Use container_of approach between core and vfio_pci drivers.
 - Comment on private/public attributes for the core structure to ease on
   code maintanance.
 - rename core structure to vfio_pci_core_device.
 - create 3 new vendor drivers (igd_vfio_pci, npu2_vfio_pci,
   nvlink2gpu_vfio_pci) and preserve backward compatibility.
 - rebase on top of Linux 5.11 tag.
 - remove patches that were accepted as stand-alone.
 - removed mlx5_vfio_pci driver from this series (3 vendor drivers will be enough
   for emphasizing the approch).

changes from v1:
 - Create a private and public vfio-pci structures (From Alex)
 - register to vfio core directly from vfio-pci-core (for now, expose
   minimal public funcionality to vfio pci drivers. This will remove the
   implicit behaviour from v1. More power to the drivers can be added in
   the future)
 - Add patch 3/9 to emphasize the needed extension for LM feature (From
   Cornelia)
 - take/release refcount for the pci module during core open/release
 - update nvlink, igd and zdev to PowerNV, X86 and s390 extensions for
   vfio-pci core
 - fix segfault bugs in current vfio-pci zdev code

Max Gurtovoy (9):
  vfio-pci: rename vfio_pci.c to vfio_pci_core.c
  vfio-pci: rename vfio_pci_private.h to vfio_pci_core.h
  vfio-pci: rename vfio_pci_device to vfio_pci_core_device
  vfio-pci: introduce vfio_pci_core subsystem driver
  vfio/pci: introduce vfio_pci_device structure
  vfio-pci-core: export vfio_pci_register_dev_region function
  vfio/pci_core: split nvlink2 to nvlink2gpu and npu2
  vfio/pci: export nvlink2 support into vendor vfio_pci drivers
  vfio/pci: export igd support into vendor vfio_pci driver

 drivers/vfio/pci/Kconfig                      |   53 +-
 drivers/vfio/pci/Makefile                     |   20 +-
 .../pci/{vfio_pci_igd.c => igd_vfio_pci.c}    |  159 +-
 drivers/vfio/pci/igd_vfio_pci.h               |   24 +
 drivers/vfio/pci/npu2_trace.h                 |   50 +
 drivers/vfio/pci/npu2_vfio_pci.c              |  364 +++
 drivers/vfio/pci/npu2_vfio_pci.h              |   24 +
 .../vfio/pci/{trace.h => nvlink2gpu_trace.h}  |   27 +-
 ...io_pci_nvlink2.c => nvlink2gpu_vfio_pci.c} |  296 +-
 drivers/vfio/pci/nvlink2gpu_vfio_pci.h        |   24 +
 drivers/vfio/pci/vfio_pci.c                   | 2433 ++---------------
 drivers/vfio/pci/vfio_pci_config.c            |   70 +-
 drivers/vfio/pci/vfio_pci_core.c              | 2245 +++++++++++++++
 drivers/vfio/pci/vfio_pci_core.h              |  242 ++
 drivers/vfio/pci/vfio_pci_intrs.c             |   42 +-
 drivers/vfio/pci/vfio_pci_private.h           |  228 --
 drivers/vfio/pci/vfio_pci_rdwr.c              |   18 +-
 drivers/vfio/pci/vfio_pci_zdev.c              |   12 +-
 18 files changed, 3528 insertions(+), 2803 deletions(-)
 rename drivers/vfio/pci/{vfio_pci_igd.c => igd_vfio_pci.c} (58%)
 create mode 100644 drivers/vfio/pci/igd_vfio_pci.h
 create mode 100644 drivers/vfio/pci/npu2_trace.h
 create mode 100644 drivers/vfio/pci/npu2_vfio_pci.c
 create mode 100644 drivers/vfio/pci/npu2_vfio_pci.h
 rename drivers/vfio/pci/{trace.h => nvlink2gpu_trace.h} (72%)
 rename drivers/vfio/pci/{vfio_pci_nvlink2.c => nvlink2gpu_vfio_pci.c} (57%)
 create mode 100644 drivers/vfio/pci/nvlink2gpu_vfio_pci.h
 create mode 100644 drivers/vfio/pci/vfio_pci_core.c
 create mode 100644 drivers/vfio/pci/vfio_pci_core.h
 delete mode 100644 drivers/vfio/pci/vfio_pci_private.h
```
#### [kvm-unit-tests PATCH v5 0/6] CSS Mesurement Block
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
From patchwork Tue Mar  9 12:51:11 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 12124959
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3406AC433E0
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 12:52:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E64A265272
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 12:52:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231180AbhCIMvj (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 07:51:39 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:2674 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S231264AbhCIMvY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 9 Mar 2021 07:51:24 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 129CXcBV031526
        for <kvm@vger.kernel.org>; Tue, 9 Mar 2021 07:51:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=hWzhu368mYkRmLRSSxtlvSUwq74LObVkUqkHJlmUkFg=;
 b=RBiMeUpDPgkt1coEx7uGJ4+dwdna2YlO9A/uLDbNX8wpwLovmXLw2LYJSrmCoMFr85j8
 FXiYkmxLxWCe692Ex9iwirsU06IML2iEuy/P2uWAi1xVAMExsuqpyts5ATGRzqjwrnDj
 DKkJIGUa0+f4KWNbhnJqO/wEsTsdLWgjmkOIo73MfoHYSK/kV8qANzp7+Aa8ro+NzIE0
 2G+s4jW88aaRMMVJvnKminLNTZ9SrkC41HkX2r+zNGOxwXVm9v9ehqr1ADLdLG17sgHG
 fFzH1asR2JQi59wMB5CalNndJi/dTB0+yJ1+V0h5CmFtS+rmsP6PmDjR9C3Pc8S8z22o PA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 375whhgsw7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Tue, 09 Mar 2021 07:51:24 -0500
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 129CYNRP034449
        for <kvm@vger.kernel.org>; Tue, 9 Mar 2021 07:51:23 -0500
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0b-001b2d01.pphosted.com with ESMTP id 375whhgsun-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Mar 2021 07:51:23 -0500
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 129CTZAI008604;
        Tue, 9 Mar 2021 12:51:21 GMT
Received: from b06cxnps4074.portsmouth.uk.ibm.com
 (d06relay11.portsmouth.uk.ibm.com [9.149.109.196])
        by ppma06ams.nl.ibm.com with ESMTP id 3768urr0ya-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 09 Mar 2021 12:51:21 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 129CpIpE42926346
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 9 Mar 2021 12:51:19 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D25EE52050;
        Tue,  9 Mar 2021 12:51:18 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.156.215])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 8DABE52054;
        Tue,  9 Mar 2021 12:51:18 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, imbrenda@linux.ibm.com
Subject: [kvm-unit-tests PATCH v5 0/6] CSS Mesurement Block
Date: Tue,  9 Mar 2021 13:51:11 +0100
Message-Id: <1615294277-7332-1-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-09_11:2021-03-08,2021-03-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 bulkscore=0
 phishscore=0 mlxlogscore=999 spamscore=0 lowpriorityscore=0 adultscore=0
 clxscore=1015 priorityscore=1501 impostorscore=0 mlxscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2103090062
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
- failures not part of the feature under test will stop the tests.
- we add a css_enabled() function to test if a subchannel is enabled.

*note*:
    I rearranged the use of the senseid for the tests, by not modifying
    the existing test and having a dedicated senseid() function for
    the purpose of the tests.
    I think that it is in the rigght way so I kept the RB and ACK on
    the simplification, there are less changes, if it is wrong from me
    I suppose I will see this in the comments.
    Since the changed are moved inside the fmt0 test which is not approved
    for now I hope it is OK.

Regards,
Pierre

Pierre Morel (6):
  s390x: css: Store CSS Characteristics
  s390x: css: simplifications of the tests
  s390x: css: extending the subchannel modifying functions
  s390x: css: implementing Set CHannel Monitor
  s390x: css: testing measurement block format 0
  s390x: css: testing measurement block format 1

 lib/s390x/css.h     | 115 ++++++++++++++++++++-
 lib/s390x/css_lib.c | 236 ++++++++++++++++++++++++++++++++++++++++----
 s390x/css.c         | 216 ++++++++++++++++++++++++++++++++++++++--
 3 files changed, 540 insertions(+), 27 deletions(-)
```
#### [PATCH v6 00/12] x86: major paravirt cleanup
##### From: Juergen Gross <jgross@suse.com>

```c
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1615297700;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
  content-transfer-encoding:content-transfer-encoding;
        bh=95nQytiynjE+lgsCD540YiASmJmBTjnBSf2S8IR/Qxo=;
        b=eTOxo46U1RhOYqXDG/YlpXeiG3mLS1gXZT03GDvmXHlWw2A41vtoW6U87OFUK88uBhj8jV
        RYsSVHbP+7xSab4R9Ef5+rs9BdphzAAW2san7SPMMtY4hgtNyB/CkvRKIfSDf7TEgMCLzP
        /udQQc2plcCPrIq/so8hMX3DhKnWiBM=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id C3B9FAC54;
        Tue,  9 Mar 2021 13:48:19 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, linux-kernel@vger.kernel.org,
        x86@kernel.org, virtualization@lists.linux-foundation.org,
        linux-arm-kernel@lists.infradead.org, linux-hyperv@vger.kernel.org,
        kvm@vger.kernel.org, clang-built-linux@googlegroups.com
Cc: Juergen Gross <jgross@suse.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Jason Baron <jbaron@akamai.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ard Biesheuvel <ardb@kernel.org>, Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        Russell King <linux@armlinux.org.uk>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        Andy Lutomirski <luto@kernel.org>,
        Nathan Chancellor <nathan@kernel.org>,
        Nick Desaulniers <ndesaulniers@google.com>
Subject: [PATCH v6 00/12] x86: major paravirt cleanup
Date: Tue,  9 Mar 2021 14:48:01 +0100
Message-Id: <20210309134813.23912-1-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a major cleanup of the paravirt infrastructure aiming at
eliminating all custom code patching via paravirt patching.

This is achieved by using ALTERNATIVE instead, leading to the ability
to give objtool access to the patched in instructions.

In order to remove most of the 32-bit special handling from pvops the
time related operations are switched to use static_call() instead.

At the end of this series all paravirt patching has to do is to
replace indirect calls with direct ones. In a further step this could
be switched to static_call(), too.

Changes in V6:
- switched back to "not" bit in feature value for "not feature"
- other minor comments addressed

Changes in V5:
- patches 1-5 of V4 dropped, as already applied
- new patches 1+3
- fixed patch 2
- split V4 patch 8 into patches 4+5
- use flag byte instead of negative feature bit for "not feature"

Changes in V4:
- fixed several build failures
- removed objtool patch, as objtool patches are in tip now
- added patch 1 for making usage of static_call easier
- even more cleanup

Changes in V3:
- added patches 7 and 12
- addressed all comments

Changes in V2:
- added patches 5-12

Juergen Gross (12):
  static_call: move struct static_call_key definition to
    static_call_types.h
  x86/paravirt: switch time pvops functions to use static_call()
  x86/alternative: drop feature parameter from ALTINSTR_REPLACEMENT()
  x86/alternative: support not-feature
  x86/alternative: support ALTERNATIVE_TERNARY
  x86: add new features for paravirt patching
  x86/paravirt: remove no longer needed 32-bit pvops cruft
  x86/paravirt: simplify paravirt macros
  x86/paravirt: switch iret pvops to ALTERNATIVE
  x86/paravirt: add new macros PVOP_ALT* supporting pvops in
    ALTERNATIVEs
  x86/paravirt: switch functions with custom code to ALTERNATIVE
  x86/paravirt: have only one paravirt patch function

 arch/arm/include/asm/paravirt.h         |  14 +-
 arch/arm/kernel/paravirt.c              |   9 +-
 arch/arm64/include/asm/paravirt.h       |  14 +-
 arch/arm64/kernel/paravirt.c            |  13 +-
 arch/x86/Kconfig                        |   1 +
 arch/x86/entry/entry_32.S               |   4 +-
 arch/x86/entry/entry_64.S               |   2 +-
 arch/x86/include/asm/alternative-asm.h  |   7 +
 arch/x86/include/asm/alternative.h      |  23 ++-
 arch/x86/include/asm/cpufeatures.h      |   2 +
 arch/x86/include/asm/irqflags.h         |   7 +-
 arch/x86/include/asm/mshyperv.h         |   2 +-
 arch/x86/include/asm/paravirt.h         | 169 +++++++++----------
 arch/x86/include/asm/paravirt_types.h   | 210 +++++++++---------------
 arch/x86/kernel/Makefile                |   3 +-
 arch/x86/kernel/alternative.c           |  51 +++++-
 arch/x86/kernel/asm-offsets.c           |   7 -
 arch/x86/kernel/cpu/vmware.c            |   5 +-
 arch/x86/kernel/kvm.c                   |   2 +-
 arch/x86/kernel/kvmclock.c              |   2 +-
 arch/x86/kernel/paravirt-spinlocks.c    |   9 +
 arch/x86/kernel/paravirt.c              |  78 +++------
 arch/x86/kernel/paravirt_patch.c        |  99 -----------
 arch/x86/kernel/tsc.c                   |   2 +-
 arch/x86/xen/enlighten_pv.c             |   4 +-
 arch/x86/xen/time.c                     |  26 +--
 drivers/xen/time.c                      |   3 +-
 include/linux/static_call.h             |  18 --
 include/linux/static_call_types.h       |  18 ++
 tools/include/linux/static_call_types.h |  18 ++
 30 files changed, 348 insertions(+), 474 deletions(-)
 delete mode 100644 arch/x86/kernel/paravirt_patch.c
```
#### [PATCH 00/10] Embed struct vfio_device in all sub-structures
##### From: Jason Gunthorpe <jgg@nvidia.com>

```c
From patchwork Tue Mar  9 21:38:42 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Gunthorpe <jgg@nvidia.com>
X-Patchwork-Id: 12126577
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,
	SPF_HELO_NONE,SPF_PASS autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6C53AC433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 21:39:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2B1F064FC1
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 21:39:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232058AbhCIVjI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 16:39:08 -0500
Received: from mail-bn7nam10on2073.outbound.protection.outlook.com
 ([40.107.92.73]:49607
        "EHLO NAM10-BN7-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S230431AbhCIVi4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 16:38:56 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=UHYN5mF7FZfyFZG/+LRO3BaG1LYrGaDhUzh9Alo+zhVgRlRnUpqpsCd3MKrooDKb8sfbyVYjvTwitSRng7JzAP3dbtgUMfS/FyAHciUTEGHIK+rWeoomi+5haQFhPavlAvMnrK7afB0jZqJcYIVtC85iuWGlyk995oWwp+v+1G4/00G9qJu98ic44KxY4um81qbou3Mr9FrLJQoeyGISVSlnREnHe8IlgZ73Yg8Mu7bByXNaM2EP8TGWeNw2rGpuxwUpAkY5f/2yJysSOwTb5XXUQBPJzEjmaufD7YZsOWTC5xitSmw2FlGJeYFuK5w3s57neD9OuMcQ+VnIOk3vGg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=YzO1HoWcWYLHOh5BqYaziAqD9AYJklgyYuoiNGMSn58=;
 b=PZIaWp1zeulCVfaWjTUHVH8n/uD8+AQZc9J/DeA7CDgduAuSbX5HrhuYJDh0MHnYXSYPNZvsyRXh+ueemh+ebNllIzBuQZluqnEoKp73rSujXs7nldSqnoWRYg9vrnOGcZhGYxCvBCoaZ72i0aqFNNKFlBpdD+/Y4oyPJB93lKHQeTZd4LGssqw2lCegjqJswTgYtlcT+/aO/PwJWvBF2ny6kDLJQziS1cS1Y0P5ykHMtNg6mtutXwdK1+0pkzZOJ2z4iSW+xxq22CmriwQgGyp46B6QPJRTD7ZJwQHSaw4mlGZrFBZZ+D7QXNa7+jFbtG/pukBIJTCzYgrUviW7Ug==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=nvidia.com; dmarc=pass action=none header.from=nvidia.com;
 dkim=pass header.d=nvidia.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=Nvidia.com;
 s=selector2;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=YzO1HoWcWYLHOh5BqYaziAqD9AYJklgyYuoiNGMSn58=;
 b=nLWNu+MOoeWR2EvmPf1jUcvox/AF7UZRmdkRNO51xgDsAU4AccmYef1RUaqPmncZ2hAtnaTZAnYlp8FzMLT2YCuVBV2jtZaXp1U62VkAiUE4YrR0u/81aaqLoGnpkYjjzwa6vWV0cz+AesIRzTGFoyCY/Z46B+fTU0b9djRCBjhOxl87W9QakpNbkvnTbUgc+3nWe/kYbTQE7p734G7f90lPVvv1Awf9/AVCpea94HKr8CEwj2ffoVvraXjSSu0io6aj9sD58QJCXMJeAZ8X2w5OTzUCd9QFyMBgaEccuKlHIx8oboG50mLgJ43RSWskp3dasE3cqAWlUCcUjT3MRQ==
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=nvidia.com;
Received: from DM6PR12MB3834.namprd12.prod.outlook.com (2603:10b6:5:14a::12)
 by DM5PR1201MB2489.namprd12.prod.outlook.com (2603:10b6:3:e2::22) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.17; Tue, 9 Mar
 2021 21:38:54 +0000
Received: from DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87]) by DM6PR12MB3834.namprd12.prod.outlook.com
 ([fe80::1c62:7fa3:617b:ab87%6]) with mapi id 15.20.3912.027; Tue, 9 Mar 2021
 21:38:54 +0000
From: Jason Gunthorpe <jgg@nvidia.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Diana Craciun <diana.craciun@oss.nxp.com>,
        Eric Auger <eric.auger@redhat.com>, kvm@vger.kernel.org,
        Kirti Wankhede <kwankhede@nvidia.com>,
        linux-doc@vger.kernel.org
Cc: "Raj, Ashok" <ashok.raj@intel.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Daniel Vetter <daniel@ffwll.ch>,
        Christoph Hellwig <hch@lst.de>,
        Leon Romanovsky <leonro@nvidia.com>,
        Max Gurtovoy <mgurtovoy@nvidia.com>,
        Tarun Gupta <targupta@nvidia.com>
Subject: [PATCH 00/10] Embed struct vfio_device in all sub-structures
Date: Tue,  9 Mar 2021 17:38:42 -0400
Message-Id: <0-v1-7355d38b9344+17481-vfio1_jgg@nvidia.com>
X-Originating-IP: [142.162.115.133]
X-ClientProxiedBy: MN2PR20CA0033.namprd20.prod.outlook.com
 (2603:10b6:208:e8::46) To DM6PR12MB3834.namprd12.prod.outlook.com
 (2603:10b6:5:14a::12)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from mlx.ziepe.ca (142.162.115.133) by
 MN2PR20CA0033.namprd20.prod.outlook.com (2603:10b6:208:e8::46) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3912.17 via Frontend
 Transport; Tue, 9 Mar 2021 21:38:53 +0000
Received: from jgg by mlx with local (Exim 4.94)        (envelope-from
 <jgg@nvidia.com>)        id 1lJk44-00AVIX-Kw; Tue, 09 Mar 2021 17:38:52 -0400
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: df06cb74-fbf7-40c8-c8a7-08d8e343bc91
X-MS-TrafficTypeDiagnostic: DM5PR1201MB2489:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR1201MB2489259CF95816D3EE18BCB4C2929@DM5PR1201MB2489.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 XZwURbBFeEkxCBj2glIwOuB50LckcjUveT3k7MPHokhAnfIJaXhnqPEDXTQsg3GXKaNZQOGPjcUXv5dw7EgQMiy+vtprU9lCMTzj1Aeqx28vFJsJbCcIsB29hn+huXg9ERPFtYiScGN93tOd/iOuUZIOVrjr07WsAITyaJuspC5J8/vpB0cyvoyS553JbeuWDO7Xfd/9YskGCRpzFKGdfEGqgj4Lq5aApd3z/C15SnonEukGVuugFaf6OQ+mNhN1FxRHusE4jDhHN9PEue1rwFadCulaHTS9kj0Z4dRcif1hlvFh31a0/RLvXwmMjATPO/G5vjJgbJQnQMtzmdq+OIA9CLY9Yhvqcq3ewKpQSV9JSIzMcYncnvW9dEStTJ3GydS58Shis8Gz97EJnzPzkcLzVE2QzYwOZde6FNyb5/IA+9ALss5w850yKn+Bu3X0lmCyvFB03OF1ZVWwcFNnX2TYxKisJPCH1F8+vCD2K+blGqOZbuvy8p7He1U/bHQKBYpBFCoO6s/AN2R1/17DYVL9JoXOECEtPM9flQOD7BGIwb3dzsRSX3xkZcUH/9udiPtuDw0ANgwF7hkYZz5OpsDgFVeYmgEudl5sFX1FAJvGqCXCcns5C+abCpXLha6rCyIMJPex32OjQXDY6lyBWg==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM6PR12MB3834.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(136003)(346002)(376002)(39860400002)(396003)(366004)(6666004)(966005)(26005)(36756003)(316002)(5660300002)(4326008)(478600001)(7416002)(54906003)(110136005)(9746002)(426003)(66556008)(66476007)(2616005)(9786002)(8936002)(86362001)(186003)(2906002)(8676002)(107886003)(83380400001)(66946007)(4216001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 G+lmDpOrsaEaur0Udf8na+GDK2sOHF8F44Tt+j/btquvyYT5vbgSlv00xrL2KijZL7z48YSM0bGY/NYhLbd+kI8SbBl7b1C7zTw4n2HgfwFAwOO7tvW7CJZ+6/0WWLzDbcNkihHd1mWWrrv3u0vVpL8NHVnc8lbDlMNGPnHustgaMJEZOiXbqIr3SWU33YtFSlqIdGHaOqmS6pwS/SbpTpwlM40/mygGtLzy/DkVALZfavhhcoLWyR9DckcObUsf6x1VvWgXwKu8XYLbOp5jdCs6exc+zbm0ddrfbg0X+mw++Am6WSt5fZ+X0cLTNZjyG5VGhDEDavuhqfIwGNn+eU82Yfu4PYuCRWop6CoRuSMmGzMNdIELiEtYhDHS/IzAfv74X7X7jY+WpaTsUo6TM2z7RMTONxUTK4bqNuDRPFUP3UW+kHBF9W29/SLaDPzlwdhaz5mkvV3T7RlcarBLLi+gdiiHP5nxSw2bK1kp6gkg/vDnSne+4hhPJ9y6Ou6FUT4P4fRF7C0f4at/wRCCgsSiKliLYt6XUBMpB6aD1MMAgoMsbOfq6janJKY7UjgRmS/dvzfjemhOVp1n9GX8IVjji46S4TnnXBJHAEMnEICMyzHCdv5yNkRWdmSYdgskPdLseeO4ENk/iofzYn13J6r01x3eVyAovQeKYsG6FVUnzwdrjmsdaNGCWBGh4P+4D7p+uQVNFIHV349WxXU4CHJdbE/qz05AWQixfbBobPCFapICinV1JKIplHD8wJbFmwzz+FmYWBlOXb7miCkgJG9uZ0KS71YJnbS0ssuOqqd3IsxOOa4ZuztbrrMoR6+EGSea2y0f3jQcT0Oo4Fx7Df/K9rmSAU+NE5SLi70oJzpEg2gqiCuvoyCNgI5ce/bwAn6FiMGwRsEo3BrVrX91kKNO9P0KkFo73aslG7dhLQiH7TSvDSIXzzBTmcU+/XQqgQjZ7DnOZACey+qa64mk9f/A7fANBncxLbnAPUjS+4Zx3EL9IkZtX2J6ElG2MJzRaImw9rv1oXOFEEIP3HCQSbmOUgenCghnqePpJRTX+D7hJGl1ihCrQ9t+ZQaQoCABZMcKZgNq8D/SwO/1pt/5wgI4JrLxdN7L/oNYrW3TmfXUIOa+p73ugJHjZF3y1W0LFOHiuasxsOwyRKFmE4JKG11E24pptRvfpW1MZ1em7DYvcF9yW9ug1PskVyaoKiH8WRYUuERd+eHU7hVYc3LADWXMSbtrTChuWPo9/eWwqdNqxozPuDXwJCFdsnkEdrwJg3VEAPP4yjrpdxNxgthI27d2eNH8fsuY4ZQB18hMTLQI3PmyJNFUpnmXTa4paIc1D5iCJOTh6XdkxDfwUin7Gw==
X-OriginatorOrg: Nvidia.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 df06cb74-fbf7-40c8-c8a7-08d8e343bc91
X-MS-Exchange-CrossTenant-AuthSource: DM6PR12MB3834.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 09 Mar 2021 21:38:54.1738
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 43083d15-7273-40c1-b7db-39efd9ccc17a
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 IvtegaQSwyzPcXk6v3WAqFrhLdAJj8YEBMYCn3f6skj7bmdQLCkOnQuYTdclKnfr
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR1201MB2489
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Prologue
========

This series is part of a larger work that arose from the minor remark that
the mdev_parent_ops indirection shim is useless and complicates
things.

The entire project is about 70 patches broken into 5 subseries, each on a
theme:

#1 - (this series) Add type safety to the core VFIO
#2 - Add type safety to MDEV

  The mdev transformation is involved, compiler assistance through actual
  static type checking makes the transformation much more reliable, thus
  the first two steps add most of the missing types.

#3 - Make all mdev drivers register directly with the core code,
     delete vfio_mdev.c

#4 - Various minor tidies that arise from the above three series

#5 - Complete type annotations and remove unused code

A preview of the future series's is here:
  https://github.com/jgunthorpe/linux/pull/3/commits

It turns out a bunch of stuff exists in the way it does because the
'struct vfio_device' was not obviously available in places that naturally
wanted it. Across the project the following APIs are deleted as reorg
removes all the users:

   mdev_uuid()
   mdev_dev()
   mdev_get_drvdata()
   mdev_set_drvdata()
   struct mdev_parent_ops
   vfio_iommu_group_get()
   vfio_iommu_group_put(),
   vfio_group_get_external_user_from_dev()
   vfio_group_pin_pages()
   vfio_group_unpin_pages()
   vfio_group_get()
   vfio_device_data()

The remaining vfio_device related APIs in mdev.h and vfio.h have correct,
specific, types instead of 'void *' or 'struct device *'.

This work is related to, but seperate from, Max's series to split
vfio_pci. When layered on this vfio_pci_core will use a similiar
container_of scheme and layer the ultimate end-driver with container_of
all the way back to a vfio_device. Types are explicit and natural to
understand through all the layers.

Further mdev and pci get a similiar design with a set of core code
supporting normal 'struct device_driver's that directly create
vfio_device's.

In essence vfio becomes close to a normal driver subsystem pattern with a
bunch of device drivers creating vfio_devices'

========
This series:

The main focus of this series is to make VFIO follow the normal kernel
convention of structure embedding for structure inheritance instead of
linking using a 'void *opaque'. Here we focus on moving the vfio_device to
be a member of every struct vfio_XX_device that is linked by a
vfio_add_group_dev().

In turn this allows 'struct vfio_device *' to be used everwhere, and the
public API out of vfio.c can be cleaned to remove places using 'struct
device *' and 'void *' as surrogates to refer to the device.

While this has the minor trade off of moving 'struct vfio_device' the
clarity of the design is worth it. I can speak directly to this idea, as
I've invested a fair amount of time carefully working backwards what all
the type-erased APIs are supposed to be and it is certainly not trivial or
intuitive.

When we get into mdev land things become even more inscrutable, and while
I now have a pretty clear picture, it was hard to obtain. I think this
agrees with the kernel style ideal of being explicit in typing and not
sacrificing clarity to create opaque structs.

After this series the general rules are:
 - Any vfio_XX_device * can be obtained at no cost from a vfio_device *
   using container_of(), and the reverse is possible by &XXdev->vdev

   This is similar to how 'struct pci_device' and 'struct device' are
   interrelated.

   This allows 'device_data' to be completely removed from the vfio.c API.

 - The drvdata for a struct device points at the vfio_XX_device that
   belongs to the driver that was probed. drvdata is removed from the core
   code, and only used as part of the implementation of the struct
   device_driver.

 - The lifetime of vfio_XX_device and vfio_device are identical, they are
   the same memory.

   This follows the existing model where vfio_del_group_dev() blocks until
   all vfio_device_put()'s are completed. This in turn means the struct
   device_driver remove() blocks, and thus under the driver_lock() a bound
   driver must have a valid drvdata pointing at both vfio device
   structs. A following series exploits this further.

Most vfio_XX_device structs have data that duplicates the 'struct
device *dev' member of vfio_device, a following series removes that
duplication too.

Jason

Jason Gunthorpe (10):
  vfio: Simplify the lifetime logic for vfio_device
  vfio: Split creation of a vfio_device into init and register ops
  vfio/platform: Use vfio_init/register/unregister_group_dev
  vfio/fsl-mc: Use vfio_init/register/unregister_group_dev
  vfio/pci: Use vfio_init/register/unregister_group_dev
  vfio/mdev: Use vfio_init/register/unregister_group_dev
  vfio/mdev: Make to_mdev_device() into a static inline
  vfio: Make vfio_device_ops pass a 'struct vfio_device *' instead of
    'void *'
  vfio/pci: Replace uses of vfio_device_data() with container_of
  vfio: Remove device_data from the vfio bus driver API

 Documentation/driver-api/vfio.rst             |  48 ++--
 drivers/vfio/fsl-mc/vfio_fsl_mc.c             |  69 +++---
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h     |   1 +
 drivers/vfio/mdev/mdev_private.h              |   5 +-
 drivers/vfio/mdev/vfio_mdev.c                 |  57 +++--
 drivers/vfio/pci/vfio_pci.c                   | 109 +++++----
 drivers/vfio/pci/vfio_pci_private.h           |   1 +
 drivers/vfio/platform/vfio_amba.c             |   8 +-
 drivers/vfio/platform/vfio_platform.c         |  21 +-
 drivers/vfio/platform/vfio_platform_common.c  |  56 ++---
 drivers/vfio/platform/vfio_platform_private.h |   5 +-
 drivers/vfio/vfio.c                           | 210 ++++++------------
 include/linux/vfio.h                          |  37 +--
 13 files changed, 299 insertions(+), 328 deletions(-)
```
#### [PATCH v2 0/4] KVM: x86: Fixups and PAE+SME fixes
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Tue Mar  9 22:42:03 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12126683
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 96AECC433DB
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 22:43:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6119B6513E
	for <kvm@archiver.kernel.org>; Tue,  9 Mar 2021 22:43:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232117AbhCIWmb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 9 Mar 2021 17:42:31 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:52874 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231231AbhCIWmO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 9 Mar 2021 17:42:14 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 87DE1C06174A
        for <kvm@vger.kernel.org>; Tue,  9 Mar 2021 14:42:14 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id b127so18938692ybc.13
        for <kvm@vger.kernel.org>; Tue, 09 Mar 2021 14:42:14 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=7aKMO2SpBi/2Jz5ddHg49VoZBghMh9FLvFL9AICAYkg=;
        b=HqQeKzbp5rUdScMKxM5d8PuM/rJvjSiWPy0g9UPtNBCZwfsKdi69aYTzYIb1/qfg4C
         /a5CaBtfkCxqwZxJrA9EGSil4/G7r/ODBT2YTsZqWQRRgWj0MMW1JDs/UqyjfLWfB2CP
         ZsHcq2s6a8CWilWWBOn8IiaIoySs8PofJLR23ejm+emMMkzpqx5Xr+GNbXYFgej8n6fq
         9weleJ3jdffP0YIv98g/Ts3a3O635s85Rc3T2fg1z0NY9wfK55LdHtYatRdvh679sqZz
         RMrcVaswESabOtP0DaN5bceak8Jrp2sGZ1/w5A9aiH8tKBZuwShzHpCZTepgoI50nRB8
         WuDg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=7aKMO2SpBi/2Jz5ddHg49VoZBghMh9FLvFL9AICAYkg=;
        b=N9NfYFechwBn/7DcVV7Hzn28ejcFKwoJxPw2Zu0Mgd6SpngS4q/Z3tZGFR61ArkKm2
         88SnJnTSHvYf7OMc8J3k9/wCZFr/TuPsvEB6ydrmgloliXGKD6+31xdioWCbHGsOikkU
         nMD8U3JgRtLqc9hv0uYNlMVWzeTAOl1mHf9AXdAs14L5XOhEMn+XGlKcmFBBYnkBZRH6
         RgdzvY82UBYqEAG/Ugsd3z2+GlDbA+4FrlKKqwqSrTGNSyTJJBefUhMtv5pzM4opVdrN
         F7IQy49AsCV2mTYmm/jpDj9NfvphFudH8KaJjcsYs4SwQcb7UEQOGB6yiHcT+TEf34gL
         ienw==
X-Gm-Message-State: AOAM531Gtb8MUIqcbzG5M6/pDboiPdlJbsXTKPIaw1+a2ePZUaCYTxDd
        NgfPmM2ueN7n69msMA0H7hKpOzn1CQE=
X-Google-Smtp-Source: 
 ABdhPJx3sXyVswQOYX3CiUvIyjRJH0JBj2aUh6zpV8P1spFgKD9Bxb6y2Vr+NUvEN0oDWXlJkM4KFFuYlR4=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:e4dd:6c31:9463:f8da])
 (user=seanjc job=sendgmr) by 2002:a25:4dc4:: with SMTP id
 a187mr162417ybb.78.1615329733767;
 Tue, 09 Mar 2021 14:42:13 -0800 (PST)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Tue,  9 Mar 2021 14:42:03 -0800
Message-Id: <20210309224207.1218275-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.1.766.gb4fecdf3b7-goog
Subject: [PATCH v2 0/4] KVM: x86: Fixups and PAE+SME fixes
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        Brijesh Singh <brijesh.singh@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A few stragglers bundled together to hopefully avoid more messy conflicts.

v2 (relative to the fixup mini-series):
  - Moved SME fixes from "PCID fixup" to its correct location, in "Mark
    PAE roots decrypted".
  - Collected Reviewed/Tested-by tags for MMU_PRESENT+MMIO snafu, though
    I expect they'll get squashed away.
  - Added the PAE patches from the SME shadow paging fixes to avoid
    spreading out the dependencies.

Sean Christopherson (4):
  KVM: x86: Fixup "Get active PCID only when writing a CR3 value"
  KVM: x86/mmu: Exclude the MMU_PRESENT bit from MMIO SPTE's generation
  KVM: x86/mmu: Use '0' as the one and only value for an invalid PAE
    root
  KVM: x86/mmu: Mark the PAE roots as decrypted for shadow paging

 arch/x86/kvm/mmu/mmu.c          | 46 ++++++++++++++++++++++++---------
 arch/x86/kvm/mmu/mmu_audit.c    |  2 +-
 arch/x86/kvm/mmu/mmu_internal.h | 10 +++++++
 arch/x86/kvm/mmu/spte.h         | 12 +++++----
 arch/x86/kvm/svm/svm.c          |  9 +++++--
 5 files changed, 59 insertions(+), 20 deletions(-)
```
