

#### [PATCH v2 0/2] Simplify mtty driver and mdev core
##### From: Parav Pandit <parav@mellanox.com>

```c

Currently mtty sample driver uses mdev state and UUID in convoluated way to
generate an interrupt.
It uses several translations from mdev_state to mdev_device to mdev uuid.
After which it does linear search of long uuid comparision to
find out mdev_state in mtty_trigger_interrupt().
mdev_state is already available while generating interrupt from which all
such translations are done to reach back to mdev_state.

This translations are done during interrupt generation path.
This is unnecessary and reduandant.

Hence,
Patch-1 simplifies mtty sample driver to directly use mdev_state.

Patch-2, Since no production driver uses mdev_uuid(), simplifies and
removes redandant mdev_uuid() exported symbol.
---
Changelog:
v1->v2:
 - Corrected email of Kirti
 - Updated cover letter commit log to address comment from Cornelia
 - Added Reviewed-by tag
v0->v1:
 - Updated commit log

Parav Pandit (2):
  vfio-mdev/mtty: Simplify interrupt generation
  vfio/mdev: Removed unused and redundant API for mdev UUID

 drivers/vfio/mdev/mdev_core.c |  6 ------
 include/linux/mdev.h          |  1 -
 samples/vfio-mdev/mtty.c      | 39 +++++++----------------------------
 3 files changed, 8 insertions(+), 38 deletions(-)
```
#### [PATCH v3 0/7] x86: KVM: svm: get rid of hardcoded instructions
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v2 [Sean Christopherson]:
- Add Reviewed-by tags:
- PATCH2 replaced with the suggested "x86: kvm: svm: propagate errors from
  skip_emulated_instruction()" approach.
- PATCH5 split into three separating vmrun_interception() from others and
  implementing the suggested solution.

Original description:

Jim rightfully complains that hardcoding instuctions lengths is not always
correct: additional (redundant) prefixes can be used. Luckily, the ugliness
is mostly harmless: modern AMD CPUs support NRIP_SAVE feature but I'd like
to clean things up and sacrifice speed in favor of correctness.

Vitaly Kuznetsov (7):
  x86: KVM: svm: don't pretend to advance RIP in case
    wrmsr_interception() results in #GP
  x86: kvm: svm: propagate errors from skip_emulated_instruction()
  x86: KVM: clear interrupt shadow on EMULTYPE_SKIP
  x86: KVM: add xsetbv to the emulator
  x86: KVM: svm: remove hardcoded instruction length from intercepts
  x86: KVM: svm: eliminate weird goto from vmrun_interception()
  x86: KVM: svm: eliminate hardcoded RIP advancement from
    vmrun_interception()

 arch/x86/include/asm/kvm_emulate.h |  3 +-
 arch/x86/include/asm/kvm_host.h    |  2 +-
 arch/x86/kvm/emulate.c             | 23 ++++++-
 arch/x86/kvm/svm.c                 | 98 +++++++++++++-----------------
 arch/x86/kvm/vmx/vmx.c             |  8 ++-
 arch/x86/kvm/x86.c                 | 13 +++-
 6 files changed, 83 insertions(+), 64 deletions(-)
```
