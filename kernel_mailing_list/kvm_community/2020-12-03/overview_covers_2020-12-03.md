

#### [PATCH RFC 0/3] Implement guest time scaling in RISC-V KVM
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
From patchwork Thu Dec  3 12:18:36 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 11948603
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6333AC64E8A
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 12:22:18 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0F9CE22241
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 12:22:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730452AbgLCMVy (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 07:21:54 -0500
Received: from szxga05-in.huawei.com ([45.249.212.191]:9099 "EHLO
        szxga05-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726157AbgLCMVy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Dec 2020 07:21:54 -0500
Received: from DGGEMS406-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga05-in.huawei.com (SkyGuard) with ESMTP id 4Cmw0N6bBrzLyy0;
        Thu,  3 Dec 2020 20:20:36 +0800 (CST)
Received: from huawei.com (10.174.186.236) by DGGEMS406-HUB.china.huawei.com
 (10.3.19.206) with Microsoft SMTP Server id 14.3.487.0; Thu, 3 Dec 2020
 20:21:02 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <anup.patel@wdc.com>, <atish.patra@wdc.com>,
        <paul.walmsley@sifive.com>, <palmer@dabbelt.com>,
        <aou@eecs.berkeley.edu>, <pbonzini@redhat.com>
CC: <kvm-riscv@lists.infradead.org>, <kvm@vger.kernel.org>,
        <linux-riscv@lists.infradead.org>, <linux-kernel@vger.kernel.org>,
        <victor.zhangxiaofeng@huawei.com>, <wu.wubin@huawei.com>,
        <zhang.zhanghailiang@huawei.com>, <dengkai1@huawei.com>,
        <yinyipeng1@huawei.com>, Yifei Jiang <jiangyifei@huawei.com>
Subject: [PATCH RFC 0/3] Implement guest time scaling in RISC-V KVM
Date: Thu, 3 Dec 2020 20:18:36 +0800
Message-ID: <20201203121839.308-1-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.186.236]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series implements guest time scaling based on RDTIME instruction
emulation so that we can allow migrating Guest/VM across Hosts with
different time frequency.

Why not through para-virt. From arm's experience[1], para-virt implementation
doesn't really solve the problem for the following two main reasons:
- RDTIME not only be used in linux, but also in firmware and userspace.
- It is difficult to be compatible with nested virtualization.

[1] https://lore.kernel.org/patchwork/cover/1288153/

Yifei Jiang (3):
  RISC-V: KVM: Change the method of calculating cycles to nanoseconds
  RISC-V: KVM: Support dynamic time frequency from userspace
  RISC-V: KVM: Implement guest time scaling

 arch/riscv/include/asm/csr.h            |  3 ++
 arch/riscv/include/asm/kvm_vcpu_timer.h | 13 +++++--
 arch/riscv/kvm/vcpu_exit.c              | 35 +++++++++++++++++
 arch/riscv/kvm/vcpu_timer.c             | 51 ++++++++++++++++++++++---
 4 files changed, 93 insertions(+), 9 deletions(-)
```
#### [PATCH RFC v4 00/15] Add riscv kvm accel support
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
From patchwork Thu Dec  3 12:46:48 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 11948657
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 974ADC83014
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 12:48:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5443F20709
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 12:48:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730407AbgLCMsI (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 07:48:08 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:8626 "EHLO
        szxga04-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730384AbgLCMsH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Dec 2020 07:48:07 -0500
Received: from DGGEMS403-HUB.china.huawei.com (unknown [172.30.72.60])
        by szxga04-in.huawei.com (SkyGuard) with ESMTP id 4CmwZk4sJMz15Wyc;
        Thu,  3 Dec 2020 20:46:54 +0800 (CST)
Received: from huawei.com (10.174.186.236) by DGGEMS403-HUB.china.huawei.com
 (10.3.19.203) with Microsoft SMTP Server id 14.3.487.0; Thu, 3 Dec 2020
 20:47:12 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <qemu-devel@nongnu.org>, <qemu-riscv@nongnu.org>
CC: <kvm-riscv@lists.infradead.org>, <kvm@vger.kernel.org>,
        <libvir-list@redhat.com>, <anup.patel@wdc.com>,
        <palmer@dabbelt.com>, <Alistair.Francis@wdc.com>,
        <sagark@eecs.berkeley.edu>, <kbastian@mail.uni-paderborn.de>,
        <victor.zhangxiaofeng@huawei.com>, <wu.wubin@huawei.com>,
        <zhang.zhanghailiang@huawei.com>, <dengkai1@huawei.com>,
        <yinyipeng1@huawei.com>, Yifei Jiang <jiangyifei@huawei.com>
Subject: [PATCH RFC v4 00/15] Add riscv kvm accel support
Date: Thu, 3 Dec 2020 20:46:48 +0800
Message-ID: <20201203124703.168-1-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.186.236]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds both riscv32 and riscv64 kvm support, and implements
migration based on riscv. It is based on temporarily unaccepted kvm:
https://github.com/kvm-riscv/linux (lastest version v15).

This series depends on above pending changes which haven't yet been
accepted, so this QEMU patch series is treated as RFC patches until
that dependency has been dealt with.

Compared to RFC v3, the time scaling is supported in this series. The
new feature also requires the following patches:
[1] Bugfix in kvm v15
https://lkml.org/lkml/2020/11/30/245
[2] kvm patches:
[PATCH RFC 0/3] Implement guest time scaling in RISC-V KVM

Several steps to use this:
1. Build emulation
$ ./configure --target-list=riscv64-softmmu
$ make -j$(nproc)

2. Build kernel
https://github.com/kvm-riscv/linux

3. Build QEMU VM
Cross built in riscv toolchain.
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

Changes since RFC v3
- Rebase on QEMU v5.2.0-rc2 and kvm-riscv linux v15.
- Add time scaling support(New patches 13, 14 and 15).
- Fix the bug that guest vm can't reboot.

Changes since RFC v2
- Fix checkpatch error at target/riscv/sbi_ecall_interface.h.
- Add riscv migration support.

Changes since RFC v1
- Add separate SBI ecall interface header.
- Add riscv32 kvm accel support.

Yifei Jiang (15):
  linux-header: Update linux/kvm.h
  target/riscv: Add target/riscv/kvm.c to place the public kvm interface
  target/riscv: Implement function kvm_arch_init_vcpu
  target/riscv: Implement kvm_arch_get_registers
  target/riscv: Implement kvm_arch_put_registers
  target/riscv: Support start kernel directly by KVM
  hw/riscv: PLIC update external interrupt by KVM when kvm enabled
  target/riscv: Handle KVM_EXIT_RISCV_SBI exit
  target/riscv: Add host cpu type
  target/riscv: Add kvm_riscv_get/put_regs_timer
  target/riscv: Implement virtual time adjusting with vm state changing
  target/riscv: Support virtual time context synchronization
  target/riscv: Introduce dynamic time frequency for virt machine
  target/riscv: Synchronize vcpu's frequency with KVM
  target/riscv: Add time frequency migration support

 hw/intc/sifive_plic.c              |  31 +-
 hw/riscv/virt.c                    |  26 +-
 linux-headers/linux/kvm.h          |   8 +
 meson.build                        |   2 +
 target/riscv/cpu.c                 |  13 +
 target/riscv/cpu.h                 |  12 +
 target/riscv/kvm.c                 | 617 +++++++++++++++++++++++++++++
 target/riscv/kvm_riscv.h           |  25 ++
 target/riscv/machine.c             |  23 ++
 target/riscv/meson.build           |   1 +
 target/riscv/sbi_ecall_interface.h |  72 ++++
 11 files changed, 817 insertions(+), 13 deletions(-)
 create mode 100644 target/riscv/kvm.c
 create mode 100644 target/riscv/kvm_riscv.h
 create mode 100644 target/riscv/sbi_ecall_interface.h
```
#### [PATCH 0/1] Fix for a recent regression in kvm/queue (guest using
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Dec  3 14:33:18 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11948963
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 820D5C4361A
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 14:51:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D6AE622293
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 14:35:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2436525AbgLCOez (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 09:34:55 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:57266 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728159AbgLCOez (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Dec 2020 09:34:55 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607006009;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=6smsIvjf77OYufhjM+C0nrIBQuuSFafCoX7/LBefMiM=;
        b=gULYPi1uPCVBZnRipEt/DTz9hk356RosnjManBt2OlMXsHldmMwq6DCD2X2zoqHWupMyjO
        B5urZ28cLHZJHSgH5T6NofDAjDgHCcoaOg+ZBRfL0d12VcD92CQTcIR2LKYwDeHmPKXvxc
        Hy5lNo30+fJ4i2F6LGIN2wMMf3d6Pkw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-365-AOBA8ru4POGmZP_E6v16cw-1; Thu, 03 Dec 2020 09:33:27 -0500
X-MC-Unique: AOBA8ru4POGmZP_E6v16cw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 716B315822E;
        Thu,  3 Dec 2020 14:33:25 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E723A18A60;
        Thu,  3 Dec 2020 14:33:20 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Joerg Roedel <joro@8bytes.org>, Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        "H. Peter Anvin" <hpa@zytor.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        linux-kernel@vger.kernel.org, Thomas Gleixner <tglx@linutronix.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 0/1] Fix for a recent regression in kvm/queue (guest using
 100% cpu time)
Date: Thu,  3 Dec 2020 16:33:18 +0200
Message-Id: <20201203143319.159394-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

I did a quick bisect yesterday after noticing that my VMs started
to take 100% cpu time.

Looks like we don't ignore SIPIs that are received while the CPU isn't
waiting for them, and that makes KVM think that CPU always has
pending events which makes it never enter an idle state.

Best regards,
	Maxim Levitsky

Maxim Levitsky (1):
  KVM: x86: ignore SIPIs that are received while not in wait-for-sipi
    state

 arch/x86/kvm/lapic.c | 15 ++++++++-------
 1 file changed, 8 insertions(+), 7 deletions(-)
```
#### [PATCH v2 0/3] RFC: Precise TSC migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Dec  3 17:11:15 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11949163
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id D9508C0018C
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 17:13:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 53F9E207AE
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 17:13:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728633AbgLCRN0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 12:13:26 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:53421 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2501942AbgLCRNY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Dec 2020 12:13:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607015518;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=zaqAemO/Fsujg9r8lt/SFqF1ctdGuOQUqsO5lgI9LxY=;
        b=eapRq1a/cEDgA0rlGekknwtGedJqPGEcwuF08WAje/e7/Q0c3mCr2p3nHuSAtCYk7tch61
        vhOX38J70DdI2K/Wv6dDcdeCyaAqbTKitwotK8HCJQAhKsnLYRIYwpARxIw9e4JZ7ETzDm
        LvrKY4WFdLnX03Mxtp+LYPVjFFyfvtg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-474-6I46_4btNSS0GSJXwwek_Q-1; Thu, 03 Dec 2020 12:11:55 -0500
X-MC-Unique: 6I46_4btNSS0GSJXwwek_Q-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 51CEC180A089;
        Thu,  3 Dec 2020 17:11:27 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2475A6F963;
        Thu,  3 Dec 2020 17:11:19 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>,
        Jim Mattson <jmattson@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        linux-kselftest@vger.kernel.org (open list:KERNEL SELFTEST FRAMEWORK),
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        linux-kernel@vger.kernel.org (open list),
        Ingo Molnar <mingo@redhat.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Joerg Roedel <joro@8bytes.org>, Borislav Petkov <bp@alien8.de>,
        Shuah Khan <shuah@kernel.org>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Oliver Upton <oupton@google.com>,
        linux-doc@vger.kernel.org (open list:DOCUMENTATION)
Subject: [PATCH v2 0/3] RFC: Precise TSC migration
Date: Thu,  3 Dec 2020 19:11:15 +0200
Message-Id: <20201203171118.372391-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi!

This is the second version of the work to make TSC migration more accurate,
as was defined by Paulo at:
https://www.spinics.net/lists/kvm/msg225525.html

I omitted most of the semi-offtopic points I raised related to TSC
in the previous RFC where we can continue the discussion.

I do want to raise another thing that I almost forgot.

On AMD systems, the Linux kernel will mark the guest tsc as
unstable unless invtsc is set which is set on recent AMD
hardware.

Take a look at 'unsynchronized_tsc()' to verify this.

This is another thing that IMHO should be fixed at least when
running under KVM.

Note that I forgot to mention that
X86_FEATURE_TSC_RELIABLE also short-circuits this code,
thus giving another reason to enable it under KVM.

Changes from V1:

- added KVM_TSC_STATE_TIMESTAMP_VALID instead of testing ns == 0
- allow diff < 0, because it is still better that capping it to 0
- updated tsc_msr_test unit test to cover this feature
- refactoring

Patches to enable this feature in qemu are in the process of
being sent to qemu-devel mailing list.

Best regards,
    Maxim Levitsky

Maxim Levitsky (3):
  KVM: x86: implement KVM_{GET|SET}_TSC_STATE
  KVM: x86: introduce KVM_X86_QUIRK_TSC_HOST_ACCESS
  kvm/selftests: update tsc_msrs_test to cover
    KVM_X86_QUIRK_TSC_HOST_ACCESS

 Documentation/virt/kvm/api.rst                | 65 +++++++++++++
 arch/x86/include/uapi/asm/kvm.h               |  1 +
 arch/x86/kvm/x86.c                            | 92 ++++++++++++++++++-
 include/uapi/linux/kvm.h                      | 15 +++
 .../selftests/kvm/x86_64/tsc_msrs_test.c      | 79 ++++++++++++++--
 5 files changed, 237 insertions(+), 15 deletions(-)
```
#### [PATCH v2 0/2] RFC: Precise TSC migration
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
From patchwork Thu Dec  3 17:15:44 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11949183
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.2 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C12A5C433FE
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 17:17:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 608AE207AF
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 17:17:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731535AbgLCRR0 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 12:17:26 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:44840 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726840AbgLCRRY (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Dec 2020 12:17:24 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607015757;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=cR3WCJq9d7LvMDlf7M0tIlYK9KyXcPJkybrgmwJqmcM=;
        b=ESZ2rLiE7RBB4RMYrrPjdRZy1yD4vyl3qnN/WfyYBFRJ0y8te99/ePSTu8VH3XYvZ64OSS
        H9hC6NjNDO/wjyuhMAH4/XAyAxrmaBfuhs5b2CWRGLKoQQArL4xdw+QoS5ccwM8XYVx2Fk
        8QbOpC6Xy9Xcan/GcHWhOVIZ3ugztV4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-490-tW323KgXM-6_kPnBfxoCwQ-1; Thu, 03 Dec 2020 12:15:56 -0500
X-MC-Unique: tW323KgXM-6_kPnBfxoCwQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 979AB858180;
        Thu,  3 Dec 2020 17:15:54 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 084AC5D6AC;
        Thu,  3 Dec 2020 17:15:47 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: qemu-devel@nongnu.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Marcelo Tosatti <mtosatti@redhat.com>,
        Eduardo Habkost <ehabkost@redhat.com>, kvm@vger.kernel.org,
        Richard Henderson <richard.henderson@linaro.org>,
        Cornelia Huck <cohuck@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH v2 0/2] RFC: Precise TSC migration
Date: Thu,  3 Dec 2020 19:15:44 +0200
Message-Id: <20201203171546.372686-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Note that to use this feature you need the kernel patches which are
posted to LKML and kvm@vger.kernel.org

The feature is disabled by default, and can be enabled with
-accel kvm,x-precise-tsc=on.

I changed the TSC and TSC adjust read/write code to go though a special
function kvm_get_tsc/kvm_set_tsc regardless of enablement of this feature.

The side effect of this is that now we upload to the kernel the TSC_ADJUST
msr only on KVM_PUT_RESET_STATE reset level.
This shouldn't matter as I don't think that qemu changes this msr on its own.

For migration I added a new state field 'cpu/tsc_ns_timestamp',
where I save the TSC nanosecond timestamp, which is the only
new thing that was added to the migration state.

First patch in this series is temporary and it just updates the kernel
headers to make qemu compile.

When the feature is merged to the kernel, a kernel header sync will bring
the same changes to the qemu, making this patch unnecessary.

V2:

- switched to -accel for enablement
- sync with updated kernel patches
- minor cleanups, renames, etc

Best regards,
    Maxim Levitsky

Maxim Levitsky (2):
  Update the kernel headers for 5.10-rc5 + TSC
  Implement support for precise TSC migration

 accel/kvm/kvm-all.c                         |  28 ++++
 include/standard-headers/asm-x86/kvm_para.h |   1 +
 include/sysemu/kvm.h                        |   1 +
 linux-headers/asm-x86/kvm.h                 |   2 +
 linux-headers/linux/kvm.h                   |  71 +++++++++-
 target/i386/cpu.h                           |   1 +
 target/i386/kvm.c                           | 140 ++++++++++++++++----
 target/i386/machine.c                       |  19 +++
 8 files changed, 234 insertions(+), 29 deletions(-)
```
#### [PATCH v3 0/2] Connect request callback to mdev and vfio-ccw
##### From: Eric Farman <farman@linux.ibm.com>

```c
From patchwork Thu Dec  3 21:35:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Farman <farman@linux.ibm.com>
X-Patchwork-Id: 11949675
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 957D3C4361B
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 21:36:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4D09E22473
	for <kvm@archiver.kernel.org>; Thu,  3 Dec 2020 21:36:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728923AbgLCVgG (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Thu, 3 Dec 2020 16:36:06 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:62368 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728252AbgLCVgF (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 3 Dec 2020 16:36:05 -0500
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0B3LYXo3027151;
        Thu, 3 Dec 2020 16:35:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id; s=pp1;
 bh=202NPPv11LZXskIKT2kUmTrWRL/sWF+vMp8dh5k9rv0=;
 b=Bd8H4QiwsZlIGgF+2kDRPYFgpigqbB/0dK2kL41Xqo0c+/AIkzORBPjxi2iTn43RE0MC
 Q0IF81AYEdunv3i3MaepVWAu0VOCrA2G7/jXk4ODWI2Cboq5zNTOcauDm7qtAVyr3CPw
 fEJQeYpBuEV0T7b/nzKtqQ0ZHHPWLo8XGXJNS/QUqTJRj61hC3kOdLVaNi+Whu6QEKvW
 FE2w11BNI1kfUAbQVLzJ9hKF8xT9ItVF9FV/CD71AUBtWcygowyCrtUK6IBvNDeE+4+D
 DtqAikB6qRhp9tmtQp2BGuGgJtlFbf8PYDvD+NCwpmAMoz4ddQUuB5PVqluOmVqjmKX9 0g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35775csgqa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Dec 2020 16:35:20 -0500
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0B3LYcMA027701;
        Thu, 3 Dec 2020 16:35:20 -0500
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 35775csgpm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Dec 2020 16:35:20 -0500
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0B3LW8aq021225;
        Thu, 3 Dec 2020 21:35:18 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma03ams.nl.ibm.com with ESMTP id 3573v9r67q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 03 Dec 2020 21:35:18 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0B3LZFed1835584
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 3 Dec 2020 21:35:15 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B3B0AAE053;
        Thu,  3 Dec 2020 21:35:15 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9E892AE045;
        Thu,  3 Dec 2020 21:35:15 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Thu,  3 Dec 2020 21:35:15 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 4958)
        id 14A8DE01E6; Thu,  3 Dec 2020 22:35:15 +0100 (CET)
From: Eric Farman <farman@linux.ibm.com>
To: Alex Williamson <alex.williamson@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>
Cc: Kirti Wankhede <kwankhede@nvidia.com>,
        Halil Pasic <pasic@linux.ibm.com>,
        Matthew Rosato <mjrosato@linux.ibm.com>,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        Eric Farman <farman@linux.ibm.com>
Subject: [PATCH v3 0/2] Connect request callback to mdev and vfio-ccw
Date: Thu,  3 Dec 2020 22:35:10 +0100
Message-Id: <20201203213512.49357-1-farman@linux.ibm.com>
X-Mailer: git-send-email 2.17.1
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.312,18.0.737
 definitions=2020-12-03_12:2020-12-03,2020-12-03 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0
 priorityscore=1501 spamscore=0 mlxscore=0 malwarescore=0 adultscore=0
 phishscore=0 lowpriorityscore=0 impostorscore=0 suspectscore=0
 clxscore=1015 mlxlogscore=817 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2009150000 definitions=main-2012030122
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Alex,

As promised, here is a v3 with a message indicating a request is blocked
until a user releases the device in question and a corresponding tweak to
the commit message describing this change (and Conny's r-b). The remainder
of the patches are otherwise identical.

v2      : https://lore.kernel.org/kvm/20201120180740.87837-1-farman@linux.ibm.com/
v1(RFC) : https://lore.kernel.org/kvm/20201117032139.50988-1-farman@linux.ibm.com/

Eric Farman (2):
  vfio-mdev: Wire in a request handler for mdev parent
  vfio-ccw: Wire in the request callback

 drivers/s390/cio/vfio_ccw_ops.c     | 26 ++++++++++++++++++++++++++
 drivers/s390/cio/vfio_ccw_private.h |  4 ++++
 drivers/vfio/mdev/mdev_core.c       |  4 ++++
 drivers/vfio/mdev/vfio_mdev.c       | 13 +++++++++++++
 include/linux/mdev.h                |  4 ++++
 include/uapi/linux/vfio.h           |  1 +
 6 files changed, 52 insertions(+)
```
