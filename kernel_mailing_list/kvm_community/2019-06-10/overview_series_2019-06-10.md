#### [PATCH 1/1] kvm/speculation: Allow KVM guests to use SSBD even if host does not
##### From: Alejandro Jimenez <alejandro.j.jimenez@oracle.com>

```c
The bits set in x86_spec_ctrl_mask are used to calculate the
guest's value of SPEC_CTRL that is written to the MSR before
VMENTRY, and control which mitigations the guest can enable.
In the case of SSBD, unless the host has enabled SSBD always
on mode (by passing "spec_store_bypass_disable=on" in the
kernel parameters), the SSBD bit is not set in the mask and
the guest can not properly enable the SSBD always on
mitigation mode.

This is confirmed by running the SSBD PoC on a guest using
the SSBD always on mitigation mode (booted with kernel
parameter "spec_store_bypass_disable=on"), and verifying
that the guest is vulnerable unless the host is also using
SSBD always on mode. In addition, the guest OS incorrectly
reports the SSB vulnerability as mitigated.

Always set the SSBD bit in x86_spec_ctrl_mask when the host
CPU supports it, allowing the guest to use SSBD whether or
not the host has chosen to enable the mitigation in any of
its modes.

Signed-off-by: Alejandro Jimenez <alejandro.j.jimenez@oracle.com>
Reviewed-by: Liam Merwick <liam.merwick@oracle.com>
Cc: stable@vger.kernel.org
---
 arch/x86/kernel/cpu/bugs.c | 11 ++++++++++-
 1 file changed, 10 insertions(+), 1 deletion(-)

```
#### [PATCH] selftests/kvm: make platform_info_test pass on AMD
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
test_msr_platform_info_disabled() generates EXIT_SHUTDOWN but VMCB state
is undefined after that so an attempt to launch this guest again from
test_msr_platform_info_enabled() fails. Reorder the tests to make test
pass.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/x86_64/platform_info_test.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v11 1/7] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 13 ++++++++-----
 drivers/nvdimm/region_devs.c | 26 ++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  9 ++++++++-
 6 files changed, 47 insertions(+), 12 deletions(-)

```
