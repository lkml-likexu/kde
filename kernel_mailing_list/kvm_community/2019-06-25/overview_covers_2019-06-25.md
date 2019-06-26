

#### [PATCH v5 0/2] Use DIAG318 to set Control Program Name & Version
##### From: Collin Walling <walling@linux.ibm.com>

```c

Changelog:

    v5
        - s/cpc/diag318_info in order to make the relevant data more clear
        - removed mutex locks for diag318_info get/set

    v4
        - removed setup.c changes introduced in bullet 1 of v3
        - kept diag318_info struct cleanup
        - analogous QEMU patches:
            https://lists.gnu.org/archive/html/qemu-devel/2019-05/msg00164.html

    v3
        - kernel patch for diag 0x318 instruction call fixup [removed in v4]
        - removed CPU model code
        - cleaned up diag318_info struct
        - cpnc is no longer unshadowed as it was not needed
        - rebased on 5.1.0-rc3

This instruction call is executed once-and-only-once during Kernel setup.
The availability of this instruction depends on Read Info byte 134, bit 0.

DIAG 318's functionality is also emulated by KVM, which means we can enable 
this feature for a guest even if the host kernel cannot support it. This
feature is made available starting with the zEC12-full model (see analogous
QEMU patches).

The diag318_info is composed of a Control Program Name Code (CPNC) and a
Control Program Version Code (CPVC). These values are used for problem 
diagnosis and allows IBM to identify control program information by answering 
the following question:

    "What environment is this guest running in?" (CPNC)
    "What are more details regarding the OS?" (CPVC)

In the future, we will implement the CPVC to convey more information about the 
OS. For now, we set this field to 0 until we come up with a solid plan.

Collin Walling (2):
  s390/setup: diag318: refactor struct
  s390/kvm: diagnose 318 handling

 Documentation/virtual/kvm/devices/vm.txt | 14 ++++++
 arch/s390/include/asm/diag.h             |  6 +--
 arch/s390/include/asm/kvm_host.h         |  5 +-
 arch/s390/include/uapi/asm/kvm.h         |  4 ++
 arch/s390/kernel/setup.c                 |  3 +-
 arch/s390/kvm/diag.c                     | 17 +++++++
 arch/s390/kvm/kvm-s390.c                 | 81 ++++++++++++++++++++++++++++++++
 arch/s390/kvm/kvm-s390.h                 |  1 +
 arch/s390/kvm/vsie.c                     |  2 +
 9 files changed, 126 insertions(+), 7 deletions(-)
```
