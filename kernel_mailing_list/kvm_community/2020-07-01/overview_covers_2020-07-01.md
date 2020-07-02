

#### [PATCH v13 00/11] Introduce support for guest CET feature
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
From patchwork Wed Jul  1 08:04:00 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yang Weijiang <weijiang.yang@intel.com>
X-Patchwork-Id: 11635617
Return-Path: <SRS0=UYgy=AM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B0D66174A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 08:06:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A393720775
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 08:06:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728535AbgGAIEY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 04:04:24 -0400
Received: from mga14.intel.com ([192.55.52.115]:2413 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728258AbgGAIEX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jul 2020 04:04:23 -0400
IronPort-SDR: 
 we9/QNuDfPRQXKdQnFSNrqQgSPDig6i9mwfxU3slCcCs3xck6ZTjKAGb/kEnpuJTwCs6QPjAa7
 FI6rCFDnM+Zw==
X-IronPort-AV: E=McAfee;i="6000,8403,9668"; a="145581813"
X-IronPort-AV: E=Sophos;i="5.75,299,1589266800";
   d="scan'208";a="145581813"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Jul 2020 01:04:12 -0700
IronPort-SDR: 
 UhJ3wEyfUjQQla5eUs0kp6guankjI+7N2vW+qen5gPxBb9drj8GuZUuPnOgi6qinh+7WZ7jgo9
 uZX+TNLG5zag==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,299,1589266800";
   d="scan'208";a="455010208"
Received: from unknown (HELO local-michael-cet-test.sh.intel.com)
 ([10.239.159.128])
  by orsmga005.jf.intel.com with ESMTP; 01 Jul 2020 01:04:10 -0700
From: Yang Weijiang <weijiang.yang@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        pbonzini@redhat.com, sean.j.christopherson@intel.com,
        jmattson@google.com
Cc: yu.c.zhang@linux.intel.com, Yang Weijiang <weijiang.yang@intel.com>
Subject: [PATCH v13 00/11] Introduce support for guest CET feature
Date: Wed,  1 Jul 2020 16:04:00 +0800
Message-Id: <20200701080411.5802-1-weijiang.yang@intel.com>
X-Mailer: git-send-email 2.17.2
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Control-flow Enforcement Technology (CET) provides protection against
Return/Jump-Oriented Programming (ROP/JOP) attack. There're two CET
sub-features: Shadow Stack (SHSTK) and Indirect Branch Tracking (IBT).
SHSTK is to prevent ROP programming and IBT is to prevent JOP programming.

Several parts in KVM have been updated to provide VM CET support, including:
CPUID/XSAVES config, MSR pass-through, user space MSR access interface, 
vmentry/vmexit config, nested VM etc. These patches have dependency on CET
kernel patches for xsaves support and CET definitions, e.g., MSR and related
feature flags.

CET kernel patches are here:
https://lkml.kernel.org/r/20200429220732.31602-1-yu-cheng.yu@intel.com

v13:
- Added CET definitions as a separate patch to facilitate KVM test.
- Disabled CET support in KVM if unrestricted_guest is turned off since
  in this case CET related instructions/infrastructure cannot be emulated
  well.

v12:
- Fixed a few issues per Sean and Paolo's review feeback.
- Refactored patches to make them properly arranged.
- Removed unnecessary hard-coded CET states for host/guest.
- Added compile-time assertions for vmcs_field_to_offset_table to detect
  mismatch of the field type and field encoding number.
- Added a custom MSR MSR_KVM_GUEST_SSP for guest active SSP save/restore.
- Rebased patches to 5.7-rc3.

v11:
- Fixed a guest vmentry failure issue when guest reboots.
- Used vm_xxx_control_{set, clear}bit() to avoid side effect, it'll
  clear cached data instead of pure VMCS field bits.
- Added vcpu->arch.guest_supported_xss dedidated for guest runtime mask,
  this avoids supported_xss overwritten issue caused by an old qemu.
- Separated vmentry/vmexit state setting with CR0/CR4 dependency check
  to make the patch more clear.
- Added CET VMCS states in dump_vmcs() for debugging purpose.
- Other refactor based on testing.
- This patch serial is built on top of below branch and CET kernel patches
  for seeking xsaves support:
  https://git.kernel.org/pub/scm/virt/kvm/kvm.git/log/?h=cpu-caps

v10:
- Refactored code per Sean's review feedback.
- Added CET support for nested VM.
- Removed fix-patch for CPUID(0xd,N) enumeration as this part is done
  by Paolo and Sean.
- This new patchset is based on Paolo's queued cpu_caps branch.
- Modified patch per XSAVES related change.
- Consolidated KVM unit-test patch with KVM patches.

v9:
- Refactored msr-check functions per Sean's feedback.
- Fixed a few issues per Sean's suggestion.
- Rebased patch to kernel-v5.4.
- Moved CET CPUID feature bits and CR4.CET to last patch.

v8:
- Addressed Jim and Sean's feedback on: 1) CPUID(0xD,i) enumeration. 2)
  sanity check when configure guest CET. 3) function improvement.
- Added more sanity check functions.
- Set host vmexit default status so that guest won't leak CET status to
  host when vmexit.
- Added CR0.WP vs. CR4.CET mutual constrains.

v7:
- Rebased patch to kernel v5.3
- Sean suggested to change CPUID(0xd, n) enumeration code as alined with
  existing one, and I think it's better to make the fix as an independent patch 
  since XSS MSR are being used widely on X86 platforms.
- Check more host and guest status before configure guest CET
  per Sean's feedback.
- Add error-check before guest accesses CET MSRs per Sean's feedback.
- Other minor fixes suggested by Sean.

v6:
- Rebase patch to kernel v5.2.
- Move CPUID(0xD, n>=1) helper to a seperate patch.
- Merge xsave size fix with other patch.
- Other minor fixes per community feedback.

v5:
- Rebase patch to kernel v5.1.
- Wrap CPUID(0xD, n>=1) code to a helper function.
- Pass through MSR_IA32_PL1_SSP and MSR_IA32_PL2_SSP to Guest.
- Add Co-developed-by expression in patch description.
- Refine patch description.

v4:
- Add Sean's patch for loading Guest fpu state before access XSAVES
  managed CET MSRs.
- Melt down CET bits setting into CPUID configuration patch.
- Add VMX interface to query Host XSS.
- Check Host and Guest XSS support bits before set Guest XSS.
- Make Guest SHSTK and IBT feature enabling independent.
- Do not report CET support to Guest when Host CET feature is Disabled.

v3:
- Modified patches to make Guest CET independent to Host enabling.
- Added patch 8 to add user space access for Guest CET MSR access.
- Modified code comments and patch description to reflect changes.

v2:
- Re-ordered patch sequence, combined one patch.
- Added more description for CET related VMCS fields.
- Added Host CET capability check while enabling Guest CET loading bit.
- Added Host CET capability check while reporting Guest CPUID(EAX=7, EXC=0).
- Modified code in reporting Guest CPUID(EAX=D,ECX>=1), make it clearer.
- Added Host and Guest XSS mask check while setting bits for Guest XSS.

Sean Christopherson (1):
  KVM: x86: Load guest fpu state when access MSRs managed by XSAVES

Yang Weijiang (10):
  KVM: x86: Include CET definitions for KVM test purpose
  KVM: VMX: Introduce CET VMCS fields and flags
  KVM: VMX: Set guest CET MSRs per KVM and host configuration
  KVM: VMX: Configure CET settings upon guest CR0/4 changing
  KVM: x86: Refresh CPUID once guest changes XSS bits
  KVM: x86: Add userspace access interface for CET MSRs
  KVM: VMX: Enable CET support for nested VM
  KVM: VMX: Add VMCS dump and sanity check for CET states
  KVM: x86: Add #CP support in guest exception dispatch
  KVM: x86: Enable CET virtualization and advertise CET to userspace

 arch/x86/include/asm/kvm_host.h      |   4 +-
 arch/x86/include/asm/vmx.h           |   8 +
 arch/x86/include/uapi/asm/kvm.h      |   1 +
 arch/x86/include/uapi/asm/kvm_para.h |   7 +-
 arch/x86/kvm/cpuid.c                 |  28 ++-
 arch/x86/kvm/vmx/capabilities.h      |   5 +
 arch/x86/kvm/vmx/nested.c            |  34 ++++
 arch/x86/kvm/vmx/vmcs12.c            | 275 ++++++++++++++++-----------
 arch/x86/kvm/vmx/vmcs12.h            |  14 +-
 arch/x86/kvm/vmx/vmx.c               | 262 ++++++++++++++++++++++++-
 arch/x86/kvm/x86.c                   |  47 ++++-
 arch/x86/kvm/x86.h                   |   2 +-
 include/linux/kvm_host.h             |  32 ++++
 13 files changed, 588 insertions(+), 131 deletions(-)
```
#### [PATCH 0/5] vfio/pci: add blocklist and disable qat
##### From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>

```c
From patchwork Wed Jul  1 11:02:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
X-Patchwork-Id: 11636131
Return-Path: <SRS0=UYgy=AM=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7EAC4912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 11:04:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6719B20772
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  1 Jul 2020 11:04:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730169AbgGALDd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 1 Jul 2020 07:03:33 -0400
Received: from mga17.intel.com ([192.55.52.151]:29868 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729791AbgGALDd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 1 Jul 2020 07:03:33 -0400
IronPort-SDR: 
 2KqFDk3XRgZZlWr61S3xgu2aN9/+ilol8Xfm45FnCb6JU/aW/uuyq08BbmzK4dw4x987i5G6rZ
 YLTjJLPHKwCQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9668"; a="126632412"
X-IronPort-AV: E=Sophos;i="5.75,300,1589266800";
   d="scan'208";a="126632412"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 01 Jul 2020 04:03:31 -0700
IronPort-SDR: 
 2roBXaX2pEJg+CrG0EZQp8eMiOVysvZQbG2RrwkA6aPyCwIKeHyrtluTkyGoM5ZMVduqaSFC4U
 OwssjGD6tfAQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,300,1589266800";
   d="scan'208";a="425557243"
Received: from silpixa00400314.ir.intel.com (HELO
 silpixa00400314.ger.corp.intel.com) ([10.237.222.51])
  by orsmga004.jf.intel.com with ESMTP; 01 Jul 2020 04:03:27 -0700
From: Giovanni Cabiddu <giovanni.cabiddu@intel.com>
To: alex.williamson@redhat.com, herbert@gondor.apana.org.au
Cc: cohuck@redhat.com, nhorman@redhat.com, vdronov@redhat.com,
        bhelgaas@google.com, mark.a.chambers@intel.com,
        gordon.mcfadden@intel.com, ahsan.atta@intel.com,
        qat-linux@intel.com, kvm@vger.kernel.org,
        linux-crypto@vger.kernel.org, linux-pci@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Giovanni Cabiddu <giovanni.cabiddu@intel.com>
Subject: [PATCH 0/5] vfio/pci: add blocklist and disable qat
Date: Wed,  1 Jul 2020 12:02:57 +0100
Message-Id: <20200701110302.75199-1-giovanni.cabiddu@intel.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset defines a blocklist of devices in the vfio-pci module and adds
the current generation of Intel(R) QuickAssist devices to it as they are
not designed to run in an untrusted environment.

By default, if a device is in the blocklist, the probe of vfio-pci fails.
If a user wants to use a device in the blocklist, he needs to disable the
full blocklist providing the option disable_blocklist=1 at the load of
vfio-pci or specifying that parameter in a config file in /etc/modprobe.d.

This series also moves the device ids definitions present in the qat driver
to linux/pci_ids.h since they will be shared between the vfio-pci and the qat
drivers and replaces the custom ADF_SYSTEM_DEVICE macro with PCI_VDEVICE.

The series is applicable to Herbert's tree but only partially applicable to
Alex's tree due to a merge conflict.

Giovanni Cabiddu (5):
  PCI: add Intel QuickAssist device IDs
  vfio/pci: add device blocklist
  vfio/pci: add qat devices to blocklist
  crypto: qat - replace device ids defines
  crypto: qat - use PCI_VDEVICE

 drivers/crypto/qat/qat_c3xxx/adf_drv.c        | 11 ++---
 drivers/crypto/qat/qat_c3xxxvf/adf_drv.c      | 11 ++---
 drivers/crypto/qat/qat_c62x/adf_drv.c         | 11 ++---
 drivers/crypto/qat/qat_c62xvf/adf_drv.c       | 11 ++---
 .../crypto/qat/qat_common/adf_accel_devices.h |  6 ---
 drivers/crypto/qat/qat_common/qat_hal.c       |  7 +--
 drivers/crypto/qat/qat_common/qat_uclo.c      |  9 ++--
 drivers/crypto/qat/qat_dh895xcc/adf_drv.c     | 11 ++---
 drivers/crypto/qat/qat_dh895xccvf/adf_drv.c   | 11 ++---
 drivers/vfio/pci/vfio_pci.c                   | 48 +++++++++++++++++++
 include/linux/pci_ids.h                       |  6 +++
 11 files changed, 87 insertions(+), 55 deletions(-)
```
