#### [PATCH 1/2][KVM nVMX]: Add a vmentry check for HOST_SYSENTER_ESP and HOST_SYSENTER_EIP fields
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "Checks on VMX Controls" in Intel SDM vol 3C, the
following check is performed on vmentry of L2 guests:

    On processors that support Intel 64 architecture, the IA32_SYSENTER_ESP
    field and the IA32_SYSENTER_EIP field must each contain a canonical
    address.

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Mihai Carabas <mihai.carabas@oracle.com>
---
 arch/x86/kvm/vmx/nested.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
#### [kvm-unit-tests PATCH v3 1/5] lib: arm: Use UART address from generated config.h
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Generate lib/config.h when configuring kvm-unit-tests. The file is empty
for all architectures except for arm and arm64, where it is used to store
the UART base address. This removes the hardcoded address from lib/arm/io.c
and provides a mechanism for using different UART addresses in the future.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 configure    | 17 +++++++++++++++++
 Makefile     |  2 +-
 lib/arm/io.c | 12 ++++++------
 .gitignore   |  1 +
 4 files changed, 25 insertions(+), 7 deletions(-)

```
#### [PATCH kvmtool v2 1/3] builtin-run: Fix warning when resolving path
##### From: Anisse Astier <aastier@freebox.fr>

```c
GCC 8.2 gives this warning:

builtin-run.c: In function ‘kvm_run_write_sandbox_cmd.isra.1’:
builtin-run.c:417:28: error: ‘%s’ directive output may be truncated writing up to 4095 bytes into a region of size 4091 [-Werror=format-truncation=]
   snprintf(dst, len, "/host%s", resolved_path);
                            ^~   ~~~~~~~~~~~~~

It's because it understands that len is PATH_MAX, the same as
resolved_path's size. This patch handles the case where the string is
truncated, and fixes the warning.

Signed-off-by: Anisse Astier <aastier@freebox.fr>
Reviewed-by: Andre Przywara <andre.przywara@arm.com>
---
 builtin-run.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH kvmtool 1/3] builtin-run: Replace strncpy calls with strlcpy
##### From: Andre Przywara <andre.przywara@arm.com>

```c
There are two uses of strncpy in builtin-run.c, where we don't make
proper use of strncpy, so that GCC 8.x complains and aborts compilation.

Replace those two calls with strlcpy(), which does the right thing in
our case.

Signed-off-by: Andre Przywara <andre.przywara@arm.com>
---
 builtin-run.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: export <linux/kvm_para.h> and <asm/kvm_para.h> for all architectures
##### From: Masahiro Yamada <yamada.masahiro@socionext.com>

```c
I do not see any consistency about headers_install of <linux/kvm_para.h>
and <asm/kvm_para.h>.

According to my analysis of Linux 5.0-rc5, there are 3 groups:

 [1] Both <linux/kvm_para.h> and <asm/kvm_para.h> are exported

    alpha, arm, hexagon, mips, powerpc, s390, sparc, x86

 [2] <asm/kvm_para.h> is exported, but <linux/kvm_para.h> is not

    arc, arm64, c6x, h8300, ia64, m68k, microblaze, nios2, openrisc

 [3] Neither <linux/kvm_para.h> nor <asm/kvm_para.h> is exported

    csky, nds32, riscv

This does not match to the actual KVM support. At least, [2] looks
like a half-way house to me.

Nor do arch maintainers look like they care about this. For example,
commit 0add53713b1c ("microblaze: Add missing kvm_para.h to Kbuild")
exported <asm/kvm_para.h> to user-space in order to fix an in-kernel
build error.

We have two ways to fix this inconsistency:

 [A] export both <linux/kvm_para.h> and <asm/kvm_para.h> for all
     architectures, irrespective of the KVM support

 [B] Match the header export of <linux/kvm_para.h> and <asm/kvm_para.h>
     to the KVM support

This commit adopts [A].

Remove 'no-export-headers' from include/uapi/linux/Kbuild to export
<linux/kvm_para.h> for all architectures.

Add 'mandatory-y' to include/uapi/asm-generic/Kbuild.asm to export
<asm/kvm_para.h> for all architectures. If arch does not have specific
implementation, a wrapper file to <asm-generic/kvm_para.h> is
automatically generated, and exported.

include/uapi/asm-generic/kvm_para.h is just a empty file. I cleaned
up empty <asm/kvm_para.h> stubs.

Signed-off-by: Masahiro Yamada <yamada.masahiro@socionext.com>
Acked-by: Christoph Hellwig <hch@lst.de>
---

If you prefer [B] (or you have a better idea),
please suggest.

 

 arch/alpha/include/uapi/asm/kvm_para.h   | 2 --
 arch/arc/include/uapi/asm/Kbuild         | 1 -
 arch/arm/include/uapi/asm/kvm_para.h     | 2 --
 arch/arm64/include/uapi/asm/Kbuild       | 2 --
 arch/c6x/include/uapi/asm/Kbuild         | 1 -
 arch/csky/include/asm/Kbuild             | 1 -
 arch/h8300/include/uapi/asm/Kbuild       | 1 -
 arch/hexagon/include/uapi/asm/kvm_para.h | 2 --
 arch/ia64/include/uapi/asm/Kbuild        | 1 -
 arch/m68k/include/uapi/asm/Kbuild        | 1 -
 arch/microblaze/include/uapi/asm/Kbuild  | 1 -
 arch/mips/include/uapi/asm/kvm_para.h    | 5 -----
 arch/nds32/include/asm/Kbuild            | 1 -
 arch/nios2/include/uapi/asm/Kbuild       | 1 -
 arch/openrisc/include/uapi/asm/Kbuild    | 1 -
 arch/parisc/include/uapi/asm/Kbuild      | 1 -
 arch/riscv/include/asm/Kbuild            | 1 -
 arch/s390/include/uapi/asm/kvm_para.h    | 8 --------
 arch/sh/include/uapi/asm/Kbuild          | 1 -
 arch/sparc/include/uapi/asm/kvm_para.h   | 2 --
 arch/unicore32/include/uapi/asm/Kbuild   | 1 -
 arch/xtensa/include/uapi/asm/Kbuild      | 1 -
 include/uapi/asm-generic/Kbuild.asm      | 1 +
 include/uapi/linux/Kbuild                | 4 ----
 24 files changed, 1 insertion(+), 42 deletions(-)
 delete mode 100644 arch/alpha/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/arm/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/hexagon/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/mips/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/s390/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/sparc/include/uapi/asm/kvm_para.h

diff --git a/arch/alpha/include/uapi/asm/kvm_para.h b/arch/alpha/include/uapi/asm/kvm_para.h
```
#### [RFC][Patch v8 1/7] KVM: Support for guest free page hinting
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
This patch includes the following:
1. Basic skeleton for the support
2. Enablement of x86 platform to use the same

Signed-off-by: Nitesh Narayan Lal <nitesh@redhat.com>
---
 arch/x86/Kbuild              |  2 +-
 arch/x86/kvm/Kconfig         |  8 ++++++++
 arch/x86/kvm/Makefile        |  2 ++
 include/linux/gfp.h          |  9 +++++++++
 include/linux/page_hinting.h | 17 +++++++++++++++++
 virt/kvm/page_hinting.c      | 36 ++++++++++++++++++++++++++++++++++++
 6 files changed, 73 insertions(+), 1 deletion(-)
 create mode 100644 include/linux/page_hinting.h
 create mode 100644 virt/kvm/page_hinting.c

```
#### [PATCH] KVM: PPC: Book3S: Allow XICS emulation to work in nested hosts using XIVE
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Currently, the KVM code assumes that if the host kernel is using the
XIVE interrupt controller (the new interrupt controller that first
appeared in POWER9 systems), then the in-kernel XICS emulation will
use the XIVE hardware to deliver interrupts to the guest.  However,
this only works when the host is running in hypervisor mode and has
full access to all of the XIVE functionality.  It doesn't work in any
nested virtualization scenario, either with PR KVM or nested-HV KVM,
because the XICS-on-XIVE code calls directly into the native-XIVE
routines, which are not initialized and cannot function correctly
because they use OPAL calls, and OPAL is not available in a guest.

This means that using the in-kernel XICS emulation in a nested
hypervisor that is using XIVE as its interrupt controller will cause a
(nested) host kernel crash.  To fix this, we change most of the places
where the current code calls xive_enabled() to select between the
XICS-on-XIVE emulation and the plain XICS emulation to call a new
function, xics_on_xive(), which returns false in a guest.

However, there is a further twist.  The plain XICS emulation has some
functions which are used in real mode and access the underlying XICS
controller (the interrupt controller of the host) directly.  In the
case of a nested hypervisor, this means doing XICS hypercalls
directly.  When the nested host is using XIVE as its interrupt
controller, these hypercalls will fail.  Therefore this also adds
checks in the places where the XICS emulation wants to access the
underlying interrupt controller directly, and if that is XIVE, makes
the code use the virtual mode fallback paths, which call generic
kernel infrastructure rather than doing direct XICS access.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
Reviewed-by: Cédric Le Goater <clg@kaod.org>
---
 arch/powerpc/include/asm/kvm_ppc.h   | 14 ++++++++++++++
 arch/powerpc/kvm/book3s.c            | 10 +++++-----
 arch/powerpc/kvm/book3s_hv.c         | 16 ++++++++--------
 arch/powerpc/kvm/book3s_hv_builtin.c | 14 +++++++-------
 arch/powerpc/kvm/book3s_hv_rm_xics.c |  7 +++++++
 arch/powerpc/kvm/book3s_rtas.c       |  8 ++++----
 arch/powerpc/kvm/powerpc.c           |  4 ++--
 7 files changed, 47 insertions(+), 26 deletions(-)

```
#### [PATCH] KVM: PPC: Book3S PR: Add emulation for slbfee. instruction
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Recent kernels, since commit e15a4fea4dee ("powerpc/64s/hash: Add
some SLB debugging tests", 2018-10-03) use the slbfee. instruction,
which PR KVM currently does not have code to emulate.  Consequently
recent kernels fail to boot under PR KVM.  This adds emulation of
slbfee., enabling these kernels to boot successfully.

Signed-off-by: Paul Mackerras <paulus@ozlabs.org>
---
 arch/powerpc/include/asm/kvm_host.h |  1 +
 arch/powerpc/kvm/book3s_32_mmu.c    |  1 +
 arch/powerpc/kvm/book3s_64_mmu.c    | 14 ++++++++++++++
 arch/powerpc/kvm/book3s_emulate.c   | 18 ++++++++++++++++++
 4 files changed, 34 insertions(+)

```
#### [RFC PATCH 1/4] madvise: Expose ability to set dontneed from kernelFrom: Alexander Duyck <alexander.duyck@gmail.com>
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

In order to enable a KVM hypervisor to notify the host that a guest has
freed its pages we will need to have a mechanism to update the virtual
memory associated with the guest. In order to expose this functionality I
am adding a new function do_madvise_dontneed that can be used to indicate
a region that a given VM is done with.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 include/linux/mm.h |    2 ++
 mm/madvise.c       |   13 ++++++++++++-
 2 files changed, 14 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH] s390x: Only look at relevant skey bits
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Reference and change indication should not be consulted when checking
for ACC and FP values of storage keys.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
---

Automated testing with the debug kernel seems to result in the
referenced bit being 1 when the key is read after setting it. This
makes the tests trip, as I compare the wrong bits (referenced and
changed are allowed to change in-between).

---
 lib/s390x/asm/mem.h |  5 +++++
 s390x/pfmf.c        |  6 +++++-
 s390x/skey.c        | 10 ++++++----
 3 files changed, 16 insertions(+), 5 deletions(-)

```
#### [RFC PATCH 1/8] svm: Fix improper check when deactivate AVICThread-Topic: [RFC PATCH 1/8] svm: Fix improper check when deactivate AVIC
##### From: "Suthikulpanit, Suravee" <Suravee.Suthikulpanit@amd.com>

```c
The function svm_refresh_apicv_exec_ctrl() always returning prematurely
as kvm_vcpu_apicv_active() always return false when calling from
the function arch/x86/kvm/x86.c:kvm_vcpu_deactivate_apicv().
This is because the apicv_active is set to false just before calling
refresh_apicv_exec_ctrl().

Also, we need to mark VMCB_AVIC bit as dirty instead of VMCB_INTR.

So, fix svm_refresh_apicv_exec_ctrl() to properly deactivate AVIC.

Fixes: 67034bb9dd5e ('KVM: SVM: Add irqchip_split() checks before enabling AVIC')
Cc: Radim Krčmář <rkrcmar@redhat.com>
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Suravee Suthikulpanit <suravee.suthikulpanit@amd.com>
---
 arch/x86/kvm/svm.c | 10 +++++-----
 1 file changed, 5 insertions(+), 5 deletions(-)

```
#### [PULL 14/25] i386/kvm: ignore masked irqs when update msi routes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
From: Peter Xu <peterx@redhat.com>

When we are with intel-iommu device and with IR on, KVM will register
an IEC notifier to detect interrupt updates from the guest and we'll
kick off kvm_update_msi_routes_all() when it happens to make sure
kernel IRQ cache is matching the latest.

Though, kvm_update_msi_routes_all() is buggy in that it ignored the
mask bit of either MSI/MSIX messages and it tries to translate the
message even if the corresponding message was already masked by the
guest driver (hence the MSI/MSIX message will be invalid).

Without this patch, we can receive an error message when we reboot a
guest with both an assigned vfio-pci device and intel-iommu enabled:

  qemu-system-x86_64: vtd_interrupt_remap_msi: MSI address low 32 bit invalid: 0x0

The error does not affect functionality of the guest since when we
failed to translate we'll just silently continue (which makes sense
since crashing the VM for this seems even worse), but still it's
better to fix it up.

Signed-off-by: Peter Xu <peterx@redhat.com>
Reviewed-by: Michael S. Tsirkin <mst@redhat.com>
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 target/i386/kvm.c | 14 +++++++++++---
 1 file changed, 11 insertions(+), 3 deletions(-)

```
#### [PULL 1/1] vfio-ccw: Don't assume there are more ccws after a TIC
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Farhan Ali <alifm@linux.ibm.com>

When trying to calculate the length of a ccw chain, we assume
there are ccws after a TIC. This can lead to overcounting and
copying garbage data from guest memory.

Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Message-Id: <d63748c1f1b03147bcbf401596638627a5e35ef7.1548082107.git.alifm@linux.ibm.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_cp.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC PATCH QEMU] i386/kvm: Enable paravirtual unused page hint mechanism
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

This patch adds the flag named kvm-pv-unused-page-hint. This functionality
is enabled by kvm for x86 and provides a mechanism by which the guest can
indicate to the host which pages it is no longer using. By providing these
hints the guest can help to reduce the memory pressure on the host as
dirtied pages will be cleared and not written out to swap if they are
marked as being unused.

Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 target/i386/cpu.c |    2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [RFC][QEMU PATCH] KVM: Support for guest free page hinting
##### From: Nitesh Narayan Lal <nitesh@redhat.com>

```c
This patch enables QEMU to recieve free page address from the guest
and to use madvise to make them available to the host.
---
 hw/virtio/trace-events                        |  1 +
 hw/virtio/virtio-balloon.c                    | 82 +++++++++++++++++++
 hw/virtio/virtio.c                            | 25 ++++++
 include/hw/virtio/virtio-access.h             |  1 +
 include/hw/virtio/virtio-balloon.h            |  2 +-
 .../standard-headers/linux/virtio_balloon.h   |  1 +
 6 files changed, 111 insertions(+), 1 deletion(-)

```
