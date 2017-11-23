#### [PATCH] KVM: MMU: Introduce single thread to zap collapsible sptes
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Last year guys from huawei reported that the call of memory_global_dirty_log_start/stop() 
takes 13s for 4T memory and cause guest freeze too long which increases the unacceptable 
migration downtime. [1] [2]

Guangrong pointed out:

| collapsible_sptes zaps 4k mappings to make memory-read happy, it is not
| required by the semanteme of KVM_SET_USER_MEMORY_REGION and it is not
| urgent for vCPU's running, it could be done in a separate thread and use
| lock-break technology.

[1] https://lists.gnu.org/archive/html/qemu-devel/2017-04/msg05249.html
[2] https://www.mail-archive.com/qemu-devel@nongnu.org/msg449994.html

Several TB memory guest is common now after NVDIMM is deployed in cloud environment.
This patch utilizes worker thread to zap collapsible sptes in order to lazy collapse 
small sptes into large sptes during roll-back after live migration fails.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/include/asm/kvm_host.h |  3 +++
 arch/x86/kvm/mmu.c              | 37 ++++++++++++++++++++++++++++++++-----
 arch/x86/kvm/x86.c              |  4 ++++
 3 files changed, 39 insertions(+), 5 deletions(-)

```
#### [kvm-unit-test 1/3] KVM nVMX: test_vmcs_page_* functions need to accept alignment size as a parameter
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
.. because not all alignments fall on page size boundary.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
---
 x86/vmx_tests.c | 44 ++++++++++++++++++++++++++------------------
 1 file changed, 26 insertions(+), 18 deletions(-)

```
#### [PATCH v8 1/7] xen/pvh: Split CONFIG_XEN_PVH into CONFIG_PVH and CONFIG_XEN_PVH
##### From: Maran Wilson <maran.wilson@oracle.com>

```c
In order to pave the way for hypervisors other than Xen to use the PVH
entry point for VMs, we need to factor the PVH entry code into Xen specific
and hypervisor agnostic components. The first step in doing that, is to
create a new config option for PVH entry that can be enabled
independently from CONFIG_XEN.

Signed-off-by: Maran Wilson <maran.wilson@oracle.com>
Reviewed-by: Juergen Gross <jgross@suse.com>
---
 arch/x86/Kconfig          | 6 ++++++
 arch/x86/kernel/head_64.S | 2 +-
 arch/x86/xen/Kconfig      | 3 ++-
 3 files changed, 9 insertions(+), 2 deletions(-)

```
#### [RFC PATCH] KVM/x86/vPMU: Avoid counter reprogramming in kvm_pmu_handle_event
##### From: kan.liang@linux.intel.com

```c
From: Kan Liang <kan.liang@linux.intel.com>

In the process of handling a guest overflow, KVM unconditionally
reprograms perf counters before entering guest. The reprogramming brings
very high overhead. For common case, (e.g. vCPU still runs on the same
CPU), it's unnecessary.

Here is current process of handling an overflow triggered by guest.
The patch intends to avoid the reprogramming in step 2.

PERF (HOST)                   KVM                          PERF (GUEST)

1. intel_pmu_handle_irq():
     Disable the counter
     ...
     overflow callback
                          overflow_intr():
                            request KVM_REQ_PMU
                            inject PMI to guest
                          overflow_intr() exit
     Enable the counter
   intel_pmu_handle_irq() exit
   ...

2.                        vcpu_enter_guest():
                            kvm_pmu_handle_event():
                              reprogram_counter():
                                pmc_stop_counter():
   Close the counter
                                pmc_reprogram_counter():
   Create a new counter
                            ...

3.                                             intel_pmu_handle_irq():
                                                  Disable all counters
                          pmc_stop_counter():
   Close the counter
                                                         ...
                                                  Enable all counters
                          pmc_reprogram_counter():
   Create a new counter
                                               intel_pmu_handle_irq exit

Only when the vcpu moves to another CPU before Step 2, the counter needs
to be reprogrammed for new CPU.
Otherwise, the reprogramming should be avoided. Because there is nothing
changed for perf event. The perf sub-system can take care of the
assigned counter.

The patch doesn't impact the counter value. Because the counter doesn't
count in host anyway.

The patch doesn't impact the behavior of step 3 (guest PMI handler). The
intel_pmu_handle_irq() is just an example. It could be any PMI handler.

The average duration of kvm_pmu_handle_event() is 85,282,765ns on
a 4 socket SKX with one guest which has perf sampling single event.
With the patch, the average duration is only 97ns.

Signed-off-by: Kan Liang <kan.liang@linux.intel.com>
---
 arch/x86/kvm/pmu.c | 12 +++++++++++-
 1 file changed, 11 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/2] s390/setup: set control program code via diag 318
##### From: Collin Walling <walling@linux.ibm.com>

```c
The s390x diagnose 318 instruction sets the control program name code (CPNC)
and control program version code (CPVC) to provide useful information
regarding the OS during debugging. The CPNC is explicitly set to 4 to
indicate a Linux/KVM environment.

The CPVC is a 7-byte value containing:

 - 3-byte Linux version code
 - 3-byte unique value, currently set to 0
 - 1-byte trailing null

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Heiko Carstens <heiko.carstens@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/include/asm/diag.h   | 12 ++++++++++++
 arch/s390/include/asm/sclp.h   |  1 +
 arch/s390/kernel/diag.c        |  1 +
 arch/s390/kernel/setup.c       | 21 +++++++++++++++++++++
 drivers/s390/char/sclp.h       |  4 +++-
 drivers/s390/char/sclp_early.c |  2 ++
 6 files changed, 40 insertions(+), 1 deletion(-)

```
#### [PATCH V2 1/2] KVM/VMX: Check ept_pointer before flushing ept tlb
##### From: lantianyu1986@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

This patch is to initialize ept_pointer to INVALID_PAGE and check it
before flushing ept tlb. If ept_pointer is invalid, bypass the flush
request.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
 arch/x86/kvm/vmx.c | 13 +++++++++++--
 1 file changed, 11 insertions(+), 2 deletions(-)

```
#### [PATCH] vhost/vsock: fix reset orphans race with close timeout
##### From: Stefan Hajnoczi <stefanha@redhat.com>

```c
If a local process has closed a connected socket and hasn't received a
RST packet yet, then the socket remains in the table until a timeout
expires.

When a vhost_vsock instance is released with the timeout still pending,
the socket is never freed because vhost_vsock has already set the
SOCK_DONE flag.

Check if the close timer is pending and let it close the socket.  This
prevents the race which can leak sockets.

Reported-by: Maximilian Riemensberger <riemensberger@cadami.net>
Cc: Graham Whaley <graham.whaley@gmail.com>
Signed-off-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 drivers/vhost/vsock.c | 22 +++++++++++++++-------
 1 file changed, 15 insertions(+), 7 deletions(-)

```
#### [PATCH v3 1/8] arm64: KVM: Make VHE Stage-2 TLB invalidation operations non-interruptible
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Contrary to the non-VHE version of the TLB invalidation helpers, the VHE
code  has interrupts enabled, meaning that we can take an interrupt in
the middle of such a sequence, and start running something else with
HCR_EL2.TGE cleared.

That's really not a good idea.

Take the heavy-handed option and disable interrupts in
__tlb_switch_to_guest_vhe, restoring them in __tlb_switch_to_host_vhe.
The latter also gain an ISB in order to make sure that TGE really has
taken effect.

Cc: stable@vger.kernel.org
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm64/kvm/hyp/tlb.c | 35 +++++++++++++++++++++++++----------
 1 file changed, 25 insertions(+), 10 deletions(-)

```
#### [Resend PATCH V5 1/10] KVM: Add tlb_remote_flush_with_range callback in kvm_x86_ops
##### From: lantianyu1986@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

Add flush range call back in the kvm_x86_ops and platform can use it
to register its associated function. The parameter "kvm_tlb_range"
accepts a single range and flush list which contains a list of ranges.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
Change since v1:
       Change "end_gfn" to "pages" to aviod confusion as to whether
"end_gfn" is inclusive or exlusive.
---
 arch/x86/include/asm/kvm_host.h | 7 +++++++
 1 file changed, 7 insertions(+)

```
#### [PATCH 1/6] x86/hyper-v: Do some housekeeping in hyperv-tlfs.h
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
hyperv-tlfs.h is a bit messy: CPUID feature bits are not always sorted,
it's hard to get which CPUID they belong to, some items are duplicated
(e.g. HV_X64_MSR_CRASH_CTL_NOTIFY/HV_CRASH_CTL_CRASH_NOTIFY).

Do some housekeeping work. While on it, replace all (1 << X) with BIT(X)
macro.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Michael Kelley <mikelley@microsoft.com>
---
 arch/x86/include/asm/hyperv-tlfs.h | 186 ++++++++++++++---------------
 arch/x86/kvm/hyperv.c              |   4 +-
 2 files changed, 93 insertions(+), 97 deletions(-)

```
