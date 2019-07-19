#### [PATCH 1/1] s390/dma: provide proper ARCH_ZONE_DMA_BITS value
##### From: Halil Pasic <pasic@linux.ibm.com>

```c
On s390 ZONE_DMA is up to 2G, i.e. ARCH_ZONE_DMA_BITS should be 31 bits.
The current value is 24 and makes __dma_direct_alloc_pages() take a
wrong turn first (but __dma_direct_alloc_pages() recovers then).

Let's correct ARCH_ZONE_DMA_BITS value and avoid wrong turns.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
Reported-by: Petr Tesarik <ptesarik@suse.cz>
Fixes: c61e9637340e ("dma-direct: add support for allocation from
ZONE_DMA and ZONE_DMA32")
---
 arch/s390/include/asm/dma.h | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH 1/2] KVM: Boost vCPUs that are delivering interrupts
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Inspired by commit 9cac38dd5d (KVM/s390: Set preempted flag during
vcpu wakeup and interrupt delivery), we want to also boost not just
lock holders but also vCPUs that are delivering interrupts. Most
smp_call_function_many calls are synchronous, so the IPI target vCPUs
are also good yield candidates.  This patch introduces vcpu->ready to
boost vCPUs during wakeup and interrupt delivery time; unlike s390 we do
not reuse vcpu->preempted so that voluntarily preempted vCPUs are taken
into account by kvm_vcpu_on_spin, but vmx_vcpu_pi_put is not affected
(VT-d PI handles voluntary preemption separately, in pi_pre_block).

Testing on 80 HT 2 socket Xeon Skylake server, with 80 vCPUs VM 80GB RAM:
ebizzy -M

            vanilla     boosting    improved
1VM          21443       23520         9%
2VM           2800        8000       180%
3VM           1800        3100        72%

Testing on my Haswell desktop 8 HT, with 8 vCPUs VM 8GB RAM, two VMs,
one running ebizzy -M, the other running 'stress --cpu 2':

w/ boosting + w/o pv sched yield(vanilla)

            vanilla     boosting   improved
              1570         4000      155%

w/ boosting + w/ pv sched yield(vanilla)

            vanilla     boosting   improved
              1844         5157      179%

w/o boosting, perf top in VM:

 72.33%  [kernel]       [k] smp_call_function_many
  4.22%  [kernel]       [k] call_function_i
  3.71%  [kernel]       [k] async_page_fault

w/ boosting, perf top in VM:

 38.43%  [kernel]       [k] smp_call_function_many
  6.31%  [kernel]       [k] async_page_fault
  6.13%  libc-2.23.so   [.] __memcpy_avx_unaligned
  4.88%  [kernel]       [k] call_function_interrupt

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: Marc Zyngier <maz@kernel.org>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
	v2->v3: put it in kvm_vcpu_wake_up, use WRITE_ONCE

 arch/s390/kvm/interrupt.c | 2 +-
 include/linux/kvm_host.h  | 1 +
 virt/kvm/kvm_main.c       | 9 +++++++--
 3 files changed, 9 insertions(+), 3 deletions(-)

```
#### [RFC PATCH v4 1/6] vfio: Define device specific irq type capability
##### From: Kechen Lu <kechen.lu@intel.com>

```c
From: Tina Zhang <tina.zhang@intel.com>

Cap the number of irqs with fixed indexes and use capability chains
to chain device specific irqs.

Signed-off-by: Tina Zhang <tina.zhang@intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---
 include/uapi/linux/vfio.h | 19 ++++++++++++++++++-
 1 file changed, 18 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: selftests: Remove superfluous define from vmx.c
##### From: Thomas Huth <thuth@redhat.com>

```c
The code in vmx.c does not use "program_invocation_name", so there
is no need to "#define _GNU_SOURCE" here.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 tools/testing/selftests/kvm/lib/x86_64/vmx.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH] KVM: x86: Add fixed counters to PMU filterFrom: Eric Hankland <ehankland@google.com>
##### From: Eric Hankland <ehankland@google.com>

```c
From: ehankland <ehankland@google.com>

Updates KVM_CAP_PMU_EVENT_FILTER so it can also whitelist or blacklist
fixed counters.

Signed-off-by: ehankland <ehankland@google.com>
---
 Documentation/virtual/kvm/api.txt | 13 ++++++++-----
 arch/x86/include/uapi/asm/kvm.h   |  9 ++++++---
 arch/x86/kvm/pmu.c                | 30 +++++++++++++++++++++++++-----
 3 files changed, 39 insertions(+), 13 deletions(-)

```
#### [PATCH] KVM: x86/vPMU: refine kvm_pmu err msg when event creation failed
##### From: Like Xu <like.xu@linux.intel.com>

```c
If a perf_event creation fails due to any reason of the host perf
subsystem, it has no chance to log the corresponding event for guest
which may cause abnormal sampling data in guest result. In debug mode,
this message helps to understand the state of vPMC and we should not
limit the number of occurrences.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/pmu.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [RFC PATCH] KVM: PPC: Enable the kvm_create_max_vcpus selftest on ppc64
##### From: Thomas Huth <thuth@redhat.com>

```c
The kvm_create_max_vcpus is generic enough so that it works out of the
box on POWER, too. We just have to provide some stubs for linking the
code from kvm_util.c.
Note that you also might have to do "ulimit -n 2500" before running the
test, to avoid that it runs out of file handles for the vCPUs.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 RFC since the stubs are a little bit ugly (does someone here like
 to implement them?), and since it's a little bit annoying that
 you have to raise the ulimit for this test in case the kernel provides
 more vCPUs than the default ulimit...

 tools/testing/selftests/kvm/Makefile          |  6 +++
 .../selftests/kvm/lib/powerpc/processor.c     | 37 +++++++++++++++++++
 2 files changed, 43 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/lib/powerpc/processor.c

```
#### [PATCH v1] mm/balloon_compaction: avoid duplicate page removal
##### From: Wei Wang <wei.w.wang@intel.com>

```c
Fixes: 418a3ab1e778 (mm/balloon_compaction: List interfaces)

A #GP is reported in the guest when requesting balloon inflation via
virtio-balloon. The reason is that the virtio-balloon driver has
removed the page from its internal page list (via balloon_page_pop),
but balloon_page_enqueue_one also calls "list_del"  to do the removal.
So remove the list_del in balloon_page_enqueue_one, and have the callers
do the page removal from their own page lists.

Signed-off-by: Wei Wang <wei.w.wang@intel.com>
---
 mm/balloon_compaction.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/2] KVM: Boosting vCPUs that are delivering interrupts
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Inspired by commit 9cac38dd5d (KVM/s390: Set preempted flag during vcpu wakeup 
and interrupt delivery), except the lock holder, we want to also boost vCPUs 
that are delivering interrupts. Actually most smp_call_function_many calls are 
synchronous ipi calls, the ipi target vCPUs are also good yield candidates. 
This patch introduces vcpu->ready to boost vCPUs during wakeup and interrupt 
delivery time.

Testing on 80 HT 2 socket Xeon Skylake server, with 80 vCPUs VM 80GB RAM:
ebizzy -M

            vanilla     boosting    improved
1VM          21443       23520         9%                      
2VM           2800        8000       180%
3VM           1800        3100        72%

Testing on my Haswell desktop 8 HT, with 8 vCPUs VM 8GB RAM, two VMs, 
one running ebizzy -M, the other running 'stress --cpu 2':

w/ boosting + w/o pv sched yield(vanilla)   

            vanilla     boosting   improved 
              1570         4000      155%

w/ boosting + w/ pv sched yield(vanilla)

            vanilla     boosting   improved 
              1844         5157      179%   

w/o boosting, perf top in VM:

 72.33%  [kernel]       [k] smp_call_function_many
  4.22%  [kernel]       [k] call_function_i
  3.71%  [kernel]       [k] async_page_fault

w/ boosting, perf top in VM:

 38.43%  [kernel]       [k] smp_call_function_many
  6.31%  [kernel]       [k] async_page_fault
  6.13%  libc-2.23.so   [.] __memcpy_avx_unaligned
  4.88%  [kernel]       [k] call_function_interrupt

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: Marc Zyngier <maz@kernel.org>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/s390/kvm/interrupt.c |  2 +-
 include/linux/kvm_host.h  |  1 +
 virt/kvm/kvm_main.c       | 12 +++++++++---
 3 files changed, 11 insertions(+), 4 deletions(-)

```
#### [PATCH v2] KVM: x86/vPMU: refine kvm_pmu err msg when event creation failed
##### From: Like Xu <like.xu@linux.intel.com>

```c
If a perf_event creation fails due to any reason of the host perf
subsystem, it has no chance to log the corresponding event for guest
which may cause abnormal sampling data in guest result. In debug mode,
this message helps to understand the state of vPMC and we may not
limit the number of occurrences but not in a spamming style.

Suggested-by: Joe Perches <joe@perches.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/pmu.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v2] mm/balloon_compaction: avoid duplicate page removal
##### From: Wei Wang <wei.w.wang@intel.com>

```c
Fixes: 418a3ab1e778 (mm/balloon_compaction: List interfaces)

A #GP is reported in the guest when requesting balloon inflation via
virtio-balloon. The reason is that the virtio-balloon driver has
removed the page from its internal page list (via balloon_page_pop),
but balloon_page_enqueue_one also calls "list_del"  to do the removal.
This is necessary when it's used from balloon_page_enqueue_list, but
not from balloon_page_enqueue_one.

So remove the list_del balloon_page_enqueue_one, and update some
comments as a reminder.

Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Acked-by: Nadav Amit <namit@vmware.com>
---
ChangeLong:
v1->v2: updated some comments

 mm/balloon_compaction.c | 14 ++++++++++----
 1 file changed, 10 insertions(+), 4 deletions(-)

```
