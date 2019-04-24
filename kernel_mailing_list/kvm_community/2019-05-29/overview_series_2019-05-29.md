#### [GIT PULL 1/2] kvm: fix compile on s390 part 2
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
We also need to fence the memunmap part.

Fixes: e45adf665a53 ("KVM: Introduce a new guest mapping API")
Fixes: d30b214d1d0a (kvm: fix compilation on s390)
Cc: Michal Kubecek <mkubecek@suse.cz>
Cc: KarimAllah Ahmed <karahmed@amazon.de>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 virt/kvm/kvm_main.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v2 3/4] KVM: PPC: Book3S: Use new mutex to synchronize access to rtas token list
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Currently the Book 3S KVM code uses kvm->lock to synchronize access
to the kvm->arch.rtas_tokens list.  Because this list is scanned
inside kvmppc_rtas_hcall(), which is called with the vcpu mutex held,
taking kvm->lock cause a lock inversion problem, which could lead to
a deadlock.

To fix this, we add a new mutex, kvm->arch.rtas_token_lock, which nests
inside the vcpu mutexes, and use that instead of kvm->lock when
accessing the rtas token list.

This removes the lockdep_assert_held() in kvmppc_rtas_tokens_free().
At this point we don't hold the new mutex, but that is OK because
kvmppc_rtas_tokens_free() is only called when the whole VM is being
destroyed, and at that point nothing can be looking up a token in
the list.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/include/asm/kvm_host.h |  1 +
 arch/powerpc/kvm/book3s.c           |  1 +
 arch/powerpc/kvm/book3s_rtas.c      | 14 ++++++--------
 3 files changed, 8 insertions(+), 8 deletions(-)

```
#### [PATCH v3 1/8] s390/mm: force swiotlb for protected virtualization
##### From: Michael Mueller <mimu@linux.ibm.com>

```c
From: Halil Pasic <pasic@linux.ibm.com>

On s390, protected virtualization guests have to use bounced I/O
buffers.  That requires some plumbing.

Let us make sure, any device that uses DMA API with direct ops correctly
is spared from the problems, that a hypervisor attempting I/O to a
non-shared page would bring.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
---
 arch/s390/Kconfig                   |  4 ++++
 arch/s390/include/asm/mem_encrypt.h | 18 ++++++++++++++
 arch/s390/mm/init.c                 | 47 +++++++++++++++++++++++++++++++++++++
 3 files changed, 69 insertions(+)
 create mode 100644 arch/s390/include/asm/mem_encrypt.h

```
#### [PATCH 09/22] docs: mark orphan documents as such
##### From: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>

```c
Sphinx doesn't like orphan documents:

    Documentation/accelerators/ocxl.rst: WARNING: document isn't included in any toctree
    Documentation/arm/stm32/overview.rst: WARNING: document isn't included in any toctree
    Documentation/arm/stm32/stm32f429-overview.rst: WARNING: document isn't included in any toctree
    Documentation/arm/stm32/stm32f746-overview.rst: WARNING: document isn't included in any toctree
    Documentation/arm/stm32/stm32f769-overview.rst: WARNING: document isn't included in any toctree
    Documentation/arm/stm32/stm32h743-overview.rst: WARNING: document isn't included in any toctree
    Documentation/arm/stm32/stm32mp157-overview.rst: WARNING: document isn't included in any toctree
    Documentation/gpu/msm-crash-dump.rst: WARNING: document isn't included in any toctree
    Documentation/interconnect/interconnect.rst: WARNING: document isn't included in any toctree
    Documentation/laptops/lg-laptop.rst: WARNING: document isn't included in any toctree
    Documentation/powerpc/isa-versions.rst: WARNING: document isn't included in any toctree
    Documentation/virtual/kvm/amd-memory-encryption.rst: WARNING: document isn't included in any toctree
    Documentation/virtual/kvm/vcpu-requests.rst: WARNING: document isn't included in any toctree

So, while they aren't on any toctree, add :orphan: to them, in order
to silent this warning.

Signed-off-by: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>
---
 Documentation/accelerators/ocxl.rst                 | 2 ++
 Documentation/arm/stm32/overview.rst                | 2 ++
 Documentation/arm/stm32/stm32f429-overview.rst      | 2 ++
 Documentation/arm/stm32/stm32f746-overview.rst      | 2 ++
 Documentation/arm/stm32/stm32f769-overview.rst      | 2 ++
 Documentation/arm/stm32/stm32h743-overview.rst      | 2 ++
 Documentation/arm/stm32/stm32mp157-overview.rst     | 2 ++
 Documentation/gpu/msm-crash-dump.rst                | 2 ++
 Documentation/interconnect/interconnect.rst         | 2 ++
 Documentation/laptops/lg-laptop.rst                 | 2 ++
 Documentation/powerpc/isa-versions.rst              | 2 ++
 Documentation/virtual/kvm/amd-memory-encryption.rst | 2 ++
 Documentation/virtual/kvm/vcpu-requests.rst         | 2 ++
 13 files changed, 26 insertions(+)

```
#### [PATCH v2] KVM: PPC: Report single stepping capability
##### From: Fabiano Rosas <farosas@linux.ibm.com>

```c
When calling the KVM_SET_GUEST_DEBUG ioctl, userspace might request
the next instruction to be single stepped via the
KVM_GUESTDBG_SINGLESTEP control bit of the kvm_guest_debug structure.

We currently don't have support for guest single stepping implemented
in Book3S HV.

This patch adds the KVM_CAP_PPC_GUEST_DEBUG_SSTEP capability in order
to inform userspace about the state of single stepping support.

Signed-off-by: Fabiano Rosas <farosas@linux.ibm.com>
---

v1 -> v2:
 - add capability description to Documentation/virtual/kvm/api.txt

 Documentation/virtual/kvm/api.txt | 3 +++
 arch/powerpc/kvm/powerpc.c        | 5 +++++
 include/uapi/linux/kvm.h          | 1 +
 3 files changed, 9 insertions(+)

```
#### [PATCH v3] mm: add account_locked_vm utility function
##### From: Daniel Jordan <daniel.m.jordan@oracle.com>

```c
locked_vm accounting is done roughly the same way in five places, so
unify them in a helper.

Include the helper's caller in the debug print to distinguish between
callsites.

Error codes stay the same, so user-visible behavior does too.  The one
exception is that the -EPERM case in tce_account_locked_vm is removed
because Alexey has never seen it triggered.

Signed-off-by: Daniel Jordan <daniel.m.jordan@oracle.com>
Tested-by: Alexey Kardashevskiy <aik@ozlabs.ru>
Cc: Alan Tull <atull@kernel.org>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Benjamin Herrenschmidt <benh@kernel.crashing.org>
Cc: Christoph Lameter <cl@linux.com>
Cc: Christophe Leroy <christophe.leroy@c-s.fr>
Cc: Davidlohr Bueso <dave@stgolabs.net>
Cc: Ira Weiny <ira.weiny@intel.com>
Cc: Jason Gunthorpe <jgg@mellanox.com>
Cc: Mark Rutland <mark.rutland@arm.com>
Cc: Michael Ellerman <mpe@ellerman.id.au>
Cc: Moritz Fischer <mdf@kernel.org>
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: Steve Sistare <steven.sistare@oracle.com>
Cc: Wu Hao <hao.wu@intel.com>
Cc: linux-mm@kvack.org
Cc: kvm@vger.kernel.org
Cc: kvm-ppc@vger.kernel.org
Cc: linuxppc-dev@lists.ozlabs.org
Cc: linux-fpga@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
---
v3:
 - uninline account_locked_vm (Andrew)
 - fix doc comment (Ira)
 - retain down_write_killable in vfio type1 (Alex)
 - leave Alexey's T-b since the code is the same aside from uninlining
 - sanity tested with vfio type1, sanity-built on ppc

 arch/powerpc/kvm/book3s_64_vio.c     | 44 ++--------------
 arch/powerpc/mm/book3s64/iommu_api.c | 41 ++-------------
 drivers/fpga/dfl-afu-dma-region.c    | 53 ++------------------
 drivers/vfio/vfio_iommu_spapr_tce.c  | 54 ++------------------
 drivers/vfio/vfio_iommu_type1.c      | 17 +------
 include/linux/mm.h                   |  4 ++
 mm/util.c                            | 75 ++++++++++++++++++++++++++++
 7 files changed, 98 insertions(+), 190 deletions(-)


base-commit: cd6c84d8f0cdc911df435bb075ba22ce3c605b07

```
#### [PATCH] vfio-pci/nvlink2: Use vma_pages function instead of explicit computation
##### From: "Thomas Meyer" <thomas@m3y3r.de>

```c
Use vma_pages function on vma object instead of explicit computation.

Signed-off-by: Thomas Meyer <thomas@m3y3r.de>
```
