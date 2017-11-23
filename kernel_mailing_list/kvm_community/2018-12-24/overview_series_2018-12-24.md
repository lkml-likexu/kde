#### [RESEND PATCH]  kvm/x86: propagate fetch fault into guest
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
When handling ept misconfig exit, it will call emulate instruction
with insn_len = 0. The decode instruction function may return a fetch
fault and should propagate to guest.

The problem will result to emulation fail.
KVM internal error. Suberror: 1
emulation failure
EAX=f81a0024 EBX=f6a07000 ECX=f6a0737c EDX=f8be0118
ESI=f6a0737c EDI=00000021 EBP=f6929f98 ESP=f6929f98
EIP=f8bdd141 EFL=00010086 [--S--P-] CPL=0 II=0 A20=1 SMM=0 HLT=0
ES =007b 00000000 ffffffff 00c0f300 DPL=3 DS   [-WA]
CS =0060 00000000 ffffffff 00c09b00 DPL=0 CS32 [-RA]
SS =0068 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
DS =007b 00000000 ffffffff 00c0f300 DPL=3 DS   [-WA]
FS =00d8 2c044000 ffffffff 00809300 DPL=0 DS16 [-WA]
GS =0033 081a44c8 01000fff 00d0f300 DPL=3 DS   [-WA]
LDT=0000 00000000 ffffffff 00000000
TR =0080 f6ea0c80 0000206b 00008b00 DPL=0 TSS32-busy
GDT=     f6e99000 000000ff
IDT=     fffbb000 000007ff
CR0=80050033 CR2=b757d000 CR3=35d31000 CR4=001406d0

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/emulate.c | 5 ++++-
 arch/x86/kvm/x86.c     | 4 +++-
 2 files changed, 7 insertions(+), 2 deletions(-)

```
