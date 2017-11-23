

#### [PATCH v2 0/4] vhost/scsi: Respond to control queue operations
##### From: Bijan Mottahedeh <bijan.mottahedeh@oracle.com>

```c

v1 -> v2:

- Use copy_to_iter() to send control queue response

This patch series causes vhost-scsi control queue TMF requests to be
explicitly rejected rather than implicitly ignored in order to prevent
a guest virito-scsi driver to wait indefinitely for a response to a SCSI
TMF request.

In addition, control queue address notification operations
(VIRTIO_SCSI_T_AN_*) get an effective no-op response.

Patch 1/4 implements a control queue handler modeled after the existing
request queue handler.  There is no commonality between the two handlers.

Patch 2/4 factors out the common processing code from the control queue
handler into separate routines.

Patch 3/4 modifies the request handler to use the common processing routines.  

Patch 4/4 uses copy_to_iter() to send back control queue responses.

Bijan Mottahedeh (4):
  vhost/scsi: Respond to control queue operations
  vhost/scsi: Extract common handling code from control queue handler
  vhost/scsi: Use common handling code in request queue handler
  vhost/scsi: Use copy_to_iter() to send control queue response

 drivers/vhost/scsi.c | 426 +++++++++++++++++++++++++++++++++++++++------------
 1 file changed, 330 insertions(+), 96 deletions(-)
```
#### [PATCH kvmtool 00/13] Implement reset of virtio devices
##### From: Julien Thierry <julien.thierry@arm.com>

```c

Hi,

This series was developped by Jean-Philippe and is needed for a series
I'll be posting shortly after to load firmwares on arm kvmtool.

Currently, when a guest tries to reset a device, a lot of ressources
aren't reset (threads keep running, virtio queue keep their state, etc).

When the guest only does the reset to initialize the device and there
were no previous users, there is no noticeable issue. But when a guest
has a firmare + Linux, if the firmware uses a virtio device, Linux will
fail to probe that device.

This series aim to properly reset the virtio resources when the guests
requests it.

Reset of net vhost is unsupported for now.

Patch 1 is a bug fix on ioeventfd
Patch 2-6 provide the core support so devices can implement their reset
Patch 7-13 implements the reset for the various virtio devices

Thanks,

Julien

-->

Jean-Philippe Brucker (13):
  ioeventfd: Fix removal of ioeventfd
  virtio: Implement notify_status
  virtio: Add get_vq_count() callback
  virtio: Add get_vq() callback
  virtio: Add exit_vq() callback
  virtio: Add reset() callback
  net/uip: Add exit function
  virtio/net: Clean virtqueue state
  virtio/net: Implement device and virtqueue reset
  virtio/blk: Reset virtqueue
  threadpool: Add cancel() function
  virtio/p9: Implement reset
  virtio/console: Implement reset

 include/kvm/threadpool.h  |   2 +
 include/kvm/uip.h         |   6 ++
 include/kvm/virtio-mmio.h |   1 +
 include/kvm/virtio-pci.h  |   1 +
 include/kvm/virtio.h      |  30 ++++++-
 ioeventfd.c               |   6 +-
 net/uip/core.c            |  17 ++++
 net/uip/dhcp.c            |   6 ++
 net/uip/tcp.c             |  54 ++++++++++---
 net/uip/udp.c             |  41 ++++++++--
 util/threadpool.c         |  25 +++++-
 virtio/9p.c               |  33 +++++++-
 virtio/balloon.c          |  17 +++-
 virtio/blk.c              |  84 ++++++++++++++------
 virtio/console.c          |  49 ++++++++----
 virtio/core.c             |  42 ++++++++++
 virtio/mmio.c             |  52 +++++++++----
 virtio/net.c              | 195 +++++++++++++++++++++++++++++++++-------------
 virtio/pci.c              |  49 ++++++++----
 virtio/rng.c              |  12 ++-
 virtio/scsi.c             |  17 +++-
 21 files changed, 582 insertions(+), 157 deletions(-)
---
1.9.1
```
#### [PATCH kvmtool 0/6] arm: Add support for firmware booting
##### From: Julien Thierry <julien.thierry@arm.com>

```c

Hi,

This series is based on the virtio reset series posted earlier:
https://marc.info/?l=kvm&m=154392174625966&w=2

We would like to be able to load firmwares like UEFI in kvmtool.

The series contains:
A way to load the firmware into RAM and an option to be able to create
non-volatile memory zones and load data into them.

Those non-volatile memory are presented throught the DT with a node:

	<name>@<addr> {
		compatible = "kvmtool,<name>";
		reg = < <addr> <size> >;
	}

These are expected to be dealt with by specific kvmtool driver and not
to be picked up by existing drivers (although technically it is just
plain memory, mapped in the guest).

Cheers,

Julien

-->

Julien Thierry (5):
  arm: Move firmware function
  builtin-run: Do not look for default kernel when firmware is provided
  arm: Support firmware loading
  kvm: Add arch specific reset
  arm: Support non-volatile memory

Sami Mujawar (1):
  rtc: Initialize the Register D for MC146818 RTC

 arm/fdt.c                                |  67 ++++++++--
 arm/include/arm-common/kvm-arch.h        |   5 +-
 arm/include/arm-common/kvm-config-arch.h |  21 +++-
 arm/kvm.c                                | 204 +++++++++++++++++++++++++++++++
 builtin-run.c                            |  24 ++--
 hw/rtc.c                                 |   8 ++
 include/kvm/kvm.h                        |   1 +
 kvm.c                                    |   2 +
 mips/kvm.c                               |   4 +
 powerpc/kvm.c                            |   4 +
 x86/kvm.c                                |   4 +
 11 files changed, 323 insertions(+), 21 deletions(-)
---
1.9.1
```
#### [kvm-unit-tests PATCH 0/5] s390x: Add cross hypervisor and disk boot
##### From: Janosch Frank <frankja@linux.ibm.com>

```c

With these patches kvm unit tests are now bootable under LPAR and
z/VM, as well as from KVM disks. Don't forget to convert the ELF files
to binary via:

objcopy -O binary s390x/test.elf test.bin

For this to work we added:
    * Initial PSW in lowcore
    * Switch to 64 bit and z/Arch
    * SCLP linemode console

This is an early version, linemode currently splits lines a bit too
often and I still need to polish comments and cleanup code.

Janosch Frank (5):
  s390x: Make tests bootable from disk
  s390x: Switch to z/Arch if needed
  s390x: Add BSS clearing for non ELF boot
  s390x: Use interrupts in SCLP and add line mode
  s390x: Fix sclp-ascii.c indents

 lib/s390x/asm/arch_def.h  |   1 +
 lib/s390x/asm/interrupt.h |   2 +
 lib/s390x/interrupt.c     |  12 ++-
 lib/s390x/io.c            |   2 +-
 lib/s390x/sclp-ascii.c    | 220 ++++++++++++++++++++++++++++++++++++++--------
 lib/s390x/sclp.c          |  42 +++++++++
 lib/s390x/sclp.h          |  71 ++++++++++++++-
 s390x/cstart64.S          |  40 ++++++++-
 s390x/flat.lds            |  10 ++-
 9 files changed, 357 insertions(+), 43 deletions(-)
```
#### [PATCH v1 0/2] Use DIAG318 to set Control Program Name & Version
##### From: Collin Walling <walling@linux.ibm.com>

```c

Changelog

    RFC -> v1
        - set distro_id to 0 for now and will be introduced properly as a follow-on
            patch with further details wrt its usage
        - created diag318 union structure to contain CPC data in kvm
        - removed VCPU_EVENT from diag318 handler (we still see a VM_EVENT)

A new diagnose instruction, 318, allows the kernel to set an 8-byte "Control 
Program Code" (CPC) that is composed of:

    1-byte Control Program Name Code (CPNC)
    7-byte Control Program Version Code (CPVC) composed of:
        3-bytes for Linux Kernel version (determined at build-time)
        3-bytes for *Distribution Identifier (currently set to 0)
        1-byte trailing NULL

*The distribution identifier will be introduced as a follow-on patch.

This instruction call is executed once-and-only-once during Kernel setup.
The availability of this instruction depends on Read SCP Info byte 134, bit 0.
Diagnose318's functionality is also emulated by KVM, which means we can 
enable this feature for a guest even if the host kernel cannot support it.

The CPNC and CPVC are used for problem diagnosis and allows IBM to identify 
control program information by answering the following questions:

    "What environment is this guest running in?" (CPNC)
    "What linux version is this guest running?" (CPVC)

Collin Walling (2):
  s390/setup: set control program code via diag 318
  s390/kvm: handle diagnose 318 instruction call

 arch/s390/include/asm/diag.h     | 12 ++++++
 arch/s390/include/asm/kvm_host.h | 13 +++++-
 arch/s390/include/asm/sclp.h     |  1 +
 arch/s390/include/uapi/asm/kvm.h |  5 +++
 arch/s390/kernel/diag.c          |  1 +
 arch/s390/kernel/setup.c         | 21 ++++++++++
 arch/s390/kvm/diag.c             | 12 ++++++
 arch/s390/kvm/kvm-s390.c         | 88 ++++++++++++++++++++++++++++++++++++++++
 arch/s390/kvm/kvm-s390.h         |  1 +
 drivers/s390/char/sclp.h         |  4 +-
 drivers/s390/char/sclp_early.c   |  2 +
 11 files changed, 158 insertions(+), 2 deletions(-)
```
