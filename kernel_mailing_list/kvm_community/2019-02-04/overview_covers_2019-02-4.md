

#### [PATCH kvmtool v2 0/3] Fix GCC 8 warnings
##### From: Anisse Astier <aastier@freebox.fr>

```c

Hi,

This patch series fixes a few warnings when building kvmtool with GCC8.
I'm not sure it's the best solution for each case.

Note that kvmtool was removed from Debian testing following these
warnings (but it's using an old version):
https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=897777

I do not know why it wasn't built with WERROR=0 instead.

Changes since v1:
 - series rebased on master
 - patch 1: fixed snprintf size thanks to Will's review
 - patch 2: added another similar warning fix in the same file
 - patch 3: errno isn't touched anymore (thanks Will)

@Andre: I did not pick up your Reviewed-by for patch 2 since it was
modified afterwards.

Regards,

Anisse
Signed-off-by: Anisse Astier <aastier@freebox.fr>
---
Anisse Astier (3):
  builtin-run: Fix warning when resolving path
  virtio: fix warning on strncpy
  kvmtool: 9p: fix overapping snprintf

 builtin-run.c | 4 +++-
 virtio/9p.c   | 9 ++++++++-
 virtio/net.c  | 6 +++---
 3 files changed, 14 insertions(+), 5 deletions(-)
```
#### [kvm-unit-tests PATCH v3 0/5] arm/arm64: Add support for running
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c

kvm-unit-tests is designed to be run with QEMU as the virtual machine
monitor. It relies on devices emulated by QEMU (like isa-debug-exit or
testdev) and it makes certain assumptions based on the implicit QEMU
virtual environment configuration (like the serial base address).

kvmtool [1] is a lightweight virtual machine monitor for running KVM
guests. kvmtool has reduced complexity compared to QEMU and is easily
hackable.

This patch series aims to make it possible to run kvm-unit-tests using
kvmtool on the arm and arm64 architectures, with two caveats:

(1) When terminating a test, the userspace process won't exit with an exit
code that signals the success or failure of the test. Output from the test
can still be parsed to determine the outcome of the test.

(2) kvmtool has been designed to work with a linux guest and it
automatically generates the command line arguments for a Linux kernel. The
arm/arm64 selftest and gic tests will fail if unexpected command line
arguments are found. To get around this limitation, the test binary needs
to be loaded using the --firmware option introduced by kvmtool in commit
5e4b563d75b9 ("arm: Allow command line for firmware"). This option
suppresses the automatic kernel command line and can be used to run all
tests, not just the tests that require specific arguments.

The run scripts haven't been modified. To run a test under kvmtool, one
needs to launch kvmtool manually. For example, to run the timer test the
following command can be used:

lkvm run --cpus 1 --console serial --firmware timer.flat.

To run the gicv3-ipi test:

lkvm run --cpus 8 --console serial --params "ipi" --irqchip gicv3 \
    --firmware gic.flat

Changes in v3:
* Updated cover letter with information about the kvmtool --firmware
  option.
* Gathered Reviewed-by tags.
* Renamed the config.h define UART_EARLY_BASE to CONFIG_UART_EARLY_BASE and
  made the necessary casts in lib/arm/io.c

Changes in v2:
* Generate lib/config.h when configuring kvm-unit-tests; arm/arm64 uses it
  to get the UART address.
* Added --vmm configure option for arm/arm64 which will set the UART
  address in lib/config.h when the tests are run under QEMU or kvmtool.
* Renamed psci_sys_reset() to psci_system_reset().
* Dropped patches that allowed a test to ignore unexpected command line
  arguments.

Summary:
* Patches 1, 2 and 3 add support for configuring kvm-unit-tests on arm and
  arm64 to use the ns16550a UART emulated by kvmtool.
* Patches 4 and 5 provide an alternative mechanism for terminating the
  virtual machine by using PSCI.

[1] https://git.kernel.org/pub/scm/linux/kernel/git/will/kvmtool.git/
[2] https://www.spinics.net/lists/kvm-arm/msg34352.html

Alexandru Elisei (5):
  lib: arm: Use UART address from generated config.h
  configure: arm/arm64: Add --vmm option with no effect
  lib: arm: Use ns16550a UART when --vmm=kvmtool
  lib: arm: Implement PSCI SYSTEM_OFF in psci_system_off()
  lib: arm: Fallback to psci_system_off() in exit()

 configure          | 32 ++++++++++++++++++++++++++++++++
 Makefile           |  2 +-
 lib/arm/asm/psci.h |  3 ++-
 lib/arm/io.c       | 41 ++++++++++++++++++++++++++---------------
 lib/arm/psci.c     |  8 +++++++-
 .gitignore         |  1 +
 6 files changed, 69 insertions(+), 18 deletions(-)
Reviewed-by: Alexandru Elisei <alexandru.elisei@arm.com>
Tested-by: Alexandru Elisei <alexandru.elisei@arm.com>
```
#### [RFC PATCH 0/8] KVM: x86: svm: Enabling AVIC with in kernel irqchip
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c

Currently, AMD AVIC can only be enabled when creating VM in irqchip
split mode, which is due to the following issues:

   * AMD AVIC does not support ExtINT, which is required during booting
     phase of Windows and FreeBSD VMs. This results in hanging in the
     boot loaders.

   * Untrap APIC EOI write for edge-trigger interrpt.
     Please see 67034bb9dd5e ('KVM: SVM: Add irqchip_split() checks
     before enabling AVIC') for more information.

This restriction makes AVIC difficult to enable since it depends on
the non-default QEMU's kernel_irqchip=split option. Therefore, this RFC
series tries to provide workaround for the issues above, and allow AVIC to
work with the option kernel_irqchip=on (QEMU default).

Patch 1 fixes AVIC deactivation.
Patch 2-6 introduces run-time AVIC acticate/deactivate support.
Patch 7 provide workaround for untrap APIC EOI.
Patch 8 removes the kernel irqchip split restriction.

This series has been tested booting Linux, Windows, and FreeBSD VMs
with kernel_irqchip=off/split/on.

Thanks,
Suravee

Julian Stecklina (1):
  KVM: i8254: Remove need for irq ack notifier

Suravee Suthikulpanit (7):
  svm: Fix improper check when deactivate AVIC
  KVM: x86: Add interface for run-time activate/de-activate APIC
    virtualization
  KVM: x86: Add callback functions for handling APIC ID, DFR and LDR
    update
  svm: Add AMD AVIC handlers for APIC ID, DFR and LDR update
  svm: Add support for APIC_ACCESS_PAGE_PRIVATE_MEMSLOT setup/destroy
  svm: Temporary deactivate AVIC during ExtINT handling
  svm: Allow AVIC with in-kernel irqchip mode

 arch/x86/include/asm/kvm_host.h |  11 +++
 arch/x86/kvm/i8254.c            |  22 +-----
 arch/x86/kvm/i8254.h            |   2 -
 arch/x86/kvm/lapic.c            |  11 ++-
 arch/x86/kvm/svm.c              | 118 +++++++++++++++++++++++++++++---
 arch/x86/kvm/x86.c              |  36 ++++++++++
 6 files changed, 164 insertions(+), 36 deletions(-)
```
#### [PATCH kvmtool 0/3] Fix more GCC 8 strncpy warnings
##### From: Andre Przywara <andre.przywara@arm.com>

```c

My build of GCC 8.2 from the FSF vanilla sources triggered more GCC 8
warnings, which are turned into errors and break the build.

Fix them, mostly by using strlcpy() instead of strncpy.

Those three patches go on top of Anisse's series and allow a clean
build with GCC 8.2.0 for me.

Cheers,
Andre.

Andre Przywara (3):
  builtin-run: Replace strncpy calls with strlcpy
  virtio: use strlcpy
  net/dhcp: avoid misleading strncpy

 builtin-run.c  | 4 ++--
 net/uip/dhcp.c | 2 +-
 virtio/net.c   | 5 +++--
 virtio/scsi.c  | 3 ++-
 4 files changed, 8 insertions(+), 6 deletions(-)
```
#### [RFC PATCH 0/4] kvm: Report unused guest pages to host
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c

This patch set provides a mechanism by which guests can notify the host of
pages that are not currently in use. Using this data a KVM host can more
easily balance memory workloads between guests and improve overall system
performance by avoiding unnecessary writing of unused pages to swap.

In order to support this I have added a new hypercall to provided unused
page hints and made use of mechanisms currently used by PowerPC and s390
architectures to provide those hints. To reduce the overhead of this call
I am only using it per huge page instead of of doing a notification per 4K
page. By doing this we can avoid the expense of fragmenting higher order
pages, and reduce overall cost for the hypercall as it will only be
performed once per huge page.

Because we are limiting this to huge pages it was necessary to add a
secondary location where we make the call as the buddy allocator can merge
smaller pages into a higher order huge page.

This approach is not usable in all cases. Specifically, when KVM direct
device assignment is used, the memory for a guest is permanently assigned
to physical pages in order to support DMA from the assigned device. In
this case we cannot give the pages back, so the hypercall is disabled by
the host.

Another situation that can lead to issues is if the page were accessed
immediately after free. For example, if page poisoning is enabled the
guest will populate the page *after* freeing it. In this case it does not
make sense to provide a hint about the page being freed so we do not
perform the hypercalls from the guest if this functionality is enabled.

My testing up till now has consisted of setting up 4 8GB VMs on a system
with 32GB of memory and 4GB of swap. To stress the memory on the system I
would run "memhog 8G" sequentially on each of the guests and observe how
long it took to complete the run. The observed behavior is that on the
systems with these patches applied in both the guest and on the host I was
able to complete the test with a time of 5 to 7 seconds per guest. On a
system without these patches the time ranged from 7 to 49 seconds per
guest. I am assuming the variability is due to time being spent writing
pages out to disk in order to free up space for the guest.
---

Alexander Duyck (4):
      madvise: Expose ability to set dontneed from kernel
      kvm: Add host side support for free memory hints
      kvm: Add guest side support for free memory hints
      mm: Add merge page notifier


 Documentation/virtual/kvm/cpuid.txt      |    4 ++
 Documentation/virtual/kvm/hypercalls.txt |   14 ++++++++
 arch/x86/include/asm/page.h              |   25 +++++++++++++++
 arch/x86/include/uapi/asm/kvm_para.h     |    3 ++
 arch/x86/kernel/kvm.c                    |   51 ++++++++++++++++++++++++++++++
 arch/x86/kvm/cpuid.c                     |    6 +++-
 arch/x86/kvm/x86.c                       |   35 +++++++++++++++++++++
 include/linux/gfp.h                      |    4 ++
 include/linux/mm.h                       |    2 +
 include/uapi/linux/kvm_para.h            |    1 +
 mm/madvise.c                             |   13 +++++++-
 mm/page_alloc.c                          |    2 +
 12 files changed, 158 insertions(+), 2 deletions(-)

--
```
#### [RFC][Patch v8 0/7] KVM: Guest Free Page Hinting
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c

The following patch-set proposes an efficient mechanism for handing freed memory between the guest and the host. It enables the guests with no page cache to rapidly free and reclaims memory to and from the host respectively.

Benefit:
With this patch-series, in our test-case, executed on a single system and single NUMA node with 15GB memory, we were able to successfully launch atleast 5 guests 
when page hinting was enabled and 3 without it. (Detailed explanation of the test procedure is provided at the bottom).

Changelog in V8:
In this patch-series, the earlier approach [1] which was used to capture and scan the pages freed by the guest has been changed. The new approach is briefly described below:

The patch-set still leverages the existing arch_free_page() to add this functionality. It maintains a per CPU array which is used to store the pages freed by the guest. The maximum number of entries which it can hold is defined by MAX_FGPT_ENTRIES(1000). When the array is completely filled, it is scanned and only the pages which are available in the buddy are stored. This process continues until the array is filled with pages which are part of the buddy free list. After which it wakes up a kernel per-cpu-thread.
This kernel per-cpu-thread rescans the per-cpu-array for any re-allocation and if the page is not reallocated and present in the buddy, the kernel thread attempts to isolate it from the buddy. If it is successfully isolated, the page is added to another per-cpu array. Once the entire scanning process is complete, all the isolated pages are reported to the host through an existing virtio-balloon driver.

Known Issues:
	* Fixed array size: The problem with having a fixed/hardcoded array size arises when the size of the guest varies. For example when the guest size increases and it starts making large allocations fixed size limits this solution's ability to capture all the freed pages. This will result in less guest free memory getting reported to the host.

Known code re-work:
	* Plan to re-use Wei's work, which communicates the poison value to the host.
	* The nomenclatures used in virtio-balloon needs to be changed so that the code can easily be distinguished from Wei's Free Page Hint code.
	* Sorting based on zonenum, to avoid repetitive zone locks for the same zone.

Other required work:
	* Run other benchmarks to evaluate the performance/impact of this approach.

Test case:
Setup:
Memory-15837 MB
Guest Memory Size-5 GB
Swap-Disabled
Test Program-Simple program which allocates 4GB memory via malloc, touches it via memset and exits.
Use case-Number of guests that can be launched completely including the successful execution of the test program.
Procedure: 
The first guest is launched and once its console is up, the test allocation program is executed with 4 GB memory request (Due to this the guest occupies almost 4-5 GB of memory in the host in a system without page hinting). Once this program exits at that time another guest is launched in the host and the same process is followed. We continue launching the guests until a guest gets killed due to low memory condition in the host.

Result:
Without Hinting-3 Guests
With Hinting-5 to 7 Guests(Based on the amount of memory freed/captured).

[1] https://www.spinics.net/lists/kvm/msg170113.html
```
