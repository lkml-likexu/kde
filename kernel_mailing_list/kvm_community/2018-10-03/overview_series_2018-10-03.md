#### [PATCH] kvm: nVMX: fix entry with pending interrupt if APICv is enabled
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Commit b5861e5cf2fcf83031ea3e26b0a69d887adf7d21 introduced a check on
the interrupt-window and NMI-window CPU execution controls in order to
inject an external interrupt vmexit before the first guest instruction
executes.  However, when APIC virtualization is enabled the host does not
need a vmexit in order to inject an interrupt at the next interrupt window;
instead, it just places the interrupt vector in RVI and the processor will
inject it as soon as possible.  Therefore, on machines with APICv it is
not enough to check the CPU execution controls: the same scenario can also
happen if RVI>0.

Fixes: b5861e5cf2fcf83031ea3e26b0a69d887adf7d21
Cc: Nikita Leshchenko <nikita.leshchenko@oracle.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Nikita Leshenko <nikita.leshchenko@oracle.com>
---
 arch/x86/kvm/vmx.c | 16 +++++++++++-----
 1 file changed, 11 insertions(+), 5 deletions(-)

```
