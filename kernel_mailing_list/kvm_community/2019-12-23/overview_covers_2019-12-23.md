

#### [PATCH v10 00/19] KVM RISC-V Support
##### From: Anup Patel <Anup.Patel@wdc.com>

```c
From patchwork Mon Dec 23 11:35:10 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Anup Patel <Anup.Patel@wdc.com>
X-Patchwork-Id: 11308121
Return-Path: <SRS0=vuOz=2N=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 702D9109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Dec 2019 11:35:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2F6602075B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Dec 2019 11:35:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=wdc.com header.i=@wdc.com header.b="UV7fc5pH";
	dkim=pass (1024-bit key) header.d=sharedspace.onmicrosoft.com
 header.i=@sharedspace.onmicrosoft.com header.b="h+X0DJcA"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726805AbfLWLfV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Dec 2019 06:35:21 -0500
Received: from esa4.hgst.iphmx.com ([216.71.154.42]:54845 "EHLO
        esa4.hgst.iphmx.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726257AbfLWLfU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Dec 2019 06:35:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=simple/simple;
  d=wdc.com; i=@wdc.com; q=dns/txt; s=dkim.wdc.com;
  t=1577100920; x=1608636920;
  h=from:to:cc:subject:date:message-id:
   content-transfer-encoding:mime-version;
  bh=yeSaGfLMF5FXGAxTwBHOx/9uAdE9VhgbQj5S4/15hG4=;
  b=UV7fc5pHDTGBELQr3gFgIsGmkh+eTEHQ5QdMtyAG8DgGBsLpBsvyrVwj
   bC16sijSgGQ4ojK97sZJb7ySnFfOpTplTgJFXXuEqk4F9333WqcVBlMW3
   c+7Lm2FjfJ91NtB+lwgiUQbcOAHGvtDym01QNfK//KQsa3O4WMlAM5nha
   5Dr5RSy/AwADY0WIaYTHfrsF9EHqe0e7EqXk7zr9sJxmiK9lidFEyd1DQ
   8Gg32Y7XxinN7xDBPoIwevkh/b6f0OZeTYxUgowqI9Uv9vHsvRx01jr7r
   X+FOlh4AS4i6QbGfc6J08k8uHOO8u2Ih/sCeIYlembzGgRy6IduuM8oaQ
   A==;
IronPort-SDR: 
 kN7wKhJO/Gphp06rSJqOATc6RVXzKRqLXFGmP/fhggDgnKj6hYoMETBxgAndpxX7tZuxUz+954
 lHBl9ufMKRUsN5pH3AUXx3yCvbWq3tZTrdqgAs9jSgnYi6Go3iYfb8WkPJ+LVVyi0rhOI52aGy
 +tyEoI4hjnqS+/awd6U6pZ3dTnd5/oV4Ng7oudnJ+z4HUPjgZdp4BjWSbWaDXT/1KwYzLmCz6y
 M4t+lMFDF3JxUaLtdXW/zVDe8iNmcnz7FSsMxopVJl/RMIaf+kMqHpeAHN85yzzvOq1F+xS5JB
 Ed8=
X-IronPort-AV: E=Sophos;i="5.69,347,1571673600";
   d="scan'208";a="125956066"
Received: from mail-bn7nam10lp2102.outbound.protection.outlook.com (HELO
 NAM10-BN7-obe.outbound.protection.outlook.com) ([104.47.70.102])
  by ob1.hgst.iphmx.com with ESMTP; 23 Dec 2019 19:35:11 +0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=Wpr92VCpISIkwo3C/o9Mj7oQaByATD7/HeWbiUjb1xXOr3ehm6Ec1pGVextbdSFbML5Ie9NrAtOSWeYjq21AovLwagNXBlI+6TK1O1+lco5DAZ/k9dSXY5dfpxELxm4cyMVjWh4cAHIJab31rDrAO5e9UXSgfls8glUFUESKUhx1gHTASzR1S7kWJnNXOO9XygrWTURf+IUTqfBPMD6/xfwiPb81WRq8yrlRlJjBLSgdY7fcHhyw73WR126V6vt3qXdXv0zXe6jAlm3NiI7TRBVnzwuc0qiqu99weHaEzzR3MHT18/r6dvahkU5V3s8dQYrOTY1FinntZiSgQY3sRw==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=PFR2e+HEgBgux6CBn8kMhzlUmyIw9t4ez5ZhbqwkuMo=;
 b=MmChiVWyGF4rw/BCwIpc16eI9v1BJIVW+iW2WqHIwjhbNVi1XswcLQeqZ+xJh8kOynfb+Or1ki+tfd77IOlqtPHwpaQgTW/+XF0h57E4oyrPbICyLm8+kP6N6psRwojKuKXRzePLZE6sCkNniQZ/9n6FJEndUL4G/knWzdM9TOLaSjK3FGUnv30FVJW0q/bJLg3w9RJF0EZfoiwW2Z2U+uyTEQF2euq8ohU3MoIK+65FLnMqjyZ9OqicOxOOZYkn7F4QuGYx381+Ucha2gtJeeZMpa0O9/6+02/Sl8aMFuepbpnqQhgIeVTefcJjCIshI1swonLU4rXEYDPPTVg9lg==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=wdc.com; dmarc=pass action=none header.from=wdc.com; dkim=pass
 header.d=wdc.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=sharedspace.onmicrosoft.com; s=selector2-sharedspace-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=PFR2e+HEgBgux6CBn8kMhzlUmyIw9t4ez5ZhbqwkuMo=;
 b=h+X0DJcAXtBNRadgxcusuDUHEUyHlS2OBDAKZIXlllMIgqdn524MGRzH/eohnGKfq54KwL6RbvxM61F736AMDBt7xwwkkfrJhn6tZ36o9o4pdYHOIj+ocwf3DcUp3LE+0Fw3WSh0Ns2C0la02TrFd2c6xH6u9CK0IV/DqMUslX8=
Received: from MN2PR04MB6061.namprd04.prod.outlook.com (20.178.246.15) by
 MN2PR04MB7072.namprd04.prod.outlook.com (10.186.146.20) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2559.15; Mon, 23 Dec 2019 11:35:11 +0000
Received: from MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::a9a0:3ffa:371f:ad89]) by MN2PR04MB6061.namprd04.prod.outlook.com
 ([fe80::a9a0:3ffa:371f:ad89%7]) with mapi id 15.20.2559.017; Mon, 23 Dec 2019
 11:35:11 +0000
Received: from wdc.com (106.51.20.238) by
 MA1PR01CA0077.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00::17) with Microsoft
 SMTP Server (version=TLS1_2, cipher=) via Frontend Transport;
 Mon, 23 Dec 2019 11:35:05 +0000
From: Anup Patel <Anup.Patel@wdc.com>
To: Palmer Dabbelt <palmer@dabbelt.com>,
        Paul Walmsley <paul.walmsley@sifive.com>,
        Albert Ou <aou@eecs.berkeley.edu>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Radim K <rkrcmar@redhat.com>
CC: Alexander Graf <graf@amazon.com>,
        Atish Patra <Atish.Patra@wdc.com>,
        Alistair Francis <Alistair.Francis@wdc.com>,
        Damien Le Moal <Damien.LeMoal@wdc.com>,
        Christoph Hellwig <hch@lst.de>,
        Anup Patel <anup@brainfault.org>,
        "kvm@vger.kernel.org" <kvm@vger.kernel.org>,
        "kvm-riscv@lists.infradead.org" <kvm-riscv@lists.infradead.org>,
        "linux-riscv@lists.infradead.org" <linux-riscv@lists.infradead.org>,
        "linux-kernel@vger.kernel.org" <linux-kernel@vger.kernel.org>,
        Anup Patel <Anup.Patel@wdc.com>
Subject: [PATCH v10 00/19] KVM RISC-V Support
Thread-Topic: [PATCH v10 00/19] KVM RISC-V Support
Thread-Index: AQHVuYUI1J4Xji1dIUi4uEOCYb8klQ==
Date: Mon, 23 Dec 2019 11:35:10 +0000
Message-ID: <20191223113443.68969-1-anup.patel@wdc.com>
Accept-Language: en-US
Content-Language: en-US
X-MS-Has-Attach: 
X-MS-TNEF-Correlator: 
x-clientproxiedby: MA1PR01CA0077.INDPRD01.PROD.OUTLOOK.COM (2603:1096:a00::17)
 To MN2PR04MB6061.namprd04.prod.outlook.com (2603:10b6:208:d8::15)
authentication-results: spf=none (sender IP is )
 smtp.mailfrom=Anup.Patel@wdc.com;
x-ms-exchange-messagesentrepresentingtype: 1
x-mailer: git-send-email 2.17.1
x-originating-ip: [106.51.20.238]
x-ms-publictraffictype: Email
x-ms-office365-filtering-ht: Tenant
x-ms-office365-filtering-correlation-id: ab1da0d7-16a6-4008-2166-08d7879c2b35
x-ms-traffictypediagnostic: MN2PR04MB7072:
x-ms-exchange-transport-forked: True
x-microsoft-antispam-prvs: 
 <MN2PR04MB70727F31AC7BF641DA3119608D2E0@MN2PR04MB7072.namprd04.prod.outlook.com>
wdcipoutbound: EOP-TRUE
x-ms-oob-tlc-oobclassifiers: OLM:277;
x-forefront-prvs: 0260457E99
x-forefront-antispam-report: 
 SFV:NSPM;SFS:(10019020)(4636009)(136003)(366004)(376002)(396003)(346002)(39860400002)(199004)(189003)(8886007)(478600001)(52116002)(316002)(16526019)(2906002)(8936002)(1076003)(7696005)(36756003)(66946007)(66476007)(86362001)(66446008)(26005)(64756008)(66556008)(4326008)(966005)(5660300002)(8676002)(186003)(7416002)(81156014)(2616005)(956004)(71200400001)(55016002)(44832011)(55236004)(81166006)(1006002)(54906003)(110136005)(6666004)(32040200004);DIR:OUT;SFP:1102;SCL:1;SRVR:MN2PR04MB7072;H:MN2PR04MB6061.namprd04.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;A:1;MX:1;
x-ms-exchange-senderadcheck: 1
x-microsoft-antispam: BCL:0;
x-microsoft-antispam-message-info: 
 RRb8jhm24zD73g3a3Km7EvOk2uNRzMTCIkSpyglgZygpD7oiGQa/4KnHnF+aHEgP0CSaLGjW38ueUeu8Tg5szXqqmFqbpdUbPEl2T97ZUmJhBx4Al5Ik2ItQPBX6pmwR7dnirIZHNJnNkuhNPVrWmouRZPmSIMt4TOQcJ7yJeA26KxiJ/1M6bWqCJ4KnIuj8Qli2ddgcGBkaajPAy0aMQoLjkE4qLmfmQyALE4ZDPpV1V9VN6qM0WgM3zzL32+yLM6uo/x4vUPepneg+KForNXemi/zmzjjOt9/IqsBKJvQja3kVwCppOxY0L1/sJwgcU3lwOB1KfDVp8O8bKfEqCsqnLw4nxehtTLANWnJG06qojP6Cvq9AJ5wsK6z0oMm2+O1T5SOPv18KvwOSlr8yB7/2hrM21M1Uec5IVIW3oupfaKPMZ7NKrY+DHXrWFtVaU8R98xHCXXsEWGQqNJku7CesxALjt0A8wtdoxEHdNGiNRSKdrJ2YrEZaPCZaWfdP+gh9eKs6rRBIeD+M/dXY67BqOCLz2GwkhA4AKPUAvbs=
MIME-Version: 1.0
X-OriginatorOrg: wdc.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 ab1da0d7-16a6-4008-2166-08d7879c2b35
X-MS-Exchange-CrossTenant-originalarrivaltime: 23 Dec 2019 11:35:10.8653
 (UTC)
X-MS-Exchange-CrossTenant-fromentityheader: Hosted
X-MS-Exchange-CrossTenant-id: b61c8803-16f3-4c35-9b17-6f65f441df86
X-MS-Exchange-CrossTenant-mailboxtype: HOSTED
X-MS-Exchange-CrossTenant-userprincipalname: 
 rnAk0P2AHJViUIha5aJ8F8l0nsXBRT8cvH/7Gf4+ubx27K795ab+3y9xoSR20nrfDgpo8Iouue29maaPpOWKJA==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: MN2PR04MB7072
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
10. Hugepage support for Guest/VM

Here's a brief TODO list which we will work upon after this series:
1. SBI v0.2 emulation in-kernel
2. SBI v0.2 hart state management emulation in-kernel
3. In-kernel PLIC emulation
4. ..... and more .....

This series can be found in riscv_kvm_v10 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v1 branch
at: https//github.com/avpatel/kvmtool.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in mainline/alistair/riscv-hyp-ext-v0.5.1 branch at:
https://github.com/kvm-riscv/qemu.git

To play around with KVM RISC-V, refer KVM RISC-V wiki at:
https://github.com/kvm-riscv/howto/wiki
https://github.com/kvm-riscv/howto/wiki/KVM-RISCV64-on-QEMU

Changes since v9:
 - Squash PATCH19 and PATCH20 into PATCH5
 - Squash PATCH18 into PATCH11
 - Squash PATCH17 into PATCH16
 - Added ONE_REG interface for VCPU timer in PATCH13
 - Use HTIMEDELTA for VCPU timer in PATCH13
 - Updated KVM RISC-V mailing list in MAINTAINERS entry
 - Update KVM kconfig option to depend on RISCV_SBI and MMU
 - Check for SBI v0.2 and SBI v0.2 RFENCE extension at boot-time
 - Use SBI v0.2 RFENCE extension in VMID implementation
 - Use SBI v0.2 RFENCE extension in Stage2 MMU implementation
 - Use SBI v0.2 RFENCE extension in SBI implementation
 - Moved to RISC-V Hypervisor v0.5 draft spec
 - Updated Documentation/virt/kvm/api.txt for timer ONE_REG interface
 - Rebased patches on Linux-5.5-rc3

Changes since v8:
 - Rebased series on Linux-5.4-rc3 and Atish's SBI v0.2 patches
 - Use HRTIMER_MODE_REL instead of HRTIMER_MODE_ABS in timer emulation
 - Fixed kvm_riscv_stage2_map() to handle hugepages
 - Added patch to forward unhandled SBI calls to user-space
 - Added patch for iterative/recursive stage2 page table programming
 - Added patch to remove per-CPU vsip_shadow variable
 - Added patch to fix race-condition in kvm_riscv_vcpu_sync_interrupts()

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
  RISC-V: Export riscv_cpuid_to_hartid_mask() API
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
  RISC-V: KVM: Document RISC-V specific parts of KVM API.
  RISC-V: KVM: Add MAINTAINERS entry

Atish Patra (4):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Implement ONE REG interface for FP registers
  RISC-V: KVM: Add SBI v0.1 support

 Documentation/virt/kvm/api.txt          |  169 +++-
 MAINTAINERS                             |   11 +
 arch/riscv/Kconfig                      |    2 +
 arch/riscv/Makefile                     |    2 +
 arch/riscv/include/asm/csr.h            |   78 +-
 arch/riscv/include/asm/hwcap.h          |   22 +
 arch/riscv/include/asm/kvm_host.h       |  264 ++++++
 arch/riscv/include/asm/kvm_vcpu_timer.h |   44 +
 arch/riscv/include/asm/pgtable-bits.h   |    1 +
 arch/riscv/include/uapi/asm/kvm.h       |  127 +++
 arch/riscv/kernel/asm-offsets.c         |  148 ++++
 arch/riscv/kernel/cpufeature.c          |   83 +-
 arch/riscv/kernel/smp.c                 |    2 +
 arch/riscv/kvm/Kconfig                  |   34 +
 arch/riscv/kvm/Makefile                 |   14 +
 arch/riscv/kvm/main.c                   |   97 +++
 arch/riscv/kvm/mmu.c                    |  762 +++++++++++++++++
 arch/riscv/kvm/tlb.S                    |   43 +
 arch/riscv/kvm/vcpu.c                   | 1013 +++++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              |  639 ++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               |  171 ++++
 arch/riscv/kvm/vcpu_switch.S            |  382 +++++++++
 arch/riscv/kvm/vcpu_timer.c             |  225 +++++
 arch/riscv/kvm/vm.c                     |   86 ++
 arch/riscv/kvm/vmid.c                   |  120 +++
 drivers/clocksource/timer-riscv.c       |    8 +
 include/clocksource/timer-riscv.h       |   16 +
 include/uapi/linux/kvm.h                |    8 +
 28 files changed, 4558 insertions(+), 13 deletions(-)
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
```
