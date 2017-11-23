

#### [kvm-unit-tests PATCH v1 0/2] x86: svm: Add MSR intercepts test
##### From: "Tambe, William" <William.Tambe@amd.com>

```c

Patch series adding SVM MSR intercepts test.

First patch of this series is a bugfix that has already been submitted
and acknowledged by maintainer, but is pending commit in master; it is
submitted again as part of this series to highlight it as a dependency
of the second patch of this series.

x86: svm: Fix incorrect ordering within struct regs
x86: svm: Add MSR intercepts test
```
#### [PATCH 0/1] vhost: parallel virtqueue handling
##### From: Vitaly Mayatskikh <v.mayatskih@gmail.com>

```c

Hi,

I stumbled across poor performance of virtio-blk while working on a
high-performance network storage protocol. Moving virtio-blk's host
side to kernel did increase single queue IOPS, but multiqueue disk
still was not scaling well. It turned out that vhost handles events
from all virtio queues in one helper thread, and that's pretty much a
big serialization point.

The following patch enables events handling in per-queue thread and
increases IO concurrency, see IOPS numbers:

# num-queues
# bare metal
# virtio-blk
# vhost-blk

1  171k  148k 195k 
2  328k  249k 349k 
3  479k  179k 501k 
4  622k  143k 620k 
5  755k  136k 737k 
6  887k  131k 830k 
7  1004k 126k 926k 
8  1099k 117k 1001k
9  1194k 115k 1055k
10 1278k 109k 1130k
11 1345k 110k 1119k
12 1411k 104k 1201k
13 1466k 106k 1260k
14 1517k 103k 1296k
15 1552k 102k 1322k
16 1480k 101k 1346k

Vitaly Mayatskikh (1):
  vhost: add per-vq worker thread

 drivers/vhost/vhost.c | 123 +++++++++++++++++++++++++++++++-----------
 drivers/vhost/vhost.h |  11 +++-
 2 files changed, 100 insertions(+), 34 deletions(-)
```
#### [PATCH 0/1] vhost: add vhost_blk driver
##### From: Vitaly Mayatskikh <v.mayatskih@gmail.com>

```c

vhost_blk is a host-side kernel mode accelerator for virtio-blk. The
driver allows VM to reach a near bare-metal disk performance. See IOPS
numbers below (fio --rw=randread --bs=4k).

This implementation uses kiocb interface. It is slightly slower than
going directly through bio, but is simpler and also works with disk
images placed on a file system.

# fio num-jobs
# A: bare metal over block
# B: bare metal over file
# C: virtio-blk over block
# D: virtio-blk over file
# E: vhost-blk bio over block
# F: vhost-blk kiocb over block
# G: vhost-blk kiocb over file
#
#  A     B     C    D    E     F     G

1  171k  151k  148k 151k 195k  187k  175k
2  328k  302k  249k 241k 349k  334k  296k
3  479k  437k  179k 174k 501k  464k  404k
4  622k  568k  143k 183k 620k  580k  492k
5  755k  697k  136k 128k 737k  693k  579k
6  887k  808k  131k 120k 830k  782k  640k
7  1004k 926k  126k 131k 926k  863k  693k
8  1099k 1015k 117k 115k 1001k 931k  712k
9  1194k 1119k 115k 111k 1055k 991k  711k
10 1278k 1207k 109k 114k 1130k 1046k 695k
11 1345k 1280k 110k 108k 1119k 1091k 663k
12 1411k 1356k 104k 106k 1201k 1142k 629k
13 1466k 1423k 106k 106k 1260k 1170k 607k
14 1517k 1486k 103k 106k 1296k 1179k 589k
15 1552k 1543k 102k 102k 1322k 1191k 571k
16 1480k 1506k 101k 102k 1346k 1202k 566k

Vitaly Mayatskikh (1):
  Add vhost_blk driver

 drivers/vhost/Kconfig  |  13 ++
 drivers/vhost/Makefile |   3 +
 drivers/vhost/blk.c    | 510 +++++++++++++++++++++++++++++++++++++++++
 3 files changed, 526 insertions(+)
 create mode 100644 drivers/vhost/blk.c
```
