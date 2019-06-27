#### [PATCH] KVM: nVMX: Change KVM_STATE_NESTED_EVMCS to signal vmcs12 is copied from eVMCS
##### From: Liran Alon <liran.alon@oracle.com>

```c
Currently KVM_STATE_NESTED_EVMCS is used to signal that eVMCS
capability is enabled on vCPU.
As indicated by vmx->nested.enlightened_vmcs_enabled.

This is quite bizarre as userspace VMM should make sure to expose
same vCPU with same CPUID values in both source and destination.
In case vCPU is exposed with eVMCS support on CPUID, it is also
expected to enable KVM_CAP_HYPERV_ENLIGHTENED_VMCS capability.
Therefore, KVM_STATE_NESTED_EVMCS is redundant.

KVM_STATE_NESTED_EVMCS is currently used on restore path
(vmx_set_nested_state()) only to enable eVMCS capability in KVM
and to signal need_vmcs12_sync such that on next VMEntry to guest
nested_sync_from_vmcs12() will be called to sync vmcs12 content
into eVMCS in guest memory.
However, because restore nested-state is rare enough, we could
have just modified vmx_set_nested_state() to always signal
need_vmcs12_sync.

From all the above, it seems that we could have just removed
the usage of KVM_STATE_NESTED_EVMCS. However, in order to preserve
backwards migration compatibility, we cannot do that.
(vmx_get_nested_state() needs to signal flag when migrating from
new kernel to old kernel).

Returning KVM_STATE_NESTED_EVMCS when just vCPU have eVMCS enabled
have a bad side-effect of userspace VMM having to send nested-state
from source to destination as part of migration stream. Even if
guest have never used eVMCS as it doesn't even run a nested
hypervisor workload. This requires destination userspace VMM and
KVM to support setting nested-state. Which make it more difficult
to migrate from new host to older host.
To avoid this, change KVM_STATE_NESTED_EVMCS to signal eVMCS is
not only enabled but also active. i.e. Guest have made some
eVMCS active via an enlightened VMEntry. i.e. vmcs12 is copied
from eVMCS and therefore should be restored into eVMCS resident
in memory (by copy_vmcs12_to_enlightened()).

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Maran Wilson <maran.wilson@oracle.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/nested.c                     | 25 ++++++++++++-------
 .../testing/selftests/kvm/x86_64/evmcs_test.c |  1 +
 2 files changed, 17 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: x86: degrade WARN to pr_warn_ratelimited
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
This warning can be triggered easily by userspace, so it should certainly not
cause a panic if panic_on_warn is set.

Suggested-by: Alexander Potapenko <glider@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] mdev: Send uevents around parent device registrationFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
This allows udev to trigger rules when a parent device is registered
or unregistered from mdev.

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/mdev/mdev_core.c |   10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
#### [PATCH v2] KVM: x86: degrade WARN to pr_warn_ratelimited
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
This warning can be triggered easily by userspace, so it should certainly not
cause a panic if panic_on_warn is set.

Suggested-by: Alexander Potapenko <glider@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reported-by: syzbot+c03f30b4f4c46bdf8575@syzkaller.appspotmail.com
Acked-by: Alexander Potapenko <glider@google.com>
---
 arch/x86/kvm/x86.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH v7 1/6] vfio/type1: Introduce iova list and add iommu aperture validity check
##### From: Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>

```c
This introduces an iova list that is valid for dma mappings. Make
sure the new iommu aperture window doesn't conflict with the current
one or with any existing dma mappings during attach.

Signed-off-by: Shameer Kolothum <shameerali.kolothum.thodi@huawei.com>
---
 drivers/vfio/vfio_iommu_type1.c | 181 +++++++++++++++++++++++++++++++-
 1 file changed, 177 insertions(+), 4 deletions(-)

```
