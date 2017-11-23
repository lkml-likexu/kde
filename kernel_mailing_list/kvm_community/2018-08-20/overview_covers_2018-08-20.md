

#### [PATCH 0/5] kvm: selftest: add dirty logging test
##### From: Peter Xu <peterx@redhat.com>

```c

Add a simple test for existing dirty logging facility.

Patch 2 tried to generalize the port IO magic a bit in misc tests but
still not be that ideal.  Let's see how people think about it.

Please have a look, thanks.

Peter Xu (5):
  tools: introduce test_and_clear_bit
  kvm: selftest: unify the guest port macros
  kvm: selftest: include the tools headers
  kvm: selftest: introduce _vm_create_default()
  kvm: selftest: add dirty logging test

 tools/include/linux/bitmap.h                  |  17 ++
 tools/testing/selftests/kvm/Makefile          |   5 +-
 .../selftests/kvm/cr4_cpuid_sync_test.c       |  30 +-
 tools/testing/selftests/kvm/dirty_logging.c   | 261 ++++++++++++++++++
 .../testing/selftests/kvm/include/kvm_util.h  |  44 +++
 .../testing/selftests/kvm/include/test_util.h |   2 -
 tools/testing/selftests/kvm/lib/kvm_util.c    |  58 ++++
 tools/testing/selftests/kvm/lib/x86.c         |  13 +-
 tools/testing/selftests/kvm/state_test.c      |  30 +-
 tools/testing/selftests/kvm/sync_regs_test.c  |  19 +-
 .../selftests/kvm/vmx_tsc_adjust_test.c       |  41 +--
 11 files changed, 420 insertions(+), 100 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/dirty_logging.c
```
