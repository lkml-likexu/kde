

#### [PATCH v2 0/5] KVM: X86: Add virtual C-states residency msrs support
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c

After exposing some host CPU power management capabilities to dedicated 
instances, there is a requirement to consult current idle power-state 
residency statistics by turbostat.

This patchset adds virtual C-states residency msrs emulation. Allowing 
guest reads CORE cstate when exposing host CPU power management capabilities 
to the guest. PKG cstate is restricted currently to avoid a guest to get 
the whole package information in multi-tenant scenario.

v1 -> v2:
 * add residency msrs emulation (base on Paolo's design)

Wanpeng Li (5):
  KVM: X86: Dynamic allocate core residency msr state
  KVM: X86: Introduce residency msrs read/write operations
  KVM: X86: setup residency msrs during vCPU creation
  KVM: VMX: Add get/set residency msrs logic
  KVM: X86: Save/restore residency values when sched_out/sched_in

 arch/arm/include/asm/kvm_host.h     |   1 +
 arch/arm64/include/asm/kvm_host.h   |   1 +
 arch/mips/include/asm/kvm_host.h    |   1 +
 arch/powerpc/include/asm/kvm_host.h |   1 +
 arch/s390/include/asm/kvm_host.h    |   1 +
 arch/x86/include/asm/kvm_host.h     |  11 ++++
 arch/x86/kvm/vmx/vmx.c              |  15 ++++++
 arch/x86/kvm/x86.c                  | 104 ++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.h                  |   5 ++
 include/linux/kvm_host.h            |   1 +
 virt/kvm/kvm_main.c                 |   1 +
 11 files changed, 142 insertions(+)
```
#### [PATCH v3 0/4] KVM: LAPIC: Implement Exitless Timer
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
~3% redis performance benefit can be observed on Skylake server.

w/o patchset:

            VM-EXIT  Samples  Samples%  Time%   Min Time  Max Time   Avg time

EXTERNAL_INTERRUPT    42916    49.43%   39.30%   0.47us   106.09us   0.71us ( +-   1.09% )

w/ patchset:

            VM-EXIT  Samples  Samples%  Time%   Min Time  Max Time         Avg time

EXTERNAL_INTERRUPT    6871     9.29%     2.96%   0.44us    57.88us   0.72us ( +-   4.02% )


v2 -> v3:
 * disarming the vmx preemption timer when posted_interrupt_inject_timer_enabled()
 * check kvm_hlt_in_guest instead

v1 -> v2:
 * check vcpu_halt_in_guest
 * move module parameter from kvm-intel to kvm
 * add housekeeping_enabled
 * rename apic_timer_expired_pi to kvm_apic_inject_pending_timer_irqs


Wanpeng Li (4):
  KVM: LAPIC: Make lapic timer unpinned when timer is injected by pi
  KVM: LAPIC: lapic timer interrupt is injected by posted interrupt
  KVM: LAPIC: Ignore timer migration when lapic timer is injected by pi
  KVM: LAPIC: add advance timer support to pi_inject_timer

 arch/x86/kvm/lapic.c            | 61 +++++++++++++++++++++++++++++++----------
 arch/x86/kvm/lapic.h            |  3 +-
 arch/x86/kvm/svm.c              |  2 +-
 arch/x86/kvm/vmx/vmx.c          |  5 ++--
 arch/x86/kvm/x86.c              |  5 ++++
 arch/x86/kvm/x86.h              |  2 ++
 include/linux/sched/isolation.h |  2 ++
 kernel/sched/isolation.c        |  6 ++++
 8 files changed, 68 insertions(+), 18 deletions(-)
```
#### [PATCH v4 0/3] KVM: Yield to IPI target if necessary
##### From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>

```c

The idea is from Xen, when sending a call-function IPI-many to vCPUs, 
yield if any of the IPI target vCPUs was preempted. 17% performance 
increasement of ebizzy benchmark can be observed in an over-subscribe 
environment. (w/ kvm-pv-tlb disabled, testing TLB flush call-function 
IPI-many since call-function is not easy to be trigged by userspace 
workload).

v3 -> v4: 
 * check map->phys_map[dest_id]
 * more cleaner kvm_sched_yield()

v2 -> v3:
 * add bounds-check on dest_id

v1 -> v2:
 * check map is not NULL
 * check map->phys_map[dest_id] is not NULL
 * make kvm_sched_yield static
 * change dest_id to unsinged long

Wanpeng Li (3):
  KVM: X86: Yield to IPI target if necessary
  KVM: X86: Implement PV sched yield hypercall
  KVM: X86: Expose PV_SCHED_YIELD CPUID feature bit to guest

 Documentation/virtual/kvm/cpuid.txt      |  4 ++++
 Documentation/virtual/kvm/hypercalls.txt | 11 +++++++++++
 arch/x86/include/uapi/asm/kvm_para.h     |  1 +
 arch/x86/kernel/kvm.c                    | 21 +++++++++++++++++++++
 arch/x86/kvm/cpuid.c                     |  3 ++-
 arch/x86/kvm/x86.c                       | 21 +++++++++++++++++++++
 include/uapi/linux/kvm_para.h            |  1 +
 7 files changed, 61 insertions(+), 1 deletion(-)
```
#### [PATCH v12 0/7] virtio pmem driver 
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

This patch series is ready to be merged via nvdimm tree
 as discussed with Dan. We have ack/review on XFS, EXT4
 & VIRTIO patches. Device mapper change is also reviewed. 

 Mike, Can you please provide ack for device mapper change
 i.e patch4. 

 This version has changed implementation for patch 4 as
 suggested by 'Mike'. Keeping all the existing r-o-bs. Jakob
 CCed also tested the patch series and confirmed the working
 of v9.
 ---

 This patch series has implementation for "virtio pmem". 
 "virtio pmem" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest kernel driver in this patchset with the 
 changes suggested in v4. Tested with Qemu side device 
 emulation [5] for virtio-pmem. Documented the impact of
 possible page cache side channel attacks with suggested
 countermeasures.

 Details of project idea for 'virtio pmem' flushing interface 
 is shared [3] & [4].

 Implementation is divided into two parts:
 New virtio pmem guest driver and qemu code changes for new 
 virtio pmem paravirtualized device.

1. Guest virtio-pmem kernel driver
---------------------------------
   - Reads persistent memory range from paravirt device and 
     registers with 'nvdimm_bus'.  
   - 'nvdimm/pmem' driver uses this information to allocate 
     persistent memory region and setup filesystem operations 
     to the allocated memory. 
   - virtio pmem driver implements asynchronous flushing 
     interface to flush from guest to host.

2. Qemu virtio-pmem device
---------------------------------
   - Creates virtio pmem device and exposes a memory range to 
     KVM guest. 
   - At host side this is file backed memory which acts as 
     persistent memory. 
   - Qemu side flush uses aio thread pool API's and virtio 
     for asynchronous guest multi request handling. 

 Virtio-pmem security implications and countermeasures:
 -----------------------------------------------------

 In previous posting of kernel driver, there was discussion [7]
 on possible implications of page cache side channel attacks with 
 virtio pmem. After thorough analysis of details of known side 
 channel attacks, below are the suggestions:

 - Depends entirely on how host backing image file is mapped 
   into guest address space. 

 - virtio-pmem device emulation, by default shared mapping is used
   to map host backing file. It is recommended to use separate
   backing file at host side for every guest. This will prevent
   any possibility of executing common code from multiple guests
   and any chance of inferring guest local data based based on 
   execution time.

 - If backing file is required to be shared among multiple guests 
   it is recommended to don't support host page cache eviction 
   commands from the guest driver. This will avoid any possibility
   of inferring guest local data or host data from another guest. 

 - Proposed device specification [6] for virtio-pmem device with 
   details of possible security implications and suggested 
   countermeasures for device emulation.

 Virtio-pmem errors handling:
 ----------------------------------------
  Checked behaviour of virtio-pmem for below types of errors
  Need suggestions on expected behaviour for handling these errors?

  - Hardware Errors: Uncorrectable recoverable Errors: 
  a] virtio-pmem: 
    - As per current logic if error page belongs to Qemu process, 
      host MCE handler isolates(hwpoison) that page and send SIGBUS. 
      Qemu SIGBUS handler injects exception to KVM guest. 
    - KVM guest then isolates the page and send SIGBUS to guest 
      userspace process which has mapped the page. 
  
  b] Existing implementation for ACPI pmem driver: 
    - Handles such errors with MCE notifier and creates a list 
      of bad blocks. Read/direct access DAX operation return EIO 
      if accessed memory page fall in bad block list.
    - It also starts backgound scrubbing.  
    - Similar functionality can be reused in virtio-pmem with MCE 
      notifier but without scrubbing(no ACPI/ARS)? Need inputs to 
      confirm if this behaviour is ok or needs any change?

Changes from PATCH v11: [1] 
 - Change implmentation for setting of synchronous DAX type
   for device mapper - Mike 

Changes from PATCH v10: [2] 
 - Rebased on Linux-5.2-rc4

Changes from PATCH v9:
 - Kconfig help text add two spaces - Randy
 - Fixed libnvdimm 'bio' include warning - Dan
 - virtio-pmem, separate request/resp struct and 
   move to uapi file with updated license - DavidH
 - Use virtio32* type for req/resp endianess - DavidH
 - Added tested-by & ack-by of Jakob
 - Rebased to 5.2-rc1

Changes from PATCH v8:
 - Set device mapper synchronous if all target devices support - Dan
 - Move virtio_pmem.h to nvdimm directory  - Dan
 - Style, indentation & better error messages in patch 2 - DavidH
 - Added MST's ack in patch 2.

Changes from PATCH v7:
 - Corrected pending request queue logic (patch 2) - Jakub Staroń
 - Used unsigned long flags for passing DAXDEV_F_SYNC (patch 3) - Dan
 - Fixed typo =>  vma 'flag' to 'vm_flag' (patch 4)
 - Added rob in patch 6 & patch 2

Changes from PATCH v6: 
 - Corrected comment format in patch 5 & patch 6. [Dave]
 - Changed variable declaration indentation in patch 6 [Darrick]
 - Add Reviewed-by tag by 'Jan Kara' in patch 4 & patch 5

Changes from PATCH v5: 
  Changes suggested in by - [Cornelia, Yuval]
- Remove assignment chaining in virtio driver
- Better error message and remove not required free
- Check nd_region before use

  Changes suggested by - [Jan Kara]
- dax_synchronous() for !CONFIG_DAX
- Correct 'daxdev_mapping_supported' comment and non-dax implementation

  Changes suggested by - [Dan Williams]
- Pass meaningful flag 'DAXDEV_F_SYNC' to alloc_dax
- Gate nvdimm_flush instead of additional async parameter
- Move block chaining logic to flush callback than common nvdimm_flush
- Use NULL flush callback for generic flush for better readability [Dan, Jan]

- Use virtio device id 27 from 25(already used) - [MST]

Changes from PATCH v4:
- Factor out MAP_SYNC supported functionality to a common helper
				[Dave, Darrick, Jan]
- Comment, indentation and virtqueue_kick failure handle - Yuval Shaia

Changes from PATCH v3: 
- Use generic dax_synchronous() helper to check for DAXDEV_SYNC 
  flag - [Dan, Darrick, Jan]
- Add 'is_nvdimm_async' function
- Document page cache side channel attacks implications & 
  countermeasures - [Dave Chinner, Michael]

Changes from PATCH v2: 
- Disable MAP_SYNC for ext4 & XFS filesystems - [Dan] 
- Use name 'virtio pmem' in place of 'fake dax' 

Changes from PATCH v1: 
- 0-day build test for build dependency on libnvdimm 

 Changes suggested by - [Dan Williams]
- Split the driver into two parts virtio & pmem  
- Move queuing of async block request to block layer
- Add "sync" parameter in nvdimm_flush function
- Use indirect call for nvdimm_flush
- Don’t move declarations to common global header e.g nd.h
- nvdimm_flush() return 0 or -EIO if it fails
- Teach nsio_rw_bytes() that the flush can fail
- Rename nvdimm_flush() to generic_nvdimm_flush()
- Use 'nd_region->provider_data' for long dereferencing
- Remove virtio_pmem_freeze/restore functions
- Remove BSD license text with SPDX license text

- Add might_sleep() in virtio_pmem_flush - [Luiz]
- Make spin_lock_irqsave() narrow

Pankaj Gupta (7):
   libnvdimm: nd_region flush callback support
   virtio-pmem: Add virtio-pmem guest driver
   libnvdimm: add nd_region buffered dax_dev flag
   dax: check synchronous mapping is supported
   dm: dm: Enable synchronous dax
   ext4: disable map_sync for virtio pmem
   xfs: disable map_sync for virtio pmem

[1] https://lkml.org/lkml/2019/6/10/209
[2] https://lkml.org/lkml/2019/5/21/569
[3] https://www.spinics.net/lists/kvm/msg149761.html
[4] https://www.spinics.net/lists/kvm/msg153095.html  
[5] https://marc.info/?l=qemu-devel&m=155860751202202&w=2
[6] https://lists.oasis-open.org/archives/virtio-dev/201903/msg00083.html
[7] https://lkml.org/lkml/2019/1/9/1191

 drivers/acpi/nfit/core.c         |    4 -
 drivers/dax/bus.c                |    2 
 drivers/dax/super.c              |   19 +++++
 drivers/md/dm-table.c            |   24 +++++--
 drivers/md/dm.c                  |    5 -
 drivers/md/dm.h                  |    5 +
 drivers/nvdimm/Makefile          |    1 
 drivers/nvdimm/claim.c           |    6 +
 drivers/nvdimm/nd.h              |    1 
 drivers/nvdimm/nd_virtio.c       |  124 +++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/pmem.c            |   18 +++--
 drivers/nvdimm/region_devs.c     |   33 +++++++++-
 drivers/nvdimm/virtio_pmem.c     |  122 ++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/virtio_pmem.h     |   55 +++++++++++++++++
 drivers/virtio/Kconfig           |   11 +++
 fs/ext4/file.c                   |   10 +--
 fs/xfs/xfs_file.c                |    9 +-
 include/linux/dax.h              |   26 +++++++-
 include/linux/libnvdimm.h        |   10 ++-
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   35 +++++++++++
 21 files changed, 488 insertions(+), 33 deletions(-)
```
#### [PATCH v2 0/9] KVM: arm/arm64: vgic: ITS translation cache
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

This is what this small series proposes. It implements a very basic
LRU cache of pre-translated LPIs, which gets used to implement
kvm_arch_set_irq_inatomic. The size of the cache is currently
hard-coded at 16 times the number of vcpus, a number I have picked
under the influence of Ali Saidi. If that's not enough for you, blame
me, though.

Does it work? well, it doesn't crash, and is thus perfect. More
seriously, I don't really have a way to benchmark it directly, so my
observations are only indirect:

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

* From v1:

  - Fixed race on allocation, where the same LPI could be cached multiple times
  - Now invalidate the cache on vgic teardown, avoiding memory leaks
  - Change patch split slightly, general reshuffling
  - Small cleanups here and there
  - Rebased on 5.2-rc4

Marc Zyngier (9):
  KVM: arm/arm64: vgic: Add LPI translation cache definition
  KVM: arm/arm64: vgic: Add __vgic_put_lpi_locked primitive
  KVM: arm/arm64: vgic-its: Add MSI-LPI translation cache invalidation
  KVM: arm/arm64: vgic-its: Invalidate MSI-LPI translation cache on
    specific commands
  KVM: arm/arm64: vgic-its: Invalidate MSI-LPI translation cache on
    disabling LPIs
  KVM: arm/arm64: vgic-its: Invalidate MSI-LPI translation cache on vgic
    teardown
  KVM: arm/arm64: vgic-its: Cache successful MSI->LPI translation
  KVM: arm/arm64: vgic-its: Check the LPI translation cache on MSI
    injection
  KVM: arm/arm64: vgic-irqfd: Implement kvm_arch_set_irq_inatomic

 include/kvm/arm_vgic.h           |   3 +
 virt/kvm/arm/vgic/vgic-init.c    |   5 +
 virt/kvm/arm/vgic/vgic-irqfd.c   |  36 +++++-
 virt/kvm/arm/vgic/vgic-its.c     | 204 +++++++++++++++++++++++++++++++
 virt/kvm/arm/vgic/vgic-mmio-v3.c |   4 +-
 virt/kvm/arm/vgic/vgic.c         |  26 ++--
 virt/kvm/arm/vgic/vgic.h         |   5 +
 7 files changed, 267 insertions(+), 16 deletions(-)
```
#### [patch 0/3] cpuidle-haltpoll driver (v3)
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c

The cpuidle-haltpoll driver allows the guest vcpus to poll for a specified
amount of time before halting. This provides the following benefits
to host side polling:

         1) The POLL flag is set while polling is performed, which allows
            a remote vCPU to avoid sending an IPI (and the associated
            cost of handling the IPI) when performing a wakeup.

         2) The VM-exit cost can be avoided.

The downside of guest side polling is that polling is performed
even with other runnable tasks in the host.

Results comparing halt_poll_ns and server/client application
where a small packet is ping-ponged:

host                                        --> 31.33
halt_poll_ns=300000 / no guest busy spin    --> 33.40   (93.8%)
halt_poll_ns=0 / guest_halt_poll_ns=300000  --> 32.73   (95.7%)

For the SAP HANA benchmarks (where idle_spin is a parameter
of the previous version of the patch, results should be the
same):

hpns == halt_poll_ns

                           idle_spin=0/   idle_spin=800/    idle_spin=0/
                           hpns=200000    hpns=0            hpns=800000
DeleteC06T03 (100 thread) 1.76           1.71 (-3%)        1.78   (+1%)
InsertC16T02 (100 thread) 2.14           2.07 (-3%)        2.18   (+1.8%)
DeleteC00T01 (1 thread)   1.34           1.28 (-4.5%)    1.29   (-3.7%)
UpdateC00T03 (1 thread)   4.72           4.18 (-12%)     4.53   (-5%)

V2:

- Move from x86 to generic code (Paolo/Christian)
- Add auto-tuning logic (Paolo)
- Add MSR to disable host side polling (Paolo)

V3:

- Do not be specific about HLT VM-exit in the documentation (Ankur Arora)
- Mark tuning parameters static and __read_mostly (Andrea Arcangeli)
- Add WARN_ON if host does not support poll control (Joao Martins)
- Use sched_clock and cleanup haltpoll_enter_idle (Peter Zijlstra)
- Mark certain functions in kvm.c as static (kernel test robot)
- Remove tracepoints as they use RCU from extended quiescent state (kernel
test robot)
```
