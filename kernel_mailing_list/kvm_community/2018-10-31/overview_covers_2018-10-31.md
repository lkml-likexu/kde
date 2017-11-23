

#### [kvm PATCH v5 0/4] shrink vcpu_vmx down to order 2
##### From: Marc Orr <marcorr@google.com>

```c

Compared to the last version of these patches, I've acted on Dave
Hansen's suggestions to get rid of redundant fpu storage and move it out
of the kvm_vcpu_arch struct.

For now, I've left the vmalloc patches in the series, but we might end
up dropping them. Thus, I've have not responded to Sean Christopherson's
review on those patches yet.

Marc Orr (4):
  kvm: x86: Use task structs fpu field for user
  kvm: x86: Dynamically allocate guest_fpu
  kvm: vmx: refactor vmx_msrs struct for vmalloc
  kvm: vmx: use vmalloc() to allocate vcpus

 arch/x86/include/asm/kvm_host.h |  10 ++--
 arch/x86/kvm/svm.c              |  10 ++++
 arch/x86/kvm/vmx.c              | 102 +++++++++++++++++++++++++++++---
 arch/x86/kvm/x86.c              |  49 ++++++++++-----
 virt/kvm/kvm_main.c             |  28 +++++----
 5 files changed, 159 insertions(+), 40 deletions(-)
```
#### [PATCH v1 0/7] s390: vfio: ap: Using GISA for AP Interrupt
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

This is the first version to handle AP Interrupt
using the GISA facility.
The patch series is based on the GISA+GIB patch series
sent by Michael Mueller.

- We define a new VFIO ioctl to ask the vfio_ap driver to register
  a interruption for the guest.
- We define the assembler code to register a GISA based interruption
  for the guest.
- We register to the GIB Alert mechanism and suppress the GISA
  (firmware) based interrupts from the list of software handled
  interrupts.

This patch series has been tested with success on z13 and z14
with adjunct processors CEX5[ACP] and CEX6C.

To use, you, of course, need the QEMU patches, which will be sent
separately.


Pierre Morel (7):
  vfio: ap: Add AP Queue Interruption Control facility
  vfio: ap: VFIO AP Queue Interrupt Control
  vfio: ap: AP Queue Interrupt structures definitions
  vfio: ap: AP Queue Interrupt Control VFIO ioctl calls
  s390: kvm: export GIB registration
  vfio: ap: register guest ISC with GISA and GIB
  s390: kvm: Handle all GISA IPM bits through GISA

 arch/s390/include/asm/kvm_host.h      |   3 +
 arch/s390/kvm/interrupt.c             |   3 +-
 arch/s390/tools/gen_facilities.c      |   1 +
 drivers/s390/crypto/vfio_ap_ops.c     | 105 ++++++++++++++++++++++++++
 drivers/s390/crypto/vfio_ap_private.h |  77 +++++++++++++++++++
 include/uapi/linux/vfio.h             |  22 ++++++
 6 files changed, 209 insertions(+), 2 deletions(-)
```
#### [kvm PATCH v6 0/2] shrink vcpu_vmx down to order 2
##### From: Marc Orr <marcorr@google.com>

```c

Compared to the last version, I've:
(1) dropped the vmalloc patches
(2) updated the kmem cache for the guest_fpu field in the kvm_vcpu_arch
    struct to be sized according to fpu_kernel_xstate_size
(3) Added minimum FPU checks in KVM's x86 init logic to avoid memory
    corruption issues.

Marc Orr (2):
  kvm: x86: Use task structs fpu field for user
  kvm: x86: Dynamically allocate guest_fpu

 arch/x86/include/asm/kvm_host.h | 10 +++---
 arch/x86/kvm/svm.c              | 10 ++++++
 arch/x86/kvm/vmx.c              | 10 ++++++
 arch/x86/kvm/x86.c              | 55 ++++++++++++++++++++++++---------
 4 files changed, 65 insertions(+), 20 deletions(-)
```
