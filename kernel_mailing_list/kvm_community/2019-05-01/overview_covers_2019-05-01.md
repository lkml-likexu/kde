

#### [RFC PATCH 0/5] KVM: arm64: Add support for contiguous PTE/PMD
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c

Currently, we support the following page sizes at stage2:

                PTE     PMD     PUD
               -----   -----   -----
 4K granule:     4K      2M      1G
16K granule:    16K     32M
64K granule:    64K    512M

And we have Contiguous bit[52] in stage2 VMSAv8-64 block and page
descriptors. As ARM ARM said, when the value of the Contiguous bit
is 1, it indicates that the entry is one of a number of adjacent
translation table entries that point to a contiguous output address
range.

This series add support for contiguous PTE/PMD hugepages at stage2
and then we can create huge mappings with following additional
sizes:

                CONT PTE     CONT PMD
                --------     --------
 4K granule:      64K          32M
16K granule:       2M           1G
64K granule:       2M          16G

These patches are based on v5.1.0-rc7 and have been tested on
Taishan 2280 server (D05) with 4K and 64K granule.

Any comments will be appreciated, thanks!

Zenghui Yu (5):
  KVM: arm/arm64: Introduce helpers for page table enties with
    contiguous bit
  KVM: arm/arm64: Re-factor building the stage2 page table entries
  KVM: arm/arm64: Support dirty page tracking for contiguous hugepages
  KVM: arm/arm64: Add support for creating PTE contiguous hugepages at
    stage2
  KVM: arm/arm64: Add support for creating PMD contiguous hugepages at
    stage2

 arch/arm/include/asm/kvm_mmu.h       |  22 +++
 arch/arm/include/asm/pgtable-hwdef.h |   8 +
 arch/arm64/include/asm/kvm_mmu.h     |  20 +++
 virt/kvm/arm/mmu.c                   | 299 ++++++++++++++++++++++++++++++-----
 4 files changed, 312 insertions(+), 37 deletions(-)
```
#### [PATCH v4 0/2] Use DIAG318 to set Control Program Name & Version
##### From: Collin Walling <walling@linux.ibm.com>

```c

Changelog:

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
The availability of this instruction depends on Read SCP Info byte 134, bit 0.
Diagnose318's functionality is also emulated by KVM, which means we can 
enable this feature for a guest even if the host kernel cannot support it.

The CPNC and CPVC are used for problem diagnosis and allows IBM to identify 
control program information by answering the following question:

    "What environment is this guest running in?" (CPNC)
    "What are more details regarding the OS?" (CPVC)

In the future, we will implement the Control Program Version Code (CPVC) to
convey more information about the OS. For now, we set this field to 0 until
we come up with a solid plan.

Collin Walling (2):
  s390/setup: diag318: refactor struct
  s390/kvm: diagnose 318 handling

 Documentation/virtual/kvm/devices/vm.txt | 14 ++++++
 arch/s390/include/asm/diag.h             |  6 +--
 arch/s390/include/asm/kvm_host.h         |  7 ++-
 arch/s390/include/uapi/asm/kvm.h         |  4 ++
 arch/s390/kernel/setup.c                 |  3 +-
 arch/s390/kvm/diag.c                     | 17 +++++++
 arch/s390/kvm/kvm-s390.c                 | 83 ++++++++++++++++++++++++++++++++
 arch/s390/kvm/kvm-s390.h                 |  1 +
 arch/s390/kvm/vsie.c                     |  2 +
 9 files changed, 129 insertions(+), 8 deletions(-)
```
