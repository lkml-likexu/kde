#### [PATCH 1/2] KVM: PPC: Book3S HV: Allow creating max number of VCPUs on POWER9
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Commit 1e175d2 ("KVM: PPC: Book3S HV: Pack VCORE IDs to access full
VCPU ID space", 2018-07-25) allowed use of VCPU IDs up to
KVM_MAX_VCPU_ID on POWER9 in all guest SMT modes and guest emulated
hardware SMT modes.  However, with the current definition of
KVM_MAX_VCPU_ID, a guest SMT mode of 1 and an emulated SMT mode of 8,
it is only possible to create KVM_MAX_VCPUS / 2 VCPUS, because
threads_per_subcore is 4 on POWER9 CPUs.  (Using an emulated SMT mode
of 8 is useful when migrating VMs to or from POWER8 hosts.)

This increases KVM_MAX_VCPU_ID to 8 * KVM_MAX_VCPUS when HV KVM is
configured in, so that a full complement of KVM_MAX_VCPUS VCPUs can
be created on POWER9 in all guest SMT modes and emulated hardware
SMT modes.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
Tested-by: Sam Bobroff <sbobroff@linux.ibm.com>
---
This and the next patch apply on my kvm-ppc-next branch, which
includes Sam Bobroff's patch "KVM: PPC: Book3S HV: Pack VCORE IDs to
access full VCPU ID space".

 arch/powerpc/include/asm/kvm_host.h | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [PATCH v12 01/12] perf/x86/intel/pt: Move Intel-PT MSRs bit definitions to a public header
##### From: Luwei Kang <luwei.kang@intel.com>

```c
From: Chao Peng <chao.p.peng@linux.intel.com>

Intel Processor Trace virtualization enabling in KVM guest
need to access these MSRs bit definitions, so move them to
public header file msr-index.h.

Signed-off-by: Chao Peng <chao.p.peng@linux.intel.com>
Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/events/intel/pt.h       | 37 -------------------------------------
 arch/x86/include/asm/msr-index.h | 33 +++++++++++++++++++++++++++++++++
 2 files changed, 33 insertions(+), 37 deletions(-)

```
#### [PATCH v9 01/13] s390/mm: Make gmap_protect_range more modular
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
This patch reworks the gmap_protect_range logic and extracts the pte
handling into an own function. Also we do now walk to the pmd and make
it accessible in the function for later use. This way we can add huge
page handling logic more easily.

Signed-off-by: Janosch Frank <frankja@linux.vnet.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Martin Schwidefsky <schwidefsky@de.ibm.com>
---
 arch/s390/mm/gmap.c | 93 +++++++++++++++++++++++++++++++++++++++++++++++------
 1 file changed, 83 insertions(+), 10 deletions(-)

```
#### [PATCH 1/3] KVM: x86: ensures all MSRs can always be KVM_GET/SET_MSR'd
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Some of the MSRs returned by GET_MSR_INDEX_LIST currently cannot be sent back
to KVM_GET_MSR and/or KVM_SET_MSR; either they can never be sent back, or you
they are only accepted under special conditions.  This makes the API a pain to
use.

To avoid this pain, this patch makes it so that the result of the get-list
ioctl can always be used for host-initiated get and set.  Since we don't have
a separate way to check for read-only MSRs, this means some Hyper-V MSRs are
ignored when written.  Arguably they should not even be in the result of
GET_MSR_INDEX_LIST, but I am leaving there in case userspace is using the
outcome of GET_MSR_INDEX_LIST to derive the support for the corresponding
Hyper-V feature.

Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/hyperv.c | 27 ++++++++++++++++++++-------
 arch/x86/kvm/hyperv.h |  2 +-
 arch/x86/kvm/x86.c    | 15 +++++++++------
 3 files changed, 30 insertions(+), 14 deletions(-)

```
#### [kvm-unit-tests PATCH] Makefiles: Remove the executable bit from the .elf and .flat files
##### From: Thomas Huth <thuth@redhat.com>

```c
The .elf and .flat files are not runnable on the host operating system,
so they should not be marked as executable. As we discovered recently,
the executable flag can also cause trouble when the files are packaged
in an .rpm file, since rpm "colors" the package differently if there
are 32-bit or 64-bit executables in the package (for multilib support).

Suggested-by: Laszlo Ersek <lersek@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Acked-by: Laszlo Ersek <lersek@redhat.com>
---
 arm/Makefile.common     | 2 ++
 powerpc/Makefile.common | 2 ++
 s390x/Makefile          | 1 +
 x86/Makefile.common     | 2 ++
 4 files changed, 7 insertions(+)

```
#### [PATCH v7 01/22] s390/zcrypt: Add ZAPQ inline function.
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From: Harald Freudenberger <freude@de.ibm.com>

Added new inline function ap_pqap_zapq()
which is a C inline function wrapper for
the AP PQAP(ZAPQ) instruction.

Signed-off-by: Harald Freudenberger <freude@de.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 drivers/s390/crypto/ap_asm.h | 19 +++++++++++++++++++
 1 file changed, 19 insertions(+)

```
