

#### [RESEND PATCH 0/7] Add FOLL_LONGTERM to GUP fast and use it
##### From: ira.weiny@intel.com
From: Ira Weiny <ira.weiny@intel.com>

```c

From: Ira Weiny <ira.weiny@intel.com>

Resending these as I had only 1 minor comment which I believe we have covered
in this series.  I was anticipating these going through the mm tree as they
depend on a cleanup patch there and the IB changes are very minor.  But they
could just as well go through the IB tree.

NOTE: This series depends on my clean up patch to remove the write parameter
from gup_fast_permitted()[1]

HFI1, qib, and mthca, use get_user_pages_fast() due to it performance
advantages.  These pages can be held for a significant time.  But
get_user_pages_fast() does not protect against mapping of FS DAX pages.

Introduce FOLL_LONGTERM and use this flag in get_user_pages_fast() which
retains the performance while also adding the FS DAX checks.  XDP has also
shown interest in using this functionality.[2]

In addition we change get_user_pages() to use the new FOLL_LONGTERM flag and
remove the specialized get_user_pages_longterm call.

[1] https://lkml.org/lkml/2019/2/11/237
[2] https://lkml.org/lkml/2019/2/11/1789

Ira Weiny (7):
  mm/gup: Replace get_user_pages_longterm() with FOLL_LONGTERM
  mm/gup: Change write parameter to flags in fast walk
  mm/gup: Change GUP fast to use flags rather than a write 'bool'
  mm/gup: Add FOLL_LONGTERM capability to GUP fast
  IB/hfi1: Use the new FOLL_LONGTERM flag to get_user_pages_fast()
  IB/qib: Use the new FOLL_LONGTERM flag to get_user_pages_fast()
  IB/mthca: Use the new FOLL_LONGTERM flag to get_user_pages_fast()

 arch/mips/mm/gup.c                          |  11 +-
 arch/powerpc/kvm/book3s_64_mmu_hv.c         |   4 +-
 arch/powerpc/kvm/e500_mmu.c                 |   2 +-
 arch/powerpc/mm/mmu_context_iommu.c         |   4 +-
 arch/s390/kvm/interrupt.c                   |   2 +-
 arch/s390/mm/gup.c                          |  12 +-
 arch/sh/mm/gup.c                            |  11 +-
 arch/sparc/mm/gup.c                         |   9 +-
 arch/x86/kvm/paging_tmpl.h                  |   2 +-
 arch/x86/kvm/svm.c                          |   2 +-
 drivers/fpga/dfl-afu-dma-region.c           |   2 +-
 drivers/gpu/drm/via/via_dmablit.c           |   3 +-
 drivers/infiniband/core/umem.c              |   5 +-
 drivers/infiniband/hw/hfi1/user_pages.c     |   5 +-
 drivers/infiniband/hw/mthca/mthca_memfree.c |   3 +-
 drivers/infiniband/hw/qib/qib_user_pages.c  |   8 +-
 drivers/infiniband/hw/qib/qib_user_sdma.c   |   2 +-
 drivers/infiniband/hw/usnic/usnic_uiom.c    |   9 +-
 drivers/media/v4l2-core/videobuf-dma-sg.c   |   6 +-
 drivers/misc/genwqe/card_utils.c            |   2 +-
 drivers/misc/vmw_vmci/vmci_host.c           |   2 +-
 drivers/misc/vmw_vmci/vmci_queue_pair.c     |   6 +-
 drivers/platform/goldfish/goldfish_pipe.c   |   3 +-
 drivers/rapidio/devices/rio_mport_cdev.c    |   4 +-
 drivers/sbus/char/oradax.c                  |   2 +-
 drivers/scsi/st.c                           |   3 +-
 drivers/staging/gasket/gasket_page_table.c  |   4 +-
 drivers/tee/tee_shm.c                       |   2 +-
 drivers/vfio/vfio_iommu_spapr_tce.c         |   3 +-
 drivers/vfio/vfio_iommu_type1.c             |   3 +-
 drivers/vhost/vhost.c                       |   2 +-
 drivers/video/fbdev/pvr2fb.c                |   2 +-
 drivers/virt/fsl_hypervisor.c               |   2 +-
 drivers/xen/gntdev.c                        |   2 +-
 fs/orangefs/orangefs-bufmap.c               |   2 +-
 include/linux/mm.h                          |  17 +-
 kernel/futex.c                              |   2 +-
 lib/iov_iter.c                              |   7 +-
 mm/gup.c                                    | 220 ++++++++++++--------
 mm/gup_benchmark.c                          |   5 +-
 mm/util.c                                   |   8 +-
 net/ceph/pagevec.c                          |   2 +-
 net/rds/info.c                              |   2 +-
 net/rds/rdma.c                              |   3 +-
 44 files changed, 232 insertions(+), 180 deletions(-)
```
#### [PATCH RFC 00/39] x86/KVM: Xen HVM guest support
##### From: Joao Martins <joao.m.martins@oracle.com>

```c

Hey,

Presented herewith a series that allows KVM to boot Xen x86 HVM guests (with their
respective frontends and backends). On the hypervisor side, the approach is to keep
the implementation similar to how HyperV was done on x86 KVM. On the backend driver
side, the intent is to reuse Xen support.

Note that this is an RFC so there are bugs and room for improvement. The intent
is to get overall feedback before proceeding further.

Running Xen guests on KVM, enables the following use-cases:

 * Run unmodified Xen HVM images;

 * Facilitate development/testing of Xen guests and Xen PV drivers;

There has been a similar proposal in the past with Xenner, albeit this work
has the following advantages over it:

 * Allows use of existing Xen PV drivers such as block, net etc, both as
 frontends and backends;

 * Xen tooling will see the same UABI as on Xen. This means things like
 xenstored, xenstore-list, xenstore-read run unmodified. Optionally,
 userspace VMM can emulate xenstore operations;

 This work is divided in two parts:

 1. Xen HVM ABI support (patches 1 - 16)

 Support the necessary mechanisms to allow HVM guests to
 boot *without* PV frontends exposed to the guest.
 
 We start by intercepting hypercalls made by the guest, followed
 by event channel IPIs/VIRQs (for PV IPI, timers, spinlocks),
 pvclock and steal clock.

	Ankur Arora (1):
	      KVM: x86/xen: support upcall vector

	Boris Ostrovsky (1):
	      KVM: x86/xen: handle PV spinlocks slowpath

	Joao Martins (14):
	      KVM: x86: fix Xen hypercall page msr handling
	      KVM: x86/xen: intercept xen hypercalls if enabled
	      KVM: x86/xen: register shared_info page
	      KVM: x86/xen: setup pvclock updates
	      KVM: x86/xen: update wallclock region
	      KVM: x86/xen: register vcpu info
	      KVM: x86/xen: register vcpu time info region
	      KVM: x86/xen: register steal clock
	      KVM: x86: declare Xen HVM guest capability
	      KVM: x86/xen: evtchn signaling via eventfd
	      KVM: x86/xen: store virq when assigning evtchn
	      KVM: x86/xen: handle PV timers oneshot mode
	      KVM: x86/xen: handle PV IPI vcpu yield
	      KVM: x86: declare Xen HVM evtchn offload capability
	 
	 Documentation/virtual/kvm/api.txt |   23 ++
	 arch/x86/include/asm/kvm_host.h   |   46 ++++
	 arch/x86/kvm/Makefile             |    2 +-
	 arch/x86/kvm/irq.c                |   25 ++-
	 arch/x86/kvm/irq_comm.c           |   11 +
	 arch/x86/kvm/trace.h              |   33 +++
	 arch/x86/kvm/x86.c                |   60 +++++-
	 arch/x86/kvm/x86.h                |    1 +
	 arch/x86/kvm/xen.c                | 1025 +++++++++++++++++++++++++++++
	 arch/x86/kvm/xen.h                |   48 +++++
	 include/linux/kvm_host.h          |   24 +++
	 include/uapi/linux/kvm.h          |   73 ++++++-
	 12 files changed, 1361 insertions(+), 10 deletions(-)


 2. PV Driver support (patches 17 - 39)

 We start by redirecting hypercalls from the backend to routines
 which emulate the behaviour that PV backends expect i.e. grant
 table and interdomain events. Next, we add support for late
 initialization of xenbus, followed by implementing
 frontend/backend communication mechanisms (i.e. grant tables and
 interdomain event channels). Finally, introduce xen-shim.ko,
 which will setup a limited Xen environment. This uses the added
 functionality of Xen specific shared memory (grant tables) and
 notifications (event channels).

 Note that patch 19 is useful to Xen on its own.

	 Ankur Arora (11):
	      x86/xen: export vcpu_info and shared_info
	      x86/xen: make hypercall_page generic
	      KVM: x86/xen: backend hypercall support
	      KVM: x86/xen: grant map support
	      KVM: x86/xen: grant unmap support
	      KVM: x86/xen: interdomain evtchn support
	      KVM: x86/xen: evtchn unmask support
	      KVM: x86/xen: add additional evtchn ops
	      xen-shim: introduce shim domain driver
	      xen/gntdev: xen_shim_domain() support
	      xen/xenbus: xen_shim_domain() support

	Joao Martins (12):
	      xen/xenbus: xenbus uninit support
	      xen-blkback: module_exit support
	      KVM: x86/xen: domid allocation
	      KVM: x86/xen: grant table init
	      KVM: x86/xen: grant table grow support
	      KVM: x86/xen: grant copy support
	      xen/balloon: xen_shim_domain() support
	      xen/grant-table: xen_shim_domain() support
	      drivers/xen: xen_shim_domain() support
	      xen-netback: xen_shim_domain() support
	      xen-blkback: xen_shim_domain() support
	      KVM: x86: declare Xen HVM Dom0 capability

	[See the entire series diffstat at the end]

There are additional Qemu patches to take advantage of this (and
they are available here[0][1]). An example on how you could run it would be:

$ ./x86_64-softmmu/qemu-system-x86_64 -nodefaults -serial mon:stdio \
  -machine xenfv,accel=kvm \
  -cpu host,-kvm,+xen,xen-major-version=4,xen-minor-version=4,+xen-vapic,+xen-pvclock \
  -kernel /path/to/kernel -m 16G -smp 16,sockets=1,cores=16,threads=1,maxcpus=16 \
  -append "earlyprintk=ttyS0 console=tty0 console=ttyS0" \
  -device xen-platform -device usb-ehci -device usb-tablet,bus=usb-bus.0 -vnc :0 -k pt \
  -netdev type=tap,id=net1,ifname=vif1.0,script=qemu-ifup \
  -device xen-nic,netdev=net1,mac=52:54:00:12:34:56,backendtype=vif,backend=0 \
  -drive file=/path/to/image.img,format=raw,id=legacy,if=ide \
  -blockdev file,node-name=drive,filename=/path/to/image.img,locking=off \
  -device xen-disk,vdev=xvda,drive=drive,backendtype=vbd

Naturally other options are still at your disposal (e.g. booting with q35
platform, or with virtio, etc).

Thoughts? 

Cheers,
	Joao

[0] https://www.github.com/jpemartins/qemu xen-shim-rfc
[1] https://www.github.com/jpemartins/linux xen-shim-rfc

 Documentation/virtual/kvm/api.txt        |   33 +
 arch/x86/include/asm/kvm_host.h          |   88 ++
 arch/x86/include/asm/xen/hypercall.h     |   12 +-
 arch/x86/kvm/Kconfig                     |   10 +
 arch/x86/kvm/Makefile                    |    3 +-
 arch/x86/kvm/irq.c                       |   25 +-
 arch/x86/kvm/irq_comm.c                  |   11 +
 arch/x86/kvm/trace.h                     |   33 +
 arch/x86/kvm/x86.c                       |   66 +-
 arch/x86/kvm/x86.h                       |    1 +
 arch/x86/kvm/xen-asm.S                   |   66 +
 arch/x86/kvm/xen-shim.c                  |  138 ++
 arch/x86/kvm/xen.c                       | 2262 ++++++++++++++++++++++++++++++
 arch/x86/kvm/xen.h                       |   55 +
 arch/x86/xen/enlighten.c                 |   49 +
 arch/x86/xen/enlighten_hvm.c             |    3 +-
 arch/x86/xen/enlighten_pv.c              |    1 +
 arch/x86/xen/enlighten_pvh.c             |    3 +-
 arch/x86/xen/xen-asm_32.S                |    2 +-
 arch/x86/xen/xen-asm_64.S                |    2 +-
 arch/x86/xen/xen-head.S                  |    8 +-
 drivers/block/xen-blkback/blkback.c      |   27 +-
 drivers/block/xen-blkback/common.h       |    2 +
 drivers/block/xen-blkback/xenbus.c       |   19 +-
 drivers/net/xen-netback/netback.c        |   25 +-
 drivers/xen/balloon.c                    |   15 +-
 drivers/xen/events/events_2l.c           |    4 +-
 drivers/xen/events/events_base.c         |    6 +-
 drivers/xen/events/events_fifo.c         |    2 +-
 drivers/xen/evtchn.c                     |    4 +-
 drivers/xen/features.c                   |    1 +
 drivers/xen/gntdev.c                     |   10 +-
 drivers/xen/grant-table.c                |   15 +-
 drivers/xen/privcmd.c                    |    5 +-
 drivers/xen/xenbus/xenbus.h              |    2 +
 drivers/xen/xenbus/xenbus_client.c       |   28 +-
 drivers/xen/xenbus/xenbus_dev_backend.c  |    4 +-
 drivers/xen/xenbus/xenbus_dev_frontend.c |    6 +-
 drivers/xen/xenbus/xenbus_probe.c        |   57 +-
 drivers/xen/xenbus/xenbus_xs.c           |   40 +-
 drivers/xen/xenfs/super.c                |    7 +-
 drivers/xen/xenfs/xensyms.c              |    4 +
 include/linux/kvm_host.h                 |   24 +
 include/uapi/linux/kvm.h                 |  104 +-
 include/xen/balloon.h                    |    7 +
 include/xen/xen-ops.h                    |    2 +-
 include/xen/xen.h                        |    5 +
 include/xen/xenbus.h                     |    3 +
 48 files changed, 3232 insertions(+), 67 deletions(-)
 create mode 100644 arch/x86/kvm/xen-asm.S
 create mode 100644 arch/x86/kvm/xen-shim.c
 create mode 100644 arch/x86/kvm/xen.c
 create mode 100644 arch/x86/kvm/xen.h
```
