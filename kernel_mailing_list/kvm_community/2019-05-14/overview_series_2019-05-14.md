#### [PATCH v17 01/10] hw/arm/virt: Add RAS platform version for migration
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Support this feature since version 4.1, disable it by
default in the old version.

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
 hw/arm/virt.c         | 6 ++++++
 include/hw/arm/virt.h | 1 +
 2 files changed, 7 insertions(+)

```
#### [GIT PULL] Please pull my kvm-ppc-next-5.2-2 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo, Radim,

I have added 3 more commits to my kvm-ppc-next tree, for various fixes
that have come in recently.  There is one bug fix, one spelling fix,
and one commit that removes some code that does nothing.  The net
result is 12 fewer lines of code in the kernel. :)

If you pull this tag and not the earlier kvm-ppc-next-5.2-1 tag, you
might want to include the text from that tag in the commit message.
That text is:

"
PPC KVM update for 5.2

* Support for guests to access the new POWER9 XIVE interrupt controller
  hardware directly, reducing interrupt latency and overhead for guests.

* In-kernel implementation of the H_PAGE_INIT hypercall.

* Reduce memory usage of sparsely-populated IOMMU tables.

* Several bug fixes.
"

Thanks,
Paul.

The following changes since commit 0caecf5b00199636eb2d32201199ecd6be52558d:

  KVM: PPC: Book3S HV: XIVE: Clear escalation interrupt pointers on device close (2019-04-30 19:41:01 +1000)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.2-2

for you to fetch changes up to 4894fbcce856635c9ab79f44e50826e86bb92110:

  KVM: PPC: Book3S: Remove useless checks in 'release' method of KVM device (2019-05-14 12:06:03 +1000)

----------------------------------------------------------------
Second PPC KVM update for 5.2

- Fix a bug, fix a spelling mistake, remove some useless code.

----------------------------------------------------------------
Colin Ian King (1):
      KVM: PPC: Book3S HV: XIVE: Fix spelling mistake "acessing" -> "accessing"

Cédric Le Goater (1):
      KVM: PPC: Book3S: Remove useless checks in 'release' method of KVM device

Paul Mackerras (1):
      KVM: PPC: Book3S HV: Make sure to load LPID for radix VCPUs

 arch/powerpc/kvm/book3s_hv_rmhandlers.S | 6 ------
 arch/powerpc/kvm/book3s_xive_native.c   | 2 +-
 virt/kvm/kvm_main.c                     | 6 ------
 3 files changed, 1 insertion(+), 13 deletions(-)
```
#### [PATCH] i386: Enable IA32_MISC_ENABLE MWAIT bit when exposing mwait/monitor
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

The CPUID.01H:ECX[bit 3] ought to mirror the value of the MSR 
IA32_MISC_ENABLE MWAIT bit and as userspace has control of them 
both, it is userspace's job to configure both bits to match on 
the initial setup.

Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 target/i386/cpu.c | 3 +++
 target/i386/cpu.h | 1 +
 2 files changed, 4 insertions(+)

```
#### [PATCH] KVM: selftests: Fix a condition in test_hv_cpuid()
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
The code is trying to check that all the padding is zeroed out and it
does this:

    entry->padding[0] == entry->padding[1] == entry->padding[2] == 0

Assume everything is zeroed correctly, then the first comparison is
true, the next comparison is false and false is equal to zero so the
overall condition is true.  This bug doesn't affect run time very
badly, but the code should instead just check that all three paddings
are zero individually.

Also the error message was copy and pasted from an earlier error and it
wasn't correct.

Fixes: 7edcb7343327 ("KVM: selftests: Add hyperv_cpuid test")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/x86_64/hyperv_cpuid.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PULL] vhost: cleanups and fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
The following changes since commit e93c9c99a629c61837d5a7fc2120cd2b6c70dbdd:

  Linux 5.1 (2019-05-05 17:42:58 -0700)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 050f4c4d2fbbd8217d94dc21051cc597d2a6848b:

  virtio/s390: enable packed ring (2019-05-12 13:11:36 -0400)

----------------------------------------------------------------
virtio: fixes, features

s390 has packed ring support.
several fixes.

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Halil Pasic (3):
      virtio/s390: use vring_create_virtqueue
      virtio/s390: DMA support for virtio-ccw
      virtio/s390: enable packed ring

Jiang Biao (1):
      virtio/virtio_ring: do some comment fixes

Jonathan Neuschäfer (1):
      tools/virtio/ringtest: Remove bogus definition of BUG_ON()

Paolo Bonzini (1):
      vhost-scsi: remove incorrect memory barrier

YueHaibing (1):
      virtio_ring: Fix potential mem leak in virtqueue_add_indirect_packed

 drivers/s390/virtio/virtio_ccw.c | 52 +++++++++++++++++++---------------------
 drivers/vhost/scsi.c             |  1 -
 drivers/virtio/virtio_ring.c     | 28 ++++++++++++----------
 include/linux/virtio.h           | 17 -------------
 tools/virtio/ringtest/ptr_ring.c |  1 -
 5 files changed, 40 insertions(+), 59 deletions(-)
```
#### [PATCH v2 1/2] KVM: Start populating /sys/hypervisor with KVM entries
##### From: Filippo Sironi <sironi@amazon.de>

```c
Start populating /sys/hypervisor with KVM entries when we're running on
KVM. This is to replicate functionality that's available when we're
running on Xen.

Start with /sys/hypervisor/uuid, which users prefer over
/sys/devices/virtual/dmi/id/product_uuid as a way to recognize a virtual
machine, since it's also available when running on Xen HVM and on Xen PV
and, on top of that doesn't require root privileges by default.
Let's create arch-specific hooks so that different architectures can
provide different implementations.

Signed-off-by: Filippo Sironi <sironi@amazon.de>
---
v2:
* move the retrieval of the VM UUID out of uuid_show and into
  kvm_para_get_uuid, which is a weak function that can be overwritten

 drivers/Kconfig              |  2 ++
 drivers/Makefile             |  2 ++
 drivers/kvm/Kconfig          | 14 ++++++++++++++
 drivers/kvm/Makefile         |  1 +
 drivers/kvm/sys-hypervisor.c | 30 ++++++++++++++++++++++++++++++
 5 files changed, 49 insertions(+)
 create mode 100644 drivers/kvm/Kconfig
 create mode 100644 drivers/kvm/Makefile
 create mode 100644 drivers/kvm/sys-hypervisor.c

```
#### [PATCH v2] KVM: X86: Emulate MSR_IA32_MISC_ENABLE MWAIT bit
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

MSR IA32_MSIC_ENABLE bit 18, according to SDM:

| When this bit is set to 0, the MONITOR feature flag is not set (CPUID.01H:ECX[bit 3] = 0). 
| This indicates that MONITOR/MWAIT are not supported.
| 
| Software attempts to execute MONITOR/MWAIT will cause #UD when this bit is 0.
| 
| When this bit is set to 1 (default), MONITOR/MWAIT are supported (CPUID.01H:ECX[bit 3] = 1). 

The CPUID.01H:ECX[bit 3] ought to mirror the value of the MSR bit, 
CPUID.01H:ECX[bit 3] is a better guard than kvm_mwait_in_guest().
kvm_mwait_in_guest() affects the behavior of MONITOR/MWAIT, not its
guest visibility.

This patch implements toggling of the CPUID bit based on guest writes 
to the MSR.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * to configure MSR_IA32_MISC_ENABLE_MWAIT bit in userspace
 * implements toggling of the CPUID bit based on guest writes to the MSR

 arch/x86/kvm/cpuid.c | 8 ++++++++
 arch/x86/kvm/x86.c   | 9 +++++++++
 2 files changed, 17 insertions(+)

```
#### [PATCH v2] svm/avic: Allow avic_vcpu_load logic to support host APIC ID 255
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
Current logic does not allow VCPU to be loaded onto CPU with
APIC ID 255. This should be allowed since the host physical APIC ID
field in the AVIC Physical APIC table entry is an 8-bit value,
and APIC ID 255 is valid in system with x2APIC enabled.
Instead, do not allow VCPU load if the host APIC ID cannot be
represented by an 8-bit value.

Also, use the more appropriate AVIC_PHYSICAL_ID_ENTRY_HOST_PHYSICAL_ID_MASK
instead of AVIC_MAX_PHYSICAL_ID_COUNT. 

Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---

Change in V2:
  * Use AVIC_PHYSICAL_ID_ENTRY_HOST_PHYSICAL_ID_MASK instead of
    AVIC_MAX_PHYSICAL_ID_COUNT. 

 arch/x86/kvm/svm.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH v9 1/7] libnvdimm: nd_region flush callback support
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
