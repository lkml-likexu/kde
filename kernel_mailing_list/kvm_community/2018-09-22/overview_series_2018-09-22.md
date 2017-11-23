#### [PATCH 1/2] KVM: x86: replace KVM_PAGES_PER_HPAGE with KVM_HPAGE_GFN_SIZE
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
KVM_PAGES_PER_HPAGE is got by left shift (KVM_HPAGE_GFN_SHIFT + PAGE_SHIFT)
and then divide by PAGE_SIZE, which could be simplified by just left shift
KVM_HPAGE_GFN_SHIFT.

At the same time, in almost 40% places where KVM_PAGES_PER_HPAGE is used,
pfn mask is actually what it needs instead of the number of pages.

This patch replaces KVM_PAGES_PER_HPAGE with KVM_HPAGE_GFN_SIZE and
introduces KVM_HPAGE_GFN_MASK to make it a little bit easy to read.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---
 arch/x86/include/asm/kvm_host.h |  3 ++-
 arch/x86/kvm/mmu.c              | 10 +++++-----
 arch/x86/kvm/paging_tmpl.h      |  6 +++---
 arch/x86/kvm/x86.c              |  6 +++---
 4 files changed, 13 insertions(+), 12 deletions(-)

```
