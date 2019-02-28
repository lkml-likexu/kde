#### [PATCH] kvm: properly check debugfs dentry before using it
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
debugfs can now report an error code if something went wrong instead of
just NULL.  So if the return value is to be used as a "real" dentry, it
needs to be checked if it is an error before dereferencing it.

This is now happening because of ff9fb72bc077 ("debugfs: return error
values, not NULL").  syzbot has found a way to trigger multiple debugfs
files attempting to be created, which fails, and then the error code
gets passed to dentry_path_raw() which obviously does not like it.

Reported-by: Eric Biggers <ebiggers@kernel.org>
Reported-and-tested-by: syzbot+7857962b4d45e602b8ad@syzkaller.appspotmail.com
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---

Paolo, this should be merged into 5.0-final, and if not there, then
5.1-rc1 and then backported to 5.0 through the stable tree.  If you
want me to send this to Linus, I will be glad to do so.

```
#### [PATCH] kvm: properly check debugfs dentry before using it
##### From: Greg Kroah-Hartman <gregkh@linuxfoundation.org>

```c
debugfs can now report an error code if something went wrong instead of
just NULL.  So if the return value is to be used as a "real" dentry, it
needs to be checked if it is an error before dereferencing it.

This is now happening because of ff9fb72bc077 ("debugfs: return error
values, not NULL").  syzbot has found a way to trigger multiple debugfs
files attempting to be created, which fails, and then the error code
gets passed to dentry_path_raw() which obviously does not like it.

Reported-by: Eric Biggers <ebiggers@kernel.org>
Reported-and-tested-by: syzbot+7857962b4d45e602b8ad@syzkaller.appspotmail.com
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: kvm@vger.kernel.org
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Greg Kroah-Hartman <gregkh@linuxfoundation.org>
---

Linus, this should go in before 5.0-final is out, as it resolves a
problem found by syzbot.  Paolo has given his ack for me to send this
directly to you.  If you want this in [GIT PULL] format, I can do that
as well.

 virt/kvm/kvm_main.c |    2 +-
```
#### [kvm-unit-tests PULL 1/5] powerpc: Enable HTM capability for h_cede_tm testcase
##### From: Thomas Huth <thuth@redhat.com>

```c
From: David Gibson <david@gibson.dropbear.id.au>

The h_cede_tm case is specifically about an edge case with the H_CEDE
hypercall while using hardware transactional memory (HTM).  Current qemu
versions don't enable HTM instructions in guests by default, so we should
explicitly enable them in order to execute this test.

Signed-off-by: David Gibson <david@gibson.dropbear.id.au>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 powerpc/unittests.cfg | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 1/3] s390x: Beautify sthyi report strings
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Tests like the register odd check in r1 and r2 were not
distinguishable and the reports were hard to read in total.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 s390x/sthyi.c | 52 ++++++++++++++++++++++++++++++++--------------------
 1 file changed, 32 insertions(+), 20 deletions(-)

```
#### [PATCH] vfio/pci: use correct format characters
##### From: Louis Taylor <louis@kragniz.eu>

```c
When compiling with -Wformat, clang emits the following warnings:

drivers/vfio/pci/vfio_pci.c:1601:5: warning: format specifies type
      'unsigned short' but the argument has type 'unsigned int' [-Wformat]
                                vendor, device, subvendor, subdevice,
                                ^~~~~~

drivers/vfio/pci/vfio_pci.c:1601:13: warning: format specifies type
      'unsigned short' but the argument has type 'unsigned int' [-Wformat]
                                vendor, device, subvendor, subdevice,
                                        ^~~~~~

drivers/vfio/pci/vfio_pci.c:1601:21: warning: format specifies type
      'unsigned short' but the argument has type 'unsigned int' [-Wformat]
                                vendor, device, subvendor, subdevice,
                                                ^~~~~~~~~

drivers/vfio/pci/vfio_pci.c:1601:32: warning: format specifies type
      'unsigned short' but the argument has type 'unsigned int' [-Wformat]
                                vendor, device, subvendor, subdevice,
                                                           ^~~~~~~~~

drivers/vfio/pci/vfio_pci.c:1605:5: warning: format specifies type
      'unsigned short' but the argument has type 'unsigned int' [-Wformat]
                                vendor, device, subvendor, subdevice,
                                ^~~~~~

drivers/vfio/pci/vfio_pci.c:1605:13: warning: format specifies type
      'unsigned short' but the argument has type 'unsigned int' [-Wformat]
                                vendor, device, subvendor, subdevice,
                                        ^~~~~~

drivers/vfio/pci/vfio_pci.c:1605:21: warning: format specifies type
      'unsigned short' but the argument has type 'unsigned int' [-Wformat]
                                vendor, device, subvendor, subdevice,
                                                ^~~~~~~~~

drivers/vfio/pci/vfio_pci.c:1605:32: warning: format specifies type
      'unsigned short' but the argument has type 'unsigned int' [-Wformat]
                                vendor, device, subvendor, subdevice,
                                                           ^~~~~~~~~
The types of these arguments are unconditionally defined, so this patch
updates the format character to the correct ones for unsigned ints.

Link: https://github.com/ClangBuiltLinux/linux/issues/378
Signed-off-by: Louis Taylor <louis@kragniz.eu>
Reviewed-by: Nick Desaulniers <ndesaulniers@google.com>
---
 drivers/vfio/pci/vfio_pci.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
