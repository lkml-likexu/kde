#### [GIT PULL v2] KVM changes for Linux 5.6-rc2
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11381349
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C060E1580
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 21:48:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8C4802168B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 21:48:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="f0fPp0s3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728216AbgBMVsz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 16:48:55 -0500
Received: from mail-wm1-f67.google.com ([209.85.128.67]:52646 "EHLO
        mail-wm1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727873AbgBMVsz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 16:48:55 -0500
Received: by mail-wm1-f67.google.com with SMTP id p9so7911613wmc.2;
        Thu, 13 Feb 2020 13:48:53 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=zF1tlZSRa/LFYwLFggJhr6dooSiaUziOFm+pJFx4Zd0=;
        b=f0fPp0s3NXmUUEAw8xyR9iLbUTCkbZAv8x0jtym8E7TomkJp/GK9Xmpg2uOnmko0Ts
         OOPhayg/leez3t/lZ+FS22qW/QsbJsjG/5NVyQx1n8ElVfynT3PS8dHDz/bGHRwzlOIb
         J/GkGvLdr/6CN7LDy9IZd60gNzuLyEnwW3+t4VdR073+UYzp1g7tsiE2lgNAe8p74JOR
         n/upBrrJxsg7rT9l3OKFBDIps7D5Nqx+jpcPQq+SVethfyrpLV0h01D0G2XgerH2FAGO
         6zZNvJHnwZwr/KteczOUhTlM9ZX5qsilKEQsSzjw70/Ta8L6+HBSOo0pnguaqZM4jgqu
         8vDQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=zF1tlZSRa/LFYwLFggJhr6dooSiaUziOFm+pJFx4Zd0=;
        b=S4VOP7jz4pDTHasALqdpKDfyiZBsNwljDHNqwfdSRjPFggJvJ6rCTBw7Ii6GEu9mya
         RjVrid6AME6niazoaB2kdRpCJOdkJmSw3KTf+iOylz8DkXru4R7mKpHd2BAVKiTkif3b
         1zVesT9agZgB5C5cqXkZoMOrg9BOFE4N52SjPAfHzforne/rACYvsiPNjkPf3BtWkA13
         +Vd1/cT6W3/ciAmLM26oVylQuGCUY4m8uWdb3GPtW2uXP/ogBx3uE8qMWK86WfcAwd5C
         WEil+CfvsOBjhejjB6rul6pzrNzi1u5C77hMS88+SdYOUirZhSo2p6OBLgnJMxWxybAn
         3cdw==
X-Gm-Message-State: APjAAAXyIiotb6ApOQjvSzLBVcWNFm4QF08pC+CrrCyQBo8ReJitaqnk
        9S0iimAtyBiSTfD3MoWDeOHd17hY
X-Google-Smtp-Source: 
 APXvYqxEjvuuR4PPy3Z8hW9AJXtIst9ksHJVkuAH7cYHIYq8QN5Y/07nJPJ8ISIyGfqfFywvJWTjDw==
X-Received: by 2002:a7b:c084:: with SMTP id r4mr89084wmh.99.1581630532373;
        Thu, 13 Feb 2020 13:48:52 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 s23sm4553324wra.15.2020.02.13.13.48.51
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 13 Feb 2020 13:48:51 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL v2] KVM changes for Linux 5.6-rc2
Date: Thu, 13 Feb 2020 22:48:49 +0100
Message-Id: <1581630529-5236-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit bb6d3fb354c5ee8d6bde2d576eb7220ea09862b9:

  Linux 5.6-rc1 (2020-02-09 16:08:48 -0800)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 120881b9e888689cbdb90a1dd1689684d8bc95f3:

  docs: virt: guest-halt-polling.txt convert to ReST (2020-02-12 20:10:08 +0100)

----------------------------------------------------------------
Bugfixes and improvements to selftests.  On top of this, Mauro converted the
KVM documentation to rst format, which was very welcome.

----------------------------------------------------------------
Eric Auger (4):
      selftests: KVM: Replace get_{gdt,idt}_base() by get_{gdt,idt}()
      selftests: KVM: AMD Nested test infrastructure
      selftests: KVM: SVM: Add vmcall test
      selftests: KVM: Remove unused x86_register enum

Marc Zyngier (1):
      KVM: Disable preemption in kvm_get_running_vcpu()

Mauro Carvalho Chehab (28):
      docs: kvm: add arm/pvtime.rst to index.rst
      docs: virt: convert UML documentation to ReST
      docs: virt: user_mode_linux.rst: update compiling instructions
      docs: virt: user_mode_linux.rst: fix URL references
      docs: virt: convert halt-polling.txt to ReST format
      docs: virt: Convert msr.txt to ReST format
      docs: kvm: devices/arm-vgic-its.txt to ReST format
      docs: kvm: devices/arm-vgit-v3.txt to ReST
      docs: kvm: convert devices/arm-vgit.txt to ReST
      docs: kvm: convert devices/mpic.txt to ReST
      docs: kvm: convert devices/s390_flic.txt to ReST
      docs: kvm: convert devices/vcpu.txt to ReST
      docs: kvm: convert devices/vfio.txt to ReST
      docs: kvm: convert devices/vm.txt to ReST
      docs: kvm: convert devices/xics.txt to ReST
      docs: kvm: convert devices/xive.txt to ReST
      docs: kvm: Convert api.txt to ReST format
      docs: kvm: convert arm/hyp-abi.txt to ReST
      docs: kvm: arm/psci.txt: convert to ReST
      docs: kvm: Convert hypercalls.txt to ReST format
      docs: kvm: Convert locking.txt to ReST format
      docs: kvm: Convert mmu.txt to ReST format
      docs: kvm: Convert nested-vmx.txt to ReST format
      docs: kvm: Convert ppc-pv.txt to ReST format
      docs: kvm: Convert s390-diag.txt to ReST format
      docs: kvm: Convert timekeeping.txt to ReST format
      docs: kvm: review-checklist.txt: rename to ReST
      docs: virt: guest-halt-polling.txt convert to ReST

Miaohe Lin (3):
      KVM: x86: remove duplicated KVM_REQ_EVENT request
      KVM: apic: reuse smp_wmb() in kvm_make_request()
      KVM: nVMX: Fix some comment typos and coding style

Oliver Upton (3):
      KVM: x86: Mask off reserved bit from #DB exception payload
      KVM: nVMX: Handle pending #DB when injecting INIT VM-exit
      KVM: x86: Deliver exception payload on KVM_GET_VCPU_EVENTS

Paolo Bonzini (2):
      KVM: x86: do not reset microcode version on INIT or RESET
      KVM: x86: fix WARN_ON check of an unsigned less than zero

Sean Christopherson (3):
      KVM: x86/mmu: Avoid retpoline on ->page_fault() with TDP
      KVM: nVMX: Use correct root level for nested EPT shadow page tables
      KVM: x86/mmu: Fix struct guest_walker arrays for 5-level paging

 .../guest-halt-polling.rst}                        |   12 +-
 Documentation/virt/index.rst                       |    2 +
 Documentation/virt/kvm/{api.txt => api.rst}        | 3350 ++++++++++++--------
 .../virt/kvm/arm/{hyp-abi.txt => hyp-abi.rst}      |   28 +-
 Documentation/virt/kvm/arm/index.rst               |   12 +
 Documentation/virt/kvm/arm/{psci.txt => psci.rst}  |   46 +-
 .../devices/{arm-vgic-its.txt => arm-vgic-its.rst} |  106 +-
 .../devices/{arm-vgic-v3.txt => arm-vgic-v3.rst}   |  132 +-
 .../kvm/devices/{arm-vgic.txt => arm-vgic.rst}     |   89 +-
 Documentation/virt/kvm/devices/index.rst           |   19 +
 .../virt/kvm/devices/{mpic.txt => mpic.rst}        |   11 +-
 .../kvm/devices/{s390_flic.txt => s390_flic.rst}   |   70 +-
 Documentation/virt/kvm/devices/vcpu.rst            |  114 +
 Documentation/virt/kvm/devices/vcpu.txt            |   76 -
 .../virt/kvm/devices/{vfio.txt => vfio.rst}        |   25 +-
 Documentation/virt/kvm/devices/{vm.txt => vm.rst}  |  206 +-
 .../virt/kvm/devices/{xics.txt => xics.rst}        |   28 +-
 .../virt/kvm/devices/{xive.txt => xive.rst}        |  152 +-
 .../kvm/{halt-polling.txt => halt-polling.rst}     |   90 +-
 .../virt/kvm/{hypercalls.txt => hypercalls.rst}    |  129 +-
 Documentation/virt/kvm/index.rst                   |   16 +
 Documentation/virt/kvm/locking.rst                 |  243 ++
 Documentation/virt/kvm/locking.txt                 |  215 --
 Documentation/virt/kvm/{mmu.txt => mmu.rst}        |   62 +-
 Documentation/virt/kvm/{msr.txt => msr.rst}        |  147 +-
 .../virt/kvm/{nested-vmx.txt => nested-vmx.rst}    |   37 +-
 Documentation/virt/kvm/{ppc-pv.txt => ppc-pv.rst}  |   26 +-
 .../{review-checklist.txt => review-checklist.rst} |    3 +
 .../virt/kvm/{s390-diag.txt => s390-diag.rst}      |   13 +-
 .../virt/kvm/{timekeeping.txt => timekeeping.rst}  |  223 +-
 ...UserModeLinux-HOWTO.txt => user_mode_linux.rst} | 1810 +++++------
 arch/x86/include/asm/kvm_host.h                    |   16 +-
 arch/x86/kvm/lapic.c                               |    3 -
 arch/x86/kvm/mmu.h                                 |   13 +
 arch/x86/kvm/mmu/mmu.c                             |   11 +-
 arch/x86/kvm/mmu/paging_tmpl.h                     |    2 +-
 arch/x86/kvm/svm.c                                 |    2 +-
 arch/x86/kvm/vmx/nested.c                          |   33 +-
 arch/x86/kvm/vmx/vmx.c                             |    5 +-
 arch/x86/kvm/x86.c                                 |   42 +-
 tools/testing/selftests/kvm/Makefile               |    3 +-
 .../selftests/kvm/include/x86_64/processor.h       |   44 +-
 tools/testing/selftests/kvm/include/x86_64/svm.h   |  297 ++
 .../selftests/kvm/include/x86_64/svm_util.h        |   38 +
 tools/testing/selftests/kvm/lib/x86_64/svm.c       |  161 +
 tools/testing/selftests/kvm/lib/x86_64/vmx.c       |    6 +-
 .../testing/selftests/kvm/x86_64/svm_vmcall_test.c |   79 +
 virt/kvm/arm/vgic/vgic-mmio.c                      |   12 -
 virt/kvm/kvm_main.c                                |   16 +-
 49 files changed, 4907 insertions(+), 3368 deletions(-)
 rename Documentation/{virtual/guest-halt-polling.txt => virt/guest-halt-polling.rst} (91%)
 rename Documentation/virt/kvm/{api.txt => api.rst} (71%)
 rename Documentation/virt/kvm/arm/{hyp-abi.txt => hyp-abi.rst} (79%)
 create mode 100644 Documentation/virt/kvm/arm/index.rst
 rename Documentation/virt/kvm/arm/{psci.txt => psci.rst} (60%)
 rename Documentation/virt/kvm/devices/{arm-vgic-its.txt => arm-vgic-its.rst} (71%)
 rename Documentation/virt/kvm/devices/{arm-vgic-v3.txt => arm-vgic-v3.rst} (77%)
 rename Documentation/virt/kvm/devices/{arm-vgic.txt => arm-vgic.rst} (66%)
 create mode 100644 Documentation/virt/kvm/devices/index.rst
 rename Documentation/virt/kvm/devices/{mpic.txt => mpic.rst} (91%)
 rename Documentation/virt/kvm/devices/{s390_flic.txt => s390_flic.rst} (87%)
 create mode 100644 Documentation/virt/kvm/devices/vcpu.rst
 delete mode 100644 Documentation/virt/kvm/devices/vcpu.txt
 rename Documentation/virt/kvm/devices/{vfio.txt => vfio.rst} (72%)
 rename Documentation/virt/kvm/devices/{vm.txt => vm.rst} (61%)
 rename Documentation/virt/kvm/devices/{xics.txt => xics.rst} (84%)
 rename Documentation/virt/kvm/devices/{xive.txt => xive.rst} (62%)
 rename Documentation/virt/kvm/{halt-polling.txt => halt-polling.rst} (64%)
 rename Documentation/virt/kvm/{hypercalls.txt => hypercalls.rst} (55%)
 create mode 100644 Documentation/virt/kvm/locking.rst
 delete mode 100644 Documentation/virt/kvm/locking.txt
 rename Documentation/virt/kvm/{mmu.txt => mmu.rst} (94%)
 rename Documentation/virt/kvm/{msr.txt => msr.rst} (74%)
 rename Documentation/virt/kvm/{nested-vmx.txt => nested-vmx.rst} (90%)
 rename Documentation/virt/kvm/{ppc-pv.txt => ppc-pv.rst} (91%)
 rename Documentation/virt/kvm/{review-checklist.txt => review-checklist.rst} (95%)
 rename Documentation/virt/kvm/{s390-diag.txt => s390-diag.rst} (90%)
 rename Documentation/virt/kvm/{timekeeping.txt => timekeeping.rst} (85%)
 rename Documentation/virt/uml/{UserModeLinux-HOWTO.txt => user_mode_linux.rst} (74%)
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/svm.h
 create mode 100644 tools/testing/selftests/kvm/include/x86_64/svm_util.h
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/svm.c
 create mode 100644 tools/testing/selftests/kvm/x86_64/svm_vmcall_test.c
```
#### [PATCH] KVM: apic: remove unused function apic_lvt_vector()
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11379669
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 266EB139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 02:36:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0F0CD21739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 02:36:18 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729527AbgBMCgP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Feb 2020 21:36:15 -0500
Received: from szxga07-in.huawei.com ([45.249.212.35]:41352 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729394AbgBMCgO (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Feb 2020 21:36:14 -0500
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 3B158490F74755B76417;
        Thu, 13 Feb 2020 10:36:11 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS404-HUB.china.huawei.com
 (10.3.19.204) with Microsoft SMTP Server id 14.3.439.0; Thu, 13 Feb 2020
 10:36:03 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: apic: remove unused function apic_lvt_vector()
Date: Thu, 13 Feb 2020 10:37:44 +0800
Message-ID: <1581561464-3893-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

The function apic_lvt_vector() is unused now, remove it.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/lapic.c | 5 -----
 1 file changed, 5 deletions(-)

```
#### [PATCH kvm-unit-tests] s390x: unittests: Use smp parameter
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11380457
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0FFF513A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 14:39:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E2E5F2073C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 14:39:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HzURuKi4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726968AbgBMOjD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 09:39:03 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:28616 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725781AbgBMOjD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 09:39:03 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581604742;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=o6W3XBfbdiVfU6zyxBNjQLFll+Vg04rm8+GTn0/p2LU=;
        b=HzURuKi4GnAzbWAfIjZXVivz4xmV4SypDaVbczKo4SloyhXTUU4BlECTJYsFz31oldJ3qU
        HSsAbw7lWQn0kW0Wn9BhI25C/omtuUeQGIN1f0LlELJ2l/cIUt9svJUfcZBvQYTFas6OkA
        mhIHTMtp+2vY8mTAQ7IuiD+bTdhsbhc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-109-E2SH1OabNqSYpNdEUpoIWw-1; Thu, 13 Feb 2020 09:39:01 -0500
X-MC-Unique: E2SH1OabNqSYpNdEUpoIWw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id DB3108EC828;
        Thu, 13 Feb 2020 14:38:59 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 21DB21001B0B;
        Thu, 13 Feb 2020 14:38:55 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: thuth@redhat.com, david@redhat.com, frankja@linux.ibm.com
Subject: [PATCH kvm-unit-tests] s390x: unittests: Use smp parameter
Date: Thu, 13 Feb 2020 15:38:55 +0100
Message-Id: <20200213143855.2965-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 s390x/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests v3] arm64: timer: Speed up gic-timer-state check
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11380029
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 441A2109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 09:33:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1A4762173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 09:33:12 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="b0Dm8qpA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729759AbgBMJdL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 04:33:11 -0500
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:53228 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729632AbgBMJdJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 13 Feb 2020 04:33:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581586388;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=O8Z9Thp+VSDpsbJ/c3/SKEh6FPSKloGY5r0r2a4bGnM=;
        b=b0Dm8qpAsBVp0LFUHF2wgAbhLn4QHlBlq2QYoNkIKBo/aXNXXhyeWgvZM3pOjSh/wpeskz
        Ta+prHgKHHFxBalCE8/bDFcE7duqF21qmQBeBGAjVQj76OMA/dxsqIWrHdfWmeTzfUnb2Z
        iBAbTKbmk9NAheMu5E/EJOFtr3aMMzo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-369-yZJ42JDsPGWE0H5Gm83c3A-1; Thu, 13 Feb 2020 04:33:04 -0500
X-MC-Unique: yZJ42JDsPGWE0H5Gm83c3A-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 26D68107ACCA;
        Thu, 13 Feb 2020 09:33:03 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id EA80B5C13F;
        Thu, 13 Feb 2020 09:32:58 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: alexandru.elisei@arm.com, yuzenghui@huawei.com,
        andre.przywara@arm.com, eric.auger@redhat.com
Subject: [PATCH kvm-unit-tests v3] arm64: timer: Speed up gic-timer-state
 check
Date: Thu, 13 Feb 2020 10:32:57 +0100
Message-Id: <20200213093257.23367-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's bail out of the wait loop if we see the expected state
to save over six seconds of run time. Make sure we wait a bit
before reading the registers and double check again after,
though, to somewhat mitigate the chance of seeing the expected
state by accident.

We also take this opportunity to push more IRQ state code to
the library.

Cc: Zenghui Yu <yuzenghui@huawei.com>
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
v3:
 - make gic_irq_state general for all irqs < 1020 [Zenghui Yu]
 - remove unused gic offsets from arm/timer.c [Alexandru Elisei]
v2:
 - check timer irq state twice [Alexandru Elisei]

 arm/timer.c       | 36 ++++++++++++------------------------
 lib/arm/asm/gic.h | 11 ++++++-----
 lib/arm/gic.c     | 45 +++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 63 insertions(+), 29 deletions(-)

```
#### [PATCH] KVM: VMX: Add 'else' to split mutually exclusive case
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11379667
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EE40A1805
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 02:33:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CD5B220724
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 02:33:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729469AbgBMCdo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Feb 2020 21:33:44 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:9726 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729333AbgBMCdo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Feb 2020 21:33:44 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 593D746914F92CDC175F;
        Thu, 13 Feb 2020 10:33:42 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS403-HUB.china.huawei.com
 (10.3.19.203) with Microsoft SMTP Server id 14.3.439.0; Thu, 13 Feb 2020
 10:33:36 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: VMX: Add 'else' to split mutually exclusive case
Date: Thu, 13 Feb 2020 10:35:15 +0800
Message-ID: <1581561315-3820-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Each if branch in handle_external_interrupt_irqoff() is mutually
exclusive. Add 'else' to make it clear and also avoid some unnecessary
check.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
---
 arch/x86/kvm/vmx/vmx.c | 6 ++----
 1 file changed, 2 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: eliminate some unreachable code
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11379681
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F165D924
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 02:52:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CD9592173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 02:52:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729515AbgBMCv6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Feb 2020 21:51:58 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:10614 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729333AbgBMCv6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Feb 2020 21:51:58 -0500
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id 268BC99038DBD4A45735;
        Thu, 13 Feb 2020 10:51:54 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS405-HUB.china.huawei.com
 (10.3.19.205) with Microsoft SMTP Server id 14.3.439.0; Thu, 13 Feb 2020
 10:51:45 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH] KVM: x86: eliminate some unreachable code
Date: Thu, 13 Feb 2020 10:53:25 +0800
Message-ID: <1581562405-30321-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

These code are unreachable, remove them.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 1 -
 arch/x86/kvm/x86.c     | 3 ---
 2 files changed, 4 deletions(-)

```
#### [PATCH] KVM: x86: fix incorrect comparison in trace event
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11380901
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2699A109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 17:27:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0691221734
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 17:27:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="ZWwD80NF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728709AbgBMR1C (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 12:27:02 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:50976 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728499AbgBMR1B (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 12:27:01 -0500
Received: by mail-wm1-f68.google.com with SMTP id a5so7161888wmb.0;
        Thu, 13 Feb 2020 09:26:59 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=xcUKyinhdCpe0Y5faS3M8RVdOca9RIh5O3GnfPcsZ1E=;
        b=ZWwD80NFfEejpAMYgf7bkpcyvwCC6dqcLDc2ipnLME/c8W+t3hvH25tZAuIzDYz4Jh
         qEDDIeaTMtLfSBLJ6RQJCI73fhgA8cslxbVdSXpOPk2ZRWfmERBR1+KLXEZvRG8ZdT5M
         eb05m1hJtjqHGXCDcTvY30p57DIczbslyE69InVjBOg+z0xPLo4mUUQBL9446TSIM0SN
         naDvrtxvEwfJL3RHqkKbzltS0zUw3y8JMo4Uw4fStNVEAgTFLGW/QzdxQKYCVxh0MOeU
         k8uOuuUftROrFsN84J/UmPBVCDJ1mkaD+/KPIrXbXtSotq+dJi88RvazPByansW9RB+6
         +Z1w==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=xcUKyinhdCpe0Y5faS3M8RVdOca9RIh5O3GnfPcsZ1E=;
        b=fb4VlVs03hq6HGGWu4dxs0YCZdmjj45c3Y3ztarObJDqyXWVQBIHvbe1khAo/9FCt7
         rPtmxcVK7viMvTftFupLMA8YXuS2WRuwWx9E5TjUob1CqSEAud8sg/abxpKUVxYXMjuo
         cPE7VHfc5siDcaNi6BPo0Vd7fnr/A4H4i7SckMmlbR7ARNRzwIZTibNiBza+I9UEmc7b
         vnyt1pKab4sqS8K8gfANXO+CpU/DjbcKoY5oYmCLK3SOev3hhwe5OmSqT0g2l3OUjWQ6
         6LYZlRx9ClrxWpgx2Fsc/ic6jseV6YOV+KK+QiSryHTSzV5ao9E77vAHpeilXnSdxae7
         kS2A==
X-Gm-Message-State: APjAAAXoOjnfuM8iLeeiRjCHLHSmZdvooiAUvCw+LL6mNSoB6nkWKwOE
        9XKcwv+72TDZZ+5eBC1iHvDSxdna
X-Google-Smtp-Source: 
 APXvYqylTYL5EvQ84wer++V2W5M5f6n9RK/s4bE8e/GOsVrXZdXk3hAB6zc89oqvmKZWQvj/0R8xqQ==
X-Received: by 2002:a05:600c:2254:: with SMTP id
 a20mr6618267wmm.97.1581614819091;
        Thu, 13 Feb 2020 09:26:59 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id 21sm3952017wmo.8.2020.02.13.09.26.58
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 13 Feb 2020 09:26:58 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: cai@lca.pw
Subject: [PATCH] KVM: x86: fix incorrect comparison in trace event
Date: Thu, 13 Feb 2020 18:26:57 +0100
Message-Id: <1581614817-17087-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The "u" field in the event has three states, -1/0/1.  Using u8 however means that
comparison with -1 will always fail, so change to signed char.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmutrace.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: fix missing prototypes
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11380899
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 07E7F109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 17:26:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DA37B2073A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 17:26:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="en/AH3gJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728583AbgBMR0o (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 12:26:44 -0500
Received: from mail-wm1-f68.google.com ([209.85.128.68]:39840 "EHLO
        mail-wm1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728541AbgBMR0o (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 12:26:44 -0500
Received: by mail-wm1-f68.google.com with SMTP id c84so7693150wme.4;
        Thu, 13 Feb 2020 09:26:43 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=vi0bzwCEngkzvYIMexg2mWcSV1LwVOXAVSzyuSvjg4s=;
        b=en/AH3gJz07K0r32poZQgPKC1i+UMLK4fVXL55mG8klebz5qHbzfVeEPM7EdjhDWyG
         gxYrc1EXnfCqmOUN6d7w/r2zyR8SvoQvh7AG1M6jx9oAlngbk+LOA6apM6HCXOt0sBqu
         qaiRyPghv83faR1K+WH5TdATIuqJw9Jdqf2R74z8dhOPrzOxmv9Cgn30KF1os/3/i+Jh
         Uehm3X+TEWfsvNjE/EujCR/jIA/dqeEmzyzv6VCYdDHkttPZUXawdIWElCqMzVf1qkzX
         P+HQgKeGxfcdjEFQ6x+qSAaIye2cAEZkl+UBkMs2S8VjgGy5mUYei8xJAHWZq+YCQfg1
         Y/uw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=vi0bzwCEngkzvYIMexg2mWcSV1LwVOXAVSzyuSvjg4s=;
        b=bFtj2UHWw61bqy0YewdPGEFQZDtnoGcfXhm2+f6dhrXF/1Dt6DwDa3UKoqFcC7Fc56
         MIeVOFiU5aMsjLWbvzHNrSoTFov4Csb4J5vX7B3sSUaeHiN8nEKxoiGHq0/iKvX/Rt/a
         EbywexV+xaYPeFyq3M1/0A3ntEiGOO0zZaTKGok0ou2T0BDWcbR95e75ZnOD4VVOXsci
         cDXOOfIlwSGigFEn46wl4YtaCsamwfL1oDs7ZyQU29K5t8B5k2Etq0K15/toCN4AOFGb
         qBntlGz23o7EZjnvxuEwEu6CUsjgKmDQJVLO1AyJe+SoB3l+NTh1pxPdpaPqPvBfoKcK
         awlQ==
X-Gm-Message-State: APjAAAWYlvmWGjnUOuG3CMzMZGaosVK/+HtxVDc5Ij3070FS+ZvTU8we
        FHV03GPkn/4UyQfT8Hnu04CYbpn3
X-Google-Smtp-Source: 
 APXvYqwc8/NzoqsuhjZzG/LiLOQKuW/m2mqUeOXYNbihohQrE4x6OwRGFEYppIgI4uFRG3dVzaxVBw==
X-Received: by 2002:a7b:cbc9:: with SMTP id n9mr6945877wmi.89.1581614802171;
        Thu, 13 Feb 2020 09:26:42 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 h2sm3813508wrt.45.2020.02.13.09.26.41
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Thu, 13 Feb 2020 09:26:41 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: cai@lca.pw
Subject: [PATCH] KVM: x86: fix missing prototypes
Date: Thu, 13 Feb 2020 18:26:40 +0100
Message-Id: <1581614800-16983-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reported with "make W=1" due to -Wmissing-prototypes.

Reported-by: Qian Cai <cai@lca.pw>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 include/linux/kvm_host.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [RFC PATCH 1/3] KVM: vmx: rewrite the comment in vmx_get_mt_mask
##### From: Chia-I Wu <olvaffe@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Chia-I Wu <olvaffe@gmail.com>
X-Patchwork-Id: 11381327
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 22CA913A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 21:30:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F29FB217F4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 21:30:49 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="VKYav0f4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728682AbgBMVat (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 16:30:49 -0500
Received: from mail-pl1-f195.google.com ([209.85.214.195]:45226 "EHLO
        mail-pl1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728368AbgBMVat (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 16:30:49 -0500
Received: by mail-pl1-f195.google.com with SMTP id b22so2839663pls.12
        for <kvm@vger.kernel.org>; Thu, 13 Feb 2020 13:30:47 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=7j+aqI6mcS2t54y8WBsKTQVk+8Kre6NazUv5XEvuQ4k=;
        b=VKYav0f415oiCoOPWgkmakg0CHFwQ9wtx/v0IZR0l+/KzKbQZo8nhG4j6/qlGqCvkR
         t2e2E8bXWSu06Lo5rZ8AvBuhmyvIffq9XAA2rceEQybe+5PgYkKCMlzeGmrtjjXdNcEJ
         T8TW+MibuMZArOxM0MlqTseRz8vv0+sB/oEuVlXfQXE3yYulvvnvUfKpTRl23LJ2CZhy
         oFTFTiFUefC52HPGukG8BK37jJ0ddMaxp+S6zu+py+UvQIwsbymAnBMfq9UKrl5/HZw5
         ciXNUJhJoR9sbs0/2FcadbW5nVJAW6pbE3a4kdWBnZETwqTgfVTV46pU2mY7jjQM9F8x
         ejBw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=7j+aqI6mcS2t54y8WBsKTQVk+8Kre6NazUv5XEvuQ4k=;
        b=C0mmkwzMTG8ZxFSmpFFkPT/a3UPy1YvVIvrSyZvIY+1t6S2nCb0DyF9zEb0eT6fqQI
         4yi85Nm9v+XJ04ATlJ4AGj2syQP5zovr+7KksIQ0CpnJUF6bV6GxAC9OswuW/pDUK4fY
         B8DpbYgY+IoxGn6cqXOOXcd4Z0gAZD9PBXcph3oalsUrtGx6vNcCpnLCA6xXDxmYErXn
         jsADhAgInEBLXi6N2gMEGr0TKt7/P4xteLyfW3+kW7FTJ/WACnwJEVENzHQgHEubTihR
         3H2MyUYzIMmp6TNNB/XGPlZGhj7pcux50YEoKk1bRWA6cpoEeVIZ3F0dG14YkWBHY6YD
         kitQ==
X-Gm-Message-State: APjAAAXpM6DQa7vhjALwOzn9IjzqHGYxMz1M23JrL/IIHip9cnqh8AYk
        fGL4cF0qkbtUy/CB0Lwrj+ityt7A
X-Google-Smtp-Source: 
 APXvYqwcfvGpQWXobqIwyn10/AWqbi/QWVme4KdemjFiaVWwsLy9ZrLAzxGbTP303AVgbN7atSEmbA==
X-Received: by 2002:a17:902:9687:: with SMTP id
 n7mr31124873plp.168.1581629446812;
        Thu, 13 Feb 2020 13:30:46 -0800 (PST)
Received: from olv0.mtv.corp.google.com
 ([2620:15c:202:201:9649:82d6:f889:b307])
        by smtp.gmail.com with ESMTPSA id
 s130sm4346683pfc.62.2020.02.13.13.30.46
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 13 Feb 2020 13:30:46 -0800 (PST)
From: Chia-I Wu <olvaffe@gmail.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, vkuznets@redhat.com, wanpengli@tencent.com,
        jmattson@google.com, joro@8bytes.org, gurchetansingh@chromium.org,
        kraxel@redhat.com, dri-devel@lists.freedesktop.org
Subject: [RFC PATCH 1/3] KVM: vmx: rewrite the comment in vmx_get_mt_mask
Date: Thu, 13 Feb 2020 13:30:34 -0800
Message-Id: <20200213213036.207625-2-olvaffe@gmail.com>
X-Mailer: git-send-email 2.25.0.265.gbab2e86ba0-goog
In-Reply-To: <20200213213036.207625-1-olvaffe@gmail.com>
References: <20200213213036.207625-1-olvaffe@gmail.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Better reflect the structure of the code and metion why we could not
always honor the guest.

Signed-off-by: Chia-I Wu <olvaffe@gmail.com>
Cc: Gurchetan Singh <gurchetansingh@chromium.org>
Cc: Gerd Hoffmann <kraxel@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 27 +++++++++++++++++----------
 1 file changed, 17 insertions(+), 10 deletions(-)

```
#### [RFC PATCH] security,anon_inodes,kvm: enable security support for anon inodes
##### From: Stephen Smalley <sds@tycho.nsa.gov>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stephen Smalley <sds@tycho.nsa.gov>
X-Patchwork-Id: 11381093
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AF8071800
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 19:48:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8503F218AC
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 19:48:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=tycho.nsa.gov header.i=@tycho.nsa.gov
 header.b="iLbBY/2f"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727902AbgBMTsQ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 14:48:16 -0500
Received: from USAT19PA20.eemsg.mail.mil ([214.24.22.194]:3236 "EHLO
        USAT19PA20.eemsg.mail.mil" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727742AbgBMTsQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 13 Feb 2020 14:48:16 -0500
X-Greylist: delayed 425 seconds by postgrey-1.27 at vger.kernel.org;
 Thu, 13 Feb 2020 14:48:14 EST
X-EEMSG-check-017: 77682231|USAT19PA20_ESA_OUT01.csd.disa.mil
X-IronPort-AV: E=Sophos;i="5.70,437,1574121600";
   d="scan'208";a="77682231"
Received: from emsm-gh1-uea11.ncsc.mil ([214.29.60.3])
  by USAT19PA20.eemsg.mail.mil with ESMTP/TLS/DHE-RSA-AES256-SHA256;
 13 Feb 2020 19:41:02 +0000
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=tycho.nsa.gov; i=@tycho.nsa.gov; q=dns/txt;
  s=tycho.nsa.gov; t=1581622862; x=1613158862;
  h=from:to:cc:subject:date:message-id:mime-version:
   content-transfer-encoding;
  bh=4sLC3taziqq+PTb7ehQVhicAG403X4m64MTt2WJhuSg=;
  b=iLbBY/2fKvOcmY0+dBeI0GsA3iqtED+sOgFwq1btELuwL2ywKv0B9O9u
   OkqhCV0xOSE84mGHcN3Iv5v+3fGrdhALkumXACafpgxTjEw23NaDjmcOR
   L3cb1CyGgRRrwJXPPcLUFbPT458f9bktcAydm2EZZHEBUh8A6+pdf20Ty
   0kS8uHH+7XjLydX2QnA7DT0ONlrcZSzbKj4PDUiNJjF7BNmEdsqwbsk8l
   VCe05XVwoqraJu8C6epZJ7/iHO1wiBPibyV2z6x9qtDLrvEnjX7Ohf4H3
   SkOWBJuUp2Agw+6M5SH1lU+lwi268svZaRIrcLDBvOEdKbKaFUg+9saYb
   g==;
X-IronPort-AV: E=Sophos;i="5.70,437,1574121600";
   d="scan'208";a="39098365"
IronPort-PHdr: 
 9a23:6xWfLR1ziOCpm0HEsmDT+DRfVm0co7zxezQtwd8ZsesULvzxwZ3uMQTl6Ol3ixeRBMOHsq4C1bqd6vq+EUU7or+/81k6OKRWUBEEjchE1ycBO+WiTXPBEfjxciYhF95DXlI2t1uyMExSBdqsLwaK+i764jEdAAjwOhRoLerpBIHSk9631+ev8JHPfglEnjWwba59IRmsrAjctcYajZZ8Jqsw1xDEvmZGd+NKyGxnIl6egwzy7dqq8p559CRQtfMh98peXqj/Yq81U79WAik4Pm4s/MHkugXNQgWJ5nsHT2UZiQFIDBTf7BH7RZj+rC33vfdg1SaAPM32Sbc0WSm+76puVRTlhjsLOyI//WrKhMNwlqZbqw+/qRJ5zYDffYWZOONwc67ZeN8XQ3dKUMRMWCxbGo6yb5UBAfcPM+hbqIfyqFQAoACiCQSvHu7j1iVFimPq0aA8zu8vERvG3AslH98WrXrUsMv6NL8SUe+ryqnD0CjNb/ZM1jf57IjHbBAgquyLULJrbMXR0lIiFx/Fj1qMqYzlOCmZ1uIWs2eB9eZgWuWvi3A+pgx3vzOhyMAsiozTiYIUzFDJ7SZ5z5gvJd2+VkF7ZcSoEJxKtyGVMYZ9X8AsQ3lwtSonxbALtoS3cSgXxJg92RLSZOKLf5KV7h/lSe2fOy13hGh/d7K6nxuy9E+gxfDiWcSsy1ZKqzZFksHLtnAQyxzf8siHReV5/kemwTuPyxrc6vtFIUApjqrXMZ8hwrg+lpoUqkTMADP5lF/qjK6Wakok+u+o5/7hYrr6vZ+TK5V4igT/MqQqgsC/AOI4PRYSX2WD5Oix27Lu8Vf5TblXlPE6jKbUvI7AKcgGvqK5BhVa0ocn6xaxFTem19EYkGEcLF1YYxKKlJTpOlHSL/D4CvezmVKskCxxyPzcMb3hBYvNImDZkLj9ZbZ991JcyA0rwNBZ4ZJUCaoMIP30Wk/2u9zYCgE2PxaozObgDdV3zpkeVn6XAq+FLKPStkeF6f81LOmKeIAVvzL9JuMq5/7pin85llsdcrez0ZQLb3C4G+xsI1+Fbnr0ntcBDWAKsxImTOPwlV2CVSVeZ26oUKIh4jE3EYemDYDERoC3nrONxju0HppTZmpeEFCDDW/od5mYW/cLcC+SPM5hkiYDVbW6So4uyxeutA7ky7Z9KurU+ysYtY/s1dRv4O3Tjx4y+SZpD8Sey2uNVX17nnsURz8q26ByuU99ykmG0aVjnfxYGsJc5+lTXgc5K5Hc1ep6BM72Wg7bedeJUlmmSM28AT4tVtIx38MOY0FlFtWmjxDD2TeqArAMm7yFH5w777zT32bvKMZ50HvGyqYhgEc8QsdVNm2pmLR/9w7NCI7NiUmZkLyqdasE1i7X6GiD1XaOvF1fUANoVaXFXHYfZlbZrNjg/UPNUaOhCak9MgtA1c6DKrJGatjujVpbWffjPMrRbnmvm2e/GxmI3KmAbIn0dGUH2iXSFkwEnxoU/XacOgg0Hj2hrH7GDDxyCVLvZFvh8fJgp3O/T080yRyKbkJ62rqr9R4am+acR+kQ3r0aoichrSt7HFKn09LREdqAqFkpQKIJet454VFaxUrHuAFneJ+tNaZvghgZaQskkVnp0kBMFohYkcUs5EgvxQ52JLPQhEhNbBuEzJvwPfvRMWC08xexPf2FkmrC2cqbr/9coM8zrE/u6UTyR0c=
X-IPAS-Result: 
 A2D8BgD2pEVe/wHyM5BmHQEBAQkBEQUFAYF7gXgFgRhVIBIqjReGXwaCOIhviTSGL4FnCQEBAQEBAQEBARsSCgQBAYRAgnI4EwIQAQEBBQEBAQEBBQMBAWyFNwyCOymDMAsBRkiBCYJbDD8BglYlD65uM4NMaQGEToE4BoE4h0ZqhA55gQeBETaCKHOEAwFzE4UvBJZhgSqXa4JEgk+EfoIsgxyJMAwchQeRVIQ7AS2XKZRQIjeBISsIAhgIIQ+DJxM9GA2BGo0PF4hkhV0jAzACAYxsgjIBAQ
Received: from tarius.tycho.ncsc.mil (HELO tarius.infosec.tycho.ncsc.mil)
 ([144.51.242.1])
  by emsm-gh1-uea11.NCSC.MIL with ESMTP; 13 Feb 2020 19:41:00 +0000
Received: from moss-pluto.infosec.tycho.ncsc.mil (moss-pluto [192.168.25.131])
        by tarius.infosec.tycho.ncsc.mil (8.14.7/8.14.4) with ESMTP id
 01DJe4pn093453;
        Thu, 13 Feb 2020 14:40:04 -0500
From: Stephen Smalley <sds@tycho.nsa.gov>
To: selinux@vger.kernel.org
Cc: linux-security-module@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, kvm@vger.kernel.org,
        viro@zeniv.linux.org.uk, paul@paul-moore.com, dancol@google.com,
        nnk@google.com, Stephen Smalley <sds@tycho.nsa.gov>
Subject: [RFC PATCH] security,anon_inodes,kvm: enable security support for
 anon inodes
Date: Thu, 13 Feb 2020 14:41:57 -0500
Message-Id: <20200213194157.5877-1-sds@tycho.nsa.gov>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add support for labeling and controlling access to files attached to anon
inodes. Introduce extended interfaces for creating such files to permit
passing a related file as an input to decide how to label the anon
inode. Define a security hook for initializing the anon inode security
attributes. Security attributes are either inherited from a related file
or determined based on some combination of the creating task and policy
(in the case of SELinux, using type_transition rules).  As an
example user of the inheritance support, convert kvm to use the new
interface for passing the related file so that the anon inode can inherit
the security attributes of /dev/kvm and provide consistent access control
for subsequent ioctl operations.  Other users of anon inodes, including
userfaultfd, will default to the transition-based mechanism instead.

Compared to the series in
https://lore.kernel.org/selinux/20200211225547.235083-1-dancol@google.com/,
this approach differs in that it does not require creation of a separate
anonymous inode for each file (instead storing the per-instance security
information in the file security blob), it applies labeling and control
to all users of anonymous inodes rather than requiring opt-in via a new
flag, it supports labeling based on a related inode if provided,
it relies on type transitions to compute the label of the anon inode
when there is no related inode, and it does not require introducing a new
security class for each user of anonymous inodes.

On the other hand, the approach in this patch does expose the name passed
by the creator of the anon inode to the policy (an indirect mapping could
be provided within SELinux if these names aren't considered to be stable),
requires the definition of type_transition rules to distinguish userfaultfd
inodes from proc inodes based on type since they share the same class,
doesn't support denying the creation of anonymous inodes (making the hook
added by this patch return something other than void is problematic due to
it being called after the file is already allocated and error handling in
the callers can't presently account for this scenario and end up calling
release methods multiple times), and may be more expensive
(security_transition_sid overhead on each anon inode allocation).

We are primarily posting this RFC patch now so that the two different
approaches can be concretely compared.  We anticipate a hybrid of the
two approaches being the likely outcome in the end.  In particular
if support for allocating a separate inode for each of these files
is acceptable, then we would favor storing the security information
in the inode security blob and using it instead of the file security
blob.

This patch only converts kvm to use a related inode (/dev/kvm) for the
creation of anon inodes as an example user. We would look to
incrementally convert other subsystems where applicable. This could
potentially cause policy breakage if policies are written for a subsystem
using the type_transition rules and then the subsystem is later converted
to use a related inode, so some means of compatible evolution would be
required.

There are a number of file permission checks in SELinux that do not
currently use the file_has_perm() helper and therefore do not pick up
the logic for handling these anonymous inodes. These will need to be looked
at further to see whether they are relevant to anonymous inodes and should
be updated with the new logic.

Any hooks that are directly passed a dentry or inode and not a file will
still skip permission checking by virtue of the S_ISPRIVATE() checks in
security/security.c and in security/selinux/hooks.c. At some point they
need to be audited to determine whether they are relevant to anonymous
inodes.

This change may create compatibility issues since it unconditionally
enables labeling and access control for all anonymous inodes; it is
known to break two selinux-testsuite bpf tests without adjusting its
policy.  It will likely need to be wrapped by a SELinux policy
capability before being merged to prevent breaking existing policies.

An example of a sample program and policy will follow in a follow-up
to this patch to demonstrate the effect on userfaultfd and kvm.

Signed-off-by: Stephen Smalley <sds@tycho.nsa.gov>
---
 fs/anon_inodes.c                  | 53 +++++++++++++++++-------
 include/linux/anon_inodes.h       |  7 ++++
 include/linux/lsm_hooks.h         | 11 +++++
 include/linux/security.h          |  8 ++++
 security/security.c               |  7 ++++
 security/selinux/hooks.c          | 69 ++++++++++++++++++++++++++++---
 security/selinux/include/objsec.h |  4 ++
 virt/kvm/kvm_main.c               | 27 +++++++-----
 8 files changed, 155 insertions(+), 31 deletions(-)

```
#### [PATCH kvm-unit-tests 1/2] arch-run: Allow $QEMU to include parameters
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 11380451
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C67B7138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 14:33:22 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A5DD724649
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 14:33:22 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="cuolvnAr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727558AbgBMOdV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 13 Feb 2020 09:33:21 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:20140 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727414AbgBMOdV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 13 Feb 2020 09:33:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581604400;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=BS1gc949f0GEp9oop4QVBA5jni4HDU5dKQyNOzlsGVM=;
        b=cuolvnAr5av0Qr+UrvGZJYqcYGw5KQow1SkqSXBJ2NMLTTwIuQSEanpvevyq4MUqzfWhZT
        b20aiRxvzdoC91JTbrC3xnJiDraqeD1bhhwYzQW+d01o3mvH96kqjdPxzudubKHk9quRHu
        UfeXHgj1Uau22P3iOWfR1RtxJN6sgXo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-304-2N3f5fKnPl-xQ9XA07MICg-1; Thu, 13 Feb 2020 09:33:16 -0500
X-MC-Unique: 2N3f5fKnPl-xQ9XA07MICg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2AEE3801E67;
        Thu, 13 Feb 2020 14:33:15 +0000 (UTC)
Received: from kamzik.brq.redhat.com (unknown [10.43.2.160])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 278CF5C1D6;
        Thu, 13 Feb 2020 14:33:08 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: peter.maydell@linaro.org, alex.bennee@linaro.org,
        pbonzini@redhat.com, lvivier@redhat.com, thuth@redhat.com,
        david@redhat.com, frankja@linux.ibm.com, eric.auger@redhat.com
Subject: [PATCH kvm-unit-tests 1/2] arch-run: Allow $QEMU to include
 parameters
Date: Thu, 13 Feb 2020 15:32:59 +0100
Message-Id: <20200213143300.32141-2-drjones@redhat.com>
In-Reply-To: <20200213143300.32141-1-drjones@redhat.com>
References: <20200213143300.32141-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Now it's possible to run all tests using run_tests.sh with a
QEMU specified by the $QEMU environment variable that also
includes additional parameters. E.g. QEMU="/path/to/qemu -icount 8"

Cc: Peter Maydell <peter.maydell@linaro.org>
Cc: Alex Bennée <alex.bennee@linaro.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Laurent Vivier <lvivier@redhat.com>
Cc: Thomas Huth <thuth@redhat.com>
Cc: David Hildenbrand <david@redhat.com>
Cc: Janosch Frank <frankja@linux.ibm.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 scripts/arch-run.bash | 14 +++++++++++++-
 1 file changed, 13 insertions(+), 1 deletion(-)

```
#### [PATCH 01/12] KVM: SVM: Add KVM_SEV SEND_START command
##### From: Ashish Kalra <Ashish.Kalra@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 11379539
Return-Path: <SRS0=MBzu=4B=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4FD6B109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 01:15:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1C4DF2173E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 13 Feb 2020 01:15:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="mmrHyqcQ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729417AbgBMBPD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 12 Feb 2020 20:15:03 -0500
Received: from mail-eopbgr690075.outbound.protection.outlook.com
 ([40.107.69.75]:63054
        "EHLO NAM04-CO1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729285AbgBMBPD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 12 Feb 2020 20:15:03 -0500
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=kcpltUeDtnAvrIdo7xSyO4w2h7i0n01TAKC4TO0f/iw8cLv0vDgDmvhlVM1b3tv6Y/jNu/BkvP+ZAe+FKU4ZPBTK5N8A4ZaZWAlQrZPg8Nmm6AmGv9dwX/AjO/4WASW6ne4En0qsUqmgkXgxjY8CK3oWWiap05mUWuNSFWofBQIQV73KmDzi8K8wDCMwZH791SrhwERsY/qPvgg+V13WIAmtD9WOE0Fj10WxDVqFEawvWIm/7axxWYgZ9YhNfWvEaXgTcVZagxGi3j1sNmeMIU/9JoxwVtZ3WFNIWcu2lLfOUY7R6ECU4/o3QerALKbw1fzHyAoP+iNgDdwR1DVQlA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=C9MwzSGFXQFgULl0SwpZg1Q23Bj647eOcOP5OeTq8nY=;
 b=UEFozcrJ7SB8iDqaRgVU8JfXWxYk180m1DcE+SkQVn9yXvUU3h6txV6FOB0p4KC9vclhGz4rwbB2C7iY4rYLQ9LAU9n+pArIZ4aaiadhurtuPxYARA/+AXS72e3aEv5eofWCwoBSPIrfMFIRPeNHmlWrl88Zmum5n3mR7llAdDsFU9kY5kXRvdto8MwJJkA+Op4XgUAjfd3FU2dxWZ5XMgm5SmgZPazKzeT+xwJhXi2UNE77yRxyhgQeYAnLYFC0HiJg6lBGyDpexJYcUS+UjVPjsTOGMpezzgSMEpHOFnFX0Oos6meQHdI655+MCLn0fVP609LYHgNLhx8/STglJw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=C9MwzSGFXQFgULl0SwpZg1Q23Bj647eOcOP5OeTq8nY=;
 b=mmrHyqcQszAA5yzEOmB9x+Q3usPitKc1SuZ4z095Me/Ofxbk2BL2IeSz8KK5qtgLcpt5PViGWJtnG9T7NyTcB0Xre3q0JiyinBDhPtP0qZEk0FLUdIgdYdxsQE6Iprnx8o+dkiDe8Iu6EM/NX77dUna7lhvX1Z+tdtDdbF4Y1J0=
Authentication-Results: spf=none (sender IP is )
 smtp.mailfrom=Ashish.Kalra@amd.com;
Received: from SN1PR12MB2528.namprd12.prod.outlook.com (52.132.196.33) by
 SN1PR12MB2366.namprd12.prod.outlook.com (52.132.194.147) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2729.22; Thu, 13 Feb 2020 01:14:59 +0000
Received: from SN1PR12MB2528.namprd12.prod.outlook.com
 ([fe80::fd48:9921:dd63:c6e1]) by SN1PR12MB2528.namprd12.prod.outlook.com
 ([fe80::fd48:9921:dd63:c6e1%7]) with mapi id 15.20.2707.030; Thu, 13 Feb 2020
 01:14:59 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        rkrcmar@redhat.com, joro@8bytes.org, bp@suse.de,
        thomas.lendacky@amd.com, rientjes@google.com, x86@kernel.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH 01/12] KVM: SVM: Add KVM_SEV SEND_START command
Date: Thu, 13 Feb 2020 01:14:49 +0000
Message-Id: 
 <59ca3ae4ac03c43751ce4af5119ede548bb9e8e4.1581555616.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1581555616.git.ashish.kalra@amd.com>
References: <cover.1581555616.git.ashish.kalra@amd.com>
X-ClientProxiedBy: DM3PR14CA0137.namprd14.prod.outlook.com
 (2603:10b6:0:53::21) To SN1PR12MB2528.namprd12.prod.outlook.com
 (2603:10b6:802:28::33)
MIME-Version: 1.0
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 DM3PR14CA0137.namprd14.prod.outlook.com (2603:10b6:0:53::21) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2729.23 via Frontend
 Transport; Thu, 13 Feb 2020 01:14:58 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: bebbe53a-c55d-4a57-d7ed-08d7b0222504
X-MS-TrafficTypeDiagnostic: SN1PR12MB2366:|SN1PR12MB2366:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN1PR12MB236670919F9212D3FC1E56958E1A0@SN1PR12MB2366.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:6108;
X-Forefront-PRVS: 031257FE13
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(346002)(136003)(366004)(376002)(39860400002)(396003)(199004)(189003)(8936002)(5660300002)(66946007)(66476007)(66556008)(7416002)(2906002)(6916009)(6666004)(4326008)(7696005)(52116002)(316002)(36756003)(66574012)(6486002)(86362001)(956004)(2616005)(81156014)(478600001)(8676002)(81166006)(26005)(16526019)(186003);DIR:OUT;SFP:1101;SCL:1;SRVR:SN1PR12MB2366;H:SN1PR12MB2528.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
Received-SPF: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 fHskUn41KKlic13cRFifhDEds/BufzdH+8S0BCy4PNqr0tSy/o+xLuSYzYnqOmwKXqWPdwuiJN9z+0+RCJ1CWP8nMeE032kvmGReXgKrxHdox9D/cbMzz5MnceDEjagzgUa7KIsUq8tZm648HKqWbDynHZ8DJuL60NMIXbzJe+bXmyD05LergEHzVzPgcFzc2pyWIcUUV84u3pK1rJvm8Z+cJtsGYtLF3FrDIICr3ixT/N51DyDsHJZdzv3Q4v/9DS2LLVtvLyNIoxo72nHFA/Q7fRO3vTs0711hyR9ltjArudmAQkkWf+hxzA/DnJTjahfUOrR50REhPtmOwWPY39bH9R93M/LsvMlDG/hapD5zcDNbtIvL6Jlj5Lm+9U/IH/GMV+HmonMpZo9VEGEm7+AsSk1DxAER2FNATwM5p3+H5hE9DzKnF0u2vJhgIMCn
X-MS-Exchange-AntiSpam-MessageData: 
 htupNgdSrfHjwPlgmtb9XpUU1/ubnLA1oOHLt1fJrQplvqNGumezQVMiOOv85qZPMyOWrLg/QRINkhxYtdPMRbY6sDfsPv4dmNYILtkap0LlJqQ6aBmkReM5/uXBYh80BrKj97ydFds9nZprXO3ZrQ==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 bebbe53a-c55d-4a57-d7ed-08d7b0222504
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 13 Feb 2020 01:14:59.4144
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 5Izgexz4yfQVg/sgTFVBhkE7KW+WmkgHBo/GqS3JwvRKvAivGGSQZvWm0840SPubH3U8W9VRKiih5ZXAP2wcsQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN1PR12MB2366
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Brijesh Singh <brijesh.singh@amd.com>

The command is used to create an outgoing SEV guest encryption context.

Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Borislav Petkov <bp@suse.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Signed-off-by: Ashish Kalra <ashish.kalra@amd.com>
---
 .../virt/kvm/amd-memory-encryption.rst        |  27 ++++
 arch/x86/kvm/svm.c                            | 125 ++++++++++++++++++
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  12 ++
 4 files changed, 168 insertions(+), 4 deletions(-)

```
