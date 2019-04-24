

#### [PATCH 0/2] kvm: Some more trivial fixes for clear dirty log
##### From: Peter Xu <peterx@redhat.com>

```c

Two issues I've noticed when I'm drafting the QEMU support of it.
With these two patches applied the QEMU binary (with the clear dirty
log supported [1]) can migrate correctly otherwise the migration can
stall forever if with/after heavy memory workload.

Please have a look, thanks.

[1] https://github.com/xzpeter/qemu/tree/kvm-clear-dirty-log

Peter Xu (2):
  kvm: Fix the bitmap range to copy during clear dirty
  kvm: Fix loop of clear dirty with off-by-one

 virt/kvm/kvm_main.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)
```
#### [PATCH v2 0/3] kvm: Some more trivial fixes for clear dirty log
##### From: Peter Xu <peterx@redhat.com>

```c

v2:
- fix patch 2 to use DIV_ROUND_UP
- add one more patch to obsolete the old cap, and introduce new [Paolo]

Two issues I've noticed when I'm drafting the QEMU support of it.
With these two patches applied the QEMU binary (with the clear dirty
log supported [1]) can migrate correctly otherwise the migration can
stall forever if with/after heavy memory workload.

Please have a look, thanks.

[1] https://github.com/xzpeter/qemu/tree/kvm-clear-dirty-log

Peter Xu (3):
  KVM: Fix the bitmap range to copy during clear dirty
  KVM: Fix loop of clear dirty with possible off-by-one
  KVM: Introduce KVM_CAP_MANUAL_DIRTY_LOG_PROTECT_2

 Documentation/virtual/kvm/api.txt            | 13 ++++++++-----
 include/uapi/linux/kvm.h                     |  5 +++--
 tools/testing/selftests/kvm/dirty_log_test.c |  4 ++--
 virt/kvm/kvm_main.c                          | 10 +++++-----
 4 files changed, 18 insertions(+), 14 deletions(-)
```
#### [PATCH 00/16] treewide: fix match_string() helper when array size
##### From: Alexandru Ardelean <alexandru.ardelean@analog.com>

```c

The intent of this patch series is to make a case for fixing the
match_string() string helper.

The doc-string of the `__sysfs_match_string()` helper mentions that `n`
(the size of the given array) should be:
 * @n: number of strings in the array or -1 for NULL terminated arrays

However, this is not the case.
The helper stops on the first NULL in the array, regardless of whether -1
is provided or not.

There are some advantages to allowing this behavior (NULL elements within
in the array). One example, is to allow reserved registers as NULL in an
array.
One example in the series is patch:
   x86/mtrr: use new match_string() helper + add gaps == minor fix
which uses a "?" string for values that are reserved/don't care.

Since the change is a bit big, the change was coupled with renaming
match_string() -> __match_string().
The new match_string() helper (resulted here) does an ARRAY_SIZE() over the
array, which is useful when the array is static. 

Also, this way of doing things is a way to go through all the users of this
helpers and check that nothing goes wrong, and notify them about the change
to match_string().
It's a way of grouping changes in a manage-able way.

The first patch is important, the others can be dropped.

Signed-off-by: Alexandru Ardelean <alexandru.ardelean@analog.com>

Alexandru Ardelean (16):
  lib: fix match_string() helper when array size is positive
  treewide: rename match_string() -> __match_string()
  lib,treewide: add new match_string() helper/macro
  powerpc/xmon: use new match_string() helper/macro
  ALSA: oxygen: use new match_string() helper/macro
  x86/mtrr: use new match_string() helper + add gaps == minor fix
  device connection: use new match_string() helper/macro
  cpufreq/intel_pstate: remove NULL entry + use match_string()
  mmc: sdhci-xenon: use new match_string() helper/macro
  pinctrl: armada-37xx: use new match_string() helper/macro
  mm/vmpressure.c: use new match_string() helper/macro
  rdmacg: use new match_string() helper/macro
  drm/edid: use new match_string() helper/macro
  staging: gdm724x: use new match_string() helper/macro
  video: fbdev: pxafb: use new match_string() helper/macro
  sched: debug: use new match_string() helper/macro

 arch/powerpc/xmon/xmon.c                         |  2 +-
 arch/x86/kernel/cpu/mtrr/if.c                    | 10 ++++++----
 drivers/ata/pata_hpt366.c                        |  2 +-
 drivers/ata/pata_hpt37x.c                        |  2 +-
 drivers/base/devcon.c                            |  2 +-
 drivers/base/property.c                          |  2 +-
 drivers/clk/bcm/clk-bcm2835.c                    |  4 +---
 drivers/clk/clk.c                                |  4 ++--
 drivers/clk/rockchip/clk.c                       |  4 ++--
 drivers/cpufreq/intel_pstate.c                   |  9 ++++-----
 drivers/gpio/gpiolib-of.c                        |  2 +-
 drivers/gpu/drm/drm_edid_load.c                  |  2 +-
 drivers/gpu/drm/drm_panel_orientation_quirks.c   |  2 +-
 drivers/gpu/drm/i915/intel_pipe_crc.c            |  2 +-
 drivers/ide/hpt366.c                             |  2 +-
 drivers/mfd/omap-usb-host.c                      |  2 +-
 drivers/mmc/host/sdhci-xenon-phy.c               | 12 ++++++------
 drivers/net/wireless/intel/iwlwifi/mvm/debugfs.c |  2 +-
 drivers/pci/pcie/aer.c                           |  2 +-
 drivers/phy/tegra/xusb.c                         |  2 +-
 drivers/pinctrl/mvebu/pinctrl-armada-37xx.c      |  4 ++--
 drivers/pinctrl/pinmux.c                         |  2 +-
 drivers/power/supply/ab8500_btemp.c              |  2 +-
 drivers/power/supply/ab8500_charger.c            |  2 +-
 drivers/power/supply/ab8500_fg.c                 |  2 +-
 drivers/power/supply/abx500_chargalg.c           |  2 +-
 drivers/power/supply/charger-manager.c           |  4 ++--
 drivers/staging/gdm724x/gdm_tty.c                |  3 +--
 drivers/usb/common/common.c                      |  4 ++--
 drivers/usb/typec/class.c                        |  8 +++-----
 drivers/usb/typec/tps6598x.c                     |  2 +-
 drivers/vfio/vfio.c                              |  4 +---
 drivers/video/fbdev/pxafb.c                      |  4 ++--
 fs/ubifs/auth.c                                  |  4 ++--
 include/linux/string.h                           | 11 ++++++++++-
 kernel/cgroup/rdma.c                             |  2 +-
 kernel/sched/debug.c                             |  2 +-
 kernel/trace/trace.c                             |  2 +-
 lib/string.c                                     | 13 ++++++++-----
 mm/mempolicy.c                                   |  2 +-
 mm/vmpressure.c                                  |  4 ++--
 security/apparmor/lsm.c                          |  4 ++--
 security/integrity/ima/ima_main.c                |  2 +-
 sound/firewire/oxfw/oxfw.c                       |  2 +-
 sound/pci/oxygen/oxygen_mixer.c                  |  2 +-
 sound/soc/codecs/max98088.c                      |  2 +-
 sound/soc/codecs/max98095.c                      |  2 +-
 sound/soc/soc-dapm.c                             |  2 +-
 48 files changed, 88 insertions(+), 82 deletions(-)
```
#### [PATCH, RFC 00/62] Intel MKTME enabling
##### From: "Kirill A. Shutemov" <kirill.shutemov@linux.intel.com>

```c

= Intro =

The patchset brings enabling of Intel Multi-Key Total Memory Encryption.
It consists of changes into multiple subsystems:

 * Core MM: infrastructure for allocation pages, dealing with encrypted VMAs
   and providing API setup encrypted mappings.
 * arch/x86: feature enumeration, program keys into hardware, setup
   page table entries for encrypted pages and more.
 * Key management service: setup and management of encryption keys.
 * DMA/IOMMU: dealing with encrypted memory on IO side.
 * KVM: interaction with virtualization side.
 * Documentation: description of APIs and usage examples.

The patchset is huge. This submission aims to give view to the full picture and
get feedback on the overall design. The patchset will be split into more
digestible pieces later.

Please review. Any feedback is welcome.

= Overview =

Multi-Key Total Memory Encryption (MKTME)[1] is a technology that allows
transparent memory encryption in upcoming Intel platforms.  It uses a new
instruction (PCONFIG) for key setup and selects a key for individual pages by
repurposing physical address bits in the page tables.

These patches add support for MKTME into the existing kernel keyring subsystem
and add a new mprotect_encrypt() system call that can be used by applications
to encrypt anonymous memory with keys obtained from the keyring.

This architecture supports encrypting both normal, volatile DRAM and persistent
memory.  However, these patches do not implement persistent memory support.  We
anticipate adding that support next.

== Hardware Background ==

MKTME is built on top of an existing single-key technology called TME.  TME
encrypts all system memory using a single key generated by the CPU on every
boot of the system. TME provides mitigation against physical attacks, such as
physically removing a DIMM or watching memory bus traffic.

MKTME enables the use of multiple encryption keys[2], allowing selection of the
encryption key per-page using the page tables.  Encryption keys are programmed
into each memory controller and the same set of keys is available to all
entities on the system with access to that memory (all cores, DMA engines,
etc...).

MKTME inherits many of the mitigations against hardware attacks from TME.  Like
TME, MKTME does not mitigate vulnerable or malicious operating systems or
virtual machine managers.  MKTME offers additional mitigations when compared to
TME.

TME and MKTME use the AES encryption algorithm in the AES-XTS mode.  This mode,
typically used for block-based storage devices, takes the physical address of
the data into account when encrypting each block.  This ensures that the
effective key is different for each block of memory. Moving encrypted content
across physical address results in garbage on read, mitigating block-relocation
attacks.  This property is the reason many of the discussed attacks require
control of a shared physical page to be handed from the victim to the attacker.

== MKTME-Provided Mitigations ==

MKTME adds a few mitigations against attacks that are not mitigated when using
TME alone.  The first set are mitigations against software attacks that are
familiar today:

 * Kernel Mapping Attacks: information disclosures that leverage the
   kernel direct map are mitigated against disclosing user data.
 * Freed Data Leak Attacks: removing an encryption key from the
   hardware mitigates future user information disclosure.

The next set are attacks that depend on specialized hardware, such as an “evil
DIMM” or a DDR interposer:

 * Cross-Domain Replay Attack: data is captured from one domain
   (guest) and replayed to another at a later time.
 * Cross-Domain Capture and Delayed Compare Attack: data is captured
   and later analyzed to discover secrets.
 * Key Wear-out Attack: data is captured and analyzed in order to
   Weaken the AES encryption itself.

More details on these attacks are below.

=== Kernel Mapping Attacks ===

Information disclosure vulnerabilities leverage the kernel direct map because
many vulnerabilities involve manipulation of kernel data structures (examples:
CVE-2017-7277, CVE-2017-9605).  We normally think of these bugs as leaking
valuable *kernel* data, but they can leak application data when application
pages are recycled for kernel use.

With this MKTME implementation, there is a direct map created for each MKTME
KeyID which is used whenever the kernel needs to access plaintext.  But, all
kernel data structures are accessed via the direct map for KeyID-0.  Thus,
memory reads which are not coordinated with the KeyID get garbage (for example,
accessing KeyID-4 data with the KeyID-0 mapping).

This means that if sensitive data encrypted using MKTME is leaked via the
KeyID-0 direct map, ciphertext decrypted with the wrong key will be disclosed.
To disclose plaintext, an attacker must “pivot” to the correct direct mapping,
which is non-trivial because there are no kernel data structures in the
KeyID!=0 direct mapping.

=== Freed Data Leak Attack ===

The kernel has a history of bugs around uninitialized data.  Usually, we think
of these bugs as leaking sensitive kernel data, but they can also be used to
leak application secrets.

MKTME can help mitigate the case where application secrets are leaked:

 * App (or VM) places a secret in a page
 * App exits or frees memory to kernel allocator
 * Page added to allocator free list
 * Attacker reallocates page to a purpose where it can read the page

Now, imagine MKTME was in use on the memory being leaked.  The data can only be
leaked as long as the key is programmed in the hardware.  If the key is
de-programmed, like after all pages are freed after a guest is shut down, any
future reads will just see ciphertext.

Basically, the key is a convenient choke-point: you can be more confident that
data encrypted with it is inaccessible once the key is removed.

=== Cross-Domain Replay Attack ===

MKTME mitigates cross-domain replay attacks where an attacker replaces an
encrypted block owned by one domain with a block owned by another domain.
MKTME does not prevent this replacement from occurring, but it does mitigate
plaintext from being disclosed if the domains use different keys.

With TME, the attack could be executed by:
 * A victim places secret in memory, at a given physical address.
   Note: AES-XTS is what restricts the attack to being performed at a
   single physical address instead of across different physical
   addresses
 * Attacker captures victim secret’s ciphertext
 * Later on, after victim frees the physical address, attacker gains
   ownership
 * Attacker puts the ciphertext at the address and get the secret
   plaintext

But, due to the presumably different keys used by the attacker and the victim,
the attacker can not successfully decrypt old ciphertext.

=== Cross-Domain Capture and Delayed Compare Attack ===

This is also referred to as a kind of dictionary attack.

Similarly, MKTME protects against cross-domain capture-and-compare attacks.
Consider the following scenario:
 * A victim places a secret in memory, at a known physical address
 * Attacker captures victim’s ciphertext
 * Attacker gains control of the target physical address, perhaps
   after the victim’s VM is shut down or its memory reclaimed.
 * Attacker computes and writes many possible plaintexts until new
   ciphertext matches content captured previously.

Secrets which have low (plaintext) entropy are more vulnerable to this attack
because they reduce the number of possible plaintexts an attacker has to
compute and write.

The attack will not work if attacker and victim uses different keys.

=== Key Wear-out Attack ===

Repeated use of an encryption key might be used by an attacker to infer
information about the key or the plaintext, weakening the encryption.  The
higher the bandwidth of the encryption engine, the more vulnerable the key is
to wear-out.  The MKTME memory encryption hardware works at the speed of the
memory bus, which has high bandwidth.

Such a weakness has been demonstrated[3] on a theoretical cipher with similar
properties as AES-XTS.

An attack would take the following steps:
 * Victim system is using TME with AES-XTS-128
 * Attacker repeatedly captures ciphertext/plaintext pairs (can be
   Performed with online hardware attack like an interposer).
 * Attacker compels repeated use of the key under attack for a
   sustained time period without a system reboot[4].
 * Attacker discovers a cipertext collision (two plaintexts
   translating to the same ciphertext)
 * Attacker can induce controlled modifications to the targeted
   plaintext by modifying the colliding ciphertext

MKTME mitigates key wear-out in two ways:
 * Keys can be rotated periodically to mitigate wear-out.  Since TME
   keys are generated at boot, rotation of TME keys requires a
   reboot.  In contrast, MKTME allows rotation while the system is
   booted.  An application could implement a policy to rotate keys at
   a frequency which is not feasible to attack.
 * In the case that MKTME is used to encrypt two guests’ memory with
   two different keys, an attack on one guest’s key would not weaken
   the key used in the second guest.
---

[1] https://software.intel.com/sites/default/files/managed/a5/16/Multi-Key-Total-Memory-Encryption-Spec.pdf
[2] The MKTME architecture supports up to 16 bits of KeyIDs, so a
    maximum of 65535 keys on top of the “TME key” at KeyID-0.  The
    first implementation is expected to support 5 bits, making 63 keys
    available to applications.  However, this is not guaranteed.  The
    number of available keys could be reduced if, for instance,
    additional physical address space is desired over additional
    KeyIDs.
[3] http://web.cs.ucdavis.edu/~rogaway/papers/offsets.pdf
[4] This sustained time required for an attack could vary from days
    to years depending on the attacker’s goals.

Alison Schofield (33):
  x86/pconfig: Set a valid encryption algorithm for all MKTME commands
  keys/mktme: Introduce a Kernel Key Service for MKTME
  keys/mktme: Preparse the MKTME key payload
  keys/mktme: Instantiate and destroy MKTME keys
  keys/mktme: Move the MKTME payload into a cache aligned structure
  keys/mktme: Strengthen the entropy of CPU generated MKTME keys
  keys/mktme: Set up PCONFIG programming targets for MKTME keys
  keys/mktme: Program MKTME keys into the platform hardware
  keys/mktme: Set up a percpu_ref_count for MKTME keys
  keys/mktme: Require CAP_SYS_RESOURCE capability for MKTME keys
  keys/mktme: Store MKTME payloads if cmdline parameter allows
  acpi: Remove __init from acpi table parsing functions
  acpi/hmat: Determine existence of an ACPI HMAT
  keys/mktme: Require ACPI HMAT to register the MKTME Key Service
  acpi/hmat: Evaluate topology presented in ACPI HMAT for MKTME
  keys/mktme: Do not allow key creation in unsafe topologies
  keys/mktme: Support CPU hotplug for MKTME key service
  keys/mktme: Find new PCONFIG targets during memory hotplug
  keys/mktme: Program new PCONFIG targets with MKTME keys
  keys/mktme: Support memory hotplug for MKTME keys
  mm: Generalize the mprotect implementation to support extensions
  syscall/x86: Wire up a system call for MKTME encryption keys
  x86/mm: Set KeyIDs in encrypted VMAs for MKTME
  mm: Add the encrypt_mprotect() system call for MKTME
  x86/mm: Keep reference counts on encrypted VMAs for MKTME
  mm: Restrict MKTME memory encryption to anonymous VMAs
  selftests/x86/mktme: Test the MKTME APIs
  x86/mktme: Overview of Multi-Key Total Memory Encryption
  x86/mktme: Document the MKTME provided security mitigations
  x86/mktme: Document the MKTME kernel configuration requirements
  x86/mktme: Document the MKTME Key Service API
  x86/mktme: Document the MKTME API for anonymous memory encryption
  x86/mktme: Demonstration program using the MKTME APIs

Jacob Pan (3):
  iommu/vt-d: Support MKTME in DMA remapping
  x86/mm: introduce common code for mem encryption
  x86/mm: Use common code for DMA memory encryption

Kai Huang (2):
  mm, x86: export several MKTME variables
  kvm, x86, mmu: setup MKTME keyID to spte for given PFN

Kirill A. Shutemov (24):
  mm: Do no merge VMAs with different encryption KeyIDs
  mm: Add helpers to setup zero page mappings
  mm/ksm: Do not merge pages with different KeyIDs
  mm/page_alloc: Unify alloc_hugepage_vma()
  mm/page_alloc: Handle allocation for encrypted memory
  mm/khugepaged: Handle encrypted pages
  x86/mm: Mask out KeyID bits from page table entry pfn
  x86/mm: Introduce variables to store number, shift and mask of KeyIDs
  x86/mm: Preserve KeyID on pte_modify() and pgprot_modify()
  x86/mm: Detect MKTME early
  x86/mm: Add a helper to retrieve KeyID for a page
  x86/mm: Add a helper to retrieve KeyID for a VMA
  x86/mm: Add hooks to allocate and free encrypted pages
  x86/mm: Map zero pages into encrypted mappings correctly
  x86/mm: Rename CONFIG_RANDOMIZE_MEMORY_PHYSICAL_PADDING
  x86/mm: Allow to disable MKTME after enumeration
  x86/mm: Calculate direct mapping size
  x86/mm: Implement syncing per-KeyID direct mappings
  x86/mm: Handle encrypted memory in page_to_virt() and __pa()
  mm/page_ext: Export lookup_page_ext() symbol
  mm/rmap: Clear vma->anon_vma on unlink_anon_vmas()
  x86/mm: Disable MKTME on incompatible platform configurations
  x86/mm: Disable MKTME if not all system memory supports encryption
  x86: Introduce CONFIG_X86_INTEL_MKTME

 .../admin-guide/kernel-parameters.rst         |   1 +
 .../admin-guide/kernel-parameters.txt         |  11 +
 Documentation/x86/mktme/index.rst             |  13 +
 .../x86/mktme/mktme_configuration.rst         |  17 +
 Documentation/x86/mktme/mktme_demo.rst        |  53 ++
 Documentation/x86/mktme/mktme_encrypt.rst     |  57 ++
 Documentation/x86/mktme/mktme_keys.rst        |  96 +++
 Documentation/x86/mktme/mktme_mitigations.rst | 150 ++++
 Documentation/x86/mktme/mktme_overview.rst    |  57 ++
 Documentation/x86/x86_64/mm.txt               |   4 +
 arch/alpha/include/asm/page.h                 |   2 +-
 arch/x86/Kconfig                              |  29 +-
 arch/x86/entry/syscalls/syscall_32.tbl        |   1 +
 arch/x86/entry/syscalls/syscall_64.tbl        |   1 +
 arch/x86/include/asm/intel-family.h           |   2 +
 arch/x86/include/asm/intel_pconfig.h          |  14 +-
 arch/x86/include/asm/mem_encrypt.h            |  29 +
 arch/x86/include/asm/mktme.h                  |  93 +++
 arch/x86/include/asm/page.h                   |   4 +
 arch/x86/include/asm/page_32.h                |   1 +
 arch/x86/include/asm/page_64.h                |   4 +-
 arch/x86/include/asm/pgtable.h                |  19 +
 arch/x86/include/asm/pgtable_types.h          |  23 +-
 arch/x86/include/asm/setup.h                  |   6 +
 arch/x86/kernel/cpu/intel.c                   |  58 +-
 arch/x86/kernel/head64.c                      |   4 +
 arch/x86/kernel/setup.c                       |   3 +
 arch/x86/kvm/mmu.c                            |  18 +-
 arch/x86/mm/Makefile                          |   3 +
 arch/x86/mm/init_64.c                         |  68 ++
 arch/x86/mm/kaslr.c                           |  11 +-
 arch/x86/mm/mem_encrypt_common.c              |  28 +
 arch/x86/mm/mktme.c                           | 630 ++++++++++++++
 drivers/acpi/hmat/hmat.c                      |  67 ++
 drivers/acpi/tables.c                         |  10 +-
 drivers/firmware/efi/efi.c                    |  25 +-
 drivers/iommu/intel-iommu.c                   |  29 +-
 fs/dax.c                                      |   3 +-
 fs/exec.c                                     |   4 +-
 fs/userfaultfd.c                              |   7 +-
 include/asm-generic/pgtable.h                 |   8 +
 include/keys/mktme-type.h                     |  39 +
 include/linux/acpi.h                          |   9 +-
 include/linux/dma-direct.h                    |   4 +-
 include/linux/efi.h                           |   1 +
 include/linux/gfp.h                           |  51 +-
 include/linux/intel-iommu.h                   |   9 +-
 include/linux/mem_encrypt.h                   |  23 +-
 include/linux/migrate.h                       |  14 +-
 include/linux/mm.h                            |  27 +-
 include/linux/page_ext.h                      |  11 +-
 include/linux/syscalls.h                      |   2 +
 include/uapi/asm-generic/unistd.h             |   4 +-
 kernel/fork.c                                 |   2 +
 kernel/sys_ni.c                               |   2 +
 mm/compaction.c                               |   3 +
 mm/huge_memory.c                              |   6 +-
 mm/khugepaged.c                               |  10 +
 mm/ksm.c                                      |  17 +
 mm/madvise.c                                  |   2 +-
 mm/memory.c                                   |   3 +-
 mm/mempolicy.c                                |  30 +-
 mm/migrate.c                                  |   4 +-
 mm/mlock.c                                    |   2 +-
 mm/mmap.c                                     |  31 +-
 mm/mprotect.c                                 |  98 ++-
 mm/page_alloc.c                               |  50 ++
 mm/page_ext.c                                 |   5 +
 mm/rmap.c                                     |   4 +-
 mm/userfaultfd.c                              |   3 +-
 security/keys/Makefile                        |   1 +
 security/keys/mktme_keys.c                    | 768 ++++++++++++++++++
 .../selftests/x86/mktme/encrypt_tests.c       | 433 ++++++++++
 .../testing/selftests/x86/mktme/flow_tests.c  | 266 ++++++
 tools/testing/selftests/x86/mktme/key_tests.c | 526 ++++++++++++
 .../testing/selftests/x86/mktme/mktme_test.c  | 300 +++++++
 76 files changed, 4301 insertions(+), 122 deletions(-)
 create mode 100644 Documentation/x86/mktme/index.rst
 create mode 100644 Documentation/x86/mktme/mktme_configuration.rst
 create mode 100644 Documentation/x86/mktme/mktme_demo.rst
 create mode 100644 Documentation/x86/mktme/mktme_encrypt.rst
 create mode 100644 Documentation/x86/mktme/mktme_keys.rst
 create mode 100644 Documentation/x86/mktme/mktme_mitigations.rst
 create mode 100644 Documentation/x86/mktme/mktme_overview.rst
 create mode 100644 arch/x86/include/asm/mktme.h
 create mode 100644 arch/x86/mm/mem_encrypt_common.c
 create mode 100644 arch/x86/mm/mktme.c
 create mode 100644 include/keys/mktme-type.h
 create mode 100644 security/keys/mktme_keys.c
 create mode 100644 tools/testing/selftests/x86/mktme/encrypt_tests.c
 create mode 100644 tools/testing/selftests/x86/mktme/flow_tests.c
 create mode 100644 tools/testing/selftests/x86/mktme/key_tests.c
 create mode 100644 tools/testing/selftests/x86/mktme/mktme_test.c
```
#### [kvm-unit-tests PATCH 0/2] x86: nVMX: Fix NMI/INTR-window tests
##### From: Nadav Amit <nadav.amit@gmail.com>
X-Google-Original-From: Nadav Amit <namit@vmware.com>
From: Nadav Amit <nadav.amit@gmail.com>

```c

From: Nadav Amit <nadav.amit@gmail.com>

The NMI/INTR-window test in VMX have a couple of bugs. The first bug is
clearly a test issue (and a KVM bug), and is fixed by the first patch.

The second bug is more interesting, and looks as a silicon bug (or
documentation bug, as Intel likes to call them). The second patch just
ensures that a failure of the test would allow the next tests to run.

Cc: Jim Mattson <jmattson@google.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>

Nadav Amit (2):
  x86: nVMX: Use #DB in nmi and intr tests
  x86: nVMX: Set guest as active after NMI/INTR-window tests

 x86/vmx_tests.c | 74 +++++++++++++++++++++++++------------------------
 1 file changed, 38 insertions(+), 36 deletions(-)
```
