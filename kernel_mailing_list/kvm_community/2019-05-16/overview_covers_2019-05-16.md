

#### [PATCH v3 0/5] KVM: LAPIC: Optimize timer latency further
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c

Advance lapic timer tries to hidden the hypervisor overhead between the 
host emulated timer fires and the guest awares the timer is fired. However, 
it just hidden the time between apic_timer_fn/handle_preemption_timer -> 
wait_lapic_expire, instead of the real position of vmentry which is 
mentioned in the orignial commit d0659d946be0 ("KVM: x86: add option to 
advance tscdeadline hrtimer expiration"). There is 700+ cpu cycles between 
the end of wait_lapic_expire and before world switch on my haswell desktop.

This patchset tries to narrow the last gap(wait_lapic_expire -> world switch), 
it takes the real overhead time between apic_timer_fn/handle_preemption_timer
and before world switch into consideration when adaptively tuning timer 
advancement. The patchset can reduce 40% latency (~1600+ cycles to ~1000+ 
cycles on a haswell desktop) for kvm-unit-tests/tscdeadline_latency when 
testing busy waits.

v2 -> v3:
 * expose 'kvm_timer.timer_advance_ns' to userspace
 * move the tracepoint below guest_exit_irqoff()
 * move wait_lapic_expire() before flushing the L1

v1 -> v2:
 * fix indent in patch 1/4
 * remove the wait_lapic_expire() tracepoint and expose by debugfs
 * move the call to wait_lapic_expire() into vmx.c and svm.c

Wanpeng Li (5):
  KVM: LAPIC: Extract adaptive tune timer advancement logic
  KVM: LAPIC: Fix lapic_timer_advance_ns parameter overflow
  KVM: LAPIC: Expose per-vCPU timer_advance_ns to userspace
  KVM: LAPIC: Delay trace advance expire delta
  KVM: LAPIC: Optimize timer latency further

 arch/x86/kvm/debugfs.c | 16 +++++++++++++
 arch/x86/kvm/lapic.c   | 62 +++++++++++++++++++++++++++++---------------------
 arch/x86/kvm/lapic.h   |  3 ++-
 arch/x86/kvm/svm.c     |  4 ++++
 arch/x86/kvm/vmx/vmx.c |  4 ++++
 arch/x86/kvm/x86.c     |  7 +++---
 6 files changed, 65 insertions(+), 31 deletions(-)
```
#### [PATCH net 0/4] Prevent vhost kthread from hogging CPU
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi:

This series try to prvernt a guest triggerable CPU hogging through
vhost kthread. This is done by introducing and checking the weight
after each requrest. The patch has been tested with reproducer of
vsock and virtio-net. Only compile test is done for vhost-scsi.

Please review.

This addresses CVE-2019-3900.

Jason Wang (4):
  vhost: introduce vhost_exceeds_weight()
  vhost_net: fix possible infinite loop
  vhost: vsock: add weight support
  vhost: scsi: add weight support

 drivers/vhost/net.c   | 41 ++++++++++++++---------------------------
 drivers/vhost/scsi.c  | 21 ++++++++++++++-------
 drivers/vhost/vhost.c | 20 +++++++++++++++++++-
 drivers/vhost/vhost.h |  5 ++++-
 drivers/vhost/vsock.c | 28 +++++++++++++++++++++-------
 5 files changed, 72 insertions(+), 43 deletions(-)
```
#### [PATCH v1 0/6] KVM: VMX: Intel PT configuration switch using
##### From: Luwei Kang <luwei.kang@intel.com>

```c

This patch set is mainly used for reduce the overhead of switch
Intel PT configuation contex on VM-Entry/Exit by XSAVES/XRSTORS
instructions.

I measured the cycles number of context witch on Manual and
XSAVES/XRSTORES by rdtsc, and the data as below:

Manual save(rdmsr):     ~334  cycles
Manual restore(wrmsr):  ~1668 cycles

XSAVES insturction:     ~124  cycles
XRSTORS instruction:    ~378  cycles

Manual: Switch the configuration by rdmsr and wrmsr instruction,
        and there have 8 registers need to be saved or restore.
        They are IA32_RTIT_OUTPUT_BASE, *_OUTPUT_MASK_PTRS,
        *_STATUS, *_CR3_MATCH, *_ADDR0_A, *_ADDR0_B,
        *_ADDR1_A, *_ADDR1_B.
XSAVES/XRSTORS: Switch the configuration context by XSAVES/XRSTORS
        instructions. This patch set will allocate separate
        "struct fpu" structure to save host and guest PT state.
        Only a small portion of this structure will be used because
        we only save/restore PT state (not save AVX, AVX-512, MPX,
        PKRU and so on).

This patch set also do some code clean e.g. patch 2 will reuse
the fpu pt_state to save the PT configuration contex and
patch 3 will dymamic allocate Intel PT configuration state.

Luwei Kang (6):
  x86/fpu: Introduce new fpu state for Intel processor trace
  KVM: VMX: Reuse the pt_state structure for PT context
  KVM: VMX: Dymamic allocate Intel PT configuration state
  KVM: VMX: Allocate XSAVE area for Intel PT configuration
  KVM: VMX: Intel PT configration context switch using XSAVES/XRSTORS
  KVM: VMX: Get PT state from xsave area to variables

 arch/x86/include/asm/fpu/types.h |  13 ++
 arch/x86/kvm/vmx/nested.c        |   2 +-
 arch/x86/kvm/vmx/vmx.c           | 338 ++++++++++++++++++++++++++-------------
 arch/x86/kvm/vmx/vmx.h           |  21 +--
 4 files changed, 243 insertions(+), 131 deletions(-)
```
#### [RFC PATCH 0/4] KVM selftests for s390x
##### From: Thomas Huth <thuth@redhat.com>

```c

This patch series enables the KVM selftests for s390x. As a first
test, the sync_regs from x86 has been adapted to s390x.

Please note that the ucall() interface is not used yet - since
s390x neither has PIO nor MMIO, this needs some more work first
before it becomes usable (we likely should use a DIAG hypercall
here, which is what the sync_reg test is currently using, too...).

Thomas Huth (4):
  KVM: selftests: Guard struct kvm_vcpu_events with
    __KVM_HAVE_VCPU_EVENTS
  KVM: selftests: Align memory region addresses to 1M on s390x
  KVM: selftests: Add processor code for s390x
  KVM: selftests: Add the sync_regs test for s390x

 MAINTAINERS                                   |   2 +
 tools/testing/selftests/kvm/Makefile          |   3 +
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 .../selftests/kvm/include/s390x/processor.h   |  22 ++
 tools/testing/selftests/kvm/lib/kvm_util.c    |  24 +-
 .../selftests/kvm/lib/s390x/processor.c       | 277 ++++++++++++++++++
 .../selftests/kvm/s390x/sync_regs_test.c      | 151 ++++++++++
 7 files changed, 476 insertions(+), 5 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/s390x/processor.h
 create mode 100644 tools/testing/selftests/kvm/lib/s390x/processor.c
 create mode 100644 tools/testing/selftests/kvm/s390x/sync_regs_test.c
```
#### [PATCH v3 0/3] s390: vfio-ccw fixes
##### From: Eric Farman <farman@linux.ibm.com>

```c

Here are the remaining patches in my fixes series, to handle the more
involved scenario of channel programs that do not move any actual data
to/from the device.  They were reordered per feedback from v2, which
means they received minor massaging because of overlapping code and
some cleanup to the commit messages.

They are based on Conny's vfio-ccw tree.  :)

Changelog:
 v2 -> v3:
  - Patches 1-4:
     - [Farhan] Added r-b
     - [Cornelia] Queued to vfio-ccw, dropped from this version
  - Patches 5/6:
     - [Cornelia/Farhan] Swapped the order of these patches, minor
       rework on the placement of bytes/idaw_nr variables and the
       commit messages that resulted.
 v2: https://patchwork.kernel.org/cover/10944075/
 v1: https://patchwork.kernel.org/cover/10928799/

Eric Farman (3):
  s390/cio: Don't pin vfio pages for empty transfers
  s390/cio: Allow zero-length CCWs in vfio-ccw
  s390/cio: Remove vfio-ccw checks of command codes

 drivers/s390/cio/vfio_ccw_cp.c | 92 ++++++++++++++++++++++++----------
 1 file changed, 65 insertions(+), 27 deletions(-)
```
