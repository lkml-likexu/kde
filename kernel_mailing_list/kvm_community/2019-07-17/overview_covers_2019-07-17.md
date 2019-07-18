

#### [PATCH V3 00/15] Packed virtqueue support for vhost
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi all:

This series implements packed virtqueues which were described
at [1]. In this version we try to address the performance regression
saw by V2. The root cause is packed virtqueue need more times of
userspace memory accesssing which turns out to be very
expensive. Thanks to the help of 7f466032dc9e ("vhost: access vq
metadata through kernel virtual address"), such overhead cold be
eliminated. So in this version, we can see about 2% improvement for
packed virtqueue on PPS.

More optimizations (e.g IN_ORDER) is on the road.

Please review.

[1] https://docs.oasis-open.org/virtio/virtio/v1.1/csprd01/virtio-v1.1-csprd01.html#x1-610007

This version were tested with:
- zercopy/datacopy
- mergeable buffer on/off
- TCP stream & virtio-user

Changes from V2:
- rebase on top of vhost metadata accelreation series
- introduce shadow used ring API
- new SET_VRING_BASE/GET_VRING_BASE that takes care about warp counter
  and index for both avail and used
- various twaeaks

Changes from V1:
- drop uapi patch and use Tiwei's
- split the enablement of packed virtqueue into a separate patch

Changes from RFC V5:
- save unnecessary barriers during vhost_add_used_packed_n()
- more compact math for event idx
- fix failure of SET_VRING_BASE when avail_wrap_counter is true
- fix not copy avail_wrap_counter during GET_VRING_BASE
- introduce SET_VRING_USED_BASE/GET_VRING_USED_BASE for syncing
- last_used_idx
- rename used_wrap_counter to last_used_wrap_counter
- rebase to net-next

Changes from RFC V4:
- fix signalled_used index recording
- track avail index correctly
- various minor fixes

Changes from RFC V3:
- Fix math on event idx checking
- Sync last avail wrap counter through GET/SET_VRING_BASE
- remove desc_event prefix in the driver/device structure

Changes from RFC V2:
- do not use & in checking desc_event_flags
- off should be most significant bit
- remove the workaround of mergeable buffer for dpdk prototype
- id should be in the last descriptor in the chain
- keep _F_WRITE for write descriptor when adding used
- device flags updating should use ADDR_USED type
- return error on unexpected unavail descriptor in a chain
- return false in vhost_ve_avail_empty is descriptor is available
- track last seen avail_wrap_counter
- correctly examine available descriptor in get_indirect_packed()
- vhost_idx_diff should return u16 instead of bool

Changes from RFC V1:
- Refactor vhost used elem code to avoid open coding on used elem
- Event suppression support (compile test only).
- Indirect descriptor support (compile test only).
- Zerocopy support.
- vIOMMU support.
- SCSI/VSOCK support (compile test only).
- Fix several bugs

Jason Wang (15):
  vhost: simplify meta data pointer accessing
  vhost: remove the unnecessary parameter of vhost_vq_avail_empty()
  vhost: remove unnecessary parameter of
    vhost_enable_notify()/vhost_disable_notify
  vhost-net: don't use vhost_add_used_n() for zerocopy
  vhost: introduce helpers to manipulate shadow used ring
  vhost_net: switch TX to use shadow used ring API
  vhost_net: calculate last used length once for mergeable buffer
  vhost_net: switch to use shadow used ring API for RX
  vhost: do not export vhost_add_used_n() and
    vhost_add_used_and_signal_n()
  vhost: hide used ring layout from device
  vhost: do not use vring_used_elem
  vhost: vhost_put_user() can accept metadata type
  vhost: packed ring support
  vhost: event suppression for packed ring
  vhost: enable packed virtqueues

 drivers/vhost/net.c   |  200 +++---
 drivers/vhost/scsi.c  |   72 +-
 drivers/vhost/test.c  |    6 +-
 drivers/vhost/vhost.c | 1508 +++++++++++++++++++++++++++++++++++------
 drivers/vhost/vhost.h |   78 ++-
 drivers/vhost/vsock.c |   57 +-
 6 files changed, 1513 insertions(+), 408 deletions(-)
```
#### [PATCH v4 0/5] vsock/virtio: optimizations to increase the throughput
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c

This series tries to increase the throughput of virtio-vsock with slight
changes.
While I was testing the v2 of this series I discovered an huge use of memory,
so I added patch 1 to mitigate this issue. I put it in this series in order
to better track the performance trends.

v4:
- rebased all patches on current master (conflicts is Patch 4)
- Patch 1: added Stefan's R-b
- Patch 3: removed lock when buf_alloc is written [David];
           moved this patch after "vsock/virtio: reduce credit update messages"
           to make it clearer
- Patch 4: vhost_exceeds_weight() is recently introduced, so I've solved some
           conflicts

v3: https://patchwork.kernel.org/cover/10970145

v2: https://patchwork.kernel.org/cover/10938743

v1: https://patchwork.kernel.org/cover/10885431

Below are the benchmarks step by step. I used iperf3 [1] modified with VSOCK
support. As Micheal suggested in the v1, I booted host and guest with 'nosmap'.

A brief description of patches:
- Patches 1:   limit the memory usage with an extra copy for small packets
- Patches 2+3: reduce the number of credit update messages sent to the
               transmitter
- Patches 4+5: allow the host to split packets on multiple buffers and use
               VIRTIO_VSOCK_MAX_PKT_BUF_SIZE as the max packet size allowed

                    host -> guest [Gbps]
pkt_size before opt   p 1     p 2+3    p 4+5

32         0.032     0.030    0.048    0.051
64         0.061     0.059    0.108    0.117
128        0.122     0.112    0.227    0.234
256        0.244     0.241    0.418    0.415
512        0.459     0.466    0.847    0.865
1K         0.927     0.919    1.657    1.641
2K         1.884     1.813    3.262    3.269
4K         3.378     3.326    6.044    6.195
8K         5.637     5.676   10.141   11.287
16K        8.250     8.402   15.976   16.736
32K       13.327    13.204   19.013   20.515
64K       21.241    21.341   20.973   21.879
128K      21.851    22.354   21.816   23.203
256K      21.408    21.693   21.846   24.088
512K      21.600    21.899   21.921   24.106

                    guest -> host [Gbps]
pkt_size before opt   p 1     p 2+3    p 4+5

32         0.045     0.046    0.057    0.057
64         0.089     0.091    0.103    0.104
128        0.170     0.179    0.192    0.200
256        0.364     0.351    0.361    0.379
512        0.709     0.699    0.731    0.790
1K         1.399     1.407    1.395    1.427
2K         2.670     2.684    2.745    2.835
4K         5.171     5.199    5.305    5.451
8K         8.442     8.500   10.083    9.941
16K       12.305    12.259   13.519   15.385
32K       11.418    11.150   11.988   24.680
64K       10.778    10.659   11.589   35.273
128K      10.421    10.339   10.939   40.338
256K      10.300     9.719   10.508   36.562
512K       9.833     9.808   10.612   35.979

As Stefan suggested in the v1, I measured also the efficiency in this way:
    efficiency = Mbps / (%CPU_Host + %CPU_Guest)

The '%CPU_Guest' is taken inside the VM. I know that it is not the best way,
but it's provided for free from iperf3 and could be an indication.

        host -> guest efficiency [Mbps / (%CPU_Host + %CPU_Guest)]
pkt_size before opt   p 1     p 2+3    p 4+5

32         0.35      0.45     0.79     1.02
64         0.56      0.80     1.41     1.54
128        1.11      1.52     3.03     3.12
256        2.20      2.16     5.44     5.58
512        4.17      4.18    10.96    11.46
1K         8.30      8.26    20.99    20.89
2K        16.82     16.31    39.76    39.73
4K        30.89     30.79    74.07    75.73
8K        53.74     54.49   124.24   148.91
16K       80.68     83.63   200.21   232.79
32K      132.27    132.52   260.81   357.07
64K      229.82    230.40   300.19   444.18
128K     332.60    329.78   331.51   492.28
256K     331.06    337.22   339.59   511.59
512K     335.58    328.50   331.56   504.56

        guest -> host efficiency [Mbps / (%CPU_Host + %CPU_Guest)]
pkt_size before opt   p 1     p 2+3    p 4+5

32         0.43      0.43     0.53     0.56
64         0.85      0.86     1.04     1.10
128        1.63      1.71     2.07     2.13
256        3.48      3.35     4.02     4.22
512        6.80      6.67     7.97     8.63
1K        13.32     13.31    15.72    15.94
2K        25.79     25.92    30.84    30.98
4K        50.37     50.48    58.79    59.69
8K        95.90     96.15   107.04   110.33
16K      145.80    145.43   143.97   174.70
32K      147.06    144.74   146.02   282.48
64K      145.25    143.99   141.62   406.40
128K     149.34    146.96   147.49   489.34
256K     156.35    149.81   152.21   536.37
512K     151.65    150.74   151.52   519.93

[1] https://github.com/stefano-garzarella/iperf/

Stefano Garzarella (5):
  vsock/virtio: limit the memory used per-socket
  vsock/virtio: reduce credit update messages
  vsock/virtio: fix locking in virtio_transport_inc_tx_pkt()
  vhost/vsock: split packets to send using multiple buffers
  vsock/virtio: change the maximum packet size allowed

 drivers/vhost/vsock.c                   | 68 ++++++++++++-----
 include/linux/virtio_vsock.h            |  4 +-
 net/vmw_vsock/virtio_transport.c        |  1 +
 net/vmw_vsock/virtio_transport_common.c | 99 ++++++++++++++++++++-----
 4 files changed, 134 insertions(+), 38 deletions(-)
```
#### [PATCH v4 0/9] Enable Sub-page Write Protection Support
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c

EPT-Based Sub-Page write Protection(SPP)is a HW capability which allows
Virtual Machine Monitor(VMM) to specify write-permission for guest
physical memory at a sub-page(128 byte) granularity. When this
capability is enabled, the CPU enforces write-access check for sub-pages
within a 4KB page.

The feature is targeted to provide fine-grained memory protection for
usages such as device virtualization, memory check-point and VM
introspection etc.

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

Please refer to the SPP introduction document in this patch set and
Intel SDM for details:

Intel SDM:
https://software.intel.com/sites/default/files/managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Previous patch:
https://lkml.org/lkml/2019/6/6/695

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

V3 -> v4:
  1. Modified documentation to make it consistent with patches.
  2. Allocated SPPT root page in init_spp() instead of vmx_set_cr3() to
     avoid SPPT miss error.
  3. Added back co-developers and sign-offs.

V2 -> V3:                                                                
  1. Rebased patches to kernel 5.1 release                                
  2. Deferred SPPT setup to EPT fault handler if the page is not
     available while set_subpage() is being called.
  3. Added init IOCTL to reduce extra cost if SPP is not used.
  4. Refactored patch structure, cleaned up cross referenced functions.
  5. Added code to deal with memory swapping/migration/shrinker cases.

V2 -> V1:
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

 Documentation/virtual/kvm/spp_kvm.txt | 173 ++++++++++
 arch/x86/include/asm/cpufeatures.h    |   1 +
 arch/x86/include/asm/kvm_host.h       |  26 +-
 arch/x86/include/asm/vmx.h            |  10 +
 arch/x86/include/uapi/asm/vmx.h       |   2 +
 arch/x86/kernel/cpu/intel.c           |   4 +
 arch/x86/kvm/mmu.c                    | 480 ++++++++++++++++++++++++++
 arch/x86/kvm/mmu.h                    |   1 +
 arch/x86/kvm/vmx/capabilities.h       |   5 +
 arch/x86/kvm/vmx/vmx.c                | 129 +++++++
 arch/x86/kvm/x86.c                    | 141 ++++++++
 include/linux/kvm_host.h              |   9 +
 include/uapi/linux/kvm.h              |  17 +
 13 files changed, 997 insertions(+), 1 deletion(-)
 create mode 100644 Documentation/virtual/kvm/spp_kvm.txt
```
