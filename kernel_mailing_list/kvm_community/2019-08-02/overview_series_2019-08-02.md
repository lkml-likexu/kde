#### [PATCH 1/9] KVM: arm64: Document PV-time interface
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
 Documentation/virtual/kvm/arm/pvtime.txt | 107 +++++++++++++++++++++++
 1 file changed, 107 insertions(+)
 create mode 100644 Documentation/virtual/kvm/arm/pvtime.txt

diff --git a/Documentation/virtual/kvm/arm/pvtime.txt b/Documentation/virtual/kvm/arm/pvtime.txt
new file mode 100644
index 000000000000..e6ae9799e1d5
--- /dev/null
+++ b/Documentation/virtual/kvm/arm/pvtime.txt
@@ -0,0 +1,107 @@
+Paravirtualized time support for arm64
+======================================
+
+Arm specification DEN0057/A defined a standard for paravirtualised time
+support for Aarch64 guests:
+
+https://developer.arm.com/docs/den0057/a
+
+KVM/Arm64 implements the stolen time part of this specification by providing
+some hypervisor service calls to support a paravirtualized guest obtaining a
+view of the amount of time stolen from its execution.
+
+Two new SMCCC compatible hypercalls are defined:
+
+PV_FEATURES 0xC5000020
+PV_TIME_ST  0xC5000022
+
+These are only available in the SMC64/HVC64 calling convention as
+paravirtualized time is not available to 32 bit Arm guests.
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
+The structure will be updated by the hypervisor periodically as time is stolen
+from the VCPU. It will be present within a reserved region of the normal
+memory given to the guest. The guest should not attempt to write into this
+memory. There is a structure by VCPU of the guest.
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
+The guest IPA of the structures must be given to KVM. This is the base address
+of an array of stolen time structures (one for each VCPU). For example:
+
+    struct kvm_device_attr st_base = {
+            .group = KVM_DEV_ARM_PV_TIME_PADDR,
+            .attr = KVM_DEV_ARM_PV_TIME_ST,
+            .addr = (u64)(unsigned long)&st_paddr
+    };
+
+    ioctl(pvtime_fd, KVM_SET_DEVICE_ATTR, &st_base);
+
+For migration (or save/restore) of a guest it is necessary to save the contents
+of the shared page(s) and later restore them. KVM_DEV_ARM_PV_TIME_STATE_SIZE
+provides the size of this data and KVM_DEV_ARM_PV_TIME_STATE allows the state
+to be read/written.
+
+It is also necessary for the physical address to be set identically when
+restoring.
+
+    void *save_state(int fd, u64 attr, u32 *size) {
+        struct kvm_device_attr get_size = {
+                .group = KVM_DEV_ARM_PV_TIME_STATE_SIZE,
+                .attr = attr,
+                .addr = (u64)(unsigned long)size
+        };
+
+        ioctl(fd, KVM_GET_DEVICE_ATTR, get_size);
+
+        void *buffer = malloc(*size);
+
+        struct kvm_device_attr get_state = {
+                .group = KVM_DEV_ARM_PV_TIME_STATE,
+                .attr = attr,
+                .addr = (u64)(unsigned long)size
+        };
+
+        ioctl(fd, KVM_GET_DEVICE_ATTR, buffer);
+    }
+
+    void *st_state = save_state(pvtime_fd, KVM_DEV_ARM_PV_TIME_ST, &st_size);
+

From patchwork Fri Aug  2 14:50:10 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11073669
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9DEDC912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Aug 2019 14:50:38 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 80AF8285ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Aug 2019 14:50:38 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 71607286B3; Fri,  2 Aug 2019 14:50:38 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id A0B58285ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Aug 2019 14:50:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436759AbfHBOug (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Aug 2019 10:50:36 -0400
Received: from foss.arm.com ([217.140.110.172]:53212 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2436754AbfHBOuf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Aug 2019 10:50:35 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 4481A15A2;
        Fri,  2 Aug 2019 07:50:34 -0700 (PDT)
Received: from e112269-lin.arm.com (e112269-lin.cambridge.arm.com
 [10.1.196.133])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 27E6A3F575;
        Fri,  2 Aug 2019 07:50:32 -0700 (PDT)
From: Steven Price <steven.price@arm.com>
Cc: Steven Price <steven.price@arm.com>,
 Catalin Marinas <catalin.marinas@arm.com>, Marc Zyngier <maz@kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Russell King <linux@armlinux.org.uk>, Will Deacon <will@kernel.org>,
 James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Pouloze <suzuki.poulose@arm.com>, kvm@vger.kernel.org,
 kvmarm@lists.cs.columbia.edu, linux-arm-kernel@lists.infradead.org,
 linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org,
 Christoffer Dall <christoffer.dall@arm.com>
Subject: [PATCH 2/9] KVM: arm/arm64: Factor out hypercall handling from PSCI
 code
Date: Fri,  2 Aug 2019 15:50:10 +0100
Message-Id: <20190802145017.42543-3-steven.price@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190802145017.42543-1-steven.price@arm.com>
References: <20190802145017.42543-1-steven.price@arm.com>
MIME-Version: 1.0
To: unlisted-recipients:; (no To-header on input)
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
#### [PATCH 1/2] KVM: arm/arm64: Sync ICH_VMCR_EL2 back when about to block
##### From: Marc Zyngier <maz@kernel.org>

```c
Since commit commit 328e56647944 ("KVM: arm/arm64: vgic: Defer
touching GICH_VMCR to vcpu_load/put"), we leave ICH_VMCR_EL2 (or
its GICv2 equivalent) loaded as long as we can, only syncing it
back when we're scheduled out.

There is a small snag with that though: kvm_vgic_vcpu_pending_irq(),
which is indirectly called from kvm_vcpu_check_block(), needs to
evaluate the guest's view of ICC_PMR_EL1. At the point were we
call kvm_vcpu_check_block(), the vcpu is still loaded, and whatever
changes to PMR is not visible in memory until we do a vcpu_put().

Things go really south if the guest does the following:

	mov x0, #0	// or any small value masking interrupts
	msr ICC_PMR_EL1, x0

	[vcpu preempted, then rescheduled, VMCR sampled]

	mov x0, #ff	// allow all interrupts
	msr ICC_PMR_EL1, x0
	wfi		// traps to EL2, so samping of VMCR

	[interrupt arrives just after WFI]

Here, the hypervisor's view of PMR is zero, while the guest has enabled
its interrupts. kvm_vgic_vcpu_pending_irq() will then say that no
interrupts are pending (despite an interrupt being received) and we'll
block for no reason. If the guest doesn't have a periodic interrupt
firing once it has blocked, it will stay there forever.

To avoid this unfortuante situation, let's resync VMCR from
kvm_arch_vcpu_blocking(), ensuring that a following kvm_vcpu_check_block()
will observe the latest value of PMR.

This has been found by booting an arm64 Linux guest with the pseudo NMI
feature, and thus using interrupt priorities to mask interrupts instead
of the usual PSTATE masking.

Cc: stable@vger.kernel.org # 4.12
Fixes: 328e56647944 ("KVM: arm/arm64: vgic: Defer touching GICH_VMCR to vcpu_load/put")
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 include/kvm/arm_vgic.h      |  1 +
 virt/kvm/arm/arm.c          | 11 +++++++++++
 virt/kvm/arm/vgic/vgic-v2.c |  9 ++++++++-
 virt/kvm/arm/vgic/vgic-v3.c |  7 ++++++-
 virt/kvm/arm/vgic/vgic.c    | 11 +++++++++++
 virt/kvm/arm/vgic/vgic.h    |  2 ++
 6 files changed, 39 insertions(+), 2 deletions(-)

```
#### [RFC PATCH v2 01/19] KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG interface
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
We will be using ONE_REG interface accessing VCPU registers from
user-space hence we add KVM_REG_RISCV for RISC-V VCPU registers.

Signed-off-by: Anup Patel <anup.patel@wdc.com>
---
 include/uapi/linux/kvm.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH kvmtool] README: Update my email address
##### From: Julien Thierry <julien.thierry.kdev@gmail.com>

```c
My @arm.com address is gonna stop working. Update README information
with an address people can use to actually reach me.

Signed-off-by: Julien Thierry <julien.thierry.kdev@gmail.com>
---
 README | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PULL 1/2] kvm-unit-tests: s390: add cpu model checks
##### From: Thomas Huth <thuth@redhat.com>

```c
From: Christian Borntraeger <borntraeger@de.ibm.com>

This adds a check for documented stfle dependencies.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
[thuth: Added missing report_prefix_pop() at the end]
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 s390x/Makefile      |  1 +
 s390x/cpumodel.c    | 60 +++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg |  3 +++
 3 files changed, 64 insertions(+)
 create mode 100644 s390x/cpumodel.c

```
#### [PATCH] [kvm-unit-tests PATCH] x86: vmx: Fix comment typo for ept_access_paddr()
##### From: Oliver Upton <oupton@google.com>

```c
the comment for ept_access_paddr() referred to a nonexistent
ept_access_data. Fixing the comment to correctly refer to
ept_access_test_data.

Signed-off-by: Oliver Upton <oupton@google.com>
---
 x86/vmx_tests.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH 01/34] mm/gup: add make_dirty arg to put_user_pages_dirty_lock()
##### From: john.hubbard@gmail.com

```c
From: John Hubbard <jhubbard@nvidia.com>

Provide more capable variation of put_user_pages_dirty_lock(),
and delete put_user_pages_dirty(). This is based on the
following:

1. Lots of call sites become simpler if a bool is passed
into put_user_page*(), instead of making the call site
choose which put_user_page*() variant to call.

2. Christoph Hellwig's observation that set_page_dirty_lock()
is usually correct, and set_page_dirty() is usually a
bug, or at least questionable, within a put_user_page*()
calling chain.

This leads to the following API choices:

    * put_user_pages_dirty_lock(page, npages, make_dirty)

    * There is no put_user_pages_dirty(). You have to
      hand code that, in the rare case that it's
      required.

Cc: Matthew Wilcox <willy@infradead.org>
Cc: Jan Kara <jack@suse.cz>
Cc: Christoph Hellwig <hch@lst.de>
Cc: Ira Weiny <ira.weiny@intel.com>
Cc: Jason Gunthorpe <jgg@ziepe.ca>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 drivers/infiniband/core/umem.c             |   5 +-
 drivers/infiniband/hw/hfi1/user_pages.c    |   5 +-
 drivers/infiniband/hw/qib/qib_user_pages.c |   5 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c   |   5 +-
 drivers/infiniband/sw/siw/siw_mem.c        |  10 +-
 include/linux/mm.h                         |   5 +-
 mm/gup.c                                   | 115 +++++++++------------
 7 files changed, 58 insertions(+), 92 deletions(-)

```
#### [PATCH 01/34] mm/gup: add make_dirty arg to put_user_pages_dirty_lock()
##### From: john.hubbard@gmail.com

```c
From: John Hubbard <jhubbard@nvidia.com>

Provide more capable variation of put_user_pages_dirty_lock(),
and delete put_user_pages_dirty(). This is based on the
following:

1. Lots of call sites become simpler if a bool is passed
into put_user_page*(), instead of making the call site
choose which put_user_page*() variant to call.

2. Christoph Hellwig's observation that set_page_dirty_lock()
is usually correct, and set_page_dirty() is usually a
bug, or at least questionable, within a put_user_page*()
calling chain.

This leads to the following API choices:

    * put_user_pages_dirty_lock(page, npages, make_dirty)

    * There is no put_user_pages_dirty(). You have to
      hand code that, in the rare case that it's
      required.

Cc: Matthew Wilcox <willy@infradead.org>
Cc: Jan Kara <jack@suse.cz>
Cc: Christoph Hellwig <hch@lst.de>
Cc: Ira Weiny <ira.weiny@intel.com>
Cc: Jason Gunthorpe <jgg@ziepe.ca>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
---
 drivers/infiniband/core/umem.c             |   5 +-
 drivers/infiniband/hw/hfi1/user_pages.c    |   5 +-
 drivers/infiniband/hw/qib/qib_user_pages.c |   5 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c   |   5 +-
 drivers/infiniband/sw/siw/siw_mem.c        |  10 +-
 include/linux/mm.h                         |   5 +-
 mm/gup.c                                   | 115 +++++++++------------
 7 files changed, 58 insertions(+), 92 deletions(-)

```
#### [PATCH 1/2] vfio-mdev/mtty: Simplify interrupt generation
##### From: Parav Pandit <parav@mellanox.com>

```c
While generating interrupt, mdev_state is already available for which
interrupt is generated.
Instead of doing indirect way from state->device->uuid-> to searching
state linearly in linked list on every interrupt generation,
directly use the available state.

Hence, simplify the code to use mdev_state and remove unused helper
function with that.

Signed-off-by: Parav Pandit <parav@mellanox.com>
---
 samples/vfio-mdev/mtty.c | 39 ++++++++-------------------------------
 1 file changed, 8 insertions(+), 31 deletions(-)

```
#### [PATCH v2] KVM: x86: Unconditionally call x86 ops that are always implemented
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Remove a few stale checks for non-NULL ops now that the ops in question
are implemented by both VMX and SVM.

Note, this is **not** stable material, the Fixes tags are there purely
to show when a particular op was first supported by both VMX and SVM.

Fixes: 74f169090b6f ("kvm/svm: Setup MCG_CAP on AMD properly")
Fixes: b31c114b82b2 ("KVM: X86: Provide a capability to disable PAUSE intercepts")
Fixes: 411b44ba80ab ("svm: Implements update_pi_irte hook to setup posted interrupt")
Cc: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---

v2: Give update_pi_iret the same treatment [Krish].

 arch/x86/kvm/x86.c | 13 +++----------
 1 file changed, 3 insertions(+), 10 deletions(-)

```
