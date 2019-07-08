

#### [PATCH 0/5] KVM: nVMX: Skip vmentry checks that are necessary only if
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c

The following functions,

	nested_vmx_check_controls
	nested_vmx_check_host_state
	nested_vmx_check_guest_state

do a number of vmentry checks for VMCS12. However, not all of these checks need
to be executed on every vmentry. This patchset makes some of these vmentry
checks optional based on the state of VMCS12 in that if VMCS12 is dirty, only
then the checks will be executed. This will reduce performance impact on
vmentry of nested guests.


[PATCH 1/5] KVM: nVMX: Skip VM-Execution Control vmentry checks that are
[PATCH 2/5] KVM: nVMX: Skip VM-Exit Control vmentry checks that are
[PATCH 3/5] KVM: nVMX: Skip VM-Entry Control checks that are necessary
[PATCH 4/5] KVM: nVMX: Skip Host State Area vmentry checks that are
[PATCH 5/5] KVM: nVMX: Skip Guest State Area vmentry checks that are

 arch/x86/kvm/vmx/nested.c | 149 ++++++++++++++++++++++++++++++++++------------
 1 file changed, 111 insertions(+), 38 deletions(-)

Krish Sadhukhan (5):
      nVMX: Skip VM-Execution Control vmentry checks that are necessary only if VMCS12 is dirty
      nVMX: Skip VM-Exit Control vmentry checks that are necessary only if VMCS12 is dirty
      nVMX: Skip VM-Entry Control checks that are necessary only if VMCS12 is dirty
      nVMX: Skip Host State Area vmentry checks that are necessary only if VMCS12 is dirty
      nVMX: Skip Guest State Area vmentry checks that are necessary only if VMCS12 is dirty
```
