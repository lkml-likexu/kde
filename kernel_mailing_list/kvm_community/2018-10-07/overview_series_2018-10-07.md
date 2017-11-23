#### [PATCH] drivers/vfio: Fix a redundant copy bug
##### From: Wenwen Wang <wang6495@umn.edu>

```c
In vfio_spapr_iommu_eeh_ioctl(), if the ioctl command is VFIO_EEH_PE_OP,
the user-space buffer 'arg' is copied to the kernel object 'op' and the
'argsz' and 'flags' fields of 'op' are checked. If the check fails, an
error code EINVAL is returned. Otherwise, 'op.op' is further checked
through a switch statement to invoke related handlers. If 'op.op' is
VFIO_EEH_PE_INJECT_ERR, the whole user-space buffer 'arg' is copied again
to 'op' to obtain the err information. However, in the following execution
of this case, the fields of 'op', except the field 'err', are actually not
used. That is, the second copy has a redundant part. Therefore, for both
performance and security reasons, the redundant part of the second copy
should be removed.

This patch removes such a part in the second copy. It only copies the 'err'
information from the buffer 'arg'.

Signed-off-by: Wenwen Wang <wang6495@umn.edu>
---
 drivers/vfio/vfio_spapr_eeh.c | 6 +++---
 1 file changed, 3 insertions(+), 3 deletions(-)

```
