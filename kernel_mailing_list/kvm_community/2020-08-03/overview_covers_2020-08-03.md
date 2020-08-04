

#### [PATCH v3 0/4] KVM: SVM: SEV-ES groundwork
##### From: Joerg Roedel <joro@8bytes.org>

```c
From patchwork Mon Aug  3 12:27:04 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11697937
Return-Path: <SRS0=Rn+f=BN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6407A722
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 12:27:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 53CBD2083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 12:27:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728541AbgHCM11 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 08:27:27 -0400
Received: from 8bytes.org ([81.169.241.247]:34650 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728530AbgHCM1Y (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 08:27:24 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id E244D423; Mon,  3 Aug 2020 14:27:21 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 0/4] KVM: SVM: SEV-ES groundwork
Date: Mon,  3 Aug 2020 14:27:04 +0200
Message-Id: <20200803122708.5942-1-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

here is v3 of the  groundwork patches for the upcoming SEV-ES support in
the Linux kernel. They are part of both the client patch-set and the
KVM hypervisor patches (under development).

Patch 1 necesary to fix a compile warning about a stack-frame getting
too large. The other 3 patches define the Guest Hypervisor
Communication Block (GHCB) and accessor functions.

This version addresses the review comments from Sean.

It would be great if you could consider them for v5.9, so that the
client and the hypervisor patch-sets can be developed more independently
of each other.

Please let me know what you think.

Regards,

	Joerg

Borislav Petkov (1):
  KVM: SVM: Use __packed shorthand

Joerg Roedel (2):
  KVM: SVM: nested: Don't allocate VMCB structures on stack
  KVM: SVM: Add GHCB Accessor functions

Tom Lendacky (1):
  KVM: SVM: Add GHCB definitions

 arch/x86/include/asm/svm.h | 100 ++++++++++++++++++++++++++++++++++---
 arch/x86/kvm/svm/nested.c  |  47 +++++++++++------
 arch/x86/kvm/svm/svm.c     |   2 +
 3 files changed, 128 insertions(+), 21 deletions(-)
```
#### [PATCH 0/6] Add SBI v0.2 support for KVM
##### From: Atish Patra <atish.patra@wdc.com>

```c
From patchwork Mon Aug  3 17:58:40 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Atish Patra <atish.patra@wdc.com>
X-Patchwork-Id: 11698527
Return-Path: <SRS0=Rn+f=BN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4F8313B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 17:59:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B51A622BED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 17:59:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="ULxvTcVi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727114AbgHCR7Q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 13:59:16 -0400
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:64728 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726239AbgHCR7Q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 13:59:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1596477555; x=1628013555;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=VOtqlyeTI7pj/+WHRY84iOltoY1CldDSHk2ut6rF0TA=;
  b=ULxvTcVi1llcpnaSO40ak6Zvkze1vb0XTLevuyK67GidwfQfT3tv1yhm
   kiwhUowBxWIcNSOXB3LqP0e2JSUjYj8T9yH1sbXVkX/0HSQhdFi8mflYu
   KmT4uVaf13AcVOQdb1H8AhLeIenNJvO6Iv/caIS8w0+r414gMZqh+Ax71
   KVU7ob+N1vmlj5Ow5ytynOOztmN5TM8RMnL7/UMOasoluYX1xQk8WPiYJ
   TkD9t81eheeU//vSPzdok8GoKYTit+demOpofOIYIVZKCAqbctAfsfGaN
   YK19yn3A6v/Pi5sa748liv02OW+kmbZ+Z1Yi0LpmONXOwG/8UyLeYbIXr
   w==;
IronPort-SDR: 
 oPMxDLwMfQHHOCpDbh1TynPUcKhbP0zVZDhIpHc9ZQaUKp5Uvt0zicWTa+VALzh2K1UiaTorSZ
 iGyLjrkO2pAavsidp9T0GlaU1ocdt2diK3Qv//pX2IMdpsPrYRrjy0e8xZzphgvoqZ6IHEn8wY
 1ltRyH5WoQ6k+qj2wQvTGHPQBqM5jAYG6I2xkvMuymmmZmT7DeZTTsmH7PsQzrIdYKxuBUWJlt
 I9mk6XbEsPGR7fvqXZndzoxONk0hwpkgBqDy2kj0/L3x8tbZ/pus9bCbA8a5r7Cgf2xqw+keQZ
 zok=
X-IronPort-AV: E=Sophos;i="5.75,430,1589212800";
   d="scan'208";a="144033180"
Received: from h199-255-45-14.hgst.com (HELO uls-op-cesaep01.wdc.com)
 ([199.255.45.14])
  by ob1.hgst.iphmx.com with ESMTP; 04 Aug 2020 01:59:03 +0800
IronPort-SDR: 
 rmitMzpTBLuDNA1XJ/LlNY19nniyj4M68ST5vAlB0K/1mVnb9ubEMpML9H6BNkENh4F+xPH/n3
 Aami7WoNuM/A==
Received: from uls-op-cesaip01.wdc.com ([10.248.3.36])
  by uls-op-cesaep01.wdc.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 03 Aug 2020 10:47:06 -0700
IronPort-SDR: 
 iZb2sq5TmobDGkm1+xth6Z7qWVDWypo/WO9cBwNRRp0XCuOe4j67qj5bOnpyao4FekVWUgDZom
 eh4CemSsEC9g==
WDCIronportException: Internal
Received: from cnf007830.ad.shared (HELO jedi-01.hgst.com) ([10.86.58.196])
  by uls-op-cesaip01.wdc.com with ESMTP; 03 Aug 2020 10:59:03 -0700
From: Atish Patra <atish.patra@wdc.com>
To: kvm-riscv@lists.infradead.org, linux-riscv@lists.infradead.org
Cc: Atish Patra <atish.patra@wdc.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Anup Patel <anup.patel@wdc.com>,
        Kefeng Wang <wangkefeng.wang@huawei.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Palmer Dabbelt <palmer@dabbelt.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Alexander Graf <graf@amazon.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Alistair Francis <Alistair.Francis@wdc.com>
Subject: [PATCH 0/6] Add SBI v0.2 support for KVM
Date: Mon,  3 Aug 2020 10:58:40 -0700
Message-Id: <20200803175846.26272-1-atish.patra@wdc.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The Supervisor Binary Interface(SBI) specification[1] now defines a
base extension that provides extendability to add future extensions
while maintaining backward compatibility with previous versions.
The new version is defined as 0.2 and older version is marked as 0.1.

This series adds following features to RISC-V Linux KVM.
1. Adds support for SBI v0.2 in KVM
2. SBI Hart state management extension (HSM) in KVM
3. Ordered booting of guest vcpus in guest Linux

This series depends on the base kvm support series[2].

Guest kernel needs to also support SBI v0.2 and HSM extension in Kernel
to boot multiple vcpus. Linux kernel supports both starting v5.7.
In absense of that, guest can only boot 1vcpu.

[1] https://github.com/riscv/riscv-sbi-doc/blob/master/riscv-sbi.adoc
[2] http://lists.infradead.org/pipermail/linux-riscv/2020-July/001028.html

Atish Patra (6):
RISC-V: Add a non-void return for sbi v02 functions
RISC-V: Mark the existing SBI v0.1 implementation as legacy
RISC-V: Reorganize SBI code by moving legacy SBI to its own file
RISC-V: Add SBI v0.2 base extension
RISC-V: Add v0.1 replacement SBI extensions defined in v02
RISC-V: Add SBI HSM extension in KVM

arch/riscv/include/asm/kvm_vcpu_sbi.h |  32 +++++
arch/riscv/include/asm/sbi.h          |  17 ++-
arch/riscv/kernel/sbi.c               |  32 ++---
arch/riscv/kvm/Makefile               |   4 +-
arch/riscv/kvm/vcpu.c                 |  19 +++
arch/riscv/kvm/vcpu_sbi.c             | 194 ++++++++++++--------------
arch/riscv/kvm/vcpu_sbi_base.c        |  73 ++++++++++
arch/riscv/kvm/vcpu_sbi_hsm.c         | 109 +++++++++++++++
arch/riscv/kvm/vcpu_sbi_legacy.c      | 129 +++++++++++++++++
arch/riscv/kvm/vcpu_sbi_replace.c     | 136 ++++++++++++++++++
10 files changed, 619 insertions(+), 126 deletions(-)
create mode 100644 arch/riscv/include/asm/kvm_vcpu_sbi.h
create mode 100644 arch/riscv/kvm/vcpu_sbi_base.c
create mode 100644 arch/riscv/kvm/vcpu_sbi_hsm.c
create mode 100644 arch/riscv/kvm/vcpu_sbi_legacy.c
create mode 100644 arch/riscv/kvm/vcpu_sbi_replace.c
---
2.24.0
```
#### [PATCH v4 0/4] KVM: SVM: SEV-ES groundwork
##### From: Joerg Roedel <joro@8bytes.org>

```c
From patchwork Mon Aug  3 21:00:30 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11698827
Return-Path: <SRS0=Rn+f=BN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C998813B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 21:00:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1FFB722BED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 21:01:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729263AbgHCVAh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 17:00:37 -0400
Received: from 8bytes.org ([81.169.241.247]:34800 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729256AbgHCVAh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 17:00:37 -0400
Received: by theia.8bytes.org (Postfix, from userid 1000)
        id 1833D217; Mon,  3 Aug 2020 23:00:36 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Tom Lendacky <thomas.lendacky@amd.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v4 0/4] KVM: SVM: SEV-ES groundwork
Date: Mon,  3 Aug 2020 23:00:30 +0200
Message-Id: <20200803210034.26386-1-joro@8bytes.org>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo,

here is v4 of the groundwork patches for the upcoming SEV-ES support in
the Linux kernel. They are part of both the client patch-set and the KVM
hypervisor patches (under development).

Patch 1 necessary to fix a compile warning about a stack-frame getting
too large. Patches 2 and 3 define the Guest Hypervisor Communication
Block (GHCB) and accessor functions and the last patch is a cleanup.

This version addresses more review comments from Sean.  Additionally the
patches are now checkpatch-clean.

It would be great if you could consider them for v5.9, so that the
client and the hypervisor patch-sets can be developed more independently
of each other.

Please let me know what you think.

Regards,

	Joerg

Borislav Petkov (1):
  KVM: SVM: Use __packed shorthand

Joerg Roedel (2):
  KVM: SVM: nested: Don't allocate VMCB structures on stack
  KVM: SVM: Add GHCB Accessor functions

Tom Lendacky (1):
  KVM: SVM: Add GHCB definitions

 arch/x86/include/asm/svm.h | 100 ++++++++++++++++++++++++++++++++++---
 arch/x86/kvm/svm/nested.c  |  47 +++++++++++------
 arch/x86/kvm/svm/svm.c     |   2 +
 3 files changed, 128 insertions(+), 21 deletions(-)
```
#### [PATCH v4 0/3] Allow user space to restrict and augment MSR emulation
##### From: Alexander Graf <graf@amazon.com>

```c
From patchwork Mon Aug  3 21:14:20 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Graf <graf@amazon.com>
X-Patchwork-Id: 11699187
Return-Path: <SRS0=Rn+f=BN=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D19C514DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 21:15:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1AD9922CA1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  3 Aug 2020 21:15:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amazon.com header.i=@amazon.com
 header.b="J1+kXVUQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729229AbgHCVPA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 3 Aug 2020 17:15:00 -0400
Received: from smtp-fw-33001.amazon.com ([207.171.190.10]:22592 "EHLO
        smtp-fw-33001.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728570AbgHCVOz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 3 Aug 2020 17:14:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.com; i=@amazon.com; q=dns/txt; s=amazon201209;
  t=1596489294; x=1628025294;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=A9YeFP9lUcJ4Il7shxNgntYRt+kEhRaIhYpWYV0cPJ0=;
  b=J1+kXVUQLiFhSSstL55tYHEXdYCwW/MRwYZ8PeIIF6YuRK3/9+T7zR8e
   ZpUchcIeeKJTWXkS8NHWdrx70G0Kqx+qpbv/T+B9qP/+xpEls9nwgPLlL
   QMKj0Ls0Tu/gdiF4nwL5T/yJzJrFjXhoQgkZG2loSgvjPDT5x1ExCBtmr
   4=;
IronPort-SDR: 
 0MUbpDfmLkGtC4er2il2s+Yd9ppFbgY98rd66QIbjUNRSq7kxydYQmSdoltQzGDv9cogKeNmHx
 sWyiZB3kMncg==
X-IronPort-AV: E=Sophos;i="5.75,431,1589241600";
   d="scan'208";a="63982103"
Received: from sea32-co-svc-lb4-vlan3.sea.corp.amazon.com (HELO
 email-inbound-relay-1e-62350142.us-east-1.amazon.com) ([10.47.23.38])
  by smtp-border-fw-out-33001.sea14.amazon.com with ESMTP;
 03 Aug 2020 21:14:39 +0000
Received: from EX13MTAUWC001.ant.amazon.com
 (iad55-ws-svc-p15-lb9-vlan2.iad.amazon.com [10.40.159.162])
        by email-inbound-relay-1e-62350142.us-east-1.amazon.com (Postfix) with
 ESMTPS id 20832A1E72;
        Mon,  3 Aug 2020 21:14:34 +0000 (UTC)
Received: from EX13D20UWC001.ant.amazon.com (10.43.162.244) by
 EX13MTAUWC001.ant.amazon.com (10.43.162.135) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 3 Aug 2020 21:14:34 +0000
Received: from u79c5a0a55de558.ant.amazon.com (10.43.161.145) by
 EX13D20UWC001.ant.amazon.com (10.43.162.244) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 3 Aug 2020 21:14:31 +0000
From: Alexander Graf <graf@amazon.com>
To: Paolo Bonzini <pbonzini@redhat.com>
CC: Jonathan Corbet <corbet@lwn.net>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>,
        KarimAllah Raslan <karahmed@amazon.de>,
        Aaron Lewis <aaronlewis@google.com>, <kvm@vger.kernel.org>,
        <linux-doc@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH v4 0/3] Allow user space to restrict and augment MSR emulation
Date: Mon, 3 Aug 2020 23:14:20 +0200
Message-ID: <20200803211423.29398-1-graf@amazon.com>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.161.145]
X-ClientProxiedBy: EX13D36UWB001.ant.amazon.com (10.43.161.84) To
 EX13D20UWC001.ant.amazon.com (10.43.162.244)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While tying to add support for the MSR_CORE_THREAD_COUNT MSR in KVM,
I realized that we were still in a world where user space has no control
over what happens with MSR emulation in KVM.

That is bad for multiple reasons. In my case, I wanted to emulate the
MSR in user space, because it's a CPU specific register that does not
exist on older CPUs and that really only contains informational data that
is on the package level, so it's a natural fit for user space to provide
it.

However, it is also bad on a platform compatibility level. Currrently,
KVM has no way to expose different MSRs based on the selected target CPU
type.

This patch set introduces a way for user space to indicate to KVM which
MSRs should be handled in kernel space. With that, we can solve part of
the platform compatibility story. Or at least we can not handle AMD specific
MSRs on an Intel platform and vice versa.

In addition, it introduces a way for user space to get into the loop
when an MSR access would generate a #GP fault, such as when KVM finds an
MSR that is not handled by the in-kernel MSR emulation or when the guest
is trying to access reserved registers.

In combination with the allow list, the user space trapping allows us
to emulate arbitrary MSRs in user space, paving the way for target CPU
specific MSR implementations from user space.

v1 -> v2:

  - s/ETRAP_TO_USER_SPACE/ENOENT/g
  - deflect all #GP injection events to user space, not just unknown MSRs.
    That was we can also deflect allowlist errors later
  - fix emulator case
  - new patch: KVM: x86: Introduce allow list for MSR emulation
  - new patch: KVM: selftests: Add test for user space MSR handling

v2 -> v3:

  - return r if r == X86EMUL_IO_NEEDED
  - s/KVM_EXIT_RDMSR/KVM_EXIT_X86_RDMSR/g
  - s/KVM_EXIT_WRMSR/KVM_EXIT_X86_WRMSR/g
  - Use complete_userspace_io logic instead of reply field
  - Simplify trapping code
  - document flags for KVM_X86_ADD_MSR_ALLOWLIST
  - generalize exit path, always unlock when returning
  - s/KVM_CAP_ADD_MSR_ALLOWLIST/KVM_CAP_X86_MSR_ALLOWLIST/g
  - Add KVM_X86_CLEAR_MSR_ALLOWLIST
  - Add test to clear whitelist
  - Adjust to reply-less API
  - Fix asserts
  - Actually trap on MSR_IA32_POWER_CTL writes

v3 -> v4:

  - Mention exit reasons in re-enter mandatory section of API documentation
  - Clear padding bytes
  - Generalize get/set deflect functions
  - Remove redundant pending_user_msr field
  - lock allow check and clearing
  - free bitmaps on clear

Alexander Graf (3):
  KVM: x86: Deflect unknown MSR accesses to user space
  KVM: x86: Introduce allow list for MSR emulation
  KVM: selftests: Add test for user space MSR handling

 Documentation/virt/kvm/api.rst                | 157 ++++++++++-
 arch/x86/include/asm/kvm_host.h               |  13 +
 arch/x86/include/uapi/asm/kvm.h               |  15 +
 arch/x86/kvm/emulate.c                        |  18 +-
 arch/x86/kvm/x86.c                            | 259 +++++++++++++++++-
 include/trace/events/kvm.h                    |   2 +-
 include/uapi/linux/kvm.h                      |  15 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/x86_64/user_msr_test.c      | 221 +++++++++++++++
 9 files changed, 692 insertions(+), 9 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/user_msr_test.c
```
