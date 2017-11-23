

#### [PATCH 0/3] KVM: Improving vCPU halt_poll_ns grow behavior
##### From: Nir Weiner <nir.weiner@oracle.com>

```c

grow_halt_poll_ns() sets the halt_poll_ns value for a vCPU when growing - It has 
significant effect on how vCPU performs. On the standard case, higher value is 
better - we will spend more time in the polling busyloop, handle 
events & interrupts faster and result in better performance for the VM. 
But on outliers it puts us in a busy loop that does nothing.

grow_halt_poll_ns() optimal algorithm changes between different workloads.
The changes in this patch series fixes 2 weird behaviors and exposes hard-coded
value which stands for the initial grow value in order to get a better
fine-tunning control. See the individual patches for more details.

Thanks,
Nir
---

Nir Weiner (3):
 KVM: grow_halt_poll_ns() should never shrink vCPU halt_poll_ns
 KVM: Expose the initial start value in grow_halt_poll_ns() as a module parameter
 KVM: Never start grow vCPU halt_poll_ns from value below halt_poll_ns_grow_start

 Documentation/virtual/kvm/halt-polling.txt |   37 +++++++++++--------
 arch/powerpc/kvm/book3s_hv.c               |   13 +++---
 include/linux/kvm_host.h                   |    1
 virt/kvm/kvm_main.c                        |   24 ++++++++----
 4 files changed, 47 insertions(+), 28 deletions(-)
```
