#### [GIT PULL] KVM fixes for 4.19-rc8
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Greg,

The following changes since commit cc906f07d7d569a30bb6f0baf8f80b2968353dc9:

  Merge tag 'kvm-ppc-fixes-4.19-3' of git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc into kvm-master (2018-10-05 09:39:53 +0200)

are available in the git repository at:


  git://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to 5f8bb004bca43f7b5043c02b4aa5b9b43e15fe50:

  KVM: vmx: hyper-v: don't pass EPT configuration info to vmx_hv_remote_flush_tlb() (2018-10-13 11:38:54 +0200)

(The last patch shows as committed a few minutes ago because I had
unqueued it and now requeued it; I had tested it before unqueuing it.
Just telling you because I know that Linus checks this stuff...).

----------------------------------------------------------------
Leftover bugfixes.

----------------------------------------------------------------
Marc Zyngier (1):
      ARM: KVM: Correctly order SGI register entries in the cp15 array

Paolo Bonzini (2):
      KVM: x86: support CONFIG_KVM_AMD=y with CONFIG_CRYPTO_DEV_CCP_DD=m
      Merge tag 'kvmarm-fixes-for-4.19-2' of git://git.kernel.org/.../kvmarm/kvmarm into kvm-master

Vitaly Kuznetsov (1):
      KVM: vmx: hyper-v: don't pass EPT configuration info to vmx_hv_remote_flush_tlb()

 arch/arm/kvm/coproc.c | 8 ++++----
 arch/x86/kvm/svm.c    | 6 +++++-
 arch/x86/kvm/vmx.c    | 6 +++++-
 3 files changed, 14 insertions(+), 6 deletions(-)
```
#### [PATCH V5 1/3]  kvm/x86 : add coalesced pio support
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
add coalesced pio support.
 
Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 include/uapi/linux/kvm.h  | 11 +++++++++--
 virt/kvm/coalesced_mmio.c | 12 +++++++++---
 virt/kvm/kvm_main.c       |  2 ++
 3 files changed, 20 insertions(+), 5 deletions(-)

```
#### [PATCH v2 1/2] libnvdimm: nd_region flush callback support
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
 drivers/nvdimm/pmem.c        | 12 ++++++++----
 drivers/nvdimm/region_devs.c | 38 ++++++++++++++++++++++++++++++++++++--
 include/linux/libnvdimm.h    |  5 ++++-
 6 files changed, 55 insertions(+), 11 deletions(-)

```
#### [PATCH V4 1/15] KVM: Add tlb_remote_flush_with_range callback in kvm_x86_ops
##### From: lantianyu1986@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

Add flush range call back in the kvm_x86_ops and platform can use it
to register its associated function. The parameter "kvm_tlb_range"
accepts a single range and flush list which contains a list of ranges.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
Change since v1:
       Change "end_gfn" to "pages" to aviod confusion as to whether
"end_gfn" is inclusive or exlusive.
---
 arch/x86/include/asm/kvm_host.h | 8 ++++++++
 1 file changed, 8 insertions(+)

```
