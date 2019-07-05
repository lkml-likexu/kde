#### [PATCH 1/2] kvm: x86: add likely to sched_info_on()
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
The condition to test is likely() to be true when make defconfig.
Add the hint.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
 arch/x86/kvm/cpuid.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 1/5] KVM: cpuid: do_cpuid_ent works on a whole CPUID function
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Rename it as well as __do_cpuid_ent and __do_cpuid_ent_emulated to have
"func" in its name, and drop the index parameter which is always 0.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/cpuid.c | 89 +++++++++++++++++++++-----------------------
 1 file changed, 42 insertions(+), 47 deletions(-)

```
#### [PATCH 1/5] kvm: x86: Do not release the page inside mmu_set_spte()
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From: Junaid Shahid <junaids@google.com>

Release the page at the call-site where it was originally acquired.
This makes the exit code cleaner for most call sites, since they
do not need to duplicate code between success and the failure
label.

Signed-off-by: Junaid Shahid <junaids@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu.c         | 18 +++++++-----------
 arch/x86/kvm/paging_tmpl.h |  8 +++-----
 2 files changed, 10 insertions(+), 16 deletions(-)

```
