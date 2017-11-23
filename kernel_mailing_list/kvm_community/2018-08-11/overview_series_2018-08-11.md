#### [PATCH v3 12/17] x86/kvm: enable Hygon support to KVM infrastructure
##### From: Pu Wen <puwen@hygon.cn>

```c
Hygon Dhyana CPU has the SVM feature as AMD family 17h does.
Add Hygon support in the KVM infrastructure.

Signed-off-by: Pu Wen <puwen@hygon.cn>
---
 arch/x86/include/asm/kvm_emulate.h |  4 ++++
 arch/x86/include/asm/virtext.h     |  5 +++--
 arch/x86/kvm/emulate.c             | 11 ++++++++++-
 3 files changed, 17 insertions(+), 3 deletions(-)

```
