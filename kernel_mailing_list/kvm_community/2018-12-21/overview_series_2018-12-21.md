#### [GIT PULL] Last straggler for 4.20-rc8 or final
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 7566ec393f4161572ba6f11ad5171fd5d59b0fbd:

  Linux 4.20-rc7 (2018-12-16 15:46:55 -0800)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 3cf85f9f6bd7b172122865432b4c6f0ec844e22a:

  KVM: x86: nSVM: fix switch to guest mmu (2018-12-19 22:19:22 +0100)

A simple patch for a pretty bad bug.  I haven't yet sent my 4.21 pull
request because currently I'm waiting for a patch to be removed from
tip (MPX removal breaks KVM live migration and was committed without
Cc or Ack from me) and until that happens I cannot finalize my
conflict resolution instructions.

With the vacation coming soon, I'm not sure whether Ingo or Thomas have
seen my messages about it, so I'll take a couple hours next week to
package everything.  Anyway, all pull requests from my submaintainers
have come and I'll try to sort this out as soon as the 27th or 28th.

Thanks,

Paolo


----------------------------------------------------------------
Unbreak AMD nested virtualization.

----------------------------------------------------------------
Vitaly Kuznetsov (1):
      KVM: x86: nSVM: fix switch to guest mmu

 arch/x86/kvm/svm.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)
```
#### [GIT PULL] Please pull my kvm-ppc-next-4.21-2 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Thanks for pulling the previous set of commits for 4.21.  Suraj
Jitindar Singh has just fixed several bugs in the page dirty tracking
for nested guests, and it seems worth while to try to get his series
in for 4.21.  So please do a pull from my tree again to get this patch
series.

Thanks,
Paul.

The following changes since commit 95d386c2d2e7660a6447df1507a9845665dab7d8:

  KVM: PPC: Book3S HV: Allow passthrough of an emulated device to an L3 guest (2018-12-17 11:33:50 +1100)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-4.21-2

for you to fetch changes up to ae59a7e1945bc2245bbb587071ca737e00daf443:

  KVM: PPC: Book3S HV: Keep rc bits in shadow pgtable in sync with host (2018-12-21 14:42:07 +1100)

----------------------------------------------------------------
Second PPC KVM update for 4.21

This has 5 commits that fix page dirty tracking when running nested
HV KVM guests, from Suraj Jitindar Singh.

----------------------------------------------------------------
Suraj Jitindar Singh (5):
      KVM: PPC: Book3S HV: Hold kvm->mmu_lock across updating nested pte rc bits
      KVM: PPC: Book3S HV: Align gfn to L1 page size when inserting nest-rmap entry
      KVM: PPC: Book3S HV: Apply combination of host and l1 pte rc for nested guest
      KVM: PPC: Book3S HV: Introduce kvmhv_update_nest_rmap_rc_list()
      KVM: PPC: Book3S HV: Keep rc bits in shadow pgtable in sync with host

 arch/powerpc/include/asm/kvm_book3s.h    |  2 +
 arch/powerpc/include/asm/kvm_book3s_64.h |  3 ++
 arch/powerpc/kvm/book3s_64_mmu_radix.c   | 26 ++++++++---
 arch/powerpc/kvm/book3s_hv_nested.c      | 74 +++++++++++++++++++++++++++++---
 4 files changed, 93 insertions(+), 12 deletions(-)
```
#### [GIT PULL] VFIO updates for v4.21-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Hi Linus,

An early pull request for the next merge window.  Happy holidays!

The following changes since commit 40e020c129cfc991e8ab4736d2665351ffd1468d:

  Linux 4.20-rc6 (2018-12-09 15:31:00 -0800)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v4.21-rc1

for you to fetch changes up to 8ba35b3a0046d6573c98f00461d9bd1b86250d35:

  vfio-mdev/samples: Use u8 instead of char for handle functions (2018-12-17 11:07:13 -0700)

----------------------------------------------------------------
VFIO updates for v4.21

 - Replace global vfio-pci lock with per bus lock to allow concurrent
   open and release (Alex Williamson)

 - Declare mdev function as static (Paolo Cretaro)

 - Convert char to u8 in mdev/mtty sample driver (Nathan Chancellor)

----------------------------------------------------------------
Alex Williamson (1):
      vfio/pci: Parallelize device open and release

Nathan Chancellor (1):
      vfio-mdev/samples: Use u8 instead of char for handle functions

Paolo Cretaro (1):
      vfio/mdev: add static modifier to add_mdev_supported_type

 drivers/vfio/mdev/mdev_sysfs.c      |   4 +-
 drivers/vfio/pci/vfio_pci.c         | 160 ++++++++++++++++++++++++++++++------
 drivers/vfio/pci/vfio_pci_private.h |   6 ++
 samples/vfio-mdev/mtty.c            |  26 +++---
 4 files changed, 157 insertions(+), 39 deletions(-)
```
#### [PATCH 1/5] KVM: PPC: Book3S HV: Hold kvm->mmu_lock across updating nested pte rc bits
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
We already hold the kvm->mmu_lock spin lock across updating the rc bits
in the pte for the L1 guest. Continue to hold the lock across updating
the rc bits in the pte for the nested guest as well to prevent
invalidations from occurring.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---
 arch/powerpc/kvm/book3s_hv_nested.c | 18 ++++++++++++------
 1 file changed, 12 insertions(+), 6 deletions(-)

```
#### [PATCH v4.9 STABLE] x86/fpu: Disable bottom halves while loading FPU registers
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
The sequence

  fpu->initialized = 1;		/* step A */
  preempt_disable();		/* step B */
  fpu__restore(fpu);
  preempt_enable();

in __fpu__restore_sig() is racy in regard to a context switch.

For 32bit frames, __fpu__restore_sig() prepares the FPU state within
fpu->state. To ensure that a context switch (switch_fpu_prepare() in
particular) does not modify fpu->state it uses fpu__drop() which sets
fpu->initialized to 0.

After fpu->initialized is cleared, the CPU's FPU state is not saved
to fpu->state during a context switch. The new state is loaded via
fpu__restore(). It gets loaded into fpu->state from userland and
ensured it is sane. fpu->initialized is then set to 1 in order to avoid
fpu__initialize() doing anything (overwrite the new state) which is part
of fpu__restore().

A context switch between step A and B above would save CPU's current FPU
registers to fpu->state and overwrite the newly prepared state. This
looks like a tiny race window but the Kernel Test Robot reported this
back in 2016 while we had lazy FPU support. Borislav Petkov made the
link between that report and another patch that has been posted. Since
the removal of the lazy FPU support, this race goes unnoticed because
the warning has been removed.

Disable bottom halves around the restore sequence to avoid the race. BH
need to be disabled because BH is allowed to run (even with preemption
disabled) and might invoke kernel_fpu_begin() by doing IPsec.

 [ bp: massage commit message a bit. ]

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Acked-by: Ingo Molnar <mingo@kernel.org>
Acked-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Rik van Riel <riel@surriel.com>
Cc: stable@vger.kernel.org
Cc: x86-ml <x86@kernel.org>
Link: http://lkml.kernel.org/r/20181120102635.ddv3fvavxajjlfqk@linutronix.de
Link: https://lkml.kernel.org/r/20160226074940.GA28911@pd.tnic
Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---
 arch/x86/kernel/fpu/signal.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
