#### [PULL 1/1] vfio: ccw: only free cp on final interrupt
##### From: Cornelia Huck <cohuck@redhat.com>

```c
When we get an interrupt for a channel program, it is not
necessarily the final interrupt; for example, the issuing
guest may request an intermediate interrupt by specifying
the program-controlled-interrupt flag on a ccw.

We must not switch the state to idle if the interrupt is not
yet final; even more importantly, we must not free the translated
channel program if the interrupt is not yet final, or the host
can crash during cp rewind.

Fixes: e5f84dbaea59 ("vfio: ccw: return I/O results asynchronously")
Cc: stable@vger.kernel.org # v4.12+
Reviewed-by: Eric Farman <farman@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_drv.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH 1/3] userfaultfd/sysctl: introduce unprivileged_userfaultfd
##### From: Peter Xu <peterx@redhat.com>

```c
Introduce a new sysctl called "vm.unprivileged_userfaultfd" that can
be used to decide whether userfaultfd syscalls are allowed by
unprivileged users.  It'll allow three modes:

  - disabled: disallow unprivileged users to use uffd

  - enabled:  allow unprivileged users to use uffd

  - kvm:      allow unprivileged users to use uffd only if the user
              had enough permission to open /dev/kvm (this option only
              exists if the kernel turned on KVM).

This patch only introduce the new interface but not yet applied it to
the userfaultfd syscalls, which will be done in the follow up patch.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 fs/userfaultfd.c              | 96 +++++++++++++++++++++++++++++++++++
 include/linux/userfaultfd_k.h |  5 ++
 init/Kconfig                  | 11 ++++
 kernel/sysctl.c               | 11 ++++
 4 files changed, 123 insertions(+)

```
#### [PATCH] vfio: ccw: only free cp on final interrupt
##### From: Cornelia Huck <cohuck@redhat.com>

```c
When we get an interrupt for a channel program, it is not
necessarily the final interrupt; for example, the issuing
guest may request an intermediate interrupt by specifying
the program-controlled-interrupt flag on a ccw.

We must not switch the state to idle if the interrupt is not
yet final; even more importantly, we must not free the translated
channel program if the interrupt is not yet final, or the host
can crash during cp rewind.

Fixes: e5f84dbaea59 ("vfio: ccw: return I/O results asynchronously")
Cc: stable@vger.kernel.org # v4.12+
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Eric Farman <farman@linux.ibm.com>
---

Previously part of "vfio-ccw: rework ssch state handling". Please review,
I plan to send a pull req asap.

---
 drivers/s390/cio/vfio_ccw_drv.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH] virt: kvm: Kconfig: pedantic formatting
##### From: "Enrico Weigelt, metux IT consult" <info@metux.net>

```c
Formatting of Kconfig files doesn't look so pretty, so let the
Great White Handkerchief come around and clean it up.

Signed-off-by: Enrico Weigelt, metux IT consult <info@metux.net>
---
 virt/kvm/Kconfig | 40 ++++++++++++++++++++--------------------
 1 file changed, 20 insertions(+), 20 deletions(-)

```
