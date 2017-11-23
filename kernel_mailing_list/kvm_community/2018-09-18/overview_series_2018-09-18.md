#### [PATCH 1/2][KVM] nVMX x86: Check EPTP on vmentry of L2 guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on VMX Controls" in Intel SDM vol 3C, the
following check needs to be enforced on vmentry of L2 guests:

    If the “enable EPT” VM-execution control is 1, the EPTP VM-execution
    control field must satisfy the following checks:

      — The EPT memory type (bits 2:0) must be a value supported by the
	processor as indicated in the IA32_VMX_EPT_VPID_CAP MSR.
      — Bits 5:3 (1 less than the EPT page-walk length) must be 3,
        indicating an EPT page-walk length of 4.
      — Bit 6 (enable bit for accessed and dirty flags for EPT) must be
        0 if bit 21 of the IA32_VMX_EPT_VPID_CAP MSR is read as 0, indicating
        that the processor does not support accessed and dirty flags for EPT.
      — Reserved bits 11:7 and 63:N (where N is the processor’s
	physical-address width) must all be 0.

Suggested-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
---
 arch/x86/include/asm/vmx.h | 4 +++-
 arch/x86/kvm/vmx.c         | 9 ++++++---
 2 files changed, 9 insertions(+), 4 deletions(-)

```
#### [PATCH 01/13] kvm: selftests: vcpu_setup: set cr4.osfxsr
##### From: Andrew Jones <drjones@redhat.com>

```c
Guest code may want to call functions that have variable arguments.
To do so, we either need to compile with -mno-sse or enable SSE in
the VCPUs. As it should be pretty safe to turn on the feature, and
-mno-sse would make linking test code with standard libraries
difficult, we choose the feature enabling.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/lib/x86.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH]  kvm-unit-test: fix script output abnormal
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
./run_tests.sh
)ASS apic-split (50 tests;
)ASS ioapic-split (19 tests;
)ASS apic (50 tests;
)ASS ioapic (19 tests;
)ASS smptest (1 tests;
)ASS smptest3 (1 tests;

modify sed statement in scripts/runtime.bash, we can see normal
output.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 scripts/runtime.bash | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH]  kvm-unit-tests: unlock before calling return
##### From: Peng Hao <penghao122@sina.com.cn>

```c
From: Peng Hao <peng.hao2@zte.com.cn>

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 lib/report.c | 13 +++++++++----
 1 file changed, 9 insertions(+), 4 deletions(-)

```
#### [PATCH RESEND]  kvm/x86: propagate fetch fault into guest
##### From: Peng Hao <penghao122@sina.com.cn>

```c
From: Peng Hao <peng.hao2@zte.com.cn>

When handling ept misconfig exit, it will call emulate instruction
with insn_len = 0. The decode instruction function may return a fetch
fault and should propagate to guest.

The problem will result to emulation fail.
KVM internal error. Suberror: 1
emulation failure
EAX=f81a0024 EBX=f6a07000 ECX=f6a0737c EDX=f8be0118
ESI=f6a0737c EDI=00000021 EBP=f6929f98 ESP=f6929f98
EIP=f8bdd141 EFL=00010086 [--S--P-] CPL=0 II=0 A20=1 SMM=0 HLT=0
ES =007b 00000000 ffffffff 00c0f300 DPL=3 DS   [-WA]
CS =0060 00000000 ffffffff 00c09b00 DPL=0 CS32 [-RA]
SS =0068 00000000 ffffffff 00c09300 DPL=0 DS   [-WA]
DS =007b 00000000 ffffffff 00c0f300 DPL=3 DS   [-WA]
FS =00d8 2c044000 ffffffff 00809300 DPL=0 DS16 [-WA]
GS =0033 081a44c8 01000fff 00d0f300 DPL=3 DS   [-WA]
LDT=0000 00000000 ffffffff 00000000
TR =0080 f6ea0c80 0000206b 00008b00 DPL=0 TSS32-busy
GDT=     f6e99000 000000ff
IDT=     fffbb000 000007ff
CR0=80050033 CR2=b757d000 CR3=35d31000 CR4=001406d0

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
Reviewed-by: Jiang Biao <jiang.biao2@zte.com.cn>
---
 arch/x86/kvm/emulate.c | 5 ++++-
 arch/x86/kvm/x86.c     | 4 +++-
 2 files changed, 7 insertions(+), 2 deletions(-)

```
#### [RFC v2 01/20] iommu: Introduce bind_pasid_table API
##### From: Eric Auger <eric.auger@redhat.com>

```c
From: Jacob Pan <jacob.jun.pan@linux.intel.com>

In virtualization use case, when a guest is assigned
a PCI host device, protected by a virtual IOMMU on a guest,
the physical IOMMU must be programmed to be consistent with
the guest mappings. If the physical IOMMU supports two
translation stages it makes sense to program guest mappings
onto the first stage/level (ARM/VTD terminology) while to host
owns the stage/level 2.

In that case, it is mandated to trap on guest configuration
settings and pass those to the physical iommu driver.

This patch adds a new API to the iommu subsystem that allows
to bind and unbind the guest configuration data to the host.

A generic iommu_pasid_table_config struct is introduced in
a new iommu.h uapi header. This is going to be used by the VFIO
user API. We foresee at least two specializations of this struct,
for PASID table passing and ARM SMMUv3.

Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Liu, Yi L <yi.l.liu@linux.intel.com>
Signed-off-by: Ashok Raj <ashok.raj@intel.com>
Signed-off-by: Jacob Pan <jacob.jun.pan@linux.intel.com>
Signed-off-by: Eric Auger <eric.auger@redhat.com>
---

In practice, I think it would be simpler to have a single
set_pasid_table function instead of bind/unbind. The "bypass" field
tells the stage 1 is bypassed (equivalent to the unbind actually).
On userspace we have notifications that the device context has changed.
Calling either bind or unbind requires to have an understand of what
was the previous state and call different notifiers. So to me the
bind/unbind complexifies the user integration while not bring much
benefits.

This patch generalizes the API introduced by Jacob & co-authors in
https://lwn.net/Articles/754331/

v1 -> v2:
- restore the original pasid table name
- remove the struct device * parameter in the API
- reworked iommu_pasid_smmuv3
---
 drivers/iommu/iommu.c      | 19 ++++++++++++++
 include/linux/iommu.h      | 21 +++++++++++++++
 include/uapi/linux/iommu.h | 52 ++++++++++++++++++++++++++++++++++++++
 3 files changed, 92 insertions(+)
 create mode 100644 include/uapi/linux/iommu.h

```
#### [PATCH v2 1/2] vfio: add edid api for display (vgpu) devices.
##### From: Gerd Hoffmann <kraxel@redhat.com>

```c
Signed-off-by: Gerd Hoffmann <kraxel@redhat.com>
---
 include/uapi/linux/vfio.h | 39 +++++++++++++++++++++++++++++++++++++++
 1 file changed, 39 insertions(+)

```
#### [PATCH 1/3] vhost/scsi: Respond to control queue operations
##### From: Bijan Mottahedeh <bijan.mottahedeh@oracle.com>

```c
The vhost-scsi driver currently does not handle any control queue
operations. In particular, vhost_scsi_ctl_handle_kick, merely prints out
a debug message but does nothing else. This can cause guest VMs to hang.

As part of SCSI recovery from an error, e.g., an I/O timeout, the SCSI
midlayer attempts to abort the failed operation. The SCSI virtio driver
translates the abort to a SCSI TMF request that gets put on the control
queue (virtscsi_abort -> virtscsi_tmf). The SCSI virtio driver then
waits indefinitely for this request to be completed, but it never will
because vhost-scsi never responds to that request.

To avoid a hang, always respond to control queue operations; explicitly
reject TMF requests, and return a no-op response to event requests.

Signed-off-by: Bijan Mottahedeh <bijan.mottahedeh@oracle.com>
---
 drivers/vhost/scsi.c | 190 +++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 190 insertions(+)

```
#### [PATCH V2 1/13] KVM: Add tlb_remote_flush_with_range callback in kvm_x86_ops
##### From: Tianyu Lan <Tianyu.Lan@microsoft.com>

```c
Add flush range call back in the kvm_x86_ops and platform can use it
to register its associated function. The parameter "kvm_tlb_range"
accepts a single range and flush list which contains a list of ranges.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
Change since v1:
       Change "end_gfn" to "pages" to aviod confusion as to whether
"end_gfn" is inclusive or exlusive.
---
 arch/x86/include/asm/kvm_host.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH v1 RESEND 1/9] x86/kvm/mmu: make vcpu->mmu a pointer to the current MMU
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
As a preparation to full MMU split between L1 and L2 make vcpu->arch.mmu
a pointer to the currently used mmu. For now, this is always
vcpu->arch.root_mmu. No functional change.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |   5 +-
 arch/x86/kvm/mmu.c              | 165 ++++++++++++++++++++--------------------
 arch/x86/kvm/mmu.h              |   8 +-
 arch/x86/kvm/mmu_audit.c        |  12 +--
 arch/x86/kvm/paging_tmpl.h      |  15 ++--
 arch/x86/kvm/svm.c              |  14 ++--
 arch/x86/kvm/vmx.c              |  15 ++--
 arch/x86/kvm/x86.c              |  20 ++---
 8 files changed, 130 insertions(+), 124 deletions(-)

```
