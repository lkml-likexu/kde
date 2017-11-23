#### [PATCH 1/1] kvm: vmx: add cpu into VMX preemption timer bug list
##### From: Wei Huang <wei@redhat.com>

```c
This patch adds Intel "Xeon CPU E3-1220 V2", with CPUID.01H.EAX=0x000306A8,
into the list of known broken CPUs which fail to support VMX preemption
timer. This bug was found while running the APIC timer test of
kvm-unit-test on this specific CPU, even though the errata info can't be
located in the public domain for this CPU.

Signed-off-by: Wei Huang <wei@redhat.com>
---
 arch/x86/kvm/vmx.c | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH RFC 1/3] kvm: Split use cases for kvm_is_reserved_pfn to kvm_is_refcounted_pfn
##### From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

```c
The function kvm_is_reserved_pfn really has two uses. One is to test for if
we should be updating the reference count on a page when we are accessing
it. The other is to determine if we should be updating the dirty flag or
marking pages as accessed.

In preparation for blurring the lines between ZONE_DEVICE and system RAM I
am splitting out the dirty/accessed cases into their own checks. Doing this
allows us to add ZONE_DEVICE to the list of refcounted pages without having
to worry about us introducing possible issues with pages being marked as
dirty or accessed and possibly causing any issues with attempted LRU
accesses on the ZONE_DEVICE pages.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 arch/x86/kvm/mmu.c       |    6 +++---
 include/linux/kvm_host.h |    2 +-
 virt/kvm/kvm_main.c      |   22 +++++++++++++---------
 3 files changed, 17 insertions(+), 13 deletions(-)

```
#### [PATCH] KVM/nVMX: Stop mapping the "APIC-access address" page into the kernel
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c
The "APIC-access address" is simply a token that the hypervisor puts into
the PFN of a 4K EPTE (or PTE if using shadow paging) that triggers APIC
virtualization whenever a page walk terminates with that PFN. This address
has to be a legal address (i.e.  within the physical address supported by
the CPU), but it need not have WB memory behind it. In fact, it need not
have anything at all behind it. When bit 31 ("activate secondary controls")
of the primary processor-based VM-execution controls is set and bit 0
("virtualize APIC accesses") of the secondary processor-based VM-execution
controls is set, the PFN recorded in the VMCS "APIC-access address" field
will never be touched. (Instead, the access triggers APIC virtualization,
which may access the PFN recorded in the "Virtual-APIC address" field of
the VMCS.)

So stop mapping the "APIC-access address" page into the kernel and even
drop the requirements to have a valid page backing it. Instead, just use
some token that:

1) Not one of the valid guest pages.
2) Within the physical address supported by the CPU.

Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: KarimAllah Ahmed <karahmed@amazon.de>
---

Thanks Jim for the commit message :)
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/mmu.c              | 10 ++++++
 arch/x86/kvm/vmx.c              | 71 ++++++++++++++++++-----------------------
 3 files changed, 42 insertions(+), 40 deletions(-)

```
#### [PATCH 01/28] KVM: nVMX: Free the VMREAD/VMWRITE bitmaps if alloc_kvm_area() fails
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Fixes: 34a1cd60d17f ("kvm: x86: vmx: move some vmx setting from vmx_init() to hardware_setup()")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx.c | 7 +++++--
 1 file changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH v4 01/14] X86/nVMX: handle_vmon: Read 4 bytes from guest memory
##### From: KarimAllah Ahmed <karahmed@amazon.de>

```c
Read the data directly from guest memory instead of the map->read->unmap
sequence. This also avoids using kvm_vcpu_gpa_to_page() and kmap() which
assumes that there is a "struct page" for guest memory.

Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: KarimAllah Ahmed <karahmed@amazon.de>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---
v1 -> v2:
- Massage commit message a bit.
---
 arch/x86/kvm/vmx.c | 14 +++-----------
 1 file changed, 3 insertions(+), 11 deletions(-)

```
#### [PATCH 1/3] mm/mmu_notifier: use structure for invalidate_range_start/end callback
##### From: jglisse@redhat.com

```c
From: Jérôme Glisse <jglisse@redhat.com>

To avoid having to change many callback definition everytime we want
to add a parameter use a structure to group all parameters for the
mmu_notifier invalidate_range_start/end callback. No functional changes
with this patch.

Signed-off-by: Jérôme Glisse <jglisse@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>
Cc: Matthew Wilcox <mawilcox@microsoft.com>
Cc: Ross Zwisler <zwisler@kernel.org>
Cc: Jan Kara <jack@suse.cz>
Cc: Dan Williams <dan.j.williams@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Michal Hocko <mhocko@kernel.org>
Cc: Christian Koenig <christian.koenig@amd.com>
Cc: Felix Kuehling <felix.kuehling@amd.com>
Cc: Ralph Campbell <rcampbell@nvidia.com>
Cc: John Hubbard <jhubbard@nvidia.com>
Cc: kvm@vger.kernel.org
Cc: dri-devel@lists.freedesktop.org
Cc: linux-rdma@vger.kernel.org
Cc: linux-fsdevel@vger.kernel.org
---
 drivers/gpu/drm/amd/amdgpu/amdgpu_mn.c  | 43 +++++++++++--------------
 drivers/gpu/drm/i915/i915_gem_userptr.c | 14 ++++----
 drivers/gpu/drm/radeon/radeon_mn.c      | 16 ++++-----
 drivers/infiniband/core/umem_odp.c      | 20 +++++-------
 drivers/infiniband/hw/hfi1/mmu_rb.c     | 13 +++-----
 drivers/misc/mic/scif/scif_dma.c        | 11 ++-----
 drivers/misc/sgi-gru/grutlbpurge.c      | 14 ++++----
 drivers/xen/gntdev.c                    | 12 +++----
 include/linux/mmu_notifier.h            | 14 +++++---
 mm/hmm.c                                | 23 ++++++-------
 mm/mmu_notifier.c                       | 21 ++++++++++--
 virt/kvm/kvm_main.c                     | 14 +++-----
 12 files changed, 102 insertions(+), 113 deletions(-)

```
#### [tip:x86/fpu] x86/fpu: Add might_fault() to user_insn()Git-Commit-ID: 6637401c35b2f327a35d27f44bda05e327f2f017
##### From: tip-bot for Sebastian Andrzej Siewior <tipbot@zytor.com>

```c
Commit-ID:  6637401c35b2f327a35d27f44bda05e327f2f017
Gitweb:     https://git.kernel.org/tip/6637401c35b2f327a35d27f44bda05e327f2f017
Author:     Sebastian Andrzej Siewior <bigeasy@linutronix.de>
AuthorDate: Wed, 28 Nov 2018 23:20:11 +0100
Committer:  Borislav Petkov <bp@suse.de>
CommitDate: Mon, 3 Dec 2018 19:15:32 +0100

x86/fpu: Add might_fault() to user_insn()

Every user of user_insn() passes an user memory pointer to this macro.

Add might_fault() to user_insn() so we can spot users which are using
this macro in sections where page faulting is not allowed.

 [ bp: Space it out to make it more visible. ]

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Reviewed-by: Rik van Riel <riel@surriel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Jann Horn <jannh@google.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: x86-ml <x86@kernel.org>
Link: https://lkml.kernel.org/r/20181128222035.2996-6-bigeasy@linutronix.de
---
 arch/x86/include/asm/fpu/internal.h | 3 +++
 1 file changed, 3 insertions(+)

```
#### [tip:x86/fpu] x86/fpu: Don't export __kernel_fpu_{begin,end}()Git-Commit-ID: 7d79adb87fa79e4a4c59424fd5b5a922861fc5f6
##### From: tip-bot for Sebastian Andrzej Siewior <tipbot@zytor.com>

```c
Commit-ID:  7d79adb87fa79e4a4c59424fd5b5a922861fc5f6
Gitweb:     https://git.kernel.org/tip/7d79adb87fa79e4a4c59424fd5b5a922861fc5f6
Author:     Sebastian Andrzej Siewior <bigeasy@linutronix.de>
AuthorDate: Thu, 29 Nov 2018 16:02:10 +0100
Committer:  Borislav Petkov <bp@suse.de>
CommitDate: Mon, 3 Dec 2018 19:37:27 +0100

x86/fpu: Don't export __kernel_fpu_{begin,end}()

There is one user of __kernel_fpu_begin() and before invoking it,
it invokes preempt_disable(). So it could invoke kernel_fpu_begin()
right away. The 32bit version of arch_efi_call_virt_setup() and
arch_efi_call_virt_teardown() does this already.

The comment above *kernel_fpu*() claims that before invoking
__kernel_fpu_begin() preemption should be disabled and that KVM is a
good example of doing it. Well, KVM doesn't do that since commit

  f775b13eedee2 ("x86,kvm: move qemu/guest FPU switching out to vcpu_run")

so it is not an example anymore.

With EFI gone as the last user of __kernel_fpu_{begin|end}(), both can
be made static and not exported anymore.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Reviewed-by: Rik van Riel <riel@surriel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Ard Biesheuvel <ard.biesheuvel@linaro.org>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Nicolai Stange <nstange@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: linux-efi <linux-efi@vger.kernel.org>
Cc: x86-ml <x86@kernel.org>
Link: https://lkml.kernel.org/r/20181129150210.2k4mawt37ow6c2vq@linutronix.de
---
 arch/x86/include/asm/efi.h     |  6 ++----
 arch/x86/include/asm/fpu/api.h | 16 ++++++----------
 arch/x86/kernel/fpu/core.c     |  6 ++----
 3 files changed, 10 insertions(+), 18 deletions(-)

```
#### [tip:x86/fpu] x86/fpu: Update comment for __raw_xsave_addr()Git-Commit-ID: 2f2fcc40a961ed04f0e130803fbaa868c2899310
##### From: tip-bot for Sebastian Andrzej Siewior <tipbot@zytor.com>

```c
Commit-ID:  2f2fcc40a961ed04f0e130803fbaa868c2899310
Gitweb:     https://git.kernel.org/tip/2f2fcc40a961ed04f0e130803fbaa868c2899310
Author:     Sebastian Andrzej Siewior <bigeasy@linutronix.de>
AuthorDate: Wed, 28 Nov 2018 23:20:12 +0100
Committer:  Borislav Petkov <bp@suse.de>
CommitDate: Mon, 3 Dec 2018 19:27:14 +0100

x86/fpu: Update comment for __raw_xsave_addr()

The comment above __raw_xsave_addr() claims that the function does not
work for compacted buffers and was introduced in:

  b8b9b6ba9dec3 ("x86/fpu: Allow setting of XSAVE state")

In this commit, the function was factored out of get_xsave_addr() and
this function claims that it works with "standard format or compacted
format of xsave area". It accesses the "xstate_comp_offsets" variable
for the actual offset and it was introduced in commit

  7496d6458fe32 ("Define kernel API to get address of each state in xsave area")

Based on the code (back then and now):
- xstate_offsets holds the standard offset.
- if compacted mode is not supported then xstate_comp_offsets gets the
  xstate_offsets copied.
- if compacted mode is supported then xstate_comp_offsets will hold the
  offset for the compacted buffer.

Based on that the function works for compacted buffers as long as the
CPU supports it and this what we care about.

Remove the "Note:" which is not accurate.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Reviewed-by: Rik van Riel <riel@surriel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: x86-ml <x86@kernel.org>
Link: https://lkml.kernel.org/r/20181128222035.2996-7-bigeasy@linutronix.de
---
 arch/x86/kernel/fpu/xstate.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [tip:x86/fpu] x86/fpu: Use unsigned long long shift in xfeature_uncompacted_offset()
##### From: tip-bot for Sebastian Andrzej Siewior <tipbot@zytor.com>

```c
Commit-ID:  d08452390179710dc7989242605e3c1faa62b64f
Gitweb:     https://git.kernel.org/tip/d08452390179710dc7989242605e3c1faa62b64f
Author:     Sebastian Andrzej Siewior <bigeasy@linutronix.de>
AuthorDate: Wed, 28 Nov 2018 23:20:07 +0100
Committer:  Borislav Petkov <bp@suse.de>
CommitDate: Mon, 3 Dec 2018 18:40:28 +0100

x86/fpu: Use unsigned long long shift in xfeature_uncompacted_offset()

The xfeature mask is 64-bit so a shift from a number to its mask should
have ULL suffix or else bits above position 31 will be lost. This is not
a problem now but should XFEATURE_MASK_SUPERVISOR gain a bit >31 then
this check won't catch it.

Use BIT_ULL() to compute a mask from a number.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Reviewed-by: Rik van Riel <riel@surriel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: x86-ml <x86@kernel.org>
Link: https://lkml.kernel.org/r/20181128222035.2996-2-bigeasy@linutronix.de
---
 arch/x86/kernel/fpu/xstate.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [tip:x86/fpu] x86/pkeys: Make init_pkru_value staticGit-Commit-ID: 1a4226efaf808fe9079ea3b29919883008918297
##### From: tip-bot for Sebastian Andrzej Siewior <tipbot@zytor.com>

```c
Commit-ID:  1a4226efaf808fe9079ea3b29919883008918297
Gitweb:     https://git.kernel.org/tip/1a4226efaf808fe9079ea3b29919883008918297
Author:     Sebastian Andrzej Siewior <bigeasy@linutronix.de>
AuthorDate: Wed, 28 Nov 2018 23:20:10 +0100
Committer:  Borislav Petkov <bp@suse.de>
CommitDate: Mon, 3 Dec 2018 19:10:18 +0100

x86/pkeys: Make init_pkru_value static

The variable init_pkru_value isn't used outside of this file.
Make it static.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Reviewed-by: Rik van Riel <riel@surriel.com>
Acked-by: Dave Hansen <dave.hansen@linux.intel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: x86-ml <x86@kernel.org>
Link: https://lkml.kernel.org/r/20181128222035.2996-5-bigeasy@linutronix.de
---
 arch/x86/mm/pkeys.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [tip:x86/fpu] x86/process/32: Remove asm/math_emu.h includeGit-Commit-ID: e08e32119b944f519664451bfb342a25b4045ead
##### From: tip-bot for Sebastian Andrzej Siewior <tipbot@zytor.com>

```c
Commit-ID:  e08e32119b944f519664451bfb342a25b4045ead
Gitweb:     https://git.kernel.org/tip/e08e32119b944f519664451bfb342a25b4045ead
Author:     Sebastian Andrzej Siewior <bigeasy@linutronix.de>
AuthorDate: Wed, 28 Nov 2018 23:20:08 +0100
Committer:  Borislav Petkov <bp@suse.de>
CommitDate: Mon, 3 Dec 2018 18:51:16 +0100

x86/process/32: Remove asm/math_emu.h include

The math_emu.h header files contains the definition of struct
math_emu_info which is not used in this file.

Remove the asm/math_emu.h include.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Reviewed-by: Andy Lutomirski <luto@kernel.org>
Reviewed-by: Rik van Riel <riel@surriel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Jann Horn <jannh@google.com>
Cc: Joerg Roedel <jroedel@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Rik van Riel <riel@surriel.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: x86-ml <x86@kernel.org>
Link: https://lkml.kernel.org/r/20181128222035.2996-3-bigeasy@linutronix.de
---
 arch/x86/kernel/process_32.c | 3 ---
 1 file changed, 3 deletions(-)

```
#### [tip:x86/fpu] x86/thread_info: Remove _TIF_ALLWORK_MASKGit-Commit-ID: d23650e06299e9b2d04e090ab8c625cdf24465bf
##### From: tip-bot for Sebastian Andrzej Siewior <tipbot@zytor.com>

```c
Commit-ID:  d23650e06299e9b2d04e090ab8c625cdf24465bf
Gitweb:     https://git.kernel.org/tip/d23650e06299e9b2d04e090ab8c625cdf24465bf
Author:     Sebastian Andrzej Siewior <bigeasy@linutronix.de>
AuthorDate: Wed, 28 Nov 2018 23:20:09 +0100
Committer:  Borislav Petkov <bp@suse.de>
CommitDate: Mon, 3 Dec 2018 19:00:28 +0100

x86/thread_info: Remove _TIF_ALLWORK_MASK

There is no user of _TIF_ALLWORK_MASK since commit

  21d375b6b34ff ("x86/entry/64: Remove the SYSCALL64 fast path").

Remove the unused define _TIF_ALLWORK_MASK.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Reviewed-by: Borislav Petkov <bp@suse.de>
Reviewed-by: Rik van Riel <riel@surriel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: David Howells <dhowells@redhat.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Tim Chen <tim.c.chen@linux.intel.com>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: x86-ml <x86@kernel.org>
Link: https://lkml.kernel.org/r/20181128222035.2996-4-bigeasy@linutronix.de
---
 arch/x86/include/asm/thread_info.h | 8 --------
 1 file changed, 8 deletions(-)

```
#### [PATCH v3] x86/hyper-v: Mark TLFS structures packed
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
The TLFS structures are used for hypervisor-guest communication and must
exactly meet the specification.

Compilers can add alignment padding to structures or reorder struct members
for randomization and optimization, which would break the hypervisor ABI.

Mark the structures as packed to prevent this.

Suggested-by: Nadav Amit <nadav.amit@gmail.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Acked-by: Thomas Gleixner <tglx@linutronix.de>
Acked-by: Nadav Amit <nadav.amit@gmail.com>
Reviewed-by: Michael Kelley <mikelley@microsoft.com>
---
- Changes since v2:
 - add __packed to struct 'u' defined within union 'hv_port_id'
   [Michael Kelley]

- This is a follow-up to my "[PATCH v2 0/4] x86/kvm/hyper-v: Implement
 Direct Mode for synthetic timers" series, as suggested by Thomas I'm
 routing it to KVM tree to avoid merge conflicts.
---
 arch/x86/include/asm/hyperv-tlfs.h | 52 +++++++++++++++---------------
 1 file changed, 26 insertions(+), 26 deletions(-)

```
