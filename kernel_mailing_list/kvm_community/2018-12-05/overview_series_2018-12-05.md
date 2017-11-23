#### [kvm-unit-tests PATCH v2 1/6] s390x: Cleanup sclp-ascii.c and add sigp order definitions
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Let's fix sclp-ascii.c indentation and rename it to sclp-console.c

Also adding sigp order codes to remove magic numbers from io.c.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 lib/s390x/asm/arch_def.h                   | 18 ++++++++++++++
 lib/s390x/io.c                             |  5 ++--
 lib/s390x/{sclp-ascii.c => sclp-console.c} | 38 +++++++++++++++---------------
 lib/s390x/sclp.h                           |  2 +-
 s390x/Makefile                             |  2 +-
 5 files changed, 42 insertions(+), 23 deletions(-)
 rename lib/s390x/{sclp-ascii.c => sclp-console.c} (54%)

```
#### [PATCH] kvm: x86: Report STIBP on GET_SUPPORTED_CPUID
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
Months ago, we have added code to allow direct access to MSR_IA32_SPEC_CTRL
to the guest, which makes STIBP available to guests.  This was implemented
by commits d28b387fb74d ("KVM/VMX: Allow direct access to
MSR_IA32_SPEC_CTRL") and b2ac58f90540 ("KVM/SVM: Allow direct access to
MSR_IA32_SPEC_CTRL").

However, we never updated GET_SUPPORTED_CPUID to let userspace know that
STIBP can be enabled in CPUID.  Fix that by updating
kvm_cpuid_8000_0008_ebx_x86_features and kvm_cpuid_7_0_edx_x86_features.

Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
---
 arch/x86/kvm/cpuid.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH AUTOSEL 4.19 025/123] s390/cio: Fix cleanup of pfn_array alloc failure
##### From: Sasha Levin <sashal@kernel.org>

```c
From: Eric Farman <farman@linux.ibm.com>

[ Upstream commit 806212f91c874b24cf9eb4a9f180323671b6c5ed ]

If pfn_array_alloc fails somehow, we need to release the pfn_array_table
that was malloc'd earlier.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
Message-Id: <20181109023937.96105-2-farman@linux.ibm.com>
Acked-by: Halil Pasic <pasic@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Sasha Levin <sashal@kernel.org>
---
 drivers/s390/cio/vfio_ccw_cp.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH AUTOSEL 3.18 15/26] KVM: x86: fix empty-body warnings
##### From: Sasha Levin <sashal@kernel.org>

```c
From: Yi Wang <wang.yi59@zte.com.cn>

[ Upstream commit 354cb410d87314e2eda344feea84809e4261570a ]

We get the following warnings about empty statements when building
with 'W=1':

arch/x86/kvm/lapic.c:632:53: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1907:42: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1936:65: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1975:44: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]

Rework the debug helper macro to get rid of these warnings.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sasha Levin <sashal@kernel.org>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH AUTOSEL 4.4 18/33] KVM: x86: fix empty-body warnings
##### From: Sasha Levin <sashal@kernel.org>

```c
From: Yi Wang <wang.yi59@zte.com.cn>

[ Upstream commit 354cb410d87314e2eda344feea84809e4261570a ]

We get the following warnings about empty statements when building
with 'W=1':

arch/x86/kvm/lapic.c:632:53: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1907:42: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1936:65: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1975:44: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]

Rework the debug helper macro to get rid of these warnings.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sasha Levin <sashal@kernel.org>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH AUTOSEL 4.9 26/45] KVM: x86: fix empty-body warnings
##### From: Sasha Levin <sashal@kernel.org>

```c
From: Yi Wang <wang.yi59@zte.com.cn>

[ Upstream commit 354cb410d87314e2eda344feea84809e4261570a ]

We get the following warnings about empty statements when building
with 'W=1':

arch/x86/kvm/lapic.c:632:53: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1907:42: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1936:65: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1975:44: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]

Rework the debug helper macro to get rid of these warnings.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sasha Levin <sashal@kernel.org>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH AUTOSEL 4.14 42/69] KVM: x86: fix empty-body warnings
##### From: Sasha Levin <sashal@kernel.org>

```c
From: Yi Wang <wang.yi59@zte.com.cn>

[ Upstream commit 354cb410d87314e2eda344feea84809e4261570a ]

We get the following warnings about empty statements when building
with 'W=1':

arch/x86/kvm/lapic.c:632:53: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1907:42: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1936:65: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]
arch/x86/kvm/lapic.c:1975:44: warning: suggest braces around empty body in an ‘if’ statement [-Wempty-body]

Rework the debug helper macro to get rid of these warnings.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sasha Levin <sashal@kernel.org>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/3] mm/mmu_notifier: use structure for invalidate_range_start/end callback
##### From: jglisse@redhat.com

```c
From: Jérôme Glisse <jglisse@redhat.com>

To avoid having to change many callback definition everytime we want
to add a parameter use a structure to group all parameters for the
mmu_notifier invalidate_range_start/end callback. No functional changes
with this patch.

Signed-off-by: Jérôme Glisse <jglisse@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Matthew Wilcox <mawilcox@microsoft.com>
Cc: Ross Zwisler <zwisler@kernel.org>
Cc: Jan Kara <jack@suse.cz>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Christian Koenig <christian.koenig@amd.com>
Cc: Felix Kuehling <felix.kuehling@amd.com>
Cc: Ralph Campbell <rcampbell@nvidia.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: kvm@vger.kernel.org
Cc: dri-devel@lists.freedesktop.org
Cc: linux-rdma@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org
Acked-by: Jan Kara <jack@suse.cz>
Acked-by: Jason Gunthorpe <jgg@mellanox.com>
---
 drivers/gpu/drm/amd/amdgpu/amdgpu_mn.c  | 43 +++++++++++--------------
 drivers/gpu/drm/i915/i915_gem_userptr.c | 14 ++++----
 drivers/gpu/drm/radeon/radeon_mn.c      | 16 ++++-----
 drivers/infiniband/core/umem_odp.c      | 20 +++++-------
 drivers/infiniband/hw/hfi1/mmu_rb.c     | 13 +++-----
 drivers/misc/mic/scif/scif_dma.c        | 11 ++-----
 drivers/misc/sgi-gru/grutlbpurge.c      | 14 ++++----
 drivers/xen/gntdev.c                    | 12 +++----
 include/linux/mmu_notifier.h            | 14 +++++---
 mm/hmm.c                                | 23 ++++++-------
 mm/mmu_notifier.c                       | 21 ++++++++++--
 virt/kvm/kvm_main.c                     | 14 +++-----
 12 files changed, 102 insertions(+), 113 deletions(-)

```
#### [PATCH v3] KVM nVMX: MSRs should not be stored if VM-entry fails during or after loading guest state
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "VM-entry Failures During or After Loading Guest State"
in Intel SDM vol 3C,

	"No MSRs are saved into the VM-exit MSR-store area."

when bit 31 of the exit reason is set.

Reported-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx.c | 16 ++++++++++++----
 1 file changed, 12 insertions(+), 4 deletions(-)

```
#### [PATCH v4 1/5] kvm: vmx: Set IA32_TSC_AUX for legacy mode guestsFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
RDTSCP is supported in legacy mode as well as long mode. The
IA32_TSC_AUX MSR should be set to the correct guest value before
entering any guest that supports RDTSCP.

Fixes: 4e47c7a6d714 ("KVM: VMX: Add instruction rdtscp support for guest")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] x86/hyper-v: Stop caring about EOI for direct stimers
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Turns out we over-engineered Direct Mode for stimers a bit: unlike
traditional stimers where we may want to try to re-inject the message upon
EOI, Direct Mode stimers just set the irq in APIC and kvm_apic_set_irq()
fails only when APIC is disabled (see APIC_DM_FIXED case in
__apic_accept_irq()). Remove the redundant part.

Suggested-by: Roman Kagan <rkagan@virtuozzo.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/hyperv.c | 36 +++---------------------------------
 1 file changed, 3 insertions(+), 33 deletions(-)

```
