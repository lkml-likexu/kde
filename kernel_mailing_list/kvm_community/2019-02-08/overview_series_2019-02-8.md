#### [kvm-unit-tests PATCH] x86/apic: wait for wrap around in lapic timer periodic test
##### From: Evgeny Yakovlev <wrfsh@yandex-team.ru>

```c
We are seeing very rare test failures in apic/split-apic with the
following: "FAIL: TMCCT should be reset to the initial-count". We are
running on 4.14 kernels and this problem occurs sporadically although we
didn't try to reproduce it on any other stable kernel branch.

It looks like under KVM lapic timer in periodic mode may return several
consecutive 0 values in apic_get_tmccr when hrtimer async callback is still
restarting the hrtimer and recalculating expiration_time value but
apic_get_tmccr is seeing ktime_now() already ahead of (still old)
expiration_time value. After a couple of 0-es from TMCCR everything
goes back to normal.

This change forces test_apic_change_mode test to wait specifically for
lapic timer wrap around skipping zero TMCCR values in one case when we are
testing for timer in periodic mode to correctly reload TMCCR from TMICR.
If timer mode change is indeed broken and TMCCR is not reset then we
will see apic test timeout.

Signed-off-by: Evgeny Yakovlev <wrfsh@yandex-team.ru>
---
 x86/apic.c | 23 +++++++++++++++++++++--
 1 file changed, 21 insertions(+), 2 deletions(-)

```
