

#### [PATCH v1 0/2] KVM: s390: Tracing APCB changes
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

In the first patch we define kvm_arch_crypto_set_masks,
a new function to centralize the setup the APCB masks
inside the CRYCB SIE satelite and add KVM_EVENT() to
kvm_arch_crypto_set_masks and kvm_arch_crypto_clear_masks.

In the second patch we replace the vfio_ap_mdev_copy_masks()
by the new kvm_arch_crypto_set_masks() function.


Pierre Morel (2):
  KVM: s390: Tracing APCB changes
  s390: vfio-ap: setup APCB mask using KVM dedicated function

 arch/s390/include/asm/kvm_host.h  |  2 ++
 arch/s390/kvm/kvm-s390.c          | 41 +++++++++++++++++++++++++++++++++++++++
 drivers/s390/crypto/vfio_ap_ops.c | 33 +++----------------------------
 3 files changed, 46 insertions(+), 30 deletions(-)
```
