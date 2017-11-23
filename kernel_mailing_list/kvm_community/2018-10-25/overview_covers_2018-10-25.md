

#### [PATCH v2 0/6] x86/kernel/hyper-v: xmm fast hypercall
##### From: Isaku Yamahata <isaku.yamahata@gmail.com>

```c

This patch series implements xmm fast hypercall for hyper-v as guest
and kvm support as VMM.
With this patch, HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE without
gva list, HVCALL_FLUSH_VIRTUAL_ADDRESS_SPACE_EX(vcpu > 64) and
HVCALL_SEND_IPI_EX(vcpu > 64) can use xmm fast hypercall.

benchmark result:
At the moment, my test machine have only pcpu=4, ipi benchmark doesn't
make any behaviour change. So for now I measured the time of
hyperv_flush_tlb_others() by ktap with 'hardinfo -r -f text'.
the average of 5 runs are as follows.
(When large machine with pcpu > 64 is avaialble, ipi_benchmark result is
interesting. But not yet now.)

hyperv_flush_tlb_others() time by hardinfo -r -f text:

with path:       9931 ns
without patch:  11111 ns


With patch of 4bd06060762b, __send_ipi_mask() now uses fast hypercall
when possible. so in the case of vcpu=4. So I used kernel before the parch
to measure the effect of xmm fast hypercall with ipi_benchmark.
The following is the average of 100 runs.

ipi_benchmark: average of 100 runs without 4bd06060762b

with patch:
Dry-run                 0        495181
Self-IPI         11352737      21549999
Normal IPI      499400218     575433727
Broadcast IPI           0    1700692010
Broadcast lock          0    1663001374

without patch:
Dry-run                 0        607657
Self-IPI         10915950      21217644
Normal IPI      621712609     735015570
Broadcast IPI           0    2173803373
Broadcast lock          0    2150451543

Isaku Yamahata (6):
  x86/kernel/hyper-v: xmm fast hypercall as guest
  x86/hyperv: use hv_do_hypercall for __send_ipi_mask_ex()
  x86/hyperv: use hv_do_hypercall for flush_virtual_address_space_ex
  hyperv: use hv_do_hypercall instead of hv_do_fast_hypercall
  x86/kvm/hyperv: implement xmm fast hypercall
  local: hyperv: test ex hypercall

 arch/x86/hyperv/hv_apic.c           |  16 +++-
 arch/x86/hyperv/mmu.c               |  24 +++--
 arch/x86/hyperv/nested.c            |   2 +-
 arch/x86/include/asm/hyperv-tlfs.h  |   3 +
 arch/x86/include/asm/mshyperv.h     | 180 ++++++++++++++++++++++++++++++++++--
 arch/x86/kvm/hyperv.c               | 101 ++++++++++++++++----
 drivers/hv/connection.c             |   3 +-
 drivers/hv/hv.c                     |   3 +-
 drivers/pci/controller/pci-hyperv.c |   7 +-
 9 files changed, 291 insertions(+), 48 deletions(-)
```
#### [PATCH v2 0/2] vfio: ccw: VFIO CCW cleanup part1
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

The goal of the patches of this serie is to clarify the code
and to prepare for a better state/event handling.

Pierre Morel (2):
  vfio: ccw: Merge BUSY and BOXED states
  vfio: ccw: Register mediated device once all structures are
    initialized

 drivers/s390/cio/vfio_ccw_drv.c     | 8 ++++----
 drivers/s390/cio/vfio_ccw_fsm.c     | 7 +------
 drivers/s390/cio/vfio_ccw_private.h | 1 -
 3 files changed, 5 insertions(+), 11 deletions(-)
```
