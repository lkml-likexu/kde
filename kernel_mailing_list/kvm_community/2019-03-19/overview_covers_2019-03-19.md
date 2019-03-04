

#### [PATCH 0/2] KVM: arm/arm64: vgic-its: Guest memory access fixes
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c

While messing with something completely different, I managed to
trigger a number of RCU warnings, due to the lack of srcu locking
in the ITS code.

Andre partially addressed those last year[1], but there was some
more left.

[1] http://lists.infradead.org/pipermail/linux-arm-kernel/2018-May/577056.html

Marc Zyngier (2):
  KVM: arm/arm64: vgic-its: Take the srcu lock when writing to guest
    memory
  KVM: arm/arm64: vgic-its: Take the srcu lock when parsing the memslots

 arch/arm/include/asm/kvm_mmu.h   | 11 +++++++++++
 arch/arm64/include/asm/kvm_mmu.h | 11 +++++++++++
 virt/kvm/arm/vgic/vgic-its.c     | 21 ++++++++++++++-------
 3 files changed, 36 insertions(+), 7 deletions(-)
```
#### [PATCH 0/9] RFC: NVME VFIO mediated device
> [PATCH 0/9] RFC: NVME VFIO mediated device
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c

Oops, I placed the subject in the wrong place.

Best regards,
	Maxim Levitsky

On Tue, 2019-03-19 at 16:41 +0200, Maxim Levitsky wrote:
> Date: Tue, 19 Mar 2019 14:45:45 +0200
> Subject: [PATCH 0/9] RFC: NVME VFIO mediated device
> 
> Hi everyone!
> 
> In this patch series, I would like to introduce my take on the problem of
> doing 
> as fast as possible virtualization of storage with emphasis on low latency.
> 
> In this patch series I implemented a kernel vfio based, mediated device that 
> allows the user to pass through a partition and/or whole namespace to a guest.
> 
> The idea behind this driver is based on paper you can find at
> https://www.usenix.org/conference/atc18/presentation/peng,
> 
> Although note that I stared the development prior to reading this paper, 
> independently.
> 
> In addition to that implementation is not based on code used in the paper as 
> I wasn't being able at that time to make the source available to me.
> 
> ***Key points about the implementation:***
> 
> * Polling kernel thread is used. The polling is stopped after a 
> predefined timeout (1/2 sec by default).
> Support for all interrupt driven mode is planned, and it shows promising
> results.
> 
> * Guest sees a standard NVME device - this allows to run guest with 
> unmodified drivers, for example windows guests.
> 
> * The NVMe device is shared between host and guest.
> That means that even a single namespace can be split between host 
> and guest based on different partitions.
> 
> * Simple configuration
> 
> *** Performance ***
> 
> Performance was tested on Intel DC P3700, With Xeon E5-2620 v2 
> and both latency and throughput is very similar to SPDK.
> 
> Soon I will test this on a better server and nvme device and provide
> more formal performance numbers.
> 
> Latency numbers:
> ~80ms - spdk with fio plugin on the host.
> ~84ms - nvme driver on the host
> ~87ms - mdev-nvme + nvme driver in the guest
> 
> Throughput was following similar pattern as well.
> 
> * Configuration example
>   $ modprobe nvme mdev_queues=4
>   $ modprobe nvme-mdev
> 
>   $ UUID=$(uuidgen)
>   $ DEVICE='device pci address'
>   $ echo $UUID > /sys/bus/pci/devices/$DEVICE/mdev_supported_types/nvme-
> 2Q_V1/create
>   $ echo n1p3 > /sys/bus/mdev/devices/$UUID/namespaces/add_namespace #attach
> host namespace 1 parition 3
>   $ echo 11 > /sys/bus/mdev/devices/$UUID/settings/iothread_cpu #pin the io
> thread to cpu 11
> 
>   Afterward boot qemu with
>   -device vfio-pci,sysfsdev=/sys/bus/mdev/devices/$UUID
>   
>   Zero configuration on the guest.
>   
> *** FAQ ***
> 
> * Why to make this in the kernel? Why this is better that SPDK
> 
>   -> Reuse the existing nvme kernel driver in the host. No new drivers in the
> guest.
>   
>   -> Share the NVMe device between host and guest. 
>      Even in fully virtualized configurations,
>      some partitions of nvme device could be used by guests as block devices 
>      while others passed through with nvme-mdev to achieve balance between
>      all features of full IO stack emulation and performance.
>   
>   -> NVME-MDEV is a bit faster due to the fact that in-kernel driver 
>      can send interrupts to the guest directly without a context 
>      switch that can be expensive due to meltdown mitigation.
> 
>   -> Is able to utilize interrupts to get reasonable performance. 
>      This is only implemented
>      as a proof of concept and not included in the patches, 
>      but interrupt driven mode shows reasonable performance
>      
>   -> This is a framework that later can be used to support NVMe devices 
>      with more of the IO virtualization built-in 
>      (IOMMU with PASID support coupled with device that supports it)
> 
> * Why to attach directly to nvme-pci driver and not use block layer IO
>   -> The direct attachment allows for better performance, but I will
>      check the possibility of using block IO, especially for fabrics drivers.
>   
> *** Implementation notes ***
> 
> *  All guest memory is mapped into the physical nvme device 
>    but not 1:1 as vfio-pci would do this.
>    This allows very efficient DMA.
>    To support this, patch 2 adds ability for a mdev device to listen on 
>    guest's memory map events. 
>    Any such memory is immediately pinned and then DMA mapped.
>    (Support for fabric drivers where this is not possible exits too,
>     in which case the fabric driver will do its own DMA mapping)
> 
> *  nvme core driver is modified to announce the appearance 
>    and disappearance of nvme controllers and namespaces,
>    to which the nvme-mdev driver is subscribed.
>  
> *  nvme-pci driver is modified to expose raw interface of attaching to 
>    and sending/polling the IO queues.
>    This allows the mdev driver very efficiently to submit/poll for the IO.
>    By default one host queue is used per each mediated device.
>    (support for other fabric based host drivers is planned)
> 
> * The nvme-mdev doesn't assume presence of KVM, thus any VFIO user, including
>   SPDK, a qemu running with tccg, ... can use this virtual device.
> 
> *** Testing ***
> 
> The device was tested with stock QEMU 3.0 on the host,
> with host was using 5.0 kernel with nvme-mdev added and the following
> hardware:
>  * QEMU nvme virtual device (with nested guest)
>  * Intel DC P3700 on Xeon E5-2620 v2 server
>  * Samsung SM981 (in a Thunderbolt enclosure, with my laptop)
>  * Lenovo NVME device found in my laptop
> 
> The guest was tested with kernel 4.16, 4.18, 4.20 and
> the same custom complied kernel 5.0
> Windows 10 guest was tested too with both Microsoft's inbox driver and
> open source community NVME driver
> (https://lists.openfabrics.org/pipermail/nvmewin/2016-December/001420.html)
> 
> Testing was mostly done on x86_64, but 32 bit host/guest combination
> was lightly tested too.
> 
> In addition to that, the virtual device was tested with nested guest,
> by passing the virtual device to it,
> using pci passthrough, qemu userspace nvme driver, and spdk
> 
> 
> PS: I used to contribute to the kernel as a hobby using the
>     maximlevitsky@gmail.com address
> 
> Maxim Levitsky (9):
>   vfio/mdev: add .request callback
>   nvme/core: add some more values from the spec
>   nvme/core: add NVME_CTRL_SUSPENDED controller state
>   nvme/pci: use the NVME_CTRL_SUSPENDED state
>   nvme/pci: add known admin effects to augument admin effects log page
>   nvme/pci: init shadow doorbell after each reset
>   nvme/core: add mdev interfaces
>   nvme/core: add nvme-mdev core driver
>   nvme/pci: implement the mdev external queue allocation interface
> 
>  MAINTAINERS                   |   5 +
>  drivers/nvme/Kconfig          |   1 +
>  drivers/nvme/Makefile         |   1 +
>  drivers/nvme/host/core.c      | 149 +++++-
>  drivers/nvme/host/nvme.h      |  55 ++-
>  drivers/nvme/host/pci.c       | 385 ++++++++++++++-
>  drivers/nvme/mdev/Kconfig     |  16 +
>  drivers/nvme/mdev/Makefile    |   5 +
>  drivers/nvme/mdev/adm.c       | 873 ++++++++++++++++++++++++++++++++++
>  drivers/nvme/mdev/events.c    | 142 ++++++
>  drivers/nvme/mdev/host.c      | 491 +++++++++++++++++++
>  drivers/nvme/mdev/instance.c  | 802 +++++++++++++++++++++++++++++++
>  drivers/nvme/mdev/io.c        | 563 ++++++++++++++++++++++
>  drivers/nvme/mdev/irq.c       | 264 ++++++++++
>  drivers/nvme/mdev/mdev.h      |  56 +++
>  drivers/nvme/mdev/mmio.c      | 591 +++++++++++++++++++++++
>  drivers/nvme/mdev/pci.c       | 247 ++++++++++
>  drivers/nvme/mdev/priv.h      | 700 +++++++++++++++++++++++++++
>  drivers/nvme/mdev/udata.c     | 390 +++++++++++++++
>  drivers/nvme/mdev/vcq.c       | 207 ++++++++
>  drivers/nvme/mdev/vctrl.c     | 514 ++++++++++++++++++++
>  drivers/nvme/mdev/viommu.c    | 322 +++++++++++++
>  drivers/nvme/mdev/vns.c       | 356 ++++++++++++++
>  drivers/nvme/mdev/vsq.c       | 178 +++++++
>  drivers/vfio/mdev/vfio_mdev.c |  11 +
>  include/linux/mdev.h          |   4 +
>  include/linux/nvme.h          |  88 +++-
>  27 files changed, 7375 insertions(+), 41 deletions(-)
>  create mode 100644 drivers/nvme/mdev/Kconfig
>  create mode 100644 drivers/nvme/mdev/Makefile
>  create mode 100644 drivers/nvme/mdev/adm.c
>  create mode 100644 drivers/nvme/mdev/events.c
>  create mode 100644 drivers/nvme/mdev/host.c
>  create mode 100644 drivers/nvme/mdev/instance.c
>  create mode 100644 drivers/nvme/mdev/io.c
>  create mode 100644 drivers/nvme/mdev/irq.c
>  create mode 100644 drivers/nvme/mdev/mdev.h
>  create mode 100644 drivers/nvme/mdev/mmio.c
>  create mode 100644 drivers/nvme/mdev/pci.c
>  create mode 100644 drivers/nvme/mdev/priv.h
>  create mode 100644 drivers/nvme/mdev/udata.c
>  create mode 100644 drivers/nvme/mdev/vcq.c
>  create mode 100644 drivers/nvme/mdev/vctrl.c
>  create mode 100644 drivers/nvme/mdev/viommu.c
>  create mode 100644 drivers/nvme/mdev/vns.c
>  create mode 100644 drivers/nvme/mdev/vsq.c
>
```
