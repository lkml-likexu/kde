#### [PATCH 1/1] s390/virtio: handle find on invalid queue gracefully
##### From: Halil Pasic <pasic@linux.ibm.com>

```c
A queue with a capacity of zero is clearly not a valid virtio queue.
Some emulators report zero queue size if queried with an invalid queue
index. Instead of crashing in this case let us just return -EINVAL. To
make that work properly, let us fix the notifier cleanup logic as well.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
---
This patch is motivated by commit 86a5597 "virtio-balloon:
VIRTIO_BALLOON_F_FREE_PAGE_HINT" (Wei Wang, 2018-08-27) which triggered
the described scenario.  The emulator in question is the current QEMU.
The problem we run into is the underflow in the following loop
in  __vring_new_virtqueue():
for (i = 0; i < vring.num-1; i++)
	vq->vring.desc[i].next = cpu_to_virtio16(vdev, i + 1)
Namely vring.num is an unsigned int.

RFC --> v1:
* Change error code from -EINVAL to -ENOENT, so we are in line with the
other transports.
* Push down the detection of the error into virtio_ccw_read_vq_conf().
---
 drivers/s390/virtio/virtio_ccw.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH 1/2] KVM: arm/arm64: Add save/restore support for firmware workaround state
##### From: Andre Przywara <andre.przywara@arm.com>

```c
KVM implements the firmware interface for mitigating cache speculation
vulnerabilities. Guests may use this interface to ensure mitigation is
active.
If we want to migrate such a guest to a host with a different support
level for those workarounds, migration might need to fail, to ensure that
critical guests don't loose their protection.

Introduce a way for userland to save and restore the workarounds state.
On restoring we do checks that make sure we don't downgrade our
mitigation level.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arch/arm/include/asm/kvm_emulate.h   |  10 ++
 arch/arm/include/uapi/asm/kvm.h      |   9 ++
 arch/arm64/include/asm/kvm_emulate.h |  14 +++
 arch/arm64/include/uapi/asm/kvm.h    |   9 ++
 virt/kvm/arm/psci.c                  | 138 ++++++++++++++++++++++++++-
 5 files changed, 178 insertions(+), 2 deletions(-)

```
#### [PATCH] Documentation/virtual/kvm: Update URL for AMD SEV API specification
##### From: Christophe de Dinechin <dinechin@redhat.com>

```c
The URL of [api-spec] in Documentation/virtual/kvm/amd-memory-encryption.rst
is no longer valid, replaced space with underscore.

Signed-off-by: Christophe de Dinechin <dinechin@redhat.com>
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
---
 Documentation/virtual/kvm/amd-memory-encryption.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: nSVM: clear events pending from svm_complete_interrupts() when exiting to L1
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
kvm-unit-tests' eventinj "NMI failing on IDT" test results in NMI being
delivered to the host (L1) when it's running nested. The problem seems to
be: svm_complete_interrupts() raises 'nmi_injected' flag but later we
decide to reflect EXIT_NPF to L1. The flag remains pending and we do NMI
injection upon entry so it got delivered to L1 instead of L2.

It seems that VMX code solves the same issue in prepare_vmcs12(), this was
introduced with code refactoring in commit 5f3d5799974b ("KVM: nVMX: Rework
event injection and recovery").

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH 01/19] powerpc/xive: export flags for the XIVE native exploitation mode hcalls
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
These flags are shared between Linux/KVM implementing the hypervisor
calls for the XIVE native exploitation mode and the driver for the
sPAPR guests.

Signed-off-by: Cédric Le Goater <clg@kaod.org>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---
 arch/powerpc/include/asm/xive.h  | 23 +++++++++++++++++++++++
 arch/powerpc/sysdev/xive/spapr.c | 28 ++++++++--------------------
 2 files changed, 31 insertions(+), 20 deletions(-)

```
#### [PATCH v3 1/3] virtio-balloon: tweak config_changed implementation
##### From: Wei Wang <wei.w.wang@intel.com>

```c
virtio-ccw has deadlock issues with reading the config space inside the
interrupt context, so we tweak the virtballoon_changed implementation
by moving the config read operations into the related workqueue contexts.
The config_read_bitmap is used as a flag to the workqueue callbacks
about the related config fields that need to be read.

The cmd_id_received is also renamed to cmd_id_received_cache, and
the value should be obtained via virtio_balloon_cmd_id_received.

Reported-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Tested-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 drivers/virtio/virtio_balloon.c | 98 +++++++++++++++++++++++++++--------------
 1 file changed, 65 insertions(+), 33 deletions(-)

```
#### [PATCH]  x86/kvm: convert to DEFINE_DEBUGFS_ATTRIBUTE
##### From: Peng Hao <penghao122@sina.com.cn>

```c
From: Peng Hao <peng.hao2@zte.com.cn>

The preferred strategy to define debugfs attributes is to use
the DEFINE_DEBUGFS_ATTRIBUTE() macro and to use
debugfs_create_file_unsafe().

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/debugfs.c | 15 +++++++++------
 1 file changed, 9 insertions(+), 6 deletions(-)

```
