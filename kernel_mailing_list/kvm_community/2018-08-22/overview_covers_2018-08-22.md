

#### [PATCH V4 0/4] Fix kvm misconceives NVDIMM pages as reserved mmio
##### From: Zhang Yi <yi.z.zhang@linux.intel.com>

```c

For device specific memory space, when we move these area of pfn to
memory zone, we will set the page reserved flag at that time, some of
these reserved for device mmio, and some of these are not, such as
NVDIMM pmem.

Now, we map these dev_dax or fs_dax pages to kvm for DIMM/NVDIMM
backend, since these pages are reserved. the check of
kvm_is_reserved_pfn() misconceives those pages as MMIO. Therefor, we
introduce 2 page map types, MEMORY_DEVICE_FS_DAX/MEMORY_DEVICE_DEV_DAX,
to indentify these pages are from NVDIMM pmem. and let kvm treat these
as normal pages.

Without this patch, Many operations will be missed due to this
mistreatment to pmem pages. For example, a page may not have chance to
be unpinned for KVM guest(in kvm_release_pfn_clean); not able to be
marked as dirty/accessed(in kvm_set_pfn_dirty/accessed) etc.

V1:
https://lkml.org/lkml/2018/7/4/91

V2:
https://lkml.org/lkml/2018/7/10/135

V3:
https://lkml.org/lkml/2018/8/9/17

V4:
[PATCH V3 1/4] Added "Reviewed-by: David / Acked-by: Pankaj"
[PATCH V3 2/4] Added "Reviewed-by: Jan"
[PATCH V3 3/4] Added "Acked-by: Jan"
[PATCH V3 4/4] Fix several typos

Zhang Yi (4):
  kvm: remove redundant reserved page check
  mm: introduce memory type MEMORY_DEVICE_DEV_DAX
  mm: add a function to differentiate the pages is from DAX device
    memory
  kvm: add a check if pfn is from NVDIMM pmem.

 drivers/dax/pmem.c       |  1 +
 include/linux/memremap.h |  8 ++++++++
 include/linux/mm.h       | 12 ++++++++++++
 virt/kvm/kvm_main.c      | 16 ++++++++--------
 4 files changed, 29 insertions(+), 8 deletions(-)
```
#### [PATCH v2 0/5] kvm: selftest: add dirty logging test
##### From: Peter Xu <peterx@redhat.com>

```c

v2:
- tune the parameters a bit (32 loops, 10ms interval) to let the test
  run ~1sec [Paolo]
- pass in extra mem pages in vm_create_default() [Paolo]
- add simple statistics on bits checked
- allow to specify parameters via argc/argv
- free bmap_track, which I forgot; rename to host_bmap_track

Add a simple test for existing dirty logging facility.

Please have a look, thanks.

Peter Xu (5):
  tools: introduce test_and_clear_bit
  kvm: selftest: unify the guest port macros
  kvm: selftest: include the tools headers
  kvm: selftest: pass in extra memory when create vm
  kvm: selftest: add dirty logging test

 tools/include/linux/bitmap.h                  |  17 +
 tools/testing/selftests/kvm/Makefile          |   5 +-
 .../selftests/kvm/cr4_cpuid_sync_test.c       |  32 +-
 tools/testing/selftests/kvm/dirty_logging.c   | 305 ++++++++++++++++++
 .../testing/selftests/kvm/include/kvm_util.h  |  46 ++-
 .../testing/selftests/kvm/include/test_util.h |   2 -
 tools/testing/selftests/kvm/lib/kvm_util.c    |  58 ++++
 tools/testing/selftests/kvm/lib/x86.c         |  18 +-
 tools/testing/selftests/kvm/set_sregs_test.c  |   2 +-
 tools/testing/selftests/kvm/state_test.c      |  32 +-
 tools/testing/selftests/kvm/sync_regs_test.c  |  21 +-
 .../selftests/kvm/vmx_tsc_adjust_test.c       |  43 +--
 12 files changed, 475 insertions(+), 106 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/dirty_logging.c
```
#### [PATCH v4 RESEND 0/5] KVM: x86: hyperv: PV IPI support for Windows
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Changes since v4:
- Adjust KVM_CAP_HYPERV_SEND_IPI's number [158]
- Add Roman's Reviewed-bys

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

 Documentation/virtual/kvm/api.txt  |   8 ++
 arch/x86/hyperv/hv_apic.c          |  12 +--
 arch/x86/include/asm/hyperv-tlfs.h |  16 +--
 arch/x86/kvm/hyperv.c              | 211 +++++++++++++++++++++++++++----------
 arch/x86/kvm/trace.h               |  42 ++++++++
 arch/x86/kvm/x86.c                 |   1 +
 include/uapi/linux/kvm.h           |   1 +
 virt/kvm/kvm_main.c                |   6 +-
 8 files changed, 224 insertions(+), 73 deletions(-)
```
#### [PATCH v2 0/5] KVM: s390: vsie: Consolidate CRYCB validation
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

Before adapting the CRYCB shadowing for a guest supporting
the AP instructions we want to clean the CRYCB shadowing code.


Pierre Morel (5):
  KVM: s390: vsie: BUG correction by shadow_crycb
  KVM: s390: vsie: Only accept FORMAT1 CRYCB for guest2
  KVM: s390: vsie: Allow support for a host without AP
  KVM: s390: vsie: Always test the crycbd for NULL
  KVM: s390: vsie: Do the CRYCB validation first

 arch/s390/kvm/vsie.c | 23 ++++++++++++++---------
 1 file changed, 14 insertions(+), 9 deletions(-)
```
#### [PATCH 0/2] KVM: x86: Don't re-{try,execute} L2 instrs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

Fix a bug where L2 can get stuck in an infinite fault loop due to an
L0 MMIO emulation failure that L0 thinks can be fixed by restarting
L2 (it thinks the fault is in the guest's domain because L0 tries
to translate an L2 GPA as an L2 GVA, i.e. CR2 isn't actually a CR2).

Sean Christopherson (2):
  KVM: x86: Do not re-{try,execute} after failed emulation in L2
  KVM: x86: Set EMULTYPE_NO_REEXECUTE for MMIO emulation

 arch/x86/kvm/mmu.c | 4 ++--
 arch/x86/kvm/x86.c | 6 ++++++
 2 files changed, 8 insertions(+), 2 deletions(-)
```
