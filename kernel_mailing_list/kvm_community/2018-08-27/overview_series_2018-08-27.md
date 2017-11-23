#### [PATCH v13 03/13] x86/cpufeatures: Add Intel-defined SGX leaf CPUID_12_EAX
##### From: Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>

```c
From: Sean Christopherson <sean.j.christopherson@intel.com>

CPUID_12_EAX is an Intel-defined feature bits leaf dedicated for SGX.
There are currently four documented feature bits, with more expected in
the not-too-distant future.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Jarkko Sakkinen <jarkko.sakkinen@linux.intel.com>
---
 arch/x86/include/asm/cpufeature.h        | 7 +++++--
 arch/x86/include/asm/cpufeatures.h       | 8 +++++++-
 arch/x86/include/asm/disabled-features.h | 3 ++-
 arch/x86/include/asm/required-features.h | 3 ++-
 arch/x86/kernel/cpu/common.c             | 7 +++++++
 arch/x86/kvm/cpuid.h                     | 1 +
 6 files changed, 24 insertions(+), 5 deletions(-)

```
#### [PATCH 1/3] KVM: VMX: immediately mark preemption timer expired only for zero value
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
A VMX preemption timer value of '0' at the time of VMEnter is
architecturally guaranteed to cause a VMExit prior to the CPU
executing any instructions in the guest.  This architectural
definition is in place to ensure that a previously expired timer
is correctly recognized by the CPU as it is possible for the timer
to reach zero and not trigger a VMexit due to a higher priority
VMExit being signalled instead, e.g. a pending #DB that morphs into
a VMExit.

Whether by design or coincidence, commit f4124500c2c1 ("KVM: nVMX:
Fully emulate preemption timer") special cased timer values of '0'
and '1' to ensure prompt delivery of the VMExit.  Unlike '0', a
timer value of '1' has no has no architectural guarantees regarding
when it is delivered.

Modify the timer emulation to trigger immediate VMExit if and only
if the timer value is '0', and document precisely why '0' is special.
Do this even if calibration of the virtual TSC failed, i.e. VMExit
will occur immediately regardless of the frequency of the timer.
Making only '0' a special case gives KVM leeway to be more aggressive
in ensuring the VMExit is injected prior to executing instructions in
the nested guest, and also eliminates any ambiguity as to why '1' is
a special case, e.g. why wasn't the threshold for a "short timeout"
set to 10, 100, 1000, etc...

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx.c | 14 ++++++++------
 1 file changed, 8 insertions(+), 6 deletions(-)

```
#### [PATCH v5 1/5] KVM: x86: hyperv: enforce vp_index < KVM_MAX_VCPUS
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Hyper-V TLFS (5.0b) states:

> Virtual processors are identified by using an index (VP index). The
> maximum number of virtual processors per partition supported by the
> current implementation of the hypervisor can be obtained through CPUID
> leaf 0x40000005. A virtual processor index must be less than the
> maximum number of virtual processors per partition.

Forbid userspace to set VP_INDEX above KVM_MAX_VCPUS. get_vcpu_by_vpidx()
can now be optimized to bail early when supplied vpidx is >= KVM_MAX_VCPUS.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Roman Kagan <rkagan@virtuozzo.com>
---
 arch/x86/kvm/hyperv.c | 8 +++++---
 1 file changed, 5 insertions(+), 3 deletions(-)

```
#### [PATCH] vfio: fix potential memory leak in vfio_msi_cap_len
##### From: Li Qiang <liq3ea@gmail.com>

```c
Free the vdev->msi_perm in error path.

Signed-off-by: Li Qiang <liq3ea@gmail.com>
Reviewed-by: Eric Auger <eric.auger@redhat.com>
---
 drivers/vfio/pci/vfio_pci_config.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH v37 1/3] virtio-balloon: VIRTIO_BALLOON_F_FREE_PAGE_HINT
##### From: Wei Wang <wei.w.wang@intel.com>

```c
Negotiation of the VIRTIO_BALLOON_F_FREE_PAGE_HINT feature indicates the
support of reporting hints of guest free pages to host via virtio-balloon.
Currenlty, only free page blocks of MAX_ORDER - 1 are reported. They are
obtained one by one from the mm free list via the regular allocation
function.

Host requests the guest to report free page hints by sending a new cmd id
to the guest via the free_page_report_cmd_id configuration register. When
the guest starts to report, it first sends a start cmd to host via the
free page vq, which acks to host the cmd id received. When the guest
finishes reporting free pages, a stop cmd is sent to host via the vq.
Host may also send a stop cmd id to the guest to stop the reporting.

VIRTIO_BALLOON_CMD_ID_STOP: Host sends this cmd to stop the guest
reporting.
VIRTIO_BALLOON_CMD_ID_DONE: Host sends this cmd to tell the guest that
the reported pages are ready to be freed.

Why does the guest free the reported pages when host tells it is ready to
free?
This is because freeing pages appears to be expensive for live migration.
free_pages() dirties memory very quickly and makes the live migraion not
converge in some cases. So it is good to delay the free_page operation
when the migration is done, and host sends a command to guest about that.

Why do we need the new VIRTIO_BALLOON_CMD_ID_DONE, instead of reusing
VIRTIO_BALLOON_CMD_ID_STOP?
This is because live migration is usually done in several rounds. At the
end of each round, host needs to send a VIRTIO_BALLOON_CMD_ID_STOP cmd to
the guest to stop (or say pause) the reporting. The guest resumes the
reporting when it receives a new command id at the beginning of the next
round. So we need a new cmd id to distinguish between "stop reporting" and
"ready to free the reported pages".

TODO:
- Add a batch page allocation API to amortize the allocation overhead.

Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Signed-off-by: Liang Li <liang.z.li@intel.com>
Cc: Michael S. Tsirkin <mst@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Linus Torvalds <torvalds@linux-foundation.org>
---
 drivers/virtio/virtio_balloon.c     | 364 ++++++++++++++++++++++++++++++++----
 include/uapi/linux/virtio_balloon.h |   5 +
 2 files changed, 336 insertions(+), 33 deletions(-)

```
#### [PATCH 1/2] x86/mm: add .data..decrypted section to hold shared variables
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
kvmclock defines few static variables which are shared with hypervisor
during the kvmclock initialization.

When SEV is active, memory is encrypted with a guest-specific key, and
if guest OS wants to share the memory region with hypervisor then it must
clear the C-bit before sharing it.

The '__decrypted' can be used to define a shared variables; the variables
will be put in the .data.decryption section. This section is mapped with
C=0 early in the boot, we also ensure that the initialized values are
updated to match with C=0 (i.e peform an in-place decryption). The
.data..decrypted section is PMD aligned and sized so that we avoid the
need for spliting the pages when map with C=0.

Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Fixes: 368a540e0232 ("x86/kvmclock: Remove memblock dependency")
Cc: stable@vger.kernel.org
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: kvm@vger.kernel.org
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@suse.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
---
 arch/x86/include/asm/mem_encrypt.h |   4 +
 arch/x86/kernel/head64.c           |  12 ++
 arch/x86/kernel/vmlinux.lds.S      |  18 +++
 arch/x86/mm/mem_encrypt_identity.c | 220 +++++++++++++++++++++++++++----------
 4 files changed, 197 insertions(+), 57 deletions(-)

```
