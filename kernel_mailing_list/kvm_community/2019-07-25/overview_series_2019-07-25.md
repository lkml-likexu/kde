#### [PATCH v6 1/8] KVM: VMX: Define CET VMCS fields and control bits
##### From: Yang Weijiang <weijiang.yang@intel.com>

```c
CET(Control-flow Enforcement Technology) is an upcoming Intel(R)
processor feature that blocks Return/Jump-Oriented Programming(ROP)
attacks. It provides the following capabilities to defend
against ROP/JOP style control-flow subversion attacks:

Shadow Stack (SHSTK):
  A second stack for program which is used exclusively for
  control transfer operations.

Indirect Branch Tracking (IBT):
  Code branching protection to defend against jump/call oriented
  programming.

Several new CET MSRs are defined in kernel to support CET:
  MSR_IA32_{U,S}_CET: Controls the CET settings for user
                      mode and suervisor mode respectively.

  MSR_IA32_PL{0,1,2,3}_SSP: Stores shadow stack pointers for
                            CPL-0,1,2,3 level respectively.

  MSR_IA32_INT_SSP_TAB: Stores base address of shadow stack
                        pointer table.

Two XSAVES state bits are introduced for CET:
  IA32_XSS:[bit 11]: For saving/restoring user mode CET states
  IA32_XSS:[bit 12]: For saving/restoring supervisor mode CET states.

Six VMCS fields are introduced for CET:
  {HOST,GUEST}_S_CET: Stores CET settings for supervisor mode.
  {HOST,GUEST}_SSP: Stores shadow stack pointer for supervisor mode.
  {HOST,GUEST}_INTR_SSP_TABLE: Stores base address of shadow stack pointer
                               table.

If VM_EXIT_LOAD_HOST_CET_STATE = 1, the host's CET MSRs are restored
from below VMCS fields at VM-Exit:
  HOST_S_CET
  HOST_SSP
  HOST_INTR_SSP_TABLE

If VM_ENTRY_LOAD_GUEST_CET_STATE = 1, the guest's CET MSRs are loaded
from below VMCS fields at VM-Entry:
  GUEST_S_CET
  GUEST_SSP
  GUEST_INTR_SSP_TABLE

Co-developed-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
Signed-off-by: Zhang Yi Z <yi.z.zhang@linux.intel.com>
Signed-off-by: Yang Weijiang <weijiang.yang@intel.com>
---
 arch/x86/include/asm/vmx.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH v3 01/10] KVM: arm/arm64: vgic: Add LPI translation cache definition
##### From: Marc Zyngier <maz@kernel.org>

```c
From: Marc Zyngier <marc.zyngier@arm.com>

Add the basic data structure that expresses an MSI to LPI
translation as well as the allocation/release hooks.

The size of the cache is arbitrarily defined as 16*nr_vcpus.

Reviewed-by: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Marc Zyngier <marc.zyngier@arm.com>
---
 include/kvm/arm_vgic.h        |  3 +++
 virt/kvm/arm/vgic/vgic-init.c |  5 ++++
 virt/kvm/arm/vgic/vgic-its.c  | 49 +++++++++++++++++++++++++++++++++++
 virt/kvm/arm/vgic/vgic.h      |  2 ++
 4 files changed, 59 insertions(+)

```
#### [PATCH stable-4.19 1/2] KVM: nVMX: do not use dangling shadow VMCS after guest reset
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From: Paolo Bonzini <pbonzini@redhat.com>

[ Upstream commit 88dddc11a8d6b09201b4db9d255b3394d9bc9e57 ]

If a KVM guest is reset while running a nested guest, free_nested will
disable the shadow VMCS execution control in the vmcs01.  However,
on the next KVM_RUN vmx_vcpu_run would nevertheless try to sync
the VMCS12 to the shadow VMCS which has since been freed.

This causes a vmptrld of a NULL pointer on my machime, but Jan reports
the host to hang altogether.  Let's see how much this trivial patch fixes.

Reported-by: Jan Kiszka <jan.kiszka@siemens.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [ v2 1/1] kvm-unit-tests: s390: add cpu model checks
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
This adds a check for documented stfle dependencies.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 s390x/Makefile      |  1 +
 s390x/cpumodel.c    | 58 +++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg |  3 +++
 3 files changed, 62 insertions(+)
 create mode 100644 s390x/cpumodel.c

```
#### [PATCH kvm-unit-tests v3] arm: Add PL031 test
##### From: Alexander Graf <graf@amazon.com>

```c
This patch adds a unit test for the PL031 RTC that is used in the virt machine.
It just pokes basic functionality. I've mostly written it to familiarize myself
with the device, but I suppose having the test around does not hurt, as it also
exercises the GIC SPI interrupt path.

Signed-off-by: Alexander Graf <graf@amazon.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---

v1 -> v2:

  - Use FDT to find base, irq and existence
  - Put isb after timer read
  - Use dist_base for gicv3

v2 -> v3

  - Enable compilation on 32bit ARM target
  - Use ioremap
---
 arm/Makefile.common |   1 +
 arm/pl031.c         | 263 ++++++++++++++++++++++++++++++++++++++++++++
 lib/arm/asm/gic.h   |   1 +
 3 files changed, 265 insertions(+)
 create mode 100644 arm/pl031.c

```
#### [PATCH kvm-unit-tests v4] arm: Add PL031 test
##### From: Alexander Graf <graf@amazon.com>

```c
This patch adds a unit test for the PL031 RTC that is used in the virt machine.
It just pokes basic functionality. I've mostly written it to familiarize myself
with the device, but I suppose having the test around does not hurt, as it also
exercises the GIC SPI interrupt path.

Signed-off-by: Alexander Graf <graf@amazon.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---

v1 -> v2:

  - Use FDT to find base, irq and existence
  - Put isb after timer read
  - Use dist_base for gicv3

v2 -> v3

  - Enable compilation on 32bit ARM target
  - Use ioremap

v3 -> v4:

  - Use dt_pbus_translate_node()
  - Make irq_triggered volatile
---
 arm/Makefile.common |   1 +
 arm/pl031.c         | 260 ++++++++++++++++++++++++++++++++++++++++++++
 lib/arm/asm/gic.h   |   1 +
 3 files changed, 262 insertions(+)
 create mode 100644 arm/pl031.c

```
#### [PATCH kvm-unit-tests v5] arm: Add PL031 test
##### From: Alexander Graf <graf@amazon.com>

```c
This patch adds a unit test for the PL031 RTC that is used in the virt machine.
It just pokes basic functionality. I've mostly written it to familiarize myself
with the device, but I suppose having the test around does not hurt, as it also
exercises the GIC SPI interrupt path.

Signed-off-by: Alexander Graf <graf@amazon.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---

v1 -> v2:

  - Use FDT to find base, irq and existence
  - Put isb after timer read
  - Use dist_base for gicv3

v2 -> v3

  - Enable compilation on 32bit ARM target
  - Use ioremap

v3 -> v4:

  - Use dt_pbus_translate_node()
  - Make irq_triggered volatile

v4 -> v5:

  - Make assert() call stand alone so it can be compiled out
---
 arm/Makefile.common |   1 +
 arm/pl031.c         | 262 ++++++++++++++++++++++++++++++++++++++++++++
 lib/arm/asm/gic.h   |   1 +
 3 files changed, 264 insertions(+)
 create mode 100644 arm/pl031.c

```
#### [PATCH stable-5.1 1/3] KVM: nVMX: do not use dangling shadow VMCS after guest reset
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From: Paolo Bonzini <pbonzini@redhat.com>

[ Upstream commit 88dddc11a8d6b09201b4db9d255b3394d9bc9e57 ]

If a KVM guest is reset while running a nested guest, free_nested will
disable the shadow VMCS execution control in the vmcs01.  However,
on the next KVM_RUN vmx_vcpu_run would nevertheless try to sync
the VMCS12 to the shadow VMCS which has since been freed.

This causes a vmptrld of a NULL pointer on my machime, but Jan reports
the host to hang altogether.  Let's see how much this trivial patch fixes.

Reported-by: Jan Kiszka <jan.kiszka@siemens.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH stable-5.2 1/3] KVM: nVMX: do not use dangling shadow VMCS after guest reset
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From: Paolo Bonzini <pbonzini@redhat.com>

[ Upstream commit 88dddc11a8d6b09201b4db9d255b3394d9bc9e57 ]

If a KVM guest is reset while running a nested guest, free_nested will
disable the shadow VMCS execution control in the vmcs01.  However,
on the next KVM_RUN vmx_vcpu_run would nevertheless try to sync
the VMCS12 to the shadow VMCS which has since been freed.

This causes a vmptrld of a NULL pointer on my machime, but Jan reports
the host to hang altogether.  Let's see how much this trivial patch fixes.

Reported-by: Jan Kiszka <jan.kiszka@siemens.com>
Cc: Liran Alon <liran.alon@oracle.com>
Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [PULL 1/4] migration: fix migrate_cancel leads live_migration thread endless loop
##### From: Juan Quintela <quintela@redhat.com>

```c
From: Ivan Ren <renyime@gmail.com>

When we 'migrate_cancel' a multifd migration, live_migration thread may
go into endless loop in multifd_send_pages functions.

Reproduce steps:

(qemu) migrate_set_capability multifd on
(qemu) migrate -d url
(qemu) [wait a while]
(qemu) migrate_cancel

Then may get live_migration 100% cpu usage in following stack:

pthread_mutex_lock
qemu_mutex_lock_impl
multifd_send_pages
multifd_queue_page
ram_save_multifd_page
ram_save_target_page
ram_save_host_page
ram_find_and_save_block
ram_find_and_save_block
ram_save_iterate
qemu_savevm_state_iterate
migration_iteration_run
migration_thread
qemu_thread_start
start_thread
clone

Signed-off-by: Ivan Ren <ivanren@tencent.com>
Message-Id: <1561468699-9819-2-git-send-email-ivanren@tencent.com>
Reviewed-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Reviewed-by: Juan Quintela <quintela@redhat.com>
Signed-off-by: Juan Quintela <quintela@redhat.com>
---
 migration/ram.c | 36 +++++++++++++++++++++++++++++-------
 1 file changed, 29 insertions(+), 7 deletions(-)

```
