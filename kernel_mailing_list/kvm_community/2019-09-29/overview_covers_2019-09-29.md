

#### [PATCH v5 0/2] x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
From patchwork Sun Sep 29 01:57:16 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Tao Xu <tao3.xu@intel.com>
X-Patchwork-Id: 11165595
Return-Path: <SRS0=JqV3=XY=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CF966912
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Sep 2019 02:02:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AA76A2146E
	for <patchwork-kvm@patchwork.kernel.org>;
 Sun, 29 Sep 2019 02:02:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728759AbfI2B5W (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 28 Sep 2019 21:57:22 -0400
Received: from mga03.intel.com ([134.134.136.65]:14348 "EHLO mga03.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728569AbfI2B5W (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 28 Sep 2019 21:57:22 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga103.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 28 Sep 2019 18:57:22 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,561,1559545200";
   d="scan'208";a="204501449"
Received: from tao-optiplex-7060.sh.intel.com ([10.239.159.36])
  by fmsmga001.fm.intel.com with ESMTP; 28 Sep 2019 18:57:20 -0700
From: Tao Xu <tao3.xu@intel.com>
To: pbonzini@redhat.com, rth@twiddle.net, ehabkost@redhat.com,
        mtosatti@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org, tao3.xu@intel.com,
        jingqi.liu@intel.com
Subject: [PATCH v5 0/2] x86: Enable user wait instructions
Date: Sun, 29 Sep 2019 09:57:16 +0800
Message-Id: <20190929015718.19562-1-tao3.xu@intel.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it in kvm and provide a capability to
enable it. Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
QEMU use "-overcommit cpu-pm=on, a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Changelog:
v5:
	Remove CPUID_7_0_ECX_WAITPKG if enable_cpu_pm is not set. (Paolo)
v4:
	Set IA32_UMWAIT_CONTROL 32bits
v3:
	Simplify the patches, expose user wait instructions when the guest
	has CPUID (Paolo)
v2:
	Separated from the series
	https://www.mail-archive.com/qemu-devel@nongnu.org/msg549526.html
	Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
	QEMU use "-overcommit cpu-pm=on"	
v1:
	Sent out with MOVDIRI/MOVDIR64B instructions patches

Tao Xu (2):
  x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
  target/i386: Add support for save/load IA32_UMWAIT_CONTROL MSR

 target/i386/cpu.c     |  3 ++-
 target/i386/cpu.h     |  3 +++
 target/i386/kvm.c     | 19 +++++++++++++++++++
 target/i386/machine.c | 20 ++++++++++++++++++++
 4 files changed, 44 insertions(+), 1 deletion(-)
```
