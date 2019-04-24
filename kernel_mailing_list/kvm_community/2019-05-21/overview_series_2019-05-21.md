#### [PATCH 1/3] Build target for emulate.o as a userspace binary
##### From: Sam Caccavale <samcacc@amazon.de>

```c
This commit contains the minimal set of functionality to build
afl-harness around arch/x86/emulate.c which allows exercising code
in that source file, like x86_emulate_insn.  Resolving the
dependencies was done via GCC's -H flag by get_headers.py.
---
 tools/Makefile                                |   9 ++
 .../fuzz/x86_instruction_emulation/.gitignore |   2 +
 tools/fuzz/x86_instruction_emulation/Makefile |  57 +++++++
 .../fuzz/x86_instruction_emulation/README.md  |  12 ++
 .../x86_instruction_emulation/afl-harness.c   | 149 ++++++++++++++++++
 tools/fuzz/x86_instruction_emulation/common.h |  87 ++++++++++
 .../x86_instruction_emulation/emulator_ops.c  |  58 +++++++
 .../x86_instruction_emulation/emulator_ops.h  | 117 ++++++++++++++
 .../scripts/get_headers.py                    |  95 +++++++++++
 .../scripts/make_deps                         |   4 +
 tools/fuzz/x86_instruction_emulation/stubs.c  |  56 +++++++
 tools/fuzz/x86_instruction_emulation/stubs.h  |  52 ++++++
 12 files changed, 698 insertions(+)
 create mode 100644 tools/fuzz/x86_instruction_emulation/.gitignore
 create mode 100644 tools/fuzz/x86_instruction_emulation/Makefile
 create mode 100644 tools/fuzz/x86_instruction_emulation/README.md
 create mode 100644 tools/fuzz/x86_instruction_emulation/afl-harness.c
 create mode 100644 tools/fuzz/x86_instruction_emulation/common.h
 create mode 100644 tools/fuzz/x86_instruction_emulation/emulator_ops.c
 create mode 100644 tools/fuzz/x86_instruction_emulation/emulator_ops.h
 create mode 100644 tools/fuzz/x86_instruction_emulation/scripts/get_headers.py
 create mode 100755 tools/fuzz/x86_instruction_emulation/scripts/make_deps
 create mode 100644 tools/fuzz/x86_instruction_emulation/stubs.c
 create mode 100644 tools/fuzz/x86_instruction_emulation/stubs.h

```
#### [PATCH 1/3] KVM: Documentation: Add disable pause exits to KVM_CAP_X86_DISABLE_EXITS
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Commit b31c114b (KVM: X86: Provide a capability to disable PAUSE intercepts)
forgot to add the KVM_X86_DISABLE_EXITS_PAUSE into api doc. This patch adds 
it.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 Documentation/virtual/kvm/api.txt | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH] kvm: change KVM_REQUEST_MASK to reflect vcpu.requests size
##### From: Rik van Riel <riel@surriel.com>

```c
The code using KVM_REQUEST_MASK uses a pattern reminiscent of a bitmask:

	set_bit(req & KVM_REQUEST_MASK, &vcpu->requests);

However, the first argument passed to set_bit, test_bit, and clear_bit
is a bit number, not a bitmask. That means the current definition would
allow users of kvm_make_request to overflow the vcpu.requests bitmask,
and is confusing to developers examining the code.

Redefine KVM_REQUEST_MASK to reflect the number of bits that actually
fit inside an unsigned long, and add a comment explaining set_bit and
friends take bit numbers, not a bitmask.

Signed-off-by: Rik van Riel <riel@surriel.com>
---
 include/linux/kvm_host.h | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: LAPIC: Do not mask the local interrupts when LAPIC is sw disabled
##### From: Luwei Kang <luwei.kang@intel.com>

```c
The current code will mask all the local interrupts in the local
vector table when the LAPIC is disabled by SVR (Spurious-Interrupt
Vector Register) "APIC Software Enable/Disable" flag (bit8).
This may block local interrupt be delivered to target vCPU
even if LAPIC is enabled by set SVR (bit8 == 1) after.

For example, reset vCPU will mask all the local interrupts and
set the SVR to default value FFH (LAPIC is disabled because
SVR[bit8] == 0). Guest may try to enable some local interrupts
(e.g. LVTPC) by clear bit16 of LVT entry before enable LAPIC.
But bit16 can't be cleared when LAPIC is "software disabled"
and this local interrupt still disabled after LAPIC "software
enabled".

This patch will not mask the local interrupts when LAPIC
is "software disabled" and add LAPIC "software enabled" checking
before deliver local interrupt.

Signed-off-by: Luwei Kang <luwei.kang@intel.com>
---
 arch/x86/kvm/lapic.c | 19 ++-----------------
 1 file changed, 2 insertions(+), 17 deletions(-)

```
#### [PATCH] kvm: support guest access CORE cstate
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Allow guest reads CORE cstate when exposing host CPU power management capabilities 
to the guest. PKG cstate is restricted to avoid a guest to get the whole package 
information in multi-tenant scenario.

Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 linux-headers/linux/kvm.h | 4 +++-
 target/i386/kvm.c         | 3 ++-
 2 files changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH] kvm: tests: Sort tests in the Makefile alphabeticallyFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 tools/testing/selftests/kvm/Makefile | 20 ++++++++++----------
 1 file changed, 10 insertions(+), 10 deletions(-)

```
#### [PATCH] MAINTAINERS: KVM: arm/arm64: Remove myself as maintainer
##### From: Christoffer Dall <christoffer.dall@arm.com>

```c
I no longer have time to actively review patches and manage the tree and
it's time to make that official.

Huge thanks to the incredible Linux community and all the contributors
who have put up with me over the past years.

I also take this opportunity to remove the website link to the Columbia
web page, as that information is no longer up to date and I don't know
who manages that anymore.

Signed-off-by: Christoffer Dall <christoffer.dall@arm.com>
---
 MAINTAINERS | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH v9 1/4] s390: ap: kvm: add PQAP interception for AQIC
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
We prepare the interception of the PQAP/AQIC instruction for
the case the AQIC facility is enabled in the guest.

First of all we do not want to change existing behavior when
intercepting AP instructions without the SIE allowing the guest
to use AP instructions.

In this patch we only handle the AQIC interception allowed by
facility 65 which will be enabled when the complete interception
infrastructure will be present.

We add a callback inside the KVM arch structure for s390 for
a VFIO driver to handle a specific response to the PQAP
instruction with the AQIC command and only this command.

But we want to be able to return a correct answer to the guest
even there is no VFIO AP driver in the kernel.
Therefor, we inject the correct exceptions from inside KVM for the
case the callback is not initialized, which happens when the vfio_ap
driver is not loaded.

We do consider the responsability of the driver to always initialize
the PQAP callback if it defines queues by initializing the CRYCB for
a guest.
If the callback has been setup we call it.
If not we setup an answer considering that no queue is available
for the guest when no callback has been setup.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 arch/s390/include/asm/kvm_host.h      |  7 +++
 arch/s390/kvm/priv.c                  | 86 +++++++++++++++++++++++++++++++++++
 drivers/s390/crypto/vfio_ap_private.h |  2 +
 3 files changed, 95 insertions(+)

```
#### [PATCH v10 1/7] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 13 ++++++++-----
 drivers/nvdimm/region_devs.c | 26 ++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  9 ++++++++-
 6 files changed, 47 insertions(+), 12 deletions(-)

```
