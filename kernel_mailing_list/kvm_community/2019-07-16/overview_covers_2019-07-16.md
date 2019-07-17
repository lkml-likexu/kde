

#### [PATCH v8 0/3] KVM: x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it. If the instruction causes a delay, the amount
of time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay (the time to delay
relative to the VM’s timestamp counter). 

The release document ref below link:
Intel 64 and IA-32 Architectures Software Developer's Manual,
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Changelog:
v8:
	Add vmx_waitpkg_supported() helper (Sean)
	Add an accessor to expose umwait_control_cached (Sean)
	Set msr_ia32_umwait_control in vcpu_vmx u32 and raise #GP when
	[63:32] is set when rdmsr. (Sean)
	Introduce a common exit helper handle_unexpected_vmexit (Sean)
v7:
	Add nested support for user wait instructions (Paolo)
	Use the test on vmx->secondary_exec_control to replace
	guest_cpuid_has (Paolo)
v6:
	add check msr_info->host_initiated in get/set msr(Xiaoyao)
	restore the atomic_switch_umwait_control_msr()(Xiaoyao)

Tao Xu (3):
  KVM: x86: Add support for user wait instructions
  KVM: vmx: Emulate MSR IA32_UMWAIT_CONTROL
  KVM: vmx: Introduce handle_unexpected_vmexit and handle WAITPKG vmexit

 arch/x86/include/asm/vmx.h      |  1 +
 arch/x86/include/uapi/asm/vmx.h |  6 ++-
 arch/x86/kernel/cpu/umwait.c    |  6 +++
 arch/x86/kvm/cpuid.c            |  2 +-
 arch/x86/kvm/vmx/capabilities.h |  6 +++
 arch/x86/kvm/vmx/nested.c       |  5 ++
 arch/x86/kvm/vmx/vmx.c          | 83 ++++++++++++++++++++++++++-------
 arch/x86/kvm/vmx/vmx.h          |  9 ++++
 arch/x86/kvm/x86.c              |  1 +
 9 files changed, 101 insertions(+), 18 deletions(-)
```
#### [PATCH v4 0/2] x86: Enable user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c

UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.

UMONITOR arms address monitoring hardware using an address. A store
to an address within the specified address range triggers the
monitoring hardware to wake up the processor waiting in umwait.

UMWAIT instructs the processor to enter an implementation-dependent
optimized state while monitoring a range of addresses. The optimized
state may be either a light-weight power/performance optimized state
(c0.1 state) or an improved power/performance optimized state
(c0.2 state).

TPAUSE instructs the processor to enter an implementation-dependent
optimized state c0.1 or c0.2 state and wake up when time-stamp counter
reaches specified timeout.

Availability of the user wait instructions is indicated by the presence
of the CPUID feature flag WAITPKG CPUID.0x07.0x0:ECX[5].

The patches enable the umonitor, umwait and tpause features in KVM.
Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it in kvm and provide a capability to
enable it. Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
QEMU use "-overcommit cpu-pm=on, a VM can use UMONITOR, UMWAIT and TPAUSE
instructions. If the instruction causes a delay, the amount of time
delayed is called here the physical delay. The physical delay is first
computed by determining the virtual delay (the time to delay relative to
the VM’s timestamp counter). Otherwise, UMONITOR, UMWAIT and TPAUSE cause
an invalid-opcode exception(#UD).

The dependency KVM patch link:
https://lkml.org/lkml/2019/7/16/58

The release document ref below link:
https://software.intel.com/sites/default/files/\
managed/39/c5/325462-sdm-vol-1-2abcd-3abcd.pdf

Changelog:
v4:
	Set IA32_UMWAIT_CONTROL 32bits
v3:
	Simplify the patches, expose user wait instructions when the guest
	has CPUID (Paolo)
v2:
	Separated from the series
	https://www.mail-archive.com/qemu-devel@nongnu.org/msg549526.html
	Use kvm capability to enable UMONITOR, UMWAIT and TPAUSE when
	QEMU use "-overcommit cpu-pm=on"	
v1:
	Sent out with MOVDIRI/MOVDIR64B instructions patches

Tao Xu (2):
  x86/cpu: Add support for UMONITOR/UMWAIT/TPAUSE
  target/i386: Add support for save/load IA32_UMWAIT_CONTROL MSR

 target/i386/cpu.c     |  3 ++-
 target/i386/cpu.h     |  3 +++
 target/i386/kvm.c     | 17 +++++++++++++++++
 target/i386/machine.c | 20 ++++++++++++++++++++
 4 files changed, 42 insertions(+), 1 deletion(-)
```
#### [PATCH 00/14] pending doc patches for 5.3-rc
##### From: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>

```c

Those are the pending documentation patches after my pull request
for this branch:

    git://git.kernel.org/pub/scm/linux/kernel/git/mchehab/linux-media.git tags/docs/v5.3-1

Patches 1 to 13 were already submitted, but got rebased. Patch 14
is a new fixup one.

Patches 1 and 2 weren't submitted before due to merge conflicts
that are now solved upstream;

Patch 3 fixes a series of random Documentation/* references that
are pointing to the wrong places.

Patch 4 fix a longstanding issue: every time a new book is added,
conf.py need changes, in order to allow generating a PDF file.
After the patch, conf.py will automatically recognize new books,
saving the trouble of keeping adding documents to it.

Patches 5 to 11 are due to fonts support when building translations.pdf.
The main focus is to add xeCJK support. While doing it, I discovered
some bugs at sphinx-pre-install script after running it with 7 different
distributions.

Patch 12 improves support for partial doc building. Currently, each
subdir needs to have its own conf.py, in order to support partial
doc build. After it, any Documentation subdir can be used to 
roduce html/pdf docs with:

	make SPHINXDIRS="foo bar" htmldocs
	(or pdfdocs, latexdocs, epubdocs, ...)

Patch 13 is a cleanup patch: it simply get rid of all those extra
conf.py files that  aren't needed anymore. The only extra config
file after it is this one:

	Documentation/media/conf_nitpick.py

With enables some extra optional Sphinx features.

Patch 14 adds Documentation/virtual to the main index.rst file
and add a new *.rst file that was orphaned there.

-

After this series, there's just one more patch meant to be applied
for 5.3, with is still waiting for some patches to be merged from
linux-next:

    https://git.linuxtv.org/mchehab/experimental.git/commit/?id=b1b5dc7d7bbfbbfdace2a248c6458301c6e34100


Mauro Carvalho Chehab (14):
  docs: powerpc: convert docs to ReST and rename to *.rst
  docs: power: add it to to the main documentation index
  docs: fix broken doc references due to renames
  docs: pdf: add all Documentation/*/index.rst to PDF output
  docs: conf.py: add CJK package needed by translations
  docs: conf.py: only use CJK if the font is available
  scripts/sphinx-pre-install: fix script for RHEL/CentOS
  scripts/sphinx-pre-install: don't use LaTeX with CentOS 7
  scripts/sphinx-pre-install: fix latexmk dependencies
  scripts/sphinx-pre-install: cleanup Gentoo checks
  scripts/sphinx-pre-install: seek for Noto CJK fonts for pdf output
  docs: load_config.py: avoid needing a conf.py just due to LaTeX docs
  docs: remove extra conf.py files
  docs: virtual: add it to the documentation body

 Documentation/PCI/pci-error-recovery.rst      |   5 +-
 Documentation/RCU/rculist_nulls.txt           |   2 +-
 Documentation/admin-guide/conf.py             |  10 --
 Documentation/conf.py                         |  30 +++-
 Documentation/core-api/conf.py                |  10 --
 Documentation/crypto/conf.py                  |  10 --
 Documentation/dev-tools/conf.py               |  10 --
 .../devicetree/bindings/arm/idle-states.txt   |   2 +-
 Documentation/doc-guide/conf.py               |  10 --
 Documentation/driver-api/80211/conf.py        |  10 --
 Documentation/driver-api/conf.py              |  10 --
 Documentation/driver-api/pm/conf.py           |  10 --
 Documentation/filesystems/conf.py             |  10 --
 Documentation/gpu/conf.py                     |  10 --
 Documentation/index.rst                       |   3 +
 Documentation/input/conf.py                   |  10 --
 Documentation/kernel-hacking/conf.py          |  10 --
 Documentation/locking/spinlocks.rst           |   4 +-
 Documentation/maintainer/conf.py              |  10 --
 Documentation/media/conf.py                   |  12 --
 Documentation/memory-barriers.txt             |   2 +-
 Documentation/networking/conf.py              |  10 --
 Documentation/power/index.rst                 |   2 +-
 .../{bootwrapper.txt => bootwrapper.rst}      |  28 +++-
 .../{cpu_families.txt => cpu_families.rst}    |  23 +--
 .../{cpu_features.txt => cpu_features.rst}    |   6 +-
 Documentation/powerpc/{cxl.txt => cxl.rst}    |  46 ++++--
 .../powerpc/{cxlflash.txt => cxlflash.rst}    |  10 +-
 .../{DAWR-POWER9.txt => dawr-power9.rst}      |  15 +-
 Documentation/powerpc/{dscr.txt => dscr.rst}  |  18 +-
 ...ecovery.txt => eeh-pci-error-recovery.rst} | 108 ++++++------
 ...ed-dump.txt => firmware-assisted-dump.rst} | 117 +++++++------
 Documentation/powerpc/{hvcs.txt => hvcs.rst}  | 108 ++++++------
 Documentation/powerpc/index.rst               |  34 ++++
 Documentation/powerpc/isa-versions.rst        |  15 +-
 .../powerpc/{mpc52xx.txt => mpc52xx.rst}      |  12 +-
 ...nv.txt => pci_iov_resource_on_powernv.rst} |  15 +-
 .../powerpc/{pmu-ebb.txt => pmu-ebb.rst}      |   1 +
 Documentation/powerpc/ptrace.rst              | 156 ++++++++++++++++++
 Documentation/powerpc/ptrace.txt              | 151 -----------------
 .../{qe_firmware.txt => qe_firmware.rst}      |  37 +++--
 .../{syscall64-abi.txt => syscall64-abi.rst}  |  29 ++--
 ...al_memory.txt => transactional_memory.rst} |  45 ++---
 Documentation/process/conf.py                 |  10 --
 Documentation/sh/conf.py                      |  10 --
 Documentation/sound/conf.py                   |  10 --
 Documentation/sphinx/load_config.py           |  27 ++-
 .../translations/ko_KR/memory-barriers.txt    |   2 +-
 Documentation/userspace-api/conf.py           |  10 --
 Documentation/virtual/kvm/index.rst           |   1 +
 Documentation/vm/conf.py                      |  10 --
 Documentation/watchdog/hpwdt.rst              |   2 +-
 Documentation/x86/conf.py                     |  10 --
 MAINTAINERS                                   |  14 +-
 arch/powerpc/kernel/exceptions-64s.S          |   2 +-
 drivers/gpu/drm/drm_modes.c                   |   2 +-
 drivers/i2c/busses/i2c-nvidia-gpu.c           |   2 +-
 drivers/scsi/hpsa.c                           |   4 +-
 drivers/soc/fsl/qe/qe.c                       |   2 +-
 drivers/tty/hvc/hvcs.c                        |   2 +-
 include/soc/fsl/qe/qe.h                       |   2 +-
 scripts/sphinx-pre-install                    | 118 ++++++++++---
 62 files changed, 738 insertions(+), 678 deletions(-)
 delete mode 100644 Documentation/admin-guide/conf.py
 delete mode 100644 Documentation/core-api/conf.py
 delete mode 100644 Documentation/crypto/conf.py
 delete mode 100644 Documentation/dev-tools/conf.py
 delete mode 100644 Documentation/doc-guide/conf.py
 delete mode 100644 Documentation/driver-api/80211/conf.py
 delete mode 100644 Documentation/driver-api/conf.py
 delete mode 100644 Documentation/driver-api/pm/conf.py
 delete mode 100644 Documentation/filesystems/conf.py
 delete mode 100644 Documentation/gpu/conf.py
 delete mode 100644 Documentation/input/conf.py
 delete mode 100644 Documentation/kernel-hacking/conf.py
 delete mode 100644 Documentation/maintainer/conf.py
 delete mode 100644 Documentation/media/conf.py
 delete mode 100644 Documentation/networking/conf.py
 rename Documentation/powerpc/{bootwrapper.txt => bootwrapper.rst} (93%)
 rename Documentation/powerpc/{cpu_families.txt => cpu_families.rst} (95%)
 rename Documentation/powerpc/{cpu_features.txt => cpu_features.rst} (97%)
 rename Documentation/powerpc/{cxl.txt => cxl.rst} (95%)
 rename Documentation/powerpc/{cxlflash.txt => cxlflash.rst} (98%)
 rename Documentation/powerpc/{DAWR-POWER9.txt => dawr-power9.rst} (95%)
 rename Documentation/powerpc/{dscr.txt => dscr.rst} (91%)
 rename Documentation/powerpc/{eeh-pci-error-recovery.txt => eeh-pci-error-recovery.rst} (82%)
 rename Documentation/powerpc/{firmware-assisted-dump.txt => firmware-assisted-dump.rst} (80%)
 rename Documentation/powerpc/{hvcs.txt => hvcs.rst} (91%)
 create mode 100644 Documentation/powerpc/index.rst
 rename Documentation/powerpc/{mpc52xx.txt => mpc52xx.rst} (91%)
 rename Documentation/powerpc/{pci_iov_resource_on_powernv.txt => pci_iov_resource_on_powernv.rst} (97%)
 rename Documentation/powerpc/{pmu-ebb.txt => pmu-ebb.rst} (99%)
 create mode 100644 Documentation/powerpc/ptrace.rst
 delete mode 100644 Documentation/powerpc/ptrace.txt
 rename Documentation/powerpc/{qe_firmware.txt => qe_firmware.rst} (95%)
 rename Documentation/powerpc/{syscall64-abi.txt => syscall64-abi.rst} (82%)
 rename Documentation/powerpc/{transactional_memory.txt => transactional_memory.rst} (93%)
 delete mode 100644 Documentation/process/conf.py
 delete mode 100644 Documentation/sh/conf.py
 delete mode 100644 Documentation/sound/conf.py
 delete mode 100644 Documentation/userspace-api/conf.py
 delete mode 100644 Documentation/vm/conf.py
 delete mode 100644 Documentation/x86/conf.py
```
