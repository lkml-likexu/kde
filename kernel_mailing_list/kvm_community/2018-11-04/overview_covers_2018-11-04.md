

#### [PATCH V6 0/8] KVM: X86: Introducing ROE Protection Kernel Hardening
##### From: Ahmed Abd El Mawgood <ahmedsoliman0x666@gmail.com>

```c

-- Summary --

ROE is a hypercall that enables host operating system to restrict guest's access
to its own memory. This will provide a hardening mechanism that can be used to
stop rootkits from manipulating kernel static data structures and code. Once a
memory region is protected the guest kernel can't even request undoing the
protection.

Memory protected by ROE should be non-swapable because even if the ROE protected
page got swapped out, It won't be possible to write anything in its place.

ROE hypercall should be capable of either protecting a whole memory frame or
parts of it. With these two, it should be possible for guest kernel to protect
its memory and all the page table entries for that memory inside the page table.
I am still not sure whether this should be part of ROE job or the guest's job.


The reason why it would be better to implement this from inside kvm: instead of
(host) user space is the need to access SPTEs to modify the permissions, while
mprotect() from user space can work in theory. It will become a big performance
hit to vmexit and switch to user space mode on each fault, on the other hand,
having the permission handled by EPT should make some remarkable performance
gain.

Our model assumes that an attacker got full root access to a running guest and
his goal is to manipulate kernel code/data (hook syscalls, overwrite IDT ..etc).

There is future work in progress to also put some sort of protection on the page
table register CR3 and other critical registers that can be intercepted by KVM.
This way it won't be possible for an attacker to manipulate any part of the
guests page table.




-- Change log V5 -> V6 --

- Make CONFIG_KVM_ROE=y the default so it can reach distros faster.
- Remove Obsolete description for Memory ROE documentation patch.
- Reorder the patches in more sensible manner (first are the helper patches,
  then the documentation, finally the real implementation).
- Add patch to log ROE via system log.
- Use affirmative mode in commits title.
- Get rid of the many #ifdefs.
- Factor most of the code out of arch/x86/kvm and place it into virt/kvm.

The previous version (V5) of the patch set can be found at [1]

-- links --

[1] https://lkml.org/lkml/2018/10/26/604

-- List of patches --

 [PATCH V6 1/8] KVM: State whether memory should be freed in
 [PATCH V6 2/8] KVM: X86: Add arbitrary data pointer in kvm memslot
 [PATCH V6 3/8] KVM: Document Memory ROE
 [PATCH V6 4/8] KVM: Create architecture independent ROE skeleton
 [PATCH V6 5/8] KVM: X86: Enable ROE for x86
 [PATCH V6 6/8] KVM: Add support for byte granular memory ROE
 [PATCH V6 7/8] KVM: X86: Port ROE_MPROTECT_CHUNK to x86
 [PATCH V6 8/8] KVM: Log ROE violations in system log

-- Difstat --
 Documentation/virtual/kvm/hypercalls.txt   |  40 ++++
 arch/x86/include/asm/kvm_host.h            |   2 +-
 arch/x86/kvm/Kconfig                       |   8 +
 arch/x86/kvm/Makefile                      |   4 +-
 arch/x86/kvm/mmu.c                         | 106 +++++----
 arch/x86/kvm/mmu.h                         |  40 +++-
 arch/x86/kvm/roe.c                         | 109 +++++++++
 arch/x86/kvm/roe_arch.h                    |  50 +++++
 arch/x86/kvm/x86.c                         |  11 +-
 include/kvm/roe.h                          |  23 ++
 include/linux/kvm_host.h                   |  29 +++
 include/uapi/linux/kvm_para.h              |   5 +
 net/sunrpc/xprtrdma/svc_rdma_backchannel.c |   4 +-
 virt/kvm/kvm_main.c                        |  55 ++++-
 virt/kvm/roe.c                             | 342 +++++++++++++++++++++++++++++
 virt/kvm/roe_generic.h                     |  46 ++++
 16 files changed, 797 insertions(+), 77 deletions(-)

Signed-off-by: Ahmed Abd El Mawgood <ahmedsoliman0x666@gmail.com>
```
