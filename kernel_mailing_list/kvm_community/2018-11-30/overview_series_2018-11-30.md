#### [PATCH 1/7] KVM: nVMX: Prepend "nested_" to check_vmentry_{pre,post}reqs()
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
.. as they are used only in nested context.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
---
 arch/x86/kvm/vmx.c | 15 ++++++++-------
 1 file changed, 8 insertions(+), 7 deletions(-)

```
#### [RFC PATCH V2 01/11] Documentation: Added EPT Subpage Protection Documentation.
##### From: Zhang Yi <yi.z.zhang@linux.intel.com>

```c
Signed-off-by: Zhang Yi <yi.z.zhang@linux.intel.com>
---
 Documentation/virtual/kvm/spp_design_kvm.txt | 275 +++++++++++++++++++++++++++
 1 file changed, 275 insertions(+)
 create mode 100644 Documentation/virtual/kvm/spp_design_kvm.txt

diff --git a/Documentation/virtual/kvm/spp_design_kvm.txt b/Documentation/virtual/kvm/spp_design_kvm.txt
new file mode 100644
index 0000000..8dc4530
--- /dev/null
+++ b/Documentation/virtual/kvm/spp_design_kvm.txt
@@ -0,0 +1,275 @@
+DRAFT: EPT-Based Sub-Page Protection (SPP) Design Doc for KVM
+=============================================================
+
+1. Overview
+
+EPT-based Sub-Page Protection (SPP) capability to allow Virtual Machine
+Monitors to specify write-protection for guest physical memory at a
+sub-page (128 byte) granularity. When this capability is utilized, the
+CPU enforces write-access permissions for sub-page regions of 4K pages
+as specified by the VMM.
+
+2. Operation of SPP
+
+Sub-Page Protection Table (SPPT) is introduced to manage sub-page
+write-access.
+
+SPPT is active when the "sub-page write protection" VM-execution control
+is 1. SPPT looks up the guest physical addresses to derive a 64 bit
+"sub-page permission" value containing sub-page write permissions. The
+lookup from guest-physical addresses to the sub-page region permissions
+is determined by a set of SPPT paging structures.
+
+When the "sub-page write protection" VM-execution control is 1, the SPPT
+is used to lookup write permission bits for the 128 byte sub-page regions
+containing in the 4KB guest physical page. EPT specifies the 4KB page
+level privileges that software is allowed when accessing the guest
+physical address, whereas SPPT defines the write permissions for software
+at the 128 byte granularity regions within a 4KB page. Write accesses
+prevented due to sub-page permissions looked up via SPPT are reported as
+EPT violation VM exits. Similar to EPT, a logical processor uses SPPT to
+lookup sub-page region write permissions for guest-physical addresses
+only when those addresses are used to access memory.
+______________________________________________________________________________
+
+How SPP hardware works:
+______________________________________________________________________________
+
+Guest write access --> GPA --> Walk EPT --> EPT leaf entry -┐
+┌-----------------------------------------------------------┘
+└-> if VMexec_control.spp && ept_leaf_entry.spp_bit (bit 61)
+     |
+     └-> <false> --> EPT legacy behavior
+     |
+     |
+     └-> <true>  --> if ept_leaf_entry.writable
+                      |
+                      └-> <true>  --> Ignore SPP
+                      |
+		      └-> <false> --> GPA --> Walk SPP 4-level table--┐
+                                                                      |
+┌------------<----------get-the-SPPT-point-from-VMCS-filed-----<------┘
+|
+Walk SPP L4E table
+|
+└┐--> entry misconfiguration ------------>----------┐<----------------┐
+ |                                                  |                 |
+else                                                |                 |
+ |                                                  |                 |
+ |   ┌------------------SPP VMexit<-----------------┘                 |
+ |   |                                                                |
+ |   └-> exit_qualification & sppt_misconfig --> sppt misconfig       |
+ |   |                                                                |
+ |   └-> exit_qualification & sppt_miss --> sppt miss                 |
+ └--┐                                                                 |
+    |                                                                 |
+walk SPPT L3E--┐--> if-entry-misconfiguration------------>------------┘
+               |                                                      |
+	      else                                                    |
+	       |                                                      |
+	       |                                                      |
+        walk SPPT L2E --┐--> if-entry-misconfiguration-------->-------┘
+                        |                                             |
+                       else                                           |
+			|                                             |
+			|                                             |
+	         walk SPPT L1E --┐-> if-entry-misconfiguration--->----┘
+                                 |
+			        else
+				 |
+                                 └-> if sub-page writable
+                                      └-> <true>  allow, write access
+	                              └-> <false> disallow, EPT violation
+______________________________________________________________________________
+
+3. Interfaces
+
+* Feature enabling
+
+Add "spp=on" to KVM module parameter to enable SPP feature, default is off.
+
+* Get/Set sub-page write access permission
+
+New KVM ioctl:
+
+`KVM_SUBPAGES_GET_ACCESS`:
+Get sub-pages write access bitmap corresponding to given rang of continuous gfn.
+
+`KVM_SUBPAGES_SET_ACCESS`
+Set sub-pages write access bitmap corresponding to given rang of continuous gfn.
+
+```c
+/* for KVM_SUBPAGES_GET_ACCESS and KVM_SUBPAGES_SET_ACCESS */
+struct kvm_subpage_info {
+	__u64 gfn;
+	__u64 npages; /* number of 4K pages */
+	__u64 *access_map; /* sub-page write-access bitmap array */
+};
+
+#define KVM_SUBPAGES_GET_ACCESS   _IOR(KVMIO,  0x49, struct kvm_subpage_info)
+#define KVM_SUBPAGES_SET_ACCESS   _IOW(KVMIO,  0x4a, struct kvm_subpage_info)
+```
+
+4. SPPT initialization
+
+* SPPT root page allocation
+
+  SPPT is referenced via a 64-bit control field called "sub-page
+  protection table pointer" (SPPTP, encoding 0x2030) which contains a
+  4K-align physical address.
+
+  SPPT also has 4 level table as well as EPT. So, as EPT does, when KVM
+  loads mmu, we allocate a root page for SPPT L4 table.
+
+* EPT leaf entry SPP bit
+
+  Set 0 to SPP bit to close SPP by default.
+
+5. Set/Get Sub-Page access bitmap for bunch of guest physical pages
+
+* To utilize SPP feature, system admin should Set a Sub-page access write via
+  SPP KVM ioctl `KVM_SUBPAGES_SET_ACCESS`, which will prepared the flowing things.
+
+   (1.Got the corresponding EPT leaf entry via the guest physical address.
+   (2.If it is a 4K page frame, flag the bit 61 to enable subpage protection on this page.
+   (3.Setup spp page structure, the page structure format is list following.
+
+   Format of the SPPT L4E, L3E, L2E:
+   | Bit    | Contents                                                                 |
+   | :----- | :------------------------------------------------------------------------|
+   | 0      | Valid entry when set; indicates whether the entry is present             |
+   | 11:1   | Reserved (0)                                                             |
+   | N-1:12 | Physical address of 4KB aligned SPPT LX-1 Table referenced by this entry |
+   | 51:N   | Reserved (0)                                                             |
+   | 63:52  | Reserved (0)                                                             |
+   Note: N is the physical address width supported by the processor. X is the page level
+
+   Format of the SPPT L1E:
+   | Bit   | Contents                                                          |
+   | :---- | :---------------------------------------------------------------- |
+   | 0+2i  | Write permission for i-th 128 byte sub-page region.               |
+   | 1+2i  | Reserved (0).                                                     |
+   Note: `0<=i<=31`
+
+   (4.Update the subpage info into memory slot structure.
+
+* Sub-page write access bitmap setting pseudo-code:
+
+```c
+static int kvm_mmu_set_subpages(struct kvm_vcpu *vcpu,
+				struct kvm_subpage_info *spp_info)
+{
+	gfn_t *gfns = spp_info->gfns;
+	u64 *access_map = spp_info->access_map;
+
+	sanity_check();
+
+	/* SPP works when the page is unwritable */
+	if (set_ept_leaf_level_unwritable(gfn) == success)
+
+		if (kvm_mmu_setup_spp_structure(gfn) == success)
+
+			set_subpage_slot_info(access_map);
+
+}
+```
+
+User could get the subpage info via SPP KVM ioctl `KVM_SUBPAGES_GET_ACCESS`,
+which from the memory slot structure corresponding the specify gpa.
+
+* Sub-page get subpage info pseudo-code:
+
+```c
+static int kvm_mmu_get_subpages(struct kvm_vcpu *vcpu,
+				struct kvm_subpage_info *spp_info)
+{
+	gfn_t *gfns = spp_info->gfns;
+
+	sanity_check(gfn);
+	spp_info = get_subpage_slot_info(gfn);
+}
+
+```
+
+5. SPPT-induced vmexits
+
+* SPP VM exits
+
+Accesses using guest physical addresses may cause VM exits due to a SPPT
+Misconfiguration or a SPPT Miss.
+
+A SPPT Misconfiguration vmexit occurs when, in the course of translating
+a guest physical address, the logical processor encounters a leaf EPT
+paging-structure entry mapping a 4KB page, with SPP enabled, during the
+SPPT lookup, a SPPT paging-structure entry contains an unsupported
+value.
+
+A SPPT Miss vmexit occurs during the SPPT lookup there is no SPPT
+misconfiguration but any level of SPPT paging-structure entries are not
+present.
+
+NOTE. SPPT misconfigurations and SPPT miss can occur only due to an
+attempt to write memory with a guest physical address.
+
+* EPT violation vmexits due to SPPT
+
+EPT violations due to memory write accesses disallowed due to sub-page
+protection permissions specified in the SPPT are reported via EPT
+violation VM exits.
+
+6. SPPT-induced vmexits handling
+
+```c
+#define EXIT_REASON_SPP                 66
+
+static int (*const kvm_vmx_exit_handlers[])(struct kvm_vcpu *vcpu) = {
+	...
+	[EXIT_REASON_SPP]                     = handle_spp,
+	...
+};
+```
+
+New exit qualification for SPPT-induced vmexits.
+
+| Bit   | Contents                                                          |
+| :---- | :---------------------------------------------------------------- |
+| 10:0  | Reserved (0).                                                     |
+| 11    | SPPT VM exit type. Set for SPPT Miss, cleared for SPPT Misconfig. |
+| 12    | NMI unblocking due to IRET                                        |
+| 63:13 | Reserved (0)                                                      |
+
+In addition to the exit qualification, Guest Linear Address and Guest
+Physical Address fields will be reported.
+
+* SPPT miss and misconfiguration
+
+Allocate a page for the SPPT entry and set the entry correctly.
+
+
+SPP VMexit handler Pseudo-code:
+```c
+static int handle_spp(kvm_vcpu *vcpu)
+{
+	exit_qualification = vmcs_readl(EXIT_QUALIFICATION);
+	if (exit_qualification & SPP_EXIT_TYPE_BIT) {
+		/* SPPT Miss */
+		/* We don't set SPP write access for the corresponding
+		 * GPA, leave it unwritable, so no need to construct
+		 * SPP table here. */
+	} else {
+		/* SPPT Misconfig */
+		vcpu->run->exit_reason = KVM_EXIT_UNKNOWN;
+		vcpu->run->hw.hardware_exit_reason = EXIT_REASON_SPP;
+	}
+	return 0;
+}
+```
+
+* EPT violation vmexits due to SPPT
+
+While hardware walking the SPP page table, If the sub-page region write
+permission bit is set, the write is allowed, else the write is disallowed
+and results in an EPT violation.
+
+we need peek this case in EPT volition handler, and trigger a user-space
+exit, return the write protected address(GPA) to user(qemu).

From patchwork Fri Nov 30 08:08:06 2018
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yi Zhang <yi.z.zhang@linux.intel.com>
X-Patchwork-Id: 10705917
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BFBBA14BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Nov 2018 08:08:30 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id B38AA2E52B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Nov 2018 08:08:30 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id A4A792F7AB; Fri, 30 Nov 2018 08:08:30 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 4A4172E52B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 30 Nov 2018 08:08:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727071AbeK3TQw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 30 Nov 2018 14:16:52 -0500
Received: from mga14.intel.com ([192.55.52.115]:12724 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727016AbeK3TQv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 30 Nov 2018 14:16:51 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 30 Nov 2018 00:08:23 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.56,297,1539673200";
   d="scan'208";a="279174483"
Received: from linux.intel.com ([10.54.29.200])
  by orsmga005.jf.intel.com with ESMTP; 30 Nov 2018 00:08:23 -0800
Received: from dazhang1-ssd.sh.intel.com (unknown [10.239.48.128])
        by linux.intel.com (Postfix) with ESMTP id D340E580213;
        Fri, 30 Nov 2018 00:08:21 -0800 (PST)
From: Zhang Yi <yi.z.zhang@linux.intel.com>
To: pbonzini@redhat.com, mdontu@bitdefender.com, ncitu@bitdefender.com
Cc: rkrcmar@redhat.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, Zhang Yi <yi.z.zhang@linux.intel.com>
Subject: [RFC PATCH V2 02/11] x86/cpufeature: Add intel Sub-Page Protection to
 CPU features
Date: Fri, 30 Nov 2018 16:08:06 +0800
Message-Id: 
 <0b6a870f960c656bc73bf0e0b9c678ee7f52998e.1543481993.git.yi.z.zhang@linux.intel.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <cover.1543481993.git.yi.z.zhang@linux.intel.com>
References: <cover.1543481993.git.yi.z.zhang@linux.intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

Adds reporting SPP capability from VMX Procbased MSR, according to
the definition of hardware spec, bit 32 is the control of the SPP
capability.

Defined X86_FEATURE_SPP under intel X86 VT-x CPU features.

Defined the X86_VMX_FEATURE_PROC_CTLS2_SPP in intel VMX MSR indicated
features, And enable SPP capability by this MSR.

Signed-off-by: Zhang Yi <yi.z.zhang@linux.intel.com>
Signed-off-by: He Chen <he.chen@linux.intel.com>
---
 arch/x86/include/asm/cpufeatures.h | 1 +
 arch/x86/kernel/cpu/intel.c        | 4 ++++
 2 files changed, 5 insertions(+)

```
#### [PATCH] KVM nVMX: MSRs should not be stored if VM-entry fails during or after loading guest state
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
If a bit-pattern for the MSR-store address is so chosen that the
address is 16-bit aligned and is less than the processor's physical
width, but is a junk, VMENTRY ultimately fails even though we
pass the checks in check_vmentry_prereqs(). In such a case, the high bit
in "exit reason" will be set, denoting a VM-entry failure. But since we
call nested_vmx_store_msr() in nested_vmx_vmexit() without checking the
"exit reason", we may end up storing the MSRs at an undefined location in
memory thereby clobbering something else. This patch fixes the problem by
calling nested_vmx_store_msr() only when "exit reason" is not VM-entry
failure.

Reported-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
---
 arch/x86/kvm/vmx.c | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
#### [PATCH v4 01/10] KVM: s390: unregister debug feature on failing arch init
##### From: Michael Mueller <mimu@linux.ibm.com>

```c
Make sure the debug feature and its allocated resources get
released upon unsuccessful architecture initialization.

A related indication of the issue will be reported as kernel
message.

Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 Documentation/kmsg/s390/kvm | 12 ++++++++++++
 arch/s390/kvm/kvm-s390.c    | 17 ++++++++++++++---
 2 files changed, 26 insertions(+), 3 deletions(-)
 create mode 100644 Documentation/kmsg/s390/kvm

diff --git a/Documentation/kmsg/s390/kvm b/Documentation/kmsg/s390/kvm
new file mode 100644
index 000000000000..76ffe2012254
--- /dev/null
+++ b/Documentation/kmsg/s390/kvm
@@ -0,0 +1,12 @@
+/*?
+ * Text: "Failed to register FLIC rc=%d\n"
+ * Severity: Error
+ * Parameter:
+ *   @1: return code of the FLIC registration call
+ * Description:
+ * The registration of the FLIC (Floating Interrupt Controller Interface)
+ * was not successful.
+ * User action:
+ * If this problem persists after a reload of the kvm kernel module, gather
+ * Linux debug data and contact your support organization.
+ */
```
#### [PATCH v2] vhost: fix IOTLB locking
##### From: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

```c
Commit 78139c94dc8c ("net: vhost: lock the vqs one by one") moved the vq
lock to improve scalability, but introduced a possible deadlock in
vhost-iotlb. vhost_iotlb_notify_vq() now takes vq->mutex while holding
the device's IOTLB spinlock. And on the vhost_iotlb_miss() path, the
spinlock is taken while holding vq->mutex.

Since calling vhost_poll_queue() doesn't require any lock, avoid the
deadlock by not taking vq->mutex.

Fixes: 78139c94dc8c ("net: vhost: lock the vqs one by one")
Acked-by: Jason Wang <jasowang@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
 drivers/vhost/vhost.c | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH v2] x86/hyper-v: Mark TLFS structures packed
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
The TLFS structures are used for hypervisor-guest communication and must
exactly meet the specification.

Compilers can add alignment padding to structures or reorder struct members
for randomization and optimization, which would break the hypervisor ABI.

Mark the structures as packed to prevent this.

Suggested-by: Nadav Amit <nadav.amit@gmail.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Acked-by: Thomas Gleixner <tglx@linutronix.de>
Acked-by: Nadav Amit <nadav.amit@gmail.com>
---
- Changes since v1:
 - Re-worded commit message for clarity. [Thomas Gleixner]

- This is a follow-up to my "[PATCH v2 0/4] x86/kvm/hyper-v: Implement
 Direct Mode for synthetic timers" series, as suggested by Thomas I'm
 routing it to KVM tree to avoid merge conflicts.
---
 arch/x86/include/asm/hyperv-tlfs.h | 50 +++++++++++++++---------------
 1 file changed, 25 insertions(+), 25 deletions(-)

```
#### [PATCH] vhost: fix IOTLB locking
##### From: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

```c
Commit 78139c94dc8c ("net: vhost: lock the vqs one by one") moved the vq
lock to improve scalability, but introduced a possible deadlock in
vhost-iotlb. vhost_iotlb_notify_vq() now takes vq->mutex while holding
the device's IOTLB spinlock. And on the vhost_iotlb_miss() path, the
spinlock is taken while holding vq->mutex.

As long as we hold dev->mutex to prevent an ioctl from modifying
vq->poll concurrently, we can safely call vhost_poll_queue() without
holding vq->mutex. Since vhost_process_iotlb_msg() holds dev->mutex when
calling vhost_iotlb_notify_vq(), avoid the deadlock by not taking
vq->mutex.

Fixes: 78139c94dc8c ("net: vhost: lock the vqs one by one")
Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Acked-by: Jason Wang <jasowang@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] x86/hyper-v: define structures from TLFS as packed
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Without 'packed' compiler is free to add optimization paddings and re-order
structure fields for randomization/optimization. And structures from
hyperv-tlfs.h are used for hypervisor-guest communication, we need to
ultimately forbid such practices.

Suggested-by: Nadav Amit <nadav.amit@gmail.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
- This is a follow-up to my "[PATCH v2 0/4] x86/kvm/hyper-v: Implement
 Direct Mode for synthetic timers" series, as suggested by Thomas I'm
 routing it to KVM tree to avoid merge conflicts.
---
 arch/x86/include/asm/hyperv-tlfs.h | 50 +++++++++++++++---------------
 1 file changed, 25 insertions(+), 25 deletions(-)

```
