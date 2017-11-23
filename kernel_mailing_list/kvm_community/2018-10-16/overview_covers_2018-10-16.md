

#### [PATCH 0/4] migration: improve multithreads
##### From: guangrong.xiao@gmail.com
X-Google-Original-From: xiaoguangrong@tencent.com
From: Xiao Guangrong <xiaoguangrong@tencent.com>

```c

From: Xiao Guangrong <xiaoguangrong@tencent.com>

This is the last part of our previous work:
   https://lists.gnu.org/archive/html/qemu-devel/2018-06/msg00526.html

This part finally improves the multithreads model used by compression
and decompression, that makes the compression feature is really usable
in the production.

Comparing with the previous version, we
1. port ptr_ring from linux kernel and use it to instead of lockless
   ring designed by ourself

   ( Michael, i added myself to the list of author in that file, if
    you dislike it, i'm fine to drop it. :) )

2  search all threads to detect if it has free room in its local ring
   to contain a request instead of RR to reduce busy-ratio

Background
----------
Current implementation of compression and decompression are very
hard to be enabled on productions. We noticed that too many wait-wakes
go to kernel space and CPU usages are very low even if the system
is really free

The reasons are:
1) there are two many locks used to do synchronous，there
　　is a global lock and each single thread has its own lock,
　　migration thread and work threads need to go to sleep if
　　these locks are busy

2) migration thread separately submits request to the thread
   however, only one request can be pended, that means, the
   thread has to go to sleep after finishing the request

Our Ideas
---------
To make it work better, we introduce a lockless multithread model,
the user, currently it is the migration thread, submits request
to each thread which has its own ring whose capacity is 4 and
puts the result to a global ring where the user fetches result
out and do remaining operations for the request, e.g, posting the
compressed data out for migration on the source QEMU

Performance Result
-----------------
We tested live migration on two hosts:
   Intel(R) Xeon(R) Gold 6142 CPU @ 2.60GHz * 64 + 256G memory

to migration a VM between each other, which has 16 vCPUs and 120G
memory, during the migration, multiple threads are repeatedly writing
the memory in the VM

We used 16 threads on the destination to decompress the data and on the
source, we tried 4, 8 and 16 threads to compress the data

1) 4 threads， compress-wait-thread = off

CPU usages

         main thread      compression threads
-----------------------------------------------
before    66.2              32.4~36.8
after     56.5              59.4~60.9

Migration result

         total time        busy-ratio
--------------------------------------------------
before   247371             0.54
after    138326             0.55

2) 4 threads， compress-wait-thread = on

CPU usages

         main thread      compression threads
-----------------------------------------------
before    55.1              51.0~63.3
after     99.9              99.9

Migration result

         total time        busy-ratio
--------------------------------------------------
before   CAN'T COMPLETE    0
after    338692            0

3) 8 threads， compress-wait-thread = off

CPU usages

         main thread      compression threads
-----------------------------------------------
before    43.3              17.5~32.5
after     54.5              54.5~56.8

Migration result

         total time        busy-ratio
--------------------------------------------------
before   427384            0.19
after    125066            0.38

4) 8 threads， compress-wait-thread = on
CPU usages

         main thread      compression threads
-----------------------------------------------
before    96.3              2.3~46.8
after     90.6              90.6~91.8

Migration result

         total time        busy-ratio
--------------------------------------------------
before   CAN'T COMPLETE    0
after    164426            0

5) 16 threads， compress-wait-thread = off
CPU usages

         main thread      compression threads
-----------------------------------------------
before    56.2              6.2~56.2
after     37.8              37.8~40.2

Migration result

         total time        busy-ratio
--------------------------------------------------
before   2317123           0.02
after    149006            0.02

5) 16 threads， compress-wait-thread = on
CPU usages

         main thread      compression threads
-----------------------------------------------
before    48.3               1.7~31.0
after     43.9              42.1~45.6

Migration result

         total time        busy-ratio
--------------------------------------------------
before   1792817           0.00
after    161423            0.00

Xiao Guangrong (4):
  ptr_ring: port ptr_ring from linux kernel to QEMU
  migration: introduce lockless multithreads model
  migration: use lockless Multithread model for compression
  migration: use lockless Multithread model for decompression

 include/qemu/lockless-threads.h |  63 +++++
 include/qemu/ptr_ring.h         | 235 ++++++++++++++++++
 migration/ram.c                 | 535 +++++++++++++++-------------------------
 util/Makefile.objs              |   1 +
 util/lockless-threads.c         | 373 ++++++++++++++++++++++++++++
 5 files changed, 865 insertions(+), 342 deletions(-)
 create mode 100644 include/qemu/lockless-threads.h
 create mode 100644 include/qemu/ptr_ring.h
 create mode 100644 util/lockless-threads.c
```
#### [PATCH v6 00/13] KVM: nVMX: Enlightened VMCS for Hyper-V on KVM
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v5:
- Rebase to kvm/queue.
- Add "KVM: selftests: state_test: test bare VMXON migration" patch.

Original description:

This is an initial implementation of Enlightened VMCS for nested Hyper-V on
KVM. Using it helps to spare 1500 cpu cycles for nested vmexit (tight cpuid
loop in WS2016 with Hyper-V role on KVM: 15200 cycles -> 13700 cycles).

Ladi Prosek (1):
  KVM: hyperv: define VP assist page helpers

Vitaly Kuznetsov (12):
  KVM: VMX: refactor evmcs_sanitize_exec_ctrls()
  KVM: nVMX: add KVM_CAP_HYPERV_ENLIGHTENED_VMCS capability
  KVM: nVMX: add enlightened VMCS state
  KVM: nVMX: implement enlightened VMPTRLD and VMCLEAR
  KVM: nVMX: optimize prepare_vmcs02{,_full} for Enlightened VMCS case
  x86/kvm/hyperv: don't clear VP assist pages on init
  x86/kvm/lapic: preserve gfn_to_hva_cache len on cache reinit
  x86/kvm/nVMX: allow bare VMXON state migration
  KVM: selftests: state_test: test bare VMXON migration
  x86/kvm/nVMX: nested state migration for Enlightened VMCS
  tools/headers: update kvm.h
  KVM: selftests: add Enlightened VMCS test

 arch/x86/include/asm/kvm_host.h               |    3 +
 arch/x86/include/uapi/asm/kvm.h               |    1 +
 arch/x86/kvm/hyperv.c                         |   31 +-
 arch/x86/kvm/hyperv.h                         |    4 +
 arch/x86/kvm/lapic.c                          |   14 +-
 arch/x86/kvm/lapic.h                          |    2 +-
 arch/x86/kvm/svm.c                            |    9 +
 arch/x86/kvm/vmx.c                            |  887 ++++++++++---
 arch/x86/kvm/x86.c                            |   23 +-
 include/uapi/linux/kvm.h                      |    1 +
 tools/include/uapi/linux/kvm.h                |    5 +
 tools/testing/selftests/kvm/Makefile          |    1 +
 tools/testing/selftests/kvm/include/evmcs.h   | 1098 +++++++++++++++++
 .../selftests/kvm/include/x86_64/vmx.h        |   29 +
 tools/testing/selftests/kvm/lib/x86_64/vmx.c  |   51 +-
 .../testing/selftests/kvm/x86_64/evmcs_test.c |  159 +++
 .../testing/selftests/kvm/x86_64/state_test.c |   22 +-
 .../kvm/x86_64/vmx_tsc_adjust_test.c          |    1 +
 18 files changed, 2159 insertions(+), 182 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/include/evmcs.h
 create mode 100644 tools/testing/selftests/kvm/x86_64/evmcs_test.c
```
#### [RFC PATCH v1 0/4] Add migration support for VFIO device
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c

Add migration support for VFIO device

This Patch set include patches as below:
- Define KABI for VFIO device for migration support.
- Generic migration functionality for VFIO device.
  * This patch set adds functionality only for PCI devices, but can be
    extended to other VFIO devices.
  * Added all the basic functions required for pre-copy, stop-and-copy and
    resume phases of migration.
  * Added state change notifier and from that notifier function, VFIO
    device's state changed is conveyed to VFIO vendor driver.
  * During save setup phase and resume/load setup phase, migration region
    is queried from vendor driver and is mmaped by QEMU. This region is
    used to read/write data from and to vendor driver.
  * .save_live_pending, .save_live_iterate and .is_active_iterate are
    implemented to use QEMU's functionality of iteration during pre-copy
    phase.
  * In .save_live_complete_precopy, that is in stop-and-copy phase,
    iteration to read data from vendor driver is implemented till pending
    bytes returned by vendor driver are not zero.
  * .save_cleanup and .load_cleanup are implemented to unmap migration
    region that was setup duing setup phase.
  * Added function to get dirty pages bitmap from vendor driver.
- Add vfio_listerner_log_sync to mark dirty pages.
- Make VFIO PCI device migration capable.

Thanks,
Kirti

Kirti Wankhede (4):
  VFIO KABI for migration interface
  Add migration functions for VFIO devices
  Add vfio_listerner_log_sync to mark dirty pages
  Make vfio-pci device migration capable.

 hw/vfio/Makefile.objs         |   2 +-
 hw/vfio/common.c              |  32 ++
 hw/vfio/migration.c           | 716 ++++++++++++++++++++++++++++++++++++++++++
 hw/vfio/pci.c                 |  13 +-
 include/hw/vfio/vfio-common.h |  23 ++
 linux-headers/linux/vfio.h    |  91 ++++++
 6 files changed, 869 insertions(+), 8 deletions(-)
 create mode 100644 hw/vfio/migration.c
```
