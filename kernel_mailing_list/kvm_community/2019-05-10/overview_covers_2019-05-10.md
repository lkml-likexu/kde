

#### [PATCH 0/4] Retrieving zPCI specific info with VFIO
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

Using the PCI VFIO interface allows userland, a.k.a. QEMU, to retrieve
ZPCI specific information without knowing Z specific identifiers
like the function ID or the function handle of the zPCI function
hidden behind the PCI interface. 
  
By using the VFIO_IOMMU_GET_INFO ioctl we enter the vfio_iommu_type1
ioctl callback and can insert there the treatment for a new Z specific
capability.
  
Once in vfio_iommu_type1 we can retrieve the real iommu device,
s390_iommu and call the get_attr iommu operation's callback
in which we can retrieve the zdev device and start clp operations
to retrieve Z specific values the guest driver is concerned with.
 
To share the code with arch/s390/pci/pci_clp.c the original functions
in pci_clp.c to query PCI functions and PCI functions group are
modified so that they can be exported.

A new function clp_query_pci() replaces clp_query_pci_fn() and
the previous calls to clp_query_pci_fn() and clp_query_pci_fngrp()
are replaced with calls to zdev_query_pci_fn() and zdev_query_pci_fngrp()
using a zdev pointer as argument.

These two functions are exported to be used from out of the s390_iommu
code.

Pierre Morel (4):
  s390: pci: Exporting access to CLP PCI function and PCI group
  vfio: vfio_iommu_type1: Define VFIO_IOMMU_INFO_CAPABILITIES
  s390: iommu: Adding get attributes for s390_iommu
  vfio: vfio_iommu_type1: implement VFIO_IOMMU_INFO_CAPABILITIES

 arch/s390/include/asm/pci.h     |  3 ++
 arch/s390/pci/pci_clp.c         | 72 ++++++++++++++++---------------
 drivers/iommu/s390-iommu.c      | 77 +++++++++++++++++++++++++++++++++
 drivers/vfio/vfio_iommu_type1.c | 95 ++++++++++++++++++++++++++++++++++++++++-
 include/linux/iommu.h           |  4 ++
 include/uapi/linux/vfio.h       | 10 +++++
 6 files changed, 226 insertions(+), 35 deletions(-)
```
#### [PATCH v2 0/8] vsock/virtio: optimizations to increase the throughput
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c

While I was testing this new series (v2) I discovered an huge use of memory
and a memory leak in the virtio-vsock driver in the guest when I sent
1-byte packets to the guest.

These issues are present since the introduction of the virtio-vsock
driver. I added the patches 1 and 2 to fix them in this series in order
to better track the performance trends.

v1: https://patchwork.kernel.org/cover/10885431/

v2:
- Add patch 1 to limit the memory usage
- Add patch 2 to avoid memory leak during the socket release
- Add patch 3 to fix locking of fwd_cnt and buf_alloc
- Patch 4: fix 'free_space' type (u32 instead of s64) [Stefan]
- Patch 5: Avoid integer underflow of iov_len [Stefan]
- Patch 5: Fix packet capture in order to see the exact packets that are
           delivered. [Stefan]
- Add patch 8 to make the RX buffer size tunable [Stefan]

Below are the benchmarks step by step. I used iperf3 [1] modified with VSOCK
support.
As Micheal suggested in the v1, I booted host and guest with 'nosmap', and I
added a column with virtio-net+vhost-net performance.

A brief description of patches:
- Patches 1+2: limit the memory usage with an extra copy and avoid memory leak
- Patches 3+4: fix locking and reduce the number of credit update messages sent
               to the transmitter
- Patches 5+6: allow the host to split packets on multiple buffers and use
               VIRTIO_VSOCK_MAX_PKT_BUF_SIZE as the max packet size allowed
- Patches 7+8: increase RX buffer size to 64 KiB

                    host -> guest [Gbps]
pkt_size before opt  p 1+2    p 3+4    p 5+6    p 7+8       virtio-net + vhost
                                                                     TCP_NODELAY
64         0.068     0.063    0.130    0.131    0.128         0.188     0.187
256        0.274     0.236    0.392    0.338    0.282         0.749     0.654
512        0.531     0.457    0.862    0.725    0.602         1.419     1.414
1K         0.954     0.827    1.591    1.598    1.548         2.599     2.640
2K         1.783     1.543    3.731    3.637    3.469         4.530     4.754
4K         3.332     3.436    7.164    7.124    6.494         7.738     7.696
8K         5.792     5.530   11.653   11.787   11.444        12.307    11.850
16K        8.405     8.462   16.372   16.855   17.562        16.936    16.954
32K       14.208    13.669   18.945   20.009   23.128        21.980    23.015
64K       21.082    18.893   20.266   20.903   30.622        27.290    27.383
128K      20.696    20.148   20.112   21.746   32.152        30.446    30.990
256K      20.801    20.589   20.725   22.685   34.721        33.151    32.745
512K      21.220    20.465   20.432   22.106   34.496        36.847    31.096

                    guest -> host [Gbps]
pkt_size before opt  p 1+2    p 3+4    p 5+6    p 7+8       virtio-net + vhost
                                                                     TCP_NODELAY
64         0.089     0.091    0.120    0.115    0.117         0.274     0.272
256        0.352     0.354    0.452    0.445    0.451         1.085     1.136
512        0.705     0.704    0.893    0.858    0.898         2.131     1.882
1K         1.394     1.433    1.721    1.669    1.691         3.984     3.576
2K         2.818     2.874    3.316    3.249    3.303         6.719     6.359
4K         5.293     5.397    6.129    5.933    6.082        10.105     9.860
8K         8.890     9.151   10.990   10.545   10.519        15.239    14.868
16K       11.444    11.018   12.074   15.255   15.577        20.551    20.848
32K       11.229    10.875   10.857   24.401   25.227        26.294    26.380
64K       10.832    10.545   10.816   39.487   39.616        34.996    32.041
128K      10.435    10.241   10.500   39.813   40.012        38.379    35.055
256K      10.263     9.866    9.845   34.971   35.143        36.559    37.232
512K      10.224    10.060   10.092   35.469   34.627        34.963    33.401

As Stefan suggested in the v1, this time I measured also the efficiency in this
way:
    efficiency = Mbps / (%CPU_Host + %CPU_Guest)

The '%CPU_Guest' is taken inside the VM. I know that it is not the best way,
but it's provided for free from iperf3 and could be an indication.

        host -> guest efficiency [Mbps / (%CPU_Host + %CPU_Guest)]
pkt_size before opt  p 1+2    p 3+4    p 5+6    p 7+8       virtio-net + vhost
                                                                     TCP_NODELAY
64          0.94      0.59     3.96     4.06     4.09          2.82      2.11
256         2.62      2.50     6.45     6.09     5.81          9.64      8.73
512         5.16      4.87    13.16    12.39    11.67         17.83     17.76
1K          9.16      8.85    24.98    24.97    25.01         32.57     32.04
2K         17.41     17.03    49.09    48.59    49.22         55.31     57.14
4K         32.99     33.62    90.80    90.98    91.72         91.79     91.40
8K         58.51     59.98   153.53   170.83   167.31        137.51    132.85
16K        89.32     95.29   216.98   264.18   260.95        176.05    176.05
32K       152.94    167.10   285.75   387.02   360.81        215.49    226.30
64K       250.38    307.20   317.65   489.53   472.70        238.97    244.27
128K      327.99    335.24   335.76   523.71   486.41        253.29    260.86
256K      327.06    334.24   338.64   533.76   509.85        267.78    266.22
512K      337.36    330.61   334.95   512.90   496.35        280.42    241.43

        guest -> host efficiency [Mbps / (%CPU_Host + %CPU_Guest)]
pkt_size before opt  p 1+2    p 3+4    p 5+6    p 7+8       virtio-net + vhost
                                                                     TCP_NODELAY
64          0.90      0.91     1.37     1.32     1.35          2.15      2.13
256         3.59      3.55     5.23     5.19     5.29          8.50      8.89
512         7.19      7.08    10.21     9.95    10.38         16.74     14.71
1K         14.15     14.34    19.85    19.06    19.33         31.44     28.11
2K         28.44     29.09    37.78    37.18    37.49         53.07     50.63
4K         55.37     57.60    71.02    69.27    70.97         81.56     79.32
8K        105.58    100.45   111.95   124.68   123.61        120.85    118.66
16K       141.63    138.24   137.67   187.41   190.20        160.43    163.00
32K       147.56    143.09   138.48   296.41   301.04        214.64    223.94
64K       144.81    143.27   138.49   433.98   462.26        298.86    269.71
128K      150.14    147.99   146.85   511.36   514.29        350.17    298.09
256K      156.69    152.25   148.69   542.19   549.97        326.42    333.32
512K      157.29    153.35   152.22   546.52   533.24        315.55    302.27

[1] https://github.com/stefano-garzarella/iperf/

Stefano Garzarella (8):
  vsock/virtio: limit the memory used per-socket
  vsock/virtio: free packets during the socket release
  vsock/virtio: fix locking for fwd_cnt and buf_alloc
  vsock/virtio: reduce credit update messages
  vhost/vsock: split packets to send using multiple buffers
  vsock/virtio: change the maximum packet size allowed
  vsock/virtio: increase RX buffer size to 64 KiB
  vsock/virtio: make the RX buffer size tunable

 drivers/vhost/vsock.c                   |  53 +++++++--
 include/linux/virtio_vsock.h            |  14 ++-
 net/vmw_vsock/virtio_transport.c        |  28 ++++-
 net/vmw_vsock/virtio_transport_common.c | 144 ++++++++++++++++++------
 4 files changed, 190 insertions(+), 49 deletions(-)
```
#### [PATCH v8 0/6] virtio pmem driver 
##### From: Pankaj Gupta <pagupta@redhat.com>

```c

Hi Michael & Dan,

 Please review/ack the patch series from LIBNVDIMM & VIRTIO side.
 We have ack on ext4, xfs patches(4, 5 & 6) patch 2. Still need
 your ack on nvdimm patches(1 & 3) & virtio patch 2. 

 Changes done from v7 are only in patch(2 & 3) and not
 affecting existing reviews. Request to please review.
 ----

 This patch series has implementation for "virtio pmem". 
 "virtio pmem" is fake persistent memory(nvdimm) in guest 
 which allows to bypass the guest page cache. This also
 implements a VIRTIO based asynchronous flush mechanism.  
 
 Sharing guest kernel driver in this patchset with the 
 changes suggested in v4. Tested with Qemu side device 
 emulation [6] for virtio-pmem. Documented the impact of
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

   David Hildenbrand CCed also posted a modified version[7] of 
   qemu virtio-pmem code based on updated Qemu memory device API. 

 Virtio-pmem security implications and countermeasures:
 -----------------------------------------------------

 In previous posting of kernel driver, there was discussion [9]
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

 - Proposed device specification [8] for virtio-pmem device with 
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

Changes from PATCH v7: [1]
 - Corrected pending request queue logic (patch 2) - Jakub Staroń
 - Used unsigned long flags for passing DAXDEV_F_SYNC (patch 3) - Dan
 - Fixed typo =>  vma 'flag' to 'vm_flag' (patch 4)
 - Added rob in patch 6 & patch 2

Changes from PATCH v6: [1]
 - Corrected comment format in patch 5 & patch 6. [Dave]
 - Changed variable declaration indentation in patch 6 [Darrick]
 - Add Reviewed-by tag by 'Jan Kara' in patch 4 & patch 5

Changes from PATCH v5: [2]
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

Pankaj Gupta (6):
   libnvdimm: nd_region flush callback support
   virtio-pmem: Add virtio-pmem guest driver
   libnvdimm: add nd_region buffered dax_dev flag
   dax: check synchronous mapping is supported
   ext4: disable map_sync for virtio pmem
   xfs: disable map_sync for virtio pmem

[1] https://lkml.org/lkml/2019/4/26/36
[2] https://lkml.org/lkml/2019/4/23/1092
[3] https://www.spinics.net/lists/kvm/msg149761.html
[4] https://www.spinics.net/lists/kvm/msg153095.html  
[5] https://lkml.org/lkml/2018/8/31/413
[6] https://marc.info/?l=linux-kernel&m=153572228719237&w=2 
[7] https://marc.info/?l=qemu-devel&m=153555721901824&w=2
[8] https://lists.oasis-open.org/archives/virtio-dev/201903/msg00083.html
[9] https://lkml.org/lkml/2019/1/9/1191

 drivers/acpi/nfit/core.c         |    4 -
 drivers/dax/bus.c                |    2 
 drivers/dax/super.c              |   13 +++
 drivers/md/dm.c                  |    3 
 drivers/nvdimm/Makefile          |    1 
 drivers/nvdimm/claim.c           |    6 +
 drivers/nvdimm/nd.h              |    1 
 drivers/nvdimm/nd_virtio.c       |  129 +++++++++++++++++++++++++++++++++++++++
 drivers/nvdimm/pmem.c            |   18 +++--
 drivers/nvdimm/region_devs.c     |   33 +++++++++
 drivers/nvdimm/virtio_pmem.c     |  117 +++++++++++++++++++++++++++++++++++
 drivers/virtio/Kconfig           |   10 +++
 fs/ext4/file.c                   |   10 +--
 fs/xfs/xfs_file.c                |    9 +-
 include/linux/dax.h              |   25 ++++++-
 include/linux/libnvdimm.h        |    9 ++
 include/linux/virtio_pmem.h      |   60 ++++++++++++++++++
 include/uapi/linux/virtio_ids.h  |    1 
 include/uapi/linux/virtio_pmem.h |   10 +++
 19 files changed, 436 insertions(+), 25 deletions(-)
```
