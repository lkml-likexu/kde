#### [PATCH 1/2] kvm: nVMX: NMI-window exiting should wake L2 from HLTFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
According to the SDM, "NMI-window exiting" VM-exits wake a logical
processor from the same inactive states as would an NMI. Specifically,
they wake a logical processor from the shutdown state and from the
states entered using the HLT and MWAIT instructions.

Fixes: 6dfacadd5858 ("KVM: nVMX: Add support for activity state HLT")
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/vmx.c | 19 ++++++++++++++++---
 1 file changed, 16 insertions(+), 3 deletions(-)

```
