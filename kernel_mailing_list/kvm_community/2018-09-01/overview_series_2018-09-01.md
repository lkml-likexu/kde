#### [RFC][PATCH 1/5] [PATCH 1/5] kvm: register in task_structReferences: <20180901112818.126790961@intel.com>
##### From: Fengguang Wu <fengguang.wu@intel.com>

```c
The added pointer will be used by the /proc/PID/idle_bitmap code to
quickly identify QEMU task and walk EPT/NPT accordingly. For virtual
machines, the A bits will be set in guest page tables and EPT/NPT,
rather than the QEMU task page table.

This costs 8 bytes in task_struct which could be wasteful for the
majority normal tasks. The alternative is to add a flag only, and
let it find the corresponding VM in kvm vm_list.

Signed-off-by: Fengguang Wu <fengguang.wu@intel.com>
---
 include/linux/sched.h | 10 ++++++++++
 virt/kvm/kvm_main.c   |  1 +
 2 files changed, 11 insertions(+)

```
