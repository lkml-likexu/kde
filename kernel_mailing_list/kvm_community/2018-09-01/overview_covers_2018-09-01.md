

#### [RFC][PATCH 0/5] introduce /proc/PID/idle_bitmap
##### From: Fengguang Wu <fengguang.wu@intel.com>

```c

This new /proc/PID/idle_bitmap interface aims to complement the current global
/sys/kernel/mm/page_idle/bitmap. To enable efficient user space driven migrations.

The pros and cons will be discussed in changelog of "[PATCH] proc: introduce
/proc/PID/idle_bitmap". The driving force is to improve efficiency by 10+
times, so that hot/cold page tracking can be done in some regular intervals in
user space w/o too much overheads. Making it possible for some user space
daemon to do regular page migration between NUMA nodes of different speeds.

Note it's not about NUMA migration between local and remote nodes -- we already
have NUMA balancing for that. This interface and user space migration daemon
targets for NUMA nodes made of different mediums -- ie. DIMM and NVDIMM(*) --
with larger performance gaps. Basic policy will be "move hot pages to DIMM;
cold pages to NVDIMM".

Since NVDIMMs size can easily reach several Terabytes, working set tracking
efficiency will matter and be challeging.

(*) Here we use persistent memory (PMEM) w/o using its persistence.
Persistence is good to have, however it requires modifying applications.
Upcoming NVDIMM products like Intel Apache Pass (AEP) will be more cost and energy
effective than DRAM, but slower. Merely using it in form of NUMA memory node
could immediately benefit many workloads. For example, warm but not hot apps,
workloads with sharp hot/cold page distribution (good for migration), or relies
more on memory size than latency and bandwidth, and do more reads than writes.

This is an early RFC version to collect feedbacks. It's complete enough to demo
the basic ideas and performance, however not usable yet.

Regards,
Fengguang
```
