

#### [PATCH v2 00/12] KVM: s390: make use of the GIB
##### From: Michael Mueller <mimu@linux.ibm.com>

```c

The Guest Information Area (GIB) and its mechanics is part of
the AIV facility. It provides hardware support to process
Adapter Interruptions (AI) for pagable storage mode guests. 

Whenever a guest cannot process an AI because none of its
vcpus is running in SIE context, a GIB alert interruption is
sent to and handled by the host program to dispatch a vcpu of
the respective guest.

Eventually, the AI is handled by the guest.

v1->v2:
  patch 01/12: New patch. Tt can go also standalone without the
  	       rest of the GIB series presented here but is a
	       requirement 
  patch 03/12: kvm_s390_gib_init() now has a return code
  patch 06/12: unlink_gib_alert_list() now uses cmpxchg() instead
    	       of atomic_xchg()
  patch 08/12: New patch. Foctors out __find_vcpu_for_floating_irq()
  patch 09/12: process_gib_alert_list() has been simplified
               the GISA clear/destroy cases have been removed
  patch 11/12: kvm_s390_gisa_clear/destroy() now clear the IAM
               and process the alert list directly
	       The IAM now gets restored in vcpu_post_run() only if
	       the GISA is not in alert list
  patch 12/12: during kvm_arch_init() now the return code of
    	       kvm_s390_gib_init() is honored.

All other patches are unchanged.

Michael Mueller (12):
  KVM: s390: leave AIs in IPM of GISA during vcpu_pre_run()
  s390/cio: add function chsc_sgib()
  KVM: s390: add the GIB and its related life-cyle functions
  KVM: s390: factor out nullify_gisa()
  KVM: s390: add metric vcpus_in_sie to struct kvm_arch
  KVM: s390: add function unlink_gib_alert_list()
  KVM: s390: add kvm reference to struct sie_page2
  KVM: s390: factor out __find_vcpu_for_floating_irq()
  KVM: s390: add function process_gib_alert_list()
  KVM: s390: add functions to (un)register GISC with GISA
  KVM: s390: add and wire function gib_alert_irq_handler()
  KVM: s390: start using the GIB

 arch/s390/include/asm/cio.h      |   1 +
 arch/s390/include/asm/irq.h      |   1 +
 arch/s390/include/asm/isc.h      |   1 +
 arch/s390/include/asm/kvm_host.h |  20 +++-
 arch/s390/kernel/irq.c           |   1 +
 arch/s390/kvm/interrupt.c        | 249 ++++++++++++++++++++++++++++++++-------
 arch/s390/kvm/kvm-s390.c         |  18 +++
 arch/s390/kvm/kvm-s390.h         |   7 ++
 drivers/s390/cio/chsc.c          |  37 ++++++
 drivers/s390/cio/chsc.h          |   1 +
 10 files changed, 295 insertions(+), 41 deletions(-)
```
