#### [PATCH kvmtool 1/6] rtc: Initialize the Register D for MC146818 RTC
##### From: Julien Thierry <julien.thierry@arm.com>

```c
From: Sami Mujawar <sami.mujawar@arm.com>

Some software drivers check the VRT bit (BIT7) of Register D before
using the MC146818 RTC. Initialized the VRT bit in rtc__init() to
indicate that the RAM and time contents are valid.

Signed-off-by: Sami Mujawar <sami.mujawar@arm.com>
Signed-off-by: Julien Thierry <julien.thierry@arm.com>
---
 hw/rtc.c | 8 ++++++++
 1 file changed, 8 insertions(+)

```
#### [PATCH kvmtool 01/13] ioeventfd: Fix removal of ioeventfd
##### From: Julien Thierry <julien.thierry@arm.com>

```c
From: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>

Fix three bugs that prevent removal of ioeventfds in KVM. Store the
flags in the right structure, check the datamatch parameter, and pass
the fd to KVM.

Signed-off-by: Jean-Philippe Brucker <jean-philippe.brucker@arm.com>
Signed-off-by: Julien Thierry <julien.thierry@arm.com>
---
 ioeventfd.c | 6 ++++--
 1 file changed, 4 insertions(+), 2 deletions(-)

```
#### [kvm-unit-tests PATCH 1/5] s390x: Make tests bootable from disk
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Currently tests are run with the --kernel option of Qemu, which will
load the ELF file and jump to the start address. When booting from
disk, we need to specify a start address. This is done by setting the
initial short PSW at 0x0.

For later compatibility with other hypervisors the short psw has 31
bit addressing specified.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 s390x/cstart64.S | 9 +++++++--
 s390x/flat.lds   | 8 +++++++-
 2 files changed, 14 insertions(+), 3 deletions(-)

```
#### [tip:core/rcu] drivers/vhost: Replace synchronize_rcu_bh() with synchronize_rcu()
##### From: "tip-bot for Paul E. McKenney" <tipbot@zytor.com>

```c
Commit-ID:  d05faa5f1ac50beef77b4ceba0e8e157d41146e2
Gitweb:     https://git.kernel.org/tip/d05faa5f1ac50beef77b4ceba0e8e157d41146e2
Author:     Paul E. McKenney <paulmck@linux.ibm.com>
AuthorDate: Mon, 5 Nov 2018 17:14:53 -0800
Committer:  Paul E. McKenney <paulmck@linux.ibm.com>
CommitDate: Tue, 27 Nov 2018 09:21:37 -0800

drivers/vhost: Replace synchronize_rcu_bh() with synchronize_rcu()

Now that synchronize_rcu() waits for bh-disable regions of code as well
as RCU read-side critical sections, synchronize_rcu_bh() can be replaced
by synchronize_rcu().  This commit therefore makes this change.

Signed-off-by: Paul E. McKenney <paulmck@linux.ibm.com>
Cc: "Michael S. Tsirkin" <mst@redhat.com>
Cc: Jason Wang <jasowang@redhat.com>
Cc: <kvm@vger.kernel.org>
Cc: <virtualization@lists.linux-foundation.org>
Cc: <netdev@vger.kernel.org>
---
 drivers/vhost/net.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [tip:x86/fpu] x86/fpu: Don't export __kernel_fpu_{begin,end}()Git-Commit-ID: 12209993e98c5fa1855c467f22a24e3d5b8be205
##### From: tip-bot for Sebastian Andrzej Siewior <tipbot@zytor.com>

```c
Commit-ID:  12209993e98c5fa1855c467f22a24e3d5b8be205
Gitweb:     https://git.kernel.org/tip/12209993e98c5fa1855c467f22a24e3d5b8be205
Author:     Sebastian Andrzej Siewior <bigeasy@linutronix.de>
AuthorDate: Thu, 29 Nov 2018 16:02:10 +0100
Committer:  Borislav Petkov <bp@suse.de>
CommitDate: Tue, 4 Dec 2018 12:37:28 +0100

x86/fpu: Don't export __kernel_fpu_{begin,end}()

There is one user of __kernel_fpu_begin() and before invoking it,
it invokes preempt_disable(). So it could invoke kernel_fpu_begin()
right away. The 32bit version of arch_efi_call_virt_setup() and
arch_efi_call_virt_teardown() does this already.

The comment above *kernel_fpu*() claims that before invoking
__kernel_fpu_begin() preemption should be disabled and that KVM is a
good example of doing it. Well, KVM doesn't do that since commit

  f775b13eedee2 ("x86,kvm: move qemu/guest FPU switching out to vcpu_run")

so it is not an example anymore.

With EFI gone as the last user of __kernel_fpu_{begin|end}(), both can
be made static and not exported anymore.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Reviewed-by: Rik van Riel <riel@surriel.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: "Jason A. Donenfeld" <Jason@zx2c4.com>
Cc: Andy Lutomirski <luto@kernel.org>
Cc: Ard Biesheuvel <ard.biesheuvel@linaro.org>
Cc: Dave Hansen <dave.hansen@linux.intel.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Nicolai Stange <nstange@suse.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: kvm ML <kvm@vger.kernel.org>
Cc: linux-efi <linux-efi@vger.kernel.org>
Cc: x86-ml <x86@kernel.org>
Link: https://lkml.kernel.org/r/20181129150210.2k4mawt37ow6c2vq@linutronix.de
---
 arch/x86/include/asm/efi.h     |  6 ++----
 arch/x86/include/asm/fpu/api.h | 15 +++++----------
 arch/x86/kernel/fpu/core.c     |  6 ++----
 3 files changed, 9 insertions(+), 18 deletions(-)

```
#### [PATCH v1 1/2] s390/setup: set control program code via diag 318
##### From: Collin Walling <walling@linux.ibm.com>

```c
The new s390x instruction, diagnose 318, sets the control program name 
code (CPNC) and control program version code (CPVC) to provide useful 
information regarding the OS during debugging. The CPNC is explicitly 
set to 4 to indicate a Linux/KVM environment.

The CPVC is a 7-byte value containing:

 - 3-byte Linux version code
 - 3-byte unique value, currently set to 0
 - 1-byte trailing null

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Heiko Carstens <heiko.carstens@de.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/include/asm/diag.h   | 12 ++++++++++++
 arch/s390/include/asm/sclp.h   |  1 +
 arch/s390/kernel/diag.c        |  1 +
 arch/s390/kernel/setup.c       | 21 +++++++++++++++++++++
 drivers/s390/char/sclp.h       |  4 +++-
 drivers/s390/char/sclp_early.c |  2 ++
 6 files changed, 40 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM nVMX: MSRs should not be stored if VM-entry fails during or after loading guest state
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
According to section "VM-entry Failures During or After Loading Guest State"
in Intel SDM vol 3C,

	"No MSRs are saved into the VM-exit MSR-store area."

when bit 31 of the exit reason is set.

Reported-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Suggested-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
Reviewed-by: Darren Kenny <darren.kenny@oracle.com>
---
 arch/x86/kvm/vmx.c | 17 +++++++++++++----
 1 file changed, 13 insertions(+), 4 deletions(-)

```
#### [PATCH V3]  kvm:x86 :remove unnecessary recalculate_apic_map
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
In the previous code, the variable apic_sw_disabled influences
recalculate_apic_map. But in "KVM: x86: simplify kvm_apic_map"
(commit:3b5a5ffa928a3f875b0d5dd284eeb7c322e1688a),
the access to apic_sw_disabled in recalculate_apic_map has been
deleted.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/lapic.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH v2 1/4] vhost/scsi: Respond to control queue operations
##### From: Bijan Mottahedeh <bijan.mottahedeh@oracle.com>

```c
The vhost-scsi driver currently does not handle any control queue
operations. In particular, vhost_scsi_ctl_handle_kick, merely prints out
a debug message but does nothing else. This can cause guest VMs to hang.

As part of SCSI recovery from an error, e.g., an I/O timeout, the SCSI
midlayer attempts to abort the failed operation. The SCSI virtio driver
translates the abort to a SCSI TMF request that gets put on the control
queue (virtscsi_abort -> virtscsi_tmf). The SCSI virtio driver then
waits indefinitely for this request to be completed, but it never will
because vhost-scsi never responds to that request.

To avoid a hang, always respond to control queue operations; explicitly
reject TMF requests, and return a no-op response to event requests.

Signed-off-by: Bijan Mottahedeh <bijan.mottahedeh@oracle.com>
---
 drivers/vhost/scsi.c | 190 +++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 190 insertions(+)

```
