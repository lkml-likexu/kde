#### [PATCH 1/3] KVM: LAPIC: Make lapic timer unpinned when timer is injected by posted-interrupt
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Make lapic timer unpinned when timer is injected by posted-interrupt,
the emulated timer can be offload to the housekeeping cpus.

This patch introduces a new kvm module parameter, it is false by default.
The host admin can enable it after fine tuned, e.g. dedicated instances 
scenario w/ nohz_full cover the pCPUs which vCPUs resident, several pCPUs 
surplus for housekeeping, disable mwait/hlt/pause vmexits to occupy the 
pCPUs, fortunately preemption timer is disabled after mwait is exposed 
to guest which makes emulated timer offload can be possible. 

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/lapic.c            | 20 ++++++++++++++++----
 arch/x86/kvm/svm.c              |  5 +++++
 arch/x86/kvm/vmx/vmx.c          |  9 +++++++++
 4 files changed, 31 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM: x86: Use DR_TRAP_BITS instead of hard-coded 15
##### From: Liran Alon <liran.alon@oracle.com>

```c
Make all code consistent with kvm_deliver_exception_payload() by using
appropriate symbolic constant instead of hard-coded number.

Reviewed-by: Nikita Leshenko <nikita.leshchenko@oracle.com>
Reviewed-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/emulate.c | 2 +-
 arch/x86/kvm/vmx/vmx.c | 4 ++--
 arch/x86/kvm/x86.c     | 2 +-
 3 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH v3 1/2] kvm: vmx: fix limit checking in get_vmx_mem_address()
##### From: Eugene Korenevsky <ekorenevsky@gmail.com>

```c
Intel SDM vol. 3, 5.3:
The processor causes a
general-protection exception (or, if the segment is SS, a stack-fault
exception) any time an attempt is made to access the following addresses
in a segment:
- A byte at an offset greater than the effective limit
- A word at an offset greater than the (effective-limit – 1)
- A doubleword at an offset greater than the (effective-limit – 3)
- A quadword at an offset greater than the (effective-limit – 7)

Therefore, the generic limit checking error condition must be

exn = (off > limit + 1 - access_len) = (off + access_len - 1 > limit)

but not

exn = (off + access_len > limit)

as for now.

Note: access length is incorrectly set to sizeof(u64). This will be fixed in
the subsequent patch.

Signed-off-by: Eugene Korenevsky <ekorenevsky@gmail.com>
---
Changes in v3 since v2: fixed limit checking condition to avoid underflow;
added note

 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v4 1/2] kvm: vmx: fix limit checking in get_vmx_mem_address()
##### From: Eugene Korenevsky <ekorenevsky@gmail.com>

```c
Intel SDM vol. 3, 5.3:
The processor causes a
general-protection exception (or, if the segment is SS, a stack-fault
exception) any time an attempt is made to access the following addresses
in a segment:
- A byte at an offset greater than the effective limit
- A word at an offset greater than the (effective-limit – 1)
- A doubleword at an offset greater than the (effective-limit – 3)
- A quadword at an offset greater than the (effective-limit – 7)

Therefore, the generic limit checking error condition must be

exn = (off > limit + 1 - access_len) = (off + access_len - 1 > limit)

but not

exn = (off + access_len > limit)

as for now.

Also avoid integer overflow of `off` at 32-bit KVM by casting it to u64.

Note: access length is currently sizeof(u64) which is incorrect. This
will be fixed in the subsequent patch.

Signed-off-by: Eugene Korenevsky <ekorenevsky@gmail.com>
---
Changes in v3 since v2: fixed limit checking condition to avoid underflow;
added note
Changes in v4 since v3: fixed `off` overflow at 32-bit by casting to u64

 arch/x86/kvm/vmx/nested.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
