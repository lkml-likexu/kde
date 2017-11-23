#### [PATCH 1/2] kvm: x86: Bounds-check argument to x86_exception_has_error_code
##### From: Jim Mattson <jmattson@google.com>

```c
x86_exception_has_error_code should deterministically return false if
its operand is greater than or equal to 32.

Fixes: 0447378a4a793 ("kvm: vmx: Nested VM-entry prereqs for event inj.")
Cc: Marc Orr <marcorr@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/x86.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [GIT PULL 1/4] KVM: s390: fix locking for crypto setting error path
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
We need to unlock the kvm->lock mutex in the error case.

Reported-by: smatch
Fixes: 37940fb0b6a2c4bf101 ("KVM: s390: device attrs to enable/disable AP interpretation")
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 16 ++++++++++++----
 1 file changed, 12 insertions(+), 4 deletions(-)

```
#### [PATCH] MAINTAINERS: remove reference to bogus vsock file
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
The file drivers/vhost/vsock.h never existed.  Remove the bogus
MAINTAINERS reference.

Fixes: 433fc58e6bf2c8bd97e57153ed28e64fd78207b8 ("VSOCK: Introduce vhost_vsock.ko")
Reported-by: Joe Perches <joe@perches.com>
Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 MAINTAINERS | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH] kvm: x86: #DF only has an error code in protected modeFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Exceptions do not have error codes in real-address mode.

Fixes: 3fd28fce76563 ("KVM: x86: make double/triple fault promotion generic to all exceptions")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v4 1/2] arm/arm64: KVM: rename function kvm_arch_dev_ioctl_check_extension()
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Rename kvm_arch_dev_ioctl_check_extension() to
kvm_arch_vm_ioctl_check_extension(), because it does
not have any relationship with device.

Renaming this function can make code readable.

Cc: James Morse <james.morse@arm.com>
Reviewed-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
I remeber James also mentioned that rename this function.
---
 arch/arm/include/asm/kvm_host.h   | 2 +-
 arch/arm64/include/asm/kvm_host.h | 2 +-
 arch/arm64/kvm/reset.c            | 4 ++--
 virt/kvm/arm/arm.c                | 2 +-
 4 files changed, 5 insertions(+), 5 deletions(-)

```
#### [PATCH v1] KVM/x86/vPMU: Guest PMI Optimization
##### From: Wei Wang <wei.w.wang@intel.com>

```c
Guest changing MSR_CORE_PERF_GLOBAL_CTRL causes KVM to reprogram pmc
counters, which re-allocates a host perf event. This process is
heavyweight and results in a long guest pmi handling time. This also
makes the perf samping events in the guest hard to move forward as the
sampling rate will be adjusted to a low value (e.g. the minimum 250).

This patch implements a fast path to handle the guest change of
MSR_CORE_PERF_GLOBAL_CTRL for the guest pmi case. Guest change of the
msr will be applied to the hardware when entering the guest, and the
old perf event will continue to be used. The guest setting of the
perf counter for the next irq period in pmi will also be written
directly to the hardware counter when entering the guest.

Tests:
1. CPU: Intel(R) Xeon(R) CPU E5-2699 v4 @ 2.20GHz
2. Add host booting parameter "nowatchdog" to avoid the noise from
   watchdog_hld
3. Run "perf stat -e cycles ./test_program" on the guest
4. Results
    - Without this optimization, the guest pmi handling time is
      ~4500000 ns, and the max sampling rate is reduced to 250.
    - With this optimization, the guest pmi handling time is ~9000 ns
      (i.e. 1 / 500 of the non-optimization case), and the max sampling
      rate remains at the original 100000.

Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Cc: Andi Kleen <ak@linux.intel.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/events/intel/core.c      | 35 +++++++++++++++++++++++++++
 arch/x86/include/asm/kvm_host.h   |  2 ++
 arch/x86/include/asm/perf_event.h |  2 ++
 arch/x86/kvm/pmu.c                |  1 +
 arch/x86/kvm/pmu_intel.c          | 50 ++++++++++++++++++++++++++++++++++++---
 5 files changed, 87 insertions(+), 3 deletions(-)

```
#### [PATCH v3 1/8] iommu: Add APIs for multiple domains per device
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Sharing a physical PCI device in a finer-granularity way
is becoming a consensus in the industry. IOMMU vendors
are also engaging efforts to support such sharing as well
as possible. Among the efforts, the capability of support
finer-granularity DMA isolation is a common requirement
due to the security consideration. With finer-granularity
DMA isolation, all DMA requests out of or to a subset of
a physical PCI device can be protected by the IOMMU. As a
result, there is a request in software to attach multiple
domains to a physical PCI device. One example of such use
model is the Intel Scalable IOV [1] [2]. The Intel vt-d
3.0 spec [3] introduces the scalable mode which enables
PASID granularity DMA isolation.

This adds the APIs to support multiple domains per device.
In order to ease the discussions, we call it 'a domain in
auxiliary mode' or simply 'auxiliary domain' when multiple
domains are attached to a physical device.

The APIs includes:

* iommu_get_dev_attr(dev, IOMMU_DEV_ATTR_AUXD_CAPABILITY)
  - Represents the ability of supporting multiple domains
    per device.

* iommu_set_dev_attr(dev, IOMMU_DEV_ATTR_AUXD_ENABLE)
  - Enable the multiple domains capability for the device
    referenced by @dev.

* iommu_set_dev_attr(dev, IOMMU_DEV_ATTR_AUXD_DISABLE)
  - Disable the multiple domains capability for the device
    referenced by @dev.

* iommu_domain_get_attr(domain, DOMAIN_ATTR_AUXD_ID)
  - Return ID used for finer-granularity DMA translation.
    For the Intel Scalable IOV usage model, this will be
    a PASID. The device which supports Scalalbe IOV needs
    to writes this ID to the device register so that DMA
    requests could be tagged with a right PASID prefix.

Many people involved in discussions of this design.

Kevin Tian <kevin.tian@intel.com>
Liu Yi L <yi.l.liu@intel.com>
Ashok Raj <ashok.raj@intel.com>
Sanjay Kumar <sanjay.k.kumar@intel.com>
Jacob Pan <jacob.jun.pan@linux.intel.com>
Alex Williamson <alex.williamson@redhat.com>
Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

and some discussions can be found here [4].

[1] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[2] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf
[3] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[4] https://lkml.org/lkml/2018/7/26/4

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Liu Yi L <yi.l.liu@intel.com>
Suggested-by: Kevin Tian <kevin.tian@intel.com>
Suggested-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/iommu.c | 25 +++++++++++++++++++++++++
 include/linux/iommu.h | 33 +++++++++++++++++++++++++++++++++
 2 files changed, 58 insertions(+)

```
