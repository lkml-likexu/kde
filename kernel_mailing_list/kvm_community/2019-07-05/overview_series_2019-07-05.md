#### [PATCH kvmtool 1/2] term: Avoid busy loop with unconnected pseudoterminals
##### From: Andre Przywara <andre.przywara@arm.com>

```c
Currently when kvmtool is creating a pseudoterminal (--tty x), the
terminal thread will consume 100% of its CPU time as long as no slave
is connected to the other end. This is due to the fact that poll()
unconditonally sets the POLLHUP bit in revents and returns immediately,
regardless of the events we are querying for.

There does not seem to be a solution to this with just poll() alone.
Using the TIOCPKT ioctl sounds promising, but doesn't help either,
as poll still detects the HUP condition.

So apart from chickening out with some poll() timeout tricks, inotify
seems to be the way to go:
Each time poll() returns with the POLLHUP bit set, we disable this
file descriptor in the poll() array and rely on the inotify IN_OPEN
watch to fire on the slave end of the pseudoterminal. We then enable the
file descriptor again.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 term.c | 48 +++++++++++++++++++++++++++++++++++++++++++++---
 1 file changed, 45 insertions(+), 3 deletions(-)

```
#### [GIT PULL] Final KVM changes for 5.2
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 6fbc7275c7a9ba97877050335f290341a1fd8dbf:

  Linux 5.2-rc7 (2019-06-30 11:25:36 +0800)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to e644fa18e2ffc8895ca30dade503ae10128573a6:

  KVM: arm64/sve: Fix vq_present() macro to yield a bool (2019-07-05 12:07:51 +0200)

----------------------------------------------------------------
x86 bugfix patches and one compilation fix for ARM.

----------------------------------------------------------------
Liran Alon (2):
      KVM: nVMX: Allow restore nested-state to enable eVMCS when vCPU in SMM
      KVM: nVMX: Change KVM_STATE_NESTED_EVMCS to signal vmcs12 is copied from eVMCS

Paolo Bonzini (1):
      KVM: x86: degrade WARN to pr_warn_ratelimited

Wanpeng Li (1):
      KVM: LAPIC: Fix pending interrupt in IRR blocked by software disable LAPIC

Zhang Lei (1):
      KVM: arm64/sve: Fix vq_present() macro to yield a bool

 arch/arm64/kvm/guest.c                          |  2 +-
 arch/x86/kvm/lapic.c                            |  2 +-
 arch/x86/kvm/vmx/nested.c                       | 30 ++++++++++++++++---------
 arch/x86/kvm/x86.c                              |  6 ++---
 tools/testing/selftests/kvm/x86_64/evmcs_test.c |  1 +
 5 files changed, 26 insertions(+), 15 deletions(-)
```
#### [PATCH] KVM: LAPIC: ARBPRI is a reserved register for x2APIC
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
kvm-unit-tests were adjusted to match bare metal behavior, but KVM
itself was not doing what bare metal does; fix that.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/lapic.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH v6 1/2] KVM: LAPIC: Make lapic timer unpinned
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Commit 61abdbe0bcc2 ("kvm: x86: make lapic hrtimer pinned") pinned the
lapic timer to avoid to wait until the next kvm exit for the guest to
see KVM_REQ_PENDING_TIMER set. There is another solution to give a kick
after setting the KVM_REQ_PENDING_TIMER bit, make lapic timer unpinned
will be used in follow up patches.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 8 ++++----
 arch/x86/kvm/x86.c   | 6 +-----
 2 files changed, 5 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: LAPIC: Reset timer_advance_ns to 1000 after adaptive tuning goes insane
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Reset timer_advance_ns to the default value 1000ns after adaptive tuning 
goes insane which can happen sporadically in product environment.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] kvm: LAPIC: write down valid APIC registers
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Replace a magic 64-bit mask with a list of valid registers, computing
the same mask in the end.

Suggested-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/lapic.c | 44 ++++++++++++++++++++++++++++++++------------
 1 file changed, 32 insertions(+), 12 deletions(-)

```
#### [PATCH] kvm: x86: ioapic and apic debug macros cleanup
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
The ioapic_debug and apic_debug have been not used
for years, and kvm tracepoints are enough for debugging,
so remove them as Paolo suggested.

However, there may be something wrong when pv evi get/put
user, so it's better to retain some log there.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
 arch/x86/kvm/ioapic.c | 15 --------
 arch/x86/kvm/lapic.c  | 98 +++++----------------------------------------------
 2 files changed, 9 insertions(+), 104 deletions(-)

```
#### [PATCH] kvm: x86: some tsc debug cleanup
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
There are some pr_debug in TSC code, which may have
been no use, so remove them as Paolo suggested.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
 arch/x86/kvm/x86.c | 8 --------
 1 file changed, 8 deletions(-)

```
#### [PULL 1/1] vfio-ccw: Fix the conversion of Format-0 CCWs to Format-1
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Eric Farman <farman@linux.ibm.com>

When processing Format-0 CCWs, we use the "len" variable as the
number of CCWs to convert to Format-1.  But that variable
contains zero here, and is not a meaningful CCW count until
ccwchain_calc_length() returns.  Since that routine requires and
expects Format-1 CCWs to identify the chaining behavior, the
format conversion must be done first.

Convert the 2KB we copied even if it's more than we need.

Fixes: 7f8e89a8f2fd ("vfio-ccw: Factor out the ccw0-to-ccw1 transition")
Reported-by: Farhan Ali <alifm@linux.ibm.com>
Signed-off-by: Eric Farman <farman@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Message-Id: <20190702180928.18113-1-farman@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH][resend] KVM: fix error handling in svm_cpu_init
##### From: Li RongQing <lirongqing@baidu.com>

```c
sd->save_area should be freed in error path

Fixes: 70cd94e60c733 ("KVM: SVM: VMRUN should use associated ASID when SEV is enabled")
Signed-off-by: Li RongQing <lirongqing@baidu.com>
Reviewed-by: Brijesh Singh <brijesh.singh@amd.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH][resend] KVM: fix error handling in svm_hardware_setup
##### From: Li RongQing <lirongqing@baidu.com>

```c
rename svm_hardware_unsetup as svm_hardware_teardown, move
it before svm_hardware_setup, and call it to free all memory
if fail to setup in svm_hardware_setup, otherwise memory will
be leaked

remove __exit attribute for it since it is called in __init
function

Signed-off-by: Li RongQing <lirongqing@baidu.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm.c | 33 ++++++++++++++++-----------------
 1 file changed, 16 insertions(+), 17 deletions(-)

```
#### [PATCH 1/4] target/i386: kvm: Init nested-state for VMX when vCPU expose VMX
##### From: Liran Alon <liran.alon@oracle.com>

```c
Reviewed-by: Joao Martins <joao.m.martins@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 target/i386/kvm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: LAPIC: Retry tune per-vCPU timer_advance_ns if adaptive tuning goes insane
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Retry tune per-vCPU timer_advance_ns if adaptive tuning goes insane which 
can happen sporadically in product environment.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v1 -> v2:
 * retry max 10 times if adaptive tuning goes insane

 arch/x86/kvm/lapic.c | 7 +++++--
 1 file changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH v15 1/7] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 13 ++++++++-----
 drivers/nvdimm/region_devs.c | 26 ++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  9 ++++++++-
 6 files changed, 47 insertions(+), 12 deletions(-)

```
#### [PATCH v3 1/3] vsock/virtio: use RCU to avoid use-after-free on the_virtio_vsock
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Some callbacks used by the upper layers can run while we are in the
.remove(). A potential use-after-free can happen, because we free
the_virtio_vsock without knowing if the callbacks are over or not.

To solve this issue we move the assignment of the_virtio_vsock at the
end of .probe(), when we finished all the initialization, and at the
beginning of .remove(), before to release resources.
For the same reason, we do the same also for the vdev->priv.

We use RCU to be sure that all callbacks that use the_virtio_vsock
ended before freeing it. This is not required for callbacks that
use vdev->priv, because after the vdev->config->del_vqs() we are sure
that they are ended and will no longer be invoked.

We also take the mutex during the .remove() to avoid that .probe() can
run while we are resetting the device.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/virtio_transport.c | 70 +++++++++++++++++++++-----------
 1 file changed, 46 insertions(+), 24 deletions(-)

```
