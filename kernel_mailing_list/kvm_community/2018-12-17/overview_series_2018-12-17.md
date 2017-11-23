#### [PATCH] kvm: Disallow wraparound in kvm_gfn_to_hva_cache_initFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Previously, in the case where (gpa + len) wrapped around, the entire
region was not validated, as the comment claimed. It doesn't actually
seem that wraparound should be allowed here at all.

Furthermore, since some callers don't check the return code from this
function, it seems prudent to clear ghc->memslot in the event of an
error.

Fixes: 8f964525a121f ("KVM: Allow cross page reads and writes from cached translations.")
Reported-by: Cfir Cohen <cfir@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Cfir Cohen <cfir@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Cc: Andrew Honig <ahonig@google.com>
---
 virt/kvm/kvm_main.c | 41 +++++++++++++++++++++--------------------
 1 file changed, 21 insertions(+), 20 deletions(-)

```
#### [PATCH] KVM: fix unregistering coalesced mmio zone from wrong bus
##### From: Eric Biggers <ebiggers@kernel.org>

```c
From: Eric Biggers <ebiggers@google.com>

If you register a kvm_coalesced_mmio_zone with '.pio = 0' but then
unregister it with '.pio = 1', KVM_UNREGISTER_COALESCED_MMIO will try to
unregister it from KVM_PIO_BUS rather than KVM_MMIO_BUS, which is a
no-op.  But it frees the kvm_coalesced_mmio_dev anyway, causing a
use-after-free.

Fix it by only unregistering and freeing the zone if the correct value
of 'pio' is provided.

Reported-by: syzbot+f87f60bb6f13f39b54e3@syzkaller.appspotmail.com
Fixes: 0804c849f1df ("kvm/x86 : add coalesced pio support")
Signed-off-by: Eric Biggers <ebiggers@google.com>
---
 virt/kvm/coalesced_mmio.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests v2 PATCH] s390x: try !FORCE SCLP read SCP info if FORCED is unknown
##### From: David Hildenbrand <david@redhat.com>

```c
Looking at what the kernel does, looks like we should
- Check for more errors
- Try to execute !FORCED read if the FORCED one is unknown
- Set the function code to a normal write
- Set control_mask[2] to SCLP_VARIABLE_LENGTH_RESPONSE

The kernel seems to set the function code to 0x80. Looking at where that
comes from, turns out this is a "dump indicator" to produce more
meaningful dumps. Looking for other function codes used in the kernel, I
discovered 0x40, which is used for "single increment assign" to speed up
memory hotplug. I was not able to find out what "control_mask[2] = 0x80"
means.

I guess we can just set the funcion code to 0 ("normal write). Let's
document the other bits in case anybody ever wonders what they mean.
Rename SCLP_VARIABLE_LENGTH_RESPONSE to SCLP_CM2_VARIABLE_LENGTH_RESPONSE
and move the SCLP function codes, mask bits and event buffer flags to
dedicated sections in the header.

Make sure that all other callers properly initialize the header
fully (also inititalize control_mask and function_code).

Tested-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
---

v1 -> v2:
- Use define for control mask value 0x80
- Rename SCLP_VARIABLE_LENGTH_RESPONSE to SCLP_CM2_VARIABLE_LENGTH_RESPONSE
- Cleanup sclp.h header file a bit (move to sections)
- Make sure control mask and function code are in a deterministic state
  when issuing sclp_service_call

 lib/s390x/sclp-ascii.c |  7 +++++++
 lib/s390x/sclp.c       | 26 ++++++++++++++++++++++++--
 lib/s390x/sclp.h       | 13 +++++++++----
 3 files changed, 40 insertions(+), 6 deletions(-)

```
#### [PATCH] KVM: X86: Fix NULL deref in vcpu_scan_ioapic
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Reported by syzkaller:

    CPU: 1 PID: 5962 Comm: syz-executor118 Not tainted 4.20.0-rc6+ #374
    Hardware name: Google Google Compute Engine/Google Compute Engine, BIOS Google 01/01/2011
    RIP: 0010:kvm_apic_hw_enabled arch/x86/kvm/lapic.h:169 [inline]
    RIP: 0010:vcpu_scan_ioapic arch/x86/kvm/x86.c:7449 [inline]
    RIP: 0010:vcpu_enter_guest arch/x86/kvm/x86.c:7602 [inline]
    RIP: 0010:vcpu_run arch/x86/kvm/x86.c:7874 [inline]
    RIP: 0010:kvm_arch_vcpu_ioctl_run+0x5296/0x7320 arch/x86/kvm/x86.c:8074
    Call Trace:
	 kvm_vcpu_ioctl+0x5c8/0x1150 arch/x86/kvm/../../../virt/kvm/kvm_main.c:2596
	 vfs_ioctl fs/ioctl.c:46 [inline]
	 file_ioctl fs/ioctl.c:509 [inline]
	 do_vfs_ioctl+0x1de/0x1790 fs/ioctl.c:696
	 ksys_ioctl+0xa9/0xd0 fs/ioctl.c:713
	 __do_sys_ioctl fs/ioctl.c:720 [inline]
	 __se_sys_ioctl fs/ioctl.c:718 [inline]
	 __x64_sys_ioctl+0x73/0xb0 fs/ioctl.c:718
	 do_syscall_64+0x1b9/0x820 arch/x86/entry/common.c:290
	 entry_SYSCALL_64_after_hwframe+0x49/0xbe 

The reason is that the testcase writes hyperv synic HV_X64_MSR_SINT14 msr
and triggers scan ioapic logic to load synic vectors into EOI exit bitmap.
However, irqchip is not initialized by this simple testcase, ioapic/apic
objects should not be accessed.

This patch fixes it by also considering whether or not apic is present.

Reported-by: syzbot+39810e6c400efadfef71@syzkaller.appspotmail.com
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### linux-next: manual merge of the kvm tree with the tip tree
##### From: Stephen Rothwell <sfr@canb.auug.org.au>

```c
Hi all,

Today's linux-next merge of the kvm tree got a conflict in:

  arch/x86/kvm/vmx.c

between commit:

  a97673a1c43d ("x86: Fix various typos in comments")

from the tip tree and commit:

  a821bab2d1ee ("KVM: VMX: Move VMX specific files to a "vmx" subdirectory")

from the kvm tree.

I fixed it up (I removed the file and then made the same changes to
the file in its new position (one change was already fixed)) and can
carry the fix as necessary. This is now fixed as far as linux-next is
concerned, but any non trivial conflicts should be mentioned to your
upstream maintainer when your tree is submitted for merging.  You may
also want to consider cooperating with the maintainer of the
conflicting tree to minimise any particularly complex conflicts.

```
#### [kvm-unit-tests v3 PATCH 1/2] s390x: cleanup and add SCLP defines
##### From: David Hildenbrand <david@redhat.com>

```c
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
---
 lib/s390x/sclp.h | 13 +++++++++----
 1 file changed, 9 insertions(+), 4 deletions(-)

```
#### [PATCH v2 1/4] KVM: PPC: Pass change type down to memslot commit function
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Currently, kvm_arch_commit_memory_region() gets called with a
parameter indicating what type of change is being made to the memslot,
but it doesn't pass it down to the platform-specific memslot commit
functions.  This adds the `change' parameter to the lower-level
functions so that they can use it in future.

[paulus@ozlabs.org - fix book E also.]

Signed-off-by: Bharata B Rao <bharata@linux.vnet.ibm.com>
Reviewed-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
v2: Fix compilation of Book E code.

 arch/powerpc/include/asm/kvm_ppc.h | 6 ++++--
 arch/powerpc/kvm/book3s.c          | 5 +++--
 arch/powerpc/kvm/book3s_hv.c       | 3 ++-
 arch/powerpc/kvm/book3s_pr.c       | 3 ++-
 arch/powerpc/kvm/booke.c           | 3 ++-
 arch/powerpc/kvm/powerpc.c         | 2 +-
 6 files changed, 14 insertions(+), 8 deletions(-)

```
#### [PATCH] vhost: split structs into a separate header file
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
vhost structs are shared by vhost-kernel and vhost-user.  Split them
into a separate file to ease copying them into programs that implement
either the server or the client side of vhost-user.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 include/uapi/linux/vhost.h       | 113 +--------------------------
 include/uapi/linux/vhost_types.h | 128 +++++++++++++++++++++++++++++++
 2 files changed, 130 insertions(+), 111 deletions(-)
 create mode 100644 include/uapi/linux/vhost_types.h

```
