

#### [PATCH 0/2] KVM: vmx: Inject #UD for SGX ENCLS instructions
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

Intel Software Guard Extensions (SGX) provides hardware-based
capabilities to protect a userspace application's secrets.  SGX
defines a new CPL0 instruction, ENCLS[1], for use by the kernel
to support and manage SGX.  Because SGX does not have a true
software enable bit, e.g. there is no CR4.SGXE bit, ENCLS isn't
guaranteed to #UD in a guest kernel, e.g. ENCLS will #GP if the
SGX enable bit in Feature Control MSR is not set (and the CPU
supports ENCLS).  Ensure a guest sees consistent and expected
fault behavior by intercepting ENCLS and injecting #UD.

This series does not add support for exposing SGX to a guest.
Virtualization of SGX depends on Enclave Page Cache (EPC)
management that is not yet available in the kernel, i.e. KVM
support for exposing SGX to a guest cannot be added until basic
SGX functionality is upstreamed, which is a WIP[2].

[1] ENCLS is really multiple instructions, referred to as leaf
    functions, that are bundled under a singled opcode, a la
    VMFUNC or GETSEC.

[2] https://www.spinics.net/lists/kvm/msg171333.html or
    https://lkml.org/lkml/2018/7/3/879

Sean Christopherson (2):
  KVM: vmx: Add defines for SGX ENCLS exiting
  KVM: vmx: Inject #UD for SGX ENCLS instruction in guest

 arch/x86/include/asm/vmx.h |  3 +++
 arch/x86/kvm/vmx.c         | 30 +++++++++++++++++++++++++++++-
 2 files changed, 32 insertions(+), 1 deletion(-)
```
#### [PATCH RESEND 0/2] KVM: vmx: Inject #UD for SGX ENCLS instructions
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

Intel Software Guard Extensions (SGX) provides hardware-based
capabilities to protect a userspace application's secrets.  SGX
defines a new CPL0 instruction, ENCLS[1], for use by the kernel
to support and manage SGX.  Because SGX does not have a true
software enable bit, e.g. there is no CR4.SGXE bit, ENCLS isn't
guaranteed to #UD in a guest kernel, e.g. ENCLS will #GP if the
SGX enable bit in Feature Control MSR is not set (and the CPU
supports ENCLS).  Ensure a guest sees consistent and expected
fault behavior by intercepting ENCLS and injecting #UD.

This series does not add support for exposing SGX to a guest.
Virtualization of SGX depends on Enclave Page Cache (EPC)
management that is not yet available in the kernel, i.e. KVM
support for exposing SGX to a guest cannot be added until basic
SGX functionality is upstreamed, which is a WIP[2].

[1] ENCLS is really multiple instructions, referred to as leaf
    functions, that are bundled under a singled opcode, a la
    VMFUNC or GETSEC.

[2] https://www.spinics.net/lists/kvm/msg171333.html or
    https://lkml.org/lkml/2018/7/3/879

Sean Christopherson (2):
  KVM: vmx: Add defines for SGX ENCLS exiting
  KVM: vmx: Inject #UD for SGX ENCLS instruction in guest

 arch/x86/include/asm/vmx.h |  3 +++
 arch/x86/kvm/vmx.c         | 30 +++++++++++++++++++++++++++++-
 2 files changed, 32 insertions(+), 1 deletion(-)
```
