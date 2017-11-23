

#### [PATCH v1 0/2] virtio-balloon: tweak config_changed
##### From: Wei Wang <wei.w.wang@intel.com>

```c

Since virtio-ccw doesn't work with accessing to the config registers
inside an interrupt context, this patch series avoids that issue by
moving the config register accesses to the related workqueue contexts.

Wei Wang (2):
  virtio-balloon: tweak config_changed implementation
  virtio-balloon: improve update_balloon_size_func

 drivers/virtio/virtio_balloon.c | 59 +++++++++++++++++++++--------------------
 1 file changed, 30 insertions(+), 29 deletions(-)
```
#### [kvm-unit-tests PATCH v4 00/13] 390x: Add cross hypervisor and disk
##### From: Janosch Frank <frankja@linux.ibm.com>

```c

With these patches kvm unit tests are now bootable under LPAR and
z/VM, as well as from KVM disks.

For this to work we added:
    * Initial PSW in lowcore
    * Switch to 64 bit and z/Arch
    * SCLP linemode console
    * Binary generation in Makefile


v4:
	* Added sigp header file
	* Moved clearing to xgr instead of lm
	* Minor renames, comment additions

v3:
	* Rebased on David's SCLP fixes
	* Added binary generation make command
	* Split up cleanup and sclp common movement
	* Fixed whitespace problems
	* Added more comments
	* Added linemode buffer to get rid of line splits

Janosch Frank (13):
  s390x: Add Sigp header file
  s390x: Rename and cleanup sclp-ascii.c
  s390x: Make tests bootable from disk
  s390x: Switch to z/Arch
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
 lib/s390x/asm/arch_def.h  |   1 +
 lib/s390x/asm/interrupt.h |   2 +
 lib/s390x/asm/sigp.h      |  60 +++++++++++++
 lib/s390x/interrupt.c     |  12 ++-
 lib/s390x/io.c            |  13 +--
 lib/s390x/sclp-ascii.c    |  68 --------------
 lib/s390x/sclp-console.c  | 222 ++++++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/sclp.c          |  75 +++++++++++++++-
 lib/s390x/sclp.h          |  74 +++++++++++++++-
 lib/s390x/time.c          |  18 ++++
 lib/s390x/time.h          | 108 ++++++++++++++++++++++
 s390x/Makefile            |  12 ++-
 s390x/cstart64.S          |  41 ++++++++-
 s390x/flat.lds            |  15 +++-
 16 files changed, 640 insertions(+), 92 deletions(-)
 create mode 100644 lib/s390x/asm/sigp.h
 delete mode 100644 lib/s390x/sclp-ascii.c
 create mode 100644 lib/s390x/sclp-console.c
 create mode 100644 lib/s390x/time.c
 create mode 100644 lib/s390x/time.h
```
