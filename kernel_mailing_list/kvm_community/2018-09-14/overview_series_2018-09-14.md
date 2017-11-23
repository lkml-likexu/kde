#### [GIT PULL 1/2] s390/mm: Check for valid vma before zapping in gmap_discard
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From: Janosch Frank <frankja@linux.ibm.com>

Userspace could have munmapped the area before doing unmapping from
the gmap. This would leave us with a valid vmaddr, but an invalid vma
from which we would try to zap memory.

Let's check before using the vma.

Fixes: 1e133ab296f3 ("s390/mm: split arch/s390/mm/pgtable.c")
Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reported-by: Dan Carpenter <dan.carpenter@oracle.com>
Message-Id: <20180816082432.78828-1-frankja@linux.ibm.com>
Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/mm/gmap.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [GIT PULL] Please pull my kvm-ppc-fixes-4.19-2 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Please do a pull from my kvm-ppc-fixes-4.19-2 tag to get two commits
that should go into 4.19 because they fix host crashes and memory
corruption that can occur on POWER machines when the memory backing a
guest contains transparent huge pages.

Thanks,
Paul.

The following changes since commit bdf7ffc89922a52a4f08a12f7421ea24bb7626a0:

  KVM: LAPIC: Fix pv ipis out-of-bounds access (2018-09-07 18:38:43 +0200)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-fixes-4.19-2

for you to fetch changes up to 71d29f43b6332badc5598c656616a62575e83342:

  KVM: PPC: Book3S HV: Don't use compound_order to determine host mapping size (2018-09-12 08:50:50 +1000)

----------------------------------------------------------------
Second set of PPC KVM fixes for 4.19

Two fixes for KVM on POWER machines.  Both of these relate to memory
corruption and host crashes seen when transparent huge pages are
enabled.  The first fixes a host crash that can occur when a DMA
mapping is removed by the guest and the page mapped was part of a
transparent huge page; the second fixes corruption that could occur
when a hypervisor page fault for a radix guest is being serviced at
the same time that the backing page is being collapsed or split.

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      KVM: PPC: Avoid marking DMA-mapped pages dirty in real mode

Nicholas Piggin (1):
      KVM: PPC: Book3S HV: Don't use compound_order to determine host mapping size

 arch/powerpc/include/asm/book3s/64/pgtable.h |  1 -
 arch/powerpc/include/asm/iommu.h             |  2 -
 arch/powerpc/include/asm/mmu_context.h       |  1 +
 arch/powerpc/kernel/iommu.c                  | 25 --------
 arch/powerpc/kvm/book3s_64_mmu_radix.c       | 91 +++++++++++-----------------
 arch/powerpc/kvm/book3s_64_vio_hv.c          | 39 +++++++++---
 arch/powerpc/mm/init_64.c                    | 49 ---------------
 arch/powerpc/mm/mmu_context_iommu.c          | 34 +++++++++--
 8 files changed, 99 insertions(+), 143 deletions(-)
```
#### [PATCH 1/2] i386: Compile CPUX86State xsave_buf only when support KVM or HVF
##### From: Liran Alon <liran.alon@oracle.com>

```c
While at it, also rename var to indicate it is not used only in KVM.

Reviewed-by: Nikita Leshchenko <nikita.leshchenko@oracle.com>
Reviewed-by: Patrick Colp <patrick.colp@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 target/i386/cpu.h         | 4 +++-
 target/i386/hvf/README.md | 2 +-
 target/i386/hvf/hvf.c     | 2 +-
 target/i386/hvf/x86hvf.c  | 4 ++--
 target/i386/kvm.c         | 6 +++---
 5 files changed, 10 insertions(+), 8 deletions(-)

```
#### [PATCH v3 1/3] KVM: nVMX: Do not expose MPX VMX controls when guest MPX disabled
##### From: Liran Alon <liran.alon@oracle.com>

```c
Before this commit, KVM exposes MPX VMX controls to L1 guest only based
on if KVM and host processor supports MPX virtualization.
However, these controls should be exposed to guest only in case guest
vCPU supports MPX.

Without this change, a L1 guest running with kernel which don't have
commit 691bd4340bef ("kvm: vmx: allow host to access guest
MSR_IA32_BNDCFGS") asserts in QEMU on the following:
	qemu-kvm: error: failed to set MSR 0xd90 to 0x0
	qemu-kvm: .../qemu-2.10.0/target/i386/kvm.c:1801 kvm_put_msrs:
	Assertion 'ret == cpu->kvm_msr_buf->nmsrs failed'
This is because L1 KVM kvm_init_msr_list() will see that
vmx_mpx_supported() (As it only checks MPX VMX controls support) and
therefore KVM_GET_MSR_INDEX_LIST IOCTL will include MSR_IA32_BNDCFGS.
However, later when L1 will attempt to set this MSR via KVM_SET_MSRS
IOCTL, it will fail because !guest_cpuid_has_mpx(vcpu).

Therefore, fix the issue by exposing MPX VMX controls to L1 guest only
when vCPU supports MPX.

Fixes: 36be0b9deb23 ("KVM: x86: Add nested virtualization support for MPX")

Reported-by: Eyal Moscovici <eyal.moscovici@oracle.com>
Reviewed-by: Nikita Leshchenko <nikita.leshchenko@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx.c | 26 ++++++++++++++++++++------
 1 file changed, 20 insertions(+), 6 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: nvmx: Check #NM VM-exit reflectionFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
When L1 intercepts #NM exceptions encountered in L2, the #NM exception
should always be reflected from L0 to L1.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 lib/x86/processor.h |  1 +
 x86/unittests.cfg   |  6 +++++
 x86/vmx_tests.c     | 65 +++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 72 insertions(+)

```
#### [RFC PATCH 04/10 v2 ] x86/fpu: eager switch PKRU state
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
While most of a task's FPU state is only needed in user space,
the protection keys need to be in place immediately after a
context switch.

The reason is that any accesses to userspace memory while running
in kernel mode also need to abide by the memory permissions
specified in the protection keys.

The pkru info is put in its own cache line in the fpu struct because
that cache line is accessed anyway at context switch time.
Remove XFEATURE_MASK_PKRU from supported flags. This removes the PKRU
state from XSAVE/XRESTORE and so decouples it from the FPU state.

The initial state of pkru is updated in pkru_set_init_value() via
fpu__clear() - it is no longer affected by fpstate_init().

Signed-off-by: Rik van Riel <riel@surriel.com>
[bigeasy: load PKRU state only if we also load FPU content]
Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---

v1…v2: remove PKRU from xsave/srestore.

On 2018-09-12 16:18:44 [+0200], Paolo Bonzini wrote:

> I think you can go a step further and exclude PKRU state from
> copy_kernel_to_fpregs altogether; you just use RDPKRU/WRPKRU.  This also
> means you don't need to call __fpregs_* functions in write_pkru.

something like this then? It looks like kvm excludes PKRU from
xsave/xrestore, too. This wouldn't be required then. This is (again)
untested since I have no box with this PKRU feature. This only available
on Intel's Xeon Scalable, right?

> Thanks,
> 
> Paolo

 arch/x86/include/asm/fpu/internal.h | 14 ++++++++++++--
 arch/x86/include/asm/fpu/types.h    |  7 +++++++
 arch/x86/include/asm/fpu/xstate.h   |  1 -
 arch/x86/include/asm/pgtable.h      |  7 +++++--
 arch/x86/include/asm/pkeys.h        |  2 +-
 arch/x86/kernel/fpu/core.c          |  2 +-
 arch/x86/kernel/fpu/xstate.c        |  4 ----
 arch/x86/mm/pkeys.c                 | 21 ++++-----------------
 include/linux/pkeys.h               |  2 +-
 9 files changed, 31 insertions(+), 29 deletions(-)

```
#### [PATCH] vfio/mdev: fix missed mdev free in mdev_device_create() error path
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
Add mdev kfree in mdev_device_create() error path which seems
to be ignored.

Fixes: 7b96953bc640 ("vfio: Mediated device Core driver")
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Kirti Wankhede <kwankhede@nvidia.com>
Signed-off-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
 drivers/vfio/mdev/mdev_core.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH v9 1/2] x86/mm: add .bss..decrypted section to hold shared variables
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
kvmclock defines few static variables which are shared with the
hypervisor during the kvmclock initialization.

When SEV is active, memory is encrypted with a guest-specific key, and
if the guest OS wants to share the memory region with the hypervisor
then it must clear the C-bit before sharing it.

Currently, we use kernel_physical_mapping_init() to split large pages
before clearing the C-bit on shared pages. But it fails when called from
the kvmclock initialization (mainly because the memblock allocator is
not ready that early during boot).

Add a __bss_decrypted section attribute which can be used when defining
such shared variable. The so-defined variables will be placed in the
.bss..decrypted section. This section will be mapped with C=0 early
during boot.

The .bss..decrypted section has a big chunk of memory that may be unused
when memory encryption is not active, free it when memory encryption is
not active.

Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Suggested-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: kvm@vger.kernel.org
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@suse.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
---
 arch/x86/include/asm/mem_encrypt.h |  7 +++++++
 arch/x86/kernel/head64.c           | 16 ++++++++++++++++
 arch/x86/kernel/vmlinux.lds.S      | 19 +++++++++++++++++++
 arch/x86/mm/init.c                 |  4 ++++
 arch/x86/mm/mem_encrypt.c          | 24 ++++++++++++++++++++++++
 5 files changed, 70 insertions(+)

```
