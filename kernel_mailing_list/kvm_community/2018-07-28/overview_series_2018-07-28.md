#### [PATCH 01/10] KVM: x86: ensure all MSRs can always be KVM_GET/SET_MSR'd
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Some of the MSRs returned by GET_MSR_INDEX_LIST currently cannot be sent back
to KVM_GET_MSR and/or KVM_SET_MSR; either they can never be sent back, or you
they are only accepted under special conditions.  This makes the API a pain to
use.

To avoid this pain, this patch makes it so that the result of the get-list
ioctl can always be used for host-initiated get and set.  Since we don't have
a separate way to check for read-only MSRs, this means some Hyper-V MSRs are
ignored when written.  Arguably they should not even be in the result of
GET_MSR_INDEX_LIST, but I am leaving there in case userspace is using the
outcome of GET_MSR_INDEX_LIST to derive the support for the corresponding
Hyper-V feature.

Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/hyperv.c | 27 ++++++++++++++++++++-------
 arch/x86/kvm/hyperv.h |  2 +-
 arch/x86/kvm/x86.c    | 15 +++++++++------
 3 files changed, 30 insertions(+), 14 deletions(-)

```
