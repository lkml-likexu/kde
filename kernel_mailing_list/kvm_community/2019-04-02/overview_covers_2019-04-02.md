

#### [PATCH 0/3] KVM: x86: clear HF_SMM_MASK before loading state
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

RSM emulation is currently broken on VMX when the interrupted guest has
CR4.VMXE=1.  Similar breakage has also occurred in the past due to
HF_SMM_MASK being cleared only after RSM completes, i.e. loading non-SMM
state while is_smm() returns true is unsurprisingly problematic.

Rather than dance around the issue of HF_SMM_MASK being set when loading
SMSTATE into architectural state, rework RSM emulation itself to clear
HF_SMM_MASK prior to loading architectural state.   AFAICT, the only
motivation for having HF_SMM_MASK set throughout is so that the memory
access from GET_SMSTATE() are tagged with role.smm (though arguably even
that is unnecessary).  Sidestep that particular issue by taking the
enter_smm() approach of reading all of SMSTATE into a buffer and then
loading state from the buffer.

The actual fix is the same concept as an earlier RFC, but without first
moving em_rsm() to x86.c, i.e. doesn't add a big pile of dependent patches
before fixing the bug.  I'm still planning on sending a series to move
the bulk of em_rsm() to x86.c, but it'll be a true cleanup.

[1] https://patchwork.kernel.org/cover/10875623/

Sean Christopherson (3):
  KVM: x86: Load SMRAM in a single shot when leaving SMM
  KVM: x86: Open code kvm_set_hflags
  KVM: x86: clear SMM flags before loading state while leaving SMM

 arch/x86/include/asm/kvm_emulate.h |   4 +-
 arch/x86/include/asm/kvm_host.h    |   5 +-
 arch/x86/kvm/emulate.c             | 160 +++++++++++++++--------------
 arch/x86/kvm/svm.c                 |  30 ++----
 arch/x86/kvm/vmx/vmx.c             |   4 +-
 arch/x86/kvm/x86.c                 |  38 ++++---
 6 files changed, 118 insertions(+), 123 deletions(-)
```
#### [PATCH 0/2] KVM: x86: Fix SMM bugs for 32-bit guests/hosts
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

Fix two tangentially related bugs that manifest when the guest's long
mode capabilities diverges from the host kernel's support, i.e. a 32-bit
vCPU running under 64-bit KVM, or a (not-actually-supported) 64-bit vCPU
running under 32-bit KVM.

Sean Christopherson (2):
  KVM: x86: Don't clear EFER during SMM transitions for 32-bit vCPU
  KVM: x86: Always use 32-bit SMRAM save state for 32-bit kernels

 arch/x86/kvm/emulate.c | 31 +++++++++++++++++++++----------
 arch/x86/kvm/x86.c     | 10 ++++++----
 2 files changed, 27 insertions(+), 14 deletions(-)
```
#### [PATCH 0/2] KVM: x86: Enforce EFER bits according to CPUID
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

KVM currently doesn't prevent the guest from setting EFER bits that
should be reserved based on the guest's CPUID model.  For example, a
64-bit guest kernel can set EFER.LME and enter long mode even if userspace
reports X86_FEATURE_LM=0 for its guest.

Sean Christopherson (2):
  KVM: x86: Skip EFER vs. guest CPUID checks for host-initiated writes
  KVM: x86: Inject #GP if guest attempts to set unsupported EFER bits

 arch/x86/kvm/x86.c | 44 +++++++++++++++++++++++++++++++-------------
 1 file changed, 31 insertions(+), 13 deletions(-)
```
#### [RFC v1 0/3] vfio-ccw fixes for kernel stacktraces
##### From: Farhan Ali <alifm@linux.ibm.com>

```c

Hi,

I have recently seen some interesting kernel stacktraces while
testing vfio-ccw mediated devices. These stack traces are seen
when things don't go right, for example when a guest crashes or
dies while still doing some I/O on the mediated device.

I have also come across an issue in the common vfio code as
well which I reported upstream (https://marc.info/?l=kvm&m=155369393523503&w=2)
and submitted a patch separately for it 
(https://marc.info/?l=kvm&m=155414703613868&w=2).

I would appreciate any review or feedback on these patches.

Thanks
Farhan


Farhan Ali (3):
  vfio-ccw: Do not call flush_workqueue while holding the spinlock
  vfio-ccw: Prevent quiesce function going into an infinite loop
  vfio-ccw: Release any channel program when releasing/removing vfio-ccw
    mdev

 drivers/s390/cio/vfio_ccw_drv.c | 28 ++++++++++++----------------
 drivers/s390/cio/vfio_ccw_ops.c |  9 +++++++++
 2 files changed, 21 insertions(+), 16 deletions(-)
```
#### [PATCH 0/6] convert locked_vm from unsigned long to atomic64_t
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c

Hi,

From patch 1:

  Taking and dropping mmap_sem to modify a single counter, locked_vm, is
  overkill when the counter could be synchronized separately.
  
  Make mmap_sem a little less coarse by changing locked_vm to an atomic,
  the 64-bit variety to avoid issues with overflow on 32-bit systems.

This is a more conservative alternative to [1] with no user-visible
effects.  Thanks to Alexey Kardashevskiy for pointing out the racy
atomics and to Alex Williamson, Christoph Lameter, Ira Weiny, and Jason
Gunthorpe for their comments on [1].

Davidlohr Bueso recently did a similar conversion for pinned_vm[2].

Testing
 1. passes LTP mlock[all], munlock[all], fork, mmap, and mremap tests in an
    x86 kvm guest
 2. a VFIO-enabled x86 kvm guest shows the same VmLck in
    /proc/pid/status before and after this change
 3. cross-compiles on powerpc

The series is based on v5.1-rc3.  Please consider for 5.2.

Daniel

[1] https://lore.kernel.org/linux-mm/20190211224437.25267-1-daniel.m.jordan@oracle.com/
[2] https://lore.kernel.org/linux-mm/20190206175920.31082-1-dave@stgolabs.net/

Daniel Jordan (6):
  mm: change locked_vm's type from unsigned long to atomic64_t
  vfio/type1: drop mmap_sem now that locked_vm is atomic
  vfio/spapr_tce: drop mmap_sem now that locked_vm is atomic
  fpga/dlf/afu: drop mmap_sem now that locked_vm is atomic
  powerpc/mmu: drop mmap_sem now that locked_vm is atomic
  kvm/book3s: drop mmap_sem now that locked_vm is atomic

 arch/powerpc/kvm/book3s_64_vio.c    | 34 ++++++++++--------------
 arch/powerpc/mm/mmu_context_iommu.c | 28 +++++++++-----------
 drivers/fpga/dfl-afu-dma-region.c   | 40 ++++++++++++-----------------
 drivers/vfio/vfio_iommu_spapr_tce.c | 37 ++++++++++++--------------
 drivers/vfio/vfio_iommu_type1.c     | 31 +++++++++-------------
 fs/proc/task_mmu.c                  |  2 +-
 include/linux/mm_types.h            |  2 +-
 kernel/fork.c                       |  2 +-
 mm/debug.c                          |  5 ++--
 mm/mlock.c                          |  4 +--
 mm/mmap.c                           | 18 ++++++-------
 mm/mremap.c                         |  6 ++---
 12 files changed, 89 insertions(+), 120 deletions(-)


base-commit: 79a3aaa7b82e3106be97842dedfd8429248896e6
```
