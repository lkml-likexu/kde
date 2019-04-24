#### [PATCH 4.4 187/266] x86/bugs: Add AMDs variant of SSB_NO
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
From: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>

commit 24809860012e0130fbafe536709e08a22b3e959e upstream.

The AMD document outlining the SSBD handling
124441_AMD64_SpeculativeStoreBypassDisable_Whitepaper_final.pdf
mentions that the CPUID 8000_0008.EBX[26] will mean that the
speculative store bypass disable is no longer needed.

A copy of this document is available at:
    https://bugzilla.kernel.org/show_bug.cgi?id=199889

Signed-off-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Janakarajan Natarajan <Janakarajan.Natarajan@amd.com>
Cc: kvm@vger.kernel.org
Cc: andrew.cooper3@citrix.com
Cc: Andy Lutomirski <luto@kernel.org>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Borislav Petkov <bp@suse.de>
Cc: David Woodhouse <dwmw@amazon.co.uk>
Link: https://lkml.kernel.org/r/20180601145921.9500-2-konrad.wilk@oracle.com
[bwh: Backported to 4.4: adjust context, indentation]
Signed-off-by: Ben Hutchings <ben@decadent.org.uk>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 arch/x86/include/asm/cpufeatures.h |    1 +
 arch/x86/kernel/cpu/common.c       |    3 ++-
 arch/x86/kvm/cpuid.c               |    2 +-
```
#### [PATCH 4.14 083/115] x86/fpu: Dont export __kernel_fpu_{begin,end}()
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
[ Upstream commit 12209993e98c5fa1855c467f22a24e3d5b8be205 ]

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
Signed-off-by: Sasha Levin <alexander.levin@microsoft.com>
---
 arch/x86/include/asm/efi.h     |  6 ++----
 arch/x86/include/asm/fpu/api.h | 15 +++++----------
 arch/x86/kernel/fpu/core.c     |  6 ++----
 3 files changed, 9 insertions(+), 18 deletions(-)

```
#### [PATCH v2 1/4] KVM: LAPIC: Extract adaptive tune timer advancement logic
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Extract adaptive tune timer advancement logic to a single function.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 57 ++++++++++++++++++++++++++++++----------------------
 1 file changed, 33 insertions(+), 24 deletions(-)

```
#### 
##### 

```c
```
#### [PATCH] KVM: s390: change default halt poll to 50000
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
older performance measurements indicated that 50000 vs 80000 reduces cpu
consumption while still providing the benefit of halt polling. We had
this change in the IBM KVM product, but it got lost so it never went
upstream. Recent re-measurement indicate that 50k is still better than
80k.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
Acked-by: Janosch Frank <frankja@linux.vnet.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 1/2] powerpc: Allow for a custom decr value to be specified to load on decr excp
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
Currently the handler for a decrementer exception will simply reload the
maximum value (0x7FFFFFFF), which will take ~4 seconds to expire again.
This means that if a vcpu cedes, it will be ~4 seconds between wakeups.

The h_cede_tm test is testing a known breakage when a guest cedes while
suspended. To be sure we cede 500 times to check for the bug. However
since it takes ~4 seconds to be woken up once we've ceded, we only get
through ~20 iterations before we reach the 90 seconds timeout and the
test appears to fail.

Add an option when registering the decrementer handler to specify the
value which should be reloaded by the handler, allowing the timeout to be
chosen.

Modify the spr test to use the max timeout to preserve existing
behaviour.
Modify the h_cede_tm test to use a 10ms timeout to ensure we can perform
500 iterations before hitting the 90 second time limit for a test.

This means the h_cede_tm test now succeeds rather than timing out.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---

V1 -> V2:
- Make decr variables static
- Load intial decr value in tm test to ensure known value present
---
 lib/powerpc/handlers.c | 7 ++++---
 powerpc/sprs.c         | 5 +++--
 powerpc/tm.c           | 4 +++-
 3 files changed, 10 insertions(+), 6 deletions(-)

```
#### [PATCH kvm-unit-tests] vmware_backdoors: run with -cpu host
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
After KVM commit 672ff6cff80ca43bf3258410d2b887036969df5f, reading a VMware
pseudo PMC will fail with #GP unless the PMU is supported by the guest.
Invoke the test with PMU emulation to ensure that it passes.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 x86/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 01/30] fuse: delete dentry if timeout is zero
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
From: Miklos Szeredi <mszeredi@redhat.com>

Don't hold onto dentry in lru list if need to re-lookup it anyway at next
access.

More advanced version of this patch would periodically flush out dentries
from the lru which have gone stale.

Signed-off-by: Miklos Szeredi <mszeredi@redhat.com>
---
 fs/fuse/dir.c | 26 +++++++++++++++++++++++---
 1 file changed, 23 insertions(+), 3 deletions(-)

```
