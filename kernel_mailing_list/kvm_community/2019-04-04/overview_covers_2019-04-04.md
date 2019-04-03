

#### [PATCH RFC 0/4] vsock/virtio: optimizations to increase the
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c

This series tries to increase the throughput of virtio-vsock with slight
changes:
 - patch 1/4: reduces the number of credit update messages sent to the
              transmitter
 - patch 2/4: allows the host to split packets on multiple buffers,
              in this way, we can remove the packet size limit to
              VIRTIO_VSOCK_DEFAULT_RX_BUF_SIZE
 - patch 3/4: uses VIRTIO_VSOCK_MAX_PKT_BUF_SIZE as the max packet size
              allowed
 - patch 4/4: increases RX buffer size to 64 KiB (affects only host->guest)

RFC:
 - maybe patch 4 can be replaced with multiple queues with different
   buffer sizes or using EWMA to adapt the buffer size to the traffic

 - as Jason suggested in a previous thread [1] I'll evaluate to use
   virtio-net as transport, but I need to understand better how to
   interface with it, maybe introducing sk_buff in virtio-vsock.

Any suggestions?

Here some benchmarks step by step. I used iperf3 [2] modified with VSOCK
support:

                        host -> guest [Gbps]
pkt_size    before opt.   patch 1   patches 2+3   patch 4
  64            0.060       0.102       0.102       0.096
  256           0.22        0.40        0.40        0.36
  512           0.42        0.82        0.85        0.74
  1K            0.7         1.6         1.6         1.5
  2K            1.5         3.0         3.1         2.9
  4K            2.5         5.2         5.3         5.3
  8K            3.9         8.4         8.6         8.8
  16K           6.6        11.1        11.3        12.8
  32K           9.9        15.8        15.8        18.1
  64K          13.5        17.4        17.7        21.4
  128K         17.9        19.0        19.0        23.6
  256K         18.0        19.4        19.8        24.4
  512K         18.4        19.6        20.1        25.3

                        guest -> host [Gbps]
pkt_size    before opt.   patch 1   patches 2+3
  64            0.088       0.100       0.101
  256           0.35        0.36        0.41
  512           0.70        0.74        0.73
  1K            1.1         1.3         1.3
  2K            2.4         2.4         2.6
  4K            4.3         4.3         4.5
  8K            7.3         7.4         7.6
  16K           9.2         9.6        11.1
  32K           8.3         8.9        18.1
  64K           8.3         8.9        25.4
  128K          7.2         8.7        26.7
  256K          7.7         8.4        24.9
  512K          7.7         8.5        25.0

Thanks,
Stefano

[1] https://www.spinics.net/lists/netdev/msg531783.html
[2] https://github.com/stefano-garzarella/iperf/

Stefano Garzarella (4):
  vsock/virtio: reduce credit update messages
  vhost/vsock: split packets to send using multiple buffers
  vsock/virtio: change the maximum packet size allowed
  vsock/virtio: increase RX buffer size to 64 KiB

 drivers/vhost/vsock.c                   | 35 ++++++++++++++++++++-----
 include/linux/virtio_vsock.h            |  3 ++-
 net/vmw_vsock/virtio_transport_common.c | 18 +++++++++----
 3 files changed, 44 insertions(+), 12 deletions(-)
```
#### [PATCH kvmtool v2 0/9] Disk fixes and AIO reset
##### From: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

```c

Changes since v1 [1]:
* Added review tags
* Fixed lkvm-static build, using $(OBJS_STATOPT/DYNOPT) in the makefile
  rather than $(OBJS).

Patches 1-7 fix a few issues found while testing disk backends, and
patches 8-9 implement reset for the AIO backend. By draining the AIO
queue on reset, we avoid writing I/O completions to the used ring after
the guest reclaimed the ring's pages.

[1] https://www.spinics.net/lists/kvm/msg182324.html

Jean-Philippe Brucker (9):
  qcow: Fix qcow1 exit fault
  virtio/blk: Set VIRTIO_BLK_F_RO when the disk is read-only
  guest: sync disk before shutting down
  disk/aio: Refactor AIO code
  disk/aio: Fix use of disk->async
  disk/aio: Fix AIO thread
  disk/aio: Cancel AIO thread on cleanup
  disk/aio: Add wait() disk operation
  virtio/blk: sync I/O on reset

 Makefile                 |   2 +
 disk/aio.c               | 150 +++++++++++++++++++++++++++++++++++++++
 disk/blk.c               |  10 +--
 disk/core.c              |  69 ++++++++----------
 disk/qcow.c              |   3 +-
 disk/raw.c               |  56 +++------------
 guest/init.c             |   1 +
 include/kvm/disk-image.h |  53 ++++++++++++--
 include/kvm/read-write.h |  11 ---
 util/read-write.c        |  36 ----------
 virtio/blk.c             |   7 +-
 11 files changed, 249 insertions(+), 149 deletions(-)
 create mode 100644 disk/aio.c
```
