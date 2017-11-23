#### [PATCH v11 01/26] KVM: s390: vsie: simulate VCPU SIE entry/exit
##### From: Tony Krowiak <akrowiak@linux.vnet.ibm.com>

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
---
 arch/s390/kvm/kvm-s390.c |  9 ++++++++-
 arch/s390/kvm/kvm-s390.h |  1 +
 arch/s390/kvm/vsie.c     | 21 +++++++++++++++++----
 3 files changed, 26 insertions(+), 5 deletions(-)

```
#### [PATCH]  kvm-unit-tests: add a fetch instruction test case
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
BUG error infomation:

KVM internal error. Suberror: 1
emulation failure
RAX=0000000000463fe8 RBX=ffffffffffffd000 RCX=000000000000000c RDX=0000000000464006
RSI=0000000000000001 RDI=0000000000463000 RBP=0000000000452ce0 RSP=0000000000452c78
R8 =0000000000000000 R9 =0000000000410d7f R10=0000000000000000 R11=0000000000000000
R12=ffffffffffffe000 R13=1111111111111111 R14=3333333333333333 R15=00000000a06d39e8
RIP=ffffffffffffd000 RFL=00010002 [-------] CPL=0 II=0 A20=1 SMM=0 HLT=0
ES =0010 0000000000000000 ffffffff 00c09300 DPL=0 DS   [-WA]
CS =0008 0000000000000000 ffffffff 00a09b00 DPL=0 CS64 [-RA]
SS =0010 0000000000000000 ffffffff 00c09300 DPL=0 DS   [-WA]

new test case emulates the situation.If patch "kvm/x86: propagate
fetch fault into guest" has merged, the test case can gracefully
handle #PF in guest and continue execute.
---
 lib/vmalloc.c  | 32 ++++++++++++++++++++++++++++++++
 lib/vmalloc.h  |  3 +++
 lib/x86/vm.c   |  5 +++++
 x86/emulator.c | 50 ++++++++++++++++++++++++++++++++++++++++++++++++--
 4 files changed, 88 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] lib/s390x/io: Make sure that exit() is not returning
##### From: Thomas Huth <thuth@redhat.com>

```c
Since commit 96d79976f779589 kvm-unit-tests can not be compiled on
s390x anymore. The compiler complains:

lib/s390x/io.c: In function ‘exit’:
lib/s390x/io.c:57:1: error: ‘noreturn’ function does return [-Werror]

Let's make sure that the function can really not return anymore
(i.e. also do not return anymore in case SIGP is broken for example).

Fixes: 96d79976f779589bbdbb24474de8fd214b179d7e
Reported-by: Lukáš Doktor <ldoktor@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Lukáš Doktor <ldoktor@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/io.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH] kvm: vmx: Remove a mysterious FIXMEFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Bits 63:32 of %rax and %rdx are cleared in handle_rdmsr, as they
should be.  There is nothing here to fix.

Signed-off-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH] KVM: x86: fix L1TF's MMIO GFN calculation
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
One defense against L1TF in KVM is to always set the upper five bits
of the *legal* physical address in the SPTEs for non-present and
reserved SPTEs, e.g. MMIO SPTEs.  In the MMIO case, the GFN of the
MMIO SPTE may overlap with the upper five bits that are being usurped
to defend against L1TF.  To preserve the GFN, the bits of the GFN that
overlap with the repurposed bits are shifted left into the reserved
bits, i.e. the GFN in the SPTE will be split into high and low parts.
When retrieving the GFN from the MMIO SPTE, e.g. to check for an MMIO
access, get_mmio_spte_gfn() unshifts the affected bits and restores
the original GFN for comparison.  Unfortunately, get_mmio_spte_gfn()
neglects to mask off the reserved bits in the SPTE that were used to
store the upper chunk of the GFN.  As a result, KVM fails to detect
MMIO accesses whose GPA overlaps the repurprosed bits, which in turn
causes guest panics and hangs.

Fix the bug by generating a mask that covers the lower chunk of the
GFN, i.e. the bits that aren't shifted by the L1TF mitigation.  The
alternative approach would be to explicitly zero the five reserved
bits that are used to store the upper chunk of the GFN, but that
requires additional run-time computation and makes an already-ugly
bit of code even more inscrutable.

Reported-by: Sakari Ailus <sakari.ailus@iki.fi>
Fixes: d9b47449c1a1 ("kvm: x86: Set highest physical address bits in non-present/reserved SPTEs")
Cc: Junaid Shahid <junaids@google.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Junaid Shahid <junaids@google.com>
Tested-by: Sakari Ailus <sakari.ailus@linux.intel.com>
---
 arch/x86/kvm/mmu.c | 23 +++++++++++++++++++----
 1 file changed, 19 insertions(+), 4 deletions(-)

```
#### [PATCH] tools/kvm_stat: cut down decimal places in update interval dialog
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
From: Stefan Raspl <stefan.raspl@de.ibm.com>

We currently display the default number of decimal places for floats in
_show_set_update_interval(), which is quite pointless. Cutting down to a
single decimal place.

Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
---
 tools/kvm/kvm_stat/kvm_stat | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: x86: fix L1TF's MMIO GFN calculation
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
One defense against L1TF in KVM is to always set the upper five bits
of the *legal* physical address in the SPTEs for non-present and
reserved SPTEs, e.g. MMIO SPTEs.  In the MMIO case, the GFN of the
MMIO SPTE may overlap with the upper five bits that are being usurped
to defend against L1TF.  To preserve the GFN, the bits of the GFN that
overlap with the repurposed bits are shifted left into the reserved
bits, i.e. the GFN in the SPTE will be split into high and low parts.
When retrieving the GFN from the MMIO SPTE, e.g. to check for an MMIO
access, get_mmio_spte_gfn() unshifts the affected bits and restores
the original GFN for comparison.  Unfortunately, get_mmio_spte_gfn()
neglects to mask off the reserved bits in the SPTE that were used to
store the upper chunk of the GFN.  As a result, KVM fails to detect
MMIO accesses whose GPA overlaps the repurprosed bits, which in turn
causes guest panics and hangs.

Fix the bug by generating a mask that covers the lower chunk of the
GFN, i.e. the bits that aren't shifted by the L1TF mitigation.  The
alternative approach would be to explicitly zero the five reserved
bits that are used to store the upper chunk of the GFN, but that
requires additional run-time computation and makes an already-ugly
bit of code even more inscrutable.

I considered adding a WARN_ON_ONCE(low_phys_bits-1 <= PAGE_SHIFT) to
warn if GENMASK_ULL() generated a nonsensical value, but that seemed
silly since that would mean a system that supports VMX has less than
18 bits of physical address space...

Reported-by: Sakari Ailus <sakari.ailus@iki.fi>
Fixes: d9b47449c1a1 ("kvm: x86: Set highest physical address bits in non-present/reserved SPTEs")
Cc: Junaid Shahid <junaids@google.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Junaid Shahid <junaids@google.com>
Tested-by: Sakari Ailus <sakari.ailus@linux.intel.com>
---

v2: Changed the mask to cover only the GFN and tweaked variable
    names to better reflect this behavior [Junaid Shahid].

I didn't include Jim and Junaid's "Reviewed-by" tags in the changelog
because v2 reworks the calculation of the mask, which is the part of
this change that I'm most likely to screw up (math is hard).  I pasted
them below in case you feel it's appropriate to keep them.

Reviewed-by: Junaid Shahid <junaids@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>

 arch/x86/kvm/mmu.c | 24 ++++++++++++++++++++----
 1 file changed, 20 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/2] virtio/s390: avoid race on vcdev->config
##### From: Halil Pasic <pasic@linux.ibm.com>

```c
Currently we have a race on vcdev->config in virtio_ccw_get_config() and
in virtio_ccw_set_config().

This normally does not cause problems, as these are usually infrequent
operations. However, for some devices writing to/reading from the config
space can be triggered through sysfs attributes. For these, userspace can
force the race by increasing the frequency.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
Cc: stable@vger.kernel.org
---
 drivers/s390/virtio/virtio_ccw.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
#### [PATCH v2 1/9] x86/kvm/mmu: make vcpu->mmu a pointer to the current MMU
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
As a preparation to full MMU split between L1 and L2 make vcpu->arch.mmu
a pointer to the currently used mmu. For now, this is always
vcpu->arch.root_mmu. No functional change.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h |   5 +-
 arch/x86/kvm/mmu.c              | 165 ++++++++++++++++----------------
 arch/x86/kvm/mmu.h              |   8 +-
 arch/x86/kvm/mmu_audit.c        |  12 +--
 arch/x86/kvm/paging_tmpl.h      |  15 +--
 arch/x86/kvm/svm.c              |  14 +--
 arch/x86/kvm/vmx.c              |  15 +--
 arch/x86/kvm/x86.c              |  20 ++--
 8 files changed, 130 insertions(+), 124 deletions(-)

```
