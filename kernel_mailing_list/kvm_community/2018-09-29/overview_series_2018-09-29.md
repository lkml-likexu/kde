#### [PATCH 3.16 048/131] KVM/VMX: Expose SSBD properly to guestsIn-Reply-To: <lsq.1538257386.330095874@decadent.org.uk>
##### From: Ben Hutchings <ben@decadent.org.uk>

```c
3.16.59-rc1 review patch.  If anyone has any objections, please let me know.

------------------

From: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>

commit 0aa48468d00959c8a37cd3ac727284f4f7359151 upstream.

The X86_FEATURE_SSBD is an synthetic CPU feature - that is
it bit location has no relevance to the real CPUID 0x7.EBX[31]
bit position. For that we need the new CPU feature name.

Fixes: 52817587e706 ("x86/cpufeatures: Disentangle SSBD enumeration")
Signed-off-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Cc: kvm@vger.kernel.org
Cc: "Radim Krčmář" <rkrcmar@redhat.com>
Cc: "H. Peter Anvin" <hpa@zytor.com>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Link: https://lkml.kernel.org/r/20180521215449.26423-2-konrad.wilk@oracle.com
[bwh: Backported to 3.16:
 - Fix guest_cpuid_has_spec_ctrl() as well
 - Adjust context]
```
