

#### [PATCH v3 0/2] vfio: add vgpu edid support
##### From: Gerd Hoffmann <kraxel@redhat.com>

```c

Update vfio api, adapt mbochs sample driver.

v3: refine vfio region layout, improve documentation.
v2: try vfio region approach.

Gerd Hoffmann (2):
  vfio: add edid api for display (vgpu) devices.
  vfio: add edid support to mbochs sample driver

 include/uapi/linux/vfio.h  |  50 +++++++++++++++++
 samples/vfio-mdev/mbochs.c | 136 ++++++++++++++++++++++++++++++++++++++-------
 2 files changed, 167 insertions(+), 19 deletions(-)
```
#### [RFC PATCH 00/32] KVM: PPC: Book3S HV: Nested HV virtualization
##### From: Paul Mackerras <paulus@ozlabs.org>

```c

This patch series implements nested virtualization in the KVM-HV
module for radix guests on POWER9 systems.  Unlike PR KVM, nested
guests are able to run in supervisor mode, meaning that performance is
much better than with PR KVM, and is very close to the performance of
a non-nested guest for most things.

The way this works is that each nested guest is also a guest of the
real hypervisor, also known as the level 0 or L0 hypervisor, which
runs in the CPU's hypervisor mode.  Its guests are at level 1, and
when a L1 system wants to run a nested guest, it performs hypercalls
to L0 to set up a virtual partition table in its (L1's) memory and to
enter the L2 guest.  The L0 hypervisor maintains a shadow
partition-scoped page table for the L2 guest and demand-faults entries
into it by translating the L1 real addresses in the partition-scoped
page table in L1 memory into L0 real addresses and puts them in the
shadow partition-scoped page table for L2.

Essentially what this is doing is providing L1 with the ability to do
(some) hypervisor functions using a mix of instruction emulation and
paravirtualization.

Along the way, this implements a new guest entry/exit path for radix
guests on POWER9 systems which is written almost entirely in C and
does not do any of the inter-thread coordination that the existing
entry/exit path does.  It is only used for radix guests and when
indep_threads_mode=Y (the default).

The limitations of the current implementation are:

- Host and all nested hypervisors and their guests must be in radix
  mode.

- Nested hypervisors cannot use indep_threads_mode=N.

- If the host (i.e. the L0 hypervisor) has indep_threads_mode=N then
  only one nested vcpu can be run on any core at any given time; the
  secondary threads will do nothing.

Paul.

 Documentation/virtual/kvm/api.txt                  |   15 +
 arch/powerpc/include/asm/asm-prototypes.h          |   21 +
 arch/powerpc/include/asm/book3s/64/mmu-hash.h      |   12 +
 .../powerpc/include/asm/book3s/64/tlbflush-radix.h |    1 +
 arch/powerpc/include/asm/hvcall.h                  |   62 +
 arch/powerpc/include/asm/kvm_asm.h                 |    4 +-
 arch/powerpc/include/asm/kvm_book3s.h              |   48 +-
 arch/powerpc/include/asm/kvm_book3s_64.h           |   45 +-
 arch/powerpc/include/asm/kvm_book3s_asm.h          |    3 +
 arch/powerpc/include/asm/kvm_booke.h               |    4 +-
 arch/powerpc/include/asm/kvm_host.h                |   16 +-
 arch/powerpc/include/asm/kvm_ppc.h                 |    4 +
 arch/powerpc/include/asm/ppc-opcode.h              |    1 +
 arch/powerpc/include/asm/reg.h                     |    2 +
 arch/powerpc/include/uapi/asm/kvm.h                |    1 +
 arch/powerpc/kernel/asm-offsets.c                  |    5 +-
 arch/powerpc/kernel/cpu_setup_power.S              |    4 +-
 arch/powerpc/kvm/Makefile                          |    3 +-
 arch/powerpc/kvm/book3s.c                          |   43 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c                |    7 +-
 arch/powerpc/kvm/book3s_64_mmu_radix.c             |  694 ++++++++---
 arch/powerpc/kvm/book3s_emulate.c                  |   13 +-
 arch/powerpc/kvm/book3s_hv.c                       |  897 +++++++++++++--
 arch/powerpc/kvm/book3s_hv_builtin.c               |   92 +-
 arch/powerpc/kvm/book3s_hv_interrupts.S            |   95 +-
 arch/powerpc/kvm/book3s_hv_nested.c                | 1199 ++++++++++++++++++++
 arch/powerpc/kvm/book3s_hv_ras.c                   |   10 +
 arch/powerpc/kvm/book3s_hv_rm_xics.c               |   13 +-
 arch/powerpc/kvm/book3s_hv_rmhandlers.S            |  805 +++++++------
 arch/powerpc/kvm/book3s_hv_tm.c                    |    6 +-
 arch/powerpc/kvm/book3s_hv_tm_builtin.c            |    5 +-
 arch/powerpc/kvm/book3s_pr.c                       |    5 +-
 arch/powerpc/kvm/book3s_xics.c                     |   14 +-
 arch/powerpc/kvm/book3s_xive.c                     |   63 +
 arch/powerpc/kvm/book3s_xive_template.c            |    8 -
 arch/powerpc/kvm/bookehv_interrupts.S              |    8 +-
 arch/powerpc/kvm/emulate_loadstore.c               |    1 -
 arch/powerpc/kvm/powerpc.c                         |   12 +
 arch/powerpc/kvm/tm.S                              |  250 ++--
 arch/powerpc/kvm/trace_book3s.h                    |    1 -
 arch/powerpc/mm/tlb-radix.c                        |    9 +
 include/uapi/linux/kvm.h                           |    1 +
 tools/perf/arch/powerpc/util/book3s_hv_exits.h     |    1 -
 43 files changed, 3636 insertions(+), 867 deletions(-)
```
#### [PATCH 0/2]  virtio/s390: fix some races in virtio-ccw
##### From: Halil Pasic <pasic@linux.ibm.com>

```c

The trigger for the series is this bug report:
https://bugs.launchpad.net/ubuntu/+source/linux/+bug/1788432

Changelog:
RFC -> v1:
* do mutual exclusion on a per device basis in ccw_io_helper() 

Halil Pasic (2):
  virtio/s390: avoid race on vcdev->config
  virtio/s390: fix race in ccw_io_helper()

 drivers/s390/virtio/virtio_ccw.c | 17 ++++++++++++++---
 1 file changed, 14 insertions(+), 3 deletions(-)
```
#### [PATCH v2 0/2] Refactor ccw_io_region
##### From: Eric Farman <farman@linux.ibm.com>

```c

Cornelia, I think you were thinking something like this?

Patch one does the refactoring to use ccw_io_region as a pointer
rather than a struct embedded in vfio_ccw_private, while patch two
is almost identical to the initial patch that I sent.

Obviously I had to remove references to the vfio_ccw_private struct
since ccw_io_region is a pointer, but the concept is the same.

Eric Farman (2):
  s390/cio: Convert ccw_io_region to pointer
  s390/cio: Refactor alloc of ccw_io_region

 drivers/s390/cio/vfio_ccw_drv.c     | 24 +++++++++++++++++++++++-
 drivers/s390/cio/vfio_ccw_fsm.c     |  6 +++---
 drivers/s390/cio/vfio_ccw_ops.c     |  4 ++--
 drivers/s390/cio/vfio_ccw_private.h |  2 +-
 4 files changed, 29 insertions(+), 7 deletions(-)
```
