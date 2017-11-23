#### [PATCH v2 1/2] KVM: x86: Inject PMI for KVM guest
##### From: Luwei Kang <luwei.kang@intel.com>

```c
Inject a PMI for KVM guest when Intel PT working
in Host-Guest mode and Guest ToPA entry memory buffer
was completely filled.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/events/intel/core.c     |  6 +++++-
 arch/x86/include/asm/msr-index.h |  4 ++++
 arch/x86/kvm/x86.c               | 10 ++++++++++
 include/linux/perf_event.h       |  1 +
 4 files changed, 20 insertions(+), 1 deletion(-)

```
#### [PATCH v5 1/9] mm/mmu_notifier: helper to test if a range invalidation is blockable
##### From: jglisse@redhat.com

```c
From: Jérôme Glisse <jglisse@redhat.com>

Simple helpers to test if range invalidation is blockable. Latter
patches use cocinnelle to convert all direct dereference of range->
blockable to use this function instead so that we can convert the
blockable field to an unsigned for more flags.

Signed-off-by: Jérôme Glisse <jglisse@redhat.com>
Cc: Christian König <christian.koenig@amd.com>
Cc: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Cc: Jani Nikula <jani.nikula@linux.intel.com>
Cc: Rodrigo Vivi <rodrigo.vivi@intel.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Felix Kuehling <Felix.Kuehling@amd.com>
Cc: Jason Gunthorpe <jgg@mellanox.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Ross Zwisler <zwisler@kernel.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Christian Koenig <christian.koenig@amd.com>
Cc: Ralph Campbell <rcampbell@nvidia.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: kvm@vger.kernel.org
Cc: dri-devel@lists.freedesktop.org
Cc: linux-rdma@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org
Cc: Arnd Bergmann <arnd@arndb.de>
---
 include/linux/mmu_notifier.h | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH net V2] vhost: correctly check the return value of translate_desc() in log_used()
##### From: Jason Wang <jasowang@redhat.com>

```c
When fail, translate_desc() returns negative value, otherwise the
number of iovs. So we should fail when the return value is negative
instead of a blindly check against zero.

Detected by CoverityScan, CID# 1442593:  Control flow issues  (DEADCODE)

Fixes: cc5e71075947 ("vhost: log dirty page correctly")
Acked-by: Michael S. Tsirkin <mst@redhat.com>
Reported-by: Stephen Hemminger <stephen@networkplumber.org>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH][next] vhost: only return early if ret indicates an error or no iovecs have been processed
##### From: Colin King <colin.king@canonical.com>

```c
From: Colin Ian King <colin.king@canonical.com>

Currently the loop that calls log_write_hva on each iovec is never
executed because of an incorrect error check on the return from the
call to translate_desc.  The check should be checking for a -ve error
return and because it makes no sense to iterate over zero items, the
checks should also check for zero too.

Detected by CoverityScan, CID#1476969 ("Logically dead code")

Fixes: cc5e71075947 ("vhost: log dirty page correctly")
Signed-off-by: Colin Ian King <colin.king@canonical.com>
---
 drivers/vhost/vhost.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 2/5] vfio/migration: support device of device config capability
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
Device config is the default data that every device should have. so
device config capability is by default on, no need to set.

- Currently two type of resources are saved/loaded for device of device
  config capability:
  General PCI config data, and Device config data.
  They are copies as a whole when precopy is stopped.

Migration setup flow:
- Setup device state regions, check its device state version and capabilities.
  Mmap Device Config Region and Dirty Bitmap Region, if available.
- If device state regions are failed to get setup, a migration blocker is
  registered instead.
- Added SaveVMHandlers to register device state save/load handlers.
- Register VM state change handler to set device's running/stop states.
- On migration startup on source machine, set device's state to
  VFIO_DEVICE_STATE_LOGGING

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
Signed-off-by: Yulei Zhang <yulei.zhang@intel.com>
---
 hw/vfio/Makefile.objs         |   2 +-
 hw/vfio/migration.c           | 633 ++++++++++++++++++++++++++++++++++++++++++
 hw/vfio/pci.c                 |   1 -
 hw/vfio/pci.h                 |  25 +-
 include/hw/vfio/vfio-common.h |   1 +
 5 files changed, 659 insertions(+), 3 deletions(-)
 create mode 100644 hw/vfio/migration.c

```
#### [kvm-unit-tests PATCH 1/3] s390x: Beautify sthyi report strings
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Tests like the register odd check in r1 and r2 were not
destinguishable and the reports were hard to read in total.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 s390x/sthyi.c | 45 +++++++++++++++++++++++++++++----------------
 1 file changed, 29 insertions(+), 16 deletions(-)

```
#### [PATCH v2] KVM: PPC: Book3S: Add KVM stat largepages_[2M/1G]
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
This adds an entry to the kvm_stats_debugfs directory which provides the
number of large (2M or 1G) pages which have been used to setup the guest
mappings.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---

V1 -> V2:
- Rename debugfs files from num_[2M/1G]_pages to largepages_[2M/1G] to match
  x86

 arch/powerpc/include/asm/kvm_host.h    |  2 ++
 arch/powerpc/kvm/book3s.c              |  3 +++
 arch/powerpc/kvm/book3s_64_mmu_radix.c | 15 ++++++++++++++-
 3 files changed, 19 insertions(+), 1 deletion(-)

```
#### [PATCH 1/8] drm/i915/gvt: Apply g2h adjust for GTT mmio access
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
From: Yulei Zhang <yulei.zhang@intel.com>

Apply guest to host gma conversion while guest try to access the
GTT mmio registers, as after enable live migration the host gma
will be changed due to the resourece re-allocation, but guest
gma should be remaining unchanged, thus g2h conversion is request
for it.

Signed-off-by: Yulei Zhang <yulei.zhang@intel.com>
Signed-off-by: Zhenyu Wang <zhenyuw@linux.intel.com>
---
 drivers/gpu/drm/i915/gvt/gtt.c | 15 +++++++--------
 1 file changed, 7 insertions(+), 8 deletions(-)

```
