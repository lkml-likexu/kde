#### [PATCH 01/10] kvm: mmu: spte_write_protect optimizationFrom: Junaid Shahid <junaids@google.com>
##### From: Junaid Shahid <junaids@google.com>

```c
This change uses a lighter-weight function instead of mmu_spte_update()
in the common case in spte_write_protect(). This helps speed up the
get_dirty_log IOCTL.

Signed-off-by: Junaid Shahid <junaids@google.com>
---
 arch/x86/kvm/mmu.c | 25 +++++++++++++++++++++----
 1 file changed, 21 insertions(+), 4 deletions(-)

```
#### [GIT PULL] Please pull my kvm-ppc-next-4.20-2 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Please do a pull from my kvm-ppc-next-4.20-2 tag to get a second
update for PPC KVM to go into 4.20.  This is a very small update, with
only two commits.  It turned out to be necessary to disable the new
nested HV KVM feature on early POWER9 chips that need a particular
hardware bug workaround which the new guest entry path doesn't
implement, so one commit does that.  The other commit is an
optimization for clearing IOMMU tables when doing PCI pass-through.

The second commit touches drivers/vfio/vfio_iommu_spapr_tce.c as well
as arch/powerpc/kvm code.  That should be OK, as Alexey Kardashevskiy
is pretty much the only person that touches that file.  However, if
you would prefer that part of the change to go via another tree, let
me know and I'll re-do the pull request without that commit (or you
can just merge the other commit on its own).

Thanks,
Paul.

The following changes since commit 3d0d0d9b1d805e39456a9d49443d847092cb21ab:

  Merge tag 'kvm-s390-next-4.20-2' of git://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux into HEAD (2018-10-13 12:00:26 +0200)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-4.20-2

for you to fetch changes up to 6e301a8e56e429d6b01d83d427a9e54fdbb0fa60:

  KVM: PPC: Optimize clearing TCEs for sparse tables (2018-10-20 20:47:02 +1100)

----------------------------------------------------------------
Second PPC KVM update for 4.20.

Two commits; one is an optimization for PCI pass-through, and the
other disables nested HV-KVM on early POWER9 chips that need a
particular hardware bug workaround.

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      KVM: PPC: Optimize clearing TCEs for sparse tables

Paul Mackerras (1):
      KVM: PPC: Book3S HV: Don't use streamlined entry path on early POWER9 chips

 arch/powerpc/include/asm/iommu.h    |  2 +-
 arch/powerpc/kvm/book3s_64_vio.c    |  5 ++---
 arch/powerpc/kvm/book3s_64_vio_hv.c |  6 +++---
 arch/powerpc/kvm/book3s_hv.c        | 13 +++++++++++--
 drivers/vfio/vfio_iommu_spapr_tce.c | 23 +++++++++++++++++++++--
 5 files changed, 38 insertions(+), 11 deletions(-)
```
#### [PATCH] KVM/nVMX: Do not validate that posted_intr_desc_addr is page aligned
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c
The spec only requires the posted interrupt descriptor address to be
64-bytes aligned (i.e. bits[0:5] == 0). Using page_address_valid also
forces the address to be page aligned.

Only validate that the address does not cross the maximum physical address
without enforcing a page alignment.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: H. Peter Anvin <hpa@zytor.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Fixes: 6de84e581c0 ("nVMX x86: check posted-interrupt descriptor addresss on vmentry of L2")
Signed-off-by: KarimAllah Ahmed <karahmed@amazon.de>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm PATCH 1/2] mm: export __vmalloc_node_range()From: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
The __vmalloc_node_range() is in the include/linux/vmalloc.h file, but
it's not exported so it can't be used. This patch exports the API. The
motivation to export it is so that we can do aligned vmalloc's of KVM
vcpus.

Signed-off-by: Marc Orr <marcorr@google.com>
---
 mm/vmalloc.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v3 01/13] X86/nVMX: handle_vmon: Read 4 bytes from guest memory
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c
Read the data directly from guest memory instead of the map->read->unmap
sequence. This also avoids using kvm_vcpu_gpa_to_page() and kmap() which
assumes that there is a "struct page" for guest memory.

Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: KarimAllah Ahmed <karahmed@amazon.de>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
v1 -> v2:
- Massage commit message a bit.
---
 arch/x86/kvm/vmx.c | 14 +++-----------
 1 file changed, 3 insertions(+), 11 deletions(-)

```
#### [PATCH v2] KVM/nVMX: Do not validate that posted_intr_desc_addr is page aligned
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c
The spec only requires the posted interrupt descriptor address to be
64-bytes aligned (i.e. bits[0:5] == 0). Using page_address_valid also
forces the address to be page aligned.

Only validate that the address does not cross the maximum physical address
without enforcing a page alignment.

v1 -> v2:
- Add a missing parenthesis (dropped while merging!)

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: H. Peter Anvin <hpa@zytor.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Fixes: 6de84e581c0 ("nVMX x86: check posted-interrupt descriptor addresss on vmentry of L2")
Signed-off-by: KarimAllah Ahmed <karahmed@amazon.de>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Krish Sadhuhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: PPC: Use exported tb_to_ns() function in decrementer emulation
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
This changes the KVM code that emulates the decrementer function to do
the conversion of decrementer values to time intervals in nanoseconds
by calling the tb_to_ns() function exported by the powerpc timer code,
in preference to open-coded arithmetic using values from the
decrementer_clockevent struct.  Similarly, the HV-KVM code that did
the same conversion using arithmetic on tb_ticks_per_sec also now
uses tb_to_ns().

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
v2: don't delete the second do_div in kvmppc_emulate_dec(), we need it.

 arch/powerpc/kvm/book3s_hv.c | 3 +--
 arch/powerpc/kvm/emulate.c   | 7 +++----
 2 files changed, 4 insertions(+), 6 deletions(-)

```
#### [PATCH V4 1/5] KVM: X86: Memory ROE documentation
##### From: Ahmed Abd El Mawgood <ahmedsoliman0x666@gmail.com>

```c
Following up with my previous threads on KVM assisted Anti rootkit
protections.
The current version doesn't address the attacks involving pages
remapping. It is still design in progress, nevertheless, it will be in
my later patch sets.

Signed-off-by: Ahmed Abd El Mawgood <ahmedsoliman0x666@gmail.com>
---
 Documentation/virtual/kvm/hypercalls.txt | 31 ++++++++++++++++++++++++
 1 file changed, 31 insertions(+)

```
