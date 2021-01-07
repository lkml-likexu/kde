

#### [PATCH v4 00/16] KVM: Add minimal support for Xen HVM guests
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Wed Jan  6 00:22:58 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 12000613
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E0CCCC433E0
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 00:25:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ADC1B22D74
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 00:25:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726677AbhAFAZS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 19:25:18 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37464 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726328AbhAFAZS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 19:25:18 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 0E7DDC061793
        for <kvm@vger.kernel.org>; Tue,  5 Jan 2021 16:24:38 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        Content-Type:MIME-Version:Message-Id:Date:Subject:Cc:To:From:Reply-To:
        Content-ID:Content-Description:In-Reply-To:References;
        bh=lUen2KjqNOUACjCPDLFaUqf5FgyBXKrzDGaKMoO5pmc=;
 b=VabqpZ0ruiaudFJShhhwk1GTKU
        Dh/VPUyT5mlIJz9hQbREN09xitjt2fKL8eAGQzQXEGCgqJuz4RpdUD7L/lzOn5job2YDYGnxWkcB7
        kn8Sgq0Q7EGh4R64zALZF58ZJtOpfujScDHE2Bme03L0b0u0VLHTSniGHTFx9Iv4YNPVcW/OMnfvu
        qF8871U45c3CzIG8TyHPX8roAAtCfvvoaVV0fBdgGkEd6jGQytJHYjcNG7MMPoricC6pjnXt/fAv7
        XCZgP1bukeko4r5+BCxjEsRK38HE6QA5W6IP50WGkbSQysE6n81LLfd2yz48/mbxWBsK8QeUMdvxc
        wMPoyEVw==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.94 #2 (Red Hat Linux))
        id 1kwwbh-001pA3-L9; Wed, 06 Jan 2021 00:23:36 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1kwwbh-001Nil-8o; Wed, 06 Jan 2021 00:23:21 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>, graf@amazon.com,
        iaslan@amazon.de, pdurrant@amazon.com, aagch@amazon.com,
        fandree@amazon.com, hch@infradead.org
Subject: [PATCH v4 00/16] KVM: Add minimal support for Xen HVM guests
Date: Wed,  6 Jan 2021 00:22:58 +0000
Message-Id: <20210106002314.328380-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.29.2
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch set provides enough kernel support to allow hosting Xen HVM 
guests in KVM. It allows hypercalls to be trapped to userspace for 
handling, uses the existing KVM functions for writing system clock and 
pvclock information to Xen shared pages, and adds Xen runstate info and 
event channel upcall vector delivery.

It's based on the first section of a patch set that Joao posted as 
RFC last year^W^W in 2019:

https://lore.kernel.org/kvm/20190220201609.28290-1-joao.m.martins@oracle.com/

I've updated and reworked the original a bit, including (in my v1):
 • Support for 32-bit guests
 • 64-bit second support in wallclock
 • Time counters for runnable/blocked states in runstate support
 • Self-tests
 • Fixed Viridian coexistence
 • No new KVM_CAP_XEN_xxx, just more bits returned by KVM_CAP_XEN_HVM

v2: 
 • Remember the RCU read-critical sections on using the shared info pages
 • Fix 32-bit build of compat structures (which we use there too)
 • Use RUNSTATE_blocked as initial state not RUNSTATE_runnable
 • Include documentation, add cosmetic KVM_XEN_HVM_CONFIG_HYPERCALL_MSR

v3:
 • Stop mapping the shared pages; use kvm_guest_write_cached() instead.
 • Use kvm_setup_pvclock_page() for Xen pvclock writes too.
 • Fix CPU numbering confusion and update documentation accordingly.
 • Support HVMIRQ_callback_vector delivery based on evtchn_upcall_pending.

v4:
 • Rebase on top of the KVM changes merged into 5.11-rc1.
 • Drop the kvm_{un,}map_gfn() cleanup as it isn't used since v2 anyway.
 • Trivial cosmetic cleanup (superfluous parens, remove declaration of a
   function removed in v3, etc.)

With the addition in v3 of the callback vector support, we can now 
successfully boot Linux guests. Other callback types can be handled 
entirely from userspace, but the vector injection needs kernel support 
because it doesn't quite work to inject it as ExtINT.

We will work on a little bit more event channel offload in future patches,
as discussed, but those are purely optimisations. There's a bunch of work
for us to do in userspace before those get to the top of our list, and
this patch set should be functionally complete as it is.

We're working on pushing out rust-vmm support to make use of this, and
Joao's qemu patches from last year should still also work with minor
tweaks where I've "improved" the KVM←→userspace ABI.

David Woodhouse (7):
      KVM: x86/xen: Fix coexistence of Xen and Hyper-V hypercalls
      KVM: x86/xen: latch long_mode when hypercall page is set up
      KVM: x86/xen: add definitions of compat_shared_info, compat_vcpu_info
      xen: add wc_sec_hi to struct shared_info
      KVM: x86: declare Xen HVM shared info capability and add test case
      KVM: Add documentation for Xen hypercall and shared_info updates
      KVM: x86/xen: Add event channel interrupt vector upcall

Joao Martins (9):
      KVM: x86/xen: fix Xen hypercall page msr handling
      KVM: x86/xen: intercept xen hypercalls if enabled
      KVM: x86/xen: add KVM_XEN_HVM_SET_ATTR/KVM_XEN_HVM_GET_ATTR
      KVM: x86/xen: register shared_info page
      KVM: x86/xen: update wallclock region
      KVM: x86/xen: register vcpu info
      KVM: x86/xen: setup pvclock updates
      KVM: x86/xen: register vcpu time info region
      KVM: x86/xen: register runstate info

 Documentation/virt/kvm/api.rst                     | 124 +++++-
 arch/x86/include/asm/kvm_host.h                    |  24 +
 arch/x86/include/asm/xen/interface.h               |   3 +
 arch/x86/kvm/Makefile                              |   2 +-
 arch/x86/kvm/hyperv.c                              |  40 +-
 arch/x86/kvm/irq.c                                 |   7 +
 arch/x86/kvm/trace.h                               |  36 ++
 arch/x86/kvm/x86.c                                 | 134 ++++--
 arch/x86/kvm/x86.h                                 |   1 +
 arch/x86/kvm/xen.c                                 | 495 +++++++++++++++++++++
 arch/x86/kvm/xen.h                                 |  68 +++
 include/linux/kvm_host.h                           |  30 +-
 include/uapi/linux/kvm.h                           |  50 +++
 include/xen/interface/xen.h                        |   4 +-
 tools/testing/selftests/kvm/Makefile               |   3 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |   1 +
 .../testing/selftests/kvm/x86_64/xen_shinfo_test.c | 194 ++++++++
 .../testing/selftests/kvm/x86_64/xen_vmcall_test.c | 150 +++++++
 18 files changed, 1288 insertions(+), 78 deletions(-)
```
#### [RFC PATCH 00/23] KVM SGX virtualization support
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Wed Jan  6 01:55:06 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12000757
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F0BF3C433DB
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 01:56:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AD4AA22CE3
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 01:56:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725919AbhAFB4C (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 5 Jan 2021 20:56:02 -0500
Received: from mga04.intel.com ([192.55.52.120]:11738 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725862AbhAFB4B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 5 Jan 2021 20:56:01 -0500
IronPort-SDR: 
 tSWTvbMIEd7IXNtfbIg5mUP+LLoxk7SqqmODszkEzc75EYdNSkeAwiTFvGLJz1nYFFGkSYz/tR
 GZUn/VGnrRQg==
X-IronPort-AV: E=McAfee;i="6000,8403,9855"; a="174636823"
X-IronPort-AV: E=Sophos;i="5.78,478,1599548400";
   d="scan'208";a="174636823"
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga104.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jan 2021 17:55:21 -0800
IronPort-SDR: 
 oVDvdbwTVC8/bptezjwLna1QIU5aVJi/ApOV4BGJBGeMlpSxcik3nc+xCIfx6fl7hvoN2RqgL5
 dbLk01ITvPJQ==
X-IronPort-AV: E=Sophos;i="5.78,478,1599548400";
   d="scan'208";a="421993073"
Received: from zhuoxuan-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.251.29.237])
  by orsmga001-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 Jan 2021 17:55:17 -0800
From: Kai Huang <kai.huang@intel.com>
To: linux-sgx@vger.kernel.org, kvm@vger.kernel.org, x86@kernel.org
Cc: seanjc@google.com, jarkko@kernel.org, luto@kernel.org,
        dave.hansen@intel.com, haitao.huang@intel.com, pbonzini@redhat.com,
        bp@alien8.de, tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        jethro@fortanix.com, b.thiel@posteo.de, mattson@google.com,
        joro@8bytes.org, vkuznets@redhat.com, wanpengli@tencent.com,
        corbet@lwn.net
Subject: [RFC PATCH 00/23] KVM SGX virtualization support
Date: Wed,  6 Jan 2021 14:55:06 +1300
Message-Id: <cover.1609890536.git.kai.huang@intel.com>
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

This series adds KVM SGX virtualization support. The first 12 patches starting
with x86/sgx or x86/cpu.. are necessary changes to x86 and SGX core/driver to
support KVM SGX virtualization, while the rest are patches to KVM subsystem.

Please help to review this series. Also I'd like to hear what is the proper
way to merge this series, since it contains change to both x86/SGX and KVM
subsystem. Any feedback is highly appreciated. And please let me know if I
forgot to CC anyone, or anyone wants to be removed from CC. Thanks in advance!

This series is based against latest tip tree's x86/sgx branch. You can also get
the code from tip branch of kvm-sgx repo on github:

        https://github.com/intel/kvm-sgx.git tip

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
KVM SGX virtualization Overview

- Virtual EPC

"Virtual EPC" is the EPC section exposed by KVM to guest so SGX software in
guest can discover it and use it to create SGX enclaves. KVM exposes SGX to 
guest via CPUID, and exposes one or more "virtual EPC" sections for guest.
The size of "virtual EPC" is passed as Qemu parameter when creating the
guest, and the base address is calcualted internally according to guest's
configuration.

To support virtual EPC, add a new misc device /dev/sgx_virt_epc to SGX
core/driver to allow userspace (Qemu) to allocate "raw" EPC, and use it as
"virtual EPC" for guest. Obviously, unlike EPC allocated for host SGX driver,
virtual EPC allocated via /dev/sgx_virt_epc doesn't have enclave associated,
and how virtual EPC is used by guest is compeletely controlled by guest's SGX
software.

Implement the "raw" EPC allocation in the x86 core-SGX subsystem via
/dev/sgx_virt_epc rather than in KVM. Doing so has two major advantages:

  - Does not require changes to KVM's uAPI, e.g. EPC gets handled as
    just another memory backend for guests.

  - EPC management is wholly contained in the SGX subsystem, e.g. SGX
    does not have to export any symbols, changes to reclaim flows don't
    need to be routed through KVM, SGX's dirty laundry doesn't have to
    get aired out for the world to see, and so on and so forth.

The virtual EPC allocated to guests is currently not reclaimable, due to
reclaiming EPC from KVM guests is not currently supported. Due to the
complications of handling reclaim conflicts between guest and host, KVM
EPC oversubscription, which allows total virtual EPC size greater than
physical EPC by being able to reclaiming guests' EPC, is significantly more
complex than basic support for SGX virtualization.

- Support SGX virtualization without SGX Launch Control unlocked mode

Although SGX driver requires SGX Launch Control unlocked mode to work, SGX
virtualization doesn't, since how enclave is created is completely controlled
by guest SGX software, which is not necessarily linux. Therefore, this series
allows KVM to expose SGX to guest even SGX Launch Control is in locked mode,
or is not present at all. The reason is the goal of SGX virtualization, or
virtualization in general, is to expose hardware feature to guest, but not to
make assumption how guest will use it. Therefore, KVM should support SGX guest
as long as hardware is able to, to have chance to support more potential use
cases in cloud environment.

- Support exposing SGX2

Due to the same reason above, SGX2 feature detection is added to core SGX code
to allow KVM to expose SGX2 to guest, even currently SGX driver doesn't support
SGX2, because SGX2 can work just fine in guest w/o any interaction to host SGX
driver.

- Restricit SGX guest access to provisioning key

To grant guest being able to fully use SGX, guest needs to be able to create
provisioning enclave. However provisioning key is sensitive and is restricted by
/dev/sgx_provision in host SGX driver, therefore KVM SGX virtualization follows
the same role: a new KVM_CAP_SGX_ATTRIBUTE is added to KVM uAPI, and only file
descriptor of /dev/sgx_provision is passed to that CAP by usersppace hypervisor
(Qemu) when creating the guest, it can access provisioning bit. This is done by
making KVM trape ECREATE instruction from guest, and check the provisioning bit
in ECREATE's attribute.


Kai Huang (1):
  x86/sgx: Add helper to update SGX_LEPUBKEYHASHn MSRs

Sean Christopherson (22):
  x86/sgx: Split out adding EPC page to free list to separate helper
  x86/sgx: Add enum for SGX_CHILD_PRESENT error code
  x86/sgx: Introduce virtual EPC for use by KVM guests
  x86/cpufeatures: Add SGX1 and SGX2 sub-features
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
  KVM: x86: Add SGX feature leaf to reverse CPUID lookup
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
 arch/x86/include/asm/cpufeature.h             |   5 +-
 arch/x86/include/asm/cpufeatures.h            |   6 +-
 arch/x86/include/asm/disabled-features.h      |   7 +-
 arch/x86/include/asm/kvm_host.h               |   5 +
 arch/x86/include/asm/required-features.h      |   2 +-
 arch/x86/include/asm/sgx.h                    |  19 +
 .../cpu/sgx/arch.h => include/asm/sgx_arch.h} |  20 +
 arch/x86/include/asm/vmx.h                    |   1 +
 arch/x86/include/uapi/asm/vmx.h               |   1 +
 arch/x86/kernel/cpu/common.c                  |   4 +
 arch/x86/kernel/cpu/feat_ctl.c                |  50 +-
 arch/x86/kernel/cpu/sgx/Makefile              |   1 +
 arch/x86/kernel/cpu/sgx/driver.c              |  17 -
 arch/x86/kernel/cpu/sgx/encl.c                |   2 +-
 arch/x86/kernel/cpu/sgx/encls.h               |  29 +-
 arch/x86/kernel/cpu/sgx/ioctl.c               |  23 +-
 arch/x86/kernel/cpu/sgx/main.c                |  79 ++-
 arch/x86/kernel/cpu/sgx/sgx.h                 |   5 +-
 arch/x86/kernel/cpu/sgx/virt.c                | 318 ++++++++++++
 arch/x86/kernel/cpu/sgx/virt.h                |  14 +
 arch/x86/kvm/Makefile                         |   2 +
 arch/x86/kvm/cpuid.c                          |  58 ++-
 arch/x86/kvm/cpuid.h                          |   1 +
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
 36 files changed, 1366 insertions(+), 139 deletions(-)
 create mode 100644 arch/x86/include/asm/sgx.h
 rename arch/x86/{kernel/cpu/sgx/arch.h => include/asm/sgx_arch.h} (96%)
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.c
 create mode 100644 arch/x86/kernel/cpu/sgx/virt.h
 create mode 100644 arch/x86/kvm/vmx/sgx.c
 create mode 100644 arch/x86/kvm/vmx/sgx.h
```
#### [PATCH 0/6] KVM: nSVM: few random fixes
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Wed Jan  6 10:49:55 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12001331
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 61388C433E0
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 10:52:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 13AC923105
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 10:52:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725868AbhAFKvk (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 6 Jan 2021 05:51:40 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:50938 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725896AbhAFKvj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 Jan 2021 05:51:39 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1609930213;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=kLT4c0oVgoGQ28S7o/zFiab9Iekvo6wVtsgLAAzAA9w=;
        b=dROA8l8vbpcPP/ENQxmQgn2VsNnDehOiutNsk5BC9B/aP95Gh4MPJ2iAkKP4gdk01hqskd
        9MeF0jXJaJsgG1eEVrYvIfzSMhNIH7o3hicFrh08IQY03hcjxmn3iCmJXD7W8r/Z1rxx4/
        gKHehC6biapXkEj/8N80vwnoY3RrC1s=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-382-ViKoHO4uNXW5l6wig8wqkg-1; Wed, 06 Jan 2021 05:50:11 -0500
X-MC-Unique: ViKoHO4uNXW5l6wig8wqkg-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2220D800D55;
        Wed,  6 Jan 2021 10:50:09 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.196])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C2805669FC;
        Wed,  6 Jan 2021 10:50:03 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Wanpeng Li <wanpengli@tencent.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/6] KVM: nSVM: few random fixes
Date: Wed,  6 Jan 2021 12:49:55 +0200
Message-Id: <20210106105001.449974-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a series of fixes to nested SVM, that finally makes my kvm on kvm
stress test pass, and fix various other issues/regressions.

Patches 1-2 are a fix for disappearing interrupts in L2 on migration which
usually make the L2 hang.
Same issue happens on VMX and WIP, patches for this will be sent in a separate
series.
Paulo helped me to find the root cause of this issue.

Note that this patch likely breaks a nested guest that uses software interrupt
injections (SVM_EXITINTINFO_TYPE_SOFT) because currently kvm ignores these
on SVM.

Patch 3 is a fix for recent regression related to code that delayed the nested
msr bitmap processing to the next vm entry, and started to crash the L1 after
my on demand nested state allocation patches.

The problem was that the code assumed that we will still be in the nested
guest mode on next vmentry after setting the nested state, but a pending event
can cause a nested vmexit prior to that.

Patches 4,5,6 are few things I found while reviewing the nested migration code.
I don't have a reproducer for them.

Best regards,
	Maxim Levitsky

Maxim Levitsky (6):
  KVM: SVM: create svm_process_injected_event
  KVM: nSVM: fix for disappearing L1->L2 event injection on L1 migration
  KVM: nSVM: cancel KVM_REQ_GET_NESTED_STATE_PAGES on nested vmexit
  KVM: nSVM: correctly restore nested_run_pending on migration
  KVM: nSVM: always leave the nested state first on KVM_SET_NESTED_STATE
  KVM: nSVM: mark vmcb as dirty when forcingly leaving the guest mode

 arch/x86/kvm/svm/nested.c | 21 ++++++++++++--
 arch/x86/kvm/svm/svm.c    | 58 ++++++++++++++++++++++-----------------
 arch/x86/kvm/svm/svm.h    |  4 +++
 3 files changed, 55 insertions(+), 28 deletions(-)
```
#### [PATCH 0/2] RFC: VMX: fix for disappearing L1->L2 event injection on
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Wed Jan  6 10:53:04 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12001345
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EE50EC433E9
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 10:54:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A17062310E
	for <kvm@archiver.kernel.org>; Wed,  6 Jan 2021 10:54:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726382AbhAFKyu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 6 Jan 2021 05:54:50 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:46842 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725877AbhAFKyu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 6 Jan 2021 05:54:50 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1609930404;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=QaEUzQ6yh8rdW3dVNi86zCFUfCiUJ9L8dDbZnEnAkcY=;
        b=cIH5zkajrbSOBznNjLYzkQbRtD0tdGIT80H1shz/nlQXKzZSJYERuwc8Z7OQcFphbraVYV
        uWIzYUmyONmKYOxnLExjUooI2PzwuOK41EgNpaD4Vz1EZh4gYhWe8kNShH0iVx7CBT3BR7
        aO8kCDuS9lLR6LlhZdj3/s4KZdFNTYY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-442-lyyoWnXsNmOTb6hm22CjDg-1; Wed, 06 Jan 2021 05:53:13 -0500
X-MC-Unique: lyyoWnXsNmOTb6hm22CjDg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 32F0810054FF;
        Wed,  6 Jan 2021 10:53:12 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.196])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 858EC5B4A9;
        Wed,  6 Jan 2021 10:53:08 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Wanpeng Li <wanpengli@tencent.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)),
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Jim Mattson <jmattson@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/2] RFC: VMX: fix for disappearing L1->L2 event injection on
 L1 migration
Date: Wed,  6 Jan 2021 12:53:04 +0200
Message-Id: <20210106105306.450602-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is VMX version of the same issue as I reproduced on SVM.

Unlike SVM, this version has 2 pending issues to resolve.

1. This seems to break 'vmx' kvm-unit-test in
'error code <-> (!URG || prot_mode) [+]' case.

The test basically tries to do nested vm entry with unrestricted guest disabled,
real mode, and for some reason that works without patch 2 of this series and it
doesn't cause the #GP to be injected, but with this patch the test complains
about unexpected #GP.
I suspect that this test case is broken, but this has to be investigated.

2. L1 MTF injections are lost since kvm has no notion of them, this is TBD to
be fixed.

This was lightly tested on my nested migration test which no VMX sadly still
crashes and burns on an (likely) unrelated issue.

Best regards,
	Maxim Levitsky

Maxim Levitsky (2):
  KVM: VMX: create vmx_process_injected_event
  KVM: nVMX: fix for disappearing L1->L2 event injection on L1 migration

 arch/x86/kvm/vmx/nested.c | 12 ++++----
 arch/x86/kvm/vmx/vmx.c    | 60 ++++++++++++++++++++++++---------------
 arch/x86/kvm/vmx/vmx.h    |  4 +++
 3 files changed, 47 insertions(+), 29 deletions(-)
```
