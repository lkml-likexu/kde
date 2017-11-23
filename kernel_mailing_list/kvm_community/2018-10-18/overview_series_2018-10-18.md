#### [PATCH] KVM/MMU: Always set cr4_pae when shadowing EPT pages
##### From: Christian Ehrhardt <lk@c--e.de>

```c
When shadowing EPT pages setup by L1 for a nested L2 guest
the value of the PAE bit %cr4 is irrelevant. However, in the
page role of a shadow page, cr4_pae basically means that the
shadowed page uses 64-bit page table entries. When shadowing
EPT page tables this is always the case. Thus set cr4_pae in
this case.

Similarly, calls to is_pae(vcpu) do not return useful information
when shadowing EPT tables. With the change above we can check
the cr4_pae bit in the current MMU's base_role instead. In most
cases this is the same as is_pae() anyway. However, when shadowing
EPT tables using is_pae() is wrong.

Signed-off-by: Christian Ehrhardt <lk@c--e.de>
---
 arch/x86/kvm/mmu.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH V7 3/5]  target-i386: add rtc 0x70 port as coalesced_pio
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 hw/timer/mc146818rtc.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [RESEND PATCH V6 1/5]  target/i386 : add coalesced pio support
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
add coalesced_pio's struct and KVM_CAP_COALESCED_PIO header.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 accel/kvm/kvm-all.c       |  4 ++--
 linux-headers/linux/kvm.h | 11 +++++++++--
 2 files changed, 11 insertions(+), 4 deletions(-)

```
#### [PATCH v2] KVM: x86: Only clear %dr6 if really neccessary
##### From: Christian Ehrhardt <lk@c--e.de>

```c
Change efdab992: "KVM: x86: fix escape of guest dr6 to the host"
has negative effects if Linux runs as the L1 guest in a nested
VM setup:

Each call to kvm_arch_vcpu_put causes an additional L1->L0 exit due
to the %dr6 write even if neither L1 nor L2 uses debug registers.
As the current hardware value of %dr6 is already in vcpu->arch.dr6
we can avoid the debug register write if all non-reserved bits have
their default value.

Update the comment and reformat it while there.

Signed-off-by: Christian Ehrhardt <lk@c--e.de>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
#### [PATCH v1 1/2] vfio: ccw: Merge BUSY and BOXED states
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
VFIO_CCW_STATE_BOXED and VFIO_CCW_STATE_BUSY have
identical actions for the same events.

Let's merge both into a single state to simplify the code.
We choose to keep VFIO_CCW_STATE_BUSY.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_fsm.c     | 7 +------
 drivers/s390/cio/vfio_ccw_private.h | 1 -
 2 files changed, 1 insertion(+), 7 deletions(-)

```
#### [PATCH] x86: Fix definition and use of DR6_RESERVED
##### From: Christian Ehrhardt <lk@c--e.de>

```c
Bit 16 in %dr6 (RTM) is no longer reserved.

Adjust the definition of DR6_RESERVED and provide new constants
DR6_INIT (moved from kvm_host.h) and DR_RTM. Fix existing users
of DR6_RESERVED that want DR6_INIT instead.

Signed-off-by: Christian Ehrhardt <lk@c--e.de>
---
 arch/x86/include/asm/kvm_host.h      | 1 -
 arch/x86/include/uapi/asm/debugreg.h | 5 ++++-
 arch/x86/kernel/process_32.c         | 2 +-
 arch/x86/kernel/process_64.c         | 2 +-
 4 files changed, 6 insertions(+), 4 deletions(-)

```
