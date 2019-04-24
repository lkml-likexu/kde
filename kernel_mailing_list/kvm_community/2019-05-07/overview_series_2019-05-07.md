#### [PATCH] KVM: fix 'release' method of KVM device
##### From: =?utf-8?q?C=C3=A9dric_Le_Goater?= <clg@kaod.org>

```c
There is no need to test for the device pointer validity when releasing
a KVM device. The file descriptor should identify it safely.

Signed-off-by: Cédric Le Goater <clg@kaod.org>
---

 Fixes http://patchwork.ozlabs.org/patch/1087506/
 https://git.kernel.org/pub/scm/linux/kernel/git/paulus/powerpc.git/commit/?h=kvm-ppc-next&id=2bde9b3ec8bdf60788e9e2ce8c07a2f8d6003dbd

 virt/kvm/kvm_main.c | 6 ------
 1 file changed, 6 deletions(-)

```
#### [PATCH 01/15] KVM: nVMX: Don't dump VMCS if virtual APIC page can't be mapped
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
... as a malicious userspace can run a toy guest to generate invalid
virtual-APIC page addresses in L1, i.e. flood the kernel log with error
messages.

Fixes: 690908104e39d ("KVM: nVMX: allow tests to use bad virtual-APIC page address")
Cc: stable@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 3 ---
 1 file changed, 3 deletions(-)

```
#### [PATCH 1/7] KVM: nVMX: Intercept VMWRITEs to read-only shadow VMCS fields
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Allowing L1 to VMWRITE read-only fields is only beneficial in a double
nesting scenario, e.g. no sane VMM will VMWRITE VM_EXIT_REASON in normal
non-nested operation.  Intercepting RO fields means KVM doesn't need to
sync them from the shadow VMCS to vmcs12 when running L2.  The obvious
downside is that L1 will VM-Exit more often when running L3, but it's
likely safe to assume most folks would happily sacrifice a bit of L3
performance, which may not even be noticeable in the grande scheme, to
improve L2 performance across the board.

Not intercepting fields tagged read-only also allows for additional
optimizations, e.g. marking GUEST_{CS,SS}_AR_BYTES as SHADOW_FIELD_RO
since those fields are rarely written by a VMMs, but read frequently.

When utilizing a shadow VMCS with asymmetric R/W and R/O bitmaps, fields
that cause VM-Exit on VMWRITE but not VMREAD need to be propagated to
the shadow VMCS during VMWRITE emulation, otherwise a subsequence VMREAD
from L1 will consume a stale value.

Note, KVM currently utilizes asymmetric bitmaps when "VMWRITE any field"
is not exposed to L1, but only so that it can reject the VMWRITE, i.e.
propagating the VMWRITE to the shadow VMCS is a new requirement, not a
bug fix.

Eliminating the copying of RO fields reduces the latency of nested
VM-Entry (copy_shadow_to_vmcs12()) by ~100 cycles (plus 40-50 cycles
if/when the AR_BYTES fields are exposed RO).

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 72 +++++++++++++++++----------------------
 1 file changed, 31 insertions(+), 41 deletions(-)

```
#### [PATCH 01/13] KVM: nVMX: Use adjusted pin controls for vmcs02
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
KVM provides a module parameter to allow disabling virtual NMI support
to simplify testing (hardware *without* virtual NMI support is virtually
non-existent, pun intended).  When preparing vmcs02, use the accessor
for pin controls to ensure that the module param is respected for nested
guests.

Opportunistically swap the order of applying L0's and L1's pin controls
to better align with other controls and to prepare for a future patche
that will ignore L1's, but not L0's, preemption timer flag.

Fixes: d02fcf50779ec ("kvm: vmx: Allow disabling virtual NMI support")
Cc: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c | 5 ++---
 arch/x86/kvm/vmx/vmx.c    | 2 +-
 arch/x86/kvm/vmx/vmx.h    | 1 +
 3 files changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] [next] KVM: lapic: allow setting apic debug dynamically
##### From: Yi Wang <wang.yi59@zte.com.cn>

```c
There are many functions invoke apic_debug(), which is defined
as a null function by default, and that's incovenient for debuging
lapic.

This patch allows setting apic debug according to add a apic_dbg
parameter of kvm.

Signed-off-by: Yi Wang <wang.yi59@zte.com.cn>
---
 arch/x86/kvm/lapic.c | 7 ++++++-
 1 file changed, 6 insertions(+), 1 deletion(-)

```
#### [PATCH RFC] vhost: don't use kmap() to log dirty pages
##### From: Jason Wang <jasowang@redhat.com>

```c
Vhost log dirty pages directly to a userspace bitmap through GUP and
kmap_atomic() since kernel doesn't have a set_bit_to_user()
helper. This will cause issues for the arch that has virtually tagged
caches. The way to fix is to keep using userspace virtual address.

Fortunately, futex has a cmpxchg to userspace memory helper
futex_atomic_cmpxchg_inatomic(). So switch to use it to exchange the
userspace bitmap with zero, set the bit and then write it back through
put_user().

Note: there're archs (few non popular ones) that don't implement
futex helper, we can't log dirty pages. We can fix them on top or
simply disable LOG_ALL features of vhost.

Cc: Christoph Hellwig <hch@infradead.org>
Cc: James Bottomley <James.Bottomley@HansenPartnership.com>
Cc: Andrea Arcangeli <aarcange@redhat.com>
Fixes: 3a4d5c94e9593 ("vhost_net: a kernel-level virtio server")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vhost.c | 27 +++++++++++++++------------
 1 file changed, 15 insertions(+), 12 deletions(-)

```
#### [PATCH] sched: introduce configurable delay before entering idle
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
Certain workloads perform poorly on KVM compared to baremetal
due to baremetal's ability to perform mwait on NEED_RESCHED
bit of task flags (therefore skipping the IPI).

This patch introduces a configurable busy-wait delay before entering the
architecture delay routine, allowing wakeup IPIs to be skipped 
(if the IPI happens in that window).

The real-life workload which this patch improves performance
is SAP HANA (by 5-10%) (for which case setting idle_spin to 30 
is sufficient).

This patch improves the attached server.py and client.py example 
as follows:

Host:                           31.814230202231556
Guest:                          38.17718765199993       (83 %)
Guest, idle_spin=50us:          33.317709898000004      (95 %)
Guest, idle_spin=220us:         32.27826551499999       (98 %)

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>
---
 kernel/sched/idle.c |   86 ++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 86 insertions(+)
#!/bin/python3

import socket
import sys
import struct, fcntl, os
import os, errno, time
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('127.0.0.1', 999)
print ("connecting to 127.0.0.1")
sock.connect(server_address)

nr_writes = 0

start_time = time.clock_gettime(time.CLOCK_MONOTONIC)

while nr_writes < 90000:
	data = sock.recv(4096)
	if len(data) == 0:
		print("connection closed!\n");
		exit(0);
	# sleep 20us
	time.sleep(20/1000000)
	sock.send(data)
	nr_writes = nr_writes+1

end_time = time.clock_gettime(time.CLOCK_MONOTONIC)
delta = end_time - start_time
print(delta)
#!/bin/python3

import socket
import sys
import struct, fcntl, os
import os, errno, time
import time

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(('127.0.0.1', 999))
sock.listen(10)
conn, addr = sock.accept()

nr_written=0
while 1:
	conn.sendall(b"a response line of text")
	data = conn.recv(1024)
	if not data:
        	break
	# sleep 200us
	time.sleep(200/1000000)
	nr_written = nr_written+1

```
