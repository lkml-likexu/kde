#### [PATCH v3 1/5] bitops: introduce change_bit_atomic
##### From: guangrong.xiao@gmail.com

```c
From: Xiao Guangrong <xiaoguangrong@tencent.com>

It will be used by threaded workqueue

Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
---
 include/qemu/bitops.h | 13 +++++++++++++
 1 file changed, 13 insertions(+)

```
#### [PATCH] x86: fix -Wmissing-prototypes warning
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
We may get -Wmissing-prototypes warnings when building
kernel with W=1, it's better to fix them as global function
signature can be changed and caller who use the old unchanged
prototypes will be hosed.

This patch fixes most of -Wmissing-prototypes warnings which
are in the root directory of arch/x86/kernel, not including
the subdirectories.

These are the warnings fixed in this patch:
arch/x86/kernel/signal.c:865:17: warning: no previous prototype for ‘sys32_x32_rt_sigreturn’ [-Wmissing-prototypes]
arch/x86/kernel/signal_compat.c:164:6: warning: no previous prototype for ‘sigaction_compat_abi’ [-Wmissing-prototypes]
arch/x86/kernel/traps.c:625:46: warning: no previous prototype for ‘sync_regs’ [-Wmissing-prototypes]
arch/x86/kernel/traps.c:640:24: warning: no previous prototype for ‘fixup_bad_iret’ [-Wmissing-prototypes]
arch/x86/kernel/traps.c:929:13: warning: no previous prototype for ‘trap_init’ [-Wmissing-prototypes]
arch/x86/kernel/irq.c:270:28: warning: no previous prototype for ‘smp_x86_platform_ipi’ [-Wmissing-prototypes]
arch/x86/kernel/irq.c:301:16: warning: no previous prototype for ‘smp_kvm_posted_intr_ipi’ [-Wmissing-prototypes]
arch/x86/kernel/irq.c:314:16: warning: no previous prototype for ‘smp_kvm_posted_intr_wakeup_ipi’ [-Wmissing-prototypes]
arch/x86/kernel/irq.c:328:16: warning: no previous prototype for ‘smp_kvm_posted_intr_nested_ipi’ [-Wmissing-prototypes]
arch/x86/kernel/irq_work.c:16:28: warning: no previous prototype for ‘smp_irq_work_interrupt’ [-Wmissing-prototypes]
arch/x86/kernel/irqinit.c:79:13: warning: no previous prototype for ‘init_IRQ’ [-Wmissing-prototypes]
arch/x86/kernel/quirks.c:672:13: warning: no previous prototype for ‘early_platform_quirks’ [-Wmissing-prototypes]
arch/x86/kernel/tsc.c:1499:15: warning: no previous prototype for ‘calibrate_delay_is_known’ [-Wmissing-prototypes]
arch/x86/kernel/process.c:653:13: warning: no previous prototype for ‘arch_post_acpi_subsys_init’ [-Wmissing-prototypes]
arch/x86/kernel/process.c:717:15: warning: no previous prototype for ‘arch_randomize_brk’ [-Wmissing-prototypes]
arch/x86/kernel/process.c:784:6: warning: no previous prototype for ‘do_arch_prctl_common’ [-Wmissing-prototypes]
arch/x86/kernel/reboot.c:869:6: warning: no previous prototype for ‘nmi_panic_self_stop’ [-Wmissing-prototypes]
arch/x86/kernel/smp.c:176:27: warning: no previous prototype for ‘smp_reboot_interrupt’ [-Wmissing-prototypes]
arch/x86/kernel/smp.c:260:28: warning: no previous prototype for ‘smp_reschedule_interrupt’ [-Wmissing-prototypes]
arch/x86/kernel/smp.c:281:28: warning: no previous prototype for ‘smp_call_function_interrupt’ [-Wmissing-prototypes]
arch/x86/kernel/smp.c:291:28: warning: no previous prototype for ‘smp_call_function_single_interrupt’ [-Wmissing-prototypes]
arch/x86/kernel/ftrace.c:840:6: warning: no previous prototype for ‘arch_ftrace_update_trampoline’ [-Wmissing-prototypes]
arch/x86/kernel/ftrace.c:934:7: warning: no previous prototype for ‘arch_ftrace_trampoline_func’ [-Wmissing-prototypes]
arch/x86/kernel/ftrace.c:946:6: warning: no previous prototype for ‘arch_ftrace_trampoline_free’ [-Wmissing-prototypes]
arch/x86/kernel/crash.c:114:6: warning: no previous prototype for ‘crash_smp_send_stop’ [-Wmissing-prototypes]
arch/x86/kernel/crash.c:351:5: warning: no previous prototype for ‘crash_setup_memmap_entries’ [-Wmissing-prototypes]
arch/x86/kernel/crash.c:424:5: warning: no previous prototype for ‘crash_load_segments’ [-Wmissing-prototypes]
arch/x86/kernel/machine_kexec_64.c:372:7: warning: no previous prototype for ‘arch_kexec_kernel_image_load’ [-Wmissing-prototypes]
arch/x86/kernel/paravirt-spinlocks.c:12:16: warning: no previous prototype for ‘__native_queued_spin_unlock’ [-Wmissing-prototypes]
arch/x86/kernel/paravirt-spinlocks.c:18:6: warning: no previous prototype for ‘pv_is_native_spin_unlock’ [-Wmissing-prototypes]
arch/x86/kernel/paravirt-spinlocks.c:24:16: warning: no previous prototype for ‘__native_vcpu_is_preempted’ [-Wmissing-prototypes]
arch/x86/kernel/paravirt-spinlocks.c:30:6: warning: no previous prototype for ‘pv_is_native_vcpu_is_preempted’ [-Wmissing-prototypes]
arch/x86/kernel/kvm.c:258:1: warning: no previous prototype for ‘do_async_page_fault’ [-Wmissing-prototypes]
arch/x86/kernel/jailhouse.c:200:6: warning: no previous prototype for ‘jailhouse_paravirt’ [-Wmissing-prototypes]
arch/x86/kernel/check.c:91:13: warning: no previous prototype for ‘setup_bios_corruption_check’ [-Wmissing-prototypes]
arch/x86/kernel/check.c:139:6: warning: no previous prototype for ‘check_for_bios_corruption’ [-Wmissing-prototypes]
arch/x86/kernel/devicetree.c:32:13: warning: no previous prototype for ‘early_init_dt_scan_chosen_arch’ [-Wmissing-prototypes]
arch/x86/kernel/devicetree.c:42:13: warning: no previous prototype for ‘add_dtb’ [-Wmissing-prototypes]
arch/x86/kernel/devicetree.c:108:6: warning: no previous prototype for ‘x86_of_pci_init’ [-Wmissing-prototypes]
arch/x86/kernel/devicetree.c:314:13: warning: no previous prototype for ‘x86_dtb_init’ [-Wmissing-prototypes]
arch/x86/kernel/tracepoint.c:16:5: warning: no previous prototype for ‘trace_pagefault_reg’ [-Wmissing-prototypes]
arch/x86/kernel/tracepoint.c:22:6: warning: no previous prototype for ‘trace_pagefault_unreg’ [-Wmissing-prototypes]
arch/x86/kernel/head64.c:113:22: warning: no previous prototype for ‘__startup_64’ [-Wmissing-prototypes]
arch/x86/kernel/head64.c:262:15: warning: no previous prototype for ‘__startup_secondary_64’ [-Wmissing-prototypes]
arch/x86/kernel/head64.c:350:12: warning: no previous prototype for ‘early_make_pgtable’ [-Wmissing-prototypes]

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
 arch/x86/include/asm/crash.h       | 1 +
 arch/x86/include/asm/efi.h         | 2 --
 arch/x86/include/asm/irq.h         | 7 +++++++
 arch/x86/include/asm/irq_work.h    | 1 +
 arch/x86/include/asm/kvm_para.h    | 1 +
 arch/x86/include/asm/paravirt.h    | 5 +++++
 arch/x86/include/asm/reboot.h      | 1 +
 arch/x86/include/asm/setup.h       | 5 +++++
 arch/x86/include/asm/sighandling.h | 5 +++++
 arch/x86/include/asm/smp.h         | 6 ++++++
 arch/x86/include/asm/traps.h       | 4 ++++
 arch/x86/include/asm/tsc.h         | 1 +
 arch/x86/kernel/check.c            | 3 ++-
 arch/x86/kernel/crash.c            | 1 +
 arch/x86/kernel/devicetree.c       | 1 +
 arch/x86/kernel/jailhouse.c        | 1 +
 arch/x86/kernel/process.c          | 3 +++
 arch/x86/kernel/quirks.c           | 1 +
 arch/x86/kernel/tracepoint.c       | 1 +
 include/linux/efi.h                | 2 ++
 include/linux/ftrace.h             | 3 +++
 include/linux/kexec.h              | 1 +
 include/linux/of_fdt.h             | 1 +
 include/linux/ptrace.h             | 1 +
 24 files changed, 55 insertions(+), 3 deletions(-)

```
