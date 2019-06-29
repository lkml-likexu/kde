#### [PATCH v4 1/2] Drivers: hv: Create Hyper-V clocksource driver from existing clockevents code
##### From: Michael Kelley <mikelley@microsoft.com>

```c
Hyper-V clock/timer code and data structures are currently mixed
in with other code in the ISA independent drivers/hv directory as
well as the ISA dependent Hyper-V code under arch/x86.  Consolidate
this code and data structures into a Hyper-V clocksource driver to
better follow the Linux model. In doing so, separate out the ISA
dependent portions so the new clocksource driver works for x86 and
for the in-process Hyper-V on ARM64 code.

To start, move the existing clockevents code to create the
new clocksource driver. Update the VMbus driver to call
initialization and cleanup routines since the Hyper-V
synthetic timers are not independently enumerated in ACPI.

No behavior is changed and no new functionality is added.

Suggested-by: Marc Zyngier <marc.zyngier@arm.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Michael Kelley <mikelley@microsoft.com>
---
 MAINTAINERS                        |   2 +
 arch/x86/include/asm/hyperv-tlfs.h |   6 ++
 arch/x86/kernel/cpu/mshyperv.c     |   2 +
 drivers/clocksource/Makefile       |   1 +
 drivers/clocksource/hyperv_timer.c | 191 +++++++++++++++++++++++++++++++++++++
 drivers/hv/Kconfig                 |   3 +
 drivers/hv/hv.c                    | 156 +-----------------------------
 drivers/hv/hyperv_vmbus.h          |   3 -
 drivers/hv/vmbus_drv.c             |  42 ++++----
 include/clocksource/hyperv_timer.h |  27 ++++++
 10 files changed, 258 insertions(+), 175 deletions(-)
 create mode 100644 drivers/clocksource/hyperv_timer.c
 create mode 100644 include/clocksource/hyperv_timer.h

```
#### [PATCH kvmtool] README: Add maintainers section
##### From: Will Deacon <will@kernel.org>

```c
Julien has kindly offered to help maintain kvmtool, but it occurred to
me that we don't actually provide any maintainer contact details in the
repository as it stands.

Add a brief "Maintainers" section to the README, immediately after the
"Contributing" section so that people know who to nag about merging and
reviewing patches.

Cc: Julien Thierry <julien.thierry@arm.com>
Signed-off-by: Will Deacon <will@kernel.org>
Acked-by: Marc Zyngier <marc.zyngier@arm.com>
---
 README | 6 ++++++
 1 file changed, 6 insertions(+)

```
#### [PATCH] kvm-unit-test: x86: Remove duplicate definitions of write_cr4_checking() and put it in library
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
..so that it can be re-used.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 lib/x86/desc.c  | 8 ++++++++
 lib/x86/desc.h  | 1 +
 x86/access.c    | 8 --------
 x86/pcid.c      | 8 --------
 x86/vmx_tests.c | 8 --------
 x86/xsave.c     | 8 --------
 6 files changed, 9 insertions(+), 32 deletions(-)

```
#### [PATCH 1/2] KVM nVMX: Check Host Segment Registers and Descriptor Tables on vmentry of nested guests
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on Host Segment and Descriptor-Table
Registers" in Intel SDM vol 3C, the following checks are performed on
vmentry of nested guests:

   - In the selector field for each of CS, SS, DS, ES, FS, GS and TR, the
     RPL (bits 1:0) and the TI flag (bit 2) must be 0.
   - The selector fields for CS and TR cannot be 0000H.
   - The selector field for SS cannot be 0000H if the "host address-space
     size" VM-exit control is 0.
   - On processors that support Intel 64 architecture, the base-address
     fields for FS, GS and TR must contain canonical addresses.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Karl Heubaum <karl.heubaum@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 26 ++++++++++++++++++++++++--
 1 file changed, 24 insertions(+), 2 deletions(-)

```
#### [PATCH 6/9] docs: virtual: there are two orphan docs there
##### From: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>

```c
Signed-off-by: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>
---
 Documentation/virtual/kvm/amd-memory-encryption.rst | 2 ++
 Documentation/virtual/kvm/vcpu-requests.rst         | 2 ++
 2 files changed, 4 insertions(+)

```
#### [PATCH v3 net-next] net: link_watch: prevent starvation when processing linkwatch wq
##### From: Yunsheng Lin <linyunsheng@huawei.com>

```c
When user has configured a large number of virtual netdev, such
as 4K vlans, the carrier on/off operation of the real netdev
will also cause it's virtual netdev's link state to be processed
in linkwatch. Currently, the processing is done in a work queue,
which may cause rtnl locking starvation problem and worker
starvation problem for other work queue, such as irqfd_inject wq.

This patch releases the cpu when link watch worker has processed
a fixed number of netdev' link watch event, and schedule the
work queue again when there is still link watch event remaining.

Signed-off-by: Yunsheng Lin <linyunsheng@huawei.com>
---
V2: use cond_resched and rtnl_unlock after processing a fixed
    number of events
V3: fall back to v1 and change commit log to reflect that.
---
---
 net/core/link_watch.c | 13 ++++++++++++-
 1 file changed, 12 insertions(+), 1 deletion(-)

```
#### [PATCH v2 1/3] vsock/virtio: use RCU to avoid use-after-free on the_virtio_vsock
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Some callbacks used by the upper layers can run while we are in the
.remove(). A potential use-after-free can happen, because we free
the_virtio_vsock without knowing if the callbacks are over or not.

To solve this issue we move the assignment of the_virtio_vsock at the
end of .probe(), when we finished all the initialization, and at the
beginning of .remove(), before to release resources.
For the same reason, we do the same also for the vdev->priv.

We use RCU to be sure that all callbacks that use the_virtio_vsock
ended before freeing it. This is not required for callbacks that
use vdev->priv, because after the vdev->config->del_vqs() we are sure
that they are ended and will no longer be invoked.

We also take the mutex during the .remove() to avoid that .probe() can
run while we are resetting the device.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 net/vmw_vsock/virtio_transport.c | 67 +++++++++++++++++++++-----------
 1 file changed, 44 insertions(+), 23 deletions(-)

```
#### [PATCH v4 1/5] Build target for emulate.o as a userspace binary
##### From: Sam Caccavale <samcacc@amazon.de>

```c
This commit contains the minimal set of functionality to build
afl-harness around arch/x86/emulate.c which allows exercising code
in that source file, like x86_emulate_insn.
---

v1 -> v2:
 - Moved -O0 to ifdef DEBUG
 - Building with ASAN by default

v2 -> v3:
 - Removed a workaround for printf smashing the stack when compiled
   with -mcmodel=kernel, and stopped compiling with -mcmodel=kernel
 - Added a null check for malloc's return value
 - Moved multiple macros from emulator_ops.c into emulator_ops.h as
   static inline functions.

v3 -> v4:
 - Added unimplemented_op macro to stub out emulator ops
 - envvar FAIL_ON_UNIMPLEMENTED_OP decides whether AFL treats this as
   a crash
 - Updated README to include core dump setup

Signed-off-by: Sam Caccavale <samcacc@amazon.de>
---
 tools/Makefile                  |   9 ++
 tools/fuzz/x86ie/.gitignore     |   2 +
 tools/fuzz/x86ie/Makefile       |  51 +++++++++++
 tools/fuzz/x86ie/README.md      |  21 +++++
 tools/fuzz/x86ie/afl-harness.c  | 151 ++++++++++++++++++++++++++++++++
 tools/fuzz/x86ie/common.h       |  87 ++++++++++++++++++
 tools/fuzz/x86ie/emulator_ops.c |  58 ++++++++++++
 tools/fuzz/x86ie/emulator_ops.h | 134 ++++++++++++++++++++++++++++
 tools/fuzz/x86ie/stubs.c        |  59 +++++++++++++
 tools/fuzz/x86ie/stubs.h        |  52 +++++++++++
 10 files changed, 624 insertions(+)
 create mode 100644 tools/fuzz/x86ie/.gitignore
 create mode 100644 tools/fuzz/x86ie/Makefile
 create mode 100644 tools/fuzz/x86ie/README.md
 create mode 100644 tools/fuzz/x86ie/afl-harness.c
 create mode 100644 tools/fuzz/x86ie/common.h
 create mode 100644 tools/fuzz/x86ie/emulator_ops.c
 create mode 100644 tools/fuzz/x86ie/emulator_ops.h
 create mode 100644 tools/fuzz/x86ie/stubs.c
 create mode 100644 tools/fuzz/x86ie/stubs.h

```
#### [PATCH v2 1/2] x86/KVM/nVMX: don't use clean fields data on enlightened VMLAUNCH
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Apparently, Windows doesn't maintain clean fields data after it does
VMCLEAR for an enlightened VMCS so we can only use it on VMRESUME.
The issue went unnoticed because currently we do nested_release_evmcs()
in handle_vmclear() and the consecutive enlightened VMPTRLD invalidates
clean fields when a new eVMCS is mapped but we're going to change the
logic.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 20 ++++++++++++--------
 1 file changed, 12 insertions(+), 8 deletions(-)

```
