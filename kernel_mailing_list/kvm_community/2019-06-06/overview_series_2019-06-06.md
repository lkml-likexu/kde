#### [PATCH v3 1/9] Documentation: Introduce EPT based Subpage Protection
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 Documentation/virtual/kvm/spp_kvm.txt | 216 ++++++++++++++++++++++++++
 1 file changed, 216 insertions(+)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt

diff --git a/Documentation/virtual/kvm/spp_kvm.txt b/Documentation/virtual/kvm/spp_kvm.txt
new file mode 100644
index 000000000000..4b5edcaf48b6
--- /dev/null
+++ b/Documentation/virtual/kvm/spp_kvm.txt
@@ -0,0 +1,216 @@
+EPT-Based Sub-Page Protection (SPP) for KVM
+=============================================
+
+1. Overview
+
+EPT-based Sub-Page Protection (SPP) capability to allow Virtual Machine
+Monitors to specify write-protection for guest physical memory at a
+sub-page (128 byte) granularity. When this capability is utilized, the
+CPU enforces write-access permissions for sub-page regions inside 4K pages
+as specified by the VMI tools.
+
+2. Operation of SPP
+
+Sub-Page Protection Table (SPPT) is introduced to manage sub-page
+write-access.
+
+SPPT is active when:
+a) moddule parameter spp=on is configured for kvm-intel.ko
+b) large paging is disabled on host
+c) "sub-page write protection" VM-execution control bit is set
+SPPT looks up the guest physical address to seek a 64-bit
+bitmap indicating sub-page write permission in SPPT leaf entry.
+
+When the "sub-page write protection" VM-execution control is 1, the SPPT
+is used to lookup write permission bits for the 128 byte sub-page regions
+contained in the 4KB guest physical page. EPT specifies the 4KB page
+write-protection privilege whereas SPPT defines the write permissions
+at 128-byte granularity within one 4KB page. Write accesses
+prevented due to sub-page permissions induces EPT violation VM exits.
+Similar to EPT, a logical processor uses SPPT to lookup sub-page level
+write permissions for guest-physical addresses only when those addresses
+are used to access memory.
+__________________________________________________________________________
+
+How SPP hardware works:
+__________________________________________________________________________
+
+Guest write access --> GPA --> Walk EPT --> EPT leaf entry -----|
+|---------------------------------------------------------------|
+|-> if VMexec_control.spp && ept_leaf_entry.spp_bit (bit 61)
+     |
+     |-> <false> --> EPT legacy behavior
+     |
+     |
+     |-> <true>  --> if ept_leaf_entry.writable
+                      |
+                      |-> <true>  --> Ignore SPP
+                      |
+                      |-> <false> --> GPA --> Walk SPP 4-level table--|
+                                                                      |
+|------------<----------get-the-SPPT-point-from-VMCS-filed-----<------|
+|
+Walk SPP L4E table
+|
+|---> if-entry-misconfiguration ------------>-------|-------<---------|
+ |                                                  |                 |
+else                                                |                 |
+ |                                                  |                 |
+ |   |------------------SPP VMexit<-----------------|                 |
+ |   |                                                                |
+ |   |-> exit_qualification & sppt_misconfig --> sppt misconfig       |
+ |   |                                                                |
+ |   |-> exit_qualification & sppt_miss --> sppt miss                 |
+ |---|                                                                |
+     |                                                                |
+walk SPPT L3E--|--> if-entry-misconfiguration------------>------------|
+               |                                                      |
+              else                                                    |
+               |                                                      |
+               |                                                      |
+        walk SPPT L2E --|--> if-entry-misconfiguration-------->-------|
+                        |                                             |
+                       else                                           |
+                        |                                             |
+                        |                                             |
+                 walk SPPT L1E --|-> if-entry-misconfiguration--->----|
+                                 |
+                               else
+                                 |
+                                 |-> if sub-page writable
+                                 |-> <true>  allow, write access
+                                 |-> <false> disallow, EPT violation
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
+KVM_SUBPAGES_GET_ACCESS:
+Get sub-pages write access bitmap corresponding to given rang of continuous gfn.
+
+KVM_SUBPAGES_SET_ACCESS
+Set sub-pages write access bitmap corresponding to given rang of continuous gfn.
+
+
+/* for KVM_SUBPAGES_GET_ACCESS and KVM_SUBPAGES_SET_ACCESS */
+struct kvm_subpage_info {
+    __u64 gfn;
+    __u64 npages; /* number of 4K pages */
+    __u64 *access_map; /* sub-page write-access bitmap array */
+};
+
+#define KVM_SUBPAGES_GET_ACCESS   _IOR(KVMIO,  0x49, struct kvm_subpage_info)
+#define KVM_SUBPAGES_SET_ACCESS   _IOW(KVMIO,  0x4a, struct kvm_subpage_info)
+
+
+4. SPPT initialization
+
+* SPPT root page allocation
+
+  SPPT is referenced via a 64-bit control field called "sub-page
+  protection table pointer" (SPPTP, encoding 0x2030) which contains a
+  4K-align physical address.
+
+  SPPT is a 4-level paging structure similar as EPT. When KVM
+  loads mmu, it allocates a root page for SPPT L4 table as well.
+
+* EPT leaf entry SPP bit (bit 61)
+
+  Set 0 to SPP bit to close SPP.
+
+5. Set/Get Sub-Page access bitmap for a bunch of guest physical pages
+
+* To utilize SPP feature, system admin should set sub-page access via
+  SPP KVM ioctl `KVM_SUBPAGES_SET_ACCESS`, configuring EPT and SPPT in below flow:
+
+  (1) If the target 4KB pages to be protected are there, it locates EPT leaf entries
+      via the guest physical addresses, flags the bit 61 of the corresponding entries to
+      enable sub-page protection for the pages, then setup SPPT paging structure.
+  (2) otherwise, stores the [gfn,permission] mappings in KVM data structure. When
+      EPT page-fault is generated due to target protected page accessing, it settles
+      EPT entry configureation together with SPPT build-up.
+
+   The SPPT paging structure format is as below:
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
+   Note: 0<=i<=31
+
+6. SPPT-induced vmexits
+
+* SPP VM exits
+
+Accesses using guest physical addresses may cause VM exits due to a SPPT
+misconfiguration or a SPPT missing.
+
+A SPPT misconfiguration vmexit occurs when, in the course of translating
+a guest physical address, the logical processor encounters a leaf EPT
+paging-structure entry mapping a 4KB page, with SPP enabled, during the
+SPPT lookup, a SPPT paging-structure entry contains an unsupported
+value.
+
+A SPPT missing vmexit occurs during the SPPT lookup there is no SPPT
+misconfiguration but any level of SPPT paging-structure entries are not
+present.
+
+NOTE. SPPT misconfigurations and SPPT miss can occur only due to an
+attempt to write memory with a guest physical address.
+
+* EPT violation vmexits due to SPPT
+
+EPT violations generated due to SPP sub-page
+permission are reported as EPT violation vmexits.
+
+7. SPPT-induced vmexits handling
+
+
+#define EXIT_REASON_SPP                 66
+
+static int (*const kvm_vmx_exit_handlers[])(struct kvm_vcpu *vcpu) = {
+    ...
+    [EXIT_REASON_SPP]                     = handle_spp,
+    ...
+};
+
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
+* EPT violation vmexits due to SPPT
+
+While hardware traverses SPPT, If the sub-page region write
+permission bit is set, the write is allowed, otherwise it's prevented
+and an EPT violation is generated.

From patchwork Thu Jun  6 15:28:05 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 10979791
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7F783924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Jun 2019 15:30:00 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 6F0BC26E49
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Jun 2019 15:30:00 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 62AD928478; Thu,  6 Jun 2019 15:30:00 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id DDBC126E49
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Jun 2019 15:29:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729358AbfFFP36 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Jun 2019 11:29:58 -0400
Received: from mga01.intel.com ([192.55.52.88]:53940 "EHLO mga01.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729390AbfFFP34 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Jun 2019 11:29:56 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga007.fm.intel.com ([10.253.24.52])
  by fmsmga101.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 06 Jun 2019 08:29:56 -0700
X-ExtLoop1: 1
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by fmsmga007.fm.intel.com with ESMTP; 06 Jun 2019 08:29:55 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, mst@redhat.com, rkrcmar@redhat.com,
        jmattson@google.com, yu.c.zhang@intel.com
Cc: Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v3 2/9] KVM: VMX: Add control flags for SPP enabling
Date: Thu,  6 Jun 2019 23:28:05 +0800
Message-Id: <20190606152812.13141-3-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20190606152812.13141-1-weijiang.yang@intel.com>
References: <20190606152812.13141-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

Check SPP capability in MSR_IA32_VMX_PROCBASED_CTLS2, its 23-bit
indicates SPP support. Mark SPP bit in CPU capabilities bitmap if
it's supported.

Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/cpufeatures.h |  1 +
 arch/x86/include/asm/vmx.h         |  1 +
 arch/x86/kernel/cpu/intel.c        |  4 ++++
 arch/x86/kvm/vmx/capabilities.h    |  5 +++++
 arch/x86/kvm/vmx/vmx.c             | 10 ++++++++++
 5 files changed, 21 insertions(+)

```
#### [PATCH v6 01/12] perf/x86: fix the variable type of the LBR MSRs
##### From: Wei Wang <wei.w.wang@intel.com>

```c
The MSR variable type can be "unsigned int", which uses less memory than
the longer unsigned long. The lbr nr won't be a negative number, so make
it "unsigned int" as well.

Suggested-by: Peter Zijlstra <peterz@infradead.org>
Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Andi Kleen <ak@linux.intel.com>
---
 arch/x86/events/perf_event.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/8] KVM: arm/arm64: vgic: Add LPI translation cache definition
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Add the basic data structure that expresses an MSI to LPI
translation as well as the allocation/release hooks.

THe size of the cache is arbitrarily defined as 4*nr_vcpus.

Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 include/kvm/arm_vgic.h        | 10 ++++++++++
 virt/kvm/arm/vgic/vgic-init.c | 34 ++++++++++++++++++++++++++++++++++
 virt/kvm/arm/vgic/vgic-its.c  |  2 ++
 virt/kvm/arm/vgic/vgic.h      |  3 +++
 4 files changed, 49 insertions(+)

```
#### [PATCH v2 1/3] KVM: LAPIC: Make lapic timer unpinned when timer is injected by posted-interrupt
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Make lapic timer unpinned when timer is injected by posted-interrupt,
the emulated timer can be offload to the housekeeping cpus.

The host admin should fine tuned, e.g. dedicated instances scenario 
w/ nohz_full cover the pCPUs which vCPUs resident, several pCPUs 
surplus for housekeeping, disable mwait/hlt/pause vmexits to occupy 
the pCPUs, fortunately preemption timer is disabled after mwait is 
exposed to guest which makes emulated timer offload can be possible. 

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c            | 20 ++++++++++++++++----
 arch/x86/kvm/x86.c              |  5 +++++
 arch/x86/kvm/x86.h              |  2 ++
 include/linux/sched/isolation.h |  2 ++
 kernel/sched/isolation.c        |  6 ++++++
 5 files changed, 31 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: nVMX: Rename prepare_vmcs02_*_full to prepare_vmcs02_*_extra
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
These function do not prepare the entire state of the vmcs02, only the
rarely needed parts.  Rename them to make this clearer.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: introduce is_pae_paging
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Checking for 32-bit PAE is quite common around code that fiddles with
the PDPTRs.  Add a function to compress all checks into a single
invocation.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 3 +--
 arch/x86/kvm/vmx/vmx.c    | 4 ++--
 arch/x86/kvm/x86.c        | 8 ++++----
 arch/x86/kvm/x86.h        | 5 +++++
 4 files changed, 12 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: x86: move MSR_IA32_POWER_CTL handling to common code
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Make it available to AMD hosts as well, just in case someone is trying
to use an Intel processor's CPUID setup.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/include/asm/kvm_host.h | 1 +
 arch/x86/kvm/vmx/vmx.c          | 6 ------
 arch/x86/kvm/vmx/vmx.h          | 2 --
 arch/x86/kvm/x86.c              | 6 ++++++
 4 files changed, 7 insertions(+), 8 deletions(-)

```
#### [PATCH RFC 1/1] allow to specify additional config data
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Add a rough implementation for vfio-ap.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 mdevctl.libexec | 25 ++++++++++++++++++++++
 mdevctl.sbin    | 56 ++++++++++++++++++++++++++++++++++++++++++++++++-
 2 files changed, 80 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/9] s390/cio: Squash cp_free() and cp_unpin_free()
##### From: Eric Farman <farman@linux.ibm.com>

```c
The routine cp_free() does nothing but call cp_unpin_free(), and while
most places call cp_free() there is one caller of cp_unpin_free() used
when the cp is guaranteed to have not been marked initialized.

This seems like a dubious way to make a distinction, so let's combine
these routines and make cp_free() do all the work.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
The RFC version of this patch received r-b's from Farhan [1] and
Pierre [2].  This patch is almost identical to that one, but I
opted to not include those tags because of the cp->initialized
check that now has an impact here.  I still think this patch makes
sense, but want them (well, Farhan) to have a chance to look it
over since it's been six or seven months.

[1] https://patchwork.kernel.org/comment/22310411/
[2] https://patchwork.kernel.org/comment/22317927/
---
 drivers/s390/cio/vfio_ccw_cp.c | 36 +++++++++++++++-------------------
 1 file changed, 16 insertions(+), 20 deletions(-)

```
#### [PATCH v4 1/8] s390/mm: force swiotlb for protected virtualization
##### From: Halil Pasic <pasic@linux.ibm.com>

```c
On s390, protected virtualization guests have to use bounced I/O
buffers.  That requires some plumbing.

Let us make sure, any device that uses DMA API with direct ops correctly
is spared from the problems, that a hypervisor attempting I/O to a
non-shared page would bring.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 arch/s390/Kconfig                   |  4 +++
 arch/s390/include/asm/mem_encrypt.h | 18 +++++++++++
 arch/s390/mm/init.c                 | 47 +++++++++++++++++++++++++++++
 3 files changed, 69 insertions(+)
 create mode 100644 arch/s390/include/asm/mem_encrypt.h

```
#### [PATCH v4] KVM: x86: Add Intel CPUID.1F cpuid emulation support
##### From: Like Xu <like.xu@linux.intel.com>

```c
Add support to expose Intel V2 Extended Topology Enumeration Leaf for
some new systems with multiple software-visible die within each package.

Because unimplemented and unexposed leaves should be explicitly reported
as zero, there is no need to limit cpuid.0.eax to the maximum value of
feature configuration but limit it to the highest leaf implemented in
the current code. A single clamping seems sufficient and cheaper.

Co-developed-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---

==changelog==

v4:
- Limited cpuid.0.eax to the highest leaf implemented in KVM

v3: https://lkml.org/lkml/2019/5/26/64
- Refine commit message and comment

v2: https://lkml.org/lkml/2019/4/25/1246

- Apply cpuid.1f check rule on Intel SDM page 3-222 Vol.2A
- Add comment to handle 0x1f anf 0xb in common code
- Reduce check time in a descending-break style

v1: https://lkml.org/lkml/2019/4/22/28
---
 arch/x86/kvm/cpuid.c | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH] vhost: Don't use defined in VHOST_ARCH_CAN_ACCEL_UACCESS definition
##### From: Nathan Chancellor <natechancellor@gmail.com>

```c
Clang warns:

  drivers/vhost/vhost.c:2085:5: warning: macro expansion producing
  'defined' has undefined behavior [-Wexpansion-to-defined]
  #if VHOST_ARCH_CAN_ACCEL_UACCESS
      ^
  drivers/vhost/vhost.h:98:38: note: expanded from macro
  'VHOST_ARCH_CAN_ACCEL_UACCESS'
  #define VHOST_ARCH_CAN_ACCEL_UACCESS defined(CONFIG_MMU_NOTIFIER) && \
                                       ^

Rework VHOST_ARCH_CAN_ACCEL_UACCESS to be defined under those conditions
so that the meaning of the code doesn't change and clang no longer
warns.

Fixes: 7f466032dc9e ("vhost: access vq metadata through kernel virtual address")
Link: https://github.com/ClangBuiltLinux/linux/issues/508
Signed-off-by: Nathan Chancellor <natechancellor@gmail.com>
Reviewed-by: Nathan Chancellor <natechancellor@gmail.com>
Tested-by: Nathan Chancellor <natechancellor@gmail.com>
---
 drivers/vhost/vhost.c | 44 +++++++++++++++++++++----------------------
 drivers/vhost/vhost.h |  7 ++++---
 2 files changed, 26 insertions(+), 25 deletions(-)

```
