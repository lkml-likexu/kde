

#### [PATCH v37 0/3] Virtio-balloon: support free page reporting
##### From: Wei Wang <wei.w.wang@intel.com>

```c

The new feature, VIRTIO_BALLOON_F_FREE_PAGE_HINT, implemented by this
series enables the virtio-balloon driver to report hints of guest free
pages to host. It can be used to accelerate virtual machine (VM) live
migration. Here is an introduction of this usage:

Live migration needs to transfer the VM's memory from the source machine
to the destination round by round. For the 1st round, all the VM's memory
is transferred. From the 2nd round, only the pieces of memory that were
written by the guest (after the 1st round) are transferred. One method
that is popularly used by the hypervisor to track which part of memory is
written is to have the hypervisor write-protect all the guest memory.

This feature enables the optimization by skipping the transfer of guest
free pages during VM live migration. It is not concerned that the memory
pages are used after they are given to the hypervisor as a hint of the
free pages, because they will be tracked by the hypervisor and transferred
in the subsequent round if they are used and written.

* Tests
1 Test Environment
    Host: Intel(R) Xeon(R) CPU E5-2699 v4 @ 2.20GHz
    Migration setup: migrate_set_speed 100G, migrate_set_downtime 400ms

2 Test Results (results are averaged over several repeated runs)
    2.1 Guest setup: 8G RAM, 4 vCPU
        2.1.1 Idle guest live migration time
            Optimization v.s. Legacy = 620ms vs 2970ms
            --> ~79% reduction
        2.1.2 Guest live migration with Linux compilation workload
          (i.e. make bzImage -j4) running
          1) Live Migration Time:
             Optimization v.s. Legacy = 2273ms v.s. 4502ms
             --> ~50% reduction
          2) Linux Compilation Time:
             Optimization v.s. Legacy = 8min42s v.s. 8min43s
             --> no obvious difference

    2.2 Guest setup: 128G RAM, 4 vCPU
        2.2.1 Idle guest live migration time
            Optimization v.s. Legacy = 5294ms vs 41651ms
            --> ~87% reduction
        2.2.2 Guest live migration with Linux compilation workload
          1) Live Migration Time:
            Optimization v.s. Legacy = 8816ms v.s. 54201ms
            --> 84% reduction
          2) Linux Compilation Time:
             Optimization v.s. Legacy = 8min30s v.s. 8min36s
             --> no obvious difference

ChangeLog:
v36->v37:
    - free the reported pages to mm when receives a DONE cmd from host.
      Please see patch 1's commit log for reasons. Please see patch 1's
      commit for detailed explanations.

For ChangeLogs from v22 to v36, please reference
https://lkml.org/lkml/2018/7/20/199

For ChangeLogs before v21, please reference
https://lwn.net/Articles/743660/

Wei Wang (3):
  virtio-balloon: VIRTIO_BALLOON_F_FREE_PAGE_HINT
  mm/page_poison: expose page_poisoning_enabled to kernel modules
  virtio-balloon: VIRTIO_BALLOON_F_PAGE_POISON

 drivers/virtio/virtio_balloon.c     | 374 ++++++++++++++++++++++++++++++++----
 include/uapi/linux/virtio_balloon.h |   8 +
 mm/page_poison.c                    |   6 +
 3 files changed, 355 insertions(+), 33 deletions(-)
```
#### [PATCH 0/2] x86: Fix SEV guest regression
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c

The following commit

"
x86/kvmclock: Remove memblock dependency

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=368a540e0232ad446931f5a4e8a5e06f69f21343
"

introduced SEV guest regression.

The guest physical address holding the wall_clock and hv_clock_boot
are shared with the hypervisor must be mapped with C=0 when SEV
is active. To clear the C-bit we use  kernel_physical_mapping_init() to
split the large pages. The above commit moved the kvmclock initialization
very early and kernel_physical_mapping_init() fails to allocate memory
while spliting the large page.

To solve it, we add a special .data..decrypted section, this section can be
used to hold the shared variables. Early boot code maps this section with
C=0. The section is pmd aligned and sized to avoid the need to split the pages.
Caller can use __decrypted attribute to add the variables in .data..decrypted
section. 

Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>

Brijesh Singh (2):
  x86/mm: add .data..decrypted section to hold shared variables
  x86/kvm: use __decrypted attribute when declaring shared variables

 arch/x86/include/asm/mem_encrypt.h |   4 +
 arch/x86/kernel/head64.c           |  12 ++
 arch/x86/kernel/kvmclock.c         |  26 ++++-
 arch/x86/kernel/vmlinux.lds.S      |  18 +++
 arch/x86/mm/mem_encrypt_identity.c | 220 +++++++++++++++++++++++++++----------
 5 files changed, 218 insertions(+), 62 deletions(-)
```
#### [PATCH v5 0/5] KVM: x86: hyperv: PV IPI support for Windows guests
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v4:
- Rebase to the current kvm/next (KVM_CAP_HYPERV_SEND_IPI is now 159)
- Use 64 instead of 'BITS_PER_LONG' [Roman Kagan]
- Continue in case wrong VP ids or disabled APICs instead of bailing
  [Roman Kagan]

Using hypercall for sending IPIs is faster because this allows to specify
any number of vCPUs (even > 64 with sparse CPU set), the whole procedure
will take only one VMEXIT.

Same as PV TLB flush, this allows Windows guests having > 64 vCPUs to boot
on KVM when Hyper-V extensions are enabled.

Vitaly Kuznetsov (5):
  KVM: x86: hyperv: enforce vp_index < KVM_MAX_VCPUS
  KVM: x86: hyperv: optimize 'all cpus' case in kvm_hv_flush_tlb()
  KVM: x86: hyperv: use get_vcpu_by_vpidx() in kvm_hv_flush_tlb()
  x86/hyper-v: rename ipi_arg_{ex,non_ex} structures
  KVM: x86: hyperv: implement PV IPI send hypercalls

 Documentation/virtual/kvm/api.txt  |   7 ++
 arch/x86/hyperv/hv_apic.c          |   8 +-
 arch/x86/include/asm/hyperv-tlfs.h |  16 +--
 arch/x86/kvm/hyperv.c              | 201 +++++++++++++++++++++++++++----------
 arch/x86/kvm/trace.h               |  42 ++++++++
 arch/x86/kvm/x86.c                 |   1 +
 include/uapi/linux/kvm.h           |   1 +
 virt/kvm/kvm_main.c                |   6 +-
 8 files changed, 214 insertions(+), 68 deletions(-)
```
#### [PATCH v13 00/13] Intel SGX1 support
##### From: Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>

```c

Intel(R) SGX is a set of CPU instructions that can be used by applications
to set aside private regions of code and data. The code outside the enclave
is disallowed to access the memory inside the enclave by the CPU access
control.  In a way you can think that SGX provides inverted sandbox. It
protects the application from a malicious host.

There is a new hardware unit in the processor called Memory Encryption
Engine (MEE) starting from the Skylake microacrhitecture. BIOS can define
one or many MEE regions that can hold enclave data by configuring them with
PRMRR registers.

The MEE automatically encrypts the data leaving the processor package to
the MEE regions. The data is encrypted using a random key whose life-time
is exactly one power cycle.

The current implementation requires that the firmware sets
IA32_SGXLEPUBKEYHASH* MSRs as writable so that ultimately the kernel can
decide what enclaves it wants run. The implementation does not create
any bottlenecks to support read-only MSRs later on.

You can tell if your CPU supports SGX by looking into /proc/cpuinfo:

	cat /proc/cpuinfo  | grep sgx

v13:
* Always use SGX_CPUID constant instead of a hardcoded value.
* Simplified and documented the macros and functions for ENCLS leaves.
* Enable sgx_free_page() to free active enclave pages on demand
  in order to allow sgx_invalidate() to delete enclave pages.
  It no longer performs EREMOVE if a page is in the process of
  being reclaimed.
* Use PM notifier per enclave so that we don't have to traverse
  the global list of active EPC pages to find enclaves.
* Removed unused SGX_LE_ROLLBACK constant from uapi/asm/sgx.h
* Always use ioremap() to map EPC banks as we only support 64-bit kernel.
* Invalidate IA32_SGXLEPUBKEYHASH cache used by sgx_einit() when going
  to sleep.

v12:
* Split to more narrow scoped commits in order to ease the review process and
  use co-developed-by tag for co-authors of commits instead of listing them in
  the source files.
* Removed cruft EXPORT_SYMBOL() declarations and converted to static variables.
* Removed in-kernel LE i.e. this version of the SGX software stack only
  supports unlocked IA32_SGXLEPUBKEYHASHx MSRs.
* Refined documentation on launching enclaves, swapping and enclave
  construction.
* Refined sgx_arch.h to include alignment information for every struct that
  requires it and removed structs that are not needed without an LE.
* Got rid of SGX_CPUID.
* SGX detection now prints log messages about firmware configuration issues.

v11:
* Polished ENCLS wrappers with refined exception handling.
* ksgxswapd was not stopped (regression in v5) in
  sgx_page_cache_teardown(), which causes a leaked kthread after driver
  deinitialization.
* Shutdown sgx_le_proxy when going to suspend because its EPC pages will be
  invalidated when resuming, which will cause it not function properly
  anymore.
* Set EINITTOKEN.VALID to zero for a token that is passed when
  SGXLEPUBKEYHASH matches MRSIGNER as alloc_page() does not give a zero
  page.
* Fixed the check in sgx_edbgrd() for a TCS page. Allowed to read offsets
  around the flags field, which causes a #GP. Only flags read is readable.
* On read access memcpy() call inside sgx_vma_access() had src and dest
  parameters in wrong order.
* The build issue with CONFIG_KASAN is now fixed. Added undefined symbols
  to LE even if “KASAN_SANITIZE := false” was set in the makefile. 
* Fixed a regression in the #PF handler. If a page has
  SGX_ENCL_PAGE_RESERVED flag the #PF handler should unconditionally fail.
  It did not, which caused weird races when trying to change other parts of
  swapping code.
* EPC management has been refactored to a flat LRU cache and moved to
  arch/x86. The swapper thread reads a cluster of EPC pages and swaps all
  of them. It can now swap from multiple enclaves in the same round.
* For the sake of consistency with SGX_IOC_ENCLAVE_ADD_PAGE, return -EINVAL
  when an enclave is already initialized or dead instead of zero.

v10:
* Cleaned up anon inode based IPC between the ring-0 and ring-3 parts
  of the driver.
* Unset the reserved flag from an enclave page if EDBGRD/WR fails
  (regression in v6).
* Close the anon inode when LE is stopped (regression in v9).
* Update the documentation with a more detailed description of SGX.

v9:
* Replaced kernel-LE IPC based on pipes with an anonymous inode.
  The driver does not require anymore new exports.

v8:
* Check that public key MSRs match the LE public key hash in the
  driver initialization when the MSRs are read-only.
* Fix the race in VA slot allocation by checking the fullness
  immediately after succeesful allocation.
* Fix the race in hash mrsigner calculation between the launch
  enclave and user enclaves by having a separate lock for hash
  calculation.

v7:
* Fixed offset calculation in sgx_edbgr/wr(). Address was masked with PAGE_MASK
  when it should have been masked with ~PAGE_MASK.
* Fixed a memory leak in sgx_ioc_enclave_create().
* Simplified swapping code by using a pointer array for a cluster
  instead of a linked list.
* Squeezed struct sgx_encl_page to 32 bytes.
* Fixed deferencing of an RSA key on OpenSSL 1.1.0.
* Modified TC's CMAC to use kernel AES-NI. Restructured the code
  a bit in order to better align with kernel conventions.

v6:
* Fixed semaphore underrun when accessing /dev/sgx from the launch enclave.
* In sgx_encl_create() s/IS_ERR(secs)/IS_ERR(encl)/.
* Removed virtualization chapter from the documentation.
* Changed the default filename for the signing key as signing_key.pem.
* Reworked EPC management in a way that instead of a linked list of
  struct sgx_epc_page instances there is an array of integers that
  encodes address and bank of an EPC page (the same data as 'pa' field
  earlier). The locking has been moved to the EPC bank level instead
  of a global lock.
* Relaxed locking requirements for EPC management. EPC pages can be
  released back to the EPC bank concurrently.
* Cleaned up ptrace() code.
* Refined commit messages for new architectural constants.
* Sorted includes in every source file.
* Sorted local variable declarations according to the line length in
  every function.
* Style fixes based on Darren's comments to sgx_le.c.

v5:
* Described IPC between the Launch Enclave and kernel in the commit messages.
* Fixed all relevant checkpatch.pl issues that I have forgot fix in earlier
  versions except those that exist in the imported TinyCrypt code.
* Fixed spelling mistakes in the documentation.
* Forgot to check the return value of sgx_drv_subsys_init().
* Encapsulated properly page cache init and teardown.
* Collect epc pages to a temp list in sgx_add_epc_bank
* Removed SGX_ENCLAVE_INIT_ARCH constant.

v4:
* Tied life-cycle of the sgx_le_proxy process to /dev/sgx.
* Removed __exit annotation from sgx_drv_subsys_exit().
* Fixed a leak of a backing page in sgx_process_add_page_req() in the
  case when vm_insert_pfn() fails.
* Removed unused symbol exports for sgx_page_cache.c.
* Updated sgx_alloc_page() to require encl parameter and documented the
  behavior (Sean Christopherson).
* Refactored a more lean API for sgx_encl_find() and documented the behavior.
* Moved #PF handler to sgx_fault.c.
* Replaced subsys_system_register() with plain bus_register().
* Retry EINIT 2nd time only if MSRs are not locked.

v3:
* Check that FEATURE_CONTROL_LOCKED and FEATURE_CONTROL_SGX_ENABLE are set.
* Return -ERESTARTSYS in __sgx_encl_add_page() when sgx_alloc_page() fails.
* Use unused bits in epc_page->pa to store the bank number.
* Removed #ifdef for WQ_NONREENTRANT.
* If mmu_notifier_register() fails with -EINTR, return -ERESTARTSYS.
* Added --remove-section=.got.plt to objcopy flags in order to prevent a
  dummy .got.plt, which will cause an inconsistent size for the LE.
* Documented sgx_encl_* functions.
* Added remark about AES implementation used inside the LE.
* Removed redundant sgx_sys_exit() from le/main.c.
* Fixed struct sgx_secinfo alignment from 128 to 64 bytes.
* Validate miscselect in sgx_encl_create().
* Fixed SSA frame size calculation to take the misc region into account.
* Implemented consistent exception handling to __encls() and __encls_ret().
* Implemented a proper device model in order to allow sysfs attributes
  and in-kernel API.
* Cleaned up various "find enclave" implementations to the unified
  sgx_encl_find().
* Validate that vm_pgoff is zero.
* Discard backing pages with shmem_truncate_range() after EADD.
* Added missing EEXTEND operations to LE signing and launch.
* Fixed SSA size for GPRS region from 168 to 184 bytes.
* Fixed the checks for TCS flags. Now DBGOPTIN is allowed.
* Check that TCS addresses are in ELRANGE and not just page aligned.
* Require kernel to be compiled with X64_64 and CPU_SUP_INTEL.
* Fixed an incorrect value for SGX_ATTR_DEBUG from 0x01 to 0x02.

v2:
* get_rand_uint32() changed the value of the pointer instead of value
  where it is pointing at.
* Launch enclave incorrectly used sigstruct attributes-field instead of
  enclave attributes-field.
* Removed unused struct sgx_add_page_req from sgx_ioctl.c
* Removed unused sgx_has_sgx2.
* Updated arch/x86/include/asm/sgx.h so that it provides stub
  implementations when sgx in not enabled.
* Removed cruft rdmsr-calls from sgx_set_pubkeyhash_msrs().
* return -ENOMEM in sgx_alloc_page() when VA pages consume too much space
* removed unused global sgx_nr_pids
* moved sgx_encl_release to sgx_encl.c
* return -ERESTARTSYS instead of -EINTR in sgx_encl_init()

Jarkko Sakkinen (8):
  x86/sgx: Update MAINTAINERS
  x86/sgx: Architectural structures
  x86/sgx: Add data structures for tracking the EPC pages
  x86/sgx: Add wrappers for ENCLS leaf functions
  x86/sgx: Enclave Page Cache (EPC) memory manager
  platform/x86: Intel SGX driver
  platform/x86: ptrace() support for the SGX driver
  x86/sgx: Driver documentation

Kai Huang (1):
  x86/cpufeature: Add SGX and SGX_LC CPU features

Sean Christopherson (4):
  x86/cpufeatures: Add Intel-defined SGX leaf CPUID_12_EAX
  x86/msr: Add SGX definitions to msr-index.h
  x86/sgx: Detect Intel SGX
  x86/sgx: Add sgx_einit() for initializing enclaves

 Documentation/index.rst                       |    1 +
 Documentation/x86/intel_sgx.rst               |  185 +++
 MAINTAINERS                                   |    7 +
 arch/x86/Kconfig                              |   19 +
 arch/x86/include/asm/cpufeature.h             |    7 +-
 arch/x86/include/asm/cpufeatures.h            |   10 +-
 arch/x86/include/asm/disabled-features.h      |    3 +-
 arch/x86/include/asm/msr-index.h              |    8 +
 arch/x86/include/asm/required-features.h      |    3 +-
 arch/x86/include/asm/sgx.h                    |  359 ++++++
 arch/x86/include/asm/sgx_arch.h               |  379 ++++++
 arch/x86/include/asm/sgx_pr.h                 |   13 +
 arch/x86/include/uapi/asm/sgx.h               |  112 ++
 arch/x86/include/uapi/asm/sgx_errno.h         |   91 ++
 arch/x86/kernel/cpu/Makefile                  |    1 +
 arch/x86/kernel/cpu/common.c                  |    7 +
 arch/x86/kernel/cpu/intel_sgx.c               |  551 +++++++++
 arch/x86/kvm/cpuid.h                          |    1 +
 drivers/platform/x86/Kconfig                  |    2 +
 drivers/platform/x86/Makefile                 |    1 +
 drivers/platform/x86/intel_sgx/Kconfig        |   22 +
 drivers/platform/x86/intel_sgx/Makefile       |   13 +
 drivers/platform/x86/intel_sgx/sgx.h          |  211 ++++
 drivers/platform/x86/intel_sgx/sgx_encl.c     | 1016 +++++++++++++++++
 .../platform/x86/intel_sgx/sgx_encl_page.c    |  288 +++++
 drivers/platform/x86/intel_sgx/sgx_fault.c    |  157 +++
 drivers/platform/x86/intel_sgx/sgx_ioctl.c    |  234 ++++
 drivers/platform/x86/intel_sgx/sgx_main.c     |  257 +++++
 drivers/platform/x86/intel_sgx/sgx_vma.c      |  167 +++
 29 files changed, 4120 insertions(+), 5 deletions(-)
 create mode 100644 Documentation/x86/intel_sgx.rst
 create mode 100644 arch/x86/include/asm/sgx.h
 create mode 100644 arch/x86/include/asm/sgx_arch.h
 create mode 100644 arch/x86/include/asm/sgx_pr.h
 create mode 100644 arch/x86/include/uapi/asm/sgx.h
 create mode 100644 arch/x86/include/uapi/asm/sgx_errno.h
 create mode 100644 arch/x86/kernel/cpu/intel_sgx.c
 create mode 100644 drivers/platform/x86/intel_sgx/Kconfig
 create mode 100644 drivers/platform/x86/intel_sgx/Makefile
 create mode 100644 drivers/platform/x86/intel_sgx/sgx.h
 create mode 100644 drivers/platform/x86/intel_sgx/sgx_encl.c
 create mode 100644 drivers/platform/x86/intel_sgx/sgx_encl_page.c
 create mode 100644 drivers/platform/x86/intel_sgx/sgx_fault.c
 create mode 100644 drivers/platform/x86/intel_sgx/sgx_ioctl.c
 create mode 100644 drivers/platform/x86/intel_sgx/sgx_main.c
 create mode 100644 drivers/platform/x86/intel_sgx/sgx_vma.c
```
#### [PATCH 0/3] KVM: VMX: handle preemption timer value of zero
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

A VMX preemption timer value of '0' at the time of VMEnter is
architecturally guaranteed to cause a VMExit prior to the CPU
executing any instructions in the guest.  KVM serendipitously
emulates this behavior when running as L0, but doesn't ensure
correct emulation when running at L1 or higher.  Explicitly
emulate the architectural behavior of a timer value of '0'.

Sean Christopherson (3):
  KVM: VMX: immediately mark preemption timer expired only for zero
    value
  KVM: VMX: modify preemption timer bit only when arming timer
  KVM: VMX: use preemption timer to force immediate VMExit

 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/vmx.c              | 77 ++++++++++++++++++++-------------
 arch/x86/kvm/x86.c              |  5 ++-
 3 files changed, 51 insertions(+), 32 deletions(-)
```
