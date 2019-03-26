#### [RFC PATCH] mm, kvm: account kvm_vcpu_mmap to kmemcgFrom: Shakeel Butt <shakeelb@google.com>
##### From: Shakeel Butt <shakeelb@google.com>

```c
A VCPU of a VM can allocate upto three pages which can be mmap'ed by the
user space application. At the moment this memory is not charged. On a
large machine running large number of VMs (or small number of VMs having
large number of VCPUs), this unaccounted memory can be very significant.
So, this memory should be charged to a kmemcg. However that is not
possible as these pages are mmapped to the userspace and PageKmemcg()
was designed with the assumption that such pages will never be mmapped
to the userspace.

One way to solve this problem is by introducing an additional memcg
charging API similar to mem_cgroup_[un]charge_skmem(). However skmem
charging API usage is contained and shared and no new users are
expected but the pages which can be mmapped and should be charged to
kmemcg can and will increase. So, requiring the usage for such API will
increase the maintenance burden. The simplest solution is to remove the
assumption of no mmapping PageKmemcg() pages to user space.

Signed-off-by: Shakeel Butt <shakeelb@google.com>
---
 arch/s390/kvm/kvm-s390.c       |  2 +-
 arch/x86/kvm/x86.c             |  2 +-
 include/linux/page-flags.h     | 26 ++++++++++++++++++--------
 include/trace/events/mmflags.h |  9 ++++++++-
 virt/kvm/coalesced_mmio.c      |  2 +-
 virt/kvm/kvm_main.c            |  2 +-
 6 files changed, 30 insertions(+), 13 deletions(-)

```
#### [PATCH v4 1/2] kvm/vmx: Switch MSR_MISC_FEATURES_ENABLES between host and guest
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c
There are two defined bits in MSR_MISC_FEATURES_ENABLES, bit 0 for cpuid
faulting and bit 1 for ring3mwait.

== cpuid Faulting ==
cpuid faulting is a feature about CPUID instruction. When cpuid faulting
is enabled, all execution of the CPUID instruction outside system-management
mode (SMM) cause a general-protection (#GP) if the CPL > 0.

About this feature, detailed information can be found at
https://www.intel.com/content/dam/www/public/us/en/documents/application-notes/virtualization-technology-flexmigration-application-note.pdf

Current KVM provides software emulation of this feature for guest.
However, because cpuid faulting takes higher priority over CPUID vm exit (Intel
SDM vol3.25.1.1), there is a risk of leaking cpuid faulting to guest when host
enables it. If host enables cpuid faulting by setting the bit 0 of
MSR_MISC_FEATURES_ENABLES, it will pass to guest since there is no switch of
MSR_MISC_FEATURES_ENABLES yet. As a result, when guest calls CPUID instruction
in CPL > 0, it will generate a #GP instead of CPUID vm eixt.

This issue will cause guest boot failure when guest uses *modprobe*
to load modules. *modprobe* calls CPUID instruction, thus causing #GP in
guest. Since there is no handling of cpuid faulting in #GP handler, guest
fails boot.

== ring3mwait ==
Ring3mwait is a Xeon-Phi Product Family x200 series specific feature,
which allows the MONITOR and MWAIT instructions to be executed in rings
other than ring 0. The feature can be enabled by setting bit 1 in
MSR_MISC_FEATURES_ENABLES. The register can also be read to determine
whether the instructions are enabled at other than ring 0.

About this feature, description can be found at
https://software.intel.com/en-us/blogs/2016/10/06/intel-xeon-phi-product-family-x200-knl-user-mode-ring-3-monitor-and-mwait

Current kvm doesn't expose feature ring3mwait to guest. However, there is also
a risk of leaking ring3mwait to guest if host enables it since there is no
switch of MSR_MISC_FEATURES_ENABLES.

== solution ==
From above analysis, both cpuid faulting and ring3mwait can be leaked to guest.
To fix this issue, MSR_MISC_FEATURES_ENABLES should be switched between host
and guest. Since MSR_MISC_FEATURES_ENABLES is intel-specific, this patch
implement the switching only in vmx.

For the reason that kvm provides the software emulation of cpuid faulting and
kvm doesn't expose ring3mwait to guest. MSR_MISC_FEATURES_ENABLES can be just
cleared to zero for guest when any of the features is enabled in host.

Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
---
 arch/x86/kernel/process.c | 1 +
 arch/x86/kvm/vmx/vmx.c    | 8 ++++++++
 2 files changed, 9 insertions(+)

```
