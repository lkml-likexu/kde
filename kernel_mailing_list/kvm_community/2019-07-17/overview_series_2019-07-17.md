#### [PATCH v4 1/9] Documentation: Introduce EPT based Subpage Protection
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
Co-developed-by: yi.z.zhang@linux.intel.com
Signed-off-by: yi.z.zhang@linux.intel.com
Co-developed-by: Yang Weijiang <weijiang.yang@intel.com>
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

From patchwork Wed Jul 17 13:37:44 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11047849
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5D02213BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jul 2019 13:37:28 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 4CE961FF7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jul 2019 13:37:28 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 415272864F; Wed, 17 Jul 2019 13:37:28 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id B3D541FF7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 17 Jul 2019 13:37:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727500AbfGQNgg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 17 Jul 2019 09:36:36 -0400
Received: from mga04.intel.com ([192.55.52.120]:36148 "EHLO mga04.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727483AbfGQNgf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Jul 2019 09:36:35 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga004.fm.intel.com ([10.253.24.48])
  by fmsmga104.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 17 Jul 2019 06:36:34 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,274,1559545200";
   d="scan'208";a="191261841"
Received: from local-michael-cet-test.sh.intel.com ([10.239.159.128])
  by fmsmga004.fm.intel.com with ESMTP; 17 Jul 2019 06:36:34 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com
Cc: mst@redhat.com, rkrcmar@redhat.com, jmattson@google.com,
        yu.c.zhang@intel.com, alazar@bitdefender.com,
        Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v4 2/9] KVM: VMX: Add control flags for SPP enabling
Date: Wed, 17 Jul 2019 21:37:44 +0800
Message-Id: <20190717133751.12910-3-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
In-Reply-To: <20190717133751.12910-1-weijiang.yang@intel.com>
References: <20190717133751.12910-1-weijiang.yang@intel.com>
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
Co-developed-by: Yang Weijiang <weijiang.yang@intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/cpufeatures.h |  1 +
 arch/x86/include/asm/vmx.h         |  1 +
 arch/x86/kernel/cpu/intel.c        |  4 ++++
 arch/x86/kvm/vmx/capabilities.h    |  5 +++++
 arch/x86/kvm/vmx/vmx.c             | 10 ++++++++++
 5 files changed, 21 insertions(+)

```
#### [PATCH] KVM: x86/vPMU: reset pmc->counter to 0 for pmu fixed_counters
##### From: Like Xu <like.xu@linux.intel.com>

```c
To avoid semantic inconsistency, the fixed_counters in Intel vPMU
need to be reset to 0 in intel_pmu_reset() as gp_counters does.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/vmx/pmu_intel.c | 11 ++++++++---
 1 file changed, 8 insertions(+), 3 deletions(-)

```
#### [PATCH V3 01/15] vhost: simplify meta data pointer accessing
##### From: Jason Wang <jasowang@redhat.com>

```c
Instead of open coding meta pointer accessing through caches. This
patch introduces vhost_get_meta_ptr()/vhost_put_meta_ptr() pair to
reduce the code duplication and simplify its callers
implementation. This is helpful for reducing LOC for packed virtqueue
as well.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 207 ++++++++++++++----------------------------
 1 file changed, 70 insertions(+), 137 deletions(-)

```
#### [PULL v2 1/6] vfio-ccw: Fix misleading comment when setting orb.cmd.c64
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Farhan Ali <alifm@linux.ibm.com>

The comment is misleading because it tells us that
we should set orb.cmd.c64 before calling ccwchain_calc_length,
otherwise the function ccwchain_calc_length would return an
error. This is not completely accurate.

We want to allow an orb without cmd.c64, and this is fine
as long as the channel program does not use IDALs. But we do
want to reject any channel program that uses IDALs and does
not set the flag, which is what we do in ccwchain_calc_length.

After we have done the ccw processing, we need to set cmd.c64,
as we use IDALs for all translated channel programs.

Also for better code readability let's move the setting of
cmd.c64 within the non error path.

Fixes: fb9e7880af35 ("vfio: ccw: push down unsupported IDA check")
Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Message-Id: <f68636106aef0faeb6ce9712584d102d1b315ff8.1562854091.git.alifm@linux.ibm.com>
Reviewed-by: Eric Farman <farman@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 13 +++++++------
 1 file changed, 7 insertions(+), 6 deletions(-)

```
#### [PATCH] vfio: re-arrange vfio region definitions
##### From: Cornelia Huck <cohuck@redhat.com>

```c
It is easy to miss already defined region types. Let's re-arrange
the definitions a bit and add more comments to make it hopefully
a bit clearer.

No functional change.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 include/uapi/linux/vfio.h | 19 ++++++++++++-------
 1 file changed, 12 insertions(+), 7 deletions(-)

```
#### [PATCH] vhost_net: fix missing descriptor recovery
##### From: huhai <huhai@kylinos.cn>

```c
When get_tx_bufs get descriptor successful, but this descriptor have
some problem, we should inform the guest to recycle this descriptor,
instead of doing nothing.

Signed-off-by: huhai <huhai@kylinos.cn>
---
 drivers/vhost/net.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v4 1/5] vsock/virtio: limit the memory used per-socket
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Since virtio-vsock was introduced, the buffers filled by the host
and pushed to the guest using the vring, are directly queued in
a per-socket list. These buffers are preallocated by the guest
with a fixed size (4 KB).

The maximum amount of memory used by each socket should be
controlled by the credit mechanism.
The default credit available per-socket is 256 KB, but if we use
only 1 byte per packet, the guest can queue up to 262144 of 4 KB
buffers, using up to 1 GB of memory per-socket. In addition, the
guest will continue to fill the vring with new 4 KB free buffers
to avoid starvation of other sockets.

This patch mitigates this issue copying the payload of small
packets (< 128 bytes) into the buffer of last packet queued, in
order to avoid wasting memory.

Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/vsock.c                   |  2 +
 include/linux/virtio_vsock.h            |  1 +
 net/vmw_vsock/virtio_transport.c        |  1 +
 net/vmw_vsock/virtio_transport_common.c | 60 +++++++++++++++++++++----
 4 files changed, 55 insertions(+), 9 deletions(-)

```
