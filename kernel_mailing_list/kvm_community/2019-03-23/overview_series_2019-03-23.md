#### [RFC] [PATCH v2 1/5] perf/x86: avoid host changing counter state for kvm_intel events holder
##### From: Like Xu <like.xu@linux.intel.com>

```c
When an perf_event is used by intel vPMU, the vPMU would be responsible
for updating its event_base and config_base. Just checking the writes not
including reading helps perf_events run as usual.

Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/events/core.c       | 37 +++++++++++++++++++++++++++++++++----
 arch/x86/events/intel/core.c |  5 +++--
 arch/x86/events/perf_event.h | 13 +++++++++----
 3 files changed, 45 insertions(+), 10 deletions(-)

```
