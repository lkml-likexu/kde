#### [PATCH RESEND v4 1/9] Documentation: Introduce EPT based Subpage Protection
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Co-developed-by: yi.z.zhang@linux.intel.com
Signed-off-by: yi.z.zhang@linux.intel.com
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 Documentation/virtual/kvm/spp_kvm.txt | 173 ++++++++++++++++++++++++++
 1 file changed, 173 insertions(+)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt

diff --git a/Documentation/virtual/kvm/spp_kvm.txt b/Documentation/virtual/kvm/spp_kvm.txt
new file mode 100644
index 000000000000..072fa86f14d3
--- /dev/null
+++ b/Documentation/virtual/kvm/spp_kvm.txt
@@ -0,0 +1,173 @@
+EPT-Based Sub-Page Protection (SPP) for KVM
+====================================================
+
+1.Overview
+  EPT-based Sub-Page Protection(SPP) allows VMM to specify
+  fine-grained(128byte per sub-page) write-protection for guest physical
+  memory. When it's enabled, the CPU enforces write-access permission
+  for the sub-pages within a 4KB page, if corresponding bit is set in
+  permission vector, write to sub-page region is allowed, otherwise,
+  it's prevented with a EPT violation.
+
+2.SPP Operation
+  Sub-Page Protection Table (SPPT) is introduced to manage sub-page
+  write-access permission.
+
+  It is active when:
+  a) large paging is disabled on host side.
+  b) "sub-page write protection" VM-execution control is 1.
+  c) SPP is initialized with KVM_INIT_SPP ioctl successfully.
+  d) Sub-page permissions are set with KVM_SUBPAGES_SET_ACCESS ioctl
+     successfully. see below sections for details.
+
+  __________________________________________________________________________
+
+  How SPP hardware works:
+  __________________________________________________________________________
+
+  Guest write access --> GPA --> Walk EPT --> EPT leaf entry -----|
+  |---------------------------------------------------------------|
+  |-> if VMexec_control.spp && ept_leaf_entry.spp_bit (bit 61)
+       |
+       |-> <false> --> EPT legacy behavior
+       |
+       |
+       |-> <true>  --> if ept_leaf_entry.writable
+                        |
+                        |-> <true>  --> Ignore SPP
+                        |
+                        |-> <false> --> GPA --> Walk SPP 4-level table--|
+                                                                        |
+  |------------<----------get-the-SPPT-point-from-VMCS-filed-----<------|
+  |
+  Walk SPP L4E table
+  |
+  |---> if-entry-misconfiguration ------------>-------|-------<---------|
+   |                                                  |                 |
+  else                                                |                 |
+   |                                                  |                 |
+   |   |------------------SPP VMexit<-----------------|                 |
+   |   |                                                                |
+   |   |-> exit_qualification & sppt_misconfig --> sppt misconfig       |
+   |   |                                                                |
+   |   |-> exit_qualification & sppt_miss --> sppt miss                 |
+   |---|                                                                |
+       |                                                                |
+  walk SPPT L3E--|--> if-entry-misconfiguration------------>------------|
+                 |                                                      |
+                else                                                    |
+                 |                                                      |
+                 |                                                      |
+          walk SPPT L2E --|--> if-entry-misconfiguration-------->-------|
+                          |                                             |
+                         else                                           |
+                          |                                             |
+                          |                                             |
+                   walk SPPT L1E --|-> if-entry-misconfiguration--->----|
+                                   |
+                                 else
+                                   |
+                                   |-> if sub-page writable
+                                   |-> <true>  allow, write access
+                                   |-> <false> disallow, EPT violation
+  ______________________________________________________________________________
+
+3.IOCTL Interfaces
+
+    KVM_INIT_SPP:
+    Allocate storage for sub-page permission vectors and SPPT root page.
+
+    KVM_SUBPAGES_GET_ACCESS:
+    Get sub-page write permission vectors for given continuous guest pages.
+
+    KVM_SUBPAGES_SET_ACCESS
+    Set sub-pages write permission vectors for given continuous guest pages.
+
+    /* for KVM_SUBPAGES_GET_ACCESS and KVM_SUBPAGES_SET_ACCESS */
+    struct kvm_subpage_info {
+       __u64 gfn; /* the first page gfn of the continuous pages */
+       __u64 npages; /* number of 4K pages */
+       __u64 *access_map; /* sub-page write-access bitmap array */
+    };
+
+    #define KVM_SUBPAGES_GET_ACCESS   _IOR(KVMIO,  0x49, __u64)
+    #define KVM_SUBPAGES_SET_ACCESS   _IOW(KVMIO,  0x4a, __u64)
+    #define KVM_INIT_SPP              _IOW(KVMIO,  0x4b, __u64)
+
+4.Set Sub-Page Permission
+
+  * To enable SPP protection, system admin sets sub-page permission via
+    KVM_SUBPAGES_SET_ACCESS ioctl:
+
+    (1) If the target 4KB pages are there, it locates EPT leaf entries
+        via the guest physical addresses, sets the bit 61 of the corresponding 
+        entries to enable sub-page protection, then set up SPPT paging structure.
+    (2) otherwise, stores the [gfn,permission] mappings in KVM data structure. When
+        EPT page-fault is generated due to access to target page, it settles
+        EPT entry configuration together with SPPT setup, this is called lazy mode
+        setup.
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
+5.SPPT-induced VM exit
+
+  * SPPT miss and misconfiguration induced VM exit
+
+    A SPPT missing VM exit occurs when walk the SPPT, there is no SPPT
+    misconfiguration but a paging-structure entry is not
+    present in any of L4E/L3E/L2E entries.
+
+    A SPPT misconfiguration VM exit occurs when reserved bits or unsupported values
+    are set in SPPT entry.
+
+    *NOTE* SPPT miss and SPPT misconfigurations can occur only due to an
+    attempt to write memory with a guest physical address.
+
+  * SPP permission induced VM exit
+    SPP sub-page permission induced violation is reported as EPT violation
+    thesefore causes VM exit.
+
+6.SPPT-induced VM exit handling
+
+  #define EXIT_REASON_SPP                 66
+
+  static int (*const kvm_vmx_exit_handlers[])(struct kvm_vcpu *vcpu) = {
+    ...
+    [EXIT_REASON_SPP]                     = handle_spp,
+    ...
+  };
+
+  New exit qualification for SPPT-induced vmexits.
+
+  | Bit   | Contents                                                          |
+  | :---- | :---------------------------------------------------------------- |
+  | 10:0  | Reserved (0).                                                     |
+  | 11    | SPPT VM exit type. Set for SPPT Miss, cleared for SPPT Misconfig. |
+  | 12    | NMI unblocking due to IRET                                        |
+  | 63:13 | Reserved (0)                                                      |
+
+  In addition to the exit qualification, guest linear address and guest
+  physical address fields will be reported.
+
+  * SPPT miss and misconfiguration induced VM exit
+    Allocate a physical page for the SPPT and set the entry correctly.
+
+  * SPP permission induced VM exit
+    This kind of VM exit is left to VMI tool to handle.

From patchwork Wed Aug 14 07:03:56 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11093385
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0C467912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Aug 2019 07:03:14 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id E8AD62872E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Aug 2019 07:03:13 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id DCC7C28732; Wed, 14 Aug 2019 07:03:13 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 649DE2872E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 14 Aug 2019 07:03:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727526AbfHNHCd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 14 Aug 2019 03:02:33 -0400
Received: from mga04.intel.com ([192.55.52.120]:42220 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727371AbfHNHC3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 14 Aug 2019 03:02:29 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 14 Aug 2019 00:02:28 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,384,1559545200";
   d="scan'208";a="181427097"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga006.jf.intel.com with ESMTP; 14 Aug 2019 00:02:26 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: mst@redhat.com, rkrcmar@redhat.com, jmattson@google.com,
        yu.c.zhang@intel.com, alazar@bitdefender.com,
        Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH RESEND v4 2/9] KVM: VMX: Add control flags for SPP enabling
Date: Wed, 14 Aug 2019 15:03:56 +0800
Message-Id: <20190814070403.6588-3-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20190814070403.6588-1-weijiang.yang@intel.com>
References: <20190814070403.6588-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

Check SPP capability in MSR_IA32_VMX_PROCBASED_CTLS2, its 23-bit
indicates SPP support. Mark SPP bit in CPU capabilities bitmap if
it's supported.

Co-developed-by: He Chen <he.chen@linux.intel.com>
Signed-off-by: He Chen <he.chen@linux.intel.com>
Co-developed-by: Zhang Yi <yi.z.zhang@linux.intel.com>
Signed-off-by: Zhang Yi <yi.z.zhang@linux.intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/cpufeatures.h |  1 +
 arch/x86/include/asm/vmx.h         |  1 +
 arch/x86/kernel/cpu/intel.c        |  4 ++++
 arch/x86/kvm/vmx/capabilities.h    |  5 +++++
 arch/x86/kvm/vmx/vmx.c             | 10 ++++++++++
 5 files changed, 21 insertions(+)

```
#### [PATCH V2 1/3] x86/Hyper-V: Fix definition of struct hv_vp_assist_page
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
#### [PATCH 1/3] selftests: kvm: do not try running the VM in vmx_set_nested_state_test
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
This test is only covering various edge cases of the
KVM_SET_NESTED_STATE ioctl.  Running the VM does not really
add anything.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 .../selftests/kvm/x86_64/vmx_set_nested_state_test.c      | 15 ---------------
 1 file changed, 15 deletions(-)

```
