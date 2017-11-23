

#### [QEMU PATCH v2 0/2]: KVM: i386: Add support for save and restore
##### From: Liran Alon <liran.alon@oracle.com>

```c

Hi,

This series aims to add support for QEMU to be able to migrate VMs that
are running nested hypervisors. In order to do so, it utilizes the new
IOCTLs introduced in KVM commit 8fcc4b5923af ("kvm: nVMX: Introduce
KVM_CAP_NESTED_STATE") which were created for this purpose.

1st patch is not really related to the goal of the patch series. It just
makes CPUX86State->xsave_buf to be compiled only when needed (When
compiling with KVM or HVF CPU accelerator).

2nd patch adds the support to migrate VMs that are running nested
hypervisors.

Regards,
-Liran

v1->v2 Changes:
* Renamed kvm_nested_state_length() to kvm_max_nested_state_length()
to better indicate it represents the max nested state size that can
be returned from kernel.
* Added error_report() calls to nested_state_post_load() to make
failures in migration easier to diagnose.
* Fixed support of migrating with various nested_state buffer sizes.
The following scenarios were tested:
(a) src and dest have same nested state size.
	==> Migration succeeds.
(b) src don't have nested state while dest do.
	==> Migration succeed and src don't send it's nested state.
(c) src have nested state while dest don't.
	==> Migration fails as it cannot restore nested state.
(d) dest have bigger max nested state size than src
	==> Migration succeeds.
(e) dest have smaller max nested state size than src but enough to store it's saved nested state
	==> Migration succeeds
(f) dest have smaller max nested state size than src but not enough to store it's saved nested state
	==> Migration fails
```
