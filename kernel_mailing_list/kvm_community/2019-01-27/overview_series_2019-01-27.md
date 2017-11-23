#### [PATCH 1/3] KVM: grow_halt_poll_ns() should never shrink vCPU halt_poll_ns
##### From: Nir Weiner <nir.weiner@oracle.com>

```c
grow_halt_poll_ns() have a strange behavior in case
(halt_poll_ns_grow == 0) && (vcpu->halt_poll_ns != 0).

In this case, vcpu->halt_pol_ns will be set to zero.
That results in shrinking instead of growing.

Fix issue by changing grow_halt_poll_ns() to not modify
vcpu->halt_poll_ns in case halt_poll_ns_grow is zero

Reviewed-by: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Nir Weiner <nir.weiner@oracle.com>
Suggested-by: Liran Alon <liran.alon@oracle.com>
---
 arch/powerpc/kvm/book3s_hv.c | 5 ++++-
 virt/kvm/kvm_main.c          | 6 +++++-
 2 files changed, 9 insertions(+), 2 deletions(-)

```
