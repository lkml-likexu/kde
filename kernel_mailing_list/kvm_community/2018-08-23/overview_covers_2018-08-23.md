

#### [PATCH V3 0/4] introduce coalesced pio support
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c

Coalesced pio is base on coalesced mmio and can be used for some port
like rtc port, pci-host config port, virtio-pci config port and so on.

Specially in case of rtc as coalesced pio, some versions of windows guest 
access rtc frequently because of rtc as system tick. guest access rtc like 
this: write register index to 0x70, then write or read data from 0x71. 
writing 0x70 port is just as index and do nothing else. So we can use 
coalesced pio to handle this scene to reduce VM-EXIT time.

without my patch, get the vm-exit time of accessing rtc 0x70 and piix 0xcf8
using perf tools: (guest OS : windows 7 64bit)
IO Port Access  Samples Samples%  Time%  Min Time  Max Time  Avg time
0x70:POUT        86     30.99%    74.59%   9us      29us    10.75us (+- 3.41%)
0xcf8:POUT     1119     2.60%     2.12%   2.79us    56.83us 3.41us (+- 2.23%)

with my patch
IO Port Access  Samples Samples%  Time%   Min Time  Max Time   Avg time
 0x70:POUT       106    32.02%    29.47%    0us      10us     1.57us (+- 7.38%)
0xcf8:POUT      1065    1.67%     0.28%   0.41us    65.44us   0.66us (+- 10.55%)

These are just qemu's patches, another patches are for kernel.
I think there is a need for further consideration in changing coalesecd_mmio's 
naming in kernel and qemu together.So maybe another patch does it.

Peng Hao (4):
  target-i386: introduce coalesced_pio kvm header update
  target-i386: add coalesced_pio API
  target-i386: add rtc 0x70 port as coalesced_pio
  target-i386: add i440fx 0xcf8 port as coalesced_pio

 accel/kvm/kvm-all.c       | 58 ++++++++++++++++++++++++++++++++++++++++++-----
 hw/pci-host/piix.c        |  4 ++++
 hw/timer/mc146818rtc.c    |  8 +++++++
 include/exec/memattrs.h   |  2 +-
 linux-headers/linux/kvm.h |  5 ++--
 5 files changed, 68 insertions(+), 9 deletions(-)
```
#### [PATCH kvm-unit-tests 0/2] arm64: support relocatable compiles
##### From: Andrew Jones <drjones@redhat.com>

```c

There was a request to support relocatable compiles (you know who you
are - and so does anybody who can read CC lists on emails.) I've also
recently had my own motivation (adding support to QEMU for a dynamic
RAM base). Here it is for arm64. I didn't do arm yet because it didn't
appear to be as easy and it's unlikely we'll want to make its RAM
base dynamic in QEMU anyway.

Thanks,
drew

Andrew Jones (2):
  arm/arm64: prepare to compile arm64 tests relocatable
  arm64: compile relocatable

 arm/Makefile.arm    |  6 +++++-
 arm/Makefile.arm64  | 10 ++++++++-
 arm/Makefile.common | 19 ++++++-----------
 arm/cstart64.S      | 52 ++++++++++++++++++++++++++++++++++-----------
 arm/flat.lds        | 42 ++++++++++++++++++++++++------------
 5 files changed, 90 insertions(+), 39 deletions(-)
```
#### [PATCH v3 0/3] KVM: s390: vsie: Consolidate CRYCB validation
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c

Before adapting the CRYCB shadowing for a guest supporting
the AP instructions we want to clean the CRYCB shadowing code.

First patch seem obvious.

Second patch introduce a change in the behavior of
the virtual machine in that the CRYCB is validated
whenever we use or not the key masks to mimic the
real machine.

Patch 3 does not correct the compiled code but make
more clear what is done concerning the formating of
the CRYCB in the guest original CRYCB and in the
shadow CRYCB.

Pierre Morel (3):
  KVM: s390: vsie: copy wrapping keys to right place
  KVM: s390: vsie: Do the CRYCB validation first
  KVM: s390: vsie: Make use of CRYCB FORMAT2 clear

 arch/s390/kvm/vsie.c | 20 +++++++++++---------
 1 file changed, 11 insertions(+), 9 deletions(-)
```
#### [PATCH v2 0/8] KVM: x86: Fix the emulation type mess
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

v1 of this series was a simple (on the surface) bug fix for an issue
where a nested guest would get stuck in an infinite loop due to L0
restarting the guest over and over after an emulation failure because
L0 incorrectly thought the emulation failure was due to a page fault
in the guest's domain.

While not wrong, v1 was essentially using duct tape to prop up the
house of cards that is emulation type.  v2 demolishes the house and
builds a nice little fortress in its place.

v2:
  - Fix known issues of EMULTYPE_NO_REEXECUTE not being passed
  - Invert re-execute flag and merge it with EMULTYPE_RETRY
  - Fix the original bug by not retrying nested guests' instructions
  - Unexport x86_emulate_instruction() to reduce the probability of
    introducing similar bugs in the future

Sean Christopherson (8):
  KVM: VMX: Do not allow reexecute_instruction() when skipping MMIO
    instr
  KVM: x86: SVM: Set EMULTYPE_NO_REEXECUTE for RSM emulation
  KVM: x86: Invert emulation re-execute behavior to make it opt-in
  KVM: x86: Merge EMULTYPE_RETRY and EMULTYPE_ALLOW_REEXECUTE
  KVM: x86: Default to not allowing emulation retry in
    kvm_mmu_page_fault
  KVM: x86: Do not re-{try,execute} after failed emulation in L2
  KVM: x86: Rename emulate_instruction() to kvm_emulate_instruction()
  KVM: x86: Unexport x86_emulate_instruction()

 arch/x86/include/asm/kvm_host.h | 19 ++++++-------------
 arch/x86/kvm/mmu.c              | 21 +++++++++++++++------
 arch/x86/kvm/svm.c              | 16 ++++++++--------
 arch/x86/kvm/vmx.c              | 18 +++++++++---------
 arch/x86/kvm/x86.c              | 28 +++++++++++++++++++++++-----
 arch/x86/kvm/x86.h              |  2 ++
 6 files changed, 63 insertions(+), 41 deletions(-)
```
