#### [PATCH kernel] vfio-pci/nvlink2: Fix ancient gcc warnings
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
Using the {0} construct as a generic initializer is perfectly fine in C,
however due to a bug in old gcc there is a warning:

  + /kisskb/src/drivers/vfio/pci/vfio_pci_nvlink2.c: warning: (near
initialization for 'cap.header') [-Wmissing-braces]:  => 181:9

Since for whatever reason we still want to compile the modern kernel
with such an old gcc without warnings, this changes the capabilities
initialization.

The gcc bugzilla: https://gcc.gnu.org/bugzilla/show_bug.cgi?id=53119

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
 drivers/vfio/pci/vfio_pci_nvlink2.c | 30 ++++++++++++++---------------
 1 file changed, 15 insertions(+), 15 deletions(-)

```
#### [PATCH 1/3] KVM: nVMX: Sign extend displacements of VMX instr's mem operands
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
The VMCS.EXIT_QUALIFCATION field reports the displacements of memory
operands for various instructions, including VMX instructions, as a
naturally sized unsigned value, but masks the value by the addr size,
e.g. given a ModRM encoded as -0x28(%ebp), the -0x28 displacement is
reported as 0xffffffd8 for a 32-bit address size.  Despite some weird
wording regarding sign extension, the SDM explicitly states that bits
beyond the instructions address size are undefined:

    In all cases, bits of this field beyond the instruction’s address
    size are undefined.

Failure to sign extend the displacement results in KVM incorrectly
treating a negative displacement as a large positive displacement when
the address size of the VMX instruction is smaller than KVM's native
size, e.g. a 32-bit address size on a 64-bit KVM.

The very original decoding, added by commit 064aea774768 ("KVM: nVMX:
Decoding memory operands of VMX instructions"), sort of modeled sign
extension by truncating the final virtual/linear address for a 32-bit
address size.  I.e. it messed up the effective address but made it work
by adjusting the final address.

When segmentation checks were added, the truncation logic was kept
as-is and no sign extension logic was introduced.  In other words, it
kept calculating the wrong effective address while mostly generating
the correct virtual/linear address.  As the effective address is what's
used in the segment limit checks, this results in KVM incorreclty
injecting #GP/#SS faults due to non-existent segment violations when
a nested VMM uses negative displacements with an address size smaller
than KVM's native address size.

Using the -0x28(%ebp) example, an EBP value of 0x1000 will result in
KVM using 0x100000fd8 as the effective address when checking for a
segment limit violation.  This causes a 100% failure rate when running
a 32-bit KVM build as L1 on top of a 64-bit KVM L0.

Fixes: f9eb4af67c9d ("KVM: nVMX: VMX instructions: add checks for #GP/#SS exceptions")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/nested.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [kvm-unit-test nVMX] If "enable EPT" is enabled in a test, EPT pointer must also be set up
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Commit,

    5b8ba41dafd7 KVM: nVMX: move vmcs12 EPTP consistency check to
check_vmentry_prereqs()

moved the check for EPT pointer, from nested_ept_get_cr3() to
check_vmentry_prereqs(). As a result, if "enabled EPT" is set in a test
but EPT pointer is not, vmentry will fail even if EPT pointer is not
tested in that particular test.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
---
 x86/vmx_tests.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH 1/2] KVM: x86: Fix PV IPIs for 32-bit KVM host
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
The recognition of the KVM_HC_SEND_IPI hypercall was unintentionally
wrapped in "#ifdef CONFIG_X86_64", causing 32-bit KVM hosts to reject
any and all PV IPI requests despite advertising the feature.  This
results in all KVM paravirtualized guests hanging during SMP boot due
to IPIs never being delivered.

Fixes: 4180bf1b655a ("KVM: X86: Implement "send IPI" hypercall")
Cc: stable@vger.kernel.org
Cc: Wanpeng Li <wanpengli@tencent.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v4 1/9] mm/mmu_notifier: contextual information for event enums
##### From: jglisse@redhat.com

```c
From: Jérôme Glisse <jglisse@redhat.com>

CPU page table update can happens for many reasons, not only as a result
of a syscall (munmap(), mprotect(), mremap(), madvise(), ...) but also
as a result of kernel activities (memory compression, reclaim, migration,
...).

This patch introduce a set of enums that can be associated with each of
the events triggering a mmu notifier. Latter patches take advantages of
those enum values.

    - UNMAP: munmap() or mremap()
    - CLEAR: page table is cleared (migration, compaction, reclaim, ...)
    - PROTECTION_VMA: change in access protections for the range
    - PROTECTION_PAGE: change in access protections for page in the range
    - SOFT_DIRTY: soft dirtyness tracking

Being able to identify munmap() and mremap() from other reasons why the
page table is cleared is important to allow user of mmu notifier to
update their own internal tracking structure accordingly (on munmap or
mremap it is not longer needed to track range of virtual address as it
becomes invalid).

Signed-off-by: Jérôme Glisse <jglisse@redhat.com>
Cc: Christian König <christian.koenig@amd.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Felix Kuehling <Felix.Kuehling@amd.com>
Cc: Jason Gunthorpe <jgg@mellanox.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Matthew Wilcox <mawilcox@microsoft.com>
Cc: Ross Zwisler <zwisler@kernel.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Ralph Campbell <rcampbell@nvidia.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: kvm@vger.kernel.org
Cc: dri-devel@lists.freedesktop.org
Cc: linux-rdma@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org
Cc: Arnd Bergmann <arnd@arndb.de>
---
 include/linux/mmu_notifier.h | 30 ++++++++++++++++++++++++++++++
 1 file changed, 30 insertions(+)

```
#### [PATCH RESEND v2] uio/uio_pci_generic: Disable bus-mastering on release
##### From: Venkatesh Srinivas <vsrinivas@ops101.org>

```c
From: Venkatesh Srinivas <venkateshs@google.com>

Userspace code using uio_pci_generic may enable bus-mastering by
directly manipulating a PCI device's command register. If a userspace
program enables bus-mastering but exits/crashes uncleanly, bus-
mastering will still be enabled and stale DMA addresses may be
programmed and live in the device.

Disable bus-mastering unconditionally on last close of a UIO PCI fd
to avoid this. If the device did not have bus-mastering enabled,
pci_clear_master() is a no-op.

Signed-off-by: Venkatesh Srinivas <venkateshs@google.com>
Reviewed-by: Bjorn Helgaas <bhelgaas@google.com>
Reviewed-by: Catherine Sullivan <csully@google.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/uio/uio_pci_generic.c | 17 +++++++++++++++++
 1 file changed, 17 insertions(+)

```
#### [PATCH net-next V4 1/5] vhost: generalize adding used elem
##### From: Jason Wang <jasowang@redhat.com>

```c
Use one generic vhost_copy_to_user() instead of two dedicated
accessor. This will simplify the conversion to fine grain
accessors. About 2% improvement of PPS were seen during vitio-user
txonly test.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 11 +----------
 1 file changed, 1 insertion(+), 10 deletions(-)

```
