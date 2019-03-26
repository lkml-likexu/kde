#### [PATCH 1/2] kvm: x86: Include multiple indices with CPUID leaf 0x8000001d
##### From: Jim Mattson <jmattson@google.com>

```c
Per the APM, "CPUID Fn8000_001D_E[D,C,B,A]X reports cache topology
information for the cache enumerated by the value passed to the
instruction in ECX, referred to as Cache n in the following
description. To gather information for all cache levels, software must
repeatedly execute CPUID with 8000_001Dh in EAX and ECX set to
increasing values beginning with 0 until a value of 00h is returned in
the field CacheType (EAX[4:0]) indicating no more cache descriptions
are available for this processor."

The termination condition is the same as leaf 4, so we can reuse that
code block for leaf 0x8000001d.

Fixes: 8765d75329a38 ("KVM: X86: Extend CPUID range to include new leaf")
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: Borislav Petkov <bp@suse.de>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
---
 arch/x86/kvm/cpuid.c | 7 +++----
 1 file changed, 3 insertions(+), 4 deletions(-)

```
#### [PATCH 1/2] KVM: x86: Rename pre_{enter,leave}_smm() ops to reference SMM state save
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Rename pre_{enter,leave}_smm() to post_smi_state_save() and
pre_rsm_load_state() to make it explicitly clear when the callbacks are
invoked, e.g. to allow a future patch to add pre_smi_save_state() and
post_rsm_load_state().

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/include/asm/kvm_emulate.h |  2 +-
 arch/x86/include/asm/kvm_host.h    |  4 ++--
 arch/x86/kvm/emulate.c             |  8 ++++----
 arch/x86/kvm/svm.c                 |  8 ++++----
 arch/x86/kvm/vmx/vmx.c             |  8 ++++----
 arch/x86/kvm/x86.c                 | 14 +++++++-------
 6 files changed, 22 insertions(+), 22 deletions(-)

```
#### [PATCH 1/4 v2][KVM nVMX]: Check "load IA32_PAT" VM-entry control on vmentry nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checking and Loading Guest State" in Intel SDM vol
3C, the following check is performed on vmentry:

    If the "load IA32_PAT" VM-entry control is 1, the value of the field
    for the IA32_PAT MSR must be one that could be written by WRMSR
    without fault at CPL 0. Specifically, each of the 8 bytes in the
    field must have one of the values 0 (UC), 1 (WC), 4 (WT), 5 (WP),
    6 (WB), or 7 (UC-).

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH 1/4 v2][KVM nVMX]: Check "load IA32_PAT" VM-exit control on vmentry of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
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
---
 arch/x86/kvm/vmx/nested.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [kvm-unit-tests PATCH v2] Add a .gitlab-ci.yml file for automatic CI testing on GitLab instances
##### From: Thomas Huth <thuth@redhat.com>

```c
When changing common code of the kvm-unit-tests, one should make sure that
the tests still compile fine for all target architectures afterwards. But
compiling kvm-unit-tests for all target architectures manually is cumbersome.
For people like me who store their git trees on GitLab, this can be done
automatically via a CI system instead. Using the .gitlab-ci.yml file, auto-
matic builds are now triggered on each push to a kvm-unit-test repository on
gitlab.com. Additionally, the script also runs the tests that can be executed
with QEMU TCG (except for s390x, since the QEMU package of the CI container
currently does not provide the required s390-ccw bios here).

Signed-off-by: Thomas Huth <thuth@redhat.com>
Acked-by: Andrew Jones <drjones@redhat.com>
---
 v2:
 - Don't use the "--processor" option for configure (they are not required)
 - Add pmu and psci tests to the arm and aarch64 builds
 - Example can be seen here:
   https://gitlab.com/huth/kvm-unit-tests/pipelines/53825156

 .gitlab-ci.yml | 75 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 75 insertions(+)
 create mode 100644 .gitlab-ci.yml

diff --git a/.gitlab-ci.yml b/.gitlab-ci.yml
new file mode 100644
index 0000000..50a1e39
--- /dev/null
+++ b/.gitlab-ci.yml
@@ -0,0 +1,75 @@
+before_script:
+ - apt-get update -qq
+ - apt-get install -y -qq qemu-system
+
+build-aarch64:
+ script:
+ - apt-get install -y -qq gcc-aarch64-linux-gnu
+ - ./configure --arch=aarch64 --cross-prefix=aarch64-linux-gnu-
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     selftest-setup selftest-vectors-kernel selftest-vectors-user selftest-smp
+     pci-test pmu gicv2-active gicv3-active psci timer
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
+
+build-arm:
+ script:
+ - apt-get install -y -qq gcc-arm-linux-gnueabi
+ - ./configure --arch=arm --cross-prefix=arm-linux-gnueabi-
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     selftest-setup selftest-vectors-kernel selftest-vectors-user selftest-smp
+     pci-test pmu gicv2-active gicv3-active psci
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
+
+build-ppc64be:
+ script:
+ - apt-get install -y -qq gcc-powerpc64-linux-gnu
+ - ./configure --arch=ppc64 --endian=big --cross-prefix=powerpc64-linux-gnu-
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     selftest-setup spapr_hcall rtas-get-time-of-day rtas-get-time-of-day-base
+     rtas-set-time-of-day emulator
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
+
+build-ppc64le:
+ script:
+ - apt-get install -y -qq gcc-powerpc64-linux-gnu
+ - ./configure --arch=ppc64 --endian=little --cross-prefix=powerpc64-linux-gnu-
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     selftest-setup spapr_hcall rtas-get-time-of-day rtas-get-time-of-day-base
+     rtas-set-time-of-day emulator
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
+
+build-s390x:
+ script:
+ - apt-get install -y -qq gcc-s390x-linux-gnu
+ - ./configure --arch=s390x --cross-prefix=s390x-linux-gnu-
+ - make -j2
+
+build-x86_64:
+ script:
+ - ./configure --arch=x86_64
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     ioapic-split ioapic smptest smptest3 vmexit_cpuid vmexit_mov_from_cr8
+     vmexit_mov_to_cr8 vmexit_inl_pmtimer  vmexit_ipi vmexit_ipi_halt
+     vmexit_ple_round_robin vmexit_tscdeadline vmexit_tscdeadline_immed
+     eventinj msr port80 sieve tsc rmap_chain umip hyperv_stimer intel_iommu
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
+
+build-i386:
+ script:
+ - apt-get install -y -qq gcc-multilib
+ - ./configure --arch=i386
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     eventinj port80 sieve tsc taskswitch umip hyperv_stimer
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
```
#### [PATCH] KVM: x86: avoid misreporting level-triggered irqs as edge-triggered in tracing
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
In __apic_accept_irq() interface trig_mode is int and actually on some code
paths it is set above u8:

kvm_apic_set_irq() extracts it from 'struct kvm_lapic_irq' where trig_mode
is u16. This is done on purpose as e.g. kvm_set_msi_irq() sets it to
(1 << 15) & e->msi.data

kvm_apic_local_deliver sets it to reg & (1 << 15).

Fix the immediate issue by making 'tm' into u16. We may also want to adjust
__apic_accept_irq() interface and use proper sizes for vector, level,
trig_mode but this is not urgent.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/trace.h | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCHv1 1/7] vfio/mdev: Avoid release parent reference during error path
##### From: Parav Pandit <parav@mellanox.com>

```c
During mdev parent registration in mdev_register_device(),
if parent device is duplicate, it releases the reference of existing
parent device.
This is incorrect. Existing parent device should not be touched.

Fixes: 7b96953bc640 ("vfio: Mediated device Core driver")
Reviewed By: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Maxim Levitsky <mlevitsk@redhat.com>
Signed-off-by: Parav Pandit <parav@mellanox.com>
---
 drivers/vfio/mdev/mdev_core.c | 1 +
 1 file changed, 1 insertion(+)

```
