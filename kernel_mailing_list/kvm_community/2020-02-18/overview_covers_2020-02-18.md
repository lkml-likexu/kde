

#### [RFC PATCH 00/11] Removing Calxeda platform support
##### From: Rob Herring <robh@kernel.org>

```c
From patchwork Tue Feb 18 17:13:10 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Rob Herring <robh@kernel.org>
X-Patchwork-Id: 11389129
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC6D3138D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 17:15:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C4CC92464E
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 17:15:11 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1582046111;
	bh=y7y/2uFhH+46BBtP5zDjE6H4fDuvmrC89I0sFFjdYSQ=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=nxwpRMX1OjF2IeppJj4DE0rBuLofvWcJvjpU4W859Zm4AXP4w4rMGrfBw529FNAxl
	 2IU7mm/pXBKMI9smytitGTgDt6RT7py3ClBv0JYfLo1Ontam6P9g3wTrgd2Jum9pdT
	 hwTQBwbrkdSDbGXiSgvRFb+N0M2VEqB9cH94LX/c=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726742AbgBRRNZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 12:13:25 -0500
Received: from mail-ot1-f68.google.com ([209.85.210.68]:34844 "EHLO
        mail-ot1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726486AbgBRRNZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 12:13:25 -0500
Received: by mail-ot1-f68.google.com with SMTP id r16so20277730otd.2;
        Tue, 18 Feb 2020 09:13:24 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=KxKWes5Maiiz92tj+onliCPmpibZ/Bkve3W+pNRz4Mc=;
        b=pPdB5Tm2in8T1907YMvR6CliDUREpPsIQjmcfrfC+segvsIdLzGRCjVJLaynod4Y/i
         yivauLepwRgD2x3AWvi9tiVrEwQSPbm575N9VfoCb/JrxLxlbDDhvMYM/ZStNkdn711H
         HF127XDj53mn4gRgd5qUmsoFjtiCdJXAbx6SeudM9gD6RTw6Eb4RxzZoZwZiSlkxrFjB
         t4eTDfd6egrl4L5lhgnoLb+E3KomlVyKDxq9gYIw9RyMVneJSUV0O8xh48N4jy5gNKbV
         DCHPEt7jU4QkNihapAHUGk4YHjWLJe/COl2DX1KDA/IPJta+risZA2Yd25U8wC5VsdWT
         LvHw==
X-Gm-Message-State: APjAAAWwkDcNRKv8WC/jVaskR9EZEVtde1acWJxTcgcs4jmvFPz0bTNz
        EUDxKbdZcOki1Ko4HW5JLw==
X-Google-Smtp-Source: 
 APXvYqw78RKkguXMrAM7M8gSXlZrfkdWkZ4c6zf2HSWTeBKpVzryzLJxnnrYZ2glk4KBR3Pi24m44w==
X-Received: by 2002:a9d:10d:: with SMTP id 13mr4047747otu.238.1582046003552;
        Tue, 18 Feb 2020 09:13:23 -0800 (PST)
Received: from xps15.herring.priv (24-155-109-49.dyn.grandenetworks.net.
 [24.155.109.49])
        by smtp.googlemail.com with ESMTPSA id
 y25sm1545755oto.27.2020.02.18.09.13.21
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 18 Feb 2020 09:13:22 -0800 (PST)
From: Rob Herring <robh@kernel.org>
To: linux-arm-kernel@lists.infradead.org, linux-kernel@vger.kernel.org,
        soc@kernel.org, Andre Przywara <andre.przywara@arm.com>,
        Robert Richter <rrichter@marvell.com>,
        Jon Loeliger <jdl@jdl.com>, Alexander Graf <graf@amazon.com>,
        Matthias Brugger <mbrugger@suse.com>,
        Mark Langsdorf <mlangsdo@redhat.com>
Cc: Alex Williamson <alex.williamson@redhat.com>,
        Borislav Petkov <bp@alien8.de>,
        Cornelia Huck <cohuck@redhat.com>,
        Daniel Lezcano <daniel.lezcano@linaro.org>,
        "David S. Miller" <davem@davemloft.net>,
        devicetree@vger.kernel.org, Eric Auger <eric.auger@redhat.com>,
        iommu@lists.linux-foundation.org,
        James Morse <james.morse@arm.com>,
        Jens Axboe <axboe@kernel.dk>, Joerg Roedel <joro@8bytes.org>,
        kvm@vger.kernel.org, linux-clk@vger.kernel.org,
        linux-edac@vger.kernel.org, linux-ide@vger.kernel.org,
        linux-pm@vger.kernel.org,
        Mauro Carvalho Chehab <mchehab@kernel.org>,
        netdev@vger.kernel.org, "Rafael J. Wysocki" <rjw@rjwysocki.net>,
        Robin Murphy <robin.murphy@arm.com>,
        Stephen Boyd <sboyd@kernel.org>,
        Tony Luck <tony.luck@intel.com>,
        Viresh Kumar <viresh.kumar@linaro.org>,
        Will Deacon <will@kernel.org>
Subject: [RFC PATCH 00/11] Removing Calxeda platform support
Date: Tue, 18 Feb 2020 11:13:10 -0600
Message-Id: <20200218171321.30990-1-robh@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Calxeda has been defunct for 6 years now. Use of Calxeda servers carried
on for some time afterwards primarily as distro builders for 32-bit ARM.
AFAIK, those systems have been retired in favor of 32-bit VMs on 64-bit
hosts.

The other use of Calxeda Midway I'm aware of was testing 32-bit ARM KVM
support as there are few or no other systems with enough RAM and LPAE. Now
32-bit KVM host support is getting removed[1].

While it's not much maintenance to support, I don't care to convert the
Calxeda DT bindings to schema nor fix any resulting errors in the dts files
(which already don't exactly match what's shipping in firmware).

Rob

[1] https://lore.kernel.org/linux-arm-kernel/20200210141324.21090-1-maz@kernel.org/

Rob Herring (11):
  vfio: Remove Calxeda XGMAC reset driver
  ata: Remove Calxeda AHCI driver
  cpuidle: Remove Calxeda driver
  cpufreq: Remove Calxeda driver
  EDAC: Remove Calxeda drivers
  iommu: arm-smmu: Remove Calxeda secure mode quirk
  net: Remove Calxeda XGMAC driver
  clk: Remove Calxeda driver
  ARM: Remove Calxeda platform support
  ARM: dts: Remove Calxeda platforms
  dt-bindings: Remove Calxeda platforms bindings

 .../devicetree/bindings/arm/calxeda.yaml      |   22 -
 .../devicetree/bindings/arm/calxeda/l2ecc.txt |   15 -
 .../devicetree/bindings/ata/sata_highbank.txt |   44 -
 .../devicetree/bindings/clock/calxeda.txt     |   17 -
 .../memory-controllers/calxeda-ddr-ctrlr.txt  |   16 -
 .../devicetree/bindings/net/calxeda-xgmac.txt |   18 -
 .../bindings/phy/calxeda-combophy.txt         |   17 -
 MAINTAINERS                                   |   14 -
 arch/arm/Kconfig                              |    2 -
 arch/arm/Kconfig.debug                        |   12 +-
 arch/arm/Makefile                             |    1 -
 arch/arm/boot/dts/Makefile                    |    3 -
 arch/arm/boot/dts/ecx-2000.dts                |  103 -
 arch/arm/boot/dts/ecx-common.dtsi             |  230 --
 arch/arm/boot/dts/highbank.dts                |  161 --
 arch/arm/configs/multi_v7_defconfig           |    5 -
 arch/arm/mach-highbank/Kconfig                |   19 -
 arch/arm/mach-highbank/Makefile               |    4 -
 arch/arm/mach-highbank/core.h                 |   18 -
 arch/arm/mach-highbank/highbank.c             |  175 --
 arch/arm/mach-highbank/pm.c                   |   49 -
 arch/arm/mach-highbank/smc.S                  |   25 -
 arch/arm/mach-highbank/sysregs.h              |   75 -
 arch/arm/mach-highbank/system.c               |   22 -
 drivers/ata/Kconfig                           |    9 -
 drivers/ata/Makefile                          |    1 -
 drivers/ata/sata_highbank.c                   |  635 ------
 drivers/clk/Makefile                          |    1 -
 drivers/clk/clk-highbank.c                    |  329 ---
 drivers/cpufreq/Kconfig.arm                   |   10 -
 drivers/cpufreq/Makefile                      |    3 +-
 drivers/cpufreq/cpufreq-dt-platdev.c          |    3 -
 drivers/cpufreq/highbank-cpufreq.c            |  106 -
 drivers/cpuidle/Kconfig.arm                   |    7 -
 drivers/cpuidle/Makefile                      |    1 -
 drivers/cpuidle/cpuidle-calxeda.c             |   72 -
 drivers/edac/Kconfig                          |   14 -
 drivers/edac/Makefile                         |    3 -
 drivers/edac/highbank_l2_edac.c               |  142 --
 drivers/edac/highbank_mc_edac.c               |  272 ---
 drivers/iommu/arm-smmu-impl.c                 |   43 -
 drivers/net/ethernet/Kconfig                  |    1 -
 drivers/net/ethernet/Makefile                 |    1 -
 drivers/net/ethernet/calxeda/Kconfig          |    9 -
 drivers/net/ethernet/calxeda/Makefile         |    2 -
 drivers/net/ethernet/calxeda/xgmac.c          | 1927 -----------------
 drivers/vfio/platform/reset/Kconfig           |    8 -
 drivers/vfio/platform/reset/Makefile          |    2 -
 .../reset/vfio_platform_calxedaxgmac.c        |   74 -
 49 files changed, 2 insertions(+), 4740 deletions(-)
 delete mode 100644 Documentation/devicetree/bindings/arm/calxeda.yaml
 delete mode 100644 Documentation/devicetree/bindings/arm/calxeda/l2ecc.txt
 delete mode 100644 Documentation/devicetree/bindings/ata/sata_highbank.txt
 delete mode 100644 Documentation/devicetree/bindings/clock/calxeda.txt
 delete mode 100644 Documentation/devicetree/bindings/memory-controllers/calxeda-ddr-ctrlr.txt
 delete mode 100644 Documentation/devicetree/bindings/net/calxeda-xgmac.txt
 delete mode 100644 Documentation/devicetree/bindings/phy/calxeda-combophy.txt
 delete mode 100644 arch/arm/boot/dts/ecx-2000.dts
 delete mode 100644 arch/arm/boot/dts/ecx-common.dtsi
 delete mode 100644 arch/arm/boot/dts/highbank.dts
 delete mode 100644 arch/arm/mach-highbank/Kconfig
 delete mode 100644 arch/arm/mach-highbank/Makefile
 delete mode 100644 arch/arm/mach-highbank/core.h
 delete mode 100644 arch/arm/mach-highbank/highbank.c
 delete mode 100644 arch/arm/mach-highbank/pm.c
 delete mode 100644 arch/arm/mach-highbank/smc.S
 delete mode 100644 arch/arm/mach-highbank/sysregs.h
 delete mode 100644 arch/arm/mach-highbank/system.c
 delete mode 100644 drivers/ata/sata_highbank.c
 delete mode 100644 drivers/clk/clk-highbank.c
 delete mode 100644 drivers/cpufreq/highbank-cpufreq.c
 delete mode 100644 drivers/cpuidle/cpuidle-calxeda.c
 delete mode 100644 drivers/edac/highbank_l2_edac.c
 delete mode 100644 drivers/edac/highbank_mc_edac.c
 delete mode 100644 drivers/net/ethernet/calxeda/Kconfig
 delete mode 100644 drivers/net/ethernet/calxeda/Makefile
 delete mode 100644 drivers/net/ethernet/calxeda/xgmac.c
 delete mode 100644 drivers/vfio/platform/reset/vfio_platform_calxedaxgmac.c


base-commit: 11a48a5a18c63fd7621bb050228cebf13566e4d8
---
2.20.1
```
#### [PATCH v6 00/22] KVM: Dynamically size memslot arrays
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Feb 18 21:07:14 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11389667
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7BC831395
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 21:09:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 5E67824656
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 21:09:42 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726840AbgBRVHq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 16:07:46 -0500
Received: from mga07.intel.com ([134.134.136.100]:6395 "EHLO mga07.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726383AbgBRVHp (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 16:07:45 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by orsmga105.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Feb 2020 13:07:44 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,457,1574150400";
   d="scan'208";a="253856390"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga002.jf.intel.com with ESMTP; 18 Feb 2020 13:07:44 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Janosch Frank <frankja@linux.ibm.com>, David Hildenbrand <david@redhat.com>,
 Cornelia Huck <cohuck@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Marc Zyngier <maz@kernel.org>, James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, linux-mips@vger.kernel.org,
 kvm@vger.kernel.org, kvm-ppc@vger.kernel.org,
 linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
 linux-kernel@vger.kernel.org, Christoffer Dall <christoffer.dall@arm.com>,
 Peter Xu <peterx@redhat.com>,
 =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
Subject: [PATCH v6 00/22] KVM: Dynamically size memslot arrays
Date: Tue, 18 Feb 2020 13:07:14 -0800
Message-Id: <20200218210736.16432-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The end goal of this series is to dynamically size the memslot array so
that KVM allocates memory based on the number of memslots in use, as
opposed to unconditionally allocating memory for the maximum number of
memslots.  On x86, each memslot consumes 88 bytes, and so with 2 address
spaces of 512 memslots, each VM consumes ~90k bytes for the memslots.
E.g. given a VM that uses a total of 30 memslots, dynamic sizing reduces
the memory footprint from 90k to ~2.6k bytes.

The changes required to support dynamic sizing are relatively small,
e.g. are essentially contained in patches 17 and 18.

Patches 2-16 clean up the memslot code, which has gotten quite crusty,
especially __kvm_set_memory_region().  The clean up is likely not strictly
necessary to switch to dynamic sizing, but I didn't have a remotely
reasonable level of confidence in the correctness of the dynamic sizing
without first doing the clean up.

v6:
  - Rebase to kvm/queue, 2c2787938512 ("KVM: selftests: Stop memslot ...")
  - Collect tags. [Peter]
  - Add a paragraph in the changelog for patch 16 to explain why
    kvm_arch_sync_dirty_log() is moved from s390 to generic code. [Peter]
  - Expand a comment in patch 12 to explain why a copy of the old memslot
    needs to be made in __kvm_set_memory_region() even when deleting a
    slot. [Peter]
  - Expand a comment in patch 14 to explain why @tmp is nullified after
    copying it by value. [Peter].
  - Stuff a non-canonical value into userspace_addr when deleting a
    private memslot (on x86). [Peter]
  - Use kvm_arch_flush_remote_tlbs_memslot() as the name for the new arch
    hook to flush TLB entries for a specific memslot during
    KVM_{CLEAR,GET}_DIRTY_LOG. [Peter]
  - Drop Christoffer's Acked-by and Tested-by for patch 15 due to the
    above rename.
  - Add patches 20-22 to use kvm_flush_remote_tlbs_with_address() in
    kvm_arch_flush_remote_tlbs_memslot() and consolidate existing open
    coded versions of kvm_arch_flush_remote_tlbs_memslot().

v5:
  - Make the selftest x86-only. [Christian].
  - Collect tags. [Peter]
  - Rebase to kvm/queue, fb0c5f8fb698 ("KVM: x86: inline memslot_...").

v4:
  - Add patch 01 to fix an x86 rmap/lpage bug, and patches 10 and 11 to
    resolve hidden conflicts with the bug fix.
  - Collect tags [Christian, Marc, Philippe].
  - Rebase to kvm/queue, commit e41a90be9659 ("KVM: x86/mmu: WARN if
    root_hpa is invalid when handling a page fault").
v3:
  - Fix build errors on PPC and MIPS due to missed params during
    refactoring [kbuild test robot].
  - Rename the helpers for update_memslots() and add comments describing
    the new algorithm and how it interacts with searching [Paolo].
  - Remove the unnecessary and obnoxious warning regarding memslots being
    a flexible array [Paolo].
  - Fix typos in the changelog of patch 09/15 [Christoffer].
  - Collect tags [Christoffer].

v2:
  - Split "Drop kvm_arch_create_memslot()" into three patches to move
    minor functional changes to standalone patches [Janosch].
  - Rebase to latest kvm/queue (f0574a1cea5b, "KVM: x86: fix ...")
  - Collect an Acked-by and a Reviewed-by

Sean Christopherson (22):
  KVM: x86: Allocate new rmap and large page tracking when moving
    memslot
  KVM: Reinstall old memslots if arch preparation fails
  KVM: Don't free new memslot if allocation of said memslot fails
  KVM: PPC: Move memslot memory allocation into prepare_memory_region()
  KVM: x86: Allocate memslot resources during prepare_memory_region()
  KVM: Drop kvm_arch_create_memslot()
  KVM: Explicitly free allocated-but-unused dirty bitmap
  KVM: Refactor error handling for setting memory region
  KVM: Move setting of memslot into helper routine
  KVM: Drop "const" attribute from old memslot in commit_memory_region()
  KVM: x86: Free arrays for old memslot when moving memslot's base gfn
  KVM: Move memslot deletion to helper function
  KVM: Simplify kvm_free_memslot() and all its descendents
  KVM: Clean up local variable usage in __kvm_set_memory_region()
  KVM: Provide common implementation for generic dirty log functions
  KVM: Ensure validity of memslot with respect to kvm_get_dirty_log()
  KVM: Terminate memslot walks via used_slots
  KVM: Dynamically size memslot array based on number of used slots
  KVM: selftests: Add test for KVM_SET_USER_MEMORY_REGION
  KVM: x86/mmu: Move kvm_arch_flush_remote_tlbs_memslot() to mmu.c
  KVM: x86/mmu: Use ranged-based TLB flush for dirty log memslot flush
  KVM: x86/mmu: Consolidate open coded variants of memslot TLB flushes

 arch/mips/include/asm/kvm_host.h              |   2 +-
 arch/mips/kvm/mips.c                          |  71 +-
 arch/powerpc/include/asm/kvm_ppc.h            |  17 +-
 arch/powerpc/kvm/book3s.c                     |  22 +-
 arch/powerpc/kvm/book3s_hv.c                  |  36 +-
 arch/powerpc/kvm/book3s_pr.c                  |  20 +-
 arch/powerpc/kvm/booke.c                      |  17 +-
 arch/powerpc/kvm/powerpc.c                    |  15 +-
 arch/s390/include/asm/kvm_host.h              |   2 +-
 arch/s390/kvm/kvm-s390.c                      |  23 +-
 arch/x86/include/asm/kvm_page_track.h         |   3 +-
 arch/x86/kvm/mmu/mmu.c                        |  42 +-
 arch/x86/kvm/mmu/page_track.c                 |  15 +-
 arch/x86/kvm/x86.c                            | 120 +---
 include/linux/kvm_host.h                      |  48 +-
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   1 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  30 +
 .../kvm/x86_64/set_memory_region_test.c       | 142 ++++
 virt/kvm/arm/arm.c                            |  48 +-
 virt/kvm/arm/mmu.c                            |  20 +-
 virt/kvm/kvm_main.c                           | 624 ++++++++++++------
 23 files changed, 754 insertions(+), 566 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/set_memory_region_test.c
```
#### [RFC v2 0/4] Paravirtualized Control Register pinning
##### From: John Andersen <john.s.andersen@intel.com>

```c
From patchwork Tue Feb 18 21:58:58 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Andersen <john.s.andersen@intel.com>
X-Patchwork-Id: 11389811
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4967317EF
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 21:58:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 21B242465A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 21:58:52 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727497AbgBRV63 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 16:58:29 -0500
Received: from mga02.intel.com ([134.134.136.20]:52969 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726482AbgBRV63 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 16:58:29 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Feb 2020 13:58:27 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,458,1574150400";
   d="scan'208";a="436004632"
Received: from gza.jf.intel.com ([10.54.75.28])
  by fmsmga006.fm.intel.com with ESMTP; 18 Feb 2020 13:58:27 -0800
From: John Andersen <john.s.andersen@intel.com>
To: tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, x86@kernel.org,
        pbonzini@redhat.com
Cc: hpa@zytor.com, sean.j.christopherson@intel.com,
        vkuznets@redhat.com, wanpengli@tencent.com, jmattson@google.com,
        liran.alon@oracle.com, luto@kernel.org, joro@8bytes.org,
        rick.p.edgecombe@intel.com, kristen@linux.intel.com,
        arjan@linux.intel.com, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, John Andersen <john.s.andersen@intel.com>
Subject: [RFC v2 0/4] Paravirtualized Control Register pinning
Date: Tue, 18 Feb 2020 13:58:58 -0800
Message-Id: <20200218215902.5655-1-john.s.andersen@intel.com>
X-Mailer: git-send-email 2.21.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Many thanks to everyone who reviewed v1. Here are some notes on the
delta and feedback that was given. Thank you all for taking the time to
review and provide suggestions. I attempted to capture everything I
heard, please let me know if anything was missed. kexec support is
still pending, due to what follows about command line parameters, opt
in, and being that those changes wouldn't be localized to KVM (and this
patchset is on top of kvm/next).

- Hibernation and suspend-to-RAM are supported.

- As Paolo requested, a patch will be sent immediately following this
  patchset to kvm-unit-tests with the unit tests for general
  functionality. selftests are included for SMM specific functionality.

- Liran's catch of ensuring bits stay pinned after returning from SMM
  is now present. As a side note, CR values per AMD and Intel SDMs
  should be read-only within SMRAM. I attempted a patch to keep a copy
  of smstate in vcpu->arch which would later be used as the source of
  the read-only values. However, I ran into issues with VM/save load
  within the selftests. If someone has a better solution or knows where
  might be a good place to persist that across save/load please let me
  know.

- Andy's suggestion of a boot option has been incorporated as the
  pv_cr_pin command line option. Boris mentioned that short-term
  solutions become immutable. However, for the reasons outlined below
  we need a way for the user to opt-in to pinning over kexec if both
  are compiled in, and the command line parameter seems to be a good
  way to do that. Liran's proposed solution of a flag within the ELF
  would allow us to identify which kernels have support is assumed to
  be implemented in the following scenarios.

  We then have the following cases (without the addition of pv_cr_pin):


  - Kernel running without pinning enabled kexecs kernel with pinning.

    - Loaded kernel has kexec

      - Do not enable pinning

    - Loaded kernel lacks kexec

      - Enable pinning

  - Kernel running with pinning enabled kexecs kernel with pinning (as
    identified by ELF addition).

    - Okay

  - Kernel running with pinning enabled kexecs kernel without pinning
    (as identified by lack of ELF addition).

    - User is presented with an error saying that they may not kexec
      a kernel without pinning support.


  With the addition of pv_cr_pin we have the following situations:


  - Kernel running without pinning enabled kexecs kernel with pinning.

    - Loaded kernel has kexec

      - pv_cr_pin command line parameter present

        - Enable pinning

      - pv_cr_pin command line parameter not present

        - Do not enable pinning

    - Loaded kernel lacks kexec

      - Enable pinning

  - Kernel running with pinning enabled kexecs kernel with pinning (as
    identified by ELF addition).

    - Okay

  - Kernel running with pinning enabled kexecs kernel without pinning
    (as identified by lack of ELF addition).

    - pv_cr_pin command line parameter present

      - User is presented with an error saying that they have opted
	into pinning support and may not kexec a kernel without pinning
        support.

    - pv_cr_pin command line parameter not present

      - Pinning not enabled (not opted into), kexec succeeds


  Without the command line parameter I'm not sure how we could preserve
  users workflows which might rely on kexecing older kernels (ones
  which wouldn't have support). I see the benefit here being that users
  have to opt-in to the possibility of breaking their workflow, via
  their addition of the pv_cr_pin command line flag. Which could of
  course also be called nokexec. A deprecation period could then be
  chosen where eventually pinning takes preference over kexec and users
  are presented with the error if they try to kexec an older kernel.
  Input on this would be much appreciated, as well as if this is the
  best way to handle things or if there's another way that would be
  preferred. This is just what we were able to come up with to ensure
  users didn't get anything broken they didn't agree to have broken.



Paravirtualized Control Register pinning is a strengthened version of
existing protections on the Write Protect, Supervisor Mode Execution /
Access Protection, and User-Mode Instruction Prevention bits. The
existing protections prevent native_write_cr*() functions from writing
values which disable those bits. This patchset prevents any guest
writes to control registers from disabling pinned bits, not just writes
from native_write_cr*(). This stops attackers within the guest from
using ROP to disable protection bits.

https://web.archive.org/web/20171029060939/http://www.blackbunny.io/linux-kernel-x86-64-bypass-smep-kaslr-kptr_restric/

The protection is implemented by adding MSRs to KVM which contain the
bits that are allowed to be pinned, and the bits which are pinned. The
guest or userspace can enable bit pinning by reading MSRs to check
which bits are allowed to be pinned, and then writing MSRs to set which
bits they want pinned.

Other hypervisors such as HyperV have implemented similar protections
for Control Registers and MSRs; which security researchers have found
effective.

https://www.abatchy.com/2018/01/kernel-exploitation-4

We add a CR pin feature bit to the KVM cpuid, read only MSRs which
guests use to identify which bits they may request be pinned, and CR
pinned MSRs which contain the pinned bits. Guests can request that KVM
pin bits within control register 0 or 4 via the CR pinned MSRs.  Writes
to the MSRs fail if they include bits that aren't allowed to be pinned.
Host userspace may clear or modify pinned bits at any time.  Once
pinned bits are set, the guest may pin more allowed bits, but may never
clear pinned bits.

In the event that the guest vCPU attempts to disable any of the pinned
bits, the vCPU that issued the write is sent a general protection
fault, and the register is left unchanged.

When running with KVM guest support and paravirtualized CR pinning
enabled, paravirtualized and existing pinning are setup at the same
point on the boot CPU. Non-boot CPUs setup pinning upon identification.

Pinning is not active when running in SMM. Entering SMM disables pinned
bits. Writes to control registers within SMM would therefore trigger
general protection faults if pinning was enforced. Upon exit from SMM,
SMRAM is modified to ensure the values of CR0/4 that will be restored
contain the correct values for pinned bits. CR0/4 values are then
restored from SMRAM as usual.

Should userspace expose the CR pining CPUID feature bit, it must zero
CR pinned MSRs on reboot. If it does not, it runs the risk of having
the guest enable pinning and subsequently cause general protection
faults on next boot due to early boot code setting control registers to
values which do not contain the pinned bits.

Hibernation to disk and suspend-to-RAM are supported. identify_cpu was
updated to ensure SMEP/SMAP/UMIP are present in mmu_cr4_features. This
is necessary to ensure protections stay active during hibernation image
restoration.

Guests using the kexec system call currently do not support
paravirtualized control register pinning. This is due to early boot
code writing known good values to control registers, these values do
not contain the protected bits. This is due to CPU feature
identification being done at a later time, when the kernel properly
checks if it can enable protections. As such, the pv_cr_pin command
line option has been added which instructs the kernel to disable kexec
in favor of enabling paravirtualized control register pinning.
crashkernel is also disabled when the pv_cr_pin parameter is specified
due to its reliance on kexec.

When we make kexec compatible, we will still need a way for a kernel
with support to know if the kernel it is attempting to load has
support. If a kernel with this enabled attempts to kexec a kernel where
this is not supported, it would trigger a fault almost immediately.

Liran suggested adding a section to the built image acting as a flag to
signify support for being kexec'd by a kernel with pinning enabled.
Should that approach be implemented, it is likely that the command line
flag (pv_cr_pin) would still be desired for some deprecation period. We
wouldn't want the default behavior to change from being able to kexec
older kernels to not being able to, as this might break some users
workflows. Since we require that the user opt-in to break kexec we've
held off on attempting to fix kexec in this patchset. This way no one
sees any behavior they are not explicitly opting in to.

Security conscious kernel configurations disable kexec already, per
KSPP guidelines. Projects such as Kata Containers, AWS Lambda, ChromeOS
Termina, and others using KVM to virtualize Linux will benefit from
this protection without the need to specify pv_cr_pin on the command
line.

Pinning of sensitive CR bits has already been implemented to protect
against exploits directly calling native_write_cr*(). The current
protection cannot stop ROP attacks which jump directly to a MOV CR
instruction. Guests running with paravirtualized CR pinning are now
protected against the use of ROP to disable CR bits. The same bits that
are being pinned natively may be pinned via the CR pinned MSRs. These
bits are WP in CR0, and SMEP, SMAP, and UMIP in CR4.

Future patches could implement similar MSRs to protect bits in MSRs.
The NXE bit of the EFER MSR is a prime candidate.

John Andersen (4):
  X86: Update mmu_cr4_features during feature identification
  KVM: X86: Add CR pin MSRs
  selftests: kvm: add test for CR pinning with SMM
  X86: Use KVM CR pin MSRs

 .../admin-guide/kernel-parameters.txt         |  11 ++
 Documentation/virt/kvm/msr.rst                |  38 ++++
 arch/x86/Kconfig                              |  10 +
 arch/x86/include/asm/kvm_host.h               |   2 +
 arch/x86/include/asm/kvm_para.h               |  17 ++
 arch/x86/include/uapi/asm/kvm_para.h          |   5 +
 arch/x86/kernel/cpu/common.c                  |  11 +-
 arch/x86/kernel/kvm.c                         |  39 ++++
 arch/x86/kernel/setup.c                       |  12 +-
 arch/x86/kvm/cpuid.c                          |   3 +-
 arch/x86/kvm/x86.c                            | 130 ++++++++++++-
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/include/x86_64/processor.h  |   9 +
 .../selftests/kvm/x86_64/smm_cr_pin_test.c    | 180 ++++++++++++++++++
 15 files changed, 462 insertions(+), 7 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/smm_cr_pin_test.c
```
#### [PATCH v2 0/3] KVM: x86: Minor emulator cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From patchwork Tue Feb 18 23:03:07 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11389921
Return-Path: <SRS0=NRU2=4G=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C183A92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 23:03:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AC05024658
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 18 Feb 2020 23:03:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727705AbgBRXDL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 18 Feb 2020 18:03:11 -0500
Received: from mga02.intel.com ([134.134.136.20]:57150 "EHLO mga02.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727298AbgBRXDL (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 18 Feb 2020 18:03:11 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by orsmga101.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 18 Feb 2020 15:03:11 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.70,458,1574150400";
   d="scan'208";a="239504569"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.202])
  by orsmga006.jf.intel.com with ESMTP; 18 Feb 2020 15:03:10 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 0/3] KVM: x86: Minor emulator cleanup
Date: Tue, 18 Feb 2020 15:03:07 -0800
Message-Id: <20200218230310.29410-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Three small patches to move emulator specific variables from 'struct
kvm_vcpu_arch' to 'struct x86_emulate_ctxt'.

v2:
  - Rebase to kvm/queue, 2c2787938512 ("KVM: selftests: Stop ...")

Sean Christopherson (3):
  KVM: x86: Add EMULTYPE_PF when emulation is triggered by a page fault
  KVM: x86: Move gpa_val and gpa_available into the emulator context
  KVM: x86: Move #PF retry tracking variables into emulation context

 arch/x86/include/asm/kvm_emulate.h |  8 ++++++
 arch/x86/include/asm/kvm_host.h    | 19 ++++++-------
 arch/x86/kvm/mmu/mmu.c             | 10 ++-----
 arch/x86/kvm/x86.c                 | 45 +++++++++++++++++++-----------
 4 files changed, 48 insertions(+), 34 deletions(-)
```
