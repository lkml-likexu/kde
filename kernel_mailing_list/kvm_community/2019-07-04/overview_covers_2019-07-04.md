

#### [PATCH 0/5] KVM: some x86 MMU cleanup and new tracepoints
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

Given the attention to pgprintk, here are the patches I had locally
to add new tracepoints to __direct_map, FNAME(fetch) and mmu_set_spte().
These tracepoints actually come from a recent debugging session, so they
have proved their usefulness. :)  And because I'm feeling both lazy *and*
generous, I'm including a couple free cleanups from the series that I was
debugging!

Paolo

Junaid Shahid (1):
  kvm: x86: Do not release the page inside mmu_set_spte()

Paolo Bonzini (4):
  KVM: x86: make FNAME(fetch) and __direct_map more similar
  KVM: x86: remove now unneeded hugepage gfn adjustment
  KVM: x86: change kvm_mmu_page_get_gfn BUG_ON to WARN_ON
  KVM: x86: add tracepoints around __direct_map and FNAME(fetch)

 arch/x86/kvm/mmu.c         | 105 ++++++++++++++++++-------------------
 arch/x86/kvm/mmutrace.h    |  59 +++++++++++++++++++++
 arch/x86/kvm/paging_tmpl.h |  42 +++++++--------
 3 files changed, 129 insertions(+), 77 deletions(-)
```
#### [PATCH 0/2] fix likely hint of sched_info_on()
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c

When make defconfig, CONFIG_SCHEDSTATS is set to be y, so
sched_info_on() is 'likely' to be true. However, some functions
invoke this function with unlikely hint or use no hint. Let's
fix this.

Yi Wang (2):
  kvm: x86: add likely to sched_info_on()
  sched: fix unlikely use of sched_info_on()

 arch/x86/kvm/cpuid.c | 2 +-
 kernel/sched/stats.h | 6 +++---
 2 files changed, 4 insertions(+), 4 deletions(-)
```
#### [PATCH 0/5] KVM: cpuid: cleanups, simplify multi-index CPUID leaves
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c

While reviewing the AVX512_BF16, Jing Liu and I noted that the handling of
CPUID leaf 7 is quite messy, and in general the handling of multi-index
CPUID leaves is confusing.  These patches clean the code to prepare
for adding CPUID leaf 7 subleaf 1.

Paolo Bonzini (5):
  KVM: cpuid: do_cpuid_ent works on a whole CPUID function
  KVM: cpuid: extract do_cpuid_7_mask and support multiple subleafs
  KVM: cpuid: set struct kvm_cpuid_entry2 flags in do_cpuid_1_ent
  KVM: cpuid: rename do_cpuid_1_ent
  KVM: cpuid: remove has_leaf_count from struct kvm_cpuid_param

 arch/x86/kvm/cpuid.c | 222 ++++++++++++++++++++++++-------------------
 1 file changed, 122 insertions(+), 100 deletions(-)
```
