

#### [PATCH v2 0/2] KVM: x86: expose direct stores instructions into VM.
##### From: Liu Jingqi <jingqi.liu@intel.com>

```c

Direct stores instructions MOVDIRI and MOVDIR64B will be available in
Tremont and other future x86 processors,
and need to be exposed to guest VM.

The release document ref below link:
https://software.intel.com/sites/default/files/managed/c5/15/\
architecture-instruction-set-extensions-programming-reference.pdf

This series expose movdiri and movdir64b features to guest VM.

Changelog:
v2:
	Separated from the series https://lkml.org/lkml/2018/7/10/160
	since umonitor/umwait/tpause instructions patches are not ready yet.
v1:
	Sent out with umonitor/umwait/tpause instructions patches.

Liu Jingqi (2):
  KVM: x86: expose MOVDIRI CPU feature into VM.
  KVM: x86: expose MOVDIR64B CPU feature into VM.

 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```
#### [PATCH v2 0/5] migration: improve multithreads
##### From: guangrong.xiao@gmail.com
X-Google-Original-From: xiaoguangrong@tencent.com
From: Xiao Guangrong <xiaoguangrong@tencent.com>

```c

From: Xiao Guangrong <xiaoguangrong@tencent.com>

Changelog in v2:
These changes are based on Paolo's suggestion:
1) rename the lockless multithreads model to threaded workqueue
2) hugely improve the internal design, that make all the request be
   a large array, properly partition it, assign requests to threads
   respectively and use bitmaps to sync up threads and the submitter,
   after that ptr_ring and spinlock are dropped
3) introduce event wait for the submitter

These changes are based on Emilio's review:
4) make more detailed description for threaded workqueue
5) add a benchmark for threaded workqueue

The previous version can be found at
	https://marc.info/?l=kvm&m=153968821910007&w=2

There's the simple performance measurement comparing these two versions,
the environment is the same as we listed in the previous version.

Use 8 threads to compress the data in the source QEMU
- with compress-wait-thread = off


      total time        busy-ratio
--------------------------------------------------
v1    125066            0.38
v2    120444            0.35

- with compress-wait-thread = on
         total time    busy-ratio
--------------------------------------------------
v1    164426            0
v2    142609            0

The v2 win slightly.

Xiao Guangrong (5):
  bitops: introduce change_bit_atomic
  util: introduce threaded workqueue
  migration: use threaded workqueue for compression
  migration: use threaded workqueue for decompression
  tests: add threaded-workqueue-bench

 include/qemu/bitops.h             |  13 +
 include/qemu/threaded-workqueue.h |  94 +++++++
 migration/ram.c                   | 538 ++++++++++++++------------------------
 tests/Makefile.include            |   5 +-
 tests/threaded-workqueue-bench.c  | 256 ++++++++++++++++++
 util/Makefile.objs                |   1 +
 util/threaded-workqueue.c         | 466 +++++++++++++++++++++++++++++++++
 7 files changed, 1030 insertions(+), 343 deletions(-)
 create mode 100644 include/qemu/threaded-workqueue.h
 create mode 100644 tests/threaded-workqueue-bench.c
 create mode 100644 util/threaded-workqueue.c
```
#### [PATCH 0/7] kvm: selftests: dirty_log_test: test with high GPAs
##### From: Andrew Jones <drjones@redhat.com>

```c

High GPAs may not get used much with "normal" guest configs. Let's make
sure we use them with the selftests. I've tested this on an AArch64
machine that supports up to 48-bit IPAs using a host kernel with the
recent > 40-bit IPA patches. We may want to modify the framework for
x86_64 someday to enable tests for 5-level page tables (or even just
to fully support the use of 4-level page tables.) For now, I just
made sure the x86_64 dirty log test still runs.

Andrew Jones (7):
  kvm: selftests: x86_64: dirty_log_test: fix -t
  kvm: selftests: dirty_log_test: don't identity map the test mem
  kvm: selftests: dirty_log_test: always use -t
  kvm: selftests: dirty_log_test: reset guest test phys offset
  kvm: selftests: dirty_log_test: improve mode param management
  kvm: selftests: add pa-48/va-48 VM modes
  kvm: selftests: aarch64: dirty_log_test: support greater than 40-bit
    IPAs

 tools/testing/selftests/kvm/dirty_log_test.c  | 146 +++++++++++-------
 .../testing/selftests/kvm/include/kvm_util.h  |   4 +
 .../selftests/kvm/lib/aarch64/processor.c     |  18 ++-
 tools/testing/selftests/kvm/lib/kvm_util.c    |  40 ++++-
 .../selftests/kvm/lib/kvm_util_internal.h     |   1 +
 5 files changed, 139 insertions(+), 70 deletions(-)
```
#### [kvm PATCH v7 0/2] shrink vcpu_vmx down to order 2
##### From: Marc Orr <marcorr@google.com>

```c

Compared to the last version, I've:
(1) Added a comment to explain the FPU checks in kvm_arch_init()
(2) Changed the kmem_cache_create_usercopy() to kmem_cache_create()

Marc Orr (2):
  kvm: x86: Use task structs fpu field for user
  kvm: x86: Dynamically allocate guest_fpu

 arch/x86/include/asm/kvm_host.h | 10 +++---
 arch/x86/kvm/svm.c              | 10 ++++++
 arch/x86/kvm/vmx.c              | 10 ++++++
 arch/x86/kvm/x86.c              | 55 ++++++++++++++++++++++++---------
 4 files changed, 65 insertions(+), 20 deletions(-)
```
#### [kvm PATCH v8 0/2] shrink vcpu_vmx down to order 2
##### From: Marc Orr <marcorr@google.com>

```c

Compared to the last version, I've:
(0) Actually update the patches, as explained below.
(1) Added a comment to explain the FPU checks in kvm_arch_init()
(2) Changed the kmem_cache_create_usercopy() to kmem_cache_create()

Marc Orr (2):
  kvm: x86: Use task structs fpu field for user
  kvm: x86: Dynamically allocate guest_fpu

 arch/x86/include/asm/kvm_host.h | 10 +++---
 arch/x86/kvm/svm.c              | 10 ++++++
 arch/x86/kvm/vmx.c              | 10 ++++++
 arch/x86/kvm/x86.c              | 55 ++++++++++++++++++++++++---------
 4 files changed, 65 insertions(+), 20 deletions(-)
```
