#### [PATCH] arm64: KVM: rename the capability to set guest SError syndrome
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
In the documentation description, this capability's name is
KVM_CAP_ARM_SET_SERROR_ESR, but in the header file this
capability's name is KVM_CAP_ARM_INJECT_SERROR_ESR, so it
is better to use a same name.

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
In the Documentation/virtual/kvm/api.txt:

+8.19 KVM_CAP_ARM_SET_SERROR_ESR

In the include/uapi/linux/kvm.h:
+#define KVM_CAP_ARM_INJECT_SERROR_ESR 156

So in above two files, the capability's name is not same, it
is better to use a same name.
---
 arch/arm64/kvm/reset.c   | 2 +-
 include/uapi/linux/kvm.h | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: Documentation: rename the capability of KVM_CAP_ARM_SET_SERROR_ESR
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
In the documentation description, this capability's name is
KVM_CAP_ARM_SET_SERROR_ESR, but in the header file this
capability's name is KVM_CAP_ARM_INJECT_SERROR_ESR, so change
the documentation description to make it same.

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
Reported-by: Andrew Jones <drjones@redhat.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
In the Documentation/virtual/kvm/api.txt:

+8.19 KVM_CAP_ARM_SET_SERROR_ESR

In the include/uapi/linux/kvm.h:
+#define KVM_CAP_ARM_INJECT_SERROR_ESR 156

So in above two files, the capability's name is not same, it
is better to use a same name.
---
 Documentation/virtual/kvm/api.txt | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Don't truncate HPTE index in xlate function
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
This fixes a bug which causes guest virtual addresses to get translated
to guest real addresses incorrectly when the guest is using the HPT MMU
and has more than 256GB of RAM, or more specifically has a HPT larger
than 2GB.  This has showed up in testing as a failure of the host to
emulate doorbell instructions correctly on POWER9 for HPT guests with
more than 256GB of RAM.

The bug is that the HPTE index in kvmppc_mmu_book3s_64_hv_xlate()
is stored as an int, and in forming the HPTE address, the index gets
shifted left 4 bits as an int before being signed-extended to 64 bits.
The simple fix is to make the variable a long int, matching the
return type of kvmppc_hv_find_lock_hpte(), which is what calculates
the index.

Fixes: 697d3899dcb4 ("KVM: PPC: Implement MMIO emulation support for Book3S HV guests")
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---
 arch/powerpc/kvm/book3s_64_mmu_hv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/5] tools: introduce test_and_clear_bit
##### From: Peter Xu <peterx@redhat.com>

```c
We have test_and_set_bit but not test_and_clear_bit.  Add it.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 tools/include/linux/bitmap.h | 17 +++++++++++++++++
 1 file changed, 17 insertions(+)

```
#### [PATCH v3 1/3] KVM: x86: Turbo bits in MSR_PLATFORM_INFOFrom: Drew Schmitt <dasch@google.com>
##### From: Drew Schmitt <dasch@google.com>

```c
Allow userspace to set turbo bits in MSR_PLATFORM_INFO. Previously, only
the CPUID faulting bit was settable. But now any bit in
MSR_PLATFORM_INFO would be settable. This can be used, for example, to
convey frequency information about the platform on which the guest is
running.

Signed-off-by: Drew Schmitt <dasch@google.com>
---
 arch/x86/kvm/x86.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH] x86: kvm: avoid unused variable warning
##### From: Arnd Bergmann <arnd@arndb.de>

```c
Removing one of the two accesses of the maxphyaddr variable led to
a harmless warning:

arch/x86/kvm/x86.c: In function 'kvm_set_mmio_spte_mask':
arch/x86/kvm/x86.c:6563:6: error: unused variable 'maxphyaddr' [-Werror=unused-variable]

Removing the #ifdef seems to be the nicest workaround, as it
makes the code look cleaner than adding another #ifdef.

Fixes: 28a1f3ac1d0c ("kvm: x86: Set highest physical address bits in non-present/reserved SPTEs")
Signed-off-by: Arnd Bergmann <arnd@arndb.de>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/x86/kvm/x86.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [PATCH] x86/mm: Simplify p[g4um]d_page() macros
##### From: Andi Kleen <andi@firstfloor.org>

```c
From: Andi Kleen <ak@linux.intel.com>

Create a pgd_pfn() macro similar to the p[4um]d_pfn() macros and then
use the p[g4um]d_pfn() macros in the p[g4um]d_page() macros instead of
duplicating the code.

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
Reviewed-by: Thomas Gleixner <tglx@linutronix.de>
Reviewed-by: Borislav Petkov <bp@suse.de>
Cc: Alexander Potapenko <glider@google.com>
Cc: Andrey Ryabinin <aryabinin@virtuozzo.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Arnd Bergmann <arnd@arndb.de>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Brijesh Singh <brijesh.singh@amd.com>
Cc: Dave Young <dyoung@redhat.com>
Cc: Dmitry Vyukov <dvyukov@google.com>
Cc: Jonathan Corbet <corbet@lwn.net>
Cc: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Cc: Larry Woodman <lwoodman@redhat.com>
Cc: Linus Torvalds <torvalds@linux-foundation.org>
Cc: Matt Fleming <matt@codeblueprint.co.uk>
Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Rik van Riel <riel@redhat.com>
Cc: Toshimitsu Kani <toshi.kani@hpe.com>
Cc: kasan-dev@googlegroups.com
Cc: kvm@vger.kernel.org
Cc: linux-arch@vger.kernel.org
Cc: linux-doc@vger.kernel.org
Cc: linux-efi@vger.kernel.org
Cc: linux-mm@kvack.org
Link: http://lkml.kernel.org/r/e61eb533a6d0aac941db2723d8aa63ef6b882dee.1500319216.git.thomas.lendacky@amd.com
[Backported to 4.9 stable by AK, suggested by Michael Hocko]
Signed-off-by: Ingo Molnar <mingo@kernel.org>
Signed-off-by: Andi Kleen <ak@linux.intel.com>
---
 arch/x86/include/asm/pgtable.h | 13 ++++++++-----
 1 file changed, 8 insertions(+), 5 deletions(-)

```
