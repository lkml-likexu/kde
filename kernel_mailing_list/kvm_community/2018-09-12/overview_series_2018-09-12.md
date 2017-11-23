#### [PATCH v2 02/17] compat_ioctl: move drivers to generic_compat_ioctl_ptrarg
##### From: Arnd Bergmann <arnd@arndb.de>

```c
Each of these drivers has a copy of the same trivial helper function to
convert the pointer argument and then call the native ioctl handler.

We now have a generic implementation of that, so use it.

Signed-off-by: Arnd Bergmann <arnd@arndb.de>
Reviewed-by: Jason Gunthorpe <jgg@mellanox.com>
Acked-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Reviewed-by: Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
---
 drivers/char/ppdev.c              | 12 +---------
 drivers/char/tpm/tpm_vtpm_proxy.c | 12 +---------
 drivers/firewire/core-cdev.c      | 12 +---------
 drivers/hid/usbhid/hiddev.c       | 11 +--------
 drivers/hwtracing/stm/core.c      | 12 +---------
 drivers/misc/mei/main.c           | 22 +----------------
 drivers/mtd/ubi/cdev.c            | 36 +++-------------------------
 drivers/net/tap.c                 | 12 +---------
 drivers/staging/pi433/pi433_if.c  | 12 +---------
 drivers/usb/core/devio.c          | 16 +------------
 drivers/vfio/vfio.c               | 39 +++----------------------------
 drivers/vhost/net.c               | 12 +---------
 drivers/vhost/scsi.c              | 12 +---------
 drivers/vhost/test.c              | 12 +---------
 drivers/vhost/vsock.c             | 12 +---------
 fs/fat/file.c                     | 13 +----------
 16 files changed, 20 insertions(+), 237 deletions(-)

```
#### [PATCH v10 01/26] KVM: s390: vsie: simulate VCPU SIE entry/exit
##### From: Tony Krowiak <akrowiak@linux.vnet.ibm.com>

```c
From: David Hildenbrand <david@redhat.com>

VCPU requests and VCPU blocking right now don't take care of the vSIE
(as it was not necessary until now). But we want to have synchronous VCPU
requests that will also be handled before running the vSIE again.

So let's simulate a SIE entry of the VCPU when calling the sie during
vSIE handling and check for PROG_ flags. The existing infrastructure
(e.g. exit_sie()) will then detect that the SIE (in form of the vSIE) is
running and properly kick the vSIE CPU, resulting in it leaving the vSIE
loop and therefore the vSIE interception handler, allowing it to handle
VCPU requests.

E.g. if we want to modify the crycb of the VCPU and make sure that any
masks also get applied to the VSIE crycb shadow (which uses masks from the
VCPU crycb), we will need a way to hinder the vSIE from running and make
sure to process the updated crycb before reentering the vSIE again.

Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c |    9 ++++++++-
 arch/s390/kvm/kvm-s390.h |    1 +
 arch/s390/kvm/vsie.c     |   21 +++++++++++++++++----
 3 files changed, 26 insertions(+), 5 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S HV: Provide mode where all vCPUs on a core must be the same VM
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
This adds a mode where the vcore scheduling logic in HV KVM limits itself
to scheduling only virtual cores from the same VM on any given physical
core.  This is enabled via a new module parameter on the kvm-hv module
called "one_vm_per_core".  For this to work on POWER9, it is necessary to
set indep_threads_mode=N.  (On POWER8, hardware limitations mean that KVM
is never in independent threads mode, regardless of the indep_threads_mode
setting.)

Thus the settings needed for this to work are:

1. The host is in SMT1 mode.
2. On POWER8, the host is not in 2-way or 4-way static split-core mode.
3. On POWER9, the indep_threads_mode parameter is N.
4. The one_vm_per_core parameter is Y.

With these settings, KVM can run up to 4 vcpus on a core at the same
time on POWER9, or up to 8 vcpus on POWER8 (depending on the guest
threading mode), and will ensure that all of the vcpus belong to the
same VM.

This is intended for use in security-conscious settings where users are
concerned about possible side-channel attacks between threads which could
perhaps enable one VM to attack another VM on the same core, or the host.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/kvm/book3s_hv.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [RFC PATCH 01/10] x86/entry: remove _TIF_ALLWORK_MASK
##### From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

```c
There is no user of _TIF_ALLWORK_MASK since commit 21d375b6b34ff
("x86/entry/64: Remove the SYSCALL64 fast path").
Remove unused define _TIF_ALLWORK_MASK.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
---
 arch/x86/include/asm/thread_info.h | 8 --------
 1 file changed, 8 deletions(-)

```
#### [PATCH net-next V2 01/11] net: sock: introduce SOCK_XDP
##### From: Jason Wang <jasowang@redhat.com>

```c
This patch introduces a new sock flag - SOCK_XDP. This will be used
for notifying the upper layer that XDP program is attached on the
lower socket, and requires for extra headroom.

TUN will be the first user.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/net/tun.c  | 19 +++++++++++++++++++
 include/net/sock.h |  1 +
 2 files changed, 20 insertions(+)

```
#### [RFC PATCH 1/2] virtio/s390: avoid race on vcdev->config
##### From: Halil Pasic <pasic@linux.ibm.com>

```c
Currently we have a race on vcdev->config in virtio_ccw_get_config() and
in virtio_ccw_set_config().

This normally does not cause problems, as these are usually infrequent
operations. But occasionally sysfs attributes are directly dependent on
pieces of virio config and trigger a get on each read. This gives us at
least one trigger.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/s390/virtio/virtio_ccw.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
