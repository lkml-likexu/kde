#### [PATCH 01/26] kvm: arm/arm64: Fix stage2_flush_memslot for 4 level page table
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
From: Suzuki K Poulose <suzuki.poulose@arm.com>

So far we have only supported 3 level page table with fixed IPA of
40bits, where PUD is folded. With 4 level page tables, we need
to check if the PUD entry is valid or not. Fix stage2_flush_memslot()
to do this check, before walking down the table.

Acked-by: Christoffer Dall <cdall@kernel.org>
Acked-by: Marc Zyngier <marc.zyngier@arm.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 virt/kvm/arm/mmu.c | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH kvmtool 1/2] kvm: Do not pause already paused vcpus
##### From: Julien Thierry <julien.thierry@arm.com>

```c
With the following sequence:
	kvm__pause();
	kvm__continue();
	kvm__pause();

There is a chance that not all paused threads have been resumed, and the
second kvm__pause will attempt to pause them again. Since the paused thread
is waiting to own the pause_lock, it won't write its second pause
notification. kvm__pause will be waiting for that notification while owning
pause_lock, so... deadlock.

Simple solution is not to try to pause thread that had not the chance to
resume.

Signed-off-by: Julien Thierry <julien.thierry@arm.com>
---
 kvm-cpu.c | 4 +---
 kvm.c     | 5 ++++-
 2 files changed, 5 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Don't use streamlined entry path on early POWER9 chips
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
This disables the use of the streamlined entry path for radix guests
on early POWER9 chips that need the workaround added in commit
a25bd72badfa ("powerpc/mm/radix: Workaround prefetch issue with KVM",
2017-07-24), because the streamlined entry path does not include
that workaround.  This also means that we can't do nested HV-KVM
on those chips.

Since the chips that need that workaround are the same ones that can't
run both radix and HPT guests at the same time on different threads of
a core, we use the existing 'no_mixing_hpt_and_radix' variable that
identifies those chips to identify when we can't use the new guest
entry path, and when we can't do nested virtualization.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_hv.c | 13 +++++++++++--
 1 file changed, 11 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: PPC: Use exported tb_to_ns() function in decrementer emulation
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
This changes the KVM code that emulates the decrementer function to do
the conversion of decrementer values to time intervals in nanoseconds
by calling the tb_to_ns() function exported by the powerpc timer code,
in preference to open-coded arithmetic using values from the
decrementer_clockevent struct.  Similarly, the HV-KVM code that did
the same conversion using arithmetic on tb_ticks_per_sec also now
uses tb_to_ns().

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_hv.c | 3 +--
 arch/powerpc/kvm/emulate.c   | 6 ++----
 2 files changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH] vfio-mdev/samples: Use u8 instead of char for handle functions
##### From: Nathan Chancellor <natechancellor@gmail.com>

```c
Clang warns:

samples/vfio-mdev/mtty.c:592:39: warning: implicit conversion from 'int'
to 'char' changes value from 162 to -94 [-Wconstant-conversion]
                *buf = UART_MSR_DSR | UART_MSR_DDSR | UART_MSR_DCD;
                     ~ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~
1 warning generated.

Turns out that all uses of buf in this function ultimately end up stored
or cast to an unsigned type. Just use u8, which has the same number of
bits but can store this larger number so Clang no longer warns.

Signed-off-by: Nathan Chancellor <natechancellor@gmail.com>
---
 samples/vfio-mdev/mtty.c | 26 +++++++++++++-------------
 1 file changed, 13 insertions(+), 13 deletions(-)

```
#### [PATCH] x86/kvm/nVMX: tweak shadow fields
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
It seems we have some leftovers from times when 'unrestricted guest'
wasn't exposed to L1. Stop shadowing GUEST_CS_{BASE,LIMIT,AR_SELECTOR}
and GUEST_ES_BASE, shadow GUEST_SS_AR_BYTES as it was found that some
hypervisors (e.g. Hyper-V without Enlightened VMCS) access it pretty
often.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx.c               | 10 +++++-----
 arch/x86/kvm/vmx_shadow_fields.h |  5 +----
 2 files changed, 6 insertions(+), 9 deletions(-)

```
