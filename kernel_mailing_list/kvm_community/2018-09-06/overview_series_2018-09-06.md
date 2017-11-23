#### [PATCH v2 1/8] perf/x86: add a function to get the lbr stack
##### From: Wei Wang <wei.w.wang@intel.com>

```c
The LBR stack MSRs are architecturally specific. The perf subsystem has
already assigned the abstracted MSR values based on the CPU architecture.

This patch enables a caller outside the perf subsystem to get the LBR
stack info. This is useful for hyperviosrs to prepare the lbr feature
for the guest.

Signed-off-by: Like Xu <like.xu@intel.com>
Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Andi Kleen <ak@linux.intel.com>
---
 arch/x86/events/intel/lbr.c       | 23 +++++++++++++++++++++++
 arch/x86/include/asm/perf_event.h | 14 ++++++++++++++
 2 files changed, 37 insertions(+)

```
#### [PATCH 1/4] KVM: nVMX: Flush TLB entries tagged by dest EPTP on L1<->L2 transitions
##### From: Liran Alon <liran.alon@oracle.com>

```c
If L1 and L2 share VPID (because L1 don't use VPID or we haven't allocated
a vpid02), we need to flush TLB on L1<->L2 transitions.

Before this patch, this TLB flushing was done by vmx_flush_tlb().
If L0 use EPT, this will translate into INVEPT(active_eptp);
However, if L1 use EPT, in L1->L2 VMEntry, active EPTP is EPTP01 but
TLB entries populated by L2 are tagged with EPTP02.
Therefore we should delay vmx_flush_tlb() until active_eptp is EPTP02.

To achieve this, instead of directly calling vmx_flush_tlb() we request
it to be called by KVM_REQ_TLB_FLUSH which is evaluated after
KVM_REQ_LOAD_CR3 which sets the active_eptp to EPTP02 as required.

Similarly, on L2->L1 VMExit, active EPTP is EPTP02 but TLB entries
populated by L1 are tagged with EPTP01 and therefore we should delay
vmx_flush_tlb() until active_eptp is EPTP01.

Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
Reviewed-by: Nikita Leshchenko <nikita.leshchenko@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx.c | 18 +++++++++++++++---
 1 file changed, 15 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: fix failure of injecting exceptions in x86_emulate_instruction
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
In order to fix a page table walk issue, commit 6ea6e84309ca
("KVM: x86: inject exceptions produced by x86_decode_insn") check
if variable ctxt->have_exception true and inject the exception.
Unfortunately, ctxt->have_exception is set to true only in function
x86_emulate_insn(), which won't be called before invoking
inject_emulated_exception() in the 6ea6e84309ca.
This patch fix this issue.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
Reviewed-by: Xi Xu <xu.xi8@zte.com.cn>
---
 arch/x86/kvm/emulate.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [PATCH v6 1/3] migration: do not flush_compressed_data at the end of iteration
##### From: guangrong.xiao@gmail.com

```c
From: Xiao Guangrong <xiaoguangrong@tencent.com>

flush_compressed_data() needs to wait all compression threads to
finish their work, after that all threads are free until the
migration feeds new request to them, reducing its call can improve
the throughput and use CPU resource more effectively

We do not need to flush all threads at the end of iteration, the
data can be kept locally until the memory block is changed or
memory migration starts over in that case we will meet a dirtied
page which may still exists in compression threads's ring

Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
Reviewed-by: Juan Quintela <quintela@redhat.com>
---
 migration/ram.c | 18 +++++++++++-------
 1 file changed, 11 insertions(+), 7 deletions(-)

```
#### [PATCH net-next 01/11] net: sock: introduce SOCK_XDP
##### From: Jason Wang <jasowang@redhat.com>

```c
This patch introduces a new sock flag - SOCK_XDP. This will be used
for notifying the upper layer that XDP program is attached on the
lower socket, and requires for extra headroom.

TUN will be the first user.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/net/tun.c  | 19 +++++++++++++++++++
 include/net/sock.h |  1 +
 2 files changed, 20 insertions(+)

```
#### [PATCH v5 1/5] x86/mm: Restructure sme_encrypt_kernel()
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
---
 arch/x86/mm/mem_encrypt_identity.c | 160 ++++++++++++++++++++++++-------------
 1 file changed, 104 insertions(+), 56 deletions(-)

```
