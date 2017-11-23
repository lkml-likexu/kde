

#### [PATCH 0/3] x86/kvm/hyper-v: Implement Direct Mode for synthetic
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

Turns out Hyper-V on KVM (as of 2016) will only use synthetic timers
if direct mode is available. With direct mode we notify the guest by
asserting APIC irq instead of sending a SynIC message.

The series was tested with Hyper-V on KVM as well as kvm-unit-tests.
I'm including Qemu a kvm-unit-tests patches for testing purposes.

Vitaly Kuznetsov (3):
  x86/hyper-v: move synic/stimer control structures definitions to
    hyperv-tlfs.h
  x86/kvm/hyper-v: use stimer config definition from hyperv-tlfs.h
  x86/kvm/hyper-v: direct mode for synthetic timers

 arch/x86/include/asm/hyperv-tlfs.h |  73 +++++++++++++++++++--
 arch/x86/include/asm/kvm_host.h    |   2 +-
 arch/x86/kvm/hyperv.c              | 100 ++++++++++++++++++++++-------
 arch/x86/kvm/trace.h               |  10 +--
 arch/x86/kvm/x86.c                 |   1 +
 drivers/hv/hv.c                    |   2 +-
 drivers/hv/hyperv_vmbus.h          |  68 --------------------
 include/uapi/linux/kvm.h           |   1 +
 8 files changed, 155 insertions(+), 102 deletions(-)
```
