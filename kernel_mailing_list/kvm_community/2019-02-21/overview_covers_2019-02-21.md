

#### [PATCH v2 0/1]  Restore change_pte optimization
##### From: jglisse@redhat.com
From: Jérôme Glisse <jglisse@redhat.com>

```c

From: Jérôme Glisse <jglisse@redhat.com>

This patch is on top of my patchset to add context information to
mmu notifier [1] you can find a branch with everything [2]. It has
been tested with qemu/KVM building kernel within the guest and also
running a benchmark which the result are given below.

The change_pte() callback is impaired by the range invalidation call-
back within KVM as the range invalidation callback as those do fully
invalidate the secondary mmu. This means that there is a window between
the range_start callback and the change_pte callback where the secondary
mmu for the address is empty. Guest can fault on that address during
that window.

That window can last for some times if the kernel code which is
doing the invalidation is interrupted or if they are other mmu
listener for the process that might sleep within their range_start
callback.

With this patch KVM will ignore the range_start and range_end call-
back and will rely solely on the change_pte callback to update the
secondary mmu. This means that the secondary mmu never have an empty
entry for the address between range_start and range_end and hence
the guest will not have a chance to fault.

This optimization is not valid for all the mmu notifier cases and
thanks to the patchset that add context informations to the mmu
notifier [1] we can now identify within KVM when it is safe to rely
on this optimization.

Roughly it is safe when:
    - going from read only to read and write (same or different pfn)
    - going from read and write to read only same pfn
    - going from read only to read only different pfn

Longer explaination in [1] and [3].

Running ksm02 from ltp gives the following results:

before  mean  {real: 675.460632, user: 857.771423, sys: 215.929657, npages: 4773.066895}
before  stdev {real:  37.035435, user:   4.395942, sys:   3.976172, npages:  675.352783}
after   mean  {real: 672.515503, user: 855.817322, sys: 200.902710, npages: 4899.000000}
after   stdev {real:  37.340954, user:   4.051633, sys:   3.894153, npages:  742.413452}

Roughly 7%-8% less time spent in the kernel. So we are saving few
cycles (this is with KSM enabled on the host and ksm sleep set to
0). Dunno how this translate to real workload.


Note that with the context information further optimization are now
possible within KVM. For instance you can find out if a range is
updated to read only (ie no pfn change just protection change) and
update the secondary mmu accordingly.

You can also identify munmap()/mremap() syscall and only free up the
resources you have allocated for the range (like freeing up secondary
page table for the range or data structure) when it is an munmap or
a mremap. Today my understanding is that kvm_unmap_hva_range() will
free up resources always assuming it is an munmap of some sort. So
for mundane invalidation (like migration, reclaim, mprotect, fork,
...) KVM is freeing up potential mega bytes of structure that it will
have to re-allocate shortly there after (see [4] for WIP example).

Cheers,
Jérôme

[1] https://lkml.org/lkml/2019/2/19/752
[2] https://cgit.freedesktop.org/~glisse/linux/log/?h=mmu-notifier-v05
[3] https://lkml.org/lkml/2019/2/19/754
[4] https://cgit.freedesktop.org/~glisse/linux/log/?h=wip-kvm-mmu-notifier-opti

Cc: Andrea Arcangeli <aarcange@redhat.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Andrew Morton <akpm@linux-foundation.org>

Jérôme Glisse (1):
  kvm/mmu_notifier: re-enable the change_pte() optimization.

 virt/kvm/kvm_main.c | 16 ++++++++++++++++
 1 file changed, 16 insertions(+)
```
#### [kvm-unit-tests PATCH 0/5] x86: nVMX: Address feedback on EPT series
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

A recent series to fix a variety of EPT related bugs[1] introduced a
few new issues of its own.  The issues were caught in code review, but
not until the series was applied (Paolo was especially quick on the
trigger that day).

[1] https://patchwork.kernel.org/cover/10808887/

Sean Christopherson (5):
  x86: nVMX: Check the return value of setup_eptp() in setup_ept()
  x86: nVMX: Pre-check EPT requirement for unrestricted guest
  x86: nVMX: Require WB for the EPT walks when possible
  x86: nVMX: Rename EPT setup functions to better convey their scope
  x86: nVMX: Add comments to the EPT helper functions

 x86/vmx_tests.c | 61 ++++++++++++++++++++++++++++++++++---------------
 1 file changed, 42 insertions(+), 19 deletions(-)
```
#### [kvm-unit-tests PATCH v1 0/2] Misc patches
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c

Primary purpose of this patch series is to improve tap13 output to be
fit for CI purposes. While almost ready to submit, stumbled upon a
glitch in the most recently added support for specifying desired tests
on the command line, so added another patch to fix that up.

Stefan Raspl (2):
  tap13: list testcases individually
  run_tests: fix command line options handling

 run_tests.sh         | 73 +++++++++++++++++++++++++++++++++++-----------------
 scripts/runtime.bash | 10 -------
 2 files changed, 50 insertions(+), 33 deletions(-)
```
#### [PATCH 0/2] KVM: s390: small prep patches for cpu model
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c

These are prep patches for some bigger work. As they make sense on their
own I want to send it out now.

Christian Borntraeger (2):
  KVM: s390: implement subfunction processor calls
  KVM: s390: add debug logging for cpu model subfunctions

 arch/s390/include/asm/kvm_host.h |   1 +
 arch/s390/kvm/kvm-s390.c         | 170 ++++++++++++++++++++++++++++---
 2 files changed, 159 insertions(+), 12 deletions(-)
```
