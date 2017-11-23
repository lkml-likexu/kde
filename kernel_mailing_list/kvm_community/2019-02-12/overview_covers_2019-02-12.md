

#### [kvm-unit-tests PATCH 0/3] KVM: nVMX: Fix unrestricted guest toggling
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

The event injection test toggles unrestricted guest to target the
consistency checks related to exception error codes.  In doing so, it
fails to properly meet unrestricted guest's requirement of EPT being
enabled.  Patch 3/3 fixes the actual bug, patches 1/3 and 2/3 tweak the
EPT configuration flow to better support tests that want to enable EPT
but never expect to fulloy enter the guest, i.e. don't need to setup the
actual page tables.

Sean Christopherson (3):
  KVM: nVMX: Remove redundant masking with allowed exec controls mask
  KVM: nVMX: Add enable_ept() helper to configure legal EPTP
  KVM: nVMX: Properly configured unrestricted guest for event injection

 x86/vmx.h       | 18 ----------
 x86/vmx_tests.c | 92 +++++++++++++++++++++++++++++++++----------------
 2 files changed, 62 insertions(+), 48 deletions(-)
```
#### [kvm-unit-tests PATCH 00/15] KVM: clean up the nVMX config
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

The VMX validation space is ginormous, e.g. there are hundreds if not
thousands of combinations of control settings alone to test, and that's
not counting tests like the VMCS shadowing test that permute every
possible value of the test space and generate tens of thousands of
sub-tests.

Because of the sheer number of things to validate, the VMX code crams
many individual test, i.e. things that report PASS/FAIL, into each
test function, i.e. a collection of tests that can be explicitly
invoked via command line, and then consolidates several test functions
under an actual test case, i.e. an entry in x86/unittests.cfg.

While the VMX test infrastructure isn't terrible (I wouldn't call it
"good" either), the testcases defind in unittests.cfg are a mess.
Clean up the worst of the mess so that the defined testcases are at
least somewhat sane, and more importantly, somehwat maintainable.

Most of the patches are relatively minor things to undo copy+paste
issues.  Patch 1/15 adds an option to run a specific test, which is

Sean Christopherson (15):
  KVM: Add a "-t" option to run a specific test
  KVM: x86/config: Consolidate EPT access tests into a single test
  KVM: nVMX: Exclude the EPT access tests from the VMX testcase
  KVM: nVMX: Drop the bogus 2gb requirement from the "vmx" testcase
  KVM: nVMX: Drop the bogus 2gb requirement from the shadow VMCS test
  KVM: nVMX: Drop the bogus SMP requirement from VMCS shadowing test
  KVM: nVMX: Rename VMCS shadowing test to "vmcs_shadow"
  KVM: nVMX: Exclude the VMCS shadowing test from the "vmx" testcase
  KVM: nVMX: Drop testcases that are redundant with the primary VMX
    testcase
  KVM: nVMX: Drop the SMP configuration of the ST APIC passthrough test
  KVM: nVMX: Consolidate the SMP tests into a single testcase
  KVM: nVMX: Rename SMP tests to being with vmx_smp_*
  KVM: nVMX: Exclude the SMP tests from the primary "vmx" testcases
  KVM: nVMX: Drop the bogus 2gb requirement from the SMP tests
  KVM: nVMX: Drop the bogus 2gb requirement from the HLT+RVI testcase

 run_tests.sh         |   6 +-
 scripts/runtime.bash |   6 +-
 x86/unittests.cfg    | 397 +------------------------------------------
 x86/vmx_tests.c      |   8 +-
 4 files changed, 20 insertions(+), 397 deletions(-)
```
