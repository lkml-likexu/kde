#### [GIT PULL] Please pull my kvm-ppc-fixes-5.1-1 tag
##### From: Paul Mackerras <paulus@ozlabs.org>

```c
Paolo or Radim,

Please do a pull from my kvm-ppc-fixes-5.1-1 tag to get two commits
which fix bugs which could potentially cause hangs or corruption in
the host.

Thanks,
Paul.

The following changes since commit 690edec54cbaa0e98dc592aae6864272f48f3c84:

  Merge tag 'kvmarm-fixes-for-5.1' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into kvm-master (2019-03-28 19:07:30 +0100)

are available in the git repository at:

  git://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc tags/kvm-ppc-fixes-5.1-1

for you to fetch changes up to 345077c8e172c255ea0707214303ccd099e5656b:

  KVM: PPC: Book3S: Protect memslots while validating user address (2019-04-05 14:37:24 +1100)

----------------------------------------------------------------
KVM/PPC fixes for 5.1

- Fix host hang in the HTM assist code for POWER9
- Take srcu read lock around memslot lookup

----------------------------------------------------------------
Alexey Kardashevskiy (1):
      KVM: PPC: Book3S: Protect memslots while validating user address

Suraj Jitindar Singh (1):
      KVM: PPC: Book3S HV: Perserve PSSCR FAKE_SUSPEND bit on guest exit

 arch/powerpc/kvm/book3s_64_vio.c | 6 +++---
 arch/powerpc/kvm/book3s_hv.c     | 4 +++-
 2 files changed, 6 insertions(+), 4 deletions(-)
```
