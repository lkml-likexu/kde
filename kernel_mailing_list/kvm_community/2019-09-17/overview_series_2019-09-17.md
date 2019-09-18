#### [PATCH 1/3] KVM: Fix coalesced mmio ring buffer out-of-bounds access
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11148181
Return-Path: <SRS0=dK0e=XM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BCA62912
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 08:16:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 93B0720678
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 08:16:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="XMfUu4yb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730223AbfIQIQe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Sep 2019 04:16:34 -0400
Received: from mail-pl1-f195.google.com ([209.85.214.195]:40142 "EHLO
        mail-pl1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725798AbfIQIQe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Sep 2019 04:16:34 -0400
Received: by mail-pl1-f195.google.com with SMTP id d22so1178444pll.7;
        Tue, 17 Sep 2019 01:16:33 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=lZpOV5nkYn4l+QDXD4wMM0QQ6pVGsg20H5ZmBWn5rFY=;
        b=XMfUu4ybyUbjaSQkc+G9xwv+FR7+SYPvEL9Au1fqvVxr5h+D75ZPor60PYddm3kRFN
         Nl17VEv+RnGNOjmQGn2murgOaEzjIqEAPfvyQIwJLfb7UKfl75QEET7wnkAsxhXl5reZ
         0dcBq4BSZBzBOm5xAZkv4cPm+qZBbc3G2f0zm/g4NCObOOIZTXCeHOaTXEkdY2twPdKb
         gagOsiBm0jYDskJ59NLZDdbeq/ZzDedazC90wFT+oFEHxo8V0cj3zwm7jD4GYXChgCB3
         flHvSawC/l/Qv9DvXaRm0Prx4z/qvrA5CZwTO3amxCGo/fekS2MpplfH1kyQAo2HL0g+
         YeHg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=lZpOV5nkYn4l+QDXD4wMM0QQ6pVGsg20H5ZmBWn5rFY=;
        b=ccy85uHNQ/ZSrKqkJKMCGBj22fUjnqHUiT7Rz9SEqDtN3EZJEpBfBM58dmNMkp8YKF
         a10ATPiRQ5hU6juW6pAqBjTdNrtEzTysagWwd6eL3pySN/Qh9Bf8ADoFWMvcpAYhsH2E
         gEmBt4bpCq4ymVJH5vt5PBoQwRboHMBu6/XrZ99OAB8oxlN1okPvh+9jp8WJPkxIy9PA
         svjUmAFrVyinz6eKKMbX53BB1lu81ubimKP78BCTLSaRBHs4tO5IaENkvRiDDDoB2Srw
         pJrSokpGuTnIkRq3oYweePdwTLoUoyBzDpBItXGos0cR2F4VO9UvjXdhFNuPH8kjCVkG
         zY8Q==
X-Gm-Message-State: APjAAAXARhfHbawggQW+8foBaVNlf/5ZYu3GntSipnffpR0QU+66+jbR
        IhX7xaOzKxWEFhgm7SHrnXQY577p
X-Google-Smtp-Source: 
 APXvYqzNMalAy4NbEJMNfObcCqA9c0UoX5pztAHwrAbtwPMPP4mPFTKD26DkYq65IQVyqtWa82QGOQ==
X-Received: by 2002:a17:902:8546:: with SMTP id
 d6mr2429121plo.170.1568708193274;
        Tue, 17 Sep 2019 01:16:33 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.123])
        by smtp.googlemail.com with ESMTPSA id
 j10sm1924142pfh.137.2019.09.17.01.16.29
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-SHA bits=128/128);
        Tue, 17 Sep 2019 01:16:32 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 stable@vger.kernel.org
Subject: [PATCH 1/3] KVM: Fix coalesced mmio ring buffer out-of-bounds access
Date: Tue, 17 Sep 2019 16:16:24 +0800
Message-Id: <1568708186-20260-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Reported by syzkaller:

	#PF: supervisor write access in kernel mode
	#PF: error_code(0x0002) - not-present page
	PGD 403c01067 P4D 403c01067 PUD 0
	Oops: 0002 [#1] SMP PTI
	CPU: 1 PID: 12564 Comm: a.out Tainted: G           OE     5.3.0-rc4+ #4
	RIP: 0010:coalesced_mmio_write+0xcc/0x130 [kvm]
	Call Trace:
	 __kvm_io_bus_write+0x91/0xe0 [kvm]
	 kvm_io_bus_write+0x79/0xf0 [kvm]
	 write_mmio+0xae/0x170 [kvm]
	 emulator_read_write_onepage+0x252/0x430 [kvm]
	 emulator_read_write+0xcd/0x180 [kvm]
	 emulator_write_emulated+0x15/0x20 [kvm]
	 segmented_write+0x59/0x80 [kvm]
	 writeback+0x113/0x250 [kvm]
	 x86_emulate_insn+0x78c/0xd80 [kvm]
	 x86_emulate_instruction+0x386/0x7c0 [kvm]
	 kvm_mmu_page_fault+0xf9/0x9e0 [kvm]
	 handle_ept_violation+0x10a/0x220 [kvm_intel]
	 vmx_handle_exit+0xbe/0x6b0 [kvm_intel]
	 vcpu_enter_guest+0x4dc/0x18d0 [kvm]
	 kvm_arch_vcpu_ioctl_run+0x407/0x660 [kvm]
	 kvm_vcpu_ioctl+0x3ad/0x690 [kvm]
	 do_vfs_ioctl+0xa2/0x690
	 ksys_ioctl+0x6d/0x80
	 __x64_sys_ioctl+0x1a/0x20
	 do_syscall_64+0x74/0x720
	 entry_SYSCALL_64_after_hwframe+0x49/0xbe
	RIP: 0010:coalesced_mmio_write+0xcc/0x130 [kvm]

Both the coalesced_mmio ring buffer indexs ring->first and ring->last are 
bigger than KVM_COALESCED_MMIO_MAX from the testcase, array out-of-bounds 
access triggers by ring->coalesced_mmio[ring->last].phys_addr = addr; 
assignment. This patch fixes it by mod indexs by KVM_COALESCED_MMIO_MAX.

syzkaller source: https://syzkaller.appspot.com/x/repro.c?x=134b2826a00000

Reported-by: syzbot+983c866c3dd6efa3662a@syzkaller.appspotmail.com
Cc: stable@vger.kernel.org
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 virt/kvm/coalesced_mmio.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v5 1/9] Documentation: Introduce EPT based Subpage Protection
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11148305
Return-Path: <SRS0=dK0e=XM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4446A16B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 08:53:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2B0D8218AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 08:53:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725825AbfIQIw4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Sep 2019 04:52:56 -0400
Received: from mga18.intel.com ([134.134.136.126]:37165 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725920AbfIQIw3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Sep 2019 04:52:29 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 17 Sep 2019 01:52:28 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,515,1559545200";
   d="scan'208";a="193695464"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by FMSMGA003.fm.intel.com with ESMTP; 17 Sep 2019 01:52:27 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: mst@redhat.com, rkrcmar@redhat.com, jmattson@google.com,
        yu.c.zhang@intel.com, alazar@bitdefender.com,
        Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v5 1/9] Documentation: Introduce EPT based Subpage Protection
Date: Tue, 17 Sep 2019 16:52:56 +0800
Message-Id: <20190917085304.16987-2-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20190917085304.16987-1-weijiang.yang@intel.com>
References: <20190917085304.16987-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Co-developed-by: yi.z.zhang@linux.intel.com
Signed-off-by: yi.z.zhang@linux.intel.com
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 Documentation/virtual/kvm/spp_kvm.txt | 178 ++++++++++++++++++++++++++
 1 file changed, 178 insertions(+)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt

diff --git a/Documentation/virtual/kvm/spp_kvm.txt b/Documentation/virtual/kvm/spp_kvm.txt
new file mode 100644
index 000000000000..1bd1c11d0a99
--- /dev/null
+++ b/Documentation/virtual/kvm/spp_kvm.txt
@@ -0,0 +1,178 @@
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
+  *Note*: In current implementation, SPP is exclusive with nested flag,
+  if it's on, SPP feature won't work.
+
+2.SPP Operation
+  Sub-Page Protection Table (SPPT) is introduced to manage sub-page
+  write-access permission.
+
+  It is active when:
+  a) nested flag is turned off.
+  b) "sub-page write protection" VM-execution control is 1.
+  c) SPP is initialized with KVM_INIT_SPP ioctl.
+  d) Sub-page permissions are set with KVM_SUBPAGES_SET_ACCESS ioctl.
+     see below sections for details.
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
+    Set SPP bit in EPT leaf entries for given continuous guest pages. The
+    actual SPPT setup is triggered when SPP miss vm-exit is handled.
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
+    (1) It first stores the access permissions in bitmap array.
+
+    (2) Then, if the target 4KB page is mapped as PT_PAGE_TABLE_LEVEL entry in EPT,
+	it sets SPP bit of the corresponding entry to mark sub-page protection.
+	If the 4KB page is mapped as PT_DIRECTORY_LEVEL or PT_PDPE_LEVEL, it
+	zapps the hugepage entry and let following memroy access to trigger EPT
+	page fault, there the gfn is check against SPP permission bitmap and
+	proper level is selected to set up EPT entry.
+
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
+    Set up SPPT entries correctly.
+
+  * SPP permission induced VM exit
+    This kind of VM exit is left to VMI tool to handle.

From patchwork Tue Sep 17 08:52:57 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11148301
Return-Path: <SRS0=dK0e=XM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F2CC01708
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 08:53:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DA91C2196F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 08:53:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726207AbfIQIw4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Sep 2019 04:52:56 -0400
Received: from mga18.intel.com ([134.134.136.126]:37165 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725951AbfIQIwb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Sep 2019 04:52:31 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga003.fm.intel.com ([10.253.24.29])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 17 Sep 2019 01:52:30 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,515,1559545200";
   d="scan'208";a="193695473"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by FMSMGA003.fm.intel.com with ESMTP; 17 Sep 2019 01:52:28 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Cc: mst@redhat.com, rkrcmar@redhat.com, jmattson@google.com,
        yu.c.zhang@intel.com, alazar@bitdefender.com,
        Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v5 2/9] vmx: spp: Add control flags for Sub-Page
 Protection(SPP)
Date: Tue, 17 Sep 2019 16:52:57 +0800
Message-Id: <20190917085304.16987-3-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20190917085304.16987-1-weijiang.yang@intel.com>
References: <20190917085304.16987-1-weijiang.yang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Check SPP capability in MSR_IA32_VMX_PROCBASED_CTLS2, its 23-bit
indicates SPP capability. Enable SPP feature bit in CPU capabilities
bitmap if it's supported.

Co-developed-by: He Chen <he.chen@linux.intel.com>
Signed-off-by: He Chen <he.chen@linux.intel.com>
Co-developed-by: Zhang Yi <yi.z.zhang@linux.intel.com>
Signed-off-by: Zhang Yi <yi.z.zhang@linux.intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/cpufeatures.h |  1 +
 arch/x86/include/asm/vmx.h         |  1 +
 arch/x86/kernel/cpu/intel.c        |  4 ++++
 arch/x86/kvm/mmu.h                 |  2 ++
 arch/x86/kvm/vmx/capabilities.h    |  5 +++++
 arch/x86/kvm/vmx/vmx.c             | 10 ++++++++++
 6 files changed, 23 insertions(+)

```
#### [kvm-unit-tests PATCH v3 1/2] x86: nvmx: fix bug in __enter_guest()From: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Orr <marcorr@google.com>
X-Patchwork-Id: 11149333
Return-Path: <SRS0=dK0e=XM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3293816B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 18:58:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0AEA021670
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 18:58:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="dgfCsN8c"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728238AbfIQS57 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Sep 2019 14:57:59 -0400
Received: from mail-pg1-f202.google.com ([209.85.215.202]:54254 "EHLO
        mail-pg1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725927AbfIQS56 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Sep 2019 14:57:58 -0400
Received: by mail-pg1-f202.google.com with SMTP id j9so2563616pgk.20
        for <kvm@vger.kernel.org>; Tue, 17 Sep 2019 11:57:58 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=4S7/wfUBRRdORQOL8HzLDNrFII6NZGP9NSs87iEQGJI=;
        b=dgfCsN8cXfYnMLyzDSHD5sRPiVf/J13oZ/+EDolHwLnb6vq/O7xePnl1T8Q6gvgq5c
         eqRoHxCkus+ct8GtS52CofjODKVIv3sq3uVLuOUc0vDG+lYJI6MWUOEbfwJhaaZCc5P2
         EptVTB652w8K9dL5DmNzGb5nhp1K0S3jKvOrI41YmzRhvchfWAqFhpk18jZc7XmUrD8n
         g/K+nJWkhjwcD6qHNEktWt0XpZM9oF8nJVecEGP9pSXz+6sSp7bawYJdLG/mC+RxxDS3
         obQzEzx1wex1SPKeVDBIPAz5aY5Yx8I4kSnz0yvI1Cvk3WS1iwTFAJh+qHGNmj9u5Q4U
         odYg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=4S7/wfUBRRdORQOL8HzLDNrFII6NZGP9NSs87iEQGJI=;
        b=phhEJWAmcYzSdmX0pW82ZimdBWNpNL/uoeSqPAKiiYtqLLYepeH08TrT1XteHvnvwa
         PoHnj/lbuUhZnUu2Hnw7vp5ngXYNdlX4JIfpxT+OtEvIOqsoSHydFc5sArAOyJ/H/gQW
         v4x1hNUhotE29Msun1taM2p1/RGDsyHirKOV1cXyKouE8d9EASXzqw3hgbXd4J6jDpl3
         ekqYzipFPu/Y0gkY5cXwnkYUr9Q7I8Bo87qQorJP/swxSQgUZfARK99jXbKOWksV0GNf
         raAv4jWEYSHKeQbxU3WsWNyWzv9PVULpVmkt9Nv9N7twTcUDYte7QAWCfR27aleenNLP
         gmSQ==
X-Gm-Message-State: APjAAAUA+opERjhYNj17/uIIMihg4oHpLjfm1uKvR9UtyEe2b68+hMPS
        nWEb0GDE1SVYJI97r90vzveQ2VTDCWpXE0elM7DOCVOav0XYAivn1N6ZSsVhdOX+c0v3Mw+E+Cd
        gOfL9/DT+2/mSkNxZN8tV29PaSvtynhpbfuSq3gUff7MEn4pfp0Js7qoKy8CD
X-Google-Smtp-Source: 
 APXvYqzKuoJV5x6zfHavf5YI3H7e/wI8+fl8XKqlyhyLaY4M3D44ha3MNDbzFoqUNiDLE6YRU0JgT7QP17Mx
X-Received: by 2002:a65:6294:: with SMTP id f20mr285699pgv.349.1568746677809;
 Tue, 17 Sep 2019 11:57:57 -0700 (PDT)
Date: Tue, 17 Sep 2019 11:57:52 -0700
Message-Id: <20190917185753.256039-1-marcorr@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.237.gc6a4ce50a0-goog
Subject: [kvm-unit-tests PATCH v3 1/2] x86: nvmx: fix bug in __enter_guest()
From: Marc Orr <marcorr@google.com>
To: kvm@vger.kernel.org, jmattson@google.com, pshier@google.com,
        sean.j.christopherson@intel.com, krish.sadhukhan@oracle.com
Cc: Marc Orr <marcorr@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

__enter_guest() should only set the launched flag when a launch has
succeeded. Thus, don't set the launched flag when the VMX_ENTRY_FAILURE,
bit 31, is set in the VMCS exit reason.

Signed-off-by: Marc Orr <marcorr@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 x86/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v4 1/2] x86: nvmx: fix bug in __enter_guest()From: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Orr <marcorr@google.com>
X-Patchwork-Id: 11149373
Return-Path: <SRS0=dK0e=XM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9A8AA14E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 20:16:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 682222171F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 20:16:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="wLB+pIE8"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726843AbfIQUQH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Sep 2019 16:16:07 -0400
Received: from mail-qt1-f201.google.com ([209.85.160.201]:40233 "EHLO
        mail-qt1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726283AbfIQUQH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Sep 2019 16:16:07 -0400
Received: by mail-qt1-f201.google.com with SMTP id k22so5523135qtm.7
        for <kvm@vger.kernel.org>; Tue, 17 Sep 2019 13:16:06 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=mksV2ZBhYV4orXZIdrmZTUy75KtkMwvBQEMRJp8a6+Q=;
        b=wLB+pIE8lHKlsV0I6t9jXUjZHLE+gESWNhrhHH094vlD3DDFsYpw3u/yyBWsSb6eRM
         ghrcablsmLGydlELdxo9TQkdXbQF7Ktd+S0RH/it24pOtq8XC4oEHk0lNVFPygLs7z1O
         C53GkDmtZ8TfDBIKVQfSEe9NyBoTHnB6+3u1a97U9+RkzLk8CnAMtiHCb8W+lZZ6+rTD
         6Dd4bXlNgJRrYyP79U/gRp64jnOuHEUkwByLRdXUyHKgEEVAnOsFxH8nkd6dCiplvWXs
         K8pNC6Aoz38mL4PFKE2dtjKIhtrjWLPrAjZ0iAsb7HLfb8FM4QlnqaBvg7ZQ5+K2P/ZD
         ew7Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=mksV2ZBhYV4orXZIdrmZTUy75KtkMwvBQEMRJp8a6+Q=;
        b=Q0u29uHbB1EwMSh2I2BX3meXscLWYYBpvvIPCzuelnppMI2ykKRIdvFkVb9zr91qu+
         zBNvVblAYrUBaAHSbBFIKgqJII/vyMIJcHwKEYL462yhuFOKjZchZS6ZeiwD1Ww5x7sO
         IUWZMdUiDRR+Ju34Azo5G6pYLAeQgui9/Uj1gYHGQQ3z4N+qXEK/DS2tilYH8RDU2seR
         Gb6Je2zWqPv4z20uJ3aty8yW9hhPI3RaxH1a7e6LR5peMAqLCJ5eJEpd2LXh5Po6JffW
         4U2GDJbjDpfy938A28QS9rdphQlZDyeU6Wfjncp94W4u8PNiafPNxkehTZGBEJbvSCef
         ZpVQ==
X-Gm-Message-State: APjAAAVg2j5ywjn5NC0W0Ckahw0oDBLJvjJmMUWi8Q+ZzAhqtl9kykfc
        2nq1HiJ4Cc6Oqd4w+6+8ta8uBn1hW/yGlZUeC/pDaHxyP+PSiUnDKce7riV8M0FSJ62E6lfddlJ
        9hgrlrgZoBYRr2cTk87prjifZmUmKfdln7GxfRwY36gEqFPquuq/K+0aebtaL
X-Google-Smtp-Source: 
 APXvYqyHmMwFj12Wr3DKtXac35BiQY8QXELQr9F/vLfC4yxKm19hK36C1XDf4ChOa9fjPiWufWSu7rmmYFKK
X-Received: by 2002:ae9:f113:: with SMTP id k19mr259393qkg.377.1568751366029;
 Tue, 17 Sep 2019 13:16:06 -0700 (PDT)
Date: Tue, 17 Sep 2019 13:16:01 -0700
Message-Id: <20190917201602.113133-1-marcorr@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.237.gc6a4ce50a0-goog
Subject: [kvm-unit-tests PATCH v4 1/2] x86: nvmx: fix bug in __enter_guest()
From: Marc Orr <marcorr@google.com>
To: kvm@vger.kernel.org, jmattson@google.com, pshier@google.com,
        sean.j.christopherson@intel.com, krish.sadhukhan@oracle.com
Cc: Marc Orr <marcorr@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

__enter_guest() should only set the launched flag when a launch has
succeeded. Thus, don't set the launched flag when the VMX_ENTRY_FAILURE,
bit 31, is set in the VMCS exit reason.

Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Marc Orr <marcorr@google.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3] kvm: nvmx: limit atomic switch MSRsFrom: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Orr <marcorr@google.com>
X-Patchwork-Id: 11149321
Return-Path: <SRS0=dK0e=XM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9416516B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 18:51:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5DF95214AF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 18:51:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="QgDOcQb+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727936AbfIQSvG (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 17 Sep 2019 14:51:06 -0400
Received: from mail-qk1-f201.google.com ([209.85.222.201]:33124 "EHLO
        mail-qk1-f201.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725865AbfIQSvG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 17 Sep 2019 14:51:06 -0400
Received: by mail-qk1-f201.google.com with SMTP id w198so3467502qka.0
        for <kvm@vger.kernel.org>; Tue, 17 Sep 2019 11:51:05 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=NMPWcurabeQXP7vAPNbg7afSkO+tYJpZfmXbtM2pzw8=;
        b=QgDOcQb+FZoMyFo0XV1gnldIvWLAV4jPghdUNU48j9HlGtYL+buXxH3tB78MCDeh9v
         d6aojj3/dYSQul7X3GbSH3bJKSKj74rRg3VYXCOT9Ywh8xej73KmL4WCbBDWlk0BZQCf
         86JLynF7K63QiJSoFTls4kFw4OL9tphAFnztjUR7n4h/VptK5ihGS/6vQ0HGBxUBZ1NS
         NHDcZVUjN/23DOvVScDcqr3zDarKZWBgry6CQvhmPS7CQkPL/7p6/vXUBVZCwTUlR5JT
         Dq39gPNvdAoS8nLEoiczAFU4obcWkCzPrB1c6SjJysQx36mv8tyj3ABHaa2i/Z4Ob3U5
         sKYg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=NMPWcurabeQXP7vAPNbg7afSkO+tYJpZfmXbtM2pzw8=;
        b=Gqa1Nb5wE39dYNrzXMarIvewcAFWfGvba7uNBxEFdEs3VKM7T8KRDbIBTeTRDPN1ne
         HQK2rhr2n3qEmtvaDQuzt79jIIilhlWXevcEvwA01N1o52Fw4+ub4O0YKi55Vt1y+LsH
         rq8yGCCAVLYSs+LcAnw26UzuzKW8jXuWdLglY7MljaHsUlHpW5bMoNI7O+0eXU4Anxj6
         WWtZD8TvZJV/Enwwy9yyIv975FxOO9ugEYmrMflP5eOxZ3FQSQA31EwpZ0mBsBDV4bcn
         oYJYlnbcPXWNcWKh+1RVmt4vJAwcOLXhL/7NPgiG7aaa9OcAA1iJVcWkk4VF0oisjxa2
         Aesg==
X-Gm-Message-State: APjAAAWsk9C45jfhxQYWVbkfjr5NIa1gjdKqtN4rfdpy7BiOcaBGBjhQ
        w3pMw0/dMovoSf89p4nupB++pWzypWlm+9SUjqv0VtvpqsXTq5bjX3TrVch2CPFZKQSsXqKdBxJ
        bYETNal7RQws9hSgVhYLS3JhO2mDFSKwV9XCMO/0wKaKeElszO0KkjOSZjRpv
X-Google-Smtp-Source: 
 APXvYqxH1zKHgCyCEQenmMAdiVtMyPQD5NJItLfgxMD8rUdEazhB8Qf4Eu5UbDZXF6WUXZJ87ujmJQviKlli
X-Received: by 2002:a0c:8a6d:: with SMTP id 42mr9207qvu.138.1568746264379;
 Tue, 17 Sep 2019 11:51:04 -0700 (PDT)
Date: Tue, 17 Sep 2019 11:50:57 -0700
Message-Id: <20190917185057.224221-1-marcorr@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.23.0.237.gc6a4ce50a0-goog
Subject: [PATCH v3] kvm: nvmx: limit atomic switch MSRs
From: Marc Orr <marcorr@google.com>
To: kvm@vger.kernel.org, jmattson@google.com, pshier@google.com,
        sean.j.christopherson@intel.com
Cc: Marc Orr <marcorr@google.com>
Content-Type: text/plain; charset="UTF-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allowing an unlimited number of MSRs to be specified via the VMX
load/store MSR lists (e.g., vm-entry MSR load list) is bad for two
reasons. First, a guest can specify an unreasonable number of MSRs,
forcing KVM to process all of them in software. Second, the SDM bounds
the number of MSRs allowed to be packed into the atomic switch MSR lists.
Quoting the "Miscellaneous Data" section in the "VMX Capability
Reporting Facility" appendix:

"Bits 27:25 is used to compute the recommended maximum number of MSRs
that should appear in the VM-exit MSR-store list, the VM-exit MSR-load
list, or the VM-entry MSR-load list. Specifically, if the value bits
27:25 of IA32_VMX_MISC is N, then 512 * (N + 1) is the recommended
maximum number of MSRs to be included in each list. If the limit is
exceeded, undefined processor behavior may result (including a machine
check during the VMX transition)."

Because KVM needs to protect itself and can't model "undefined processor
behavior", arbitrarily force a VM-entry to fail due to MSR loading when
the MSR load list is too large. Similarly, trigger an abort during a VM
exit that encounters an MSR load list or MSR store list that is too large.

The MSR list size is intentionally not pre-checked so as to maintain
compatibility with hardware inasmuch as possible.

Test these new checks with the kvm-unit-test "x86: nvmx: test max atomic
switch MSRs".

Suggested-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Signed-off-by: Marc Orr <marcorr@google.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
v2 -> v3
* Updated commit message.
* Removed superflous function declaration.
* Expanded in-line comment.

 arch/x86/include/asm/vmx.h |  1 +
 arch/x86/kvm/vmx/nested.c  | 44 ++++++++++++++++++++++++++++----------
 2 files changed, 34 insertions(+), 11 deletions(-)

```
#### [RFC v4 1/3] vfio: support getting vfio device from device fd
##### From: Tiwei Bie <tiwei.bie@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tiwei Bie <tiwei.bie@intel.com>
X-Patchwork-Id: 11147967
Return-Path: <SRS0=dK0e=XM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2DFA21708
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 01:05:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0BF27214D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 17 Sep 2019 01:05:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2390686AbfIQBFB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 16 Sep 2019 21:05:01 -0400
Received: from mga04.intel.com ([192.55.52.120]:34819 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727996AbfIQBFB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 16 Sep 2019 21:05:01 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 16 Sep 2019 18:05:01 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,514,1559545200";
   d="scan'208";a="180611948"
Received: from dpdk-virtio-tbie-2.sh.intel.com ([10.67.104.71])
  by orsmga008.jf.intel.com with ESMTP; 16 Sep 2019 18:04:58 -0700
From: Tiwei Bie <tiwei.bie@intel.com>
To: mst@redhat.com, jasowang@redhat.com, alex.williamson@redhat.com,
        maxime.coquelin@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        dan.daly@intel.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, lingshan.zhu@intel.com, tiwei.bie@intel.com
Subject: [RFC v4 1/3] vfio: support getting vfio device from device fd
Date: Tue, 17 Sep 2019 09:02:02 +0800
Message-Id: <20190917010204.30376-2-tiwei.bie@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20190917010204.30376-1-tiwei.bie@intel.com>
References: <20190917010204.30376-1-tiwei.bie@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch introduces the support for getting VFIO device
from VFIO device fd. With this support, it's possible for
vhost to get VFIO device from the group fd and device fd
set by the userspace.

Signed-off-by: Tiwei Bie <tiwei.bie@intel.com>
---
 drivers/vfio/vfio.c  | 25 +++++++++++++++++++++++++
 include/linux/vfio.h |  4 ++++
 2 files changed, 29 insertions(+)

```
