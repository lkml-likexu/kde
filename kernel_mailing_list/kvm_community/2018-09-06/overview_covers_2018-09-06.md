

#### [PATCH net-next 00/11] Vhost_net TX batching
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi all:

This series tries to batch submitting packets to underlayer socket
through msg_control during sendmsg(). This is done by:

1) Doing userspace copy inside vhost_net
2) Build XDP buff
3) Batch at most 64 (VHOST_NET_BATCH) XDP buffs and submit them once
   through msg_control during sendmsg().
4) Underlayer sockets can use XDP buffs directly when XDP is enalbed,
   or build skb based on XDP buff.

For the packet that can not be built easily with XDP or for the case
that batch submission is hard (e.g sndbuf is limited). We will go for
the previous slow path, passing iov iterator to underlayer socket
through sendmsg() once per packet.

This can help to improve cache utilization and avoid lots of indirect
calls with sendmsg(). It can also co-operate with the batching support
of the underlayer sockets (e.g the case of XDP redirection through
maps).

Testpmd(txonly) in guest shows obvious improvements:

Test                /+pps%
XDP_DROP on TAP     /+44.8%
XDP_REDIRECT on TAP /+29%
macvtap (skb)       /+26%

Netperf TCP_STREAM TX from guest shows obvious improvements on small
packet:

    size/session/+thu%/+normalize%
       64/     1/   +2%/    0%
       64/     2/   +3%/   +1%
       64/     4/   +7%/   +5%
       64/     8/   +8%/   +6%
      256/     1/   +3%/    0%
      256/     2/  +10%/   +7%
      256/     4/  +26%/  +22%
      256/     8/  +27%/  +23%
      512/     1/   +3%/   +2%
      512/     2/  +19%/  +14%
      512/     4/  +43%/  +40%
      512/     8/  +45%/  +41%
     1024/     1/   +4%/    0%
     1024/     2/  +27%/  +21%
     1024/     4/  +38%/  +73%
     1024/     8/  +15%/  +24%
     2048/     1/  +10%/   +7%
     2048/     2/  +16%/  +12%
     2048/     4/    0%/   +2%
     2048/     8/    0%/   +2%
     4096/     1/  +36%/  +60%
     4096/     2/  -11%/  -26%
     4096/     4/    0%/  +14%
     4096/     8/    0%/   +4%
    16384/     1/   -1%/   +5%
    16384/     2/    0%/   +2%
    16384/     4/    0%/   -3%
    16384/     8/    0%/   +4%
    65535/     1/    0%/  +10%
    65535/     2/    0%/   +8%
    65535/     4/    0%/   +1%
    65535/     8/    0%/   +3%

Please review.

Thanks

Jason Wang (11):
  net: sock: introduce SOCK_XDP
  tuntap: switch to use XDP_PACKET_HEADROOM
  tuntap: enable bh early during processing XDP
  tuntap: simplify error handling in tun_build_skb()
  tuntap: tweak on the path of non-xdp case in tun_build_skb()
  tuntap: split out XDP logic
  tuntap: move XDP flushing out of tun_do_xdp()
  tun: switch to new type of msg_control
  tuntap: accept an array of XDP buffs through sendmsg()
  tap: accept an array of XDP buffs through sendmsg()
  vhost_net: batch submitting XDP buffers to underlayer sockets

 drivers/net/tap.c      |  87 +++++++++++++-
 drivers/net/tun.c      | 251 +++++++++++++++++++++++++++++++----------
 drivers/vhost/net.c    | 171 +++++++++++++++++++++++++---
 include/linux/if_tun.h |   7 ++
 include/net/sock.h     |   1 +
 5 files changed, 437 insertions(+), 80 deletions(-)
```
#### [PATCH v6 0/3] migration: compression optimization
##### From: guangrong.xiao@gmail.com
X-Google-Original-From: xiaoguangrong@tencent.com
From: Xiao Guangrong <xiaoguangrong@tencent.com>

```c

From: Xiao Guangrong <xiaoguangrong@tencent.com>

Changelog in v6:

Thanks to Juan's review, in this version we
1) move flush compressed data to find_dirty_block() where it hits the end
   of memblock
2) use save_page_use_compression instead of migrate_use_compression in
   flush_compressed_data

Xiao Guangrong (3):
  migration: do not flush_compressed_data at the end of iteration
  migration: show the statistics of compression
  migration: use save_page_use_compression in flush_compressed_data

 hmp.c                 | 13 +++++++++++
 migration/migration.c | 12 ++++++++++
 migration/ram.c       | 63 +++++++++++++++++++++++++++++++++++++++++++--------
 migration/ram.h       |  1 +
 qapi/migration.json   | 26 ++++++++++++++++++++-
 5 files changed, 105 insertions(+), 10 deletions(-)
```
#### [PATCH v5 0/5] x86: Fix SEV guest regression
##### From: Brijesh Singh <brijesh.singh@amd.com>

```c

The following commit

"
x86/kvmclock: Remove memblock dependency

https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=368a540e0232ad446931f5a4e8a5e06f69f21343
"

introduced SEV guest regression.

The guest physical address holding the wall_clock and hv_clock_boot
are shared with the hypervisor must be mapped with C=0 when SEV
is active. To clear the C-bit we use  kernel_physical_mapping_init() to
split the large pages. The above commit moved the kvmclock initialization
very early and kernel_physical_mapping_init() fails to allocate memory
while spliting the large page.

To solve it, we add a special .data..decrypted section, this section can be
used to hold the shared variables. Early boot code maps this section with
C=0. The section is pmd aligned and sized to avoid the need to split the pages.
Caller can use __decrypted attribute to add the variables in .data..decrypted
section. 

Cc: Tom Lendacky <thomas.lendacky@amd.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Borislav Petkov <bp@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>

Changes since v4:
 - define few static pages in .data..decrypted which can be used
   for cpus > HVC_BOOT_ARRAY_SIZE when SEV is active.

Changes since v3:
 - commit message improvements (based on Sean's feedback)

Changes since v2:
 - commit message and code comment improvements (based on Boris feedback)
 - move sme_populate_pgd fixes in new patch.
 - drop stable Cc - will submit to stable after patch is upstreamed.

Changes since v1:
 - move the logic to re-arrange mapping in new patch
 - move the definition of __start_data_* in mem_encrypt.h
 - map the workarea buffer as encrypted when SEV is enabled
 - enhance the sme_populate_pgd to update the pte/pmd flags when mapping exist

Brijesh Singh (5):
  x86/mm: Restructure sme_encrypt_kernel()
  x86/mm: fix sme_populate_pgd() to update page flags
  x86/mm: add .data..decrypted section to hold shared variables
  x86/kvm: use __decrypted attribute in shared variables
  x86/kvm: Avoid dynamic allocation of pvclock data when SEV is active

 arch/x86/include/asm/mem_encrypt.h |  10 ++
 arch/x86/kernel/head64.c           |  11 ++
 arch/x86/kernel/kvmclock.c         |  26 ++++-
 arch/x86/kernel/vmlinux.lds.S      |  20 ++++
 arch/x86/mm/init.c                 |   3 +
 arch/x86/mm/mem_encrypt.c          |  10 ++
 arch/x86/mm/mem_encrypt_identity.c | 232 +++++++++++++++++++++++++++----------
 7 files changed, 245 insertions(+), 67 deletions(-)
```
#### [PATCH v2 0/8] Guest LBR Enabling
##### From: Wei Wang <wei.w.wang@intel.com>

```c

Last Branch Recording (LBR) is a performance monitor unit (PMU) feature
on Intel CPUs that captures branch related info. This patch series enables
this feature to KVM guests.

Here is a conclusion of the fundamental methods that we use:
1) the LBR feature is enabled per guest via QEMU setting of
   KVM_CAP_X86_GUEST_LBR;
2) when the guest has the LBR feature, the LBR stack is passed through to
   the guest for direct accesses;
3) When the guest uses the LBR feature with the user callstack mode, the
   host will help save/resotre the LBR stack when the vCPU thread is
   scheduled out/in.

Patches 1-5 implements the above 1) and 2), and patches 6-8 implements
the above 3).

ChangeLog:
v1->v2:
    - add the per guest LBR capability, KVM_CAP_X86_GUEST_LBR;
    - save/restore the LBR stack conditionally on the vCPU thread context
      switching, instead of on VMX transitions;
    - expose MSR_IA32_PERF_CAPABILITIES to the guest.

The first version was sent out long time ago, and can be referenced here:
https://lkml.org/lkml/2017/9/25/11 , and thanks for lots of the
suggestions from Paolo Bonzini and Andi Kleen.

Like Xu (2):
  KVM: PMU: support to save/restore the guest lbr stack on vCPU
    switching
  perf/x86/intel/lbr: add the guest_lbr boolean to cpuc

Wei Wang (6):
  perf/x86: add a function to get the lbr stack
  KVM/x86: KVM_CAP_X86_GUEST_LBR
  KVM/vmx: Pass through the lbr stack to a guest
  KVM/x86: expose MSR_IA32_PERF_CAPABILITIES to the guest
  KVM/x86: enable the guest to access the debugctl msr
  perf/x86/intel/lbr: guest requesting KVM for lbr stack save/restore

 arch/x86/events/intel/lbr.c          | 54 +++++++++++++++++++++++++--
 arch/x86/events/perf_event.h         |  1 +
 arch/x86/include/asm/kvm_host.h      |  3 ++
 arch/x86/include/asm/perf_event.h    | 19 ++++++++++
 arch/x86/include/uapi/asm/kvm_para.h |  2 +
 arch/x86/kvm/cpuid.c                 |  5 ++-
 arch/x86/kvm/pmu_intel.c             | 71 +++++++++++++++++++++++++++++++++++-
 arch/x86/kvm/vmx.c                   | 60 ++++++++++++++++++++++++++++++
 arch/x86/kvm/x86.c                   | 18 +++------
 include/uapi/linux/kvm.h             |  1 +
 10 files changed, 215 insertions(+), 19 deletions(-)
```
#### [PATCH 0/4]: KVM: nVMX: Consider TLB are tagged with different EPTP
##### From: Liran Alon <liran.alon@oracle.com>

```c

Hi,

This patch series aim to enhance L1<->L2 transitions to avoid
unnecessary TLB flushes in case L1 uses VPID and EPT.

The 1st patch fixes a bug that INVEPT was executed on L1<->L2
transitions to flush TLB but with the wrong EPTP because it hasn't been
loaded yet with the destination EPTP. The patch handles this issue
easily by just delaying vmx_flush_tlb() to be called after EPTP has been
set to destination by using KVM_REQ_TLB_FLUSH.

The 2nd patch avoids unnecessary flushing TLB on L2->L1 VMExit if L1
uses VPID and EPT. This is because TLB entries of L1 and L2 are
separated by the fact they are tagged with different EPTP.

The 3rd patch modifies L1->L2 VMEntry code such that it will set
vmcs02->vpid to vmcs12->vpid in case L1 uses EPT. This leverages the
fact TLB entries of L1 and L2 are separated by being tagged with
different EPTPs and therefore we don't need to use the special vpid02.

The 4rd patch then modifies L1->L2 VMEntry code to avoid unnecessary
flushing TLB in case L1 uses both VPID and EPT as TLB entries of L1 and
L2 are separated by different EPTP tags.

Regards,
-Liran
```
