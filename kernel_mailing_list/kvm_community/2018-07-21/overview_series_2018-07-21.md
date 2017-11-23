#### [kvm-unit-tests PATCH 1/2] x86: io: fix 8250 serial controller initialization
##### From: Eugene Korenevsky <ekorenevsky@gmail.com>

```c
These changes make serial controller working at real hardware and BOCHS:
- Disable interrupts
- Set up LCR, FCR, MCR properly

Signed-off-by: Eugene Korenevsky <ekorenevsky@gmail.com>
---
 lib/x86/io.c | 9 +++++++++
 1 file changed, 9 insertions(+)

```
