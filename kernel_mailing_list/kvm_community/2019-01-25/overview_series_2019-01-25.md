#### [GIT PULL] VFIO fixes for v5.0-rc4
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Hi Linus,

The following changes since commit 49a57857aeea06ca831043acbb0fa5e0f50602fd:

  Linux 5.0-rc3 (2019-01-21 13:14:44 +1300)

are available in the Git repository at:

  git://github.com/awilliam/linux-vfio.git tags/vfio-v5.0-rc4

for you to fetch changes up to 9a71ac7e15a723e90fc40388b4b92eefaabf747c:

  vfio-pci/nvlink2: Fix ancient gcc warnings (2019-01-23 08:20:43 -0700)

----------------------------------------------------------------
VFIO fixes for v5.0-rc4

 - Cleanup licenses in new files (Thomas Gleixner)

 - Cleanup new compiler warnings (Alexey Kardashevskiy)

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      vfio-pci/nvlink2: Fix ancient gcc warnings

Thomas Gleixner (1):
      vfio/pci: Cleanup license mess

 drivers/vfio/pci/trace.h            |  6 +-----
 drivers/vfio/pci/vfio_pci_nvlink2.c | 36 ++++++++++++++++--------------------
 2 files changed, 17 insertions(+), 25 deletions(-)
```
#### [PATCH 1/2] i386: kvm: Disable arch_capabilities if MSR can't be set
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
KVM has two bugs in the handling of MSR_IA32_ARCH_CAPABILITIES:

1) Linux commit commit 1eaafe91a0df ("kvm: x86: IA32_ARCH_CAPABILITIES
   is always supported") makes GET_SUPPORTED_CPUID return
   arch_capabilities even if running on SVM.  This makes "-cpu
   host,migratable=off" incorrectly expose arch_capabilities on CPUID on
   AMD hosts (where the MSR is not emulated by KVM).

2) KVM_GET_MSR_INDEX_LIST does not return MSR_IA32_ARCH_CAPABILITIES if
   the MSR is not supported by the host CPU.  This makes QEMU not
   initialize the MSR properly at kvm_put_msrs() on those hosts.

Work around both bugs on the QEMU side, by checking if the MSR
was returned by KVM_GET_MSR_INDEX_LIST before returning the
feature flag on kvm_arch_get_supported_cpuid().

This has the unfortunate side effect of making arch_capabilities
unavailable on hosts without hardware support for the MSR until bug #2
is fixed on KVM, but I can't see another way to work around bug #1
without that side effect.

Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
Cc: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: KarimAllah Ahmed <karahmed@amazon.de>
Cc: David Woodhouse <dwmw@amazon.co.uk>
Cc: Darren Kenny <darren.kenny@oracle.com>
---
 target/i386/kvm.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [PATCH] i386: Disable MSR_PLATFORM_INFO emulation
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
Linux v4.12 introduced[1] emulation of MSR_PLATFORM_INFO and
MSR_MISC_FEATURES_ENABLES, and enabled the
MSR_PLATFORM_INFO_CPUID_FAULT bit unconditionally.  This made
guests incorrectly believe the VM emulates
MSR_MISC_FEATURES_ENABLES properly (which is not true because
QEMU has no migration code to handle the MSR).

The KVM_CAP_MSR_PLATFORM_INFO capability was added[2] to Linux
v4.19 to address the issue.  Use it to disable emulation of
MSR_PLATFORM_INFO and stop incorrectly exposing cpuid_fault to
guests.

References:
[1] commit db2336a80489 ("KVM: x86: virtualize cpuid faulting")
[2] commit 6fbbde9a1969 ("KVM: x86: Control guest reads of MSR_PLATFORM_INFO")

Reported-by: Maxime Coquelin <maxime.coquelin@redhat.com>
Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
 target/i386/kvm.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH v2 1/2] KVM: arm/arm64: Add save/restore support for firmware workaround state
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
 arch/arm/include/asm/kvm_emulate.h   |  10 +++
 arch/arm/include/uapi/asm/kvm.h      |   9 ++
 arch/arm64/include/asm/kvm_emulate.h |  14 ++++
 arch/arm64/include/uapi/asm/kvm.h    |   9 ++
 virt/kvm/arm/psci.c                  | 118 +++++++++++++++++++++++----
 5 files changed, 144 insertions(+), 16 deletions(-)

```
#### [PATCH 1/5] KVM: arm/arm64: Reset the VCPU without preemption and vcpu state loaded
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
Resetting the VCPU state modifies the system register state in memory,
but this may interact with vcpu_load/vcpu_put if running with preemption
disabled, which in turn may lead to corrupted system register state.

Address this by disabling preemption and doing put/load if required
around the reset logic.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 arch/arm64/kvm/reset.c | 26 ++++++++++++++++++++++++--
 1 file changed, 24 insertions(+), 2 deletions(-)

```
#### [PATCH kvmtool] arm: Allow command line for firmware
##### From: Andre Przywara <andre.przywara@arm.com>

```c
When loading a firmware instead of a kernel, we can still pass on any
*user-provided* command line, as /chosen/bootargs is a generic device tree
feature. We just need to make sure to not pass our mangled-for-Linux
version.

This allows to run "firmware" images which make use of a command line,
still are not Linux kernels, like kvm-unit-tests.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
Hi Will,

this goes on top of Julien's firmware series (which did not yet appear
on kernel.org?)
This fixes an issue with some kvm-unit-tests support. [1]

Cheers,
Andre.

[1] https://lists.cs.columbia.edu/pipermail/kvmarm/2019-January/034251.html

 arm/fdt.c | 9 +++------
 1 file changed, 3 insertions(+), 6 deletions(-)

```
#### [kvm-unit-tests PATCH] KVM: nVMX: Use host_phys_bits for EPT tests that require 40+ PA bits
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
The EPT tests require at least 40 bits of physical address space so that
they can use a separate EPT L4 entry to hold guest data.  Qemu defaults
to 40 bits for the size of the guest PA, which causes the tests' check
against CPUID to always pass regardless of the system's actual PA space.
This results in unexpected reserved-bit page faults due to attempting to
access a GPA beyond the physical address width of the system, i.e. bit
39 is reserved.

Pass host_phys_bits for the tests to instruct Qemu to use the host's PA
bits.  Qemu has supported this option since v2.7, which was released in
2016, before the introduction of the EPT tests in 2017.

GPA bits mapped to EPT levels:

    Offset: 11:0
    EPT L1: 20:12
    EPT L2: 29:21
    EPT L3: 38:30
    EPT L4: 47:39
    EPT L5: 56:48

Fixes: 359575f ("x86: ept access tests")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 x86/unittests.cfg | 40 ++++++++++++++++++++--------------------
 1 file changed, 20 insertions(+), 20 deletions(-)

```
#### [PATCH v3 01/33] KVM: VMX: Compare only a single byte for VMCS' "launched" in vCPU-run
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
The vCPU-run asm blob does a manual comparison of a VMCS' launched
status to execute the correct VM-Enter instruction, i.e. VMLAUNCH vs.
VMRESUME.  The launched flag is a bool, which is a typedef of _Bool.
C99 does not define an exact size for _Bool, stating only that is must
be large enough to hold '0' and '1'.  Most, if not all, compilers use
a single byte for _Bool, including gcc[1].

Originally, 'launched' was of type 'int' and so the asm blob used 'cmpl'
to check the launch status.  When 'launched' was moved to be stored on a
per-VMCS basis, struct vcpu_vmx's "temporary" __launched flag was added
in order to avoid having to pass the current VMCS into the asm blob.
The new  '__launched' was defined as a 'bool' and not an 'int', but the
'cmp' instruction was not updated.

This has not caused any known problems, likely due to compilers aligning
variables to 4-byte or 8-byte boundaries and KVM zeroing out struct
vcpu_vmx during allocation.  I.e. vCPU-run accesses "junk" data, it just
happens to always be zero and so doesn't affect the result.

[1] https://gcc.gnu.org/ml/gcc-patches/2000-10/msg01127.html

Fixes: d462b8192368 ("KVM: VMX: Keep list of loaded VMCSs, instead of vcpus")
Cc: <stable@vger.kernel.org>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: fix TRACE_INCLUDE_PATH and remove -I. header search paths
##### From: Masahiro Yamada <yamada.masahiro@socionext.com>

```c
The header search path -I. in kernel Makefiles is very suspicious;
it allows the compiler to search for headers in the top of $(srctree),
where obviously no header file exists.

The reason of having -I. here is to make the incorrectly set
TRACE_INCLUDE_PATH working.

As the comment block in include/trace/define_trace.h says,
TRACE_INCLUDE_PATH should be a relative path to the define_trace.h

Fix the TRACE_INCLUDE_PATH, and remove the iffy include paths.

Signed-off-by: Masahiro Yamada <yamada.masahiro@socionext.com>
---

 arch/x86/kvm/Makefile | 4 ----
 arch/x86/kvm/trace.h  | 2 +-
 2 files changed, 1 insertion(+), 5 deletions(-)

```
#### [PATCH] KVM: x86: Mark expected switch fall-throughs
##### From: "Gustavo A. R. Silva" <gustavo@embeddedor.com>

```c
In preparation to enabling -Wimplicit-fallthrough, mark switch
cases where we are expecting to fall through.

This patch fixes the following warnings:

arch/x86/kvm/lapic.c:1037:27: warning: this statement may fall through [-Wimplicit-fallthrough=]
arch/x86/kvm/lapic.c:1876:3: warning: this statement may fall through [-Wimplicit-fallthrough=]
arch/x86/kvm/hyperv.c:1637:6: warning: this statement may fall through [-Wimplicit-fallthrough=]
arch/x86/kvm/svm.c:4396:6: warning: this statement may fall through [-Wimplicit-fallthrough=]
arch/x86/kvm/mmu.c:4372:36: warning: this statement may fall through [-Wimplicit-fallthrough=]
arch/x86/kvm/x86.c:3835:6: warning: this statement may fall through [-Wimplicit-fallthrough=]
arch/x86/kvm/x86.c:7938:23: warning: this statement may fall through [-Wimplicit-fallthrough=]
arch/x86/kvm/vmx/vmx.c:2015:6: warning: this statement may fall through [-Wimplicit-fallthrough=]
arch/x86/kvm/vmx/vmx.c:1773:6: warning: this statement may fall through [-Wimplicit-fallthrough=]

Warning level 3 was used: -Wimplicit-fallthrough=3

This patch is part of the ongoing efforts to enabling -Wimplicit-fallthrough.

Signed-off-by: Gustavo A. R. Silva <gustavo@embeddedor.com>
---
 arch/x86/kvm/hyperv.c  | 2 +-
 arch/x86/kvm/lapic.c   | 2 ++
 arch/x86/kvm/mmu.c     | 1 +
 arch/x86/kvm/svm.c     | 2 +-
 arch/x86/kvm/vmx/vmx.c | 4 ++--
 arch/x86/kvm/x86.c     | 3 +++
 6 files changed, 10 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/2] x86/kvm/hyper-v: don't recommend doing reset via synthetic MSR
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
System reset through synthetic MSR is not recommended neither by genuine
Hyper-V nor my QEMU.

Fixes: 2bc39970e932 ("x86/kvm/hyper-v: Introduce KVM_GET_SUPPORTED_HV_CPUID")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/hyperv.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH kvmtool 1/6] arm: turn pr_info() into pr_debug() messages
##### From: Andre Przywara <andre.przywara@arm.com>

```c
For whatever reason on ARM/arm64 machines kvmtool greets us with quite
some elaborate messages:
  Info: Loaded kernel to 0x80080000 (18704896 bytes)
  Info: Placing fdt at 0x8fe00000 - 0x8fffffff
  Info: virtio-mmio.devices=0x200@0x10000:36

  Info: virtio-mmio.devices=0x200@0x10200:37

  Info: virtio-mmio.devices=0x200@0x10400:38

This is not really useful information for the casual user, so change
those lines to use pr_debug().
This also fixes the long standing line ending issue for the mmio output.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arm/fdt.c     |  2 +-
 arm/kvm.c     | 16 ++++++++--------
 virtio/mmio.c |  3 ++-
 3 files changed, 11 insertions(+), 10 deletions(-)

```
