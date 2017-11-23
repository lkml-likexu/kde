

#### [kvm-unit-tests PATCH v2 0/5] arm/arm64: Add support for running
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
automatically generates the command line arguments for a Linux kernel. This
causes the arm/arm64 selftest and gic tests to fail because those tests are
very specific with regards to the command line arguments that are provided
by the virtual machine manager.

With regards to (2), a patch was posted that seeks too eliminate this
behavior for kvmtool [2].

The run scripts haven't been modified. To run a test under kvmtool, one
needs to launch kvmtool manually. For example, to run the timer test the
following command can be used:

lkvm run -c 1 --console=serial -k timer.flat.

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

 configure          | 31 +++++++++++++++++++++++++++++++
 Makefile           |  2 +-
 lib/arm/asm/psci.h |  3 ++-
 lib/arm/io.c       | 34 ++++++++++++++++++++++------------
 lib/arm/psci.c     |  8 +++++++-
 .gitignore         |  1 +
 6 files changed, 64 insertions(+), 15 deletions(-)
```
#### [PATCH v3 0/2] vsock/virtio: fix issues on device hot-unplug
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c

These patches try to handle the hot-unplug of vsock virtio transport device in
a proper way.

Maybe move the vsock_core_init()/vsock_core_exit() functions in the module_init
and module_exit of vsock_virtio_transport module can't be the best way, but the
architecture of vsock_core forces us to this approach for now.

The vsock_core proto_ops expect a valid pointer to the transport device, so we
can't call vsock_core_exit() until there are open sockets.

v2 -> v3:
 - Rebased on master

v1 -> v2:
 - Fixed commit message of patch 1.
 - Added Reviewed-by, Acked-by tags by Stefan

Stefano Garzarella (2):
  vsock/virtio: fix kernel panic after device hot-unplug
  vsock/virtio: reset connected sockets on device removal

 net/vmw_vsock/virtio_transport.c | 29 +++++++++++++++++++++--------
 1 file changed, 21 insertions(+), 8 deletions(-)
```
#### [PATCH v2 0/4] Various convenience fixes
##### From: Andre Przywara <andre.przywara@arm.com>

```c

As I found myself using kvmtool more often in the last weeks, I got more
and more annoyed by some smaller "ticks" that kvmtool shows.

So this is an attempt to post various smaller fixes I gathered up over
the years, but never found worth enough to send out.
Version 2 drops the two patches that have been merged already, and
amends the remaining ones.

The patches address:
- add /chosen/stdout-path node in .dtb
- honour make -s switch
- remove pointless kvmtool version number
- introduce autodetection of supported GIC type

Changelog v1..v2:
- stdout-path: Let hw/serial.c set the node path and use an alias
- make -s: adapt to newest version from the Linux kernel
- kvmtool "version" number: unchanged, but verified to be compatible
  with the Debian package
- GIC autodetection: ignore --force-pci, always try to have an MSI
  controller

Please have a look!

Cheers,
Andre.

Andre Przywara (4):
  arm: fdt: add stdout-path to /chosen node
  Makefile: support -s switch
  Makefile: Remove echoing of kvmtools version file
  arm: Auto-detect guest GIC type

 Makefile                     |  6 +++++-
 arm/fdt.c                    | 10 ++++++++++
 arm/gic.c                    | 25 +++++++++++++++++++++++++
 arm/include/arm-common/gic.h |  1 +
 hw/serial.c                  |  9 +++++++++
 include/kvm/fdt.h            |  2 ++
 util/KVMTOOLS-VERSION-GEN    |  1 -
 7 files changed, 52 insertions(+), 2 deletions(-)
```
#### [PATCH V2 00/10] X86/KVM/Hyper-V: Add HV ept tlb range list flush
##### From: lantianyu1986@gmail.com
X-Google-Original-From: Tianyu.Lan@microsoft.com
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

```c

From: Lan Tianyu <Tianyu.Lan@microsoft.com>

This patchset is to introduce hv ept tlb range list flush function
support in the KVM MMU component. Flushing ept tlbs of several address
range can be done via single hypercall and new list flush function is
used in the kvm_mmu_commit_zap_page() and FNAME(sync_page). This patchset
also adds more hv ept tlb range flush support in more KVM MMU function.

Change since v1:
       1) Make flush list as a hlist instead of list in order to 
       keep struct kvm_mmu_page size.
       2) Add last_level flag in the struct kvm_mmu_page instead
       of spte pointer
       3) Move tlb flush from kvm_mmu_notifier_clear_flush_young() to kvm_age_hva()
       4) Use range flush in the kvm_vm_ioctl_get/clear_dirty_log()

Lan Tianyu (10):
  X86/Hyper-V: Add parameter offset for
    hyperv_fill_flush_guest_mapping_list()
  KVM/VMX: Fill range list in kvm_fill_hv_flush_list_func()
  KVM/MMU: Add last_level in the struct mmu_spte_page
  KVM/MMU: Introduce tlb flush with range list
  KVM/MMU: Flush tlb with range list in sync_page()
  KVM/MMU: Flush tlb directly in the kvm_mmu_slot_gfn_write_protect()
  KVM: Add kvm_get_memslot() to get memslot via slot id
  KVM: Use tlb range flush in the kvm_vm_ioctl_get/clear_dirty_log()
  KVM: Add flush parameter for kvm_age_hva()
  KVM/MMU: Use tlb range flush  in the kvm_age_hva()

 arch/arm/include/asm/kvm_host.h     |  3 ++-
 arch/arm64/include/asm/kvm_host.h   |  3 ++-
 arch/mips/include/asm/kvm_host.h    |  3 ++-
 arch/mips/kvm/mmu.c                 | 11 ++++++--
 arch/powerpc/include/asm/kvm_host.h |  3 ++-
 arch/powerpc/kvm/book3s.c           | 10 ++++++--
 arch/powerpc/kvm/e500_mmu_host.c    |  3 ++-
 arch/x86/hyperv/nested.c            |  4 +--
 arch/x86/include/asm/kvm_host.h     | 11 +++++++-
 arch/x86/include/asm/mshyperv.h     |  2 +-
 arch/x86/kvm/mmu.c                  | 51 +++++++++++++++++++++++++++++--------
 arch/x86/kvm/mmu.h                  |  7 +++++
 arch/x86/kvm/paging_tmpl.h          | 15 ++++++++---
 arch/x86/kvm/vmx/vmx.c              | 18 +++++++++++--
 arch/x86/kvm/x86.c                  | 16 +++++++++---
 include/linux/kvm_host.h            |  1 +
 virt/kvm/arm/mmu.c                  | 13 ++++++++--
 virt/kvm/kvm_main.c                 | 51 +++++++++++++++----------------------
 18 files changed, 160 insertions(+), 65 deletions(-)
```
#### [PATCH 0/2] KVM: SVM: move the SEV command handling into a separate
##### From: "Singh, Brijesh" <brijesh.singh@amd.com>

```c

svm.c is pretty huge, before we add more SEV specific commands (e.g SEV-ES,
SEV-Migration etc) lets move the SEV command handling into a separate file.
There is no logical changes in this series.

The patch is based on motivation from this thread:
https://marc.info/?l=linux-kernel&m=153910240507399&w=2

Cc: Borislav Petkov <bp@alien8.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Tom Lendacky <Thomas.Lendacky@amd.com>

Brijesh Singh (2):
  KVM: SVM: move common struct definitions to header file
  KVM: SVM: move the SEV specific function in a separate file

 arch/x86/include/asm/svm.h |  155 +++++
 arch/x86/kvm/Makefile      |    2 +
 arch/x86/kvm/sev.c         | 1076 +++++++++++++++++++++++++++++++
 arch/x86/kvm/sev.h         |   40 ++
 arch/x86/kvm/svm.c         | 1234 +-----------------------------------
 5 files changed, 1296 insertions(+), 1211 deletions(-)
 create mode 100644 arch/x86/kvm/sev.c
 create mode 100644 arch/x86/kvm/sev.h
```
