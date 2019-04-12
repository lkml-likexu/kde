#### [PATCH v3 09/26] compat_ioctl: move drivers to compat_ptr_ioctl
##### From: Arnd Bergmann <arnd@arndb.de>

```c
Each of these drivers has a copy of the same trivial helper function to
convert the pointer argument and then call the native ioctl handler.

We now have a generic implementation of that, so use it.

Acked-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Reviewed-by: Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
Reviewed-by: Jason Gunthorpe <jgg@mellanox.com>
Signed-off-by: Arnd Bergmann <arnd@arndb.de>
Reviewed-by: Jiri Kosina <jkosina@suse.cz>
---
 drivers/char/ppdev.c              | 12 +---------
 drivers/char/tpm/tpm_vtpm_proxy.c | 12 +---------
 drivers/firewire/core-cdev.c      | 12 +---------
 drivers/hid/usbhid/hiddev.c       | 11 +--------
 drivers/hwtracing/stm/core.c      | 12 +---------
 drivers/misc/mei/main.c           | 22 +----------------
 drivers/mtd/ubi/cdev.c            | 36 +++-------------------------
 drivers/net/tap.c                 | 12 +---------
 drivers/staging/pi433/pi433_if.c  | 12 +---------
 drivers/usb/core/devio.c          | 16 +------------
 drivers/vfio/vfio.c               | 39 +++----------------------------
 drivers/vhost/net.c               | 12 +---------
 drivers/vhost/scsi.c              | 12 +---------
 drivers/vhost/test.c              | 12 +---------
 drivers/vhost/vsock.c             | 12 +---------
 fs/fat/file.c                     | 13 +----------
 16 files changed, 20 insertions(+), 237 deletions(-)

```
#### [PATCH v2 1/2] KVM: polling: add architecture backend to disable polling
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
There are cases where halt polling is unwanted. For example when running
KVM on an over committed LPAR we rather want to give back the CPU to
neighbour LPARs instead of polling. Let us provide a callback that
allows architectures to disable polling.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 include/linux/kvm_host.h | 10 ++++++++++
 virt/kvm/Kconfig         |  3 +++
 virt/kvm/kvm_main.c      |  2 +-
 3 files changed, 14 insertions(+), 1 deletion(-)

```
#### [GIT PULL] KVM changes for Linux 5.1-rc6
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 771acc7e4a6e5dba779cb1a7fd851a164bc81033:

  Bluetooth: btusb: request wake pin with NOAUTOEN (2019-04-09 17:38:24 -1000)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 09f8bbfd55b2710770e0fc978da2773f6e705bed:

  KVM: x86: avoid misreporting level-triggered irqs as edge-triggered in tracing (2019-04-16 10:59:20 +0200)

5.1 keeps its reputation as a big bugfix release for KVM x86.

----------------------------------------------------------------
* Fix for a memory leak introduced during the merge window
* Fixes for nested VMX with ept=0
* Fixes for AMD (APIC virtualization, NMI injection)
* Fixes for Hyper-V under KVM and KVM under Hyper-V
* Fixes for 32-bit SMM and tests for SMM virtualization
* More array_index_nospec peppering

----------------------------------------------------------------
Ben Gardon (1):
      kvm: mmu: Fix overflow on kvm mmu page limit calculation

Hariprasad Kelam (1):
      KVM: x86: fix warning Using plain integer as NULL pointer

Liran Alon (2):
      KVM: x86: Raise #GP when guest vCPU do not support PMU
      KVM: nVMX: Expose RDPMC-exiting only when guest supports PMU

Paolo Bonzini (5):
      KVM: nVMX: allow tests to use bad virtual-APIC page address
      KVM: nVMX: always use early vmcs check when EPT is disabled
      selftests: kvm/evmcs_test: complete I/O before migrating guest state
      selftests: kvm: fix for compilers that do not support -no-pie
      KVM: fix spectrev1 gadgets

Sean Christopherson (6):
      KVM: x86/mmu: Fix an inverted list_empty() check when zapping sptes
      KVM: x86: Load SMRAM in a single shot when leaving SMM
      KVM: x86: Open code kvm_set_hflags
      KVM: x86: clear SMM flags before loading state while leaving SMM
      KVM: x86: Don't clear EFER during SMM transitions for 32-bit vCPU
      KVM: x86: Always use 32-bit SMRAM save state for 32-bit kernels

Suthikulpanit, Suravee (2):
      Revert "svm: Fix AVIC incomplete IPI emulation"
      svm/avic: Fix invalidate logical APIC id entry

Vitaly Kuznetsov (3):
      KVM: x86: svm: make sure NMI is injected after nmi_singlestep
      selftests: kvm: add a selftest for SMM
      KVM: x86: avoid misreporting level-triggered irqs as edge-triggered in tracing

WANG Chao (1):
      x86/kvm: move kvm_load/put_guest_xcr0 into atomic context

 arch/x86/include/asm/kvm_emulate.h                 |   4 +-
 arch/x86/include/asm/kvm_host.h                    |  17 +-
 arch/x86/include/uapi/asm/vmx.h                    |   1 +
 arch/x86/kvm/emulate.c                             | 191 +++++++++++----------
 arch/x86/kvm/lapic.c                               |   4 +-
 arch/x86/kvm/mmu.c                                 |  15 +-
 arch/x86/kvm/mmu.h                                 |   2 +-
 arch/x86/kvm/pmu.c                                 |   4 +
 arch/x86/kvm/svm.c                                 |  57 +++---
 arch/x86/kvm/trace.h                               |   4 +-
 arch/x86/kvm/vmx/nested.c                          |  47 +++--
 arch/x86/kvm/vmx/vmx.c                             |  35 +++-
 arch/x86/kvm/vmx/vmx.h                             |   2 +
 arch/x86/kvm/x86.c                                 |  64 ++++---
 arch/x86/kvm/x86.h                                 |   2 +
 include/linux/kvm_host.h                           |  10 +-
 tools/testing/selftests/kvm/Makefile               |   9 +-
 .../selftests/kvm/include/x86_64/processor.h       |  27 +++
 tools/testing/selftests/kvm/lib/kvm_util.c         |   5 +
 tools/testing/selftests/kvm/lib/x86_64/processor.c |  20 ++-
 tools/testing/selftests/kvm/x86_64/evmcs_test.c    |   5 +-
 tools/testing/selftests/kvm/x86_64/smm_test.c      | 157 +++++++++++++++++
 tools/testing/selftests/kvm/x86_64/state_test.c    |  15 +-
 virt/kvm/irqchip.c                                 |   5 +-
 virt/kvm/kvm_main.c                                |   6 +-
 25 files changed, 496 insertions(+), 212 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/smm_test.c
```
#### [GIT PULL v2] KVM changes for Linux 5.1-rc6
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 771acc7e4a6e5dba779cb1a7fd851a164bc81033:

  Bluetooth: btusb: request wake pin with NOAUTOEN (2019-04-09 17:38:24 -1000)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 7a223e06b1a411cef6c4cd7a9b9a33c8d225b10e:

  KVM: x86: avoid misreporting level-triggered irqs as edge-triggered in tracing (2019-04-16 15:38:08 +0200)

5.1 keeps its reputation as a big bugfix release for KVM x86.

----------------------------------------------------------------
* Fix for a memory leak introduced during the merge window
* Fixes for nested VMX with ept=0
* Fixes for AMD (APIC virtualization, NMI injection)
* Fixes for Hyper-V under KVM and KVM under Hyper-V
* Fixes for 32-bit SMM and tests for SMM virtualization
* More array_index_nospec peppering

----------------------------------------------------------------
Ben Gardon (1):
      kvm: mmu: Fix overflow on kvm mmu page limit calculation

Hariprasad Kelam (1):
      KVM: x86: fix warning Using plain integer as NULL pointer

Liran Alon (2):
      KVM: x86: Raise #GP when guest vCPU do not support PMU
      KVM: nVMX: Expose RDPMC-exiting only when guest supports PMU

Paolo Bonzini (5):
      KVM: nVMX: allow tests to use bad virtual-APIC page address
      KVM: nVMX: always use early vmcs check when EPT is disabled
      selftests: kvm/evmcs_test: complete I/O before migrating guest state
      selftests: kvm: fix for compilers that do not support -no-pie
      KVM: fix spectrev1 gadgets

Sean Christopherson (6):
      KVM: x86/mmu: Fix an inverted list_empty() check when zapping sptes
      KVM: x86: Load SMRAM in a single shot when leaving SMM
      KVM: x86: Open code kvm_set_hflags
      KVM: x86: clear SMM flags before loading state while leaving SMM
      KVM: x86: Don't clear EFER during SMM transitions for 32-bit vCPU
      KVM: x86: Always use 32-bit SMRAM save state for 32-bit kernels

Suthikulpanit, Suravee (2):
      Revert "svm: Fix AVIC incomplete IPI emulation"
      svm/avic: Fix invalidate logical APIC id entry

Vitaly Kuznetsov (3):
      KVM: x86: svm: make sure NMI is injected after nmi_singlestep
      selftests: kvm: add a selftest for SMM
      KVM: x86: avoid misreporting level-triggered irqs as edge-triggered in tracing

WANG Chao (1):
      x86/kvm: move kvm_load/put_guest_xcr0 into atomic context

 arch/x86/include/asm/kvm_emulate.h                 |   4 +-
 arch/x86/include/asm/kvm_host.h                    |  17 +-
 arch/x86/include/uapi/asm/vmx.h                    |   1 +
 arch/x86/kvm/emulate.c                             | 191 +++++++++++----------
 arch/x86/kvm/lapic.c                               |   4 +-
 arch/x86/kvm/mmu.c                                 |  15 +-
 arch/x86/kvm/mmu.h                                 |   2 +-
 arch/x86/kvm/pmu.c                                 |   4 +
 arch/x86/kvm/svm.c                                 |  57 +++---
 arch/x86/kvm/trace.h                               |   4 +-
 arch/x86/kvm/vmx/nested.c                          |  47 +++--
 arch/x86/kvm/vmx/vmx.c                             |  35 +++-
 arch/x86/kvm/vmx/vmx.h                             |   2 +
 arch/x86/kvm/x86.c                                 |  64 ++++---
 arch/x86/kvm/x86.h                                 |   2 +
 include/linux/kvm_host.h                           |  10 +-
 tools/testing/selftests/kvm/Makefile               |   9 +-
 .../selftests/kvm/include/x86_64/processor.h       |  27 +++
 tools/testing/selftests/kvm/lib/kvm_util.c         |   5 +
 tools/testing/selftests/kvm/lib/x86_64/processor.c |  20 ++-
 tools/testing/selftests/kvm/x86_64/evmcs_test.c    |   5 +-
 tools/testing/selftests/kvm/x86_64/smm_test.c      | 157 +++++++++++++++++
 tools/testing/selftests/kvm/x86_64/state_test.c    |  15 +-
 virt/kvm/irqchip.c                                 |   5 +-
 virt/kvm/kvm_main.c                                |   6 +-
 25 files changed, 496 insertions(+), 212 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/x86_64/smm_test.c
```
#### [PATCH v2 1/7] KVM: lapic: Hard cap the auto-calculated timer advancement
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
To minimize the latency of timer interrupts as observed by the guest,
KVM adjusts the values it programs into the host timers to account for
the host's overhead of programming and handling the timer event.  Now
that the timer advancement is automatically tuned during runtime, it's
effectively unbounded by default, e.g. if KVM is running as L1 the
advancement can measure in hundreds of milliseconds.

Place a somewhat arbitrary hard cap of 5000ns on the auto-calculated
advancement, as large advancements can break reasonable assumptions of
the guest, e.g. that a timer configured to fire after 1ms won't arrive
on the next instruction.  Although KVM busy waits to mitigate the timer
event arriving too early, complications can arise when shifting the
interrupt too far, e.g. vmx.flat/interrupt in kvm-unit-tests will fail
when its "host" exits on interrupts (because the INTR is injected before
the gets executes STI+HLT).  Arguably the unit test is "broken" in the
sense that delaying the timer interrupt by 1ms doesn't technically
guarantee the interrupt will arrive after STI+HLT, but it's a reasonable
assumption that KVM should support.

Furthermore, an unbounded advancement also effectively unbounds the time
spent busy waiting, e.g. if the guest programs a timer with a very large
delay.

Arguably the advancement logic could simply be disabled when running as
L1, but KVM needs to bound the advancement time regardless, e.g. if the
TSC is unstable and the calculations get wildly out of whack.  And
allowing the advancement when running as L1 is a good stress test of
sorts for the logic.

Cc: Liran Alon <liran.alon@oracle.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Fixes: 3b8a5df6c4dc6 ("KVM: LAPIC: Tune lapic_timer_advance_ns automatically")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/lapic.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH v3 1/9] KVM: lapic: Hard cap the auto-calculated timer advancement
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
To minimize the latency of timer interrupts as observed by the guest,
KVM adjusts the values it programs into the host timers to account for
the host's overhead of programming and handling the timer event.  Now
that the timer advancement is automatically tuned during runtime, it's
effectively unbounded by default, e.g. if KVM is running as L1 the
advancement can measure in hundreds of milliseconds.

Place a somewhat arbitrary hard cap of 5000ns on the auto-calculated
advancement, as large advancements can break reasonable assumptions of
the guest, e.g. that a timer configured to fire after 1ms won't arrive
on the next instruction.  Although KVM busy waits to mitigate the timer
event arriving too early, complications can arise when shifting the
interrupt too far, e.g. vmx.flat/interrupt in kvm-unit-tests will fail
when its "host" exits on interrupts (because the INTR is injected before
the gets executes STI+HLT).  Arguably the unit test is "broken" in the
sense that delaying the timer interrupt by 1ms doesn't technically
guarantee the interrupt will arrive after STI+HLT, but it's a reasonable
assumption that KVM should support.

Furthermore, an unbounded advancement also effectively unbounds the time
spent busy waiting, e.g. if the guest programs a timer with a very large
delay.

Arguably the advancement logic could simply be disabled when running as
L1, but KVM needs to bound the advancement time regardless, e.g. if the
TSC is unstable and the calculations get wildly out of whack.  And
allowing the advancement when running as L1 is a good stress test of
sorts for the logic.

Cc: Liran Alon <liran.alon@oracle.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Fixes: 3b8a5df6c4dc6 ("KVM: LAPIC: Tune lapic_timer_advance_ns automatically")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/lapic.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [kvm-unit-tests v3 PATCH] s390x: Add a test for the diagnose 0x308 hypercall
##### From: Thomas Huth <thuth@redhat.com>

```c
The original idea for this test is to have an easy way to check for a
problem that has been fixed in QEMU recently: QEMU simply aborted if this
diagnose call was called with an unsupported subcode (e.g. 2). The problem
has been fixed in QEMU commit 37dbd1f4d4805edcd18d94eb202bb3461b3cd52d
("Return specification exception for unimplemented diag 308 subcodes"),
and this test now should make sure that we do not regress here again.
While we're at it, also check whether LOAD NORMAL via subcode 1 works
correctly, whether the diagnose call is blocked correctly in problem state
and whether subcodes 5 and 6 are generating specification exceptions for
illegal parameters as expected.

Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 v3: Use "d" in assembler constraints instead of "a"

 s390x/Makefile      |   1 +
 s390x/diag308.c     | 130 ++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg |   3 +
 3 files changed, 134 insertions(+)
 create mode 100644 s390x/diag308.c

```
#### [PATCH] KVM: x86: Consider LAPIC TSC-Deadline timer expired if deadline too short
##### From: Liran Alon <liran.alon@oracle.com>

```c
If guest sets MSR_IA32_TSCDEADLINE to value such that in host
time-domain it's shorter than lapic_timer_advance_ns, we can
reach a case that we call hrtimer_start() with expiration time set at
the past.

Because lapic_timer.timer is init with HRTIMER_MODE_ABS_PINNED, it
is not allowed to run in softirq and therefore will never expire.

To avoid such a scenario, verify that deadline expiration time is set on
host time-domain further than (now + lapic_timer_advance_ns).

A future patch can also consider adding a min_timer_deadline_ns module parameter,
similar to min_timer_period_us to avoid races that amount of ns it takes
to run logic could still call hrtimer_start() with expiration timer set
at the past.

Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/lapic.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
#### [PATCH] kvm: x86: Fix several SPTE mask calculation errors caused by MKTME
##### From: Kai Huang <kai.huang@linux.intel.com>

```c
With both Intel MKTME and AMD SME/SEV, physical address bits are reduced
due to several high bits of physical address are repurposed for memory
encryption. To honor such behavior those repurposed bits are reduced from
cpuinfo_x86->x86_phys_bits for both Intel MKTME and AMD SME/SEV, thus
boot_cpu_data.x86_phys_bits doesn't hold physical address bits reported
by CPUID anymore.

KVM uses boot_cpu_data.x86_phys_bits to calculate several SPTE masks
based on assumption that: 1) boot_cpu_data.x86_phys_bits equals to
physical address bits reported by CPUID -- this is used to check CPU has
reserved bits when KVM calculates shadow_mmio_{value|mask}; and whether
shadow_nonpresent_or_rsvd_mask should be setup (KVM assumes L1TF is not
present if CPU has 52 physical address bits); 2) if it is smaller than
52, bits [x86_phys_bits, 51] are reserved bits.

With Intel MKTME or AMD SME/SEV above assumption is not valid any more,
especially when calculating reserved bits with Intel MKTME, since Intel
MKTME treats the reduced bits as 'keyID', thus they are not reduced
bits, therefore boot_cpu_data.x86_phys_bits cannot be used to calcualte
reserved bits anymore, although we can still use it for AMD SME/SEV
since SME/SEV treats the reduced bits differently -- they are treated as
reserved bits, the same as other reserved bits in page table entity [1].

Fix by introducing a new 'shadow_first_rsvd_bit' variable in kvm x86 MMU
code to store the actual position of reserved bits -- for Intel MKTME,
it equals to physical address reported by CPUID, and for AMD SME/SEV, it
is boot_cpu_data.x86_phys_bits. And in reserved bits related calculation
it is used instead of boot_cpu_data.x86_phys_bits. Some other code
changes too to make code more reasonable, ie, kvm_set_mmio_spte_mask is
moved to x86/kvm/mmu.c from x86/kvm/x86.c to use shadow_first_rsvd_bit;
shadow_nonpresent_or_rsvd_mask calculation logic is slightly changed,
based on the fact that only Intel CPU is impacted by L1TF, so that KVM
can use shadow_first_rsvd_bit to check whether KVM should set
shadow_nonpresent_or_rsvd_mask or not.

Note that for the physical address bits reported to guest should remain
unchanged -- KVM should report physical address reported by CPUID to
guest, but not boot_cpu_data.x86_phys_bits. Because for Intel MKTME,
there's no harm if guest sets up 'keyID' bits in guest page table (since
MKTME only works at physical address level), and KVM doesn't even expose
MKTME to guest. Arguably, for AMD SME/SEV, guest is aware of SEV thus it
should adjust boot_cpu_data.x86_phys_bits when it detects SEV, therefore
KVM should still reports physcial address reported by CPUID to guest.

[1] Section 7.10.1 Determining Support for Secure Memory Encryption,
    AMD Architecture Programmer's Manual Volume 2: System Programming).

Signed-off-by: Kai Huang <kai.huang@linux.intel.com>
---
 arch/x86/kvm/mmu.c | 152 +++++++++++++++++++++++++++++++++++++++++++----------
 arch/x86/kvm/mmu.h |   1 +
 arch/x86/kvm/x86.c |  29 ----------
 3 files changed, 125 insertions(+), 57 deletions(-)

```
#### [PATCH v3 1/1] vfio-ccw: Prevent quiesce function going into an infinite loop
##### From: Farhan Ali <alifm@linux.ibm.com>

```c
The quiesce function calls cio_cancel_halt_clear() and if we
get an -EBUSY we go into a loop where we:
	- wait for any interrupts
	- flush all I/O in the workqueue
	- retry cio_cancel_halt_clear

During the period where we are waiting for interrupts or
flushing all I/O, the channel subsystem could have completed
a halt/clear action and turned off the corresponding activity
control bits in the subchannel status word. This means the next
time we call cio_cancel_halt_clear(), we will again start by
calling cancel subchannel and so we can be stuck between calling
cancel and halt forever.

Rather than calling cio_cancel_halt_clear() immediately after
waiting, let's try to disable the subchannel. If we succeed in
disabling the subchannel then we know nothing else can happen
with the device.

Suggested-by: Eric Farman <farman@linux.ibm.com>
Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
---
ChangeLog:
v2 -> v3
   - Log an error message when cio_cancel_halt_clear
     returns EIO and break out of the loop.
   
   - Did not include past change log as the other patches
     of the original series have been queued by Conny.
     Old series (v2) can be found here:
     https://marc.info/?l=kvm&m=155475754101769&w=2

 drivers/s390/cio/vfio_ccw_drv.c | 32 ++++++++++++++++++--------------
 1 file changed, 18 insertions(+), 14 deletions(-)

```
#### [PATCH] vhost/scsi: drop unnecessary smp_mb__after_atomic()
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
The vhost_scsi.ko code used several atomic variables at one point.
Later they were dropped or converted to regular ints protected by a
mutex.

The commit that made these changes left an unused smp_mb__after_atomic()
in vhost_scsi_set_endpoint().  It was previously used after incrementing
vhost_scsi->vhost_ref_cnt but this field has been dropped:

  -     atomic_inc(&vs->vhost_ref_cnt);
        smp_mb__after_atomic_inc();

Reported-by: Andrea Parri <andrea.parri@amarulasolutions.com>
Fixes: 101998f6fcd680 ("tcm_vhost: Post-merge review changes requested by MST")
Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 drivers/vhost/scsi.c | 1 -
 1 file changed, 1 deletion(-)

```
