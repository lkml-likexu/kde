#### [kvm-unit-tests PATCH] Add VMX INS/OUTS testFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Test that all of the appropriate exit information is provided to L1
for INS and OUTS instructions intercepted in L2.

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
---
 lib/x86/msr.h     |  3 ++
 x86/unittests.cfg |  6 +++
 x86/vmx.h         | 17 ++++++++
 x86/vmx_tests.c   | 98 +++++++++++++++++++++++++++++++++++++++++++++++
 4 files changed, 124 insertions(+)

```
#### [kvm-unit-tests PATCH] s390x: Add linemode buffer to fix newline on every print
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Linemode seems to add a newline for each sent message which makes
reading rather hard. Hence we add a small buffer and only print if
it's full or a newline is encountered. Except for when the string is
longer than the buffer, then we flush the buffer and print directly.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---

How about something like this, splitting buffer handling and actual
printing, while adding buffer that's separate from the sclp locking. I
hope that all offsets and ptrs are correct despite the weekday and
hour...

---
 lib/s390x/sclp-console.c | 71 +++++++++++++++++++++++++++++++++++++++++++++---
 1 file changed, 67 insertions(+), 4 deletions(-)

```
#### [PATCH net V3] vhost: log dirty page correctly
##### From: Jason Wang <jasowang@redhat.com>

```c
Vhost dirty page logging API is designed to sync through GPA. But we
try to log GIOVA when device IOTLB is enabled. This is wrong and may
lead to missing data after migration.

To solve this issue, when logging with device IOTLB enabled, we will:

1) reuse the device IOTLB translation result of GIOVA->HVA mapping to
   get HVA, for writable descriptor, get HVA through iovec. For used
   ring update, translate its GIOVA to HVA
2) traverse the GPA->HVA mapping to get the possible GPA and log
   through GPA. Pay attention this reverse mapping is not guaranteed
   to be unique, so we should log each possible GPA in this case.

This fix the failure of scp to guest during migration. In -next, we
will probably support passing GIOVA->GPA instead of GIOVA->HVA.

Fixes: 6b1e6cc7855b ("vhost: new device IOTLB API")
Reported-by: Jintack Lim <jintack@cs.columbia.edu>
Cc: Jintack Lim <jintack@cs.columbia.edu>
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
Changes from V2:
- check and log the case of range overlap
- remove unnecessary u64 cast
- use smp_wmb() for the case of device IOTLB as well
Changes from V1:
- return error instead of warn
---
 drivers/vhost/net.c   |  3 +-
 drivers/vhost/vhost.c | 88 ++++++++++++++++++++++++++++++++++++-------
 drivers/vhost/vhost.h |  3 +-
 3 files changed, 78 insertions(+), 16 deletions(-)

```
#### [PATCH v2 1/3] migration: introduce pages-per-second
##### From: guangrong.xiao@gmail.com

```c
From: Xiao Guangrong <xiaoguangrong@tencent.com>

It introduces a new statistic, pages-per-second, as bandwidth or mbps is
not enough to measure the performance of posting pages out as we have
compression, xbzrle, which can significantly reduce the amount of the
data size, instead, pages-per-second is the one we want

Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
---
 hmp.c                 |  2 ++
 migration/migration.c | 11 ++++++++++-
 migration/migration.h |  8 ++++++++
 migration/ram.c       |  6 ++++++
 qapi/migration.json   |  5 ++++-
 5 files changed, 30 insertions(+), 2 deletions(-)

```
