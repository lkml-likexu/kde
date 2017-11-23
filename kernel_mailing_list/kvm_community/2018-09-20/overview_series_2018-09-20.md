#### [PATCH v3 1/5] perf/x86: add a function to get the lbr stack
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
#### [PATCH] KVM: nVMX: Clear reserved bits of #DB exit qualificationFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
Per volume 2 of the SDM, bits 63:15 and 12:4 of the exit qualification
field for debug exceptions are reserved (cleared to 0).

There is still an issue with stale DR6 bits potentially being
misreported for the current debug exception.  DR6 should not have been
modified before vectoring the #DB exception, and the "new DR6 bits"
should be available somewhere, but it was and they aren't.

Fixes: b96fb439774e1 ("KVM: nVMX: fixes to nested virt interrupt injection")
Signed-off-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/include/asm/kvm_host.h | 1 +
 arch/x86/kvm/vmx.c              | 3 ++-
 2 files changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] arm/arm64: fix gic-ipi test regression
##### From: Andrew Jones <drjones@redhat.com>

```c
The gic-ipi tests started crashing in a strange way after
commit 9064d89b ("kvm-unit-tests: unlock before calling
return"). Eventually I narrowed it down to the NR_CPUS change
being the problem. I still don't understand what's going on,
but NR_CPUS=511 works and NR_CPUS=512 doesn't. I don't have
time to debug this further right now, so this is just a
temporary hack that appears to fix the regression.

Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 lib/arm/asm/setup.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH net-next] vhost_net: add a missing error return
##### From: Dan Carpenter <dan.carpenter@oracle.com>

```c
We accidentally left out this error return so it leads to some use after
free bugs later on.

Fixes: 0a0be13b8fe2 ("vhost_net: batch submitting XDP buffers to underlayer sockets")
Signed-off-by: Dan Carpenter <dan.carpenter@oracle.com>
Acked-by: Michael S. Tsirkin <mst@redhat.com>
Acked-by: Jason Wang <jasowang@redhat.com>

```
#### [PATCH RESEND]  kvm:x86 :remove unnecessary recalculate_apic_map
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
In the previous code, the variable sw_apic_disabled is accessed in
recalculate_apic_map. Now it has never accessed sw_apic_disabled,
so it is unnecessary to call recalculate_apic_map when sw_apic_disabled
changes.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/lapic.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH] s390/cio: Refactor alloc of vfio_ccw_private
##### From: Eric Farman <farman@linux.ibm.com>

```c
If I attach a vfio-ccw device to my guest, I get the following warning
on the host when the host kernel is CONFIG_HARDENED_USERCOPY=y

[250757.595325] Bad or missing usercopy whitelist? Kernel memory overwrite attempt detected to SLUB object 'dma-kmalloc-512' (offset 64, size 124)!
[250757.595365] WARNING: CPU: 2 PID: 10958 at mm/usercopy.c:81 usercopy_warn+0xac/0xd8
[250757.595369] Modules linked in: kvm vhost_net vhost tap xt_CHECKSUM iptable_mangle ipt_MASQUERADE iptable_nat nf_nat_ipv4 nf_nat nf_conntrack_ipv4 nf_defrag_ipv4 xt_conntrack nf_conntrack libcrc32c devlink tun bridge stp llc ebtable_filter ebtables ip6table_filter ip6_tables sunrpc dm_multipath s390_trng crc32_vx_s390 ghash_s390 prng aes_s390 des_s390 des_generic sha512_s390 sha1_s390 eadm_sch tape_3590 tape tape_class qeth_l2 qeth ccwgroup vfio_ccw vfio_mdev zcrypt_cex4 mdev vfio_iommu_type1 zcrypt vfio sha256_s390 sha_common zfcp scsi_transport_fc qdio dasd_eckd_mod dasd_mod
[250757.595424] CPU: 2 PID: 10958 Comm: CPU 2/KVM Not tainted 4.18.0-derp #2
[250757.595426] Hardware name: IBM 3906 M05 780 (LPAR)
...snip regs...
[250757.595523] Call Trace:
[250757.595529] ([<0000000000349210>] usercopy_warn+0xa8/0xd8)
[250757.595535]  [<000000000032daaa>] __check_heap_object+0xfa/0x160
[250757.595540]  [<0000000000349396>] __check_object_size+0x156/0x1d0
[250757.595547]  [<000003ff80332d04>] vfio_ccw_mdev_write+0x74/0x148 [vfio_ccw]
[250757.595552]  [<000000000034ed12>] __vfs_write+0x3a/0x188
[250757.595556]  [<000000000034f040>] vfs_write+0xa8/0x1b8
[250757.595559]  [<000000000034f4e6>] ksys_pwrite64+0x86/0xc0
[250757.595568]  [<00000000008959a0>] system_call+0xdc/0x2b0
[250757.595570] Last Breaking-Event-Address:
[250757.595573]  [<0000000000349210>] usercopy_warn+0xa8/0xd8

While vfio_ccw_mdev_{write|read} validates that the input position/count
does not run over the ccw_io_region struct, the usercopy code that does
copy_{to|from}_user doesn't necessarily know this. It sees the variable
length and gets worried that it's affecting a normal kmalloc'd struct,
and generates the above warning.

Adjust how the vfio_ccw_struct is alloc'd, with a whitelist for the
ccw_io_region within it, to remove this warning. The boundary checking
will continue to do its thing.

Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_drv.c | 21 ++++++++++++++++++---
 1 file changed, 18 insertions(+), 3 deletions(-)

```
#### [PATCH v2] vfio/pci: Mask buggy SR-IOV VF INTx supportFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
The SR-IOV spec requires that VFs must report zero for the INTx pin
register as VFs are precluded from INTx support.  It's much easier for
the host kernel to understand whether a device is a VF and therefore
whether a non-zero pin register value is bogus than it is to do the
same in userspace.  Override the INTx count for such devices and
virtualize the pin register to provide a consistent view of the device
to the user.

As this is clearly a spec violation, warn about it to support hardware
validation, but also provide a known whitelist as it doesn't do much
good to continue complaining if the hardware vendor doesn't plan to
fix it.

Known devices with this issue: 8086:270c

Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
Tested-by: Gage Eads <gage.eads@intel.com>
Reviewed-by: Ashok Raj <ashok.raj@intel.com>
---

v2:
Moved the warning to vfio_config_init(), so it triggers on device open and
no longer depends on the user looking at the number of INTx IRQs available.
Also changed from dev_warn_once() to pci_warn() as this new location seems
sufficiently low frequency to nag repeatedly.  Please test.  Thanks,

Alex

 drivers/vfio/pci/vfio_pci.c        |    8 ++++++--
 drivers/vfio/pci/vfio_pci_config.c |   27 +++++++++++++++++++++++++++
 2 files changed, 33 insertions(+), 2 deletions(-)

```
