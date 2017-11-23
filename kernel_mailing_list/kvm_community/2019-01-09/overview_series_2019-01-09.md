#### [PATCH 01/22] x86/fpu: Remove fpu->initialized usage in __fpu__restore_sig()
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
This is a preparation for the removal of the ->initialized member in the
fpu struct.
__fpu__restore_sig() is deactivating the FPU via fpu__drop() and then
setting manually ->initialized followed by fpu__restore(). The result is
that it is possible to manipulate fpu->state and the state of registers
won't be saved/restored on a context switch which would overwrite
fpu->state.

Don't access the fpu->state while the content is read from user space
and examined / sanitized. Use a temporary kmalloc() buffer for the
preparation of the FPU registers and once the state is considered okay,
load it. Should something go wrong, return with an error and without
altering the original FPU registers.

The removal of "fpu__initialize()" is a nop because fpu->initialized is
already set for the user task.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Acked-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/fpu/signal.h |  2 +-
 arch/x86/kernel/fpu/regset.c      |  5 ++--
 arch/x86/kernel/fpu/signal.c      | 41 ++++++++++++-------------------
 3 files changed, 19 insertions(+), 29 deletions(-)

```
#### [PATCH 1/3] arm/arm64: KVM: Introduce kvm_call_hyp_ret()
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Until now, we haven't differentiated between HYP calls that
have a return value and those who don't. As we're about to
change this, introduce kvm_call_hyp_ret(), and change all
call sites that actually make use of a return value.

Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm/include/asm/kvm_host.h   | 3 +++
 arch/arm64/include/asm/kvm_host.h | 1 +
 arch/arm64/kvm/debug.c            | 2 +-
 virt/kvm/arm/arm.c                | 2 +-
 virt/kvm/arm/vgic/vgic-v3.c       | 4 ++--
 5 files changed, 8 insertions(+), 4 deletions(-)

```
#### [PATCH net-next V2 1/3] virtio: introduce in order feature bit
##### From: Jason Wang <jasowang@redhat.com>

```c
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 include/uapi/linux/virtio_config.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH v1 1/2] vfio:iommu: Use capabilities do report IOMMU informations
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
We add a new flag, VFIO_IOMMU_INFO_CAPABILITIES, inside the
vfio_iommu_type1_info to specify the support for capabilities.

We add a new capability, with id VFIO_IOMMU_INFO_CAP_DMA
in the capability list of the VFIO_IOMMU_GET_INFO ioctl.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 include/uapi/linux/vfio.h | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [PATCH v3 1/5] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

This also handles asynchronous flush requests from the block layer
by creating a child bio and chaining it with parent bio.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 12 ++++++++----
 drivers/nvdimm/region_devs.c | 38 ++++++++++++++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  5 ++++-
 6 files changed, 55 insertions(+), 11 deletions(-)

```
#### [PATCH v3 1/5] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

This also handles asynchronous flush requests from the block layer
by creating a child bio and chaining it with parent bio.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 12 ++++++++----
 drivers/nvdimm/region_devs.c | 38 ++++++++++++++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  5 ++++-
 6 files changed, 55 insertions(+), 11 deletions(-)

```
#### [PATCH v5 01/13] X86/nVMX: handle_vmon: Read 4 bytes from guest memory
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c
Read the data directly from guest memory instead of the map->read->unmap
sequence. This also avoids using kvm_vcpu_gpa_to_page() and kmap() which
assumes that there is a "struct page" for guest memory.

Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: KarimAllah Ahmed <karahmed@amazon.de>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
v1 -> v2:
- Massage commit message a bit.
---
 arch/x86/kvm/vmx/nested.c | 14 +++-----------
 1 file changed, 3 insertions(+), 11 deletions(-)

```
#### [PATCH net V2] vhost: log dirty page correctly
##### From: Jason Wang <jasowang@redhat.com>

```c
Vhost dirty page logging API is designed to sync through GPA. But we
try to log GIOVA when device IOTLB is enabled. This is wrong and may
lead to missing data after migration.

To solve this issue, when logging with device IOTLB enabled, we will:

1) reuse the device IOTLB translation result of GIOVA->HVA mapping to
   get HVA, for writable descriptor, get HVA through iovec. For used
   ring update, translate its GIOVA to HVA
2) traverse the GPA->HVA mapping to get the possible GPA and log
   through GPA. Pay attention this reverse mapping is not guaranteed
   to be unique, so we should log each possible GPA in this case.

This fix the failure of scp to guest during migration. In -next, we
will probably support passing GIOVA->GPA instead of GIOVA->HVA.

Fixes: 6b1e6cc7855b ("vhost: new device IOTLB API")
Reported-by: Jintack Lim <jintack@cs.columbia.edu>
Cc: Jintack Lim <jintack@cs.columbia.edu>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
The patch is needed for stable.
Changes from V1:
- return error instead of warn
---
 drivers/vhost/net.c   |  3 +-
 drivers/vhost/vhost.c | 82 +++++++++++++++++++++++++++++++++++--------
 drivers/vhost/vhost.h |  3 +-
 3 files changed, 72 insertions(+), 16 deletions(-)

```
#### [PATCH tip/core/rcu 2/2] virt/kvm: Replace spin_is_locked() with lockdep
##### From: "Paul E. McKenney" <paulmck@linux.ibm.com>

```c
lockdep_assert_held() is better suited to checking locking requirements,
since it only checks if the current thread holds the lock regardless of
whether someone else does. This is also a step towards possibly removing
spin_is_locked().

Signed-off-by: Paul E. McKenney <paulmck@linux.ibm.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: <kvm@vger.kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 virt/kvm/kvm_main.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH RESEND] KVM: MMU: Introduce single thread to zap collapsible sptes
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Last year guys from huawei reported that the call of memory_global_dirty_log_start/stop() 
takes 13s for 4T memory and cause guest freeze too long which increases the unacceptable 
migration downtime. [1] [2]

Guangrong pointed out:

| collapsible_sptes zaps 4k mappings to make memory-read happy, it is not
| required by the semanteme of KVM_SET_USER_MEMORY_REGION and it is not
| urgent for vCPU's running, it could be done in a separate thread and use
| lock-break technology.

Several TB memory guest is common now after NVDIMM is deployed in cloud environment.
This patch utilizes worker thread to zap collapsible sptes in order to lazy collapse 
small sptes into large sptes during roll-back after live migration fails.

[1] https://lists.gnu.org/archive/html/qemu-devel/2017-04/msg05249.html
[2] https://www.mail-archive.com/qemu-devel@nongnu.org/msg449994.html

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
Note:
I ever consider to add a list of memslots to be zapped, delete from the list
and add in kvm_mmu_zap_collapsible_sptes(). However, i observe a lot of races 
here, the memslot can disappear/modify underneath before the worker thread
start to zap even if i introduce lock to protect the list. This patch delays 
the worker thread by 60s(to assume memory_global_dirty_log_stop can absolutely 
complete) to coalesce all the zap requirements after live migration fails.

 arch/x86/include/asm/kvm_host.h |  3 +++
 arch/x86/kvm/mmu.c              | 37 ++++++++++++++++++++++++++++++++-----
 arch/x86/kvm/x86.c              |  4 ++++
 3 files changed, 39 insertions(+), 5 deletions(-)

```
#### [PATCH v6] x86: load FPU registers on return to userland
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
This is a refurbished series originally started by by Rik van Riel. The
goal is load the FPU registers on return to userland and not on every
context switch. By this optimisation we can:
- avoid loading the registers if the task stays in kernel and does
  not return to userland
- make kernel_fpu_begin() cheaper: it only saves the registers on the
  first invocation. The second invocation does not need save them again.

To access the FPU registers in kernel we need:
- disable preemption to avoid that the scheduler switches tasks. By
  doing so it would set TIF_NEED_FPU_LOAD and the FPU registers would be
  not valid.
- disable BH because the softirq might use kernel_fpu_begin() and then
  set TIF_NEED_FPU_LOAD instead loading the FPU registers on completion.

v5…v6:
Rebased on top of v5.0-rc1. Integrated a few fixes which I noticed while
looking over the patches, dropped the first few patches which were
already applied.

v4…v5:
Rebased on top of a fix, noticed a problem with XSAVES and then redid
the restore on sig return (patch #26 to #28).

I don't like very much the sig save+restore thing that we are doing. It
has been always like that. I *think* that this is just because we have
nowhere to stash the FPU state while we are handling the signal. We
could add another fpu->state for the signal handler and avoid the thing.
Debian code-search revealed that `criu' is using it (and I didn't
figure out why). Nothing else (that is packaged in Debian). Maybe we
could get rid of this and if `criu' would then use a dedicated interface
for its needs rather the signal interface that happen to do what it
wants :)

v3…v4:
It has been suggested to remove the `initialized' member of the struct
fpu because it should not required be needed with lazy-FPU-restore and
would make the review easier. This is the first part of the series, the
second is basically the rebase of the v3 queue. As a result, the
diffstat became negative (which wasn't the case in previous version) :)
I tried to incorporate all the review comments that came up, some of
them were "outdated" after the removal of the `initialized' member. I'm
sorry should I missed any.

v1…v3:
v2 was never posted. I followed the idea to completely decouple PKRU
from xstate. This didn't quite work and made a few things complicated. 
One obvious required fixup is copy_fpstate_to_sigframe() where the PKRU
state needs to be fiddled into xstate. This required another
xfeatures_mask so that the sanity checks were performed and
xstate_offsets would be computed. Additionally ptrace also reads/sets
xstate in order to get/set the register and PKRU is one of them. So this
would need some fiddle, too.
In v3 I dropped that decouple idea. I also learned that the wrpkru
instruction is not privileged and so caching it in kernel does not work.
Instead I keep PKRU in xstate area and load it at context switch time
while the remaining registers are deferred (until return to userland).
The offset of PKRU within xstate is enumerated at boot time so why not
use it.

The following changes since commit bfeffd155283772bbe78c6a05dec7c0128ee500c:

  Linux 5.0-rc1 (2019-01-06 17:08:20 -0800)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/bigeasy/staging.git x86_fpu_rtu_v6

for you to fetch changes up to b7b783d84166b6b74aed2bfd4a07128ff303fed6:

  x86/fpu: Defer FPU state load until return to userspace (2019-01-07 11:32:57 +0100)

----------------------------------------------------------------
Rik van Riel (5):
      x86/fpu: Add (__)make_fpregs_active helpers
      x86/fpu: Eager switch PKRU state
      x86/fpu: Always store the registers in copy_fpstate_to_sigframe()
      x86/fpu: Prepare copy_fpstate_to_sigframe() for TIF_NEED_FPU_LOAD
      x86/fpu: Defer FPU state load until return to userspace

Sebastian Andrzej Siewior (17):
      x86/fpu: Remove fpu->initialized usage in __fpu__restore_sig()
      x86/fpu: Remove fpu__restore()
      x86/fpu: Remove preempt_disable() in fpu__clear()
      x86/fpu: Always init the `state' in fpu__clear()
      x86/fpu: Remove fpu->initialized usage in copy_fpstate_to_sigframe()
      x86/fpu: Don't save fxregs for ia32 frames in copy_fpstate_to_sigframe()
      x86/fpu: Remove fpu->initialized
      x86/fpu: Remove user_fpu_begin()
      x86/fpu: Make __raw_xsave_addr() use feature number instead of mask
      x86/fpu: Make get_xsave_field_ptr() and get_xsave_addr() use feature number instead of mask
      x86/fpu: Only write PKRU if it is different from current
      x86/pkeys: Don't check if PKRU is zero before writting it
      x86/entry: Add TIF_NEED_FPU_LOAD
      x86/fpu: Update xstate's PKRU value on write_pkru()
      x86/fpu: Inline copy_user_to_fpregs_zeroing()
      x86/fpu: Let __fpu__restore_sig() restore the !32bit+fxsr frame from kernel memory
      x86/fpu: Merge the two code paths in __fpu__restore_sig()

 Documentation/preempt-locking.txt    |   1 -
 arch/x86/entry/common.c              |   8 ++
 arch/x86/ia32/ia32_signal.c          |  17 +--
 arch/x86/include/asm/fpu/api.h       |  31 ++++++
 arch/x86/include/asm/fpu/internal.h  | 151 +++++++++++---------------
 arch/x86/include/asm/fpu/signal.h    |   2 +-
 arch/x86/include/asm/fpu/types.h     |   9 --
 arch/x86/include/asm/fpu/xstate.h    |   5 +-
 arch/x86/include/asm/pgtable.h       |  20 +++-
 arch/x86/include/asm/special_insns.h |  13 ++-
 arch/x86/include/asm/thread_info.h   |   2 +
 arch/x86/include/asm/trace/fpu.h     |   8 +-
 arch/x86/kernel/fpu/core.c           | 193 ++++++++++++++++-----------------
 arch/x86/kernel/fpu/init.c           |   2 -
 arch/x86/kernel/fpu/regset.c         |  24 +---
 arch/x86/kernel/fpu/signal.c         | 205 ++++++++++++++++-------------------
 arch/x86/kernel/fpu/xstate.c         |  43 ++++----
 arch/x86/kernel/process.c            |   2 +-
 arch/x86/kernel/process_32.c         |  11 +-
 arch/x86/kernel/process_64.c         |  11 +-
 arch/x86/kernel/signal.c             |  17 ++-
 arch/x86/kernel/traps.c              |   2 +-
 arch/x86/kvm/x86.c                   |  48 +++++---
 arch/x86/math-emu/fpu_entry.c        |   3 -
 arch/x86/mm/mpx.c                    |   6 +-
 arch/x86/mm/pkeys.c                  |  14 +--
 26 files changed, 411 insertions(+), 437 deletions(-)

From patchwork Wed Jan  9 11:47:24 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: 'Sebastian Andrzej Siewior' <bigeasy@linutronix.de>
X-Patchwork-Id: 10753941
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CF16B13BF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  9 Jan 2019 11:51:14 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id BDE1028F5C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  9 Jan 2019 11:51:14 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id B211828F7F; Wed,  9 Jan 2019 11:51:14 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 36F7F28F5C
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  9 Jan 2019 11:51:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730951AbfAILsb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 9 Jan 2019 06:48:31 -0500
Received: from Galois.linutronix.de ([146.0.238.70]:56119 "EHLO
        Galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1730239AbfAILsa (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 9 Jan 2019 06:48:30 -0500
Received: from localhost ([127.0.0.1] helo=bazinga.breakpoint.cc)
        by Galois.linutronix.de with esmtp (Exim 4.80)
        (envelope-from <bigeasy@linutronix.de>)
        id 1ghCLQ-0007Al-BL; Wed, 09 Jan 2019 12:48:24 +0100
From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
To: linux-kernel@vger.kernel.org
Cc: x86@kernel.org, Andy Lutomirski <luto@kernel.org>,
 Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm@vger.kernel.org,
 "Jason A. Donenfeld" <Jason@zx2c4.com>, Rik van Riel <riel@surriel.com>,
 Dave Hansen <dave.hansen@linux.intel.com>,
 Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Subject: [PATCH 02/22] x86/fpu: Remove fpu__restore()
Date: Wed,  9 Jan 2019 12:47:24 +0100
Message-Id: <20190109114744.10936-3-bigeasy@linutronix.de>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190109114744.10936-1-bigeasy@linutronix.de>
References: <20190109114744.10936-1-bigeasy@linutronix.de>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

There are no users of fpu__restore() so it is time to remove it.
The comment regarding fpu__restore() and TS bit is stale since commit
  b3b0870ef3ffe ("i387: do not preload FPU state at task switch time")
and has no meaning since.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---
 Documentation/preempt-locking.txt   |  1 -
 arch/x86/include/asm/fpu/internal.h |  1 -
 arch/x86/kernel/fpu/core.c          | 24 ------------------------
 arch/x86/kernel/process_32.c        |  4 +---
 arch/x86/kernel/process_64.c        |  4 +---
 5 files changed, 2 insertions(+), 32 deletions(-)

```
#### [PATCH] x86/kvm/nVMX: don't skip emulated instruction twice when vmptr address is not backed
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Since commit 09abb5e3e5e50 ("KVM: nVMX: call kvm_skip_emulated_instruction
in nested_vmx_{fail,succeed}") nested_vmx_failValid() results in
kvm_skip_emulated_instruction() so doing it again in handle_vmptrld() when
vmptr address is not backed is wrong, we end up advancing RIP twice.

Fixes: fca91f6d60b6e ("kvm: nVMX: Set VM instruction error for VMPTRLD of unbacked page")
Reported-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
