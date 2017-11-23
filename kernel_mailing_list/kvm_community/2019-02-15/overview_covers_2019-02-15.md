

#### [PATCH 0/3] KVM: Fix device ioctl bug and update docs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c

Patch 2/3 contains the only real code change, which adds a check to the
device ioctl to reject the ioctl if the issuer is not the same process
that created VM which owns said device.  The bulk of the patches are to
tweak and enhance KVM's API documentation.

This series was prompted by the recent series to add memcg accounting
to KVM's kernel allocation[1], Paolo's comment that KVM allows creating
multiple VM's in a single process[2], and work on an unrelated project
that uses a similar file descriptor approach for managing an API.

[1] https://patchwork.kernel.org/patch/10806707
[2] https://lkml.kernel.org/r/f23265d4-528e-3bd4-011f-4d7b8f3281db@redhat.com

Sean Christopherson (3):
  KVM: doc: Fix incorrect word ordering regarding supported use of APIs
  KVM: Reject device ioctls from processes other than the VM's creator
  KVM: doc: Document the life cycle of a VM and its resources

 Documentation/virtual/kvm/api.txt | 48 ++++++++++++++++++++++---------
 virt/kvm/kvm_main.c               |  3 ++
 2 files changed, 38 insertions(+), 13 deletions(-)
```
