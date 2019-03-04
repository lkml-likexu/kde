#### [PATCH] kvm/x86: Move MSR_IA32_ARCH_CAPABILITIES to array emulated_msrs
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c
Since MSR_IA32_ARCH_CAPABILITIES is emualted unconditionally even if
host doesn't suppot it. We should move it to array emulated_msrs from
arry msrs_to_save, to report to userspace that guest support this msr.

Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
---
 arch/x86/kvm/x86.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [RFC net-next v1 1/3] vfio/mdev: Inherit dma masks of parent device
##### From: Parav Pandit <parav@mellanox.com>

```c
Inherit dma mask of parent device in child mdev devices, so that
protocol stack can use right dma mask while doing dma mappings.

Signed-off-by: Parav Pandit <parav@mellanox.com>
---
 drivers/vfio/mdev/mdev_core.c | 4 ++++
 1 file changed, 4 insertions(+)

```
