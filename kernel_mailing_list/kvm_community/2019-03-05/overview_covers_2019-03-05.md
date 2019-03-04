

#### [PATCH 0/2] disabling halt polling for nested virtualization
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c

Folks,

this is a very simple variant to disable halt polling when the KVM host
is already running virtualized. We could imagine more complex variants
(like tuning down the halt polling value) but this seems to do the trick
for some kvm deployment scenarios on s390x. (e.g. having multiple LPARS
with KVMs that are in itself already overcommitted). 
This still needs tuning and the right default value, but I want to start
the discussion.


Christian Borntraeger (2):
  KVM: polling: add architecture backend to disable polling
  KVM: s390: provide kvm_arch_no_poll function

 arch/s390/include/asm/kvm_host.h |  6 ++++++
 arch/s390/kvm/Kconfig            |  1 +
 include/linux/kvm_host.h         | 10 ++++++++++
 virt/kvm/Kconfig                 |  3 +++
 virt/kvm/kvm_main.c              |  2 +-
 5 files changed, 21 insertions(+), 1 deletion(-)
```
