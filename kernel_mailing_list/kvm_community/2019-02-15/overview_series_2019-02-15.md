#### [PATCH 1/3] KVM: doc: Fix incorrect word ordering regarding supported use of APIs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Per Paolo[1], instantiating multiple VMs in a single process is legal;
but this conflicts with KVM's API documentation, which states:

  The only supported use is one virtual machine per process, and one
  vcpu per thread.

However, an earlier section in the documentation states:

   Only run VM ioctls from the same process (address space) that was used
   to create the VM.

and:

   Only run vcpu ioctls from the same thread that was used to create the
   vcpu.

This suggests that the conflicting documentation is simply an incorrect
ordering of of words, i.e. what's really meant is that a virtual machine
can't be shared across multiple processes and a vCPU can't be shared
across multiple threads.

Tweak the blurb on issuing ioctls to use a more assertive tone, and
rewrite the "supported use" sentence to reference said blurb instead of
poorly restating it in different terms.

Opportunistically add missing punctuation.

[1] https://lkml.kernel.org/r/f23265d4-528e-3bd4-011f-4d7b8f3281db@redhat.com

Fixes: 9c1b96e34717 ("KVM: Document basic API")
Cc: <stable@vger.kernel.org>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 Documentation/virtual/kvm/api.txt | 17 ++++++++---------
 1 file changed, 8 insertions(+), 9 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S: Add KVM stat num_[2M/1G]_pages
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
This adds an entry to the kvm_stats_debugfs directory which provides the
number of large (2M or 1G) pages which have been used to setup the guest
mappings.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/include/asm/kvm_host.h    |  2 ++
 arch/powerpc/kvm/book3s.c              |  3 +++
 arch/powerpc/kvm/book3s_64_mmu_radix.c | 15 ++++++++++++++-
 3 files changed, 19 insertions(+), 1 deletion(-)

```
#### [PATCH net] vhost: correctly check the return value of translate_desc() in log_used()
##### From: Jason Wang <jasowang@redhat.com>

```c
When fail, translate_desc() returns negative value, otherwise the
number of iovs. So we should fail when the return value is negative
instead of a blindly check against zero.

Reported-by: Stephen Hemminger <stephen@networkplumber.org>
Fixes: cc5e71075947 ("vhost: log dirty page correctly")
Signed-off-by: Jason Wang <jasowang@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] KVM: SVM: Workaround errata#1096 (insn_len maybe zero on SMAP violation)
##### From: "Singh, Brijesh" <brijesh.singh@amd.com>

```c
Errata#1096:

On a nested data page fault when CR.SMAP=1 and the guest data read
generates a SMAP violation, GuestInstrBytes field of the VMCB on a
VMEXIT will incorrectly return 0h instead the correct guest
instruction bytes .

Recommend Workaround:

To determine what instruction the guest was executing the hypervisor
will have to decode the instruction at the instruction pointer.

The recommended workaround can not be implemented for the SEV
guest because guest memory is encrypted with the guest specific key,
and instruction decoder will not be able to decode the instruction
bytes. If we hit this errata in the SEV guest then log the message
and request a guest shutdown.

Reported-by: Venkatesh Srinivas <venkateshs@google.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
---

Changes since v1:
 * request to shutdown the guest instead of injecting #GP
 * use the pr_err_ratelimited to supress the host dmesg

 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/mmu.c              |  6 ++++--
 arch/x86/kvm/svm.c              | 32 ++++++++++++++++++++++++++++++++
 arch/x86/kvm/vmx/vmx.c          |  6 ++++++
 4 files changed, 44 insertions(+), 2 deletions(-)

```
#### [PATCH v3] vfio_pci: Enable memory accesses before calling pci_map_rom
##### From: Eric Auger <eric.auger@redhat.com>

```c
pci_map_rom/pci_get_rom_size() performs memory access in the ROM.
In case the Memory Space accesses were disabled, readw() is likely
to trigger a synchronous external abort on some platforms.

In case memory accesses were disabled, re-enable them before the
call and disable them back again just after.

Fixes: 89e1f7d4c66d ("vfio: Add PCI device driver")

Signed-off-by: Eric Auger <eric.auger@redhat.com>
Suggested-by: Alex Williamson <alex.williamson@redhat.com>
---
v2 -> v3:
- follow Alex re-writing

v1 -> v2:
- also re-enable in case of error
---
 drivers/vfio/pci/vfio_pci.c | 25 +++++++++++++++++--------
 1 file changed, 17 insertions(+), 8 deletions(-)

```
