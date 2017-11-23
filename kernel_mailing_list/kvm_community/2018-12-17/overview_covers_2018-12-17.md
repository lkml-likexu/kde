

#### [kvm-unit-tests v3 PATCH 0/2] s390x: try !FORCE SCLP read SCP info if
##### From: David Hildenbrand <david@redhat.com>

```c

Try to mimic what the Linux kernel does when trying to read the SCP
info via SCLP. See patch #2 for details.

v2 -> v3:
- Move cleanups to separate patch
- Don't touch unrelated code, Janosch will clean these up
- Don't set SCLP_CM2_VARIABLE_LENGTH_RESPONSE

David Hildenbrand (2):
  s390x: cleanup and add SCLP defines
  s390x: try !FORCE SCLP read SCP info if FORCED is unknown

 lib/s390x/sclp.c | 23 +++++++++++++++++++++--
 lib/s390x/sclp.h | 13 +++++++++----
 2 files changed, 30 insertions(+), 6 deletions(-)
```
