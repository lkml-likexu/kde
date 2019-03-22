#### [PATCH]  kvm: fix a function description error
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
The parameter's name of function description is different from
definition.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 virt/kvm/kvm_main.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: nVMX: Expose RDPMC-exiting only when guest supports PMU
##### From: Liran Alon <liran.alon@oracle.com>

```c
Issue was discovered when running kvm-unit-tests on KVM running as L1 on
top of Hyper-V.

When vmx_instruction_intercept unit-test attempts to run RDPMC to test
RDPMC-exiting, it is intercepted by L1 KVM which it's EXIT_REASON_RDPMC
handler raise #GP because vCPU exposed by Hyper-V doesn't support PMU.
Instead of unit-test expectation to be reflected with EXIT_REASON_RDPMC.

The reason vmx_instruction_intercept unit-test attempts to run RDPMC
even though Hyper-V doesn't support PMU is because L1 expose to L2
support for RDPMC-exiting. Which is reasonable to assume that is
supported only in case CPU supports PMU to being with.

Above issue can easily be simulated by modifying
vmx_instruction_intercept config in x86/unittests.cfg to run QEMU with
"-cpu host,+vmx,-pmu" and run unit-test.

To handle issue, change KVM to expose RDPMC-exiting only when guest
supports PMU.

Reported-by: Saar Amar <saaramar@microsoft.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx/vmx.c | 25 +++++++++++++++++++++++++
 1 file changed, 25 insertions(+)

```
#### [patch] KVM: SVM: prevent DBG_DECRYPT and DBG_ENCRYPT overflow
##### From: David Rientjes <rientjes@google.com>

```c
This ensures that the address and length provided to DBG_DECRYPT and
DBG_ENCRYPT do not cause an overflow.

At the same time, pass the actual number of pages pinned in memory to
sev_unpin_memory() as a cleanup.

Reported-by: Cfir Cohen <cfir@google.com>
Signed-off-by: David Rientjes <rientjes@google.com>
---
 arch/x86/kvm/svm.c | 12 +++++++++---
 1 file changed, 9 insertions(+), 3 deletions(-)
```
#### [PATCH] kvm: vmx: Silence a shift wrap warning
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
This code generates a Smatch warning:

arch/x86/kvm/vmx/nested.c:4828 handle_vmfunc() warn: should '(1 << function)' be a 64 bit type?

The warning is generated because "vmcs12->vm_function_control" is a u64
but the shift can only test the lower 32 bits.  This doesn't cause a
problem in the current code because we only use BIT(0).  This patch just
silences the static checker warning.

Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: Raise #GP when guest vCPU do not support PMU
##### From: Liran Alon <liran.alon@oracle.com>

```c
Before this change, reading a VMware pseduo PMC will succeed even when
PMU is not supported by guest. This can easily be seen by running
kvm-unit-test vmware_backdoors with "-cpu host,-pmu" option.

Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/pmu.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PULL kvm-unit-tests] arm/arm64: support kvmtool
##### From: Andrew Jones <drjones@redhat.com>

```c
The following changes since commit 0eac5394af6b481328857d43acb5d8e628b0dbac:

  x86/apic: wait for wrap around in lapic timer periodic test (2019-03-08 14:03:30 +0100)

are available in the Git repository at:

  https://github.com/rhdrjones/kvm-unit-tests support-kvmtool

for you to fetch changes up to 35145f140442b286a27b2daf0c23466e83756061:

  arm/arm64: kvmtool: force all tests to run (2019-03-20 18:57:23 +0100)

----------------------------------------------------------------
Alexandru Elisei (5):
      lib: arm: Use UART address from generated config.h
      configure: arm/arm64: Add --vmm option with no effect
      lib: arm: Use ns16550a UART when --vmm=kvmtool
      lib: arm: Implement PSCI SYSTEM_OFF in psci_system_off()
      lib: arm: Fallback to psci_system_off() in exit()

Andrew Jones (2):
      arm/arm64: selftest.vectors-user: clean up PSCI exit
      arm/arm64: kvmtool: force all tests to run

 .gitignore         |  1 +
 Makefile           |  2 +-
 arm/selftest.c     | 25 +++++++++++++++++++++++++
 configure          | 35 +++++++++++++++++++++++++++++++++++
 lib/arm/asm/psci.h |  3 ++-
 lib/arm/io.c       | 41 ++++++++++++++++++++++++++---------------
 lib/arm/psci.c     |  8 +++++++-
 lib/errata.h       | 11 ++++++++++-
 8 files changed, 107 insertions(+), 19 deletions(-)
```
#### [PATCH v3 1/2] kvm/vmx: Switch MSR_MISC_FEATURES_ENABLES between host and guest
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c
There are two defined bits in MSR_MISC_FEATURES_ENABLES, bit 0 for cpuid
faulting and bit 1 for ring3mwait.

== cpuid Faulting ==
cpuid faulting is a feature about CPUID instruction. When cpuid faulting
is enabled, all execution of the CPUID instruction outside system-management
mode (SMM) cause a general-protection (#GP) if the CPL > 0.

About this feature, detailed information can be found at
https://www.intel.com/content/dam/www/public/us/en/documents/application-notes/virtualization-technology-flexmigration-application-note.pdf

Current KVM provides software emulation of this feature for guest.
However, because cpuid faulting takes higher priority over CPUID vm exit (Intel
SDM vol3.25.1.1), there is a risk of leaking cpuid faulting to guest when host
enables it. If host enables cpuid faulting by setting the bit 0 of
MSR_MISC_FEATURES_ENABLES, it will pass to guest since there is no switch of
MSR_MISC_FEATURES_ENABLES yet. As a result, when guest calls CPUID instruction
in CPL > 0, it will generate a #GP instead of CPUID vm eixt.

This issue will cause guest boot failure when guest uses *modprobe*
to load modules. *modprobe* calls CPUID instruction, thus causing #GP in
guest. Since there is no handling of cpuid faulting in #GP handler, guest
fails boot.

== ring3mwait ==
Ring3mwait is a Xeon-Phi Product Family x200 series specific feature,
which allows the MONITOR and MWAIT instructions to be executed in rings
other than ring 0. The feature can be enabled by setting bit 1 in
MSR_MISC_FEATURES_ENABLES. The register can also be read to determine
whether the instructions are enabled at other than ring 0.

About this feature, description can be found at
https://software.intel.com/en-us/blogs/2016/10/06/intel-xeon-phi-product-family-x200-knl-user-mode-ring-3-monitor-and-mwait

Current kvm doesn't expose feature ring3mwait to guest. However, there is also
a risk of leaking ring3mwait to guest if host enables it since there is no
switch of MSR_MISC_FEATURES_ENABLES.

== solution ==
From above analysis, both cpuid faulting and ring3mwait can be leaked to guest.
To fix this issue, MSR_MISC_FEATURES_ENABLES should be switched between host
and guest. Since MSR_MISC_FEATURES_ENABLES is intel-specific, this patch
implement the switching only in vmx.

For the reason that kvm provides the software emulation of cpuid faulting and
kvm doesn't expose ring3mwait to guest. MSR_MISC_FEATURES_ENABLES can be just
cleared to zero for guest when any of the features is enabled in host.

Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
---
 arch/x86/kernel/process.c |  1 +
 arch/x86/kvm/vmx/vmx.c    | 24 ++++++++++++++++++++++++
 2 files changed, 25 insertions(+)

```
#### [PATCH v8 1/9] iommu: Add APIs for multiple domains per device
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Sharing a physical PCI device in a finer-granularity way
is becoming a consensus in the industry. IOMMU vendors
are also engaging efforts to support such sharing as well
as possible. Among the efforts, the capability of support
finer-granularity DMA isolation is a common requirement
due to the security consideration. With finer-granularity
DMA isolation, subsets of a PCI function can be isolated
from each others by the IOMMU. As a result, there is a
request in software to attach multiple domains to a physical
PCI device. One example of such use model is the Intel
Scalable IOV [1] [2]. The Intel vt-d 3.0 spec [3] introduces
the scalable mode which enables PASID granularity DMA
isolation.

This adds the APIs to support multiple domains per device.
In order to ease the discussions, we call it 'a domain in
auxiliary mode' or simply 'auxiliary domain' when multiple
domains are attached to a physical device.

The APIs include:

* iommu_dev_has_feature(dev, IOMMU_DEV_FEAT_AUX)
  - Detect both IOMMU and PCI endpoint devices supporting
    the feature (aux-domain here) without the host driver
    dependency.

* iommu_dev_feature_enabled(dev, IOMMU_DEV_FEAT_AUX)
  - Check the enabling status of the feature (aux-domain
    here). The aux-domain interfaces are available only
    if this returns true.

* iommu_dev_enable/disable_feature(dev, IOMMU_DEV_FEAT_AUX)
  - Enable/disable device specific aux-domain feature.

* iommu_aux_attach_device(domain, dev)
  - Attaches @domain to @dev in the auxiliary mode. Multiple
    domains could be attached to a single device in the
    auxiliary mode with each domain representing an isolated
    address space for an assignable subset of the device.

* iommu_aux_detach_device(domain, dev)
  - Detach @domain which has been attached to @dev in the
    auxiliary mode.

* iommu_aux_get_pasid(domain, dev)
  - Return ID used for finer-granularity DMA translation.
    For the Intel Scalable IOV usage model, this will be
    a PASID. The device which supports Scalable IOV needs
    to write this ID to the device register so that DMA
    requests could be tagged with a right PASID prefix.

This has been updated with the latest proposal from Joerg
posted here [5].

Many people involved in discussions of this design.

Kevin Tian <kevin.tian@intel.com>
Liu Yi L <yi.l.liu@intel.com>
Ashok Raj <ashok.raj@intel.com>
Sanjay Kumar <sanjay.k.kumar@intel.com>
Jacob Pan <jacob.jun.pan@linux.intel.com>
Alex Williamson <alex.williamson@redhat.com>
Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Joerg Roedel <joro@8bytes.org>

and some discussions can be found here [4] [5].

[1] https://software.intel.com/en-us/download/intel-scalable-io-virtualization-technical-specification
[2] https://schd.ws/hosted_files/lc32018/00/LC3-SIOV-final.pdf
[3] https://software.intel.com/en-us/download/intel-virtualization-technology-for-directed-io-architecture-specification
[4] https://lkml.org/lkml/2018/7/26/4
[5] https://www.spinics.net/lists/iommu/msg31874.html

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Liu Yi L <yi.l.liu@intel.com>
Suggested-by: Kevin Tian <kevin.tian@intel.com>
Suggested-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Suggested-by: Joerg Roedel <jroedel@suse.de>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
Reviewed-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
---
 drivers/iommu/iommu.c | 96 +++++++++++++++++++++++++++++++++++++++++++
 include/linux/iommu.h | 70 +++++++++++++++++++++++++++++++
 2 files changed, 166 insertions(+)

```
#### [PATCH] vfio: Use dev_printk() when possible
##### From: Bjorn Helgaas <helgaas@kernel.org>

```c
From: Bjorn Helgaas <bhelgaas@google.com>

Use dev_printk() when possible to make messages consistent with other
device-related messages.

Signed-off-by: Bjorn Helgaas <bhelgaas@google.com>
---
 drivers/vfio/pci/vfio_pci.c                   |  8 ++---
 drivers/vfio/pci/vfio_pci_config.c            | 29 +++++++++----------
 .../platform/reset/vfio_platform_amdxgbe.c    |  5 ++--
 drivers/vfio/platform/vfio_platform_common.c  | 12 ++++----
 drivers/vfio/vfio.c                           | 29 +++++++++----------
 5 files changed, 40 insertions(+), 43 deletions(-)

```
#### [PATCH 1/2] kvm/x86: Move MSR_K7_HWCR to svm.c
##### From: Borislav Petkov <bp@alien8.de>

```c
From: Borislav Petkov <bp@suse.de>

This is an AMD-specific MSR. Put it where it belongs.

Signed-off-by: Borislav Petkov <bp@suse.de>
Tested-by: Yazen Ghannam <yazen.ghannam@amd.com>
---
 arch/x86/kvm/svm.c | 14 ++++++++++++++
 arch/x86/kvm/x86.c | 12 ------------
 2 files changed, 14 insertions(+), 12 deletions(-)

```
