#### [PATCH v2 01/12] KVM: s390: leave AIs in IPM of GISA during vcpu_pre_run()
##### From: Michael Mueller <mimu@linux.ibm.com>

```c
Do not call __deliver_io() for adapter interruptions already
pending in the IPM. That is a double effort. They will
be processed as soon the vcpu control is given to SIE.

Signed-off-by: Michael Mueller <mimu@linux.ibm.com>
---
 arch/s390/kvm/interrupt.c | 54 ++++++++++++++++++++++-------------------------
 1 file changed, 25 insertions(+), 29 deletions(-)

```
#### [PATCH] kvm: vmx: Rename vmx_instruction_info to vm_exit_instruction_info
##### From: Jim Mattson <jmattson@google.com>

```c
I vaguely recall that at some time in the distant past, field 440EH of
the VMCS was referred to as the "VMX instruction-information field."
However, this field now provides instruction-information for string
PIO VM-exits, descriptor table VM-exits, RDRAND VM-exits, and RDSEED
VM-exits. The SDM now refers to it as the "VM-exit
instruction-information field." Since this field still is not yet
exposed as part of a userspace API, let's rename it to match the SDM.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/hyperv-tlfs.h |  2 +-
 arch/x86/include/asm/vmx.h         |  2 +-
 arch/x86/kvm/vmx.c                 | 96 ++++++++++++++++--------------
 arch/x86/kvm/vmx_evmcs.h           |  2 +-
 4 files changed, 54 insertions(+), 48 deletions(-)

```
#### [PATCH v2] x86/fpu: Disable BH while while loading FPU registers in __fpu__restore_sig()
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
The sequence
   fpu->initialized = 1; /* step A */
   preempt_disable();	 /* step B */
   fpu__restore(fpu);
   preempt_enable();

is racy in regard to a context switch.
For 32bit frames __fpu__restore_sig() prepares the FPU state within
fpu->state. To ensure that a context switch (switch_fpu_prepare() in
particular) does not modify fpu->state it uses fpu__drop() which sets
fpu->initializes to 0. With this change the CPU's FPU state is not saved
to fpu->state during a context switch. It then loads the state to
fpu->state from userland and ensures it sane. The new state is loaded
via fpu__restore(). The code sets then fpu->initializes to 1 in order
to avoid fpu__initialize() doing anything (overwrite the new state)
which is part of fpu__restore().
A context switch between step A and B would save CPU's current FPU
registers to fpu->state and overwrite the newly prepared state. This
looks like tiny race window but the Kernel Test Robot reported this back
in 2016 while we had lazy FPU support. Borislav Petkov made the link
between that report and another patch that has been posted.
Since the removal of the lazy FPU support, this race goes unnoticed
because the warning has been removed.

Use local_bh_disable() around the restore sequence to avoid the race. BH
needs to be disabled because BH is allowed to run (even with preemption
disabled) and might invoke kernel_fpu_begin().

Link: https://lkml.kernel.org/r/20160226074940.GA28911@pd.tnic
Cc: stable@vger.kernel.org
Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---
v1…v2: A more verbose commit as message.

 arch/x86/kernel/fpu/signal.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
