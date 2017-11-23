#### [QEMU PATCH v2 1/2] i386: Compile CPUX86State xsave_buf only when support KVM or HVF
##### From: Liran Alon <liran.alon@oracle.com>

```c
While at it, also rename var to indicate it is not used only in KVM.

Reviewed-by: Nikita Leshchenko <nikita.leshchenko@oracle.com>
Reviewed-by: Patrick Colp <patrick.colp@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 target/i386/cpu.h         | 4 +++-
 target/i386/hvf/README.md | 2 +-
 target/i386/hvf/hvf.c     | 2 +-
 target/i386/hvf/x86hvf.c  | 4 ++--
 target/i386/kvm.c         | 6 +++---
 5 files changed, 10 insertions(+), 8 deletions(-)

```
#### [PATCH] KVM: x86: pvec always has more than 1 sp
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
Here is the code flow related to mmu_pages_first():

    mmu_unsync_walk()
        mmu_pages_add()
	__mmu_unsync_walk()
    for_each_sp()
        mmu_pages_first()

Every time when mmu_pages_first() is invoked, pvec is prepared by
mmu_unsync_walk() which insert at least one sp in pvec.

This patch removes the check on pvec->nr since this doesn't happen.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---
 arch/x86/kvm/mmu.c | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH v2] KVM: nVMX: Fix bad cleanup on error of get/set nested state IOCTLs
##### From: Liran Alon <liran.alon@oracle.com>

```c
The handlers of IOCTLs in kvm_arch_vcpu_ioctl() are expected to set
their return value in "r" local var and break out of switch block
when they encounter some error.
This is because vcpu_load() is called before the switch block which
have a proper cleanup of vcpu_put() afterwards.

However, KVM_{GET,SET}_NESTED_STATE IOCTLs handlers just return
immediately on error without performing above mentioned cleanup.

Thus, change these handlers to behave as expected.

Fixes: 8fcc4b5923af ("kvm: nVMX: Introduce KVM_CAP_NESTED_STATE")

Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
Reviewed-by: Patrick Colp <patrick.colp@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/x86.c | 22 ++++++++++++++--------
 1 file changed, 14 insertions(+), 8 deletions(-)

```
