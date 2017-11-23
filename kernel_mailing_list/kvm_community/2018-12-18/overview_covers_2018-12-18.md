

#### [kvm-unit-tests PATCH v3 00/13] 390x: Add cross hypervisor and disk
##### From: Janosch Frank <frankja@linux.ibm.com>

```c

With these patches kvm unit tests are now bootable under LPAR and
z/VM, as well as from KVM disks.

For this to work we added:
    * Initial PSW in lowcore
    * Switch to 64 bit and z/Arch
    * SCLP linemode console
    * Binary generation in Makefile

Patches 8 - 13 are more or less RFCs.


v3:
	* Rebased on David's SCLP fixes
	* Added binary generation make command
	* Split up cleanup and sclp common movement
	* Fixed whitespace problems
	* Added more comments
	* Added linemode buffer to get rid of line splits

v2:
	* Moved cleanup to the front and broadened patch
	* Split up SCLP patch into interrupt and linemode
	* Removed unneeded instructions
	* Improved comments and commit messages


Janosch Frank (13):
  s390x: Add Sigp order codes
  s390x: Rename and cleanup sclp-ascii.c
  s390x: Make tests bootable from disk
  s390x: Switch to z/Arch if needed
  s390x: Add BSS clearing for non ELF boot
  s390x: Move common sclp data and functions to sclp.c
  s390x: Use interrupts in SCLP
  s390x: Add linemode console
  s390x: Add binary generation to makefile
  s390x: Add linemode buffer to fix newline on every print
  s390x: Add sclp busy indication locking
  s390x: Add time functions to lib
  lib/report: Add stamps to reports

 lib/libcflat.h            |   1 +
 lib/report.c              |  10 +++
 lib/s390x/asm/arch_def.h  |  19 ++++
 lib/s390x/asm/interrupt.h |   2 +
 lib/s390x/interrupt.c     |  12 ++-
 lib/s390x/io.c            |   5 +-
 lib/s390x/sclp-ascii.c    |  68 --------------
 lib/s390x/sclp-console.c  | 225 ++++++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/sclp.c          |  75 +++++++++++++++-
 lib/s390x/sclp.h          |  75 +++++++++++++++-
 lib/s390x/time.c          |  18 ++++
 lib/s390x/time.h          | 104 +++++++++++++++++++++
 s390x/Makefile            |  10 ++-
 s390x/cstart64.S          |  38 +++++++-
 s390x/flat.lds            |  15 +++-
 15 files changed, 596 insertions(+), 81 deletions(-)
 delete mode 100644 lib/s390x/sclp-ascii.c
 create mode 100644 lib/s390x/sclp-console.c
 create mode 100644 lib/s390x/time.c
 create mode 100644 lib/s390x/time.h
```
