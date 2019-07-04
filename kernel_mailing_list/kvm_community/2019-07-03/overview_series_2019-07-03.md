#### [tip:timers/core] clocksource/drivers: Make Hyper-V clocksource ISA agnostic
##### From: tip-bot for Michael Kelley <tipbot@zytor.com>

```c
Commit-ID:  fd1fea6834d0f9f93062ae6685862908a9baed39
Gitweb:     https://git.kernel.org/tip/fd1fea6834d0f9f93062ae6685862908a9baed39
Author:     Michael Kelley <mikelley@microsoft.com>
AuthorDate: Mon, 1 Jul 2019 04:25:56 +0000
Committer:  Thomas Gleixner <tglx@linutronix.de>
CommitDate: Wed, 3 Jul 2019 11:00:59 +0200

clocksource/drivers: Make Hyper-V clocksource ISA agnostic

Hyper-V clock/timer code and data structures are currently mixed
in with other code in the ISA independent drivers/hv directory as
well as the ISA dependent Hyper-V code under arch/x86.

Consolidate this code and data structures into a Hyper-V clocksource driver
to better follow the Linux model. In doing so, separate out the ISA
dependent portions so the new clocksource driver works for x86 and for the
in-process Hyper-V on ARM64 code.

To start, move the existing clockevents code to create the new clocksource
driver. Update the VMbus driver to call initialization and cleanup routines
since the Hyper-V synthetic timers are not independently enumerated in
ACPI.

No behavior is changed and no new functionality is added.

Suggested-by: Marc Zyngier <marc.zyngier@arm.com>
Signed-off-by: Michael Kelley <mikelley@microsoft.com>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: "bp@alien8.de" <bp@alien8.de>
Cc: "will.deacon@arm.com" <will.deacon@arm.com>
Cc: "catalin.marinas@arm.com" <catalin.marinas@arm.com>
Cc: "mark.rutland@arm.com" <mark.rutland@arm.com>
Cc: "linux-arm-kernel@lists.infradead.org" <linux-arm-kernel@lists.infradead.org>
Cc: "gregkh@linuxfoundation.org" <gregkh@linuxfoundation.org>
Cc: "linux-hyperv@vger.kernel.org" <linux-hyperv@vger.kernel.org>
Cc: "olaf@aepfle.de" <olaf@aepfle.de>
Cc: "apw@canonical.com" <apw@canonical.com>
Cc: "jasowang@redhat.com" <jasowang@redhat.com>
Cc: "marcelo.cerri@canonical.com" <marcelo.cerri@canonical.com>
Cc: Sunil Muthuswamy <sunilmut@microsoft.com>
Cc: KY Srinivasan <kys@microsoft.com>
Cc: "sashal@kernel.org" <sashal@kernel.org>
Cc: "vincenzo.frascino@arm.com" <vincenzo.frascino@arm.com>
Cc: "linux-arch@vger.kernel.org" <linux-arch@vger.kernel.org>
Cc: "linux-mips@vger.kernel.org" <linux-mips@vger.kernel.org>
Cc: "linux-kselftest@vger.kernel.org" <linux-kselftest@vger.kernel.org>
Cc: "arnd@arndb.de" <arnd@arndb.de>
Cc: "linux@armlinux.org.uk" <linux@armlinux.org.uk>
Cc: "ralf@linux-mips.org" <ralf@linux-mips.org>
Cc: "paul.burton@mips.com" <paul.burton@mips.com>
Cc: "daniel.lezcano@linaro.org" <daniel.lezcano@linaro.org>
Cc: "salyzyn@android.com" <salyzyn@android.com>
Cc: "pcc@google.com" <pcc@google.com>
Cc: "shuah@kernel.org" <shuah@kernel.org>
Cc: "0x7f454c46@gmail.com" <0x7f454c46@gmail.com>
Cc: "linux@rasmusvillemoes.dk" <linux@rasmusvillemoes.dk>
Cc: "huw@codeweavers.com" <huw@codeweavers.com>
Cc: "sfr@canb.auug.org.au" <sfr@canb.auug.org.au>
Cc: "pbonzini@redhat.com" <pbonzini@redhat.com>
Cc: "rkrcmar@redhat.com" <rkrcmar@redhat.com>
Cc: "kvm@vger.kernel.org" <kvm@vger.kernel.org>
Link: https://lkml.kernel.org/r/1561955054-1838-2-git-send-email-mikelley@microsoft.com
---
 MAINTAINERS                        |   2 +
 arch/x86/include/asm/hyperv-tlfs.h |   6 ++
 arch/x86/kernel/cpu/mshyperv.c     |   4 +-
 drivers/clocksource/Makefile       |   1 +
 drivers/clocksource/hyperv_timer.c | 200 +++++++++++++++++++++++++++++++++++++
 drivers/hv/Kconfig                 |   3 +
 drivers/hv/hv.c                    | 156 +----------------------------
 drivers/hv/hyperv_vmbus.h          |   3 -
 drivers/hv/vmbus_drv.c             |  42 ++++----
 include/clocksource/hyperv_timer.h |  27 +++++
 10 files changed, 268 insertions(+), 176 deletions(-)

```
