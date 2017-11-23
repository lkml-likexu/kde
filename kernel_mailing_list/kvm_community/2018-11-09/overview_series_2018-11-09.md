#### [PATCH] KVM: PPC: Book3S HV: fix handling for interrupted H_ENTER_NESTED
##### From: Michael Roth <mdroth@linux.vnet.ibm.com>

```c
While running a nested guest VCPU on L0 via H_ENTER_NESTED hcall, a
pending signal in the L0 QEMU process can generate the following
sequence:

  ret0 = kvmppc_pseries_do_hcall()
    ret1 = kvmhv_enter_nested_guest()
      ret2 = kvmhv_run_single_vcpu()
      if (ret2 == -EINTR)
        return H_INTERRUPT
    if (ret1 == H_INTERRUPT)
      kvmppc_set_gpr(vcpu, 3, 0)
      return -EINTR
    /* skipped: */
    kvmppc_set_gpr(vcpu, 3, ret)
    vcpu->arch.hcall_needed = 0
    return RESUME_GUEST

which causes an exit to L0 userspace with ret0 == -EINTR.

The intention seems to be to set the hcall return value to 0 (via
VCPU r3) so that L1 will see a successful return from H_ENTER_NESTED
once we resume executing the VCPU. However, because we don't set
vcpu->arch.hcall_needed = 0, we do the following once userspace
resumes execution via kvm_arch_vcpu_ioctl_run():

  ...
  } else if (vcpu->arch.hcall_needed) {
    int i

    kvmppc_set_gpr(vcpu, 3, run->papr_hcall.ret);
    for (i = 0; i < 9; ++i)
           kvmppc_set_gpr(vcpu, 4 + i, run->papr_hcall.args[i]);
    vcpu->arch.hcall_needed = 0;

since vcpu->arch.hcall_needed == 1 indicates that userspace should
have handled the hcall and stored the return value in
run->papr_hcall.ret. Since that's not the case here, we can get an
unexpected value in VCPU r3, which can result in
kvmhv_p9_guest_entry() reporting an unexpected trap value when it
returns from H_ENTER_NESTED, causing the following register dump to
console via subsequent call to kvmppc_handle_exit_hv() in L1:

  [  350.612854] vcpu 00000000f9564cf8 (0):
  [  350.612915] pc  = c00000000013eb98  msr = 8000000000009033  trap = 1
  [  350.613020] r 0 = c0000000004b9044  r16 = 0000000000000000
  [  350.613075] r 1 = c00000007cffba30  r17 = 0000000000000000
  [  350.613120] r 2 = c00000000178c100  r18 = 00007fffc24f3b50
  [  350.613166] r 3 = c00000007ef52480  r19 = 00007fffc24fff58
  [  350.613212] r 4 = 0000000000000000  r20 = 00000a1e96ece9d0
  [  350.613253] r 5 = 70616d00746f6f72  r21 = 00000a1ea117c9b0
  [  350.613295] r 6 = 0000000000000020  r22 = 00000a1ea1184360
  [  350.613338] r 7 = c0000000783be440  r23 = 0000000000000003
  [  350.613380] r 8 = fffffffffffffffc  r24 = 00000a1e96e9e124
  [  350.613423] r 9 = c00000007ef52490  r25 = 00000000000007ff
  [  350.613469] r10 = 0000000000000004  r26 = c00000007eb2f7a0
  [  350.613513] r11 = b0616d0009eccdb2  r27 = c00000007cffbb10
  [  350.613556] r12 = c0000000004b9000  r28 = c00000007d83a2c0
  [  350.613597] r13 = c000000001b00000  r29 = c0000000783cdf68
  [  350.613639] r14 = 0000000000000000  r30 = 0000000000000000
  [  350.613681] r15 = 0000000000000000  r31 = c00000007cffbbf0
  [  350.613723] ctr = c0000000004b9000  lr  = c0000000004b9044
  [  350.613765] srr0 = 0000772f954dd48c srr1 = 800000000280f033
  [  350.613808] sprg0 = 0000000000000000 sprg1 = c000000001b00000
  [  350.613859] sprg2 = 0000772f9565a280 sprg3 = 0000000000000000
  [  350.613911] cr = 88002848  xer = 0000000020040000  dsisr = 42000000
  [  350.613962] dar = 0000772f95390000
  [  350.614031] fault dar = c000000244b278c0 dsisr = 00000000
  [  350.614073] SLB (0 entries):
  [  350.614157] lpcr = 0040000003d40413 sdr1 = 0000000000000000 last_inst = ffffffff
  [  350.614252] trap=0x1 | pc=0xc00000000013eb98 | msr=0x8000000000009033

followed by L1's QEMU reporting the following before stopping execution
of the nested guest:

  KVM: unknown exit, hardware reason 1
  NIP c00000000013eb98   LR c0000000004b9044 CTR c0000000004b9000 XER 0000000020040000 CPU#0
  MSR 8000000000009033 HID0 0000000000000000  HF 8000000000000000 iidx 3 didx 3
  TB 00000000 00000000 DECR 00000000
  GPR00 c0000000004b9044 c00000007cffba30 c00000000178c100 c00000007ef52480
  GPR04 0000000000000000 70616d00746f6f72 0000000000000020 c0000000783be440
  GPR08 fffffffffffffffc c00000007ef52490 0000000000000004 b0616d0009eccdb2
  GPR12 c0000000004b9000 c000000001b00000 0000000000000000 0000000000000000
  GPR16 0000000000000000 0000000000000000 00007fffc24f3b50 00007fffc24fff58
  GPR20 00000a1e96ece9d0 00000a1ea117c9b0 00000a1ea1184360 0000000000000003
  GPR24 00000a1e96e9e124 00000000000007ff c00000007eb2f7a0 c00000007cffbb10
  GPR28 c00000007d83a2c0 c0000000783cdf68 0000000000000000 c00000007cffbbf0
  CR 88002848  [ L  L  -  -  E  L  G  L  ]             RES ffffffffffffffff
   SRR0 0000772f954dd48c  SRR1 800000000280f033    PVR 00000000004e1202 VRSAVE 0000000000000000
  SPRG0 0000000000000000 SPRG1 c000000001b00000  SPRG2 0000772f9565a280  SPRG3 0000000000000000
  SPRG4 0000000000000000 SPRG5 0000000000000000  SPRG6 0000000000000000  SPRG7 0000000000000000
  HSRR0 0000000000000000 HSRR1 0000000000000000
   CFAR 0000000000000000
   LPCR 0000000003d40413
   PTCR 0000000000000000   DAR 0000772f95390000  DSISR 0000000042000000

Fix this by setting vcpu->arch.hcall_needed = 0 to indicate completion
of H_ENTER_NESTED before we exit to L0 userspace.

Cc: linuxppc-dev@ozlabs.org
Cc: David Gibson <david@gibson.dropbear.id.au>
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Signed-off-by: Michael Roth <mdroth@linux.vnet.ibm.com>
---
 arch/powerpc/kvm/book3s_hv.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH 1/7] iommu/amd: Collect page-table pages in freelist
##### From: Joerg Roedel <joro@8bytes.org>

```c
From: Joerg Roedel <jroedel@suse.de>

Collect all pages that belong to a page-table in a list and
free them after the tree has been traversed. This allows to
implement safer page-table updates in subsequent patches.
Also move the functions for page-table freeing a bit upwards
in the file so that they are usable from the iommu_map() path.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 drivers/iommu/amd_iommu.c | 144 ++++++++++++++++++++++----------------
 1 file changed, 83 insertions(+), 61 deletions(-)

```
#### [PATCH kvm-unit-tests] x86/hyperv: pass hv_vpindex cpu flag along with hv_synic
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Since Qemu commit 9b4cf107b09d ("hyperv: only add SynIC in compatible
 configurations") hv_vpindex flag is mandatory if hv_synic is used:

$ qemu-system-x86_64 -nodefaults -cpu kvm64,hv_time,hv_synic,hv_stimer  \
     -device hyperv-testdev -device pc-testdev -device isa-debug-exit,  \
     iobase=0xf4,iosize=0x4 -vnc none -serial stdio -device pci-testdev \
     -machine accel=kvm -kernel x86/hyperv_stimer.flat

Results in:

Hyper-V SynIC (requested by 'hv-synic' cpu flag) requires Hyper-V VP_INDEX
 ('hv-vpindex')
qemu-system-x86_64: kvm_init_vcpu failed: Function not implemented

Fix the configuration.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 x86/unittests.cfg | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] x86/intel-iommu: add test for address width 48 and 57.
##### From: Yu Zhang <yu.c.zhang@linux.intel.com>

```c
Current iommu test only covers 39-bit address width. This patch
extends the test case to based on the supported maximum guest
address width.

Signed-off-by: Yu Zhang <yu.c.zhang@linux.intel.com>
Reviewed-by: Michael S. Tsirkin <mst@redhat.com>
---
 lib/x86/intel-iommu.c | 14 ++++----------
 lib/x86/intel-iommu.h | 11 ++++++++++-
 x86/intel-iommu.c     | 21 ++++++++++++++++-----
 3 files changed, 30 insertions(+), 16 deletions(-)

```
#### [PATCH 1/2] mm: make dev_pagemap_mapping_shift() externally visibleFrom: Barret Rhoden <brho@google.com>
##### From: Barret Rhoden <brho@google.com>

```c
KVM has a use case for determining the size of a dax mapping.  The KVM
code has easy access to the address and the mm; hence the change in
parameters.

Signed-off-by: Barret Rhoden <brho@google.com>
---
 include/linux/mm.h  |  3 +++
 mm/memory-failure.c | 38 +++-----------------------------------
 mm/util.c           | 34 ++++++++++++++++++++++++++++++++++
 3 files changed, 40 insertions(+), 35 deletions(-)

```
#### [PATCH] kvm: vmx: Allow guest read access to IA32_TSCFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Let the guest read the IA32_TSC MSR with the generic RDMSR instruction
as well as the specific RDTSC(P) instructions. Note that the hardware
applies the TSC multiplier and offset (when applicable) to the result of
RDMSR(IA32_TSC), just as it does to the result of RDTSC(P).

Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] kvm: vmx: Set IA32_TSC_AUX for legacy mode guestsFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
RDTSCP is supported in legacy mode as well as long mode. The
IA32_TSC_AUX MSR should be set to the correct guest value before
entering any guest that supports RDTSCP.

Fixes: 4e47c7a6d714 ("KVM: VMX: Add instruction rdtscp support for guest")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [PATCH] uio/uio_pci_generic: Disable bus-mastering on releaseFrom: Venkatesh Srinivas <venkateshs@google.com>
##### From: Venkatesh Srinivas <venkateshs@google.com>

```c
Userspace code using uio_pci_generic may enable bus-mastering by
directly manipulating a PCI device's command register. If a userspace
program enables bus-mastering but exits/crashes uncleanly, bus-
mastering will still be enabled and stale DMA addresses may be
programmed and live in the device.

Disable bus-mastering unconditionally on last close of a UIO PCI fd
to avoid this. If the device did not have bus-mastering enabled,
pci_clear_master() is a no-op.

Signed-off-by: Venkatesh Srinivas <venkateshs@google.com>
Reviewed-by: Bjorn Helgaas <bhelgaas@google.com>
Reviewed-by: Catherine Sullivan <csully@google.com>
---
 drivers/uio/uio_pci_generic.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [PATCH v2 1/4] kvm: vmx: Set IA32_TSC_AUX for legacy mode guestsFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
RDTSCP is supported in legacy mode as well as long mode. The
IA32_TSC_AUX MSR should be set to the correct guest value before
entering any guest that supports RDTSCP.

Fixes: 4e47c7a6d714 ("KVM: VMX: Add instruction rdtscp support for guest")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
#### [RFC PATCH v1 01/10] s390/cio: Fix cleanup of pfn_array alloc failure
##### From: Eric Farman <farman@linux.ibm.com>

```c
If pfn_array_alloc fails somehow, we need to release the pfn_array_table
that was malloc'd earlier.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] vfio/pci: Parallelize device open and releaseFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
In commit 61d792562b53 ("vfio-pci: Use mutex around open, release, and
remove") a mutex was added to freeze the refcnt for a device so that
we can handle errors and perform bus resets on final close.  However,
bus resets can be rather slow and a global mutex here is undesirable.
A per-device mutex provides the best granularity, but then our chances
of triggering a bus/slot reset with multiple affected devices is slim
when devices are released in parallel.  Instead create a reflck object
shared among all devices under the same bus or slot, allowing devices
on independent buses to be released in parallel while serializing per
bus/slot.

Reported-by: Christian Ehrhardt <christian.ehrhardt@canonical.com>
Tested-by: Christian Ehrhardt <christian.ehrhardt@canonical.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci.c         |  157 ++++++++++++++++++++++++++++++-----
 drivers/vfio/pci/vfio_pci_private.h |    6 +
 2 files changed, 139 insertions(+), 24 deletions(-)

```
