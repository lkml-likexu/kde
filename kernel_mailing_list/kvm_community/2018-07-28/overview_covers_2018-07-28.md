

#### [PATCH v6 00/10] kvm: x86: migration of nested virtualization state
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

This is the next version of the nested virtualization migration series,
now with unit tests too.

Patches 6, 7, and 9 replace the (broken) WIP patches in the kvm/queue branch,
while the other seven are new and related to the tests.  In particular, patch 1
is an independent bugfix, which makes it much simpler to use KVM_GET_MSR/KVM_SET_MSR
in a simple userspace client such as the new test.  Patches 2-4 are also
improvements and bugfixes to the unit test infrastructure.

Please review (especially the non-test patches of course!).

Thanks,

Paolo

Jim Mattson (1):
	kvm: nVMX: Introduce KVM_CAP_NESTED_STATE

Paolo Bonzini (9):
	KVM: x86: ensure all MSRs can always be KVM_GET/SET_MSR'd
	kvm: selftests: create a GDT and TSS
	kvm: selftests: actually use all of lib/vmx.c
	kvm: selftests: ensure vcpu file is released
	kvm: selftests: add basic test for state save and restore
	KVM: x86: do not load vmcs12 pages while still in SMM
	kvm: selftests: add test for nested state save/restore
	KVM: nVMX: include shadow vmcs12 in nested state
	KVM: selftests: add tests for shadow VMCS save/restore

 Documentation/virtual/kvm/api.txt                   |   56 ++++
 arch/x86/include/asm/kvm_host.h                     |    9 
 arch/x86/include/uapi/asm/kvm.h                     |   37 ++
 arch/x86/kvm/hyperv.c                               |   27 +-
 arch/x86/kvm/hyperv.h                               |    2 
 arch/x86/kvm/vmx.c                                  |  255 ++++++++++++++++++-
 arch/x86/kvm/x86.c                                  |   71 +++++
 include/uapi/linux/kvm.h                            |    4 
 tools/testing/selftests/kvm/Makefile                |    1 
 tools/testing/selftests/kvm/cr4_cpuid_sync_test.c   |    2 
 tools/testing/selftests/kvm/include/kvm_util.h      |    4 
 tools/testing/selftests/kvm/include/vmx.h           |   66 ++++-
 tools/testing/selftests/kvm/include/x86.h           |    8 
 tools/testing/selftests/kvm/lib/kvm_util.c          |  102 ++++++-
 tools/testing/selftests/kvm/lib/kvm_util_internal.h |    7 
 tools/testing/selftests/kvm/lib/vmx.c               |  104 +++++---
 tools/testing/selftests/kvm/lib/x86.c               |  256 ++++++++++++++++----
 tools/testing/selftests/kvm/state_test.c            |  224 +++++++++++++++++
 tools/testing/selftests/kvm/vmx_tsc_adjust_test.c   |   69 +----
 19 files changed, 1105 insertions(+), 199 deletions(-)
```
