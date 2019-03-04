#### [multiprocess RFC PATCH 04/37] multi-process: Add stub functions to facilate build of multi-process
##### From: elena.ufimtseva@oracle.com

```c
From: Jagannathan Raman <jag.raman@oracle.com>

Add stub functions that are needed during compile time but not in
runtime.

Signed-off-by: John G Johnson <john.g.johnson@oracle.com>
Signed-off-by: Jagannathan Raman <jag.raman@oracle.com>
Signed-off-by: Elena Ufimtseva <elena.ufimtseva@oracle.com>
---
 accel/stubs/kvm-stub.c    |  5 +++
 accel/stubs/tcg-stub.c    | 85 +++++++++++++++++++++++++++++++++++++++++++++++
 stubs/machine-init-done.c |  4 +++
 stubs/monitor.c           | 25 ++++++++++++++
 stubs/net-stub.c          | 31 +++++++++++++++++
 stubs/replay.c            | 14 ++++++++
 stubs/vl-stub.c           | 75 +++++++++++++++++++++++++++++++++++++++++
 stubs/vmstate.c           | 20 +++++++++++
 stubs/xen-mapcache.c      | 22 ++++++++++++
 9 files changed, 281 insertions(+)
 create mode 100644 stubs/net-stub.c
 create mode 100644 stubs/vl-stub.c
 create mode 100644 stubs/xen-mapcache.c

```
#### [PATCH] kvm/x86/vmx: Make the emulation of MSR_IA32_ARCH_CAPABILITIES only for vmx
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c
At present, we report F(ARCH_CAPABILITIES) for x86 arch(both vmx and svm)
unconditionally, but we only emulate this MSR in vmx. It will cause #GP
while guest kernel rdmsr(MSR_IA32_ARCH_CAPABILITIES) in an AMD host.

Since MSR IA32_ARCH_CAPABILITIES is an intel-specific MSR, it makes no
sense to emulate it in svm. Thus this patch chooses to only emulate it
for vmx, and moves the related handling to vmx related files.

Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
---
 arch/x86/include/asm/kvm_host.h |  1 -
 arch/x86/kvm/cpuid.c            |  8 +++++---
 arch/x86/kvm/vmx/vmx.c          | 26 +++++++++++++++++++++++++-
 arch/x86/kvm/x86.c              | 25 -------------------------
 4 files changed, 30 insertions(+), 30 deletions(-)

```
#### [PATCH kvmtool 01/16] Makefile: Only compile vesa for archs that need it
##### From: Julien Thierry <julien.thierry@arm.com>

```c
The vesa framebuffer is only used by architectures that explicitly
require it (i.e. x86). Compile it out for architectures not using it, as
its current implementation might not work for them.

Signed-off-by: Julien Thierry <julien.thierry@arm.com>
---
 Makefile | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
