

#### [PATCH v4 0/5] x86 instruction emulator fuzzing
##### From: Sam Caccavale <samcacc@amazon.de>

```c

Dear all,

This series aims to provide an entrypoint for, and fuzz KVM's x86 instruction
emulator from userspace.  It mirrors Xen's application of the AFL fuzzer to
it's instruction emulator in the hopes of discovering vulnerabilities.
Since this entrypoint also allows arbitrary execution of the emulators code
from userspace, it may also be useful for testing.

The current 4 patches build the emulator and 2 harnesses: simple-harness is
an example of unit testing; afl-harness is a frontend for the AFL fuzzer.
The fifth patch contains useful scripts for development but is not intended
for usptream consumption.

Patches
=======

- 01: Builds and links afl-harness with the required kernel objects.
- 02: Introduces the minimal set of emulator operations and supporting code
to emulate simple instructions.
- 03: Demonstrates simple-harness as a unit test.
- 04: Adds scripts for install and building.
- 05: Useful scripts for development


Issues
=======

Currently, fuzzing results in a large amount of FPU related crashes.  Xen's
fuzzing efforts had this issue too.  Their (temporary?) solution was to
disable FPU exceptions after every instruction iteration?  Some solution
is desired for this project.


Changelog
=======

v1 -> v2:
 - Moved -O0 to ifdef DEBUG
 - Building with ASAN by default
 - Removed a number of macros from emulator_ops.c and moved them as
   static inline functions in emulator_ops.h
 - Accidentally changed the example in simple-harness (reverted in v3)
 - Introduced patch 4 for scripts

v2 -> v3:
 - Removed a workaround for printf smashing the stack when compiled
   with -mcmodel=kernel, and stopped compiling with -mcmodel=kernel
 - Added a null check for malloc's return value
 - Moved more macros from emulator_ops.c into emulator_ops.h as
   static inline functions
 - Removed commented out code
 - Moved changes to emulator_ops.h into the first patch
 - Moved addition of afl-many script to the script patch
 - Fixed spelling mistakes in documentation
 - Reverted the simple-harness example back to the more useful original one
 - Moved non-essential development scripts from patch 4 to new patch 5

v3 -> v4:
 - Stubbed out all unimplemented emulator_ops with a unimplemented_op macro
 - Setting FAIL_ON_UNIMPLEMENTED_OP on compile decides whether calling these
   is treated as a crash or ignored
 - Moved setting up core dumps out of the default build/install path and
   detailed this change in the README
 - Added a .sh extention to afl-many
 - Added an optional timeout to afl-many.sh and made deploy_remote.sh use it
 - Building no longer creates a new .config each time and does not force any
   config options
 - Fixed a path bug in afl-many.sh

Any comments/suggestions are greatly appreciated.

Best,
Sam Caccavale

Sam Caccavale (5):
  Build target for emulate.o as a userspace binary
  Emulate simple x86 instructions in userspace
  Demonstrating unit testing via simple-harness
  Added build and install scripts
  Development scripts for crash triage and deploy

 tools/Makefile                                |   9 +
 tools/fuzz/x86ie/.gitignore                   |   2 +
 tools/fuzz/x86ie/Makefile                     |  54 ++
 tools/fuzz/x86ie/README.md                    |  21 +
 tools/fuzz/x86ie/afl-harness.c                | 151 +++++
 tools/fuzz/x86ie/common.h                     |  87 +++
 tools/fuzz/x86ie/emulator_ops.c               | 590 ++++++++++++++++++
 tools/fuzz/x86ie/emulator_ops.h               | 134 ++++
 tools/fuzz/x86ie/scripts/afl-many.sh          |  31 +
 tools/fuzz/x86ie/scripts/bin.sh               |  49 ++
 tools/fuzz/x86ie/scripts/build.sh             |  34 +
 tools/fuzz/x86ie/scripts/coalesce.sh          |   5 +
 tools/fuzz/x86ie/scripts/deploy.sh            |   9 +
 tools/fuzz/x86ie/scripts/deploy_remote.sh     |  10 +
 tools/fuzz/x86ie/scripts/gen_output.sh        |  11 +
 tools/fuzz/x86ie/scripts/install_afl.sh       |  15 +
 .../fuzz/x86ie/scripts/install_deps_ubuntu.sh |   5 +
 tools/fuzz/x86ie/scripts/rebuild.sh           |   6 +
 tools/fuzz/x86ie/scripts/run.sh               |  10 +
 tools/fuzz/x86ie/scripts/summarize.sh         |   9 +
 tools/fuzz/x86ie/simple-harness.c             |  49 ++
 tools/fuzz/x86ie/stubs.c                      |  59 ++
 tools/fuzz/x86ie/stubs.h                      |  52 ++
 23 files changed, 1402 insertions(+)
 create mode 100644 tools/fuzz/x86ie/.gitignore
 create mode 100644 tools/fuzz/x86ie/Makefile
 create mode 100644 tools/fuzz/x86ie/README.md
 create mode 100644 tools/fuzz/x86ie/afl-harness.c
 create mode 100644 tools/fuzz/x86ie/common.h
 create mode 100644 tools/fuzz/x86ie/emulator_ops.c
 create mode 100644 tools/fuzz/x86ie/emulator_ops.h
 create mode 100755 tools/fuzz/x86ie/scripts/afl-many.sh
 create mode 100755 tools/fuzz/x86ie/scripts/bin.sh
 create mode 100755 tools/fuzz/x86ie/scripts/build.sh
 create mode 100755 tools/fuzz/x86ie/scripts/coalesce.sh
 create mode 100644 tools/fuzz/x86ie/scripts/deploy.sh
 create mode 100755 tools/fuzz/x86ie/scripts/deploy_remote.sh
 create mode 100755 tools/fuzz/x86ie/scripts/gen_output.sh
 create mode 100755 tools/fuzz/x86ie/scripts/install_afl.sh
 create mode 100755 tools/fuzz/x86ie/scripts/install_deps_ubuntu.sh
 create mode 100755 tools/fuzz/x86ie/scripts/rebuild.sh
 create mode 100755 tools/fuzz/x86ie/scripts/run.sh
 create mode 100755 tools/fuzz/x86ie/scripts/summarize.sh
 create mode 100644 tools/fuzz/x86ie/simple-harness.c
 create mode 100644 tools/fuzz/x86ie/stubs.c
 create mode 100644 tools/fuzz/x86ie/stubs.h
---
2.17.1




Amazon Development Center Germany GmbH
Krausenstr. 38
10117 Berlin
Geschaeftsfuehrung: Christian Schlaeger, Ralf Herbrich
Eingetragen am Amtsgericht Charlottenburg unter HRB 149173 B
Sitz: Berlin
Ust-ID: DE 289 237 879
```
#### [PATCH v2 0/2] x86/kvm/nVMX: fix Enlightened VMCLEAR
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c

VMCLEAR implementation for Enlightened VMCS is not entirely correct
when something else than the currently active eVMCS on the calling vCPU
is targeted. In case there's no currently active eVMCS on the calling vCPU
we are corrupting the targeted area by writing to the non-existent
launch_state field.

Fix the logic by always treating the targeted area as 'enlightened' in case
Enlightened VMEntry is enabled on the calling vCPU.

Changes since v1:
- 'evmcs_vmptr' -> 'evmcs_gpa' [Paolo Bonzini]
- avoid nested_release_evmcs() in handle_vmclear even for the currently
  active eVMCS on the calling vCPU [Liran Alon], PATCH1 added to support
  the change.

Vitaly Kuznetsov (2):
  x86/KVM/nVMX: don't use clean fields data on enlightened VMLAUNCH
  x86/kvm/nVMX: fix VMCLEAR when Enlightened VMCS is in use

 arch/x86/kvm/vmx/evmcs.c  | 18 ++++++++++++++
 arch/x86/kvm/vmx/evmcs.h  |  1 +
 arch/x86/kvm/vmx/nested.c | 52 ++++++++++++++++++++++-----------------
 3 files changed, 49 insertions(+), 22 deletions(-)
```
#### [PATCH 0/9] Some doc fixes
##### From: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>

```c

This patch series is against linux-next (next-20190627). I doubt those
would apply cleanly against docs next tree.

So, please apply it via the subsystem trees. Otherwise, they could
be pushed by the end of the merge window or for -rc1 via a docs tree.

Most, if not all were I already sent.


Mauro Carvalho Chehab (9):
  hrtimer: Use a bullet for the returns bullet list
  docs: trace: fix a broken label
  docs: signal: fix a kernel-doc markup
  dt: leds-lm36274.txt: fix a broken reference to ti-lmu.txt
  docs: fix some broken references due to txt->rst renames
  docs: virtual: there are two orphan docs there
  docs: gpu: add msm-crash-dump.rst to the index.rst file
  drm: fix a reference for a renamed file: fb/modedb.rst
  platform: x86: get rid of a non-existent document

 Documentation/devicetree/bindings/arm/idle-states.txt   | 2 +-
 Documentation/devicetree/bindings/leds/leds-lm36274.txt | 2 +-
 Documentation/gpu/drivers.rst                           | 1 +
 Documentation/gpu/msm-crash-dump.rst                    | 2 --
 Documentation/trace/kprobetrace.rst                     | 1 +
 Documentation/virtual/kvm/amd-memory-encryption.rst     | 2 ++
 Documentation/virtual/kvm/vcpu-requests.rst             | 2 ++
 drivers/gpu/drm/drm_modes.c                             | 2 +-
 drivers/gpu/drm/i915/intel_runtime_pm.h                 | 2 +-
 drivers/i2c/busses/i2c-nvidia-gpu.c                     | 2 +-
 drivers/platform/x86/Kconfig                            | 3 ---
 kernel/signal.c                                         | 2 +-
 kernel/time/hrtimer.c                                   | 7 ++++---
 13 files changed, 16 insertions(+), 14 deletions(-)
```
#### [PATCH v2 0/3] vsock/virtio: several fixes in the .probe() and
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c

During the review of "[PATCH] vsock/virtio: Initialize core virtio vsock
before registering the driver", Stefan pointed out some possible issues
in the .probe() and .remove() callbacks of the virtio-vsock driver.

This series tries to solve these issues:
- Patch 1 adds RCU critical sections to avoid use-after-free of
  'the_virtio_vsock' pointer.
- Patch 2 stops workers before to call vdev->config->reset(vdev) to
  be sure that no one is accessing the device.
- Patch 3 moves the works flush at the end of the .remove() to avoid
  use-after-free of 'vsock' object.

v2:
- Patch 1: use RCU to protect 'the_virtio_vsock' pointer
- Patch 2: no changes
- Patch 3: flush works only at the end of .remove()
- Removed patch 4 because virtqueue_detach_unused_buf() returns all the buffers
  allocated.

v1: https://patchwork.kernel.org/cover/10964733/

Stefano Garzarella (3):
  vsock/virtio: use RCU to avoid use-after-free on the_virtio_vsock
  vsock/virtio: stop workers during the .remove()
  vsock/virtio: fix flush of works during the .remove()

 net/vmw_vsock/virtio_transport.c | 131 ++++++++++++++++++++++++-------
 1 file changed, 102 insertions(+), 29 deletions(-)
```
#### [PATCH v4 0/2] Drivers: hv: Move Hyper-V clock/timer code to separate
##### From: Michael Kelley <mikelley@microsoft.com>

```c

This patch series moves Hyper-V clock/timer code to a separate Hyper-V
clocksource driver. Previously, Hyper-V clock/timer code and data
structures were mixed in with other Hyper-V code in the ISA independent
drivers/hv code as well as in ISA dependent code. The new Hyper-V
clocksource driver is ISA independent, with a just few dependencies on
ISA specific functions. The patch series does not change any behavior
or functionality -- it only reorganizes the existing code and fixes up
the linkages. A few places outside of Hyper-V code are fixed up to use
the new #include file structure.

This restructuring is in response to Marc Zyngier's review comments
on supporting Hyper-V running on ARM64, and is a good idea in general.
It increases the amount of code shared between the x86 and ARM64
architectures, and reduces the size of the new code for supporting
Hyper-V on ARM64. A new version of the Hyper-V on ARM64 patches will
follow once this clocksource restructuring is accepted.

The code is diff'ed against the upstream tip tree:
git://git.kernel.org/pub/scm/linux/kernel/git/tip/tip.git timers/vdso

Changes in v4:
* Revised commit messages
* Rebased to upstream tip tree

Changes in v3:
* Removed boolean argument to hv_init_clocksource(). Always call
sched_clock_register, which is needed on ARM64 but a no-op on x86.
* Removed separate cpuhp setup in hv_stimer_alloc() and instead
directly call hv_stimer_init() and hv_stimer_cleanup() from
corresponding VMbus functions.  This more closely matches original
code and avoids clocksource stop/restart problems on ARM64 when
VMbus code denies CPU offlining request.

Changes in v2:
* Revised commit short descriptions so the distinction between
the first and second patches is clearer [GregKH]
* Renamed new clocksource driver files and functions to use
existing "timer" and "stimer" names instead of introducing
"syntimer". [Vitaly Kuznetsov]
* Introduced CONFIG_HYPER_TIMER to fix build problem when
CONFIG_HYPERV=m [Vitaly Kuznetsov]
* Added "Suggested-by: Marc Zyngier"

Michael Kelley (2):
  Drivers: hv: Create Hyper-V clocksource driver from existing
    clockevents code
  Drivers: hv: Move Hyper-V clocksource code to new clocksource driver

 MAINTAINERS                              |   2 +
 arch/x86/entry/vdso/vma.c                |   2 +-
 arch/x86/hyperv/hv_init.c                |  91 +--------
 arch/x86/include/asm/hyperv-tlfs.h       |   6 +
 arch/x86/include/asm/mshyperv.h          |  81 ++------
 arch/x86/include/asm/vdso/gettimeofday.h |   2 +-
 arch/x86/kernel/cpu/mshyperv.c           |   2 +
 arch/x86/kvm/x86.c                       |   1 +
 drivers/clocksource/Makefile             |   1 +
 drivers/clocksource/hyperv_timer.c       | 321 +++++++++++++++++++++++++++++++
 drivers/hv/Kconfig                       |   3 +
 drivers/hv/hv.c                          | 156 +--------------
 drivers/hv/hyperv_vmbus.h                |   3 -
 drivers/hv/vmbus_drv.c                   |  42 ++--
 include/clocksource/hyperv_timer.h       | 105 ++++++++++
 15 files changed, 483 insertions(+), 335 deletions(-)
 create mode 100644 drivers/clocksource/hyperv_timer.c
 create mode 100644 include/clocksource/hyperv_timer.h
```
#### [PATCH 0/2] nVMX: Check Host Segment Registers and Descriptor Tables
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c

Patch# 1 implements the following checks, from Intel SDM vol 3C, on
vmentry of nested guests:

   - In the selector field for each of CS, SS, DS, ES, FS, GS and TR, the
     RPL (bits 1:0) and the TI flag (bit 2) must be 0.
   - The selector fields for CS and TR cannot be 0000H.
   - The selector field for SS cannot be 0000H if the "host address-space
     size" VM-exit control is 0.
   - On processors that support Intel 64 architecture, the base-address
     fields for FS, GS and TR must contain canonical addresses.

Patch# 2 adds kvm-unit-tests for the above checks.


[PATCH 1/2] KVM nVMX: Check Host Segment Registers and Descriptor Tables on
[PATCH 2/2] kvm-unit-test nVMX: Test Host Segment Registers and Descriptor Tables on

 arch/x86/kvm/vmx/nested.c | 26 ++++++++++++++++++++++++--
 1 file changed, 24 insertions(+), 2 deletions(-)

Krish Sadhukhan (1):
      nVMX: Check Host Segment Registers and Descriptor Tables on vmentry of nested guests

 x86/vmx_tests.c     | 159 +++++++++++++++++++++++++++++++++++++++++++++++++++
 2 files changed, 164 insertions(+)

Krish Sadhukhan (1):
      nVMX: Test Host Segment Registers and Descriptor Tables on vmentry of nested guests
```
