

#### [PATCH 0/8] KVM: PPC: Implement passthrough of emulated devices for
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c

This patch series allows for emulated devices to be passed through to nested
guests, irrespective of at which level the device is being emulated.

Note that the emulated device must be using dma, not virtio.

For example, passing through an emulated e1000:

1. Emulate the device at L(n) for L(n+1)

qemu-system-ppc64 -netdev type=user,id=net0 -device e1000,netdev=net0

2. Assign the VFIO-PCI driver at L(n+1)

echo 0000:00:00.0 > /sys/bus/pci/drivers/e1000/unbind
echo 0000:00:00.0 > /sys/bus/pci/drivers/vfio-pci/bind
chmod 666 /dev/vfio/0

3. Pass the device through from L(n+1) to L(n+2)

qemu-system-ppc64 -device vfio-pci,host=0000:00:00.0

4. L(n+2) can now access the device which will be emulated at L(n)

Suraj Jitindar Singh (8):
  KVM: PPC: Only report KVM_CAP_SPAPR_TCE_VFIO on powernv machines
  KVM: PPC: Book3S HV: Add function kvmhv_vcpu_is_radix()
  KVM: PPC: Book3S HV: Implement functions to access quadrants 1 & 2
  KVM: PPC: Add load_from_eaddr and store_to_eaddr to the kvmppc_ops
    struct
  KVM: PPC: Update kvmppc_st and kvmppc_ld to use quadrants
  KVM: PPC: Book3S HV: Allow passthrough of an emulated device to an L2
    guest
  KVM: PPC: Introduce new hcall H_COPY_TOFROM_GUEST to access quadrants
    1 & 2
  KVM: PPC: Book3S HV: Allow passthrough of an emulated device to an L3
    guest

 arch/powerpc/include/asm/hvcall.h        |   1 +
 arch/powerpc/include/asm/kvm_book3s.h    |  10 ++-
 arch/powerpc/include/asm/kvm_book3s_64.h |  13 ++++
 arch/powerpc/include/asm/kvm_host.h      |   3 +
 arch/powerpc/include/asm/kvm_ppc.h       |   4 ++
 arch/powerpc/kernel/exceptions-64s.S     |   9 +++
 arch/powerpc/kvm/book3s_64_mmu_radix.c   |  97 ++++++++++++++++++++++++++
 arch/powerpc/kvm/book3s_hv.c             |  58 ++++++++++++++--
 arch/powerpc/kvm/book3s_hv_nested.c      | 114 +++++++++++++++++++++++++++++--
 arch/powerpc/kvm/powerpc.c               |  28 +++++++-
 arch/powerpc/mm/fault.c                  |   1 +
 11 files changed, 323 insertions(+), 15 deletions(-)
```
