#### [PATCH v3 02/33] docs: arm64: convert docs to ReST and rename to .rst
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
 .../arm64/{memory.txt => memory.rst}          |  91 +++---
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
 23 files changed, 651 insertions(+), 427 deletions(-)
 rename Documentation/arm64/{acpi_object_usage.txt => acpi_object_usage.rst} (84%)
 rename Documentation/arm64/{arm-acpi.txt => arm-acpi.rst} (86%)
 rename Documentation/arm64/{booting.txt => booting.rst} (86%)
 rename Documentation/arm64/{cpu-feature-registers.txt => cpu-feature-registers.rst} (65%)
 rename Documentation/arm64/{elf_hwcaps.txt => elf_hwcaps.rst} (92%)
 rename Documentation/arm64/{hugetlbpage.txt => hugetlbpage.rst} (86%)
 create mode 100644 Documentation/arm64/index.rst
 rename Documentation/arm64/{legacy_instructions.txt => legacy_instructions.rst} (73%)
 rename Documentation/arm64/{memory.txt => memory.rst} (36%)
 rename Documentation/arm64/{pointer-authentication.txt => pointer-authentication.rst} (99%)
 rename Documentation/arm64/{silicon-errata.txt => silicon-errata.rst} (55%)
 rename Documentation/arm64/{sve.txt => sve.rst} (98%)
 rename Documentation/arm64/{tagged-pointers.txt => tagged-pointers.rst} (94%)

diff --git a/Documentation/arm64/acpi_object_usage.txt b/Documentation/arm64/acpi_object_usage.rst
similarity index 84%
rename from Documentation/arm64/acpi_object_usage.txt
```
