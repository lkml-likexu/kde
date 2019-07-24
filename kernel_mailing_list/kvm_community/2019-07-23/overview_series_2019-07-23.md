#### [PATCH 1/1] virtio/s390: fix race on airq_areas[]
##### From: Halil Pasic <pasic@linux.ibm.com>

```c
The access to airq_areas was racy ever since the adapter interrupts got
introduced to virtio-ccw, but since commit 39c7dcb15892 ("virtio/s390:
make airq summary indicators DMA") this became an issue in practice as
well. Namely before that commit the airq_info that got overwritten was
still functional. After that commit however the two infos share a
summary_indicator, which aggravates the situation. Which means
auto-online mechanism occasionally hangs the boot with virtio_blk.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
Reported-by: Marc Hartmayer <mhartmay@linux.ibm.com>
Fixes: 96b14536d935 ("virtio-ccw: virtio-ccw adapter interrupt support.")
---
* We need definitely this fixed for 5.3. For older stable kernels it is
to be discussed. @Connie what do you think: do we need a cc stable?

* I have a variant that does not need the extra mutex but uses cmpxchg().
Decided to post this one because that one is more complex. But if there
is interest we can have a look at it as well.
---
 drivers/s390/virtio/virtio_ccw.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v19 01/15] arm64: untag user pointers in access_ok and __uaccess_mask_ptr
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
This patch is a part of a series that extends kernel ABI to allow to pass
tagged user pointers (with the top byte set to something else other than
0x00) as syscall arguments.

copy_from_user (and a few other similar functions) are used to copy data
from user memory into the kernel memory or vice versa. Since a user can
provided a tagged pointer to one of the syscalls that use copy_from_user,
we need to correctly handle such pointers.

Do this by untagging user pointers in access_ok and in __uaccess_mask_ptr,
before performing access validity checks.

Note, that this patch only temporarily untags the pointers to perform the
checks, but then passes them as is into the kernel internals.

Reviewed-by: Vincenzo Frascino <vincenzo.frascino@arm.com>
Reviewed-by: Kees Cook <keescook@chromium.org>
Reviewed-by: Catalin Marinas <catalin.marinas@arm.com>
Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
---
 arch/arm64/include/asm/uaccess.h | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)

```
#### [PATCH 1/6] vhost: don't set uaddr for invalid address
##### From: Jason Wang <jasowang@redhat.com>

```c
We should not setup uaddr for the invalid address, otherwise we may
try to pin or prefetch mapping of wrong pages.

Fixes: 7f466032dc9e ("vhost: access vq metadata through kernel virtual address")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: init x2apic_enabled() once
##### From: luferry@163.com

```c
From: luferry <luferry@163.com>

x2apic_eanbled() costs about 200 cycles
when guest trigger halt pretty high, pi ops in hotpath

Signed-off-by: luferry <luferry@163.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)

```
#### [1/1] kvm-unit-tests: s390: test for gen15a/b cpu model dependencies
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
This adds a test for the cpu model gen15a/b. The test check for
dependencies and proper subfunctions.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 s390x/Makefile      |   1 +
 s390x/gen15.c       | 191 ++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg |   4 +
 3 files changed, 196 insertions(+)
 create mode 100644 s390x/gen15.c

```
#### [PATCH v2 1/1] s390/dma: provide proper ARCH_ZONE_DMA_BITS value
##### From: Halil Pasic <pasic@linux.ibm.com>

```c
On s390 ZONE_DMA is up to 2G, i.e. ARCH_ZONE_DMA_BITS should be 31 bits.
The current value is 24 and makes __dma_direct_alloc_pages() take a
wrong turn first (but __dma_direct_alloc_pages() recovers then).

Let's correct ARCH_ZONE_DMA_BITS value and avoid wrong turns.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
Reported-by: Petr Tesarik <ptesarik@suse.cz>
Fixes: c61e9637340e ("dma-direct: add support for allocation from ZONE_DMA and ZONE_DMA32")
---
 arch/s390/include/asm/page.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v8 1/6] vfio/type1: Introduce iova list and add iommu aperture validity check
##### From: Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>

```c
This introduces an iova list that is valid for dma mappings. Make
sure the new iommu aperture window doesn't conflict with the current
one or with any existing dma mappings during attach.

Signed-off-by: Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>
---
v7-->v8
 -Addressed suggestions by Eric to update comments.
---
 drivers/vfio/vfio_iommu_type1.c | 184 +++++++++++++++++++++++++++++++-
 1 file changed, 181 insertions(+), 3 deletions(-)

```
