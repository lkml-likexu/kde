

#### [PATCH v5 00/11] KVM SGX virtualization support (KVM part)
##### From: Kai Huang <kai.huang@intel.com>

```c
From patchwork Mon Apr 12 04:21:32 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kai Huang <kai.huang@intel.com>
X-Patchwork-Id: 12196771
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=unavailable autolearn_force=no
 version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id EF10BC43460
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 04:21:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C69976120A
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 04:21:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229854AbhDLEWK (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 00:22:10 -0400
Received: from mga07.intel.com ([134.134.136.100]:53368 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229448AbhDLEWJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 00:22:09 -0400
IronPort-SDR: 
 FoYqkzv/LFzzJ+QB1ew3CltJuopGb2eqWcnF/1yzIQDeZ+JeGaK4o0o7Z2+11bi8ic/5lfItNh
 iqRycluaGVzQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9951"; a="258083736"
X-IronPort-AV: E=Sophos;i="5.82,214,1613462400";
   d="scan'208";a="258083736"
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga105.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Apr 2021 21:21:51 -0700
IronPort-SDR: 
 T3JTS6xv/VQ4UVbj73NncAbScptLx2jk2XAtoh50u0vb/bK0hBltG4Ks9TM/xIQDTNjE9k447z
 sqIGwDVpVPrw==
X-IronPort-AV: E=Sophos;i="5.82,214,1613462400";
   d="scan'208";a="521030335"
Received: from rutujajo-mobl.amr.corp.intel.com (HELO
 khuang2-desk.gar.corp.intel.com) ([10.212.194.203])
  by fmsmga001-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 11 Apr 2021 21:21:48 -0700
From: Kai Huang <kai.huang@intel.com>
To: kvm@vger.kernel.org, linux-sgx@vger.kernel.org
Cc: seanjc@google.com, pbonzini@redhat.com, bp@alien8.de,
        jarkko@kernel.org, dave.hansen@intel.com, luto@kernel.org,
        rick.p.edgecombe@intel.com, haitao.huang@intel.com
Subject: [PATCH v5 00/11] KVM SGX virtualization support (KVM part)
Date: Mon, 12 Apr 2021 16:21:32 +1200
Message-Id: <cover.1618196135.git.kai.huang@intel.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hi Paolo, Sean,

Boris has merged x86 part patches to the tip/x86/sgx. This series is KVM part
patches. Due to some code change in x86 part patches, two KVM patches need
update so this is the new version. Please help to review. Thanks!

Specifically, x86 patch (x86/sgx: Add helpers to expose ECREATE and EINIT to
KVM) was changed to return -EINVAL directly w/o setting trapnr when 
access_ok()s fail on any user pointers, so KVM patches:

KVM: VMX: Add SGX ENCLS[ECREATE] handler to enforce CPUID restrictions
KVM: VMX: Add ENCLS[EINIT] handler to support SGX Launch Control (LC)

were updated to handle this case.

This seris was firstly based on tip/x86/sgx, and then rebased to latest
kvm/queue, so it can be applied to kvm/queue directly now.

Changelog:

(Please see individual patch for changelog for specific patch)

v4->v5:
 - Addressed Sean's comments (patch 06, 07, 09 were slightly updated).
 - Rebased to latest kvm/queue (patch 08, 11 were updated to resolve conflict).

Sean Christopherson (11):
  KVM: x86: Export kvm_mmu_gva_to_gpa_{read,write}() for SGX (VMX)
  KVM: x86: Define new #PF SGX error code bit
  KVM: x86: Add support for reverse CPUID lookup of scattered features
  KVM: x86: Add reverse-CPUID lookup support for scattered SGX features
  KVM: VMX: Add basic handling of VM-Exit from SGX enclave
  KVM: VMX: Frame in ENCLS handler for SGX virtualization
  KVM: VMX: Add SGX ENCLS[ECREATE] handler to enforce CPUID restrictions
  KVM: VMX: Add emulation of SGX Launch Control LE hash MSRs
  KVM: VMX: Add ENCLS[EINIT] handler to support SGX Launch Control (LC)
  KVM: VMX: Enable SGX virtualization for SGX1, SGX2 and LC
  KVM: x86: Add capability to grant VM access to privileged SGX
    attribute

 Documentation/virt/kvm/api.rst  |  23 ++
 arch/x86/include/asm/kvm_host.h |   5 +
 arch/x86/include/asm/vmx.h      |   1 +
 arch/x86/include/uapi/asm/vmx.h |   1 +
 arch/x86/kvm/Makefile           |   2 +
 arch/x86/kvm/cpuid.c            |  89 +++++-
 arch/x86/kvm/cpuid.h            |  50 +++-
 arch/x86/kvm/vmx/nested.c       |  28 +-
 arch/x86/kvm/vmx/nested.h       |   5 +
 arch/x86/kvm/vmx/sgx.c          | 502 ++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/sgx.h          |  34 +++
 arch/x86/kvm/vmx/vmcs12.c       |   1 +
 arch/x86/kvm/vmx/vmcs12.h       |   4 +-
 arch/x86/kvm/vmx/vmx.c          | 109 ++++++-
 arch/x86/kvm/vmx/vmx.h          |   3 +
 arch/x86/kvm/x86.c              |  23 ++
 include/uapi/linux/kvm.h        |   1 +
 17 files changed, 858 insertions(+), 23 deletions(-)
 create mode 100644 arch/x86/kvm/vmx/sgx.c
 create mode 100644 arch/x86/kvm/vmx/sgx.h
```
#### [PATCH RFC v5 00/12] Add riscv kvm accel support
##### From: Yifei Jiang <jiangyifei@huawei.com>

```c
From patchwork Mon Apr 12 06:52:34 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Yifei Jiang <jiangyifei@huawei.com>
X-Patchwork-Id: 12196945
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 69226C433ED
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 06:53:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3A68B6109F
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 06:53:30 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236624AbhDLGxq (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 02:53:46 -0400
Received: from szxga07-in.huawei.com ([45.249.212.35]:17309 "EHLO
        szxga07-in.huawei.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S231175AbhDLGxq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 02:53:46 -0400
Received: from DGGEMS412-HUB.china.huawei.com (unknown [172.30.72.59])
        by szxga07-in.huawei.com (SkyGuard) with ESMTP id 4FJfXG3S84z9yZR;
        Mon, 12 Apr 2021 14:51:10 +0800 (CST)
Received: from huawei.com (10.174.186.236) by DGGEMS412-HUB.china.huawei.com
 (10.3.19.212) with Microsoft SMTP Server id 14.3.498.0; Mon, 12 Apr 2021
 14:53:17 +0800
From: Yifei Jiang <jiangyifei@huawei.com>
To: <qemu-devel@nongnu.org>, <qemu-riscv@nongnu.org>
CC: <kvm-riscv@lists.infradead.org>, <kvm@vger.kernel.org>,
        <libvir-list@redhat.com>, <anup.patel@wdc.com>,
        <palmer@dabbelt.com>, <Alistair.Francis@wdc.com>,
        <sagark@eecs.berkeley.edu>, <kbastian@mail.uni-paderborn.de>,
        <bin.meng@windriver.com>, <fanliang@huawei.com>,
        <wu.wubin@huawei.com>, <zhang.zhanghailiang@huawei.com>,
        <yinyipeng1@huawei.com>, Yifei Jiang <jiangyifei@huawei.com>
Subject: [PATCH RFC v5 00/12] Add riscv kvm accel support
Date: Mon, 12 Apr 2021 14:52:34 +0800
Message-ID: <20210412065246.1853-1-jiangyifei@huawei.com>
X-Mailer: git-send-email 2.26.2.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.174.186.236]
X-CFilter-Loop: Reflected
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds both riscv32 and riscv64 kvm support, and implements
migration based on riscv. It is based on temporarily unaccepted kvm:
https://github.com/kvm-riscv/linux (lastest version v17).

This series depends on above pending changes which haven't yet been
accepted, so this QEMU patch series is treated as RFC patches until
that dependency has been dealt with.

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

Changes since RFC v4
- Rebase on QEMU v6.0.0-rc2 and kvm-riscv linux v17.
- Remove time scaling support as software solution is incomplete.
  Because it will cause unacceptable performance degradation. and
  We will post a better solution.
- Revise according to Alistair's review comments.
  - Remove compile time XLEN checks in kvm_riscv_reg_id
  - Surround TYPE_RISCV_CPU_HOST definition by CONFIG_KVM and share
    it between RV32 and RV64.
  - Add kvm-stub.c for reduce unnecessary compilation checks.
  - Add riscv_setup_direct_kernel() to direct boot kernel for KVM.

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

Yifei Jiang (12):
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

 hw/intc/sifive_plic.c              |  29 +-
 hw/riscv/boot.c                    |  11 +
 hw/riscv/virt.c                    |   7 +
 include/hw/riscv/boot.h            |   1 +
 linux-headers/linux/kvm.h          |  97 +++++
 meson.build                        |   2 +
 target/riscv/cpu.c                 |  17 +
 target/riscv/cpu.h                 |  10 +
 target/riscv/kvm-stub.c            |  30 ++
 target/riscv/kvm.c                 | 605 +++++++++++++++++++++++++++++
 target/riscv/kvm_riscv.h           |  25 ++
 target/riscv/machine.c             |  14 +
 target/riscv/meson.build           |   1 +
 target/riscv/sbi_ecall_interface.h |  72 ++++
 14 files changed, 912 insertions(+), 9 deletions(-)
 create mode 100644 target/riscv/kvm-stub.c
 create mode 100644 target/riscv/kvm.c
 create mode 100644 target/riscv/kvm_riscv.h
 create mode 100644 target/riscv/sbi_ecall_interface.h
```
#### [PATCH v5 0/3] ppc: Enable 2nd DAWR support on Power10
##### From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>

```c
From patchwork Mon Apr 12 11:44:30 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
X-Patchwork-Id: 12197791
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A764AC433ED
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 11:45:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 830D66102A
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 11:45:20 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S239874AbhDLLph (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 07:45:37 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:54102 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S237792AbhDLLpg (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 12 Apr 2021 07:45:36 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 13CBZD1E099481;
        Mon, 12 Apr 2021 07:44:43 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : content-transfer-encoding : mime-version; s=pp1;
 bh=zROa97CJSkAXDOF05z4b0Av2x+Xi+AT9U3HHYG8ufmY=;
 b=S/YN7IiKGelyXqKY0i22tmArFpC34sB1LlAfdzOUEOXI0SL7f7E29TnDyvIwTkiDNOx8
 QhV/yZjyH3iY4U0S1b+DNm3b1dIjNZ5pwdlCovk1PPuYtEWgMImTZ/iMClSl+shvw9oh
 3IUw7+WNqNWOrsOn2H5dy2sCcly2c6f3X06enL21DMJ+djrm492y/5hew3ikdJYXjyOd
 Zr8AyuP2QdaHLohmnINJxkDb9b0oIgJBjwQxbpXqt/Wc9kU/hrL3+9afBPoZSjA0gwqW
 NkF8svOo+tfKVv7EjU7s72Yt38KpMt66RXwiT7EuWGBgsDmKknR2fua0VdZyXNE6CW/6 XQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37vkphcdpd-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 12 Apr 2021 07:44:43 -0400
Received: from m0098393.ppops.net (m0098393.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 13CBZcWe100457;
        Mon, 12 Apr 2021 07:44:43 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0a-001b2d01.pphosted.com with ESMTP id 37vkphcdmv-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 12 Apr 2021 07:44:43 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 13CBiNr1006407;
        Mon, 12 Apr 2021 11:44:40 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma04ams.nl.ibm.com with ESMTP id 37u3n8srn3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 12 Apr 2021 11:44:40 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 13CBicZq41484710
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 12 Apr 2021 11:44:38 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7811FAE045;
        Mon, 12 Apr 2021 11:44:38 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id AAE58AE053;
        Mon, 12 Apr 2021 11:44:34 +0000 (GMT)
Received: from bangoria.ibmuc.com (unknown [9.199.37.145])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 12 Apr 2021 11:44:34 +0000 (GMT)
From: Ravi Bangoria <ravi.bangoria@linux.ibm.com>
To: paulus@samba.org, david@gibson.dropbear.id.au
Cc: ravi.bangoria@linux.ibm.com, mpe@ellerman.id.au, mikey@neuling.org,
        pbonzini@redhat.com, mst@redhat.com, clg@kaod.org,
        qemu-ppc@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org,
        cohuck@redhat.com, groug@kaod.org
Subject: [PATCH v5 0/3] ppc: Enable 2nd DAWR support on Power10
Date: Mon, 12 Apr 2021 17:14:30 +0530
Message-Id: <20210412114433.129702-1-ravi.bangoria@linux.ibm.com>
X-Mailer: git-send-email 2.30.2
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: 9VwWoDvnhcUD0pSTkFrnUVwF-rNHsrwX
X-Proofpoint-ORIG-GUID: 2iGnkR8121EAucctxYslK97SjSRNfqM7
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-04-12_09:2021-04-12,2021-04-12 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 suspectscore=0 spamscore=0
 impostorscore=0 malwarescore=0 mlxlogscore=999 mlxscore=0
 lowpriorityscore=0 clxscore=1015 adultscore=0 phishscore=0
 priorityscore=1501 bulkscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2104060000 definitions=main-2104120079
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series enables 2nd DAWR support on p10 qemu guest. 2nd
DAWR is new watchpoint added in Power10 processor. Kernel/kvm
patches are already in[1]. Watchpoint on powerpc TCG guest is
not supported and thus 2nd DAWR is not enabled for TCG mode.

Patches apply fine on qemu/master branch (f2afdc2ad94b).

v4: https://lore.kernel.org/r/20210406053833.282907-1-ravi.bangoria@linux.ibm.com
v3->v4:
  - Make error message more proper.

v3: https://lore.kernel.org/r/20210330095350.36309-1-ravi.bangoria@linux.ibm.com
v3->v4:
  - spapr_dt_pa_features(): POWER10 processor is compatible with 3.0
    (PCR_COMPAT_3_00). No need to ppc_check_compat(3_10) for now as
    ppc_check_compati(3_00) will also be true. ppc_check_compat(3_10)
    can be added while introducing pa_features_310 in future.
  - Use error_append_hint() for hints. Also add ERRP_GUARD().
  - Add kvmppc_set_cap_dawr1() stub function for CONFIG_KVM=n.

v2: https://lore.kernel.org/r/20210329041906.213991-1-ravi.bangoria@linux.ibm.com
v2->v3:
  - Don't introduce pa_features_310[], instead, reuse pa_features_300[]
    for 3.1 guests, as there is no difference between initial values of
    them atm.
  - Call gen_spr_book3s_310_dbg() from init_proc_POWER10() instead of
    init_proc_POWER8(). Also, Don't call gen_spr_book3s_207_dbg() from
    gen_spr_book3s_310_dbg() as init_proc_POWER10() already calls it.

v1: https://lore.kernel.org/r/20200723104220.314671-1-ravi.bangoria@linux.ibm.com
[Apologies for long gap]
v1->v2:
  - Introduce machine capability cap-dawr1 to enable/disable
    the feature. By default, 2nd DAWR is OFF for guests even
    when host kvm supports it. User has to manually enable it
    with -machine cap-dawr1=on if he wishes to use it.
  - Split the header file changes into separate patch. (Sync
    headers from v5.12-rc3)

[1] https://git.kernel.org/torvalds/c/bd1de1a0e6eff

Ravi Bangoria (3):
  Linux headers: update from 5.12-rc3
  ppc: Rename current DAWR macros and variables
  ppc: Enable 2nd DAWR support on p10

 hw/ppc/spapr.c                                |  7 +-
 hw/ppc/spapr_caps.c                           | 32 +++++++
 include/hw/ppc/spapr.h                        |  8 +-
 include/standard-headers/drm/drm_fourcc.h     | 23 ++++-
 include/standard-headers/linux/input.h        |  2 +-
 .../standard-headers/rdma/vmw_pvrdma-abi.h    |  7 ++
 linux-headers/asm-generic/unistd.h            |  4 +-
 linux-headers/asm-mips/unistd_n32.h           |  1 +
 linux-headers/asm-mips/unistd_n64.h           |  1 +
 linux-headers/asm-mips/unistd_o32.h           |  1 +
 linux-headers/asm-powerpc/kvm.h               |  2 +
 linux-headers/asm-powerpc/unistd_32.h         |  1 +
 linux-headers/asm-powerpc/unistd_64.h         |  1 +
 linux-headers/asm-s390/unistd_32.h            |  1 +
 linux-headers/asm-s390/unistd_64.h            |  1 +
 linux-headers/asm-x86/kvm.h                   |  1 +
 linux-headers/asm-x86/unistd_32.h             |  1 +
 linux-headers/asm-x86/unistd_64.h             |  1 +
 linux-headers/asm-x86/unistd_x32.h            |  1 +
 linux-headers/linux/kvm.h                     | 89 +++++++++++++++++++
 linux-headers/linux/vfio.h                    | 27 ++++++
 target/ppc/cpu.h                              |  6 +-
 target/ppc/kvm.c                              | 12 +++
 target/ppc/kvm_ppc.h                          | 12 +++
 target/ppc/translate_init.c.inc               | 19 +++-
 25 files changed, 250 insertions(+), 11 deletions(-)
```
#### [PATCH 0/6] KVM: x86: Make the cause of instruction emulation
##### From: David Edmondson <david.edmondson@oracle.com>

```c
From patchwork Mon Apr 12 13:09:31 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Edmondson <david.edmondson@oracle.com>
X-Patchwork-Id: 12198017
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 7E05AC433B4
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 13:09:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 39BBF61356
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 13:09:48 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S241773AbhDLNKE (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 09:10:04 -0400
Received: from wforward5-smtp.messagingengine.com ([64.147.123.35]:50317 "EHLO
        wforward5-smtp.messagingengine.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S241762AbhDLNKD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 12 Apr 2021 09:10:03 -0400
Received: from compute5.internal (compute5.nyi.internal [10.202.2.45])
        by mailforward.west.internal (Postfix) with ESMTP id DD56F166C;
        Mon, 12 Apr 2021 09:09:43 -0400 (EDT)
Received: from mailfrontend2 ([10.202.2.163])
  by compute5.internal (MEProxy); Mon, 12 Apr 2021 09:09:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=
        messagingengine.com; h=cc:content-transfer-encoding:date:from
        :message-id:mime-version:subject:to:x-me-proxy:x-me-proxy
        :x-me-sender:x-me-sender:x-sasl-enc; s=fm2; bh=HvfGYkD6c6q5bKKXX
        v71mYB4LVLkTvCXjY38JwER9zY=; b=IrmYYw3lKD9YPFcY2YObOjK5hmSskK1No
        0Pi4pNblwsWnnkPrVssJO2q/n2ekOtwhLKj0sBZG3J0pudk2S1rZva27+rU1uc7o
        nXofXjBsUzQ7a1sKJeqLAluYIeVfa20lWlOl5GvCRJi7FTQ300iVg4AGhDG1Szmi
        USX5p8jfP94K2I5o2iFnvgIXWMyjhCpZqO8hCHzvSSh5NMxyhpU973b2PffQbQKL
        nX10/wh3nbsbd9Mc5gPvxegPomaTckCUozd9ubX5BLWhrLFoKrDYLMa4Lb75g4mP
        MgRpkndHPnvdpQpuMbfGFb1BP40EuslaoBTCeQLT0Cp+gnADOeoZA==
X-ME-Sender: <xms:lEZ0YHe8qRFjKHSNjMJnOzRgSQpAXkIWDHipsTyK_nA7a1IKBaPKjg>
    <xme:lEZ0YNNEQjxdWdqQrSJExg7FmdtHd_gjauaN9DcO_ghePDO42TI2Zcr4lN7XUmbg5
    WcgkyRPhzD3DHoLfAg>
X-ME-Proxy-Cause: 
 gggruggvucftvghtrhhoucdtuddrgeduledrudekjedgiedvucetufdoteggodetrfdotf
    fvucfrrhhofhhilhgvmecuhfgrshhtofgrihhlpdfqfgfvpdfurfetoffkrfgpnffqhgen
    uceurghilhhouhhtmecufedttdenucesvcftvggtihhpihgvnhhtshculddquddttddmne
    cujfgurhephffvufffkffoggfgsedtkeertdertddtnecuhfhrohhmpeffrghvihguucfg
    ughmohhnughsohhnuceouggrvhhiugdrvggumhhonhgushhonhesohhrrggtlhgvrdgtoh
    hmqeenucggtffrrghtthgvrhhnpefhfedtieevleetueeukeffvdfffeeigfdtvdffgeei
    tdegfeffleeihfevtdekfeenucffohhmrghinhepkhgvrhhnvghlrdhorhhgnecukfhppe
    ekuddrudekjedrvdeirddvfeeknecuvehluhhsthgvrhfuihiivgeptdenucfrrghrrghm
    pehmrghilhhfrhhomhepuggrvhhiugdrvggumhhonhgushhonhesohhrrggtlhgvrdgtoh
    hm
X-ME-Proxy: <xmx:lEZ0YAg48ZU9ihscVRcu6m6i2D1stiUbgNLMMSRyEEQpXIl3tmztdA>
    <xmx:lEZ0YI93T2xtGgtKXKMUp9vfCXEMlTq9BJqGK1lQqB4qvKmYRpy4sQ>
    <xmx:lEZ0YDsmWPmrgibhE6RawTpfXHPRGnD5xwOIM7IE9b7jwbLmjsCgmw>
    <xmx:l0Z0YOmuyhVczSt0b4dC3noOkcatOAJfgkzg36sp1vsuNxj9n7iQQMXjfKcGycPi>
Received: from disaster-area.hh.sledj.net (disaster-area.hh.sledj.net
 [81.187.26.238])
        by mail.messagingengine.com (Postfix) with ESMTPA id A83D91080067;
        Mon, 12 Apr 2021 09:09:39 -0400 (EDT)
Received: from localhost (disaster-area.hh.sledj.net [local])
        by disaster-area.hh.sledj.net (OpenSMTPD) with ESMTPA id d55ec073;
        Mon, 12 Apr 2021 13:09:38 +0000 (UTC)
From: David Edmondson <david.edmondson@oracle.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        "H. Peter Anvin" <hpa@zytor.com>, x86@kernel.org,
        Sean Christopherson <seanjc@google.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Joerg Roedel <joro@8bytes.org>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Jim Mattson <jmattson@google.com>,
        Ingo Molnar <mingo@redhat.com>,
        David Edmondson <david.edmondson@oracle.com>
Subject: [PATCH 0/6] KVM: x86: Make the cause of instruction emulation
 available to user-space
Date: Mon, 12 Apr 2021 14:09:31 +0100
Message-Id: <20210412130938.68178-1-david.edmondson@oracle.com>
X-Mailer: git-send-email 2.30.2
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instruction emulation happens for a variety of reasons, yet on error
we have no idea exactly what triggered it. Add a cause of emulation to
the various originators and pass it upstream when emulation fails.

Joao originally produced the patches but is busy with other things and
I wanted to use it, so picked it up.

Tested by reverting commit 51b958e5aeb1e18c00332e0b37c5d4e95a3eff84
("KVM: x86: clflushopt should be treated as a no-op by emulation")
then running the test included in
https://lore.kernel.org/r/20201118121129.6276-1-david.edmondson@oracle.com.

Joao Martins (6):
  KVM: x86: add an emulation_reason to x86_emulate_instruction()
  KVM: x86: pass emulation_reason to handle_emulation_failure()
  KVM: x86: add emulation_reason to kvm_emulate_instruction()
  KVM: x86: pass a proper reason to kvm_emulate_instruction()
  KVM: SVM: pass a proper reason in kvm_emulate_instruction()
  KVM: VMX: pass a proper reason in kvm_emulate_instruction()

 arch/x86/include/asm/kvm_host.h | 27 +++++++++++++++++++++++--
 arch/x86/kvm/mmu/mmu.c          |  4 ++--
 arch/x86/kvm/svm/avic.c         |  3 ++-
 arch/x86/kvm/svm/svm.c          | 26 +++++++++++++-----------
 arch/x86/kvm/vmx/vmx.c          | 17 ++++++++--------
 arch/x86/kvm/x86.c              | 35 ++++++++++++++++++++++-----------
 arch/x86/kvm/x86.h              |  3 ++-
 7 files changed, 78 insertions(+), 37 deletions(-)
```
#### [PATCH v2 0/4]  Add support for XMM fast hypercalls
##### From: Siddharth Chandrasekaran <sidcha@amazon.de>

```c
From patchwork Mon Apr 12 17:00:13 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Siddharth Chandrasekaran <sidcha@amazon.de>
X-Patchwork-Id: 12198533
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 029EFC43460
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 17:02:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C962E6023C
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 17:02:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S244410AbhDLRCs (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 13:02:48 -0400
Received: from smtp-fw-9102.amazon.com ([207.171.184.29]:16009 "EHLO
        smtp-fw-9102.amazon.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S243659AbhDLRBo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 13:01:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
  d=amazon.de; i=@amazon.de; q=dns/txt; s=amazon201209;
  t=1618246887; x=1649782887;
  h=from:to:cc:subject:date:message-id:mime-version;
  bh=rqIXEoKr8J06sdj1H8DHbETKlNN7iSR0KNAHaBFZ++A=;
  b=SclBWRXYus0mkGCeRdXZ3YXtUZKaVogr37JxIqMhkU7N5Q3U5crEECus
   nXf5iWOcFJ5lLp4StAidEcagIlSPpXAX6Y2VbKDCFSA4cLk/CPD2zhUeZ
   c1u2t/ZcO8wERxbilT720jcyOH30NtYWNFI8GrP5ldWYPY8TUDmwDOA2L
   8=;
X-IronPort-AV: E=Sophos;i="5.82,216,1613433600";
   d="scan'208";a="126988018"
Received: from pdx4-co-svc-p1-lb2-vlan3.amazon.com (HELO
 email-inbound-relay-1e-42f764a0.us-east-1.amazon.com) ([10.25.36.214])
  by smtp-border-fw-out-9102.sea19.amazon.com with ESMTP;
 12 Apr 2021 17:00:59 +0000
Received: from EX13D28EUC003.ant.amazon.com
 (iad12-ws-svc-p26-lb9-vlan2.iad.amazon.com [10.40.163.34])
        by email-inbound-relay-1e-42f764a0.us-east-1.amazon.com (Postfix) with
 ESMTPS id D3C0DC03BD;
        Mon, 12 Apr 2021 17:00:52 +0000 (UTC)
Received: from uc8bbc9586ea454.ant.amazon.com (10.43.161.253) by
 EX13D28EUC003.ant.amazon.com (10.43.164.43) with Microsoft SMTP Server (TLS)
 id 15.0.1497.2; Mon, 12 Apr 2021 17:00:44 +0000
From: Siddharth Chandrasekaran <sidcha@amazon.de>
To: "K. Y. Srinivasan" <kys@microsoft.com>,
        Haiyang Zhang <haiyangz@microsoft.com>,
        Stephen Hemminger <sthemmin@microsoft.com>,
        Wei Liu <wei.liu@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        <x86@kernel.org>, "H. Peter Anvin" <hpa@zytor.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        "Sean Christopherson" <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        "Joerg Roedel" <joro@8bytes.org>
CC: Siddharth Chandrasekaran <sidcha@amazon.de>,
        Alexander Graf <graf@amazon.com>,
        Evgeny Iakovlev <eyakovl@amazon.de>,
        Liran Alon <liran@amazon.com>,
        Ioannis Aslanidis <iaslan@amazon.de>,
        <linux-hyperv@vger.kernel.org>, <linux-kernel@vger.kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH v2 0/4]  Add support for XMM fast hypercalls
Date: Mon, 12 Apr 2021 19:00:13 +0200
Message-ID: <cover.1618244920.git.sidcha@amazon.de>
X-Mailer: git-send-email 2.17.1
MIME-Version: 1.0
X-Originating-IP: [10.43.161.253]
X-ClientProxiedBy: EX13D16UWB001.ant.amazon.com (10.43.161.17) To
 EX13D28EUC003.ant.amazon.com (10.43.164.43)
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hyper-V supports the use of XMM registers to perform fast hypercalls.
This allows guests to take advantage of the improved performance of the
fast hypercall interface even though a hypercall may require more than
(the current maximum of) two general purpose registers.

The XMM fast hypercall interface uses an additional six XMM registers
(XMM0 to XMM5) to allow the caller to pass an input parameter block of
up to 112 bytes. Hyper-V can also return data back to the guest in the
remaining XMM registers that are not used by the current hypercall.

Although the Hyper-v TLFS mentions that a guest cannot use this feature
unless the hypervisor advertises support for it, some hypercalls which
we plan on upstreaming in future uses them anyway. This patchset adds
necessary infrastructure for handling input/output via XMM registers and
patches kvm_hv_flush_tlb() to use xmm input arguments.

~ Sid.

v2:
- Add hc.fast to is_xmm_fast_hypercall() check
- Split CPUID feature bits for input and output

Siddharth Chandrasekaran (4):
  KVM: x86: Move FPU register accessors into fpu.h
  KVM: hyper-v: Collect hypercall params into struct
  KVM: x86: kvm_hv_flush_tlb use inputs from XMM registers
  KVM: hyper-v: Advertise support for fast XMM hypercalls

 arch/x86/include/asm/hyperv-tlfs.h |   7 +-
 arch/x86/kvm/emulate.c             | 138 +++-------------
 arch/x86/kvm/fpu.h                 | 140 +++++++++++++++++
 arch/x86/kvm/hyperv.c              | 242 +++++++++++++++++++----------
 4 files changed, 327 insertions(+), 200 deletions(-)
 create mode 100644 arch/x86/kvm/fpu.h
```
#### [PATCH v12 00/13] Add AMD SEV guest live migration support
##### From: Ashish Kalra <Ashish.Kalra@amd.com>
From: Ashish Kalra <ashish.kalra@amd.com>

```c
From patchwork Mon Apr 12 19:42:15 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ashish Kalra <Ashish.Kalra@amd.com>
X-Patchwork-Id: 12198721
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-18.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,
	SPF_PASS,USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 48FB6C433B4
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 19:42:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 0FF4B6109E
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 19:42:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237660AbhDLTmt (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 15:42:49 -0400
Received: from mail-dm6nam11on2059.outbound.protection.outlook.com
 ([40.107.223.59]:55880
        "EHLO NAM11-DM6-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S229676AbhDLTmq (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 15:42:46 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=K5TKQyEpJtkZh1ZoTsBPMA/pmEv+lvjOldQCokYuABt8DyCLZDjvUnRhxMlfDioLYQ6lWeyaKHmPvMnpdlGnkAT5yF5URJPkex4d0lWpf9UPgAxzF4oRtaUJxcSA7t3AwUBgsYgHqfez3EmJCgGju9yQFctiYJq05epYeK2OjYchl9iZYunihJ+aa5V5w+3tHILuGfbdGEKe5/qzoyPcOoAuJ8bM8VdXsP85YhMf0/Xf0pa5kKO4tBepJ6axGaKxkORjuuh99RPo/Dn9OxZ5nesLGnkSPQSbK6SEWZgMpHugD0et3YsG9AOPYMMeSM7rEtPZPgm6WjSCpyfuwVFoxA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=BawN9Uv/MbzHfJg0olJ89xQLad74fVBDL9NvarR0NjY=;
 b=HSSNPysAE2FwJMpIuOQHrpGx7Wy+k7hPHPp3pIltZRODCF/RBBUJHX/rEEtACSL7LXFi6XYiAlm8U78ufM3+hewOvTL8oU/iAYoK7lDW4ld6eNgAd4Tisj1NxGKeS7MAmNIEhNQQIC2eVwLrB5j+tg0apB597tAiHyclnPFInFD/vYako3hlCPby8UfPyvTgwzskYF+oLxKx4VUtoUbh7W37pdl+sYWZMd4KbxqbdPngN4dCjD7GCnbnyVAl3Mt9e651/jZMw0qELqFminsDAi1wciqDKzi/gknWcDxC7Ea+Ral7/e0dKL+qXr5yM7T1eeCqilg92+uXHNGBY8Z10w==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=amd.com; s=selector1;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=BawN9Uv/MbzHfJg0olJ89xQLad74fVBDL9NvarR0NjY=;
 b=nLQQX15lfWHVw80RYJqKmEj4tgBmMD4LQQTJqiTTrGmHgC9hRKD77fg5lLdb5R+c+Sig0xOU9jbIam91qmc/pQD1FhDY6vzsWsqiNmLhG2KrhNqnibWEHha0NjGI8NMj5sqQ1841CGkAgZ95qm+aggJ17EXzXLOxb+XHroEo3bo=
Authentication-Results: redhat.com; dkim=none (message not signed)
 header.d=none;redhat.com; dmarc=none action=none header.from=amd.com;
Received: from SN6PR12MB2767.namprd12.prod.outlook.com (2603:10b6:805:75::23)
 by SN6PR12MB2640.namprd12.prod.outlook.com (2603:10b6:805:6c::20) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.22; Mon, 12 Apr
 2021 19:42:25 +0000
Received: from SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e]) by SN6PR12MB2767.namprd12.prod.outlook.com
 ([fe80::1fb:7d59:2c24:615e%6]) with mapi id 15.20.4020.022; Mon, 12 Apr 2021
 19:42:25 +0000
From: Ashish Kalra <Ashish.Kalra@amd.com>
To: pbonzini@redhat.com
Cc: tglx@linutronix.de, mingo@redhat.com, hpa@zytor.com,
        joro@8bytes.org, bp@suse.de, thomas.lendacky@amd.com,
        x86@kernel.org, kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        srutherford@google.com, seanjc@google.com,
        venu.busireddy@oracle.com, brijesh.singh@amd.com
Subject: [PATCH v12 00/13] Add AMD SEV guest live migration support
Date: Mon, 12 Apr 2021 19:42:15 +0000
Message-Id: <cover.1618254007.git.ashish.kalra@amd.com>
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SN4PR0601CA0013.namprd06.prod.outlook.com
 (2603:10b6:803:2f::23) To SN6PR12MB2767.namprd12.prod.outlook.com
 (2603:10b6:805:75::23)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ashkalra_ubuntu_server.amd.com (165.204.77.1) by
 SN4PR0601CA0013.namprd06.prod.outlook.com (2603:10b6:803:2f::23) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.17 via Frontend
 Transport; Mon, 12 Apr 2021 19:42:24 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 46f4eda6-6ec7-45b9-0d27-08d8fdeb18ec
X-MS-TrafficTypeDiagnostic: SN6PR12MB2640:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <SN6PR12MB2640756FFFD8FDF4168C0C0F8E709@SN6PR12MB2640.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:229;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 ZAy1RYoAkYcgPp1Sj4xs1UWB1ZXeegS0lvxqxiZUXSZmJY9DfvxHGTmAud4FJgYGj1kjBhxradeY6MlXzGuCWO7JEOLwDK4MvcOWs1IzD0MiR9kZA4x43E+uP8DWzAaDYV/3mSRj1y4WvMCPbJhJZCWE0GTWXO+LScTvLsWwDSOtFli1v2xu393OunizePF+rC5+yxWGvEJWit+5WCZp4xwK4uqh37kegP3x4OjRvtX9WlbHVhs0ZJZ6BjdY1o4kJBMX0ITr1mxAEP/vjHCEKcaaYMlpZsMUtzW4DPFxJxiivK3NQO7yINyBLdHdNKcNLHIB5/YoEdl+Udxhh6WwSHMnfkas1xrg1FLSiOeNx4ob+TOYeDKE8u+YLwONU0f8YL9u3Np+blroPX75E6qvv0zxtp8dkJrMxvfRtui8F0Qo/WMdWZFDUJRy9PhQsowD0g0BsfnLmcZsoAhRmfiEVN+PmqfjwtHawd3NjvC/t7Vx3V+CGiQfa2+FC030BTAEd3qBIiAc2nuKUuYtLiemMzswGjOQhdLMPs7HLejeSIZB3r1no2JDORJjbbvqulBTgAsWg5wCcd5NPiwPt5Z53+dfxuAehpNBeOOzcfMn0pkPYX+MiFBi8tmux2aqb8rvKa9sIoCduU9Xr2J14Ym4tGPq50R/r0aAT3XeTv2OpMdxLoQNd9Jc28p/SvfUL23TA/Kjc5PudXd2ekYiNTZIrYXvGrsHTH7KVjYGVFfcA48=
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR12MB2767.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(346002)(396003)(136003)(366004)(39860400002)(376002)(38100700002)(38350700002)(52116002)(7696005)(6486002)(86362001)(2616005)(8936002)(956004)(6666004)(16526019)(316002)(6916009)(186003)(36756003)(66946007)(2906002)(83380400001)(4326008)(966005)(8676002)(5660300002)(66476007)(7416002)(66556008)(26005)(478600001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: =?utf-8?q?hZLiu4JFTjrkY6J2F3oWFduHvWQRTw?=
	=?utf-8?q?SUzdz4A2julQeQQcQJ7XNdiRuuaEjyEqz+nJxdLJnFggDQqJ//qQryrkwStdfNIyz?=
	=?utf-8?q?NJrPlwfigYh9RotFzdhMVZdPYoniwlopwGOGl6HD+JNBf5kGh8w3dJklVZhwiPS1J?=
	=?utf-8?q?OpS6fxtls0Hfue68//g+m6z7uTH5uyeYGTpRPFh1b86zQPfinnoyZiP7zn0RCGm10?=
	=?utf-8?q?wL2E98GlCI0FU4tGIQcqNzHzVTXInuCzLfe5nprocErZuQS0NgbOUfQRTx9igBQJK?=
	=?utf-8?q?u+MWFwRiH95dtZ2mglJPLlT6lY/FZ4RS6xrlaerQgc2+ekHO4IXNT7Q9DkQyPaeIw?=
	=?utf-8?q?O6QPMFodALtaGpxhl3GoBRQl778JvyF5hpO8EJFOd7aouXjKonPAZGq+y+P3r8NKP?=
	=?utf-8?q?yER9Vig9Zni/hWzaj/g7uacsGf1gzNs0w2SHNbCyQLLm6nSK5xYFMxkQzyNpmlqlb?=
	=?utf-8?q?U8LbAQs8jtapiU+gNjJAoMDd35o7dEZboRolKPqN5ckPitQTg8rxJScE7CH5zYKV8?=
	=?utf-8?q?AydH2citaHb/apStcmi4G5dIuI6lmlaZNBndkJo0qPSD0XwqDD7gVWc53rtDE6H7o?=
	=?utf-8?q?jAqYFvI3Yn0e3jvZuQUkevSlg+Ww6OtXbCDNjtlhcbRBSnTyq+uNdnS5wdCvIYCUO?=
	=?utf-8?q?UBGgHMQCBIfaa5YsE96CCD3trb0i0pZXZLlLoTOpK2axoV/TIoxtUFXqLy18lRqUo?=
	=?utf-8?q?sXSF351HyKu7mZJ4BVCz8HWDWpHuJcLwMyN1PLWehRFP7JnUrTi0yt0rynTElZdKG?=
	=?utf-8?q?tDQtzDh91Yl7rosdGjLbVOdDuFOmtkIDE+X0V6vpDmo9veh1YhVfZJdoYT8IsxXYA?=
	=?utf-8?q?Cb853ia5BNRGTRH7V1U92g97L3dnLLnbEZCddzMqv1wtjEFnNcPyyVEFBrj4SEZYP?=
	=?utf-8?q?VbIy8YgHKKHdKFIEOAZMALSTHBYIhVvZ2nULugkeXpODZL3Qln3//Ej+rPpU61WrI?=
	=?utf-8?q?1kDGqqIBlNELKPV04g+haC+xN31QoncaWbRssaEnWdLCG2abulQo3Ol9j8TZJUtOB?=
	=?utf-8?q?BKjRRbBPVzcw3qJ/50Ew4sQdpd5OS7Hh4tk2YWgLt1PaENrL9dzlq5Z1DN226Ukn3?=
	=?utf-8?q?g7w91GbKYCqIrqI9Jiw9Hul2IBe5UdB60QqvNYoJZsuEnfSr5NLF3oRXJIrBbW62e?=
	=?utf-8?q?sTWm1QBhESTq1N7jSY1ekYjjs84Suj6bDrw8O9AUTuJRm5RqNZeCFoNXmH3fSDyON?=
	=?utf-8?q?d/V3me4Y/nuvyXlNN2CMx9XAeKiwikTgcGO9ph134QwTD4Hs3rOjkhrKeM14eh9Me?=
	=?utf-8?q?L4JlPy7iZnp4Jy?=
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 46f4eda6-6ec7-45b9-0d27-08d8fdeb18ec
X-MS-Exchange-CrossTenant-AuthSource: SN6PR12MB2767.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 Apr 2021 19:42:25.1889
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 RNUXRn2C94pjQEgEYKAI+/Zb4UkBTcfpp38wD6jPruKLVbn1fOXbPgGbiPXkqM0NnKzgq2CAcLZAcAaSUTuMrg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR12MB2640
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ashish Kalra <ashish.kalra@amd.com>

The series add support for AMD SEV guest live migration commands. To protect the
confidentiality of an SEV protected guest memory while in transit we need to
use the SEV commands defined in SEV API spec [1].

SEV guest VMs have the concept of private and shared memory. Private memory
is encrypted with the guest-specific key, while shared memory may be encrypted
with hypervisor key. The commands provided by the SEV FW are meant to be used
for the private memory only. The patch series introduces a new hypercall.
The guest OS can use this hypercall to notify the page encryption status.
If the page is encrypted with guest specific-key then we use SEV command during
the migration. If page is not encrypted then fallback to default.

The patch uses the KVM_EXIT_HYPERCALL exitcode and hypercall to
userspace exit functionality as a common interface from the guest back to the
VMM and passing on the guest shared/unencrypted page information to the
userspace VMM/Qemu. Qemu can consult this information during migration to know 
whether the page is encrypted.

This section descibes how the SEV live migration feature is negotiated
between the host and guest, the host indicates this feature support via 
KVM_FEATURE_CPUID. The guest firmware (OVMF) detects this feature and
sets a UEFI enviroment variable indicating OVMF support for live
migration, the guest kernel also detects the host support for this
feature via cpuid and in case of an EFI boot verifies if OVMF also
supports this feature by getting the UEFI enviroment variable and if it
set then enables live migration feature on host by writing to a custom
MSR, if not booted under EFI, then it simply enables the feature by
again writing to the custom MSR. The MSR is also handled by the
userspace VMM/Qemu.

A branch containing these patches is available here:
https://github.com/AMDESE/linux/tree/sev-migration-v12

[1] https://developer.amd.com/wp-content/resources/55766.PDF

Changes since v11:
- Clean up and remove kvm_x86_ops callback for page_enc_status_hc and
  instead add a new per-VM flag to support/enable the page encryption
  status hypercall.
- Remove KVM_EXIT_DMA_SHARE/KVM_EXIT_DMA_UNSHARE exitcodes and instead
  use the KVM_EXIT_HYPERCALL exitcode for page encryption status
  hypercall to userspace functionality. 

Changes since v10:
- Adds new KVM_EXIT_DMA_SHARE/KVM_EXIT_DMA_UNSHARE hypercall to
  userspace exit functionality as a common interface from the guest back to the
  KVM and passing on the guest shared/unencrypted region information to the
  userspace VMM/Qemu. KVM/host kernel does not maintain the guest shared
  memory regions information anymore. 
- Remove implicit enabling of SEV live migration feature for an SEV
  guest, now this is explicitly in control of the userspace VMM/Qemu.
- Custom MSR handling is also now moved into userspace VMM/Qemu.
- As KVM does not maintain the guest shared memory region information
  anymore, sev_dbg_crypt() cannot bypass unencrypted guest memory
  regions without support from userspace VMM/Qemu.

Changes since v9:
- Transitioning from page encryption bitmap to the shared pages list
  to keep track of guest's shared/unencrypted memory regions.
- Move back to marking the complete _bss_decrypted section as 
  decrypted in the shared pages list.
- Invoke a new function check_kvm_sev_migration() via kvm_init_platform()
  for guest to query for host-side support for SEV live migration 
  and to enable the SEV live migration feature, to avoid
  #ifdefs in code 
- Rename MSR_KVM_SEV_LIVE_MIG_EN to MSR_KVM_SEV_LIVE_MIGRATION.
- Invoke a new function handle_unencrypted_region() from 
  sev_dbg_crypt() to bypass unencrypted guest memory regions.

Changes since v8:
- Rebasing to kvm next branch.
- Fixed and added comments as per review feedback on v8 patches.
- Removed implicitly enabling live migration for incoming VMs in
  in KVM_SET_PAGE_ENC_BITMAP, it is now done via KVM_SET_MSR ioctl.
- Adds support for bypassing unencrypted guest memory regions for
  DBG_DECRYPT API calls, guest memory region encryption status in
  sev_dbg_decrypt() is referenced using the page encryption bitmap.

Changes since v7:
- Removed the hypervisor specific hypercall/paravirt callback for
  SEV live migration and moved back to calling kvm_sev_hypercall3 
  directly.
- Fix build errors as
  Reported-by: kbuild test robot <lkp@intel.com>, specifically fixed
  build error when CONFIG_HYPERVISOR_GUEST=y and
  CONFIG_AMD_MEM_ENCRYPT=n.
- Implicitly enabled live migration for incoming VM(s) to handle 
  A->B->C->... VM migrations.
- Fixed Documentation as per comments on v6 patches.
- Fixed error return path in sev_send_update_data() as per comments 
  on v6 patches. 

Changes since v6:
- Rebasing to mainline and refactoring to the new split SVM
  infrastructre.
- Move to static allocation of the unified Page Encryption bitmap
  instead of the dynamic resizing of the bitmap, the static allocation
  is done implicitly by extending kvm_arch_commit_memory_region() callack
  to add svm specific x86_ops which can read the userspace provided memory
  region/memslots and calculate the amount of guest RAM managed by the KVM
  and grow the bitmap.
- Fixed KVM_SET_PAGE_ENC_BITMAP ioctl to set the whole bitmap instead
  of simply clearing specific bits.
- Removed KVM_PAGE_ENC_BITMAP_RESET ioctl, which is now performed using
  KVM_SET_PAGE_ENC_BITMAP.
- Extended guest support for enabling Live Migration feature by adding a
  check for UEFI environment variable indicating OVMF support for Live
  Migration feature and additionally checking for KVM capability for the
  same feature. If not booted under EFI, then we simply check for KVM
  capability.
- Add hypervisor specific hypercall for SEV live migration by adding
  a new paravirt callback as part of x86_hyper_runtime.
  (x86 hypervisor specific runtime callbacks)
- Moving MSR handling for MSR_KVM_SEV_LIVE_MIG_EN into svm/sev code 
  and adding check for SEV live migration enabled by guest in the 
  KVM_GET_PAGE_ENC_BITMAP ioctl.
- Instead of the complete __bss_decrypted section, only specific variables
  such as hv_clock_boot and wall_clock are marked as decrypted in the
  page encryption bitmap

Changes since v5:
- Fix build errors as
  Reported-by: kbuild test robot <lkp@intel.com>

Changes since v4:
- Host support has been added to extend KVM capabilities/feature bits to 
  include a new KVM_FEATURE_SEV_LIVE_MIGRATION, which the guest can
  query for host-side support for SEV live migration and a new custom MSR
  MSR_KVM_SEV_LIVE_MIG_EN is added for guest to enable the SEV live
  migration feature.
- Ensure that _bss_decrypted section is marked as decrypted in the
  page encryption bitmap.
- Fixing KVM_GET_PAGE_ENC_BITMAP ioctl to return the correct bitmap
  as per the number of pages being requested by the user. Ensure that
  we only copy bmap->num_pages bytes in the userspace buffer, if
  bmap->num_pages is not byte aligned we read the trailing bits
  from the userspace and copy those bits as is. This fixes guest
  page(s) corruption issues observed after migration completion.
- Add kexec support for SEV Live Migration to reset the host's
  page encryption bitmap related to kernel specific page encryption
  status settings before we load a new kernel by kexec. We cannot
  reset the complete page encryption bitmap here as we need to
  retain the UEFI/OVMF firmware specific settings.

Changes since v3:
- Rebasing to mainline and testing.
- Adding a new KVM_PAGE_ENC_BITMAP_RESET ioctl, which resets the 
  page encryption bitmap on a guest reboot event.
- Adding a more reliable sanity check for GPA range being passed to
  the hypercall to ensure that guest MMIO ranges are also marked
  in the page encryption bitmap.

Changes since v2:
 - reset the page encryption bitmap on vcpu reboot

Changes since v1:
 - Add support to share the page encryption between the source and target
   machine.
 - Fix review feedbacks from Tom Lendacky.
 - Add check to limit the session blob length.
 - Update KVM_GET_PAGE_ENC_BITMAP icotl to use the base_gfn instead of
   the memory slot when querying the bitmap.

Ashish Kalra (5):
  KVM: X86: Introduce KVM_HC_PAGE_ENC_STATUS hypercall
  KVM: x86: Introduce new KVM_FEATURE_SEV_LIVE_MIGRATION feature &
    Custom MSR.
  EFI: Introduce the new AMD Memory Encryption GUID.
  x86/kvm: Add guest support for detecting and enabling SEV Live
    Migration feature.
  x86/kvm: Add kexec support for SEV Live Migration.

Brijesh Singh (8):
  KVM: SVM: Add KVM_SEV SEND_START command
  KVM: SVM: Add KVM_SEND_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_SEND_FINISH command
  KVM: SVM: Add support for KVM_SEV_RECEIVE_START command
  KVM: SVM: Add KVM_SEV_RECEIVE_UPDATE_DATA command
  KVM: SVM: Add KVM_SEV_RECEIVE_FINISH command
  KVM: x86: Add AMD SEV specific Hypercall3
  mm: x86: Invoke hypercall when page encryption status is changed

 .../virt/kvm/amd-memory-encryption.rst        | 120 +++++
 Documentation/virt/kvm/cpuid.rst              |   5 +
 Documentation/virt/kvm/hypercalls.rst         |  15 +
 Documentation/virt/kvm/msr.rst                |  12 +
 arch/x86/include/asm/kvm_host.h               |   2 +
 arch/x86/include/asm/kvm_para.h               |  12 +
 arch/x86/include/asm/mem_encrypt.h            |   8 +
 arch/x86/include/asm/paravirt.h               |  10 +
 arch/x86/include/asm/paravirt_types.h         |   2 +
 arch/x86/include/uapi/asm/kvm_para.h          |   4 +
 arch/x86/kernel/kvm.c                         |  76 +++
 arch/x86/kernel/paravirt.c                    |   1 +
 arch/x86/kvm/cpuid.c                          |   3 +-
 arch/x86/kvm/svm/sev.c                        | 454 ++++++++++++++++++
 arch/x86/kvm/x86.c                            |  29 ++
 arch/x86/mm/mem_encrypt.c                     |  98 +++-
 arch/x86/mm/pat/set_memory.c                  |   7 +
 include/linux/efi.h                           |   1 +
 include/linux/psp-sev.h                       |   8 +-
 include/uapi/linux/kvm.h                      |  39 ++
 include/uapi/linux/kvm_para.h                 |   1 +
 21 files changed, 901 insertions(+), 6 deletions(-)
```
#### [PATCH 0/3] KVM: Fixes and a cleanup for coalesced MMIO
##### From: Sean Christopherson <seanjc@google.com>

```c
From patchwork Mon Apr 12 22:20:47 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <seanjc@google.com>
X-Patchwork-Id: 12198887
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-21.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT,
	USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 70F40C433ED
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 22:20:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4B3A06135C
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 22:20:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1343673AbhDLWVN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 18:21:13 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45618 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S240210AbhDLWVN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 18:21:13 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 98B03C061574
        for <kvm@vger.kernel.org>; Mon, 12 Apr 2021 15:20:54 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id l30so1832462ybj.1
        for <kvm@vger.kernel.org>; Mon, 12 Apr 2021 15:20:54 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=reply-to:date:message-id:mime-version:subject:from:to:cc;
        bh=FmBbxZ043goYbQIFSTxJ5QFyMNro4zr+9usEl2+6KDo=;
        b=hebwHaNs+u2Qy3E5HnHs5sMbimi6gtUB5qGU2iwPTwr39qciShPjHjm2OjWEBnJv/H
         2Z5lGaeZ/CxTwz0GnZt4uyBMidroUpcfjHNxD54TFfmT7toDqzikl9Kp3K708NdTulaq
         W4OEOj+1tePlpcyup7wK3zdUH2C+ypfZ8CSjfzyfsQWY8Cp3lkXJ7quWGdr9OyKdluhS
         sAGgDl84wKM4pJWIvxCUz5iIFkXGbBy2e4pKVc/RfErxIS8M7GpgnWrctmIW06X5AoFQ
         r2LHB4gYWVJVQ7b3s/WBQz5yD9mZ15LQChGVrPOYofyYgxHHbWTzu0E6ydSR4VVS8EYU
         /c4A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:reply-to:date:message-id:mime-version:subject
         :from:to:cc;
        bh=FmBbxZ043goYbQIFSTxJ5QFyMNro4zr+9usEl2+6KDo=;
        b=kjxe30DdEEqx/Ew45x0hQqEI3OpBUDu2mE4g9F+vm3GMZuTXXS1zGnkrkfunB/sm5/
         32y6rHFJDMGBlh/DIQkyMWf+PLa1g0zg6L+w3DiCUjibArg5aJ9sITW2vHHzKJwfCopS
         UbUE6XjyLQLQDrEmlPlvp61suOHFmsNYyOmEqx+p4KGNiGOlM1p32DZRXcypcu9Y44pP
         QE1SAFR7IqnUp75oJ12ipqTKEklGGkQWUxye7DJFvQMCY6R6hdOoNa6oQCduftIukkal
         bqyo4q5vQVjftL8n3D6rop7CPy1c1xnnYZGZuwLFBmNqm3u31a8WSiQs3XFY64KPh821
         MPTw==
X-Gm-Message-State: AOAM530V+Bif8jiYcAOXuIioUBssM1jn491cA6V0vUWYR96cT+IkpQSG
        oKavcyWqOUx+FlE5DubvDxszjZ4PkF8=
X-Google-Smtp-Source: 
 ABdhPJxLzjwHbeMX6Sc39ErUuoMnIIuqepvQr0GA8yDCc1C9yqhYjoovvhYRQv4GKHvI5QOlH8N/sWIX7t0=
X-Received: from seanjc798194.pdx.corp.google.com
 ([2620:15c:f:10:f031:9c1c:56c7:c3bf])
 (user=seanjc job=sendgmr) by 2002:a25:25d0:: with SMTP id
 l199mr27919439ybl.256.1618266053917;
 Mon, 12 Apr 2021 15:20:53 -0700 (PDT)
Reply-To: Sean Christopherson <seanjc@google.com>
Date: Mon, 12 Apr 2021 15:20:47 -0700
Message-Id: <20210412222050.876100-1-seanjc@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.31.1.295.g9ea45b61b8-goog
Subject: [PATCH 0/3] KVM: Fixes and a cleanup for coalesced MMIO
From: Sean Christopherson <seanjc@google.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Sean Christopherson <seanjc@google.com>,
        Hao Sun <sunhao.th@gmail.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fix two bugs that are exposed if unregistered a device on an I/O bus fails
due to OOM.  Tack on opportunistic cleanup in the related code.
 
Sean Christopherson (3):
  KVM: Destroy I/O bus devices on unregister failure _after_ sync'ing
    SRCU
  KVM: Stop looking for coalesced MMIO zones if the bus is destroyed
  KVM: Add proper lockdep assertion in I/O bus unregister

 include/linux/kvm_host.h  |  4 ++--
 virt/kvm/coalesced_mmio.c | 19 +++++++++++++++++--
 virt/kvm/kvm_main.c       | 26 ++++++++++++++++----------
 3 files changed, 35 insertions(+), 14 deletions(-)
```
#### [PATCH 0/7 v7] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Mon Apr 12 21:56:04 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12198961
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,MSGID_FROM_MTA_HEADER,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 155FDC433ED
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 22:45:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EB60A61246
	for <kvm@archiver.kernel.org>; Mon, 12 Apr 2021 22:45:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S244727AbhDLWpX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 12 Apr 2021 18:45:23 -0400
Received: from aserp2130.oracle.com ([141.146.126.79]:56768 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S238085AbhDLWpW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 12 Apr 2021 18:45:22 -0400
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 13CMdhOb017999;
        Mon, 12 Apr 2021 22:45:01 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : content-transfer-encoding : content-type :
 mime-version; s=corp-2020-01-29;
 bh=YGXCCLw7OFf7O/CtEm69QSDmw5u4ixNLwGc7y5OQFDI=;
 b=wCmOfs5uDCP24XGdyGcZ1ukEY0pxxQ6UUD43Wn4P/f82Zxa6KHXzkBikRC1Vp7/3UxfP
 SY20F6IGkW60ypjFb5IUDUwWyDhkBspnKu6ZSmVPQxzMpH3NtoHt0lm7HECti5ERmdX7
 MTufDzuEoeJ0XiFHBy4MzTgMwGhRP2sFLbwr6qOpaVJpdO1r3T6MzDCXKFfIz75lvmPq
 zlsXFyOzUf7mYxG5VVhHJnqdzagsEj6RtRSPna6yNv74YWp3DBNQQwTRBySXAP+br/lg
 w5GjfshkJ4FlEjSVvkJ2bYMlsYAUT1ccPL//cRX2mS8Pv/VgfCVTe5TbaHVkrSBW75MM Cg==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2130.oracle.com with ESMTP id 37u1hbde1u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 12 Apr 2021 22:45:01 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 13CMeLjO153578;
        Mon, 12 Apr 2021 22:45:00 GMT
Received: from nam10-bn7-obe.outbound.protection.outlook.com
 (mail-bn7nam10lp2104.outbound.protection.outlook.com [104.47.70.104])
        by userp3030.oracle.com with ESMTP id 37unxw0q5h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 12 Apr 2021 22:45:00 +0000
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=QsXC7XaoVDib2w2et5mKvJ8FigRxB87iQAOaBMwTetZY4Yqi7J0Jp6MZ82m5AdbLcrZrfupa7UASR49UeCj64L23IFfr553MSEANgbOjQC7NAI82VLwRIZzMXm6iKiZo6PsFR02tnFkt3jUF2rzMBE2CEEKi2qRzAUD30kCkU3QRuOUJUo9jYgUUjOhdXdYl4/vO/rhDdg1Lc8CgNsq5nVdjmZxmUvJu6DibjLAFiVbPRGVZeWuIjYpNkgCIbU3DMKwyiZ25fLmfvYg0LpOFUeF2vamUU+SXcmXrcOQhT9nslcLMBvzFX+ct8Mq56eHm6bHfW4nStv8SF8obfeBTyA==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=YGXCCLw7OFf7O/CtEm69QSDmw5u4ixNLwGc7y5OQFDI=;
 b=CtuiTePQos2LWJbYXn/2oU4YDT94K4Dg/wZbqOWlFifPLlYY3LSGVrcNHuafqBQ76872YP8MSvJ4rFKH2z6SsAP10D3whJ6hLoqJEneMUTrTTGFzUVyDThU1Rmrq784rWlGoKHfZCni/LGqLC1w6+rBWBkceK5vZIXWI/NwfUCOk3RuGLKw3DsO2EffoUEUm7x6d5K0gEurx8wuBlZZoXiD/WUb+pQ9+f8eb5csTGcUWomBiqrd8IMEkpphpJSpEEqtA61S6CYhZdW9R6nk5JAMsfU9NcDY9WDI3CzG36YoOVh29RqG96pzBfANc9kwzhsPa1YZLZ9qy17Wh1gYQhQ==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=oracle.com; dmarc=pass action=none header.from=oracle.com;
 dkim=pass header.d=oracle.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=oracle.onmicrosoft.com; s=selector2-oracle-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=YGXCCLw7OFf7O/CtEm69QSDmw5u4ixNLwGc7y5OQFDI=;
 b=0AF3CZKDp3TFMLO8p6/0gqDW7pguk84IepP5MyrCuM9f6TZ7SQ8XffTaVArgwD+qPgcFv18Y4Y2ftrUmVb6Iio7PGFH3dqjwz1W2U+dyY5kzATUzFykQdoBCvuxrSSMJUDfLKfPrtMyInxY//PRQVvHRw5qoW/qXmE1r0uUYh8w=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=oracle.com;
Received: from SN6PR10MB3021.namprd10.prod.outlook.com (2603:10b6:805:cc::19)
 by SN6PR10MB3022.namprd10.prod.outlook.com (2603:10b6:805:d8::25) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3999.28; Mon, 12 Apr
 2021 22:44:58 +0000
Received: from SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44]) by SN6PR10MB3021.namprd10.prod.outlook.com
 ([fe80::5911:9489:e05c:2d44%5]) with mapi id 15.20.4020.022; Mon, 12 Apr 2021
 22:44:58 +0000
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/7 v7] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
 tables on vmrun of nested guests
Date: Mon, 12 Apr 2021 17:56:04 -0400
Message-Id: <20210412215611.110095-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.25.4
X-Originating-IP: [138.3.201.29]
X-ClientProxiedBy: BYAPR06CA0058.namprd06.prod.outlook.com
 (2603:10b6:a03:14b::35) To SN6PR10MB3021.namprd10.prod.outlook.com
 (2603:10b6:805:cc::19)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from ban25x6uut29.us.oracle.com (138.3.201.29) by
 BYAPR06CA0058.namprd06.prod.outlook.com (2603:10b6:a03:14b::35) with
 Microsoft SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.4020.17 via Frontend
 Transport; Mon, 12 Apr 2021 22:44:57 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 63802c67-863e-445a-558c-08d8fe0499b7
X-MS-TrafficTypeDiagnostic: SN6PR10MB3022:
X-Microsoft-Antispam-PRVS: 
 <SN6PR10MB30220956799411B1F8E0737A81709@SN6PR10MB3022.namprd10.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:8882;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 egJHEC4aIQAzjODUdGq1nVYuJ2O6uFi1ZYdaTxjgVizFzNakkQqy6xX9NGCBA3ISz2sYCo+wqVVl0Hs6h7D8SN7sulyWMlhQxqaY5cTqQUXkw/dmqjELjWcSeIepbPuZuKDsnWev99Qq5oeo6tMnGG+0Sc2kcxaUlWWwR06Jh16V1T0o36+L1KRgZHfQR1jBFNic0GKppczhxBPc9B4/OVNU7DLhdeyVwrNmhGSPha7BUOKuJhH4xjHqz3tiPuGVGEV+V9ZKYb67opAhMilA2hEpI8dv+RFbX6SEANxBSDfj3DxiURBeiXVR99AelvI9Eiu8yi3Wb1FkIKjiazIyLd1lbHTSTez0H853+z4L0hWrEy7aYssQpDhSPy4poOZ1YI0/wdSWVagLauIpkWM5fOb6fEoAdWPGBUIxvSxyq1BywjbljAtAy2Qs9Jjo2rbvgvHW6a7s8NzS2Tzd8lD287mxlitSty1VHVGcb+zRMfVWxU3TuGXlRgXDC9btD81ua7LzEalXDOPvdTwksCTxyRSbDHP/ULyim3EGe8fm5wRIn+AyKqmMv0uqdqQQbOcq/wDwdtnKcbeAgFiFE0T8L65EIbvzrJqpDT+zhYmt9CQNjqXo+X7UNf5LSr1Jvf8yhWyIzT6OMseXvGokwUdzyw==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:SN6PR10MB3021.namprd10.prod.outlook.com;PTR:;CAT:NONE;SFS:(366004)(346002)(396003)(376002)(39860400002)(136003)(66476007)(478600001)(66556008)(83380400001)(2616005)(66946007)(36756003)(86362001)(8936002)(1076003)(44832011)(6916009)(316002)(4326008)(956004)(2906002)(7696005)(6486002)(52116002)(38350700002)(6666004)(8676002)(16526019)(5660300002)(26005)(38100700002)(186003);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 uRkMB7iko7e5DyEmzzNsHxX0V5F+gvQzBiODFmC7DG8dp38KlplSYjXzlyefqxi/XwmtEl/Omk/kctc5SNcolpvdxtI/Bma9J+h3PbnVwJVB4FRmOCInTPEVDO9REeC2VYIkTLLkbJovrPRKMwHKYVhRlqAE3++mtf0LtjEraSHUikyV8AxCh4pxd18VS275oM+OxR0wStdRiL2C2EjOjYwYEAI5sSfxdA8kA5mV4mYutPAnxCuwZqCs+U4+lpGAGHuVraFQs6xtYRBr30iWkZzzN2Xt6oL3fOi6ObB7DLqR+VMvocY1LUScDgkfw/O49sJ1yh2o4bSSdeXOcXbqxGgFLRcM2cVHD9GKifJlqSkjok4hgyLW3ZGbVZsD2kOuIniPk4QGgFRAiMGkaygjapCVhmxOYzsL5SHqMRnDpwoPd74OuiT+SrCz68m7E30fpPLlX10iTH4viOJe3KKarvvfePBR11Z4vQyF9d0M59sVEgQZF8/8/Od/bkFbHYVtzzGCBklgKXdOmG0ZcT0VaPf3asyNACGphfZRfZ2Ii7unfKB0orrdUSpUJTCW0+zR5o/N/44ztxpEgVuFnWQVoxDNpDi+Uj6Zk8zZ3BSg5NxtIue01L2m4JDYcJJWWiLuG6qwGXBPOvE4T41EXRmlMCWiiJWrvyAB70AgeOaQWHcQwf/b99zyFKgQlDWKJBKHCYKdRuWHUv1ZVBBKYbGd/HiPs99xB3IQ/45seYHEWZg9tbbOda9Pq81LOAgee561Y/Y7LK8pZk5DifX1YoOZyDPeK676Fjj5sbbjKbrJHy1e/4Yee2VHpo52bC1hukc5NMNMS3W4zuOskOHEUDgwh/Z4hrRvFj5aNSRKOb41hxKt+TG1LHWhoMHV8bJcgRKjapPkO/it4yGK1YEvq7aaurlTnBEJM9f7CDogomddPBTRYwsQH65pjL3Edk3zpgKYMPn4LR/77pW9cG+Zo6YnXa6U1ojgBMvbbKUXJGZ0nTVZW+BNESAnYmu2CElMKR5c/1zlmTr9oNKYn5YswmM+JAQvz0PX9xpqyUXT10H5kyz1ONIkeufYnXyrdVIBBNlQV8Nkl+PSpLGn/nDEcyY6QPSWQ2xJ8ag+9xC2ljQQHGcIbR4bn9jMzfbCvvEF2uO+QGXb+kSpkNxB17VcCpxawG5WCUjAhENeCblL8YQKehkAGHVem+yHIMthccDWskox0dgD5E1p6HHVKGq7AEOrRm8GzqUzKvDL+wTmzy4Qy6uzvv/tSjDHWIwExTw54S7tMWSVysZ4FuPtQp0/L2gY3AvG+klgF+EQaXfPEijbZ7WDFQp+O/qPHtfCtNwBVEXe
X-OriginatorOrg: oracle.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 63802c67-863e-445a-558c-08d8fe0499b7
X-MS-Exchange-CrossTenant-AuthSource: SN6PR10MB3021.namprd10.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 12 Apr 2021 22:44:58.7317
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 4e2c6054-71cb-48f1-bd6c-3a9705aca71b
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 465Q9BRZScDM5mNpYDVJqIVu25Z7CacVIp6b91Jh5Fs1eGWOZ4a71Vkg4WUpaV/V8gzC9SLfUuUvLLlxdCqOnTUbXlGEFlhW8eJyTC8PglE=
X-MS-Exchange-Transport-CrossTenantHeadersStamped: SN6PR10MB3022
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9952
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 bulkscore=0 malwarescore=0
 spamscore=0 adultscore=0 phishscore=0 mlxlogscore=999 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104060000
 definitions=main-2104120146
X-Proofpoint-GUID: zKy70qTvd-4xENiApMx_B_onl_LScGId
X-Proofpoint-ORIG-GUID: zKy70qTvd-4xENiApMx_B_onl_LScGId
X-Proofpoint-Virus-Version: vendor=nai engine=6200 definitions=9952
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 priorityscore=1501
 clxscore=1015 adultscore=0 mlxlogscore=999 impostorscore=0 malwarescore=0
 lowpriorityscore=0 spamscore=0 phishscore=0 bulkscore=0 suspectscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2104060000
 definitions=main-2104120146
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v6 -> v7:
	1. In patch# 4, the logic in nested_svm_check_bitmap_pa() has been
	   fixed. The size of IOPM passed to nested_svm_check_bitmap_pa() has
	   also been corrected. Indentation has been improved.
	2. In patch# 1, the names of the #defines have been changed.
	3. In patch# 2, a new exit code is defined to differentiate between
	   consistency failures and failures after switching to guest mode,
	   because tests need to know the exact failure instead of
	   SVM_EXIT_ERR. This exit code is similar to what nVMX does and
	   appears to be the best solution to differentiate the above-mentioned
	   error scenarios.
	4. In patch# 3, code that unset bit 11:0 of the MSRPm and IOPM tables,
	   has been removed because hardware doesn't care about the value
	   these bits. Also, tests need to verify hardware behavior. So if
	   these bits are unset, the checks in nested_svm_check_bitmap_pa()
	   do not work as expected.
	5. In patch# 7, additional test cases have been added.


[PATCH 1/7 v7] KVM: SVM: Define actual size of IOPM and MSRPM tables
[PATCH 2/7 v7] KVM: nSVM: Define an exit code to reflect consistency
[PATCH 3/7 v7] KVM: nSVM: No need to set bits 11:0 in MSRPM and IOPM
[PATCH 4/7 v7] nSVM: Check addresses of MSR and IO permission maps
[PATCH 5/7 v7] SVM: Use ALIGN macro when aligning 'io_bitmap_area'
[PATCH 6/7 v7] nSVM: Define an exit code to reflect consistency check
[PATCH 7/7 v7] nSVM: Test addresses of MSR and IO permissions maps

 arch/x86/include/uapi/asm/svm.h |  1 +
 arch/x86/kvm/svm/nested.c       | 29 +++++++++++++++++++++++------
 arch/x86/kvm/svm/svm.c          | 20 ++++++++++----------
 arch/x86/kvm/svm/svm.h          |  3 +++
 4 files changed, 37 insertions(+), 16 deletions(-)

Krish Sadhukhan (4):
      KVM: SVM: Define actual size of IOPM and MSRPM tables
      KVM: nSVM: Define an exit code to reflect consistency check failure
      KVM: nSVM: No need to set bits 11:0 in MSRPM and IOPM bitmaps
      nSVM: Check addresses of MSR and IO permission maps

 x86/svm.c       |  2 +-
 x86/svm.h       |  1 +
 x86/svm_tests.c | 78 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++-
 3 files changed, 79 insertions(+), 2 deletions(-)

Krish Sadhukhan (3):
      SVM: Use ALIGN macro when aligning 'io_bitmap_area'
      nSVM: Define an exit code to reflect consistency check failure
      nSVM: Test addresses of MSR and IO permissions maps
```
