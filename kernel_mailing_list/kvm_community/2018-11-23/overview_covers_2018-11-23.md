

#### [PATCH net-next 0/3] basic in order support for vhost_net
##### From: Jason Wang <jasowang@redhat.com>

```c

Hi:

This series implement basic in order feature support for
vhost_net. This feature requires both driver and device to use
descriptors in order which can simplify the implementation and
optimizaton for both side. The series also implement a simple
optimization that avoid read available ring. Test shows 10%
performance improvement.

More optimizations could be done on top.

Jason Wang (3):
  virtio: introduce in order feature bit
  vhost_net: support in order feature
  vhost: don't touch avail ring if in_order is negotiated

 drivers/vhost/net.c                |  6 ++++--
 drivers/vhost/vhost.c              | 19 ++++++++++++-------
 include/uapi/linux/virtio_config.h |  6 ++++++
 3 files changed, 22 insertions(+), 9 deletions(-)
```
#### [PATCH v2 0/8] Workaround for Cortex-A76 erratum 1165522
##### From: Marc Zyngier <marc.zyngier@arm.com>

```c

Early Cortex-A76 suffer from an erratum that can result in invalid
TLBs when the CPU speculatively executes an AT instruction in the
middle of a guest world switch, while the guest virtual memory
configuration is in an inconsistent state.

We handle this issue by mandating the use of VHE and making sure that
the guest context is fully installed before switching HCR_EL2.TGE to
zero. This ensures that a speculated AT instruction is either executed
on the host context (TGE set) or the guest context (TGE clear), and
that there is no intermediate state.

There is some additional complexity in the TLB invalidation code,
where we most make sure that a speculated AT instruction cannot mess
the stage-1 TLBs.

* From v1:
  - VHE TLB invalidation now atomic
  - Avoid speculated AT during TLB invalidation
  - Addressed most comments from Christoffer
  - Resplit to ease reviewing

Marc Zyngier (8):
  arm64: KVM: Make VHE Stage-2 TLB invalidation operations
    non-interruptible
  KVM: arm64: Rework detection of SVE, !VHE systems
  arm64: KVM: Install stage-2 translation before enabling traps
  arm64: Add TCR_EPD{0,1} definitions
  arm64: KVM: Force VHE for systems affected by erratum 1165522
  arm64: KVM: Add synchronization on translation regime change for
    erratum 1165522
  arm64: KVM: Handle ARM erratum 1165522 in TLB invalidation
  arm64: Add configuration/documentation for Cortex-A76 erratum 1165522

 Documentation/arm64/silicon-errata.txt |  1 +
 arch/arm/include/asm/kvm_host.h        |  2 +-
 arch/arm64/Kconfig                     | 12 +++++
 arch/arm64/include/asm/cpucaps.h       |  3 +-
 arch/arm64/include/asm/kvm_host.h      | 10 ++--
 arch/arm64/include/asm/kvm_hyp.h       |  7 +++
 arch/arm64/include/asm/pgtable-hwdef.h |  4 ++
 arch/arm64/kernel/cpu_errata.c         |  8 +++
 arch/arm64/kvm/hyp/switch.c            | 23 +++++++-
 arch/arm64/kvm/hyp/tlb.c               | 73 ++++++++++++++++++++++----
 virt/kvm/arm/arm.c                     |  8 +--
 11 files changed, 130 insertions(+), 21 deletions(-)
```
