#### [QEMU PATCH v3 1/9] KVM: Introduce kvm_arch_destroy_vcpu()
##### From: Liran Alon <liran.alon@oracle.com>

```c
Simiar to how kvm_init_vcpu() calls kvm_arch_init_vcpu() to perform
arch-dependent initialisation, introduce kvm_arch_destroy_vcpu()
to be called from kvm_destroy_vcpu() to perform arch-dependent
destruction.

This was added because some architectures (Such as i386)
currently do not free memory that it have allocated in
kvm_arch_init_vcpu().

Suggested-by: Maran Wilson <maran.wilson@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 accel/kvm/kvm-all.c  |  5 +++++
 include/sysemu/kvm.h |  1 +
 target/arm/kvm32.c   |  5 +++++
 target/arm/kvm64.c   |  5 +++++
 target/i386/kvm.c    | 12 ++++++++++++
 target/mips/kvm.c    |  5 +++++
 target/ppc/kvm.c     |  5 +++++
 target/s390x/kvm.c   | 10 ++++++++++
 8 files changed, 48 insertions(+)

```
#### [PATCH v4 1/5] KVM: LAPIC: Make lapic timer unpinned
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Make lapic timer unpinned when timer is injected by posted-interrupt,
the emulated timer can be offload to the housekeeping cpus, kick after 
setting the pending timer request as alternative to commit 61abdbe0bcc.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Marcelo Tosatti <mtosatti@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 8 ++++----
 arch/x86/kvm/x86.c   | 6 +-----
 2 files changed, 5 insertions(+), 9 deletions(-)

```
#### [PATCH net-next] vhost_net: disable zerocopy by default
##### From: Jason Wang <jasowang@redhat.com>

```c
Vhost_net was known to suffer from HOL[1] issues which is not easy to
fix. Several downstream disable the feature by default. What's more,
the datapath was split and datacopy path got the support of batching
and XDP support recently which makes it faster than zerocopy part for
small packets transmission.

It looks to me that disable zerocopy by default is more
appropriate. It cold be enabled by default again in the future if we
fix the above issues.

[1] https://patchwork.kernel.org/patch/3787671/

Signed-off-by: Jason Wang <jasowang@redhat.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/net.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCHv2] x86/hyperv: Hold cpus_read_lock() on assigning reenlightenment vector
##### From: Dmitry Safonov <dima@arista.com>

```c
KVM support may be compiled as dynamic module, which triggers the
following splat on modprobe (under CONFIG_DEBUG_PREEMPT):

 KVM: vmx: using Hyper-V Enlightened VMCS
 BUG: using smp_processor_id() in preemptible [00000000] code: modprobe/466
 caller is debug_smp_processor_id+0x17/0x19
 CPU: 0 PID: 466 Comm: modprobe Kdump: loaded Not tainted 4.19.43 #1
 Hardware name: Microsoft Corporation Virtual Machine/Virtual Machine, BIOS 090007  06/02/2017
 Call Trace:
  dump_stack+0x61/0x7e
  check_preemption_disabled+0xd4/0xe6
  debug_smp_processor_id+0x17/0x19
  set_hv_tscchange_cb+0x1b/0x89
  kvm_arch_init+0x14a/0x163 [kvm]
  kvm_init+0x30/0x259 [kvm]
  vmx_init+0xed/0x3db [kvm_intel]
  do_one_initcall+0x89/0x1bc
  do_init_module+0x5f/0x207
  load_module+0x1b34/0x209b
  __ia32_sys_init_module+0x17/0x19
  do_fast_syscall_32+0x121/0x1fa
  entry_SYSENTER_compat+0x7f/0x91

Hold cpus_read_lock() so that MSR will be written for an online CPU,
even if set_hv_tscchange_cb() gets being preempted.
While at it, cleanup smp_processor_id()'s in hv_cpu_init() and add a
lockdep assert into hv_cpu_die().

Fixes: 93286261de1b4 ("x86/hyperv: Reenlightenment notifications
support")

Cc: Andy Lutomirski <luto@kernel.org>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Cathy Avery <cavery@redhat.com>
Cc: Haiyang Zhang <haiyangz@microsoft.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: "K. Y. Srinivasan" <kys@microsoft.com>
Cc: "Michael Kelley (EOSG)" <Michael.H.Kelley@microsoft.com>
Cc: Mohammed Gamal <mmorsy@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Peter Zijlstra <peterz@infradead.org>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Roman Kagan <rkagan@virtuozzo.com>
Cc: Sasha Levin <sashal@kernel.org>
Cc: Stephen Hemminger <sthemmin@microsoft.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>

Cc: devel@linuxdriverproject.org
Cc: kvm@vger.kernel.org
Cc: linux-hyperv@vger.kernel.org
Cc: x86@kernel.org
Reported-by: Prasanna Panchamukhi <panchamukhi@arista.com>
Signed-off-by: Dmitry Safonov <dima@arista.com>
---
v1 link: lkml.kernel.org/r/20190611212003.26382-1-dima@arista.com

NOTE that I hadn't a chance to test v2 on hyperv machine so far,
ONLY BUILD TESTED. (In hope that the patch still makes sense and Kbuild
bot will report any issue).

 arch/x86/hyperv/hv_init.c | 16 +++++++++++++---
 1 file changed, 13 insertions(+), 3 deletions(-)

```
#### [PATCH v2] target/i386: define a new MSR based feature word - FEAT_CORE_CAPABILITY
##### From: Xiaoyao Li <xiaoyao.li@linux.intel.com>

```c
MSR IA32_CORE_CAPABILITY is a feature-enumerating MSR, which only
enumerates the feature split lock detection (via bit 5) by now.

The existence of MSR IA32_CORE_CAPABILITY is enumerated by CPUID.7_0:EDX[30].

The latest kernel patches about them can be found here:
https://lkml.org/lkml/2019/4/24/1909

Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
---
Changelog:
v2
    Add definition of MSR_CORE_CAP_SPLIT_LOCK_DETECT for SNR cpu model
---
 target/i386/cpu.c | 22 +++++++++++++++++++++-
 target/i386/cpu.h |  5 +++++
 target/i386/kvm.c |  9 +++++++++
 3 files changed, 35 insertions(+), 1 deletion(-)

```
#### [PATCH] vhost_net: remove wrong 'unlikely' check
##### From: huhai <huhai@kylinos.cn>

```c
Since commit f9611c43ab0d ("vhost-net: enable zerocopy tx by default")
experimental_zcopytx is set to true by default, so remove the unlikely check.

Signed-off-by: huhai <huhai@kylinos.cn>
---
 drivers/vhost/net.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
