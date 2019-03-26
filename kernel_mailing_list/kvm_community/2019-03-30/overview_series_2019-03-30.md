#### [PATCH 3/5] x86/kvm: Convert some slow-path static_cpu_has() callers to boot_cpu_has()
##### From: Borislav Petkov <bp@alien8.de>

```c
From: Borislav Petkov <bp@suse.de>

Using static_cpu_has() is pointless on those paths, convert them to the
boot_cpu_has() variant.

No functional changes.

Signed-off-by: Borislav Petkov <bp@suse.de>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: x86@kernel.org
---
 arch/x86/kvm/svm.c     | 10 +++++-----
 arch/x86/kvm/vmx/vmx.c |  4 ++--
 2 files changed, 7 insertions(+), 7 deletions(-)

```
#### [PATCH 1/1] vfio: Use dev_printk() when possible
##### From: Bjorn Helgaas <helgaas@kernel.org>

```c
From: Bjorn Helgaas <bhelgaas@google.com>

Use dev_printk() when possible to make messages consistent with other
device-related messages.

Signed-off-by: Bjorn Helgaas <bhelgaas@google.com>
---
 drivers/vfio/pci/vfio_pci.c                   | 26 +++++++----------
 drivers/vfio/pci/vfio_pci_config.c            | 28 ++++++++----------
 .../platform/reset/vfio_platform_amdxgbe.c    |  5 ++--
 drivers/vfio/platform/vfio_platform_common.c  | 12 ++++----
 drivers/vfio/vfio.c                           | 29 +++++++++----------
 include/linux/pci.h                           |  3 ++
 6 files changed, 49 insertions(+), 54 deletions(-)

```
