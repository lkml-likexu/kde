

#### [PATCH 0/2] KVM: x86: fixes for AMD speculation bug CPUID leaf
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

Patch 1 fixes the reporting of bugs and mitigations via the
0x8000_0008 CPUID leaf on Intel processors.

Patch 2 fixes the reporting of VIRT_SPEC availability on
AMD processors.

Paolo

Paolo Bonzini (2):
  KVM: x86: fix reporting of AMD speculation bug CPUID leaf
  KVM: x86: always expose VIRT_SSBD to guests

 arch/x86/kvm/cpuid.c | 27 +++++++++++++++++----------
 1 file changed, 17 insertions(+), 10 deletions(-)
```
#### [PATCH v2 0/3] KVM: X86: Some tracepoint enhancements
##### From: Peter Xu <peterx@redhat.com>

```c

v2:
- fix commit messages, change format of ple window tracepoint [Sean]
- rebase [Wanpeng]

Each small patch explains itself.  I noticed them when I'm tracing
some IRQ paths and I found them helpful at least to me.

Please have a look.  Thanks,

Peter Xu (3):
  KVM: X86: Trace vcpu_id for vmexit
  KVM: X86: Remove tailing newline for tracepoints
  KVM: X86: Tune PLE Window tracepoint

 arch/x86/kvm/svm.c     | 16 ++++++++--------
 arch/x86/kvm/trace.h   | 30 ++++++++++++------------------
 arch/x86/kvm/vmx/vmx.c | 14 ++++++++------
 arch/x86/kvm/x86.c     |  2 +-
 4 files changed, 29 insertions(+), 33 deletions(-)
```
#### [PATCH v2 00/15] kvm: x86: Support AMD SVM AVIC w/ in-kernel irqchip
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c

The 'commit 67034bb9dd5e ("KVM: SVM: Add irqchip_split() checks before
enabling AVIC")' was introduced to fix miscellaneous boot-hang issues
when enable AVIC. This is mainly due to AVIC hardware doest not #vmexit
on write to LAPIC EOI register resulting in-kernel PIC and IOAPIC to
wait and do not inject new interrupts (e.g. PIT).

This limits AVIC to only work with kernel_irqchip=split mode, which is
not currently enabled by default, and also required user-space to
support split irqchip model, which might not be the case.

The goal of this series is to enable AVIC to work in both irqchip modes.
by allowing AVIC to be deactivated temporary during runtime and fallback
to legacy interrupt injection mode (w/ vINTR and interrupt windows)
when needed, and then re-enabled subseqently.

Similar approach is also used to handle Hyper-V SynIC in the
'commit 5c919412fe61 ("kvm/x86: Hyper-V synthetic interrupt controller")',
where APICv is permanently disabled at runtime (currently broken for
AVIC, and fixed by this series). 

In addition, currently when KVM disables APICv (e.g. running with
kernel_irqchip=on mode on AMD, or due to Hyper-V SyncIC mode), this happens
under the hood and often cause confusion to users. This will be addressed
in part 1 of this series.

This series contains three parts:
  * Part 1: patch 1-4
     Introduce APICv state enum and logic for keeping track of the state
     for each vm, along with debugfs for checking to see if APICv is
     enabled for a particular vm.

  * Part 2: patch 5-11
     Add support for activate/deactivate APICv at runtime

  * Part 3: patch 12-15:
     Provide workaround for AVIC EOI and allow enable AVIC w/
     kernel_irqchip=on

Pre-requisite Patch:
  * commit b9c6ff94e43a ("iommu/amd: Re-factor guest virtual APIC
    (de-)activation code")
    (https://git.kernel.org/pub/scm/linux/kernel/git/joro/iommu.git/commit/
     ?h=next&id=b9c6ff94e43a0ee053e0c1d983fba1ac4953b762)

This series has been tested against v5.2 as following:
  * Booting Linux, FreeBSD, and Windows Server 2019 VMs upto 255 vCPUs
    w/ qemu option "kernel-irqchip=on" and "-no-hpet".
  * Pass-through Intel 10GbE NIC and run netperf in the VM.

Changes from V1: (https://lkml.org/lkml/2019/3/22/1042)
  * Introduce APICv state enumeration
  * Introduce KVM debugfs for APICv state
  * Add synchronization logic for APICv state to prevent potential
    race condition (per Jan's suggestion)
  * Add support for activate/deactivate posted interrupt
    (per Jan's suggestion)
  * Remove callback functions for handling APIC ID, DFR and LDR update
    (per Paolo's suggestion)
  * Add workaround for handling EOI for in-kernel PIT and IOAPIC.

Suravee Suthikulpanit (15):
  kvm: x86: Modify kvm_x86_ops.get_enable_apicv() to use struct kvm
    parameter
  kvm: x86: Introduce KVM APICv state
  kvm: Add arch-specific per-VM debugfs support
  kvm: x86: Add per-VM APICv state debugfs
  kvm: lapic: Introduce APICv update helper function
  kvm: x86: Add support for activate/de-activate APICv at runtime
  kvm: x86: svm: Add support to activate/deactivate posted interrupts
  svm: Add support for setup/destroy virutal APIC backing page for AVIC
  svm: Add support for activate/deactivate AVIC at runtime
  kvm: x86: hyperv: Use APICv deactivate request interface
  svm: Temporary deactivate AVIC during ExtINT handling
  kvm: i8254: Check LAPIC EOI pending when injecting irq on SVM AVIC
  kvm: lapic: Clean up APIC predefined macros
  kvm: ioapic: Delay update IOAPIC EOI for RTC
  svm: Allow AVIC with in-kernel irqchip mode

 arch/mips/kvm/mips.c            |   5 ++
 arch/powerpc/kvm/powerpc.c      |   5 ++
 arch/s390/kvm/kvm-s390.c        |   5 ++
 arch/x86/include/asm/kvm_host.h |  26 +++++-
 arch/x86/kvm/debugfs.c          |  27 +++++++
 arch/x86/kvm/hyperv.c           |  12 ++-
 arch/x86/kvm/i8254.c            |  31 +++++--
 arch/x86/kvm/ioapic.c           |  36 ++++++++-
 arch/x86/kvm/lapic.c            |  35 +++++---
 arch/x86/kvm/lapic.h            |   2 +
 arch/x86/kvm/svm.c              | 173 +++++++++++++++++++++++++++++++++++++---
 arch/x86/kvm/vmx/vmx.c          |   2 +-
 arch/x86/kvm/x86.c              |  96 +++++++++++++++++++++-
 include/linux/kvm_host.h        |   1 +
 virt/kvm/arm/arm.c              |   5 ++
 virt/kvm/kvm_main.c             |   2 +-
 16 files changed, 421 insertions(+), 42 deletions(-)
```
