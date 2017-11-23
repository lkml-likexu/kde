

#### [PATCH 0/2] vfio: add vgpu edid support
##### From: Gerd Hoffmann <kraxel@redhat.com>

```c

Update vfio api, adapt mbochs sample driver.

Gerd Hoffmann (2):
  vfio: add edid api for display (vgpu) devices.
  vfio: add edid support to mbochs sample driver

 include/uapi/linux/vfio.h  | 38 ++++++++++++++++++++++++++++++++
 samples/vfio-mdev/mbochs.c | 54 ++++++++++++++++++++++++++++++++++++++++++++--
 2 files changed, 90 insertions(+), 2 deletions(-)
```
#### [PATCH 0/2]: KVM: nVMX: Fix bugs in MPX VMX controls emulation
##### From: Liran Alon <liran.alon@oracle.com>

```c

Hi,

This series aims to fix 2 issues in MPX VMX controls emulation.

The 1st patch makes sure that we don't expose MPX VMX controls to guest
in case vCPU doesn't support MPX (It is not exposed via CPUID).

The 2nd patch fixes an issue in emulation of VM_ENTRY_LOAD_BNDCFGS.

Regards,
-Liran
```
#### [PATCH v2 0/2] KVM: nVMX: Fix bugs in MPX VMX controls emulation
##### From: Liran Alon <liran.alon@oracle.com>

```c

Hi,

This series aims to fix 2 issues in MPX VMX controls emulation.

The 1st patch makes sure that we don't expose MPX VMX controls to guest
in case vCPU doesn't support MPX (It is not exposed via CPUID).

The 2nd patch fixes an issue in emulation of VM_ENTRY_LOAD_BNDCFGS.

Regards,
-Liran

v1->v2 Changes:
Fixed enter_vmx_non_root_mode() change to not vmcs_read(GUEST_BNDCFGS)
in case !vmx_mpx_supported() (Thanks to Sean J Christopherson)
```
#### [PATCH v5 00/12] KVM: nVMX: Enlightened VMCS for Hyper-V on KVM
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v4:
- Rebase.
- Adjust nested state migration support after additional testing.
- Enhance self-test.
- Drop "KVM: selftests: compile against local uapi headers" patch,
  add "tools/headers: update kvm.h" instead.

Original description:

This is an initial implementation of Enlightened VMCS for nested Hyper-V on
KVM. Using it helps to spare 1500 cpu cycles for nested vmexit (tight cpuid
loop in WS2016 with Hyper-V role on KVM: 15200 cycles -> 13700 cycles).

Ladi Prosek (1):
  KVM: hyperv: define VP assist page helpers

Vitaly Kuznetsov (11):
  KVM: VMX: refactor evmcs_sanitize_exec_ctrls()
  KVM: nVMX: add KVM_CAP_HYPERV_ENLIGHTENED_VMCS capability
  KVM: nVMX: add enlightened VMCS state
  KVM: nVMX: implement enlightened VMPTRLD and VMCLEAR
  KVM: nVMX: optimize prepare_vmcs02{,_full} for Enlightened VMCS case
  x86/kvm/hyperv: don't clear VP assist pages on init
  x86/kvm/lapic: preserve gfn_to_hva_cache len on cache reinit
  x86/kvm/nVMX: allow bare VMXON state migration
  x86/kvm/nVMX: nested state migration for Enlightened VMCS
  tools/headers: update kvm.h
  KVM: selftests: add Enlightened VMCS test

 arch/x86/include/asm/kvm_host.h             |    3 +
 arch/x86/include/uapi/asm/kvm.h             |    1 +
 arch/x86/kvm/hyperv.c                       |   31 +-
 arch/x86/kvm/hyperv.h                       |    4 +
 arch/x86/kvm/lapic.c                        |   14 +-
 arch/x86/kvm/lapic.h                        |    2 +-
 arch/x86/kvm/svm.c                          |    9 +
 arch/x86/kvm/vmx.c                          |  906 ++++++++++++++++++----
 arch/x86/kvm/x86.c                          |   23 +-
 include/uapi/linux/kvm.h                    |    1 +
 tools/include/uapi/linux/kvm.h              |    7 +
 tools/testing/selftests/kvm/Makefile        |    1 +
 tools/testing/selftests/kvm/evmcs_test.c    |  160 ++++
 tools/testing/selftests/kvm/include/evmcs.h | 1099 +++++++++++++++++++++++++++
 tools/testing/selftests/kvm/include/vmx.h   |   28 +
 tools/testing/selftests/kvm/lib/vmx.c       |   48 +-
 16 files changed, 2156 insertions(+), 181 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/evmcs_test.c
 create mode 100644 tools/testing/selftests/kvm/include/evmcs.h
```
#### [PATCH V7 0/2] KSM replace hash algo with xxhash
##### From: Timofey Titovets <timofey.titovets@synesis.ru>
From: Timofey Titovets <nefelim4ag@gmail.com>

```c

From: Timofey Titovets <nefelim4ag@gmail.com>

Currently used jhash are slow enough and replace it allow as to make KSM
less cpu hungry.

About speed (in kernel):
        ksm: crc32c   hash() 12081 MB/s
        ksm: xxh64    hash()  8770 MB/s
        ksm: xxh32    hash()  4529 MB/s
        ksm: jhash2   hash()  1569 MB/s

By sioh Lee tests (copy from other mail):
Test platform: openstack cloud platform (NEWTON version)
Experiment node: openstack based cloud compute node (CPU: xeon E5-2620 v3, memory 64gb)
VM: (2 VCPU, RAM 4GB, DISK 20GB) * 4
Linux kernel: 4.14 (latest version)
KSM setup - sleep_millisecs: 200ms, pages_to_scan: 200

Experiment process
Firstly, we turn off KSM and launch 4 VMs.
Then we turn on the KSM and measure the checksum computation time until full_scans become two.

The experimental results (the experimental value is the average of the measured values)
crc32c_intel: 1084.10ns
crc32c (no hardware acceleration): 7012.51ns
xxhash32: 2227.75ns
xxhash64: 1413.16ns
jhash2: 5128.30ns

In summary, the result shows that crc32c_intel has advantages over all 
of the hash function used in the experiment. (decreased by 84.54% compared to crc32c,
78.86% compared to jhash2, 51.33% xxhash32, 23.28% compared to xxhash64)
the results are similar to those of Timofey.

But,
use only xxhash for now, because for using crc32c,
cryptoapi must be initialized first - that require some
tricky solution to work good in all situations.

So:
  - Fisrt patch implement compile time pickup of fastest implementation of xxhash
    for target platform.
  - Second replace jhash2 with xxhash
  
Thanks.

CC: Andrea Arcangeli <aarcange@redhat.com>
CC: linux-mm@kvack.org
CC: kvm@vger.kernel.org
CC: leesioh <solee@os.korea.ac.kr>

Timofey Titovets (2):
  xxHash: create arch dependent 32/64-bit xxhash()
  ksm: replace jhash2 with xxhash

 include/linux/xxhash.h | 23 +++++++++++++
 mm/Kconfig             |  2 ++
 mm/ksm.c               | 93 +++++++++++++++++++++++++++++++++++++++++++++++---
 3 files changed, 114 insertions(+), 4 deletions(-)
```
#### [PATCH V8 0/2] Currently used jhash are slow enough and replace it
##### From: Timofey Titovets <timofey.titovets@synesis.ru>

```c

About speed (in kernel):
        ksm: crc32c   hash() 12081 MB/s
        ksm: xxh64    hash()  8770 MB/s
        ksm: xxh32    hash()  4529 MB/s
        ksm: jhash2   hash()  1569 MB/s

By sioh Lee tests (copy from other mail):
Test platform: openstack cloud platform (NEWTON version)
Experiment node: openstack based cloud compute node (CPU: xeon E5-2620 v3, memory 64gb)
VM: (2 VCPU, RAM 4GB, DISK 20GB) * 4
Linux kernel: 4.14 (latest version)
KSM setup - sleep_millisecs: 200ms, pages_to_scan: 200

Experiment process
Firstly, we turn off KSM and launch 4 VMs.
Then we turn on the KSM and measure the checksum computation time until full_scans become two.

The experimental results (the experimental value is the average of the measured values)
crc32c_intel: 1084.10ns
crc32c (no hardware acceleration): 7012.51ns
xxhash32: 2227.75ns
xxhash64: 1413.16ns
jhash2: 5128.30ns

In summary, the result shows that crc32c_intel has advantages over all 
of the hash function used in the experiment. (decreased by 84.54% compared to crc32c,
78.86% compared to jhash2, 51.33% xxhash32, 23.28% compared to xxhash64)
the results are similar to those of Timofey.

But,
use only xxhash for now, because for using crc32c,
cryptoapi must be initialized first - that require some
tricky solution to work good in all situations.

So:
  - Fisrt patch implement compile time pickup of fastest implementation of xxhash
    for target platform.
  - Second replace jhash2 with xxhash

Thanks.

CC: Andrea Arcangeli <aarcange@redhat.com>
CC: linux-mm@kvack.org
CC: kvm@vger.kernel.org
CC: leesioh <solee@os.korea.ac.kr>

Timofey Titovets (2):
  xxHash: create arch dependent 32/64-bit xxhash()
  ksm: replace jhash2 with xxhash

 include/linux/xxhash.h | 23 +++++++++++++++++++++++
 mm/Kconfig             |  1 +
 mm/ksm.c               |  4 ++--
 3 files changed, 26 insertions(+), 2 deletions(-)
```
#### [PATCH v8 0/2] x86: Fix SEV guest regression
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

NOTE: Since there was some design changes based on Thomas G suggestion hence I
dropped Acked and R-b from Tom, Paolo and Boris.

Changes since v7:
 - As per Thomas Gleixner suggestion move the decrypted data in .bss..decrypted section
 - remove the second auxiliary array from SEV case
 - allocate memory for pvclock data pointer early and map with C=0 for SEV case

Changes since v6:
 - improve commit messages
 - rename free_decrypted_mem -> mem_encrypt_free_decrypted_mem

Changes since v5:
 - rename hvclock_boot_dec -> hvclock_boot_aux.
 - rename section from .data..decrypted_aux -> .data..decrypted.aux.
 - use NR_CPUS instead of random number elements in hv_clock_aux variable.

Changes since v4:
 - define few static pages in .data..decrypted which can be used
   for cpus > HVC_BOOT_ARRAY_SIZE when SEV is active.

Changes since v3:
 - commit message improvements (based on Sean's feedback)

Changes since v2:
 - commit message and code comment improvements (based on Boris feedback)
 - move sme_populate_pgd fixes in new patch.
 - drop stable Cc - will submit to stable after patch is upstreamed.

Changes since v1:
 - move the logic to re-arrange mapping in new patch
 - move the definition of __start_data_* in mem_encrypt.h
 - map the workarea buffer as encrypted when SEV is enabled
 - enhance the sme_populate_pgd to update the pte/pmd flags when mapping exist

Brijesh Singh (2):
  x86/mm: add .bss..decrypted section to hold shared variables
  x86/kvm: use __bss_decrypted attribute in shared variables

 arch/x86/include/asm/mem_encrypt.h |  7 +++++++
 arch/x86/kernel/head64.c           | 16 +++++++++++++++
 arch/x86/kernel/kvmclock.c         | 42 +++++++++++++++++++++++++++++++++++---
 arch/x86/kernel/vmlinux.lds.S      | 19 +++++++++++++++++
 arch/x86/mm/init.c                 |  4 ++++
 arch/x86/mm/mem_encrypt.c          | 10 +++++++++
 6 files changed, 95 insertions(+), 3 deletions(-)
```
