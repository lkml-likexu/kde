#### [PATCH] kvm_main: fix some comments
##### From: Jiang Biao <benbjiang@tencent.com>

```c
is_dirty has been rename to flush, but the comment for it is
outdated. And the description about @flush parameter for
kvm_clear_dirty_log_protect() is missing, add it in this patch
also.

Signed-off-by: Jiang Biao <benbjiang@tencent.com>
---
 virt/kvm/kvm_main.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2] kvm_main: fix some comments
##### From: Jiang Biao <benbjiang@tencent.com>

```c
is_dirty has been renamed to flush, but the comment for it is
outdated. And the description about @flush parameter for
kvm_clear_dirty_log_protect() is missing, add it in this patch
as well.

Signed-off-by: Jiang Biao <benbjiang@tencent.com>
---
 virt/kvm/kvm_main.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH v2] x86: kvm: hyper-v: deal with buggy TLB flush requests from WS2012
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
It was reported that with some special Multi Processor Group configuration,
e.g:
 bcdedit.exe /set groupsize 1
 bcdedit.exe /set maxgroup on
 bcdedit.exe /set groupaware on
for a 16-vCPU guest WS2012 shows BSOD on boot when PV TLB flush mechanism
is in use.

Tracing kvm_hv_flush_tlb immediately reveals the issue:

 kvm_hv_flush_tlb: processor_mask 0x0 address_space 0x0 flags 0x2

The only flag set in this request is HV_FLUSH_ALL_VIRTUAL_ADDRESS_SPACES,
however, processor_mask is 0x0 and no HV_FLUSH_ALL_PROCESSORS is specified.
We don't flush anything and apparently it's not what Windows expects.

TLFS doesn't say anything about such requests and newer Windows versions
seem to be unaffected. This all feels like a WS2012 bug, which is, however,
easy to workaround in KVM: let's flush everything when we see an empty
flush request, over-flushing doesn't hurt.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
Changes from v1:
- Re-worded the comment [Paolo Bonzini, Sean Christopherson]
- "(flush.processor_mask == 0)" => "!flush.processor_mask" [Sean Christopherson]
---
 arch/x86/kvm/hyperv.c | 11 ++++++++++-
 1 file changed, 10 insertions(+), 1 deletion(-)

```
#### [RFC PATCH V3 1/6] vhost: generalize adding used elem
##### From: Jason Wang <jasowang@redhat.com>

```c
Use one generic vhost_copy_to_user() instead of two dedicated
accessor. This will simplify the conversion to fine grain
accessors. About 2% improvement of PPS were seen during vitio-user
txonly test.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 11 +----------
 1 file changed, 1 insertion(+), 10 deletions(-)

```
#### [PATCH v6 1/6] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 13 ++++++++-----
 drivers/nvdimm/region_devs.c | 26 ++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  8 +++++++-
 6 files changed, 46 insertions(+), 12 deletions(-)

```
