

#### [PATCH v2 0/2] Avoid cpuid faulting leaking and one optimization
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c

This series avoid cpuid faulting of host leakding to guest, which may
potentially cause guest boot failure, and use hardware cpuid faulting
to remove emulation overhead.

Patch 1 avoids cpuid faulting leaking to guest through clearing cpuid faulting
bit before enter guest and restoring host's cpuid faulting bit when switch
to host.

Patch 2 enables hardware cpuid faulting for guest if it exists, to avoid
the emulation overhead.

==changelog==
v2:
- move the save/restore of cpuid faulting bit to
vmx_prepare_swich_to_guest/vmx_prepare_swich_to_host to avoid every
vmentry RDMSR, based on Paolo's comment.

==previous version==
v1: https://patchwork.kernel.org/patch/10852253/

Xiaoyao Li (2):
  kvm/vmx: avoid CPUID faulting leaking to guest
  kvm/vmx: Using hardware cpuid faulting to avoid emulation overhead

 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/vmx/vmx.c          | 45 +++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.h          |  2 ++
 arch/x86/kvm/x86.c              | 15 ++++++++---
 4 files changed, 61 insertions(+), 3 deletions(-)
```
