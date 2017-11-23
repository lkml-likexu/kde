#### [kvm-unit-tests PULL 01/10] s390x: cleanup and add SCLP defines
##### From: Thomas Huth <thuth@redhat.com>

```c
From: David Hildenbrand <david@redhat.com>

Reading the Linux kernel SCLP code, one might wonder what certain magic
values mean and why we don't have to set them in our SCLP code. So
let's define them for us. We might want to make use of them in the
future.

Add two new defines for values used in the linux kernel
- SCLP_FC_SINGLE_INCREMENT_ASSIGN (used to speed up memory hotplug)
- SCLP_FC_DUMP_INDICATOR (used to get more reasonable dumps)

Also rename SCLP_VARIABLE_LENGTH_RESPONSE to
SCLP_CM2_VARIABLE_LENGTH_RESPONSE, so it is clear where this is actually
used. Move the defines to separate sections.

Signed-off-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/sclp.h | 13 +++++++++----
 1 file changed, 9 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: Fix single-step debugging
##### From: Alexander Popov <alex.popov@linux.com>

```c
The single-step debugging of KVM guests on x86 is broken: if we run
gdb 'stepi' command at the breakpoint when the guest interrupts are
enabled, RIP always jumps to native_apic_mem_write(). Then other
nasty effects follow.

Long investigation showed that the commit c8401dda2f0a00cd25c0 (Jun 7 2017)
introduced the kvm_run.debug corruption: kvm_vcpu_do_singlestep() can
be called without X86_EFLAGS_TF set.

Let's fix it. Please consider that for -stable.
---
 arch/x86/kvm/x86.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH] [next] kvm: vmx: fix some -Wmissing-prototypes warnings
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
We get some warnings when building kernel with W=1:
arch/x86/kvm/vmx/vmx.c:426:5: warning: no previous prototype for ‘kvm_fill_hv_flush_list_func’ [-Wmissing-prototypes]
arch/x86/kvm/vmx/nested.c:58:6: warning: no previous prototype for ‘init_vmcs_shadow_fields’ [-Wmissing-prototypes]

Make them static to fix this.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
 arch/x86/kvm/vmx/nested.c | 2 +-
 arch/x86/kvm/vmx/vmx.c    | 2 +-
 2 files changed, 2 insertions(+), 2 deletions(-)

```
#### [RFC v1 1/2] vfio-ccw: Don't assume there are more ccws after a TIC
##### From: Farhan Ali <alifm@linux.ibm.com>

```c
When trying to calculate the length of a ccw chain, we assume
there are ccws after a TIC. This can lead to overcounting and
copying garbage data from guest memory.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: x86: Fix single-step debugging
##### From: Alexander Popov <alex.popov@linux.com>

```c
The single-step debugging of KVM guests on x86 is broken: if we run
gdb 'stepi' command at the breakpoint when the guest interrupts are
enabled, RIP always jumps to native_apic_mem_write(). Then other
nasty effects follow.

Long investigation showed that on Jun 7, 2017 the
commit c8401dda2f0a00cd25c0 ("KVM: x86: fix singlestepping over syscall")
introduced the kvm_run.debug corruption: kvm_vcpu_do_singlestep() can
be called without X86_EFLAGS_TF set.

Let's fix it. Please consider that for -stable.

Signed-off-by: Alexander Popov <alex.popov@linux.com>
---
 arch/x86/kvm/x86.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v2 1/5] vfio-ccw: make it safe to access channel programs
##### From: Cornelia Huck <cohuck@redhat.com>

```c
When we get a solicited interrupt, the start function may have
been cleared by a csch, but we still have a channel program
structure allocated. Make it safe to call the cp accessors in
any case, so we can call them unconditionally.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 3 +++
 drivers/s390/cio/vfio_ccw_cp.h | 2 ++
 2 files changed, 5 insertions(+)

```
#### [PATCH v2 1/2] vfio-ccw: new capability chain support
##### From: Cornelia Huck <cohuck@redhat.com>

```c
To be replaced with a real linux-headers update.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 linux-headers/linux/vfio.h     |  4 ++++
 linux-headers/linux/vfio_ccw.h | 12 ++++++++++++
 2 files changed, 16 insertions(+)

```
#### [PATCH 1/3] virtio-ccw: diag 500 may return a negative cookie
##### From: Cornelia Huck <cohuck@redhat.com>

```c
If something goes wrong in the kvm io bus handling, the virtio-ccw
diagnose may return a negative error value in the cookie gpr.

Document this.

Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 Documentation/virtual/kvm/s390-diag.txt | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
