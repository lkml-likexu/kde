#### [PATCH net-next 1/3] virtio: introduce in order feature bit
##### From: Jason Wang <jasowang@redhat.com>

```c
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 include/uapi/linux/virtio_config.h | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH] KVM: VMX: re-add ple_gap module parameter
##### From: Luiz Capitulino <lcapitulino@redhat.com>

```c
Apparently, the ple_gap parameter was accidentally removed
by commit c8e88717cfc6b36bedea22368d97667446318291. Add it
back.

Signed-off-by: Luiz Capitulino <lcapitulino@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Babu Moger <babu.moger@amd.com>
---
 arch/x86/kvm/vmx.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v2 1/8] arm64: KVM: Make VHE Stage-2 TLB invalidation operations non-interruptible
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c
Contrary to the non-VHE version of the TLB invalidation helpers, the VHE
code  has interrupts enabled, meaning that we can take an interrupt in
the middle of such a sequence, and start running something else with
HCR_EL2.TGE cleared.

That's really not a good idea.

Take the heavy-handed option and disable interrupts in
__tlb_switch_to_guest_vhe, restoring them in __tlb_switch_to_host_vhe.
The latter also gain an ISB in order to make sure that TGE really has
taken effect.

Cc: stable@vger.kernel.org
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 arch/arm64/kvm/hyp/tlb.c | 35 +++++++++++++++++++++++++----------
 1 file changed, 25 insertions(+), 10 deletions(-)

```
