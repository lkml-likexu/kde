#### [PATCH 1/3] kvm: nVMX: Set nested_run_pending in vmx_set_nested_state after checks complete
##### From: Aaron Lewis <aaronlewis@google.com>

```c
nested_run_pending=1 implies we have successfully entered guest mode.
Move setting from external state in vmx_set_nested_state() until after
all other checks are complete.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/vmx/nested.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [GIT PULL] Please pull my kvm-ppc-next-5.2-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Please do a pull from my kvm-ppc-next-5.2-1 tag to get a PPC update
for 5.2.  The main new feature here is that we can now let guests
access the POWER9 XIVE interrupt controller directly for things like
acknowledge, EOI, enable and disable on interrupts, rather than
requiring guests to do hypercalls for these operations.

I have merged in the topic/ppc-kvm branch from the powerpc tree
because one of the patches there is a prerequisite for the XIVE patch
series.  That's why there are changes to arch/powerpc/kernel in the
diffstat.

Stephen Rothwell noted a conflict between my tree and the kvm-arm tree
because we have both allocated new capability numbers.

The XIVE patch series also modifies generic KVM code to add mmap and
release methods on KVM devices.

Thanks,
Paul.

The following changes since commit 345077c8e172c255ea0707214303ccd099e5656b:

  KVM: PPC: Book3S: Protect memslots while validating user address (2019-04-05 14:37:24 +1100)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.2-1

for you to fetch changes up to 0caecf5b00199636eb2d32201199ecd6be52558d:

  KVM: PPC: Book3S HV: XIVE: Clear escalation interrupt pointers on device close (2019-04-30 19:41:01 +1000)

----------------------------------------------------------------
PPC KVM update for 5.2

* Support for guests to access the new POWER9 XIVE interrupt controller
  hardware directly, reducing interrupt latency and overhead for guests.

* In-kernel implementation of the H_PAGE_INIT hypercall.

* Reduce memory usage of sparsely-populated IOMMU tables.

* Several bug fixes.

----------------------------------------------------------------
Alexey Kardashevskiy (3):
      KVM: PPC: Book3S HV: Fix lockdep warning when entering the guest
      KVM: PPC: Book3S HV: Avoid lockdep debugging in TCE realmode handlers
      KVM: PPC: Book3S: Allocate guest TCEs on demand too

Cédric Le Goater (17):
      powerpc/xive: add OPAL extensions for the XIVE native exploitation support
      KVM: PPC: Book3S HV: Add a new KVM device for the XIVE native exploitation mode
      KVM: PPC: Book3S HV: XIVE: Introduce a new capability KVM_CAP_PPC_IRQ_XIVE
      KVM: PPC: Book3S HV: XIVE: add a control to initialize a source
      KVM: PPC: Book3S HV: XIVE: Add a control to configure a source
      KVM: PPC: Book3S HV: XIVE: Add controls for the EQ configuration
      KVM: PPC: Book3S HV: XIVE: Add a global reset control
      KVM: PPC: Book3S HV: XIVE: Add a control to sync the sources
      KVM: PPC: Book3S HV: XIVE: Add a control to dirty the XIVE EQ pages
      KVM: PPC: Book3S HV: XIVE: Add get/set accessors for the VP XIVE state
      KVM: Introduce a 'mmap' method for KVM devices
      KVM: PPC: Book3S HV: XIVE: Add a TIMA mapping
      KVM: PPC: Book3S HV: XIVE: Add a mapping for the source ESB pages
      KVM: PPC: Book3S HV: XIVE: Add passthrough support
      KVM: PPC: Book3S HV: XIVE: Activate XIVE exploitation mode
      KVM: Introduce a 'release' method for KVM devices
      KVM: PPC: Book3S HV: XIVE: Replace the 'destroy' method by a 'release' method

Michael Neuling (1):
      powerpc: Add force enable of DAWR on P9 option

Palmer Dabbelt (1):
      KVM: PPC: Book3S HV: smb->smp comment fixup

Paul Mackerras (6):
      KVM: PPC: Book3S HV: Fix XICS-on-XIVE H_IPI when priority = 0
      KVM: PPC: Book3S HV: Move HPT guest TLB flushing to C code
      KVM: PPC: Book3S HV: Flush TLB on secondary radix threads
      Merge remote-tracking branch 'remotes/powerpc/topic/ppc-kvm' into kvm-ppc-next
      KVM: PPC: Book3S HV: XIVE: Prevent races when releasing device
      KVM: PPC: Book3S HV: XIVE: Clear escalation interrupt pointers on device close

Suraj Jitindar Singh (4):
      KVM: PPC: Book3S HV: Implement virtual mode H_PAGE_INIT handler
      KVM: PPC: Book3S HV: Implement real mode H_PAGE_INIT handler
      KVM: PPC: Book3S HV: Handle virtual mode in XIVE VCPU push code
      KVM: PPC: Book3S HV: Save/restore vrsave register in kvmhv_p9_guest_entry()

 Documentation/powerpc/DAWR-POWER9.txt      |   32 +
 Documentation/virtual/kvm/api.txt          |   10 +
 Documentation/virtual/kvm/devices/xive.txt |  197 +++++
 arch/powerpc/include/asm/hw_breakpoint.h   |    8 +
 arch/powerpc/include/asm/kvm_host.h        |   11 +-
 arch/powerpc/include/asm/kvm_ppc.h         |   41 +-
 arch/powerpc/include/asm/opal-api.h        |    7 +-
 arch/powerpc/include/asm/opal.h            |    7 +
 arch/powerpc/include/asm/xive.h            |   17 +
 arch/powerpc/include/uapi/asm/kvm.h        |   46 +
 arch/powerpc/kernel/hw_breakpoint.c        |   62 +-
 arch/powerpc/kernel/process.c              |    9 +-
 arch/powerpc/kernel/ptrace.c               |    3 +-
 arch/powerpc/kvm/Makefile                  |    2 +-
 arch/powerpc/kvm/book3s.c                  |   42 +-
 arch/powerpc/kvm/book3s_64_vio.c           |   96 ++-
 arch/powerpc/kvm/book3s_64_vio_hv.c        |  105 ++-
 arch/powerpc/kvm/book3s_hv.c               |  155 ++--
 arch/powerpc/kvm/book3s_hv_builtin.c       |   57 ++
 arch/powerpc/kvm/book3s_hv_rm_mmu.c        |  144 ++++
 arch/powerpc/kvm/book3s_hv_rmhandlers.S    |  103 +--
 arch/powerpc/kvm/book3s_xive.c             |  250 ++++--
 arch/powerpc/kvm/book3s_xive.h             |   37 +
 arch/powerpc/kvm/book3s_xive_native.c      | 1249 ++++++++++++++++++++++++++++
 arch/powerpc/kvm/book3s_xive_template.c    |   78 +-
 arch/powerpc/kvm/powerpc.c                 |   37 +
 arch/powerpc/platforms/powernv/opal-call.c |    3 +
 arch/powerpc/sysdev/xive/native.c          |  110 +++
 include/linux/kvm_host.h                   |   10 +
 include/uapi/linux/kvm.h                   |    3 +
 virt/kvm/kvm_main.c                        |   24 +
 31 files changed, 2670 insertions(+), 285 deletions(-)
 create mode 100644 Documentation/virtual/kvm/devices/xive.txt
 create mode 100644 arch/powerpc/kvm/book3s_xive_native.c
```
#### [PATCH] KVM: nVMX: Set msr bitmap correctly for MSR_FS_BASE in vmcs02
##### From: Jintack Lim <jintack@cs.columbia.edu>

```c
Even when neither L0 nor L1 configured to trap MSR_FS_BASE writes from
its own VMs, the current KVM L0 always traps MSR_FS_BASE writes from L2.
Let's check if both L0 and L1 disabled trap for MSR_FS_BASE for its VMs
respectively, and let L2 write to MSR_FS_BASE without trap if that's the
case.

Signed-off-by: Jintack Lim <jintack@cs.columbia.edu>
---
 arch/x86/kvm/vmx/nested.c | 7 +++++++
 1 file changed, 7 insertions(+)

```
#### [kvm-unit-tests PATCH] lib/alloc_page: Zero allocated pages
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

One of the most important properties of tests is reproducibility. For
tests to be reproducible, the same environment should be set on each
test invocation.

When it comes to memory content, this is not exactly the case in
kvm-unit-tests. The tests might, mistakenly or intentionally, assume
that memory is zeroed, which apparently is the case after seabios runs.
However, failures might not be reproducible if this assumption is
broken.

As an example, consider x86 do_iret(), which mistakenly does not push
SS:RSP onto the stack on 64-bit mode, although they are popped
unconditionally.

Do not assume that memory is zeroed. Clear it once it is allocated to
allow tests to easily be reproducible.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 lib/alloc_page.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests PATCH] x86: Restore VMCS state when test_vmcs_addr() is done
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

The VMCS fields of APIC_VIRT_ADDR and TPR_THRESHOLD are modified by
test_vmcs_addr() but are not restored to their original value. Save and
restore them.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/vmx_tests.c | 12 +++++++-----
 1 file changed, 7 insertions(+), 5 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Set "APIC Software Enable" after APIC reset
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

After the APIC is reset, some of its registers might be reset. As the
SDM says: "When IA32_APIC_BASE[11] is set to 0, prior initialization to
the APIC may be lost and the APIC may return to the state described in
Section 10.4.7.1". The SDM also says that after APIC reset "the
spurious-interrupt vector register is initialized to 000000FFH". This
means that after the APIC is reset it needs to be software-enabled
through the SPIV.

This is done one occasion, but there are (at least) two occasions that
do not software-enable the APIC after reset (__test_apic_id() and main()
in vmx.c).

Move APIC SPIV reinitialization into reset_apic(). Remove SPIV settings
which are unnecessary after reset_apic() is modified.

Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 lib/x86/apic.c | 1 +
 x86/apic.c     | 1 -
 2 files changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 01/10] vfio/mdev: add notifier for map events
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Allow an VFIO mdev device to listen to map events
This will allow a mdev driver to dma map memory
as soon as it gets added to the domain
---
Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 drivers/vfio/vfio_iommu_type1.c | 97 +++++++++++++++++++++++++++++----
 include/linux/vfio.h            |  4 ++
 2 files changed, 89 insertions(+), 12 deletions(-)

```
#### [PATCH] tests: kvm: Add tests for KVM_CAP_MAX_VCPUS and KVM_CAP_MAX_CPU_ID
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
---
 tools/testing/selftests/kvm/.gitignore        |  1 +
 tools/testing/selftests/kvm/Makefile          |  1 +
 .../kvm/x86_64/kvm_create_max_vcpus.c         | 70 +++++++++++++++++++
 3 files changed, 72 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/x86_64/kvm_create_max_vcpus.c

```
#### [PATCH] tests: kvm: Add tests to .gitignoreFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 tools/testing/selftests/kvm/.gitignore | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v8 1/4] s390: ap: kvm: add PQAP interception for AQIC
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
We prepare the interception of the PQAP/AQIC instruction for
the case the AQIC facility is enabled in the guest.

First of all we do not want to change existing behavior when
intercepting AP instructions without the SIE allowing the guest
to use AP instructions.

In this patch we only handle the AQIC interception allowed by
facility 65 which will be enabled when the complete interception
infrastructure will be present.

We add a callback inside the KVM arch structure for s390 for
a VFIO driver to handle a specific response to the PQAP
instruction with the AQIC command and only this command.

But we want to be able to return a correct answer to the guest
even there is no VFIO AP driver in the kernel.
Therefor, we inject the correct exceptions from inside KVM for the
case the callback is not initialized, which happens when the vfio_ap
driver is not loaded.

We do consider the responsability of the driver to always initialize
the PQAP callback if it defines queues by initializing the CRYCB for
a guest.
If the callback has been setup we call it.
If not we setup an answer considering that no queue is available
for the guest when no callback has been setup.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 arch/s390/include/asm/kvm_host.h      |  7 +++
 arch/s390/kvm/priv.c                  | 86 +++++++++++++++++++++++++++++++++++
 drivers/s390/crypto/vfio_ap_private.h |  2 +
 3 files changed, 95 insertions(+)

```
