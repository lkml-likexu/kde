#### [PATCH 1/7] KVM: lapic: Hard cap the auto-calculated timer advancement
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
#### [PATCH v9 1/3] vfio/mdev: Add iommu related member in mdev_device
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
A parent device might create different types of mediated
devices. For example, a mediated device could be created
by the parent device with full isolation and protection
provided by the IOMMU. One usage case could be found on
Intel platforms where a mediated device is an assignable
subset of a PCI, the DMA requests on behalf of it are all
tagged with a PASID. Since IOMMU supports PASID-granular
translations (scalable mode in VT-d 3.0), this mediated
device could be individually protected and isolated by an
IOMMU.

This patch adds a new member in the struct mdev_device to
indicate that the mediated device represented by mdev could
be isolated and protected by attaching a domain to a device
represented by mdev->iommu_device. It also adds a helper to
add or set the iommu device.

* mdev_device->iommu_device
  - This, if set, indicates that the mediated device could
    be fully isolated and protected by IOMMU via attaching
    an iommu domain to this device. If empty, it indicates
    using vendor defined isolation, hence bypass IOMMU.

* mdev_set/get_iommu_device(dev, iommu_device)
  - Set or get the iommu device which represents this mdev
    in IOMMU's device scope. Drivers don't need to set the
    iommu device if it uses vendor defined isolation.

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Liu Yi L <yi.l.liu@intel.com>
Suggested-by: Kevin Tian <kevin.tian@intel.com>
Suggested-by: Alex Williamson <alex.williamson@redhat.com>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
Reviewed-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Reviewed-by: Kirti Wankhede <kwankhede@nvidia.com>
Acked-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/mdev/mdev_core.c    | 18 ++++++++++++++++++
 drivers/vfio/mdev/mdev_private.h |  1 +
 include/linux/mdev.h             | 14 ++++++++++++++
 3 files changed, 33 insertions(+)

```
#### [PATCH] x86/kvm: move kvm_load/put_guest_xcr0 into atomic context
##### From: WANG Chao <chao.wang@ucloud.cn>

```c
guest xcr0 could leak into host when MCE happens in guest mode. Because
do_machine_check() could schedule out at a few places.

For example:

kvm_load_guest_xcr0
...
kvm_x86_ops->run(vcpu) {
  vmx_vcpu_run
    vmx_complete_atomic_exit
      kvm_machine_check
        do_machine_check
          do_memory_failure
            memory_failure
              lock_page

In this case, host_xcr0 is 0x2ff, guest vcpu xcr0 is 0xff. After schedule
out, host cpu has guest xcr0 loaded (0xff).

In __switch_to {
     switch_fpu_finish
       copy_kernel_to_fpregs
         XRSTORS

If any bit i in XSTATE_BV[i] == 1 and xcr0[i] == 0, XRSTORS will
generate #GP (In this case, bit 9). Then ex_handler_fprestore kicks in
and tries to reinitialize fpu by restoring init fpu state. Same story as
last #GP, except we get DOUBLE FAULT this time.

Cc: stable@vger.kernel.org
Signed-off-by: WANG Chao <chao.wang@ucloud.cn>
---
 arch/x86/kvm/svm.c     |  2 ++
 arch/x86/kvm/vmx/vmx.c |  4 ++++
 arch/x86/kvm/x86.c     | 10 ++++------
 arch/x86/kvm/x86.h     |  2 ++
 4 files changed, 12 insertions(+), 6 deletions(-)

```
