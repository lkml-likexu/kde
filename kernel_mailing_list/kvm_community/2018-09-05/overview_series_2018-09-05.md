#### [GIT PULL 1/3] KVM: s390: Fix pfmf and conditional skey emulation
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
From: Janosch Frank <frankja@linux.ibm.com>

We should not return with a lock.
We also have to increase the address when we do page clearing.

Fixes: bd096f644319 ("KVM: s390: Add skey emulation fault handling")
Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Message-Id: <20180830081355.59234-1-frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/priv.c | 30 ++++++++++++++++++------------
 1 file changed, 18 insertions(+), 12 deletions(-)

```
