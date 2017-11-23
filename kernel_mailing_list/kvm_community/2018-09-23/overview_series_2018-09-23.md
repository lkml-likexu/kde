#### [PATCH v8 11/16] x86/kvm: Add Hygon Dhyana support to KVM infrastructure
##### From: Pu Wen <puwen@hygon.cn>

```c
The Hygon Dhyana CPU has the SVM feature as AMD family 17h does.
So enable the KVM infrastructure support to it.

Signed-off-by: Pu Wen <puwen@hygon.cn>
Reviewed-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/include/asm/kvm_emulate.h |  4 ++++
 arch/x86/include/asm/virtext.h     |  5 +++--
 arch/x86/kvm/emulate.c             | 11 ++++++++++-
 3 files changed, 17 insertions(+), 3 deletions(-)

```
