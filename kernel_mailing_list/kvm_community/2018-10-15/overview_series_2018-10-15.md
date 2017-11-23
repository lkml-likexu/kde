#### Avoid unneccessary %dr6 accesses in nested VM setups
##### From: Christian Ehrhardt <lk@c--e.de>

```c
Hi,

while debugging a nested VM setup where Linux runs as an L1
guest, I found lots of VM exits due to %dr6 writes. However,
neither L0 nor L1 or L2 where using debug registers.

The behaviour was introdued with change efdab992 and the
original author suggested the patch below.

BTW: I'm not related to the other guy with the same name.

     regards    Christian


From e18794eaa15a6bd8829a86a806bc8acb964eefb9 Mon Sep 17 00:00:00 2001
From: Christian Ehrhardt <lk@--e.de>
Date: Mon, 15 Oct 2018 20:05:48 +0200
Subject: [PATCH 1/2] KVM: x86: Only clear %dr6 if really neccessary

Change efdab992: "KVM: x86: fix escape of guest dr6 to the host"
has negative effects if Linux runs as the L1 guest in a nested
VM setup:

Each call to kvm_arch_vcpu_put causes an additional L1->L0 exit due
to the %dr6 write even if neither L1 nor L2 uses debug registers.
As the current hardware value of %dr6 is already in vcpu->arch.dr6
we can avoid the debug register write if the value is already zero.

Update the comment and reformat it while there.

Signed-off-by: Christian Ehrhardt <lk@c--e.de>
---
 arch/x86/kvm/x86.c | 10 ++++++----
 1 file changed, 6 insertions(+), 4 deletions(-)

```
#### Fix bug when shadowing EPT page tables
##### From: Christian Ehrhardt <lk@c--e.de>

```c
Hi,

on x86 shadow paging uses is_pae() to determine if the page
table that is shadowed contains 4-byte or 8-byte PTE entries.
However, when shadowing EPT tables setup by an L1 guest for a
nested L2 guest, this may be wrong as EPT page tables always use
8-byte PTEs regardless of the value of %cr4.PAE.

Similar logic applies to the cr4_pae field of a shadow page's
page role. Arguably the flag should be set when shadowing an EPT
page table. However, currently this is not the case.

As a result all 8-byte PTE writes to write tracked pages are
treated as unaligned accesses to a page with 4-byte PTEs
(detect_write_misaligned wrongly returns true). For non-PAE
L2 guests I thing we might zap the wrong PTEs.

The patch below fixes this for the VMX case with the following
approach:
- Always set cr4_pae in the base_role when shadwoing EPT tables.
- Replace calls to is_pae() with base_role.cr4_pae.
Someone who properly understands the SVM case whould probably have
a look at this and determine if something similar is required.

    regards    Christian


From 7e1b585e80c93ecf890c173bef43a4015af40630 Mon Sep 17 00:00:00 2001
From: Christian Ehrhardt <lk@--e.de>
Date: Mon, 15 Oct 2018 20:06:04 +0200
Subject: [PATCH 2/2] KVM/MMU: Always set cr4_pae when shadowing EPT pages

When shadowing EPT pages setup by L1 for a nested L2 guest
the value of the PAE bit %cr4 is irrelevant. However, in the
page role of a shadow page, cr4_pae basically means that the
shadowed page uses 64-bit page table entries. When shadowing
EPT page tables this is always the case. Thus set cr4_pae in
this case.

Similarly, calls to is_pae(vcpu) do not return useful information
when shadowing EPT tables. With the change above we can check
the cr4_pae bit in the current MMU's base_role instead. In most
cases this is the same as is_pae() anyway. However, when shadowing
EPT tables using is_pae() is wrong.

Signed-off-by: Christian Ehrhardt <lk@c--e.de>
---
 arch/x86/kvm/mmu.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH] x86: svm: Fix incorrect ordering within struct regs
##### From: "Tambe, William" <William.Tambe@amd.com>

```c
"struct regs" is used within x86/svm.c to describe
the memory region where SAVE_GPR_C saves registers.

The ordering within "struct regs" must be corrected
so that it matches how SAVE_GPR_C stores registers.

Signed-off-by: William Tambe <william.tambe@amd.com>
---
 x86/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] s390/cio: make vfio_ccw_io_region staticUser-Agent: Alpine 2.21 (LFD 202 2017-01-01)
##### From: Sebastian Ott <sebott@linux.ibm.com>

```c
Fix the following sparse warning:
drivers/s390/cio/vfio_ccw_drv.c:25:19: warning: symbol 'vfio_ccw_io_region'
was not declared. Should it be static?

Signed-off-by: Sebastian Ott <sebott@linux.ibm.com>
---
 drivers/s390/cio/vfio_ccw_drv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/2] kvm: x86: Bounds-check argument to x86_exception_has_error_code
##### From: Jim Mattson <jmattson@google.com>

```c
x86_exception_has_error_code should deterministically return false if
its operand is greater than 32.

Fixes: 0447378a4a793 ("kvm: vmx: Nested VM-entry prereqs for event inj.")
Cc: Marc Orr <marcorr@google.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Marc Orr <marcorr@google.com>
---
 arch/x86/kvm/x86.h | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/2] kvm: x86: Bounds-check argument to x86_exception_has_error_code
##### From: Jim Mattson <jmattson@google.com>

```c
x86_exception_has_error_code should deterministically return false if
its operand is greater than 32.

Fixes: 0447378a4a793 ("kvm: vmx: Nested VM-entry prereqs for event inj.")
Cc: Marc Orr <marcorr@google.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/x86.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH kernel 1/3] vfio_pci: Allow mapping extra regions
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
So far we only allowed mapping of MMIO BARs to the userspace. However
there there are GPUs with on-board coherent RAM accessible via side
channels which we also want to map to the userspace. The first client
for this is NVIDIA V100 GPU with NVLink2 direct links to a POWER9
NPU-enabled CPU; such GPUs have 16GB RAM which is coherently mapped
to the system address space, we are going to export these as an extra
PCI region.

We already support extra PCI regions and this adds support for mapping
them to the userspace.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
Changes:
v2:
* reverted one of mistakenly removed error checks
---
 drivers/vfio/pci/vfio_pci_private.h | 3 +++
 drivers/vfio/pci/vfio_pci.c         | 8 ++++++++
 2 files changed, 11 insertions(+)

```
