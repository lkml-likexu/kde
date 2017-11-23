#### [Qemu-devel] [PATCH 1/1] hw/arm/virt: provide a model property in the fdt
##### From: Heinrich Schuchardt <xypron.glpk@gmx.de>

```c
Device trees in the Linux kernel generally provide a model property. Some
software like the Debian flash-kernel package rely on this property to
identify boards.

The patch sets the model property for the virt boards to 'QEMU virt'.

Signed-off-by: Heinrich Schuchardt <xypron.glpk@gmx.de>
---
 hw/arm/virt.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [Qemu-devel] [PATCH v7 01/19] block: implement bdrv_snapshot_goto for blkreplay
##### From: Pavel Dovgalyuk <Pavel.Dovgaluk@ispras.ru>

```c
From: Pavel Dovgalyuk <pavel.dovgaluk@ispras.ru>

This patch enables making snapshots with blkreplay used in
block devices.
This function is required to make bdrv_snapshot_goto without
calling .bdrv_open which is not implemented.

Signed-off-by: Pavel Dovgalyuk <pavel.dovgaluk@ispras.ru>
---
 block/blkreplay.c |    8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [Qemu-devel] [PATCH] ide: piix: convert constant device name to MACRO
##### From: Li Qiang <liq3ea@gmail.com>

```c
Signed-off-by: Li Qiang <liq3ea@gmail.com>
Reviewed-by: John Snow <jsnow@redhat.com>
Acked-by: John Snow <jsnow@redhat.com>
---
 hw/ide/piix.c | 16 ++++++++++------
 1 file changed, 10 insertions(+), 6 deletions(-)

```
#### [Qemu-devel] [PATCH v5 02/10] linux-user/strace: Display invalid pointer in print_timeval()
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Suggested-by: Laurent Vivier <laurent@vivier.eu>
Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
---
 linux-user/strace.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [Qemu-devel] [PATCH] machine: fix a typoX-BeenThere: qemu-devel@nongnu.org
##### From: Li Qiang <liq3ea@163.com>

```c
Cc: qemu-trivial@nongnu.org
Signed-off-by: Li Qiang <liq3ea@163.com>
Reviewed-by: Stefano Garzarella <stefanogarzarella@gmail.com>
---
 hw/core/machine.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [Qemu-devel] =?utf-8?q?=5BPATCH_1/2=5D_mailmap=3A_Fix_Reimar_D?=	=?utf-8?q?=C3=B6ffinger_name?=
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
This probably happened when interpreting the utf8 name as latin1.

Fixes dbbaaff6867 and f4e94dfefb6.

Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
---
 .mailmap | 3 ++-
 1 file changed, 2 insertions(+), 1 deletion(-)

```
#### [Qemu-devel] [PATCH v6 01/14] target/arm: Mark PMINTENCLR and PMINTENCLR_EL1 accesses as possibly doing IO
##### From: Aaron Lindsay <aclindsa@gmail.com>

```c
I previously fixed this for PMINTENSET_EL1, but missed these.

Signed-off-by: Aaron Lindsay <alindsay@codeaurora.org>
Signed-off-by: Aaron Lindsay <aclindsa@gmail.com>
---
 target/arm/helper.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [Qemu-devel] [PATCH 1/3] hw/pci-bridge/xio3130: Remove unused functions
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Introduced in 48ebf2f90f8 and faf1e708d5b, these functions
were never used. Remove them.

Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
---
 hw/pci-bridge/xio3130_downstream.h | 11 -----------
 hw/pci-bridge/xio3130_upstream.h   | 10 ----------
 hw/pci-bridge/xio3130_downstream.c | 28 +---------------------------
 hw/pci-bridge/xio3130_upstream.c   | 24 +-----------------------
 4 files changed, 2 insertions(+), 71 deletions(-)
 delete mode 100644 hw/pci-bridge/xio3130_downstream.h
 delete mode 100644 hw/pci-bridge/xio3130_upstream.h

diff --git a/hw/pci-bridge/xio3130_downstream.h b/hw/pci-bridge/xio3130_downstream.h
```
#### [Qemu-devel] [PULL 1/5] tests/check-qjson: fix a leakX-BeenThere: qemu-devel@nongnu.org
##### From: Markus Armbruster <armbru@redhat.com>

```c
From: Marc-André Lureau <marcandre.lureau@redhat.com>

Spotted by ASAN:

=================================================================
==11893==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 1120 byte(s) in 28 object(s) allocated from:
    #0 0x7fd0515b0c48 in malloc (/lib64/libasan.so.5+0xeec48)
    #1 0x7fd050ffa3c5 in g_malloc (/lib64/libglib-2.0.so.0+0x523c5)
    #2 0x559e708b56a4 in qstring_from_str /home/elmarco/src/qq/qobject/qstring.c:66
    #3 0x559e708b4fe0 in qstring_new /home/elmarco/src/qq/qobject/qstring.c:23
    #4 0x559e708bda7d in parse_string /home/elmarco/src/qq/qobject/json-parser.c:143
    #5 0x559e708c1009 in parse_literal /home/elmarco/src/qq/qobject/json-parser.c:484
    #6 0x559e708c1627 in parse_value /home/elmarco/src/qq/qobject/json-parser.c:547
    #7 0x559e708c1c67 in json_parser_parse /home/elmarco/src/qq/qobject/json-parser.c:573
    #8 0x559e708bc0ff in json_message_process_token /home/elmarco/src/qq/qobject/json-streamer.c:92
    #9 0x559e708d1655 in json_lexer_feed_char /home/elmarco/src/qq/qobject/json-lexer.c:292
    #10 0x559e708d1fe1 in json_lexer_feed /home/elmarco/src/qq/qobject/json-lexer.c:339
    #11 0x559e708bc856 in json_message_parser_feed /home/elmarco/src/qq/qobject/json-streamer.c:121
    #12 0x559e708b8b4b in qobject_from_jsonv /home/elmarco/src/qq/qobject/qjson.c:69
    #13 0x559e708b8d02 in qobject_from_json /home/elmarco/src/qq/qobject/qjson.c:83
    #14 0x559e708a74ae in from_json_str /home/elmarco/src/qq/tests/check-qjson.c:30
    #15 0x559e708a9f83 in utf8_string /home/elmarco/src/qq/tests/check-qjson.c:781
    #16 0x7fd05101bc49 in test_case_run gtestutils.c:2255
    #17 0x7fd05101bc49 in g_test_run_suite_internal gtestutils.c:2339

Signed-off-by: Marc-André Lureau <marcandre.lureau@redhat.com>
Message-Id: <20180901211917.10372-1-marcandre.lureau@redhat.com>
Reviewed-by: Markus Armbruster <armbru@redhat.com>
Signed-off-by: Markus Armbruster <armbru@redhat.com>
---
 tests/check-qjson.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [Qemu-devel] [PATCH RFC v5 1/7] Fix segmentation fault when qemu_signal_init fails
##### From: Fei Li <fli@suse.com>

```c
Currently, when qemu_signal_init() fails it only returns a non-zero
value but without propagating any Error. But its callers need a
non-null err when runs error_report_err(err), or else 0->msg occurs.

To avoid such segmentation fault, add a new Error parameter to make
the call trace to propagate the err to the final caller.

Signed-off-by: Fei Li <fli@suse.com>
Reviewed-by: Fam Zheng <famz@redhat.com>
---
 include/qemu/osdep.h | 2 +-
 util/compatfd.c      | 9 ++++++---
 util/main-loop.c     | 9 ++++-----
 3 files changed, 11 insertions(+), 9 deletions(-)

```
#### [Qemu-devel] [PATCH v11 2/6] s390x/cpumodel: Set up CPU model for AP device support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
A new CPU model feature and two new CPU model facilities are
introduced to support AP devices for a KVM guest.

CPU model features:

1. The S390_FEAT_AP CPU model feature indicates whether AP
   instructions are available to the guest. This feature will
   be enabled only if the AP instructions are available on the
   linux host as determined by the availability of the
   KVM_S390_VM_CRYPTO_ENABLE_APIE VM attribute which is exposed
   by KVM only if the AP instructions are available on the
   host.

   This feature must be turned on from userspace to execute AP
   instructions on the KVM guest. The QEMU command line to turn
   this feature on looks something like this:

	qemu-system-s390x ... -cpu xxx,ap=on ...

   This feature will be supported for zEC12 and newer CPU models.
   The feature will not be supported for older models because
   there are few older systems on which to test and the older
   crypto cards will be going out of service in the relatively
   near future.

CPU model facilities:

1. The S390_FEAT_AP_QUERY_CONFIG_INFO feature indicates whether the
   AP Query Configuration Information (QCI) facility is available
   to the guest as determined by whether the facility is available
   on the host. This feature will be exposed by KVM only if the
   QCI facility is installed on the host.

2. The S390_FEAT_AP_FACILITY_TEST feature indicates whether the AP
   Facility Test (APFT) facility is available to the guest as
   determined by whether the facility is available on the host.
   This feature will be exposed by KVM only if APFT is installed
   on the host.

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
Tested-by: Pierre Morel<pmorel@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 target/s390x/cpu_features.c     | 3 +++
 target/s390x/cpu_features_def.h | 3 +++
 target/s390x/cpu_models.c       | 2 ++
 target/s390x/gen-features.c     | 3 +++
 4 files changed, 11 insertions(+)

```
#### [Qemu-devel] [PATCH 1/4] tcg: access cpu->icount_decr.u16.high with atomics
##### From: "Emilio G. Cota" <cota@braap.org>

```c
Consistently access u16.high with atomics to avoid
undefined behaviour in MTTCG.

Note that icount_decr.u16.low is only used in icount mode,
so regular accesses to it are OK.

Reviewed-by: Richard Henderson <richard.henderson@linaro.org>
Signed-off-by: Emilio G. Cota <cota@braap.org>
---
 accel/tcg/tcg-all.c       | 2 +-
 accel/tcg/translate-all.c | 2 +-
 qom/cpu.c                 | 2 +-
 3 files changed, 3 insertions(+), 3 deletions(-)

```
#### [Qemu-devel] [PATCH v11 1/6] linux-headers: linux header updates for AP support
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Updates the linux header files in preparation for introduction
of the VFIO AP device:

* Added device attributes to the KVM_S390_VM_CRYPTO group
  to indicate whether AP instructions are to be interpreted

* Added VFIO device information for AP devices

Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 linux-headers/asm-s390/kvm.h | 2 ++
 linux-headers/linux/vfio.h   | 2 ++
 2 files changed, 4 insertions(+)

```
#### [Qemu-devel] [PATCH v2] target/cris/translate: Get rid of qemu_log_separate()
##### From: Thomas Huth <thuth@redhat.com>

```c
The gen_BUG() function calls already cpu_abort(), which prints the
information to stderr and the log already. So instead of additionally
printing the dc->pc via fprintf() and qemu_log here, too, we can
simply pass this information to cpu_abort() instead.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 v2: Use "pc=" instead of "dc->pc=" in the string as suggested by Phil

 target/cris/translate.c | 6 +-----
 1 file changed, 1 insertion(+), 5 deletions(-)

```
#### [Qemu-devel] [PATCH v3] python: Use io.StringIOX-BeenThere: qemu-devel@nongnu.org
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Both Python 2.7 and 3 support the same io.StringIO to
handle unicode strings.

Use the common form to use indistinctly Python 2.7 or 3.

http://python-future.org/compatible_idioms.html#stringio

This fixes running tests on the Fedora Docker image,
which uses Python3 since 356dc290f:

  $ make docker-test-block@fedora
  [...]
  045         [failed, exit status 1] - output mismatch (see 045.out.bad)
  --- /tmp/qemu-test/src/tests/qemu-iotests/045.out       2018-07-17 16:56:18.000000000 +0000
  +++ /tmp/qemu-test/build/tests/qemu-iotests/045.out.bad 2018-07-17 17:19:22.448409007 +0000
  @@ -1,5 +1,6 @@
  -...........
  -----------------------------------------------------------------------
  -Ran 11 tests
  -
  -OK
  +Traceback (most recent call last):
  +  File "045", line 178, in <module>
  +    iotests.main(supported_fmts=['raw'])
  +  File "/tmp/qemu-test/src/tests/qemu-iotests/iotests.py", line 682, in main
  +    import StringIO
  +ModuleNotFoundError: No module named 'StringIO'
  132         [failed, exit status 1] - output mismatch (see 132.out.bad)
  152         [failed, exit status 1] - output mismatch (see 152.out.bad)

  Failures: 045 132 152

Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
Reviewed-by: Paolo Bonzini <pbonzini@redhat.com>
---
 tests/qemu-iotests/iotests.py | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [Qemu-devel] [PATCH v5 01/10] linux-user/syscall: Verify recvfrom(addr) is user-writable
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <f4bug@amsat.org>

```c
Signed-off-by: Philippe Mathieu-Daudé <f4bug@amsat.org>
Tested-By: Guido Günther <agx@sigxcpu.org>
Reviewed-by: Laurent Vivier <laurent@vivier.eu>
---
 linux-user/syscall.c | 5 +++++
 1 file changed, 5 insertions(+)

```
