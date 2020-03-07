#### [PATCH v3 1/2] KVM: VMX: rename 'kvm_area' to 'vmxon_region'
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11423843
Return-Path: <SRS0=b048=4X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5CCB3921
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 13:02:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3DCCB2166E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 13:02:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Q6oy0vfp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727146AbgCFNC0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Mar 2020 08:02:26 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:34939 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726733AbgCFNCZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 6 Mar 2020 08:02:25 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1583499744;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=y2yWNaYqjJ/RvKkVVduCbhM3C1I4Zkz6logIvpDXjRI=;
        b=Q6oy0vfpoUSWpizjCenTyIP2H4xFppaP/aL07Tm8nzTBA6pdF1XE+jmnddi2ZcTyWuBlAa
        w3wCs136ssTu+Svp7AkJQeLFFeBLaCNSFlm9uStyelesBKIk/WmWKtDkm8F4UYOkp2ctCO
        /ce8cmJ3WZQZZHlewRo8GFYP/uo7N9s=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-39-wG0-d9-HNH2lQX5CDpht-g-1; Fri, 06 Mar 2020 08:02:20 -0500
X-MC-Unique: wG0-d9-HNH2lQX5CDpht-g-1
Received: by mail-wm1-f69.google.com with SMTP id y7so859576wmd.4
        for <kvm@vger.kernel.org>; Fri, 06 Mar 2020 05:02:20 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=y2yWNaYqjJ/RvKkVVduCbhM3C1I4Zkz6logIvpDXjRI=;
        b=gjBXfGAR4kLou//3lyaAI8T0E4rmodS85S0CpWR+wcKxcweqQXZmTjks6+1CPtjAsW
         T6tBFLIqqoWKLLdKeysTV3f8UHdPQzq+m+8r/UraopYsyUm0b/zWnbTnMVzA6iZrFFzO
         gMLaqvrj7KM3VcN8RqbmR1Pf7RjHCmV1O+b2GkxdFdFpw7XsOu6j1UmJDgjmCAfCYy6Q
         sYjBdbsk/76qY9MgJ4Lu65lJmFU8PLWhKvFuE3iFwxBY/WqOzI8qV6i0T/g366jofJml
         RuO5y9kYZIs4leEEVb8hT3mTCZTG6cBL9vMwu05hnKXQx95mz3lcCcb6QdtjVxu4yUPe
         lgfA==
X-Gm-Message-State: ANhLgQ3wwSqwi3cmsT1IqZC87bPc8lxZVrO8cLE21rjUBwdSnALTD358
        rSzBxD33rO+47z/Y2Hvybs/G/pWLC2fPgD3899N89tNPi+AuVE3BjdiSGcvAG5BeNuZfIFuAohU
        2BvXrbgZ4Qy4u
X-Received: by 2002:a5d:6690:: with SMTP id l16mr4193877wru.251.1583499739787;
        Fri, 06 Mar 2020 05:02:19 -0800 (PST)
X-Google-Smtp-Source: 
 ADFU+vt1OXPzlEbyvBAvceW/RbmClBEpZeiagwVFOODbocvqNKeEiZjWeqYhWm0qnk58uiEN6mYnZw==
X-Received: by 2002:a5d:6690:: with SMTP id l16mr4193848wru.251.1583499739540;
        Fri, 06 Mar 2020 05:02:19 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 i67sm26613243wri.50.2020.03.06.05.02.18
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 06 Mar 2020 05:02:18 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Jim Mattson <jmattson@google.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 1/2] KVM: VMX: rename 'kvm_area' to 'vmxon_region'
Date: Fri,  6 Mar 2020 14:02:14 +0100
Message-Id: <20200306130215.150686-2-vkuznets@redhat.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200306130215.150686-1-vkuznets@redhat.com>
References: <20200306130215.150686-1-vkuznets@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The name 'kvm_area' is misleading (as we have way too many areas which are
KVM related), what alloc_kvm_area()/free_kvm_area() functions really do is
allocate/free VMXON region for all CPUs. Rename accordingly.

No functional change intended.

Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH v1 1/3] i386: Add "pebs" parameter to enable PEBS feature
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Kang, Luwei" <luwei.kang@intel.com>
X-Patchwork-Id: 11422941
Return-Path: <SRS0=b048=4X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3812717E0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 02:21:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 232F620801
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 02:21:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726682AbgCFCVm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 5 Mar 2020 21:21:42 -0500
Received: from mga18.intel.com ([134.134.136.126]:19708 "EHLO mga18.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726533AbgCFCVm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 5 Mar 2020 21:21:42 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by orsmga106.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 05 Mar 2020 18:21:41 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,520,1574150400";
   d="scan'208";a="413742185"
Received: from snr.bj.intel.com ([10.240.193.90])
  by orsmga005.jf.intel.com with ESMTP; 05 Mar 2020 18:21:39 -0800
From: Luwei Kang <luwei.kang@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        mst@redhat.com, marcel.apfelbaum@gmail.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org,
        Luwei Kang <luwei.kang@intel.com>
Subject: [PATCH v1 1/3] i386: Add "pebs" parameter to enable PEBS feature
Date: Fri,  6 Mar 2020 18:20:03 +0800
Message-Id: <1583490005-27761-2-git-send-email-luwei.kang@intel.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1583490005-27761-1-git-send-email-luwei.kang@intel.com>
References: <1583490005-27761-1-git-send-email-luwei.kang@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The PEBS virtualization enabling in KVM guest will be supported start from
IceLake hardware. This patch introduce a new CPU parameter "pebs" to enable
PEBS feature. The paramter of "pebs" is false by default.

PDCM,DTES64,DTS are needed by PEBS feature. Expose these feature bits to
KVM guest when the KVM support PEBS virtualization and the "pebs" parameter
is true.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 hw/i386/pc.c      |  1 +
 target/i386/cpu.c | 14 ++++++++++++++
 target/i386/cpu.h |  7 +++++++
 3 files changed, 22 insertions(+)

```
#### [PATCH 07/22] mips: Add MIPS32 Release 5 support
##### From: <Sergey.Semin@baikalelectronics.ru>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sergey Semin <Sergey.Semin@baikalelectronics.ru>
X-Patchwork-Id: 11423737
Return-Path: <SRS0=b048=4X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0219A1395
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 12:18:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B20A4208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 12:18:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726905AbgCFMSL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Mar 2020 07:18:11 -0500
Received: from mail.baikalelectronics.com ([87.245.175.226]:35038 "EHLO
        mail.baikalelectronics.ru" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726973AbgCFMSJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Mar 2020 07:18:09 -0500
X-Greylist: delayed 405 seconds by postgrey-1.27 at vger.kernel.org;
 Fri, 06 Mar 2020 07:18:04 EST
Received: from localhost (unknown [127.0.0.1])
        by mail.baikalelectronics.ru (Postfix) with ESMTP id 8B4398030795;
        Fri,  6 Mar 2020 12:11:18 +0000 (UTC)
X-Virus-Scanned: amavisd-new at baikalelectronics.ru
Received: from mail.baikalelectronics.ru ([127.0.0.1])
        by localhost (mail.baikalelectronics.ru [127.0.0.1]) (amavisd-new,
 port 10024)
        with ESMTP id CyGbeyZB4V-0; Fri,  6 Mar 2020 15:11:17 +0300 (MSK)
From: <Sergey.Semin@baikalelectronics.ru>
To: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
CC: Serge Semin <Sergey.Semin@baikalelectronics.ru>,
        Serge Semin <fancer.lancer@gmail.com>,
        Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>,
        Paul Burton <paulburton@kernel.org>,
        Ralf Baechle <ralf@linux-mips.org>,
        <linux-mips@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH 07/22] mips: Add MIPS32 Release 5 support
Date: Fri, 6 Mar 2020 15:08:31 +0300
In-Reply-To: <20200306120847.32690-1-Sergey.Semin@baikalelectronics.ru>
References: <20200306120847.32690-1-Sergey.Semin@baikalelectronics.ru>
MIME-Version: 1.0
X-ClientProxiedBy: MAIL.baikal.int (192.168.51.25) To mail (192.168.51.25)
Message-Id: <20200306121118.8B4398030795@mail.baikalelectronics.ru>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Serge Semin <Sergey.Semin@baikalelectronics.ru>

There are five MIPS32/64 architecture releases currently available:
from 1 to 6 except fourth one, which was intentionally skipped.
Three of them can be called as major: 1st, 2nd and 6th, that not only
have some system level alterations, but also introduced significant
core/ISA level updates. The rest of the MIPS architecture releases are
minor.

Even though they don't have as much ISA/system/core level changes
as the major ones with respect to the previous releases, they still
provide a set of updates (I'd say they were intended to be the
intermediate releases before a major one) that might be useful for the
kernel and user-level code, when activated by the kernel or compiler.
In particular the following features were introduced or ended up being
available at/after MIPS32 Release 5 architecture:
+ the last release of the misaligned memory access instructions,
+ virtualisation - VZ ASE - is optional component of the arch,
+ SIMD - MSA ASE - is optional component of the arch,
+ DSP ASE is optional component of the arch,
+ CP0.Status.FR=1 for CP1.FIR.F64=1 (pure 64-bit FPU general registers)
  must be available if FPU is implemented,
+ CP1.FIR.Has2008 support is required so CP1.FCSR.{ABS2008,NAN2008} bits
  are available.
+ UFR/UNFR aliases to access CP0.Status.FR from user-space by means of
  ctc1/cfc1 instructions (enabled by CP0.Config5.UFR),
+ CP0.COnfig5.LLB=1 and eretnc instruction are implemented to without
  accidentally clearing LL-bit when returning from an interrupt,
  exception, or error trap,
+ XPA feature together with extended versions of CPx registers is
  introduced, which needs to have mfhc0/mthc0 instructions available.

So due to these changes GNU GCC provides an extended instructions set
support for MIPS32 Release 5 by default like eretnc/mfhc0/mthc0. Even
though the architecture alteration isn't that big, it still worth to be
taken into account by the kernel software. Finally we can't deny that
some optimization/limitations might be found in future and implemented
on some level in kernel or compiler. In this case having even
intermediate MIPS architecture releases support would be more than
useful.

So the most of the changes provided by this commit can be split into
either compile- or runtime configs related. The compile-time related
changes are caused by adding the new CONFIG_CPU_MIPS32_R5/CONFIG_CPU_MIPSR5
configs and concern the code activating MIPSR2 or MIPSR6 already
implemented features (like eretnc/LLbit, mthc0/mfhc0). In addition
CPU_HAS_MSA can be now freely enabled for MIPS32 release 5 based
platforms as this is done for CPU_MIPS32_R6 CPUs. The runtime changes
concerns the features which are handled with respect to the MIPS ISA
revision detected at run-time by means of CP0.Config.{AT,AR} bits. Alas
these fields can be used to detect either r1 or r2 or r6 releases.
But since we know which CPUs in fact support the R5 arch, we can manually
set MIPS_CPU_ISA_M32R5 bit of c->isa_level and then use cpu_has_mips32_r5
where it's appropriate.

Since XPA/EVA provide too complex alterationss and to have them used with
MIPS32 Release 2 charged kernels (for compatibility with current platform
configs) they are left to be setup as a separate kernel configs.

Signed-off-by: Serge Semin <Sergey.Semin@baikalelectronics.ru>
Signed-off-by: Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>
Cc: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: Paul Burton <paulburton@kernel.org>
Cc: Ralf Baechle <ralf@linux-mips.org>
---
Even without this patch the code contains too many patterns like:
+#if defined(CONFIG_MIPS32R2) || defined(CONFIG_MIPS32R6)
What about switching it to a simpler
+#if CONFIG_TARGET_ISA_REV >= 2 ?
Though I'd prefer this config to be named like CONFIG_CPU_MIPS_REV.
What do you think?

Similarly the pattern like:
(MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
 MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
 MIPS_CPU_ISA_M32R5 |
 MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6)
could be replaced with simpler one:
(MIPS_CPU_ISA_M32 | MIPS_CPU_ISA_M64)
if corresponding macro were available. What do think about adding such?

We also could add CPU_MIPS64_R5 config support here, but I don't think
it's necessary at the moment seeing there is no any real chip ever
produced with that arch. Right?
---
 arch/mips/Kconfig                    | 34 ++++++++++++++++++++++++----
 arch/mips/Makefile                   |  1 +
 arch/mips/include/asm/asmmacro.h     | 18 ++++++++-------
 arch/mips/include/asm/compiler.h     |  5 ++++
 arch/mips/include/asm/cpu-features.h | 20 +++++++++++-----
 arch/mips/include/asm/cpu-info.h     |  2 +-
 arch/mips/include/asm/cpu-type.h     |  6 ++++-
 arch/mips/include/asm/cpu.h          |  7 +++---
 arch/mips/include/asm/fpu.h          |  4 ++--
 arch/mips/include/asm/hazards.h      |  8 ++++---
 arch/mips/include/asm/module.h       |  2 ++
 arch/mips/include/asm/stackframe.h   |  2 +-
 arch/mips/include/asm/switch_to.h    |  8 +++----
 arch/mips/kernel/cpu-probe.c         | 12 ++++++++++
 arch/mips/kernel/entry.S             |  6 ++---
 arch/mips/kernel/proc.c              |  2 ++
 arch/mips/kernel/r4k_fpu.S           | 14 ++++++------
 arch/mips/kvm/vz.c                   |  6 ++---
 arch/mips/lib/csum_partial.S         |  6 +++--
 arch/mips/mm/c-r4k.c                 |  7 +++---
 arch/mips/mm/sc-mips.c               |  7 +++---
 21 files changed, 123 insertions(+), 54 deletions(-)

```
#### [PATCH 07/22] mips: Add MIPS32 Release 5 support
##### From: <Sergey.Semin@baikalelectronics.ru>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sergey Semin <Sergey.Semin@baikalelectronics.ru>
X-Patchwork-Id: 11423803
Return-Path: <SRS0=b048=4X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 313021580
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 12:48:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E472A2187F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 12:48:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727085AbgCFMst (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Mar 2020 07:48:49 -0500
Received: from mail.baikalelectronics.com ([87.245.175.226]:35516 "EHLO
        mail.baikalelectronics.ru" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726998AbgCFMst (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Mar 2020 07:48:49 -0500
Received: from localhost (unknown [127.0.0.1])
        by mail.baikalelectronics.ru (Postfix) with ESMTP id 472228030794;
        Fri,  6 Mar 2020 12:48:43 +0000 (UTC)
X-Virus-Scanned: amavisd-new at baikalelectronics.ru
Received: from mail.baikalelectronics.ru ([127.0.0.1])
        by localhost (mail.baikalelectronics.ru [127.0.0.1]) (amavisd-new,
 port 10024)
        with ESMTP id 5kThnAxJGwEA; Fri,  6 Mar 2020 15:48:41 +0300 (MSK)
From: <Sergey.Semin@baikalelectronics.ru>
To: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
CC: Serge Semin <Sergey.Semin@baikalelectronics.ru>,
        Serge Semin <fancer.lancer@gmail.com>,
        Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>,
        Paul Burton <paulburton@kernel.org>,
        Ralf Baechle <ralf@linux-mips.org>,
        <linux-mips@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH 07/22] mips: Add MIPS32 Release 5 support
Date: Fri, 6 Mar 2020 15:46:50 +0300
In-Reply-To: <20200306124705.6595-1-Sergey.Semin@baikalelectronics.ru>
References: <20200306124705.6595-1-Sergey.Semin@baikalelectronics.ru>
MIME-Version: 1.0
X-ClientProxiedBy: MAIL.baikal.int (192.168.51.25) To mail (192.168.51.25)
Message-Id: <20200306124843.472228030794@mail.baikalelectronics.ru>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Serge Semin <Sergey.Semin@baikalelectronics.ru>

There are five MIPS32/64 architecture releases currently available:
from 1 to 6 except fourth one, which was intentionally skipped.
Three of them can be called as major: 1st, 2nd and 6th, that not only
have some system level alterations, but also introduced significant
core/ISA level updates. The rest of the MIPS architecture releases are
minor.

Even though they don't have as much ISA/system/core level changes
as the major ones with respect to the previous releases, they still
provide a set of updates (I'd say they were intended to be the
intermediate releases before a major one) that might be useful for the
kernel and user-level code, when activated by the kernel or compiler.
In particular the following features were introduced or ended up being
available at/after MIPS32 Release 5 architecture:
+ the last release of the misaligned memory access instructions,
+ virtualisation - VZ ASE - is optional component of the arch,
+ SIMD - MSA ASE - is optional component of the arch,
+ DSP ASE is optional component of the arch,
+ CP0.Status.FR=1 for CP1.FIR.F64=1 (pure 64-bit FPU general registers)
  must be available if FPU is implemented,
+ CP1.FIR.Has2008 support is required so CP1.FCSR.{ABS2008,NAN2008} bits
  are available.
+ UFR/UNFR aliases to access CP0.Status.FR from user-space by means of
  ctc1/cfc1 instructions (enabled by CP0.Config5.UFR),
+ CP0.COnfig5.LLB=1 and eretnc instruction are implemented to without
  accidentally clearing LL-bit when returning from an interrupt,
  exception, or error trap,
+ XPA feature together with extended versions of CPx registers is
  introduced, which needs to have mfhc0/mthc0 instructions available.

So due to these changes GNU GCC provides an extended instructions set
support for MIPS32 Release 5 by default like eretnc/mfhc0/mthc0. Even
though the architecture alteration isn't that big, it still worth to be
taken into account by the kernel software. Finally we can't deny that
some optimization/limitations might be found in future and implemented
on some level in kernel or compiler. In this case having even
intermediate MIPS architecture releases support would be more than
useful.

So the most of the changes provided by this commit can be split into
either compile- or runtime configs related. The compile-time related
changes are caused by adding the new CONFIG_CPU_MIPS32_R5/CONFIG_CPU_MIPSR5
configs and concern the code activating MIPSR2 or MIPSR6 already
implemented features (like eretnc/LLbit, mthc0/mfhc0). In addition
CPU_HAS_MSA can be now freely enabled for MIPS32 release 5 based
platforms as this is done for CPU_MIPS32_R6 CPUs. The runtime changes
concerns the features which are handled with respect to the MIPS ISA
revision detected at run-time by means of CP0.Config.{AT,AR} bits. Alas
these fields can be used to detect either r1 or r2 or r6 releases.
But since we know which CPUs in fact support the R5 arch, we can manually
set MIPS_CPU_ISA_M32R5 bit of c->isa_level and then use cpu_has_mips32_r5
where it's appropriate.

Since XPA/EVA provide too complex alterationss and to have them used with
MIPS32 Release 2 charged kernels (for compatibility with current platform
configs) they are left to be setup as a separate kernel configs.

Signed-off-by: Serge Semin <Sergey.Semin@baikalelectronics.ru>
Signed-off-by: Alexey Malahov <Alexey.Malahov@baikalelectronics.ru>
Cc: Thomas Bogendoerfer <tsbogend@alpha.franken.de>
Cc: Paul Burton <paulburton@kernel.org>
Cc: Ralf Baechle <ralf@linux-mips.org>
---
Even without this patch the code contains too many patterns like:
+#if defined(CONFIG_MIPS32R2) || defined(CONFIG_MIPS32R6)
What about switching it to a simpler
+#if CONFIG_TARGET_ISA_REV >= 2 ?
Though I'd prefer this config to be named like CONFIG_CPU_MIPS_REV.
What do you think?

Similarly the pattern like:
(MIPS_CPU_ISA_M32R1 | MIPS_CPU_ISA_M64R1 |
 MIPS_CPU_ISA_M32R2 | MIPS_CPU_ISA_M64R2 |
 MIPS_CPU_ISA_M32R5 |
 MIPS_CPU_ISA_M32R6 | MIPS_CPU_ISA_M64R6)
could be replaced with simpler one:
(MIPS_CPU_ISA_M32 | MIPS_CPU_ISA_M64)
if corresponding macro were available. What do think about adding such?

We also could add CPU_MIPS64_R5 config support here, but I don't think
it's necessary at the moment seeing there is no any real chip ever
produced with that arch. Right?
---
 arch/mips/Kconfig                    | 34 ++++++++++++++++++++++++----
 arch/mips/Makefile                   |  1 +
 arch/mips/include/asm/asmmacro.h     | 18 ++++++++-------
 arch/mips/include/asm/compiler.h     |  5 ++++
 arch/mips/include/asm/cpu-features.h | 20 +++++++++++-----
 arch/mips/include/asm/cpu-info.h     |  2 +-
 arch/mips/include/asm/cpu-type.h     |  6 ++++-
 arch/mips/include/asm/cpu.h          |  7 +++---
 arch/mips/include/asm/fpu.h          |  4 ++--
 arch/mips/include/asm/hazards.h      |  8 ++++---
 arch/mips/include/asm/module.h       |  2 ++
 arch/mips/include/asm/stackframe.h   |  2 +-
 arch/mips/include/asm/switch_to.h    |  8 +++----
 arch/mips/kernel/cpu-probe.c         | 12 ++++++++++
 arch/mips/kernel/entry.S             |  6 ++---
 arch/mips/kernel/proc.c              |  2 ++
 arch/mips/kernel/r4k_fpu.S           | 14 ++++++------
 arch/mips/kvm/vz.c                   |  6 ++---
 arch/mips/lib/csum_partial.S         |  6 +++--
 arch/mips/mm/c-r4k.c                 |  7 +++---
 arch/mips/mm/sc-mips.c               |  7 +++---
 21 files changed, 123 insertions(+), 54 deletions(-)

```
#### [PATCH 1/7] tools/kvm_stat: rework command line sequence and message texts
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefan Raspl <raspl@linux.ibm.com>
X-Patchwork-Id: 11423669
Return-Path: <SRS0=b048=4X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 00C2F14B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 11:43:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DE60C2084E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 11:43:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726879AbgCFLm7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Mar 2020 06:42:59 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:14564 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726025AbgCFLm7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 6 Mar 2020 06:42:59 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 026Bd4b8160103
        for <kvm@vger.kernel.org>; Fri, 6 Mar 2020 06:42:58 -0500
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2yk33mwx3k-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 06 Mar 2020 06:42:58 -0500
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <raspl@linux.ibm.com>;
        Fri, 6 Mar 2020 11:42:56 -0000
Received: from b06cxnps4075.portsmouth.uk.ibm.com (9.149.109.197)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 6 Mar 2020 11:42:53 -0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 026Bgq2P59310256
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 6 Mar 2020 11:42:52 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 755AA42041;
        Fri,  6 Mar 2020 11:42:52 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4C96542042;
        Fri,  6 Mar 2020 11:42:52 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri,  6 Mar 2020 11:42:52 +0000 (GMT)
From: Stefan Raspl <raspl@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: rkrcmar@redhat.com, pbonzini@redhat.com
Subject: [PATCH 1/7] tools/kvm_stat: rework command line sequence and message
 texts
Date: Fri,  6 Mar 2020 12:42:44 +0100
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200306114250.57585-1-raspl@linux.ibm.com>
References: <20200306114250.57585-1-raspl@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 20030611-0016-0000-0000-000002EDC083
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 20030611-0017-0000-0000-000033511847
Message-Id: <20200306114250.57585-2-raspl@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-03-06_03:2020-03-06,2020-03-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 bulkscore=0
 mlxscore=0 priorityscore=1501 suspectscore=1 lowpriorityscore=0
 clxscore=1015 malwarescore=0 impostorscore=0 phishscore=0 mlxlogscore=999
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2003060084
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Stefan Raspl <raspl@de.ibm.com>

Make sure command line arguments are sorted alphabetically
everywhere, and adjusted existing texts for interactive command 's' to
become consistent with the long form --set-delay.
Throwing in some PEP8 fixes (all cosmetics) for good measure.

Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
---
 tools/kvm/kvm_stat/kvm_stat     |  9 ++++----
 tools/kvm/kvm_stat/kvm_stat.txt | 40 ++++++++++++++++-----------------
 2 files changed, 25 insertions(+), 24 deletions(-)

```
#### [PATCH v3 1/5] x86/kvm/hyper-v: Explicitly align hcall param for kvm_hyperv_exit
##### From: Jon Doron <arilou@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jon Doron <arilou@gmail.com>
X-Patchwork-Id: 11424311
Return-Path: <SRS0=b048=4X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E58E792A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 16:39:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BBF612073D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  6 Mar 2020 16:39:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="ZNWeuQFw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726879AbgCFQjM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Mar 2020 11:39:12 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:33705 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725873AbgCFQjL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 6 Mar 2020 11:39:11 -0500
Received: by mail-wr1-f66.google.com with SMTP id x7so3139610wrr.0;
        Fri, 06 Mar 2020 08:39:10 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=cqBaz7Pqcjvqd8BzE+nwXVxffgaDXzbn0ymPrZ8bx5I=;
        b=ZNWeuQFwBIvTe8w5V1YJ7K5Z6Uu46S0ZxGEZAY4hVwRfR305Iu/gbeKfetnAfBNPgI
         8DzwxVoXrZUQ2NFGEq7plXlQHolqW+qSNR4ehqjlUNm3bdhyFOSeuMVVHh+U/PduMNlT
         n75b04c8DeJbXpcl18LinJ07xHBbS0Rhx1cuOSvwnxYK7r6Op4Aub+IAkwSQRC8oqs5/
         tx6OeVom0IetxxCro0quRNTy+T3ypiGa26ogoaJsPjnKm9ZWc67GqVPf1IDz777fSQwm
         85TPnF34t+l25w63hgf6ek3xBpPXp08T7mHZiqz/wD8c+1ca5TASle1ytUTGZV7afNIq
         9Gzw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=cqBaz7Pqcjvqd8BzE+nwXVxffgaDXzbn0ymPrZ8bx5I=;
        b=N24onkn78bekmvRkr+j0aTAkL6M85MIJhjeg2aRK6zbm60/++gNR1S9iof2EloA40L
         Zo6Lk1h2d4SloiHLZrJvnplg8oUg3NWDbqwKvAhFbAeyRmQvWKb95h1wIrQcASKGIcGP
         yKuU43Jlt4q1uohruKrbI5wi17l4iDhSZ0u77R+VmbXqbd0AHv3AMwv3qQ0NIls0swUi
         6EyuLEoJ69UtUp0kkThoFfzHvanN6tx3ZXU9kIFAxqqMm9orwg/5cRL7Re0qMVEw/E8W
         1hL8M7zo9TEozU+bnB+Qe/HwN7JwQs2XHv0fJ6IoQvrB1QC9LPjMyZjpIrdeFV4Tax/S
         xEQw==
X-Gm-Message-State: ANhLgQ0klXP/Q6RZHoUeSRDM7r8uFsX3Xn5USXyV0yypCPoz/G9ukaFl
        HAykQCDQ6OzMnPjS1bb8OdOYG5s9
X-Google-Smtp-Source: 
 ADFU+vu8PM8BfB/3tnpmAnl4QkKt8nOdKP/pQ6jqE9wlHwfOK4XvbbLSVru+j194LDNaN8YJVuc/lQ==
X-Received: by 2002:a5d:410a:: with SMTP id l10mr4491955wrp.380.1583512750017;
        Fri, 06 Mar 2020 08:39:10 -0800 (PST)
Received: from linux.local ([199.203.162.213])
        by smtp.gmail.com with ESMTPSA id
 n24sm8812760wra.61.2020.03.06.08.39.08
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 06 Mar 2020 08:39:09 -0800 (PST)
From: Jon Doron <arilou@gmail.com>
To: kvm@vger.kernel.org, linux-hyperv@vger.kernel.org
Cc: vkuznets@redhat.com, Jon Doron <arilou@gmail.com>
Subject: [PATCH v3 1/5] x86/kvm/hyper-v: Explicitly align hcall param for
 kvm_hyperv_exit
Date: Fri,  6 Mar 2020 18:39:05 +0200
Message-Id: <20200306163909.1020369-2-arilou@gmail.com>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <20200306163909.1020369-1-arilou@gmail.com>
References: <20200306163909.1020369-1-arilou@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Jon Doron <arilou@gmail.com>
---
 include/uapi/linux/kvm.h | 1 +
 1 file changed, 1 insertion(+)

```
