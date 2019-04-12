#### [PATCH] KVM: x86: Add Intel CPUID.1F cpuid emulation support
##### From: Like Xu <like.xu@linux.intel.com>

```c
Expose Intel V2 Extended Topology Enumeration Leaf to guest only when
host system has multiple software-visible die within each package.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/cpuid.c | 13 +++++++++++++
 1 file changed, 13 insertions(+)

```
