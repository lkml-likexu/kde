

#### [PATCH 0/2] Fix reserved bits calculation errors caused by MKTME
##### From: Kai Huang <kai.huang@linux.intel.com>

```c

This series fix reserved bits related calculation errors caused by MKTME. MKTME
repurposes high bits of physical address bits as 'keyID' thus they are not
reserved bits, and to honor such HW behavior those reduced bits are taken away
from boot_cpu_data.x86_phys_bits when MKTME is detected (exactly how many bits
are taken away is configured by BIOS). Currently KVM asssumes bits from
boot_cpu_data.x86_phys_bits to 51 are reserved bits, which is not true anymore
with MKTME, and needs fix.

This series was splitted from the old patch I sent out around 2 weeks ago:

kvm: x86: Fix several SPTE mask calculation errors caused by MKTME

Changes to old patch:

  - splitted one patch into two patches. First patch is to move
    kvm_set_mmio_spte_mask() as prerequisite. It doesn't impact functionality.
    Patch 2 does the real fix.

  - renamed shadow_first_rsvd_bits to shadow_phys_bits suggested by Sean.

  - refined comments and commit msg to be more concise.

Btw sorry that I will be out next week and won't be able to reply email.

Kai Huang (2):
  kvm: x86: Move kvm_set_mmio_spte_mask() from x86.c to mmu.c
  kvm: x86: Fix reserved bits related calculation errors caused by MKTME

 arch/x86/kvm/mmu.c | 61 ++++++++++++++++++++++++++++++++++++++++++++++++++----
 arch/x86/kvm/x86.c | 31 ---------------------------
 2 files changed, 57 insertions(+), 35 deletions(-)
```
#### [PATCH v1 0/7] s390: vfio-ccw fixes
##### From: Eric Farman <farman@linux.ibm.com>

```c

The attached are a few fixes to the vfio-ccw kernel code for potential
errors or architecture anomalies.  Under normal usage, and even most
abnormal usage, they don't expose any problems to a well-behaved guest
and its devices.  But, they are deficiencies just the same and could
cause some weird behavior if they ever popped up in real life.

I have tried to arrange these patches in a "solves a noticeable problem
with existing workloads" to "solves a theoretical problem with
hypothetical workloads" order.  This way, the bigger ones at the end
can be discussed without impeding the smaller and more impactful ones
at the start.

They are based on today's master, not Conny's vfio-ccw tree even though
there are some good fixes pending there.  I've run this series both with
and without that code, but couldn't decide which base would provide an
easier time applying patches.  "I think" they should apply fine to both,
but I apologize in advance if I guessed wrong!  :)

Eric Farman (7):
  s390/cio: Update SCSW if it points to the end of the chain
  s390/cio: Set vfio-ccw FSM state before ioeventfd
  s390/cio: Split pfn_array_alloc_pin into pieces
  s390/cio: Initialize the host addresses in pfn_array
  s390/cio: Allow zero-length CCWs in vfio-ccw
  s390/cio: Don't pin vfio pages for empty transfers
  s390/cio: Remove vfio-ccw checks of command codes

 drivers/s390/cio/vfio_ccw_cp.c  | 163 ++++++++++++++++++++++++++++------------
 drivers/s390/cio/vfio_ccw_drv.c |   6 +-
 2 files changed, 116 insertions(+), 53 deletions(-)
```
#### [PATCH v6 0/3] KVM: arm/arm64: Add VCPU workarounds firmware register
##### From: Andre Przywara <andre.przywara@arm.com>

```c

Hi,

hopefully the final update on this series, rebasing on Catalin's and
Will's arm64/for-next/mitigations branch.
This slightly adjusts the internal names to use "not required"
instead of "unaffected", which is less precise.
As introduced in v5, this one contains the patch to propagate the new
"not required" state for Spectre v2 to KVM and its guests.

Cheers,
Andre

-----------------------------
Workarounds for Spectre variant 2 or 4 vulnerabilities require some help
from the firmware, so KVM implements an interface to provide that for
guests. When such a guest is migrated, we want to make sure we don't
loose the protection the guest relies on.

This introduces two new firmware registers in KVM's GET/SET_ONE_REG
interface, so userland can save the level of protection implemented by
the hypervisor and used by the guest. Upon restoring these registers,
we make sure we don't downgrade and reject any values that would mean
weaker protection.
The protection level is encoded in the lower 4 bits, with smaller
values indicating weaker protection.

ARM(32) is a bit of a pain (again), as the firmware register interface
is shared, but 32-bit does not implement all the workarounds.
For now I stuffed two wrappers into kvm_emulate.h, which doesn't sound
like the best solution. Happy to hear about better solutions.

This has been tested with migration between two Juno systems. Out of the
box they advertise identical workaround levels, and migration succeeds.
However when disabling the A57 cluster on one system, WORKAROUND_1 is
not needed and the host kernel propagates this. Migration now only
succeeds in one direction (from the big/LITTLE configuration to the
A53-only setup).

Please have a look and comment!

This is based upon arm64/for-next/migitations.
Find a git branch here:
{git,http}://linux-arm.org/linux-ap.git branch fw-regs/v6-sysfs

Cheers,
Andre

Changelog:
v5 .. v6:
- rebase on merged sysfs vulnerabilities series
- rename ..._UNAFFECTED to ..._NOT_REQUIRED
- rename ARM64_BP_HARDEN_MITIGATED
- add tags

v4 .. v5:
- add patch to advertise ARM64_BP_HARDEN_MITIGATED state to a guest
- allow migration from KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_AVAIL to
  (new) KVM_REG_ARM_SMCCC_ARCH_WORKAROUND_1_UNAFFECTED
- reword API documentation
- return -EINVAL on querying invalid firmware register
- add some comments
- minor fixes according to Eric's review

v3 .. v4:
- clarify API documentation for WORKAROUND_1
- check for unknown bits in userland provided register values
- report proper -ENOENT when register ID is unknown

v2 .. v3:
- rebase against latest kvm-arm/next
- introduce UNAFFECTED value for WORKAROUND_1
- require exact match for WORKAROUND_1 levels

v1 .. v2:
- complete rework of WORKAROUND_2 presentation to use a linear scale,
  dropping the complicated comparison routine

Andre Przywara (3):
  arm64: KVM: Propagate full Spectre v2 workaround state to KVM guests
  KVM: arm/arm64: Add save/restore support for firmware workaround state
  KVM: doc: add API documentation on the KVM_REG_ARM_WORKAROUNDS
    register

 Documentation/virtual/kvm/arm/psci.txt |  31 +++++
 arch/arm/include/asm/kvm_emulate.h     |  10 ++
 arch/arm/include/asm/kvm_host.h        |  12 +-
 arch/arm/include/uapi/asm/kvm.h        |  12 ++
 arch/arm64/include/asm/cpufeature.h    |   6 +
 arch/arm64/include/asm/kvm_emulate.h   |  14 +++
 arch/arm64/include/asm/kvm_host.h      |  16 ++-
 arch/arm64/include/uapi/asm/kvm.h      |  10 ++
 arch/arm64/kernel/cpu_errata.c         |  23 +++-
 virt/kvm/arm/psci.c                    | 149 ++++++++++++++++++++++---
 10 files changed, 257 insertions(+), 26 deletions(-)
```
#### [PATCH kvmtool 0/2] Automatically clean up ghost socket files
##### From: Andre Przywara <andre.przywara@arm.com>

```c

kvmtool is creating UNIX socket inodes to communicate between a running
instance and a debug command issued by another lkvm process.
When kvmtool (or the kernel) crashes, those files are not cleaned up and
cause all kind of annoyances.
Those two patches delete leftover socket files on calling "lkvm list",
also remove an existing one (then reusing the same name) when creating
a guest.
This avoids random breakages when running kvmtool, and helps to run it
from scripts.

Cheers,
Andre

Andre Przywara (2):
  list: Clean up ghost socket files
  run: Check for ghost socket file upon VM creation

 kvm-ipc.c | 44 ++++++++++++++++++++++++++++++++++++--------
 1 file changed, 36 insertions(+), 8 deletions(-)
```
#### [PATCH kvmtool 0/4] kvmtool: clang/GCC9 fixes
##### From: Andre Przywara <andre.przywara@arm.com>

```c

When compiling kvmtool with clang (works only on aarch64/arm), it turned
up some interesting warnings. One of those is also issued by GCC9.

This series fixes them. More details in each commit message.

Please have look!

Cheers,
Andre.

Andre Przywara (4):
  vfio: remove spurious ampersand
  vfio: remove unneeded test
  vfio: rework vfio_irq_set payload setting
  virtio/blk: Avoid taking pointer to packed struct

 vfio/pci.c   | 28 ++++++++++++++--------------
 virtio/blk.c |  4 ++--
 2 files changed, 16 insertions(+), 16 deletions(-)
```
#### [kvm-unit-tests PATCH v2 0/4] Zero allocated pages
##### From: nadav.amit@gmail.com
From: Nadav Amit <nadav.amit@gmail.com>

```c

From: Nadav Amit <nadav.amit@gmail.com>

For reproducibility, it is best to zero pages before they are used.
There are hidden assumptions on memory being zeroed (by BIOS/KVM), which
might be broken at any given moment. The full argument appears in the
first patch commit log.

Following the first patch that zeros the memory, the rest of the
patch-set removes redundant zeroing do to the additional zeroing.

This patch-set is only tested on x86.

v1->v2:
* Change alloc_pages() as well
* Remove redundant page zeroing [Andrew]

Nadav Amit (4):
  lib/alloc_page: Zero allocated pages
  x86: Remove redeundant page zeroing
  lib: Remove redeundant page zeroing
  arm: Remove redeundant page zeroing

 lib/alloc_page.c         |  4 ++++
 lib/arm/asm/pgtable.h    |  2 --
 lib/arm/mmu.c            |  1 -
 lib/arm64/asm/pgtable.h  |  1 -
 lib/virtio-mmio.c        |  1 -
 lib/x86/intel-iommu.c    |  5 -----
 x86/eventinj.c           |  1 -
 x86/hyperv_connections.c |  4 ----
 x86/vmx.c                | 10 ----------
 x86/vmx_tests.c          | 11 -----------
 10 files changed, 4 insertions(+), 36 deletions(-)
```
#### [PATCH v2 0/7] s390: vfio-ap: dynamic configuration support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c

This patch series extends the crypto adapter pass-through support to 
provide safeguards against inadvertent sharing of AP resources between
guests and/or the host, and to implement more of the s390 AP
architecture related to provisioning and dynamic configuration of
AP resources.

Change log v2->v3:
-----------------
* Allow guest access to an AP queue only if the queue is bound to
  the vfio_ap device driver.

* Removed the patch to test CRYCB masks before taking the vCPUs
  out of SIE. Now checking the shadow CRYCB in the vfio_ap driver.

Change log v1->v2:
-----------------
* Removed patches preventing root user from unbinding AP queues from 
  the vfio_ap device driver
* Introduced a shadow CRYCB in the vfio_ap driver to manage dynamic 
  changes to the AP guest configuration due to root user interventions
  or hardware anomalies.

Tony Krowiak (7):
  s390: vfio-ap: wait for queue empty on queue reset
  s390: vfio-ap: maintain a shadow of the guest's CRYCB
  s390: vfio-ap: sysfs interface to display guest CRYCB
  s390: vfio-ap: allow assignment of unavailable AP resources to mdev
    device
  s390: vfio-ap: allow hot plug/unplug of AP resources using mdev device
  s390: vfio-ap: handle bind and unbind of AP queue device
  s390: vfio-ap: update documentation

 Documentation/s390/vfio-ap.txt        | 191 +++++++----
 drivers/s390/crypto/vfio_ap_drv.c     |  12 +-
 drivers/s390/crypto/vfio_ap_ops.c     | 612 ++++++++++++++++++++++------------
 drivers/s390/crypto/vfio_ap_private.h |   4 +
 4 files changed, 536 insertions(+), 283 deletions(-)
```
