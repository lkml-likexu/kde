#### [PATCH kvm-unit-tests] x86: umip: skip SMSW test because it fails
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
SMSW does not cause a VMEXIT and therefore emulated UMIP fails.
Comment out the test.

Suggested-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/umip.c | 3 +++
 1 file changed, 3 insertions(+)

```
