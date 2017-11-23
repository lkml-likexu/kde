#### [PATCH] kvm: x86: Add AMD's EX_CFG to the list of ignored MSRs
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
Some guests OSes (including Windows 10) write to MSR 0xc001102c
on some cases (possibly while trying to apply a CPU errata).
Make KVM ignore reads and writes to that MSR, so the guest won't
crash.

The MSR is documented as "Execution Unit Configuration (EX_CFG)",
at AMD's "BIOS and Kernel Developer's Guide (BKDG) for AMD Family
15h Models 00h-0Fh Processors".

Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
 arch/x86/include/asm/msr-index.h | 1 +
 arch/x86/kvm/x86.c               | 2 ++
 2 files changed, 3 insertions(+)

```
