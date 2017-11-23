#### [PATCH 01/29] x86/fpu: Use ULL for shift in xfeature_uncompacted_offset()
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
The xfeature mask is 64bit so a shift from a number to its mask should
have LL prefix or else nr > 31 will be lost. This is not a problem now
but should XFEATURE_MASK_SUPERVISOR gain a bit >31 then this check won't
catch it.

Use BIT_ULL() to compute a mask from a number.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Reviewed-by: Rik van Riel <riel@surriel.com>
---
 arch/x86/kernel/fpu/xstate.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [GIT PULL] KVM fixes for 4.20-rc4
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 9ff01193a20d391e8dbce4403dd5ef87c7eaaca6:

  Linux 4.20-rc3 (2018-11-18 13:33:44 -0800)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to fd65d3142f734bc4376053c8d75670041903134d:

  kvm: svm: Ensure an IBPB on all affected CPUs when freeing a vmcb (2018-11-27 12:50:42 +0100)

----------------------------------------------------------------
Bugfixes, many of them reported by syzkaller and mostly predating the
merge window.

----------------------------------------------------------------
Jim Mattson (1):
      kvm: svm: Ensure an IBPB on all affected CPUs when freeing a vmcb

Junaid Shahid (1):
      kvm: mmu: Fix race in emulated page table writes

Leonid Shatz (1):
      KVM: nVMX/nSVM: Fix bug which sets vcpu->arch.tsc_offset to L1 tsc_offset

Liran Alon (5):
      KVM: nVMX: Fix kernel info-leak when enabling KVM_CAP_HYPERV_ENLIGHTENED_VMCS more than once
      KVM: x86: Fix kernel info-leak in KVM_HC_CLOCK_PAIRING hypercall
      KVM: VMX: Update shared MSRs to be saved/restored on MSR_EFER.LMA changes
      KVM: nVMX: Verify eVMCS revision id match supported eVMCS version on eVMCS VMPTRLD
      KVM: nVMX: vmcs12 revision_id is always VMCS12_REVISION even when copied from eVMCS

Luiz Capitulino (1):
      KVM: VMX: re-add ple_gap module parameter

Michael Roth (1):
      KVM: PPC: Book3S HV: Fix handling for interrupted H_ENTER_NESTED

Paolo Bonzini (1):
      Merge tag 'kvm-ppc-fixes-4.20-1' of https://git.kernel.org/.../paulus/powerpc into HEAD

Wanpeng Li (2):
      KVM: LAPIC: Fix pv ipis use-before-initialization
      KVM: X86: Fix scan ioapic use-before-initialization

Wei Wang (1):
      svm: Add mutex_lock to protect apic_access_page_done on AMD systems

Yi Wang (2):
      KVM: x86: fix empty-body warnings
      x86/kvm/vmx: fix old-style function declaration

 arch/powerpc/kvm/book3s_hv.c    |  1 +
 arch/x86/include/asm/kvm_host.h |  3 +-
 arch/x86/kvm/lapic.c            |  7 ++-
 arch/x86/kvm/mmu.c              | 27 ++++--------
 arch/x86/kvm/svm.c              | 44 +++++++++++-------
 arch/x86/kvm/vmx.c              | 98 +++++++++++++++++++++++++++--------------
 arch/x86/kvm/x86.c              | 10 +++--
 7 files changed, 118 insertions(+), 72 deletions(-)
```
#### [PATCH v3 01/12] KVM: s390: unregister debug feature on failing arch init
##### From: Michael Mueller <mimu@linux.ibm.com>

```c
Make sure the debug feature and its allocated resources get
released upon unsuccessful architecture initialization.

A related idication of the issue will be reported by common
kvm code.

Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Pierre Morel<pmorel@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 16 +++++++++++++---
 1 file changed, 13 insertions(+), 3 deletions(-)

```
#### [PATCH 1/3] kvm: make KVM_CAP_ENABLE_CAP_VM architecture agnostic
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
The first such capability to be handled in virt/kvm/ will be manual
dirty page reprotection.

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virtual/kvm/api.txt | 13 +++++++++----
 arch/powerpc/kvm/powerpc.c        | 14 ++------------
 arch/s390/kvm/kvm-s390.c          | 11 +----------
 arch/x86/kvm/x86.c                | 14 ++------------
 include/linux/kvm_host.h          |  2 ++
 virt/kvm/kvm_main.c               | 25 +++++++++++++++++++++++++
 6 files changed, 41 insertions(+), 38 deletions(-)

```
#### [PATCH v3 1/6] vfio: ccw: Register mediated device once all structures are initialized
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
There is a risk that the mediated device is used before all the
data are initialized if it is registered too early.

Let's register the mediated device when all the data structures
which could be used are initialized.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_drv.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
