

#### [PATCH 00/15] KVM: Add Xen hypercall and shared info pages
##### From: David Woodhouse <dwmw2@infradead.org>

```c
From patchwork Fri Dec  4 01:18:33 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11950331
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EACF4C193FE
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 01:20:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9E05C224D1
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 01:20:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388396AbgLDBUO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 20:20:14 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56472 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2388385AbgLDBUN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Dec 2020 20:20:13 -0500
Received: from casper.infradead.org (casper.infradead.org
 [IPv6:2001:8b0:10b:1236::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 60802C08E860
        for <kvm@vger.kernel.org>; Thu,  3 Dec 2020 17:18:56 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=casper.20170209;
 h=Sender:Content-Transfer-Encoding:
        Content-Type:MIME-Version:Message-Id:Date:Subject:Cc:To:From:Reply-To:
        Content-ID:Content-Description:In-Reply-To:References;
        bh=5/ALs+wec0ATyor0qyB+ptL8rnFvrdLxgaVqB/c//Ts=;
 b=pLlRSn7dVAbUIKxLAgtAS/gZII
        8p/OqVEbwlRWZEgJy8zgLBWM5nvNS4iFvNYr6fHF3/jO/5fMnMXCnV2io2TDIG+s7s+2TvKmNYYGp
        WgMl5d8NDGc4TuCaE8JGleWKePJJrqf0xCDINmuVCNrP9ZAWc8MB/PR+rWwZehkBDlIs8Qzf1JpnC
        7IQrpTlyd5jozg/+FsvZr723o3teaVwhe57oDAqKQyueNP3w9IwA4TzftbRxg9pZU9VcDlwvnutKt
        jJ8Ln+/fVRYN6pAfk3euzoU9K6XwUMGaLnK+Lcrf07tIppWjCLSK+rnnoGZVbceA7fzC56WfkUXnK
        r1kzqn/A==;
Received: from i7.infradead.org ([2001:8b0:10b:1:21e:67ff:fecb:7a92])
        by casper.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kkzkK-0004KY-Jj; Fri, 04 Dec 2020 01:18:53 +0000
Received: from dwoodhou by i7.infradead.org with local (Exim 4.94 #2 (Red Hat
 Linux))
        id 1kkzkK-00CS9i-67; Fri, 04 Dec 2020 01:18:52 +0000
From: David Woodhouse <dwmw2@infradead.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ankur Arora <ankur.a.arora@oracle.com>,
        Joao Martins <joao.m.martins@oracle.com>,
        Boris Ostrovsky <boris.ostrovsky@oracle.com>,
        Sean Christopherson <seanjc@google.com>
Subject: [PATCH 00/15] KVM: Add Xen hypercall and shared info pages
Date: Fri,  4 Dec 2020 01:18:33 +0000
Message-Id: <20201204011848.2967588-1-dwmw2@infradead.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
Sender: David Woodhouse <dwmw2@infradead.org>
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 casper.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reviving the first section (so far) of a patch set that Joao posted as 
RFC last year:

https://lore.kernel.org/kvm/20190220201609.28290-1-joao.m.martins@oracle.com/

This adds basic hypercall interception support, and adds support for
timekeeping and runstate-related shared info regions.

I've updated and reworked the original a bit, including:
 • Support for 32-bit guests
 • 64-bit second support in wallclock
 • Time counters for runnable/blocked states in runstate support
 • Self-tests
 • Fixed Viridian coexistence
 • No new KVM_CAP_XEN_xxx, just more bits returned by KVM_CAP_XEN_HVM

I'm about to do the event channel support, but this part stands alone
and should be sufficient to get a fully functional Xen HVM guest running.

David Woodhouse (6):
      KVM: Fix arguments to kvm_{un,}map_gfn()
      KVM: x86/xen: Fix coexistence of Xen and Hyper-V hypercalls
      KVM: x86/xen: latch long_mode when hypercall page is set up
      KVM: x86/xen: add definitions of compat_shared_info, compat_vcpu_info
      xen: add wc_sec_hi to struct shared_info
      KVM: x86: declare Xen HVM shared info capability and add test case

Joao Martins (9):
      KVM: x86/xen: fix Xen hypercall page msr handling
      KVM: x86/xen: intercept xen hypercalls if enabled
      KVM: x86/xen: add KVM_XEN_HVM_SET_ATTR/KVM_XEN_HVM_GET_ATTR
      KVM: x86/xen: register shared_info page
      KVM: x86/xen: setup pvclock updates
      KVM: x86/xen: update wallclock region
      KVM: x86/xen: register vcpu info
      KVM: x86/xen: register vcpu time info region
      KVM: x86/xen: register runstate info

 arch/x86/include/asm/kvm_host.h                    |  23 +
 arch/x86/include/asm/xen/interface.h               |   3 +
 arch/x86/kvm/Makefile                              |   2 +-
 arch/x86/kvm/hyperv.c                              |  40 +-
 arch/x86/kvm/trace.h                               |  36 ++
 arch/x86/kvm/x86.c                                 | 109 +++--
 arch/x86/kvm/x86.h                                 |   1 +
 arch/x86/kvm/xen.c                                 | 544 +++++++++++++++++++++
 arch/x86/kvm/xen.h                                 |  83 ++++
 include/linux/kvm_host.h                           |  34 +-
 include/uapi/linux/kvm.h                           |  47 ++
 include/xen/interface/xen.h                        |   4 +-
 tools/testing/selftests/kvm/Makefile               |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |   1 +
 .../testing/selftests/kvm/x86_64/xen_shinfo_test.c | 187 +++++++
 .../testing/selftests/kvm/x86_64/xen_vmcall_test.c | 150 ++++++
 virt/kvm/kvm_main.c                                |   8 +-
 17 files changed, 1201 insertions(+), 73 deletions(-)

32-bit guests, and fleshed out the runstate information a little more
to add times for all of running, runnable, blocked states.
```
#### [for-6.0 v5 00/13] Generalize memory encryption models
##### From: David Gibson <david@gibson.dropbear.id.au>

```c
From patchwork Fri Dec  4 05:44:02 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Gibson <david@gibson.dropbear.id.au>
X-Patchwork-Id: 11950621
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D954EC433FE
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 05:45:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7F94822581
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 05:45:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728126AbgLDFpB (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 00:45:01 -0500
Received: from bilbo.ozlabs.org ([203.11.71.1]:37939 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728066AbgLDFpA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 00:45:00 -0500
Received: by ozlabs.org (Postfix, from userid 1007)
        id 4CnM8f5b6bz9sT5; Fri,  4 Dec 2020 16:44:18 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple;
        d=gibson.dropbear.id.au; s=201602; t=1607060658;
        bh=mxWjWsAC0dVXxgKbwgpPWZDm0iZBSpsgilWWeTLy1wA=;
        h=From:To:Cc:Subject:Date:From;
        b=VvdNlqruhi8QpiSlhHbtiZmcLN+T/iqxrEaYWyAPqXmFUKeQj43iZdpFnJU378aJq
         AjsaiHVW2SGmCfXMTOKRxdvm7exQZ1idr85upuRz1XjerQecmgliAPzW6dk5zJeTR/
         d/0Gq7iSG0cFDUmkMNUyMSgSdsgWxSXB75PuKVag=
From: David Gibson <david@gibson.dropbear.id.au>
To: pair@us.ibm.com, pbonzini@redhat.com, frankja@linux.ibm.com,
        brijesh.singh@amd.com, dgilbert@redhat.com, qemu-devel@nongnu.org
Cc: Eduardo Habkost <ehabkost@redhat.com>, qemu-ppc@nongnu.org,
        rth@twiddle.net, thuth@redhat.com, berrange@redhat.com,
        mdroth@linux.vnet.ibm.com, Marcelo Tosatti <mtosatti@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Marcel Apfelbaum <marcel.apfelbaum@gmail.com>,
        david@redhat.com, Richard Henderson <richard.henderson@linaro.org>,
        borntraeger@de.ibm.com, David Gibson <david@gibson.dropbear.id.au>,
        cohuck@redhat.com, kvm@vger.kernel.org, qemu-s390x@nongnu.org,
        pasic@linux.ibm.com
Subject: [for-6.0 v5 00/13] Generalize memory encryption models
Date: Fri,  4 Dec 2020 16:44:02 +1100
Message-Id: <20201204054415.579042-1-david@gibson.dropbear.id.au>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A number of hardware platforms are implementing mechanisms whereby the
hypervisor does not have unfettered access to guest memory, in order
to mitigate the security impact of a compromised hypervisor.

AMD's SEV implements this with in-cpu memory encryption, and Intel has
its own memory encryption mechanism.  POWER has an upcoming mechanism
to accomplish this in a different way, using a new memory protection
level plus a small trusted ultravisor.  s390 also has a protected
execution environment.

The current code (committed or draft) for these features has each
platform's version configured entirely differently.  That doesn't seem
ideal for users, or particularly for management layers.

AMD SEV introduces a notionally generic machine option
"machine-encryption", but it doesn't actually cover any cases other
than SEV.

This series is a proposal to at least partially unify configuration
for these mechanisms, by renaming and generalizing AMD's
"memory-encryption" property.  It is replaced by a
"securable-guest-memory" property pointing to a platform specific
object which configures and manages the specific details.

Changes since v4:
 * Renamed from "host trust limitation" to "securable guest memory",
   which I think is marginally more descriptive
 * Re-organized initialization, because the previous model called at
   kvm_init didn't work for s390
* Assorted fixes to the s390 implementation; rudimentary testing
  (gitlab CI) only
Changes since v3:
 * Rebased
 * Added first cut at handling of s390 protected virtualization
Changes since RFCv2:
 * Rebased
 * Removed preliminary SEV cleanups (they've been merged)
 * Changed name to "host trust limitation"
 * Added migration blocker to the PEF code (based on SEV's version)
Changes since RFCv1:
 * Rebased
 * Fixed some errors pointed out by Dave Gilbert

David Gibson (12):
  securable guest memory: Introduce new securable guest memory base
    class
  securable guest memory: Handle memory encryption via interface
  securable guest memory: Move side effect out of
    machine_set_memory_encryption()
  securable guest memory: Rework the "memory-encryption" property
  securable guest memory: Decouple kvm_memcrypt_*() helpers from KVM
  sev: Add Error ** to sev_kvm_init()
  securable guest memory: Introduce sgm "ready" flag
  securable guest memory: Move SEV initialization into arch specific
    code
  spapr: Add PEF based securable guest memory
  spapr: PEF: prevent migration
  securable guest memory: Alter virtio default properties for protected
    guests
  s390: Recognize securable-guest-memory option

Greg Kurz (1):
  qom: Allow optional sugar props

 accel/kvm/kvm-all.c                   |  39 +------
 accel/kvm/sev-stub.c                  |  10 +-
 accel/stubs/kvm-stub.c                |  10 --
 backends/meson.build                  |   1 +
 backends/securable-guest-memory.c     |  30 +++++
 hw/core/machine.c                     |  71 ++++++++++--
 hw/i386/pc_sysfw.c                    |   6 +-
 hw/ppc/meson.build                    |   1 +
 hw/ppc/pef.c                          | 124 +++++++++++++++++++++
 hw/ppc/spapr.c                        |  10 ++
 hw/s390x/pv.c                         |  58 ++++++++++
 include/exec/securable-guest-memory.h |  86 +++++++++++++++
 include/hw/boards.h                   |   2 +-
 include/hw/ppc/pef.h                  |  26 +++++
 include/hw/s390x/pv.h                 |   1 +
 include/qemu/typedefs.h               |   1 +
 include/qom/object.h                  |   3 +-
 include/sysemu/kvm.h                  |  17 ---
 include/sysemu/sev.h                  |   5 +-
 qom/object.c                          |   4 +-
 softmmu/vl.c                          |  16 ++-
 target/i386/kvm.c                     |  12 ++
 target/i386/monitor.c                 |   1 -
 target/i386/sev.c                     | 153 ++++++++++++--------------
 target/ppc/kvm.c                      |  18 ---
 target/ppc/kvm_ppc.h                  |   6 -
 target/s390x/kvm.c                    |   3 +
 27 files changed, 510 insertions(+), 204 deletions(-)
 create mode 100644 backends/securable-guest-memory.c
 create mode 100644 hw/ppc/pef.c
 create mode 100644 include/exec/securable-guest-memory.h
 create mode 100644 include/hw/ppc/pef.h
```
#### [PATCH v3 0/2] clocksource: arm_arch_timer: Some fixes
##### From: Keqian Zhu <zhukeqian1@huawei.com>

```c
From patchwork Fri Dec  4 07:31:24 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: zhukeqian <zhukeqian1@huawei.com>
X-Patchwork-Id: 11950821
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A1570C0018C
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 07:33:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 740CF225AA
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 07:33:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728293AbgLDHdD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 02:33:03 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:9375 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726669AbgLDHdD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 02:33:03 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.58])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4CnPXm0qWLz76lf;
        Fri,  4 Dec 2020 15:31:52 +0800 (CST)
Received: from DESKTOP-5IS4806.china.huawei.com (10.174.187.37) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.487.0; Fri, 4 Dec 2020 15:32:12 +0800
From: Keqian Zhu <zhukeqian1@huawei.com>
To: <linux-kernel@vger.kernel.org>,
        <linux-arm-kernel@lists.infradead.org>,
        <kvmarm@lists.cs.columbia.edu>, <kvm@vger.kernel.org>
CC: Marc Zyngier <maz@kernel.org>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Catalin Marinas <catalin.marinas@arm.com>,
        Will Deacon <will@kernel.org>,
        James Morse <james.morse@arm.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        "Sean Christopherson" <sean.j.christopherson@intel.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Mark Brown <broonie@kernel.org>,
        "Andrew Morton" <akpm@linux-foundation.org>,
        Alexios Zavras <alexios.zavras@intel.com>,
        <wanghaibin.wang@huawei.com>, Keqian Zhu <zhukeqian1@huawei.com>
Subject: [PATCH v3 0/2] clocksource: arm_arch_timer: Some fixes
Date: Fri, 4 Dec 2020 15:31:24 +0800
Message-ID: <20201204073126.6920-1-zhukeqian1@huawei.com>
X-Mailer: git-send-email 2.8.4.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.37]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

change log:

v3:
 - Address Marc's comments.
 - Reform arch_timer_configure_evtstream.

v2:
 - Do not revert commit 0ea415390cd3, fix it instead.
 - Correct the tags of second patch.

Keqian Zhu (2):
  clocksource: arm_arch_timer: Use stable count reader in erratum sne
  clocksource: arm_arch_timer: Correct fault programming of
    CNTKCTL_EL1.EVNTI

 drivers/clocksource/arm_arch_timer.c | 27 ++++++++++++++++++---------
 1 file changed, 18 insertions(+), 9 deletions(-)
```
#### [PATCH v2 0/2] KVM: arm64: Expose CSV3 to guests on running on
##### From: Marc Zyngier <maz@kernel.org>
X-SA-Exim-Mail-From: maz@kernel.org

```c
From patchwork Fri Dec  4 18:37:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11952119
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.0 required=3.0 tests=BAYES_00,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6F835C433FE
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 18:38:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1BC8022CA1
	for <kvm@archiver.kernel.org>; Fri,  4 Dec 2020 18:38:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730173AbgLDSi1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 4 Dec 2020 13:38:27 -0500
Received: from mail.kernel.org ([198.145.29.99]:48474 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727210AbgLDSi1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 4 Dec 2020 13:38:27 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 6B3FE22AAB;
        Fri,  4 Dec 2020 18:37:46 +0000 (UTC)
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa  (TLS1.3) tls
 TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384
        (Exim 4.94)
        (envelope-from <maz@kernel.org>)
        id 1klFxg-00G3Uh-30; Fri, 04 Dec 2020 18:37:44 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: Will Deacon <will@kernel.org>, James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        David Brazdil <dbarzdil@google.com>, kernel-team@android.com
Subject: [PATCH v2 0/2] KVM: arm64: Expose CSV3 to guests on running on
 Meltdown-safe HW
Date: Fri,  4 Dec 2020 18:37:07 +0000
Message-Id: <20201204183709.784533-1-maz@kernel.org>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, will@kernel.org,
 james.morse@arm.com, julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
 dbarzdil@google.com, kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Will recently pointed out that when running on big-little systems that
are known not to be vulnerable to Metldown, guests are not presented
with the CSV3 property if the physical HW include a core that doesn't
have CSV3, despite being known to be safe (it is on the kpti_safe_list).

Since this is valuable information that can be cheaply given to the
guest, let's just do that. The scheme is the same as what we do for
CSV2, allowing userspace to change the default setting if this doesn't
advertise a safer setting than what the kernel thinks it is.

* From v1:
  - Fix the clearing of ID_AA64PFR0_EL1.CSV3 on update from userspace
  - Actually store the userspace value

Marc Zyngier (2):
  arm64: Make the Meltdown mitigation state available
  KVM: arm64: Advertise ID_AA64PFR0_EL1.CSV3=1 if the CPUs are
    Meltdown-safe

 arch/arm64/include/asm/kvm_host.h |  1 +
 arch/arm64/include/asm/spectre.h  |  2 ++
 arch/arm64/kernel/cpufeature.c    | 20 +++++++++++++++++---
 arch/arm64/kvm/arm.c              |  6 ++++--
 arch/arm64/kvm/sys_regs.c         | 16 +++++++++++++---
 5 files changed, 37 insertions(+), 8 deletions(-)
```
