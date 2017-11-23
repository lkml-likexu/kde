

#### [PATCH V3 0/4] Fix kvm misconceives NVDIMM pages as reserved mmio
##### From: Zhang Yi <yi.z.zhang@linux.intel.com>

```c

For device specific memory space, when we move these area of pfn to
memory zone, we will set the page reserved flag at that time, some of
these reserved for device mmio, and some of these are not, such as
NVDIMM pmem.

Now, we map these dev_dax or fs_dax pages to kvm for DIMM/NVDIMM
backend, since these pages are reserved. the check of
kvm_is_reserved_pfn() misconceives those pages as MMIO. Therefor, we
introduce 2 page map types, MEMORY_DEVICE_FS_DAX/MEMORY_DEVICE_DEV_DAX,
to indentify these pages are from NVDIMM pmem. and let kvm treat these
as normal pages.

Without this patch, Many operations will be missed due to this
mistreatment to pmem pages. For example, a page may not have chance to
be unpinned for KVM guest(in kvm_release_pfn_clean); not able to be
marked as dirty/accessed(in kvm_set_pfn_dirty/accessed) etc.

V1:
https://lkml.org/lkml/2018/7/4/91

V2:
https://lkml.org/lkml/2018/7/10/135

V3:
[PATCH V3 1/4] Needs Comments.
[PATCH V3 2/4] Update the description of MEMORY_DEVICE_DEV_DAX: Jan
[PATCH V3 3/4] Acked-by: Jan in V2
[PATCH V3 4/4] Needs Comments.

Zhang Yi (4):
  kvm: remove redundant reserved page check
  mm: introduce memory type MEMORY_DEVICE_DEV_DAX
  mm: add a function to differentiate the pages is from DAX device
    memory
  kvm: add a check if pfn is from NVDIMM pmem.

 drivers/dax/pmem.c       |  1 +
 include/linux/memremap.h |  8 ++++++++
 include/linux/mm.h       | 12 ++++++++++++
 virt/kvm/kvm_main.c      | 16 ++++++++--------
 4 files changed, 29 insertions(+), 8 deletions(-)
```
#### [patch 0/2] switch kvmclock base to CLOCK_MONOTONIC_RAW
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c

Please see individual patches for details.
```
#### [patch 0/2]  switch kvmclock base to CLOCK_MONOTONIC_RAW (v2)
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c

Please see individual patches for details.

v2: remove leftover comment
```
