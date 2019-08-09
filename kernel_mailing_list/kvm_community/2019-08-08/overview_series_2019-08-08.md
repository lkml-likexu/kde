#### [PATCH v2 1/2] vfio-mdev/mtty: Simplify interrupt generation
##### From: Parav Pandit <parav@mellanox.com>

```c
While generating interrupt, mdev_state is already available for which
interrupt is generated.
Instead of doing indirect way from state->device->uuid-> to searching
state linearly in linked list on every interrupt generation,
directly use the available state.

Hence, simplify the code to use mdev_state and remove unused helper
function with that.

Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Parav Pandit <parav@mellanox.com>
---
 samples/vfio-mdev/mtty.c | 39 ++++++++-------------------------------
 1 file changed, 8 insertions(+), 31 deletions(-)

```
#### [PATCH v2] selftests: kvm: Adding config fragments
##### From: Naresh Kamboju <naresh.kamboju@linaro.org>

```c
selftests kvm all test cases need pre-required kernel configs for the
tests to get pass.

The KVM tests are skipped without these configs:

        dev_fd = open(KVM_DEV_PATH, O_RDONLY);
        if (dev_fd < 0)
                exit(KSFT_SKIP);

Signed-off-by: Naresh Kamboju <naresh.kamboju@linaro.org>
Acked-by: Shuah Khan <skhan@linuxfoundation.org>
---
 tools/testing/selftests/kvm/config | 3 +++
 1 file changed, 3 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/config

diff --git a/tools/testing/selftests/kvm/config b/tools/testing/selftests/kvm/config
new file mode 100644
index 000000000000..63ed533f73d6
--- /dev/null
+++ b/tools/testing/selftests/kvm/config
@@ -0,0 +1,3 @@
+CONFIG_KVM=y
+CONFIG_KVM_INTEL=y
+CONFIG_KVM_AMD=y
```
#### [PATCH] vhost: do not reference a file that does not exist
##### From: egranata@chromium.org

```c
From: Enrico Granata <egranata@google.com>

lguest was removed from the mainline kernel in late 2017.

Signed-off-by: Enrico Granata <egranata@google.com>
---
 drivers/vhost/vhost.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v3 1/7] x86: KVM: svm: don't pretend to advance RIP in case wrmsr_interception() results in #GP
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
svm->next_rip is only used by skip_emulated_instruction() and in case
kvm_set_msr() fails we rightfully don't do that. Move svm->next_rip
advancement to 'else' branch to avoid creating false impression that
it's always advanced (and make it look like rdmsr_interception()).

This is a preparatory change to removing hardcoded RIP advancement
from instruction intercepts, no functional change.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
