#### [PATCH v2 1/9] KVM: arm64: Document PV-time interface
##### From: Steven Price <steven.price@arm.com>

```c
Introduce a paravirtualization interface for KVM/arm64 based on the
"Arm Paravirtualized Time for Arm-Base Systems" specification DEN 0057A.

This only adds the details about "Stolen Time" as the details of "Live
Physical Time" have not been fully agreed.

User space can specify a reserved area of memory for the guest and
inform KVM to populate the memory with information on time that the host
kernel has stolen from the guest.

A hypercall interface is provided for the guest to interrogate the
hypervisor's support for this interface and the location of the shared
memory structures.

Signed-off-by: Steven Price <steven.price@arm.com>
---
 Documentation/virt/kvm/arm/pvtime.txt | 100 ++++++++++++++++++++++++++
 1 file changed, 100 insertions(+)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.txt

diff --git a/Documentation/virt/kvm/arm/pvtime.txt b/Documentation/virt/kvm/arm/pvtime.txt
new file mode 100644
index 000000000000..1ceb118694e7
--- /dev/null
+++ b/Documentation/virt/kvm/arm/pvtime.txt
@@ -0,0 +1,100 @@
+Paravirtualized time support for arm64
+======================================
+
+Arm specification DEN0057/A defined a standard for paravirtualised time
+support for AArch64 guests:
+
+https://developer.arm.com/docs/den0057/a
+
+KVM/arm64 implements the stolen time part of this specification by providing
+some hypervisor service calls to support a paravirtualized guest obtaining a
+view of the amount of time stolen from its execution.
+
+Two new SMCCC compatible hypercalls are defined:
+
+PV_FEATURES 0xC5000020
+PV_TIME_ST  0xC5000022
+
+These are only available in the SMC64/HVC64 calling convention as
+paravirtualized time is not available to 32 bit Arm guests. The existence of
+the PV_FEATURES hypercall should be probed using the SMCCC 1.1 ARCH_FEATURES
+mechanism before calling it.
+
+PV_FEATURES
+    Function ID:  (uint32)  : 0xC5000020
+    PV_func_id:   (uint32)  : Either PV_TIME_LPT or PV_TIME_ST
+    Return value: (int32)   : NOT_SUPPORTED (-1) or SUCCESS (0) if the relevant
+                              PV-time feature is supported by the hypervisor.
+
+PV_TIME_ST
+    Function ID:  (uint32)  : 0xC5000022
+    Return value: (int64)   : IPA of the stolen time data structure for this
+                              (V)CPU. On failure:
+                              NOT_SUPPORTED (-1)
+
+The IPA returned by PV_TIME_ST should be mapped by the guest as normal memory
+with inner and outer write back caching attributes, in the inner shareable
+domain. A total of 16 bytes from the IPA returned are guaranteed to be
+meaningfully filled by the hypervisor (see structure below).
+
+PV_TIME_ST returns the structure for the calling VCPU.
+
+Stolen Time
+-----------
+
+The structure pointed to by the PV_TIME_ST hypercall is as follows:
+
+  Field       | Byte Length | Byte Offset | Description
+  ----------- | ----------- | ----------- | --------------------------
+  Revision    |      4      |      0      | Must be 0 for version 0.1
+  Attributes  |      4      |      4      | Must be 0
+  Stolen time |      8      |      8      | Stolen time in unsigned
+              |             |             | nanoseconds indicating how
+              |             |             | much time this VCPU thread
+              |             |             | was involuntarily not
+              |             |             | running on a physical CPU.
+
+The structure will be updated by the hypervisor prior to scheduling a VCPU. It
+will be present within a reserved region of the normal memory given to the
+guest. The guest should not attempt to write into this memory. There is a
+structure per VCPU of the guest.
+
+User space interface
+====================
+
+User space can request that KVM provide the paravirtualized time interface to
+a guest by creating a KVM_DEV_TYPE_ARM_PV_TIME device, for example:
+
+    struct kvm_create_device pvtime_device = {
+            .type = KVM_DEV_TYPE_ARM_PV_TIME,
+            .attr = 0,
+            .flags = 0,
+    };
+
+    pvtime_fd = ioctl(vm_fd, KVM_CREATE_DEVICE, &pvtime_device);
+
+Creation of the device should be done after creating the vCPUs of the virtual
+machine.
+
+The IPA of the structures must be given to KVM. This is the base address
+of an array of stolen time structures (one for each VCPU). The base address
+must be page aligned. The size must be at least 64 * number of VCPUs and be a
+multiple of PAGE_SIZE.
+
+The memory for these structures should be added to the guest in the usual
+manner (e.g. using KVM_SET_USER_MEMORY_REGION).
+
+For example:
+
+    struct kvm_dev_arm_st_region region = {
+            .gpa = <IPA of guest base address>,
+            .size = <size in bytes>
+    };
+
+    struct kvm_device_attr st_base = {
+            .group = KVM_DEV_ARM_PV_TIME_PADDR,
+            .attr = KVM_DEV_ARM_PV_TIME_ST,
+            .addr = (u64)&region
+    };
+
+    ioctl(pvtime_fd, KVM_SET_DEVICE_ATTR, &st_base);

From patchwork Mon Aug 19 14:04:29 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11101051
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 78E4113A0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 19 Aug 2019 14:04:52 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 6719728823
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 19 Aug 2019 14:04:52 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 5553A28868; Mon, 19 Aug 2019 14:04:52 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 878EF2886F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 19 Aug 2019 14:04:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727329AbfHSOEu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 19 Aug 2019 10:04:50 -0400
Received: from foss.arm.com ([217.140.110.172]:54938 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727252AbfHSOEt (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Aug 2019 10:04:49 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 90980360;
        Mon, 19 Aug 2019 07:04:48 -0700 (PDT)
Received: from e112269-lin.arm.com (e112269-lin.cambridge.arm.com
 [10.1.196.133])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 5953F3F718;
        Mon, 19 Aug 2019 07:04:46 -0700 (PDT)
From: Steven Price <steven.price@arm.com>
To: Marc Zyngier <maz@kernel.org>, Will Deacon <will@kernel.org>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu
Cc: Steven Price <steven.price@arm.com>,
 Catalin Marinas <catalin.marinas@arm.com>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Russell King <linux@armlinux.org.uk>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Pouloze <suzuki.poulose@arm.com>,
 Mark Rutland <mark.rutland@arm.com>, kvm@vger.kernel.org,
 linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
 Christoffer Dall <christoffer.dall@arm.com>
Subject: [PATCH v2 2/9] KVM: arm/arm64: Factor out hypercall handling from
 PSCI code
Date: Mon, 19 Aug 2019 15:04:29 +0100
Message-Id: <20190819140436.12207-3-steven.price@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190819140436.12207-1-steven.price@arm.com>
References: <20190819140436.12207-1-steven.price@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

From: Christoffer Dall <christoffer.dall@arm.com>

We currently intertwine the KVM PSCI implementation with the general
dispatch of hypercall handling, which makes perfect sense because PSCI
is the only category of hypercalls we support.

However, as we are about to support additional hypercalls, factor out
this functionality into a separate hypercall handler file.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
[steven.price@arm.com: rebased]
Signed-off-by: Steven Price <steven.price@arm.com>
---
 arch/arm/kvm/Makefile        |  2 +-
 arch/arm/kvm/handle_exit.c   |  2 +-
 arch/arm64/kvm/Makefile      |  1 +
 arch/arm64/kvm/handle_exit.c |  4 +-
 include/kvm/arm_hypercalls.h | 43 ++++++++++++++++++
 include/kvm/arm_psci.h       |  2 +-
 virt/kvm/arm/hypercalls.c    | 59 +++++++++++++++++++++++++
 virt/kvm/arm/psci.c          | 84 +-----------------------------------
 8 files changed, 110 insertions(+), 87 deletions(-)
 create mode 100644 include/kvm/arm_hypercalls.h
 create mode 100644 virt/kvm/arm/hypercalls.c

```
#### [PATCH ARM] selftests, arm64: fix uninitialized symbol in tags_test.cFrom: Andrey Konovalov <andreyknvl@google.com>
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
Fix tagged_ptr not being initialized when TBI is not enabled.

Dan Carpenter <dan.carpenter@oracle.com>
Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
---
 tools/testing/selftests/arm64/tags_test.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH kernel] KVM: PPC: vfio/spapr_tce: Split out TCE invalidation from TCE updates
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
The VFIO IOMMU implementation on SPAPR uses iommu_table::exchange() hook
to update hardware TCE tables (a table where an index is a IOBA>>pageshift
and the value is a host physical address). Each TCE update requires
TCE cache invalidation, both at the PHB and NPU levels. The invalidation
interface allows invalidation of 1) a single TCE, 2) all TCEs belonging
to a specific IOMMU group (or "PE"), 3) entire cache. The invalidation
is implemented in the host system firmware (skiboot) via an OPAL call and
writes to the registers called "TCE Kill" (hence the naming).

At the moment iommu_tce_xchg() is the only interface to
update-and-invalidate a TCE, i.e. we call OPAL for each TCE update.
This is not a problem for relatively small guests (32GB guest takes
less than 2s to map everything into the huge window) but it is for
bigger guests. It gets worse with GPU+NVLinks as NPU (a hardware bit
implementing NVLinks) needs its own TCE cache to be invalidated.

To map a 100GB guest with 1 GPU + 2xNVLinks, a loop over the guest RAM
takes 20s where 10s and 9s go to NPU and PHB TCE cache invalidation.
This is that slow because:
1) we call OPAL for every TCE entry;
2) invalidating many TCEs takes longer than flushing the entire TCE cache.

This implements iommu_tce_kill() and removes TCE cache invalidation from
iommu_tce_xchg. This greatly reduces the number of OPAL calls and halves
the time spent in invalidation. Also, since now OPAL is called for more
just a single TCE, skiboot can choose to invalidate the entire TCE cache
depending on the number of TCEs or entirely (NPU).

This implements iommu_tce_kill_rm() locally in the realmode handlers file
similar to iommu_tce_xchg_rm() as, unlike iommu_tce_kill(), it is not
shared between VFIO IOMMU driver and KVM.

While at this, this fixes incorrect early returns in KVM's
H_PUT_TCE_INDIRECT handlers which skips unlocking locks:
both kvmppc_h_put_tce_indirect and kvmppc_rm_h_put_tce_indirect used
to return H_PARAMETER instead of jumping to unlock_exit.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---

This came up after debugging https://patchwork.ozlabs.org/patch/1134763/
"powerpc/pseries/iommu: Add cond_resched() for huge updates"
which we do not actually need.

This should fix bz https://bugzilla.linux.ibm.com/show_bug.cgi?id=175630#c19
I have also backported it at https://github.ibm.com/alexey/linux/commit/25271aa004de51f518408a1f105e36fabe823bf5


---
 arch/powerpc/include/asm/iommu.h          |  7 ++++++
 arch/powerpc/kernel/iommu.c               |  8 +++++++
 arch/powerpc/kvm/book3s_64_vio.c          | 21 ++++++++++++----
 arch/powerpc/kvm/book3s_64_vio_hv.c       | 29 +++++++++++++++++++----
 arch/powerpc/platforms/powernv/pci-ioda.c | 15 +++---------
 drivers/vfio/vfio_iommu_spapr_tce.c       |  8 ++++++-
 6 files changed, 66 insertions(+), 22 deletions(-)

```
#### [PATCH kernel] vfio/spapr_tce: Fix incorrect tce_iommu_group memory free
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
The @tcegrp variable is used in 1) a loop over attached groups
2) it stores a pointer to a newly allocated tce_iommu_group if 1) found
nothing. However the error handler does not distinguish how we got there
and incorrectly releases memory for a found+incompatible group.

This fixes it by adding another error handling case.

Fixes: 0bd971676e68 ("powerpc/powernv/npu: Add compound IOMMU groups")
Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---

The bug is there since 2157e7b82f3b but it would not appear in practice
before 0bd971676e68, hence that "Fixes". Or it still should be
157e7b82f3b ("vfio: powerpc/spapr: Register memory and define IOMMU v2")
?

Found it when tried adding a "compound PE" (GPU + NPUs) to a container
with a passed through xHCI host. The compatibility test (->create_table
should be equal) treats them as incompatible which might a bug (or
we are just suboptimal here) on its own.

---
 drivers/vfio/vfio_iommu_spapr_tce.c | 9 +++++----
 1 file changed, 5 insertions(+), 4 deletions(-)

```
#### [PATCH V3 1/3] x86/Hyper-V: Fix definition of struct hv_vp_assist_page
##### From: lantianyu1986@gmail.com

```c
From: Tianyu Lan <Tianyu.Lan@microsoft.com>

The struct hv_vp_assist_page was defined incorrectly.
The "vtl_control" should be u64[3], "nested_enlightenments
_control" should be a u64 and there is 7 reserved bytes
following "enlighten_vmentry". This patch is to fix it.

Signed-off-by: Tianyu Lan <Tianyu.Lan@microsoft.com>
---
Change since v1:
       Move definition of struct hv_nested_enlightenments_control
       into this patch to fix offset issue.
---
 arch/x86/include/asm/hyperv-tlfs.h | 20 +++++++++++++++-----
 1 file changed, 15 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: lapic: restart counter on change to periodic modeFrom: Matt delco <delco@google.com>
##### From: Matt delco <delco@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matt delco <delco@google.com>
X-Patchwork-Id: 11102341
Return-Path: <SRS0=6q4q=WP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6B8711398
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 19 Aug 2019 23:04:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4823F2341B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 19 Aug 2019 23:04:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="Vj3S26Qu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729006AbfHSXEb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 19 Aug 2019 19:04:31 -0400
Received: from mail-pl1-f201.google.com ([209.85.214.201]:35401 "EHLO
        mail-pl1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728894AbfHSXE3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Aug 2019 19:04:29 -0400
Received: by mail-pl1-f201.google.com with SMTP id s21so2841457plr.2
        for <kvm@vger.kernel.org>; Mon, 19 Aug 2019 16:04:29 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=yvso1VMUv5HDW/FWRWW4aLcQc7dQhn5xX7myTuMzxOM=;
        b=Vj3S26QuOjsxQcqWZv2x1d1sJe1SuGuBsGjkgram6TdMUJOBdkigrttT8pumAYozyX
         cbZOjPfub6CCO9zMBScmBZdDQBxaPkinjmvSpAEJot73Ty883i1IRvl52wcCm+EoBmM4
         9np7OFo65LbNf1yybsZPcctyKC7N+WkjTavobcwpw/ClTqmgyi2unvGp+6fn6DQa7di4
         qXFzK4YsQ1J37H2pK7x0FSVakMvvQ8QWh2gRoNefui+YKAsSgNe/71/FHkdFJGnKLrtx
         W9I3RPv/H+8tdgzCJJBOe7Qb1eCn3BUB2Yvlz3tt5Dv64LN7+xkF4vzqMM2pZZLL9vhO
         KnLQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=yvso1VMUv5HDW/FWRWW4aLcQc7dQhn5xX7myTuMzxOM=;
        b=ODaZKLM/7oE+msN7XgRVWcIQLErKiSAG8ctgfPkC8pOiKj8jMEQwczn+xI/AF4Qd0z
         g10nXg9KxXAx0vuo7nJ6hYGc3EEegxY5u1XjWBNwwcePdeNR+8wrvFh3E6rIQC5ApCVU
         0oa/7qoOLEg7d6xizVkLY4ZPvhUJJTjXd3YrM/bLjIOsknpKM/q0IDT25Tr1z1hQaguK
         pXnPmZ8ma9DYHyCPhG5MWXEDP7L0SilqWp2ACcMyzhSm6BRkjRK6zenQnT7obJwjJQ26
         n2poZtrbvAoj6Ur/47QGxz2Fsw3aki2Sn54xf9JxBQ9Wu6Dm8sZfTLjZqOCGMaEhtqhM
         U/JQ==
X-Gm-Message-State: APjAAAV59mTfbRz703Sc4Pj0pPdBvU+/v7HDSWq/5pYegL+1yS52eKO/
        BgzA8YYmf/ZT8fMuwziISbX9U6zmww==
X-Google-Smtp-Source: 
 APXvYqz17SfaxDarP4cPp/OzAe0kryC+XSYGBc2IGWqxdB/hJbMYggEGwLNS58HQu2HNj1UTKQ39ZjcXZQ==
X-Received: by 2002:a63:6888:: with SMTP id
 d130mr21122501pgc.197.1566255868467;
 Mon, 19 Aug 2019 16:04:28 -0700 (PDT)
Date: Mon, 19 Aug 2019 16:04:22 -0700
Message-Id: <20190819230422.244888-1-delco@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.rc1.153.gdeed80330f-goog
Subject: [PATCH] KVM: lapic: restart counter on change to periodic mode
From: Matt delco <delco@google.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com
Cc: kvm@vger.kernel.org, Matt Delco <delco@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Matt Delco <delco@google.com>

Time seems to eventually stop in a Windows VM when using Skype.
Instrumentation shows that the OS is frequently switching the APIC
timer between one-shot and periodic mode.  The OS is typically writing
to both LVTT and TMICT.  When time stops the sequence observed is that
the APIC was in one-shot mode, the timer expired, and the OS writes to
LVTT (but not TMICT) to change to periodic mode.  No future timer events
are received by the OS since the timer is only re-armed on TMICT writes.

With this change time continues to advance in the VM.  TBD if physical
hardware will reset the current count if/when the mode is changed to
period and the current count is zero.

Signed-off-by: Matt Delco <delco@google.com>
---
 arch/x86/kvm/lapic.c | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH 1/2] KVM: nVMX: Always indicate HLT activity support in VMX_MISC MSR
##### From: Nikita Leshenko <nikita.leshchenko@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikita Leshenko <nikita.leshchenko@oracle.com>
X-Patchwork-Id: 11102023
Return-Path: <SRS0=6q4q=WP=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C43491813
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 19 Aug 2019 21:47:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A400622CF4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 19 Aug 2019 21:47:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="THBZmmIW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728387AbfHSVrQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 19 Aug 2019 17:47:16 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:58176 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728366AbfHSVrQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Aug 2019 17:47:16 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7JLclYh146946
        for <kvm@vger.kernel.org>; Mon, 19 Aug 2019 21:47:15 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2019-08-05;
 bh=GemwLGsaF4rpE+fJDdpdoLqPR+C5oWuNOlT58p0HfOM=;
 b=THBZmmIWHXuromk0KYAumuNgnX5HXLxuEWKT+MEKcFx0bAF3Jsk0Gf/E2bnEMWVPtbav
 9yvjXWDDVgMUFtcK0PmBiOyajBMmCktN9z1ugicXjiy6B3FONm6T9eFY2sSzyd+Y4xRe
 28vWoRMLK8mOL1l6CTY0dG9rVR0YHi8R884F2n73yIZGH4LGsVVZRBfCwWGt1Vp1TIhe
 O/yUwPBIOVbbx9lP76VRgVJLnUfiO5AKib9XQ+GONBrnLmri9di/R9r0VC9UpruBqRLl
 da34l6XOGgHP0PHUwWcUy4Vsgzx47ZgYjqOY9n3ug8WnNwCPzrAm9J+F/VTv8HKDLHPl rw==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by userp2120.oracle.com with ESMTP id 2uea7qj4cx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK)
        for <kvm@vger.kernel.org>; Mon, 19 Aug 2019 21:47:15 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 x7JLd5lC108600
        for <kvm@vger.kernel.org>; Mon, 19 Aug 2019 21:47:14 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by aserp3030.oracle.com with ESMTP id 2ufwgcdbhy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK)
        for <kvm@vger.kernel.org>; Mon, 19 Aug 2019 21:47:14 +0000
Received: from abhmp0019.oracle.com (abhmp0019.oracle.com [141.146.116.25])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id x7JLlDtQ010127
        for <kvm@vger.kernel.org>; Mon, 19 Aug 2019 21:47:13 GMT
Received: from spark.ravello.local (/213.57.127.2)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 19 Aug 2019 14:47:13 -0700
From: Nikita Leshenko <nikita.leshchenko@oracle.com>
To: kvm@vger.kernel.org
Cc: Nikita Leshenko <nikita.leshchenko@oracle.com>,
        Liran Alon <liran.alon@oracle.com>,
        Krish Sadhukhan <krish.sadhukhan@oracle.com>
Subject: [PATCH 1/2] KVM: nVMX: Always indicate HLT activity support in
 VMX_MISC MSR
Date: Tue, 20 Aug 2019 00:46:49 +0300
Message-Id: <20190819214650.41991-2-nikita.leshchenko@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190819214650.41991-1-nikita.leshchenko@oracle.com>
References: <20190819214650.41991-1-nikita.leshchenko@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9354
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1906280000 definitions=main-1908190217
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9354
 signatures=668684
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=999 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1906280000
 definitions=main-1908190217
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Before this commit, userspace could disable the GUEST_ACTIVITY_HLT bit in
VMX_MISC yet KVM would happily accept GUEST_ACTIVITY_HLT activity state in
VMCS12. We can fix it by either failing VM entries with HLT activity state when
it's not supported or by disallowing clearing this bit.

The latter is preferable. If we go with the former, to disable
GUEST_ACTIVITY_HLT userspace also has to make CPU_BASED_HLT_EXITING a "must be
1" control, otherwise KVM will be presenting a bogus model to L1.

Don't fail writes that disable GUEST_ACTIVITY_HLT to maintain backwards
compatibility.

Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Nikita Leshenko <nikita.leshchenko@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
