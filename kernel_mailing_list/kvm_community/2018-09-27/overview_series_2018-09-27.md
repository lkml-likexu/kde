#### [kvm-unit-tests PATCH] MAINTAINERS: Add reviewer entry type and make me a s390 reviewer
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
As I missed some mails that introduced problems on s390 and their
fixes, this might help to broaden review coverage.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Suggested-by: Thomas Huth <thuth@redhat.com>
Acked-by: David Hildenbrand <david@redhat.com>
---
 MAINTAINERS | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH net V2] vhost-vsock: fix use after free
##### From: Jason Wang <jasowang@redhat.com>

```c
The access of vsock is not protected by vhost_vsock_lock. This may
lead to use after free since vhost_vsock_dev_release() may free the
pointer at the same time.

Fix this by holding the lock during the access.

Reported-by: syzbot+e3e074963495f92a89ed@syzkaller.appspotmail.com
Fixes: 16320f363ae1 ("vhost-vsock: add pkt cancel capability")
Fixes: 433fc58e6bf2 ("VSOCK: Introduce vhost_vsock.ko")
Cc: Stefan Hajnoczi <stefanha@redhat.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
Reviewed-by: Stefan Hajnoczi <stefanha@redhat.com>
---
- V2: fix typos
- The patch is needed for -stable.
---
 drivers/vhost/vsock.c | 26 +++++++++++++++++++-------
 1 file changed, 19 insertions(+), 7 deletions(-)

```
#### [PATCH net] vhost-vsock: fix use after free
##### From: Jason Wang <jasowang@redhat.com>

```c
The access of vsock is not protected by vhost_vsock_lock. This may
lead use after free since vhost_vsock_dev_release() may free the
pointer at the same time.

Fix this by holding the lock during the acess.

Reported-by: syzbot+e3e074963495f92a89ed@syzkaller.appspotmail.com
Fixes: 16320f363ae1 ("vhost-vsock: add pkt cancel capability")
Fixes: 433fc58e6bf2 ("VSOCK: Introduce vhost_vsock.ko")
Cc: Stefan Hajnoczi <stefanha@redhat.com>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
- The patch is needed for -stable.
---
 drivers/vhost/vsock.c | 26 +++++++++++++++++++-------
 1 file changed, 19 insertions(+), 7 deletions(-)

```
#### [RFC PATCH v1 1/1] Add attribute multiple_mdev_support for mdev type-id
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Generally a single instance of mdev device, a share of physical device, is
assigned to user space application or a VM. There are cases when multiple
instances of mdev devices of same or different types are required by User
space application or VM. For example in case of vGPU, multiple mdev devices
of type which represents whole GPU can be assigned to one instance of
application or VM.

All types of mdev devices may not support assigning multiple mdev devices
to a user space application. In that case vendor driver can fail open()
call of mdev device. But there is no way to know User space application
about the configuration supported by vendor driver.

To expose supported configuration, vendor driver should add
'multiple_mdev_support' attribute to type-id directory if vendor driver
supports assigning multiple mdev devices of a particular type-id to one
instance of user space application or a VM.

User space application should read if 'multiple_mdev_support' attibute is
present in type-id directory of all mdev devices which are going to be
used. If all read 1 then user space application can proceed with multiple
mdev devices.

This is optional and readonly attribute.

Signed-off-by: Neo Jia <cjia@nvidia.com>
Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
---
 Documentation/ABI/testing/sysfs-bus-vfio-mdev | 13 +++++++++++++
 1 file changed, 13 insertions(+)

```
#### [PATCH v2] KVM: x86: remove check on nr_mmu_pages in kvm_arch_commit_memory_region()
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
* nr_mmu_pages would be non-zero only if kvm->arch.n_requested_mmu_pages is
  non-zero.

* nr_mmu_pages is always non-zero, since kvm_mmu_calculate_mmu_pages()
  never return zero.

Based on these two reasons, we can merge the two *if* clause and use the
return value from kvm_mmu_calculate_mmu_pages() directly. This simplify
the code and also eliminate the possibility for reader to believe
nr_mmu_pages would be zero.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
v2: refactor changelog and rename kvm_mmu_calculate_mmu_pages() based on
Sean Christopherson comment.
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 arch/x86/kvm/mmu.c              | 2 +-
 arch/x86/kvm/x86.c              | 8 ++------
 3 files changed, 4 insertions(+), 8 deletions(-)

```
#### [PATCH v2] reset: Exclusive resets must be dedicated to a single hardware block
##### From: Geert Uytterhoeven <geert+renesas@glider.be>

```c
In some SoCs multiple hardware blocks may share a reset control.
The reset control API for shared resets will only assert such a reset
when the drivers for all hardware blocks agree.
The exclusive reset control API still allows to assert such a reset, but
that impacts all other hardware blocks sharing the reset.

While the kernel doc comments clearly state that the API for shared
resets applies to reset controls which are shared between hardware
blocks, the exact meaning of exclusive resets is not documented.
Fix the semantic ambiguity with respect to exclusive access vs.
exclusive reset lines by:
  1. Clarifying that exclusive resets really are intended for use with
     reset controls which are dedicated to a single hardware block,
  2. Ensuring that obtaining an exclusive reset control will fail if the
     reset is shared by multiple hardware blocks, for both DT-based and
     lookup-based reset controls.

Signed-off-by: Geert Uytterhoeven <geert+renesas@glider.be>
---
This is v2 of "[RFC] reset: Add support for dedicated reset controls":
  - Fix wrong variable in __reset_is_dedicated() loop,
  - Add missing of_node_put() in __of_reset_is_dedicated(),
  - Document that exclusive reset controls imply they are dedicated to a
    single hardware block,
  - Drop new dedicated flag and new API reset_control_get_dedicated(),
    as exclusive already implies dedicated,
  - Rename {__of_,}reset_is_dedicated() to {__of_,}reset_is_exclusive(),
  - Reword description.

Note: Exclusive lookup-based reset controls were not tested.
---
 drivers/reset/core.c  | 58 +++++++++++++++++++++++++++++++++++++++++++
 include/linux/reset.h |  5 +++-
 2 files changed, 62 insertions(+), 1 deletion(-)

```
#### [PATCH V3 1/13] KVM: Add tlb_remote_flush_with_range callback in kvm_x86_ops
##### From: Tianyu Lan <Tianyu.Lan@microsoft.com>

```c
Add flush range call back in the kvm_x86_ops and platform can use it
to register its associated function. The parameter "kvm_tlb_range"
accepts a single range and flush list which contains a list of ranges.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
Change since v1:
       Change "end_gfn" to "pages" to aviod confusion as to whether
"end_gfn" is inclusive or exlusive.
---
 arch/x86/include/asm/kvm_host.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
