

#### [PATCH 0/5] x86: KVM: svm: get rid of hardcoded instructions lengths
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since RFC (It's been awhile and I apologize for that):
- Dropped ' + 3' from vmrun_interception() as well.
- Added xsetbv's implementation to the emulator [Paolo Bonzini]
- Added Jim's R-b tags to PATCHes 2 and 3. 
- Tested with the newly added 'nrips' svm module parameter.

Original description:

Jim rightfully complains that hardcoding instuctions lengths is not always
correct: additional (redundant) prefixes can be used. Luckily, the ugliness
is mostly harmless: modern AMD CPUs support NRIP_SAVE feature but I'd like
to clean things up and sacrifice speed in favor of correctness.

Vitaly Kuznetsov (5):
  x86: KVM: svm: don't pretend to advance RIP in case
    wrmsr_interception() results in #GP
  x86: KVM: svm: avoid flooding logs when skip_emulated_instruction()
    fails
  x86: KVM: svm: clear interrupt shadow on all paths in
    skip_emulated_instruction()
  x86: KVM: add xsetbv to the emulator
  x86: KVM: svm: remove hardcoded instruction length from intercepts

 arch/x86/include/asm/kvm_emulate.h |  3 ++-
 arch/x86/kvm/emulate.c             | 23 ++++++++++++++++++++++-
 arch/x86/kvm/svm.c                 | 23 ++++++++---------------
 arch/x86/kvm/x86.c                 |  6 ++++++
 4 files changed, 38 insertions(+), 17 deletions(-)
```
#### [patch 0/5] posix-cpu-timers: Move expiry into task work context
##### From: Thomas Gleixner <tglx@linutronix.de>

```c

Running posix cpu timers in hard interrupt context has a few downsides:

 - For PREEMPT_RT it cannot work as the expiry code needs to take sighand
   lock, which is a 'sleeping spinlock' in RT

 - For fine grained accounting it's just wrong to run this in context of
   the timer interrupt because that way a process specific cpu time is
   accounted to the timer interrupt.

There is no real hard requirement to run the expiry code in hard interrupt
context. The posix CPU timers are an approximation anyway, so having them
expired and evaluated in task work context does not really make them worse.

That unearthed the fact that KVM is missing to handle task work before
entering a VM which is delaying pending task work until the vCPU thread
goes all the way back to user space qemu.

The series implements the necessary handling for x86/KVM and switches the
posix cpu timer expiry into task work for X86. The posix timer modification
is conditional on a selectable config switch as this requires that
task work is handled in KVM.

The available tests pass and no problematic difference has been observed.

Thanks,

	tglx

8<--------------------
 arch/x86/kvm/x86.c             |    8 ++++-
 arch/x86/Kconfig               |    1 
 include/linux/sched.h          |    3 ++
 include/linux/tracehook.h      |   15 ++++++++++
 kernel/task_work.c             |   19 ++++++++++++
 kernel/time/Kconfig            |    5 +++
 kernel/time/posix-cpu-timers.c |   61 ++++++++++++++++++++++++++++++-----------
 7 files changed, 95 insertions(+), 17 deletions(-)
```
#### [PATCH v2 00/11] VSOCK: add vsock_test test suite
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c

The vsock_diag.ko module already has a test suite but the core AF_VSOCK
functionality has no tests.  This patch series adds several test cases that
exercise AF_VSOCK SOCK_STREAM socket semantics (send/recv, connect/accept,
half-closed connections, simultaneous connections).

Stefan: Do you think we should have a single application or is better to
split it in single tests (e.g. vsock_test_send_recv, vsock_test_half_close,
vsock_test_multiconnection, etc.)?

Jorgen: Please test the VMCI transport and let me know if the fixes work.
I added the '--transport' parameter to skip the read() on the half-closed
connection test.

Dexuan: Do you think can be useful to test HyperV?

The v1 of this series was originally sent by Stefan. I rebased on master
and tried to fix some issues reported by Jorgen.

v2:
- Patch 1 added by Stefan to fix header include in vsock_diag_test.
- Patch 2 added by Stefan to add SPDX identifiers. I modified it to be
  aligned with SPDX currently used on master.
- Patch 3:
  * fixed SPDX [Stefano].
- Patch 7:
  * Drop unnecessary includes [Stefan]
  * Fixed SPDX [Stefano]
  * Set MULTICONN_NFDS to 100 [Stefano]
  * Changed (i % 1) in (i % 2) in the 'multiconn' test [Stefano]
- Patches 8,9,10 added to skip read after close in test_stream*close tests
  on a VMCI host.
- Patch 11 added to wait for the remote to close the connection, before
  check if a send returns -EPIPE.

v1: https://patchwork.ozlabs.org/cover/847998/

Stefan Hajnoczi (7):
  VSOCK: fix header include in vsock_diag_test
  VSOCK: add SPDX identifiers to vsock tests
  VSOCK: extract utility functions from vsock_diag_test.c
  VSOCK: extract connect/accept functions from vsock_diag_test.c
  VSOCK: add full barrier between test cases
  VSOCK: add send_byte()/recv_byte() test utilities
  VSOCK: add AF_VSOCK test cases

Stefano Garzarella (4):
  VSOCK: add vsock_get_local_cid() test utility
  vsock_test: add --transport parameter
  vsock_test: skip read() in test_stream*close tests on a VMCI host
  vsock_test: wait for the remote to close the connection

 tools/testing/vsock/.gitignore        |   1 +
 tools/testing/vsock/Makefile          |   9 +-
 tools/testing/vsock/README            |   3 +-
 tools/testing/vsock/control.h         |   1 +
 tools/testing/vsock/timeout.h         |   1 +
 tools/testing/vsock/util.c            | 342 ++++++++++++++++++++++++
 tools/testing/vsock/util.h            |  54 ++++
 tools/testing/vsock/vsock_diag_test.c | 170 ++----------
 tools/testing/vsock/vsock_test.c      | 362 ++++++++++++++++++++++++++
 9 files changed, 793 insertions(+), 150 deletions(-)
 create mode 100644 tools/testing/vsock/util.c
 create mode 100644 tools/testing/vsock/util.h
 create mode 100644 tools/testing/vsock/vsock_test.c
```
#### [PATCH 0/3] KVM: x86/mmu: minor MMIO SPTE cleanup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

A few loosely related MMIO SPTE patches to get rid of a bit of cruft that
has been a source of annoyance when mucking around in the MMIO code.

No functional changes intended.

Sean Christopherson (3):
  KVM: x86: Rename access permissions cache member in struct
    kvm_vcpu_arch
  KVM: x86/mmu: Add explicit access mask for MMIO SPTEs
  KVM: x86/mmu: Consolidate "is MMIO SPTE" code

 Documentation/virtual/kvm/mmu.txt |  4 ++--
 arch/x86/include/asm/kvm_host.h   |  2 +-
 arch/x86/kvm/mmu.c                | 31 +++++++++++++++++--------------
 arch/x86/kvm/mmu.h                |  2 +-
 arch/x86/kvm/vmx/vmx.c            |  2 +-
 arch/x86/kvm/x86.c                |  2 +-
 arch/x86/kvm/x86.h                |  2 +-
 7 files changed, 24 insertions(+), 21 deletions(-)
```
#### [PATCH v3 0/6] mm / virtio: Provide support for unused page
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c

This series provides an asynchronous means of reporting to a hypervisor
that a guest page is no longer in use and can have the data associated
with it dropped. To do this I have implemented functionality that allows
for what I am referring to as unused page reporting

The functionality for this is fairly simple. When enabled it will allocate
statistics to track the number of reported pages in a given free area.
When the number of free pages exceeds this value plus a high water value,
currently 32, it will begin performing page reporting which consists of
pulling pages off of free list and placing them into a scatter list. The
scatterlist is then given to the page reporting device and it will perform
the required action to make the pages "reported", in the case of
virtio-balloon this results in the pages being madvised as MADV_DONTNEED
and as such they are forced out of the guest. After this they are placed
back on the free list, and an additional bit is added if they are not
merged indicating that they are a reported buddy page instead of a
standard buddy page. The cycle then repeats with additional non-reported
pages being pulled until the free areas all consist of reported pages.

I am leaving a number of things hard-coded such as limiting the lowest
order processed to PAGEBLOCK_ORDER, and have left it up to the guest to
determine what the limit is on how many pages it wants to allocate to
process the hints. The upper limit for this is based on the size of the
queue used to store the scatterlist.

My primary testing has just been to verify the memory is being freed after
allocation by running memhog 40g on a 40g guest and watching the total
free memory via /proc/meminfo on the host. With this I have verified most
of the memory is freed after each iteration. As far as performance I have
been mainly focusing on the will-it-scale/page_fault1 test running with
16 vcpus. With that I have seen up to a 2% difference between the base
kernel without these patches and the patches with virtio-balloon enabled
or disabled.

One side effect of these patches is that the guest becomes much more
resilient in terms of NUMA locality. With the pages being freed and then
reallocated when used it allows for the pages to be much closer to the
active thread, and as a result there can be situations where this patch
set will out-perform the stock kernel when the guest memory is not local
to the guest vCPUs.

Patch 4 is a bit on the large side at about 600 lines of change, however
I really didn't see a good way to break it up since each piece feeds into
the next. So I couldn't add the statistics by themselves as it didn't
really make sense to add them without something that will either read or
increment/decrement them, or add the Hinted state without something that
would set/unset it. As such I just ended up adding the entire thing as
one patch. It makes it a bit bigger but avoids the issues in the previous
set where I was referencing things that had not yet been added.

Changes from the RFC:
https://lore.kernel.org/lkml/20190530215223.13974.22445.stgit@localhost.localdomain/
Moved aeration requested flag out of aerator and into zone->flags.
Moved boundary out of free_area and into local variables for aeration.
Moved aeration cycle out of interrupt and into workqueue.
Left nr_free as total pages instead of splitting it between raw and aerated.
Combined size and physical address values in virtio ring into one 64b value.

Changes from v1:
https://lore.kernel.org/lkml/20190619222922.1231.27432.stgit@localhost.localdomain/
Dropped "waste page treatment" in favor of "page hinting"
Renamed files and functions from "aeration" to "page_hinting"
Moved from page->lru list to scatterlist
Replaced wait on refcnt in shutdown with RCU and cancel_delayed_work_sync
Virtio now uses scatterlist directly instead of intermediate array
Moved stats out of free_area, now in separate area and pointed to from zone
Merged patch 5 into patch 4 to improve review-ability
Updated various code comments throughout

Changes from v2:
https://lore.kernel.org/lkml/20190724165158.6685.87228.stgit@localhost.localdomain/
Dropped "page hinting" in favor of "page reporting"
Renamed files from "hinting" to "reporting"
Replaced "Hinted" page type with "Reported" page flag
Added support for page poisoning while hinting is active
Add QEMU patch that implements PAGE_POISON feature
---

Alexander Duyck (6):
      mm: Adjust shuffle code to allow for future coalescing
      mm: Move set/get_pcppage_migratetype to mmzone.h
      mm: Use zone and order instead of free area in free_list manipulators
      mm: Introduce Reported pages
      virtio-balloon: Pull page poisoning config out of free page hinting
      virtio-balloon: Add support for providing unused page reports to host


 drivers/virtio/Kconfig              |    1 
 drivers/virtio/virtio_balloon.c     |   75 ++++++++-
 include/linux/mmzone.h              |  116 ++++++++------
 include/linux/page-flags.h          |   11 +
 include/linux/page_reporting.h      |  138 ++++++++++++++++
 include/uapi/linux/virtio_balloon.h |    1 
 mm/Kconfig                          |    5 +
 mm/Makefile                         |    1 
 mm/internal.h                       |   18 ++
 mm/memory_hotplug.c                 |    1 
 mm/page_alloc.c                     |  238 ++++++++++++++++++++--------
 mm/page_reporting.c                 |  299 +++++++++++++++++++++++++++++++++++
 mm/shuffle.c                        |   24 ---
 mm/shuffle.h                        |   32 ++++
 14 files changed, 821 insertions(+), 139 deletions(-)
 create mode 100644 include/linux/page_reporting.h
 create mode 100644 mm/page_reporting.c

--
```
