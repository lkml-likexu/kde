#### [GIT PULL] KVM changes for Linux 4.19-rc5
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Greg,

The following changes since commit 7876320f88802b22d4e2daf7eb027dd14175a0f8:

  Linux 4.19-rc4 (2018-09-16 11:52:37 -0700)

are available in the git repository at:

  git://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 26b471c7e2f7befd0f59c35b257749ca57e0ed70:

  KVM: nVMX: Fix bad cleanup on error of get/set nested state IOCTLs (2018-09-20 18:54:08 +0200)

----------------------------------------------------------------
This pull request is slightly bigger than usual at this stage, but
I swear I would have sent it the same to Linus!  The main cause for
this is that I was on vacation until two weeks ago and it took a while
to sort all the pending patches between 4.19 and 4.20, test them and
so on.

It's mostly small bugfixes and cleanups, mostly around x86 nested
virtualization.  One important change, not related to nested
virtualization, is that the ability for the guest kernel to trap CPUID
instructions (in Linux that's the ARCH_SET_CPUID arch_prctl) is now
masked by default.  This is because the feature is detected through an
MSR; a very bad idea that Intel seems to like more and more.  Some
applications choke if the other fields of that MSR are not initialized
as on real hardware, hence we have to disable the whole MSR by default,
as was the case before Linux 4.12.

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      KVM: PPC: Avoid marking DMA-mapped pages dirty in real mode

Andy Shevchenko (1):
      KVM: SVM: Switch to bitmap_zalloc()

Drew Schmitt (3):
      KVM: x86: Turbo bits in MSR_PLATFORM_INFO
      KVM: x86: Control guest reads of MSR_PLATFORM_INFO
      kvm: selftests: Add platform_info_test

Janosch Frank (2):
      s390/mm: Check for valid vma before zapping in gmap_discard
      KVM: s390: Make huge pages unavailable in ucontrol VMs

Junaid Shahid (1):
      kvm: mmu: Don't read PDPTEs when paging is not enabled

Krish Sadhukhan (2):
      nVMX x86: check posted-interrupt descriptor addresss on vmentry of L2
      nVMX x86: Check VPID value on vmentry of L2 guests

Lei Yang (1):
      kvm: selftests: use -pthread instead of -lpthread

Liran Alon (2):
      KVM: nVMX: Wake blocked vCPU in guest-mode if pending interrupt in virtual APICv
      KVM: nVMX: Fix bad cleanup on error of get/set nested state IOCTLs

Nicholas Piggin (1):
      KVM: PPC: Book3S HV: Don't use compound_order to determine host mapping size

Paolo Bonzini (3):
      Merge tag 'kvm-s390-master-4.19-2' of git://git.kernel.org/.../kvms390/linux into HEAD
      Merge tag 'kvm-ppc-fixes-4.19-2' of git://git.kernel.org/.../paulus/powerpc into HEAD
      KVM: VMX: check nested state and CR4.VMXE against SMM

Sean Christopherson (3):
      KVM: VMX: immediately mark preemption timer expired only for zero value
      KVM: VMX: modify preemption timer bit only when arming timer
      KVM: VMX: use preemption timer to force immediate VMExit

Sebastian Andrzej Siewior (1):
      kvm: x86: make kvm_{load|put}_guest_fpu() static

Tianyu Lan (1):
      KVM/MMU: Fix comment in walk_shadow_page_lockless_end()

Vitaly Kuznetsov (2):
      x86/kvm/lapic: always disable MMIO interface in x2APIC mode
      x86/hyper-v: rename ipi_arg_{ex,non_ex} structures

Wei Yang (1):
      KVM: x86: don't reset root in kvm_mmu_setup()

 Documentation/virtual/kvm/api.txt                |  12 +-
 arch/powerpc/include/asm/book3s/64/pgtable.h     |   1 -
 arch/powerpc/include/asm/iommu.h                 |   2 -
 arch/powerpc/include/asm/mmu_context.h           |   1 +
 arch/powerpc/kernel/iommu.c                      |  25 ----
 arch/powerpc/kvm/book3s_64_mmu_radix.c           |  91 ++++++---------
 arch/powerpc/kvm/book3s_64_vio_hv.c              |  39 +++++--
 arch/powerpc/mm/init_64.c                        |  49 --------
 arch/powerpc/mm/mmu_context_iommu.c              |  34 +++++-
 arch/s390/kvm/kvm-s390.c                         |   4 +-
 arch/s390/mm/gmap.c                              |   4 +-
 arch/x86/hyperv/hv_apic.c                        |   8 +-
 arch/x86/include/asm/hyperv-tlfs.h               |  16 +--
 arch/x86/include/asm/kvm_host.h                  |   5 +
 arch/x86/include/uapi/asm/kvm.h                  |   1 +
 arch/x86/kvm/lapic.c                             |  22 +++-
 arch/x86/kvm/mmu.c                               |   9 +-
 arch/x86/kvm/svm.c                               |   7 +-
 arch/x86/kvm/vmx.c                               | 138 ++++++++++++++++-------
 arch/x86/kvm/x86.c                               | 101 +++++++++++------
 include/linux/kvm_host.h                         |   2 -
 include/uapi/linux/kvm.h                         |   1 +
 tools/testing/selftests/kvm/.gitignore           |   1 +
 tools/testing/selftests/kvm/Makefile             |   5 +-
 tools/testing/selftests/kvm/include/kvm_util.h   |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c       |  89 +++++++++++++++
 tools/testing/selftests/kvm/platform_info_test.c | 110 ++++++++++++++++++
 27 files changed, 537 insertions(+), 244 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/platform_info_test.c
```
#### [GIT PULL] KVM changes for Linux 4.19-rc5
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Greg,

The following changes since commit 7876320f88802b22d4e2daf7eb027dd14175a0f8:

  Linux 4.19-rc4 (2018-09-16 11:52:37 -0700)

are available in the git repository at:

  git://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 26b471c7e2f7befd0f59c35b257749ca57e0ed70:

  KVM: nVMX: Fix bad cleanup on error of get/set nested state IOCTLs (2018-09-20 18:54:08 +0200)

----------------------------------------------------------------
This pull request is slightly bigger than usual at this stage, but
I swear I would have sent it the same to Linus!  The main cause for
this is that I was on vacation until two weeks ago and it took a while
to sort all the pending patches between 4.19 and 4.20, test them and
so on.

It's mostly small bugfixes and cleanups, mostly around x86 nested
virtualization.  One important change, not related to nested
virtualization, is that the ability for the guest kernel to trap CPUID
instructions (in Linux that's the ARCH_SET_CPUID arch_prctl) is now
masked by default.  This is because the feature is detected through an
MSR; a very bad idea that Intel seems to like more and more.  Some
applications choke if the other fields of that MSR are not initialized
as on real hardware, hence we have to disable the whole MSR by default,
as was the case before Linux 4.12.

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      KVM: PPC: Avoid marking DMA-mapped pages dirty in real mode

Andy Shevchenko (1):
      KVM: SVM: Switch to bitmap_zalloc()

Drew Schmitt (3):
      KVM: x86: Turbo bits in MSR_PLATFORM_INFO
      KVM: x86: Control guest reads of MSR_PLATFORM_INFO
      kvm: selftests: Add platform_info_test

Janosch Frank (2):
      s390/mm: Check for valid vma before zapping in gmap_discard
      KVM: s390: Make huge pages unavailable in ucontrol VMs

Junaid Shahid (1):
      kvm: mmu: Don't read PDPTEs when paging is not enabled

Krish Sadhukhan (2):
      nVMX x86: check posted-interrupt descriptor addresss on vmentry of L2
      nVMX x86: Check VPID value on vmentry of L2 guests

Lei Yang (1):
      kvm: selftests: use -pthread instead of -lpthread

Liran Alon (2):
      KVM: nVMX: Wake blocked vCPU in guest-mode if pending interrupt in virtual APICv
      KVM: nVMX: Fix bad cleanup on error of get/set nested state IOCTLs

Nicholas Piggin (1):
      KVM: PPC: Book3S HV: Don't use compound_order to determine host mapping size

Paolo Bonzini (3):
      Merge tag 'kvm-s390-master-4.19-2' of git://git.kernel.org/.../kvms390/linux into HEAD
      Merge tag 'kvm-ppc-fixes-4.19-2' of git://git.kernel.org/.../paulus/powerpc into HEAD
      KVM: VMX: check nested state and CR4.VMXE against SMM

Sean Christopherson (3):
      KVM: VMX: immediately mark preemption timer expired only for zero value
      KVM: VMX: modify preemption timer bit only when arming timer
      KVM: VMX: use preemption timer to force immediate VMExit

Sebastian Andrzej Siewior (1):
      kvm: x86: make kvm_{load|put}_guest_fpu() static

Tianyu Lan (1):
      KVM/MMU: Fix comment in walk_shadow_page_lockless_end()

Vitaly Kuznetsov (2):
      x86/kvm/lapic: always disable MMIO interface in x2APIC mode
      x86/hyper-v: rename ipi_arg_{ex,non_ex} structures

Wei Yang (1):
      KVM: x86: don't reset root in kvm_mmu_setup()

 Documentation/virtual/kvm/api.txt                |  12 +-
 arch/powerpc/include/asm/book3s/64/pgtable.h     |   1 -
 arch/powerpc/include/asm/iommu.h                 |   2 -
 arch/powerpc/include/asm/mmu_context.h           |   1 +
 arch/powerpc/kernel/iommu.c                      |  25 ----
 arch/powerpc/kvm/book3s_64_mmu_radix.c           |  91 ++++++---------
 arch/powerpc/kvm/book3s_64_vio_hv.c              |  39 +++++--
 arch/powerpc/mm/init_64.c                        |  49 --------
 arch/powerpc/mm/mmu_context_iommu.c              |  34 +++++-
 arch/s390/kvm/kvm-s390.c                         |   4 +-
 arch/s390/mm/gmap.c                              |   4 +-
 arch/x86/hyperv/hv_apic.c                        |   8 +-
 arch/x86/include/asm/hyperv-tlfs.h               |  16 +--
 arch/x86/include/asm/kvm_host.h                  |   5 +
 arch/x86/include/uapi/asm/kvm.h                  |   1 +
 arch/x86/kvm/lapic.c                             |  22 +++-
 arch/x86/kvm/mmu.c                               |   9 +-
 arch/x86/kvm/svm.c                               |   7 +-
 arch/x86/kvm/vmx.c                               | 138 ++++++++++++++++-------
 arch/x86/kvm/x86.c                               | 101 +++++++++++------
 include/linux/kvm_host.h                         |   2 -
 include/uapi/linux/kvm.h                         |   1 +
 tools/testing/selftests/kvm/.gitignore           |   1 +
 tools/testing/selftests/kvm/Makefile             |   5 +-
 tools/testing/selftests/kvm/include/kvm_util.h   |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c       |  89 +++++++++++++++
 tools/testing/selftests/kvm/platform_info_test.c | 110 ++++++++++++++++++
 27 files changed, 537 insertions(+), 244 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/platform_info_test.c
```
#### [GIT PULL] KVM changes for Linux 4.20-rc5
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Greg,

The following changes since commit 7876320f88802b22d4e2daf7eb027dd14175a0f8:

  Linux 4.19-rc4 (2018-09-16 11:52:37 -0700)

are available in the git repository at:

  git://git.kernel.org/pub/scm/virt/kvm/kvm.git queue

for you to fetch changes up to 26b471c7e2f7befd0f59c35b257749ca57e0ed70:

  KVM: nVMX: Fix bad cleanup on error of get/set nested state IOCTLs (2018-09-20 18:54:08 +0200)

----------------------------------------------------------------
This pull request is slightly bigger than usual at this stage, but
I swear I would have sent it the same to Linus!  The main cause for
this is that I was on vacation until two weeks ago and it took a while
to sort all the pending patches between 4.20 and 4.21, test them and
so on.

It's mostly small bugfixes and cleanups, mostly around x86 nested
virtualization.  One important change, not related to nested
virtualization, is that the ability for the guest kernel to trap CPUID
instructions (in Linux that's the ARCH_SET_CPUID arch_prctl) is now
masked by default.  This is because the feature is detected through an
MSR; a very bad idea that Intel seems to like more and more.  Some
applications choke if the other fields of that MSR are not initialized
as on real hardware, hence we have to disable the whole MSR by default,
as was the case before Linux 4.12.

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      KVM: PPC: Avoid marking DMA-mapped pages dirty in real mode

Andy Shevchenko (1):
      KVM: SVM: Switch to bitmap_zalloc()

Drew Schmitt (3):
      KVM: x86: Turbo bits in MSR_PLATFORM_INFO
      KVM: x86: Control guest reads of MSR_PLATFORM_INFO
      kvm: selftests: Add platform_info_test

Janosch Frank (2):
      s390/mm: Check for valid vma before zapping in gmap_discard
      KVM: s390: Make huge pages unavailable in ucontrol VMs

Junaid Shahid (1):
      kvm: mmu: Don't read PDPTEs when paging is not enabled

Krish Sadhukhan (2):
      nVMX x86: check posted-interrupt descriptor addresss on vmentry of L2
      nVMX x86: Check VPID value on vmentry of L2 guests

Lei Yang (1):
      kvm: selftests: use -pthread instead of -lpthread

Liran Alon (2):
      KVM: nVMX: Wake blocked vCPU in guest-mode if pending interrupt in virtual APICv
      KVM: nVMX: Fix bad cleanup on error of get/set nested state IOCTLs

Nicholas Piggin (1):
      KVM: PPC: Book3S HV: Don't use compound_order to determine host mapping size

Paolo Bonzini (3):
      Merge tag 'kvm-s390-master-4.19-2' of git://git.kernel.org/.../kvms390/linux into HEAD
      Merge tag 'kvm-ppc-fixes-4.19-2' of git://git.kernel.org/.../paulus/powerpc into HEAD
      KVM: VMX: check nested state and CR4.VMXE against SMM

Sean Christopherson (3):
      KVM: VMX: immediately mark preemption timer expired only for zero value
      KVM: VMX: modify preemption timer bit only when arming timer
      KVM: VMX: use preemption timer to force immediate VMExit

Sebastian Andrzej Siewior (1):
      kvm: x86: make kvm_{load|put}_guest_fpu() static

Tianyu Lan (1):
      KVM/MMU: Fix comment in walk_shadow_page_lockless_end()

Vitaly Kuznetsov (2):
      x86/kvm/lapic: always disable MMIO interface in x2APIC mode
      x86/hyper-v: rename ipi_arg_{ex,non_ex} structures

Wei Yang (1):
      KVM: x86: don't reset root in kvm_mmu_setup()

 Documentation/virtual/kvm/api.txt                |  12 +-
 arch/powerpc/include/asm/book3s/64/pgtable.h     |   1 -
 arch/powerpc/include/asm/iommu.h                 |   2 -
 arch/powerpc/include/asm/mmu_context.h           |   1 +
 arch/powerpc/kernel/iommu.c                      |  25 ----
 arch/powerpc/kvm/book3s_64_mmu_radix.c           |  91 ++++++---------
 arch/powerpc/kvm/book3s_64_vio_hv.c              |  39 +++++--
 arch/powerpc/mm/init_64.c                        |  49 --------
 arch/powerpc/mm/mmu_context_iommu.c              |  34 +++++-
 arch/s390/kvm/kvm-s390.c                         |   4 +-
 arch/s390/mm/gmap.c                              |   4 +-
 arch/x86/hyperv/hv_apic.c                        |   8 +-
 arch/x86/include/asm/hyperv-tlfs.h               |  16 +--
 arch/x86/include/asm/kvm_host.h                  |   5 +
 arch/x86/include/uapi/asm/kvm.h                  |   1 +
 arch/x86/kvm/lapic.c                             |  22 +++-
 arch/x86/kvm/mmu.c                               |   9 +-
 arch/x86/kvm/svm.c                               |   7 +-
 arch/x86/kvm/vmx.c                               | 138 ++++++++++++++++-------
 arch/x86/kvm/x86.c                               | 101 +++++++++++------
 include/linux/kvm_host.h                         |   2 -
 include/uapi/linux/kvm.h                         |   1 +
 tools/testing/selftests/kvm/.gitignore           |   1 +
 tools/testing/selftests/kvm/Makefile             |   5 +-
 tools/testing/selftests/kvm/include/kvm_util.h   |   4 +
 tools/testing/selftests/kvm/lib/kvm_util.c       |  89 +++++++++++++++
 tools/testing/selftests/kvm/platform_info_test.c | 110 ++++++++++++++++++
 27 files changed, 537 insertions(+), 244 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/platform_info_test.c
```
#### [RFC PATCH 01/32] KVM: PPC: Book3S: Simplify external interrupt handling
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Currently we use two bits in the vcpu pending_exceptions bitmap to
indicate that an external interrupt is pending for the guest, one
for "one-shot" interrupts that are cleared when delivered, and one
for interrupts that persist until cleared by an explicit action of
the OS (e.g. an acknowledge to an interrupt controller).  The
BOOK3S_IRQPRIO_EXTERNAL bit is used for one-shot interrupt requests
and BOOK3S_IRQPRIO_EXTERNAL_LEVEL is used for persisting interrupts.

In practice BOOK3S_IRQPRIO_EXTERNAL never gets used, because our
Book3S platforms generally, and pseries in particular, expect
external interrupt requests to persist until they are acknowledged
at the interrupt controller.  That combined with the confusion
introduced by having two bits for what is essentially the same thing
makes it attractive to simplify things by only using one bit.  This
patch does that.

With this patch there is only BOOK3S_IRQPRIO_EXTERNAL, and by default
it has the semantics of a persisting interrupt.  In order to avoid
breaking the ABI, we introduce a new "external_oneshot" flag which
preserves the behaviour of the KVM_INTERRUPT ioctl with the
KVM_INTERRUPT_SET argument.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---
 arch/powerpc/include/asm/kvm_asm.h             |  4 +--
 arch/powerpc/include/asm/kvm_host.h            |  1 +
 arch/powerpc/kvm/book3s.c                      | 43 ++++++++++++++++++++------
 arch/powerpc/kvm/book3s_hv_rm_xics.c           |  5 ++-
 arch/powerpc/kvm/book3s_hv_rmhandlers.S        |  4 +--
 arch/powerpc/kvm/book3s_pr.c                   |  1 -
 arch/powerpc/kvm/book3s_xics.c                 | 11 +++----
 arch/powerpc/kvm/book3s_xive_template.c        |  2 +-
 arch/powerpc/kvm/trace_book3s.h                |  1 -
 tools/perf/arch/powerpc/util/book3s_hv_exits.h |  1 -
 10 files changed, 44 insertions(+), 29 deletions(-)

```
#### [kvm-unit-tests PATCH v2] x86: nVMX: Basic test of #DB intercept in L1
##### From: Jim Mattson <jmattson@google.com>

```c
Test a single-step trap delivered by hardware to set expectations, and
then test a single-step trap synthesized by L0 to see if those
expectations are met. Single-step traps in simulated MOVSS-shadow are
tested as well.

As a bonus, test a single-step trap in a transactional region to set
expectations for that unusual case as well.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 x86/unittests.cfg |   6 ++
 x86/vmx.h         |   9 ++
 x86/vmx_tests.c   | 207 ++++++++++++++++++++++++++++++++++++++++++++++
 3 files changed, 222 insertions(+)

```
#### [kvm-unit-tests PATCH] x86: nVMX: Basic test of #DB intercept in L1From: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Test a single-step trap delivered by hardware to set expectations, and
then test a single-step trap synthesized by L0 to see if those
expectations are met.

As a bonus, test a single-step trap in a transactional region to set
expectations for that unusual case as well.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 x86/unittests.cfg |   6 ++
 x86/vmx_tests.c   | 157 ++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 163 insertions(+)

```
#### [PATCH] KVM: x86: Remove documentation for KVM_CAP_INTR_SHADOWFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
This capability was never implemented. Aside from the #define, there
are no references to it anywhere in the code base. Let's remove the
misleading documentation.

Signed-off-by: Jim Mattson <jmattson@google.com>
---
 Documentation/virtual/kvm/api.txt | 4 +---
 include/uapi/linux/kvm.h          | 2 +-
 tools/include/uapi/linux/kvm.h    | 2 +-
 3 files changed, 3 insertions(+), 5 deletions(-)

```
#### [PULL kvm-unit-tests] arm/arm64: patches ready for master
##### From: Andrew Jones <drjones@redhat.com>

```c
The following changes since commit 9064d89bbda92f447bf3efebf71b7f95cfafb8b9:

  kvm-unit-tests: unlock before calling return (2018-09-20 00:43:40 +0200)

are available in the Git repository at:

  https://github.com/rhdrjones/kvm-unit-tests tags/for-master

for you to fetch changes up to 090e15321d2fef1adf8d182a9104cbfaa2665212:

  arm64: add micro-bench (2018-09-21 13:15:18 +0200)

----------------------------------------------------------------
arm/arm64 patches ready for master

----------------------------------------------------------------
Andre Przywara (6):
      arm64: timer: add TVAL accessors
      arm64: timer: Add TVAL timeout IRQ trigger test
      mark exit() and abort() as non-returning functions
      arm/arm64: GIC: basic GICv2 MMIO tests
      arm/arm64: GICv2: add GICD_IPRIORITYR testing
      arm/arm64: GICv2: add GICD_ITARGETSR testing

Andrew Jones (1):
      arm/arm64: fix gic-ipi test regression

Shih-Wei Li (1):
      arm64: add micro-bench

 arm/Makefile.arm64  |   1 +
 arm/gic.c           | 213 +++++++++++++++++++++++++++++++++++++++++++++++++++
 arm/micro-bench.c   | 215 ++++++++++++++++++++++++++++++++++++++++++++++++++++
 arm/timer.c         |  36 +++++++++
 arm/unittests.cfg   |  26 +++++++
 lib/arm/asm/gic.h   |   5 ++
 lib/arm/asm/setup.h |   2 +-
 lib/arm/io.c        |   1 +
 lib/libcflat.h      |   7 +-
 lib/powerpc/io.c    |   1 +
 lib/x86/io.c        |   1 +
 11 files changed, 504 insertions(+), 4 deletions(-)
 create mode 100644 arm/micro-bench.c
```
#### [PATCH v2 1/2] s390/cio: Convert ccw_io_region to pointer
##### From: Eric Farman <farman@linux.ibm.com>

```c
In the event that we want to change the layout of the ccw_io_region in the
future[1], it might be easier to work with it as a pointer within the
vfio_ccw_private struct rather than an embedded struct.

[1] https://patchwork.kernel.org/comment/22228541/

Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_drv.c     | 12 +++++++++++-
 drivers/s390/cio/vfio_ccw_fsm.c     |  6 +++---
 drivers/s390/cio/vfio_ccw_ops.c     |  4 ++--
 drivers/s390/cio/vfio_ccw_private.h |  2 +-
 4 files changed, 17 insertions(+), 7 deletions(-)

```
#### [PATCH v2] KVM: nVMX: Clear reserved bits of #DB exit qualificationFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
According to volume 3 of the SDM, bits 63:15 and 12:4 of the exit
qualification field for debug exceptions are reserved (cleared to
0). However, the SDM is incorrect about bit 16 (corresponding to
DR6.RTM). This bit should be set if a debug exception (#DB) or a
breakpoint exception (#BP) occurred inside an RTM region while
advanced debugging of RTM transactional regions was enabled. Note that
this is the opposite of DR6.RTM, which "indicates (when clear) that a
debug exception (#DB) or breakpoint exception (#BP) occurred inside an
RTM region while advanced debugging of RTM transactional regions was
enabled."

There is still an issue with stale DR6 bits potentially being
misreported for the current debug exception.  DR6 should not have been
modified before vectoring the #DB exception, and the "new DR6 bits"
should be available somewhere, but it was and they aren't.

Fixes: b96fb439774e1 ("KVM: nVMX: fixes to nested virt interrupt injection")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h | 1 +
 arch/x86/kvm/vmx.c              | 7 +++++--
 2 files changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH v3 1/2] vfio: add edid api for display (vgpu) devices.
##### From: Gerd Hoffmann <kraxel@redhat.com>

```c
This allows to set EDID monitor information for the vgpu display, for a
more flexible display configuration, using a special vfio region.  Check
the comment describing struct vfio_region_gfx_edid for more details.

Signed-off-by: Gerd Hoffmann <kraxel@redhat.com>
---
 include/uapi/linux/vfio.h | 50 +++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 50 insertions(+)

```
#### [PATCH 1/2] virtio/s390: avoid race on vcdev->config
##### From: Halil Pasic <pasic@linux.ibm.com>

```c
Currently we have a race on vcdev->config in virtio_ccw_get_config() and
in virtio_ccw_set_config().

This normally does not cause problems, as these are usually infrequent
operations. But occasionally sysfs attributes are directly dependent on
pieces of virio config and trigger a get on each read. This gives us at
least one trigger.

Let us protect the shared state using vcdev->lock.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/s390/virtio/virtio_ccw.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
