#### [PATCH] KVM: export <linux/kvm_para.h> and <asm/kvm_para.h> iif KVM is supported
##### From: Masahiro Yamada <yamada.masahiro@socionext.com>

```c
I do not see any consistency about headers_install of <linux/kvm_para.h>
and <asm/kvm_para.h>.

According to my analysis of Linux 5.0-rc5, there are 3 groups:

 [1] Both <linux/kvm_para.h> and <asm/kvm_para.h> are exported

    alpha, arm, hexagon, mips, powerpc, s390, sparc, x86

 [2] <asm/kvm_para.h> is exported, but <linux/kvm_para.h> is not

    arc, arm64, c6x, h8300, ia64, m68k, microblaze, nios2, openrisc

 [3] Neither <linux/kvm_para.h> nor <asm/kvm_para.h> is exported

    csky, nds32, riscv

This does not match to the actual KVM support. At least, [2] is
half-baked.

Nor do arch maintainers look like they care about this. For example,
commit 0add53713b1c ("microblaze: Add missing kvm_para.h to Kbuild")
exported <asm/kvm_para.h> to user-space in order to fix an in-kernel
build error.

We have two ways to make this consistent:

 [A] export both <linux/kvm_para.h> and <asm/kvm_para.h> for all
     architectures, irrespective of the KVM support

 [B] Match the header export of <linux/kvm_para.h> and <asm/kvm_para.h>
     to the KVM support

My first attempt was [A] because the code looks better, but Paolo
showed preference in [B].

  https://patchwork.kernel.org/patch/10794919/

So, this commit is the implementation of [B].

For most architectures, <asm/kvm_para.h> was moved to the kernel-space.
I changed include/uapi/linux/Kbuild so that it checks generated
asm/kvm_para.h as well as check-in ones.

After this commit, there will be two groups:

 [1] Both <linux/kvm_para.h> and <asm/kvm_para.h> are exported

    arm arm64 mips powerpc s390 x86

 [2] Neither <linux/kvm_para.h> nor <asm/kvm_para.h> is exported

    alpha arc c6x csky h8300 hexagon ia64 m68k microblaze nds32 nios2
    openrisc parisc riscv sh sparc unicore32 xtensa

Signed-off-by: Masahiro Yamada <yamada.masahiro@socionext.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---

The alternative solution [A] is available at:
https://patchwork.kernel.org/patch/10794919/

Comparing the code diff, I personally prefer [A]...


 arch/alpha/include/asm/Kbuild            | 1 +
 arch/alpha/include/uapi/asm/kvm_para.h   | 2 --
 arch/arc/include/asm/Kbuild              | 1 +
 arch/arc/include/uapi/asm/Kbuild         | 1 -
 arch/arm/include/uapi/asm/Kbuild         | 1 +
 arch/arm/include/uapi/asm/kvm_para.h     | 2 --
 arch/c6x/include/asm/Kbuild              | 1 +
 arch/c6x/include/uapi/asm/Kbuild         | 1 -
 arch/h8300/include/asm/Kbuild            | 1 +
 arch/h8300/include/uapi/asm/Kbuild       | 1 -
 arch/hexagon/include/asm/Kbuild          | 1 +
 arch/hexagon/include/uapi/asm/kvm_para.h | 2 --
 arch/ia64/include/asm/Kbuild             | 1 +
 arch/ia64/include/uapi/asm/Kbuild        | 1 -
 arch/m68k/include/asm/Kbuild             | 1 +
 arch/m68k/include/uapi/asm/Kbuild        | 1 -
 arch/microblaze/include/asm/Kbuild       | 1 +
 arch/microblaze/include/uapi/asm/Kbuild  | 1 -
 arch/mips/include/uapi/asm/Kbuild        | 1 +
 arch/mips/include/uapi/asm/kvm_para.h    | 5 -----
 arch/nios2/include/asm/Kbuild            | 1 +
 arch/nios2/include/uapi/asm/Kbuild       | 1 -
 arch/openrisc/include/asm/Kbuild         | 1 +
 arch/openrisc/include/uapi/asm/Kbuild    | 1 -
 arch/parisc/include/asm/Kbuild           | 1 +
 arch/parisc/include/uapi/asm/Kbuild      | 1 -
 arch/s390/include/uapi/asm/Kbuild        | 1 +
 arch/s390/include/uapi/asm/kvm_para.h    | 8 --------
 arch/sh/include/asm/Kbuild               | 1 +
 arch/sh/include/uapi/asm/Kbuild          | 1 -
 arch/sparc/include/asm/Kbuild            | 1 +
 arch/sparc/include/uapi/asm/kvm_para.h   | 2 --
 arch/unicore32/include/asm/Kbuild        | 1 +
 arch/unicore32/include/uapi/asm/Kbuild   | 1 -
 arch/xtensa/include/asm/Kbuild           | 1 +
 arch/xtensa/include/uapi/asm/Kbuild      | 1 -
 include/uapi/linux/Kbuild                | 2 ++
 37 files changed, 20 insertions(+), 33 deletions(-)
 delete mode 100644 arch/alpha/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/arm/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/hexagon/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/mips/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/s390/include/uapi/asm/kvm_para.h
 delete mode 100644 arch/sparc/include/uapi/asm/kvm_para.h

```
