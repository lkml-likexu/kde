

#### [RFC PATCH 00/26] Runtime paravirt patching
##### From: Ankur Arora <ankur.a.arora@oracle.com>

```c
From patchwork Wed Apr  8 05:02:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ankur Arora <ankur.a.arora@oracle.com>
X-Patchwork-Id: 11479383
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EAD30112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 05:07:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B879E20857
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 05:07:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="dwADO76B"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726566AbgDHFF3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 01:05:29 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:38456 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725932AbgDHFF3 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 01:05:29 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 03853tXb191207;
        Wed, 8 Apr 2020 05:04:59 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=gEHA9nx+P2Ept/nnZJ17DEilIouWJcKCIoMOvLrgo7U=;
 b=dwADO76B6vyzwqtdoXeIlwaxqVZQMSnNBam+TctIiRToIoKUqiF9ff/rdW4nswrnoVXf
 LqtZc8ZIJwHi4WqQ1PtdUff0JHwT9kQYFrXeCqYTa1rT8hMAWktj0PlnQeX6fOYag+Vd
 pBe27mf8+o64sXWgrZAq8BnD3+13rAIDHPmp0MgUwnSNQsmWXbBv4i3lHAH1A3rg7HaO
 l6joM8aTubnbQd5fjWdUG1Wg0tBf58rERzrpIZmG7BWOWgmGRd4sTk/FUa1mGSZ4cdUh
 njagTvBUGP5DSwstjTEk6O80pHwZ2XAc1e9qsO9U8L5UoIYMhU87qlaORuwqdRFDatA/ Zw==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 3091m0s0r9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 08 Apr 2020 05:04:59 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 03851Xb2100769;
        Wed, 8 Apr 2020 05:04:58 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 3091m2hu00-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 08 Apr 2020 05:04:58 +0000
Received: from abhmp0012.oracle.com (abhmp0012.oracle.com [141.146.116.18])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 03854oaP015085;
        Wed, 8 Apr 2020 05:04:53 GMT
Received: from monad.ca.oracle.com (/10.156.75.81)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 07 Apr 2020 22:04:50 -0700
From: Ankur Arora <ankur.a.arora@oracle.com>
To: linux-kernel@vger.kernel.org, x86@kernel.org
Cc: peterz@infradead.org, hpa@zytor.com, jpoimboe@redhat.com,
        namit@vmware.com, mhiramat@kernel.org, jgross@suse.com,
        bp@alien8.de, vkuznets@redhat.com, pbonzini@redhat.com,
        boris.ostrovsky@oracle.com, mihai.carabas@oracle.com,
        kvm@vger.kernel.org, xen-devel@lists.xenproject.org,
        virtualization@lists.linux-foundation.org,
        Ankur Arora <ankur.a.arora@oracle.com>
Subject: [RFC PATCH 00/26] Runtime paravirt patching
Date: Tue,  7 Apr 2020 22:02:57 -0700
Message-Id: <20200408050323.4237-1-ankur.a.arora@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9584
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 bulkscore=0 mlxscore=0
 malwarescore=0 spamscore=0 adultscore=0 suspectscore=0 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2003020000
 definitions=main-2004080037
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9584
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxlogscore=999 mlxscore=0
 priorityscore=1501 phishscore=0 suspectscore=0 bulkscore=0
 lowpriorityscore=0 impostorscore=0 malwarescore=0 clxscore=1011
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2004080037
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A KVM host (or another hypervisor) might advertise paravirtualized
features and optimization hints (ex KVM_HINTS_REALTIME) which might
become stale over the lifetime of the guest. For instance, the
host might go from being undersubscribed to being oversubscribed
(or the other way round) and it would make sense for the guest
switch pv-ops based on that.

This lockorture splat that I saw on the guest while testing this is
indicative of the problem:

  [ 1136.461522] watchdog: BUG: soft lockup - CPU#8 stuck for 22s! [lock_torture_wr:12865]
  [ 1136.461542] CPU: 8 PID: 12865 Comm: lock_torture_wr Tainted: G W L 5.4.0-rc7+ #77
  [ 1136.461546] RIP: 0010:native_queued_spin_lock_slowpath+0x15/0x220

(Caused by an oversubscribed host but using mismatched native pv_lock_ops
on the gues.)

This series addresses the problem by doing paravirt switching at runtime.

We keep an interesting subset of pv-ops (pv_lock_ops only for now,
but PV-TLB ops are also good candidates) in .parainstructions.runtime,
while discarding the .parainstructions as usual at init. This is then
used for switching back and forth between native and paravirt mode.
([1] lists some representative numbers of the increased memory
footprint.)

Mechanism: the patching itself is done using stop_machine(). That is
not ideal -- text_poke_stop_machine() was replaced with INT3+emulation
via text_poke_bp(), but I'm using this to address two issues:
 1) emulation in text_poke() can only easily handle a small set
 of instructions and this is problematic for inlined pv-ops (and see
 a possible alternatives use-case below.)
 2) paravirt patching might have inter-dependendent ops (ex.
 lock.queued_lock_slowpath, lock.queued_lock_unlock are paired and
 need to be updated atomically.)

The alternative use-case is a runtime version of apply_alternatives()
(not posted with this patch-set) that can be used for some safe subset
of X86_FEATUREs. This could be useful in conjunction with the ongoing
late microcode loading work that Mihai Carabas and others have been
working on.

Also, there are points of similarity with the ongoing static_call work
which does rewriting of indirect calls. The difference here is that
we need to switch a group of calls atomically and given that
some of them can be inlined, need to handle a wider variety of opcodes.

To patch safely we need to satisfy these constraints:

 - No references to insn sequences under replacement on any kernel stack
   once replacement is in progress. Without this constraint we might end
   up returning to an address that is in the middle of an instruction.

 - handle inter-dependent ops: as above, lock.queued_lock_unlock(),
   lock.queued_lock_slowpath() and the rest of the pv_lock_ops are
   a good example.

 - handle a broader set of insns than CALL and JMP: some pv-ops end up
   getting inlined. Alternatives can contain arbitrary instructions.

 - locking operations can be called from interrupt handlers which means
   we cannot trivially use IPIs for flushing.

Handling these, necessitates that target pv-ops not be preemptible.
Once that is a given (for safety these need to be explicitly whitelisted
in runtime_patch()), use a state-machine with the primary CPU doing the
patching and secondary CPUs in a sync_core() loop. 

In case we hit an INT3/BP (in NMI or thread-context) we makes forward
progress by continuing the patching instead of emulating.

One remaining issue is inter-dependent pv-ops which are also executed in
the NMI handler -- patching can potentially deadlock in case of multiple
NMIs. Handle these by pushing some of this work in the NMI handler where
we know it will be uninterrupted.

There are four main sets of patches in this series:

 1. PV-ops management (patches 1-10, 20): mostly infrastructure and
 refactoring pieces to make paravirt patching usable at runtime. For the
 most part scoped under CONFIG_PARAVIRT_RUNTIME.

 Patches 1-7, to persist part of parainstructions in memory:
  "x86/paravirt: Specify subsection in PVOP macros"
  "x86/paravirt: Allow paravirt patching post-init"
  "x86/paravirt: PVRTOP macros for PARAVIRT_RUNTIME"
  "x86/alternatives: Refactor alternatives_smp_module*
  "x86/alternatives: Rename alternatives_smp*, smp_alt_module
  "x86/alternatives: Remove stale symbols
  "x86/paravirt: Persist .parainstructions.runtime"

 Patches 8-10, develop the inerfaces to safely switch pv-ops:
  "x86/paravirt: Stash native pv-ops"
  "x86/paravirt: Add runtime_patch()"
  "x86/paravirt: Add primitives to stage pv-ops"

 Patch 20 enables switching of pv_lock_ops:
  "x86/paravirt: Enable pv-spinlocks in runtime_patch()"

 2. Non-emulated text poking (patches 11-19)

 Patches 11-13 are mostly refactoring to split __text_poke() into map,
 unmap and poke/memcpy phases with the poke portion being re-entrant
  "x86/alternatives: Remove return value of text_poke*()"
  "x86/alternatives: Use __get_unlocked_pte() in text_poke()"
  "x86/alternatives: Split __text_poke()"

 Patches 15, 17 add the actual poking state-machine:
  "x86/alternatives: Non-emulated text poking"
  "x86/alternatives: Add patching logic in text_poke_site()"

 with patches 14 and 18 containing the pieces for BP handling:
  "x86/alternatives: Handle native insns in text_poke_loc*()"
  "x86/alternatives: Handle BP in non-emulated text poking"

 and patch 19 provides the ability to use the state-machine above in an
 NMI context (fixes some potential deadlocks when handling inter-
 dependent operations and multiple NMIs):
  "x86/alternatives: NMI safe runtime patching".

 Patch 16 provides the interface (paravirt_runtime_patch()) to use the
 poking mechanism developed above and patch 21 adds a selftest:
  "x86/alternatives: Add paravirt patching at runtime"
  "x86/alternatives: Paravirt runtime selftest"

 3. KVM guest changes to be able to use this (patches 22-23,25-26):
  "kvm/paravirt: Encapsulate KVM pv switching logic"
  "x86/kvm: Add worker to trigger runtime patching"
  "x86/kvm: Guest support for dynamic hints"
  "x86/kvm: Add hint change notifier for KVM_HINT_REALTIME".

 4. KVM host changes to notify the guest of a change (patch 24):
  "x86/kvm: Support dynamic CPUID hints"

Testing:
With paravirt patching, the code is mostly stable on Intel and AMD
systems under kernbench and locktorture with paravirt toggling (with,
without synthetic NMIs) in the background.

Queued spinlock performance for locktorture is also on expected lines:
 [ 1533.221563] Writes:  Total: 1048759000  Max/Min: 0/0   Fail: 0 
 # toggle PV spinlocks

 [ 1594.713699] Writes:  Total: 1111660545  Max/Min: 0/0   Fail: 0 
 # PV spinlocks (in ~60 seconds) = 62,901,545

 # toggle native spinlocks
 [ 1656.117175] Writes:  Total: 1113888840  Max/Min: 0/0   Fail: 0 
  # native spinlocks (in ~60 seconds) = 2,228,295

The alternatives testing is more limited with it being used to rewrite
mostly harmless X86_FEATUREs with load in the background.

Patches also at:

ssh://git@github.com/terminus/linux.git alternatives-rfc-upstream-v1

Please review.

Thanks
Ankur

[1] The precise change in memory footprint depends on config options
but the following example inlines queued_spin_unlock() (which forms
the bulk of the added state). The added footprint is the size of the
.parainstructions.runtime section:

 $ objdump -h vmlinux|grep .parainstructions
 Idx Name              		Size      VMA               
 	LMA                File-off  Algn
  27 .parainstructions 		0001013c  ffffffff82895000
  	0000000002895000   01c95000  2**3
  28 .parainstructions.runtime  0000cd2c  ffffffff828a5140
  	00000000028a5140   01ca5140  2**3

  $ size vmlinux                                         
  text       data       bss        dec      hex       filename
  13726196   12302814   14094336   40123346 2643bd2   vmlinux

Ankur Arora (26):
  x86/paravirt: Specify subsection in PVOP macros
  x86/paravirt: Allow paravirt patching post-init
  x86/paravirt: PVRTOP macros for PARAVIRT_RUNTIME
  x86/alternatives: Refactor alternatives_smp_module*
  x86/alternatives: Rename alternatives_smp*, smp_alt_module
  x86/alternatives: Remove stale symbols
  x86/paravirt: Persist .parainstructions.runtime
  x86/paravirt: Stash native pv-ops
  x86/paravirt: Add runtime_patch()
  x86/paravirt: Add primitives to stage pv-ops
  x86/alternatives: Remove return value of text_poke*()
  x86/alternatives: Use __get_unlocked_pte() in text_poke()
  x86/alternatives: Split __text_poke()
  x86/alternatives: Handle native insns in text_poke_loc*()
  x86/alternatives: Non-emulated text poking
  x86/alternatives: Add paravirt patching at runtime
  x86/alternatives: Add patching logic in text_poke_site()
  x86/alternatives: Handle BP in non-emulated text poking
  x86/alternatives: NMI safe runtime patching
  x86/paravirt: Enable pv-spinlocks in runtime_patch()
  x86/alternatives: Paravirt runtime selftest
  kvm/paravirt: Encapsulate KVM pv switching logic
  x86/kvm: Add worker to trigger runtime patching
  x86/kvm: Support dynamic CPUID hints
  x86/kvm: Guest support for dynamic hints
  x86/kvm: Add hint change notifier for KVM_HINT_REALTIME

 Documentation/virt/kvm/api.rst        |  17 +
 Documentation/virt/kvm/cpuid.rst      |   9 +-
 arch/x86/Kconfig                      |  14 +
 arch/x86/Kconfig.debug                |  13 +
 arch/x86/entry/entry_64.S             |   5 +
 arch/x86/include/asm/alternative.h    |  20 +-
 arch/x86/include/asm/kvm_host.h       |   6 +
 arch/x86/include/asm/kvm_para.h       |  17 +
 arch/x86/include/asm/paravirt.h       |  10 +-
 arch/x86/include/asm/paravirt_types.h | 230 ++++--
 arch/x86/include/asm/text-patching.h  |  18 +-
 arch/x86/include/uapi/asm/kvm_para.h  |   2 +
 arch/x86/kernel/Makefile              |   1 +
 arch/x86/kernel/alternative.c         | 987 +++++++++++++++++++++++---
 arch/x86/kernel/kvm.c                 | 191 ++++-
 arch/x86/kernel/module.c              |  42 +-
 arch/x86/kernel/paravirt.c            |  16 +-
 arch/x86/kernel/paravirt_patch.c      |  61 ++
 arch/x86/kernel/pv_selftest.c         | 264 +++++++
 arch/x86/kernel/pv_selftest.h         |  15 +
 arch/x86/kernel/setup.c               |   2 +
 arch/x86/kernel/vmlinux.lds.S         |  16 +
 arch/x86/kvm/cpuid.c                  |   3 +-
 arch/x86/kvm/x86.c                    |  39 +
 include/asm-generic/kvm_para.h        |  12 +
 include/asm-generic/vmlinux.lds.h     |   8 +
 include/linux/kvm_para.h              |   5 +
 include/linux/mm.h                    |  16 +-
 include/linux/preempt.h               |  17 +
 include/uapi/linux/kvm.h              |   4 +
 kernel/locking/lock_events.c          |   2 +-
 mm/memory.c                           |   9 +-
 32 files changed, 1850 insertions(+), 221 deletions(-)
 create mode 100644 arch/x86/kernel/pv_selftest.c
 create mode 100644 arch/x86/kernel/pv_selftest.h
```
#### [PATCH v3 0/2] VFIO mdev aggregated resources handling
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
From patchwork Wed Apr  8 05:58:22 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenyu Wang <zhenyuw@linux.intel.com>
X-Patchwork-Id: 11479443
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 56A42912
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 05:58:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3EF2B206C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 05:58:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726192AbgDHF62 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 01:58:28 -0400
Received: from mga03.intel.com ([134.134.136.65]:43466 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725932AbgDHF62 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 01:58:28 -0400
IronPort-SDR: 
 2CZw4EnYlo8jjYUV+9egdg4/blRgqok1AhajKRasFk/zwa65g31hFb/sDPLCtp/C5tzZbnGXi+
 HGFWV0vJzoXA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by orsmga103.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Apr 2020 22:58:27 -0700
IronPort-SDR: 
 W7jDh2gunSXO6Z7vei5H3mV7KGwC6eZD3DZFw2MetsdfFxWq6BTdBz6ZuemTbESVBXbSb0bk3v
 JCpbuNwmSYFA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,357,1580803200";
   d="scan'208";a="286448324"
Received: from jianli5-mobl2.ccr.corp.intel.com (HELO
 dell-xps.ccr.corp.intel.com) ([10.249.173.130])
  by fmsmga002.fm.intel.com with ESMTP; 07 Apr 2020 22:58:25 -0700
From: Zhenyu Wang <zhenyuw@linux.intel.com>
To: alex.williamson@redhat.com
Cc: kevin.tian@intel.com, intel-gvt-dev@lists.freedesktop.org,
        kvm@vger.kernel.org
Subject: [PATCH v3 0/2] VFIO mdev aggregated resources handling
Date: Wed,  8 Apr 2020 13:58:22 +0800
Message-Id: <20200408055824.2378-1-zhenyuw@linux.intel.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200326054136.2543-1-zhenyuw@linux.intel.com>
References: <20200326054136.2543-1-zhenyuw@linux.intel.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi,

This is a refresh on previous series: https://patchwork.kernel.org/cover/11208279/
and https://patchwork.freedesktop.org/series/70425/

Current mdev device create interface depends on fixed mdev type, which
get uuid from user to create instance of mdev device. If user wants to
use customized number of resource for mdev device, then only can
create new mdev type for that which may not be flexible. This
requirement comes not only from to be able to allocate flexible
resources for KVMGT, but also from Intel scalable IO virtualization
which would use vfio/mdev to be able to allocate arbitrary resources
on mdev instance. More info on [1] [2] [3].

As we agreed that for current opaque mdev device type, we'd still
explore management interface based on mdev sysfs definition. And this
one tries to follow Alex's previous suggestion to create generic
parameters under 'mdev' directory for each device, so vendor driver
could provide support like as other defined mdev sysfs entries.

For mdev type with aggregation support, files as "aggregated_instances"
and "max_aggregation" should be created under 'mdev' directory. E.g

/sys/devices/pci0000:00/0000:00:02.0/<UUID>/mdev/
   |-- aggregated_instances
   |-- max_aggregation

"aggregated_instances" is used to set or return current number of
instances for aggregation, which can not be larger than "max_aggregation".

The first patch is to update the document for new mdev parameter directory.
The second one is to add aggregation support in GVT driver.

References:
[1] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[2] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[3] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf

Changelog:
v3:
- add more description for sysfs entries
- rebase GVT support
- rename accounting function

Zhenyu Wang (2):
  Documentation/driver-api/vfio-mediated-device.rst: update for
    aggregation support
  drm/i915/gvt: mdev aggregation type

 .../driver-api/vfio-mediated-device.rst       |  22 +++
 drivers/gpu/drm/i915/gvt/aperture_gm.c        |  44 +++--
 drivers/gpu/drm/i915/gvt/gtt.c                |   9 +-
 drivers/gpu/drm/i915/gvt/gvt.c                |   7 +-
 drivers/gpu/drm/i915/gvt/gvt.h                |  42 +++--
 drivers/gpu/drm/i915/gvt/kvmgt.c              | 115 +++++++++++-
 drivers/gpu/drm/i915/gvt/vgpu.c               | 172 ++++++++++++------
 7 files changed, 317 insertions(+), 94 deletions(-)
```
#### [PATCH 0/2] KVM: Fix out-of-bounds memslot access
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Wed Apr  8 06:40:57 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11479457
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 168541392
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 06:41:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F3AEF2072A
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 06:41:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726620AbgDHGlB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 02:41:01 -0400
Received: from mga11.intel.com ([192.55.52.93]:58629 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726584AbgDHGlB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 02:41:01 -0400
IronPort-SDR: 
 O0vphgqvcSfvdwK8eA1NKUhh2SPd3BTkw2PHjiuFhA70O3PEFQ4GGtuV0DKFux5c9qjJAxcTDP
 96ol0kHH5MNw==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga007.jf.intel.com ([10.7.209.58])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Apr 2020 23:41:00 -0700
IronPort-SDR: 
 1usDcTI6wc8x5ZLUrsON3Wq0Th2N0cJsPE7Kky6Uud5b/JMvzdo9mo6V0nW2s1XVIEzRDCpwrt
 rgIPR+666OdA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.72,357,1580803200";
   d="scan'208";a="240207985"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga007.jf.intel.com with ESMTP; 07 Apr 2020 23:40:59 -0700
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Cc: David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org,
        syzbot+d889b59b2bb87d4047a2@syzkaller.appspotmail.com
Subject: [PATCH 0/2] KVM: Fix out-of-bounds memslot access
Date: Tue,  7 Apr 2020 23:40:57 -0700
Message-Id: <20200408064059.8957-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Two fixes for what are effectively the same bug.  The binary search used
for memslot lookup doesn't check the resolved index and can access memory
beyond the end of the memslot array.

I split the s390 specific change to a separate patch because it's subtly
different, and to simplify backporting.  The KVM wide fix can be applied
to stable trees as is, but AFAICT the s390 change would need to be paired
with the !used_slots check from commit 774a964ef56 ("KVM: Fix out of range
accesses to memslots").  This is why I tagged only the KVM wide patch for
stable.

Sean Christopherson (2):
  KVM: Check validity of resolved slot when searching memslots
  KVM: s390: Return last valid slot if approx index is out-of-bounds

 arch/s390/kvm/kvm-s390.c | 3 +++
 include/linux/kvm_host.h | 2 +-
 2 files changed, 4 insertions(+), 1 deletion(-)
```
#### [PATCH 00/35] Documentation fixes for Kernel 5.8
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
From patchwork Wed Apr  8 15:45:52 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11480439
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 46F69112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 15:48:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2015C2076D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 15:48:24 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1586360904;
	bh=NGLDDtyN8RZKYu/2cTSKBLZPkCz8Mr0c9YVBRHz1zys=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=fHvOzht8r19oshBwI3KxC3AdskGiLIejjnMvkaQkLb8/fKE5fo/XfYttUpNSQ8olk
	 mUSc2HMIaxAN5uIZkDZIr/hdOFfhYb6W5r0CajaQb8+uY39AkST4UC6UCLWmbTwnTV
	 3Vj+v8yDQ4xHyttQUnyL7y4ltp0Q4D9mOcF5dh+o=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729932AbgDHPr6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 11:47:58 -0400
Received: from mail.kernel.org ([198.145.29.99]:48894 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729567AbgDHPqd (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Apr 2020 11:46:33 -0400
Received: from mail.kernel.org (ip5f5ad4d8.dynamic.kabel-deutschland.de
 [95.90.212.216])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id E436F20769;
        Wed,  8 Apr 2020 15:46:30 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1586360791;
        bh=NGLDDtyN8RZKYu/2cTSKBLZPkCz8Mr0c9YVBRHz1zys=;
        h=From:To:Cc:Subject:Date:From;
        b=I3LVCc26/VdF24AsOrt+PHJ6A8shQrFjca47izBLXO8vl1fetOmpTsay+HfFnjRDn
         ELpq2el4OVbLL0QQpHim4bJ4r72BlEiJ9tHPbEFlZ/E6g9CVUSW9fzJZn0GNpSqQLs
         eoPTB+ArHDBqNWFtK9BnG7DerSf9cD29j4b39qq4=
Received: from mchehab by mail.kernel.org with local (Exim 4.92.3)
        (envelope-from <mchehab@kernel.org>)
        id 1jMCuK-000cAH-Vl; Wed, 08 Apr 2020 17:46:28 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        linux-kernel@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        Rob Herring <robh@kernel.org>,
        Maxime Ripard <maxime@cerno.tech>,
        Yuti Amonkar <yamonkar@cadence.com>,
        Kishon Vijay Abraham I <kishon@ti.com>,
        devicetree@vger.kernel.org, linux-arch@vger.kernel.org,
        kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
        linuxppc-dev@lists.ozlabs.org, dri-devel@lists.freedesktop.org,
        linux-arm-kernel@lists.infradead.org,
        linux-fsdevel@vger.kernel.org, linux-unionfs@vger.kernel.org,
        linux-mm@kvack.org, linux-rdma@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, linux-crypto@vger.kernel.org,
        linux-media@vger.kernel.org, linux-arm-msm@vger.kernel.org,
        freedreno@lists.freedesktop.org, linux-afs@lists.infradead.org,
        ecryptfs@vger.kernel.org, linux-ntfs-dev@lists.sourceforge.net,
        ocfs2-devel@oss.oracle.com, linux-pci@vger.kernel.org,
        linux1394-devel@lists.sourceforge.net, linux-ide@vger.kernel.org,
        linux-edac@vger.kernel.org, linux-spi@vger.kernel.org,
        MPT-FusionLinux.pdl@broadcom.com, linux-scsi@vger.kernel.org,
        Stephen Boyd <swboyd@chromium.org>,
        Sandeep Maheswaram <sanm@codeaurora.org>,
        Matthias Kaehlcke <mka@chromium.org>,
        linux-usb@vger.kernel.org,
        Linus Walleij <linus.walleij@linaro.org>,
        Sudeep Holla <sudeep.holla@arm.com>,
        Geert Uytterhoeven <geert+renesas@glider.be>,
        Matthias Brugger <mbrugger@suse.com>, netdev@vger.kernel.org,
        linux-i2c@vger.kernel.org
Subject: [PATCH 00/35] Documentation fixes for Kernel 5.8
Date: Wed,  8 Apr 2020 17:45:52 +0200
Message-Id: <cover.1586359676.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.25.2
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Jon,

I have a large list of patches this time for the Documentation/. So, I'm
starting sending them a little earier. Yet, those are meant to be applied
after the end of the merge window. They're based on today's linux-next,
with has only 49 patches pending to be applied upstream touching
Documentation/, so I don't expect much conflicts if applied early at
-rc cycle.

Most of the patches here were already submitted, but weren't
merged yet at next. So, it seems that nobody picked them yet.

In any case, most of those patches here are independent from 
the others.

The number of doc build warnings have been rising with time.
The main goal with this series is to get rid of most Sphinx warnings
and other errors.

Patches 1 to 5: fix broken references detected by this tool:

        ./scripts/documentation-file-ref-check

The other patches fix other random errors due to tags being
mis-interpreted or mis-used.

You should notice that several patches touch kernel-doc scripts.
IMHO, some of the warnings are actually due to kernel-doc being
too pedantic. So, I ended by improving some things at the toolset,
in order to make it smarter. That's the case of those patches:

	docs: scripts/kernel-doc: accept blank lines on parameter description
	scripts: kernel-doc: accept negation like !@var
	scripts: kernel-doc: proper handle @foo->bar()

The last 4 patches address problems with PDF building.

The first one address a conflict that will rise during the merge
window: Documentation/media will be removed. Instead of
just drop it from the list of PDF documents, I opted to drop the
entire list, as conf.py will auto-generate from the sources:

	docs: LaTeX/PDF: drop list of documents

Also, right now, PDF output is broken due to a namespace conflict 
at I2c (two pdf outputs there will have the same name).

	docs: i2c: rename i2c.svg to i2c_bus.svg

The third PDF patch is not really a fix, but it helps a lot to identify
if the build succeeded or not, by placing the final PDF output on
a separate dir:

	docs: Makefile: place final pdf docs on a separate dir

Finally, the last one solves a bug since the first supported Sphinx
version, with also impacts PDF output: basically while nested tables
are valid with ReST notation, the toolset only started supporting
it on PDF output since version 2.4:

	docs: update recommended Sphinx version to 2.4.4

PS.: Due to the large number of C/C, I opted to keep a smaller
set of C/C at this first e-mail (only e-mails with "L:" tag from
MAINTAINERS file).

Mauro Carvalho Chehab (35):
  MAINTAINERS: dt: update display/allwinner file entry
  docs: dt: fix broken reference to phy-cadence-torrent.yaml
  docs: fix broken references to text files
  docs: fix broken references for ReST files that moved around
  docs: filesystems: fix renamed references
  docs: amu: supress some Sphinx warnings
  docs: arm64: booting.rst: get rid of some warnings
  docs: pci: boot-interrupts.rst: improve html output
  futex: get rid of a kernel-docs build warning
  firewire: firewire-cdev.hL get rid of a docs warning
  scripts: kernel-doc: proper handle @foo->bar()
  lib: bitmap.c: get rid of some doc warnings
  ata: libata-core: fix a doc warning
  fs: inode.c: get rid of docs warnings
  docs: ras: get rid of some warnings
  docs: ras: don't need to repeat twice the same thing
  docs: watch_queue.rst: supress some Sphinx warnings
  scripts: kernel-doc: accept negation like !@var
  docs: infiniband: verbs.c: fix some documentation warnings
  docs: scripts/kernel-doc: accept blank lines on parameter description
  docs: spi: spi.h: fix a doc building warning
  docs: drivers: fix some warnings at base/platform.c when building docs
  docs: fusion: mptbase.c: get rid of a doc build warning
  docs: mm: slab.h: fix a broken cross-reference
  docs mm: userfaultfd.rst: use ``foo`` for literals
  docs: mm: userfaultfd.rst: use a cross-reference for a section
  docs: vm: index.rst: add an orphan doc to the building system
  docs: dt: qcom,dwc3.txt: fix cross-reference for a converted file
  MAINTAINERS: dt: fix pointers for ARM Integrator, Versatile and
    RealView
  docs: dt: fix a broken reference for a file converted to json
  powerpc: docs: cxl.rst: mark two section titles as such
  docs: LaTeX/PDF: drop list of documents
  docs: i2c: rename i2c.svg to i2c_bus.svg
  docs: Makefile: place final pdf docs on a separate dir
  docs: update recommended Sphinx version to 2.4.4

 Documentation/ABI/stable/sysfs-devices-node   |   2 +-
 Documentation/ABI/testing/procfs-smaps_rollup |   2 +-
 Documentation/Makefile                        |   6 +-
 Documentation/PCI/boot-interrupts.rst         |  34 +--
 Documentation/admin-guide/cpu-load.rst        |   2 +-
 Documentation/admin-guide/mm/userfaultfd.rst  | 209 +++++++++---------
 Documentation/admin-guide/nfs/nfsroot.rst     |   2 +-
 Documentation/admin-guide/ras.rst             |  18 +-
 Documentation/arm64/amu.rst                   |   5 +
 Documentation/arm64/booting.rst               |  36 +--
 Documentation/conf.py                         |  38 ----
 .../bindings/net/qualcomm-bluetooth.txt       |   2 +-
 .../bindings/phy/ti,phy-j721e-wiz.yaml        |   2 +-
 .../devicetree/bindings/usb/qcom,dwc3.txt     |   4 +-
 .../doc-guide/maintainer-profile.rst          |   2 +-
 .../driver-api/driver-model/device.rst        |   4 +-
 .../driver-api/driver-model/overview.rst      |   2 +-
 Documentation/filesystems/dax.txt             |   2 +-
 Documentation/filesystems/dnotify.txt         |   2 +-
 .../filesystems/ramfs-rootfs-initramfs.rst    |   2 +-
 Documentation/filesystems/sysfs.rst           |   2 +-
 Documentation/i2c/{i2c.svg => i2c_bus.svg}    |   2 +-
 Documentation/i2c/summary.rst                 |   2 +-
 Documentation/memory-barriers.txt             |   2 +-
 Documentation/powerpc/cxl.rst                 |   2 +
 .../powerpc/firmware-assisted-dump.rst        |   2 +-
 Documentation/process/adding-syscalls.rst     |   2 +-
 Documentation/process/submit-checklist.rst    |   2 +-
 Documentation/sphinx/requirements.txt         |   2 +-
 .../it_IT/process/adding-syscalls.rst         |   2 +-
 .../it_IT/process/submit-checklist.rst        |   2 +-
 .../translations/ko_KR/memory-barriers.txt    |   2 +-
 .../translations/zh_CN/filesystems/sysfs.txt  |   8 +-
 .../zh_CN/process/submit-checklist.rst        |   2 +-
 Documentation/virt/kvm/arm/pvtime.rst         |   2 +-
 Documentation/virt/kvm/devices/vcpu.rst       |   2 +-
 Documentation/virt/kvm/hypercalls.rst         |   4 +-
 Documentation/virt/kvm/mmu.rst                |   2 +-
 Documentation/virt/kvm/review-checklist.rst   |   2 +-
 Documentation/vm/index.rst                    |   1 +
 Documentation/watch_queue.rst                 |  34 ++-
 MAINTAINERS                                   |   7 +-
 arch/powerpc/include/uapi/asm/kvm_para.h      |   2 +-
 arch/x86/kvm/mmu/mmu.c                        |   2 +-
 drivers/ata/libata-core.c                     |   2 +-
 drivers/base/core.c                           |   2 +-
 drivers/base/platform.c                       |   6 +-
 .../allwinner/sun8i-ce/sun8i-ce-cipher.c      |   2 +-
 .../crypto/allwinner/sun8i-ce/sun8i-ce-core.c |   2 +-
 .../allwinner/sun8i-ss/sun8i-ss-cipher.c      |   2 +-
 .../crypto/allwinner/sun8i-ss/sun8i-ss-core.c |   2 +-
 drivers/gpu/drm/Kconfig                       |   2 +-
 drivers/gpu/drm/drm_ioctl.c                   |   2 +-
 drivers/gpu/drm/msm/disp/dpu1/dpu_kms.h       |   2 +-
 drivers/hwtracing/coresight/Kconfig           |   2 +-
 drivers/infiniband/core/verbs.c               |   7 +-
 drivers/media/v4l2-core/v4l2-fwnode.c         |   2 +-
 drivers/message/fusion/mptbase.c              |   8 +-
 fs/Kconfig                                    |   2 +-
 fs/Kconfig.binfmt                             |   2 +-
 fs/adfs/Kconfig                               |   2 +-
 fs/affs/Kconfig                               |   2 +-
 fs/afs/Kconfig                                |   6 +-
 fs/bfs/Kconfig                                |   2 +-
 fs/cramfs/Kconfig                             |   2 +-
 fs/ecryptfs/Kconfig                           |   2 +-
 fs/fat/Kconfig                                |   8 +-
 fs/fuse/Kconfig                               |   2 +-
 fs/fuse/dev.c                                 |   2 +-
 fs/hfs/Kconfig                                |   2 +-
 fs/hpfs/Kconfig                               |   2 +-
 fs/inode.c                                    |   6 +-
 fs/isofs/Kconfig                              |   2 +-
 fs/namespace.c                                |   2 +-
 fs/notify/inotify/Kconfig                     |   2 +-
 fs/ntfs/Kconfig                               |   2 +-
 fs/ocfs2/Kconfig                              |   2 +-
 fs/overlayfs/Kconfig                          |   6 +-
 fs/proc/Kconfig                               |   4 +-
 fs/romfs/Kconfig                              |   2 +-
 fs/sysfs/dir.c                                |   2 +-
 fs/sysfs/file.c                               |   2 +-
 fs/sysfs/mount.c                              |   2 +-
 fs/sysfs/symlink.c                            |   2 +-
 fs/sysv/Kconfig                               |   2 +-
 fs/udf/Kconfig                                |   2 +-
 include/linux/kobject.h                       |   2 +-
 include/linux/kobject_ns.h                    |   2 +-
 include/linux/mm.h                            |   4 +-
 include/linux/relay.h                         |   2 +-
 include/linux/slab.h                          |   2 +-
 include/linux/spi/spi.h                       |   1 +
 include/linux/sysfs.h                         |   2 +-
 include/uapi/linux/ethtool_netlink.h          |   2 +-
 include/uapi/linux/firewire-cdev.h            |   2 +-
 include/uapi/linux/kvm.h                      |   4 +-
 include/uapi/rdma/rdma_user_ioctl_cmds.h      |   2 +-
 kernel/futex.c                                |   3 +
 kernel/relay.c                                |   2 +-
 lib/bitmap.c                                  |  27 +--
 lib/kobject.c                                 |   4 +-
 mm/gup.c                                      |  12 +-
 scripts/kernel-doc                            |  41 ++--
 tools/include/uapi/linux/kvm.h                |   4 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c              |   2 +-
 virt/kvm/arm/vgic/vgic.h                      |   4 +-
 106 files changed, 373 insertions(+), 338 deletions(-)
 rename Documentation/i2c/{i2c.svg => i2c_bus.svg} (99%)
```
#### [PATCH v4 0/2] selftests: kvm: Introduce the mem_slot_test test
##### From: Wainer dos Santos Moschetta <wainersm@redhat.com>

```c
From patchwork Wed Apr  8 22:08:16 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wainer dos Santos Moschetta <wainersm@redhat.com>
X-Patchwork-Id: 11481015
Return-Path: <SRS0=FdSL=5Y=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A973492C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 22:08:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 819AB2082D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Apr 2020 22:08:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="M7RCowO6"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726508AbgDHWId (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Apr 2020 18:08:33 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:48020 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726483AbgDHWId (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 8 Apr 2020 18:08:33 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1586383711;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=+07ZF0vhV+iDgSNtpgYgvjiDt2fwmsqUI3y1zso6lMk=;
        b=M7RCowO640PAUAZOwEyt7EN2lQXhgPazDNP0Ly2Qd714oJSzIyZIfgy2aYbr2akYABjZrC
        YwdLRhLuVLy2+jJmWZTDwayZmUfXeaMgK38147A5keOeX/rNZCdqNuLgdiQXt23cymsKex
        XDXNhC/DfcZBMa4/42TkLxpGYkwZZbI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-472-fWbpv2IoNLOtV8qPfljB5g-1; Wed, 08 Apr 2020 18:08:27 -0400
X-MC-Unique: fWbpv2IoNLOtV8qPfljB5g-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 893811007280;
        Wed,  8 Apr 2020 22:08:26 +0000 (UTC)
Received: from localhost.localdomain (ovpn-116-15.gru2.redhat.com
 [10.97.116.15])
        by smtp.corp.redhat.com (Postfix) with ESMTP id F0666118F4A;
        Wed,  8 Apr 2020 22:08:20 +0000 (UTC)
From: Wainer dos Santos Moschetta <wainersm@redhat.com>
To: pbonzini@redhat.com, kvm@vger.kernel.org
Cc: drjones@redhat.com, david@redhat.com, linux-kernel@vger.kernel.org,
        linux-kselftest@vger.kernel.org
Subject: [PATCH v4 0/2] selftests: kvm: Introduce the mem_slot_test test
Date: Wed,  8 Apr 2020 19:08:16 -0300
Message-Id: <20200408220818.4306-1-wainersm@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series introduces a new KVM selftest (mem_slot_test) that goal
is to verify memory slots can be added up to the maximum allowed. An
extra slot is attempted which should occur on error.

The patch 01 is needed so that the VM fd can be accessed from the
test code (for the ioctl call attempting to add an extra slot).

I ran the test successfully on x86_64, aarch64, and s390x.  This
is why it is enabled to build on those arches.

- Changelog -

v3 -> v4:
 - Discarded mem_reg_flags variable. Simply using 0 instead [drjones]
 - Discarded kvm_region pointer. Instead passing a compound literal in
   the ioctl [drjones]
 - All variables are declared on the declaration block [drjones]

v2 -> v3:
 - Keep alphabetical order of .gitignore and Makefile [drjones]
 - Use memory region flags equals to zero [drjones]
 - Changed mmap() assert from 'mem != NULL' to 'mem != MAP_FAILED' [drjones]
 - kvm_region is declared along side other variables and malloc()'ed
   later [drjones]
 - Combined two asserts into a single 'ret == -1 && errno == EINVAL'
   [drjones]

v1 -> v2:
 - Rebased to queue
 - vm_get_fd() returns int instead of unsigned int (patch 01) [drjones]
 - Removed MEM_REG_FLAGS and GUEST_VM_MODE defines [drjones]
 - Replaced DEBUG() with pr_info() [drjones]
 - Calculate number of guest pages with vm_calc_num_guest_pages()
   [drjones]
 - Using memory region of 1 MB sized (matches mininum needed
   for s390x)
 - Removed the increment of guest_addr after the loop [drjones]
 - Added assert for the errno when adding a slot beyond-the-limit [drjones]
 - Prefer KVM_MEM_READONLY flag but on s390x it switch to KVM_MEM_LOG_DIRTY_PAGES,
   so ensure the coverage of both flags. Also somewhat tests the KVM_CAP_READONLY_MEM capability check [drjones]
 - Moved the test logic to test_add_max_slots(), this allows to more easily add new cases in the "suite".

v1: https://lore.kernel.org/kvm/20200330204310.21736-1-wainersm@redhat.com

Wainer dos Santos Moschetta (2):
  selftests: kvm: Add vm_get_fd() in kvm_util
  selftests: kvm: Add mem_slot_test test

 tools/testing/selftests/kvm/.gitignore        |  1 +
 tools/testing/selftests/kvm/Makefile          |  3 +
 .../testing/selftests/kvm/include/kvm_util.h  |  1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  5 ++
 tools/testing/selftests/kvm/mem_slot_test.c   | 76 +++++++++++++++++++
 5 files changed, 86 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/mem_slot_test.c
```
