#### [PATCH V5 1/5] KVM: X86: Memory ROE documentation
##### From: Ahmed Abd El Mawgood <ahmedsoliman0x666@gmail.com>

```c
Following up with my previous threads on KVM assisted Anti rootkit
protections.
The current version doesn't address the attacks involving pages
remapping. It is still design in progress, nevertheless, it will be in
my later patch sets.

Signed-off-by: Ahmed Abd El Mawgood <ahmedsoliman0x666@gmail.com>
---
 Documentation/virtual/kvm/hypercalls.txt | 31 ++++++++++++++++++++++++
 1 file changed, 31 insertions(+)

```
#### [kvm PATCH v4 1/2] kvm: vmx: refactor vmx_msrs struct for vmallocFrom: Marc Orr <marcorr@google.com>
##### From: Marc Orr <marcorr@google.com>

```c
Previously, the vmx_msrs struct relied being aligned within a struct
that is backed by the direct map (e.g., memory allocated with kalloc()).
Specifically, this enabled the virtual addresses associated with the
struct to be translated to physical addresses. However, we'd like to
refactor the host struct, vcpu_vmx, to be allocated with vmalloc(), so
that allocation will succeed when contiguous physical memory is scarce.

Thus, this patch refactors how vmx_msrs is declared and allocated, to
ensure that it can be mapped to the physical address space, even when
vmx_msrs resides within in a vmalloc()'d struct.

Signed-off-by: Marc Orr <marcorr@google.com>
---
 arch/x86/kvm/vmx.c | 57 ++++++++++++++++++++++++++++++++++++++++++++--
 1 file changed, 55 insertions(+), 2 deletions(-)

```
