#### [PATCH RESEND] i386/kvm: support guest access CORE cstate
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Allow guest reads CORE cstate when exposing host CPU power management capabilities 
to the guest. PKG cstate is restricted to avoid a guest to get the whole package 
information in multi-tenant scenario.

Cc: Eduardo Habkost <ehabkost@redhat.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 linux-headers/linux/kvm.h | 4 +++-
 target/i386/kvm.c         | 3 ++-
 2 files changed, 5 insertions(+), 2 deletions(-)

```
