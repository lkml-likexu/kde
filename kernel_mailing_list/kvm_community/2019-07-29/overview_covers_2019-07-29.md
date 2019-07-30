

#### [PATCH 0/3] KVM: X86: Some tracepoint enhancements
##### From: Peter Xu <zhexu@redhat.com>
X-Google-Original-From: Peter Xu <peterx@redhat.com>

```c

Each small patch explains itself.  I noticed them when I'm tracing
some IRQ paths and I found them helpful at least to me.

Please have a look.  Thanks,

Peter Xu (3):
  KVM: X86: Trace vcpu_id for vmexit
  KVM: X86: Remove tailing newline for tracepoints
  KVM: X86: Tune PLE Window tracepoint

 arch/x86/kvm/svm.c     |  8 ++++----
 arch/x86/kvm/trace.h   | 33 ++++++++++++++++-----------------
 arch/x86/kvm/vmx/vmx.c |  4 ++--
 3 files changed, 22 insertions(+), 23 deletions(-)
```
#### [RFC PATCH 00/16] KVM RISC-V Support
##### From: Anup Patel <Anup.Patel@wdc.com>

```c

This series adds initial KVM RISC-V support. Currently, we are able to boot
RISC-V 64bit Linux Guests with multiple VCPUs.

Few key aspects of KVM RISC-V added by this series are:
1. Minimal possible KVM world-switch which touches only GPRs and few CSRs.
2. Full Guest/VM switch is done via vcpu_get/vcpu_put infrastructure.
3. KVM ONE_REG interface for VCPU register access from user-space.
4. PLIC emulation is done in user-space. In-kernel PLIC emulation, will
   be added in future.
5. Timer and IPI emuation is done in-kernel.
6. MMU notifiers supported.
7. FP lazy save/restore supported.
8. SBI v0.1 emulation for KVM Guest available.

More feature additions and enhancments will follow after this series and
eventually KVM RISC-V will be at-par with other architectures.

This series is based upon KVM pre-patches sent by Atish earlier
(https://lkml.org/lkml/2019/7/26/1271) and it can be found in
riscv_kvm_v1 branch at:
https//github.com/avpatel/linux.git

Our work-in-progress KVMTOOL RISC-V port can be found in riscv_v1 branch at:
https//github.com/avpatel/kvmtool.git

We need OpenSBI with RISC-V hypervisor extension support which can be
found in hyp_ext_changes_v1 branch at:
https://github.com/riscv/opensbi.git

The QEMU RISC-V hypervisor emulation is done by Alistair and is available
in riscv-hyp-work.next branch at:
https://github.com/alistair23/qemu.git

To play around with KVM RISC-V, here are few reference commands:
1) To cross-compile KVMTOOL:
   $ make lkvm-static
2) To launch RISC-V Host Linux:
   $ qemu-system-riscv64 -monitor null -cpu rv64,h=true -M virt \
   -m 512M -display none -serial mon:stdio \
   -kernel opensbi/build/platform/qemu/virt/firmware/fw_jump.elf \
   -device loader,file=build-riscv64/arch/riscv/boot/Image,addr=0x80200000 \
   -initrd ./rootfs_kvm_riscv64.img \
   -append "root=/dev/ram rw console=ttyS0 earlycon=sbi"
3) To launch RISC-V Guest Linux with 9P rootfs:
   $ ./apps/lkvm-static run -m 128 -c2 --console serial \
   -p "console=ttyS0 earlycon=uart8250,mmio,0x3f8" -k ./apps/Image --debug
4) To launch RISC-V Guest Linux with initrd:
   $ ./apps/lkvm-static run -m 128 -c2 --console serial \
   -p "console=ttyS0 earlycon=uart8250,mmio,0x3f8" -k ./apps/Image \
   -i ./apps/rootfs.img --debug

Anup Patel (13):
  KVM: RISC-V: Add KVM_REG_RISCV for ONE_REG interface
  RISC-V: Add hypervisor extension related CSR defines
  RISC-V: Add initial skeletal KVM support
  RISC-V: KVM: Implement VCPU create, init and destroy functions
  RISC-V: KVM: Implement VCPU interrupts and requests handling
  RISC-V: KVM: Implement KVM_GET_ONE_REG/KVM_SET_ONE_REG ioctls
  RISC-V: KVM: Implement VCPU world-switch
  RISC-V: KVM: Handle MMIO exits for VCPU
  RISC-V: KVM: Handle WFI exits for VCPU
  RISC-V: KVM: Implement VMID allocator
  RISC-V: KVM: Implement stage2 page table programming
  RISC-V: KVM: Implement MMU notifiers
  RISC-V: Enable VIRTIO drivers in RV64 and RV32 defconfig

Atish Patra (3):
  RISC-V: KVM: Add timer functionality
  RISC-V: KVM: FP lazy save/restore
  RISC-V: KVM: Add SBI v0.1 support

 arch/riscv/Kconfig                      |   2 +
 arch/riscv/Makefile                     |   2 +
 arch/riscv/configs/defconfig            |  23 +-
 arch/riscv/configs/rv32_defconfig       |  13 +
 arch/riscv/include/asm/csr.h            |  58 ++
 arch/riscv/include/asm/kvm_host.h       | 232 ++++++
 arch/riscv/include/asm/kvm_vcpu_timer.h |  32 +
 arch/riscv/include/asm/pgtable-bits.h   |   1 +
 arch/riscv/include/uapi/asm/kvm.h       |  74 ++
 arch/riscv/kernel/asm-offsets.c         | 148 ++++
 arch/riscv/kvm/Kconfig                  |  34 +
 arch/riscv/kvm/Makefile                 |  14 +
 arch/riscv/kvm/main.c                   |  64 ++
 arch/riscv/kvm/mmu.c                    | 904 ++++++++++++++++++++++++
 arch/riscv/kvm/tlb.S                    |  42 ++
 arch/riscv/kvm/vcpu.c                   | 817 +++++++++++++++++++++
 arch/riscv/kvm/vcpu_exit.c              | 553 +++++++++++++++
 arch/riscv/kvm/vcpu_sbi.c               | 118 ++++
 arch/riscv/kvm/vcpu_switch.S            | 367 ++++++++++
 arch/riscv/kvm/vcpu_timer.c             | 106 +++
 arch/riscv/kvm/vm.c                     | 107 +++
 arch/riscv/kvm/vmid.c                   | 130 ++++
 drivers/clocksource/timer-riscv.c       |   6 +
 include/clocksource/timer-riscv.h       |  14 +
 include/uapi/linux/kvm.h                |   1 +
 25 files changed, 3857 insertions(+), 5 deletions(-)
 create mode 100644 arch/riscv/include/asm/kvm_host.h
 create mode 100644 arch/riscv/include/asm/kvm_vcpu_timer.h
 create mode 100644 arch/riscv/include/uapi/asm/kvm.h
 create mode 100644 arch/riscv/kvm/Kconfig
 create mode 100644 arch/riscv/kvm/Makefile
 create mode 100644 arch/riscv/kvm/main.c
 create mode 100644 arch/riscv/kvm/mmu.c
 create mode 100644 arch/riscv/kvm/tlb.S
 create mode 100644 arch/riscv/kvm/vcpu.c
 create mode 100644 arch/riscv/kvm/vcpu_exit.c
 create mode 100644 arch/riscv/kvm/vcpu_sbi.c
 create mode 100644 arch/riscv/kvm/vcpu_switch.S
 create mode 100644 arch/riscv/kvm/vcpu_timer.c
 create mode 100644 arch/riscv/kvm/vm.c
 create mode 100644 arch/riscv/kvm/vmid.c
 create mode 100644 include/clocksource/timer-riscv.h
---
2.17.1
```
