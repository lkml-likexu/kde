

#### [PATCH v2 0/3] KVM: LAPIC: Implement Exitless Timer
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c

Dedicated instances are currently disturbed by unnecessary jitter due 
to the emulated lapic timers fire on the same pCPUs which vCPUs resident.
There is no hardware virtual timer on Intel for guest like ARM. Both 
programming timer in guest and the emulated timer fires incur vmexits.
This patchset tries to avoid vmexit which is incurred by the emulated 
timer fires in dedicated instance scenario. 

When nohz_full is enabled in dedicated instances scenario, the unpinned 
timer will be moved to the nearest busy housekeepers after commit 444969223c8
("sched/nohz: Fix affine unpinned timers mess"). However, KVM always makes 
lapic timer pinned to the pCPU which vCPU residents, the reason is explained 
by commit 61abdbe0 (kvm: x86: make lapic hrtimer pinned). Actually, these 
emulated timers can be offload to the housekeeping cpus since APICv 
is really common in recent years. The guest timer interrupt is injected by 
posted-interrupt which is delivered by housekeeping cpu once the emulated 
timer fires. 

The host admin should fine tuned, e.g. dedicated instances scenario w/ 
nohz_full cover the pCPUs which vCPUs resident, several pCPUs surplus 
for housekeeping, disable mwait/hlt/pause vmexits to occupy the pCPUs, 
fortunately preemption timer is disabled after mwait is exposed to 
guest which makes emulated timer offload can be possible. 
3%~5% redis performance benefit can be observed on Skylake server.

v1 -> v2:
 * check vcpu_halt_in_guest
 * move module parameter from kvm-intel to kvm
 * add housekeeping_enabled
 * rename apic_timer_expired_pi to kvm_apic_inject_pending_timer_irqs

Wanpeng Li (3):
  KVM: LAPIC: Make lapic timer unpinned when timer is injected by
    posted-interrupt
  KVM: LAPIC: lapic timer interrupt is injected by posted interrupt
  KVM: LAPIC: Ignore timer migration when lapic timer is injected by
    posted-interrupt

 arch/x86/kvm/lapic.c            | 55 ++++++++++++++++++++++++++++++++---------
 arch/x86/kvm/x86.c              |  5 ++++
 arch/x86/kvm/x86.h              |  7 ++++++
 include/linux/sched/isolation.h |  2 ++
 kernel/sched/isolation.c        |  6 +++++
 5 files changed, 63 insertions(+), 12 deletions(-)
```
#### [PATCH v6 00/12] Guest LBR Enabling
##### From: Wei Wang <wei.w.wang@intel.com>

```c

Last Branch Recording (LBR) is a performance monitor unit (PMU) feature
on Intel CPUs that captures branch related info. This patch series enables
this feature to KVM guests.

Here is a conclusion of the fundamental methods that we use:
1) the LBR feature is enabled per guest via QEMU setting of
   KVM_CAP_X86_GUEST_LBR;
2) the LBR stack is passed through to the guest for direct accesses after
   the guest's first access to any of the lbr related MSRs;
3) the host will help save/resotre the LBR stack when the vCPU is
   scheduled out/in.

ChangeLog:
    - perf/x86:
        - Patch 7:
                - define "no counter" as a new PERF_EV cap and keep it
                  used in the kernel, instead of esposing it in the user
                  ABI (if defined in perf_event_attr)
                - add a new API, perf_event_create, which can be used to
                  create a perf event without counter assignment (e.g.
                  a perf event simply to get the perf core's help of
                  switching lbr stack on thread switching, please see
                  patch 8)
    - KVM/vPMU:
	- Patch 8: use perf_event_create to create a perf event without
                   the need of a perf counter
	- Patch 12: set the GLOBAL_STATUS_COUNTERS_FROZEN bit when
                   injecting a vPMI.
previous:
	https://lkml.org/lkml/2019/2/14/210

Like Xu (1):
  KVM/x86/vPMU: Add APIs to support host save/restore the guest lbr
    stack

Wei Wang (11):
  perf/x86: fix the variable type of the LBR MSRs
  perf/x86: add a function to get the lbr stack
  KVM/x86: KVM_CAP_X86_GUEST_LBR
  KVM/x86: intel_pmu_lbr_enable
  KVM/x86/vPMU: tweak kvm_pmu_get_msr
  KVM/x86: expose MSR_IA32_PERF_CAPABILITIES to the guest
  perf/x86: no counter allocation support
  perf/x86: save/restore LBR_SELECT on vCPU switching
  KVM/x86/lbr: lazy save the guest lbr stack
  KVM/x86: remove the common handling of the debugctl msr
  KVM/VMX/vPMU: support to report GLOBAL_STATUS_LBRS_FROZEN

 arch/x86/events/core.c            |  12 ++
 arch/x86/events/intel/lbr.c       |  43 ++++-
 arch/x86/events/perf_event.h      |   6 +-
 arch/x86/include/asm/kvm_host.h   |   5 +
 arch/x86/include/asm/perf_event.h |  16 ++
 arch/x86/kvm/cpuid.c              |   2 +-
 arch/x86/kvm/cpuid.h              |   8 +
 arch/x86/kvm/pmu.c                |  29 ++-
 arch/x86/kvm/pmu.h                |  12 +-
 arch/x86/kvm/pmu_amd.c            |   7 +-
 arch/x86/kvm/vmx/pmu_intel.c      | 397 +++++++++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx/vmx.c            |   4 +-
 arch/x86/kvm/vmx/vmx.h            |   2 +
 arch/x86/kvm/x86.c                |  32 +--
 include/linux/perf_event.h        |  13 ++
 include/uapi/linux/kvm.h          |   1 +
 kernel/events/core.c              |  37 ++--
 17 files changed, 574 insertions(+), 52 deletions(-)
```
#### [PATCH v4 0/8] s390: virtio: support protected virtualization
##### From: Halil Pasic <pasic@linux.ibm.com>

```c

Enhanced virtualization protection technology may require the use of
bounce buffers for I/O. While support for this was built into the virtio
core, virtio-ccw wasn't changed accordingly.

Some background on technology (not part of this series) and the
terminology used.

* Protected Virtualization (PV):

Protected Virtualization guarantees, that non-shared memory of a  guest
that operates in PV mode private to that guest. I.e. any attempts by the
hypervisor or other guests to access it will result in an exception. If
supported by the environment (machine, KVM, guest VM) a guest can decide
to change into PV mode by doing the appropriate ultravisor calls.

* Ultravisor:

A hardware/firmware entity that manages PV guests, and polices access to
their memory. A PV guest prospect needs to interact with the ultravisor,
to enter PV mode, and potentially to share pages (for I/O which should
be encrypted by the guest). A guest interacts with the ultravisor via so
called ultravisor calls. A hypervisor needs to interact with the
ultravisor to facilitate interpretation, emulation and swapping. A
hypervisor  interacts with the ultravisor via ultravisor calls and via
the SIE state description. Generally the ultravisor sanitizes hypervisor
inputs so that the guest can not be corrupted (except for denial of
service.


What needs to be done
=====================

Thus what needs to be done to bring virtio-ccw up to speed with respect
to protected virtualization is:
* use some 'new' common virtio stuff
* make sure that virtio-ccw specific stuff uses shared memory when
  talking to the hypervisor (except control/communication blocks like ORB,
  these are handled by the ultravisor)
* make sure the DMA API does what is necessary to talk through shared
  memory if we are a protected virtualization guest.
* make sure the common IO layer plays along as well (airqs, sense).


Important notes
================

* This patch set is based on Martins features branch
 (git://git.kernel.org/pub/scm/linux/kernel/git/s390/linux.git branch
 'features').

* Documentation is still very sketchy. I'm committed to improving this,
  but I'm currently hampered by some dependencies currently.  

* The existing naming in the common infrastructure (kernel internal
  interfaces) is pretty much based on the AMD SEV terminology. Thus the
  names aren't always perfect. There might be merit to changing these
  names to more abstract ones. I did not put much thought into that at
  the current stage.

* Testing: Please use iommu_platform=on for any virtio devices you are
  going to test this code with (so virtio actually uses the DMA API).

@Sebastian: I kept your r-b on patch 2 "s390/cio: introduce DMA pools to
cio" despite the small changes pointed out below. Please do complain if
it ain't OK for you!

Change log
==========

v3 --> v4
* fixed cleanup in css_bus_init() (Connie)
* made cio.h include genalloc.h instead of a forward declaration
  (Connie)
* added comments about dma_mask/coherent_dma_mask values (Connie)
* fixed error handling in virtio_ccw_init() (Connie)
* got rid of the *vc_dma* wrappers (Connie)
* added some Reviewed-bys
* rebased on top of current master, no changes were necessary

v2 --> v3:
* patch 2/8
    potential cio_dma_pool_init() returning NULL issue fixed
    potential cio_gp_dma_create() returning NULL issue fixed
    warning issues with doc type comments fixed
    unused define statement removed 
* patch 3/8
    potential cio_gp_dma_create() returning NULL issue fixed
    whitespace issue fixed
    warning issues with doc type comments fixed
* patch 8/8
    potential cio_dma_zalloc() returning NULL issue fixed

v1 --> v2:
* patch "virtio/s390: use vring_create_virtqueue" went already upstream
* patch "virtio/s390: DMA support for virtio-ccw" went already upstream
* patch "virtio/s390: enable packed ring" went already upstream
* Made dev.dma_mask point to dev.coherent_dma_mask for css, subchannel
  and ccw devices.
* While rebasing 's390/airq: use DMA memory for adapter interrupts' the
  newly introduced kmem_cache  was replaced with an equivalent dma_pool;
  the kalloc() allocations are now replaced with cio_dma_zalloc()
  allocations to avoid wasting almost a full page.
* Made virtio-ccw use the new AIRQ_IV_CACHELINE flag.
* fixed all remaining checkpatch issues

RFC --> v1:
* Fixed bugs found by Connie (may_reduce and handling reduced,  warning,
  split move -- thanks Connie!).
* Fixed console bug found by Sebastian (thanks Sebastian!).
* Removed the completely useless duplicate of dma-mapping.h spotted by
  Christoph (thanks Christoph!).
* Don't use the global DMA pool for subchannel and ccw device
  owned memory as requested by Sebastian. Consequences:
	* Both subchannel and ccw devices have their dma masks
	now (both specifying 31 bit addressable)
	* We require at least 2 DMA pages per ccw device now, most of
	this memory is wasted though.
	* DMA memory allocated by virtio is also 31 bit addressable now
        as virtio uses the parent (which is the ccw device).
* Enabled packed ring.
* Rebased onto Martins feature branch; using the actual uv (ultravisor)
  interface instead of TODO comments.
* Added some explanations to the cover letter (Connie, David).
* Squashed a couple of patches together and fixed some text stuff. 

Halil Pasic (8):
  s390/mm: force swiotlb for protected virtualization
  s390/cio: introduce DMA pools to cio
  s390/cio: add basic protected virtualization support
  s390/airq: use DMA memory for adapter interrupts
  virtio/s390: use cacheline aligned airq bit vectors
  virtio/s390: add indirection to indicators access
  virtio/s390: use DMA memory for ccw I/O and classic notifiers
  virtio/s390: make airq summary indicators DMA

 arch/s390/Kconfig                   |   5 +
 arch/s390/include/asm/airq.h        |   2 +
 arch/s390/include/asm/ccwdev.h      |   4 +
 arch/s390/include/asm/cio.h         |  11 ++
 arch/s390/include/asm/mem_encrypt.h |  18 ++
 arch/s390/mm/init.c                 |  47 ++++++
 drivers/s390/cio/airq.c             |  32 ++--
 drivers/s390/cio/ccwreq.c           |   9 +-
 drivers/s390/cio/cio.h              |   2 +
 drivers/s390/cio/css.c              | 132 ++++++++++++++-
 drivers/s390/cio/device.c           |  68 ++++++--
 drivers/s390/cio/device_fsm.c       |  49 +++---
 drivers/s390/cio/device_id.c        |  20 ++-
 drivers/s390/cio/device_ops.c       |  21 ++-
 drivers/s390/cio/device_pgid.c      |  22 +--
 drivers/s390/cio/device_status.c    |  24 +--
 drivers/s390/cio/io_sch.h           |  20 ++-
 drivers/s390/virtio/virtio_ccw.c    | 248 +++++++++++++++-------------
 18 files changed, 534 insertions(+), 200 deletions(-)
 create mode 100644 arch/s390/include/asm/mem_encrypt.h
```
#### [PATCH RFC 0/1] mdevctl: further config for vfio-ap
##### From: Cornelia Huck <cohuck@redhat.com>

```c

This patch adds a very rough implementation of additional config data
for mdev devices. The idea is to make it possible to specify some
type-specific key=value pairs in the config file for an mdev device.
If a device is started automatically, the device is stopped and restarted
after applying the config.

The code has still some problems, like not doing a lot of error handling
and being ugly in general; but most importantly, I can't really test it,
as I don't have the needed hardware. Feedback welcome; would be good to
know if the direction is sensible in general.

Also available at

https://github.com/cohuck/mdevctl conf-data

Cornelia Huck (1):
  allow to specify additional config data

 mdevctl.libexec | 25 ++++++++++++++++++++++
 mdevctl.sbin    | 56 ++++++++++++++++++++++++++++++++++++++++++++++++-
 2 files changed, 80 insertions(+), 1 deletion(-)
```
#### [PATCH v3 0/9] Enable Sub-page Write Protection Support
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c

EPT-Based Sub-Page write Protection(SPP)is a HW capability which
allows Virtual Machine Monitor(VMM) to specify write-permission for
guest physical memory at a sub-page(128 byte) granularity. When this
capability is enabled, the CPU enforces write-access check for
sub-pages within a 4KB page.

The feature is targeted to provide fine-grained memory protection
for usages such as device virtualization, memory check-point and
VM introspection etc.

SPP is active when the "sub-page write protection" (bit 23) is 1 in
Secondary VM-Execution Controls. The feature is backed with a Sub-Page
Permission Table(SPPT), SPPT is referenced via a 64-bit control field
called Sub-Page Permission Table Pointer (SPPTP) which contains a
4K-aligned physical address.

Right now, only 4KB physical pages are supported for SPP. To enable SPP
for certain physical page, we need to first make the physical page
write-protected, then set bit 61 of the corresponding EPT leaf entry. 
While HW walks EPT, if bit 61 is set, it traverses SPPT with the guset
physical address to find out the sub-page permissions at the leaf entry.
If the corresponding bit is set, write to sub-page is permitted,
otherwise, SPP induced EPT vilation is generated.

Please refer to the SPP introduction document in this patch set and Intel SDM
for details:

Intel SDM:
https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Previous patch:
https://lkml.org/lkml/2018/11/30/605

Patch 1: Introduction to SPP.
Patch 2: Add SPP related flags and control bits.
Patch 3: Functions for SPPT setup.
Patch 4: Add SPP access bitmaps for memslots.
Patch 5: Low level implementation of SPP operations.
Patch 6: Implement User space access IOCTLs.
Patch 7: Handle SPP induced VMExit and EPT violation.
Patch 8: Enable lazy mode SPPT setup.
Patch 9: Handle memory remapping and reclaim.


Change logs:

V2 - V3:                                                                
 1. Rebased patches to kernel 5.1 release                                
 2. Deferred SPPT setup to EPT fault handler if the page is not available
    while set_subpage() is being called.                                 
 3. Added init IOCTL to reduce extra cost if SPP is not used.            
 4. Refactored patch structure, cleaned up cross referenced functions.    
 5. Added code to deal with memory swapping/migration/shrinker cases.    
                                                                           
V2 - V1:                                                                
 1. Rebased to 4.20-rc1                                                  
 2. Move VMCS change to a separated patch.                               
 3. Code refine and Bug fix 


Yang Weijiang (9):
  Documentation: Introduce EPT based Subpage Protection
  KVM: VMX: Add control flags for SPP enabling
  KVM: VMX: Implement functions for SPPT paging setup
  KVM: VMX: Introduce SPP access bitmap and operation functions
  KVM: VMX: Add init/set/get functions for SPP
  KVM: VMX: Introduce SPP user-space IOCTLs
  KVM: VMX: Handle SPP induced vmexit and page fault
  KVM: MMU: Enable Lazy mode SPPT setup
  KVM: MMU: Handle host memory remapping and reclaim

 Documentation/virtual/kvm/spp_kvm.txt | 216 ++++++++++++
 arch/x86/include/asm/cpufeatures.h    |   1 +
 arch/x86/include/asm/kvm_host.h       |  26 +-
 arch/x86/include/asm/vmx.h            |  10 +
 arch/x86/include/uapi/asm/vmx.h       |   2 +
 arch/x86/kernel/cpu/intel.c           |   4 +
 arch/x86/kvm/mmu.c                    | 469 ++++++++++++++++++++++++++
 arch/x86/kvm/mmu.h                    |   1 +
 arch/x86/kvm/vmx/capabilities.h       |   5 +
 arch/x86/kvm/vmx/vmx.c                | 138 ++++++++
 arch/x86/kvm/x86.c                    | 141 ++++++++
 include/linux/kvm_host.h              |   9 +
 include/uapi/linux/kvm.h              |  17 +
 13 files changed, 1038 insertions(+), 1 deletion(-)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt
```
#### [PATCH 0/8] KVM: arm/arm64: vgic: ITS translation cache
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c

It recently became apparent[1] that our LPI injection path is not as
efficient as it could be when injecting interrupts coming from a VFIO
assigned device.

Although the proposed patch wasn't 100% correct, it outlined at least
two issues:

(1) Injecting an LPI from VFIO always results in a context switch to a
    worker thread: no good

(2) We have no way of amortising the cost of translating a DID+EID pair
    to an LPI number

The reason for (1) is that we may sleep when translating an LPI, so we
do need a context process. A way to fix that is to implement a small
LPI translation cache that could be looked up from an atomic
context. It would also solve (2).

This is what this small series proposes. it implements a very basic
LRU cache of pre-translated LPIs, which gets used to implement
kvm_arch_set_irq_inatomic. The size of the cache is currently
hard-coded at 4 times the number of vcpus, a number I have randomly
chosen with the utmost care.

Does it work? well, it doesn't crash, and is thus perfect. More
seriously, I don't really have a way to benchmark it directly, so my
observations are indirect:

On a TX2 system, I run a 4 vcpu VM with an Ethernet interface passed
to it directly. From the host, I inject interrupts using debugfs. In
parallel, I look at the number of context switch, and the number of
interrupts on the host. Without this series, I get the same number for
both IRQ and CS (about half a million of each per second is pretty
easy to reach). With this series, the number of context switches drops
to something pretty small (in the low 2k), while the number of
interrupts stays the same.

Yes, this is a pretty rubbish benchmark, what did you expect? ;-)

So I'm putting this out for people with real workloads to try out and
report what they see.

[1] https://lore.kernel.org/lkml/1552833373-19828-1-git-send-email-yuzenghui@huawei.com/

Marc Zyngier (8):
  KVM: arm/arm64: vgic: Add LPI translation cache definition
  KVM: arm/arm64: vgic: Add __vgic_put_lpi_locked primitive
  KVM: arm/arm64: vgic-its: Cache successful MSI->LPI translation
  KVM: arm/arm64: vgic-its: Add kvm parameter to
    vgic_its_free_collection
  KVM: arm/arm64: vgic-its: Invalidate MSI-LPI translation cache on
    specific commands
  KVM: arm/arm64: vgic-its: Invalidate MSI-LPI translation cache on
    disabling LPIs
  KVM: arm/arm64: vgic-its: Check the LPI translation cache on MSI
    injection
  KVM: arm/arm64: vgic-irqfd: Implement kvm_arch_set_irq_inatomic

 include/kvm/arm_vgic.h           |  10 +++
 virt/kvm/arm/vgic/vgic-init.c    |  34 ++++++++
 virt/kvm/arm/vgic/vgic-irqfd.c   |  36 ++++++--
 virt/kvm/arm/vgic/vgic-its.c     | 143 +++++++++++++++++++++++++++++--
 virt/kvm/arm/vgic/vgic-mmio-v3.c |   4 +-
 virt/kvm/arm/vgic/vgic.c         |  26 ++++--
 virt/kvm/arm/vgic/vgic.h         |   6 ++
 7 files changed, 238 insertions(+), 21 deletions(-)
```
#### [PATCH v2 0/9] s390: vfio-ccw code rework
##### From: Eric Farman <farman@linux.ibm.com>

```c

Now that we've gotten a lot of other series either merged or
pending for the next merge window, I'd like to revisit some
code simplification that I started many moons ago.

In that first series, a couple of fixes got merged into 4.20,
a couple more got some "seems okay" acks/reviews, and the rest
were nearly forgotten about.  I dusted them off and did quite a
bit of rework to make things a little more sequential and
providing a better narrative (I think) based on the lessons we
learned in my earlier changes.  Because of this rework, the
acks/reviews on the first version didn't really translate to the
code that exists here (patch 1 being the closest exception), so
I didn't apply any of them here.  The end result is mostly the
same as before, but now looks like this:

Patch summary:
1:   Squash duplicate code
2-4: Remove duplicate code in CCW processor
5-7: Remove one layer of nested arrays
8-9: Combine direct/indirect addressing CCW processors

Using 5.2.0-rc3 as a base plus the vfio-ccw branch of recent fixes,
we shrink the code quite a bit (8.7% according to the bloat-o-meter),
and we remove one set of mallocs/frees on the I/O path by removing
one layer of the nested arrays.  There are no functional/behavioral
changes with this series; all the tests that I would run previously
continue to pass/fail as they today.

Changelog:
 v1/RFC->v2:
  - [Eric] Dropped first two patches, as they have been merged
  - [Eric] Shuffling of patches for readability/understandability
  - [Halil] Actually added meaningful comments/commit messages
    in the patches
 v1/RFC: https://patchwork.kernel.org/cover/10675251/

Eric Farman (9):
  s390/cio: Squash cp_free() and cp_unpin_free()
  s390/cio: Refactor the routine that handles TIC CCWs
  s390/cio: Generalize the TIC handler
  s390/cio: Use generalized CCW handler in cp_init()
  vfio-ccw: Rearrange pfn_array and pfn_array_table arrays
  vfio-ccw: Adjust the first IDAW outside of the nested loops
  vfio-ccw: Remove pfn_array_table
  vfio-ccw: Rearrange IDAL allocation in direct CCW
  s390/cio: Combine direct and indirect CCW paths

 drivers/s390/cio/vfio_ccw_cp.c | 313 +++++++++++----------------------
 1 file changed, 102 insertions(+), 211 deletions(-)
```
