#### [GIT PULL 01/28] KVM: s390: vsie: simulate VCPU SIE entry/exit
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From: David Hildenbrand <david@redhat.com>

VCPU requests and VCPU blocking right now don't take care of the vSIE
(as it was not necessary until now). But we want to have synchronous VCPU
requests that will also be handled before running the vSIE again.

So let's simulate a SIE entry of the VCPU when calling the sie during
vSIE handling and check for PROG_ flags. The existing infrastructure
(e.g. exit_sie()) will then detect that the SIE (in form of the vSIE) is
running and properly kick the vSIE CPU, resulting in it leaving the vSIE
loop and therefore the vSIE interception handler, allowing it to handle
VCPU requests.

E.g. if we want to modify the crycb of the VCPU and make sure that any
masks also get applied to the VSIE crycb shadow (which uses masks from the
VCPU crycb), we will need a way to hinder the vSIE from running and make
sure to process the updated crycb before reentering the vSIE again.

Signed-off-by: David Hildenbrand <david@redhat.com>
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Message-Id: <20180925231641.4954-2-akrowiak@linux.vnet.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c |  9 ++++++++-
 arch/s390/kvm/kvm-s390.h |  1 +
 arch/s390/kvm/vsie.c     | 21 +++++++++++++++++----
 3 files changed, 26 insertions(+), 5 deletions(-)

```
#### [PATCH kernel] vfio_pci: Allow mapping extra regions
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
So far we only allowed mapping of MMIO BARs to the userspace. However
there there are GPUs with on-board coherent RAM accessible via side
channels which we also want to map to the userspace. The first client
for this is NVIDIA V100 GPU with NVLink2 direct links to a POWER9
NPU-enabled CPU; such GPUs have 16GB RAM which is coherently mapped
to the system address space, we are going to export these as an extra
PCI region.

We already support extra PCI regions and this adds support for mapping
them to the userspace.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
 drivers/vfio/pci/vfio_pci_private.h |  3 +++
 drivers/vfio/pci/vfio_pci.c         | 10 ++++++++--
 2 files changed, 11 insertions(+), 2 deletions(-)

```
#### [PATCH kernel] vfio_pci: Allow regions to add own capabilities
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
VFIO regions already support region capabilities with a limited set of
fields. However the subdriver might have to report to the userspace
additional bits.

This adds an add_capability() hook to vfio_pci_regops.

This is aiming Witherspoon POWER9 machines which have multiple
interconnected NVIDIA V100 GPUs with coherent RAM; each GPU's RAM
is mapped to a system bus and to each of GPU internal system bus and
the GPUs use this for DMA routing as DMA trafic can go via any
of many NVLink2 (GPU-GPU or GPU-CPU) or even stay local within a GPU.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---

This is based on top of "vfio_pci: Allow mapping extra regions"

---
 drivers/vfio/pci/vfio_pci_private.h | 3 +++
 drivers/vfio/pci/vfio_pci.c         | 6 ++++++
 2 files changed, 9 insertions(+)

```
#### [PATCH v3 01/33] powerpc: Turn off CPU_FTR_P9_TM_HV_ASSIST in non-hypervisor mode
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
When doing nested virtualization, it is only necessary to do the
transactional memory hypervisor assist at level 0, that is, when
we are in hypervisor mode.  Nested hypervisors can just use the TM
facilities as architected.  Therefore we should clear the
CPU_FTR_P9_TM_HV_ASSIST bit when we are not in hypervisor mode,
along with the CPU_FTR_HVMODE bit.

Doing this will not change anything at this stage because the only
code that tests CPU_FTR_P9_TM_HV_ASSIST is in HV KVM, which currently
can only be used when when CPU_FTR_HVMODE is set.

Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kernel/cpu_setup_power.S | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PULL 1/1] s390/cio: Fix how vfio-ccw checks pinned pages
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Eric Farman <farman@linux.ibm.com>

We have two nested loops to check the entries within the pfn_array_table
arrays.  But we mistakenly use the outer array as an index in our check,
and completely ignore the indexing performed by the inner loop.

Cc: stable@vger.kernel.org
Signed-off-by: Eric Farman <farman@linux.ibm.com>
Message-Id: <20181002010235.42483-1-farman@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Farhan Ali <alifm@linux.ibm.com>
Reviewed-by: Jason J. Herne <jjherne@linux.vnet.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] s390/cio: Fix how vfio-ccw checks pinned pages
##### From: Eric Farman <farman@linux.ibm.com>

```c
We have two nested loops to check the entries within the pfn_array_table
arrays.  But we mistakenly use the outer array as an index in our check,
and completely ignore the indexing performed by the inner loop.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
