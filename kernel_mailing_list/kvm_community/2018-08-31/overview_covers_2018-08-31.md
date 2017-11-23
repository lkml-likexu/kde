

#### [PATCH V5 0/4] introduce coalesced pio support
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c

Coalesced pio is base on coalesced mmio and can be used for some port
like rtc port, pci-host config port, virtio-pci config port and so on.

Specially in case of rtc as coalesced pio, some versions of windows guest
access rtc frequently because of rtc as system tick. guest access rtc like
this: write register index to 0x70, then write or read data from 0x71.
writing 0x70 port is just as index and do nothing else. So we can use
coalesced pio to handle this scene to reduce VM-EXIT time.

When it starts and closes the virtual machine, it will access pci-host config
port or virtio-pci config port frequently. So setting these port as
coalesced pio can reduce startup and shutdown time. In qemu I just realize
piixfx's pci-host, it is convenient for other pci-host type implementations.

without my patch, get the vm-exit time of accessing rtc 0x70 and piix 0xcf8
using perf tools: (guest OS : windows 7 64bit)
IO Port Access  Samples Samples%  Time%  Min Time  Max Time  Avg time
0x70:POUT        86     30.99%    74.59%   9us      29us    10.75us (+- 3.41%)
0xcf8:POUT     1119     2.60%     2.12%   2.79us    56.83us 3.41us (+- 2.23%)

with my patch
IO Port Access  Samples Samples%  Time%   Min Time  Max Time   Avg time
0x70:POUT       106    32.02%    29.47%    0us      10us     1.57us (+- 7.38%)
0xcf8:POUT      1065    1.67%     0.28%   0.41us    65.44us   0.66us (+- 10.55%)

These are just qemu's patches, another patches are for kernel.

Changes v4 --> v5:
   update kvm header, improve compatibility.

Changes v3 --> v4
   modify coalesced_mmio_{add|del} to coalesced_io_{add|del}
   delete unnecessary macro define

Peng Hao (4):
  target-i386: introduce coalesced_pio kvm header update
  target-i386: add coalesced_pio API
  target-i386: add rtc 0x70 port as coalesced_pio
  target-i386: add i440fx 0xcf8 port as coalesced_pio

 accel/kvm/kvm-all.c       | 61 ++++++++++++++++++++++++++++++++++++++++++-----
 hw/pci-host/piix.c        |  4 ++++
 hw/timer/mc146818rtc.c    |  8 +++++++
 include/exec/memory.h     |  4 ++--
 linux-headers/linux/kvm.h | 11 +++++++--
 memory.c                  |  4 ++--
 6 files changed, 80 insertions(+), 12 deletions(-)
```
#### [PATCH 0/3] kvm "fake DAX" device
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

This patch series has implementation for "fake DAX". 
 "fake DAX" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest driver and qemu device changes in separate 
 patch sets for easy review and it has been tested together. 
 
 Details of project idea for 'fake DAX' flushing interface 
 is shared [2] & [3].

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

   David Hildenbrand CCed also posted a modified version[4] of 
   qemu virtio-pmem code based on updated Qemu memory device API. 

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

Changes from RFC v3: [1]
- Rebase to latest upstream - Luiz
- Call ndregion->flush in place of nvdimm_flush- Luiz
- kmalloc return check - Luiz
- virtqueue full handling - Stefan
- Don't map entire virtio_pmem_req to device - Stefan
- request leak,correct sizeof req- Stefan
- Move declaration to virtio_pmem.c

Changes from RFC v2:
- Add flush function in the nd_region in place of switching
  on a flag - Dan & Stefan
- Add flush completion function with proper locking and wait
  for host side flush completion - Stefan & Dan
- Keep userspace API in uapi header file - Stefan, MST
- Use LE fields & New device id - MST
- Indentation & spacing suggestions - MST & Eric
- Remove extra header files & add licensing - Stefan

Changes from RFC v1:
- Reuse existing 'pmem' code for registering persistent 
  memory and other operations instead of creating an entirely 
  new block driver.
- Use VIRTIO driver to register memory information with 
  nvdimm_bus and create region_type accordingly. 
- Call VIRTIO flush from existing pmem driver.

Pankaj Gupta (3):
   nd: move nd_region to common header
   libnvdimm: nd_region flush callback support
   virtio-pmem: Add virtio-pmem guest driver

[1] https://lkml.org/lkml/2018/7/13/102
[2] https://www.spinics.net/lists/kvm/msg149761.html
[3] https://www.spinics.net/lists/kvm/msg153095.html  
[4] https://marc.info/?l=qemu-devel&m=153555721901824&w=2

 drivers/acpi/nfit/core.c         |    7 -
 drivers/nvdimm/claim.c           |    3 
 drivers/nvdimm/nd.h              |   39 -----
 drivers/nvdimm/pmem.c            |   12 +
 drivers/nvdimm/region_devs.c     |   12 +
 drivers/virtio/Kconfig           |    9 +
 drivers/virtio/Makefile          |    1 
 drivers/virtio/virtio_pmem.c     |  255 +++++++++++++++++++++++++++++++++++++++
 include/linux/libnvdimm.h        |    4 
 include/linux/nd.h               |   40 ++++++
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   40 ++++++
 12 files changed, 374 insertions(+), 49 deletions(-)
```
#### [RFC PATCH 0/3] Use DIAG318 to set Control Program Name & Version
##### From: Collin Walling <walling@linux.ibm.com>

```c

A new diagnose instruction, 318, allows the kernel to set an 8-byte "Control 
Program Code" (CPC) that is composed of:

    1-byte Control Program Name Code (CPNC)
    7-byte Control Program Version Code (CPVC) composed of:
        3-bytes for Linux Kernel version (determined at build-time)
        3-bytes for Distribution Identifier (referred to as distro_id; set by Kconfig option)
        1-byte trailing NULL

Note about distro_id:
[
The initial idea for the 3-byte distro_id is for each distribution to set 
three characters that correspond to their distribution name (for a theoretical 
distributor "ACME," they could set "ACM" as the distro_id). A registry file 
could be included in the s390 kernel documentation to avoid name collisions.
]

This instruction call is executed once-and-only-once during Kernel setup.
The availability of this instruction depends on Read SCP Info byte 134, bit 0.
Diagnose318's functionality is also emulated by KVM, which means we can 
enable this feature for a guest even if the host cannot support it.

Also introduced with this patchset is a Host Program Identifier (HPID), which
denotes the underlying host environment.

The CPC and HPID are used for problem diagnosis and allows IBM to identify 
control program information by answering the following questions:

    "What environment is this guest running in?" (CPNC)
    "What distribution is this guest running?" (CPVC)
    "What underlying host environment is this guest running on?" (HPID)

Please note: I will be returning to the office on Thursday (9/6).

Collin Walling (3):
  s390/setup: set control program code via diag 318
  s390/kvm: handle diagnose 318 instruction call
  s390/kvm: set host program identifier

 arch/s390/Kconfig                      |  8 +++
 arch/s390/include/asm/diag.h           | 12 +++++
 arch/s390/include/asm/kvm_host.h       | 12 ++++-
 arch/s390/include/asm/sclp.h           |  1 +
 arch/s390/include/uapi/asm/kvm.h       |  5 ++
 arch/s390/kernel/diag.c                |  1 +
 arch/s390/kernel/setup.c               | 23 +++++++++
 arch/s390/kvm/diag.c                   | 16 ++++++
 arch/s390/kvm/kvm-s390.c               | 92 ++++++++++++++++++++++++++++++++++
 arch/s390/kvm/kvm-s390.h               |  1 +
 arch/s390/kvm/vsie.c                   |  2 +
 drivers/s390/char/sclp_early.c         |  6 ++-
 tools/arch/s390/include/uapi/asm/kvm.h |  1 +
 13 files changed, 177 insertions(+), 3 deletions(-)
```
