#### [PATCH 1/2] kvm: nVMX: Enforce must-be-zero bits in the IA32_VMX_VMCS_ENUM MSR
##### From: Aaron Lewis <aaronlewis@google.com>

```c
According to the SDM, bit 0 and bits 63:10 of the IA32_VMX_VMCS_ENUM
MSR are reserved and are read as 0.

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/nested.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH v4 1/2] vfio/mdev: add migration_version attribute for mdev device
##### From: Yan Zhao <yan.y.zhao@intel.com>

```c
migration_version attribute is used to check migration compatibility
between two mdev devices of the same mdev type.
The key is that it's rw and its data is opaque to userspace.

Userspace reads migration_version of mdev device at source side and
writes the value to migration_version attribute of mdev device at target
side. It judges migration compatibility according to whether the read
and write operations succeed or fail.

As this attribute is under mdev_type node, userspace is able to know
whether two mdev devices are compatible before a mdev device is created.

userspace needs to check whether the two mdev devices are of the same
mdev type before checking the migration_version attribute. It also needs
to check device creation parameters if aggregation is supported in
future.

             __    userspace
              /\              \
             /                 \write
            / read              \
   ________/__________       ___\|/_____________
  | migration_version |     | migration_version |-->check migration
  ---------------------     ---------------------   compatibility
    mdev device A               mdev device B

Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Erik Skultety <eskultet@redhat.com>
Cc: "Dr. David Alan Gilbert" <dgilbert@redhat.com>
Cc: Cornelia Huck <cohuck@redhat.com>
Cc: "Tian, Kevin" <kevin.tian@intel.com>
Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Cc: "Wang, Zhi A" <zhi.a.wang@intel.com>
Cc: Neo Jia <cjia@nvidia.com>
Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: Daniel P. Berrangé <berrange@redhat.com>
Cc: Christophe de Dinechin <dinechin@redhat.com>

Signed-off-by: Yan Zhao <yan.y.zhao@intel.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
v4:
fixed a typo. (Cornelia Huck)

v3:
1. renamed version to migration_version
(Christophe de Dinechin, Cornelia Huck, Alex Williamson)
2. let errno to be freely defined by vendor driver
(Alex Williamson, Erik Skultety, Cornelia Huck, Dr. David Alan Gilbert)
3. let checking mdev_type be prerequisite of migration compatibility
check. (Alex Williamson)
4. reworded example usage section.
(most of this section came from Alex Williamson)
5. reworded attribute intention section (Cornelia Huck)

v2:
1. added detailed intent and usage
2. made definition of version string completely private to vendor driver
   (Alex Williamson)
3. abandoned changes to sample mdev drivers (Alex Williamson)
4. mandatory --> optional (Cornelia Huck)
5. added description for errno (Cornelia Huck)
---
 Documentation/vfio-mediated-device.txt | 113 +++++++++++++++++++++++++
 1 file changed, 113 insertions(+)

```
#### [PATCH] KVM: irqchip: Use struct_size() in kzalloc()
##### From: "Gustavo A. R. Silva" <gustavo@embeddedor.com>

```c
One of the more common cases of allocation size calculations is finding
the size of a structure that has a zero-sized array at the end, along
with memory for some number of elements for that array. For example:

struct foo {
   int stuff;
   struct boo entry[];
};

instance = kzalloc(sizeof(struct foo) + count * sizeof(struct boo), GFP_KERNEL);

Instead of leaving these open-coded and prone to type mistakes, we can
now use the new struct_size() helper:

instance = kzalloc(struct_size(instance, entry, count), GFP_KERNEL);

This code was detected with the help of Coccinelle.

Signed-off-by: Gustavo A. R. Silva <gustavo@embeddedor.com>
---
 virt/kvm/irqchip.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [RFC PATCH v2 04/12] x86/mm/tlb: Flush remote and local TLBs concurrently
##### From: Nadav Amit <namit@vmware.com>

```c
To improve TLB shootdown performance, flush the remote and local TLBs
concurrently. Introduce flush_tlb_multi() that does so. The current
flush_tlb_others() interface is kept, since paravirtual interfaces need
to be adapted first before it can be removed. This is left for future
work. In such PV environments, TLB flushes are not performed, at this
time, concurrently.

Add a static key to tell whether this new interface is supported.

Cc: "K. Y. Srinivasan" <kys@microsoft.com>
Cc: Haiyang Zhang <haiyangz@microsoft.com>
Cc: Stephen Hemminger <sthemmin@microsoft.com>
Cc: Sasha Levin <sashal@kernel.org>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: x86@kernel.org
Cc: Juergen Gross <jgross@suse.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Boris Ostrovsky <boris.ostrovsky@oracle.com>
Cc: linux-hyperv@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: virtualization@lists.linux-foundation.org
Cc: kvm@vger.kernel.org
Cc: xen-devel@lists.xenproject.org
Signed-off-by: Nadav Amit <namit@vmware.com>
---
 arch/x86/hyperv/mmu.c                 |  2 +
 arch/x86/include/asm/paravirt.h       |  8 +++
 arch/x86/include/asm/paravirt_types.h |  6 ++
 arch/x86/include/asm/tlbflush.h       |  6 ++
 arch/x86/kernel/kvm.c                 |  1 +
 arch/x86/kernel/paravirt.c            |  3 +
 arch/x86/mm/tlb.c                     | 80 +++++++++++++++++++++++----
 arch/x86/xen/mmu_pv.c                 |  2 +
 8 files changed, 96 insertions(+), 12 deletions(-)

```
#### [PATCH] tests: kvm: Check for a kernel warningFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
When running with /sys/module/kvm_intel/parameters/unrestricted_guest=N,
test that a kernel warning does not occur informing us that
vcpu->mmio_needed=1.  This can happen when KVM_RUN is called after a
triple fault.
This test was made to detect a bug that was reported by Syzkaller
(https://groups.google.com/forum/#!topic/syzkaller/lHfau8E3SOE) and
fixed with commit bbeac2830f4de ("KVM: X86: Fix residual mmio emulation
request to userspace").

Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 tools/testing/selftests/kvm/.gitignore        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/include/kvm_util.h  |   2 +
 .../selftests/kvm/include/x86_64/processor.h  |   2 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  36 +++++
 .../selftests/kvm/lib/x86_64/processor.c      |  16 +++
 .../selftests/kvm/x86_64/mmio_warning_test.c  | 126 ++++++++++++++++++
 7 files changed, 184 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/x86_64/mmio_warning_test.c

```
#### [PATCH v2 1/2] KVM: LAPIC: Optimize timer latency consider world switch time
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Advance lapic timer tries to hidden the hypervisor overhead between the
host emulated timer fires and the guest awares the timer is fired. However,
even though after more sustaining optimizations, kvm-unit-tests/tscdeadline_latency 
still awares ~1000 cycles latency since we lost the time between the end of 
wait_lapic_expire and the guest awares the timer is fired. There are 
codes between the end of wait_lapic_expire and the world switch, furthermore, 
the world switch itself also has overhead. Actually the guest_tsc is equal 
to the target deadline time in wait_lapic_expire is too late, guest will
aware the latency between the end of wait_lapic_expire() and after vmentry 
to the guest. This patch takes this time into consideration. 

The vmentry_lapic_timer_advance_ns module parameter should be well tuned by 
host admin, setting bit 0 to 1 to finally cache parameter in KVM. This patch 
can reduce average cyclictest latency from 3us to 2us on Skylake server. 
(guest w/ nohz=off, idle=poll, host w/ preemption_timer=N, the cyclictest 
latency is not too sensitive when preemption_timer=Y for this optimization in 
my testing), kvm-unit-tests/tscdeadline_latency can reach 0.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
NOTE: rebase on https://lkml.org/lkml/2019/5/20/449
v1 -> v2:
 * rename get_vmentry_advance_delta to get_vmentry_advance_cycles
 * cache vmentry_advance_cycles by setting param bit 0 
 * add param max limit 

 arch/x86/kvm/lapic.c   | 38 +++++++++++++++++++++++++++++++++++---
 arch/x86/kvm/lapic.h   |  3 +++
 arch/x86/kvm/vmx/vmx.c |  2 +-
 arch/x86/kvm/x86.c     |  9 +++++++++
 arch/x86/kvm/x86.h     |  2 ++
 5 files changed, 50 insertions(+), 4 deletions(-)

```
#### [PATCH v3 1/5] vsock/virtio: limit the memory used per-socket
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Since virtio-vsock was introduced, the buffers filled by the host
and pushed to the guest using the vring, are directly queued in
a per-socket list. These buffers are preallocated by the guest
with a fixed size (4 KB).

The maximum amount of memory used by each socket should be
controlled by the credit mechanism.
The default credit available per-socket is 256 KB, but if we use
only 1 byte per packet, the guest can queue up to 262144 of 4 KB
buffers, using up to 1 GB of memory per-socket. In addition, the
guest will continue to fill the vring with new 4 KB free buffers
to avoid starvation of other sockets.

This patch mitigates this issue copying the payload of small
packets (< 128 bytes) into the buffer of last packet queued, in
order to avoid wasting memory.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 drivers/vhost/vsock.c                   |  2 +
 include/linux/virtio_vsock.h            |  1 +
 net/vmw_vsock/virtio_transport.c        |  1 +
 net/vmw_vsock/virtio_transport_common.c | 60 +++++++++++++++++++++----
 4 files changed, 55 insertions(+), 9 deletions(-)

```
