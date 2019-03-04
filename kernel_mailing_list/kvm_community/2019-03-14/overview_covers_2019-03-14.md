

#### [PATCH 0/7] cpufreq: Call transition notifier only once for each
##### From: Viresh Kumar <viresh.kumar@linaro.org>

```c

Currently we call the cpufreq transition notifiers once for each CPU of
the policy->cpus cpumask, which isn't that efficient. This patchset
tries to simplify that by adding another field in struct cpufreq_freqs,
cpus, so the callback has all the information available with a single
call for each policy.

I have tested this on arm64 platform and is compile tested for other
platforms. This has gone through 0-day testing as well, I have pushed my
branch over a week back to the public tree which gets tested by 0-day
bot.

FWIW, it maybe possible to make the callback implementation more
efficient now that they are called only once for each policy, but this
patchset only did the minimum amount of changes to make sure we don't
end up breaking otherwise working code.
---
viresh

Viresh Kumar (7):
  cpufreq: Pass policy->related_cpus to transition notifiers
  ARM: smp: Update cpufreq transition notifier to handle multiple CPUs
  ARM: twd: Update cpufreq transition notifier to handle multiple CPUs
  sparc64: Update cpufreq transition notifier to handle multiple CPUs
  x86/tsc: Update cpufreq transition notifier to handle multiple CPUs
  KVM: x86: Update cpufreq transition notifier to handle multiple CPUs
  cpufreq: Call transition notifiers only once for each policy

 arch/arm/kernel/smp.c       | 23 ++++++++++++++---------
 arch/arm/kernel/smp_twd.c   |  9 ++++++---
 arch/sparc/kernel/time_64.c | 28 ++++++++++++++++------------
 arch/x86/kernel/tsc.c       | 31 ++++++++++++++++++++-----------
 arch/x86/kvm/x86.c          | 31 ++++++++++++++++++++-----------
 drivers/cpufreq/cpufreq.c   | 19 ++++++++++---------
 include/linux/cpufreq.h     |  2 +-
 7 files changed, 87 insertions(+), 56 deletions(-)
```
