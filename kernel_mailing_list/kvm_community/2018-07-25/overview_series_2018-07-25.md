#### [PATCH] Debugger extension: Add cr3 to debug/bp exception kvm_exit struct
##### From: Peter Shier <pshier@google.com>

```c
From: Ken Hofsass <hofsass@google.com>

Enables determining whether a debug/break event is associated with a guest
process of interest.

Signed-off-by: Ken Hofsass <hofsass@google.com>
Signed-off-by: Peter Shier <pshier@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/include/uapi/asm/kvm.h | 1 +
 arch/x86/kvm/vmx.c              | 2 ++
 arch/x86/kvm/x86.c              | 1 +
 include/uapi/linux/kvm.h        | 1 +
 4 files changed, 5 insertions(+)

```
#### [PATCH v3 1/6] KVM: hyperv: define VP assist page helpers
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From: Ladi Prosek <lprosek@redhat.com>

The state related to the VP assist page is still managed by the LAPIC
code in the pv_eoi field.

Signed-off-by: Ladi Prosek <lprosek@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/hyperv.c | 23 +++++++++++++++++++++--
 arch/x86/kvm/hyperv.h |  4 ++++
 arch/x86/kvm/lapic.c  |  4 ++--
 arch/x86/kvm/lapic.h  |  2 +-
 arch/x86/kvm/x86.c    |  2 +-
 5 files changed, 29 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: x86: Skip pae_root shadow allocation if tdp enabled
##### From: Liang Chen <liangchen.linux@gmail.com>

```c
Considering the fact that the pae_root shadow is not needed when
tdp is in use, skip the pae_root shadow page allocation to allow
mmu creation even not being able to obtain memory from DMA32
zone when particular cgroup cpuset.mems or mempolicy control is
applied.

Signed-off-by: Liang Chen <liangchen.linux@gmail.com>
---
 arch/x86/kvm/mmu.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH/RFC] drivers/vfio: Allow type-1 IOMMU instantiation with Renesas IPMMU-VMSA
##### From: Geert Uytterhoeven <geert+renesas@glider.be>

```c
The Renesas IPMMU-VMSA driver is compatible with the notion of a type-1
IOMMU in VFIO.

This patch allows guests to use the VFIO_IOMMU_TYPE1 API on hosts
equipped with a Renesas VMSA-compatible IPMMU.

Signed-off-by: Geert Uytterhoeven <geert+renesas@glider.be>
---
Lightly tested with sata_rcar on Renesas R-Car H3 ES2.0.

For testing, this patch and all prerequisites are available in the
topic/rcar3-virt-gpio-passthrough-v3 branch of my git repository at
git://git.kernel.org/pub/scm/linux/kernel/git/geert/renesas-drivers.git.
---
 drivers/vfio/Kconfig | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: s390: Add skey emulation fault handling
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
When doing skey emulation for huge guests, we now need to fault in
pmds, as we don't have PGSTES anymore to store them when we do not
have valid table entries.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---

Added skey fault handling for migration.
I'd be happy if people could have a look, it looks trivial, but it can
bite quite hard.

---
 arch/s390/kvm/kvm-s390.c |  15 +++++--
 arch/s390/kvm/priv.c     | 105 ++++++++++++++++++++++++++++++++---------------
 2 files changed, 83 insertions(+), 37 deletions(-)

```
#### [PATCH v4 1/1] KVM: PPC: Book3S HV: pack VCORE IDs to access full VCPU ID space
##### From: Sam Bobroff <sbobroff@linux.ibm.com>

```c
From: Sam Bobroff <sam.bobroff@au1.ibm.com>

It is not currently possible to create the full number of possible
VCPUs (KVM_MAX_VCPUS) on Power9 with KVM-HV when the guest uses less
threads per core than it's core stride (or "VSMT mode"). This is
because the VCORE ID and XIVE offsets to grow beyond KVM_MAX_VCPUS
even though the VCPU ID is less than KVM_MAX_VCPU_ID.

To address this, "pack" the VCORE ID and XIVE offsets by using
knowledge of the way the VCPU IDs will be used when there are less
guest threads per core than the core stride. The primary thread of
each core will always be used first. Then, if the guest uses more than
one thread per core, these secondary threads will sequentially follow
the primary in each core.

So, the only way an ID above KVM_MAX_VCPUS can be seen, is if the
VCPUs are being spaced apart, so at least half of each core is empty
and IDs between KVM_MAX_VCPUS and (KVM_MAX_VCPUS * 2) can be mapped
into the second half of each core (4..7, in an 8-thread core).

Similarly, if IDs above KVM_MAX_VCPUS * 2 are seen, at least 3/4 of
each core is being left empty, and we can map down into the second and
third quarters of each core (2, 3 and 5, 6 in an 8-thread core).

Lastly, if IDs above KVM_MAX_VCPUS * 4 are seen, only the primary
threads are being used and 7/8 of the core is empty, allowing use of
the 1, 5, 3 and 7 thread slots.

(Strides less than 8 are handled similarly.)

This allows the VCORE ID or offset to be calculated quickly from the
VCPU ID or XIVE server numbers, without access to the VCPU structure.

Signed-off-by: Sam Bobroff <sam.bobroff@au1.ibm.com>
---
Hello everyone,

Here's v4, addressing comments from Paul. See below for the changes.

Cheers,
Sam.

Patch set v4:
Patch 1/1: KVM: PPC: Book3S HV: pack VCORE IDs to access full VCPU ID space
* The block offsets are corrected for the vsmt=4 case (swap 3 and 5).
* The initial checks on the VCPU ID are changed to be against (KVM_MAX_VCPUS *
  emul_smt_mode) (a tigher bound).
* The BUG_ON()s in kvmppc_pack_vcpu_id() are changed to a WARN_ONCE(), and
  they'll return 0 in that case. KVM_MAX_VCPUS is another possible return value
  in this case, but it seemed safer to use 0 as it's not likely to cause a
  memory overrun if it's used. The warning shouldn't ever be triggered when
  VCPU IDs are allocate using the scheme that QEMU uses.
* The vcore creation code is adjusted to handle collisions by returning -EINVAL
  instead of bugging out.

Patch set v3:
Patch 1/1: KVM: PPC: Book3S HV: pack VCORE IDs to access full VCPU ID space

Patch set v2:
Patch 1/1: KVM: PPC: Book3S HV: pack VCORE IDs to access full VCPU ID space
* Corrected places in kvm/book3s_xive.c where IDs weren't packed.
* Because kvmppc_pack_vcpu_id() is only called on P9, there is no need to test "emul_smt_mode > 1", so remove it.
* Re-ordered block_offsets[] to be more ascending.
* Added more detailed description of the packing algorithm.

Patch set v1:
Patch 1/1: KVM: PPC: Book3S HV: pack VCORE IDs to access full VCPU ID space

 arch/powerpc/include/asm/kvm_book3s.h | 46 +++++++++++++++++++++++++++++++++++
 arch/powerpc/kvm/book3s_hv.c          | 25 ++++++++++++++-----
 arch/powerpc/kvm/book3s_xive.c        | 19 +++++++++------
 3 files changed, 77 insertions(+), 13 deletions(-)

```
