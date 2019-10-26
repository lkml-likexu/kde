#### [GIT PULL] KVM changes for Linux 5.4-rc5
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11212115
Return-Path: <SRS0=InyR=YS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ECBDE139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 11:46:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C8DEA21D71
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 11:46:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="MweLNAF2"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2502063AbfJYLqE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Oct 2019 07:46:04 -0400
Received: from mail-wm1-f66.google.com ([209.85.128.66]:52392 "EHLO
        mail-wm1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730088AbfJYLqE (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Oct 2019 07:46:04 -0400
Received: by mail-wm1-f66.google.com with SMTP id p21so1785710wmg.2;
        Fri, 25 Oct 2019 04:46:02 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=ef0+hHhWKCL6Ca0t5L5+DnFrjs6xNw6+Odbfva8qwPs=;
        b=MweLNAF2NZ7iEpk6wMj4PgBgpG0sqWOQGUnZ5/A9SGuzDzfVMXAN5EOmXw054lnilC
         JpvmjXsT/o5JUWHkilzQ2uVNbpRohLVa7vT3MLWYjKbzLw0zfei+xFbAfcpkzUMVHcNT
         1yuGX4/2mATN/KrU26ulSjsIbQhVgWDlKT89ksOjIDjRWMF97PGryx1U/4GKJcCWlN3Q
         FEJIHXFkbTrYjPv+N/bdFEOW1ghAqmjl+ZUX4kwlH3mBK5/tH9GhXQEFjxOsG3Uf7DF1
         8rliUCEFFCibiUJens7WliBKOngilDkc+PKmVWT4F1ICYgPD7EDjpsafY4vWcdZi+n9Z
         dtiw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=ef0+hHhWKCL6Ca0t5L5+DnFrjs6xNw6+Odbfva8qwPs=;
        b=HjcyKQ93uuk7clM+wMechRaJcC2vhSYsVuJ1ZqtCvh6g9dkz/QiXDvvezF6KqLtEaz
         N2zugzszywtnFlti8woXMZhdm7+o4bE5Gb45ErydCgjiGDlAWvq75PxJMhtrYTUOcoQy
         vmT3y/fzzQhiQvUuo9mr/joR0zH+wCYK/3jMAeOlIc5M/aZtzsFbrLsE3nBINXMJZCKo
         mdnhqwxtD+MiP01iT/N/+Q2sTaHI1ewLGoUYwmJcOV/Yc9HEnxV/4ktEZvtuvaIosegG
         LPu0ulnzKgw1A2tU/ldI6KESu2R6uJL2Ul5LO5rrCRZS7QT4SWXmDgWjq4Az2OUE5jr0
         rIzw==
X-Gm-Message-State: APjAAAVQo8HIMTdum7YuiiPOPiEoDpCAe3ds1wunF7VKuf3cWZ0fYQZN
        qaFpGRaZARq4eiO5pz21LNo=
X-Google-Smtp-Source: 
 APXvYqxyiXMNCEwujviBcaGWHHKgI5g4AoZaYE7MQ718Qwr4MDjEGH3/HrmtiPExX3WW7QD0UVNFjg==
X-Received: by 2002:a1c:f305:: with SMTP id q5mr3127071wmq.137.1572003961887;
        Fri, 25 Oct 2019 04:46:01 -0700 (PDT)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 g69sm1881335wme.31.2019.10.25.04.46.00
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Fri, 25 Oct 2019 04:46:01 -0700 (PDT)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, rkrcmar@redhat.com,
        kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.4-rc5
Date: Fri, 25 Oct 2019 13:45:59 +0200
Message-Id: <1572003959-43063-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 3b7c59a1950c75f2c0152e5a9cd77675b09233d6:

  Merge tag 'pinctrl-v5.4-2' of git://git.kernel.org/pub/scm/linux/kernel/git/linusw/linux-pinctrl (2019-10-22 06:40:07 -0400)

are available in the git repository at:


  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 671ddc700fd08b94967b1e2a937020e30c838609:

  KVM: nVMX: Don't leak L1 MMIO regions to L2 (2019-10-22 19:04:40 +0200)

----------------------------------------------------------------
Bugfixes for ARM, PPC and x86, plus selftest improvements.

----------------------------------------------------------------
Greg Kurz (1):
      KVM: PPC: Book3S HV: XIVE: Ensure VP isn't already in use

Jim Mattson (2):
      kvm: x86: Expose RDPID in KVM_GET_SUPPORTED_CPUID
      KVM: nVMX: Don't leak L1 MMIO regions to L2

Liran Alon (1):
      KVM: VMX: Remove specialized handling of unexpected exit-reasons

Marc Zyngier (4):
      KVM: arm64: pmu: Fix cycle counter truncation
      arm64: KVM: Handle PMCR_EL0.LC as RES1 on pure AArch64 systems
      KVM: arm64: pmu: Set the CHAINED attribute before creating the in-kernel event
      KVM: arm64: pmu: Reset sample period on overflow handling

Miaohe Lin (1):
      KVM: SVM: Fix potential wrong physical id in avic_handle_ldr_update

Paolo Bonzini (3):
      kvm: clear kvmclock MSR on reset
      Merge tag 'kvmarm-fixes-5.4-2' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD
      Merge tag 'kvm-ppc-fixes-5.4-1' of git://git.kernel.org/.../paulus/powerpc into HEAD

Vitaly Kuznetsov (5):
      selftests: kvm: synchronize .gitignore to Makefile
      selftests: kvm: vmx_set_nested_state_test: don't check for VMX support twice
      selftests: kvm: consolidate VMX support checks
      selftests: kvm: vmx_dirty_log_test: skip the test when VMX is not supported
      selftests: kvm: fix sync_regs_test with newer gccs

Wanpeng Li (1):
      KVM: Don't shrink/grow vCPU halt_poll_ns if host side polling is disabled

kbuild test robot (1):
      KVM: x86: fix bugon.cocci warnings

 arch/arm64/kvm/sys_regs.c                          |  4 ++
 arch/powerpc/kvm/book3s_xive.c                     | 24 +++++---
 arch/powerpc/kvm/book3s_xive.h                     | 12 ++++
 arch/powerpc/kvm/book3s_xive_native.c              |  6 +-
 arch/x86/include/asm/kvm_host.h                    |  2 +-
 arch/x86/kvm/cpuid.c                               |  2 +-
 arch/x86/kvm/lapic.c                               |  5 --
 arch/x86/kvm/lapic.h                               |  5 ++
 arch/x86/kvm/svm.c                                 |  6 +-
 arch/x86/kvm/vmx/nested.c                          | 64 ++++++++++++----------
 arch/x86/kvm/vmx/nested.h                          | 13 ++++-
 arch/x86/kvm/vmx/vmx.c                             | 12 ----
 arch/x86/kvm/x86.c                                 | 19 ++++---
 tools/testing/selftests/kvm/.gitignore             |  2 +
 tools/testing/selftests/kvm/include/x86_64/vmx.h   |  2 +
 tools/testing/selftests/kvm/lib/x86_64/vmx.c       | 10 ++++
 .../testing/selftests/kvm/x86_64/sync_regs_test.c  | 21 +++----
 .../kvm/x86_64/vmx_close_while_nested_test.c       |  6 +-
 .../selftests/kvm/x86_64/vmx_dirty_log_test.c      |  2 +
 .../kvm/x86_64/vmx_set_nested_state_test.c         | 13 +----
 .../selftests/kvm/x86_64/vmx_tsc_adjust_test.c     |  6 +-
 virt/kvm/arm/pmu.c                                 | 48 +++++++++++-----
 virt/kvm/kvm_main.c                                | 29 +++++-----
 23 files changed, 186 insertions(+), 127 deletions(-)
```
#### [PATCH] KVM: avoid unnecessary bitmap clear ops
##### From: Miaohe Lin <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Miaohe Lin <linmiaohe@huawei.com>
X-Patchwork-Id: 11211209
Return-Path: <SRS0=InyR=YS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0F7A3139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 02:24:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E9C4521928
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 02:24:22 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389885AbfJYCYT (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 22:24:19 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:5175 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728416AbfJYCYT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 22:24:19 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 89FA6803B9A47E74ED00;
        Fri, 25 Oct 2019 10:24:16 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.439.0; Fri, 25 Oct 2019
 10:24:07 +0800
From: Miaohe Lin <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <x86@kernel.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <linmiaohe@huawei.com>
Subject: [PATCH] KVM: avoid unnecessary bitmap clear ops
Date: Fri, 25 Oct 2019 10:24:41 +0800
Message-ID: <1571970281-20083-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When set one bit in bitmap, there is no need to
clear it before.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/svm.c | 3 ++-
 arch/x86/kvm/x86.c | 3 ++-
 2 files changed, 4 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH 1/2] x86: smap: Use correct reg to pass a parameter
##### From: Chenyi Qiang <chenyi.qiang@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chenyi Qiang <chenyi.qiang@intel.com>
X-Patchwork-Id: 11211771
Return-Path: <SRS0=InyR=YS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AC6F013B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 09:03:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 94EC821D81
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 09:03:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2408659AbfJYJD1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Oct 2019 05:03:27 -0400
Received: from mga11.intel.com ([192.55.52.93]:37164 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2408378AbfJYJD1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Oct 2019 05:03:27 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 25 Oct 2019 02:03:27 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,228,1569308400";
   d="scan'208";a="202556658"
Received: from chenyi-pc.sh.intel.com ([10.239.159.72])
  by orsmga006.jf.intel.com with ESMTP; 25 Oct 2019 02:03:26 -0700
From: Chenyi Qiang <chenyi.qiang@intel.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Subject: [kvm-unit-tests PATCH 1/2] x86: smap: Use correct reg to pass a
 parameter
Date: Fri, 25 Oct 2019 17:03:28 +0800
Message-Id: <20191025090329.11679-1-chenyi.qiang@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The first parameter is passed using rdi in x86_64.

Signed-off-by: Chenyi Qiang <chenyi.qiang@intel.com>
---
 x86/smap.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: Fix the register order to match struct regs
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 11212711
Return-Path: <SRS0=InyR=YS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C538F112C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 17:01:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A0D3521E6F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 17:01:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="HvfRaXXB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2409574AbfJYRBd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Oct 2019 13:01:33 -0400
Received: from mail-pf1-f202.google.com ([209.85.210.202]:33741 "EHLO
        mail-pf1-f202.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2407149AbfJYRB1 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Oct 2019 13:01:27 -0400
Received: by mail-pf1-f202.google.com with SMTP id z4so2384062pfn.0
        for <kvm@vger.kernel.org>; Fri, 25 Oct 2019 10:01:27 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=a6D0LvDSWvcPBISgGIo9u1LrVZKZJkW1is0FU9Md0OY=;
        b=HvfRaXXBnGrJSskwO0aa3yK7r+fVk0GhnUvg8UuwljtMvXv/KUagkTPmoVgEVUkq9Q
         sRYAcnWBSCQkCNI4xtJsuZ47zKbDmg+Ql2+80FxQjKqH1gDRubxox973Olwc0pzVWeOc
         4hfk0I+7tw7P+JyaINX52bPHkJRjzvaQZiG5pz6Sza/ZzR/l+/h8twyra8ntCwfu0Ai6
         wbK7aOTcLUZUTYPLQVsYMi63Z3Y2L4Z31NBSwo3UJNzELEpy0FOXP+Kl/mfl8oQqaEPQ
         XaBOtjkeW04gFuxGfUxC3LWNTFaGGspYJM6BavaDn6ssdpW0CRra8zrI7Dob2/HVLFpf
         E/UA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=a6D0LvDSWvcPBISgGIo9u1LrVZKZJkW1is0FU9Md0OY=;
        b=rxpKOy1r6R4aTb4PSDBOMkVoIB4VJuTsqppusIg4ExfTzlr7T4Efng/IOO+qBMValT
         NVqEOwalwzW/AkOOz+LoIbfSaFfoM86Ke/Y7IyyTYVmVGddHrf+ZC0LB1O/Zuh6ZIPVn
         P3nibn7VSsOXmXcN87Ibvt1diSa5LAgyJpRjvM7qPTZtvK28uCiyM2mGxDGnFDzyjuDD
         Bst4fCpEJTfClyDlhlRer7FyiXojutQx5lp7XAngqVa2vvCVMVf+MssAAT9tlWH9BH7Y
         OEnzJX/s/RDz7i/NWxEJfLnrskR2Q9FOFcpCVUiX1X77fqFc0zNUl0b8ZY4IBzilM9jg
         p/fQ==
X-Gm-Message-State: APjAAAWb6MXq1Io+EvQu2EsMYpPZMKOXlXgVZjtve+E+jgSIu9Y0Yxto
        xroaTpcpzh53VsVPlJve5o4qG3yjoXZC2GIs9g0RNsDfkXuqvUZsn1M5uPFGJLoH80WFSmn8plU
        YU4idGGT8Ox25El7SzDOLADbaqcEDOfmIySTdN7SL8d26uGahXLMDOIKzHHj+NV7M/dQe
X-Google-Smtp-Source: 
 APXvYqzM+PZUsiUM0XEyTdAz47yojmWnA/U//ZUx038MVrVrkkLbzob+ZLq40EC7C0Er45FGIR1DW5A0X5YxwzuU
X-Received: by 2002:a63:28f:: with SMTP id 137mr2506003pgc.301.1572022886509;
 Fri, 25 Oct 2019 10:01:26 -0700 (PDT)
Date: Fri, 25 Oct 2019 10:00:57 -0700
Message-Id: <20191025170056.109755-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.24.0.rc0.303.g954a862665-goog
Subject: [kvm-unit-tests PATCH] x86: Fix the register order to match struct
 regs
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: Aaron Lewis <aaronlewis@google.com>,
        Jim Mattson <jmattson@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix the order the registers show up in SAVE_GPR and SAVE_GPR_C to ensure
the correct registers get the correct values.  Previously, the registers
were being written to (and read from) the wrong fields.

Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
---
 x86/vmx.h | 12 ++++++------
 1 file changed, 6 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86: get rid of odd out jump label in pdptrs_changed
##### From: Miaohe Lin <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Miaohe Lin <linmiaohe@huawei.com>
X-Patchwork-Id: 11211199
Return-Path: <SRS0=InyR=YS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4047813BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 02:01:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1C50721929
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 02:01:02 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389614AbfJYCAy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 22:00:54 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:49186 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725860AbfJYCAy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 22:00:54 -0400
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id F0C5DB9DC0999ECE50E2;
        Fri, 25 Oct 2019 10:00:51 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.439.0; Fri, 25 Oct 2019
 10:00:45 +0800
From: Miaohe Lin <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <x86@kernel.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <linmiaohe@huawei.com>
Subject: [PATCH] KVM: x86: get rid of odd out jump label in pdptrs_changed
Date: Fri, 25 Oct 2019 10:01:18 +0800
Message-ID: <1571968878-10437-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The odd out jump label is really not needed. Get rid of
it by check r >= 0.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/x86.c | 7 +++----
 1 file changed, 3 insertions(+), 4 deletions(-)

```
#### linux-next: manual merge of the kvm-ppc tree with the kvm-arm tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Rothwell <sfr@canb.auug.org.au>
X-Patchwork-Id: 11211197
Return-Path: <SRS0=InyR=YS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2E07E14ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 01:55:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0C71F206DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 01:55:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=canb.auug.org.au header.i=@canb.auug.org.au
 header.b="rHSq/xld"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389552AbfJYBy7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 24 Oct 2019 21:54:59 -0400
Received: from ozlabs.org ([203.11.71.1]:39295 "EHLO ozlabs.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2389488AbfJYBy4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 24 Oct 2019 21:54:56 -0400
Received: from authenticated.ozlabs.org (localhost [127.0.0.1])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits)
         key-exchange ECDHE (P-256) server-signature RSA-PSS (4096 bits)
 server-digest SHA256)
        (No client certificate requested)
        by mail.ozlabs.org (Postfix) with ESMTPSA id 46znHK2bcBz9sP3;
        Fri, 25 Oct 2019 12:54:53 +1100 (AEDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=canb.auug.org.au;
        s=201702; t=1571968493;
        bh=7C+Sf4WcmsYMuwrmETgFQmmDGqQheurLBFa+StuqxPg=;
        h=Date:From:To:Cc:Subject:From;
        b=rHSq/xldZ2Ia1Ech2xZeEfzwY2F8dj0M6TCPtPrHcuUHpRyPvxiqpGn0e/pS/wG34
         IFKmqbfIXfio3vs/ry0EZ0NK/gUkZRs+FX2HDTXbn3oy4S1IJnby/MMo75lGAz9pUQ
         dC3pZu+po47WyqPVvb+9GeF45EwpehhDBnIu5I9r0v8iMB+Jy8gtmK14tyhzU3sZ3Q
         0yx40B71AAoHweOlQSGk4wTAflEyqVdxV4H19AJixQ5YSDMyUeOLs8BJcZ0FxcCgtH
         jn/z+qKh+tCSjxgK3D9Zb7LfoqzC5PG0zaGBbBAlZFf8HeFddFeZXZaxse1/WHCgRR
         NmgXBAMvezemw==
Date: Fri, 25 Oct 2019 12:54:36 +1100
From: Stephen Rothwell <sfr@canb.auug.org.au>
To: Paul Mackerras <paulus@ozlabs.org>,
        Christoffer Dall <cdall@cs.columbia.edu>,
        Marc Zyngier <marc.zyngier@arm.com>
Cc: Linux Next Mailing List <linux-next@vger.kernel.org>,
 Linux Kernel Mailing List <linux-kernel@vger.kernel.org>,
 Fabiano Rosas <farosas@linux.ibm.com>, Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 KVM <kvm@vger.kernel.org>
Subject: linux-next: manual merge of the kvm-ppc tree with the kvm-arm tree
Message-ID: <20191025125436.6c85dbfe@canb.auug.org.au>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi all,

Today's linux-next merge of the kvm-ppc tree got a conflict in:

  include/uapi/linux/kvm.h

between commits:

  c726200dd106 ("KVM: arm/arm64: Allow reporting non-ISV data aborts to userspace")
  da345174ceca ("KVM: arm/arm64: Allow user injection of external data aborts")

from the kvm-arm tree and commit:

  1a9167a214f5 ("KVM: PPC: Report single stepping capability")

from the kvm-ppc tree.

I fixed it up (see below) and can carry the fix as necessary. This
is now fixed as far as linux-next is concerned, but any non trivial
conflicts should be mentioned to your upstream maintainer when your tree
is submitted for merging.  You may also want to consider cooperating
with the maintainer of the conflicting tree to minimise any particularly
complex conflicts.

```
#### [RFC v2] KVM: s390: protvirt: Secure memory is not mergeable
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11211683
Return-Path: <SRS0=InyR=YS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AACD9139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 08:25:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 886DF21929
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 08:25:03 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2437963AbfJYIZC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Oct 2019 04:25:02 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:16740 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2437952AbfJYIZC (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 25 Oct 2019 04:25:02 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9P87IDU094301
        for <kvm@vger.kernel.org>; Fri, 25 Oct 2019 04:25:01 -0400
Received: from e06smtp05.uk.ibm.com (e06smtp05.uk.ibm.com [195.75.94.101])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vuw339056-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 25 Oct 2019 04:25:00 -0400
Received: from localhost
        by e06smtp05.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Fri, 25 Oct 2019 09:24:58 +0100
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp05.uk.ibm.com (192.168.101.135) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 25 Oct 2019 09:24:56 +0100
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9P8Osq147579140
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 25 Oct 2019 08:24:54 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 65FDA11C04A;
        Fri, 25 Oct 2019 08:24:54 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0B81A11C050;
        Fri, 25 Oct 2019 08:24:52 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.50.181])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri, 25 Oct 2019 08:24:51 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, imbrenda@linux.ibm.com,
        mihajlov@linux.ibm.com, mimu@linux.ibm.com, cohuck@redhat.com,
        gor@linux.ibm.com, frankja@linux.ibm.com
Subject: [RFC v2] KVM: s390: protvirt: Secure memory is not mergeable
Date: Fri, 25 Oct 2019 04:24:46 -0400
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20191024114059.102802-8-frankja@linux.ibm.com>
References: <20191024114059.102802-8-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19102508-0020-0000-0000-0000037E5677
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19102508-0021-0000-0000-000021D4A185
Message-Id: <20191025082446.754-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-25_05:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=612 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910250078
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KSM will not work on secure pages, because when the kernel reads a
secure page, it will be encrypted and hence no two pages will look the
same.

Let's mark the guest pages as unmergeable when we transition to secure
mode.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/include/asm/gmap.h |  1 +
 arch/s390/kvm/kvm-s390.c     |  6 ++++++
 arch/s390/mm/gmap.c          | 32 +++++++++++++++++++++-----------
 3 files changed, 28 insertions(+), 11 deletions(-)

```
#### [kvm-unit-tests PATCH v2 1/5] s390x: remove redundant defines
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11212733
Return-Path: <SRS0=InyR=YS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4ECA1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 17:06:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BBD9720867
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 17:06:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2505774AbfJYRGn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Oct 2019 13:06:43 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:8556 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S2409745AbfJYRGm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 25 Oct 2019 13:06:42 -0400
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x9PH3ftY081402
        for <kvm@vger.kernel.org>; Fri, 25 Oct 2019 13:06:41 -0400
Received: from e06smtp04.uk.ibm.com (e06smtp04.uk.ibm.com [195.75.94.100])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2vv4ax9qhf-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 25 Oct 2019 13:06:41 -0400
Received: from localhost
        by e06smtp04.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <imbrenda@linux.ibm.com>;
        Fri, 25 Oct 2019 18:06:40 +0100
Received: from b06cxnps3075.portsmouth.uk.ibm.com (9.149.109.195)
        by e06smtp04.uk.ibm.com (192.168.101.134) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Fri, 25 Oct 2019 18:06:37 +0100
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps3075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x9PH6Z8P61276302
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 25 Oct 2019 17:06:35 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A6FB2A404D;
        Fri, 25 Oct 2019 17:06:35 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6F2A6A4040;
        Fri, 25 Oct 2019 17:06:35 +0000 (GMT)
Received: from p-imbrenda.boeblingen.de.ibm.com (unknown [9.152.224.39])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Fri, 25 Oct 2019 17:06:35 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, thuth@redhat.com, david@redhat.com,
        borntraeger@de.ibm.com, frankja@linux.ibm.com
Subject: [kvm-unit-tests PATCH v2 1/5] s390x: remove redundant defines
Date: Fri, 25 Oct 2019 19:06:30 +0200
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1572023194-14370-1-git-send-email-imbrenda@linux.ibm.com>
References: <1572023194-14370-1-git-send-email-imbrenda@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19102517-0016-0000-0000-000002BD9B82
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19102517-0017-0000-0000-0000331EE65B
Message-Id: <1572023194-14370-2-git-send-email-imbrenda@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-10-25_09:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=936 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1910250157
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/sclp.h | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH v2] KVM: x86: get rid of odd out jump label in pdptrs_changed
##### From: Miaohe Lin <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Miaohe Lin <linmiaohe@huawei.com>
X-Patchwork-Id: 11211961
Return-Path: <SRS0=InyR=YS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DF7EC13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 10:54:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C4CB621D7F
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 25 Oct 2019 10:54:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2502707AbfJYKyR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 25 Oct 2019 06:54:17 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:5186 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2502594AbfJYKyR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 25 Oct 2019 06:54:17 -0400
Received: from DGGEMS407-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 8D4AF84C3F8D4F971006;
        Fri, 25 Oct 2019 18:54:14 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS407-HUB.china.huawei.com
 (10.3.19.207) with Microsoft SMTP Server id 14.3.439.0; Fri, 25 Oct 2019
 18:54:07 +0800
From: Miaohe Lin <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <x86@kernel.org>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <linmiaohe@huawei.com>
Subject: [PATCH v2] KVM: x86: get rid of odd out jump label in pdptrs_changed
Date: Fri, 25 Oct 2019 18:54:34 +0800
Message-ID: <1572000874-28259-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The odd out jump label is really not needed. Get rid of
it by return true directly while r < 0 as suggested by
Paolo. This further lead to var changed being unused.
Remove it too.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/x86.c | 7 ++-----
 1 file changed, 2 insertions(+), 5 deletions(-)

```
