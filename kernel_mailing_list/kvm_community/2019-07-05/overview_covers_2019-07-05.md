

#### [PATCH kvmtool 0/2] Add terminal detach feature
##### From: Andre Przywara <andre.przywara@arm.com>

```c

At the moment running a guest will tie it to the console where kvmtool
is running on. So one cannot logout of the terminal without killing the
guest. Existing workarounds are running in a terminal multiplexer like
screen or using the --tty option to detach kvmtool from the very
beginning.

Both of these solutions need to be invoked at guest creation time,
though. Patch 2 introduces a "detach" command, which can be invoked at
any point during the guest's runtime using the terminal escape sequence
("Ctrl+A d" by default). This will redirect the guest's serial output
to pseudo-terminals and detach the process from the console. More
details in the commit message.

Patch 1 contains a bugfix, which avoids the kvmtool terminal thread to
hog the full CPU time because poll() is not exactly doing what we think
it does.

Please have a look and comment!

Cheers,
Andre

Andre Przywara (2):
  term: Avoid busy loop with unconnected pseudoterminals
  Add detach feature

 builtin-run.c     |   3 +
 include/kvm/kvm.h |   2 +
 term.c            | 139 +++++++++++++++++++++++++++++++++++++++++++++-
 3 files changed, 141 insertions(+), 3 deletions(-)
```
#### [PATCH v3 0/3] vsock/virtio: several fixes in the .probe() and
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c

During the review of "[PATCH] vsock/virtio: Initialize core virtio vsock
before registering the driver", Stefan pointed out some possible issues
in the .probe() and .remove() callbacks of the virtio-vsock driver.

This series tries to solve these issues:
- Patch 1 adds RCU critical sections to avoid use-after-free of
  'the_virtio_vsock' pointer.
- Patch 2 stops workers before to call vdev->config->reset(vdev) to
  be sure that no one is accessing the device.
- Patch 3 moves the works flush at the end of the .remove() to avoid
  use-after-free of 'vsock' object.

v3:
- Patch 1: use rcu_dereference_protected() to get the_virtio_vosck value in
           the virtio_vsock_probe() [Jason]

v2: https://patchwork.kernel.org/cover/11022343/

v1: https://patchwork.kernel.org/cover/10964733/

Before this series the guest crashes in a few second. After this series the
test runs (~12h) without issues.
Tested on an SMP guest (-smp 4 -monitor tcp:127.0.0.1:1234,server,nowait)
with these scripts to stress the .probe()/.remove() path:

- guest
  while true; do
      cat /dev/urandom | nc-vsock -l 4321 > /dev/null &
      cat /dev/urandom | nc-vsock -l 5321 > /dev/null &
      cat /dev/urandom | nc-vsock -l 6321 > /dev/null &
      cat /dev/urandom | nc-vsock -l 7321 > /dev/null &
      wait
  done

- host
  while true; do
      cat /dev/urandom | nc-vsock 3 4321 > /dev/null &
      cat /dev/urandom | nc-vsock 3 5321 > /dev/null &
      cat /dev/urandom | nc-vsock 3 6321 > /dev/null &
      cat /dev/urandom | nc-vsock 3 7321 > /dev/null &
      sleep 2
      echo "device_del v1" | nc 127.0.0.1 1234
      sleep 1
      echo "device_add vhost-vsock-pci,id=v1,guest-cid=3" | nc 127.0.0.1 1234
      sleep 1
  done

Stefano Garzarella (3):
  vsock/virtio: use RCU to avoid use-after-free on the_virtio_vsock
  vsock/virtio: stop workers during the .remove()
  vsock/virtio: fix flush of works during the .remove()

 net/vmw_vsock/virtio_transport.c | 134 ++++++++++++++++++++++++-------
 1 file changed, 104 insertions(+), 30 deletions(-)
```
#### [PATCH v15 0/7] virtio pmem driver 
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

Hi Dan,

 This series has only change in patch 2 for linux-next build
 failure. There is no functional change. Keeping all the
 existing review/acks and reposting the patch series for
 merging via libnvdimm tree.
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

Changes from PATCH v13: [1] 
 - Rebase to Linux-5.2-rc7
 - Fix Linux-next build failure for undefined type

Changes from PATCH v13: [2] 
 - Rebased to Linux-5.2-rc5
 - Fix S390x build failure in patch 3
 - Fix for !CONFIG_DAX with dax_synchronous
 - Fix sparse warning in virtio patch 2

Changes from PATCH v12:
 - Minor changes(function name, dev_err -> dev_info & 
   make function static in virtio patch - [Cornelia]
 - Added r-o-b of Mike in patch 4

Changes from PATCH v11: 
 - Change implmentation for setting of synchronous DAX type
   for device mapper - [Mike] 

Changes from PATCH v10:
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

[1] https://lkml.org/lkml/2019/6/21/452
[2] https://lkml.org/lkml/2019/6/12/624
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
 drivers/nvdimm/nd_virtio.c       |  125 +++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/pmem.c            |   18 +++--
 drivers/nvdimm/region_devs.c     |   33 +++++++++-
 drivers/nvdimm/virtio_pmem.c     |  122 ++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/virtio_pmem.h     |   55 +++++++++++++++++
 drivers/s390/block/dcssblk.c     |    2 
 drivers/virtio/Kconfig           |   11 +++
 fs/ext4/file.c                   |   10 +--
 fs/xfs/xfs_file.c                |    9 +-
 include/linux/dax.h              |   41 ++++++++++++
 include/linux/libnvdimm.h        |   10 ++-
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   34 ++++++++++
 22 files changed, 504 insertions(+), 34 deletions(-)
```
#### [PATCH v6 0/2] KVM: LAPIC: Implement Exitless Timer
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
timer will be moved to the nearest busy housekeepers after commit
9642d18eee2cd (nohz: Affine unpinned timers to housekeepers) and commit 
444969223c8 ("sched/nohz: Fix affine unpinned timers mess"). However, 
KVM always makes lapic timer pinned to the pCPU which vCPU residents, the 
reason is explained by commit 61abdbe0 (kvm: x86: make lapic hrtimer 
pinned). Actually, these emulated timers can be offload to the housekeeping 
cpus since APICv is really common in recent years. The guest timer interrupt 
is injected by posted-interrupt which is delivered by housekeeping cpu 
once the emulated timer fires. 

The host admin should fine tuned, e.g. dedicated instances scenario w/ 
nohz_full cover the pCPUs which vCPUs resident, several pCPUs surplus 
for busy housekeeping, disable mwait/hlt/pause vmexits to keep in non-root  
mode, ~3% redis performance benefit can be observed on Skylake server.

w/o patchset:

            VM-EXIT  Samples  Samples%  Time%   Min Time  Max Time   Avg time

EXTERNAL_INTERRUPT    42916    49.43%   39.30%   0.47us   106.09us   0.71us ( +-   1.09% )

w/ patchset:

            VM-EXIT  Samples  Samples%  Time%   Min Time  Max Time         Avg time

EXTERNAL_INTERRUPT    6871     9.29%     2.96%   0.44us    57.88us   0.72us ( +-   4.02% )

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>

v5 -> v6:
 * don't overwrites whatever the user specified
 * introduce kvm_can_post_timer_interrupt and kvm_use_posted_timer_interrupt
 * remove kvm_hlt_in_guest() condition
 * squash all of 2/3/4 together

v4 -> v5:
 * update patch description in patch 1/4
 * feed latest apic->lapic_timer.expired_tscdeadline to kvm_wait_lapic_expire()
 * squash advance timer handling to patch 2/4

v3 -> v4:
 * drop the HRTIMER_MODE_ABS_PINNED, add kick after set pending timer
 * don't posted inject already-expired timer

v2 -> v3:
 * disarming the vmx preemption timer when posted_interrupt_inject_timer_enabled()
 * check kvm_hlt_in_guest instead

v1 -> v2:
 * check vcpu_halt_in_guest
 * move module parameter from kvm-intel to kvm
 * add housekeeping_enabled
 * rename apic_timer_expired_pi to kvm_apic_inject_pending_timer_irqs



Wanpeng Li (2):
  KVM: LAPIC: Make lapic timer unpinned
  KVM: LAPIC: Inject timer interrupt via posted interrupt

 arch/x86/kvm/lapic.c            | 60 +++++++++++++++++++++++++++++------------
 arch/x86/kvm/lapic.h            |  3 ++-
 arch/x86/kvm/svm.c              |  2 +-
 arch/x86/kvm/vmx/vmx.c          |  5 ++--
 arch/x86/kvm/x86.c              | 12 +++++----
 arch/x86/kvm/x86.h              |  2 ++
 include/linux/sched/isolation.h |  2 ++
 kernel/sched/isolation.c        |  6 +++++
 8 files changed, 66 insertions(+), 26 deletions(-)
```
#### [PATCH 0/4] target/i386: kvm: Various nested-state fixes
##### From: Liran Alon <liran.alon@oracle.com>

```c

Hi,

This series is just a bunch of small fixes to recent QEMU nested-state
migration support.

1st and 2nd patch can be considered as trivial refactoring patches.

3rd patch fixes a bug of requiring to save VMX nested-state when it is
not needed.

4rd patch removes migration blocker when vCPU is exposed with VMX and
instead demand nested migration kernel capabilities only when vCPU may
have enabled VMX. To provide for better backwards-compatible migration
scenarios. For more info, refer to relevant commit message.

Thanks,
-Liran
```
