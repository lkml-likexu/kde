#### [PULL 1/7] i386: correct cpu_x86_cpuid(0xd)
##### From: Eduardo Habkost <ehabkost@redhat.com>

```c
From: Sebastian Andrzej Siewior <bigeasy@linutronix.de>

Intel SDM says for CPUID function 0DH, sub-function 0:

| • ECX enumerates the size (in bytes) required by the XSAVE instruction for an
|   XSAVE area containing all the user state components supported by this
|   processor.
| • EBX enumerates the size (in bytes) required by the XSAVE instruction for an
|   XSAVE area containing all the user state components corresponding to bits
|   currently set in XCR0.

Signed-off-by: Sebastian Andrzej Siewior <bigeasy@linutronix.de>
Message-Id: <20180928104319.3296-1-bigeasy@linutronix.de>
Reviewed-by: Eduardo Habkost <ehabkost@redhat.com>
Signed-off-by: Eduardo Habkost <ehabkost@redhat.com>
---
 target/i386/cpu.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
