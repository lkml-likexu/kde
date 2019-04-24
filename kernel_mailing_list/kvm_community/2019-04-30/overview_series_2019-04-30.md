#### [PATCH v14 01/17] uaccess: add untagged_addr definition for other arches
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
To allow arm64 syscalls to accept tagged pointers from userspace, we must
untag them when they are passed to the kernel. Since untagging is done in
generic parts of the kernel, the untagged_addr macro needs to be defined
for all architectures.

Define it as a noop for architectures other than arm64.

Acked-by: Catalin Marinas <catalin.marinas@arm.com>
Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
---
 include/linux/mm.h | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH 4.19 083/100] x86/fpu: Dont export __kernel_fpu_{begin,end}()
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

commit 12209993e98c5fa1855c467f22a24e3d5b8be205 upstream.

There is one user of __kernel_fpu_begin() and before invoking it,
it invokes preempt_disable(). So it could invoke kernel_fpu_begin()
right away. The 32bit version of arch_efi_call_virt_setup() and
arch_efi_call_virt_teardown() does this already.

The comment above *kernel_fpu*() claims that before invoking
__kernel_fpu_begin() preemption should be disabled and that KVM is a
good example of doing it. Well, KVM doesn't do that since commit

  f775b13eedee2 ("x86,kvm: move qemu/guest FPU switching out to vcpu_run")

so it is not an example anymore.

With EFI gone as the last user of __kernel_fpu_{begin|end}(), both can
be made static and not exported anymore.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Reviewed-by: Rik van Riel <riel@surriel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Ard Biesheuvel <ard.biesheuvel@linaro.org>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Nicolai Stange <nstange@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: linux-efi <linux-efi@vger.kernel.org>
Cc: x86-ml <x86@kernel.org>
Link: https://lkml.kernel.org/r/20181129150210.2k4mawt37ow6c2vq@linutronix.de
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 arch/x86/include/asm/efi.h     |    6 ++----
 arch/x86/include/asm/fpu/api.h |   15 +++++----------
 arch/x86/kernel/fpu/core.c     |    6 ++----
```
#### [PATCH] KVM: PPC: Book3S HV: Save/restore vrsave register in kvmhv_p9_guest_entry()
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
On POWER9 and later processors where the host can schedule vcpus on a
per thread basis, there is a streamlined entry path used when the guest
is radix. This entry path saves/restores the fp and vr state in
kvmhv_p9_guest_entry() by calling store_[fp/vr]_state() and
load_[fp/vr]_state(). This is the same as the old entry path however the
old entry path also saved/restored the VRSAVE register, which isn't done
in the new entry path.

This means that the vrsave register is now volatile across guest exit,
which is an incorrect change in behaviour.

Fix this by saving/restoring the vrsave register in kvmhv_p9_guest_entry().
This restores the old, correct, behaviour.

Fixes: 95a6432ce9038 ("KVM: PPC: Book3S HV: Streamlined guest entry/exit path on P9 for radix guests")

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/book3s_hv.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: Change ALTERNATE_APIC_BASE to saner value
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

According to the SDM, during initialization, the BSP "Switches to
protected mode and ensures that the APIC address space is mapped to the
strong uncacheable (UC) memory type." This requirement is not followed
when the tests that relocate the APIC.

Use the TPM base address for the alternate local-APIC base, as it is
expected to be set as uncacheable by the BIOS.

Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/apic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] x86: Disable cache before relocating local APIC
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

According to the SDM, during initialization, the BSP "Switches to
protected mode and ensures that the APIC address space is mapped to the
strong uncacheable (UC) memory type."

This requirement is not followed when the tests relocate the APIC. Set
the cache-disable flag while the APIC base is reprogrammed. According
to the SDM, the MTRRs should be modified as well, but it seems somewhat
complicated to do that and probably unnecessary.

Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 lib/x86/processor.h | 1 +
 x86/apic.c          | 7 +++++++
 2 files changed, 8 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: Fix APIC version register test
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

The local APIC existance test considers reserved bits (bits [8:15]),
which is not good. In addition, it is best to consider every integrated
APIC version as valid.

Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/apic.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH 1/3] KVM: x86: Omit caching logic for always-available GPRs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Except for RSP and RIP, which are held in VMX's VMCS, GPRs are always
treated "available and dirtly" on both VMX and SVM, i.e. are
unconditionally loaded/saved immediately before/after VM-Enter/VM-Exit.

Eliminating the unnecessary caching code reduces the size of KVM by a
non-trivial amount, much of which comes from the most common code paths.
E.g. on x86_64, kvm_emulate_cpuid() is reduced from 342 to 182 bytes and
kvm_emulate_hypercall() from 1362 to 1143, with the total size of KVM
dropping by ~1000 bytes.  With CONFIG_RETPOLINE=y, the numbers are even
more pronounced, e.g.: 353->182, 1418->1172 and well over 2000 bytes.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---

As an added bonus, this also gave me a legitimate way to get rid of the
funky wrapping of ": 0;" in complete_fast_pio_in(), which is probably my
favorite part of this patch.  ;-)

 arch/x86/kvm/cpuid.c          | 12 ++---
 arch/x86/kvm/hyperv.c         | 24 +++++-----
 arch/x86/kvm/kvm_cache_regs.h | 32 ++++++++++++-
 arch/x86/kvm/svm.c            | 26 +++++-----
 arch/x86/kvm/vmx/vmx.c        |  2 +-
 arch/x86/kvm/x86.c            | 89 +++++++++++++++++------------------
 6 files changed, 105 insertions(+), 80 deletions(-)

```
#### [PATCH] KVM: x86: revert the order of calls in kvm_fast_pio()
##### From: Perr Zhang <strongbox8@zoho.com>

```c
In commit 45def77ebf79, the order of function calls in kvm_fast_pio()
was changed. This causes that the vm(XP,and also XP's iso img) failed
to boot. This doesn't happen with win10 or ubuntu.

After revert the order, the vm(XP) succeedes to boot. In addition, the
change of calls's order of kvm_fast_pio() in commit 45def77ebf79 has no
obvious reason.

Fixes: 45def77ebf79 ("KVM: x86: update %rip after emulating IO")
Cc: <stable@vger.kernel.org>
Signed-off-by: Perr Zhang <strongbox8@zoho.com>
---
 arch/x86/kvm/x86.c | 7 +++----
 1 file changed, 3 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: revert the order of calls in kvm_fast_pio()
##### From: Perr Zhang <strongbox8@zoho.com>

```c
In commit 45def77ebf79, the order of function calls in kvm_fast_pio()
was changed. This causes that the vm(XP,and also XP's iso img) failed
to boot. This doesn't happen with win10 or ubuntu.

After revert the order, the vm(XP) succeedes to boot. In addition, the
change of calls's order of kvm_fast_pio() in commit 45def77ebf79 has no
obvious reason.

Fixes: 45def77ebf79 ("KVM: x86: update %rip after emulating IO")
Cc: <stable@vger.kernel.org>
Signed-off-by: Perr Zhang <strongbox8@zoho.com>
---
 arch/x86/kvm/x86.c | 7 +++----
 1 file changed, 3 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: use direct accessors for RIP and RSP
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Use specific inline functions for RIP and RSP instead of
going through kvm_register_read and kvm_register_write,
which are quite a mouthful.  kvm_rsp_read and kvm_rsp_write
did not exist, so add them.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/kvm_cache_regs.h | 10 ++++++++++
 arch/x86/kvm/svm.c            |  8 ++++----
 arch/x86/kvm/vmx/nested.c     | 12 ++++++------
 arch/x86/kvm/x86.c            |  4 ++--
 4 files changed, 22 insertions(+), 12 deletions(-)

```
#### [PATCH v2] KVM: PPC: Book3S HV: Fix XICS-on-XIVE H_IPI when priority = 0
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
This fixes a bug in the XICS emulation on POWER9 machines which is
triggered by the guest doing a H_IPI with priority = 0 (the highest
priority).  What happens is that the notification interrupt arrives
at the destination at priority zero.  The loop in scan_interrupts()
sees that a priority 0 interrupt is pending, but because xc->mfrr is
zero, we break out of the loop before taking the notification
interrupt out of the queue and EOI-ing it.  (This doesn't happen
when xc->mfrr != 0; in that case we process the priority-0 notification
interrupt on the first iteration of the loop, and then break out of
a subsequent iteration of the loop with hirq == XICS_IPI.)

To fix this, we move the prio >= xc->mfrr check down to near the end
of the loop.  However, there are then some other things that need to
be adjusted.  Since we are potentially handling the notification
interrupt and also delivering an IPI to the guest in the same loop
iteration, we need to update pending and handle any q->pending_count
value before the xc->mfrr check, rather than at the end of the loop.
Also, we need to update the queue pointers when we have processed and
EOI-ed the notification interrupt, since we may not do it later.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
v2: add check for xc->mfrr < xc->cppr in the first prio >= xc->cppr test

 arch/powerpc/kvm/book3s_xive_template.c | 78 +++++++++++++++++----------------
 1 file changed, 40 insertions(+), 38 deletions(-)

```
#### [PATCHv2 01/10] vfio/mdev: Avoid release parent reference during error path
##### From: Parav Pandit <parav@mellanox.com>

```c
During mdev parent registration in mdev_register_device(),
if parent device is duplicate, it releases the reference of existing
parent device.
This is incorrect. Existing parent device should not be touched.

Fixes: 7b96953bc640 ("vfio: Mediated device Core driver")
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed By: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Maxim Levitsky <mlevitsk@redhat.com>
Signed-off-by: Parav Pandit <parav@mellanox.com>
---
 drivers/vfio/mdev/mdev_core.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] x86/fpu: Remove unneeded saving of FPU registers in copy_fpstate_to_sigframe()
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
Since commit

  eeec00d73be2e ("x86/fpu: Fault-in user stack if copy_fpstate_to_sigframe() fails")

there is no need to have FPU registers saved if
copy_fpregs_to_sigframe() fails because we retry it after we resolved
the fault condition.
Saving the registers is not wrong but it is not needed and it forces us
to load the FPU registers on the retry attempt.

Don't save the FPU registers if copy_fpstate_to_sigframe() fails.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---
 arch/x86/kernel/fpu/signal.c | 6 +-----
 1 file changed, 1 insertion(+), 5 deletions(-)

```
#### [PATCH] x86/kvm/mmu: reset MMU context when 32-bit guest switches PAE
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Commit 47c42e6b4192 ("KVM: x86: fix handling of role.cr4_pae and rename it
to 'gpte_size'") introduced a regression: 32-bit PAE guests stopped
working. The issue appears to be: when guest switches (enables) PAE we need
to re-initialize MMU context (set context->root_level, do
reset_rsvds_bits_mask(), ...) but init_kvm_tdp_mmu() doesn't do that
because we threw away is_pae(vcpu) flag from mmu role. Restore it to
kvm_mmu_extended_role (as we now don't need it in base role) to fix
the issue.

Fixes: 47c42e6b4192 ("KVM: x86: fix handling of role.cr4_pae and rename it to 'gpte_size'")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
- RFC: it was proven multiple times that mmu code is more complex than it
  appears (at least to me) :-)
---
 arch/x86/include/asm/kvm_host.h | 1 +
 arch/x86/kvm/mmu.c              | 1 +
 2 files changed, 2 insertions(+)

```
