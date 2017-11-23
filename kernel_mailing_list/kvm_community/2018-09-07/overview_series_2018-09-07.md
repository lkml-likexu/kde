#### [ 1/1] KVM/MMU: Fix comment in walk_shadow_page_lockless_end()Thread-Topic: [ 1/1] KVM/MMU: Fix comment in walk_shadow_page_lockless_end()
##### From: Tianyu Lan <Tianyu.Lan@microsoft.com>

```c
kvm_commit_zap_page() has been renamed to kvm_mmu_commit_zap_page()
This patch is to fix the commit.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
 arch/x86/kvm/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH V5 1/4] kvm: remove redundant reserved page check
##### From: Zhang Yi <yi.z.zhang@linux.intel.com>

```c
PageReserved() is already checked inside kvm_is_reserved_pfn(),
remove it from kvm_set_pfn_dirty().

Signed-off-by: Zhang Yi <yi.z.zhang@linux.intel.com>
Signed-off-by: Zhang Yu <yu.c.zhang@linux.intel.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Acked-by: Pankaj Gupta <pagupta@redhat.com>
---
 virt/kvm/kvm_main.c | 8 ++------
 1 file changed, 2 insertions(+), 6 deletions(-)

```
#### [PULL RESEND v2 1/4] KVM: arm/arm64: Clean dcache to PoC when changing PTE due to CoW
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
From: Marc Zyngier <marc.zyngier@arm.com>

When triggering a CoW, we unmap the RO page via an MMU notifier
(invalidate_range_start), and then populate the new PTE using another
one (change_pte). In the meantime, we'll have copied the old page
into the new one.

The problem is that the data for the new page is sitting in the
cache, and should the guest have an uncached mapping to that page
(or its MMU off), following accesses will bypass the cache.

In a way, this is similar to what happens on a translation fault:
We need to clean the page to the PoC before mapping it. So let's just
do that.

This fixes a KVM unit test regression observed on a HiSilicon platform,
and subsequently reproduced on Seattle.

Fixes: a9c0e12ebee5 ("KVM: arm/arm64: Only clean the dcache on translation fault")
Cc: stable@vger.kernel.org # v4.16+
Reported-by: Mike Galbraith <efault@gmx.de>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 virt/kvm/arm/mmu.c | 9 ++++++++-
 1 file changed, 8 insertions(+), 1 deletion(-)

```
#### [Resend PATCH] KVM/MMU: Fix comment in walk_shadow_page_lockless_end()
##### From: Tianyu Lan <Tianyu.Lan@microsoft.com>

```c
kvm_commit_zap_page() has been renamed to kvm_mmu_commit_zap_page()
This patch is to fix the commit.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
Sorry for the broken title and resend.

 arch/x86/kvm/mmu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### RfC: vfio: add vgpu edid support?
##### From: Gerd Hoffmann <kraxel@redhat.com>

```c
Hi,

I consider adding EDID support to qemu, for display configuration.

qemu patches are here:
    https://git.kraxel.org/cgit/qemu/log/?h=sirius/edid

linux kernel patches are here:
    https://git.kraxel.org/cgit/linux/log/?h=edid

Current (experimental) patches have support for the stdvga and
virtio-vga.

I think it would be quite useful for vgpu too.  Unlike emulated devices
vgpu's do not have a paravirtual display configuration path, because the
standard way to configure the display is to simply read the edid from
the monitor.

Intel has two hard-coded edid blobs for that (depending on vgpu type).
Not sure how nvidia handles this, but probably simliar.  With qemu
passing a edid blob for the virtual display instead of using the
hardcoded blob we could make the display configuration much more
flexible.

Ideally qemu would also be able to update the edid blob at any time, and
the vgpu will notify the guest about it (probably by emulating a monitor
hotplug event).  The guest can react on qemu window resizing then and
adapt automatically, simliar to how it works with qxl and virtio-gpu.

The guest and the vgpu should be able to handle "odd" non-standard
display resolutions like this (coming from random window resizing):

   Detailed mode: Clock 106.620 MHz, 477 mm x 330 mm
                  1212 1515 1551 1636 hborder 0
                   840  844  848  869 vborder 0
                  -hsync -vsync 
                  VertFreq: 74 Hz, HorFreq: 65171 Hz

RfC patch for the vfio interface is below.

Comments?

cheers,
  Gerd

=================== cut here ===================

From 556299e8c6280b1c4061fdae15491a013c22be98 Mon Sep 17 00:00:00 2001
From: Gerd Hoffmann <kraxel@redhat.com>
Date: Thu, 6 Sep 2018 16:17:17 +0200
Subject: [PATCH] [RfC] vfio: edid interface

Signed-off-by: Gerd Hoffmann <kraxel@redhat.com>
---
 include/uapi/linux/vfio.h | 42 ++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 42 insertions(+)

```
#### [PATCH v3] KVM: x86: don't reset root in kvm_mmu_setup()
##### From: Wei Yang <richard.weiyang@gmail.com>

```c
Here is the code path which shows kvm_mmu_setup() is invoked after
kvm_mmu_create(). Since kvm_mmu_setup() is only invoked in this code path,
this means the root_hpa and prev_roots are guaranteed to be invalid. And
it is not necessary to reset it again.

    kvm_vm_ioctl_create_vcpu()
        kvm_arch_vcpu_create()
            vmx_create_vcpu()
                kvm_vcpu_init()
                    kvm_arch_vcpu_init()
                        kvm_mmu_create()
        kvm_arch_vcpu_setup()
            kvm_mmu_setup()
                kvm_init_mmu()

This patch set reset_roots to false in kmv_mmu_setup().

Signed-off-by: Wei Yang <richard.weiyang@gmail.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
v3: add a comment in code based on Liran comment.
v2: adjust changelog based on Sean Christopherson comment
---
 arch/x86/kvm/mmu.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH v6 1/5] x86/mm: Restructure sme_encrypt_kernel()
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c
Re-arrange the sme_encrypt_kernel() by moving the workarea map/unmap
logic in a separate static function. There are no logical changes in this
patch. The restructuring will allow us to expand the sme_encrypt_kernel
in future.

Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Reviewed-by: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: kvm@vger.kernel.org
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@suse.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: linux-kernel@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: kvm@vger.kernel.org
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Reviewed-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/mm/mem_encrypt_identity.c | 160 ++++++++++++++++++++++++-------------
 1 file changed, 104 insertions(+), 56 deletions(-)

```
