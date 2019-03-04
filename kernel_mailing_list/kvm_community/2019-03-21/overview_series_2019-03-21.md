#### [PATCH 01/24] x86/fpu: Remove fpu->initialized usage in __fpu__restore_sig()
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
This is a preparation for the removal of the ->initialized member in the
fpu struct.
__fpu__restore_sig() is deactivating the FPU via fpu__drop() and then
setting manually ->initialized followed by fpu__restore(). The result is
that it is possible to manipulate fpu->state and the state of registers
won't be saved/restored on a context switch which would overwrite
fpu->state.

Don't access the fpu->state while the content is read from user space
and examined / sanitized. Use a temporary kmalloc() buffer for the
preparation of the FPU registers and once the state is considered okay,
load it. Should something go wrong, return with an error and without
altering the original FPU registers.

The removal of "fpu__initialize()" is a nop because fpu->initialized is
already set for the user task.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Acked-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/fpu/signal.h |  2 +-
 arch/x86/kernel/fpu/regset.c      |  5 ++--
 arch/x86/kernel/fpu/signal.c      | 40 ++++++++++++-------------------
 3 files changed, 18 insertions(+), 29 deletions(-)

```
