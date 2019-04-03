

#### [PATCH kvm-unit-tests 0/6] x86: nVMX: test APIC reg features
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

This patch series adds test for nested "APIC-register virtualization"
and nested "virtualize x2APIC mode".

Paolo

Marc Orr (6):
  Test nested APIC-register virtualization
  Test odd/incorrect APIC-register virt configs
  apic_reg_virt_test: Make APIC-access addr 4k page
  fix vmx_apic_reg_virt for older platforms
  Test VMX's virtualize x2APIC mode w/ nested
  Add leak scenario to virt_x2apic_mode_test

 lib/x86/apic-defs.h |    1 +
 lib/x86/apic.h      |   28 +
 lib/x86/processor.h |   15 +
 lib/x86/vm.c        |   83 +++
 lib/x86/vm.h        |    3 +
 x86/vmexit.c        |    5 -
 x86/vmx.c           |   75 ++-
 x86/vmx.h           |    1 +
 x86/vmx_tests.c     | 1427 +++++++++++++++++++++++++++++++++++++++++++++++++++
 9 files changed, 1614 insertions(+), 24 deletions(-)
```
#### [PATCH 0/2] KVM: x86: nVMX bugs
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

These patches fix issues with the nested VMX MSR bitmap.  I have already
sent them to Linus.

Paolo

Marc Orr (2):
  KVM: x86: nVMX: close leak of L0's x2APIC MSRs (CVE-2019-3887)
  KVM: x86: nVMX: fix x2APIC VTPR read intercept

 arch/x86/kvm/vmx/nested.c | 74 ++++++++++++++++++++++++++++-------------------
 1 file changed, 45 insertions(+), 29 deletions(-)
```
