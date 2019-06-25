#### [PATCH v18 01/15] arm64: untag user pointers in access_ok and __uaccess_mask_ptr
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
This patch is a part of a series that extends kernel ABI to allow to pass
tagged user pointers (with the top byte set to something else other than
0x00) as syscall arguments.

copy_from_user (and a few other similar functions) are used to copy data
from user memory into the kernel memory or vice versa. Since a user can
provided a tagged pointer to one of the syscalls that use copy_from_user,
we need to correctly handle such pointers.

Do this by untagging user pointers in access_ok and in __uaccess_mask_ptr,
before performing access validity checks.

Note, that this patch only temporarily untags the pointers to perform the
checks, but then passes them as is into the kernel internals.

Reviewed-by: Vincenzo Frascino <vincenzo.frascino@arm.com>
Reviewed-by: Kees Cook <keescook@chromium.org>
Reviewed-by: Catalin Marinas <catalin.marinas@arm.com>
Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
---
 arch/arm64/include/asm/uaccess.h | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)

```
#### [PATCH v3 1/5] Build target for emulate.o as a userspace binary
##### From: Sam Caccavale <samcacc@amazon.de>

```c
This commit contains the minimal set of functionality to build
afl-harness around arch/x86/emulate.c which allows exercising code
in that source file, like x86_emulate_insn.
---

v1 -> v2:
 - Moved -O0 to ifdef DEBUG
 - Building with ASAN by default

v2 -> v3:
 - Removed a workaround for printf smashing the stack when compiled
   with -mcmodel=kernel, and stopped compiling with -mcmodel=kernel
 - Added a null check for malloc's return value
 - Moved multiple macros from emulator_ops.c into emulator_ops.h as
   static inline functions.

Signed-off-by: Sam Caccavale <samcacc@amazon.de>
---
 tools/Makefile                  |   9 ++
 tools/fuzz/x86ie/.gitignore     |   2 +
 tools/fuzz/x86ie/Makefile       |  51 +++++++++++
 tools/fuzz/x86ie/README.md      |  17 ++++
 tools/fuzz/x86ie/afl-harness.c  | 151 ++++++++++++++++++++++++++++++++
 tools/fuzz/x86ie/common.h       |  87 ++++++++++++++++++
 tools/fuzz/x86ie/emulator_ops.c |  58 ++++++++++++
 tools/fuzz/x86ie/emulator_ops.h | 120 +++++++++++++++++++++++++
 tools/fuzz/x86ie/stubs.c        |  56 ++++++++++++
 tools/fuzz/x86ie/stubs.h        |  52 +++++++++++
 10 files changed, 603 insertions(+)
 create mode 100644 tools/fuzz/x86ie/.gitignore
 create mode 100644 tools/fuzz/x86ie/Makefile
 create mode 100644 tools/fuzz/x86ie/README.md
 create mode 100644 tools/fuzz/x86ie/afl-harness.c
 create mode 100644 tools/fuzz/x86ie/common.h
 create mode 100644 tools/fuzz/x86ie/emulator_ops.c
 create mode 100644 tools/fuzz/x86ie/emulator_ops.h
 create mode 100644 tools/fuzz/x86ie/stubs.c
 create mode 100644 tools/fuzz/x86ie/stubs.h

```
#### [PATCH] vfio-ccw: make convert_ccw0_to_ccw1 static
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Reported by sparse.

Fixes: 7f8e89a8f2fd ("vfio-ccw: Factor out the ccw0-to-ccw1 transition")
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
On top of my vfio-ccw branch.

s390 arch maintainers: let me know if I should queue it and send
a pull request, or if you prefer to apply it directly.
---
 drivers/s390/cio/vfio_ccw_cp.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v3 2/5] Emulate simple x86 instructions in userspace
##### From: Sam Caccavale <samcacc@amazon.de>

```c
Added the minimal subset of code to run afl-harness with a binary file
as input.  These bytes are used to populate the vcpu structure and then
as an instruction stream for the emulator.  It does not attempt to handle
exceptions and only supports very simple ops.
---

v1 -> v2:
 - Removed a number of macros and moved them as static inline functions
   in emulator_ops.h

v2 -> v3:
 - Removed commented out code
 - Moved changes to emulator_ops.h into the first patch
 - Moved addition of afl-many script to a later patch
 - Fixed a spelling mistake

Signed-off-by: Sam Caccavale <samcacc@amazon.de>
---
 tools/fuzz/x86ie/emulator_ops.c | 325 +++++++++++++++++++++++++++++++-
 1 file changed, 324 insertions(+), 1 deletion(-)

```
#### [PATCH] x86/kvm/nVMCS: fix VMCLEAR when Enlightened VMCS is in use
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
When Enlightened VMCS is in use, it is valid to do VMCLEAR and,
according to TLFS, this should "transition an enlightened VMCS from the
active to the non-active state". It is, however, wrong to assume that
it is only valid to do VMCLEAR for the eVMCS which is currently active
on the vCPU performing VMCLEAR.

Currently, the logic in handle_vmclear() is broken: in case, there is no
active eVMCS on the vCPU doing VMCLEAR we treat the argument as a 'normal'
VMCS and kvm_vcpu_write_guest() to the 'launch_state' field irreversibly
corrupts the memory area.

So, in case the VMCLEAR argument is not the current active eVMCS on the
vCPU, how can we know if the area it is pointing to is a normal or an
enlightened VMCS?
Thanks to the bug in Hyper-V (see commit 72aeb60c52bf7 ("KVM: nVMX: Verify
eVMCS revision id match supported eVMCS version on eVMCS VMPTRLD")) we can
not, the revision can't be used to distinguish between them. So let's
assume it is always enlightened in case enlightened vmentry is enabled in
the assist page. Also, check if vmx->nested.enlightened_vmcs_enabled to
minimize the impact for 'unenlightened' workloads.

Fixes: b8bbab928fb1 ("KVM: nVMX: implement enlightened VMPTRLD and VMCLEAR")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/evmcs.c  | 18 ++++++++++++++++++
 arch/x86/kvm/vmx/evmcs.h  |  1 +
 arch/x86/kvm/vmx/nested.c | 19 ++++++++-----------
 3 files changed, 27 insertions(+), 11 deletions(-)

```
