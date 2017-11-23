#### [GIT PULL 01/19] KVM: s390: Replace clear_user with kvm_clear_guest
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From: Janosch Frank <frankja@linux.ibm.com>

kvm_clear_guest also does the dirty tracking for us, which we want to
have.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/priv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [GIT PULL] Please pull my kvm-ppc-next-4.19-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Please do a pull from my kvm-ppc-next-4.19-1 tag to get a PPC update
for 4.19.  There is not much in there, just some code cleanups and bug
fixes.

Michael Ellerman also has some changes that touch arch/powerpc/kvm in
his topic/ppc-kvm branch, which he has merged into his next branch.  I
have not pulled them into my tree since there are no conflicts with
the changes in my kvm-ppc-next branch.

Thanks,
Paul.

The following changes since commit 6f0d349d922ba44e4348a17a78ea51b7135965b1:

  Merge git://git.kernel.org/pub/scm/linux/kernel/git/davem/net (2018-06-25 15:58:17 +0800)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-4.19-1

for you to fetch changes up to b5c6f7607b908b1445f2556c8d2f3b1ec5fc5aa8:

  KVM: PPC: Book3S HV: Read kvm->arch.emul_smt_mode under kvm->lock (2018-07-26 15:38:41 +1000)

----------------------------------------------------------------
PPC KVM update for 4.19.

This update adds no new features; it just has some minor code cleanups
and bug fixes, including a fix to allow us to create KVM_MAX_VCPUS
vCPUs on POWER9 in all CPU threading modes.

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      KVM: PPC: Book3S: Fix matching of hardware and emulated TCE tables

Nicholas Mc Guire (2):
      KVM: PPC: Book3S HV: Add of_node_put() in success path
      KVM: PPC: Book3S HV: Fix constant size warning

Paul Mackerras (2):
      KVM: PPC: Book3S HV: Allow creating max number of VCPUs on POWER9
      KVM: PPC: Book3S HV: Read kvm->arch.emul_smt_mode under kvm->lock

Sam Bobroff (1):
      KVM: PPC: Book3S HV: Pack VCORE IDs to access full VCPU ID space

Simon Guo (1):
      KVM: PPC: Remove mmio_vsx_tx_sx_enabled in KVM MMIO emulation

 arch/powerpc/include/asm/kvm_book3s.h | 47 +++++++++++++++++++++++++++++++++++
 arch/powerpc/include/asm/kvm_host.h   | 26 +++++++++++--------
 arch/powerpc/include/asm/reg.h        |  2 +-
 arch/powerpc/kvm/book3s_64_vio.c      |  5 ++--
 arch/powerpc/kvm/book3s_hv.c          | 42 +++++++++++++++++++++----------
 arch/powerpc/kvm/book3s_xive.c        | 19 ++++++++------
 arch/powerpc/kvm/emulate_loadstore.c  |  7 +++---
 arch/powerpc/kvm/powerpc.c            | 30 +++++++++++-----------
 8 files changed, 125 insertions(+), 53 deletions(-)
```
#### [PATCH 01/16] KVM: nVMX: move host EFER consistency checks to VMFail path
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Invalid host state related to loading EFER on VMExit causes a
VMFail(VMXERR_ENTRY_INVALID_HOST_STATE_FIELD), not a VMExit.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx.c | 31 ++++++++++++++++---------------
 1 file changed, 16 insertions(+), 15 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S PR: Exiting split hack mode needs to fixup both PC and LR
##### From: Cameron Kaiser <spectre@floodgap.com>

```c
When an OS (currently only classic Mac OS) is running in KVM-PR and makes a
linked jump from code with split hack addressing enabled into code that does
not, LR is not correctly updated and reflects the previously munged PC. This
undoes the address munge when exiting split hack mode so that code relying
on LR being a proper address will now execute. This does not affect OS X
or other operating systems running on KVM-PR.

Signed-off-by: Cameron Kaiser <spectre@floodgap.com>

```
#### [PATCH] KVM: vmx: write HOST_IA32_EFER in vmx_set_constant_host_state()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
EFER is constant in the host and writing it once during setup means
we can skip writing the host value in add_atomic_switch_msr_special().

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: X86: Disable KVM_FEATURE_STEAL_TIME when both delayacct_on added to cmdline and CONFIG_SCHEDSTATS is set
##### From: Chen Xiao <abigwc@gmail.com>

```c
From: Chen Xiao <abigwc@163.com>

When sched_info_on returns 1，KVM_FEATURE_STEAL_TIME will be set,
steal% can be seen in the virtual machine.The returned value of
sched_info_on depends on delayacct_on. If nodelayacct is added to
kernel boot cmdline,the KVM_FEATURE_STEAL_TIME will be turned off
by setting delayacct_on to 0.When CONFIG_SCHEDSTATS is set, sched_info_on
always returns 1, and adding nodelayacct to the cmdline cannot turn
off the KVM_FEATURE_STEAL_TIME Sometimes the users do not want the
running state of host to be perceived in the virtual machine, and 
intend to turn off KVM_FEATURE_STEAL_TIME. The requirement is not
available, however, when CONFIG_SCHEDSTATS has been set.Modify the
judgment criteria for being set up from KVM_FEATURE_STEAL_TIME, and
it is only be judged by the value of delayacct_on.

Signed-off-by: Chen Xiao <abigwc@gmail.com>
---
 arch/x86/kvm/cpuid.c |  2 +-
 arch/x86/kvm/x86.c   |  8 ++++----
 arch/x86/kvm/x86.h   | 10 ++++++++++
 3 files changed, 15 insertions(+), 5 deletions(-)

```
