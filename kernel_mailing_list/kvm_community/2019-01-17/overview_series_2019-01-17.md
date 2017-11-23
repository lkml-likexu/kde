#### [PATCH kvmtool 1/3] builtin-run: Fix warning when resolving path
##### From: Anisse Astier <aastier@freebox.fr>

```c
GCC 8.2 gives this warning:

builtin-run.c: In function ‘kvm_run_write_sandbox_cmd.isra.1’:
builtin-run.c:417:28: error: ‘%s’ directive output may be truncated writing up to 4095 bytes into a region of size 4091 [-Werror=format-truncation=]
   snprintf(dst, len, "/host%s", resolved_path);
                            ^~   ~~~~~~~~~~~~~

It's because it understands that len is PATH_MAX, the same as
resolved_path's size. This patch handles the case where the string is
truncated, and fixes the warning.

Signed-off-by: Anisse Astier <aastier@freebox.fr>
---
 builtin-run.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH 1/4] KVM: MMU: correct the behavior of mmu_spte_update_no_track
##### From: Zhuangyanying <ann.zhuangyanying@huawei.com>

```c
From: Xiao Guangrong <xiaoguangrong@tencent.com>

Current behavior of mmu_spte_update_no_track() does not match
the name of _no_track() as actually the A/D bits are tracked
and returned to the caller

This patch introduces the real _no_track() function to update
the spte regardless of A/D bits and rename the original function
to _track()

The _no_track() function will be used by later patches to update
upper spte which need not care of A/D bits indeed

Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
---
 arch/x86/kvm/mmu.c | 25 ++++++++++++++++++++++---
 1 file changed, 22 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: nVMX: Fix size checks in vmx_set_nested_stateFrom: Jim Mattson <jmattson@google.com>
##### From: Jim Mattson <jmattson@google.com>

```c
The size checks in vmx_nested_state are wrong because the calculations
are made based on the size of a pointer to a struct kvm_nested_state
rather than the size of a struct kvm_nested_state.

Reported-by: Felix Wilhelm  <fwilhelm@google.com>
Signed-off-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Drew Schmitt <dasch@google.com>
Reviewed-by: Marc Orr <marcorr@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
---
 arch/x86/kvm/vmx/nested.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH kvmtool] init: fix sysfs mount arguments
##### From: Dmitry Monakhov <dmonakhov@openvz.org>

```c
From: Dmitry Monakhov <dmtrmonakhov@yandex-team.ru>

It is not good idea to pass empty 'source' argument to  mount(2) because libmount complains about
incorrect /proc/self/mountinfo structure. This affect many applications such as findmnt, umount and etc.
Let's add fake source argument to sysfs mount command as we do with all other filesystems.

#TESTCASE_BEGIN:
## findmount will complain like this 'findmnt: /proc/self/mountinfo: parse error at line 4 -- ignored'
echo "/bin/findmnt" > ./test.sh
./lkvm setup init-mount-test
./lkvm run -d init-mount-test --sandbox test.sh
rm -rf ~/.lkvm/init-mount-test
#TESTCASE_END
---
 guest/init.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [patch 9/9] vfio/pci: Cleanup license messReferences: <20190117231416.111952141@linutronix.de>
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
The recently added nvlink2 VFIO driver introduced a license conflict in two
files. In both cases the SPDX license identifier is:

  SPDX-License-Identifier: GPL-2.0+

but the files contain also the following license boiler plate text:

  * This program is free software; you can redistribute it and/or modify
  * it under the terms of the GNU General Public License version 2 as
  * published by the Free Software Foundation

The latter is GPL-2.9-only and not GPL-2.0=.

Looking deeper. The nvlink source file is derived from vfio_pci_igd.c which
is also licensed under GPL-2.0-only and it can be assumed that the file was
copied and modified. As the original file is licensed GPL-2.0-only it's not
possible to relicense derivative work to GPL-2.0-or-later.

Fix the SPDX identifier and remove the boiler plate as it is redundant.

Fixes: 7f92891778df ("vfio_pci: Add NVIDIA GV100GL [Tesla V100 SXM2] subdriver")
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Cc: Alexey Kardashevskiy <aik@ozlabs.ru>
Cc: Alex Williamson <alex.williamson@redhat.com>
Cc: Michael Ellerman <mpe@ellerman.id.au>
Cc: kvm@vger.kernel.org
---

P.S.: This patch is part of a larger cleanup, but independent of other
      patches and is intended to be picked up by the maintainer directly.

---
 drivers/vfio/pci/trace.h            |    6 +-----
 drivers/vfio/pci/vfio_pci_nvlink2.c |    6 +-----
```
#### [PATCH 1/2] x86/kvm/hyper-v: nested_enable_evmcs() sets vmcs_version incorrectly
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Commit e2e871ab2f02 ("x86/kvm/hyper-v: Introduce nested_get_evmcs_version()
helper") broke EVMCS enablement: to set vmcs_version we now call
nested_get_evmcs_version() but this function checks
enlightened_vmcs_enabled flag which is not yet set so we end up returning
zero.

Fix the issue by re-arranging things in nested_enable_evmcs().

Fixes: e2e871ab2f02 ("x86/kvm/hyper-v: Introduce nested_get_evmcs_version() helper")
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/evmcs.c | 7 ++++---
 1 file changed, 4 insertions(+), 3 deletions(-)

```
