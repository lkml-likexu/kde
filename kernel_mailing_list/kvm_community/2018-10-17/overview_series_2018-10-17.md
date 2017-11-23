#### [PATCH] KVM: arm64: Safety check PSTATE when entering guest and handle IL
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
This commit adds a paranoid check when entering the guest to make sure
we don't attempt running guest code in an equally or more privilged mode
than the hypervisor.  We also catch other accidental programming of the
SPSR_EL2 which results in an illegal exception return and report this
safely back to the user.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 arch/arm64/include/asm/kvm_asm.h |  1 +
 arch/arm64/include/asm/ptrace.h  |  3 +++
 arch/arm64/kvm/handle_exit.c     |  7 +++++++
 arch/arm64/kvm/hyp/hyp-entry.S   | 16 +++++++++++++++-
 arch/arm64/kvm/hyp/sysreg-sr.c   | 19 ++++++++++++++++++-
 5 files changed, 44 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM/x86: Use 32bit xor to clear registers in svm.c
##### From: Uros Bizjak <ubizjak@gmail.com>

```c
x86_64 zero-extends 32bit xor operation to a full 64bit register.

Also add a comment and remove unnecessary instruction suffix in vmx.c

Signed-off-by: Uros Bizjak <ubizjak@gmail.com>
---
 arch/x86/kvm/svm.c | 28 +++++++++++++---------------
 arch/x86/kvm/vmx.c |  6 +++++-
 2 files changed, 18 insertions(+), 16 deletions(-)

```
#### [PATCH 3/3] kvm: don't redefine flags as something else
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
The function irqfd_wakeup() has flags defined as __poll_t and then it
has additional flags which is used for irqflags.

Redefine the inner flags variable as iflags so it does not shadow the
outer flags.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 virt/kvm/eventfd.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH v3 1/6] vfio/mdev: Add new "aggregate" parameter for mdev create
##### From: Zhenyu Wang <zhenyuw@linux.intel.com>

```c
For special mdev type which can aggregate instances for mdev device,
this extends mdev create interface by allowing extra "aggregate=xxx"
parameter, which is passed to mdev device model to be able to create
bundled number of instances for target mdev device.

v2: create new create_with_instances operator for vendor driver
v3:
- Change parameter name as "aggregate="
- Fix new interface comments.
- Parameter checking for new option, pass UUID string only to
  parse and properly end parameter for kstrtouint() conversion.

Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
 drivers/vfio/mdev/mdev_core.c    | 21 +++++++++++++++++----
 drivers/vfio/mdev/mdev_private.h |  4 +++-
 drivers/vfio/mdev/mdev_sysfs.c   | 32 ++++++++++++++++++++++++++++----
 include/linux/mdev.h             | 11 +++++++++++
 4 files changed, 59 insertions(+), 9 deletions(-)

```
#### [PATCH] drivers/vfio: Fix an 8-byte alignment issue
##### From: Wenwen Wang <wang6495@umn.edu>

```c
This patch adds a 4-byte reserved field in the structure
vfio_eeh_pe_op to make sure that the u64 fields in the structure
vfio_eeh_pe_err are 8-byte aligned.

Signed-off-by: Wenwen Wang <wang6495@umn.edu>
---
 include/uapi/linux/vfio.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH V6 1/5]  target/i386 : add coalesced pio support
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
add coalesced_pio's struct and KVM_CAP_COALESCED_PIO header.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 accel/kvm/kvm-all.c       | 4 ++--
 linux-headers/linux/kvm.h | 9 ++++++++-
 2 files changed, 10 insertions(+), 3 deletions(-)

```
#### [PATCH v3] drivers/vfio: Fix a redundant copy bug
##### From: Wenwen Wang <wang6495@umn.edu>

```c
In vfio_spapr_iommu_eeh_ioctl(), if the ioctl command is VFIO_EEH_PE_OP,
the user-space buffer 'arg' is copied to the kernel object 'op' and the
'argsz' and 'flags' fields of 'op' are checked. If the check fails, an
error code EINVAL is returned. Otherwise, 'op.op' is further checked
through a switch statement to invoke related handlers. If 'op.op' is
VFIO_EEH_PE_INJECT_ERR, the whole user-space buffer 'arg' is copied again
to 'op' to obtain the err information. However, in the following execution
of this case, the fields of 'op', except the field 'err', are actually not
used. That is, the second copy has a redundant part. Therefore, for both
performance consideration, the redundant part of the second copy should be
removed.

This patch removes such a part in the second copy. It only copies from
'err.type' to 'err.mask', which is exactly required by the
VFIO_EEH_PE_INJECT_ERR op.

This patch also adds a 4-byte reserved field in the structure
vfio_eeh_pe_op to make sure that the u64 fields in the structure
vfio_eeh_pe_err are 8-byte aligned.

Signed-off-by: Wenwen Wang <wang6495@umn.edu>
---
 drivers/vfio/vfio_spapr_eeh.c | 9 ++++++---
 include/uapi/linux/vfio.h     | 1 +
 2 files changed, 7 insertions(+), 3 deletions(-)

```
#### [PATCH v4] drivers/vfio: Fix a redundant copy bug
##### From: Wenwen Wang <wang6495@umn.edu>

```c
In vfio_spapr_iommu_eeh_ioctl(), if the ioctl command is VFIO_EEH_PE_OP,
the user-space buffer 'arg' is copied to the kernel object 'op' and the
'argsz' and 'flags' fields of 'op' are checked. If the check fails, an
error code EINVAL is returned. Otherwise, 'op.op' is further checked
through a switch statement to invoke related handlers. If 'op.op' is
VFIO_EEH_PE_INJECT_ERR, the whole user-space buffer 'arg' is copied again
to 'op' to obtain the err information. However, in the following execution
of this case, the fields of 'op', except the field 'err', are actually not
used. That is, the second copy has a redundant part. Therefore, for
performance consideration, the redundant part of the second copy should be
removed.

This patch removes such a part in the second copy. It only copies from
'err.type' to 'err.mask', which is exactly required by the
VFIO_EEH_PE_INJECT_ERR op.

Signed-off-by: Wenwen Wang <wang6495@umn.edu>
---
 drivers/vfio/vfio_spapr_eeh.c | 9 ++++++---
 1 file changed, 6 insertions(+), 3 deletions(-)

```
