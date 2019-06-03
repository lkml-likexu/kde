#### [PATCH v17 01/15] arm64: untag user pointers in access_ok and __uaccess_mask_ptr
##### From: Andrey Konovalov <andreyknvl@google.com>

```c
This patch is a part of a series that extends arm64 kernel ABI to allow to
pass tagged user pointers (with the top byte set to something else other
than 0x00) as syscall arguments.

copy_from_user (and a few other similar functions) are used to copy data
from user memory into the kernel memory or vice versa. Since a user can
provided a tagged pointer to one of the syscalls that use copy_from_user,
we need to correctly handle such pointers.

Do this by untagging user pointers in access_ok and in __uaccess_mask_ptr,
before performing access validity checks.

Note, that this patch only temporarily untags the pointers to perform the
checks, but then passes them as is into the kernel internals.

Reviewed-by: Kees Cook <keescook@chromium.org>
Reviewed-by: Catalin Marinas <catalin.marinas@arm.com>
Signed-off-by: Andrey Konovalov <andreyknvl@google.com>
Reviewed-by: Vincenzo Frascino <vincenzo.frascino@arm.com>
---
 arch/arm64/include/asm/uaccess.h | 10 +++++++---
 1 file changed, 7 insertions(+), 3 deletions(-)

```
#### [PATCH v3 1/5] KVM: LAPIC: Extract adaptive tune timer advancement logic
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Extract adaptive tune timer advancement logic to a single function.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c | 57 ++++++++++++++++++++++++++++++----------------------
 1 file changed, 33 insertions(+), 24 deletions(-)

```
#### [PATCH] kvm: remove invalid check for debugfs_create_dir()
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
debugfs_create_dir() can never return NULL, so no need to check for an
impossible thing.

It's also not needed to ever check the return value of this function, so
just remove the check entirely, and indent the previous line to a sane
formatting :)

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---
 virt/kvm/kvm_main.c | 4 +---
 1 file changed, 1 insertion(+), 3 deletions(-)

```
#### [PATCH v4 02/28] docs: arm64: convert docs to ReST and rename to .rst
##### From: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>

```c
The documentation is in a format that is very close to ReST format.

The conversion is actually:
  - add blank lines in order to identify paragraphs;
  - fixing tables markups;
  - adding some lists markups;
  - marking literal blocks;
  - adjust some title markups.

At its new index.rst, let's add a :orphan: while this is not linked to
the main index.rst file, in order to avoid build warnings.

Signed-off-by: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>
---
 ...object_usage.txt => acpi_object_usage.rst} | 288 ++++++++++++------
 .../arm64/{arm-acpi.txt => arm-acpi.rst}      | 155 +++++-----
 .../arm64/{booting.txt => booting.rst}        |  91 ++++--
 ...egisters.txt => cpu-feature-registers.rst} | 204 +++++++------
 .../arm64/{elf_hwcaps.txt => elf_hwcaps.rst}  |  56 +---
 .../{hugetlbpage.txt => hugetlbpage.rst}      |   7 +-
 Documentation/arm64/index.rst                 |  28 ++
 ...structions.txt => legacy_instructions.rst} |  43 ++-
 Documentation/arm64/memory.rst                |  98 ++++++
 Documentation/arm64/memory.txt                |  97 ------
 ...ication.txt => pointer-authentication.rst} |   2 +
 ...{silicon-errata.txt => silicon-errata.rst} |  65 +++-
 Documentation/arm64/{sve.txt => sve.rst}      |  12 +-
 ...agged-pointers.txt => tagged-pointers.rst} |   6 +-
 .../translations/zh_CN/arm64/booting.txt      |   4 +-
 .../zh_CN/arm64/legacy_instructions.txt       |   4 +-
 .../translations/zh_CN/arm64/memory.txt       |   4 +-
 .../zh_CN/arm64/silicon-errata.txt            |   4 +-
 .../zh_CN/arm64/tagged-pointers.txt           |   4 +-
 Documentation/virtual/kvm/api.txt             |   2 +-
 arch/arm64/include/asm/efi.h                  |   2 +-
 arch/arm64/include/asm/image.h                |   2 +-
 arch/arm64/include/uapi/asm/sigcontext.h      |   2 +-
 arch/arm64/kernel/kexec_image.c               |   2 +-
 24 files changed, 703 insertions(+), 479 deletions(-)
 rename Documentation/arm64/{acpi_object_usage.txt => acpi_object_usage.rst} (84%)
 rename Documentation/arm64/{arm-acpi.txt => arm-acpi.rst} (86%)
 rename Documentation/arm64/{booting.txt => booting.rst} (86%)
 rename Documentation/arm64/{cpu-feature-registers.txt => cpu-feature-registers.rst} (65%)
 rename Documentation/arm64/{elf_hwcaps.txt => elf_hwcaps.rst} (92%)
 rename Documentation/arm64/{hugetlbpage.txt => hugetlbpage.rst} (86%)
 create mode 100644 Documentation/arm64/index.rst
 rename Documentation/arm64/{legacy_instructions.txt => legacy_instructions.rst} (73%)
 create mode 100644 Documentation/arm64/memory.rst
 delete mode 100644 Documentation/arm64/memory.txt
 rename Documentation/arm64/{pointer-authentication.txt => pointer-authentication.rst} (99%)
 rename Documentation/arm64/{silicon-errata.txt => silicon-errata.rst} (55%)
 rename Documentation/arm64/{sve.txt => sve.rst} (98%)
 rename Documentation/arm64/{tagged-pointers.txt => tagged-pointers.rst} (94%)

diff --git a/Documentation/arm64/acpi_object_usage.txt b/Documentation/arm64/acpi_object_usage.rst
similarity index 84%
rename from Documentation/arm64/acpi_object_usage.txt
```
#### [PATCH v1 1/5] KVM: arm/arm64: Remove kvm_mmio_emulate tracepoint
##### From: Zenghui Yu <yuzenghui@huawei.com>

```c
In current KVM/ARM code, no one will invoke trace_kvm_mmio_emulate().
Remove this TRACE_EVENT definition.

Cc: Christoffer Dall <christoffer.dall@arm.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Signed-off-by: Zenghui Yu <yuzenghui@huawei.com>
---
 virt/kvm/arm/trace.h | 21 ---------------------
 1 file changed, 21 deletions(-)

```
#### [RFC 01/10] x86/mm/kaslr: refactor to use enum indices for regions
##### From: Marius Hillenbrand <mhillenb@amazon.de>

```c
The KASLR randomization code currently refers to specific regions, such
as the vmalloc area, by literal indices into an array. When adding new
regions, we have to be careful to also change all indices that may
potentially change. Avoid that risk by introducing an enum used as
indices.

Signed-off-by: Marius Hillenbrand <mhillenb@amazon.de>
Cc: Alexander Graf <graf@amazon.de>
Cc: David Woodhouse <dwmw@amazon.co.uk>
---
 arch/x86/mm/kaslr.c | 22 ++++++++++++++--------
 1 file changed, 14 insertions(+), 8 deletions(-)

```
#### [PULL 1/1] vfio-ccw: Destroy kmem cache region on module exit
##### From: Cornelia Huck <cohuck@redhat.com>

```c
From: Farhan Ali <alifm@linux.ibm.com>

Free the vfio_ccw_cmd_region on module exit.

Fixes: d5afd5d135c8 ("vfio-ccw: add handling for async channel instructions")
Signed-off-by: Farhan Ali <alifm@linux.ibm.com>
Message-Id: <c0f39039d28af39ea2939391bf005e3495d890fd.1559576250.git.alifm@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_drv.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v5 1/8] s390/mm: force swiotlb for protected virtualization
##### From: Halil Pasic <pasic@linux.ibm.com>

```c
On s390, protected virtualization guests have to use bounced I/O
buffers.  That requires some plumbing.

Let us make sure, any device that uses DMA API with direct ops correctly
is spared from the problems, that a hypervisor attempting I/O to a
non-shared page would bring.

Signed-off-by: Halil Pasic <pasic@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 arch/s390/Kconfig                   |  4 +++
 arch/s390/include/asm/mem_encrypt.h | 18 +++++++++++
 arch/s390/mm/init.c                 | 47 +++++++++++++++++++++++++++++
 3 files changed, 69 insertions(+)
 create mode 100644 arch/s390/include/asm/mem_encrypt.h

```
#### [PATCH v3 1/2] KVM: LAPIC: Optimize timer latency consider world switch time
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Advance lapic timer tries to hidden the hypervisor overhead between the
host emulated timer fires and the guest awares the timer is fired. However,
even though after more sustaining optimizations, kvm-unit-tests/tscdeadline_latency 
still awares ~1000 cycles latency since we lost the time between the end of 
wait_lapic_expire and the guest awares the timer is fired. There are 
codes between the end of wait_lapic_expire and the world switch, furthermore, 
the world switch itself also has overhead. Actually the guest_tsc is equal 
to the target deadline time in wait_lapic_expire is too late, guest will
aware the latency between the end of wait_lapic_expire() and after vmentry 
to the guest. This patch takes this time into consideration. 

The vmentry+vmexit time which is measured by kvm-unit-tests/vmexit.falt is 
1800 cycles on my 2.5GHz Skylake server, the vmentry_advance_ns module 
parameter default value is 300ns, it can be tuned/reworked in the further.
This patch can reduce average cyclictest latency from 3us to 2us on Skylake 
server. (guest w/ nohz=off, idle=poll, host w/ preemption_timer=N, the 
cyclictest latency is not too sensitive when preemption_timer=Y for this 
optimization in my testing).

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
v2 -> v3:
 * read-only module parameter
 * get_vmentry_advance_cycles() not inline
v1 -> v2:
 * rename get_vmentry_advance_delta to get_vmentry_advance_cycles
 * cache vmentry_advance_cycles by setting param bit 0 
 * add param max limit 

 arch/x86/kvm/lapic.c   | 33 ++++++++++++++++++++++++++++++---
 arch/x86/kvm/lapic.h   |  3 +++
 arch/x86/kvm/vmx/vmx.c |  2 +-
 arch/x86/kvm/x86.c     |  8 ++++++++
 arch/x86/kvm/x86.h     |  2 ++
 5 files changed, 44 insertions(+), 4 deletions(-)

```
#### [PATCH v5] KVM: x86: Add Intel CPUID.1F cpuid emulation support
##### From: Like Xu <like.xu@linux.intel.com>

```c
Add support to expose Intel V2 Extended Topology Enumeration Leaf for
some new systems with multiple software-visible die within each package.

Because unimplemented and unexposed leaves should be explicitly reported
as zero, there is no need to limit cpuid.0.eax to the maximum value of
feature configuration but limit it to the highest leaf implemented in
the current code. A single clamping seems sufficient and cheaper.

Reported-by: kbuild test robot <lkp@intel.com>
Co-developed-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Xiaoyao Li <xiaoyao.li@linux.intel.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---

==changelog==

v5:
- Fixed sparse warnings: ncompatible types in comparison expression

v4: https://lkml.org/lkml/2019/6/5/1029
- Limited cpuid.0.eax to the highest leaf implemented in KVM

v3: https://lkml.org/lkml/2019/5/26/64
- Refine commit message and comment

v2: https://lkml.org/lkml/2019/4/25/1246

- Apply cpuid.1f check rule on Intel SDM page 3-222 Vol.2A
- Add comment to handle 0x1f anf 0xb in common code
- Reduce check time in a descending-break style

v1: https://lkml.org/lkml/2019/4/22/28

---
 arch/x86/kvm/cpuid.c | 9 +++++++--
 1 file changed, 7 insertions(+), 2 deletions(-)

```
#### [PATCH v13 1/7] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 13 ++++++++-----
 drivers/nvdimm/region_devs.c | 26 ++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  9 ++++++++-
 6 files changed, 47 insertions(+), 12 deletions(-)

```
#### [v2, 1/4] Build target for emulate.o as a userspace binary
##### From: Sam Caccavale <samcacc@amazon.de>

```c
This commit contains the minimal set of functionality to build
afl-harness around arch/x86/emulate.c which allows exercising code
in that source file, like x86_emulate_insn.  Resolving the
dependencies was done via GCC's -H flag by get_headers.py.

CR: https://code.amazon.com/reviews/CR-8325546
---
 tools/Makefile                  |   9 ++
 tools/fuzz/x86ie/.gitignore     |   2 +
 tools/fuzz/x86ie/Makefile       |  51 +++++++++++
 tools/fuzz/x86ie/README.md      |  12 +++
 tools/fuzz/x86ie/afl-harness.c  | 149 ++++++++++++++++++++++++++++++++
 tools/fuzz/x86ie/common.h       |  87 +++++++++++++++++++
 tools/fuzz/x86ie/emulator_ops.c |  58 +++++++++++++
 tools/fuzz/x86ie/emulator_ops.h | 117 +++++++++++++++++++++++++
 tools/fuzz/x86ie/stubs.c        |  56 ++++++++++++
 tools/fuzz/x86ie/stubs.h        |  52 +++++++++++
 10 files changed, 593 insertions(+)
 create mode 100644 tools/fuzz/x86ie/.gitignore
 create mode 100644 tools/fuzz/x86ie/Makefile
 create mode 100644 tools/fuzz/x86ie/README.md
 create mode 100644 tools/fuzz/x86ie/afl-harness.c
 create mode 100644 tools/fuzz/x86ie/common.h
 create mode 100644 tools/fuzz/x86ie/emulator_ops.c
 create mode 100644 tools/fuzz/x86ie/emulator_ops.h
 create mode 100644 tools/fuzz/x86ie/stubs.c
 create mode 100644 tools/fuzz/x86ie/stubs.h

--
2.17.1




Amazon Development Center Germany GmbH
Krausenstr. 38
10117 Berlin
Geschaeftsfuehrung: Christian Schlaeger, Ralf Herbrich
Eingetragen am Amtsgericht Charlottenburg unter HRB 149173 B
Sitz: Berlin
Ust-ID: DE 289 237 879

```
