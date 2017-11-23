#### [PATCH 1/1] ARM: KVM: Correctly order SGI register entries in the cp15 array
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
The ICC_ASGI1R and ICC_SGI0R register entries in the cp15 array
are not correctly ordered, leading to a BUG() at boot time.

Move them to their natural location.

Fixes: 3e8a8a50c7ef ("KVM: arm: vgic-v3: Add support for ICC_SGI0R and ICC_ASGI1R accesses")
Reported-by: Florian Fainelli <f.fainelli@gmail.com>
Tested-by: Florian Fainelli <f.fainelli@gmail.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm/kvm/coproc.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: Start populating /sys/hypervisor with KVM entries
##### From: Filippo Sironi <sironi@amazon.de>

```c
Start populating /sys/hypervisor with KVM entries when we're running on
KVM. This is to replicate functionality that's available when we're
running on Xen.

Let's start with /sys/hypervisor/uuid, which users prefer over
/sys/devices/virtual/dmi/id/product_uuid as a way to recognize a virtual
machine, since it's also available when running on Xen HVM and on Xen PV
and, on top of that doesn't require root privileges by default.

Signed-off-by: Filippo Sironi <sironi@amazon.de>
---
 drivers/Kconfig              |  2 ++
 drivers/Makefile             |  2 ++
 drivers/kvm/Kconfig          | 14 ++++++++++++++
 drivers/kvm/Makefile         |  1 +
 drivers/kvm/sys-hypervisor.c | 26 ++++++++++++++++++++++++++
 5 files changed, 45 insertions(+)
 create mode 100644 drivers/kvm/Kconfig
 create mode 100644 drivers/kvm/Makefile
 create mode 100644 drivers/kvm/sys-hypervisor.c

```
#### [kvm-unit-tests PATCH] x86: VMX: Fix EPT MMIO access failed
##### From: Li Zhijian <zhijianx.li@intel.com>

```c
0Day robot noticed that "FAIL: EPT - MMIO access" since kernel commit
d1766202: ("x86/kvm/lapic: always disable MMIO interface in x2APIC mode")

As the changelog said, MMIO accessing is disabled in x2APIC mode
which is a common feature in modern CPUs, so disable x2APIC mode when the tests
try to access lapic MMIO accrodingly

CC: Rong Chen <rong.a.chen@intel.com>
CC: Philip Li <philip.li@intel.com>
CC: 0day robot <lkp@intel.com>
CC: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Li Zhijian <zhijianx.li@intel.com>
---
 x86/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] KVM: x86: support CONFIG_KVM_AMD=y with CONFIG_CRYPTO_DEV_CCP_DD=m
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
SEV requires access to the AMD cryptographic device APIs, and this
does not work when KVM is builtin and the crypto driver is a module.
Actually the Kconfig conditions for CONFIG_KVM_AMD_SEV try to disable
SEV in that case, but it does not work because the actual crypto
calls are not culled, only sev_hardware_setup() is.

This patch adds two CONFIG_KVM_AMD_SEV checks that gate all the remaining
SEV code; it fixes this particular configuration, and drops 5 KiB of
code when CONFIG_KVM_AMD_SEV=n.

Reported-by: Guenter Roeck <linux@roeck-us.net>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH 1/2] KVM: refine the comment of function gfn_to_hva_memslot_prot()
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
The original comment is little hard to understand.

No functional change, just amend the comment a little.

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
---
 virt/kvm/kvm_main.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH v2] KVM: LAPIC: Tune lapic_timer_advance_ns automatically
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

In cloud environment, lapic_timer_advance_ns is needed to be tuned for every CPU 
generations, and every host kernel versions(the kvm-unit-tests/tscdeadline_latency.flat 
is 5700 cycles for upstream kernel and 9600 cycles for our 3.10 product kernel, 
both preemption_timer=N, Skylake server).

This patch adds the capability to automatically tune lapic_timer_advance_ns
step by step, the initial value is 1000ns as 'commit d0659d946be0 ("KVM: x86: 
add option to advance tscdeadline hrtimer expiration")' recommended, it will be 
reduced when it is too early, and increased when it is too late. The guest_tsc 
and tsc_deadline are hard to equal, so we assume we are done when the delta 
is within a small scope e.g. 100 cycles. This patch reduces latency 
(kvm-unit-tests/tscdeadline_latency, busy waits, preemption_timer enabled)
from ~2600 cyles to ~1200 cyles on our Skylake server.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * converts between guest TSC units to host nanoseconds correctly
 * put hard-coded numbers to #define 

 arch/x86/kvm/lapic.c | 25 ++++++++++++++++++++++++-
 arch/x86/kvm/x86.c   |  2 +-
 2 files changed, 25 insertions(+), 2 deletions(-)

```
#### [PATCH v2]  kvm-unit-test: add a fetch insn test case
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
the test case is for "kvm/x86: fix a fetch fault emulation" .
KVM internal error. Suberror: 1
emulation failure
RAX=0000000000463fe8 RBX=ffffffffffffd000 RCX=000000000000000c RDX=0000000000464006
RSI=0000000000000001 RDI=0000000000463000 RBP=0000000000452ce0 RSP=0000000000452c78
R8 =0000000000000000 R9 =0000000000410d7f R10=0000000000000000 R11=0000000000000000
R12=ffffffffffffe000 R13=1111111111111111 R14=3333333333333333 R15=00000000a06d39e8
RIP=ffffffffffffd000 RFL=00010002 [-------] CPL=0 II=0 A20=1 SMM=0 HLT=0
ES =0010 0000000000000000 ffffffff 00c09300 DPL=0 DS   [-WA]
CS =0008 0000000000000000 ffffffff 00a09b00 DPL=0 CS64 [-RA]
SS =0010 0000000000000000 ffffffff 00c09300 DPL=0 DS   [-WA]

v1 --> v2:
   simply some functions.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 lib/vmalloc.c  | 18 ++++++++++++++----
 lib/vmalloc.h  |  9 +++++++--
 lib/x86/io.c   |  2 +-
 lib/x86/vm.c   |  5 +++++
 x86/emulator.c | 52 +++++++++++++++++++++++++++++++++++++++++++++++++---
 5 files changed, 76 insertions(+), 10 deletions(-)

```
