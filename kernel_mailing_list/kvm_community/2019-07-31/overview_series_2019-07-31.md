#### [PATCH 1/3] KVM: Don't need to wakeup vCPU twice afer timer fire
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

kvm_set_pending_timer() will take care to wake up the sleeping vCPU which 
has pending timer, don't need to check this in apic_timer_expired() again.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 8 --------
 1 file changed, 8 deletions(-)

```
#### [PATCH 1/5] KVM: arm/arm64: Introduce kvm_pmu_vcpu_init() to setup PMU counter index
##### From: Marc Zyngier <maz@kernel.org>

```c
From: Zenghui Yu <yuzenghui@huawei.com>

We use "pmc->idx" and the "chained" bitmap to determine if the pmc is
chained, in kvm_pmu_pmc_is_chained().  But idx might be uninitialized
(and random) when we doing this decision, through a KVM_ARM_VCPU_INIT
ioctl -> kvm_pmu_vcpu_reset(). And the test_bit() against this random
idx will potentially hit a KASAN BUG [1].

In general, idx is the static property of a PMU counter that is not
expected to be modified across resets, as suggested by Julien.  It
looks more reasonable if we can setup the PMU counter idx for a vcpu
in its creation time. Introduce a new function - kvm_pmu_vcpu_init()
for this basic setup. Oh, and the KASAN BUG will get fixed this way.

[1] https://www.spinics.net/lists/kvm-arm/msg36700.html

Fixes: 80f393a23be6 ("KVM: arm/arm64: Support chained PMU counters")
Suggested-by: Andrew Murray <andrew.murray@arm.com>
Suggested-by: Julien Thierry <julien.thierry@arm.com>
Acked-by: Julien Thierry <julien.thierry@arm.com>
Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 include/kvm/arm_pmu.h |  2 ++
 virt/kvm/arm/arm.c    |  2 ++
 virt/kvm/arm/pmu.c    | 18 +++++++++++++++---
 3 files changed, 19 insertions(+), 3 deletions(-)

```
#### [PATCH V2 1/9] vhost: don't set uaddr for invalid address
##### From: Jason Wang <jasowang@redhat.com>

```c
We should not setup uaddr for the invalid address, otherwise we may
try to pin or prefetch mapping of wrong pages.

Fixes: 7f466032dc9e ("vhost: access vq metadata through kernel virtual address")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [GIT PULL] KVM/arm updates for 5.3-rc3
##### From: Marc Zyngier <maz@kernel.org>

```c
Paolo, Radim,

Here's a handful of patches for 5.3-rc3: Two actual fixes (missing
break; in the 32bit register mapping, PMU reset being broken after the
chained counter update). The rest is either cosmetic (exception
classes in debug/tracing) or silence warnings (the fall-through
explosion).

Please pull.

	M.

The following changes since commit 5f9e832c137075045d15cd6899ab0505cfb2ca4b:

  Linus 5.3-rc1 (2019-07-21 14:05:38 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm.git tags/kvmarm-fixes-for-5.3

for you to fetch changes up to cdb2d3ee0436d74fa9092f2df46aaa6f9e03c969:

  arm64: KVM: hyp: debug-sr: Mark expected switch fall-through (2019-07-29 11:01:37 +0100)

----------------------------------------------------------------
KVM/arm fixes for 5.3

- A bunch of switch/case fall-through annotation, fixing one actual bug
- Fix PMU reset bug
- Add missing exception class debug strings

----------------------------------------------------------------
Anders Roxell (3):
      arm64: KVM: regmap: Fix unexpected switch fall-through
      KVM: arm: vgic-v3: Mark expected switch fall-through
      arm64: KVM: hyp: debug-sr: Mark expected switch fall-through

Zenghui Yu (2):
      KVM: arm/arm64: Introduce kvm_pmu_vcpu_init() to setup PMU counter index
      KVM: arm64: Update kvm_arm_exception_class and esr_class_str for new EC

 arch/arm64/include/asm/kvm_arm.h |  7 ++++---
 arch/arm64/kernel/traps.c        |  1 +
 arch/arm64/kvm/hyp/debug-sr.c    | 30 ++++++++++++++++++++++++++++++
 arch/arm64/kvm/regmap.c          |  5 +++++
 include/kvm/arm_pmu.h            |  2 ++
 virt/kvm/arm/arm.c               |  2 ++
 virt/kvm/arm/hyp/vgic-v3-sr.c    |  8 ++++++++
 virt/kvm/arm/pmu.c               | 18 +++++++++++++++---
 8 files changed, 67 insertions(+), 6 deletions(-)

From patchwork Wed Jul 31 17:36:47 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11068933
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A85B11395
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 31 Jul 2019 17:37:08 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 9010B1FFBE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 31 Jul 2019 17:37:08 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 83AFC228C9; Wed, 31 Jul 2019 17:37:08 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 1DFD11FFBE
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 31 Jul 2019 17:37:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728232AbfGaRhH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 31 Jul 2019 13:37:07 -0400
Received: from foss.arm.com ([217.140.110.172]:52480 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727125AbfGaRhH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 31 Jul 2019 13:37:07 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 35BDC1596;
        Wed, 31 Jul 2019 10:37:06 -0700 (PDT)
Received: from big-swifty.lan (unknown [172.31.20.19])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPSA id
 1D8E13F71F;
        Wed, 31 Jul 2019 10:37:02 -0700 (PDT)
From: Marc Zyngier <maz@kernel.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Anders Roxell <anders.roxell@linaro.org>,
        Andrew Murray <andrew.murray@arm.com>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry@arm.com>,
        Zenghui Yu <yuzenghui@huawei.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Subject: [PATCH 2/5] arm64: KVM: regmap: Fix unexpected switch fall-through
Date: Wed, 31 Jul 2019 18:36:47 +0100
Message-Id: <20190731173650.12627-3-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190731173650.12627-1-maz@kernel.org>
References: <20190731173650.12627-1-maz@kernel.org>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

From: Anders Roxell <anders.roxell@linaro.org>

When fall-through warnings was enabled by default, commit d93512ef0f0e
("Makefile: Globally enable fall-through warning"), the following
warnings was starting to show up:

In file included from ../arch/arm64/include/asm/kvm_emulate.h:19,
                 from ../arch/arm64/kvm/regmap.c:13:
../arch/arm64/kvm/regmap.c: In function ‘vcpu_write_spsr32’:
../arch/arm64/include/asm/kvm_hyp.h:31:3: warning: this statement may fall
 through [-Wimplicit-fallthrough=]
   asm volatile(ALTERNATIVE(__msr_s(r##nvh, "%x0"), \
   ^~~
../arch/arm64/include/asm/kvm_hyp.h:46:31: note: in expansion of macro ‘write_sysreg_elx’
 #define write_sysreg_el1(v,r) write_sysreg_elx(v, r, _EL1, _EL12)
                               ^~~~~~~~~~~~~~~~
../arch/arm64/kvm/regmap.c:180:3: note: in expansion of macro ‘write_sysreg_el1’
   write_sysreg_el1(v, SYS_SPSR);
   ^~~~~~~~~~~~~~~~
../arch/arm64/kvm/regmap.c:181:2: note: here
  case KVM_SPSR_ABT:
  ^~~~
In file included from ../arch/arm64/include/asm/cputype.h:132,
                 from ../arch/arm64/include/asm/cache.h:8,
                 from ../include/linux/cache.h:6,
                 from ../include/linux/printk.h:9,
                 from ../include/linux/kernel.h:15,
                 from ../include/asm-generic/bug.h:18,
                 from ../arch/arm64/include/asm/bug.h:26,
                 from ../include/linux/bug.h:5,
                 from ../include/linux/mmdebug.h:5,
                 from ../include/linux/mm.h:9,
                 from ../arch/arm64/kvm/regmap.c:11:
../arch/arm64/include/asm/sysreg.h:837:2: warning: this statement may fall
 through [-Wimplicit-fallthrough=]
  asm volatile("msr " __stringify(r) ", %x0"  \
  ^~~
../arch/arm64/kvm/regmap.c:182:3: note: in expansion of macro ‘write_sysreg’
   write_sysreg(v, spsr_abt);
   ^~~~~~~~~~~~
../arch/arm64/kvm/regmap.c:183:2: note: here
  case KVM_SPSR_UND:
  ^~~~

Rework to add a 'break;' in the swich-case since it didn't have that,
leading to an interresting set of bugs.

Cc: stable@vger.kernel.org # v4.17+
Fixes: a892819560c4 ("KVM: arm64: Prepare to handle deferred save/restore of 32-bit registers")
Signed-off-by: Anders Roxell <anders.roxell@linaro.org>
[maz: reworked commit message, fixed stable range]
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/regmap.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCHv2 01/59] mm: Do no merge VMAs with different encryption KeyIDs
##### From: "Kirill A. Shutemov" <kirill@shutemov.name>

```c
VMAs with different KeyID do not mix together. Only VMAs with the same
KeyID are compatible.

Signed-off-by: Kirill A. Shutemov <kirill.shutemov@linux.intel.com>
---
 fs/userfaultfd.c   |  7 ++++---
 include/linux/mm.h |  9 ++++++++-
 mm/madvise.c       |  2 +-
 mm/mempolicy.c     |  3 ++-
 mm/mlock.c         |  2 +-
 mm/mmap.c          | 31 +++++++++++++++++++------------
 mm/mprotect.c      |  2 +-
 7 files changed, 36 insertions(+), 20 deletions(-)

```
#### [PATCH v2 1/3] KVM: selftests: Split ucall.c into architecture specific files
##### From: Thomas Huth <thuth@redhat.com>

```c
The way we exit from a guest to userspace is very specific to the
architecture: On x86, we use PIO, on aarch64 we are using MMIO and on
s390x we're going to use an instruction instead. The possibility to
select a type via the ucall_type_t enum is currently also completely
unused, so the code in ucall.c currently looks more complex than
required. Let's split this up into architecture specific ucall.c
files instead, so we can get rid of the #ifdefs and the unnecessary
ucall_type_t handling.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 tools/testing/selftests/kvm/Makefile          |   6 +-
 tools/testing/selftests/kvm/dirty_log_test.c  |   2 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   8 +-
 .../testing/selftests/kvm/lib/aarch64/ucall.c | 112 +++++++++++++
 tools/testing/selftests/kvm/lib/ucall.c       | 157 ------------------
 .../testing/selftests/kvm/lib/x86_64/ucall.c  |  56 +++++++
 6 files changed, 173 insertions(+), 168 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/lib/aarch64/ucall.c
 delete mode 100644 tools/testing/selftests/kvm/lib/ucall.c
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/ucall.c

```
#### [PATCH v3 1/3] KVM: selftests: Split ucall.c into architecture specific files
##### From: Thomas Huth <thuth@redhat.com>

```c
The way we exit from a guest to userspace is very specific to the
architecture: On x86, we use PIO, on aarch64 we are using MMIO and on
s390x we're going to use an instruction instead. The possibility to
select a type via the ucall_type_t enum is currently also completely
unused, so the code in ucall.c currently looks more complex than
required. Let's split this up into architecture specific ucall.c
files instead, so we can get rid of the #ifdefs and the unnecessary
ucall_type_t handling.

Reviewed-by: Andrew Jones <drjones@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 tools/testing/selftests/kvm/Makefile          |   6 +-
 tools/testing/selftests/kvm/dirty_log_test.c  |   2 +-
 .../testing/selftests/kvm/include/kvm_util.h  |   8 +-
 .../testing/selftests/kvm/lib/aarch64/ucall.c | 112 +++++++++++++
 tools/testing/selftests/kvm/lib/ucall.c       | 157 ------------------
 .../testing/selftests/kvm/lib/x86_64/ucall.c  |  56 +++++++
 6 files changed, 173 insertions(+), 168 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/lib/aarch64/ucall.c
 delete mode 100644 tools/testing/selftests/kvm/lib/ucall.c
 create mode 100644 tools/testing/selftests/kvm/lib/x86_64/ucall.c

```
#### [PATCH] KVM: selftests: Update gitignore file for latest changes
##### From: Thomas Huth <thuth@redhat.com>

```c
The kvm_create_max_vcpus test has been moved to the main directory,
and sync_regs_test is now available on s390x, too.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 tools/testing/selftests/kvm/.gitignore | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v5 1/7] s390: vfio-ap: Refactor vfio_ap driver probe and remove callbacks
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
In order to limit the number of private mdev functions called from the
vfio_ap device driver as well as to provide a landing spot for dynamic
configuration code related to binding/unbinding AP queue devices to/from
the vfio_ap driver, the following changes are being introduced:

* Move code from the vfio_ap driver's probe callback into a function
  defined in the mdev private operations file.

* Move code from the vfio_ap driver's remove callback into a function
  defined in the mdev private operations file.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_drv.c     | 23 +++--------
 drivers/s390/crypto/vfio_ap_ops.c     | 78 ++++++++++++++++++++++++++++-------
 drivers/s390/crypto/vfio_ap_private.h |  6 +--
 3 files changed, 71 insertions(+), 36 deletions(-)

```
#### [PATCH] selftests: kvm: Adding config fragments
##### From: Naresh Kamboju <naresh.kamboju@linaro.org>

```c
selftests kvm test cases need pre-required kernel configs for the test
to get pass.

Signed-off-by: Naresh Kamboju <naresh.kamboju@linaro.org>
---
 tools/testing/selftests/kvm/config | 26 ++++++++++++++++++++++++++
 1 file changed, 26 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/config

diff --git a/tools/testing/selftests/kvm/config b/tools/testing/selftests/kvm/config
new file mode 100644
index 000000000000..3b1cbd726af6
--- /dev/null
+++ b/tools/testing/selftests/kvm/config
@@ -0,0 +1,26 @@
+CONFIG_ARCH_ENABLE_THP_MIGRATION=y
+CONFIG_HAVE_KVM_IRQCHIP=y
+CONFIG_HAVE_KVM_IRQFD=y
+CONFIG_HAVE_KVM_IRQ_ROUTING=y
+CONFIG_HAVE_KVM_EVENTFD=y
+CONFIG_KVM_MMIO=y
+CONFIG_KVM_ASYNC_PF=y
+CONFIG_HAVE_KVM_MSI=y
+CONFIG_HAVE_KVM_CPU_RELAX_INTERCEPT=y
+CONFIG_KVM_VFIO=y
+CONFIG_KVM_GENERIC_DIRTYLOG_READ_PROTECT=y
+CONFIG_KVM_COMPAT=y
+CONFIG_HAVE_KVM_IRQ_BYPASS=y
+CONFIG_HAVE_KVM_NO_POLL=y
+CONFIG_KVM=y
+CONFIG_VHOST_NET=y
+CONFIG_VHOST=y
+CONFIG_VHOST_CROSS_ENDIAN_LEGACY=y
+CONFIG_USER_RETURN_NOTIFIER=y
+CONFIG_PREEMPT_NOTIFIERS=y
+CONFIG_TRANSPARENT_HUGEPAGE=y
+CONFIG_TRANSPARENT_HUGEPAGE_MADVISE=y
+CONFIG_THP_SWAP=y
+CONFIG_TRANSPARENT_HUGE_PAGECACHE=y
+CONFIG_IRQ_BYPASS_MANAGER=y
+CONFIG_XARRAY_MULTI=y
```
#### [PATCH v2 1/2] KVM: remove kvm_arch_has_vcpu_debugfs()
##### From: Greg KH <gregkh@linuxfoundation.org>

```c
There is no need for this function as all arches have to implement
kvm_arch_create_vcpu_debugfs() no matter what, so just remove this call
as it is pointless.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krm" <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: <x86@kernel.org>
Cc: <kvm@vger.kernel.org>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
v2: new patch in the series

 arch/mips/kvm/mips.c       | 5 -----
 arch/powerpc/kvm/powerpc.c | 5 -----
 arch/s390/kvm/kvm-s390.c   | 5 -----
 arch/x86/kvm/debugfs.c     | 5 -----
 include/linux/kvm_host.h   | 1 -
 virt/kvm/arm/arm.c         | 5 -----
 virt/kvm/kvm_main.c        | 3 ---
 7 files changed, 29 deletions(-)

```
#### [PATCH v2 3/3] KVM: Fix leak vCPU's VMCS value into other pCPU
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

After commit d73eb57b80b (KVM: Boost vCPUs that are delivering interrupts), a 
five years ago bug is exposed. Running ebizzy benchmark in three 80 vCPUs VMs 
on one 80 pCPUs Skylake server, a lot of rcu_sched stall warning splatting 
in the VMs after stress testing:

 INFO: rcu_sched detected stalls on CPUs/tasks: { 4 41 57 62 77} (detected by 15, t=60004 jiffies, g=899, c=898, q=15073)
 Call Trace:
   flush_tlb_mm_range+0x68/0x140
   tlb_flush_mmu.part.75+0x37/0xe0
   tlb_finish_mmu+0x55/0x60
   zap_page_range+0x142/0x190
   SyS_madvise+0x3cd/0x9c0
   system_call_fastpath+0x1c/0x21

swait_active() sustains to be true before finish_swait() is called in 
kvm_vcpu_block(), voluntarily preempted vCPUs are taken into account 
by kvm_vcpu_on_spin() loop greatly increases the probability condition 
kvm_arch_vcpu_runnable(vcpu) is checked and can be true, when APICv 
is enabled the yield-candidate vCPU's VMCS RVI field leaks(by 
vmx_sync_pir_to_irr()) into spinning-on-a-taken-lock vCPU's current 
VMCS.

This patch fixes it by reverting the kvm_arch_vcpu_runnable() condition 
in kvm_vcpu_on_spin() loop and checking swait_active(&vcpu->wq) for 
involuntary preemption.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Fixes: 98f4a1467 (KVM: add kvm_arch_vcpu_runnable() test to kvm_vcpu_on_spin() loop)
Cc: stable@vger.kernel.org
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * checking swait_active(&vcpu->wq) for involuntary preemption

 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
