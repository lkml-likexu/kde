

#### [PATCH kvmtool v2 0/2] Automatically clean up ghost socket files
##### From: Andre Przywara <andre.przywara@arm.com>

```c

kvmtool is creating UNIX socket inodes to communicate between a running
instance and a debug command issued by another lkvm process.
When kvmtool (or the kernel) crashes, those files are not cleaned up and
cause all kind of annoyances.
Those two patches delete leftover socket files on calling "lkvm list",
also remove an existing one (then reusing the same name) when creating
a guest.
This avoids random breakages when running kvmtool, and helps to run it
from scripts.

Cheers,
Andre

Changelog:
v1 ... v2:
- Printing name of each remove socket file on lkvm list, removing summary.
- Printing name of removed socket file on lkvm run.

Andre Przywara (2):
  list: Clean up ghost socket files
  run: Check for ghost socket file upon VM creation

 kvm-ipc.c | 37 ++++++++++++++++++++++++++++++-------
 1 file changed, 30 insertions(+), 7 deletions(-)
```
