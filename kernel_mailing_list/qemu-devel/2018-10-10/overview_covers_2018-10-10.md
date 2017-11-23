

#### [Qemu-devel] [PATCH RFC v5 0/7] qemu_thread_create: propagate
##### From: Fei Li <fli@suse.com>
X-Received-From: 195.135.221.5

```c

Hi,

This idea comes from BiteSizedTasks, and this patch series implement
the error checking of qemu_thread_create: make qemu_thread_create
return a flag to indicate if it succeeded rather than failing with an
error; make all callers check it.

The first three patches apply to those call traces whose further
callers already have the *errp to pass, thus add a new Error paramater
in the call trace to propagate the error and let the further caller
check it. The last patch modifies the qemu_thread_create() and makes
it return a bool to all direct callers to indicate if it succeeds.
The middle three fix some segmentation fault when using GDB to debug.

###### Here I have a concern about using multifd migration. ######
It is about "[PATCH RFC v4 5/7] migration: fix the multifd code".
In our current code, when multifd is used during migration, if there
is an error before the destination receives all new channels (I mean
multifd_recv_new_channel(ioc)), the destination does not exit but
keeps waiting (Hang in recvmsg() in qio_channel_socket_readv) until
the source exits. I know hang is not right, but so sorry that I did
not come up with a good idea on handling this. Not so familiar with
that part of code.. Hope @Juan could give a hand. Thanks!

Please help to review, thanks. :)

v5:
- Remove `errno = err` in qemu_thread_create() for Linux, and change
  `return errno` to `return -1` in qemu_signal_init() to indicate
  the error in case qemu_thread_create() fails.
- Delete the v4-added qemu_cond/mutex_destroy() in iothread_complete()
  as the destroy() will be done by its callers' object_unref().

v4:
- Separate the migration compression patch from this series
- Add one more error handling patch related with migration
- Add more cleaning up code for touched functions

v3:
- Add two migration related patches to fix the segmentaion fault
- Extract the segmentation fault fix from v2's last patch to be a 
  separate patch
- Add cleaning up code for touched functions
- Update some error messages

v2:
- Pass errp straightly instead of using a local_err & error_propagate
- Return a bool: false/true to indicate if one function succeeds
- Merge v1's last two patches into one to avoid the compile error
- Fix one omitted error in patch1 and update some error messages

Fei Li (7):
  Fix segmentation fault when qemu_signal_init fails
  ui/vnc.c: polish vnc_init_func
  qemu_init_vcpu: add a new Error parameter to propagate
  qemu_thread_join: fix segmentation fault
  migration: fix the multifd code
  migration: fix some error handling
  qemu_thread_create: propagate the error to callers to handle

 accel/tcg/user-exec-stub.c      |  2 +-
 cpus.c                          | 79 ++++++++++++++++++++++++++---------------
 dump.c                          |  6 ++--
 hw/misc/edu.c                   |  6 ++--
 hw/ppc/spapr_hcall.c            | 10 ++++--
 hw/rdma/rdma_backend.c          |  4 ++-
 hw/usb/ccid-card-emulated.c     | 13 ++++---
 include/qemu/osdep.h            |  2 +-
 include/qemu/thread.h           |  4 +--
 include/qom/cpu.h               |  2 +-
 include/ui/console.h            |  2 +-
 io/task.c                       |  3 +-
 iothread.c                      | 16 ++++++---
 migration/migration.c           | 54 ++++++++++++++++++----------
 migration/postcopy-ram.c        | 17 +++++++--
 migration/ram.c                 | 68 ++++++++++++++++++++++++-----------
 migration/ram.h                 |  2 +-
 migration/savevm.c              | 11 ++++--
 target/alpha/cpu.c              |  4 ++-
 target/arm/cpu.c                |  4 ++-
 target/cris/cpu.c               |  4 ++-
 target/hppa/cpu.c               |  4 ++-
 target/i386/cpu.c               |  4 ++-
 target/lm32/cpu.c               |  4 ++-
 target/m68k/cpu.c               |  4 ++-
 target/microblaze/cpu.c         |  4 ++-
 target/mips/cpu.c               |  4 ++-
 target/moxie/cpu.c              |  4 ++-
 target/nios2/cpu.c              |  4 ++-
 target/openrisc/cpu.c           |  4 ++-
 target/ppc/translate_init.inc.c |  4 ++-
 target/riscv/cpu.c              |  4 ++-
 target/s390x/cpu.c              |  4 ++-
 target/sh4/cpu.c                |  4 ++-
 target/sparc/cpu.c              |  4 ++-
 target/tilegx/cpu.c             |  4 ++-
 target/tricore/cpu.c            |  4 ++-
 target/unicore32/cpu.c          |  4 ++-
 target/xtensa/cpu.c             |  4 ++-
 tests/atomic_add-bench.c        |  3 +-
 tests/iothread.c                |  2 +-
 tests/qht-bench.c               |  3 +-
 tests/rcutorture.c              |  3 +-
 tests/test-aio.c                |  2 +-
 tests/test-rcu-list.c           |  3 +-
 ui/vnc-jobs.c                   | 17 ++++++---
 ui/vnc-jobs.h                   |  2 +-
 ui/vnc.c                        | 12 +++++--
 util/compatfd.c                 | 18 +++++++---
 util/main-loop.c                | 11 +++---
 util/oslib-posix.c              | 17 ++++++---
 util/qemu-thread-posix.c        | 25 ++++++++-----
 util/qemu-thread-win32.c        | 18 +++++++---
 util/rcu.c                      |  3 +-
 util/thread-pool.c              |  4 ++-
 55 files changed, 366 insertions(+), 162 deletions(-)
```
#### [Qemu-devel] [PATCH v7 00/19] Fixing record/replay and adding
##### From: Pavel Dovgalyuk <Pavel.Dovgaluk@ispras.ru>
X-Received-From: 83.149.199.45

```c

GDB remote protocol supports reverse debugging of the targets.
It includes 'reverse step' and 'reverse continue' operations.
The first one finds the previous step of the execution,
and the second one is intended to stop at the last breakpoint that
would happen when the program is executed normally.

Reverse debugging is possible in the replay mode, when at least
one snapshot was created at the record or replay phase.
QEMU can use these snapshots for travelling back in time with GDB.

Running the execution in replay mode allows using GDB reverse debugging
commands:
 - reverse-stepi (or rsi): Steps one instruction to the past.
   QEMU loads on of the prior snapshots and proceeds to the desired
   instruction forward. When that step is reaches, execution stops.
 - reverse-continue (or rc): Runs execution "backwards".
   QEMU tries to find breakpoint or watchpoint by loaded prior snapshot
   and replaying the execution. Then QEMU loads snapshots again and
   replays to the latest breakpoint. When there are no breakpoints in
   the examined section of the execution, QEMU finds one more snapshot
   and tries again. After the first snapshot is processed, execution
   stops at this snapshot.

The set of patches include the following modifications:
 - gdbstub update for reverse debugging support
 - functions that automatically perform reverse step and reverse
   continue operations
 - hmp/qmp commands for manipulating the replay process
 - improvement of the snapshotting for saving the execution step
   in the snapshot parameters
 - other record/replay fixes

The patches are available in the repository:
https://github.com/ispras/qemu/tree/rr-181010

v7 changes:
 - rebased to the new master with upstreamed patches from the series
 - several improvements in hmp/qmp commands handling (suggested by Markus Armbruster)
 - fixed record/replay with '-rtc base' option enabled
 - added document with virtual hardware requirements

v6 changes:
 - rebased to the new version of master
 - fixed build of linux-user configurations
 - added new clock for slirp and vnc timers

v5 changes:
 - multiple fixes of record/replay bugs appeared after QEMU core update
 - changed reverse debugging to 'since 3.1'

v4 changes:
 - changed 'since 2.13' to 'since 3.0' in json (as suggested by Eric Blake)

v3 changes:
 - Fixed PS/2 bug with save/load vm, which caused failures of the replay.
 - Rebased to the new code base.
 - Minor fixes.

v2 changes:
 - documented reverse debugging
 - fixed start vmstate loading in record mode
 - documented qcow2 changes (as suggested by Eric Blake)
 - made icount SnapshotInfo field optional (as suggested by Eric Blake)
 - renamed qmp commands (as suggested by Eric Blake)
 - minor changes
---

Pavel Dovgalyuk (19):
      block: implement bdrv_snapshot_goto for blkreplay
      replay: disable default snapshot for record/replay
      replay: update docs for record/replay with block devices
      replay: don't drain/flush bdrv queue while RR is working
      replay: finish record/replay before closing the disks
      qcow2: introduce icount field for snapshots
      migration: introduce icount field for snapshots
      replay: provide and accessor for rr filename
      replay: introduce info hmp/qmp command
      replay: introduce breakpoint at the specified step
      replay: implement replay-seek command to proceed to the desired step
      replay: refine replay-time module
      replay: flush rr queue before loading the vmstate
      gdbstub: add reverse step support in replay mode
      gdbstub: add reverse continue support in replay mode
      replay: describe reverse debugging in docs/replay.txt
      replay: add BH oneshot event for block layer
      replay: init rtc after enabling the replay
      replay: document development rules


 accel/tcg/translator.c    |    1 
 block/blkreplay.c         |    8 +
 block/block-backend.c     |    3 
 block/io.c                |   22 +++
 block/qapi.c              |   17 ++
 block/qcow2-snapshot.c    |    9 +
 block/qcow2.h             |    2 
 blockdev.c                |   10 +
 cpus.c                    |   19 ++-
 docs/devel/replay.txt     |   45 ++++++
 docs/interop/qcow2.txt    |    4 +
 docs/replay.txt           |   45 ++++++
 exec.c                    |    6 +
 gdbstub.c                 |   50 +++++++
 hmp-commands-info.hx      |   14 ++
 hmp-commands.hx           |   44 ++++++
 hmp.h                     |    4 +
 include/block/snapshot.h  |    1 
 include/sysemu/replay.h   |   20 +++
 migration/savevm.c        |   15 +-
 qapi/block-core.json      |    7 +
 qapi/block.json           |    3 
 qapi/misc.json            |   77 +++++++++++
 replay/Makefile.objs      |    3 
 replay/replay-debugging.c |  319 +++++++++++++++++++++++++++++++++++++++++++++
 replay/replay-events.c    |   16 ++
 replay/replay-internal.h  |    7 +
 replay/replay-time.c      |   32 ++---
 replay/replay.c           |   26 ++++
 stubs/Makefile.objs       |    1 
 stubs/replay-user.c       |    9 +
 stubs/replay.c            |   10 +
 vl.c                      |   22 ++-
 33 files changed, 818 insertions(+), 53 deletions(-)
 create mode 100644 docs/devel/replay.txt
 create mode 100644 replay/replay-debugging.c
 create mode 100644 stubs/replay-user.c
```
#### [Qemu-devel] [PATCH 0/4] some TCG fixes
##### From: "Emilio G. Cota" <cota@braap.org>
X-Received-From: 66.111.4.27

```c

The first patch we've seen before -- I'm taking it from the
atomic interrupt_request series.

The other three patches are related to TCG profiling. One
of them is a build fix that I suspect has gone unnoticed
due to its dependence on CONFIG_PROFILER.

The series is checkpatch-clean. You can fetch it from:
  https://github.com/cota/qemu/tree/tcg-profile

Thanks,

		Emilio
```
#### [Qemu-devel] [PATCH v11 0/6] s390x: vfio-ap: guest dedicated crypto
##### From: Tony Krowiak <akrowiak@linux.ibm.com>
X-Received-From: 148.163.156.1

```c

This patch series is the QEMU counterpart to the KVM/kernel support for 
guest dedicated crypto adapters. The KVM/kernel model is built on the 
VFIO mediated device framework and provides the infrastructure for 
granting exclusive guest access to crypto devices installed on the linux 
host. This patch series introduces a new QEMU command line option, QEMU 
object model and CPU model features to exploit the KVM/kernel model.

See the detailed specifications for AP virtualization provided by this 
patch set in docs/vfio-ap.txt for a more complete discussion of the 
design introduced by this patch series.

v10 => v11 Change log:
=====================
* Replaced DO_UPCAST macros in ap.c
* Initializing GError in vfio_ap_get_group() function (BUG)
* Updated s390 maintainers with new files in MAINTAINERS
* Fixed memory leak in vfio_ap_get_group() function

v9 => v10 Change log:
====================
* Removed KVM_S390_VM_CPU_FEAT_AP feature from kvm.h
* Moved check for KVM_S390_VM_CRYPTO_ENABLE_APIE from patch 2/6 to patch
  3/6
* Removed vfio from all function names in ap-bridge.c 
* Removed unused macros and structure from ap-bridge.h
* Removed unused macros from ap-device.h

v8 => v9 Change log:
===================
* Removed all references to VFIO in AP bridge and bus
* Expose AP feature only if the KVM_S390_VM_CRYPTO_ENABLE_APIE VM attribute
  is exposed by KVM - i.e., if AP instructions are available on the linux
  host.
* Enable AP interpretation only if AP feature is switched on; no need to
  disable because it is disabled by default.

v7 => v8 Change log:
===================
* Enable SIE interpretation AP instructions if the CPU model feature for
  AP instructions is turned on for the guest.

v6 => v7 Change log;
===================
* Changed email address for Signed-off-by

v5 => v6 Change log:
===================
* Added reset handling fo vfio-ap device
* Added a bridge/bus to AP device object model - thanks to Halil Pasic

v4 => v5 Change log:
===================
* Added MAINTAINERS entries for VFIO AP
* Added explanation for why we are only supporting zEC12 and newer CPU 
  models.
* Changed CPU model feature qci=on|off to apqci=on|off
* Misc. minor changes

v3 => v4 Change log:
===================
* Made vfio-ap device unpluggable for now
* Renamed command line CPU model feature for QCI: qci=on -> apqci=on
* Removed call to KVM_S390_VM_CRYPTO_INTERPRET_AP ioctl - ioctl was 
  removed from kernel and AP instruction interpretation is set from the
  VFIO device driver
* Added check to ensure only one vfio-ap device can be configured per 
  guest
* Removed AP instruction interception handlers: AP instructions will be 
  interpreted by default if AP facilities are installed to handle the case
  where feature ap=on and no vfio-ap device is configured for the guest.


Tony Krowiak (6):
  linux-headers: linux header updates for AP support
  s390x/cpumodel: Set up CPU model for AP device support
  s390x/kvm: enable AP instruction interpretation for guest
  s390x/ap: base Adjunct Processor (AP) object model
  s390x/vfio: ap: Introduce VFIO AP device
  s390: doc: detailed specifications for AP virtualization

 MAINTAINERS                       |  16 +
 default-configs/s390x-softmmu.mak |   1 +
 docs/vfio-ap.txt                  | 825 ++++++++++++++++++++++++++++++
 hw/s390x/Makefile.objs            |   2 +
 hw/s390x/ap-bridge.c              |  78 +++
 hw/s390x/ap-device.c              |  38 ++
 hw/s390x/s390-virtio-ccw.c        |   4 +
 hw/vfio/Makefile.objs             |   1 +
 hw/vfio/ap.c                      | 179 +++++++
 include/hw/s390x/ap-bridge.h      |  19 +
 include/hw/s390x/ap-device.h      |  22 +
 include/hw/vfio/vfio-common.h     |   1 +
 linux-headers/asm-s390/kvm.h      |   2 +
 linux-headers/linux/vfio.h        |   2 +
 target/s390x/cpu_features.c       |   3 +
 target/s390x/cpu_features_def.h   |   3 +
 target/s390x/cpu_models.c         |   2 +
 target/s390x/gen-features.c       |   3 +
 target/s390x/kvm.c                |  19 +
 19 files changed, 1220 insertions(+)
 create mode 100644 docs/vfio-ap.txt
 create mode 100644 hw/s390x/ap-bridge.c
 create mode 100644 hw/s390x/ap-device.c
 create mode 100644 hw/vfio/ap.c
 create mode 100644 include/hw/s390x/ap-bridge.h
 create mode 100644 include/hw/s390x/ap-device.h
```
#### [Qemu-devel] [PATCH v6 00/14] More fully implement ARM PMUv3
##### From: Aaron Lindsay <aclindsa@gmail.com>
X-Received-From: 2607:f8b0:4864:20::c43

```c

The ARM PMU implementation currently contains a basic cycle counter, but
it is often useful to gather counts of other events, filter them based
on execution mode, and/or be notified on counter overflow. These patches
flesh out the implementations of various PMU registers including
PM[X]EVCNTR and PM[X]EVTYPER, add a struct definition to represent
arbitrary counter types, implement mode filtering, send interrupts on
counter overflow, and add instruction, cycle, and software increment
events.

Since v5 [1] I have:
* Taken a first pass at addressing migration
* Restructured the list of supported events, and ensured they're all
  initialized 
* Fixed aliasing for PMOVSSET
* Added ARM_CP_IO for PMINTENCLR and PMINTENCLR_EL1
* Addressed a few non-code issues (comment style, patch staging,
  spelling, etc.)

[1] - https://lists.gnu.org/archive/html/qemu-devel/2018-06/msg06830.html

Aaron Lindsay (14):
  target/arm: Mark PMINTENCLR and PMINTENCLR_EL1 accesses as possibly
    doing IO
  target/arm: Mask PMOVSR writes based on supported counters
  migration: Add post_save function to VMStateDescription
  target/arm: Swap PMU values before/after migrations
  target/arm: Reorganize PMCCNTR accesses
  target/arm: Filter cycle counter based on PMCCFILTR_EL0
  target/arm: Allow AArch32 access for PMCCFILTR
  target/arm: Implement PMOVSSET
  target/arm: Add array for supported PMU events, generate PMCEID[01]
  target/arm: Finish implementation of PM[X]EVCNTR and PM[X]EVTYPER
  target/arm: PMU: Add instruction and cycle events
  target/arm: PMU: Set PMCR.N to 4
  target/arm: Implement PMSWINC
  target/arm: Send interrupts on PMU counter overflow

 docs/devel/migration.rst    |   9 +-
 include/migration/vmstate.h |   1 +
 migration/vmstate.c         |  10 +-
 target/arm/cpu.c            |  28 +-
 target/arm/cpu.h            |  68 +++-
 target/arm/cpu64.c          |   2 -
 target/arm/helper.c         | 781 ++++++++++++++++++++++++++++++++----
 target/arm/machine.c        |  19 +
 8 files changed, 817 insertions(+), 101 deletions(-)
```
#### [Qemu-devel] [PATCH 0/3] pci: Add missing include and remove
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
X-Received-From: 2a00:1450:4864:20::32a

```c

Hi Michael, these are obvious cleanups patches.

I might ressurect David's old series later:
https://lists.gnu.org/archive/html/qemu-devel/2017-11/msg05277.html

Regards,

Phil.

Philippe Mathieu-Daudé (3):
  hw/pci-bridge/xio3130: Remove unused functions
  hw/pci-bridge/ioh3420: Remove unuseful header
  hw/pci: Add missing include

 hw/pci-bridge/ioh3420.h            |  6 ------
 hw/pci-bridge/xio3130_downstream.h | 11 -----------
 hw/pci-bridge/xio3130_upstream.h   | 10 ----------
 include/hw/pci/pci_bus.h           |  2 ++
 hw/pci-bridge/ioh3420.c            |  2 +-
 hw/pci-bridge/xio3130_downstream.c | 28 +---------------------------
 hw/pci-bridge/xio3130_upstream.c   | 24 +-----------------------
 7 files changed, 5 insertions(+), 78 deletions(-)
 delete mode 100644 hw/pci-bridge/ioh3420.h
 delete mode 100644 hw/pci-bridge/xio3130_downstream.h
 delete mode 100644 hw/pci-bridge/xio3130_upstream.h
```
#### [Qemu-devel] [PATCH 0/2] mailmap: Sort and clean an utf8 encoding
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
X-Received-From: 2a00:1450:4864:20::335

```c

Hi,

This amazing series sort a bit the mailmap sections,
then fix Reimar Döffinger name from 2 missed commits.

Regards,

Phil.

Philippe Mathieu-Daudé (2):
  mailmap: Fix Reimar Döffinger name
  mailmap: Split 'prefered emails' from 'original git import' section

 .mailmap | 24 +++++++++++++++---------
 1 file changed, 15 insertions(+), 9 deletions(-)
```
#### [Qemu-devel] [PATCH v5 00/10] linux-user: strace improvements
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>
X-Received-From: 2a00:1450:4864:20::444

```c

Hi Laurent,

Few patches I'v been writting while trying to figure out this issue:
http://lists.nongnu.org/archive/html/qemu-arm/2018-01/msg00514.html

As usual with linux-user files, this series will trigger some checkpatch
benign warnings.

Regards,

Phil.

Since v4:
- rebased on master (no change)

Since v3:
- addressed Laurent comments
- added print_sockfd()
- removed the print_sockaddr_ptr() patch, also the two
  getsockname()/recvfrom() patches for after 3.0.

Since v2:
- display invalid pointer in print_timeval() and print_timezone()
- do not display gettimeofday() arguments

Since v1:
- addressed Laurent comments
- added 'last' argument to print_sockaddr()
- reordered series, so patches already correct can get applied directly
- dropped "linux-user/syscall: simplify recvfrom()" for now

v1: http://lists.nongnu.org/archive/html/qemu-devel/2018-01/msg05855.html
v2: http://lists.nongnu.org/archive/html/qemu-devel/2018-06/msg08216.html
v3: http://lists.nongnu.org/archive/html/qemu-devel/2018-07/msg00411.html

$ git backport-diff
[----] : patches are identical
[####] : number of functional differences between upstream/downstream patch
[down] : patch is downstream-only
The flags [FC] indicate (F)unctional and (C)ontextual differences, respectively

001/12:[----] [--] 'linux-user/syscall: Verify recvfrom(addr) is user-writable'
002/12:[----] [--] 'linux-user/strace: Improve capget()/capset() output'
003/12:[0002] [FC] 'linux-user/strace: Display invalid pointer in print_timeval()'
004/12:[0002] [FC] 'linux-user/strace: Add print_timezone()'
005/12:[----] [--] 'linux-user/strace: Improve settimeofday()'
006/12:[down] 'linux-user/syscall: Introduce target_sockaddr_nl'
007/12:[0018] [FC] 'linux-user/strace: Dump AF_NETLINK sockaddr content'
008/12:[----] [--] 'linux-user/strace: Improve recvmsg() output'
009/12:[down] 'linux-user/strace: Add print_sockfd()'
010/12:[0004] [FC] 'linux-user/strace: Let print_sockaddr() have a 'last' argument'
011/12:[0004] [FC] 'linux-user/strace: Improve bind() output'
012/12:[0004] [FC] 'linux-user/strace: improve sendto() output'

Philippe Mathieu-Daudé (10):
  linux-user/syscall: Verify recvfrom(addr) is user-writable
  linux-user/strace: Display invalid pointer in print_timeval()
  linux-user/strace: Add print_timezone()
  linux-user/strace: Improve settimeofday()
  linux-user/syscall: Introduce target_sockaddr_nl
  linux-user/strace: Dump AF_NETLINK sockaddr content
  linux-user/strace: Add print_sockfd()
  linux-user/strace: Let print_sockaddr() have a 'last' argument
  linux-user/strace: Improve bind() output
  linux-user/strace: improve sendto() output

 linux-user/syscall_defs.h |   7 ++
 linux-user/strace.c       | 133 ++++++++++++++++++++++++++++++++++----
 linux-user/syscall.c      |  11 +++-
 linux-user/strace.list    |   6 +-
 4 files changed, 139 insertions(+), 18 deletions(-)
```
