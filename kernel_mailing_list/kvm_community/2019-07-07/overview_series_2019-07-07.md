#### [PATCH 1/5] KVM: nVMX: Skip VM-Execution Control vmentry checks that are necessary only if VMCS12 is dirty
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
..so that every nested vmentry is not slowed down by those checks.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 57 +++++++++++++++++++++++++--------------
 1 file changed, 37 insertions(+), 20 deletions(-)

```
