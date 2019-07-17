#### [GIT PULL] VFIO updates for v5.3-rc1
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Hi Linus,

The following changes since commit 6fbc7275c7a9ba97877050335f290341a1fd8dbf:

  Linux 5.2-rc7 (2019-06-30 11:25:36 +0800)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.3-rc1

for you to fetch changes up to 1e4d09d2212d9e230b967f57bc8df463527dbd75:

  mdev: Send uevents around parent device registration (2019-07-11 13:26:52 -0600)

----------------------------------------------------------------
VFIO updates for v5.3-rc1

 - Static symbol cleanup in mdev samples (Kefeng Wang)

 - Use vma help in nvlink code (Peng Hao)

 - Remove unused code in mbochs sample (YueHaibing)

 - Send uevents around mdev registration (Alex Williamson)

----------------------------------------------------------------
Alex Williamson (1):
      mdev: Send uevents around parent device registration

Kefeng Wang (1):
      vfio-mdev/samples: make some symbols static

Peng Hao (1):
      vfio: vfio_pci_nvlink2: use a vma helper function

YueHaibing (1):
      sample/mdev/mbochs: remove set but not used variable 'mdev_state'

 drivers/vfio/mdev/mdev_core.c       |  9 +++++++
 drivers/vfio/pci/vfio_pci_nvlink2.c |  3 +--
 samples/vfio-mdev/mbochs.c          |  3 ---
 samples/vfio-mdev/mtty.c            | 47 +++++++++++++++++++------------------
 4 files changed, 34 insertions(+), 28 deletions(-)
```
#### [PATCH v8 1/3] KVM: x86: Add support for user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use 32bit IA32_UMWAIT_CONTROL MSR
to set the maximum time.

The behavior of user wait instructions in VMX non-root operation is
determined first by the setting of the "enable user wait and pause"
secondary processor-based VM-execution control bit 26.
	If the VM-execution control is 0, UMONITOR/UMWAIT/TPAUSE cause
an invalid-opcode exception (#UD).
	If the VM-execution control is 1, treatment is based on the
setting of the “RDTSC exiting” VM-execution control. Because KVM never
enables RDTSC exiting, if the instruction causes a delay, the amount of
time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay. If
IA32_UMWAIT_CONTROL[31:2] is zero, the virtual delay is the value in
EDX:EAX minus the value that RDTSC would return; if
IA32_UMWAIT_CONTROL[31:2] is not zero, the virtual delay is the minimum
of that difference and AND(IA32_UMWAIT_CONTROL,FFFFFFFCH).

Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it.

Detailed information about user wait instructions can be found in the
latest Intel 64 and IA-32 Architectures Software Developer's Manual.

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---

Changes in v8:
    - Remove unnecessary comments (Sean)
    - Add vmx_waitpkg_supported() helper (Sean)
---
 arch/x86/include/asm/vmx.h      |  1 +
 arch/x86/kvm/cpuid.c            |  2 +-
 arch/x86/kvm/vmx/capabilities.h |  6 ++++++
 arch/x86/kvm/vmx/nested.c       |  1 +
 arch/x86/kvm/vmx/vmx.c          | 18 ++++++++++++++++++
 5 files changed, 27 insertions(+), 1 deletion(-)

```
#### [PATCH] MAINTAINERS: Update my email address to @kernel.org
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
I will soon lose access to my @arm.com email address, so let's
update the MAINTAINERS file to point to my @kernel.org address,
as well as .mailmap for good measure.

Note that my @arm.com address will still work, but someone else
will be reading whatever is sent there. Don't say you didn't know!

Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---

Notes:
    Yes, I'm sending this from my ARM address. That's intentional.
    I'll probably send it as part of a pull request later in the
    cycle, but that's just so that people know what is coming.

 .mailmap    | 1 +
 MAINTAINERS | 8 ++++----
 2 files changed, 5 insertions(+), 4 deletions(-)

```
#### [PATCH 14/14] docs: virtual: add it to the documentation body
##### From: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>

```c
As files are getting converted to ReST, add them to the
documentation body.

Signed-off-by: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/index.rst             | 1 +
 Documentation/virtual/kvm/index.rst | 1 +
 2 files changed, 2 insertions(+)

```
#### [PULL 1/5] vfio-ccw: Fix misleading comment when setting orb.cmd.c64
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Farhan Ali <alifm@linux.ibm.com>

The comment is misleading because it tells us that
we should set orb.cmd.c64 before calling ccwchain_calc_length,
otherwise the function ccwchain_calc_length would return an
error. This is not completely accurate.

We want to allow an orb without cmd.c64, and this is fine
as long as the channel program does not use IDALs. But we do
want to reject any channel program that uses IDALs and does
not set the flag, which is what we do in ccwchain_calc_length.

After we have done the ccw processing, we need to set cmd.c64,
as we use IDALs for all translated channel programs.

Also for better code readability let's move the setting of
cmd.c64 within the non error path.

Fixes: fb9e7880af35 ("vfio: ccw: push down unsupported IDA check")
Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Message-Id: <f68636106aef0faeb6ce9712584d102d1b315ff8.1562854091.git.alifm@linux.ibm.com>
Reviewed-by: Eric Farman <farman@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 13 +++++++------
 1 file changed, 7 insertions(+), 6 deletions(-)

```
#### [PULL] virtio, vhost: fixes, features, performance
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
The following changes since commit c1ea02f15ab5efb3e93fc3144d895410bf79fcf2:

  vhost: scsi: add weight support (2019-05-27 11:08:23 -0400)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to 5e663f0410fa2f355042209154029842ba1abd43:

  virtio-mmio: add error check for platform_get_irq (2019-07-11 16:22:29 -0400)

----------------------------------------------------------------
virtio, vhost: fixes, features, performance

new iommu device
vhost guest memory access using vmap (just meta-data for now)
minor fixes

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

Note: due to code driver changes the driver-core tree, the following
patch is needed when merging tree with commit 92ce7e83b4e5
("driver_find_device: Unify the match function with
class_find_device()") in the driver-core tree:

From: Nathan Chancellor <natechancellor@gmail.com>
Subject: [PATCH] iommu/virtio: Constify data parameter in viommu_match_node

After commit 92ce7e83b4e5 ("driver_find_device: Unify the match
function with class_find_device()") in the driver-core tree.

Signed-off-by: Nathan Chancellor <natechancellor@gmail.com>
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/iommu/virtio-iommu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)


----------------------------------------------------------------
Gustavo A. R. Silva (1):
      scsi: virtio_scsi: Use struct_size() helper

Ihor Matushchak (1):
      virtio-mmio: add error check for platform_get_irq

Jason Wang (6):
      vhost: generalize adding used elem
      vhost: fine grain userspace memory accessors
      vhost: rename vq_iotlb_prefetch() to vq_meta_prefetch()
      vhost: introduce helpers to get the size of metadata area
      vhost: factor out setting vring addr and num
      vhost: access vq metadata through kernel virtual address

Jean-Philippe Brucker (7):
      dt-bindings: virtio-mmio: Add IOMMU description
      dt-bindings: virtio: Add virtio-pci-iommu node
      of: Allow the iommu-map property to omit untranslated devices
      PCI: OF: Initialize dev->fwnode appropriately
      iommu: Add virtio-iommu driver
      iommu/virtio: Add probe request
      iommu/virtio: Add event queue

Michael S. Tsirkin (1):
      vhost: fix clang build warning

 Documentation/devicetree/bindings/virtio/iommu.txt |   66 ++
 Documentation/devicetree/bindings/virtio/mmio.txt  |   30 +
 MAINTAINERS                                        |    7 +
 drivers/iommu/Kconfig                              |   11 +
 drivers/iommu/Makefile                             |    1 +
 drivers/iommu/virtio-iommu.c                       | 1158 ++++++++++++++++++++
 drivers/of/base.c                                  |   10 +-
 drivers/pci/of.c                                   |    8 +
 drivers/scsi/virtio_scsi.c                         |    2 +-
 drivers/vhost/net.c                                |    4 +-
 drivers/vhost/vhost.c                              |  850 +++++++++++---
 drivers/vhost/vhost.h                              |   43 +-
 drivers/virtio/virtio_mmio.c                       |    7 +-
 include/uapi/linux/virtio_ids.h                    |    1 +
 include/uapi/linux/virtio_iommu.h                  |  161 +++
 15 files changed, 2228 insertions(+), 131 deletions(-)
 create mode 100644 Documentation/devicetree/bindings/virtio/iommu.txt
 create mode 100644 drivers/iommu/virtio-iommu.c
 create mode 100644 include/uapi/linux/virtio_iommu.h

```
#### [PATCH v4 1/2] x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The patch enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it. And use QEMU command-line "-overcommit cpu-pm=on"
(enable_cpu_pm is enabled), a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---

No changes in v4.
---
 target/i386/cpu.c | 3 ++-
 target/i386/cpu.h | 1 +
 target/i386/kvm.c | 4 ++++
 3 files changed, 7 insertions(+), 1 deletion(-)

```
