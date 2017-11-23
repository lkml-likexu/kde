#### [PATCH 01/10] KVM: State whether memory should be freed in kvm_free_memslot
##### From: Ahmed Abd El Mawgood <ahmedsoliman@mena.vt.edu>

```c
The conditions upon which kvm_free_memslot are kind of ad-hock,
it will be hard to extend memslot with allocatable data that needs to be
freed, so I replaced the current mechanism by clear flag that states if
the memory slot should be freed.

Signed-off-by: Ahmed Abd El Mawgood <ahmedsoliman@mena.vt.edu>
---
 virt/kvm/kvm_main.c | 11 ++++++-----
 1 file changed, 6 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S PR: Set hflag to indicate that POWER9 supports 1T segments
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
When booting a kvm-pr guest on a POWER9 machine the following message is
observed:
"qemu-system-ppc64: KVM does not support 1TiB segments which guest expects"

This is because the guest is expecting to be able to use 1T segments
however we don't indicate support for it. This is because we don't set
the BOOK3S_HFLAG_MULTI_PGSIZE flag in the hflags in kvmppc_set_pvr_pr()
on POWER9.

POWER9 does indeed have support for 1T segments, so add a case for
POWER9 to the switch statement to ensure it is set.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/book3s_pr.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] KVM: PPC: Book3S PR: Set hflag to indicate that POWER9 supports 1T segments
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
When booting a kvm-pr guest on a POWER9 machine the following message is
observed:
"qemu-system-ppc64: KVM does not support 1TiB segments which guest expects"

This is because the guest is expecting to be able to use 1T segments
however we don't indicate support for it. This is because we don't set
the BOOK3S_HFLAG_MULTI_PGSIZE flag in the hflags in kvmppc_set_pvr_pr()
on POWER9.

POWER9 does indeed have support for 1T segments, so add a case for
POWER9 to the switch statement to ensure it is set.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/book3s_pr.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH 1/8] KVM: PPC: Only report KVM_CAP_SPAPR_TCE_VFIO on powernv machines
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
The kvm capability KVM_CAP_SPAPR_TCE_VFIO is used to indicate the
availability of in kernel tce acceleration for vfio. However it is
currently the case that this is only available on a powernv machine,
not for a pseries machine.

Thus make this capability dependent on having the cpu feature
CPU_FTR_HVMODE.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/powerpc.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [kvm-unit-test 1/2] nVMX: Move all tests for VM-execution control fields to a separate function
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
... to improve readability and maintainability, and to align the code as per
the layout of the checks in chapter "VM Entries" in Intel SDM vol 3C.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
---
 x86/vmx_tests.c | 30 +++++++++++++++++++-----------
 1 file changed, 19 insertions(+), 11 deletions(-)

```
#### RESEND [PATCH 10/10] KVM: Log ROE violations in system log
##### From: Ahmed Abd El Mawgood <ahmedsoliman@mena.vt.edu>

```c
I am absolutely sorry, I had some modifications that I forgot to commit
before I send. so please use this one patch 10/10 instead of the last
one.

Signed-off-by: Ahmed Abd El Mawgood <ahmedsoliman@mena.vt.edu>
---
 virt/kvm/kvm_main.c    |  3 ++-
 virt/kvm/roe.c         | 26 ++++++++++++++++++++++++++
 virt/kvm/roe_generic.h |  3 ++-
 3 files changed, 30 insertions(+), 2 deletions(-)

```
