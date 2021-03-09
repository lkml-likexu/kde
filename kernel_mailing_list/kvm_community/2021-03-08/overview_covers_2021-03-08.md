

#### [PATCH V2 0/4] vDPA/ifcvf: enables Intel C5000X-PL virtio-net
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
From patchwork Mon Mar  8 08:35:21 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 12121773
Return-Path: <SRS0=plzI=IG=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id E1656C4332D
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 08:41:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B499B651C9
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 08:41:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231684AbhCHIk7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 03:40:59 -0500
Received: from mga07.intel.com ([134.134.136.100]:18103 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S231629AbhCHIkr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 8 Mar 2021 03:40:47 -0500
IronPort-SDR: 
 VP1R2fNgB0H4ROvQN4elXIgzEcSUDGiwox5Ej6QNnJSfdmy3pj2wEfNZQNDOwQPObp5kqdAwh6
 zD4RmtvA9ZTA==
X-IronPort-AV: E=McAfee;i="6000,8403,9916"; a="252017299"
X-IronPort-AV: E=Sophos;i="5.81,232,1610438400";
   d="scan'208";a="252017299"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Mar 2021 00:40:43 -0800
IronPort-SDR: 
 5/7mWfhbXQZ9W+tE+3a0S4/vPOpQqcAATcML29BS7DsDhncEUFxBmutrNt3ZPPKSiEa0O1DUhZ
 tE7tAFEo1Aqw==
X-IronPort-AV: E=Sophos;i="5.81,232,1610438400";
   d="scan'208";a="508855612"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.73])
  by fmsmga001-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Mar 2021 00:40:40 -0800
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com, lulu@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH V2 0/4] vDPA/ifcvf: enables Intel C5000X-PL virtio-net
Date: Mon,  8 Mar 2021 16:35:21 +0800
Message-Id: <20210308083525.382514-1-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enabled Intel FGPA SmartNIC C5000X-PL virtio-net for vDPA

changes from V1:
remove version number string(Leon)
add new device ids and remove original device ids
in separate patches(Jason)

Zhu Lingshan (4):
  vDPA/ifcvf: get_vendor_id returns a device specific vendor id
  vDPA/ifcvf: enable Intel C5000X-PL virtio-net for vDPA
  vDPA/ifcvf: rename original IFCVF dev ids to N3000 ids
  vDPA/ifcvf: remove the version number string

 drivers/vdpa/ifcvf/ifcvf_base.h | 13 +++++++++----
 drivers/vdpa/ifcvf/ifcvf_main.c | 20 +++++++++++++-------
 2 files changed, 22 insertions(+), 11 deletions(-)
```
#### [PATCH v5 00/12] x86: major paravirt cleanup
##### From: Juergen Gross <jgross@suse.com>

```c
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=suse.com; s=susede1;
        t=1615206531;
 h=from:from:reply-to:date:date:message-id:message-id:to:to:cc:cc:
         mime-version:mime-version:
  content-transfer-encoding:content-transfer-encoding;
        bh=Pj0+lsoXMYSDviFMNu3CfGDulAqhBZd0duxurV0jt/k=;
        b=ullbjypHk4a2OSdXRZBXV7LzXx1wRPq0P3DUkuf3g00TxnX2Kvmikn2mvZgT5yu1bK+GT9
        Pb18L02feaPu+UmwjPoQNvBkbpJDORl8H6ArZ/XWAobYvxZmsd1kHtOeWcA3mN+bVvHI/I
        evXt2ltyGZ054ZgETkOoGM4IjjxGEog=
Received: from relay2.suse.de (unknown [195.135.221.27])
        by mx2.suse.de (Postfix) with ESMTP id EE520ADCD;
        Mon,  8 Mar 2021 12:28:50 +0000 (UTC)
From: Juergen Gross <jgross@suse.com>
To: xen-devel@lists.xenproject.org, linux-kernel@vger.kernel.org,
        x86@kernel.org, virtualization@lists.linux-foundation.org,
        linux-arm-kernel@lists.infradead.org, linux-hyperv@vger.kernel.org,
        kvm@vger.kernel.org, clang-built-linux@googlegroups.com
Cc: Juergen Gross <jgross@suse.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Jason Baron <jbaron@akamai.com>,
        Steven Rostedt <rostedt@goodmis.org>,
        Ard Biesheuvel <ardb@kernel.org>, Deep Shah <sdeep@vmware.com>,
        "VMware, Inc." <pv-drivers@vmware.com>,
        Russell King <linux@armlinux.org.uk>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Stefano Stabellini <sstabellini@kernel.org>,
        Andy Lutomirski <luto@kernel.org>,
        Nathan Chancellor <nathan@kernel.org>,
        Nick Desaulniers <ndesaulniers@google.com>
Subject: [PATCH v5 00/12] x86: major paravirt cleanup
Date: Mon,  8 Mar 2021 13:28:32 +0100
Message-Id: <20210308122844.30488-1-jgross@suse.com>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This is a major cleanup of the paravirt infrastructure aiming at
eliminating all custom code patching via paravirt patching.

This is achieved by using ALTERNATIVE instead, leading to the ability
to give objtool access to the patched in instructions.

In order to remove most of the 32-bit special handling from pvops the
time related operations are switched to use static_call() instead.

At the end of this series all paravirt patching has to do is to
replace indirect calls with direct ones. In a further step this could
be switched to static_call(), too.

Changes in V5:
- patches 1-5 of V4 dropped, as already applied
- new patches 1+3
- fixed patch 2
- split V4 patch 8 into patches 4+5
- use flag byte instead of negative feature bit for "not feature"

Changes in V4:
- fixed several build failures
- removed objtool patch, as objtool patches are in tip now
- added patch 1 for making usage of static_call easier
- even more cleanup

Changes in V3:
- added patches 7 and 12
- addressed all comments

Changes in V2:
- added patches 5-12

Juergen Gross (12):
  staticcall: move struct static_call_key definition to
    static_call_types.h
  x86/paravirt: switch time pvops functions to use static_call()
  x86/alternative: drop feature parameter from ALTINSTR_REPLACEMENT()
  x86/alternative: support not-feature
  x86/alternative: support ALTERNATIVE_TERNARY
  x86: add new features for paravirt patching
  x86/paravirt: remove no longer needed 32-bit pvops cruft
  x86/paravirt: simplify paravirt macros
  x86/paravirt: switch iret pvops to ALTERNATIVE
  x86/paravirt: add new macros PVOP_ALT* supporting pvops in
    ALTERNATIVEs
  x86/paravirt: switch functions with custom code to ALTERNATIVE
  x86/paravirt: have only one paravirt patch function

 arch/arm/include/asm/paravirt.h               |  14 +-
 arch/arm/kernel/paravirt.c                    |   9 +-
 arch/arm64/include/asm/paravirt.h             |  14 +-
 arch/arm64/kernel/paravirt.c                  |  13 +-
 arch/x86/Kconfig                              |   1 +
 arch/x86/entry/entry_32.S                     |   4 +-
 arch/x86/entry/entry_64.S                     |   2 +-
 arch/x86/include/asm/alternative-asm.h        |  10 +
 arch/x86/include/asm/alternative.h            |  28 ++-
 arch/x86/include/asm/cpufeature.h             |   2 +
 arch/x86/include/asm/cpufeatures.h            |   2 +
 arch/x86/include/asm/irqflags.h               |   7 +-
 arch/x86/include/asm/mshyperv.h               |   2 +-
 arch/x86/include/asm/paravirt.h               | 167 +++++++-------
 arch/x86/include/asm/paravirt_types.h         | 210 +++++++-----------
 arch/x86/kernel/Makefile                      |   3 +-
 arch/x86/kernel/alternative.c                 |  37 ++-
 arch/x86/kernel/asm-offsets.c                 |   7 -
 arch/x86/kernel/cpu/vmware.c                  |   5 +-
 arch/x86/kernel/kvm.c                         |   2 +-
 arch/x86/kernel/kvmclock.c                    |   2 +-
 arch/x86/kernel/paravirt-spinlocks.c          |   9 +
 arch/x86/kernel/paravirt.c                    |  78 ++-----
 arch/x86/kernel/paravirt_patch.c              |  99 ---------
 arch/x86/kernel/tsc.c                         |   2 +-
 arch/x86/xen/enlighten_pv.c                   |   4 +-
 arch/x86/xen/time.c                           |  11 +-
 drivers/xen/time.c                            |   3 +-
 include/linux/static_call.h                   |  18 --
 include/linux/static_call_types.h             |  18 ++
 tools/include/linux/static_call_types.h       |  18 ++
 tools/objtool/arch/x86/include/arch/special.h |   6 +-
 32 files changed, 339 insertions(+), 468 deletions(-)
 delete mode 100644 arch/x86/kernel/paravirt_patch.c
Acked-by: Peter Zijlstra (Intel) <peterz@infradead.org>
```
#### [PATCH v1 00/14] vfio: Device memory DMA mapping improvements
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
From patchwork Mon Mar  8 21:47:16 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12123435
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F0CCCC43381
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 21:48:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B667B6529E
	for <kvm@archiver.kernel.org>; Mon,  8 Mar 2021 21:48:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231321AbhCHVsS (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 8 Mar 2021 16:48:18 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:59805 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S231195AbhCHVrx (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 8 Mar 2021 16:47:53 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1615240072;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=D+es/eWhmxxz29JK+WvmP/Ck2/6vYOLc/3sWGVtLCbc=;
        b=RFgXid9+IxNYras43sTW+ZLPZD7AskI0UkHzUclZIRk9RuxgTNb6oIQ+vGwMHTm3qsfGrK
        tW7D+cKcvSb/fhZESF6K80UW68sNiWWBEwZ8T/gCSBfsJX+S9m7dwmBAJXg/H5tZhmppdw
        1NjhZfe65sYslA30mZlvFe+Rx68n+Pg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-242-5e4ZJSszOj6VeyxB2DsjeQ-1; Mon, 08 Mar 2021 16:47:24 -0500
X-MC-Unique: 5e4ZJSszOj6VeyxB2DsjeQ-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 35A241005D45;
        Mon,  8 Mar 2021 21:47:23 +0000 (UTC)
Received: from gimli.home (ovpn-112-255.phx2.redhat.com [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C66601037E80;
        Mon,  8 Mar 2021 21:47:16 +0000 (UTC)
Subject: [PATCH v1 00/14] vfio: Device memory DMA mapping improvements
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, jgg@nvidia.com, peterx@redhat.com
Date: Mon, 08 Mar 2021 14:47:16 -0700
Message-ID: <161523878883.3480.12103845207889888280.stgit@gimli.home>
User-Agent: StGit/0.21-2-g8ef5
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The primary goal of this series is to better manage device memory
mappings, both with a much simplified scheme to zap CPU mappings of
device memory using unmap_mapping_range() and also to restrict IOMMU
mappings of PFNMAPs to vfio device memory and drop those mappings on
device release.  This series updates vfio-pci to include the necessary
vma-to-pfn interface, allowing the type1 IOMMU backend to recognize
vfio device memory.  If other bus drivers support peer-to-peer DMA,
they should be updated with a similar callback and trigger the device
notifier on release.

RFC->v1:

 - Fix some incorrect ERR handling
 - Fix use of vm_pgoff to be compatible with unmap_mapping_range()
 - Add vma-to-pfn interfaces
 - Generic device-from-vma handling
 - pfnmap obj directly maps back to vfio_dma obj
 - No bypass for strict MMIO handling
 - Batch PFNMAP handling
 - Follow-on patches to cleanup "extern" usage and bare unsigned

Works in my environment, further testing always appreciated.  This
will need to be merged with a solution for concurrent fault handling.
Thanks especially to Jason Gunthorpe for previous reviews and
suggestions.  Thanks,

Alex

RFC:https://lore.kernel.org/kvm/161401167013.16443.8389863523766611711.stgit@gimli.home/
---

Alex Williamson (14):
      vfio: Create vfio_fs_type with inode per device
      vfio: Update vfio_add_group_dev() API
      vfio: Export unmap_mapping_range() wrapper
      vfio/pci: Use vfio_device_unmap_mapping_range()
      vfio: Create a vfio_device from vma lookup
      vfio: Add vma to pfn callback
      vfio: Add a device notifier interface
      vfio/pci: Notify on device release
      vfio/type1: Refactor pfn_list clearing
      vfio/type1: Pass iommu and dma objects through to vaddr_get_pfn
      vfio/type1: Register device notifier
      vfio/type1: Support batching of device mappings
      vfio: Remove extern from declarations across vfio
      vfio: Cleanup use of bare unsigned


 Documentation/driver-api/vfio-mediated-device.rst |   19 +-
 Documentation/driver-api/vfio.rst                 |    8 -
 drivers/s390/cio/vfio_ccw_cp.h                    |   13 +
 drivers/s390/cio/vfio_ccw_private.h               |   14 +
 drivers/s390/crypto/vfio_ap_private.h             |    2 
 drivers/vfio/Kconfig                              |    1 
 drivers/vfio/fsl-mc/vfio_fsl_mc.c                 |    6 -
 drivers/vfio/fsl-mc/vfio_fsl_mc_private.h         |    7 -
 drivers/vfio/mdev/vfio_mdev.c                     |    5 
 drivers/vfio/pci/vfio_pci.c                       |  229 ++++-----------------
 drivers/vfio/pci/vfio_pci_intrs.c                 |   42 ++--
 drivers/vfio/pci/vfio_pci_private.h               |   69 +++---
 drivers/vfio/platform/vfio_platform_common.c      |    7 -
 drivers/vfio/platform/vfio_platform_irq.c         |   21 +-
 drivers/vfio/platform/vfio_platform_private.h     |   31 +--
 drivers/vfio/vfio.c                               |  154 ++++++++++++--
 drivers/vfio/vfio_iommu_type1.c                   |  234 +++++++++++++++------
 include/linux/vfio.h                              |  129 ++++++------
 18 files changed, 543 insertions(+), 448 deletions(-)
```
