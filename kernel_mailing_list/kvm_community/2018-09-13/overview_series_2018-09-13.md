#### [PATCH]  kvm:x86 :remove necessary recalculate_apic_map
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
In the previous code, the variable sw_apic_disabled influences
recalculate_apic_map. Now it never has accessed sw_apic_disabled
in recalculate_apic_map.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/lapic.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
