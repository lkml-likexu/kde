#### [PATCH v26 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a common macro
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: gengdongjiu <gengdongjiu@huawei.com>
X-Patchwork-Id: 11533761
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 847EB81
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 13:40:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7576A2073A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 13:40:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726519AbgEGNkW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 09:40:22 -0400
Received: from szxga04-in.huawei.com ([45.249.212.190]:3897 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725969AbgEGNkW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 09:40:22 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.60])
        by Forcepoint Email with ESMTP id E53868DD50292E4B1F94;
        Thu,  7 May 2020 21:40:17 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS412-HUB.china.huawei.com
 (10.3.19.212) with Microsoft SMTP Server id 14.3.487.0; Thu, 7 May 2020
 21:40:09 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <imammedo@redhat.com>, <mst@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <peter.maydell@linaro.org>,
        <shannon.zhaosl@gmail.com>, <pbonzini@redhat.com>,
        <fam@euphon.net>, <rth@twiddle.net>, <ehabkost@redhat.com>,
        <mtosatti@redhat.com>, <qemu-devel@nongnu.org>,
        <kvm@vger.kernel.org>, <qemu-arm@nongnu.org>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>,
        <Jonathan.Cameron@huawei.com>, <linuxarm@huawei.com>
Subject: [PATCH v26 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a common
 macro
Date: Thu, 7 May 2020 21:41:56 +0800
Message-ID: <20200507134205.7559-2-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200507134205.7559-1-gengdongjiu@huawei.com>
References: <20200507134205.7559-1-gengdongjiu@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.151.151.243]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The little end UUID is used in many places, so make
NVDIMM_UUID_LE to a common macro to convert the UUID
to a little end array.

Reviewed-by: Xiang Zheng <zhengxiang9@huawei.com>
Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
Change since v25:
1. Address Peter's comments to add a proper doc-comment comment for
   UUID_LE macros.
---
 hw/acpi/nvdimm.c    | 10 +++-------
 include/qemu/uuid.h | 26 ++++++++++++++++++++++++++
 slirp               |  2 +-
 3 files changed, 30 insertions(+), 8 deletions(-)

```
#### [GIT PULL] KVM changes for Linux 5.7-rc5
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11533241
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1524F139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 11:53:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F0D1E20735
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 11:53:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="JkaYZiam"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726393AbgEGLx3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 07:53:29 -0400
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:26401 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725948AbgEGLx1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 7 May 2020 07:53:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588852406;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc; bh=oJNhrRBC0c+BFGHFCS+s7JJ0R5CeLnnrd6LkdO80vW4=;
        b=JkaYZiam3G6JGPcqod1r+SrcRaaWkpkTZsLidhZxsCjsU7LPohv4i22LWTzDnrTdOI9Ml8
        pneeBU5vMVQ4UsI7a8yqtmp/pHVWxHHhzkcV1y15YZFRU1TroYkeutnhzy7G3phn7+/icZ
        Q6S8Yb9ywKFPXnj/oJf9GFE/ui3P9mQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-291-KMK427m6N2a7db-dpEdpog-1; Thu, 07 May 2020 07:53:23 -0400
X-MC-Unique: KMK427m6N2a7db-dpEdpog-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AA47480058A;
        Thu,  7 May 2020 11:53:22 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 599246ACE6;
        Thu,  7 May 2020 11:53:22 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.7-rc5
Date: Thu,  7 May 2020 07:53:22 -0400
Message-Id: <20200507115322.495846-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 00a6a5ef39e7db3648b35c86361058854db84c83:

  Merge tag 'kvm-ppc-fixes-5.7-1' of git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc into kvm-master (2020-04-21 09:39:55 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 2673cb6849722a4ffd74c27a9200a9ec43f64be3:

  Merge tag 'kvm-s390-master-5.7-3' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into HEAD (2020-05-06 08:09:17 -0400)

----------------------------------------------------------------
Bugfixes, mostly for ARM and AMD, and more documentation.

----------------------------------------------------------------

Slightly bigger than usual because I couldn't send out what was pending
for rc4, but there is nothing worrisome going on.  I have more
fixes pending for guest debugging support (gdbstub) but I will send them
next week.

Thanks,

Paolo

Christian Borntraeger (1):
      KVM: s390: Remove false WARN_ON_ONCE for the PQAP instruction

Fangrui Song (1):
      KVM: arm64: Delete duplicated label in invalid_vector

Kashyap Chamarthy (1):
      docs/virt/kvm: Document configuring and running nested guests

Marc Zyngier (11):
      KVM: arm: vgic: Fix limit condition when writing to GICD_I[CS]ACTIVER
      KVM: arm64: PSCI: Narrow input registers when using 32bit functions
      KVM: arm64: PSCI: Forbid 64bit functions for 32bit guests
      KVM: arm: vgic: Synchronize the whole guest on GIC{D,R}_I{S,C}ACTIVER read
      KVM: arm: vgic: Only use the virtual state when userspace accesses enable bits
      KVM: arm: vgic-v2: Only use the virtual state when userspace accesses pending bits
      Merge branch 'kvm-arm64/psci-fixes-5.7' into kvmarm-master/master
      Merge branch 'kvm-arm64/vgic-fixes-5.7' into kvmarm-master/master
      KVM: arm64: Save/restore sp_el0 as part of __guest_enter
      KVM: arm64: vgic-v4: Initialize GICv4.1 even in the absence of a virtual ITS
      KVM: arm64: Fix 32bit PC wrap-around

Paolo Bonzini (6):
      KVM: SVM: fill in kvm_run->debug.arch.dr[67]
      Merge tag 'kvmarm-fixes-5.7-1' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master
      Merge tag 'kvmarm-fixes-5.7-2' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master
      kvm: ioapic: Restrict lazy EOI update to edge-triggered interrupts
      kvm: x86: Use KVM CPU capabilities to determine CR4 reserved bits
      Merge tag 'kvm-s390-master-5.7-3' of git://git.kernel.org/.../kvms390/linux into HEAD

Peter Xu (2):
      KVM: selftests: Fix build for evmcs.h
      KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly

Sean Christopherson (2):
      KVM: nVMX: Replace a BUG_ON(1) with BUG() to squash clang warning
      KVM: VMX: Explicitly clear RFLAGS.CF and RFLAGS.ZF in VM-Exit RSB path

Suravee Suthikulpanit (1):
      KVM: x86: Fixes posted interrupt check for IRQs delivery modes

Zenghui Yu (2):
      KVM: arm64: vgic-v3: Retire all pending LPIs on vcpu destroy
      KVM: arm64: vgic-its: Fix memory leak on the error path of vgic_add_lpi()

 Documentation/virt/kvm/index.rst                 |   2 +
 Documentation/virt/kvm/running-nested-guests.rst | 276 +++++++++++++++++++++++
 arch/arm64/kvm/guest.c                           |   7 +
 arch/arm64/kvm/hyp/entry.S                       |  23 ++
 arch/arm64/kvm/hyp/hyp-entry.S                   |   1 -
 arch/arm64/kvm/hyp/sysreg-sr.c                   |  17 +-
 arch/powerpc/kvm/powerpc.c                       |   1 +
 arch/s390/kvm/kvm-s390.c                         |   1 +
 arch/s390/kvm/priv.c                             |   4 +-
 arch/x86/include/asm/kvm_host.h                  |   4 +-
 arch/x86/kvm/ioapic.c                            |  10 +-
 arch/x86/kvm/svm/svm.c                           |   2 +
 arch/x86/kvm/vmx/nested.c                        |   2 +-
 arch/x86/kvm/vmx/vmenter.S                       |   3 +
 arch/x86/kvm/x86.c                               |  21 +-
 tools/testing/selftests/kvm/include/evmcs.h      |   4 +-
 tools/testing/selftests/kvm/lib/x86_64/vmx.c     |   3 +
 virt/kvm/arm/hyp/aarch32.c                       |   8 +-
 virt/kvm/arm/psci.c                              |  40 ++++
 virt/kvm/arm/vgic/vgic-init.c                    |  19 +-
 virt/kvm/arm/vgic/vgic-its.c                     |  11 +-
 virt/kvm/arm/vgic/vgic-mmio-v2.c                 |  16 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c                 |  31 +--
 virt/kvm/arm/vgic/vgic-mmio.c                    | 228 ++++++++++++++-----
 virt/kvm/arm/vgic/vgic-mmio.h                    |  19 ++
 25 files changed, 628 insertions(+), 125 deletions(-)
 create mode 100644 Documentation/virt/kvm/running-nested-guests.rst
```
#### [GIT PULL] KVM changes for Linux 5.7-rc5
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11533243
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 09C6E139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 11:53:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E3AE220A8B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 11:53:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HQei5SeV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726774AbgEGLxi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 07:53:38 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:60768 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726580AbgEGLxi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 07:53:38 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588852416;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=oJNhrRBC0c+BFGHFCS+s7JJ0R5CeLnnrd6LkdO80vW4=;
        b=HQei5SeVaDd6hPqjS4D1PRRpCbpdlC7Ci8jM9g2KMtmvCuwmcqWrY1k9F/oDe1dnJNqu8H
        w1XI4CixLnftHTe8Qt6RwBNn2VQEK9YXkq86Yri5bjiZ6g9TFoC37oiq2/fel5mSVvgQ7C
        C3JP8mlpF088z/nOGwhuAgn5Q2X0Wn8=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-187-r-JReGUDMy6MKKvTDqstzw-1; Thu, 07 May 2020 07:53:34 -0400
X-MC-Unique: r-JReGUDMy6MKKvTDqstzw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 821341005510;
        Thu,  7 May 2020 11:53:33 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 11C1F1C933;
        Thu,  7 May 2020 11:53:32 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: torvalds@linux-foundation.org
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [GIT PULL] KVM changes for Linux 5.7-rc5
Date: Thu,  7 May 2020 07:53:32 -0400
Message-Id: <20200507115332.495930-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Linus,

The following changes since commit 00a6a5ef39e7db3648b35c86361058854db84c83:

  Merge tag 'kvm-ppc-fixes-5.7-1' of git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc into kvm-master (2020-04-21 09:39:55 -0400)

are available in the Git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 2673cb6849722a4ffd74c27a9200a9ec43f64be3:

  Merge tag 'kvm-s390-master-5.7-3' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into HEAD (2020-05-06 08:09:17 -0400)

----------------------------------------------------------------
Bugfixes, mostly for ARM and AMD, and more documentation.

----------------------------------------------------------------

Slightly bigger than usual because I couldn't send out what was pending
for rc4, but there is nothing worrisome going on.  I have more
fixes pending for guest debugging support (gdbstub) but I will send them
next week.

Thanks,

Paolo

Christian Borntraeger (1):
      KVM: s390: Remove false WARN_ON_ONCE for the PQAP instruction

Fangrui Song (1):
      KVM: arm64: Delete duplicated label in invalid_vector

Kashyap Chamarthy (1):
      docs/virt/kvm: Document configuring and running nested guests

Marc Zyngier (11):
      KVM: arm: vgic: Fix limit condition when writing to GICD_I[CS]ACTIVER
      KVM: arm64: PSCI: Narrow input registers when using 32bit functions
      KVM: arm64: PSCI: Forbid 64bit functions for 32bit guests
      KVM: arm: vgic: Synchronize the whole guest on GIC{D,R}_I{S,C}ACTIVER read
      KVM: arm: vgic: Only use the virtual state when userspace accesses enable bits
      KVM: arm: vgic-v2: Only use the virtual state when userspace accesses pending bits
      Merge branch 'kvm-arm64/psci-fixes-5.7' into kvmarm-master/master
      Merge branch 'kvm-arm64/vgic-fixes-5.7' into kvmarm-master/master
      KVM: arm64: Save/restore sp_el0 as part of __guest_enter
      KVM: arm64: vgic-v4: Initialize GICv4.1 even in the absence of a virtual ITS
      KVM: arm64: Fix 32bit PC wrap-around

Paolo Bonzini (6):
      KVM: SVM: fill in kvm_run->debug.arch.dr[67]
      Merge tag 'kvmarm-fixes-5.7-1' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master
      Merge tag 'kvmarm-fixes-5.7-2' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master
      kvm: ioapic: Restrict lazy EOI update to edge-triggered interrupts
      kvm: x86: Use KVM CPU capabilities to determine CR4 reserved bits
      Merge tag 'kvm-s390-master-5.7-3' of git://git.kernel.org/.../kvms390/linux into HEAD

Peter Xu (2):
      KVM: selftests: Fix build for evmcs.h
      KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly

Sean Christopherson (2):
      KVM: nVMX: Replace a BUG_ON(1) with BUG() to squash clang warning
      KVM: VMX: Explicitly clear RFLAGS.CF and RFLAGS.ZF in VM-Exit RSB path

Suravee Suthikulpanit (1):
      KVM: x86: Fixes posted interrupt check for IRQs delivery modes

Zenghui Yu (2):
      KVM: arm64: vgic-v3: Retire all pending LPIs on vcpu destroy
      KVM: arm64: vgic-its: Fix memory leak on the error path of vgic_add_lpi()

 Documentation/virt/kvm/index.rst                 |   2 +
 Documentation/virt/kvm/running-nested-guests.rst | 276 +++++++++++++++++++++++
 arch/arm64/kvm/guest.c                           |   7 +
 arch/arm64/kvm/hyp/entry.S                       |  23 ++
 arch/arm64/kvm/hyp/hyp-entry.S                   |   1 -
 arch/arm64/kvm/hyp/sysreg-sr.c                   |  17 +-
 arch/powerpc/kvm/powerpc.c                       |   1 +
 arch/s390/kvm/kvm-s390.c                         |   1 +
 arch/s390/kvm/priv.c                             |   4 +-
 arch/x86/include/asm/kvm_host.h                  |   4 +-
 arch/x86/kvm/ioapic.c                            |  10 +-
 arch/x86/kvm/svm/svm.c                           |   2 +
 arch/x86/kvm/vmx/nested.c                        |   2 +-
 arch/x86/kvm/vmx/vmenter.S                       |   3 +
 arch/x86/kvm/x86.c                               |  21 +-
 tools/testing/selftests/kvm/include/evmcs.h      |   4 +-
 tools/testing/selftests/kvm/lib/x86_64/vmx.c     |   3 +
 virt/kvm/arm/hyp/aarch32.c                       |   8 +-
 virt/kvm/arm/psci.c                              |  40 ++++
 virt/kvm/arm/vgic/vgic-init.c                    |  19 +-
 virt/kvm/arm/vgic/vgic-its.c                     |  11 +-
 virt/kvm/arm/vgic/vgic-mmio-v2.c                 |  16 +-
 virt/kvm/arm/vgic/vgic-mmio-v3.c                 |  31 +--
 virt/kvm/arm/vgic/vgic-mmio.c                    | 228 ++++++++++++++-----
 virt/kvm/arm/vgic/vgic-mmio.h                    |  19 ++
 25 files changed, 628 insertions(+), 125 deletions(-)
 create mode 100644 Documentation/virt/kvm/running-nested-guests.rst
```
#### [PATCH resend 1/2] KVM: arm64: Clean up the checking for huge mapping
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zenghui Yu <yuzenghui@huawei.com>
X-Patchwork-Id: 11533509
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D226981
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 12:36:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id BAB3120735
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 12:36:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726518AbgEGMgh (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 08:36:37 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:48596 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1725947AbgEGMgh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 08:36:37 -0400
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 920F063535DED5715A9D;
        Thu,  7 May 2020 20:36:31 +0800 (CST)
Received: from DESKTOP-8RFUVS3.china.huawei.com (10.173.222.27) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.487.0; Thu, 7 May 2020 20:36:23 +0800
From: Zenghui Yu <yuzenghui@huawei.com>
To: <kvmarm@lists.cs.columbia.edu>, <suzuki.poulose@arm.com>
CC: <maz@kernel.org>, <christoffer.dall@arm.com>,
        <james.morse@arm.com>, <julien.thierry.kdev@gmail.com>,
        <kvm@vger.kernel.org>, <linux-arm-kernel@lists.infradead.org>,
        <linux-kernel@vger.kernel.org>, <wanghaibin.wang@huawei.com>,
        <zhengxiang9@huawei.com>, <amurray@thegoodpenguin.co.uk>,
        <eric.auger@redhat.com>, Zenghui Yu <yuzenghui@huawei.com>
Subject: [PATCH resend 1/2] KVM: arm64: Clean up the checking for huge mapping
Date: Thu, 7 May 2020 20:35:45 +0800
Message-ID: <20200507123546.1875-2-yuzenghui@huawei.com>
X-Mailer: git-send-email 2.23.0.windows.1
In-Reply-To: <20200507123546.1875-1-yuzenghui@huawei.com>
References: <20200507123546.1875-1-yuzenghui@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.173.222.27]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Suzuki K Poulose <suzuki.poulose@arm.com>

If we are checking whether the stage2 can map PAGE_SIZE,
we don't have to do the boundary checks as both the host
VMA and the guest memslots are page aligned. Bail the case
easily.

While we're at it, fixup a typo in the comment below.

Cc: Christoffer Dall <christoffer.dall@arm.com>
Cc: Marc Zyngier <maz@kernel.org>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
---
 virt/kvm/arm/mmu.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: Replace zero-length array with flexible-array
##### From: "Gustavo A. R. Silva" <gustavoars@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Gustavo A. R. Silva" <gustavoars@kernel.org>
X-Patchwork-Id: 11534713
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id ADD7F14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 18:51:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 972212495D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 18:51:51 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1588877511;
	bh=+83EaeRY/7OLMLTOiUPtLBN9CV5OHRJu2uYjreh/MG0=;
	h=Date:From:To:Cc:Subject:List-ID:From;
	b=UgGtM+bh4zRHakd1r5o9/dB0n08EiTmegzgZOL1CuXnxxPuQyIULO5rg1tPN6yhna
	 lt8YTtUQ68mP1ZQoynoIAxgsbzg9v7NAy22jO88gBNHB6dwno5tHX+46UT7oVRFmWT
	 avX72i7TQmkBqAheIZPCQm/pm1v2lrDpBjPFzhis=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728743AbgEGSvr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 14:51:47 -0400
Received: from mail.kernel.org ([198.145.29.99]:52510 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728110AbgEGSvr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 14:51:47 -0400
Received: from embeddedor (unknown [189.207.59.248])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id E9A0624957;
        Thu,  7 May 2020 18:51:46 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1588877507;
        bh=+83EaeRY/7OLMLTOiUPtLBN9CV5OHRJu2uYjreh/MG0=;
        h=Date:From:To:Cc:Subject:From;
        b=PJ9CpzulMqFvltlGIQj6v0A68/uG35qnUgsPfyAL/pyESRGYYy8Yvjecbm4OdF+mQ
         2E7OIngP0zMiAMNU7IMfUW3f891p4uTzeWROnLP9rhleYm3gYfEKPKK+r35gjqTpfm
         9BxPdRbQdLG3xoxDPiKXSq8Ay3jpaBIhZ/DHn5j4=
Date: Thu, 7 May 2020 13:56:13 -0500
From: "Gustavo A. R. Silva" <gustavoars@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: Replace zero-length array with flexible-array
Message-ID: <20200507185613.GA14808@embeddedor>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.9.4 (2018-02-28)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current codebase makes use of the zero-length array language
extension to the C90 standard, but the preferred mechanism to declare
variable-length types such as these ones is a flexible array member[1][2],
introduced in C99:

struct foo {
        int stuff;
        struct boo array[];
};

By making use of the mechanism above, we will get a compiler warning
in case the flexible array does not occur last in the structure, which
will help us prevent some kind of undefined behavior bugs from being
inadvertently introduced[3] to the codebase from now on.

Also, notice that, dynamic memory allocations won't be affected by
this change:

"Flexible array members have incomplete type, and so the sizeof operator
may not be applied. As a quirk of the original implementation of
zero-length arrays, sizeof evaluates to zero."[1]

sizeof(flexible-array-member) triggers a warning because flexible array
members have incomplete type[1]. There are some instances of code in
which the sizeof operator is being incorrectly/erroneously applied to
zero-length arrays and the result is zero. Such instances may be hiding
some bugs. So, this work (flexible-array member conversions) will also
help to get completely rid of those sorts of issues.

This issue was found with the help of Coccinelle.

[1] https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html
[2] https://github.com/KSPP/linux/issues/21
[3] commit 76497732932f ("cxgb3/l2t: Fix undefined behaviour")

Signed-off-by: Gustavo A. R. Silva <gustavoars@kernel.org>
---
 include/linux/kvm_host.h |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/9] KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11533235
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F7E3139F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 11:51:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 278D521582
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 11:51:18 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hMF7qf6x"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727849AbgEGLvR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 07:51:17 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:29738 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726308AbgEGLuT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 7 May 2020 07:50:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588852218;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=h2l3KOMDutolAkEtGy6K6Owvl6fNHONxFxSaO2J+VP4=;
        b=hMF7qf6xYyIH6PqiJSsC9KDNQP/GynhJYPwF1hioypRNTDT33Jjp+2PrSEFGIIV5N8tXHH
        /+sg97hiLvcj/+M5kUFteoMXN0q4hYT99hR+JS936tkHe9eipOM+WZIxjk4waKsflrZAnD
        d59rUIjM2KVxIUGTyKcAcOWHhf/Vses=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-386-BuECpVyTNryiHOA58JYFOQ-1; Thu, 07 May 2020 07:50:16 -0400
X-MC-Unique: BuECpVyTNryiHOA58JYFOQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 807B51895A29;
        Thu,  7 May 2020 11:50:15 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 24DF62E041;
        Thu,  7 May 2020 11:50:15 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: peterx@redhat.com
Subject: [PATCH v2 1/9] KVM: X86: Declare KVM_CAP_SET_GUEST_DEBUG properly
Date: Thu,  7 May 2020 07:50:03 -0400
Message-Id: <20200507115011.494562-2-pbonzini@redhat.com>
In-Reply-To: <20200507115011.494562-1-pbonzini@redhat.com>
References: <20200507115011.494562-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Xu <peterx@redhat.com>

KVM_CAP_SET_GUEST_DEBUG should be supported for x86 however it's not declared
as supported.  My wild guess is that userspaces like QEMU are using "#ifdef
KVM_CAP_SET_GUEST_DEBUG" to check for the capability instead, but that could be
wrong because the compilation host may not be the runtime host.

The userspace might still want to keep the old "#ifdef" though to not break the
guest debug on old kernels.

Signed-off-by: Peter Xu <peterx@redhat.com>
Message-Id: <20200505154750.126300-1-peterx@redhat.com>
[Do the same for PPC and s390. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/powerpc/kvm/powerpc.c | 1 +
 arch/s390/kvm/kvm-s390.c   | 1 +
 arch/x86/kvm/x86.c         | 1 +
 3 files changed, 3 insertions(+)

```
#### [PATCH] KVM: VMX: Replace zero-length array with flexible-array
##### From: "Gustavo A. R. Silva" <gustavoars@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Gustavo A. R. Silva" <gustavoars@kernel.org>
X-Patchwork-Id: 11534715
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4DB9615AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 18:51:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 388F924961
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 18:51:56 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1588877516;
	bh=zzvNz1vCMUzUeBqErf8Y+hXv+ekNJ/H+9YqrTouDhq0=;
	h=Date:From:To:Cc:Subject:List-ID:From;
	b=AA5JGZlsW4xR3v0SNfSc2Zk0jjtpgJWrtO1U26+SHZuZ5zR73CW/g4noJEFRFjjSs
	 vGgLktZ7PfTIhjL3+SBxALhF+p4RmrWi1HFFTLgNG/QBxrNfqA1YJuGv8KMQrcecU3
	 OnDWuIyzH8PdbpIqoA5CtjrgNncL19YPiXbBT0xI=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728760AbgEGSvx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 14:51:53 -0400
Received: from mail.kernel.org ([198.145.29.99]:52626 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726761AbgEGSvx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 14:51:53 -0400
Received: from embeddedor (unknown [189.207.59.248])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 2806A24959;
        Thu,  7 May 2020 18:51:52 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1588877512;
        bh=zzvNz1vCMUzUeBqErf8Y+hXv+ekNJ/H+9YqrTouDhq0=;
        h=Date:From:To:Cc:Subject:From;
        b=RwFhaoWMFjAjpOVDoA285PYVW+aLxxIiFivqXm1pwGc9kXYPiKKDR5Yj5kYob+G00
         asc5kpTlDem0K9m3ptWpLrfg2WiaUeRKL5lbvxQQiO6ZaxKv4muzu+7iF9CPCR4Nw8
         4oBK1ojgP16NGqrHIgHKIZMPItRKOdzrUATnvAw4=
Date: Thu, 7 May 2020 13:56:18 -0500
From: "Gustavo A. R. Silva" <gustavoars@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: VMX: Replace zero-length array with flexible-array
Message-ID: <20200507185618.GA14831@embeddedor>
MIME-Version: 1.0
Content-Disposition: inline
User-Agent: Mutt/1.9.4 (2018-02-28)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The current codebase makes use of the zero-length array language
extension to the C90 standard, but the preferred mechanism to declare
variable-length types such as these ones is a flexible array member[1][2],
introduced in C99:

struct foo {
        int stuff;
        struct boo array[];
};

By making use of the mechanism above, we will get a compiler warning
in case the flexible array does not occur last in the structure, which
will help us prevent some kind of undefined behavior bugs from being
inadvertently introduced[3] to the codebase from now on.

Also, notice that, dynamic memory allocations won't be affected by
this change:

"Flexible array members have incomplete type, and so the sizeof operator
may not be applied. As a quirk of the original implementation of
zero-length arrays, sizeof evaluates to zero."[1]

sizeof(flexible-array-member) triggers a warning because flexible array
members have incomplete type[1]. There are some instances of code in
which the sizeof operator is being incorrectly/erroneously applied to
zero-length arrays and the result is zero. Such instances may be hiding
some bugs. So, this work (flexible-array member conversions) will also
help to get completely rid of those sorts of issues.

This issue was found with the help of Coccinelle.

[1] https://gcc.gnu.org/onlinedocs/gcc/Zero-Length.html
[2] https://github.com/KSPP/linux/issues/21
[3] commit 76497732932f ("cxgb3/l2t: Fix undefined behaviour")

Signed-off-by: Gustavo A. R. Silva <gustavoars@kernel.org>
---
 arch/x86/kvm/vmx/vmcs.h |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: SVM: Disable AVIC before setting V_IRQ
##### From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Suravee Suthikulpanit <Suravee.Suthikulpanit@amd.com>
X-Patchwork-Id: 11532347
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0286492A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 02:35:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DAA2A2087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 02:35:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="Wjfjz2Tj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728003AbgEGCft (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 22:35:49 -0400
Received: from mail-dm6nam10on2084.outbound.protection.outlook.com
 ([40.107.93.84]:6058
        "EHLO NAM10-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726218AbgEGCft (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 22:35:49 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=ctsxaRxcRoM8DInmPZ7iHRqV7SCiZdvPboCEjSwm2ytd7DP2AWNAIPQBhyfPMWiokU5PCxI4tZ4zFFyL2fRWMM0SO9+umkQeQZSPMBE6iJ1Q14/G/r2ZGkSuWQa/wrTp5fU9a6uWlXihTwfGM6BiL/Vo71ZOk9xKJNc2xORC8dTjrEOxQFEvWNq1NCGMPYEdzEelsTUBtkriSYND2mqeSvKqAVxWkQWtk5ekkEwOuljApxOyn03E0FSra1YOlZ/jsUQz+Rs3PsKwPDuePsMBFKAXmyMyOyOimDISXepBey2pyWKQzlQh8LfdbyY4HpjVZxsWWMJEmoTOJu7swjV0mQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=8G7Ca0agfDFFQ3J1uPht5rubdXkJpsWQ9jleN+Qzjpg=;
 b=U6bW2Y8I+K/vAj/xLazjlM3rT7iV3uJWIxGfjC5RlJ+ZxFlAu0RjHzTM8eeb8y0N/RuO7kIw+MLRjJAt8fhbMGAGFRBiJbH0jYO4JMjyaVdvmvLxY7sYQuZi5v6y5mAgUniSYqhN4CNQt/7i/00z9QB3+I5uImUXvLdS/H/WqLsPqf1g9Z3IKJjnK6JaG5iJsBXMT9P3hLjZ6NFYf3DIbn3cTHaAV6B6xXj4Xc5vJvbhPrcpnOiRRF0EQaT8KX930ZLKk2kAHSIxUbKjyaoMZKAElfHK08TwVCOb2TjsrpdeSFxESzyIi6yM1IpIA/ckhkZuLefvtOcna8AnufRJAw==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=8G7Ca0agfDFFQ3J1uPht5rubdXkJpsWQ9jleN+Qzjpg=;
 b=Wjfjz2TjQNQNrTlb/GT49Rr+8OskLHdBzSMEdAYv7pCxQ1h2K8qWxgpPYEOemfvEvpoLLH29Dv39/JjpNNyXRb0VdvKuydcIbrdN91NdVTwi+Rgsj96SpUqvTulX/DxiS4/cgyH02zb51UewvTds4Z5hB52K838X2daP/hl1YhM=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1163.namprd12.prod.outlook.com (2603:10b6:3:7a::18) by
 DM5PR12MB1130.namprd12.prod.outlook.com (2603:10b6:3:75::19) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2958.20; Thu, 7 May 2020 02:35:45 +0000
Received: from DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::d061:4c5:954e:4744]) by DM5PR12MB1163.namprd12.prod.outlook.com
 ([fe80::d061:4c5:954e:4744%4]) with mapi id 15.20.2958.030; Thu, 7 May 2020
 02:35:45 +0000
From: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: pbonzini@redhat.com, joro@8bytes.org, jon.grimm@amd.com,
        mlevitsk@redhat.com,
        Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Subject: [PATCH v2] KVM: SVM: Disable AVIC before setting V_IRQ
Date: Wed,  6 May 2020 21:35:39 -0500
Message-Id: <1588818939-54264-1-git-send-email-suravee.suthikulpanit@amd.com>
X-Mailer: git-send-email 1.8.3.1
X-ClientProxiedBy: SN4PR0201CA0051.namprd02.prod.outlook.com
 (2603:10b6:803:20::13) To DM5PR12MB1163.namprd12.prod.outlook.com
 (2603:10b6:3:7a::18)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ssuthiku-rhel7-ssp.amd.com (165.204.78.2) by
 SN4PR0201CA0051.namprd02.prod.outlook.com (2603:10b6:803:20::13) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2979.26 via Frontend
 Transport; Thu, 7 May 2020 02:35:45 +0000
X-Mailer: git-send-email 1.8.3.1
X-Originating-IP: [165.204.78.2]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 207996f9-af26-4e9f-177f-08d7f22f5850
X-MS-TrafficTypeDiagnostic: DM5PR12MB1130:|DM5PR12MB1130:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM5PR12MB11307F02672977B7FE769C88F3A50@DM5PR12MB1130.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:983;
X-Forefront-PRVS: 03965EFC76
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 LA8P/Y6JxDI91OQNn738QNxhUzxkUuV5MwJRHPoQy+Z/Q3SvIBzUQ7IxwSSs9/vTRIuYD+zjQ/F/eyJaxiv/aEW9VWCWkliYQ9TYleTQcz/dZu1pbRavrktphoqBho6CkPVSv9Ob5tBHQkoD59+EybySCiKxZC5Dpxm0AnirAWoTpklVpo1xcrPhEAHBBJqHK/AGFrQMfSrRQo+bFh1KaSR1oS7DOPlSuXUH7CgVRHV7QadO/66h00ssR24cmRn1FcJtQxbb+qb11LJ4ZV4vA1EcZXFDxidEHCwzEWFa/71Lqg3rDMKIVJAiKusnSyYW7JeF5X+qjaW8qzuG5qmCt5rgFL4DzojoJ/1w+SPYxYiDu0IT+DK/zJL4s7hEgrpKZeX2FTGay3HwLJBqaJG+nrZ7owi64HXt2wBbOJpCaFI5gXAY28xORlIb9Wppjr1MRswKN7jayWWwV9Jq/i+ae9EJ0PtKK0d5vS4vizwJhW2GS13852C27K3lgsAv+l1gDt0OKxTMSuTBzPPL2wtJNFsSKJ6Cr3PQid3h2KM9UdNCLhxsOm/7RjEti5ZJKg6lyngzmc4iNj7meVPStkcdtGMA3ZRwOfEe0nVcqPAnxN4=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1163.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFTY:;SFS:(4636009)(39860400002)(136003)(366004)(376002)(346002)(396003)(33430700001)(66946007)(8676002)(66556008)(8936002)(5660300002)(66476007)(4326008)(52116002)(16526019)(26005)(7696005)(966005)(6486002)(2906002)(478600001)(186003)(36756003)(316002)(2616005)(44832011)(33440700001)(6666004)(956004)(86362001)(83300400001)(83310400001)(83320400001)(83280400001)(83290400001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 Y8+oeBfM0pPiW4vwcyTmbVZeMFYcHcIc3w3LJU04hjNgkkty9sc6xTacKMal7hlBZTG9r5NlkuoiESWHizsN4ufRUTlEV7WGYbcHKFrTJQVe0v3nVEFxBSeYWot9y+Tk/Dy9CWWAiwiKEEHWbxj82VWUH0AkSSavys+xePriqeel83TAoVYQlu49j3laNPqifLVA3iYFruZXuURreu8uKpvW19Vyb1yYcKTHs7wn80Tnue58cWnvmyfex/jAl/QV6ZjZHnxpaIoM3zhL6Yczud3zb8Dl3ZfwSNX6H0O45qw5ICBnhnjZhxrp+LHHtqv2pHZGa+7aq3Z+iNMayohaTBAOnFUiseIsGcU5JZYm8M4KoExbvyZN5lX4wXWYwyO7KaXmOlKQW3VsKrJ+hlwaIwOohaySvEem1vWejbtRaIIE5YIFOpEx9eEdaIZIkJ/nLu/3IRgBCzP5p1uVgABtQmDEzyjKNU+5A/hWcWiFwq/wGtm7sgQx26SsSFPlb09HJHG2F4f5Lj9Pae34JzwfsqO8o1E//vx4ap+KYKN7fakxz276agR1Leri5j94y5mDmzw1olrXUDM8Iya07i33AASuADPwzRZskVzWRyonhhTEF5oASfTnqd06UCRBLPTs5m240eaRqrkNatUAf6NjIXY3etSoTOVgKM6OK66xEWfWwpah3z0kFPbDaGIbfQMHTltFPI6y2pXhFOpqudiGWvgTBgyf57MX3s+VI2Ypbu9rx/62PvVBzziB06w9/WlpjIZnsuQoKjVqVWAS4hNGQ60xqoNVv9bvePMutKSqc1s=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 207996f9-af26-4e9f-177f-08d7f22f5850
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 07 May 2020 02:35:45.7392
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 DDn//I0STdTOc44A4YMJj+U1N9AY14vbYsw1r94xtrL20mPmvEEQ/H16MNjNzkOTHdAcyqZVWPjSuhTWBypc+g==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM5PR12MB1130
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The commit 64b5bd270426 ("KVM: nSVM: ignore L1 interrupt window
while running L2 with V_INTR_MASKING=1") introduced a WARN_ON,
which checks if AVIC is enabled when trying to set V_IRQ
in the VMCB for enabling irq window.

The following warning is triggered because the requesting vcpu
(to deactivate AVIC) does not get to process APICv update request
for itself until the next #vmexit.

WARNING: CPU: 0 PID: 118232 at arch/x86/kvm/svm/svm.c:1372 enable_irq_window+0x6a/0xa0 [kvm_amd]
 RIP: 0010:enable_irq_window+0x6a/0xa0 [kvm_amd]
 Call Trace:
  kvm_arch_vcpu_ioctl_run+0x6e3/0x1b50 [kvm]
  ? kvm_vm_ioctl_irq_line+0x27/0x40 [kvm]
  ? _copy_to_user+0x26/0x30
  ? kvm_vm_ioctl+0xb3e/0xd90 [kvm]
  ? set_next_entity+0x78/0xc0
  kvm_vcpu_ioctl+0x236/0x610 [kvm]
  ksys_ioctl+0x8a/0xc0
  __x64_sys_ioctl+0x1a/0x20
  do_syscall_64+0x58/0x210
  entry_SYSCALL_64_after_hwframe+0x44/0xa9

Fixes by sending APICV update request to all other vcpus, and
immediately update APIC for itself.

Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
Link: https://lkml.org/lkml/2020/5/2/167
Fixes: 64b5bd270426 ("KVM: nSVM: ignore L1 interrupt window while running L2 with V_INTR_MASKING=1")
---
 arch/x86/kvm/x86.c | 13 ++++++++++++-
 1 file changed, 12 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: VMX: Fix operand constraint of PUSH instructions
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Uros Bizjak <ubizjak@gmail.com>
X-Patchwork-Id: 11532853
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 01B3292A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 08:44:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DCD002083B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 08:44:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="WU6iyPzX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725949AbgEGIo4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 04:44:56 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:51654 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725809AbgEGIoz (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 04:44:55 -0400
Received: from mail-wm1-x344.google.com (mail-wm1-x344.google.com
 [IPv6:2a00:1450:4864:20::344])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 4DD8DC061A10
        for <kvm@vger.kernel.org>; Thu,  7 May 2020 01:44:55 -0700 (PDT)
Received: by mail-wm1-x344.google.com with SMTP id 188so5488947wmc.2
        for <kvm@vger.kernel.org>; Thu, 07 May 2020 01:44:55 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=PU7avU5KLld7I6xnGMnybddyyBfXBbnu4ZRjbpdICJw=;
        b=WU6iyPzXjetTb4A8FHXJ6TZ1lAnGwZ10FXhgUJdKGf/nLtAQwSN6FLvTLdBCPQs5e/
         haGqya1wJVGSnWblIX2mxmgIMlPRyMw0DndrJ0SSKY8uPY6TL38/7dlRCVxro98jLZwu
         Ytvv2SjUgBOqM7PSMEsDihXoVdIvNdRBau7mxR9vtsLf0ZS2IA5vXPsP0gDwuHDFvHie
         cPpP/i7rIsgZ7ml1NacOfHrM14ZXwqqo77anTzZN1vAInMXJrvJsw/vmM2EGxjx2gGAr
         e/87JXnbI9IkKvWfZCDdRAeVjvKcg++6v1UZLrsGOF3Yje8uaXOQQakkmci4D0Ut679J
         I8sw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=PU7avU5KLld7I6xnGMnybddyyBfXBbnu4ZRjbpdICJw=;
        b=axxlVWgi42hjwfkXlMfgne92ledjXEBJeCzfTVeq5zWQqodyju9i3YJnHi3LPrQZl2
         uuiCJdbzonekRHmzNgFOL4wK6ssgDvxxwmt8QJoIY/ER4/PbYuRbawmJEHhf7OAcJ3hQ
         disZbBjNcXg1BfVx9rveuSB+remLk3pmK9qqa3Nt2L+hMl4c5XgRv6gacT0ACIjIKJC3
         07RBIp5SLvAzfG0Tm2fZvO2DsAdxCSDGYi+fCAcEJWBdBpKQtaUotfNCDm08BGW+X4/I
         VtnkVGj0/tw8uaPKapFma7ocpHACVJXNbVgTeN4eDzEaDHDr1iXwyIYEuUvjQYgiAc9a
         Psew==
X-Gm-Message-State: AGi0PuY8vxvSr4jq2K8dDUaZcYZgEB/rL1DB9Kloyfx8Zm7lw5du0QwG
        8fwsLiu4h5NDgKiFJKzSzCwDOoVKAp8=
X-Google-Smtp-Source: 
 APiQypLXBKZPf9frSIx0Q/EiP927405tYWl11FO5QPPY2TAWgxz6TxS3Jw5pmSuBRdIitGL8IRV8PQ==
X-Received: by 2002:a1c:3281:: with SMTP id y123mr9158534wmy.30.1588841093739;
        Thu, 07 May 2020 01:44:53 -0700 (PDT)
Received: from localhost.localdomain (93-103-18-160.static.t-2.net.
 [93.103.18.160])
        by smtp.gmail.com with ESMTPSA id
 f26sm6943031wmj.11.2020.05.07.01.44.52
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Thu, 07 May 2020 01:44:52 -0700 (PDT)
From: Uros Bizjak <ubizjak@gmail.com>
To: kvm@vger.kernel.org
Cc: Uros Bizjak <ubizjak@gmail.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH v2] KVM: VMX: Fix operand constraint of PUSH instructions
Date: Thu,  7 May 2020 10:44:37 +0200
Message-Id: <20200507084437.321212-1-ubizjak@gmail.com>
X-Mailer: git-send-email 2.25.4
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

PUSH instructions can't handle 64-bit immediate operands, so "i"
operand constraint is not correct. Use "er" operand constraint
to limit the range of the immediate operand to a signed 32-bit
value and also to leave the compiler the freedom to pass the value
via the register.

Please note that memory operands are not allowed here. These
operands include stack slots, and these are not valid in this
asm block due to the clobbered %rsp register.

v2: Add casts.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/vmx/vmx.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v2] KVM: x86/pmu: Support full width counting
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11532333
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2BCCB92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 02:15:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 172E2206B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 02:15:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727105AbgEGCO6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 6 May 2020 22:14:58 -0400
Received: from mga07.intel.com ([134.134.136.100]:51519 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725809AbgEGCO6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 6 May 2020 22:14:58 -0400
IronPort-SDR: 
 6+o5o9Z8Nei5ikD7cVdrsq+LH3/i3l3edyJZCTHd+gqSOdJbrpmyyYk68JJf3VhnKy4fb029Av
 b6sbRbHwWGrQ==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 06 May 2020 19:14:57 -0700
IronPort-SDR: 
 fw44h69tpA8aEv4BASRoUBgr4ADobJFK+151kyMvE1I+gBX5dTBNNDPw12opxqiLEgankTFDXc
 feNhsAPwH3ig==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,361,1583222400";
   d="scan'208";a="251376347"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by fmsmga008.fm.intel.com with ESMTP; 06 May 2020 19:14:53 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Like Xu <like.xu@linux.intel.com>
Subject: [PATCH v2] KVM: x86/pmu: Support full width counting
Date: Thu,  7 May 2020 10:14:52 +0800
Message-Id: <20200507021452.174646-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Intel CPUs have a new alternative MSR range (starting from MSR_IA32_PMC0)
for GP counters that allows writing the full counter width. Enable this
range from a new capability bit (IA32_PERF_CAPABILITIES.FW_WRITE[bit 13]).

The guest would query CPUID to get the counter width, and sign extends
the counter values as needed. The traditional MSRs always limit to 32bit,
even though the counter internally is larger (usually 48 bits).

When the new capability is set, use the alternative range which do not
have these restrictions. This lowers the overhead of perf stat slightly
because it has to do less interrupts to accumulate the counter value.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/cpuid.c            |  2 +-
 arch/x86/kvm/vmx/capabilities.h | 15 ++++++++++++++
 arch/x86/kvm/vmx/pmu_intel.c    | 35 +++++++++++++++++++++++++++++----
 arch/x86/kvm/vmx/vmx.c          |  5 +++++
 arch/x86/kvm/x86.c              |  8 ++++++++
 6 files changed, 61 insertions(+), 5 deletions(-)

```
#### [PATCH v3 01/15] virtio-mem: Paravirtualized memory hotplug
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11533049
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6D1FE139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 10:33:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3BD7F20CC7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 10:33:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PEBviJOq"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726565AbgEGKcY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 06:32:24 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:23106 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726470AbgEGKcT (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 7 May 2020 06:32:19 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588847533;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=k2OhcsLgMCCLNJM+/+KyVTsfTQY12HesKlmdjf922u0=;
        b=PEBviJOqqxOL9edMq3IWtHYPE7mD/2JwvbgKeEO03Nv9gMgMFvEgvK8GaItaGajcxTkyeg
        K7zZbumjMfA2mt5TQ+Hk5HwdmH5QVtBKfYWbiwzOLF11UaKHTGbs7kwVar3jdbl+tuw4CG
        2Nhpc4f4awmrRiBzHj5usukwXjRkYQo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-152-tj6qOR9MMcCKKtGykjwt4g-1; Thu, 07 May 2020 06:32:07 -0400
X-MC-Unique: tj6qOR9MMcCKKtGykjwt4g-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3D24019200C2;
        Thu,  7 May 2020 10:32:05 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-245.ams2.redhat.com [10.36.113.245])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 513855D9DA;
        Thu,  7 May 2020 10:31:51 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: linux-mm@kvack.org, virtio-dev@lists.oasis-open.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Michal Hocko <mhocko@kernel.org>,
        Andrew Morton <akpm@linux-foundation.org>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Pankaj Gupta <pankaj.gupta.linux@gmail.com>,
        Jason Wang <jasowang@redhat.com>,
        Oscar Salvador <osalvador@suse.de>,
        Igor Mammedov <imammedo@redhat.com>,
        Dave Young <dyoung@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Vlastimil Babka <vbabka@suse.cz>,
        "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Len Brown <lenb@kernel.org>, linux-acpi@vger.kernel.org
Subject: [PATCH v3 01/15] virtio-mem: Paravirtualized memory hotplug
Date: Thu,  7 May 2020 12:31:05 +0200
Message-Id: <20200507103119.11219-2-david@redhat.com>
In-Reply-To: <20200507103119.11219-1-david@redhat.com>
References: <20200507103119.11219-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Each virtio-mem device owns exactly one memory region. It is responsible
for adding/removing memory from that memory region on request.

When the device driver starts up, the requested amount of memory is
queried and then plugged to Linux. On request, further memory can be
plugged or unplugged. This patch only implements the plugging part.

On x86-64, memory can currently be plugged in 4MB ("subblock") granularity.
When required, a new memory block will be added (e.g., usually 128MB on
x86-64) in order to plug more subblocks. Only x86-64 was tested for now.

The online_page callback is used to keep unplugged subblocks offline
when onlining memory - similar to the Hyper-V balloon driver. Unplugged
pages are marked PG_offline, to tell dump tools (e.g., makedumpfile) to
skip them.

User space is usually responsible for onlining the added memory. The
memory hotplug notifier is used to synchronize virtio-mem activity
against memory onlining/offlining.

Each virtio-mem device can belong to a NUMA node, which allows us to
easily add/remove small chunks of memory to/from a specific NUMA node by
using multiple virtio-mem devices. Something that works even when the
guest has no idea about the NUMA topology.

One way to view virtio-mem is as a "resizable DIMM" or a DIMM with many
"sub-DIMMS".

This patch directly introduces the basic infrastructure to implement memory
unplug. Especially the memory block states and subblock bitmaps will be
heavily used there.

Notes:
- In case memory is to be onlined by user space, we limit the amount of
  offline memory blocks, to not run out of memory. This is esp. an
  issue if memory is added faster than it is getting onlined.
- Suspend/Hibernate is not supported due to the way virtio-mem devices
  behave. Limited support might be possible in the future.
- Reloading the device driver is not supported.

Reviewed-by: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
Tested-by: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Jason Wang <jasowang@redhat.com>
Cc: Oscar Salvador <osalvador@suse.de>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Igor Mammedov <imammedo@redhat.com>
Cc: Dave Young <dyoung@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Pavel Tatashin <pasha.tatashin@soleen.com>
Cc: Stefan Hajnoczi <stefanha@redhat.com>
Cc: Vlastimil Babka <vbabka@suse.cz>
Cc: "Rafael J. Wysocki" <rjw@rjwysocki.net>
Cc: Len Brown <lenb@kernel.org>
Cc: linux-acpi@vger.kernel.org
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 drivers/virtio/Kconfig          |   16 +
 drivers/virtio/Makefile         |    1 +
 drivers/virtio/virtio_mem.c     | 1533 +++++++++++++++++++++++++++++++
 include/uapi/linux/virtio_ids.h |    1 +
 include/uapi/linux/virtio_mem.h |  200 ++++
 5 files changed, 1751 insertions(+)
 create mode 100644 drivers/virtio/virtio_mem.c
 create mode 100644 include/uapi/linux/virtio_mem.h

```
#### [PATCH v4 01/15] virtio-mem: Paravirtualized memory hotplug
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11533885
Return-Path: <SRS0=eykK=6V=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8FF5B912
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 14:02:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5FEAC20838
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  7 May 2020 14:02:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hbUYsljW"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727110AbgEGOCn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 7 May 2020 10:02:43 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:55839 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726913AbgEGOCl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 7 May 2020 10:02:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1588860150;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=oLDi6FYkUrzlPuVVL59bSwiB1VdnsS5ln6uTiqorFC4=;
        b=hbUYsljWrEQFd03EG2C97mE8+RWtg6cRVVDfg3VtIw3vnMt/eR9/IvVRRK4P+FsZSpr8OS
        KO2yyAMO0qMZgLCe35cAh4U7yTGe2S4d34rpdrEv9yglMwdCkJcJYJuiX/spVIVdkruNIG
        3pizpSdQ/M0goQB/rskId3nMXKbN2K4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-159-UabHRN9fMG-fs9pcOG5ong-1; Thu, 07 May 2020 10:02:13 -0400
X-MC-Unique: UabHRN9fMG-fs9pcOG5ong-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A64868BF62A;
        Thu,  7 May 2020 14:02:11 +0000 (UTC)
Received: from t480s.redhat.com (ovpn-113-245.ams2.redhat.com [10.36.113.245])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2152E610AB;
        Thu,  7 May 2020 14:01:58 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: linux-mm@kvack.org, virtio-dev@lists.oasis-open.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Michal Hocko <mhocko@kernel.org>,
        Andrew Morton <akpm@linux-foundation.org>,
        "Michael S . Tsirkin" <mst@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Pankaj Gupta <pankaj.gupta.linux@gmail.com>,
        Jason Wang <jasowang@redhat.com>,
        Oscar Salvador <osalvador@suse.de>,
        Igor Mammedov <imammedo@redhat.com>,
        Dave Young <dyoung@redhat.com>,
        Dan Williams <dan.j.williams@intel.com>,
        Pavel Tatashin <pasha.tatashin@soleen.com>,
        Stefan Hajnoczi <stefanha@redhat.com>,
        Vlastimil Babka <vbabka@suse.cz>,
        "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Len Brown <lenb@kernel.org>, linux-acpi@vger.kernel.org
Subject: [PATCH v4 01/15] virtio-mem: Paravirtualized memory hotplug
Date: Thu,  7 May 2020 16:01:25 +0200
Message-Id: <20200507140139.17083-2-david@redhat.com>
In-Reply-To: <20200507140139.17083-1-david@redhat.com>
References: <20200507140139.17083-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Each virtio-mem device owns exactly one memory region. It is responsible
for adding/removing memory from that memory region on request.

When the device driver starts up, the requested amount of memory is
queried and then plugged to Linux. On request, further memory can be
plugged or unplugged. This patch only implements the plugging part.

On x86-64, memory can currently be plugged in 4MB ("subblock") granularity.
When required, a new memory block will be added (e.g., usually 128MB on
x86-64) in order to plug more subblocks. Only x86-64 was tested for now.

The online_page callback is used to keep unplugged subblocks offline
when onlining memory - similar to the Hyper-V balloon driver. Unplugged
pages are marked PG_offline, to tell dump tools (e.g., makedumpfile) to
skip them.

User space is usually responsible for onlining the added memory. The
memory hotplug notifier is used to synchronize virtio-mem activity
against memory onlining/offlining.

Each virtio-mem device can belong to a NUMA node, which allows us to
easily add/remove small chunks of memory to/from a specific NUMA node by
using multiple virtio-mem devices. Something that works even when the
guest has no idea about the NUMA topology.

One way to view virtio-mem is as a "resizable DIMM" or a DIMM with many
"sub-DIMMS".

This patch directly introduces the basic infrastructure to implement memory
unplug. Especially the memory block states and subblock bitmaps will be
heavily used there.

Notes:
- In case memory is to be onlined by user space, we limit the amount of
  offline memory blocks, to not run out of memory. This is esp. an
  issue if memory is added faster than it is getting onlined.
- Suspend/Hibernate is not supported due to the way virtio-mem devices
  behave. Limited support might be possible in the future.
- Reloading the device driver is not supported.

Reviewed-by: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
Tested-by: Pankaj Gupta <pankaj.gupta.linux@gmail.com>
Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Jason Wang <jasowang@redhat.com>
Cc: Oscar Salvador <osalvador@suse.de>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Igor Mammedov <imammedo@redhat.com>
Cc: Dave Young <dyoung@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Pavel Tatashin <pasha.tatashin@soleen.com>
Cc: Stefan Hajnoczi <stefanha@redhat.com>
Cc: Vlastimil Babka <vbabka@suse.cz>
Cc: "Rafael J. Wysocki" <rjw@rjwysocki.net>
Cc: Len Brown <lenb@kernel.org>
Cc: linux-acpi@vger.kernel.org
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 drivers/virtio/Kconfig          |   16 +
 drivers/virtio/Makefile         |    1 +
 drivers/virtio/virtio_mem.c     | 1533 +++++++++++++++++++++++++++++++
 include/uapi/linux/virtio_ids.h |    1 +
 include/uapi/linux/virtio_mem.h |  200 ++++
 5 files changed, 1751 insertions(+)
 create mode 100644 drivers/virtio/virtio_mem.c
 create mode 100644 include/uapi/linux/virtio_mem.h

```
