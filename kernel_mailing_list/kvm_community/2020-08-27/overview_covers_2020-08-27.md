

#### [PATCH RFC 0/2] Add log dirty support
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
From patchwork Thu Aug 27 08:22:49 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 11740277
Return-Path: <SRS0=uiX/=CF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 059D114E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 08:24:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EB05620738
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 08:24:00 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728284AbgH0IX5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 04:23:57 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:45806 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728265AbgH0IXy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Aug 2020 04:23:54 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 5C70C129FCFD88B23E96;
        Thu, 27 Aug 2020 16:23:48 +0800 (CST)
Received: from huawei.com (10.174.187.31) by DGGEMS402-HUB.china.huawei.com
 (10.3.19.202) with Microsoft SMTP Server id 14.3.487.0; Thu, 27 Aug 2020
 16:23:41 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <paul.walmsley@sifive.com>, <palmer@dabbelt.com>,
        <aou@eecs.berkeley.edu>, <anup.patel@wdc.com>,
        <alistair.francis@wdc.com>, <atish.patra@wdc.com>,
        <deepa.kernel@gmail.com>
CC: <kvm-riscv@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-riscv@lists.infradead.org>, <linux-kernel@vger.kernel.org>,
        <victor.zhangxiaofeng@huawei.com>, <wu.wubin@huawei.com>,
        <zhang.zhanghailiang@huawei.com>, <dengkai1@huawei.com>,
        <yinyipeng1@huawei.com>, Yifei Jiang <jiangyifei@huawei.com>
Subject: [PATCH RFC 0/2] Add log dirty support
Date: Thu, 27 Aug 2020 16:22:49 +0800
Message-ID: <20200827082251.1591-1-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.31]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series supports log dirty for migration in RISC-V KVM. Two interfaces
are added for kvm_main.c, and some bugs are fixed.

We have implemented the vm migration in Qemu. So these patches have been
tested.

This series is implemented based on https://github.com/avpatel/linux/tree/riscv_kvm_v13.

Yifei Jiang (2):
  riscv/kvm: Fix use VSIP_VALID_MASK mask HIP register
  target/kvm: Add interfaces needed for log dirty

 arch/riscv/configs/defconfig |  1 +
 arch/riscv/kvm/Kconfig       |  1 +
 arch/riscv/kvm/mmu.c         | 43 ++++++++++++++++++++++++++++++++++++
 arch/riscv/kvm/vcpu.c        |  2 +-
 arch/riscv/kvm/vm.c          |  6 -----
 5 files changed, 46 insertions(+), 7 deletions(-)
```
#### [PATCH RFC v3 00/14] Add riscv kvm accel support
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
From patchwork Thu Aug 27 09:21:23 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 11740309
Return-Path: <SRS0=uiX/=CF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8578D739
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 09:22:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 770A62177B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 09:22:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728369AbgH0JWk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 05:22:40 -0400
Received: from szxga05-in.huawei.com ([45.249.212.191]:10272 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1728228AbgH0JWh (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 27 Aug 2020 05:22:37 -0400
Received: from DGGEMS402-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id D58A74862EF1E1423524;
        Thu, 27 Aug 2020 17:22:34 +0800 (CST)
Received: from huawei.com (10.174.187.31) by DGGEMS402-HUB.china.huawei.com
 (10.3.19.202) with Microsoft SMTP Server id 14.3.487.0; Thu, 27 Aug 2020
 17:22:25 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <qemu-devel@nongnu.org>, <qemu-riscv@nongnu.org>
CC: <kvm-riscv@lists.infradead.org>, <kvm@vger.kernel.org>,
        <libvir-list@redhat.com>, <anup.patel@wdc.com>,
        <palmer@dabbelt.com>, <Alistair.Francis@wdc.com>,
        <sagark@eecs.berkeley.edu>, <kbastian@mail.uni-paderborn.de>,
        <victor.zhangxiaofeng@huawei.com>, <wu.wubin@huawei.com>,
        <zhang.zhanghailiang@huawei.com>, <dengkai1@huawei.com>,
        <yinyipeng1@huawei.com>, Yifei Jiang <jiangyifei@huawei.com>
Subject: [PATCH RFC v3 00/14] Add riscv kvm accel support
Date: Thu, 27 Aug 2020 17:21:23 +0800
Message-ID: <20200827092137.479-1-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.187.31]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds both riscv32 and riscv64 kvm support, and implements
migration based on riscv. It is based on temporarily unaccepted kvm:
https://github.com/kvm-riscv/linux

Compared to RFC v2, the migration is supported in this series. The new
added migration feature also requires the following patches:
[1]
[PATCH RFC 0/2] Add log dirty support
https://www.mail-archive.com/linux-kernel@vger.kernel.org/msg2284945.html

[2]
[PATCH] target/riscv: raise exception to HS-mode at get_physical_address
https://patchew.org/QEMU/20200824084158.1769-1-jiangyifei@huawei.com/

Several steps to use this:
1. Build emulation
$ ./configure --target-list=riscv64-softmmu
$ make -j$(nproc)

2. Build kernel
https://github.com/kvm-riscv/linux

3. Build QEMU VM
I cross built in riscv toolchain.
$ PKG_CONFIG_LIBDIR=<toolchain pkgconfig path>
$ export PKG_CONFIG_SYSROOT_DIR=<toolchain sysroot path>
$ ./configure --target-list=riscv64-softmmu --enable-kvm \
--cross-prefix=riscv64-linux-gnu- --disable-libiscsi --disable-glusterfs \
--disable-libusb --disable-usb-redir --audio-drv-list= --disable-opengl \
--disable-libxml2
$ make -j$(nproc)

4. Start emulation
$ ./qemu-system-riscv64 -M virt -m 4096M -cpu rv64,x-h=true -nographic \
        -name guest=riscv-hyp,debug-threads=on \
        -smp 4 \
        -bios ./fw_jump.bin \
        -kernel ./Image \
        -drive file=./hyp.img,format=raw,id=hd0 \
        -device virtio-blk-device,drive=hd0 \
        -append "root=/dev/vda rw console=ttyS0 earlycon=sbi"

5. Start kvm-acceled QEMU VM in emulation
$ ./qemu-system-riscv64 -M virt,accel=kvm -m 1024M -cpu host -nographic \
        -name guest=riscv-guset \
        -smp 2 \
        -bios none \
        -kernel ./Image \
        -drive file=./guest.img,format=raw,id=hd0 \
        -device virtio-blk-device,drive=hd0 \
        -append "root=/dev/vda rw console=ttyS0 earlycon=sbi"

This following link describes the details about live migration steps:
https://gitee.com/openeuler/qemu/wikis/Live%20migration?sort_id=2767831

Changes since RFC v2
1. Fix checkpatch error at target/riscv/sbi_ecall_interface.h.
2. Add riscv migration support.

Changes since RFC v1
1. Add separate SBI ecall interface header.
2. Add riscv32 kvm accel support.

Yifei Jiang (14):
  linux-header: Update linux/kvm.h
  target/riscv: Add target/riscv/kvm.c to place the public kvm interface
  target/riscv: Implement function kvm_arch_init_vcpu
  target/riscv: Implement kvm_arch_get_registers
  arget/riscv: Implement kvm_arch_put_registers
  target/riscv: Support start kernel directly by KVM
  hw/riscv: PLIC update external interrupt by KVM when kvm enabled
  target/riscv: Handler KVM_EXIT_RISCV_SBI exit
  target/riscv: Add host cpu type
  target/riscv: Add sifive_plic vmstate
  target/riscv: Support riscv cpu vmstate
  target/riscv: Add kvm_riscv_get/put_regs_timer
  target/riscv: Implement virtual time adjusting with vm state changing
  target/riscv: Support virtual time context synchronization

 configure                          |   1 +
 hw/riscv/sifive_plic.c             |  55 ++-
 hw/riscv/virt.c                    |   8 +
 include/hw/riscv/sifive_plic.h     |   1 +
 linux-headers/linux/kvm.h          |   8 +
 target/riscv/cpu.c                 |  41 +-
 target/riscv/cpu.h                 |  10 +
 target/riscv/kvm.c                 | 599 +++++++++++++++++++++++++++++
 target/riscv/kvm_riscv.h           |  25 ++
 target/riscv/meson.build           |   1 +
 target/riscv/sbi_ecall_interface.h |  72 ++++
 11 files changed, 809 insertions(+), 12 deletions(-)
 create mode 100644 target/riscv/kvm.c
 create mode 100644 target/riscv/kvm_riscv.h
 create mode 100644 target/riscv/sbi_ecall_interface.h
```
#### [PATCH 0/3] Few nSVM bugfixes
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Aug 27 16:27:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11741017
Return-Path: <SRS0=uiX/=CF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9DBAD722
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 16:27:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7EA192087E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 16:27:36 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Y4UDiw3s"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726293AbgH0Q1f (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 12:27:35 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:41881 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726200AbgH0Q1e (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 27 Aug 2020 12:27:34 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598545653;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=nAUeeK2BuQYFsQta/IVHJijuZ4P+QQy9wWHlAAEXfrY=;
        b=Y4UDiw3sg3FznLLDwU4U00+ASlZciptZROty1CO3ED7S+cBVPIZOAmWjvWo9CMuaIkwPYH
        a5doYTIoqJ8cWfrw/NYLFvsR7HCvrq/yufuTbYY7tNwZpxNrtjRNyBLgHtbTHEsgrcUpaw
        1RXxa5K9freqsXpOrXiLeIRzHryuskk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-274-48E3qiZPMbekZUWy7CI_mA-1; Thu, 27 Aug 2020 12:27:31 -0400
X-MC-Unique: 48E3qiZPMbekZUWy7CI_mA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B8CB718B9F14;
        Thu, 27 Aug 2020 16:27:29 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.185])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 07B735C22E;
        Thu, 27 Aug 2020 16:27:21 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Borislav Petkov <bp@alien8.de>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel@vger.kernel.org, Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Ingo Molnar <mingo@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/3] Few nSVM bugfixes
Date: Thu, 27 Aug 2020 19:27:17 +0300
Message-Id: <20200827162720.278690-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series contains few nested SVM fixes from
testing I did this weekend.

Patch #1 fixes issue where we were setting the GIF (global interrupt flag)
on first nested VMexit, after migration thus making the nested guest crash
from unexpected interrupts.

Patch #2 is my observation that we never setup nesed msr bitmap on nested
state load after migration.

Patch #3 was 'migrated' ;-) from my other patch series to make it smaller,
which is about more strict checks when we about to return to a nested guest,
from SMM.

Best regards,
	Maxim Levitsky

Maxim Levitsky (3):
  SVM: nSVM: correctly restore GIF on vmexit from nesting after
    migration
  SVM: nSVM: setup nested msr permission bitmap on nested state load
  KVM: nSVM: more strict SMM checks when returning to nested guest

 arch/x86/kvm/svm/nested.c |  7 ++++++-
 arch/x86/kvm/svm/svm.c    | 29 ++++++++++++++++++-----------
 2 files changed, 24 insertions(+), 12 deletions(-)
```
#### [PATCH 0/8] KVM: nSVM: ondemand nested state allocation + smm fixes
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Aug 27 17:04:26 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11741089
Return-Path: <SRS0=uiX/=CF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C5D8109B
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 17:04:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7090A20737
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 17:04:59 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KysYfwv+"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726804AbgH0REs (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 13:04:48 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:37786 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726232AbgH0REr (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 27 Aug 2020 13:04:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598547885;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=6skhDZK1eBFqInLIv6DlYJCfL20AefptLm3lM0sktaQ=;
        b=KysYfwv++BEGcBPflnLlC/v8oNnYgrJ6UYCVvRORnSFF5J3Ge2PBT37wZEScUzp5jjn76j
        Sy5t4SGWqd38h2Xrd5TgOaCBPsvt8sTI1qUQBO73ToKSu66BAvPgbQy8fPap9vTdOkKKeL
        q4Y6NLkLaUCK90E+lhKRtijBnBKA8+A=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-43-vuJ0MpH5PuSgTyT0hBShIQ-1; Thu, 27 Aug 2020 13:04:41 -0400
X-MC-Unique: vuJ0MpH5PuSgTyT0hBShIQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 1DF13107464C;
        Thu, 27 Aug 2020 17:04:40 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.185])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2891919936;
        Thu, 27 Aug 2020 17:04:34 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, linux-kernel@vger.kernel.org,
        Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/8] KVM: nSVM: ondemand nested state allocation + smm fixes
Date: Thu, 27 Aug 2020 20:04:26 +0300
Message-Id: <20200827170434.284680-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series does some refactoring and implements on demand nested state area
This way at least guests that don't use nesting won't waste memory
on nested state.

This patch series is based on patch series '[PATCH 0/3] Few nSVM bugfixes'
(patch #7 here should have beeing moved there as well to be honest)

The series was tested with various nested guests, and it seems to work
as long as I disable the TSC deadline timer (this is unrelated to this
patch series)

I addressed the review feedback from V2, and added few refactoring
patches to this series as suggested.

Best regards,
        Maxim Levitsky

Maxim Levitsky (8):
  KVM: SVM: rename a variable in the svm_create_vcpu
  KVM: nSVM: rename nested vmcb to vmcb12
  KVM: SVM: refactor msr permission bitmap allocation
  KVM: SVM: use __GFP_ZERO instead of clear_page
  KVM: SVM: refactor exit labels in svm_create_vcpu
  KVM: x86: allow kvm_x86_ops.set_efer to return a value
  KVM: emulator: more strict rsm checks.
  KVM: nSVM: implement ondemand allocation of the nested state

 arch/x86/include/asm/kvm_host.h |   2 +-
 arch/x86/kvm/emulate.c          |  22 ++-
 arch/x86/kvm/svm/nested.c       | 267 ++++++++++++++++++--------------
 arch/x86/kvm/svm/svm.c          | 106 +++++++------
 arch/x86/kvm/svm/svm.h          |  10 +-
 arch/x86/kvm/vmx/vmx.c          |   9 +-
 arch/x86/kvm/x86.c              |   3 +-
 7 files changed, 243 insertions(+), 176 deletions(-)
```
#### [PATCH v3 0/8] KVM: nSVM: ondemand nested state allocation + smm
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Aug 27 17:11:37 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11741131
Return-Path: <SRS0=uiX/=CF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2F5F913B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 17:12:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 115D722BF5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 27 Aug 2020 17:12:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="XendloUh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727095AbgH0RL4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 27 Aug 2020 13:11:56 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:38108 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726232AbgH0RLz (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 27 Aug 2020 13:11:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1598548314;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=6skhDZK1eBFqInLIv6DlYJCfL20AefptLm3lM0sktaQ=;
        b=XendloUhFiswFH7LvIYEY6LJUg5M8Fd5YMJtowPxYwGVuSWqYtBzQqKCpyufHdZXnx8JwD
        T12LdHH8doWvVhlMYG+Lz8ab43uEyS/mjvynEgsk/7DIFLdXJFlHthrxzqIodCHirEOpnR
        dT7nZAoXe2JHG7E1XP2lAFAVlrpEpK0=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-542-4-_sblBzO3mMfn4CsuUU5Q-1; Thu, 27 Aug 2020 13:11:52 -0400
X-MC-Unique: 4-_sblBzO3mMfn4CsuUU5Q-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0FAAE425DA;
        Thu, 27 Aug 2020 17:11:50 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.185])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8C73C5D9E8;
        Thu, 27 Aug 2020 17:11:46 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)), Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Jim Mattson <jmattson@google.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Joerg Roedel <joro@8bytes.org>,
        Wanpeng Li <wanpengli@tencent.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v3 0/8] KVM: nSVM: ondemand nested state allocation + smm
 fixes
Date: Thu, 27 Aug 2020 20:11:37 +0300
Message-Id: <20200827171145.374620-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch series does some refactoring and implements on demand nested state area
This way at least guests that don't use nesting won't waste memory
on nested state.

This patch series is based on patch series '[PATCH 0/3] Few nSVM bugfixes'
(patch #7 here should have beeing moved there as well to be honest)

The series was tested with various nested guests, and it seems to work
as long as I disable the TSC deadline timer (this is unrelated to this
patch series)

I addressed the review feedback from V2, and added few refactoring
patches to this series as suggested.

Best regards,
        Maxim Levitsky

Maxim Levitsky (8):
  KVM: SVM: rename a variable in the svm_create_vcpu
  KVM: nSVM: rename nested vmcb to vmcb12
  KVM: SVM: refactor msr permission bitmap allocation
  KVM: SVM: use __GFP_ZERO instead of clear_page
  KVM: SVM: refactor exit labels in svm_create_vcpu
  KVM: x86: allow kvm_x86_ops.set_efer to return a value
  KVM: emulator: more strict rsm checks.
  KVM: nSVM: implement ondemand allocation of the nested state

 arch/x86/include/asm/kvm_host.h |   2 +-
 arch/x86/kvm/emulate.c          |  22 ++-
 arch/x86/kvm/svm/nested.c       | 267 ++++++++++++++++++--------------
 arch/x86/kvm/svm/svm.c          | 106 +++++++------
 arch/x86/kvm/svm/svm.h          |  10 +-
 arch/x86/kvm/vmx/vmx.c          |   9 +-
 arch/x86/kvm/x86.c              |   3 +-
 7 files changed, 243 insertions(+), 176 deletions(-)
```
