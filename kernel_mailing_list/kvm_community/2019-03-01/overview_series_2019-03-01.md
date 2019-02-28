#### [GIT PULL] Please pull my kvm-ppc-next-5.1-2 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Please do a pull from my kvm-ppc-next-5.1-2 tag to get one commit,
which fixes a compile error on PPC when the powernv platform is
enabled but KVM isn't.

Thanks,
Paul.

The following changes since commit 71783e09b4874c845819b5658b968d8b5b899333:

  Merge tag 'kvmarm-for-v5.1' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into kvm-next (2019-02-22 17:45:05 +0100)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.1-2

for you to fetch changes up to e74d53e30e2927fa5b223296ac7922baf15ea89a:

  KVM: PPC: Fix compilation when KVM is not enabled (2019-02-27 09:14:44 +1100)

----------------------------------------------------------------
Second PPC KVM update for 5.1

- Fix an error in compiling for the powernv platform with KVM disabled.

----------------------------------------------------------------
Paul Mackerras (1):
      KVM: PPC: Fix compilation when KVM is not enabled

 arch/powerpc/include/asm/kvm_ppc.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)
```
#### [GIT PULL] Please pull my kvm-ppc-next-5.1-3 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo & Radim,

Immediately after I sent my previous pull request, I saw that Suraj
had posted a patch that advertises a new mitigation for one of the
spectre vulnerabilities to userspace.  The code for the host to know
about and use this new mitigation went into 4.19.  Since the patch is
low-risk and security-related, I would like to get it into 5.1.  With
this patch and a related QEMU patch, guests will be able to use this
new mitigation on machines that support it.

So, please do a pull from my kvm-ppc-next-5.1-3 tag to get this
commit.  (If you haven't already pulled the 5.1-2 tag then you will
get the compile fix as well, of course.)

Thanks,
Paul.

The following changes since commit e74d53e30e2927fa5b223296ac7922baf15ea89a:

  KVM: PPC: Fix compilation when KVM is not enabled (2019-02-27 09:14:44 +1100)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-next-5.1-3

for you to fetch changes up to 2b57ecd0208f7ac0b20b1b171698f027481a39f6:

  KVM: PPC: Book3S: Add count cache flush parameters to kvmppc_get_cpu_char() (2019-03-01 15:11:14 +1100)

----------------------------------------------------------------
Third PPC KVM update for 5.1

- Tell userspace about whether a particular hardware workaround for
  one of the Spectre vulnerabilities is available, so that userspace
  can inform the guest.

----------------------------------------------------------------
Suraj Jitindar Singh (1):
      KVM: PPC: Book3S: Add count cache flush parameters to kvmppc_get_cpu_char()

 arch/powerpc/include/uapi/asm/kvm.h |  2 ++
 arch/powerpc/kvm/powerpc.c          | 18 ++++++++++++++----
 2 files changed, 16 insertions(+), 4 deletions(-)
```
#### [PATCH] KVM: PPC: powerpc: Add count cache flush parameters to kvmppc_get_cpu_char()
##### From: Suraj Jitindar Singh <sjitindarsingh@gmail.com>

```c
Add KVM_PPC_CPU_CHAR_BCCTR_FLUSH_ASSIST &
KVM_PPC_CPU_BEHAV_FLUSH_COUNT_CACHE to the characteristics returned from
the H_GET_CPU_CHARACTERISTICS H-CALL, as queried from either the
hypervisor or the device tree.

Signed-off-by: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
---
 arch/powerpc/include/uapi/asm/kvm.h |  2 ++
 arch/powerpc/kvm/powerpc.c          | 18 ++++++++++++++----
 2 files changed, 16 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH] Add a .gitlab-ci.yml file for automatic CI testing on GitLab instances
##### From: Thomas Huth <thuth@redhat.com>

```c
When changing common code of the kvm-unit-tests, one should make sure that
the tests still compile fine for all target architectures afterwards. But
compiling kvm-unit-tests for all target architectures manually is cumbersome.
For people like me who store their git trees on GitLab, this can be done
automatically via a CI system instead. Using the .gitlab-ci.yml file, auto-
matic builds are now triggered on each push to a kvm-unit-test repository on
gitlab.com. Additionally, the script also runs the tests that can be executed
with QEMU TCG (except for s390x, since the QEMU package of the CI container
currently does not provide the required s390-ccw bios here).

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 An example output can be found here:
 https://gitlab.com/huth/kvm-unit-tests/pipelines/49788391

 .gitlab-ci.yml | 78 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 78 insertions(+)
 create mode 100644 .gitlab-ci.yml

diff --git a/.gitlab-ci.yml b/.gitlab-ci.yml
new file mode 100644
index 0000000..bc6ca0e
--- /dev/null
+++ b/.gitlab-ci.yml
@@ -0,0 +1,78 @@
+before_script:
+ - apt-get update -qq
+ - apt-get install -y -qq qemu-system
+
+build-aarch64:
+ script:
+ - apt-get install -y -qq gcc-aarch64-linux-gnu
+ - ./configure --arch=aarch64 --processor=arm64
+     --cross-prefix=aarch64-linux-gnu-
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     selftest-setup selftest-vectors-kernel selftest-vectors-user selftest-smp
+     pci-test gicv2-active gicv3-active timer
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
+
+build-arm:
+ script:
+ - apt-get install -y -qq gcc-arm-linux-gnueabi
+ - ./configure --arch=arm --processor=arm --cross-prefix=arm-linux-gnueabi-
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     selftest-setup selftest-vectors-kernel selftest-vectors-user selftest-smp
+     pci-test gicv2-active gicv3-active
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
+
+build-ppc64be:
+ script:
+ - apt-get install -y -qq gcc-powerpc64-linux-gnu
+ - ./configure --arch=ppc64 --processor=powerpc --endian=big
+     --cross-prefix=powerpc64-linux-gnu-
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     selftest-setup spapr_hcall rtas-get-time-of-day rtas-get-time-of-day-base
+     rtas-set-time-of-day emulator
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
+
+build-ppc64le:
+ script:
+ - apt-get install -y -qq gcc-powerpc64-linux-gnu
+ - ./configure --arch=ppc64 --processor=powerpc --endian=little
+     --cross-prefix=powerpc64-linux-gnu-
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     selftest-setup spapr_hcall rtas-get-time-of-day rtas-get-time-of-day-base
+     rtas-set-time-of-day emulator
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
+
+build-s390x:
+ script:
+ - apt-get install -y -qq gcc-s390x-linux-gnu
+ - ./configure --arch=s390x --processor=s390x --cross-prefix=s390x-linux-gnu-
+ - make -j2
+
+build-x86_64:
+ script:
+ - ./configure --arch=x86_64 --processor=x86_64
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     ioapic-split ioapic smptest smptest3 vmexit_cpuid vmexit_mov_from_cr8
+     vmexit_mov_to_cr8 vmexit_inl_pmtimer  vmexit_ipi vmexit_ipi_halt
+     vmexit_ple_round_robin vmexit_tscdeadline vmexit_tscdeadline_immed
+     eventinj msr port80 sieve tsc rmap_chain umip hyperv_stimer intel_iommu
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
+
+build-i386:
+ script:
+ - apt-get install -y -qq gcc-multilib
+ - ./configure --arch=i386 --processor=i386
+ - make -j2
+ - ACCEL=tcg ./run_tests.sh
+     eventinj port80 sieve tsc taskswitch umip hyperv_stimer
+     | tee results.txt
+ - if grep -q FAIL results.txt ; then exit 1 ; fi
```
#### [PATCH v4 1/6] vfio-ccw: make it safe to access channel programs
##### From: Cornelia Huck <cohuck@redhat.com>

```c
When we get a solicited interrupt, the start function may have
been cleared by a csch, but we still have a channel program
structure allocated. Make it safe to call the cp accessors in
any case, so we can call them unconditionally.

While at it, also make sure that functions called from other parts
of the code return gracefully if the channel program structure
has not been initialized (even though that is a bug in the caller).

Reviewed-by: Eric Farman <farman@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/cio/vfio_ccw_cp.c  | 21 ++++++++++++++++++++-
 drivers/s390/cio/vfio_ccw_cp.h  |  2 ++
 drivers/s390/cio/vfio_ccw_fsm.c |  5 +++++
 3 files changed, 27 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/2] vfio-ccw: new capability chain support
##### From: Cornelia Huck <cohuck@redhat.com>

```c
To be replaced with a real linux-headers update.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 linux-headers/linux/vfio.h     |  4 ++++
 linux-headers/linux/vfio_ccw.h | 12 ++++++++++++
 2 files changed, 16 insertions(+)

```
