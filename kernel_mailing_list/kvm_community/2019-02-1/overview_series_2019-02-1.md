#### [kvm-unit-tests PATCH v2 1/5] lib: arm: Use UART address from generated config.h
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Generate lib/config.h when configuring kvm-unit-tests. The file is empty
for all architectures except for arm and arm64, where it is used to store
the UART base address. This removes the hardcoded address from lib/arm/io.c
and provides a mechanism for using different UART addresses in the future.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 configure    | 17 +++++++++++++++++
 Makefile     |  2 +-
 lib/arm/io.c |  5 ++---
 .gitignore   |  1 +
 4 files changed, 21 insertions(+), 4 deletions(-)

```
#### [PATCH 1/2] KVM: SVM: move common struct definitions to header fileThread-Topic: [PATCH 1/2] KVM: SVM: move common struct definitions to header
##### From: "Singh, Brijesh" <brijesh.singh@amd.com>

```c
Some of the structure will be used by sev.c in next patch, lets
move the common structure definition in svm.h so that both the
sev.c and svm.c can use it.

Signed-off-by: Brijesh Singh <brijesh.singh@amd.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: Tom Lendacky <Thomas.Lendacky@amd.com>
---
 arch/x86/include/asm/svm.h | 155 +++++++++++++++++++++++++++++++++++++
 arch/x86/kvm/svm.c         | 155 -------------------------------------
 2 files changed, 155 insertions(+), 155 deletions(-)

```
#### [PATCH] kvm: x86: Remove useless index and parameter
##### From: Jing Liu <jing2.liu@linux.intel.com>

```c
The kvm_cpuid_param structure is designed for getting cpu level, with ECX input
is zero. While it is useless and wasteful to use a field in the structure for this.
Just remove the field and use 0 directly.

Also, the parameter in function is_centaur_cpu() is also useless.

Number of a 64 bit build:

          text    data     bss     dec     hex filename
before:   7529     112       0    7641    1dd9 ./arch/x86/kvm/cpuid.o
after:    7428     112       0    7540    1d74 ./arch/x86/kvm/cpuid.o

Signed-off-by: Jing Liu <jing2.liu@linux.intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/cpuid.c | 11 +++++------
 1 file changed, 5 insertions(+), 6 deletions(-)

```
#### [PATCH v1] KVM: s390: vsie: fix Do the CRYCB validation first
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
The case when the SIE for guest3 is not setup for using
encryption keys nor Adjunct processor but the guest2
does use these features was not properly handled.

This leads SIE entry for guest3 to crash with validity intercept
because the guest2, not having the use of encryption keys nor
Adjunct Processor did not initialize the CRYCB designation.

In the case where none of ECA_APIE, ECB3_AES or ECB3_DEA
are set in guest3 a format 0 CRYCB is allowed for guest3
and the CRYCB designation in the SIE for guest3 is not checked
on SIE entry.

Let's allow the CRYCD designation to be ignored when the
SIE for guest3 is not initialized for encryption key usage
nor AP.

Fixup: d6f6959 (KVM: s390: vsie: Do the CRYCB validation first)

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reported-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 arch/s390/kvm/vsie.c | 3 +++
 1 file changed, 3 insertions(+)

```
#### [PATCH v2 1/4] arm: fdt: add stdout-path to /chosen node
##### From: Andre Przywara <andre.przywara@arm.com>

```c
The DT spec describes the stdout-path property in the /chosen node to
contain the DT path for a default device usable for outputting characters.
The Linux kernel uses this for earlycon (without further parameters),
other DT users might rely on this as well.

Add a stdout-path property pointing to the "serial0" alias, then add an
aliases node at the end of the FDT, containing the actual path. This
allows the FDT generation code in hw/serial.c to set this string.

Even when we use the virtio console, the serial console is still there
and works, so we can expose this unconditionally. Putting the virtio
console path in there will not work anyway.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 arm/fdt.c         | 10 ++++++++++
 hw/serial.c       |  9 +++++++++
 include/kvm/fdt.h |  2 ++
 3 files changed, 21 insertions(+)

```
#### [PATCH v3 1/2] vsock/virtio: fix kernel panic after device hot-unplug
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
virtio_vsock_remove() invokes the vsock_core_exit() also if there
are opened sockets for the AF_VSOCK protocol family. In this way
the vsock "transport" pointer is set to NULL, triggering the
kernel panic at the first socket activity.

This patch move the vsock_core_init()/vsock_core_exit() in the
virtio_vsock respectively in module_init and module_exit functions,
that cannot be invoked until there are open sockets.

Bugzilla: https://bugzilla.redhat.com/show_bug.cgi?id=1609699
Reported-by: Yan Fu <yafu@redhat.com>
Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
Acked-by: Stefan Hajnoczi <stefanha@redhat.com>
---
 net/vmw_vsock/virtio_transport.c | 26 ++++++++++++++++++--------
 1 file changed, 18 insertions(+), 8 deletions(-)

```
#### 
##### 

```c
```
