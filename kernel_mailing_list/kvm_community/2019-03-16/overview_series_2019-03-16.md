#### [PATCH] KVM: x86: check KVM availability when setting up pv tlb flush
##### From: Masanori Misono <m.misono760@gmail.com>

```c
kvm_setup_pv_tlb_flush() does not check if kvm_para_available() is true
unlike kvm_guest_init(). Therefore it may proceed even if
kvm_para_available() is 0 (e.g., when booting the VM with `qemu -cpu
host,kvm=off`). In this case, the pr_info message is confusing.
This fixed it.

Signed-off-by: Masanori Misono <m.misono760@gmail.com>
---
 arch/x86/kernel/kvm.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
