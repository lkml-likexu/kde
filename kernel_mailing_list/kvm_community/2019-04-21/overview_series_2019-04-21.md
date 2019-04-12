#### [PATCH] tools/kvm_stat: fix fields filter for child events
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c
From: Stefan Raspl <stefan.raspl@de.ibm.com>

The fields filter would not work with child fields, as the respective
parents would not be included. No parents displayed == no childs displayed.
To reproduce, run on s390 (would work on other platforms, too, but would
require a different filter name):
- Run 'kvm_stat -d'
- Press 'f'
- Enter 'instruct'
Notice that events like instruction_diag_44 or instruction_diag_500 are not
displayed - the output remains empty.
With this patch, we will filter by matching events and their parents.
However, consider the following example where we filter by
instruction_diag_44:

  kvm statistics - summary
                   regex filter: instruction_diag_44
   Event                                         Total %Total CurAvg/s
   exit_instruction                                276  100.0       12
     instruction_diag_44                           256   92.8       11
   Total                                           276              12

Note that the parent ('exit_instruction') displays the total events, but
the childs listed do not match its total (256 instead of 276). This is
intended (since we're filtering all but one child), but might be confusing
on first sight.

Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
---
 tools/kvm/kvm_stat/kvm_stat     | 16 ++++++++++++----
 tools/kvm/kvm_stat/kvm_stat.txt |  2 ++
 2 files changed, 14 insertions(+), 4 deletions(-)

```
