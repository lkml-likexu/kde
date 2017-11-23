

#### [RFC PATCH v1 00/10] vfio-ccw channel program rework
##### From: Eric Farman <farman@linux.ibm.com>

```c

Hi Connie, Pierre,

This is a first round of rework to vfio-ccw that I've been cooking to
make the channel program handler easier to understand.  My apologies
for the number of patches; as there are some intersections within them
I couldn't break them up without forcing them to be applied in a
particular order.  I imagine that since there will probably need to be
some discussion, an RFC tag makes sense and one giant series will be
fine for now.  I can break them up for later versions if desired.

(Sidebar: I'm leaving next Thursday for an early start on the US
Thanksgiving holiday.  So if you are busy and can't get to this,
no problem!  Now where did I leave Pierre's rework patches...  :)

Patch summary:

1-2:	Fixes for cleanup on error paths
3:	Code simplication
4-6:	Simplify the ccwchain processing
7-10:	Simplify the pfn_array processing

The first few patches are very straightforward, if unlikely to occur.
They could even be considered candidates for 4.20, if so inclined.

The ccwchain patches are the result of two observations about how we
currently process a channel program and its component CCWs.  One is a
duplicate set of code for a Transfer In Channel (TIC) CCW versus any
other type, which provides an easy opportunity for simplification when
all it's trying to handle is a memory jump.  The other is a duplication
between a direct-addressed CCW and an Indirect Data Address (IDA) CCW.
There is currently the nuance that the direct CCW path creates:

  ch_pat->pfn_array_table[1]->pfn_array[#pages]

while an IDA CCW creates:

  ch_pat->pfn_array_table[#idaws]->pfn_array[1]

It might not be obvious, but #pages is calculated identically to #idaws,
as highlighted by patch 7.  By removing these duplications, we set the
stage for the next patches, which can eliminate an array entirely.

The pfn_array patches permit a non-contiguous array of addresses to be
passed to pfn_array_alloc(_pin), which in turn permits the removal of
struct pfn_array_table and a squashing of our arrays.  Thus, instead of
either of the two nested arrays described above, we have:

  ch_pa->pfn_array[#idaws]

(Doesn't that look nice?!)

The last two patches in this series should be squashed together; I just
left them apart in the RFC to make it easier to see how turn-key this
becomes after the complexities of the previous patches, and without the
noise of realigning the code afterward.  (Sorry, kbuild robot.)

While this series provides no functionality changes, I find that
sizeof(vfio_ccw.ko) decreases by about 7 percent according to the
bloat-o-meter, and we remove some of the malloc load for a given
channel program.  Hopefully there's also an increase in Readability,
Understandability, and Maintainability too!

Eric Farman (10):
  s390/cio: Fix cleanup of pfn_array alloc failure
  s390/cio: Fix cleanup when unsupported IDA format is used
  s390/cio: Squash cp_free and cp_unpin_free
  s390/cio: Breakout the processing of a channel program
  s390/cio: Use common channel program processor for TIC
  s390/cio: Combine ccwchain_fetch _idal and _direct
  s390/cio: Tell pfn_array_alloc_pin to pin pages, not bytes
  s390/cio: Split pfn_array_alloc_pin into pieces
  s390/cio: Eliminate the pfn_array_table struct
  s390/cio: Remove unused function/variables FIXUP

 drivers/s390/cio/vfio_ccw_cp.c | 416 +++++++++++++++--------------------------
 drivers/s390/cio/vfio_ccw_cp.h |   1 +
 2 files changed, 150 insertions(+), 267 deletions(-)
```
#### [PATCH 0/7] iommu/amd: Always allow to map huge pages
##### From: Joerg Roedel <joro@8bytes.org>

```c

Hi,

the AMD IOMMU driver had an issue for a long time where it
didn't allow to map a huge-page when smaller mappings
existed at that address range before. The VFIO driver even
had a workaround for that behavior.

These patches fix the issue and remove the workaround from
the VFIO driver.

Please review.

Thanks,

	Joerg

Joerg Roedel (7):
  iommu/amd: Collect page-table pages in freelist
  iommu/amd: Introduce free_sub_pt() function
  iommu/amd: Ignore page-mode 7 in free_sub_pt()
  iommu/amd: Allow downgrading page-sizes in alloc_pte()
  iommu/amd: Restart loop if cmpxchg64 succeeded in alloc_pte()
  iommu/amd: Allow to upgrade page-size
  vfio/type1: Remove map_try_harder() code path

 drivers/iommu/amd_iommu.c       | 204 +++++++++++++++++++++-----------
 drivers/iommu/amd_iommu_types.h |   1 +
 drivers/vfio/vfio_iommu_type1.c |  33 +-----
 3 files changed, 137 insertions(+), 101 deletions(-)
```
#### [PATCH 0/2] kvm: Use huge pages for DAX-backed files
##### From: Barret Rhoden <brho@google.com>

```c

This patch series depends on dax pages not being PageReserved.  Once
that is in place, these changes will let KVM use huge pages with
dax-backed files.  Without the PageReserved change, KVM and DAX still
work with these patches, simply without huge pages - which is the
current situation.

RFC/discussion thread:
https://lore.kernel.org/lkml/20181029210716.212159-1-brho@google.com/

Barret Rhoden (2):
  mm: make dev_pagemap_mapping_shift() externally visible
  kvm: Use huge pages for DAX-backed files

 arch/x86/kvm/mmu.c  | 34 ++++++++++++++++++++++++++++++++--
 include/linux/mm.h  |  3 +++
 mm/memory-failure.c | 38 +++-----------------------------------
 mm/util.c           | 34 ++++++++++++++++++++++++++++++++++
 4 files changed, 72 insertions(+), 37 deletions(-)
```
