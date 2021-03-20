#### [PATCH] documentation/kvm: additional explanations on KVM_SET_BOOT_CPU_ID
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 12150437
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BFF1CC433E6
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 09:17:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7F97D64F62
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 09:17:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229849AbhCSJR1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Mar 2021 05:17:27 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:36307 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229826AbhCSJRI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Mar 2021 05:17:08 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616145427;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=dTG0YNeiE2Tcbqwn6SJ65GVmG9r9Ym8B4ZrhCrxe4xk=;
        b=Xfv9UIX2cLY/g0NU6oXuBO8ORClG0buiap3aTMo64UHdwlLpIpVBvnwcucdBCeX4MNOLey
        Iy40NFrOvRi+nFuTq4nA6Rd7p+Hnd/Mk8LFlC2UP3gtXaMbw8UWdkN74T0PcgU/pFbwPPp
        gC6Po/WJIjIdMItWjqA1c8lmkGoRLPM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-317-sIzvRL-cMLiXnT6fmBNyZg-1; Fri, 19 Mar 2021 05:16:56 -0400
X-MC-Unique: sIzvRL-cMLiXnT6fmBNyZg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id D996A189CD06;
        Fri, 19 Mar 2021 09:16:54 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-113-38.ams2.redhat.com
 [10.36.113.38])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 10E5961D31;
        Fri, 19 Mar 2021 09:16:51 +0000 (UTC)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: linux-doc@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Andrew Jones <drjones@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] documentation/kvm: additional explanations on
 KVM_SET_BOOT_CPU_ID
Date: Fri, 19 Mar 2021 10:16:50 +0100
Message-Id: <20210319091650.11967-1-eesposit@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The ioctl KVM_SET_BOOT_CPU_ID fails when called after vcpu creation.
Add this explanation in the documentation.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 Documentation/virt/kvm/api.rst | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [GIT PULL] KVM changes for Linux 5.12-rc4
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 12151863
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,INCLUDES_PULL_REQUEST,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,
	SPF_HELO_NONE,SPF_PASS autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 09B22C433DB
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 20:26:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CB01761949
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 20:26:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230335AbhCSUZ4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Mar 2021 16:25:56 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:35800 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230206AbhCSUZZ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Mar 2021 16:25:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1616185520;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=PMF1Va7K5vPqZ+/8veih9JjawoEvPslxFD06HPVOZ3Y=;
        b=A9khCmcUNGk/BtEfdnTxnJjOQ8Js0qt9Qmu3/zX3RlPg1MAYeXrNbcKjdDXrYt/UHftgaM
        Q3ZaixwLCi1II2muTDCy7uqOj2jQrBhkW4IH5t6Ir7nVnv32o+whHlv81cnPJQlMfFWr/r
        6zhKLxupEs0V1YAjT3qE9UsnDs7h1IQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-350-dBMOzxH6M_2ICz1x-dzqSw-1; Fri, 19 Mar 2021 16:25:18 -0400
X-MC-Unique: dBMOzxH6M_2ICz1x-dzqSw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5554F801817;
        Fri, 19 Mar 2021 20:25:17 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 0231F1A874;
        Fri, 19 Mar 2021 20:25:16 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.12-rc4
Date: Fri, 19 Mar 2021 16:25:16 -0400
Message-Id: <20210319202516.2235406-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 1e28eed17697bcf343c6743f0028cc3b5dd88bf0:

  Linux 5.12-rc3 (2021-03-14 14:41:02 -0700)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 9ce3746d64132a561bceab6421715e7c04e85074:

  documentation/kvm: additional explanations on KVM_SET_BOOT_CPU_ID (2021-03-19 05:31:32 -0400)

----------------------------------------------------------------
x86:
* new selftests
* fixes for migration with HyperV re-enlightenment enabled
* fix RCU/SRCU usage
* fixes for local_irq_restore misuse false positive

----------------------------------------------------------------
Ben Gardon (3):
      KVM: x86/mmu: Fix RCU usage in handle_removed_tdp_mmu_page
      KVM: x86/mmu: Fix RCU usage when atomically zapping SPTEs
      KVM: x86/mmu: Factor out tdp_iter_return_to_root

Emanuele Giuseppe Esposito (4):
      selftests: kvm: add get_msr_index_features
      selftests: kvm: add _vm_ioctl
      selftests: kvm: add set_boot_cpu_id test
      documentation/kvm: additional explanations on KVM_SET_BOOT_CPU_ID

Sean Christopherson (2):
      KVM: x86/mmu: Store the address space ID in the TDP iterator
      KVM: x86: Protect userspace MSR filter with SRCU, and set atomically-ish

Vitaly Kuznetsov (5):
      KVM: x86: hyper-v: Limit guest to writing zero to HV_X64_MSR_TSC_EMULATION_STATUS
      KVM: x86: hyper-v: Prevent using not-yet-updated TSC page by secondary CPUs
      KVM: x86: hyper-v: Track Hyper-V TSC page status
      KVM: x86: hyper-v: Don't touch TSC page values when guest opted for re-enlightenment
      selftests: kvm: Add basic Hyper-V clocksources tests

Wanpeng Li (2):
      KVM: X86: Fix missing local pCPU when executing wbinvd on all dirty pCPUs
      x86/kvm: Fix broken irq restoration in kvm_wait

 Documentation/virt/kvm/api.rst                     |   9 +-
 arch/x86/include/asm/kvm_host.h                    |  34 ++-
 arch/x86/kernel/kvm.c                              |  23 +-
 arch/x86/kvm/hyperv.c                              |  91 +++++++-
 arch/x86/kvm/hyperv.h                              |   1 +
 arch/x86/kvm/mmu/mmu_internal.h                    |   5 +
 arch/x86/kvm/mmu/tdp_iter.c                        |  30 ++-
 arch/x86/kvm/mmu/tdp_iter.h                        |   4 +-
 arch/x86/kvm/mmu/tdp_mmu.c                         |  40 ++--
 arch/x86/kvm/x86.c                                 | 113 +++++----
 tools/testing/selftests/kvm/.gitignore             |   3 +
 tools/testing/selftests/kvm/Makefile               |   3 +
 tools/testing/selftests/kvm/include/kvm_util.h     |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c         |   7 +-
 .../testing/selftests/kvm/lib/kvm_util_internal.h  |   2 -
 .../selftests/kvm/x86_64/get_msr_index_features.c  | 134 +++++++++++
 tools/testing/selftests/kvm/x86_64/hyperv_clock.c  | 260 +++++++++++++++++++++
 .../testing/selftests/kvm/x86_64/set_boot_cpu_id.c | 166 +++++++++++++
 18 files changed, 807 insertions(+), 120 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/get_msr_index_features.c
 create mode 100644 tools/testing/selftests/kvm/x86_64/hyperv_clock.c
 create mode 100644 tools/testing/selftests/kvm/x86_64/set_boot_cpu_id.c
```
#### [PATCH v3 01/25] x86/cpufeatures: Make SGX_LC feature bit depend on SGX bit
##### From: Kai Huang <kai.huang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12150231
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 2FC60C4332B
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 07:23:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F3A1464F62
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 07:23:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S234137AbhCSHW4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Mar 2021 03:22:56 -0400
Received: from mga14.intel.com ([192.55.52.115]:59402 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S234168AbhCSHWf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Mar 2021 03:22:35 -0400
IronPort-SDR: 
 QD/x6QbE3d4QiXI3s5T2V8hw9nUYgmY1CDCPuGO6JMk8a+tmBJvoPWV/o5/OREYh3Xda1f7HF1
 t9YiweWugdZw==
X-IronPort-AV: E=McAfee;i="6000,8403,9927"; a="189222109"
X-IronPort-AV: E=Sophos;i="5.81,261,1610438400";
   d="scan'208";a="189222109"
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Mar 2021 00:22:35 -0700
IronPort-SDR: 
 ed42vW7y4IWWkFm1KTmRfBEu3a4rTD9KmDRu7JHDeYOobOLmh2VNPJefR46n1qAo1SD2ddlQP7
 w2M4wUBjyimw==
X-IronPort-AV: E=Sophos;i="5.81,261,1610438400";
   d="scan'208";a="413409177"
Received: from dlmeisen-mobl1.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.255.229.165])
  by orsmga008-auth.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 19 Mar 2021 00:22:30 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, x86@kernel.org, linux-sgx@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, seanjc@google.com, jarkko@kernel.org,
        luto@kernel.org, dave.hansen@intel.com, rick.p.edgecombe@intel.com,
        haitao.huang@intel.com, pbonzini@redhat.com, bp@alien8.de,
        tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        Kai Huang <kai.huang@intel.com>
Subject: [PATCH v3 01/25] x86/cpufeatures: Make SGX_LC feature bit depend on
 SGX bit
Date: Fri, 19 Mar 2021 20:22:17 +1300
Message-Id: 
 <5d4220fd0a39f52af024d3fa166231c1d498dd10.1616136308.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.30.2
In-Reply-To: <cover.1616136307.git.kai.huang@intel.com>
References: <cover.1616136307.git.kai.huang@intel.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Move SGX_LC feature bit to CPUID dependency table to make clearing all
SGX feature bits easier. Also remove clear_sgx_caps() since it is just
a wrapper of setup_clear_cpu_cap(X86_FEATURE_SGX) now.

Suggested-by: Sean Christopherson <seanjc@google.com>
Acked-by: Dave Hansen <dave.hansen@intel.com>
Acked-by: Jarkko Sakkinen <jarkko@kernel.org>
Reviewed-by: Sean Christopherson <seanjc@google.com>
Signed-off-by: Kai Huang <kai.huang@intel.com>
---
 arch/x86/kernel/cpu/cpuid-deps.c |  1 +
 arch/x86/kernel/cpu/feat_ctl.c   | 12 +++---------
 2 files changed, 4 insertions(+), 9 deletions(-)

```
#### [kvm-unit-tests PATCH v3] configure: arm/arm64: Add --earlycon option to set UART type and address
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 12151545
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A7CEFC433DB
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 16:54:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7353261963
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 16:54:38 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229991AbhCSQyG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Mar 2021 12:54:06 -0400
Received: from foss.arm.com ([217.140.110.172]:56786 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229806AbhCSQxm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Mar 2021 12:53:42 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 64399ED1;
        Fri, 19 Mar 2021 09:53:42 -0700 (PDT)
Received: from monolith.localdoman (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 97D1F3FA00;
        Fri, 19 Mar 2021 09:53:41 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: drjones@redhat.com, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu
Cc: pbonzini@redhat.com
Subject: [kvm-unit-tests PATCH v3] configure: arm/arm64: Add --earlycon option
 to set UART type and address
Date: Fri, 19 Mar 2021 16:53:59 +0000
Message-Id: <20210319165359.58498-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.31.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Currently, the UART early address is set indirectly with the --vmm option
and there are only two possible values: if the VMM is qemu (the default),
then the UART address is set to 0x09000000; if the VMM is kvmtool, then the
UART address is set to 0x3f8.

The upstream kvmtool commit 45b4968e0de1 ("hw/serial: ARM/arm64: Use MMIO
at higher addresses") changed the UART address to 0x1000000, and
kvm-unit-tests so far hasn't had mechanism to let the user set a specific
address, which means that for recent versions of kvmtool the early UART
won't be available.

This situation will only become worse as kvm-unit-tests gains support to
run as an EFI app, as each platform will have their own UART type and
address.

To address both issues, a new configure option is added, --earlycon. The
syntax and semantics are identical to the kernel parameter with the same
name. For example, for kvmtool, --earlycon=uart,mmio,0x1000000 will set the
correct UART address. Specifying this option will overwrite the UART
address set by --vmm.

At the moment, the UART type and register width parameters are ignored
since both qemu's and kvmtool's UART emulation use the same offset for the
TX register and no other registers are used by kvm-unit-tests, but the
parameters will become relevant once EFI support is added.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
Besides working with current versions of kvmtool, this will also make early
console work if the user specifies a custom memory layout [1] (patches are
old, but I plan to pick them up at some point in the future).

Changes in v3:
* Switched to using IFS and read instead of cut.
* Fixed typo in option description.
* Added check that $addr is a valid number.

Changes in v2:
* kvmtool patches were merged, so I reworked the commit message to point to
  the corresponding kvmtool commit.
* Restricted pl011 register size to 32 bits, as per Arm Base System
  Architecture 1.0 (DEN0094A), and to match Linux.
* Reworked the way the fields are extracted to make it more precise
  (without the -s argument, the entire string is echo'ed when no delimiter
  is found).
* The changes are not trivial, so I dropped Drew's Reviewed-by.

[1] https://lore.kernel.org/kvm/1569245722-23375-1-git-send-email-alexandru.elisei@arm.com/

 configure | 53 +++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 53 insertions(+)

```
#### [PATCH] KVM: x86: Remove unused variable rc
##### From: Jiapeng Chong <jiapeng.chong@linux.alibaba.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jiapeng Chong <jiapeng.chong@linux.alibaba.com>
X-Patchwork-Id: 12150417
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 81DE1C433DB
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 08:54:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4255164F40
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 08:54:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229745AbhCSIxx (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Mar 2021 04:53:53 -0400
Received: from out30-56.freemail.mail.aliyun.com ([115.124.30.56]:42757 "EHLO
        out30-56.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229624AbhCSIxV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Mar 2021 04:53:21 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R701e4;CH=green;DM=||false|;DS=||;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e04420;MF=jiapeng.chong@linux.alibaba.com;NM=1;PH=DS;RN=14;SR=0;TI=SMTPD_---0USZNPTU_1616143992;
Received: from
 j63c13417.sqa.eu95.tbsite.net(mailfrom:jiapeng.chong@linux.alibaba.com
 fp:SMTPD_---0USZNPTU_1616143992)
          by smtp.aliyun-inc.com(127.0.0.1);
          Fri, 19 Mar 2021 16:53:18 +0800
From: Jiapeng Chong <jiapeng.chong@linux.alibaba.com>
To: pbonzini@redhat.com
Cc: seanjc@google.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, tglx@linutronix.de,
        mingo@redhat.com, bp@alien8.de, x86@kernel.org, hpa@zytor.com,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Jiapeng Chong <jiapeng.chong@linux.alibaba.com>
Subject: [PATCH] KVM: x86: Remove unused variable rc
Date: Fri, 19 Mar 2021 16:53:12 +0800
Message-Id: 
 <1616143992-30228-1-git-send-email-jiapeng.chong@linux.alibaba.com>
X-Mailer: git-send-email 1.8.3.1
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the following coccicheck warnings:

./arch/x86/kvm/emulate.c:4985:5-7: Unneeded variable: "rc". Return
"X86EMUL_CONTINUE" on line 5019.

Reported-by: Abaci Robot <abaci@linux.alibaba.com>
Signed-off-by: Jiapeng Chong <jiapeng.chong@linux.alibaba.com>
---
 arch/x86/kvm/emulate.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH 1/4] arm/arm64: Avoid calling cpumask_test_cpu for CPUs above nr_cpu
##### From: Nikos Nikoleris <nikos.nikoleris@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Nikos Nikoleris <nikos.nikoleris@arm.com>
X-Patchwork-Id: 12150953
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 493DEC43381
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 12:25:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 230BF64F78
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 12:25:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229965AbhCSMY7 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Mar 2021 08:24:59 -0400
Received: from foss.arm.com ([217.140.110.172]:48404 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S230260AbhCSMYc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 19 Mar 2021 08:24:32 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 413DB101E;
        Fri, 19 Mar 2021 05:24:32 -0700 (PDT)
Received: from localhost.localdomain (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 7E13D3F70D;
        Fri, 19 Mar 2021 05:24:31 -0700 (PDT)
From: Nikos Nikoleris <nikos.nikoleris@arm.com>
To: kvm@vger.kernel.org
Cc: drjones@redhat.com, alexandru.elisei@arm.com,
        Nikos Nikoleris <nikos.nikoleris@arm.com>
Subject: [kvm-unit-tests PATCH 1/4] arm/arm64: Avoid calling cpumask_test_cpu
 for CPUs above nr_cpu
Date: Fri, 19 Mar 2021 12:24:11 +0000
Message-Id: <20210319122414.129364-2-nikos.nikoleris@arm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210319122414.129364-1-nikos.nikoleris@arm.com>
References: <20210319122414.129364-1-nikos.nikoleris@arm.com>
MIME-Version: 1.0
X-ARM-No-Footer: FoSSMail
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Nikos Nikoleris <nikos.nikoleris@arm.com>
---
 lib/arm/asm/cpumask.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v1 1/2] s390/kvm: split kvm_s390_real_to_abs
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12151795
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C9074C433DB
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 19:34:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7FDED6197F
	for <kvm@archiver.kernel.org>; Fri, 19 Mar 2021 19:34:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231167AbhCSTeW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 19 Mar 2021 15:34:22 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:10302 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230484AbhCSTeC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 19 Mar 2021 15:34:02 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 12JJXZeS163337;
        Fri, 19 Mar 2021 15:34:02 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=EL0EXsKdn+CdnE+hMLx4Kn1Qd6h/HPL7TktJ9faigO8=;
 b=VKky4RZmsxfliRmKcwXy7F7ujTPFAoGO3EOqPH/IwpQxtH0ozTsb1Rd+Z7nrSF2POpYT
 U1/4n9phA3jYIHKwoNVvwAESYOGHcFEgI7K8JPZYXOWM3NbzueNSgs9Skkp06+SFC/P7
 c+hZprAIXgz48TQhiMkS7972XTAI/VYqbaKe3/FH3DRdH7c4z6eD7+aOoYRWGf+CKZUH
 odoYBti19bdcIHVBvJfSB1y93gczC66HVycLtVouU1ggGk46yCV6OtO25KJ08sB8LlUz
 NHiPYFu8kVB0agQ8nihMc9iMxv66LZPH7WDw03X7lNeh9k4OV+fSRYbaKmyDPUURDqff pw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37c2vqn2gs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 19 Mar 2021 15:34:01 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 12JJXwH2164925;
        Fri, 19 Mar 2021 15:34:01 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37c2vqn2g6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 19 Mar 2021 15:34:01 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 12JJWWuu018953;
        Fri, 19 Mar 2021 19:33:59 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma03fra.de.ibm.com with ESMTP id 378n18b649-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 19 Mar 2021 19:33:58 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 12JJXthC35062160
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 19 Mar 2021 19:33:55 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BFB05A4054;
        Fri, 19 Mar 2021 19:33:55 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5A596A405F;
        Fri, 19 Mar 2021 19:33:55 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.2.56])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 19 Mar 2021 19:33:55 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
        cohuck@redhat.com, kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        stable@vger.kernel.org
Subject: [PATCH v1 1/2] s390/kvm: split kvm_s390_real_to_abs
Date: Fri, 19 Mar 2021 20:33:53 +0100
Message-Id: <20210319193354.399587-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20210319193354.399587-1-imbrenda@linux.ibm.com>
References: <20210319193354.399587-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-03-19_10:2021-03-19,2021-03-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 priorityscore=1501 impostorscore=0 phishscore=0 mlxlogscore=974 mlxscore=0
 bulkscore=0 suspectscore=0 spamscore=0 clxscore=1015 adultscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2103190130
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A new function _kvm_s390_real_to_abs will apply prefixing to a real address
with a given prefix value.

The old kvm_s390_real_to_abs becomes now a wrapper around the new function.

This is needed to avoid code duplication in vSIE.

Cc: stable@vger.kernel.org
Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 arch/s390/kvm/gaccess.h | 23 +++++++++++++++++------
 1 file changed, 17 insertions(+), 6 deletions(-)

```
