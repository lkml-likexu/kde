#### [kvm-unit-tests PATCH] Remove non-ASCII characters from vmx_tests.cFrom: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Some of the comments in vmx_test.c were copy/pasted from the SDM, and
include non-ASCII characters, which may not render properly in some
software engineering environments (e.g., vi). Thus, let's replace these
with their dumber, but superior, ASCII equivalents.

Signed-off-by: Marc Orr <marcorr@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 x86/vmx_tests.c | 18 +++++++++---------
 1 file changed, 9 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: x86: nVMX: allow RSM to restore VMXE CR4 flag
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Commit 5bea5123cbf0 ("KVM: VMX: check nested state and CR4.VMXE against
SMM") introduced a check to vmx_set_cr4() forbidding to set VMXE from SMM.
The check is correct, however, there is a special case when RSM is called
to leave SMM: rsm_enter_protected_mode() is called with HF_SMM_MASK still
set and in case VMXE was set before entering SMM we're failing to return.

Resolve the issue by temporary dropping HF_SMM_MASK around set_cr4() calls
when ops->set_cr() is called from RSM.

Reported-by: Jon Doron <arilou@gmail.com>
Suggested-by: Liran Alon <liran.alon@oracle.com>
Fixes: 5bea5123cbf0 ("KVM: VMX: check nested state and CR4.VMXE against SMM")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
- Instread of putting the temporary HF_SMM_MASK drop to
  rsm_enter_protected_mode() (as was suggested by Liran), move it to
  emulator_set_cr() modifying its interface. emulate.c seems to be
  vcpu-specifics-free at this moment, we may want to keep it this way.
- It seems that Hyper-V+UEFI on KVM is still broken, I'm observing sporadic
  hangs even with this patch. These hangs, however, seem to be unrelated to
  rsm.
---
 arch/x86/include/asm/kvm_emulate.h |  3 ++-
 arch/x86/kvm/emulate.c             | 27 ++++++++++++++-------------
 arch/x86/kvm/x86.c                 | 12 +++++++++++-
 3 files changed, 27 insertions(+), 15 deletions(-)

```
#### [PATCH v6 1/8] mm/mmu_notifier: helper to test if a range invalidation is blockable
##### From: jglisse@redhat.com

```c
From: Jérôme Glisse <jglisse@redhat.com>

Simple helpers to test if range invalidation is blockable. Latter
patches use cocinnelle to convert all direct dereference of range->
blockable to use this function instead so that we can convert the
blockable field to an unsigned for more flags.

Signed-off-by: Jérôme Glisse <jglisse@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: linux-mm@kvack.org
Cc: Christian König <christian.koenig@amd.com>
Cc: Joonas Lahtinen <joonas.lahtinen@linux.intel.com>
Cc: Jani Nikula <jani.nikula@linux.intel.com>
Cc: Rodrigo Vivi <rodrigo.vivi@intel.com>
Cc: Jan Kara <jack@suse.cz>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Felix Kuehling <Felix.Kuehling@amd.com>
Cc: Jason Gunthorpe <jgg@mellanox.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Ross Zwisler <zwisler@kernel.org>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Christian Koenig <christian.koenig@amd.com>
Cc: Ralph Campbell <rcampbell@nvidia.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: kvm@vger.kernel.org
Cc: dri-devel@lists.freedesktop.org
Cc: linux-rdma@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org
Cc: Arnd Bergmann <arnd@arndb.de>
---
 include/linux/mmu_notifier.h | 11 +++++++++++
 1 file changed, 11 insertions(+)

```
#### [PATCH v2] svm/avic: Fix invalidate logical APIC id entryThread-Topic: [PATCH v2] svm/avic: Fix invalidate logical APIC id entry
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
Only clear the valid bit when invalidate logical APIC id entry.
The current logic clear the valid bit, but also set the rest of
the bits (including reserved bits) to 1.

Fixes: 98d90582be2e ('svm: Fix AVIC DFR and LDR handling')
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH kvmtool v3 1/3] vfio-pci: Release INTx's unmask eventfd properly
##### From: Leo Yan <leo.yan@linaro.org>

```c
The PCI device INTx uses event fd 'unmask_fd' to signal the deassertion
of the line from guest to host; but this eventfd isn't released properly
when disable INTx.

This patch firstly adds field 'unmask_fd' in struct vfio_pci_device for
storing unmask eventfd and close it when disable INTx.

Reviewed-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Leo Yan <leo.yan@linaro.org>
---
 include/kvm/vfio.h | 1 +
 vfio/pci.c         | 2 ++
 2 files changed, 3 insertions(+)

```
