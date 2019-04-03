#### [PATCH 1/2] kvm: arm: Clean up the checking for huge mapping
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c
If we are checking whether the stage2 can map PAGE_SIZE,
we don't have to do the boundary checks as both the host
VMA and the guest memslots are page aligned. Bail the case
easily.

Cc: Christoffer Dall <christoffer.dall@arm.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
---
 virt/kvm/arm/mmu.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v5 01/16] powerpc/xive: add OPAL extensions for the XIVE native exploitation support
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
The support for XIVE native exploitation mode in Linux/KVM needs a
couple more OPAL calls to get and set the state of the XIVE internal
structures being used by a sPAPR guest.

Signed-off-by: Cédric Le Goater <clg@kaod.org>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---
 arch/powerpc/include/asm/opal-api.h        |  7 +-
 arch/powerpc/include/asm/opal.h            |  7 ++
 arch/powerpc/include/asm/xive.h            | 14 +++
 arch/powerpc/platforms/powernv/opal-call.c |  3 +
 arch/powerpc/sysdev/xive/native.c          | 99 ++++++++++++++++++++++
 5 files changed, 127 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH] Add s390x/*.bin to the .gitignore file
##### From: Thomas Huth <thuth@redhat.com>

```c
Since commit 1a4cd2f22a48b8de53ef9e46afb8 ("s390x: Add binary generation
to makefile") we are also generating *.bin files from the *.elf files
in the s390x directory. Add them to the .gitignore file so that they
do not show up in the output of "git status" anymore.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Acked-by: David Hildenbrand <david@redhat.com>
---
 .gitignore | 1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests PATCH] s390x: Add a test for the diagnose 0x308 hypercall
##### From: Thomas Huth <thuth@redhat.com>

```c
The original idea for this test is to have an easy way to check for a
problem that has been fixed in QEMU recently: QEMU simply aborted if this
diagnose call was called with an unsupported subcode (e.g. 2). The problem
has been fixed in QEMU commit 37dbd1f4d4805edcd18d94eb202bb3461b3cd52d
("Return specification exception for unimplemented diag 308 subcodes"),
and this test now should make sure that we do not regress here again.
While we're at it, also check whether LOAD NORMAL via subcode 1 works
correctly, whether the diagnose call is blocked correctly in problem state
and whether subcodes 5 and 6 are generating specification exceptions for
illegal parameters as expected.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 s390x/Makefile      |   1 +
 s390x/diag308.c     | 130 ++++++++++++++++++++++++++++++++++++++++++++
 s390x/unittests.cfg |   3 +
 3 files changed, 134 insertions(+)
 create mode 100644 s390x/diag308.c

```
#### [kvm-unit-tests PATCH v2] scripts: Colorize output only on terminal
##### From: =?utf-8?q?Daniel_D=C3=ADaz?= <daniel.diaz@linaro.org>

```c
Instead of colorizing the output of PASS/SKIP/FAIL all the
time, do it only when stdout is plugged to a terminal, which
is generally a good indication that colors will be helpful.

When stdout is instead redirected, say, to a file, it's not
easy to parse the results of the tests. When analyzing and
extracting information out of the logs, it would be better to
strip the color information and just keep the test results.

Signed-off-by: Daniel Díaz <daniel.diaz@linaro.org>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 scripts/runtime.bash | 18 +++++++++++++++---
 1 file changed, 15 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: x86: clear VM_EXIT_SAVE_IA32_PAT
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
This is not needed, PAT writes always take an MSR vmexit.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/vmx.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH] KVM: x86: optimize check for valid PAT value
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
This check will soon be done on every nested vmentry and vmexit,
"parallelize" it using bitwise operations.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mtrr.c    | 10 +---------
 arch/x86/kvm/vmx/vmx.c |  2 +-
 arch/x86/kvm/x86.h     |  8 ++++++++
 3 files changed, 10 insertions(+), 10 deletions(-)

```
#### [PULL] virtio: fixes
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
The following changes since commit 15ade5d2e7775667cf191cf2f94327a4889f8b9d:

  Linux 5.1-rc4 (2019-04-07 14:09:59 -1000)

are available in the Git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/mst/vhost.git tags/for_linus

for you to fetch changes up to cf94db21905333e610e479688add629397a4b384:

  virtio: Honour 'may_reduce_num' in vring_create_virtqueue (2019-04-08 17:05:52 -0400)

----------------------------------------------------------------
virtio: fixes, reviewers

Several fixes, add more reviewers to the list

Signed-off-by: Michael S. Tsirkin <mst@redhat.com>

----------------------------------------------------------------
Cornelia Huck (1):
      virtio: Honour 'may_reduce_num' in vring_create_virtqueue

Longpeng (1):
      virtio_pci: fix a NULL pointer reference in vp_del_vqs

Michael S. Tsirkin (1):
      MAiNTAINERS: add Paolo, Stefan for virtio blk/scsi

 MAINTAINERS                        | 15 ++++++++++++++-
 drivers/virtio/virtio_pci_common.c |  8 +++++---
 drivers/virtio/virtio_ring.c       |  2 ++
 include/linux/virtio_ring.h        |  2 +-
 4 files changed, 22 insertions(+), 5 deletions(-)
```
#### [RFC] Check if X86_FEATURE_OSPKE is supported before accessing pkruThread-Topic: [RFC] Check if X86_FEATURE_OSPKE is supported before accessing
##### From: Xiexiangyou <xiexiangyou@huawei.com>

```c
Hi,

Commit b9dd21e104bcd45e124acfe978a79df71259e59b describes guest_CR4.PKE=1 implies host_CR4.PKE=1, and there is no need to judge OSPKE on the host.

However, I have found that the following scenarios may lead to inconsistencies with expectations:

1. The VM is migrated from the A host to the B host. The A host is configured
   with nopku but the B host is not.
2. The VM has an internal restart on the B host. The "setup_pku" is executed
   during the booting of the VM kernel. Because pku is supported, CR4.PKE is set.
3. Next, migrate the VM from the B host back to the A host. Panic will be
   triggered. Because vcpu vmexit will do host pkru restoring if guest_CR4.PKE
   is enabled.

static void vmx_vcpu_run(struct kvm_vcpu *vcpu) ...
	if (static_cpu_has(X86_FEATURE_PKU) &&
	    kvm_read_cr4_bits(vcpu, X86_CR4_PKE)) {
		vcpu->arch.pkru = __read_pkru();
		if (vcpu->arch.pkru != vmx->host_pkru)
			__write_pkru(vmx->host_pkru);
	}
...

Since hostos is configured with 'nopku', host CR4.PKE is 0, According to the intel manual, UD exception will occur when pkru is accessed in this case.

It is more appropriate to check X86_FEATURE_OSPKE than X86_FEATURE_PKU before accessing pkru.

Best Regards.
---
 arch/x86/kvm/vmx/vmx.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

--
1.8.3.1
```
#### [RFC] selftests: kvm: add a selftest for SMM
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Early RFC, based on state_test.

Add a simplistic test for SMM. Currently it fails with
"Unexpected result from KVM_SET_NESTED_STATE" even when a patch fixing
rsm after VMXON is added. There's likey some other issue in nested
save/restore when SMM os on.

The test implements its own sync between the guest and the host as using
our ucall library seems to be too cumbersome: SMI handler is happening in
real-address mode.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../selftests/kvm/include/x86_64/processor.h  |  27 +++
 tools/testing/selftests/kvm/x86_64/smm_test.c | 159 ++++++++++++++++++
 3 files changed, 187 insertions(+)
 create mode 100644 tools/testing/selftests/kvm/x86_64/smm_test.c

```
#### [PATCH v2] kvm: arm: Skip stage2 huge mappings for unaligned ipa backed by THP
##### From: Suzuki K Poulose <suzuki.poulose@arm.com>

```c
With commit a80868f398554842b14, we no longer ensure that the
THP page is properly aligned in the guest IPA. Skip the stage2
huge mapping for unaligned IPA backed by transparent hugepages.

Fixes: a80868f398554842b14 ("KVM: arm/arm64: Enforce PTE mappings at stage2 when needed")
Reported-by: Eric Auger <eric.auger@redhat.com>
Cc: Marc Zyngier <marc.zyngier@arm.com>
Cc: Chirstoffer Dall <christoffer.dall@arm.com>
Cc: Zenghui Yu <yuzenghui@huawei.com>
Cc: Zheng Xiang <zhengxiang9@huawei.com>
Cc: Andrew Murray <andrew.murray@arm.com>
Cc: Eric Auger <eric.auger@redhat.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
---
Changes since V1:
 - Zenghui Yu reported that the first version misses the boundary
   check for the end address. Lets reuse the existing helper to
   check it.
---
 virt/kvm/arm/mmu.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH v5 1/6] libnvdimm: nd_region flush callback support
##### From: Pankaj Gupta <pagupta@redhat.com>

```c
This patch adds functionality to perform flush from guest
to host over VIRTIO. We are registering a callback based
on 'nd_region' type. virtio_pmem driver requires this special
flush function. For rest of the region types we are registering
existing flush function. Report error returned by host fsync
failure to userspace.

This also handles asynchronous flush requests from the block layer
by creating a child bio and chaining it with parent bio.

Signed-off-by: Pankaj Gupta <pagupta@redhat.com>
---
 drivers/acpi/nfit/core.c     |  4 ++--
 drivers/nvdimm/claim.c       |  6 ++++--
 drivers/nvdimm/nd.h          |  1 +
 drivers/nvdimm/pmem.c        | 14 ++++++++-----
 drivers/nvdimm/region_devs.c | 38 ++++++++++++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  8 +++++++-
 6 files changed, 59 insertions(+), 12 deletions(-)

```
