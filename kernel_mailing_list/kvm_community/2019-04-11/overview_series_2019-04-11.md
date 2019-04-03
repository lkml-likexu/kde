#### [PATCH kernel v3] powerpc/powernv: Isolate NVLinks between GV100GL on Witherspoon
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
The NVIDIA V100 SXM2 GPUs are connected to the CPU via PCIe links and
(on POWER9) NVLinks. In addition to that, GPUs themselves have direct
peer-to-peer NVLinks in groups of 2 to 4 GPUs with no buffers/latches
between GPUs.

Because of these interconnected NVLinks, the POWERNV platform puts such
interconnected GPUs to the same IOMMU group. However users want to pass
GPUs through individually which requires separate IOMMU groups.

Thankfully V100 GPUs implement an interface to disable arbitrary links
by programming link disabling mask via the GPU's BAR0. Once a link is
disabled, it only can be enabled after performing the secondary bus reset
(SBR) on the GPU. Since these GPUs do not advertise any other type of
reset, it is reset by the platform's SBR handler.

This adds an extra step to the POWERNV's SBR handler to block NVLinks to
GPUs which do not belong to the same group as the GPU being reset.

This adds a new "isolate_nvlink" kernel parameter to force GPU isolation;
when enabled, every GPU gets placed in its own IOMMU group. The new
parameter is off by default to preserve the existing behaviour.

Before isolating:
[nvdbg ~]$ nvidia-smi topo -m
        GPU0    GPU1    GPU2    CPU Affinity
GPU0     X      NV2     NV2     0-0
GPU1    NV2      X      NV2     0-0
GPU2    NV2     NV2      X      0-0

After isolating:
[nvdbg ~]$ nvidia-smi topo -m
        GPU0    GPU1    GPU2    CPU Affinity
GPU0     X      PHB     PHB     0-0
GPU1    PHB      X      PHB     0-0
GPU2    PHB     PHB      X      0-0

Where:
  X    = Self
  PHB  = Connection traversing PCIe as well as a PCIe Host Bridge (typically the CPU)
  NV#  = Connection traversing a bonded set of # NVLinks

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
Changes:
v3:
* added pci_err() for failed ioremap
* reworked commit log

v2:
* this is rework of [PATCH kernel RFC 0/2] vfio, powerpc/powernv: Isolate GV100GL
but this time it is contained in the powernv platform
---
 arch/powerpc/platforms/powernv/Makefile      |   2 +-
 arch/powerpc/platforms/powernv/pci.h         |   1 +
 arch/powerpc/platforms/powernv/eeh-powernv.c |   1 +
 arch/powerpc/platforms/powernv/npu-dma.c     |  24 +++-
 arch/powerpc/platforms/powernv/nvlinkgpu.c   | 137 +++++++++++++++++++
 5 files changed, 162 insertions(+), 3 deletions(-)
 create mode 100644 arch/powerpc/platforms/powernv/nvlinkgpu.c

```
#### [PATCH] KVM: fix spectrev1 gadgets
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
These were found with smatch, and then generalized when applicable.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/lapic.c     |  4 +++-
 include/linux/kvm_host.h | 10 ++++++----
 virt/kvm/irqchip.c       |  5 +++--
 virt/kvm/kvm_main.c      |  6 ++++--
 4 files changed, 16 insertions(+), 9 deletions(-)

```
#### [PATCH v6 1/7] Check "load IA32_PAT" VM-exit control on vmentry
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

According to section "Checks on Host Control Registers and MSRs" in Intel
SDM vol 3C, the following check is performed on vmentry:

    If the "load IA32_PAT" VM-exit control is 1, the value of the field
    for the IA32_PAT MSR must be one that could be written by WRMSR
    without fault at CPL 0. Specifically, each of the 8 bytes in the
    field must have one of the values 0 (UC), 1 (WC), 4 (WT), 5 (WP),
    6 (WB), or 7 (UC-).

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH 1/2] KVM: introduce a 'release' method for KVM devices
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
When a P9 sPAPR VM boots, the CAS negotiation process determines which
interrupt mode to use (XICS legacy or XIVE native) and invokes a
machine reset to activate the chosen mode.

To be able to switch from one interrupt mode to another, we introduce
the capability to release a KVM device without destroying the VM. The
KVM device interface is extended with a new 'release' method which is
called when the file descriptor of the device is closed.

Once 'release' is called, the 'destroy' method will not be called
anymore as the device is removed from the device list of the VM.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Cédric Le Goater <clg@kaod.org>
---
 include/linux/kvm_host.h |  9 +++++++++
 virt/kvm/kvm_main.c      | 13 +++++++++++++
 2 files changed, 22 insertions(+)

```
#### [PATCH 1/3] selftests: kvm/evmcs_test: complete I/O before migrating guest state
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Starting state migration after an IO exit without first completing IO
may result in test failures.  We already have two tests that need this
(this patch in fact fixes evmcs_test, similar to what was fixed for
state_test in commit 0f73bbc851ed, "KVM: selftests: complete IO before
migrating guest state", 2019-03-13) and a third is coming.  So, move the
code to vcpu_save_state, and while at it do not access register state
until after I/O is complete.
---
 tools/testing/selftests/kvm/lib/kvm_util.c         |  5 +++++
 tools/testing/selftests/kvm/lib/x86_64/processor.c |  8 ++++++++
 tools/testing/selftests/kvm/x86_64/evmcs_test.c    |  5 +++--
 tools/testing/selftests/kvm/x86_64/state_test.c    | 15 +--------------
 4 files changed, 17 insertions(+), 16 deletions(-)

```
#### [kvm-unit-tests PATCH] s390x/skey: Skip the "iske" test when running under z/VM 6
##### From: Thomas Huth <thuth@redhat.com>

```c
There is a known bug of z/VM 6 which causes the "iske" test to fail.
Since it is still sometimes useful to run the kvm-unit-tests in such
a nested environment, let's rather skip the "iske" test there instead
of always reporting a failure.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 s390x/skey.c | 55 ++++++++++++++++++++++++++++++++++++++++++++++++----
 1 file changed, 51 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH v2] x86: Fix wrong test for 5-level page-table
##### From: Nadav Amit <nadav.amit@gmail.com>

```c
Untested, but clearly bit 12 is the one that needs to be tested.

Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/cstart64.S | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/7] s390: zcrypt: driver callback to indicate resource in use
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Introduces a new driver callback to prevent a root user from unbinding
an AP queue from its device driver if the queue is in use. This prevents
a root user from inadvertently taking a queue away from a guest and
giving it to the host, or vice versa. The callback will be invoked
whenever a change to the AP bus's apmask or aqmask sysfs interfaces may
result in one or more AP queues being removed from its driver. If the
callback responds in the affirmative for any driver queried, the change
to the apmask or aqmask will be rejected with a device in use error.

For this patch, only non-default drivers will be queried. Currently,
there is only one non-default driver, the vfio_ap device driver. The
vfio_ap device driver manages AP queues passed through to one or more
guests and we don't want to unexpectedly take AP resources away from
guests which are most likely independently administered.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/ap_bus.c | 138 +++++++++++++++++++++++++++++++++++++++++--
 drivers/s390/crypto/ap_bus.h |   3 +
 2 files changed, 135 insertions(+), 6 deletions(-)

```
