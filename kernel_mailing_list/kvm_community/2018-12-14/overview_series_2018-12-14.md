#### [PATCH V3 1/8] KVM: PPC: Only report KVM_CAP_SPAPR_TCE_VFIO on powernv machines
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
The kvm capability KVM_CAP_SPAPR_TCE_VFIO is used to indicate the
availability of in kernel tce acceleration for vfio. However it is
currently the case that this is only available on a powernv machine,
not for a pseries machine.

Thus make this capability dependent on having the cpu feature
CPU_FTR_HVMODE.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/powerpc.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests v1] s390x: try !FORCE SCLP read SCP info if FORCED is unknown
##### From: David Hildenbrand <david@redhat.com>

```c
Looking at what the kernel does, looks like we should
- Check for more errors
- Try to execute !FORCED read if the FORCED one is unknown
- Set the function code to a normal write
- Set control_mask[2] to 0x80 (no idea what that means)

The kernel seems to set the function code to 0x80. Looking at where that
comes from, turns out this is a "dump indicator" to produce more
meaningful dumps. Looking for other function codes used in the kernel, I
discovered 0x40, which is used for "single increment assign" to speed up
memory hotplug. I was not able to find out what "control_mask[2] = 0x80"
means.

I guess we can just set the funcion code to 0 ("normal write). Let's
document the other bits in case anybody ever wonders what they mean.
Also, let's just set the other bits in the mask to 0, not sure if they
will actually be used, but this is definetly not wrong.

Signed-off-by: David Hildenbrand <david@redhat.com>
Tested-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---

Quickly tested under kvm (on top of z/VM) and under tcg.

 lib/s390x/sclp.c | 26 ++++++++++++++++++++++++--
 lib/s390x/sclp.h |  2 ++
 2 files changed, 26 insertions(+), 2 deletions(-)

```
#### [RESEND PATCH]  kvm: svm: remove unused struct definition
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
structure svm_init_data is never used. So remove it.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/svm.c | 5 -----
 1 file changed, 5 deletions(-)

```
#### [RFC RESEND PATCH] kvm: arm64: export memory error recovery capability to user space
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
When user space do memory recovery, it will check whether KVM and
guest support the error recovery, only when both of them support,
user space will do the error recovery. This patch exports this
capability of KVM to user space.

Cc: Peter Maydell <peter.maydell@linaro.org>
Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
---
User space needs to check this capability of KVM is suggested by Peter[1],
this patch as RFC tag because user space patches are still under review,
so this kernel patch is firstly sent out for review.

[1]: https://patchwork.codeaurora.org/patch/652261/
---
 Documentation/virtual/kvm/api.txt | 9 +++++++++
 arch/arm64/kvm/reset.c            | 1 +
 include/uapi/linux/kvm.h          | 1 +
 3 files changed, 11 insertions(+)

```
#### [PATCH v2] kvm: Change offset in kvm_write_guest_offset_cached to unsigned
##### From: Jim Mattson <jmattson@google.com>

```c
Since the offset is added directly to the hva from the
gfn_to_hva_cache, a negative offset could result in an out of bounds
write. The existing BUG_ON only checks for addresses beyond the end of
the gfn_to_hva_cache, not for addresses before the start of the
gfn_to_hva_cache.

Note that all current call sites have non-negative offsets.

Fixes: 4ec6e8636256 ("kvm: Introduce kvm_write_guest_offset_cached()")
Reported-by: Cfir Cohen <cfir@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Cfir Cohen <cfir@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 include/linux/kvm_host.h | 3 ++-
 virt/kvm/kvm_main.c      | 3 ++-
 2 files changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH V4 1/8] KVM: PPC: Only report KVM_CAP_SPAPR_TCE_VFIO on powernv machines
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
The kvm capability KVM_CAP_SPAPR_TCE_VFIO is used to indicate the
availability of in kernel tce acceleration for vfio. However it is
currently the case that this is only available on a powernv machine,
not for a pseries machine.

Thus make this capability dependent on having the cpu feature
CPU_FTR_HVMODE.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/kvm/powerpc.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
