

#### [PATCH kvmtool 0/2] Fix kvm__pause races
##### From: Julien Thierry <julien.thierry@arm.com>

```c

Hi,

Here are some fixes for potential races I found in the pause/resume
code.

Cheers,

Julien

-->

Julien Thierry (2):
  kvm: Do not pause already paused vcpus
  kvm-cpu: Pause vCPU in signal handler

 kvm-cpu.c | 17 ++++++++++++-----
 kvm.c     |  5 ++++-
 2 files changed, 16 insertions(+), 6 deletions(-)
---
1.9.1
```
