#### [PATCH v7 11/16] x86/kvm: Add Hygon Dhyana support to KVM infrastructure
##### From: Pu Wen <puwen@hygon.cn>

```c
The Hygon Dhyana CPU has the SVM feature as AMD family 17h does.
So enable the KVM infrastructure support to it.

Signed-off-by: Pu Wen <puwen@hygon.cn>
Reviewed-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/kvm_emulate.h |  4 ++++
 arch/x86/include/asm/virtext.h     |  5 +++--
 arch/x86/kvm/emulate.c             | 11 ++++++++++-
 3 files changed, 17 insertions(+), 3 deletions(-)

```
#### [PATCH 02/35] target/i386: use cpu_reset_interrupt
##### From: "Emilio G. Cota" <cota@braap.org>

```c
From: Paolo Bonzini <pbonzini@redhat.com>

It will be changed to an atomic operation soon.

Cc: Richard Henderson <rth@twiddle.net>
Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Emilio G. Cota <cota@braap.org>
Reviewed-by: Richard Henderson <richard.henderson@linaro.org>
---
 target/i386/hax-all.c    |  4 ++--
 target/i386/hvf/x86hvf.c |  8 ++++----
 target/i386/kvm.c        | 14 +++++++-------
 target/i386/seg_helper.c | 13 ++++++-------
 target/i386/svm_helper.c |  2 +-
 target/i386/whpx-all.c   | 10 +++++-----
 6 files changed, 25 insertions(+), 26 deletions(-)

```
#### [PATCH v5 01/18] kvm: arm/arm64: Fix stage2_flush_memslot for 4 level page table
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c
So far we have only supported 3 level page table with fixed IPA of
40bits, where PUD is folded. With 4 level page tables, we need
to check if the PUD entry is valid or not. Fix stage2_flush_memslot()
to do this check, before walking down the table.

Acked-by: Christoffer Dall <cdall@kernel.org>
Acked-by: Marc Zyngier <marc.zyngier@arm.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
---
 virt/kvm/arm/mmu.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: nVMX: L0 should emulate instructions for L2From: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
When L0 enumerates support for an instruction not supported by the
physical CPU, it must emulate that instruction for L2 as well as for
L1. Take MOVBE, for example. If hardware reports that
CPUID.1:ECX.MOVBE[bit 22] is clear, but L0 sets the bit when emulating
CPUID for L1, then L0 is obligated to intercept #UD and emulate the
MOVBE instruction for L1. Furthermore, L0 is also obligated to
intercept #UD and emulate the MOVBE instruction for L2. Even if L1
chooses to intercept #UD, L0 must be prepared to decode the
instruction and emulate MOVBE before deciding to reflect the #UD
VM-exit to L1.

Rewriting the wrong hypercall instruction with the correct hypercall
instruction is not as clear-cut. One could argue that this is a
property of a kvm virtual CPU, and that L0 should always do
it. However, to avoid surprises, I've preserved the existing behavior
(right or wrong).

Signed-off-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx.c | 2 ++
 arch/x86/kvm/x86.c | 6 ++++++
 2 files changed, 8 insertions(+)

```
#### [PATCH/RFC v4 1/2] reset: Add support for dedicated reset controls
##### From: Geert Uytterhoeven <geert+renesas@glider.be>

```c
In some SoCs multiple hardware blocks may share a reset control.
The existing reset control API for shared resets will only assert such a
reset when the drivers for all hardware blocks agree.
The existing exclusive reset control API still allows to assert such a
reset, but that impacts all other hardware blocks sharing the reset.

Sometimes a driver needs to reset a specific hardware block, and be 100%
sure it has no impact on other hardware blocks.  This is e.g. the case
for virtualization with device pass-through, where the host wants to
reset any exported device before and after exporting it for use by the
guest, for isolation.

Hence a new flag for dedicated resets is added to the internal methods,
with a new public reset_control_get_dedicated() method, to obtain an
exclusive handle to a reset that is dedicated to one specific hardware
block.

This supports both DT-based and lookup-based reset controls.

Signed-off-by: Geert Uytterhoeven <geert+renesas@glider.be>
---
v4:
  - New.

Notes:
  - Dedicated lookup-based reset controls were not tested,
  - Several internal functions now take 3 boolean flags, and should
    probably be converted to take a bitmask instead,
  - I think __device_reset() should call __reset_control_get() with
    dedicated=true.  However, that will impact existing users,
  - Should a different error than -EINVAL be returned on failure?
---
 drivers/reset/core.c  | 76 ++++++++++++++++++++++++++++++++++++++-----
 include/linux/reset.h | 60 ++++++++++++++++++++++------------
 2 files changed, 107 insertions(+), 29 deletions(-)

```
