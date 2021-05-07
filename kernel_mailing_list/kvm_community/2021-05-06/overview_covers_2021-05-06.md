

#### [RFC][PATCH v1 00/10] Enable encrypted guest memory access in QEMU
##### From: Yuan Yao <yuan.yao@linux.intel.com>
From: Yuan Yao <yuan.yao@intel.com>

```c
From patchwork Thu May  6 01:40:27 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yuan Yao <yuan.yao@linux.intel.com>
X-Patchwork-Id: 12241443
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8E0AEC433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 01:40:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4EE22613B5
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 01:40:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230144AbhEFBlo (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 5 May 2021 21:41:44 -0400
Received: from mga17.intel.com ([192.55.52.151]:23042 "EHLO mga17.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229465AbhEFBln (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 May 2021 21:41:43 -0400
IronPort-SDR: 
 xb+9QEEzCv4VccF6ESe+8/bOZfaLMxfjv7XTHLdn7Bpdd+5577oe7WWdOfM8pWtyN8QdZqeO7r
 xN8CD/m67R4w==
X-IronPort-AV: E=McAfee;i="6200,9189,9975"; a="178579116"
X-IronPort-AV: E=Sophos;i="5.82,276,1613462400";
   d="scan'208";a="178579116"
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga107.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 May 2021 18:40:46 -0700
IronPort-SDR: 
 zQ7EbdqEJwrBw+4OMqt9VyMttbWhq7tYPmxvfMikKcLBu9QuvwYJtGo5L8CSQLzE7xehyIKi0b
 /X6YY9A5P1nQ==
X-IronPort-AV: E=Sophos;i="5.82,276,1613462400";
   d="scan'208";a="469220276"
Received: from yy-desk-7060.sh.intel.com ([10.239.159.38])
  by orsmga001-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 05 May 2021 18:40:42 -0700
From: Yuan Yao <yuan.yao@linux.intel.com>
To: pbonzini@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org, dgilbert@redhat.com,
        ehabkost@redhat.com, mst@redhat.com, armbru@redhat.com,
        mtosatti@redhat.com, ashish.kalra@amd.com, Thomas.Lendacky@amd.com,
        brijesh.singh@amd.com, isaku.yamahata@intel.com, yuan.yao@intel.com
Subject: [RFC][PATCH v1 00/10] Enable encrypted guest memory access in QEMU
Date: Thu,  6 May 2021 09:40:27 +0800
Message-Id: <20210506014037.11982-1-yuan.yao@linux.intel.com>
X-Mailer: git-send-email 2.17.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Yuan Yao <yuan.yao@intel.com>

This RFC series introduces the basic framework and a common
implementation on x86 to handle encrypted guest memory
reading/writing, to support QEMU's built-in guest debugging
features, like the monitor command xp and gdbstub.

The encrypted guest which its memory and/or register context
is encrypted by vendor specific technology(AMD SEV/INTEL TDX),
is able to resist the attack from malicious VMM or other
privileged components in host side, however, this ability also
breaks down the QEMU's built-in guest debugging features,
because it prohibits the direct guest memory accessing
(memcpy() with HVA) from QEMU which is the base of these
debugging features.

The framework part based on the previous patche set from
AMD[1] and some discussion result in community[2]. The main
idea is, introduce some new debug interfaces to handle the
encrypted guest physical memory accessing, also introduce
new interfaces in MemoryRegion to handle the actual accessing
there with KVM, don't bother the exist memory access logic or
callbacks as far as possible. 

[1] https://lore.kernel.org/qemu-devel/
    cover.1605316268.git.ashish.kalra@amd.com/
[2] https://lore.kernel.org/qemu-devel/
    20200922201124.GA6606@ashkalra_ubuntu_server/

 - The difference part in this patch series:
   - We introduce another new vm level ioctl focus on the encrypted
     guest memory accessing:

     KVM_MEMORY_ENCRYPT_{READ,WRITE}_MEMORY

     struct kvm_rw_memory rw;
     rw.addr = gpa_OR_hva;
     rw.buf = (__u64)src;
     rw.len = len;
     kvm_vm_ioctl(kvm_state,
                  KVM_MEMORY_ENCRYPT_{READ,WRITE}_MEMORY,
                  &rw);

     This new ioctl has more neutral and general name for its
     purpose, the debugging support of AMD SEV and INTEL TDX
     can be covered by a unify QEMU implementation on x86 with this
     ioctl. Although only INTEL TD guest is supported in this series,
     AMD SEV could be also supported with implementation of this
     ioctl in KVM, plus small modifications in QEMU to enable the
     unify part.

   - The MemoryRegion interface introduced by AMD before now has
     addtional GPA parameter(only HVA before).
     This is for INTEL TDX which uses GPA to do guest memory
     accessing. This change won't impact AMD SEV which is using
     HVA to access the guest memory.

 - New APIs in QEMU:
   - Physical memory accessing:
     - cpu_physical_memory_rw_debug().
     - cpu_physical_memory_read_debug().
     - cpu_physical_memory_write_debug().
     - x86_ldl_phys_debug().
     - x86_ldq_phys_debug().
   - Access from address_space:
     - address_space_read_debug().
     - address_space_write_rom_debug().
   - Virtual memory accessing and page table walking:
     - cpu_memory_rw_debug().
     - x86_cpu_get_phys_page_attrs_encrypted_debug().

 - New intrfaces in QEMU:
   - MemoryDebugOps *physical_memory_debug_op
     - For normal guest:
       Just call the old exist memory RW functions.
     - For encrypted guest:
       Forward the request to MemoryRegion->ram_debug_ops

   - MemoryRegionRAMReadWriteOps MemoryRegion::*ram_debug_ops
     - For normal guest:
       NULL and nobody use it.
     - For encrypted guest:
       Forward the request to common/vendor specific implementation.

 - The relationship diagram of the APIs and interfaces:

                 +---------------------------------------------+
                 |x86_cpu_get_phys_page_attrs_encrypted_debug()|
                 +----------------------------------+----------+
                                                    |
          +---------------------------------+       |
          |cpu_physical_memory_rw_debug()   |       |
          |cpu_physical_memory_read_debug() |       |
          |cpu_physical_memory_write_debug()|       |
          +----------------------+----------+       |
                                 |                  |
   +---------------------+       |        +---------v----------+
   |cpu_memory_rw_debug()|       |        |x86_ldl_phys_debug()|
   +-------------------+-+       |        |x86_ldq_phys_debug()|
                       |         |        +-------+------------+
                       |         |                |
                       |         |                |
  +--------------------v---------v----------------v------------+
  |         MemoryDebugOps *physical_memory_debug_op           |
  +----------------------+--------------------------+----------+
                         |                          |
                         |Encrypted guest           |Normal guest
                         |                          |
    +--------------------v-----------------------+  |
    |address_space_encrypted_memory_read_debug() |  |
    |address_space_encrypted_rom_write_debug()   |  |
    +--------------------+-----------------------+  |
                         |                          | 
                         |          +---------------v----------+
                         |          |address_space_read()      |
                         |          |address_space_write_rom() |
                         |          +--------------------------+
                         |
        +----------------v----------------+
        | address_space_read_debug()      |
        | address_space_write_rom_debug() |
        +----------------+----------------+
                         |
                         |
                         |
        +----------------v----------------+
        |  MemoryRegionRAMReadWriteOps    |
        |  MemoryRegion::*ram_debug_ops   |
        +--------+--------------+---------+
                 |              |
                 |              |Normal guest
                 |              |
  Encrypted guest|          +---v-------------------+
                 |          | NULL(nobody using it) |
                 |          +-----------------------+
                 |
       +---------v----------------------------+
       |  kvm_encrypted_guest_read_memory()   |
       |  kvm_encrypted_guest_write_memory()  |
       +--------------------------------------+

Ashish Kalra (2):
  Introduce new MemoryDebugOps which hook into guest virtual and
    physical memory debug interfaces such as cpu_memory_rw_debug, to
    allow vendor specific assist/hooks for debugging and delegating
    accessing the guest memory. This is required for example in case of
    AMD SEV platform where the guest memory is encrypted and a SEV
    specific debug assist/hook will be required to access the guest
    memory.
  Add new address_space_read and address_space_write debug helper
    interfaces which can be invoked by vendor specific guest memory
    debug assist/hooks to do guest RAM memory accesses using the added
    MemoryRegion callbacks.

Brijesh Singh (2):
  Extend the MemTxAttrs to include a 'debug' flag. The flag can be used
    as general indicator that operation was triggered by the debugger.
  Currently, guest memory access for debugging purposes is performed
    using memcpy(). Extend the 'struct MemoryRegion' to include new
    callbacks that can be used to override the use of memcpy() with
    something else.

Yuan Yao (6):
  Introduce new interface KVMState::set_mr_debug_ops and its wrapper
  Implements the common MemoryRegion::ram_debug_ops for encrypted guests
  Set the RAM's MemoryRegion::debug_ops for INTEL TD guests
  Introduce debug version of physical memory read/write API
  Change the monitor and other commands and gdbstub to use the debug API
  Introduce new CPUClass::get_phys_page_attrs_debug implementation for
    encrypted guests

 accel/kvm/kvm-all.c       |  17 +++++
 accel/stubs/kvm-stub.c    |  11 +++
 dump/dump.c               |   2 +-
 gdbstub.c                 |   4 +-
 hw/i386/pc.c              |   4 +
 include/exec/cpu-common.h |  14 ++++
 include/exec/memattrs.h   |   4 +
 include/exec/memory.h     |  54 +++++++++++++
 include/sysemu/kvm.h      |   5 ++
 include/sysemu/tdx.h      |   3 +
 monitor/misc.c            |  12 ++-
 softmmu/cpus.c            |   2 +-
 softmmu/physmem.c         | 154 +++++++++++++++++++++++++++++++++++++-
 target/i386/cpu.h         |   4 +
 target/i386/helper.c      |  64 +++++++++++++---
 target/i386/kvm/kvm.c     |  68 +++++++++++++++++
 target/i386/kvm/tdx.c     |  21 ++++++
 target/i386/monitor.c     |  52 ++++++-------
 18 files changed, 447 insertions(+), 48 deletions(-)
```
#### [PATCH 0/2] x86: Disable kexec for SEV-ES guests
##### From: Joerg Roedel <joro@8bytes.org>
From: Joerg Roedel <jroedel@suse.de>

```c
From patchwork Thu May  6 09:31:20 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12241911
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2DD4CC433B4
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 09:32:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C19D7611AD
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 09:31:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234002AbhEFJc4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 05:32:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:36818 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S233028AbhEFJcz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 May 2021 05:32:55 -0400
Received: from theia.8bytes.org (8bytes.org
 [IPv6:2a01:238:4383:600:38bc:a715:4b6d:a889])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 3288EC061574;
        Thu,  6 May 2021 02:31:58 -0700 (PDT)
Received: from cap.home.8bytes.org (p5b0069de.dip0.t-ipconnect.de
 [91.0.105.222])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id EB37B247;
        Thu,  6 May 2021 11:31:55 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Eric Biederman <ebiederm@xmission.com>, x86@kernel.org
Cc: kexec@lists.infradead.org, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        Joerg Roedel <joro@8bytes.org>, linux-coco@lists.linux.dev,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH 0/2] x86: Disable kexec for SEV-ES guests
Date: Thu,  6 May 2021 11:31:20 +0200
Message-Id: <20210506093122.28607-1-joro@8bytes.org>
X-Mailer: git-send-email 2.31.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Hi,

two small patches to disable kexec on x86 when running as an SEV-ES
guest. Trying to kexec a new kernel would fail anyway because there is
no mechanism yet to hand over the APs from the old to the new kernel.
Supporting this needs changes in the Hypervisor and the guest kernel
as well.

This code is currently being work on, but disable kexec in SEV-ES
guests until it is ready.

Please review.

Regards,

	Joerg

Joerg Roedel (2):
  kexec: Allow architecture code to opt-out at runtime
  x86/kexec/64: Forbid kexec when running as an SEV-ES guest

 arch/x86/kernel/machine_kexec_64.c |  8 ++++++++
 kernel/kexec.c                     | 14 ++++++++++++++
 2 files changed, 22 insertions(+)
```
#### [PATCH 0/8] KVM: VMX: Implement nested TSC scaling
##### From: ilstam@mailbox.org
From: Ilias Stamatis <ilstam@amazon.com>

```c
Received: from smtp1.mailbox.org ([80.241.60.240])
        by spamfilter02.heinlein-hosting.de (spamfilter02.heinlein-hosting.de
 [80.241.56.116]) (amavisd-new, port 10030)
        with ESMTP id FYd6A0ERsLu4; Thu,  6 May 2021 12:34:01 +0200 (CEST)
From: ilstam@mailbox.org
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: ilstam@amazon.com, seanjc@google.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        haozhong.zhang@intel.com, zamsden@gmail.com, mtosatti@redhat.com,
        dplotnikov@virtuozzo.com, dwmw@amazon.co.uk
Subject: [PATCH 0/8] KVM: VMX: Implement nested TSC scaling
Date: Thu,  6 May 2021 10:32:20 +0000
Message-Id: <20210506103228.67864-1-ilstam@mailbox.org>
X-MBO-SPAM-Probability: 
X-Rspamd-Score: -4.11 / 15.00 / 15.00
X-Rspamd-Queue-Id: A98F71404
X-Rspamd-UID: 10da07
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ilias Stamatis <ilstam@amazon.com>

KVM currently supports hardware-assisted TSC scaling but only for L1 and it
doesn't expose the feature to nested guests. This patch series adds support for
nested TSC scaling and allows both L1 and L2 to be scaled with different
scaling factors.

When scaling and offsetting is applied, the TSC for the guest is calculated as:

(TSC * multiplier >> 48) + offset

With nested scaling the values in VMCS01 and VMCS12 need to be merged
together and stored in VMCS02.

The VMCS02 values are calculated as follows:

offset_02 = ((offset_01 * mult_12) >> 48) + offset_12
mult_02 = (mult_01 * mult_12) >> 48

The last patch of the series adds a KVM selftest.

Ilias Stamatis (8):
  KVM: VMX: Add a TSC multiplier field in VMCS12
  KVM: X86: Store L1's TSC scaling ratio in 'struct kvm_vcpu_arch'
  KVM: X86: Pass an additional 'L1' argument to kvm_scale_tsc()
  KVM: VMX: Adjust the TSC-related VMCS fields on L2 entry and exit
  KVM: X86: Move tracing outside write_l1_tsc_offset()
  KVM: VMX: Make vmx_write_l1_tsc_offset() work with nested TSC scaling
  KVM: VMX: Expose TSC scaling to L2
  KVM: selftests: x86: Add vmx_nested_tsc_scaling_test

 arch/x86/include/asm/kvm_host.h               |   8 +-
 arch/x86/kvm/svm/svm.c                        |   4 -
 arch/x86/kvm/vmx/nested.c                     |  32 ++-
 arch/x86/kvm/vmx/vmcs12.c                     |   1 +
 arch/x86/kvm/vmx/vmcs12.h                     |   4 +-
 arch/x86/kvm/vmx/vmx.c                        |  31 ++-
 arch/x86/kvm/x86.c                            |  54 ++++-
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../kvm/x86_64/vmx_nested_tsc_scaling_test.c  | 209 ++++++++++++++++++
 10 files changed, 312 insertions(+), 33 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/vmx_nested_tsc_scaling_test.c
```
#### [PATCH v2 0/9] misc: Replace alloca() by g_malloc()
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c
From patchwork Thu May  6 13:37:49 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?=
 <philmd@redhat.com>
X-Patchwork-Id: 12242143
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B30D5C433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 13:38:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 764F2613F5
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 13:38:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234306AbhEFNjD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 09:39:03 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:47035 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234303AbhEFNjC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 May 2021 09:39:02 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620308284;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=vbCDEC95SLEC7NvBUhks/P3w4WBw9RAigT+kNtWZnU0=;
        b=Jv1tbvCGglKUBFYqfewu2XJXU/j5zoKWTR9dUqvk7dSvd3AT208rBOAGrskOel9Kvp962D
        bGVIuA/SsQAsEwB2GswgXMNrM8MeY+il5NJOSEPXJI6K+6p3QIU1FWxLUQ9XPYe1gYygnt
        ZWUEpgDoZ51YZLSA34UCTVC9QXiJ5aA=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-447--QSe6JI3OuWDG87omWAQyw-1; Thu, 06 May 2021 09:38:01 -0400
X-MC-Unique: -QSe6JI3OuWDG87omWAQyw-1
Received: by mail-wm1-f69.google.com with SMTP id
 j128-20020a1c55860000b02901384b712094so2681163wmb.2
        for <kvm@vger.kernel.org>; Thu, 06 May 2021 06:38:01 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=vbCDEC95SLEC7NvBUhks/P3w4WBw9RAigT+kNtWZnU0=;
        b=CE6QyV+U7qJnvfPq6S0MtuTgAwd+4zmHPsq7AjAHvUw/OecFRDIXvTnUbQkaurPM5Z
         9wZHncBJGxcwt7s3DYeS+kyDmrLmSJaxxNpTxlMvlAWkvBSuZa8nDCZlz3LzuVpdT3OM
         TdUy/qSkz4K8DrrVVkLRHntZdUGLUrngzjl55PJo3HoFjDsB6tRVbGdHksIs7jO7eNKt
         kDzOX6tNSc5aSqwF67DKKd/Oc+ZsykVX6Zm3MVs9ts38yBqYMocBolwoF6VSmbUUv1nr
         /XeWlDa6efwzmm7CmKHJlTw4IMpCW8tjeZZ0YW1XShW7UJD27AzrO9DrX3iYp4byX6Yi
         WalQ==
X-Gm-Message-State: AOAM533wGBmmgRyetQ8ndsvHjLwWYkNUCTdO3FGLaWO4/IjZ3hWz+bjB
        Ga0b12ysE+CvNXc/Jz74N7j2/G0s1Gq9hSMmoTVjpgS+2AnB+DpG4RYmvruKRP0Q0Og876R0mNa
        5NTcv1m42H0j9
X-Received: by 2002:a5d:4412:: with SMTP id z18mr5160046wrq.103.1620308280249;
        Thu, 06 May 2021 06:38:00 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJw/lpKgeXPwedLJvJ4wj/Fl9lQspP9LDG16WhazAs5p4oUW5BEc7XMk6TLu2WdAwkGSukQsXA==
X-Received: by 2002:a5d:4412:: with SMTP id z18mr5160036wrq.103.1620308280136;
        Thu, 06 May 2021 06:38:00 -0700 (PDT)
Received: from localhost.localdomain
 (astrasbourg-652-1-219-60.w90-40.abo.wanadoo.fr. [90.40.114.60])
        by smtp.gmail.com with ESMTPSA id
 e8sm4414680wrt.30.2021.05.06.06.37.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 06 May 2021 06:37:59 -0700 (PDT)
From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>
To: qemu-devel@nongnu.org
Cc: kvm@vger.kernel.org, qemu-ppc@nongnu.org, qemu-arm@nongnu.org,
 Gerd Hoffmann <kraxel@redhat.com>, Paolo Bonzini <pbonzini@redhat.com>,
	=?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>, =?utf-8?q?Philippe_M?=
	=?utf-8?q?athieu-Daud=C3=A9?= <philmd@redhat.com>
Subject: [PATCH v2 0/9] misc: Replace alloca() by g_malloc()
Date: Thu,  6 May 2021 15:37:49 +0200
Message-Id: <20210506133758.1749233-1-philmd@redhat.com>
X-Mailer: git-send-email 2.26.3
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ALLOCA(3) man-page mentions its "use is discouraged".
Replace few calls by equivalent GLib malloc().

Last call site is linux-user/.

Since v1:
- Converted more uses (alsaaudio, tpm, pca9552)
- Reworked gdbstub (Alex)
- Simplified PPC/KVM (Greg)

Philippe Mathieu-Daudé (9):
  audio/alsaaudio: Replace ALSA alloca() by malloc() equivalent
  backends/tpm: Replace qemu_mutex_lock calls with QEMU_LOCK_GUARD
  backends/tpm: Replace g_alloca() by g_malloc()
  bsd-user/syscall: Replace alloca() by g_new()
  gdbstub: Constify GdbCmdParseEntry
  gdbstub: Only call cmd_parse_params() with non-NULL command schema
  gdbstub: Replace alloca() + memset(0) by g_new0()
  hw/misc/pca9552: Replace g_newa() by g_new()
  target/ppc/kvm: Replace alloca() by g_malloc()

 audio/alsaaudio.c           | 11 +++++++----
 backends/tpm/tpm_emulator.c | 35 +++++++++++++++--------------------
 bsd-user/syscall.c          |  3 +--
 gdbstub.c                   | 34 +++++++++++++++-------------------
 hw/misc/pca9552.c           |  2 +-
 target/ppc/kvm.c            |  3 +--
 6 files changed, 40 insertions(+), 48 deletions(-)
```
#### [PATCH 0/2] KVM: SVM: Fix error handling bugs in SEV migration
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Thu May  6 17:58:24 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12242925
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5EBB1C433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 17:58:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2836561107
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 17:58:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236489AbhEFR7a (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 13:59:30 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:38200 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236455AbhEFR7a (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 May 2021 13:59:30 -0400
Received: from mail-qt1-x84a.google.com (mail-qt1-x84a.google.com
 [IPv6:2607:f8b0:4864:20::84a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id F10E6C061761
        for <kvm@vger.kernel.org>; Thu,  6 May 2021 10:58:31 -0700 (PDT)
Received: by mail-qt1-x84a.google.com with SMTP id
 o5-20020ac872c50000b02901c32e7e3c21so4082461qtp.8
        for <kvm@vger.kernel.org>; Thu, 06 May 2021 10:58:31 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=SUMsUAFzIemUpIBh2rroEWqtHg/B5XRDxbgXqiS7JYk=;
        b=OJ1k0E0Z3EM1Jd+PqZlqiUTHRz2VbvEyk6Ph32nc1oQ3BxdvTn5XfcAi7cXOr3sbTL
         bj5hLwc/CkfTcjm30F7Wf9VihsDtH86hu32xeB6qM/07sGUXbx0bsVxw7cll6pmlK9cv
         TTBGm++H8aMhgmnNCFvz+6JE/SRMUYMrya2QcKndzRlY40mp/U1GKxu9jgTYAwlS1Tkw
         1U2gkPnYH2IVUlYrD38OqdkOXxLtALL7jCwo2lt9k6L1qTxlDQvgwzsGxKMCcAAR7Dmo
         XH0sY17LEmePiS++VIktKhcohJJf8SBCZswQD3NKvi63MGsrEQt7ltfJjNYC3r1GekPU
         /jIw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=SUMsUAFzIemUpIBh2rroEWqtHg/B5XRDxbgXqiS7JYk=;
        b=Sw/hdlPWkpdEEcK3KglcdsRDpXtmSycGdIP8hknaknQsrCPC+MDM7ltK/cIY174K/+
         0+zxYW5i7buowQT2au6a/srFzeG3/+2wYsFu01KUQUiFVcc9F31wsPHp4bHpp9fj6Rx8
         v5dOJLn1JojcK4h06U/N1AUnFKY/fwVy1lqJmu3EY1Osf84TGSKca7G1a7H7oPnY45UD
         RUPBk6RZ9UXk0sih8uVRgSGVoV3BHL8k7zOGB3h0Q1NdZTvnuOmKrKH2biKUJZbBshsG
         TJJbtON3OuDejSzVdlc3yueF1x3cfIm/rvsaZVW2w11AHuj5oXXJkCY0Qejia+gCHaMr
         064w==
X-Gm-Message-State: AOAM530onGPjKuOtVWosvxxQugBCFcCBIQud7fKNly7LzTspVNB8tQTf
        p2Q1viEYO5N90nZ6G2OD+JA8p4oZ6o8=
X-Google-Smtp-Source: 
 ABdhPJx0cGg+sprFiauhsjPcfoixOwxTfbfmSMeTmduPX7FT15DTHEoDsTXgjDcfPTxqQJ7rr3Iu/+6OeBg=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:818d:5ca3:d49c:cfc8])
 (user=seanjc job=sendgmr) by 2002:a0c:c3cd:: with SMTP id
 p13mr5775763qvi.4.1620323911188;
 Thu, 06 May 2021 10:58:31 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Thu,  6 May 2021 10:58:24 -0700
Message-Id: <20210506175826.2166383-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH 0/2] KVM: SVM: Fix error handling bugs in SEV migration
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        Dan Carpenter <dan.carpenter@oracle.com>,
        Steve Rutherford <srutherford@google.com>,
        Brijesh Singh <brijesh.singh@amd.com>,
        Ashish Kalra <ashish.kalra@amd.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fixes for bugs reported by Dan Carpenter, found by static analysis.  All
credit goes to Dan, the bug report all but wrote the code for me.

Compile tested only, I don't have a SEV migration sussed out yet.

Sean Christopherson (2):
  KVM: SVM: Return -EFAULT if copy_to_user() for SEV mig packet header
    fails
  KVM: SVM: Fix sev_pin_memory() error checks in SEV migration utilities

 arch/x86/kvm/svm/sev.c | 14 ++++++++------
 1 file changed, 8 insertions(+), 6 deletions(-)
```
#### [PATCH v3 0/8] Lazily allocate memslot rmaps
##### From: Ben Gardon <bgardon@google.com>

```c
From patchwork Thu May  6 18:42:33 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ben Gardon <bgardon@google.com>
X-Patchwork-Id: 12242957
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id F06CFC433ED
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 18:42:49 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9A76B613C0
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 18:42:49 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234441AbhEFSnr (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 14:43:47 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47970 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S234241AbhEFSnp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 May 2021 14:43:45 -0400
Received: from mail-qt1-x849.google.com (mail-qt1-x849.google.com
 [IPv6:2607:f8b0:4864:20::849])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 05BDAC061574
        for <kvm@vger.kernel.org>; Thu,  6 May 2021 11:42:46 -0700 (PDT)
Received: by mail-qt1-x849.google.com with SMTP id
 69-20020aed304b0000b02901c6d87aed7fso4119670qte.21
        for <kvm@vger.kernel.org>; Thu, 06 May 2021 11:42:45 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=sOvqNeuGyU/ZMmaxdOA2l2pA74nfx+pU9gEcCSqkRJU=;
        b=uoosXHvihKGjquSMLz/CYZMZ4tR+g+wYMy+PQ0C6KeO5KYBM56Yk/c//Vb8khLCpLa
         YCHBvNfyl8fH5jv4BySXf883bxjZ+cUiwAKJ1zfGhX8PIIuFYLGMwj52jIzhvNJwbrdG
         ctX1VXEfR5WjkdhcV0c1eKg/C6Y6xKdg5LtFepfs9Lx49Y5kn3+C6LKUY85fNB9EBNUI
         tZejepMkiSxcVdz5z3kRvFkJ0MgkNm40VBAr7pwUVoWYY16zBkswnXhIKMmIsWItYJkX
         YakB7IEn+bKpzh6aLKFM1KSAejHXtfO3bkROa587oG0OexgaEENARbJzHsBf91VwKuP8
         sppg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=sOvqNeuGyU/ZMmaxdOA2l2pA74nfx+pU9gEcCSqkRJU=;
        b=rXcG3cFM27IiiZakOlDrgCOZIbNCv4nwrNAZduXma9Iy47i6LWvMTcXiLY6AGECgDf
         1KosnYMAg5YTfooodwctzhmcdCVvCT+AH/wZ5YFtLmt5cVmTXZFUL2i8HjBwU4pIzuNC
         +ob5RTWOCYxogqE8FYZ8k/3UhqwXnEn3R4PLCGnlMuKSBDfiBSoehwc6flVG7gDZ4HvV
         gP4qYbd3dutoQv7AD7Luoh9tx46fPCRsv7+Jsjc/Pj4IAESFQgiDs7cESKQgwk/iS9pq
         XWiPzLFuFkMb3f0JQbGwzvCh7fT9PnTD0tKWJHH84CpZHem2OOFkwo9Gve8PF6tpTTXN
         K5jg==
X-Gm-Message-State: AOAM5318BTIDr2dfKSDt2FH8hV9D95edP+kc2bCRS3Cm3ruvCoDj0AKT
        yAGfx/GsYNN/IFsLeFiuqtwbZOXq2gid
X-Google-Smtp-Source: 
 ABdhPJwtioxMRraHZDM3/mQxHN62IsmMxoyEHNLt1azp+GP7XBXuMx1lN08IjxpvyrsToOHNvTb9HUS7kNjB
X-Received: from bgardon.sea.corp.google.com
 ([2620:15c:100:202:9258:9474:54ca:4500])
 (user=bgardon job=sendgmr) by 2002:a05:6214:258d:: with SMTP id
 fq13mr6103004qvb.50.1620326565176; Thu, 06 May 2021 11:42:45 -0700 (PDT)
Date: Thu,  6 May 2021 11:42:33 -0700
Message-Id: <20210506184241.618958-1-bgardon@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.607.g51e8a6a459-goog
Subject: [PATCH v3 0/8] Lazily allocate memslot rmaps
From: Ben Gardon <bgardon@google.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>, Peter Xu <peterx@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Peter Shier <pshier@google.com>,
        Yulei Zhang <yulei.kernel@gmail.com>,
        Wanpeng Li <kernellwp@gmail.com>,
        Xiao Guangrong <xiaoguangrong.eric@gmail.com>,
        Kai Huang <kai.huang@intel.com>,
        Keqian Zhu <zhukeqian1@huawei.com>,
        Ben Gardon <bgardon@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enables KVM to save memory when using the TDP MMU by waiting
to allocate memslot rmaps until they are needed. To do this, KVM tracks
whether or not a shadow root has been allocated. In order to get away
with not allocating the rmaps, KVM must also be sure to skip operations
which iterate over the rmaps. If the TDP MMU is in use and we have not
allocated a shadow root, these operations would essentially be op-ops
anyway. Skipping the rmap operations has a secondary benefit of avoiding
acquiring the MMU lock in write mode in many cases, substantially
reducing MMU lock contention.

This series was tested on an Intel Skylake machine. With the TDP MMU off
and on, this introduced no new failures on kvm-unit-tests or KVM selftests.

Changelog:
v2:
	Incorporated feedback from Paolo and Sean
	Replaced the memslot_assignment_lock with slots_arch_lock, which
	has a larger critical section.

v3:
	Removed shadow_mmu_active as suggested by Sean
	Removed everything except adding a return value to
	kvm_mmu_init_tdp_mmu from patch 1 of v2
	Added RCU protection and better memory ordering for installing the
	memslot rmaps as suggested by Paolo
	Reordered most of the patches

Ben Gardon (8):
  KVM: x86/mmu: Deduplicate rmap freeing
  KVM: x86/mmu: Factor out allocating memslot rmap
  KVM: mmu: Refactor memslot copy
  KVM: mmu: Add slots_arch_lock for memslot arch fields
  KVM: x86/mmu: Add a field to control memslot rmap allocation
  KVM: x86/mmu: Skip rmap operations if rmaps not allocated
  KVM: x86/mmu: Protect rmaps independently with SRCU
  KVM: x86/mmu: Lazily allocate memslot rmaps

 arch/x86/include/asm/kvm_host.h |   9 ++
 arch/x86/kvm/mmu/mmu.c          | 195 ++++++++++++++++++++------------
 arch/x86/kvm/mmu/tdp_mmu.c      |   6 +-
 arch/x86/kvm/mmu/tdp_mmu.h      |   4 +-
 arch/x86/kvm/x86.c              | 107 ++++++++++++++----
 include/linux/kvm_host.h        |   9 ++
 virt/kvm/kvm_main.c             |  54 +++++++--
 7 files changed, 275 insertions(+), 109 deletions(-)
```
#### [patch 0/2] VMX: configure posted interrupt descriptor when assigning
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
From patchwork Thu May  6 18:57:32 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marcelo Tosatti <mtosatti@redhat.com>
X-Patchwork-Id: 12243393
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-6.4 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=no autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2A86CC433B4
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 19:07:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0B4BB613B5
	for <kvm@archiver.kernel.org>; Thu,  6 May 2021 19:07:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234729AbhEFTIb (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 6 May 2021 15:08:31 -0400
Received: from us-smtp-delivery-124.mimecast.com ([170.10.133.124]:26167 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S233217AbhEFTIa (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 May 2021 15:08:30 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1620328052;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=TgGRM+ReCWnEJOnYf4hSAh/OAMQkcq+MlZhUWMnz+ok=;
        b=NizREWK8xFYd5ygrQzfVZteWUE2Bjap2AV1Z6ITZRwpPiALfGuiKjva3Pr4hOorFZPZ89N
        xcquJusd3XoHR6drM9MuLD31BzWRUN1LKwJERC8eIb/FnocroDza1LpWAPbzNdBwINd6Ds
        f33fXpU9eJmqOobnNIp9XLFrfLJUI6Y=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-350-QN36qnc-NkSPXb8b6gKSag-1; Thu, 06 May 2021 15:07:28 -0400
X-MC-Unique: QN36qnc-NkSPXb8b6gKSag-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 872998014D8;
        Thu,  6 May 2021 19:07:27 +0000 (UTC)
Received: from fuller.cnet (ovpn-112-4.gru2.redhat.com [10.97.112.4])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id 922485D735;
        Thu,  6 May 2021 19:07:23 +0000 (UTC)
Received: by fuller.cnet (Postfix, from userid 1000)
        id E6EAA40E6DF4; Thu,  6 May 2021 16:07:03 -0300 (-03)
Message-ID: <20210506185732.609010123@redhat.com>
User-Agent: quilt/0.66
Date: Thu, 06 May 2021 15:57:32 -0300
From: Marcelo Tosatti <mtosatti@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Alex Williamson <alex.williamson@redhat.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [patch 0/2] VMX: configure posted interrupt descriptor when assigning
 device
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Configuration of the posted interrupt descriptor is incorrect when devices 
are hotplugged to the guest (and vcpus are halted).

See patch 2 for details.
```
