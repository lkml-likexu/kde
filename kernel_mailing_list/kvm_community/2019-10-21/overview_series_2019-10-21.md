#### [PATCH v7 01/10] KVM: arm64: Document PV-time interface
##### From: Steven Price <steven.price@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Steven Price <Steven.Price@arm.com>
X-Patchwork-Id: 11202537
Return-Path: <SRS0=e9EM=YO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B542713B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 15:29:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 942E1214AE
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 15:29:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729559AbfJUP3B (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Oct 2019 11:29:01 -0400
Received: from [217.140.110.172] ([217.140.110.172]:55730 "EHLO foss.arm.com"
        rhost-flags-FAIL-FAIL-OK-OK) by vger.kernel.org with ESMTP
        id S1727960AbfJUP3A (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Oct 2019 11:29:00 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 915001042;
        Mon, 21 Oct 2019 08:28:35 -0700 (PDT)
Received: from e112269-lin.cambridge.arm.com (e112269-lin.cambridge.arm.com
 [10.1.194.43])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 8F77C3F71F;
        Mon, 21 Oct 2019 08:28:33 -0700 (PDT)
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
 linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v7 01/10] KVM: arm64: Document PV-time interface
Date: Mon, 21 Oct 2019 16:28:14 +0100
Message-Id: <20191021152823.14882-2-steven.price@arm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191021152823.14882-1-steven.price@arm.com>
References: <20191021152823.14882-1-steven.price@arm.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

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
 Documentation/virt/kvm/arm/pvtime.rst   | 81 +++++++++++++++++++++++++
 Documentation/virt/kvm/devices/vcpu.txt | 14 +++++
 2 files changed, 95 insertions(+)
 create mode 100644 Documentation/virt/kvm/arm/pvtime.rst

diff --git a/Documentation/virt/kvm/arm/pvtime.rst b/Documentation/virt/kvm/arm/pvtime.rst
new file mode 100644
index 000000000000..a5ded253e2d4
--- /dev/null
+++ b/Documentation/virt/kvm/arm/pvtime.rst
@@ -0,0 +1,81 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+Paravirtualized time support for arm64
+======================================
+
+Arm specification DEN0057/A defines a standard for paravirtualised time
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
+* PV_TIME_FEATURES: 0xC5000020
+* PV_TIME_ST:       0xC5000021
+
+These are only available in the SMC64/HVC64 calling convention as
+paravirtualized time is not available to 32 bit Arm guests. The existence of
+the PV_FEATURES hypercall should be probed using the SMCCC 1.1 ARCH_FEATURES
+mechanism before calling it.
+
+PV_TIME_FEATURES
+    ============= ========    ==========
+    Function ID:  (uint32)    0xC5000020
+    PV_call_id:   (uint32)    The function to query for support.
+                              Currently only PV_TIME_ST is supported.
+    Return value: (int64)     NOT_SUPPORTED (-1) or SUCCESS (0) if the relevant
+                              PV-time feature is supported by the hypervisor.
+    ============= ========    ==========
+
+PV_TIME_ST
+    ============= ========    ==========
+    Function ID:  (uint32)    0xC5000021
+    Return value: (int64)     IPA of the stolen time data structure for this
+                              VCPU. On failure:
+                              NOT_SUPPORTED (-1)
+    ============= ========    ==========
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
++-------------+-------------+-------------+----------------------------+
+| Field       | Byte Length | Byte Offset | Description                |
++=============+=============+=============+============================+
+| Revision    |      4      |      0      | Must be 0 for version 1.0  |
++-------------+-------------+-------------+----------------------------+
+| Attributes  |      4      |      4      | Must be 0                  |
++-------------+-------------+-------------+----------------------------+
+| Stolen time |      8      |      8      | Stolen time in unsigned    |
+|             |             |             | nanoseconds indicating how |
+|             |             |             | much time this VCPU thread |
+|             |             |             | was involuntarily not      |
+|             |             |             | running on a physical CPU. |
++-------------+-------------+-------------+----------------------------+
+
+All values in the structure are stored little-endian.
+
+The structure will be updated by the hypervisor prior to scheduling a VCPU. It
+will be present within a reserved region of the normal memory given to the
+guest. The guest should not attempt to write into this memory. There is a
+structure per VCPU of the guest.
+
+It is advisable that one or more 64k pages are set aside for the purpose of
+these structures and not used for other purposes, this enables the guest to map
+the region using 64k pages and avoids conflicting attributes with other memory.
+
+For the user space interface see Documentation/virt/kvm/devices/vcpu.txt
+section "3. GROUP: KVM_ARM_VCPU_PVTIME_CTRL".
+
```
#### [GIT PULL] Please pull my kvm-ppc-fixes-5.4-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paul Mackerras <paulus@ozlabs.org>
X-Patchwork-Id: 11201305
Return-Path: <SRS0=e9EM=YO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 69A8C13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 04:19:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 487C7205ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 04:19:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ozlabs.org header.i=@ozlabs.org
 header.b="tIY5F3uZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726939AbfJUETu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Oct 2019 00:19:50 -0400
Received: from ozlabs.org ([203.11.71.1]:53351 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725785AbfJUETu (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Oct 2019 00:19:50 -0400
Received: by ozlabs.org (Postfix, from userid 1003)
        id 46xNhM73BQz9sPL; Mon, 21 Oct 2019 15:19:47 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=ozlabs.org; s=201707;
        t=1571631587; bh=tFDCZHiCpDGbaT0g9jIZjA6STP+v2L5+76W/D47yv9Y=;
        h=Date:From:To:Cc:Subject:From;
        b=tIY5F3uZeIgiqDlirqZ5oQdhDWT8xCCUei8csmJxyyxai9Et8lFhPTlP3SPUXars6
         MAbJl0gE0dABKeiz3DiVEpnb3mJ+gf7Md+5TiQkgnNOen0Fhlgo12SN+Fdplu5uMHl
         DlyhsOT3LK+9Eypnp5IpsO8DAJdDo699v0vTbTW1eT0QVktaJiqHVo77sit1o9BxNq
         sYgGnpq9yA3bEOr6gp4xKoQafzbQLL69q2dxS/xkVQCPqQkD0Udfo4fEubsp7A80/2
         dm/DKWXrw3CWNwK4S2IiKR0Cq0WnBP/seSVrS7TbPIH0+sgXAYqhZs98FV4V/4JNHH
         WXvsVcSnS7ROw==
Date: Mon, 21 Oct 2019 15:19:41 +1100
From: Paul Mackerras <paulus@ozlabs.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org, David Gibson <david@gibson.dropbear.id.au>
Subject: [GIT PULL] Please pull my kvm-ppc-fixes-5.4-1 tag
Message-ID: <20191021041941.GA17498@oak.ozlabs.ibm.com>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.10.1 (2018-07-13)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Paolo or Radim,

Please do a pull from my kvm-ppc-fixes-5.4-1 tag to get a commit which
fixes a potential host crash.  I have based my tree on 5.4-rc3 because
there is another KVM fix which is included in 5.4-rc3, having gone
upstream via Michael Ellerman's tree.

Thanks,
Paul.

The following changes since commit 4f5cafb5cb8471e54afdc9054d973535614f7675:

  Linux 5.4-rc3 (2019-10-13 16:37:36 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-fixes-5.4-1

for you to fetch changes up to 12ade69c1eb9958b13374edf5ef742ea20ccffde:

  KVM: PPC: Book3S HV: XIVE: Ensure VP isn't already in use (2019-10-15 16:09:11 +1100)

----------------------------------------------------------------
PPC KVM fix for 5.4

- Fix a bug in the XIVE code which can cause a host crash.

----------------------------------------------------------------
Greg Kurz (1):
      KVM: PPC: Book3S HV: XIVE: Ensure VP isn't already in use

 arch/powerpc/kvm/book3s_xive.c        | 24 ++++++++++++++++--------
 arch/powerpc/kvm/book3s_xive.h        | 12 ++++++++++++
 arch/powerpc/kvm/book3s_xive_native.c |  6 ++++--
 3 files changed, 32 insertions(+), 10 deletions(-)
```
#### [PATCH] KVM: Add separate helper for putting borrowed reference to kvm
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11203165
Return-Path: <SRS0=e9EM=YO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B4FA0913
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 22:58:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9C4B6214B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 22:58:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730506AbfJUW6o (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Oct 2019 18:58:44 -0400
Received: from mga14.intel.com ([192.55.52.115]:50811 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730405AbfJUW6n (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Oct 2019 18:58:43 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by fmsmga103.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 21 Oct 2019 15:58:43 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,325,1566889200";
   d="scan'208";a="209539352"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by fmsmga001.fm.intel.com with ESMTP; 21 Oct 2019 15:58:43 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paul Mackerras <paulus@ozlabs.org>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: kvm-ppc@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: Add separate helper for putting borrowed reference to
 kvm
Date: Mon, 21 Oct 2019 15:58:42 -0700
Message-Id: <20191021225842.23941-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.22.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a new helper, kvm_put_kvm_no_destroy(), to handle putting a borrowed
reference[*] to the VM when installing a new file descriptor fails.  KVM
expects the refcount to remain valid in this case, as the in-progress
ioctl() has an explicit reference to the VM.  The primary motiviation
for the helper is to document that the 'kvm' pointer is still valid
after putting the borrowed reference, e.g. to document that doing
mutex(&kvm->lock) immediately after putting a ref to kvm isn't broken.

[*] When exposing a new object to userspace via a file descriptor, e.g.
    a new vcpu, KVM grabs a reference to itself (the VM) prior to making
    the object visible to userspace to avoid prematurely freeing the VM
    in the scenario where userspace immediately closes file descriptor.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/powerpc/kvm/book3s_64_mmu_hv.c |  2 +-
 arch/powerpc/kvm/book3s_64_vio.c    |  2 +-
 include/linux/kvm_host.h            |  1 +
 virt/kvm/kvm_main.c                 | 16 ++++++++++++++--
 4 files changed, 17 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: remove redundant code in kvm_arch_vm_ioctl
##### From: Miaohe Lin <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Miaohe Lin <linmiaohe@huawei.com>
X-Patchwork-Id: 11201219
Return-Path: <SRS0=e9EM=YO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E0BB139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 02:52:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E376421897
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 02:52:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726995AbfJUCwe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 20 Oct 2019 22:52:34 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:4737 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726768AbfJUCwe (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 20 Oct 2019 22:52:34 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 93BB4285F04837690E45;
        Mon, 21 Oct 2019 10:52:31 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.439.0; Mon, 21 Oct 2019
 10:52:24 +0800
From: Miaohe Lin <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <x86@kernel.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <linmiaohe@huawei.com>
Subject: [PATCH] KVM: remove redundant code in kvm_arch_vm_ioctl
Date: Mon, 21 Oct 2019 10:52:56 +0800
Message-ID: <1571626376-11357-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we reach here with r = 0, we will reassign r = 0
unnecesarry, then do the label set_irqchip_out work.
If we reach here with r != 0, then we will do the label
work directly. So this if statement and r = 0 assignment
is redundant.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/x86.c | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: realmode: use ARRAY_SIZE in test_long_jmp
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11202759
Return-Path: <SRS0=e9EM=YO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 691FF13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 17:07:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 47BF42064B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 17:07:39 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="OAFoDQlS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727805AbfJURHi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Oct 2019 13:07:38 -0400
Received: from mail-wr1-f65.google.com ([209.85.221.65]:38697 "EHLO
        mail-wr1-f65.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726847AbfJURHi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Oct 2019 13:07:38 -0400
Received: by mail-wr1-f65.google.com with SMTP id v9so3610352wrq.5
        for <kvm@vger.kernel.org>; Mon, 21 Oct 2019 10:07:36 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=oz5guTpCU+BI0skIIQHdlX4fd7KpDc/8V5k4nfR1aRA=;
        b=OAFoDQlSjTcKTNgeHLPnodG/40JaarX+hMqGz9GhIMo/JhcV4OpE/TMr8k+xK/IGUV
         azcwmCzpqUEqTAmXVi8BY+5pZ0s2Wv4zMtFwqtfr/oPB6jDzVbZ5r4P+gg03jBG//n3r
         15gG3/wAkSBRdR1Ny8eNDdSD4d4GrpR4f5i1YJ5HPiZsMAxB6xFF6mhUNILF2ZdDQZoc
         R0VUAEUq9LUeKepz5xvy4RR7JVk1FVOAg1KJblgN4ERufw1o2SYDzZBPZpB7TwElbeiW
         p8Eq54nZ1FG/nxAsZbhddyDYNP6X54qBiRUC95SsEJX7HH3Mqb54qs/0NqQKJVwPBqbR
         bDTQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :mime-version:content-transfer-encoding;
        bh=oz5guTpCU+BI0skIIQHdlX4fd7KpDc/8V5k4nfR1aRA=;
        b=iXgag/HAlE060lP8Dgz8NG1EThTbAD4h1SZfJdsGmaSwgkYOSRBEAjOggV9zrsz/6w
         TfBfLRTsEjbeFkTezUKlFKks7O6QEAwuLGOquBeJpBAvO7+OEHXLQ7f7/oYGSugEdag3
         JflJmBsL4PesNlzGlBhoaeFUpt+yvfVqnPYD3VZ+froCoWEj71ZBjtpErDmspDZYKUjd
         HHVoO3DICn4r9ARudzxIh+KmyhVVtFXuKyP5kOm5/8YoaeAQjQDvpMDnRVKyPNRYG6/E
         FHjjpFaHaK1xaoghnzrvz3R5+x7ZFANY41XocC6ZB2oJedzLRBc5Y7VfApPOn3y/1MEX
         DO2g==
X-Gm-Message-State: APjAAAUhsujfk44Z5pgzTVP2HO4KpTO15RUkIiK9mttxZhAA8RQYILV3
        ZB0X+lWkXu8s/gsUmGzp5et5PwhF
X-Google-Smtp-Source: 
 APXvYqzDGGzdYOLWNVUyofNDNjidCspPssY7nDDwQSKnzAswWIKWBr08i0pasP9aLvPbosRH9LQveA==
X-Received: by 2002:adf:ef8b:: with SMTP id d11mr5416486wro.257.1571677655710;
        Mon, 21 Oct 2019 10:07:35 -0700 (PDT)
Received: from donizetti.redhat.com ([2001:b07:6468:f312:847b:6afc:17c:89dd])
        by smtp.gmail.com with ESMTPSA id a5sm482619wrm.78.2019.10.21.10.07.34
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 21 Oct 2019 10:07:34 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: jmattson@google.com
Subject: [PATCH kvm-unit-tests] x86: realmode: use ARRAY_SIZE in test_long_jmp
Date: Mon, 21 Oct 2019 19:07:33 +0200
Message-Id: <20191021170733.16876-1-pbonzini@redhat.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Make the code a little bit more robust and self-explanatory.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 x86/realmode.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: remove redundant code in kvm_arch_vm_ioctl
##### From: Miaohe Lin <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Miaohe Lin <linmiaohe@huawei.com>
X-Patchwork-Id: 11201567
Return-Path: <SRS0=e9EM=YO=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A49C513BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 08:52:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8CCB3214D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 21 Oct 2019 08:52:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727110AbfJUIw1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 21 Oct 2019 04:52:27 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:4739 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726181AbfJUIw0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 21 Oct 2019 04:52:26 -0400
Received: from DGGEMS401-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 85CC1A26E84D34BABAC3;
        Mon, 21 Oct 2019 16:52:24 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS401-HUB.china.huawei.com
 (10.3.19.201) with Microsoft SMTP Server id 14.3.439.0; Mon, 21 Oct 2019
 16:52:14 +0800
From: Miaohe Lin <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <x86@kernel.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <linmiaohe@huawei.com>
Subject: [PATCH v2] KVM: remove redundant code in kvm_arch_vm_ioctl
Date: Mon, 21 Oct 2019 16:52:53 +0800
Message-ID: <1571647973-18657-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we reach here with r = 0, we will reassign r = 0
unnecesarry, then do the label set_irqchip_out work.
If we reach here with r != 0, then we will do the label
work directly. So this if statement and r = 0 assignment
is redundant. We remove them and therefore we can get rid
of odd set_irqchip_out lable further pointed out by tglx.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/x86.c | 9 ++-------
 1 file changed, 2 insertions(+), 7 deletions(-)

```
