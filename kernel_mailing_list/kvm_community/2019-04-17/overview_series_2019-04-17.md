#### [PATCH v2 4/7] KVM: s390: enable MSA9 keywrapping functions depending on cpu model
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Instead of adding a new machine option to disable/enable the keywrapping
options of pckmo (like for AES and DEA) we can now use the CPU model to
decide.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Collin Walling <walling@linux.ibm.com>
---
v1->v2: - enable vsie
	- also check if the host has the pckmo functions
 arch/s390/include/asm/kvm_host.h | 1 +
 arch/s390/kvm/kvm-s390.c         | 7 +++++++
 arch/s390/kvm/vsie.c             | 5 ++++-
 3 files changed, 12 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: fix KVM_CLEAR_DIRTY_LOG for memory slots of unaligned size
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
If a memory slot's size is not a multiple of 64 pages (256K), then
the KVM_CLEAR_DIRTY_LOG API is unusable: clearing the final 64 pages
either requires the requested page range to go beyond memslot->npages,
or requires log->num_pages to be unaligned, and kvm_clear_dirty_log_protect
requires log->num_pages to be both in range and aligned.

To allow this case, allow log->num_pages not to be a multiple of 64 if
it ends exactly on the last page of the slot.

Reported-by: Peter Xu <peterx@redhat.com>
Fixes: 98938aa8edd6 ("KVM: validate userspace input in kvm_clear_dirty_log_protect()", 2019-01-02)
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virtual/kvm/api.txt            | 5 +++--
 tools/testing/selftests/kvm/dirty_log_test.c | 4 ++--
 virt/kvm/kvm_main.c                          | 7 ++++---
 3 files changed, 9 insertions(+), 7 deletions(-)

```
#### [PATCH v4 1/4] KVM: lapic: Disable timer advancement if adaptive tuning goes haywire
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
To minimize the latency of timer interrupts as observed by the guest,
KVM adjusts the values it programs into the host timers to account for
the host's overhead of programming and handling the timer event.  Now
that the timer advancement is automatically tuned during runtime, it's
effectively unbounded by default, e.g. if KVM is running as L1 the
advancement can measure in hundreds of milliseconds.

Disable timer advancement if adaptive tuning yields an advancement of
more than 5000ns, as large advancements can break reasonable assumptions
of the guest, e.g. that a timer configured to fire after 1ms won't
arrive on the next instruction.  Although KVM busy waits to mitigate the
case of a timer event arriving too early, complications can arise when
shifting the interrupt too far, e.g. kvm-unit-test's vmx.interrupt test
will fail when its "host" exits on interrupts as KVM may inject the INTR
before the guest executes STI+HLT.   Arguably the unit test is "broken"
in the sense that delaying a timer interrupt by 1ms doesn't technically
guarantee the interrupt will arrive after STI+HLT, but it's a reasonable
assumption that KVM should support.

Furthermore, an unbounded advancement also effectively unbounds the time
spent busy waiting, e.g. if the guest programs a timer with a very large
delay.

5000ns is a somewhat arbitrary threshold.  When running on bare metal,
which is the intended use case, timer advancement is expected to be in
the general vicinity of 1000ns.  5000ns is high enough that false
positives are unlikely, while not being so high as to negatively affect
the host's performance/stability.

Note, a future patch will enable userspace to disable KVM's adaptive
tuning, which will allow priveleged userspace will to specifying an
advancement value in excess of this arbitrary threshold in order to
satisfy an abnormal use case.

Cc: Liran Alon <liran.alon@oracle.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Fixes: 3b8a5df6c4dc6 ("KVM: LAPIC: Tune lapic_timer_advance_ns automatically")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/lapic.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH] KVM: s390: Fix potential spectre warnings
##### From: Eric Farman <farman@linux.ibm.com>

```c
Fix some warnings from smatch:

arch/s390/kvm/interrupt.c:2310 get_io_adapter() warn: potential spectre issue 'kvm->arch.adapters' [r] (local cap)
arch/s390/kvm/interrupt.c:2341 register_io_adapter() warn: potential spectre issue 'dev->kvm->arch.adapters' [w]

Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
A recent patch from Paolo [1] acted as a reminder (thanks, Christian!)
that I had one for the s390 KVM code after some code reviews [2].
Let's clean that up.

[1] https://patchwork.kernel.org/patch/10895463/
[2] https://patchwork.kernel.org/patch/10788565/#22484223
---
 arch/s390/kvm/interrupt.c | 11 +++++++++--
 1 file changed, 9 insertions(+), 2 deletions(-)

```
#### [PATCH 1/7] KVM: s390: add vector enhancements facility 2 to cpumodel
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
If vector support is enabled, the vector enhancements facility 2
might also be enabled.
We can directly forward this facility to the guest if available
and VX is requested by user space.

Please note that user space can and will have the final decision
on the facility bits for a guests.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Collin Walling <walling@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
 arch/s390/kvm/kvm-s390.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [kvm-unit-tests PATCH] lib: Do not report failures when test passes
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

Currently, if a test is expected to fail, but surprisingly it passes,
the test is considered as "failing". This means that running on old
KVM-unit-tests on new KVM versions can falsely report failures.

Fix it and simplify the logic.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 lib/report.c | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: Initialize vmcs_root
##### From: nadav.amit@gmail.com

```c
From: Nadav Amit <nadav.amit@gmail.com>

vmcs_root was not initialized, so vmclear was run on the memory in which
the IDT resides. That is not good.

Signed-off-by: Nadav Amit <nadav.amit@gmail.com>
---
 x86/vmx.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v7 01/21] x86/common: Align cpu_caps_cleared and cpu_caps_set to unsigned long
##### From: Fenghua Yu <fenghua.yu@intel.com>

```c
cpu_caps_cleared[] and cpu_caps_set[] may not be aligned to unsigned long.
Atomic operations (i.e. set_bit() and clear_bit()) on the bitmaps may
access two cache lines (a.k.a. split lock) and cause the CPU to do a bus
lock to block all memory accesses from other processors to ensure
atomicity.

To avoid the overall performance degradation from the bus locking, align
the two variables to unsigned long.

Defining the variables as unsigned long may also fix the issue because
they will be naturally aligned to unsigned long. But that needs additional
code changes. Adding __aligned(unsigned long) is a simpler fix.

Signed-off-by: Fenghua Yu <fenghua.yu@intel.com>
Reviewed-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/kernel/cpu/common.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
