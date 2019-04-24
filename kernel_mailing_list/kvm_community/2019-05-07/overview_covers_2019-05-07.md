

#### [PATCH 0/7]  KVM: nVMX: Optimize VMCS data copying
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

KVM spends a lot of time copying data between VMCSes, especially when
utilizing a shadow VMCS as data needs to moved between vmcs12 and the
shadow VMCS.

This series is comprised of three mostly unrelated optimizations that
happen to modify the same code and would cause non-trivial conflicts:

  - Expose read-frequently write-rarely fields to L1 for VMREAD only.
    Exposing fields to L1 for both VMWRITE and VMREAD means KVM needs
    to copy data from the shadow VMCS to vmcs12 on nested VM-Entry.
    For fields that are almost never written by L1, copying those
    fields on every nested VM-Entry is pure overhead.

  - Track the vmcs12 offsets for shadowed fields.  All offsets are
    known at compile time (HIGH fields complicate this slightly), but
    KVM currently does a runtime lookup to get the offset, which adds
    measurable latency to copying to/from the shadow VMCS.

  - Sync rarely accessed guest fields from vmcs02 to vmcs12 only when
    necessary.  A non-trivial number of guest fields are infrequently
    accessed by VMMs, e.g. most segment descriptor fields.  Avoid
    copying the fields from vmcs02 (30+ VMREADs) on every nested VM-Exit
    to L1, and instead pull them from vmcs02 when read by L1, or when
    they may be consumed by KVM, e.g. for consistency checks.


Sean Christopherson (7):
  KVM: nVMX: Intercept VMWRITEs to read-only shadow VMCS fields
  KVM: nVMX: Intercept VMWRITEs to GUEST_{CS,SS}_AR_BYTES
  KVM: nVMX: Track vmcs12 offsets for shadowed VMCS fields
  KVM: nVMX: Lift sync_vmcs12() out of prepare_vmcs12()
  KVM: nVMX: Use descriptive names for VMCS sync functions and flags
  KVM: nVMX: Add helpers to identify shadowed VMCS fields
  KVM: nVMX: Sync rarely accessed guest fields only when needed

 arch/x86/kvm/vmx/nested.c             | 384 +++++++++++++++++---------
 arch/x86/kvm/vmx/nested.h             |   2 +-
 arch/x86/kvm/vmx/vmcs12.h             |  57 ++--
 arch/x86/kvm/vmx/vmcs_shadow_fields.h |  78 +++---
 arch/x86/kvm/vmx/vmx.c                |   4 +-
 arch/x86/kvm/vmx/vmx.h                |   8 +-
 6 files changed, 320 insertions(+), 213 deletions(-)
```
#### [PATCH 00/15] KVM: nVMX: Optimize nested VM-Entry
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

The majority of patches in this series are loosely related optimizations
to pick off low(ish) hanging fruit in nested VM-Entry, e.g. there are
many VMREADs and VMWRITEs that can be optimized away without too much
effort.

The major change (in terms of performance) is to not "put" the vCPU
state when switching between vmcs01 and vmcs02, which can reudce the
latency of a nested VM-Entry by upwards of 1000 cycles.

A few bug fixes are prepended as they touch code that happens to be
modified by the various optimizations.

Sean Christopherson (15):
  KVM: nVMX: Don't dump VMCS if virtual APIC page can't be mapped
  KVM: VMX: Always signal #GP on WRMSR to MSR_IA32_CR_PAT with bad value
  KVM: nVMX: Always sync GUEST_BNDCFGS when it comes from vmcs01
  KVM: nVMX: Write ENCLS-exiting bitmap once per vmcs02
  KVM: nVMX: Don't rewrite GUEST_PML_INDEX during nested VM-Entry
  KVM: nVMX: Don't "put" vCPU or host state when switching VMCS
  KVM: nVMX: Don't reread VMCS-agnostic state when switching VMCS
  KVM: nVMX: Don't speculatively write virtual-APIC page address
  KVM: nVMX: Don't speculatively write APIC-access page address
  KVM: nVMX: Update vmcs12 for MSR_IA32_CR_PAT when it's written
  KVM: nVMX: Update vmcs12 for SYSENTER MSRs when they're written
  KVM: nVMX: Update vmcs12 for MSR_IA32_DEBUGCTLMSR when it's written
  KVM: nVMX: Update vmcs02 GUEST_IA32_DEBUGCTL only when vmcs12 is dirty
  KVM: nVMX: Don't update GUEST_BNDCFGS if it's clean in HV eVMCS
  KVM: nVMX: Copy PDPTRs to/from vmcs12 only when necessary

 arch/x86/kvm/vmx/nested.c | 142 +++++++++++++++++++-------------------
 arch/x86/kvm/vmx/vmx.c    |  93 +++++++++++++++++--------
 arch/x86/kvm/vmx/vmx.h    |   5 +-
 3 files changed, 136 insertions(+), 104 deletions(-)
```
#### [PATCH 00/13]  KVM: VMX: Reduce VMWRITEs to VMCS controls
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

The overarching theme of this series is to reduce the number of VMWRITEs
to VMCS controls.  VMWRITEs to the major VMCS controls, i.e. vm_entry,
vm_exit, pin, exec and sec_exec, are deceptively expensive.  CPUs with
VMCS caching (Westmere and later) also optimize away consistency checks
on VM-Entry, i.e. skip consistency checks if the relevant fields haven't
changed since the last successful VM-Entry (of the cached VMCS).
Because uops are a precious commodity, uCode's dirty VMCS field tracking
isn't as precise as software would prefer.  Notably, writing any of the
major VMCS fields effectively marks the entire VMCS dirty, i.e. causes
the next VM-Entry to perform all consistency checks, which consumes
several hundred cycles.

The majority of this series is technically vanilla VMX, but the end goal
of nearly every patch is to eliminate VMWRITEs to controls when running
nested guests, e.g. much of the series resolves around shadowing the
various controls so that they don't need to be rewritten to vmcs02 on
every nested VM-Entry.

The sole patch that is purely vanilla VMX is to avoid writing pin
controls when disabling/enabling the preemption timer.  This is the
last known known case where semi-frequent writes to control fields
can be avoided (in non-nested operation).  E.g. detecting IRQ windows
frequently toggles VIRTUAL_INTR_PENDING, but at this juncture that
behavior is effectively unavoidable.  Resolving the preemption timer
case takes a somewhat adventurous approach of leaving the timer running
even when it's not in use.

Sean Christopherson (13):
  KVM: nVMX: Use adjusted pin controls for vmcs02
  KVM: VMX: Add builder macros for shadowing controls
  KVM: VMX: Shadow VMCS pin controls
  KVM: VMX: Shadow VMCS primary execution controls
  KVM: VMX: Shadow VMCS secondary execution controls
  KVM: nVMX: Shadow VMCS controls on a per-VMCS basis
  KVM: nVMX: Don't reset VMCS controls shadow on VMCS switch
  KVM: VMX: Explicitly initialize controls shadow at VMCS allocation
  KVM: nVMX: Preserve last USE_MSR_BITMAPS when preparing vmcs02
  KVM: nVMX: Preset *DT exiting in vmcs02 when emulating UMIP
  KVM: VMX: Drop hv_timer_armed from 'struct loaded_vmcs'
  KVM: nVMX: Don't mark vmcs12 as dirty when L1 writes pin controls
  KVM: VMX: Leave preemption timer running when it's disabled

 arch/x86/kvm/vmx/nested.c |  54 ++++++-------
 arch/x86/kvm/vmx/vmcs.h   |  11 ++-
 arch/x86/kvm/vmx/vmx.c    | 156 +++++++++++++++++++-------------------
 arch/x86/kvm/vmx/vmx.h    |  92 +++++++---------------
 4 files changed, 145 insertions(+), 168 deletions(-)
```
