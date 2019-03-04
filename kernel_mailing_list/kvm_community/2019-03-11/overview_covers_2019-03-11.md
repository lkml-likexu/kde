

#### [PATCH 0/3] userfaultfd: allow to forbid unprivileged users
##### From: Peter Xu <peterx@redhat.com>

```c

Hi,

(The idea comes from Andrea, and following discussions with Mike and
 other people)

This patchset introduces a new sysctl flag to allow the admin to
forbid users from using userfaultfd:

  $ cat /proc/sys/vm/unprivileged_userfaultfd
  [disabled] enabled kvm

  - When set to "disabled", all unprivileged users are forbidden to
    use userfaultfd syscalls.

  - When set to "enabled", all users are allowed to use userfaultfd
    syscalls.

  - When set to "kvm", all unprivileged users are forbidden to use the
    userfaultfd syscalls, except the user who has permission to open
    /dev/kvm.

This new flag can add one more layer of security to reduce the attack
surface of the kernel by abusing userfaultfd.  Here we grant the
thread userfaultfd permission by checking against CAP_SYS_PTRACE
capability.  By default, the value is "disabled" which is the most
strict policy.  Distributions can have their own perferred value.

The "kvm" entry is a bit special here only to make sure that existing
users like QEMU/KVM won't break by this newly introduced flag.  What
we need to do is simply set the "unprivileged_userfaultfd" flag to
"kvm" here to automatically grant userfaultfd permission for processes
like QEMU/KVM without extra code to tweak these flags in the admin
code.

Patch 1:  The interface patch to introduce the flag

Patch 2:  The KVM related changes to detect opening of /dev/kvm

Patch 3:  Apply the flag to userfaultfd syscalls

All comments would be greatly welcomed.  Thanks,

Peter Xu (3):
  userfaultfd/sysctl: introduce unprivileged_userfaultfd
  kvm/mm: introduce MMF_USERFAULTFD_ALLOW flag
  userfaultfd: apply unprivileged_userfaultfd check

 fs/userfaultfd.c               | 121 +++++++++++++++++++++++++++++++++
 include/linux/sched/coredump.h |   1 +
 include/linux/userfaultfd_k.h  |   5 ++
 init/Kconfig                   |  11 +++
 kernel/sysctl.c                |  11 +++
 virt/kvm/kvm_main.c            |   7 ++
 6 files changed, 156 insertions(+)
```
