

#### [PATCH v8 00/19] KVM RISC-V Support
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
From patchwork Thu Oct  3 05:06:29 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11172087
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5DB4414DB
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 05:07:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3235E222C5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 05:07:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="RjIN4Gtw";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="PTarw0x7"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727349AbfJCFGo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 01:06:44 -0400
Received: from esa5.hgst.iphmx.com ([216.71.153.144]:3936 "EHLO
        esa5.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725497AbfJCFGo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 01:06:44 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1570079204; x=1601615204;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=PIEuOeu7U/Kt1Kj4de+aysu6dAD4lAg836SUqf4HZKs=;
  b=RjIN4GtwadXaLr9MWRlWtfTUFxlyR8A+0cGrqbknMSLy9HFeg5PSiof5
   UcofB5+rWLBzLtSO3EHH+qgv5P8sUvCsAoA/JpuO/vAt27y/IhZjdwxKq
   A8s4VxTqHduqEqcItmnED1ehV+VwlIAzH+N3tDzwSaL3pV/bTdYfCPTfX
   zAwgwnOgnwd8vxWOxUpzcsY5Nx9Ua06uxVPeyp19LyjTOwAezhuIzbSA+
   M4yLyP7yfquL4j9X56MRDIcxqX+H93Y1juJOX4rbQnlqHJIg6wF6IgBs3
   /f29qWZd9kR/2tDZwmHyvKICMfVSnF7LY2OfIdax/l54qr+KDWswD0dNI
   w==;
IronPort-SDR: 
 8aEVDO10LywIJEQMq5nLkL7QFpozJGUFmaHDME19WPd91FuyT50z3k2tdNmdG6qHTMK3cqswNb
 SiYhgU9t7BSSOoXr6fQTimjvH9JfwFbvRcYDc6nR6FBc6QTnI9fzIgVILuHnQHcDh+pv41jT4K
 Mg/Ucu/yflX4PDWS5TSHijmCtbNjhVoSsspSSvSONkp1UugPrrUVLU4ju6RnmX0x3uTdnajfPz
 AnVQGsChDPTAQSd0gZc8ILrJUsk/fhGbYW5FM9BZ3nO0jOyeEWrURHF8q2tLxOKx63+0p2fIo1
 sGw=
X-IronPort-AV: E=Sophos;i="5.67,251,1566835200";
   d="scan'208";a="120461277"
Received: from mail-co1nam03lp2057.outbound.protection.outlook.com (HELO
 NAM03-CO1-obe.outbound.protection.outlook.com) ([104.47.40.57])
  by ob1.hgst.iphmx.com with ESMTP; 03 Oct 2019 13:06:30 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=K8HEn7mgBAoLM6o3LrLdPSm3hic0XqCLKc7y2wwiBSSjJJ7ROmTGx2ncrbQ1SkmhqoIgTQaaETpEo4jX1BH0ATN2th/z0NB4zkWYWldPak8hWM3vsTCLZm9Pb/ZR74ecVNUMyCMHjMgKoUVo93aWNl9qdX98nWMNO7chsZS6i6Libi78VLJ7ilngi6bu9jF0LFqDnNmzKUBBeH45VH2RUZO+wN7C/iA9AA2sjevzHOQs167AKGFgrRQSg883zNGei8OgpbKwiZRp07cCx5Sa2IVt8mYYKqThUlUw4WdDUTdniC/yC+29C2GHuEsCGYgdydwWKOADkUXcQz4GDyz4Tg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ooYuGa/Sijxs9VtSmp1l7kG4pwbuyGv+5FMmGy7ct+4=;
 b=WpoU0selQwM2ByYzOEqrJpOfSAetdPdV03CWT7auXudEeexAIW4jF1dKNBY5eCgez38fw2VSuyKYGToBrM+vqGF/kxEji4czwLJAGY16X+J9ECrBaZuE9Q1G6estKhEeofmRZY6PCfUM2Y8VLzcZ2Keq3ezlKc3DRBPLRaJI0YqVFgj8ZPQuhb/swTmWiqLqhxEI6in5M6xKoxIPkuAY0hoYpVXKADkLMREr213ZfynNYN08KFaOSzVJMF2g78NVL7GqlfBYjnYyxTzNQQ4qLANNumVm+hoDMSib5s9PIA5gP+Sn20Br4cnQlLFTotw8WFT7SEg/i4tTmvwmII/76A==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=ooYuGa/Sijxs9VtSmp1l7kG4pwbuyGv+5FMmGy7ct+4=;
 b=PTarw0x7u61/QYtDiHg++rfYAI6PCg0rWsDttzA7E3dI77Olqb+2g+myz8+qcrlfQNZVfzedEFtIeOqTgC2tp4y0CtoFI4G4NoiWHeeSnZHPniiSAbPWkW3JdcJkT1CwjYkfug1HQEm7N58LeUuob0l2WjHCjCtB1pqDeHDTc/Q=
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (20.178.246.15) by
 MN2PR04MB6991.namprd04.prod.outlook.com (10.186.144.209) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2305.18; Thu, 3 Oct 2019 05:06:29 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::1454:87a:13b0:d3a]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::1454:87a:13b0:d3a%7]) with mapi id 15.20.2305.023; Thu, 3 Oct 2019
 05:06:29 +0000
From: Anup Patel <Anup.Patel@wdc.com>
To: Palmer Dabbelt <palmer@sifive.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Radim K <rkrcmar@redhat.com>
CC: Daniel Lezcano <daniel.lezcano@linaro.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Alexander Graf <graf@amazon.com>,
        Atish Patra <Atish.Patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <Damien.LeMoal@wdc.com>,
        Christoph Hellwig <hch@infradead.org>,
        Anup Patel <anup@brainfault.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-riscv@lists.infradead.org" <linux-riscv@lists.infradead.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        Anup Patel <Anup.Patel@wdc.com>
Subject: [PATCH v8 00/19] KVM RISC-V Support
Thread-Topic: [PATCH v8 00/19] KVM RISC-V Support
Thread-Index: AQHVeahQgwihNAIJEEKPI5RCfSwzzA==
Date: Thu, 3 Oct 2019 05:06:29 +0000
Message-ID: <20191003050558.9031-1-anup.patel@wdc.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: BMXPR01CA0030.INDPRD01.PROD.OUTLOOK.COM
 (2603:1096:b00:c::16) To MN2PR04MB6061.namprd04.prod.outlook.com
 (2603:10b6:208:d8::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [111.235.74.37]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 225bdbcf-ebe5-4764-54bd-08d747bf730c
x-ms-office365-filtering-ht: Tenant
x-ms-traffictypediagnostic: MN2PR04MB6991:
x-ms-exchange-purlcount: 3
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MN2PR04MB6991B602B0D5F5EE0AFFB6FC8D9F0@MN2PR04MB6991.namprd04.prod.outlook.com>
wdcipoutbound: EOP-TRUE
x-ms-oob-tlc-oobclassifiers: OLM:277;
x-forefront-prvs: 01792087B6
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(366004)(346002)(39860400002)(136003)(376002)(396003)(189003)(199004)(7416002)(52116002)(25786009)(102836004)(54906003)(6506007)(1076003)(386003)(7736002)(44832011)(6436002)(486006)(66066001)(71190400001)(71200400001)(6116002)(3846002)(476003)(2616005)(26005)(305945005)(6512007)(36756003)(186003)(6306002)(14454004)(110136005)(5660300002)(6486002)(66446008)(66476007)(8936002)(966005)(66556008)(256004)(64756008)(14444005)(66946007)(86362001)(8676002)(81156014)(81166006)(99286004)(316002)(4326008)(2906002)(478600001)(50226002);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB6991;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 gR9ZDyA/0BYzGeddDD6gVBxFOmNKgNkuOPexW4H4MRGnyF5jgB+VqcSsCkldSsVJPkIcfVEaPuwTIk/UDollFAk/KAdY+VkwkyTXxWtmWU7MB/Kt1kXmklenNbbZoK+B2tNI8pc+WMNuitZURsA5rexHbr/IbysQvnDbr29CE2u6UM81bjT+e5EyuuEzv/Hm2UK5ot1nXoRivV1c0OuDhVzVoOVxvtuhxzZYNO4xVRG58ipuDqQ0UBpLjJ3BKgasgQ0uSL4t57rwPtm+JT4swDswZo0wsWwZ9JU3RGovYLDTJPKkmeARveOvZ9MJkNUyudfvFZ7Li4iF7PrhHdW1YhcYHSq+ZkJElgoY9vprRwTyV9dlcE92vSj48mHiKfKlcVZm0DU/Yunj1cdJrMrH37idvub0wK1NwHXnZFrGv/3Bck7e/3SyTm1fh9TcWH672c3coce56dshwOqhW9h8hw==
Content-Type: text/plain; charset="iso-8859-1"
MIME-Version: 1.0
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 225bdbcf-ebe5-4764-54bd-08d747bf730c
X-MS-Exchange-CrossTenant-originalarrivaltime: 03 Oct 2019 05:06:29.4166
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 Q+JLqBmwd1EpAM8r+6NbMAiGhUC2Neyen8V4KxwRmYHwAvRaW/QB3KPf7sInWsFgYzhvtWj8nvfVfj4KfUoxfg==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB6991
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This series adds initial KVM RISC-V support. Currently, we are able to boot
RISC-V 64bit Linux Guests with multiple VCPUs.

Few key aspects of KVM RISC-V added by this series are:
1. Minimal possible KVM world-switch which touches only GPRs and few CSRs.
2. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure.
3. KVM ONE_REG interface for VCPU register access from user-space.
4. PLIC emulation is done in user-space.
5. Timer and IPI emuation is done in-kernel.
6. MMU notifiers supported.
7. FP lazy save/restore supported.
8. SBI v0.1 emulation for KVM Guest available.
9. Forward unhandled SBI calls to KVM userspace.

Here's a brief TODO list which we will work upon after this series:
1. Implement recursive stage2 page table programing
2. SBI v0.2 emulation in-kernel
3. SBI v0.2 hart hotplug emulation in-kernel
4. In-kernel PLIC emulation
5. ..... and more .....

This series can be found in riscv_kvm_v8 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v1 branch at:
https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in riscv-hyp-work.next branch at:
https://github.com/alistair23/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU

Changes since v7:
- Rebased series on Linux-5.4-rc1 and Atish's SBI v0.2 patches
- Removed PATCH1, PATCH3, and PATCH20 because these already merged
- Use kernel doc style comments for ISA bitmap functions
- Don't parse X, Y, and Z extension in riscv_fill_hwcap() because it will
  be added in-future
- Mark KVM RISC-V kconfig option as EXPERIMENTAL
- Typo fix in commit description of PATCH6 of v7 series
- Use separate structs for CORE and CSR registers of ONE_REG interface
- Explicitly include asm/sbi.h in kvm/vcpu_sbi.c
- Removed implicit switch-case fall-through in kvm_riscv_vcpu_exit()
- No need to set VSSTATUS.MXR bit in kvm_riscv_vcpu_unpriv_read()
- Removed register for instruction length in kvm_riscv_vcpu_unpriv_read()
- Added defines for checking/decoding instruction length
- Added separate patch to forward unhandled SBI calls to userspace tool

Changes since v6:
- Rebased patches on Linux-5.3-rc7
- Added "return_handled" in struct kvm_mmio_decode to ensure that
  kvm_riscv_vcpu_mmio_return() updates SEPC only once
- Removed trap_stval parameter from kvm_riscv_vcpu_unpriv_read()
- Updated git repo URL in MAINTAINERS entry

Changes since v5:
- Renamed KVM_REG_RISCV_CONFIG_TIMEBASE register to
  KVM_REG_RISCV_CONFIG_TBFREQ register in ONE_REG interface
- Update SPEC in kvm_riscv_vcpu_mmio_return() for MMIO exits
- Use switch case instead of illegal instruction opcode table for simplicity
- Improve comments in stage2_remote_tlb_flush() for a potential remote TLB
  flush optimization
- Handle all unsupported SBI calls in default case of
  kvm_riscv_vcpu_sbi_ecall() function
- Fixed kvm_riscv_vcpu_sync_interrupts() for software interrupts
- Improved unprivilege reads to handle traps due to Guest stage1 page table
- Added separate patch to document RISC-V specific things in
  Documentation/virt/kvm/api.txt

Changes since v4:
- Rebased patches on Linux-5.3-rc5
- Added Paolo's Acked-by and Reviewed-by
- Updated mailing list in MAINTAINERS entry

Changes since v3:
- Moved patch for ISA bitmap from KVM prep series to this series
- Make vsip_shadow as run-time percpu variable instead of compile-time
- Flush Guest TLBs on all Host CPUs whenever we run-out of VMIDs

Changes since v2:
- Removed references of KVM_REQ_IRQ_PENDING from all patches
- Use kvm->srcu within in-kernel KVM run loop
- Added percpu vsip_shadow to track last value programmed in VSIP CSR
- Added comments about irqs_pending and irqs_pending_mask
- Used kvm_arch_vcpu_runnable() in-place-of kvm_riscv_vcpu_has_interrupt()
  in system_opcode_insn()
- Removed unwanted smp_wmb() in kvm_riscv_stage2_vmid_update()
- Use kvm_flush_remote_tlbs() in kvm_riscv_stage2_vmid_update()
- Use READ_ONCE() in kvm_riscv_stage2_update_hgatp() for vmid

Changes since v1:
- Fixed compile errors in building KVM RISC-V as module
- Removed unused kvm_riscv_halt_guest() and kvm_riscv_resume_guest()
- Set KVM_CAP_SYNC_MMU capability only after MMU notifiers are implemented
- Made vmid_version as unsigned long instead of atomic
- Renamed KVM_REQ_UPDATE_PGTBL to KVM_REQ_UPDATE_HGATP
- Renamed kvm_riscv_stage2_update_pgtbl() to kvm_riscv_stage2_update_hgatp()
- Configure HIDELEG and HEDELEG in kvm_arch_hardware_enable()
- Updated ONE_REG interface for CSR access to user-space
- Removed irqs_pending_lock and use atomic bitops instead
- Added separate patch for FP ONE_REG interface
- Added separate patch for updating MAINTAINERS file

Anup Patel (15):
  RISC-V: Add bitmap reprensenting ISA features common across CPUs
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: KVM: Forward unhandled SBI calls to userspace
  RISC-V: KVM: Document RISC-V specific parts of KVM API.
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.txt          |  158 +++-
 MAINTAINERS                             |   10 +
 arch/riscv/Kconfig                      |    2 +
 arch/riscv/Makefile                     |    2 +
 arch/riscv/include/asm/csr.h            |   58 ++
 arch/riscv/include/asm/hwcap.h          |   22 +
 arch/riscv/include/asm/kvm_host.h       |  263 ++++++
 arch/riscv/include/asm/kvm_vcpu_timer.h |   30 +
 arch/riscv/include/asm/pgtable-bits.h   |    1 +
 arch/riscv/include/uapi/asm/kvm.h       |  111 +++
 arch/riscv/kernel/asm-offsets.c         |  148 ++++
 arch/riscv/kernel/cpufeature.c          |   83 +-
 arch/riscv/kvm/Kconfig                  |   34 +
 arch/riscv/kvm/Makefile                 |   14 +
 arch/riscv/kvm/main.c                   |   92 +++
 arch/riscv/kvm/mmu.c                    |  911 ++++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |   43 +
 arch/riscv/kvm/vcpu.c                   | 1011 +++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              |  610 ++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               |  149 ++++
 arch/riscv/kvm/vcpu_switch.S            |  382 +++++++++
 arch/riscv/kvm/vcpu_timer.c             |  113 +++
 arch/riscv/kvm/vm.c                     |   86 ++
 arch/riscv/kvm/vmid.c                   |  123 +++
 drivers/clocksource/timer-riscv.c       |    8 +
 include/clocksource/timer-riscv.h       |   16 +
 include/uapi/linux/kvm.h                |    8 +
 27 files changed, 4478 insertions(+), 10 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
---
2.17.1
```
#### [kvm-unit-tests PATCH v2 0/3] arm64: Add code generation test
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
From patchwork Thu Oct  3 11:32:14 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11172541
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1BCD376
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 11:32:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 03D222086A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 11:32:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730124AbfJCLcf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 07:32:35 -0400
Received: from foss.arm.com ([217.140.110.172]:42360 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729942AbfJCLce (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 07:32:34 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 73465337;
        Thu,  3 Oct 2019 04:32:34 -0700 (PDT)
Received: from e123195-lin.cambridge.arm.com (e123195-lin.cambridge.arm.com
 [10.1.196.63])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 65BED3F706;
        Thu,  3 Oct 2019 04:32:33 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, kvmarm@lists.cs.columbia.edu
Cc: drjones@redhat.com, pbonzini@redhat.com, maz@kernel.org,
        mark.rutland@arm.com, andre.przywara@arm.com
Subject: [kvm-unit-tests PATCH v2 0/3] arm64: Add code generation test
Date: Thu,  3 Oct 2019 12:32:14 +0100
Message-Id: <20191003113217.25464-1-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add a test to check if KVM honors the CTR_EL0.{IDC, DIC} bits that it
advertises to the guests. Full details are in patch #3.

Changes in v2:
* Gathered Reviewed-by tags.
* Fixed typo s/group/groups in #3.

Alexandru Elisei (3):
  lib: arm64: Add missing ISB in flush_tlb_page
  lib: arm/arm64: Add function to clear the PTE_USER bit
  arm64: Add cache code generation test

 arm/Makefile.arm64    |   1 +
 lib/arm/asm/mmu-api.h |   1 +
 lib/arm64/asm/mmu.h   |   1 +
 lib/arm/mmu.c         |  15 ++++++
 arm/cache.c           | 122 ++++++++++++++++++++++++++++++++++++++++++
 arm/unittests.cfg     |   6 +++
 6 files changed, 146 insertions(+)
 create mode 100644 arm/cache.c
```
#### [PATCH 0/5] SEV fixes and performance enhancements
##### From: "Lendacky, Thomas" <Thomas.Lendacky@amd.com>
From: Tom Lendacky <thomas.lendacky@amd.com>

```c
From patchwork Thu Oct  3 21:17:42 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Lendacky, Thomas" <thomas.lendacky@amd.com>
X-Patchwork-Id: 11173397
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F276917EE
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 21:18:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CFF0E21A4C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 21:18:11 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="Vta+9zqS"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731371AbfJCVRp (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 17:17:45 -0400
Received: from mail-eopbgr730044.outbound.protection.outlook.com
 ([40.107.73.44]:46240
        "EHLO NAM05-DM3-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1727789AbfJCVRo (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 17:17:44 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Xh1GUcGH7wot7Gn8TYnIg3uToFIZOrvndTaYyZtNb1qjTmgn4MpbGJbMbqWBfBMgkmrysjmzfqERl52KSGNldjW57+WxccIcktbDeS8F7nTj0HwOlckCFkGpPnWiCJNaOtlBOdOs3VP4oEETDHbtvNdQ1XY62Fj/mGlsA7t+zRPglESPiMi0Q9Xbv8S6cEskpiNXXvNUOw8RDd2PJcq93jvCdBSopPlKeSBRB/+k/8wdaKDvBy7h3irh9aq5sV4Me6umKRyE+3c3ByZqKrZCxRhy8sFXnr+euxa/C0iPkabblK7bU+lj/auF0cjGfUEhmfJGWguXXyneqGcc8q7Acw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=XykmkkuZiFPc1sAZo3nrIR4fnLv6b1zXkHkJqbpZlZ8=;
 b=dbsnN2Yp7XYb9BZME+aqNIEhdfCMzt5mntZ8rVxSoVWaijUryEbmH1uvFUwLgigsQOP8XN+kiByJVw45tF3JRQaJHvSLCXKTCESfxl0uby795WaDhKa4ZT4gM4h4Jh6/fSOZCetq8Dy1IcTzaR5sUavBb42zm+utlePS1kb3C9oPHDFYZ5I18dav0rbAWgl45UazEkYvPGqi60/Qe79x9tto1ufpJHsLUTU6xbTBiei3VFf3lipKtJIn2EHcoMZtX9ahLp5O4KWzC7YqieVgt4Ke+S4i7KXx6uia0atLyItb2rnAPlVB7WMD1VfgktrFpNNNQBJwmLJGxqYxqG3zUA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=XykmkkuZiFPc1sAZo3nrIR4fnLv6b1zXkHkJqbpZlZ8=;
 b=Vta+9zqSCbM46rP75lk58TdSLXwr32HBcWB4bTG8AlhItj5b9OTfcvGIVBy/Gx/HgaCamR4bphmCH7zpLeMK6YvY4k3LVi3ucbr4ZqK6qIReQb6ywQMYs134YXOXNicnV4nIdpwzacH7y7FiGK4a+69TVFwuOR4zU8I+gNBq4H0=
Received: from DM6PR12MB3163.namprd12.prod.outlook.com (20.179.104.150) by
 DM6PR12MB3211.namprd12.prod.outlook.com (20.179.105.75) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2305.20; Thu, 3 Oct 2019 21:17:42 +0000
Received: from DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::85b7:7456:1a67:78aa]) by DM6PR12MB3163.namprd12.prod.outlook.com
 ([fe80::85b7:7456:1a67:78aa%7]) with mapi id 15.20.2305.023; Thu, 3 Oct 2019
 21:17:42 +0000
From: "Lendacky, Thomas" <Thomas.Lendacky@amd.com>
To: "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>
CC: Paolo Bonzini <pbonzini@redhat.com>,
 =?iso-8859-2?q?Radim_Kr=E8m=E1=F8?= <rkrcmar@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>, "Singh,
 Brijesh" <brijesh.singh@amd.com>, David Rientjes <rientjes@google.com>
Subject: [PATCH 0/5] SEV fixes and performance enhancements
Thread-Topic: [PATCH 0/5] SEV fixes and performance enhancements
Thread-Index: AQHVei/+m230dNdjaEiFD9na+UoMxQ==
Date: Thu, 3 Oct 2019 21:17:42 +0000
Message-ID: <cover.1570137447.git.thomas.lendacky@amd.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-mailer: git-send-email 2.17.1
x-clientproxiedby: SN6PR05CA0006.namprd05.prod.outlook.com
 (2603:10b6:805:de::19) To DM6PR12MB3163.namprd12.prod.outlook.com
 (2603:10b6:5:182::22)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Thomas.Lendacky@amd.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-originating-ip: [165.204.78.1]
x-ms-publictraffictype: Email
x-ms-office365-filtering-correlation-id: 107dc618-4be3-43c6-8d74-08d74847206b
x-ms-office365-filtering-ht: Tenant
x-ms-traffictypediagnostic: DM6PR12MB3211:
x-ms-exchange-purlcount: 1
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <DM6PR12MB32119FD1CFE01D20404D6F98EC9F0@DM6PR12MB3211.namprd12.prod.outlook.com>
x-ms-oob-tlc-oobclassifiers: OLM:873;
x-forefront-prvs: 01792087B6
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10009020)(4636009)(39860400002)(396003)(376002)(346002)(366004)(136003)(199004)(189003)(256004)(26005)(14444005)(386003)(6506007)(316002)(4744005)(36756003)(66446008)(71200400001)(71190400001)(5660300002)(66476007)(66556008)(64756008)(66946007)(66066001)(8936002)(2501003)(50226002)(7416002)(6512007)(6306002)(102836004)(81156014)(8676002)(2906002)(14454004)(81166006)(7736002)(4326008)(6436002)(305945005)(478600001)(966005)(25786009)(86362001)(476003)(2616005)(186003)(6486002)(54906003)(99286004)(110136005)(486006)(52116002)(3846002)(6116002);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6PR12MB3211;H:DM6PR12MB3163.namprd12.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
received-spf: None (protection.outlook.com: amd.com does not designate
 permitted sender hosts)
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 7b2d93MzHyd29yRYfEtOAYt75dsFDFkF5hIk8qztgLHhaezbE34NsYrT59DJwkWQhDhOOjLJbCMrnMi7waTm1E2Ed+j1iLyx/6O4CmVNvvroFGzYLxh+0qWQBJl6jPDQXl9uRXJPbWsUPp0JIFfT2+2el5iBq6fUgNIYbugPOeXry1uIK99GLRoptPnf9qHLGG3KhOAFMvaSyLN2lZOhBwPWxjZYScy24tImQYbAPTl0UKabo0zoNrzRy82CHrX1dt/HCW0HbMQQt4KcScJ1RsFUGSYlg7lzT3c7doWghu3oByhsjgcMLVZBX47BBCHx2jqYB5iO34kqby8281USTupdmtROPqTnSNT+UA7/JG93q66fQn/d/wfXHLk0CXI5z4NIPY9UbSIzzSRpw6B72S0qXlGWgYEwZt7oo7JPmB3HTuH5uimTGn7JyZi6Xt+B86BaXztFUdkLp5RtlGXQ4w==
Content-Type: text/plain; charset="iso-8859-2"
Content-ID: <815C7A99E43A514B91700271E42C6B99@namprd12.prod.outlook.com>
MIME-Version: 1.0
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 107dc618-4be3-43c6-8d74-08d74847206b
X-MS-Exchange-CrossTenant-originalarrivaltime: 03 Oct 2019 21:17:42.2230
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 wFxgXjsrqNtwe8CFWbCg9p3nuZVohk/ZIvb5UHwOdgcysUArcKYjJwIrVqU7O0cfjNOMuM9Mtb8ZpDvWVQHUPQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB3211
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

This patch series provides fixes in the area of ASID assignment and VM
deactivation.

Additionally, it provides some performance enhancements by reducing the
number of WBINVD/DF_FLUSH invocations that are made.

Note: The third patch in the series modifies a file that is outside of
      the arch/x86/kvm directory.
---

Patches based on https://git.kernel.org/pub/scm/virt/kvm/kvm.git next
and commit:
  fd3edd4a9066 ("KVM: nVMX: cleanup and fix host 64-bit mode checks")

Tom Lendacky (5):
  KVM: SVM: Serialize access to the SEV ASID bitmap
  KVM: SVM: Guard against DEACTIVATE when performing WBINVD/DF_FLUSH
  KVM: SVM: Remove unneeded WBINVD and DF_FLUSH when starting SEV guests
  KVM: SVM: Convert DEACTIVATE mutex to read/write semaphore
  KVM: SVM: Reduce WBINVD/DF_FLUSH invocations

 arch/x86/kvm/svm.c           | 105 +++++++++++++++++++++++++++--------
 drivers/crypto/ccp/psp-dev.c |   9 +++
 2 files changed, 92 insertions(+), 22 deletions(-)
```
#### [RFC PATCH 00/13] XOM for KVM guest userspace
##### From: Rick Edgecombe <rick.p.edgecombe@intel.com>

```c
From patchwork Thu Oct  3 21:23:47 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Rick Edgecombe <rick.p.edgecombe@intel.com>
X-Patchwork-Id: 11173455
Return-Path: <SRS0=nqo7=X4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F259B76
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 21:40:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D1F002133F
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  3 Oct 2019 21:40:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389351AbfJCVkL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 3 Oct 2019 17:40:11 -0400
Received: from mga09.intel.com ([134.134.136.24]:52651 "EHLO mga09.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1731058AbfJCVi6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 3 Oct 2019 17:38:58 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga008.jf.intel.com ([10.7.209.65])
  by orsmga102.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 03 Oct 2019 14:38:57 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.67,253,1566889200";
   d="scan'208";a="186051612"
Received: from linksys13920.jf.intel.com (HELO rpedgeco-DESK5.jf.intel.com)
 ([10.54.75.11])
  by orsmga008.jf.intel.com with ESMTP; 03 Oct 2019 14:38:57 -0700
From: Rick Edgecombe <rick.p.edgecombe@intel.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org,
        linux-mm@kvack.org, luto@kernel.org, peterz@infradead.org,
        dave.hansen@intel.com, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, keescook@chromium.org
Cc: kristen@linux.intel.com, deneen.t.dock@intel.com,
        Rick Edgecombe <rick.p.edgecombe@intel.com>
Subject: [RFC PATCH 00/13] XOM for KVM guest userspace
Date: Thu,  3 Oct 2019 14:23:47 -0700
Message-Id: <20191003212400.31130-1-rick.p.edgecombe@intel.com>
X-Mailer: git-send-email 2.17.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patchset enables the ability for KVM guests to create execute-only (XO)
memory by utilizing EPT based XO permissions. XO memory is currently supported
on Intel hardware natively for CPU's with PKU, but this enables it on older
platforms, and can support XO for kernel memory as well.

In the guest, this patchset enables XO memory for userspace, using the existing
interface (mprotect PROT_EXEC && !PROT_READ) used for arm64 and x86 PKU HW. A
larger follow on to this enables setting the kernel text as XO, but this is just
the KVM pieces and guest userspace. The yet un-posted QEMU patches to work with
these changes are here:
https://github.com/redgecombe/qemu/

Guest Interface
===============
The way XO is exposed to the guest is by creating a virtual XO permission bit in
the guest page tables.

There are normally four kinds of page table bits:
1. Bits ignored by the hardware
2. Bits that must be 0 or else the hardware throws a RSVD page fault
3. Bits used by the hardware for addresses
4. Bits used by the hardware for permissions and other features

We want to find a bit in the guest page tables to use to mean execute-only
memory so that guest can map the same physical memory with different permissions
simultaneously like other permission bits. We also want the translations to be
done by the hardware, which means we can't use ignored or reserved bits. We also
can't easily re-purpose a feature bit. This leaves address bits. The idea here
is we will take an address bit and re-purpose it as a feature bit.

The first thing we have to do is tell the guest that it can't use the address
bit we are stealing. Luckily there is an existing CPUID leaf that conveys the
number of physical address bits which is already intercepted by KVM, and so we
can reduce it as needed. This puts what was previously the top physical address
bit into what is defined as the "reserved area" of the PTE.

Here is how the PTE would be transformed, where M is the number of physical bits
exposed by the CPUID leaf.

Normal:
|--------------------------------------------------------|
| .. |     RSVD (51 to M)     |   PFN (M-1 to 12)   | .. |
|--------------------------------------------------------|

KVM XO (with M reduced by 1):
|--------------------------------------------------------|
| .. |  RSVD (51 to M+1) | XO |   PFN (M-1 to 12)   | .. |
|--------------------------------------------------------|

So the way XOM is exposed to the guest is by having the VMM provide two aliases
in the guest physical address space for the same memory. The first half has
normal EPT permissions, and the second half has XO permissions. This way the
high PFN bit in the guest page tables acts like an XO permission bit. The VMM
reports to the guest a number of physical address bits that exclude the XO bit,
so from the guest perspective the XO bit is in the region that would be
"reserved", and from the CPU's perspective the bit is still a normal PFN bit.

Backwards Compatibility
-----------------------
Since software would have previously received a #PF with the RSVD error code
set, when the HW encountered any set bits in the region 51 to M, there was some
internal discussion on whether this should have a virtual MSR for the OS to turn
it on only if the OS knows it isn't relying on this behavior for bit M. The
argument against needing an MSR is this blurb from the Intel SDM about reserved
bits:
"Bits reserved in the paging-structure entries are reserved for future
functionality. Software developers should be aware that such bits may be used in
the future and that a paging-structure entry that causes a page-fault exception
on one processor might not do so in the future."

So in the current patchset there is no MSR write required for the guest to turn
on this feature. It will have this behavior whenever qemu is run with
"-cpu +xo".

KVM XO CPUID Feature Bit
------------------------
Althrough this patchset targets KVM, the idea is that this interface might be
implemented by other hypervisors. Especially since as it appears especially like
a normal CPU feature it would be nice if there was a single CPUID bit to check
for different implementations like there often is for real CPU features. In the
past there was a proposal for "generic leaves" [1], where regions are assigned
for VMMs to define, but where the behavior will not change across VMMs. This
patchset follows this proposal and defines a bit in a new leaf to expose the
presense of the above described behavior. I'm hoping to get some suggestions on
the right way to expose it by this RFC.

Injecting Page Faults
---------------------
When there is an attempt to read memory from an XO address range, a #PF is
injected into the guest with P=1, W/R=0, RSVD=0, I/D=0. When there is an attempt
to write, it is P=1, W/R=1, RSVD=0, I/D=0.

Implementation
==============
In KVM this patchset adds a new memslot, KVM_MEM_EXECONLY, which maps memory as
execute-only via EPT permissions, and will inject a PF to the guest if there is
a violation. The x86 emulator is also made aware of XO memory perissions, and
virtualized features that act on PFN's are made aware that VTs view of the GFN
includes the permission bit (and so needs to be masked to get the guests view of
the PFN).

QEMU manipulates the physical address bits exposed to the guest and adds an
extra KVM_MEM_EXECONLY memslot that points to the same userspace memory in the
XO range for every memslot added in the normal range.

The violating linear address is determined from the EPT feature that provides
the linear address of the violation if availible, and if not availible emulates
the violating instruction to determine which linear address to use in the
injected fault.

Performance
===========
The performance impact is not fully characterized yet. In the larger patchset
that sets kernel text to be XO, there wasn't any measurable impact compiling
the kernel. The hope is that there will not be a large impact, but more testing
is needed.

Status
======
Regression testing is still needed including the nested virtualization case and
impact of XO in the other memslot address spaces. This is based on 5.3.

[1] https://lwn.net/Articles/301888/


Rick Edgecombe (13):
  kvm: Enable MTRR to work with GFNs with perm bits
  kvm: Add support for X86_FEATURE_KVM_XO
  kvm: Add XO memslot type
  kvm, vmx: Add support for gva exit qualification
  kvm: Add #PF injection for KVM XO
  kvm: Add KVM_CAP_EXECONLY_MEM
  kvm: Add docs for KVM_CAP_EXECONLY_MEM
  x86/boot: Rename USE_EARLY_PGTABLE_L5
  x86/cpufeature: Add detection of KVM XO
  x86/mm: Add NR page bit for KVM XO
  x86, ptdump: Add NR bit to page table dump
  mmap: Add XO support for KVM XO
  x86/Kconfig: Add Kconfig for KVM based XO

 Documentation/virt/kvm/api.txt                | 16 ++--
 arch/x86/Kconfig                              | 13 +++
 arch/x86/boot/compressed/misc.h               |  2 +-
 arch/x86/include/asm/cpufeature.h             |  7 +-
 arch/x86/include/asm/cpufeatures.h            |  5 +-
 arch/x86/include/asm/disabled-features.h      |  3 +-
 arch/x86/include/asm/kvm_host.h               |  7 ++
 arch/x86/include/asm/pgtable_32_types.h       |  1 +
 arch/x86/include/asm/pgtable_64_types.h       | 30 ++++++-
 arch/x86/include/asm/pgtable_types.h          | 13 +++
 arch/x86/include/asm/required-features.h      |  3 +-
 arch/x86/include/asm/sparsemem.h              |  4 +-
 arch/x86/include/asm/vmx.h                    |  1 +
 arch/x86/include/uapi/asm/kvm_para.h          |  3 +
 arch/x86/kernel/cpu/common.c                  |  7 +-
 arch/x86/kernel/head64.c                      | 43 +++++++++-
 arch/x86/kvm/cpuid.c                          |  7 ++
 arch/x86/kvm/cpuid.h                          |  1 +
 arch/x86/kvm/mmu.c                            | 79 +++++++++++++++++--
 arch/x86/kvm/mtrr.c                           |  8 ++
 arch/x86/kvm/paging_tmpl.h                    | 29 +++++--
 arch/x86/kvm/svm.c                            |  6 ++
 arch/x86/kvm/vmx/vmx.c                        |  6 ++
 arch/x86/kvm/x86.c                            |  9 ++-
 arch/x86/mm/dump_pagetables.c                 |  6 +-
 arch/x86/mm/init.c                            |  3 +
 arch/x86/mm/kasan_init_64.c                   |  2 +-
 include/uapi/linux/kvm.h                      |  2 +
 mm/mmap.c                                     | 30 +++++--
 .../arch/x86/include/asm/disabled-features.h  |  3 +-
 tools/include/uapi/linux/kvm.h                |  1 +
 virt/kvm/kvm_main.c                           | 15 +++-
 32 files changed, 322 insertions(+), 43 deletions(-)
```
