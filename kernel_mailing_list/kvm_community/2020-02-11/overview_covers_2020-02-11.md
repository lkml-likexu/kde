

#### [kvm-unit-tests PATCH 0/3] arm64: minor cleanups for timer test
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
From patchwork Tue Feb 11 08:38:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11375075
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EEBA417F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 08:40:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CBC66206CC
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 08:40:44 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727685AbgBKIkm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 03:40:42 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:52184 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727669AbgBKIkm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 03:40:42 -0500
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 797FE2C7D398984F714B;
        Tue, 11 Feb 2020 16:40:40 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.173.222.27) by
 DGGEMS407-HUB.china.huawei.com (10.3.19.207) with Microsoft SMTP Server id
 14.3.439.0; Tue, 11 Feb 2020 16:40:33 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <drjones@redhat.com>, <kvm@vger.kernel.org>,
        <kvmarm@lists.cs.columbia.edu>
CC: <alexandru.elisei@arm.com>, <wanghaibin.wang@huawei.com>,
        Zenghui Yu <yuzenghui@huawei.com>
Subject: [kvm-unit-tests PATCH 0/3] arm64: minor cleanups for timer test
Date: Tue, 11 Feb 2020 16:38:58 +0800
Message-ID: <20200211083901.1478-1-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.173.222.27]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Drew,

There's some minor cleanups which based on your arm/queue branch for
the timer test.  Please consider taking them if they make the code
a bit better :)

Thanks

Zenghui Yu (3):
  arm/arm64: gic: Move gic_state enumeration to asm/gic.h
  arm64: timer: Use the proper RDist register name in GICv3
  arm64: timer: Use existing helpers to access counter/timers

 arm/timer.c          | 27 ++++++++++-----------------
 lib/arm/asm/gic-v3.h |  4 ++++
 lib/arm/asm/gic.h    |  7 +++++++
 3 files changed, 21 insertions(+), 17 deletions(-)
```
#### [RFC PATCH v3 0/9] Introduce vendor ops in vfio-pci
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
From patchwork Tue Feb 11 09:57:27 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yan Zhao <yan.y.zhao@intel.com>
X-Patchwork-Id: 11375157
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4E287921
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 10:19:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2DE2E20870
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 10:19:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728272AbgBKKTH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 05:19:07 -0500
Received: from mga17.intel.com ([192.55.52.151]:61104 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728257AbgBKKTG (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 05:19:06 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga107.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 11 Feb 2020 02:19:06 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,428,1574150400";
   d="scan'208";a="405896777"
Received: from joy-optiplex-7040.sh.intel.com ([10.239.13.16])
  by orsmga005.jf.intel.com with ESMTP; 11 Feb 2020 02:19:03 -0800
From: Yan Zhao <yan.y.zhao@intel.com>
To: alex.williamson@redhat.com
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        cohuck@redhat.com, zhenyuw@linux.intel.com, zhi.a.wang@intel.com,
        kevin.tian@intel.com, shaopeng.he@intel.com, yi.l.liu@intel.com,
        Yan Zhao <yan.y.zhao@intel.com>
Subject: [RFC PATCH v3 0/9] Introduce vendor ops in vfio-pci
Date: Tue, 11 Feb 2020 04:57:27 -0500
Message-Id: <20200211095727.20426-1-yan.y.zhao@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When using module vfio-pci to pass through devices, though for the most
of time, it is desired to use default implementations in vfio-pci, vendors
sometimes may want to do certain kind of customization.
For example, vendors may want to add a vendor device region or may want to
intercept writes to a BAR region.
So, in this patch set, we introduce a way to allow vendors to focus on
handling of regions of their interest and call default vfio-pci ops to
handle the reset ones.

It goes like this:
(1) macros are provided to let vendor drivers register/unregister
vfio_pci_vendor_driver_ops to vfio_pci in their module_init() and
module_exit().
vfio_pci_vendor_driver_ops contains callbacks probe() and remove() and a
pointer to vfio_device_ops.

(2) vendor drivers define their module aliases as
"vfio-pci:$vendor_id-$device_id".
E.g. A vendor module for VF devices of Intel(R) Ethernet Controller XL710
family can define its module alias as MODULE_ALIAS("vfio-pci:8086-154c").

(3) when module vfio_pci is bound to a device, it would call modprobe in
user space for modules of alias "vfio-pci:$vendor_id-$device_id", which
would trigger unloaded vendor drivers to register their
vfio_pci_vendor_driver_ops to vfio_pci.
Then it searches registered ops list and calls probe() to test whether this
vendor driver supports this physical device.
A success probe() would make vfio_pci to use vfio_device_ops provided
vendor driver as the ops of the vfio device. So vfio_pci_ops are not to be
called for this device any more. Instead, they are exported to be called
from vendor drivers as a default implementation.


                                        _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ 
                                  
 __________   (un)register vendor ops  |  ___________    ___________   |
|          |<----------------------------|    VF    |   |           |   
| vfio-pci |                           | |  vendor  |   | PF driver |  |
|__________|---------------------------->|  driver  |   |___________|   
     |           probe/remove()        |  -----------          |       |
     |                                                         |         
     |                                 |_ _ _ _ _ _ _ _ _ _ _ _|_ _ _ _|
    \|/                                                       \|/
-----------                                              ------------
|    VF   |                                              |    PF    |
-----------                                              ------------
                   a typical usage in SRIOV



Ref counts:
(1) vendor drivers must be a module and compiled to depend on module
vfio_pci.
(2) In vfio_pci, a successful register would add refs of itself, and a
successful unregister would derefs of itself.
(3) In vfio_pci, a successful probe() of a vendor driver would add ref of
the vendor module. It derefs of the vendor module after calling remove().
(4) macro provided to make sure vendor module always unregister itself in
its module_exit

Those are to prevent below conditions:
a. vfio_pci is unloaded after a successful register from vendor driver.
   Though vfio_pci would later call modprobe to ask the vendor module to
   register again, it cannot help if vendor driver remain as loaded
   across unloading-loading of vfio_pci.
b. vendor driver unregisters itself after successfully probed by vfio_pci.
c. circular dependency between vfio_pci and the vendor driver.
   if vfio_pci adds refs to both vfio_pci and vendor driver on a successful
   register and if vendor driver only do the unregister in its module_exit,
   then it would have no chance to do the unregister.


Patch Overview
patches 1-2 making struct vfio_pci_device public and functions
            in struct vfio_pci_ops exported
patches 3-4 provide register/unregister interfaces for vendor drivers
patches 5-6 some more enhancements
patch 7 provides an sample to pass through IGD devices
patches 8-9 implement VF live migration on Intel's 710 SRIOV devices.
            Some dirty page tracking functions are intentionally
            commented out and would send out later in future.

Changelog:
RFC v2- RFC v3:
- embedding struct vfio_pci_device into struct vfio_pci_device_private.
(Alex)

RFC v1- RFC v2:
- renamed mediate ops to vendor ops
- use of request_module and module alias to manage vendor driver load
  (Alex)
- changed from vfio_pci_ops calling vendor ops
  to vendor ops calling default vfio_pci_ops  (Alex)
- dropped patches for dynamic traps of BARs. will submit them later.

Links:
Previous versions:
RFC v2:
https://lkml.org/lkml/2020/1/30/956

RFC v1:
kernel part: https://www.spinics.net/lists/kernel/msg3337337.html.
qemu part: https://www.spinics.net/lists/kernel/msg3337337.html.

VFIO live migration v8:
https://lists.gnu.org/archive/html/qemu-devel/2019-08/msg05542.html.


Yan Zhao (9):
  vfio/pci: export vfio_pci_device public and add
    vfio_pci_device_private
  vfio/pci: export functions in vfio_pci_ops
  vfio/pci: register/unregister vfio_pci_vendor_driver_ops
  vfio/pci: macros to generate module_init and module_exit for vendor
    modules
  vfio/pci: let vfio_pci know how many vendor regions are registered
  vfio/pci: export vfio_pci_setup_barmap
  samples/vfio-pci: add a sample vendor module of vfio-pci for IGD
    devices
  vfio: header for vfio live migration region.
  i40e/vf_migration: vfio-pci vendor driver for VF live migration

 drivers/net/ethernet/intel/Kconfig            |  10 +
 drivers/net/ethernet/intel/i40e/Makefile      |   2 +
 drivers/net/ethernet/intel/i40e/i40e.h        |   2 +
 .../ethernet/intel/i40e/i40e_vf_migration.c   | 635 ++++++++++++++++++
 .../ethernet/intel/i40e/i40e_vf_migration.h   |  92 +++
 drivers/vfio/pci/vfio_pci.c                   | 385 +++++++----
 drivers/vfio/pci/vfio_pci_config.c            | 186 ++---
 drivers/vfio/pci/vfio_pci_igd.c               |  19 +-
 drivers/vfio/pci/vfio_pci_intrs.c             | 186 ++---
 drivers/vfio/pci/vfio_pci_nvlink2.c           |  22 +-
 drivers/vfio/pci/vfio_pci_private.h           |  13 +-
 drivers/vfio/pci/vfio_pci_rdwr.c              |  64 +-
 include/linux/vfio.h                          |  57 ++
 include/uapi/linux/vfio.h                     | 149 ++++
 samples/Kconfig                               |   6 +
 samples/Makefile                              |   1 +
 samples/vfio-pci/Makefile                     |   2 +
 samples/vfio-pci/igd_pt.c                     | 148 ++++
 18 files changed, 1645 insertions(+), 334 deletions(-)
 create mode 100644 drivers/net/ethernet/intel/i40e/i40e_vf_migration.c
 create mode 100644 drivers/net/ethernet/intel/i40e/i40e_vf_migration.h
 create mode 100644 samples/vfio-pci/Makefile
 create mode 100644 samples/vfio-pci/igd_pt.c
```
#### [RFC PATCH 00/62] Linux as SEV-ES Guest Support
##### From: Joerg Roedel <joro@8bytes.org>

```c
From patchwork Tue Feb 11 13:51:54 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11375669
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B283717F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 13:59:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8AB3A24672
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 13:59:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729397AbgBKNxK (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 08:53:10 -0500
Received: from 8bytes.org ([81.169.241.247]:51752 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729383AbgBKNxJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 08:53:09 -0500
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 4F93F303; Tue, 11 Feb 2020 14:53:07 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Thomas Hellstrom <thellstrom@vmware.com>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>
Subject: [RFC PATCH 00/62] Linux as SEV-ES Guest Support
Date: Tue, 11 Feb 2020 14:51:54 +0100
Message-Id: <20200211135256.24617-1-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

here is the first public post of the patch-set to enable Linux to run
under SEV-ES enabled hypervisors. The code is mostly feature-complete,
but there are still a couple of bugs to fix. Nevertheless, given the
size of the patch-set, I think it is about time to ask for initial
feedback of the changes that come with it. To better understand the code
here is a quick explanation of SEV-ES first.

This patch-set does not contain the hypervisor changes necessary to run
SEV-ES enabled KVM guests. These patches will be sent separatly when
they are ready to be sent out.

What is SEV-ES
==============

SEV-ES is an acronym for 'Secure Encrypted Virtualization - Encrypted
State' and means a hardware feature of AMD processors which hides the
register state of VCPUs to the hypervisor by encrypting it. The
hypervisor can't read or make changes to the guests register state.

Most intercepts set by the hypervisor do not cause a #VMEXIT of the
guest anymore, but turn into a VMM Communication Exception (#VC
exception, vector 29) inside the guest. The error-code of this exception
is the intercept exit-code that caused the exception. The guest handles
the #VC exception by communicating with the hypervisor through a shared
data structure, the 'Guest-Hypervisor-Communication-Block' (GHCB). The
layout of that data-structure and the protocol is specified in [1].

A description of the SEV-ES hardware interface can be found in the AMD64
Architecture Programmer's Manual Volume 2, Section 15.35 [2].

Implementation Details
======================

SEV-ES guests will always boot via UEFI firmware and use the 64-bit EFI
entry point into the kernel. This implies that only 64-bit Linux x86
guests are supported.

Pre-Decompression Boot Code and Early Exception Support
-------------------------------------------------------

Intercepts that cause exceptions in the guest include instructions like
CPUID, RDMSR/WRMSR, IOIO instructions and a couple more. Some of them
are executed very early during boot, which means that exceptions need to
work that early. That is the reason big parts of this patch-set enable
support for early exceptions, first in the pre-decompression boot-code
and later also in the early boot-code of the kernel image.

As these patches add exception support to the pre-decompression boot
code, it also implements a page-fault handler to create the
identity-mapped page-table on-demand. One reason for this change is to
make use of the exception handling code in non SEV-ES guests too, so
that it is less likely to break in the future. The other reason is that
for SEV-ES guests the code needs to setup its own page-table to map the
GHCB unencrypted. Without these patches the pre-decompression code only
uses its own page-table when KASLR is enabled and used.

SIPI and INIT Handling
----------------------

The hypervisor also can't make changes to the guest register state,
which implies that it can't emulate SIPI and INIT messages. This means
that any CPU register state reset needs to be done inside the guest.
Most of this is handled in the firmware, but the Linux kernel has to
setup an AP Jump Table to boot secondary processors. CPU online/offline
handling also needs special handling, where this patch-set implements a
shortcut. An offlined CPU will not go back to real-mode when it is woken
up again, but stays in long-mode an just jumps back to the trampoline
code.

NMI Special Handling
--------------------

The last thing that needs special handling with SEV-ES are NMIs.
Hypervisors usually start to intercept IRET instructions when an NMI got
injected to find out when the NMI window is re-opened. But handling IRET
intercepts requires the hypervisor to access guest register state and is
not possible with SEV-ES. The specification under [1] solves this
problem with an NMI_COMPLETE message sent my the guest to the
hypervisor, upon which the hypervisor re-opens the NMI window for the
guest.

This patch-set sends the NMI_COMPLETE message before the actual IRET,
while the kernel is still on a valid stack and kernel cr3. This opens
the NMI-window a few instructions early, but this is fine as under
x86-64 Linux NMI-nesting is safe. The alternative would be to
single-step over the IRET, but that requires more intrusive changes to
the entry code because it does not handle entries from kernel-mode while
on the entry stack.

Besides the special handling above the patch-set contains the handlers
for the #VC exception and all the exit-codes specified in [1].

Current State of the Patches
============================

The patch-set posted here can boot an SMP Linux guest under
SEV-ES-enabled KVM and the guest survives some load-testing
(kernel-compiles).  The guest boots to the graphical desktop and is
usable. But there are still know bugs and issues:

	* Putting some NMI-load on the guest will make it crash usually
	  within a minute
	* The handler for MMIO events needs more security checks when
	  walking the page-table
	* The MMIO handler also lacks emulation for MOVS and REP MOVS
	  instructions like used by memcpy_toio() and memcpy_fromio().

More testing will likely uncover more bugs, but I think the patch-set is
ready for initial feedback. It grew pretty big already and handling it
becomes more and more painful.

So please review the parts of the patch-set that you find interesting
and let me know your feedback.

Thanks a lot,

       Joerg

[1] https://developer.amd.com/wp-content/resources/56421.pdf
[2] https://www.amd.com/system/files/TechDocs/24593.pdf

Doug Covelli (1):
  x86/vmware: Add VMware specific handling for VMMCALL under SEV-ES

Joerg Roedel (43):
  KVM: SVM: Add GHCB Accessor functions
  x86/traps: Move some definitions to <asm/trap_defs.h>
  x86/insn-decoder: Make inat-tables.c suitable for pre-decompression
    code
  x86/boot/compressed: Fix debug_puthex() parameter type
  x86/boot/compressed/64: Disable red-zone usage
  x86/boot/compressed/64: Add IDT Infrastructure
  x86/boot/compressed/64: Rename kaslr_64.c to ident_map_64.c
  x86/boot/compressed/64: Add page-fault handler
  x86/boot/compressed/64: Always switch to own page-table
  x86/boot/compressed/64: Don't pre-map memory in KASLR code
  x86/boot/compressed/64: Change add_identity_map() to take start and
    end
  x86/boot/compressed/64: Add stage1 #VC handler
  x86/boot/compressed/64: Call set_sev_encryption_mask earlier
  x86/boot/compressed/64: Check return value of
    kernel_ident_mapping_init()
  x86/boot/compressed/64: Add function to map a page unencrypted
  x86/boot/compressed/64: Setup GHCB Based VC Exception handler
  x86/fpu: Move xgetbv()/xsetbv() into separate header
  x86/idt: Move IDT to data segment
  x86/idt: Split idt_data setup out of set_intr_gate()
  x86/head/64: Install boot GDT
  x86/head/64: Reload GDT after switch to virtual addresses
  x86/head/64: Load segment registers earlier
  x86/head/64: Switch to initial stack earlier
  x86/head/64: Load IDT earlier
  x86/head/64: Move early exception dispatch to C code
  x86/sev-es: Add SEV-ES Feature Detection
  x86/sev-es: Compile early handler code into kernel image
  x86/sev-es: Setup early #VC handler
  x86/sev-es: Setup GHCB based boot #VC handler
  x86/sev-es: Wire up existing #VC exit-code handlers
  x86/sev-es: Handle instruction fetches from user-space
  x86/sev-es: Harden runtime #VC handler for exceptions from user-space
  x86/sev-es: Filter exceptions not supported from user-space
  x86/sev-es: Handle RDTSCP Events
  x86/sev-es: Handle #AC Events
  x86/sev-es: Handle #DB Events
  x86/paravirt: Allow hypervisor specific VMMCALL handling under SEV-ES
  x86/realmode: Add SEV-ES specific trampoline entry point
  x86/head/64: Don't call verify_cpu() on starting APs
  x86/head/64: Rename start_cpu0
  x86/sev-es: Support CPU offline/online
  x86/cpufeature: Add SEV_ES_GUEST CPU Feature
  x86/sev-es: Add NMI state tracking

Tom Lendacky (18):
  KVM: SVM: Add GHCB definitions
  x86/cpufeatures: Add SEV-ES CPU feature
  x86/sev-es: Add support for handling IOIO exceptions
  x86/sev-es: Add CPUID handling to #VC handler
  x86/sev-es: Add handler for MMIO events
  x86/sev-es: Setup per-cpu GHCBs for the runtime handler
  x86/sev-es: Add Runtime #VC Exception Handler
  x86/sev-es: Handle MSR events
  x86/sev-es: Handle DR7 read/write events
  x86/sev-es: Handle WBINVD Events
  x86/sev-es: Handle RDTSC Events
  x86/sev-es: Handle RDPMC Events
  x86/sev-es: Handle INVD Events
  x86/sev-es: Handle MONITOR/MONITORX Events
  x86/sev-es: Handle MWAIT/MWAITX Events
  x86/sev-es: Handle VMMCALL Events
  x86/kvm: Add KVM specific VMMCALL handling under SEV-ES
  x86/realmode: Setup AP jump table

 arch/x86/Kconfig                           |   1 +
 arch/x86/boot/Makefile                     |   2 +-
 arch/x86/boot/compressed/Makefile          |   8 +-
 arch/x86/boot/compressed/head_64.S         |  41 ++
 arch/x86/boot/compressed/ident_map_64.c    | 320 +++++++++
 arch/x86/boot/compressed/idt_64.c          |  53 ++
 arch/x86/boot/compressed/idt_handlers_64.S |  78 +++
 arch/x86/boot/compressed/kaslr.c           |  36 +-
 arch/x86/boot/compressed/kaslr_64.c        | 156 -----
 arch/x86/boot/compressed/misc.h            |  34 +-
 arch/x86/boot/compressed/sev-es.c          | 148 ++++
 arch/x86/entry/entry_64.S                  |  52 ++
 arch/x86/include/asm/cpu.h                 |   2 +-
 arch/x86/include/asm/cpufeatures.h         |   2 +
 arch/x86/include/asm/desc.h                |   2 +
 arch/x86/include/asm/desc_defs.h           |   3 +
 arch/x86/include/asm/fpu/internal.h        |  29 +-
 arch/x86/include/asm/fpu/xcr.h             |  32 +
 arch/x86/include/asm/mem_encrypt.h         |   5 +
 arch/x86/include/asm/msr-index.h           |   3 +
 arch/x86/include/asm/processor.h           |   1 +
 arch/x86/include/asm/realmode.h            |   4 +
 arch/x86/include/asm/segment.h             |   2 +-
 arch/x86/include/asm/sev-es.h              | 119 ++++
 arch/x86/include/asm/svm.h                 | 103 +++
 arch/x86/include/asm/trap_defs.h           |  50 ++
 arch/x86/include/asm/traps.h               |  51 +-
 arch/x86/include/asm/x86_init.h            |  16 +-
 arch/x86/include/uapi/asm/svm.h            |  11 +
 arch/x86/kernel/Makefile                   |   1 +
 arch/x86/kernel/cpu/amd.c                  |  10 +-
 arch/x86/kernel/cpu/scattered.c            |   1 +
 arch/x86/kernel/cpu/vmware.c               |  48 +-
 arch/x86/kernel/head64.c                   |  49 ++
 arch/x86/kernel/head_32.S                  |   4 +-
 arch/x86/kernel/head_64.S                  | 162 +++--
 arch/x86/kernel/idt.c                      |  60 +-
 arch/x86/kernel/kvm.c                      |  35 +-
 arch/x86/kernel/nmi.c                      |   8 +
 arch/x86/kernel/sev-es-shared.c            | 721 ++++++++++++++++++++
 arch/x86/kernel/sev-es.c                   | 748 +++++++++++++++++++++
 arch/x86/kernel/smpboot.c                  |   4 +-
 arch/x86/kernel/traps.c                    |   3 +
 arch/x86/mm/extable.c                      |   1 +
 arch/x86/mm/mem_encrypt.c                  |  11 +-
 arch/x86/mm/mem_encrypt_identity.c         |   3 +
 arch/x86/realmode/init.c                   |  12 +
 arch/x86/realmode/rm/header.S              |   3 +
 arch/x86/realmode/rm/trampoline_64.S       |  20 +
 arch/x86/tools/gen-insn-attr-x86.awk       |  50 +-
 tools/arch/x86/tools/gen-insn-attr-x86.awk |  50 +-
 51 files changed, 3016 insertions(+), 352 deletions(-)
 create mode 100644 arch/x86/boot/compressed/ident_map_64.c
 create mode 100644 arch/x86/boot/compressed/idt_64.c
 create mode 100644 arch/x86/boot/compressed/idt_handlers_64.S
 delete mode 100644 arch/x86/boot/compressed/kaslr_64.c
 create mode 100644 arch/x86/boot/compressed/sev-es.c
 create mode 100644 arch/x86/include/asm/fpu/xcr.h
 create mode 100644 arch/x86/include/asm/sev-es.h
 create mode 100644 arch/x86/include/asm/trap_defs.h
 create mode 100644 arch/x86/kernel/sev-es-shared.c
 create mode 100644 arch/x86/kernel/sev-es.c
```
#### [PATCH v2 00/94] KVM: arm64: ARMv8.3/8.4 Nested Virtualization
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Tue Feb 11 17:48:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11376113
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BAE9714E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 17:49:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8DB2A208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 17:49:58 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581443398;
	bh=9vwiKEQFnDa6LliQSaOHC4Wfh37cKJtZ5767GPU5BgU=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=z6G1ntI6828kL8U6c1KMUrCox+uv7KSSSgcSWd7yL/fJea82CpROB2s8gHCY5tZ4C
	 zhG6HUQEa+MG4QvnUsPWUIEpEP/lpp8PvriPgadTw0loeoR2JHG7Yg5ATPewLzd4Zh
	 D9zzLZl/5RVuj1kQK3wwChotAHewuZXSNr6EqRhg=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729750AbgBKRt5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 12:49:57 -0500
Received: from mail.kernel.org ([198.145.29.99]:52216 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728575AbgBKRt5 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 12:49:57 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 9809820661;
        Tue, 11 Feb 2020 17:49:55 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1581443395;
        bh=9vwiKEQFnDa6LliQSaOHC4Wfh37cKJtZ5767GPU5BgU=;
        h=From:To:Cc:Subject:Date:From;
        b=aPf2mlbZgwWNSlMbAEHC7MaB+7fC8wf7Ih96SAL3nPzhlcz9Hs8JAVX4QKsjImm73
         GZNBwG359SqoBWNrv4yhWPgruH5wws7kPBW+g5lqewHLj6gshQOg/Nl91fqsNtF52x
         hU6rHp6rgkeSnAvxZjkDLz3f0+rN45jk4GYNh7kU=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1j1ZfV-004O7k-Pq; Tue, 11 Feb 2020 17:49:53 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Andre Przywara <andre.przywara@arm.com>,
        Christoffer Dall <christoffer.dall@arm.com>,
        Dave Martin <Dave.Martin@arm.com>,
        Jintack Lim <jintack@cs.columbia.edu>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>
Subject: [PATCH v2 00/94] KVM: arm64: ARMv8.3/8.4 Nested Virtualization
 support
Date: Tue, 11 Feb 2020 17:48:04 +0000
Message-Id: <20200211174938.27809-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, andre.przywara@arm.com,
 christoffer.dall@arm.com, Dave.Martin@arm.com, jintack@cs.columbia.edu,
 alexandru.elisei@arm.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a major rework of the NV series that I posted over 6 months
ago[1], and a lot has changed since then:

- Early ARMv8.4-NV support
- ARMv8.4-TTL support in host and guest
- ARMv8.5-GTG support in host and guest
- Lots of comments addressed after the review
- Rebased on v5.6-rc1
- Way too many patches

In my defence, the whole of the NV code is still smaller that the
32bit KVM/arm code I'm about to remove, so I feel less bad inflicting
this on everyone! ;-)

From a functionality perspective, you can expect a L2 guest to work,
but don't even think of L3, as we only partially emulate the
ARMv8.{3,4}-NV extensions themselves. Same thing for vgic, debug, PMU,
as well as anything that would require a Stage-1 PTW. What we want to
achieve is that with NV disabled, there is no performance overhead and
no regression.

The series is roughly divided in 5 parts: exception handling, memory
virtualization, interrupts and timers for ARMv8.3, followed by the
ARMv8.4 support. There are of course some dependencies, but you'll
hopefully get the gist of it.

For the most courageous of you, I've put out a branch[2]. Of course,
you'll need some userspace. Andre maintains a hacked version of
kvmtool[3] that takes a --nested option, allowing the guest to be
started at EL2. You can run the whole stack in the Foundation
model. Don't be in a hurry ;-).

[1] https://lore.kernel.org/r/20190621093843.220980-1-marc.zyngier@arm.com
[2] git://git.kernel.org/pub/scm/linux/kernel/git/maz/arm-platforms.git kvm-arm64/nv-5.6-rc1
[3] git://linux-arm.org/kvmtool.git nv/nv-wip-5.2-rc5

Andre Przywara (3):
  KVM: arm64: nv: Save/Restore vEL2 sysregs
  KVM: arm64: nv: Handle traps for timer _EL02 and _EL2 sysregs
    accessors
  KVM: arm64: nv: vgic: Allow userland to set VGIC maintenance IRQ

Christoffer Dall (17):
  KVM: arm64: nv: Introduce nested virtualization VCPU feature
  KVM: arm64: nv: Reset VCPU to EL2 registers if VCPU nested virt is set
  KVM: arm64: nv: Allow userspace to set PSR_MODE_EL2x
  KVM: arm64: nv: Add nested virt VCPU primitives for vEL2 VCPU state
  KVM: arm64: nv: Handle trapped ERET from virtual EL2
  KVM: arm64: nv: Emulate PSTATE.M for a guest hypervisor
  KVM: arm64: nv: Trap EL1 VM register accesses in virtual EL2
  KVM: arm64: nv: Only toggle cache for virtual EL2 when SCTLR_EL2
    changes
  KVM: arm/arm64: nv: Factor out stage 2 page table data from struct kvm
  KVM: arm64: nv: Implement nested Stage-2 page table walk logic
  KVM: arm64: nv: Handle shadow stage 2 page faults
  KVM: arm64: nv: Unmap/flush shadow stage 2 page tables
  KVM: arm64: nv: arch_timer: Support hyp timer emulation
  KVM: arm64: nv: vgic-v3: Take cpu_if pointer directly instead of vcpu
  KVM: arm64: nv: vgic: Emulate the HW bit in software
  KVM: arm64: nv: Add nested GICv3 tracepoints
  KVM: arm64: nv: Sync nested timer state with ARMv8.4

Jintack Lim (19):
  arm64: Add ARM64_HAS_NESTED_VIRT cpufeature
  KVM: arm64: nv: Add EL2 system registers to vcpu context
  KVM: arm64: nv: Support virtual EL2 exceptions
  KVM: arm64: nv: Inject HVC exceptions to the virtual EL2
  KVM: arm64: nv: Trap SPSR_EL1, ELR_EL1 and VBAR_EL1 from virtual EL2
  KVM: arm64: nv: Trap CPACR_EL1 access in virtual EL2
  KVM: arm64: nv: Handle PSCI call via smc from the guest
  KVM: arm64: nv: Respect virtual HCR_EL2.TWX setting
  KVM: arm64: nv: Respect virtual CPTR_EL2.{TFP,FPEN} settings
  KVM: arm64: nv: Respect the virtual HCR_EL2.NV bit setting
  KVM: arm64: nv: Respect virtual HCR_EL2.TVM and TRVM settings
  KVM: arm64: nv: Respect the virtual HCR_EL2.NV1 bit setting
  KVM: arm64: nv: Emulate EL12 register accesses from the virtual EL2
  KVM: arm64: nv: Configure HCR_EL2 for nested virtualization
  KVM: arm64: nv: Introduce sys_reg_desc.forward_trap
  KVM: arm64: nv: Set a handler for the system instruction traps
  KVM: arm64: nv: Trap and emulate AT instructions from virtual EL2
  KVM: arm64: nv: Trap and emulate TLBI instructions from virtual EL2
  KVM: arm64: nv: Nested GICv3 Support

Marc Zyngier (55):
  KVM: arm64: Move __load_guest_stage2 to kvm_mmu.h
  KVM: arm64: nv: Reset VMPIDR_EL2 and VPIDR_EL2 to sane values
  KVM: arm64: nv: Add EL2->EL1 translation helpers
  KVM: arm64: nv: Refactor vcpu_{read,write}_sys_reg
  KVM: arm64: nv: Handle virtual EL2 registers in
    vcpu_read/write_sys_reg()
  KVM: arm64: nv: Handle SPSR_EL2 specially
  KVM: arm64: nv: Handle HCR_EL2.E2H specially
  KVM: arm64: nv: Forward debug traps to the nested guest
  KVM: arm64: nv: Filter out unsupported features from ID regs
  KVM: arm64: nv: Hide RAS from nested guests
  KVM: arm64: nv: Use ARMv8.5-GTG to advertise supported Stage-2 page
    sizes
  KVM: arm64: Check advertised Stage-2 page size capability
  KVM: arm64: nv: Support multiple nested Stage-2 mmu structures
  KVM: arm64: nv: Move last_vcpu_ran to be per s2 mmu
  KVM: arm64: nv: Fold guest's HCR_EL2 configuration into the host's
  KVM: arm64: nv: Propagate CNTVOFF_EL2 to the virtual EL1 timer
  KVM: arm64: nv: Load timer before the GIC
  KVM: arm64: nv: Implement maintenance interrupt forwarding
  arm64: KVM: nv: Add handling of EL2-specific timer registers
  arm64: KVM: nv: Honor SCTLR_EL2.SPAN on entering vEL2
  arm64: KVM: nv: Handle SCTLR_EL2 RES0/RES1 bits
  arm64: KVM: nv: Restrict S2 RD/WR permissions to match the guest's
  arm64: KVM: nv: Allow userspace to request KVM_ARM_VCPU_NESTED_VIRT
  arm64: Detect the ARMv8.4 TTL feature
  arm64: KVM: nv: Add handling of ARMv8.4-TTL TLB invalidation
  arm64: KVM: nv: Invalidate TLBs based on shadow S2 TTL-like
    information
  arm64: KVM: nv: Tag shadow S2 entries with nested level
  arm64: Add SW reserved PTE/PMD bits
  arm64: Add level-hinted TLB invalidation helper
  arm64: KVM: Add a level hint to __kvm_tlb_flush_vmid_ipa
  arm64: KVM: Use TTL hint in when invalidating stage-2 translations
  arm64: KVM: nv: Add include containing the VNCR_EL2 offsets
  KVM: arm64: Introduce accessor for ctxt->sys_reg
  KVM: arm64: sysreg: Use ctxt_sys_reg() instead of raw sys_regs access
  KVM: arm64: sve: Use __vcpu_sys_reg() instead of raw sys_regs access
  KVM: arm64: pauth: Use ctxt_sys_reg() instead of raw sys_regs access
  KVM: arm64: debug: Use ctxt_sys_reg() instead of raw sys_regs access
  KVM: arm64: Add missing reset handlers for PMU emulation
  KVM: arm64: nv: Move sysreg reset check to boot time
  KVM: arm64: Map VNCR-capable registers to a separate page
  KVM: arm64: nv: Move nested vgic state into the sysreg file
  KVM: arm64: Use accessors for timer ctl/cval/offset
  KVM: arm64: Add VNCR-capable timer accessors for arm64
  KVM: arm64: Make struct kvm_regs userspace-only
  KVM: arm64: VNCR-ize ELR_EL1
  KVM: arm64: VNCR-ize SP_EL1
  KVM: arm64: Disintegrate SPSR array
  KVM: arm64: aarch32: Use __vcpu_sys_reg() instead of raw sys_regs
    access
  KVM: arm64: VNCR-ize SPSR_EL1
  KVM: arm64: Add ARMv8.4 Enhanced Nested Virt cpufeature
  KVM: arm64: nv: Synchronize PSTATE early on exit
  KVM: arm64: nv: Allocate VNCR page when required
  KVM: arm64: nv: Enable ARMv8.4-NV support
  KVM: arm64: nv: Fast-track 'InHost' exception returns
  KVM: arm64: nv: Fast-track EL1 TLBIs for VHE guests

 .../admin-guide/kernel-parameters.txt         |    4 +
 .../virt/kvm/devices/arm-vgic-v3.txt          |    8 +
 arch/arm/include/asm/kvm_asm.h                |    6 +-
 arch/arm/include/asm/kvm_emulate.h            |    3 +
 arch/arm/include/asm/kvm_host.h               |   32 +-
 arch/arm/include/asm/kvm_hyp.h                |   12 +-
 arch/arm/include/asm/kvm_mmu.h                |   90 +-
 arch/arm/include/asm/kvm_nested.h             |   11 +
 arch/arm/include/asm/stage2_pgtable.h         |    9 +
 arch/arm/include/uapi/asm/kvm.h               |    1 +
 arch/arm/kvm/hyp/switch.c                     |   11 +-
 arch/arm/kvm/hyp/tlb.c                        |   18 +-
 arch/arm64/include/asm/cpucaps.h              |    5 +-
 arch/arm64/include/asm/esr.h                  |    6 +
 arch/arm64/include/asm/kvm_arm.h              |   28 +-
 arch/arm64/include/asm/kvm_asm.h              |   10 +-
 arch/arm64/include/asm/kvm_coproc.h           |    2 +-
 arch/arm64/include/asm/kvm_emulate.h          |  181 +-
 arch/arm64/include/asm/kvm_host.h             |  212 ++-
 arch/arm64/include/asm/kvm_hyp.h              |   32 +-
 arch/arm64/include/asm/kvm_mmu.h              |   62 +-
 arch/arm64/include/asm/kvm_nested.h           |   94 +
 arch/arm64/include/asm/pgtable-hwdef.h        |    2 +
 arch/arm64/include/asm/stage2_pgtable.h       |    9 +
 arch/arm64/include/asm/sysreg.h               |  126 +-
 arch/arm64/include/asm/tlbflush.h             |   30 +
 arch/arm64/include/asm/vncr_mapping.h         |   73 +
 arch/arm64/include/uapi/asm/kvm.h             |    2 +
 arch/arm64/kernel/asm-offsets.c               |    3 +-
 arch/arm64/kernel/cpufeature.c                |   55 +
 arch/arm64/kvm/Makefile                       |    5 +
 arch/arm64/kvm/emulate-nested.c               |  205 +++
 arch/arm64/kvm/fpsimd.c                       |    6 +-
 arch/arm64/kvm/guest.c                        |   85 +-
 arch/arm64/kvm/handle_exit.c                  |   98 +-
 arch/arm64/kvm/hyp/Makefile                   |    1 +
 arch/arm64/kvm/hyp/at.c                       |  231 +++
 arch/arm64/kvm/hyp/debug-sr.c                 |   18 +-
 arch/arm64/kvm/hyp/entry.S                    |    3 +-
 arch/arm64/kvm/hyp/switch.c                   |  241 ++-
 arch/arm64/kvm/hyp/sysreg-sr.c                |  338 +++-
 arch/arm64/kvm/hyp/tlb.c                      |  134 +-
 arch/arm64/kvm/inject_fault.c                 |   12 -
 arch/arm64/kvm/nested.c                       |  899 ++++++++++
 arch/arm64/kvm/regmap.c                       |   37 +-
 arch/arm64/kvm/reset.c                        |   72 +-
 arch/arm64/kvm/sys_regs.c                     | 1523 +++++++++++++++--
 arch/arm64/kvm/sys_regs.h                     |    6 +
 arch/arm64/kvm/trace.h                        |   56 +
 include/kvm/arm_arch_timer.h                  |    9 +-
 include/kvm/arm_vgic.h                        |   21 +-
 virt/kvm/arm/arch_timer.c                     |  271 ++-
 virt/kvm/arm/arch_timer_nested.c              |   95 +
 virt/kvm/arm/arm.c                            |   72 +-
 virt/kvm/arm/hyp/vgic-v3-sr.c                 |   35 +-
 virt/kvm/arm/mmio.c                           |   14 +-
 virt/kvm/arm/mmu.c                            |  458 +++--
 virt/kvm/arm/trace.h                          |    6 +-
 virt/kvm/arm/vgic/vgic-init.c                 |   30 +
 virt/kvm/arm/vgic/vgic-kvm-device.c           |   22 +
 virt/kvm/arm/vgic/vgic-nested-trace.h         |  137 ++
 virt/kvm/arm/vgic/vgic-v2.c                   |   10 +-
 virt/kvm/arm/vgic/vgic-v3-nested.c            |  240 +++
 virt/kvm/arm/vgic/vgic-v3.c                   |   51 +-
 virt/kvm/arm/vgic/vgic.c                      |   74 +-
 virt/kvm/arm/vgic/vgic.h                      |   10 +
 66 files changed, 5925 insertions(+), 737 deletions(-)
 create mode 100644 arch/arm/include/asm/kvm_nested.h
 create mode 100644 arch/arm64/include/asm/kvm_nested.h
 create mode 100644 arch/arm64/include/asm/vncr_mapping.h
 create mode 100644 arch/arm64/kvm/emulate-nested.c
 create mode 100644 arch/arm64/kvm/hyp/at.c
 create mode 100644 arch/arm64/kvm/nested.c
 create mode 100644 virt/kvm/arm/arch_timer_nested.c
 create mode 100644 virt/kvm/arm/vgic/vgic-nested-trace.h
 create mode 100644 virt/kvm/arm/vgic/vgic-v3-nested.c
```
#### [PATCH v17 0/9] mm / virtio: Provide support for free page reporting
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From patchwork Tue Feb 11 22:45:51 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11377025
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DA01013A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:46:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A7EDF20842
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 22:46:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="N5OcV8fZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727681AbgBKWqA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 17:46:00 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:52088 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727573AbgBKWqA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 11 Feb 2020 17:46:00 -0500
Received: by mail-wm1-f68.google.com with SMTP id t23so5812671wmi.1;
        Tue, 11 Feb 2020 14:45:58 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:user-agent:mime-version
         :content-transfer-encoding;
        bh=GsPmJGGf+DooiUQnRVw88h1ECl93wLEKNnVoNBGKOV0=;
        b=N5OcV8fZOFmGzYJGP/LY5VTGUNr+WuyccD3l2/C8WFOKj9aeWqZzm72GG7UMk+yf0g
         E8SfAXA5HVUtQgO0tjtWwTmWj/EreDUYDh9/9S4U/KvJwstkQ3UlEGKZ3ViyIbc8CopW
         r1lzSmcKrpGO1q89zAaa5aDntetbw+BI4pbDBow87Uc7mthJgmf95AjQ7h6TN2O+9zem
         xHdB/HKrXgujcS/5B7x9vpzJ+ixP0ul/sP0RQC6Lun9Wuo+vR/T12j5ctUIwEIx9Ufnw
         YFJgYwXGHA5q25LPbqsn2K8TIACaZAez4hCDpv3NzL7K9AuPEJY1W91xztR9eASwyxJ6
         oEiA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:user-agent
         :mime-version:content-transfer-encoding;
        bh=GsPmJGGf+DooiUQnRVw88h1ECl93wLEKNnVoNBGKOV0=;
        b=D4w9EF8pocEIy4CGumdPBWs9P8yFoxEtn7vGTOezugMAuFNIfaI4Ydp67RLGC1sxwE
         6GTrfequ9+WA5es86sXI1rCw40ySVRUE+/N2IaNRysHlXJNaLOtg27gViHlOl43Cpbad
         wqVBpqadCvIMZNyzlPA+Qs6FJwy7tQwz/xoowuW2aF2R2XWR1EoGH1ZM/ZN5dZ2bAMOW
         A9KRA7QY8n2HghtnVHsg7J5SZ5CHXY7XOes4pxjoUAT7S1w8Z20+oLOqido9WCWkck+J
         GieYPjO0sfmBvzK+n1jyq5aWtMVGx9xIZ66/VfGb2GKFN90T/UaUC3TSrdfnJB/G+M5k
         5w1Q==
X-Gm-Message-State: APjAAAUVX1bUHqkVB8SdRtdzYpOo2stqqv8RXj+M8t39qij4ug1S7AsA
        Uw7kUy7Ba1NOEXEYxzArCZ0=
X-Google-Smtp-Source: 
 APXvYqwtnOKOSxIoOzvkoV5FpvgDv1HAvyY2jCvx+QtwMEUIeyuLvNPVE3+IgnU+0ZQYjGWQuYMsew==
X-Received: by 2002:a7b:c152:: with SMTP id z18mr8048957wmi.70.1581461157407;
        Tue, 11 Feb 2020 14:45:57 -0800 (PST)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 h10sm5810498wml.18.2020.02.11.14.45.52
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Tue, 11 Feb 2020 14:45:56 -0800 (PST)
Subject: [PATCH v17 0/9] mm / virtio: Provide support for free page reporting
From: Alexander Duyck <alexander.duyck@gmail.com>
To: kvm@vger.kernel.org, david@redhat.com, mst@redhat.com,
        linux-kernel@vger.kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, mgorman@techsingularity.net
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        willy@infradead.org, lcapitulino@redhat.com, dave.hansen@intel.com,
        wei.w.wang@intel.com, aarcange@redhat.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, mhocko@kernel.org,
        alexander.h.duyck@linux.intel.com, vbabka@suse.cz,
        osalvador@suse.de
Date: Tue, 11 Feb 2020 14:45:51 -0800
Message-ID: <20200211224416.29318.44077.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series provides an asynchronous means of reporting free guest pages
to a hypervisor so that the memory associated with those pages can be
dropped and reused by other processes and/or guests on the host. Using
this it is possible to avoid unnecessary I/O to disk and greatly improve
performance in the case of memory overcommit on the host.

When enabled we will be performing a scan of free memory every 2 seconds
while pages of sufficiently high order are being freed. In each pass at
least one sixteenth of each free list will be reported. By doing this we
avoid racing against other threads that may be causing a high amount of
memory churn.

The lowest page order currently scanned when reporting pages is
pageblock_order so that this feature will not interfere with the use of
Transparent Huge Pages in the case of virtualization.

Currently this is only in use by virtio-balloon however there is the hope
that at some point in the future other hypervisors might be able to make
use of it. In the virtio-balloon/QEMU implementation the hypervisor is
currently using MADV_DONTNEED to indicate to the host kernel that the page
is currently free. It will be zeroed and faulted back into the guest the
next time the page is accessed.

To track if a page is reported or not the Uptodate flag was repurposed and
used as a Reported flag for Buddy pages. We walk though the free list
isolating pages and adding them to the scatterlist until we either
encounter the end of the list or have processed at least one sixteenth of
the pages that were listed in nr_free prior to us starting. If we fill the
scatterlist before we reach the end of the list we rotate the list so that
the first unreported page we encounter is moved to the head of the list as
that is where we will resume after we have freed the reported pages back
into the tail of the list.

Below are the results from various benchmarks. I primarily focused on two
tests. The first is the will-it-scale/page_fault2 test, and the other is
a modified version of will-it-scale/page_fault1 that was enabled to use
THP. I did this as it allows for better visibility into different parts
of the memory subsystem. The guest is running with 32G for RAM on one
node of a E5-2630 v3. The host has had some features such as CPU turbo
disabled in the BIOS.

Test                   page_fault1 (THP)    page_fault2
Name            tasks  Process Iter  STDEV  Process Iter  STDEV
Baseline            1    1012402.50  0.14%     361855.25  0.81%
                   16    8827457.25  0.09%    3282347.00  0.34%

Patches Applied     1    1007897.00  0.23%     361887.00  0.26%
                   16    8784741.75  0.39%    3240669.25  0.48%

Patches Enabled     1    1010227.50  0.39%     359749.25  0.56%
                   16    8756219.00  0.24%    3226608.75  0.97%

Patches Enabled     1    1050982.00  4.26%     357966.25  0.14%
 page shuffle      16    8672601.25  0.49%    3223177.75  0.40%

Patches enabled     1    1003238.00  0.22%     360211.00  0.22%
 shuffle w/ RFC    16    8767010.50  0.32%    3199874.00  0.71%

The results above are for a baseline with a linux-next-20191219 kernel,
that kernel with this patch set applied but page reporting disabled in
virtio-balloon, the patches applied and page reporting fully enabled, the
patches enabled with page shuffling enabled, and the patches applied with
page shuffling enabled and an RFC patch that makes used of MADV_FREE in
QEMU. These results include the deviation seen between the average value
reported here versus the high and/or low value. I observed that during the
test memory usage for the first three tests never dropped whereas with the
patches fully enabled the VM would drop to using only a few GB of the
host's memory when switching from memhog to page fault tests.

Any of the overhead visible with this patch set enabled seems due to page
faults caused by accessing the reported pages and the host zeroing the page
before giving it back to the guest. This overhead is much more visible when
using THP than with standard 4K pages. In addition page shuffling seemed to
increase the amount of faults generated due to an increase in memory churn.
The overehad is reduced when using MADV_FREE as we can avoid the extra
zeroing of the pages when they are reintroduced to the host, as can be seen
when the RFC is applied with shuffling enabled.

The overall guest size is kept fairly small to only a few GB while the test
is running. If the host memory were oversubscribed this patch set should
result in a performance improvement as swapping memory in the host can be
avoided.

A brief history on the background of free page reporting can be found at:
https://lore.kernel.org/lkml/29f43d5796feed0dec8e8bb98b187d9dac03b900.camel@linux.intel.com/

Changes from v14:
https://lore.kernel.org/lkml/20191119214454.24996.66289.stgit@localhost.localdomain/
Renamed "unused page reporting" to "free page reporting"
  Updated code, kconfig, and patch descriptions
Split out patch for __free_isolated_page
  Renamed function to __putback_isolated_page
Rewrote core reporting functionality
  Added logic to reschedule worker in 2 seconds instead of run to completion
  Removed reported_pages statistics
  Removed REPORTING_REQUESTED bit used in zone flags
  Replaced page_reporting_dev_info refcount with state variable
  Removed scatterlist from page_reporting_dev_info
  Removed capacity from page reporting device
  Added dynamic scatterlist allocation/free at start/end of reporting process
  Updated __free_one_page so that reported pages are not always added to tail
  Added logic to handle error from report function
Updated virtio-balloon patch that adds support for page reporting
  Updated patch description to try and highlight differences in approaches
  Updated logic to reflect that we cannot limit the scatterlist from device
  Added logic to return error from report function
Moved documentation patch to end of patch set

Changes from v15:
https://lore.kernel.org/lkml/20191205161928.19548.41654.stgit@localhost.localdomain/
Rebased on linux-next-20191219
Split out patches for budget and moving head to last page processed
Updated budget code to reduce how much memory is reported per pass
Added logic to also rotate the list if we exit due a page isolation failure
Added migratetype as argument in __putback_isolated_page

Changes from v16:
https://lore.kernel.org/lkml/20200103210509.29237.18426.stgit@localhost.localdomain/
Rebased on linux-next-20200122
  Updated patch 2 to to account for removal of pr_info in __isolate_free_page 
Updated patch title for patches 7, 8, and 9 to included mm/page_reporting

Changes from v16.1:
https://lore.kernel.org/lkml/20200122173040.6142.39116.stgit@localhost.localdomain/
Rebased QEMU patches to latest
Rebased on linux-next-20200211
  Tweaked cover page to more accurately describe hinting process
  Verified results have not changed in significant way
---

Alexander Duyck (9):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Add function __putback_isolated_page
      mm: Introduce Reported pages
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing free page reports to host
      mm/page_reporting: Rotate reported pages to the tail of the list
      mm/page_reporting: Add budget limit on how many pages can be reported per pass
      mm/page_reporting: Add free page reporting documentation


 Documentation/vm/free_page_reporting.rst |   41 +++
 drivers/virtio/Kconfig                   |    1 
 drivers/virtio/virtio_balloon.c          |   87 +++++++
 include/linux/mmzone.h                   |   44 ----
 include/linux/page-flags.h               |   11 +
 include/linux/page_reporting.h           |   26 ++
 include/uapi/linux/virtio_balloon.h      |    1 
 mm/Kconfig                               |   11 +
 mm/Makefile                              |    1 
 mm/internal.h                            |    2 
 mm/page_alloc.c                          |  164 ++++++++++----
 mm/page_isolation.c                      |    6 
 mm/page_reporting.c                      |  364 ++++++++++++++++++++++++++++++
 mm/page_reporting.h                      |   54 ++++
 mm/shuffle.c                             |   12 -
 mm/shuffle.h                             |    6 
 16 files changed, 725 insertions(+), 106 deletions(-)
 create mode 100644 Documentation/vm/free_page_reporting.rst
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c
 create mode 100644 mm/page_reporting.h

--
```
#### [PATCH 0/7] vfio/pci: SR-IOV support
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
From patchwork Tue Feb 11 23:05:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11377095
Return-Path: <SRS0=UyAS=37=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7213F924
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 23:05:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 482592082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 11 Feb 2020 23:05:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HX8zUnAu"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727817AbgBKXFc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 11 Feb 2020 18:05:32 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:56333 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727799AbgBKXFb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 11 Feb 2020 18:05:31 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581462331;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=kHSxze2a1nRCn20xOJSopREUpsR/wHcjPJb/ZM+x9bk=;
        b=HX8zUnAuQN12GbxBfoHSaJsArO+KMiZgMLtzE3o65zJN3gzSGazQqUjYwukw9r2kHJ16PQ
        r13a0IJCV5d5ShSjaP+dfr+mFA0o7HKa31AbmOmh6uIGR25WTfdbG/fpRGvZltEZd5tot6
        Vp92gJIv0baEWW8K4q1nAHSgXcp48K0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-403-ov1zL7QkOzGol9JblHnMjg-1; Tue, 11 Feb 2020 18:05:22 -0500
X-MC-Unique: ov1zL7QkOzGol9JblHnMjg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6F81718FF660;
        Tue, 11 Feb 2020 23:05:20 +0000 (UTC)
Received: from gimli.home (ovpn-116-28.phx2.redhat.com [10.3.116.28])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2EAC160BF1;
        Tue, 11 Feb 2020 23:05:17 +0000 (UTC)
Subject: [PATCH 0/7] vfio/pci: SR-IOV support
From: Alex Williamson <alex.williamson@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-pci@vger.kernel.org, linux-kernel@vger.kernel.org,
        dev@dpdk.org, mtosatti@redhat.com, thomas@monjalon.net,
        bluca@debian.org, jerinjacobk@gmail.com,
        bruce.richardson@intel.com, cohuck@redhat.com
Date: Tue, 11 Feb 2020 16:05:16 -0700
Message-ID: <158145472604.16827.15751375540102298130.stgit@gimli.home>
User-Agent: StGit/0.19-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Given the mostly positive feedback from the RFC[1], here's a new
non-RFC revision.  Changes since RFC:

 - vfio_device_ops.match semantics refined
 - Use helpers for struct pci_dev.physfn to avoid breakage without
   CONFIG_PCI_IOV
 - Relax to allow SR-IOV configuration changes while PF is opened.
   There are potentially interesting use cases here, including
   perhaps QEMU emulating an SR-IOV capability and calling out
   to a privileged entity to manipulate sriov_numvfs and corral
   the resulting devices.
 - Retest vfio_device_feature.argsz to include uuid length.
 - Add Connie's R-b on 6/7

I still wish we had a solution to make it less opaque to the user
why a VFIO_GROUP_GET_DEVICE_FD() has failed if a VF token is
required, but this is still the best I've been able to come up with.
If there are objections or better ideas, please raise them now.

The synopsis of this series is that we have an ongoing desire to drive
PCIe SR-IOV PFs from userspace with VFIO.  There's an immediate need
for this with DPDK drivers and potentially interesting future use
cases in virtualization.  We've been reluctant to add this support
previously due to the dependency and trust relationship between the
VF device and PF driver.  Minimally the PF driver can induce a denial
of service to the VF, but depending on the specific implementation,
the PF driver might also be responsible for moving data between VFs
or have direct access to the state of the VF, including data or state
otherwise private to the VF or VF driver.

To help resolve these concerns, we introduce a VF token into the VFIO
PCI ABI, which acts as a shared secret key between drivers.  The
userspace PF driver is required to set the VF token to a known value
and userspace VF drivers are required to provide the token to access
the VF device.  If a PF driver is restarted with VF drivers in use, it
must also provide the current token in order to prevent a rogue
untrusted PF driver from replacing a known driver.  The degree to
which this new token is considered secret is left to the userspace
drivers, the kernel intentionally provides no means to retrieve the
current token.

Note that the above token is only required for this new model where
both the PF and VF devices are usable through vfio-pci.  Existing
models of VFIO drivers where the PF is used without SR-IOV enabled
or the VF is bound to a userspace driver with an in-kernel, host PF
driver are unaffected.

The latter configuration above also highlights a new inverted scenario
that is now possible, a userspace PF driver with in-kernel VF drivers.
I believe this is a scenario that should be allowed, but should not be
enabled by default.  This series includes code to set a default
driver_override for VFs sourced from a vfio-pci user owned PF, such
that the VFs are also bound to vfio-pci.  This model is compatible
with tools like driverctl and allows the system administrator to
decide if other bindings should be enabled.  The VF token interface
above exists only between vfio-pci PF and VF drivers, once a VF is
bound to another driver, the administrator has effectively pronounced
the device as trusted.  The vfio-pci driver will note alternate
binding in dmesg for logging and debugging purposes.

Please review, comment, and test.  The example QEMU implementation
provided with the RFC[2] is still current for this version.  Thanks,

Alex

[1] https://lore.kernel.org/lkml/158085337582.9445.17682266437583505502.stgit@gimli.home/
[2] https://lore.kernel.org/lkml/20200204161737.34696b91@w520.home/
---

Alex Williamson (7):
      vfio: Include optional device match in vfio_device_ops callbacks
      vfio/pci: Implement match ops
      vfio/pci: Introduce VF token
      vfio: Introduce VFIO_DEVICE_FEATURE ioctl and first user
      vfio/pci: Add sriov_configure support
      vfio/pci: Remove dev_fmt definition
      vfio/pci: Cleanup .probe() exit paths


 drivers/vfio/pci/vfio_pci.c         |  312 ++++++++++++++++++++++++++++++++---
 drivers/vfio/pci/vfio_pci_private.h |   10 +
 drivers/vfio/vfio.c                 |   20 ++
 include/linux/vfio.h                |    4 
 include/uapi/linux/vfio.h           |   37 ++++
 5 files changed, 355 insertions(+), 28 deletions(-)
```
