#### [PATCH kernel v6.1 20/20 REPOST] vfio_pci: Add NVIDIA GV100GL [Tesla V100 SXM2] subdriver
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
POWER9 Witherspoon machines come with 4 or 6 V100 GPUs which are not
pluggable PCIe devices but still have PCIe links which are used
for config space and MMIO. In addition to that the GPUs have 6 NVLinks
which are connected to other GPUs and the POWER9 CPU. POWER9 chips
have a special unit on a die called an NPU which is an NVLink2 host bus
adapter with p2p connections to 2 to 3 GPUs, 3 or 2 NVLinks to each.
These systems also support ATS (address translation services) which is
a part of the NVLink2 protocol. Such GPUs also share on-board RAM
(16GB or 32GB) to the system via the same NVLink2 so a CPU has
cache-coherent access to a GPU RAM.

This exports GPU RAM to the userspace as a new VFIO device region. This
preregisters the new memory as device memory as it might be used for DMA.
This inserts pfns from the fault handler as the GPU memory is not onlined
until the vendor driver is loaded and trained the NVLinks so doing this
earlier causes low level errors which we fence in the firmware so
it does not hurt the host system but still better be avoided; for the same
reason this does not map GPU RAM into the host kernel (usual thing for
emulated access otherwise).

This exports an ATSD (Address Translation Shootdown) register of NPU which
allows TLB invalidations inside GPU for an operating system. The register
conveniently occupies a single 64k page. It is also presented to
the userspace as a new VFIO device region. One NPU has 8 ATSD registers,
each of them can be used for TLB invalidation in a GPU linked to this NPU.
This allocates one ATSD register per an NVLink bridge allowing passing
up to 6 registers. Due to the host firmware bug (just recently fixed),
only 1 ATSD register per NPU was actually advertised to the host system
so this passes that alone register via the first NVLink bridge device in
the group which is still enough as QEMU collects them all back and
presents to the guest via vPHB to mimic the emulated NPU PHB on the host.

In order to provide the userspace with the information about GPU-to-NVLink
connections, this exports an additional capability called "tgt"
(which is an abbreviated host system bus address). The "tgt" property
tells the GPU its own system address and allows the guest driver to
conglomerate the routing information so each GPU knows how to get directly
to the other GPUs.

For ATS to work, the nest MMU (an NVIDIA block in a P9 CPU) needs to
know LPID (a logical partition ID or a KVM guest hardware ID in other
words) and PID (a memory context ID of a userspace process, not to be
confused with a linux pid). This assigns a GPU to LPID in the NPU and
this is why this adds a listener for KVM on an IOMMU group. A PID comes
via NVLink from a GPU and NPU uses a PID wildcard to pass it through.

This requires coherent memory and ATSD to be available on the host as
the GPU vendor only supports configurations with both features enabled
and other configurations are known not to work. Because of this and
because of the ways the features are advertised to the host system
(which is a device tree with very platform specific properties),
this requires enabled POWERNV platform.

The V100 GPUs do not advertise any of these capabilities via the config
space and there are more than just one device ID so this relies on
the platform to tell whether these GPUs have special abilities such as
NVLinks.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
---
Changes:
v6.1:
* fixed outdated comment about VFIO_REGION_INFO_CAP_NVLINK2_LNKSPD

v6:
* reworked capabilities - tgt for nvlink and gpu and link-speed
for nvlink only

v5:
* do not memremap GPU RAM for emulation, map it only when it is needed
* allocate 1 ATSD register per NVLink bridge, if none left, then expose
the region with a zero size
* separate caps per device type
* addressed AW review comments

v4:
* added nvlink-speed to the NPU bridge capability as this turned out to
be not a constant value
* instead of looking at the exact device ID (which also changes from system
to system), now this (indirectly) looks at the device tree to know
if GPU and NPU support NVLink

v3:
* reworded the commit log about tgt
* added tracepoints (do we want them enabled for entire vfio-pci?)
* added code comments
* added write|mmap flags to the new regions
* auto enabled VFIO_PCI_NVLINK2 config option
* added 'tgt' capability to a GPU so QEMU can recreate ibm,npu and ibm,gpu
references; there are required by the NVIDIA driver
* keep notifier registered only for short time
---
 drivers/vfio/pci/Makefile           |   1 +
 drivers/vfio/pci/trace.h            | 102 ++++++
 drivers/vfio/pci/vfio_pci_private.h |  14 +
 include/uapi/linux/vfio.h           |  37 +++
 drivers/vfio/pci/vfio_pci.c         |  27 +-
 drivers/vfio/pci/vfio_pci_nvlink2.c | 482 ++++++++++++++++++++++++++++
 drivers/vfio/pci/Kconfig            |   6 +
 7 files changed, 667 insertions(+), 2 deletions(-)
 create mode 100644 drivers/vfio/pci/trace.h
 create mode 100644 drivers/vfio/pci/vfio_pci_nvlink2.c

```
#### [PATCH kvmtool v3 1/9] arm: Allow use of hugepage with 16K pagesize host
##### From: Julien Grall <julien.grall@arm.com>

```c
From: Suzuki K Poulose <suzuki.poulose@arm.com>

With 16K pagesize, the hugepage size is 32M. Align the guest
memory to the hugepagesize for 16K.

Cc: Marc Zyngier <marc.zyngier@arm.com>
Cc: Andre Przywara <andre.przywara@arm.com>
Cc: Will Deacon <will.deacon@arm.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Signed-off-by: Julien Grall <julien.grall@arm.com>
---
 arm/kvm.c | 12 ++++++++++--
 1 file changed, 10 insertions(+), 2 deletions(-)

```
#### [PATCH 01/11] KVM: VMX: Explicitly reference RCX as the vmx_vcpu pointer in asm blobs
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Use '%% " _ASM_CX"' instead of '%0' to dereference RCX, i.e. the
'struct vmx_vcpu' pointer, in the VM-Enter asm blobs of vmx_vcpu_run()
and nested_vmx_check_vmentry_hw().  Using the symbolic name means that
adding/removing an output parameter(s) requires "rewriting" almost all
of the asm blob, which makes it nearly impossible to understand what's
being changed in even the most minor patches.

Opportunistically improve the code comments.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/vmx/nested.c |  6 +--
 arch/x86/kvm/vmx/vmx.c    | 86 +++++++++++++++++++++------------------
 2 files changed, 50 insertions(+), 42 deletions(-)

```
#### [PATCH] KVM: x86: Use jmp to invoke kvm_spurious_fault() from .fixup
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
____kvm_handle_fault_on_reboot() provides a generic exception fixup
handler that is used to cleanly handle faults on VMX/SVM instructions
during reboot (or at least try to).  If there isn't a reboot in
progress, ____kvm_handle_fault_on_reboot() treats any exception as
fatal to KVM and invokes kvm_spurious_fault(), which in turn generates
a BUG() to get a stack trace and die.

When it was originally added by commit 4ecac3fd6dc2 ("KVM: Handle
virtualization instruction #UD faults during reboot"), the "call" to
kvm_spurious_fault() was handcoded as PUSH+JMP, where the PUSH'd value
is the RIP of the faulting instructing.

The PUSH+JMP trickery is necessary because the exception fixup handler
code lies outside of its associated function, e.g. right after the
function.  An actual CALL from the .fixup code would show a slightly
bogus stack trace, e.g. an extra "random" function would be inserted
into the trace, as the return RIP on the stack would point to no known
function (and the unwinder will likely try to guess who owns the RIP).

Unfortunately, the JMP was replaced with a CALL when the macro was
reworked to not spin indefinitely during reboot (commit b7c4145ba2eb
"KVM: Don't spin on virt instruction faults during reboot").  This
causes the aforementioned behavior where a bogus function is inserted
into the stack trace, e.g. my builds like to blame free_kvm_area().

Revert the CALL back to a JMP.  The changelog for commit b7c4145ba2eb
("KVM: Don't spin on virt instruction faults during reboot") contains
nothing that indicates the switch to CALL was deliberate.  This is
backed up by the fact that the PUSH <insn RIP> was left intact.

Note that an alternative to the PUSH+JMP magic would be to JMP back
to the "real" code and CALL from there, but that would require adding
a JMP in the non-faulting path to avoid calling kvm_spurious_fault()
and would add no value, i.e. the stack trace would be the same.

Using CALL:

------------[ cut here ]------------
kernel BUG at /home/sean/go/src/kernel.org/linux/arch/x86/kvm/x86.c:356!
invalid opcode: 0000 [#1] SMP
CPU: 4 PID: 1057 Comm: qemu-system-x86 Not tainted 4.20.0-rc6+ #75
Hardware name: QEMU Standard PC (Q35 + ICH9, 2009), BIOS 0.0.0 02/06/2015
RIP: 0010:kvm_spurious_fault+0x5/0x10 [kvm]
Code: <0f> 0b 66 0f 1f 84 00 00 00 00 00 0f 1f 44 00 00 41 55 49 89 fd 41
RSP: 0018:ffffc900004bbcc8 EFLAGS: 00010046
RAX: 0000000000000000 RBX: 0000000000000000 RCX: ffffffffffffffff
RDX: 0000000000000000 RSI: 0000000000000000 RDI: 0000000000000000
RBP: ffff888273fd8000 R08: 00000000000003e8 R09: 0000000000000000
R10: 0000000000000000 R11: 0000000000000784 R12: ffffc90000371fb0
R13: 0000000000000000 R14: 000000026d763cf4 R15: ffff888273fd8000
FS:  00007f3d69691700(0000) GS:ffff888277800000(0000) knlGS:0000000000000000
CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
CR2: 000055f89bc56fe0 CR3: 0000000271a5a001 CR4: 0000000000362ee0
Call Trace:
 free_kvm_area+0x1044/0x43ea [kvm_intel]
 ? vmx_vcpu_run+0x156/0x630 [kvm_intel]
 ? kvm_arch_vcpu_ioctl_run+0x447/0x1a40 [kvm]
 ? kvm_vcpu_ioctl+0x368/0x5c0 [kvm]
 ? kvm_vcpu_ioctl+0x368/0x5c0 [kvm]
 ? __set_task_blocked+0x38/0x90
 ? __set_current_blocked+0x50/0x60
 ? __fpu__restore_sig+0x97/0x490
 ? do_vfs_ioctl+0xa1/0x620
 ? __x64_sys_futex+0x89/0x180
 ? ksys_ioctl+0x66/0x70
 ? __x64_sys_ioctl+0x16/0x20
 ? do_syscall_64+0x4f/0x100
 ? entry_SYSCALL_64_after_hwframe+0x44/0xa9
Modules linked in: vhost_net vhost tap kvm_intel kvm irqbypass bridge stp llc
---[ end trace 9775b14b123b1713 ]---

Using JMP:

------------[ cut here ]------------
kernel BUG at /home/sean/go/src/kernel.org/linux/arch/x86/kvm/x86.c:356!
invalid opcode: 0000 [#1] SMP
CPU: 6 PID: 1067 Comm: qemu-system-x86 Not tainted 4.20.0-rc6+ #75
Hardware name: QEMU Standard PC (Q35 + ICH9, 2009), BIOS 0.0.0 02/06/2015
RIP: 0010:kvm_spurious_fault+0x5/0x10 [kvm]
Code: <0f> 0b 66 0f 1f 84 00 00 00 00 00 0f 1f 44 00 00 41 55 49 89 fd 41
RSP: 0018:ffffc90000497cd0 EFLAGS: 00010046
RAX: 0000000000000000 RBX: 0000000000000000 RCX: ffffffffffffffff
RDX: 0000000000000000 RSI: 0000000000000000 RDI: 0000000000000000
RBP: ffff88827058bd40 R08: 00000000000003e8 R09: 0000000000000000
R10: 0000000000000000 R11: 0000000000000784 R12: ffffc90000369fb0
R13: 0000000000000000 R14: 00000003c8fc6642 R15: ffff88827058bd40
FS:  00007f3d7219e700(0000) GS:ffff888277900000(0000) knlGS:0000000000000000
CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
CR2: 00007f3d64001000 CR3: 0000000271c6b004 CR4: 0000000000362ee0
Call Trace:
 vmx_vcpu_run+0x156/0x630 [kvm_intel]
 ? kvm_arch_vcpu_ioctl_run+0x447/0x1a40 [kvm]
 ? kvm_vcpu_ioctl+0x368/0x5c0 [kvm]
 ? kvm_vcpu_ioctl+0x368/0x5c0 [kvm]
 ? __set_task_blocked+0x38/0x90
 ? __set_current_blocked+0x50/0x60
 ? __fpu__restore_sig+0x97/0x490
 ? do_vfs_ioctl+0xa1/0x620
 ? __x64_sys_futex+0x89/0x180
 ? ksys_ioctl+0x66/0x70
 ? __x64_sys_ioctl+0x16/0x20
 ? do_syscall_64+0x4f/0x100
 ? entry_SYSCALL_64_after_hwframe+0x44/0xa9
Modules linked in: vhost_net vhost tap kvm_intel kvm irqbypass bridge stp llc
---[ end trace f9daedb85ab3ddba ]---

Fixes: b7c4145ba2eb ("KVM: Don't spin on virt instruction faults during reboot")
Cc: stable@vger.kernel.org
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/include/asm/kvm_host.h | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH] MAINTAINERS: Add arch/x86/kvm sub-directories to existing KVM/x86 entry
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
A series currently sitting in KVM's queue for 4.21 moves the bulk of
KVM's VMX code to a dedicated VMX sub-directory[1].  As a result,
get_maintainers.pl doesn't get any hits on the newly relocated VMX
files when the script is run with --pattern-depth=1.

Add all arch/x86/kvm sub-directories to the existing MAINTAINERS entry
for KVM/x86 instead of arch/x86/kvm/vmx as other code, e.g. SVM, may
get similar treatment in the near future.

[1] https://patchwork.kernel.org/cover/10710751/

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 MAINTAINERS | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH kernel v7 01/20] powerpc/ioda/npu: Call skiboot's hot reset hook when disabling NPU2
##### From: Alexey Kardashevskiy <aik@ozlabs.ru>

```c
The skiboot firmware has a hot reset handler which fences the NVIDIA V100
GPU RAM on Witherspoons and makes accesses no-op instead of throwing HMIs:
https://github.com/open-power/skiboot/commit/fca2b2b839a67

Now we are going to pass V100 via VFIO which most certainly involves
KVM guests which are often terminated without getting a chance to offline
GPU RAM so we end up with a running machine with misconfigured memory.
Accessing this memory produces hardware management interrupts (HMI)
which bring the host down.

To suppress HMIs, this wires up this hot reset hook to vfio_pci_disable()
via pci_disable_device() which switches NPU2 to a safe mode and prevents
HMIs.

Signed-off-by: Alexey Kardashevskiy <aik@ozlabs.ru>
Acked-by: Alistair Popple <alistair@popple.id.au>
Reviewed-by: David Gibson <david@gibson.dropbear.id.au>
---
Changes:
v2:
* updated the commit log
---
 arch/powerpc/platforms/powernv/pci-ioda.c | 10 ++++++++++
 1 file changed, 10 insertions(+)

```
#### [PATCH v3] kvm: selftests: ucall: fix exit mmio address guessing
##### From: Andrew Jones <drjones@redhat.com>

```c
Dan pointed out the unsigned less than zero comparison and Paolo
suggested a different approach to the iteration. I pulled together
something that also ensures we maintain page aligned addresses
by using power-of-two divisors (8 and 16) and fixes two other bugs.
The first other bug was that the start and step calculations were
wrong since they were dividing the number of address bits instead
of the address space. The second other bug was that the guessing
algorithm wasn't considering the valid physical and virtual address
ranges correctly for an identity map. Sigh... Hopefully we've finally
got this thing right!

Reported-by: Dan Carpenter <dan.carpenter@oracle.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/lib/ucall.c | 36 ++++++++++++++-----------
 1 file changed, 21 insertions(+), 15 deletions(-)

```
#### [RFC PATCH v5 01/20] kvm: document the VM introspection API
##### From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>

```c
From: Mihai DONTU <mdontu@bitdefender.com>

This includes the protocol, the commands and events.

Signed-off-by: Adalbert Lazăr <alazar@bitdefender.com>
Signed-off-by: Mihai Donțu <mdontu@bitdefender.com>
---
 Documentation/virtual/kvm/kvmi.rst | 1351 ++++++++++++++++++++++++++++
 1 file changed, 1351 insertions(+)
 create mode 100644 Documentation/virtual/kvm/kvmi.rst

diff --git a/Documentation/virtual/kvm/kvmi.rst b/Documentation/virtual/kvm/kvmi.rst
new file mode 100644
index 000000000000..1cb11fdb2471
--- /dev/null
+++ b/Documentation/virtual/kvm/kvmi.rst
@@ -0,0 +1,1351 @@
+=========================================================
+KVMI - The kernel virtual machine introspection subsystem
+=========================================================
+
+The KVM introspection subsystem provides a facility for applications running
+on the host or in a separate VM, to control the execution of other VM-s
+(pause, resume, shutdown), query the state of the vCPUs (GPRs, MSRs etc.),
+alter the page access bits in the shadow page tables (only for the hardware
+backed ones, eg. Intel's EPT) and receive notifications when events of
+interest have taken place (shadow page table level faults, key MSR writes,
+hypercalls etc.). Some notifications can be responded to with an action
+(like preventing an MSR from being written), others are mere informative
+(like breakpoint events which can be used for execution tracing).
+With few exceptions, all events are optional. An application using this
+subsystem will explicitly register for them.
+
+The use case that gave way for the creation of this subsystem is to monitor
+the guest OS and as such the ABI/API is highly influenced by how the guest
+software (kernel, applications) sees the world. For example, some events
+provide information specific for the host CPU architecture
+(eg. MSR_IA32_SYSENTER_EIP) merely because its leveraged by guest software
+to implement a critical feature (fast system calls).
+
+At the moment, the target audience for KVMI are security software authors
+that wish to perform forensics on newly discovered threats (exploits) or
+to implement another layer of security like preventing a large set of
+kernel rootkits simply by "locking" the kernel image in the shadow page
+tables (ie. enforce .text r-x, .rodata rw- etc.). It's the latter case that
+made KVMI a separate subsystem, even though many of these features are
+available in the device manager (eg. QEMU). The ability to build a security
+application that does not interfere (in terms of performance) with the
+guest software asks for a specialized interface that is designed for minimum
+overhead.
+
+API/ABI
+=======
+
+This chapter describes the VMI interface used to monitor and control local
+guests from a user application.
+
+Overview
+--------
+
+The interface is socket based, one connection for every VM. One end is in the
+host kernel while the other is held by the user application (introspection
+tool).
+
+The initial connection is established by an application running on the host
+(eg. QEMU) that connects to the introspection tool and after a handshake the
+socket is passed to the host kernel making all further communication take
+place between it and the introspection tool. The initiating party (QEMU) can
+close its end so that any potential exploits cannot take a hold of it.
+
+The socket protocol allows for commands and events to be multiplexed over
+the same connection. As such, it is possible for the introspection tool to
+receive an event while waiting for the result of a command. Also, it can
+send a command while the host kernel is waiting for a reply to an event.
+
+The kernel side of the socket communication is blocking and will wait for
+an answer from its peer indefinitely or until the guest is powered off
+(killed), restarted or the peer goes away, at which point it will wake
+up and properly cleanup as if the introspection subsystem has never been
+used on that guest. Obviously, whether the guest can really continue
+normal execution depends on whether the introspection tool has made any
+modifications that require an active KVMI channel.
+
+All messages (commands or events) have a common header::
+
+	struct kvmi_msg_hdr {
+		__u16 id;
+		__u16 size;
+		__u32 seq;
+	};
+
+and all need a reply with the same kind of header, having the same
+sequence number (``seq``) and the same message id (``id``).
+
+Because events from different vCPU threads can send messages at the same
+time and the replies can come in any order, the receiver loop uses the
+sequence number (seq) to identify which reply belongs to which vCPU, in
+order to dispatch the message to the right thread waiting for it.
+
+After ``kvmi_msg_hdr``, ``id`` specific data of ``size`` bytes will
+follow.
+
+The message header and its data must be sent with one ``sendmsg()`` call
+to the socket. This simplifies the receiver loop and avoids
+the reconstruction of messages on the other side.
+
+The wire protocol uses the host native byte-order. The introspection tool
+must check this during the handshake and do the necessary conversion.
+
+A command reply begins with::
+
+	struct kvmi_error_code {
+		__s32 err;
+		__u32 padding;
+	}
+
+followed by the command specific data if the error code ``err`` is zero.
+
+The error code -KVM_ENOSYS (packed in a ``kvmi_error_code``) is returned for
+unsupported commands.
+
+The error code -KVM_EACCES is returned for disallowed commands (see **Hooking**).
+
+The error code is related to the message processing. For all the other
+errors (socket errors, incomplete messages, wrong sequence numbers
+etc.) the socket must be closed. The device manager will be notified
+and it will reconnect.
+
+While all commands will have a reply as soon as possible, the replies
+to events will probably be delayed until a set of (new) commands will
+complete::
+
+   Host kernel               Tool
+   -----------               ----
+   event 1 ->
+                             <- command 1
+   command 1 reply ->
+                             <- command 2
+   command 2 reply ->
+                             <- event 1 reply
+
+If both ends send a message at the same time::
+
+   Host kernel               Tool
+   -----------               ----
+   event X ->                <- command X
+
+the host kernel will reply to 'command X', regardless of the receive time
+(before or after the 'event X' was sent).
+
+As it can be seen below, the wire protocol specifies occasional padding. This
+is to permit working with the data by directly using C structures or to round
+the structure size to a multiple of 8 bytes (64bit) to improve the copy
+operations that happen during ``recvmsg()`` or ``sendmsg()``. The members
+should have the native alignment of the host (4 bytes on x86). All padding
+must be initialized with zero otherwise the respective commands will fail
+with -KVM_EINVAL.
+
+To describe the commands/events, we reuse some conventions from api.txt:
+
+  - Architectures: which instruction set architectures provide this command/event
+
+  - Versions: which versions provide this command/event
+
+  - Parameters: incoming message data
+
+  - Returns: outgoing/reply message data
+
+Handshake
+---------
+
+Although this falls out of the scope of the introspection subsystem, below
+is a proposal of a handshake that can be used by implementors.
+
+Based on the system administration policies, the management tool
+(eg. libvirt) starts device managers (eg. QEMU) with some extra arguments:
+what introspector could monitor/control that specific guest (and how to
+connect to) and what introspection commands/events are allowed.
+
+The device manager will connect to the introspection tool and wait for a
+cryptographic hash of a cookie that should be known by both peers. If the
+hash is correct (the destination has been "authenticated"), the device
+manager will send another cryptographic hash and random salt. The peer
+recomputes the hash of the cookie bytes including the salt and if they match,
+the device manager has been "authenticated" too. This is a rather crude
+system that makes it difficult for device manager exploits to trick the
+introspection tool into believing its working OK.
+
+The cookie would normally be generated by a management tool (eg. libvirt)
+and make it available to the device manager and to a properly authenticated
+client. It is the job of a third party to retrieve the cookie from the
+management application and pass it over a secure channel to the introspection
+tool.
+
+Once the basic "authentication" has taken place, the introspection tool
+can receive information on the guest (its UUID) and other flags (endianness
+or features supported by the host kernel).
+
+In the end, the device manager will pass the file handle (plus the allowed
+commands/events) to KVM, and forget about it. It will be notified by
+KVM when the introspection tool closes the file handle (in case of
+errors), and should reinitiate the handshake.
+
+Once the file handle reaches KVM, the introspection tool should use the
+*KVMI_GET_VERSION* command to get the API version, the commands and the
+events (see *KVMI_CONTROL_VM_EVENTS* and *KVMI_CONTROL_EVENTS*) which
+are allowed for this guest. The error code -KVM_EPERM will be returned
+if the introspection tool uses a command or enables an event which is
+not allowed.
+
+Unhooking
+---------
+
+During a VMI session it is possible for the guest to be patched and for
+some of these patches to "talk" with the introspection tool. It thus
+becomes necessary to remove them before the guest is suspended, moved
+(migrated) or a snapshot with memory is created.
+
+The actions are normally performed by the device manager. In the case
+of QEMU, it will use the *KVM_INTROSPECTION_UNHOOK* ioctl to trigger
+the *KVMI_EVENT_UNHOOK* event and wait for a limited amount of time (a
+few seconds) for a confirmation from the introspection tool
+that is OK to proceed.
+
+Live migrations
+---------------
+
+Before the live migration takes place, the introspection tool has to be
+notified and have a chance to unhook (see **Unhooking**).
+
+The QEMU instance on the receiving end, if configured for KVMI, will need to
+establish a connection to the introspection tool after the migration has
+completed.
+
+Obviously, this creates a window in which the guest is not introspected. The
+user will need to be aware of this detail. Future introspection
+technologies can choose not to disconnect and instead transfer the necessary
+context to the introspection tool at the migration destination via a separate
+channel.
+
+Memory access safety
+--------------------
+
+The KVMI API gives access to the entire guest physical address space but
+provides no information on which parts of it are system RAM and which are
+device-specific memory (DMA, emulated MMIO, reserved by a passthrough
+device etc.). It is up to the user to determine, using the guest operating
+system data structures, the areas that are safe to access (code, stack, heap
+etc.).
+
+Commands
+--------
+
+The following C structures are meant to be used directly when communicating
+over the wire. The peer that detects any size mismatch should simply close
+the connection and report the error.
+
+0. KVMI_GET_VERSION
+-------------------
+
+:Architectures: all
+:Versions: >= 1
+:Parameters: none
+:Returns:
+
+::
+
+	struct kvmi_error_code;
+	struct kvmi_get_version_reply {
+		__u32 version;
+		__u32 commands;
+		__u32 events;
+		__u32 padding;
+	};
+
+Returns the introspection API version, the bit mask with allowed commands
+and the bit mask with allowed events.
+
+These two masks represent all the features allowed by the management tool
+(see **Handshake**) or supported by the host.
+
+The host kernel and the userland can use these macros to check if
+a command/event is allowed for a guest::
+
+	KVMI_ALLOWED_COMMAND(cmd_id, cmd_mask)
+	KVMI_ALLOWED_VM_EVENT(event_id, event_mask)
+	KVMI_ALLOWED_VCPU_EVENT(event_id, event_mask)
+
+This command is always successful.
+
+1. KVMI_GET_GUEST_INFO
+----------------------
+
+:Architectures: x86
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_get_guest_info {
+		__u16 vcpu;
+		__u16 padding[3];
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code;
+	struct kvmi_get_guest_info_reply {
+		__u32 vcpu_count;
+		__u32 padding;
+		__u64 tsc_speed;
+	};
+
+Returns the number of online vCPUs and the TSC frequency (in HZ)
+if available.
+
+The parameter ``vcpu`` must be zero. It is required for consistency with
+all other commands and in the future it might be used to return true
+vCPU-specific information.
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+
+2. KVMI_PAUSE_ALL_VCPUS
+------------------------
+
+:Architecture: all
+:Versions: >= 1
+:Parameters: none
+
+:Returns:
+
+::
+
+	struct kvmi_error_code;
+	struct kvmi_pause_all_vcpus_reply {
+		__u32 vcpu_count;
+		__u32 padding;
+	};
+
+Kicks all the vCPUs from guest. Once this command returns, no VCPU will
+run in guest mode and some of them may be ready to accept introspection
+commands.
+
+This command returns the number of kicked vCPUs. All of these will send
+a *KVMI_EVENT_PAUSE_VCPU* event before entering in guest mode.
+
+Please note that new vCPUs may be created later. The introspector should
+use *KVMI_CONTROL_VM_EVENTS* to enable the *KVMI_EVENT_CREATE_VCPU* event
+in order to stop these new vCPUs as well (by delaying the event reply).
+
+This command is always successful (unless disallowed).
+
+3. KVMI_GET_REGISTERS
+---------------------
+
+:Architectures: x86
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_get_registers {
+		__u16 vcpu;
+		__u16 nmsrs;
+		__u16 padding[2];
+		__u32 msrs_idx[0];
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code;
+	struct kvmi_get_registers_reply {
+		__u32 mode;
+		__u32 padding;
+		struct kvm_regs regs;
+		struct kvm_sregs sregs;
+		struct kvm_msrs msrs;
+	};
+
+For the given vCPU and the ``nmsrs`` sized array of MSRs registers,
+returns the current vCPU mode (in bytes: 2, 4 or 8), the general purpose
+registers, the special registers and the requested set of MSRs.
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EINVAL - one of the indicated MSR-s is invalid
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+* -KVM_ENOMEM - not enough memory to allocate the reply
+
+4. KVMI_SET_REGISTERS
+---------------------
+
+:Architectures: x86
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_set_registers {
+		__u16 vcpu;
+		__u16 padding[3];
+		struct kvm_regs regs;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code
+
+Sets the general purpose registers for the given vCPU. The changes become
+visible to other threads accessing the KVM vCPU structure after the event
+currently being handled is replied to.
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+
+5. KVMI_GET_CPUID
+-----------------
+
+:Architectures: x86
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_get_cpuid {
+		__u16 vcpu;
+		__u16 padding[3];
+		__u32 function;
+		__u32 index;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code;
+	struct kvmi_get_cpuid_reply {
+		__u32 eax;
+		__u32 ebx;
+		__u32 ecx;
+		__u32 edx;
+	};
+
+Returns a CPUID leaf (as seen by the guest OS).
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+* -KVM_ENOENT - the selected leaf is not present or is invalid
+
+6. KVMI_GET_PAGE_ACCESS
+-----------------------
+
+:Architectures: all
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_get_page_access {
+		__u16 vcpu;
+		__u16 count;
+		__u16 view;
+		__u16 padding;
+		__u64 gpa[0];
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code;
+	struct kvmi_get_page_access_reply {
+		__u8 access[0];
+	};
+
+Returns the spte access bits (rwx) for the specified vCPU and for an array of
+``count`` guest physical addresses.
+
+The valid access bits for *KVMI_GET_PAGE_ACCESS* and *KVMI_SET_PAGE_ACCESS*
+are::
+
+	KVMI_PAGE_ACCESS_R
+	KVMI_PAGE_ACCESS_W
+	KVMI_PAGE_ACCESS_X
+
+By default, for any guest physical address, the returned access mode will
+be 'rwx' (all the above bits). If the introspection tool must prevent
+the code execution from a guest page, for example, it should use the
+KVMI_SET_PAGE_ACCESS command to set the 'rw' bits for any guest physical
+addresses contained in that page. Of course, in order to receive
+page fault events when these violations take place, the KVMI_CONTROL_EVENTS
+command must be used to enable this type of event (KVMI_EVENT_PF).
+
+On Intel hardware with multiple EPT views, the ``view`` argument selects the
+EPT view (0 is primary). On all other hardware it must be zero.
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EINVAL - the selected SPT view is invalid
+* -KVM_EINVAL - a SPT view was selected but the hardware doesn't support it
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+* -KVM_ENOMEM - not enough memory to allocate the reply
+
+7. KVMI_SET_PAGE_ACCESS
+-----------------------
+
+:Architectures: all
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_page_access_entry {
+		__u64 gpa;
+		__u8 access;
+		__u8 padding[7];
+	};
+
+	struct kvmi_set_page_access {
+		__u16 vcpu;
+		__u16 count;
+		__u16 view;
+		__u16 padding;
+		struct kvmi_page_access_entry entries[0];
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code
+
+Sets the spte access bits (rwx) for an array of ``count`` guest physical
+addresses.
+
+The command will fail with -KVM_EINVAL if any of the specified combination
+of access bits is not supported.
+
+The command will make the changes in order and it will not stop on errors. The
+introspector tool should handle the rollback.
+
+In order to 'forget' an address, all the access bits ('rwx') must be set.
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EINVAL - the specified access bits combination is invalid
+* -KVM_EINVAL - the selected SPT view is invalid
+* -KVM_EINVAL - a SPT view was selected but the hardware doesn't support it
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+* -KVM_ENOMEM - not enough memory to add the page tracking structures
+
+8. KVMI_INJECT_EXCEPTION
+------------------------
+
+:Architectures: x86
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_inject_exception {
+		__u16 vcpu;
+		__u8 nr;
+		__u8 has_error;
+		__u16 error_code;
+		__u16 padding;
+		__u64 address;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code
+
+Injects a vCPU exception with or without an error code. In case of page fault
+exception, the guest virtual address has to be specified.
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EINVAL - the specified exception number is invalid
+* -KVM_EINVAL - the specified address is invalid
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+
+9. KVMI_READ_PHYSICAL
+---------------------
+
+:Architectures: all
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_read_physical {
+		__u64 gpa;
+		__u64 size;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code;
+	__u8 data[0];
+
+Reads from the guest memory.
+
+Currently, the size must be non-zero and the read must be restricted to
+one page (offset + size <= PAGE_SIZE).
+
+:Errors:
+
+* -KVM_EINVAL - the specified gpa is invalid
+
+10. KVMI_WRITE_PHYSICAL
+-----------------------
+
+:Architectures: all
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_write_physical {
+		__u64 gpa;
+		__u64 size;
+		__u8  data[0];
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code
+
+Writes into the guest memory.
+
+Currently, the size must be non-zero and the write must be restricted to
+one page (offset + size <= PAGE_SIZE).
+
+:Errors:
+
+* -KVM_EINVAL - the specified gpa is invalid
+
+11. KVMI_CONTROL_EVENTS
+-----------------------
+
+:Architectures: all
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_control_events {
+		__u16 vcpu;
+		__u16 padding;
+		__u32 events;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code
+
+Enables/disables vCPU introspection events, by setting or clearing one or
+more of the following bits::
+
+	KVMI_EVENT_CR_FLAG
+	KVMI_EVENT_MSR_FLAG
+	KVMI_EVENT_XSETBV_FLAG
+	KVMI_EVENT_BREAKPOINT_FLAG
+	KVMI_EVENT_HYPERCALL_FLAG
+	KVMI_EVENT_PF_FLAG
+	KVMI_EVENT_TRAP_FLAG
+	KVMI_EVENT_DESCRIPTOR_FLAG
+
+For example:
+
+	``events = KVMI_EVENT_BREAKPOINT_FLAG | KVMI_EVENT_PF``
+
+it will disable all events but breakpoints and page faults.
+
+When an event is enabled, the introspection tool is notified and it
+must return a reply: allow, skip, etc. (see 'Events' below).
+
+The *KVMI_EVENT_PAUSE_VCPU* event is always allowed because
+it is triggered by the *KVMI_PAUSE_ALL_VCPUS* command. The
+*KVMI_EVENT_CREATE_VCPU* and *KVMI_UNHOOK_EVENT* events are controlled
+by the *KVMI_CONTROL_VM_EVENTS* command.
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EINVAL - the specified mask of events is invalid
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+* -KVM_EPERM - access to one or more events specified in the events mask is
+  restricted by the host
+
+12. KVMI_CONTROL_CR
+-------------------
+
+:Architectures: x86
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_control_cr {
+		__u16 vcpu;
+		__u8 enable;
+		__u8 padding;
+		__u32 cr;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code
+
+Enables/disables introspection for a specific control register and must
+be used in addition to *KVMI_CONTROL_EVENTS* with the *KVMI_EVENT_CR_FLAG*
+bit set.
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EINVAL - the specified control register is not part of the CR0, CR3
+   or CR4 set
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+
+13. KVMI_CONTROL_MSR
+--------------------
+
+:Architectures: x86
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_control_msr {
+		__u16 vcpu;
+		__u8 enable;
+		__u8 padding;
+		__u32 msr;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code
+
+Enables/disables introspection for a specific MSR and must be used
+in addition to *KVMI_CONTROL_EVENTS* with the *KVMI_EVENT_MSR_FLAG* bit set.
+
+Currently, only MSRs within the following two ranges are supported. Trying
+to control events for any other register will fail with -KVM_EINVAL::
+
+	0          ... 0x00001fff
+	0xc0000000 ... 0xc0001fff
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EINVAL - the specified MSR is invalid
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+
+14. KVMI_CONTROL_VE
+-------------------
+
+:Architecture: x86
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_control_ve {
+		__u16 vcpu;
+		__u16 count;
+		__u8 enable;
+		__u8 padding[3];
+		__u64 gpa[0]
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code
+
+On hardware supporting virtualized exceptions, this command can control
+the #VE bit for the listed guest physical addresses.
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EINVAL - one of the specified gpa-s is invalid
+* -KVM_EINVAL - the hardware does not support #VE
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+
+.. note::
+
+  Virtualized exceptions are designed such that they can be controlled by
+  the guest itself and used for (among others) accelerate network
+  operations. Since this will obviously interfere with VMI, the guest
+  is denied access to VE while the introspection channel is active.
+
+15. KVMI_CONTROL_VM_EVENTS
+--------------------------
+
+:Architectures: all
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_control_vm_events {
+		__u32 events;
+		__u32 padding;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code
+
+Enables/disables VM introspection events, by setting or clearing one or
+more of the following bits::
+
+	KVMI_EVENT_CREATE_VCPU_FLAG
+	KVMI_EVENT_UNHOOK_FLAG
+
+For example:
+
+	``events = KVMI_EVENT_UNHOOK_FLAG``
+
+it will enable *KVMI_EVENT_UNHOOK_FLAG* event only.
+
+When an event is enabled, the introspection tool is notified and it
+must return a reply: allow, skip, etc. (see 'Events' below).
+
+:Errors:
+
+* -KVM_EINVAL - the specified mask of events is invalid
+* -KVM_EPERM - access to one or more events specified in the events mask is
+  restricted by the host
+
+
+16. KVMI_GET_MAP_TOKEN
+----------------------
+
+:Architecture: all
+:Versions: >= 1
+:Parameters: none
+:Returns:
+
+::
+
+	struct kvmi_error_code;
+	struct kvmi_get_map_token_reply {
+		struct kvmi_map_mem_token token;
+	};
+
+Where::
+
+	struct kvmi_map_mem_token {
+		__u64 token[4];
+	};
+
+Requests a token for a memory map operation.
+
+On this command, the host generates a random token to be used (once)
+to map a physical page from the introspected guest. The introspector
+could use the token with the KVM_INTRO_MEM_MAP ioctl (on /dev/kvmmem)
+to map a guest physical page to one of its memory pages. The ioctl,
+in turn, will use the KVM_HC_MEM_MAP hypercall (see hypercalls.txt).
+
+The guest kernel exposing /dev/kvmmem keeps a list with all the mappings
+(to all the guests introspected by the tool) in order to unmap them
+(using the KVM_HC_MEM_UNMAP hypercall) when /dev/kvmmem is closed or on
+demand (using the KVM_INTRO_MEM_UNMAP ioctl).
+
+:Errors:
+
+* -KVM_EAGAIN - too many tokens have accumulated
+* -KVM_ENOMEM - not enough memory to allocate a new token
+
+17. KVMI_GET_XSAVE
+------------------
+
+:Architecture: x86
+:Versions: >= 1
+:Parameters:
+
+::
+
+	struct kvmi_get_xsave {
+		__u16 vcpu;
+		__u16 padding[3];
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_error_code;
+	struct kvmi_get_xsave_reply {
+		__u32 region[0];
+	};
+
+Returns a buffer containing the XSAVE area. Currently, the size of
+``kvm_xsave`` is used, but it could change. The userspace should get
+the buffer size from the message size.
+
+:Errors:
+
+* -KVM_EINVAL - the selected vCPU is invalid
+* -KVM_EAGAIN - the selected vCPU can't be introspected yet
+* -KVM_ENOMEM - not enough memory to allocate the reply
+
+Events
+======
+
+All vCPU events are sent using the *KVMI_EVENT* message id. No event will
+be sent unless it is explicitly enabled with a *KVMI_CONTROL_EVENTS*
+or a *KVMI_CONTROL_VM_EVENTS* command or requested, as it is the case
+with the *KVMI_EVENT_PAUSE_VCPU* event (see **KVMI_PAUSE_ALL_VCPUS**).
+
+The message data begins with a common structure, having the vCPU id,
+its mode (in bytes: 2, 4 and 8) and the event::
+
+	struct kvmi_event {
+		__u32 event;
+		__u16 vcpu;
+		__u8 mode;
+		__u8 padding;
+		/* arch/event specific data */
+	}
+
+On x86 the structure looks like this::
+
+	struct kvmi_event {
+		__u32 event;
+		__u16 vcpu;
+		__u8 mode;
+		__u8 padding;
+		struct kvm_regs regs;
+		struct kvm_sregs sregs;
+		struct {
+			__u64 sysenter_cs;
+			__u64 sysenter_esp;
+			__u64 sysenter_eip;
+			__u64 efer;
+			__u64 star;
+			__u64 lstar;
+			__u64 cstar;
+			__u64 pat;
+			__u64 shadow_gs;
+		} msrs;
+	};
+
+It contains information about the vCPU state at the time of the event.
+
+The replies to events have the *KVMI_EVENT_REPLY* message id and begin
+with a common structure::
+
+	struct kvmi_event_reply {
+		__u32 action;
+		__u32 event;
+	};
+
+All events accept the KVMI_EVENT_ACTION_CRASH action, which stops the
+guest ungracefully but as soon as possible.
+
+Most of the events accept the KVMI_EVENT_ACTION_CONTINUE action, which
+lets the instruction that caused the event to continue (unless specified
+otherwise).
+
+Some of the events accept the KVMI_EVENT_ACTION_RETRY action, to continue
+by re-entering the guest.
+
+Specific data can follow these common structures.
+
+0. KVMI_EVENT_PAUSE_VCPU
+------------------------
+
+:Architectures: all
+:Versions: >= 1
+:Actions: CONTINUE, CRASH
+:Parameters:
+
+::
+
+	struct kvmi_event
+
+:Returns:
+
+::
+
+	struct kvmi_event_reply
+
+This event is sent in response to a *KVMI_PAUSE_ALL_VCPUS* command and
+cannot be disabled via *KVMI_CONTROL_EVENTS*.
+
+One event is sent for every *KVMI_PAUSE_ALL_VCPUS* command.
+
+This event has a low priority. It will be sent after any other vCPU
+introspection event and when no vCPU introspection command is queued.
+
+1. KVMI_EVENT_CR
+----------------
+
+:Architectures: x86
+:Versions: >= 1
+:Actions: CONTINUE, CRASH
+:Parameters:
+
+::
+
+	struct kvmi_event;
+	struct kvmi_event_cr {
+		__u16 cr;
+		__u16 padding[3];
+		__u64 old_value;
+		__u64 new_value;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_event_reply;
+	struct kvmi_event_cr_reply {
+		__u64 new_val;
+	};
+
+This event is sent when a control register is going to be changed and the
+introspection has been enabled for this event and for this specific
+register (see *KVMI_CONTROL_EVENTS* and *KVMI_CONTROL_CR_FLAG*).
+
+``kvmi_event``, the control register number, the old value and the new value
+are sent to the introspector. The *CONTINUE* action will set the ``new_val``.
+
+2. KVMI_EVENT_MSR
+-----------------
+
+:Architectures: x86
+:Versions: >= 1
+:Actions: CONTINUE, CRASH
+:Parameters:
+
+::
+
+	struct kvmi_event;
+	struct kvmi_event_msr {
+		__u32 msr;
+		__u32 padding;
+		__u64 old_value;
+		__u64 new_value;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_event_reply;
+	struct kvmi_event_msr_reply {
+		__u64 new_val;
+	};
+
+This event is sent when a model specific register is going to be changed
+and the introspection has been enabled for this event and for this specific
+register (see *KVMI_CONTROL_EVENTS* and *KVMI_CONTROL_MSR_FLAG*).
+
+``kvmi_event``, the MSR number, the old value and the new value are
+sent to the introspector. The *CONTINUE* action will set the ``new_val``.
+
+3. KVMI_EVENT_XSETBV
+--------------------
+
+:Architectures: x86
+:Versions: >= 1
+:Actions: CONTINUE, CRASH
+:Parameters:
+
+::
+
+	struct kvmi_event;
+
+:Returns:
+
+::
+
+	struct kvmi_event_reply;
+
+This event is sent when the extended control register XCR0 is going
+to be changed and the introspection has been enabled for this event
+(see *KVMI_CONTROL_EVENTS*).
+
+``kvmi_event`` is sent to the introspector.
+
+4. KVMI_EVENT_BREAKPOINT
+------------------------
+
+:Architectures: x86
+:Versions: >= 1
+:Actions: CONTINUE, CRASH, RETRY
+:Parameters:
+
+::
+
+	struct kvmi_event;
+	struct kvmi_event_breakpoint {
+		__u64 gpa;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_event_reply;
+
+This event is sent when a breakpoint was reached and the introspection has
+been enabled for this event (see *KVMI_CONTROL_EVENTS*).
+
+Some of these breakpoints could have been injected by the introspector,
+placed in the slack space of various functions and used as notification
+for when the OS or an application has reached a certain state or is
+trying to perform a certain operation (like creating a process).
+
+``kvmi_event`` and the guest physical address are sent to the introspector.
+
+The *RETRY* action is used by the introspector for its own breakpoints.
+
+5. KVMI_EVENT_HYPERCALL
+-----------------------
+
+:Architectures: x86
+:Versions: >= 1
+:Actions: CONTINUE, CRASH
+:Parameters:
+
+::
+
+	struct kvmi_event
+
+:Returns:
+
+::
+
+	struct kvmi_event_reply
+
+This event is sent on a specific user hypercall when the introspection has
+been enabled for this event (see *KVMI_CONTROL_EVENTS*).
+
+The hypercall number must be ``KVM_HC_XEN_HVM_OP`` with the
+``KVM_HC_XEN_HVM_OP_GUEST_REQUEST_VM_EVENT`` sub-function
+(see hypercalls.txt).
+
+It is used by the code residing inside the introspected guest to call the
+introspection tool and to report certain details about its operation. For
+example, a classic antimalware remediation tool can report what it has
+found during a scan.
+
+6. KVMI_EVENT_PF
+----------------
+
+:Architectures: x86
+:Versions: >= 1
+:Actions: CONTINUE, CRASH, RETRY
+:Parameters:
+
+::
+
+	struct kvmi_event;
+	struct kvmi_event_pf {
+		__u64 gva;
+		__u64 gpa;
+		__u32 mode;
+		__u32 padding;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_event_reply;
+	struct kvmi_event_pf_reply {
+		__u8 singlestep;
+		__u8 rep_complete;
+		__u16 padding;
+		__u32 ctx_size;
+		__u8 ctx_data[256];
+	};
+
+This event is sent when a hypervisor page fault occurs due to a failed
+permission check in the shadow page tables, the introspection has
+been enabled for this event (see *KVMI_CONTROL_EVENTS*) and the event was
+generated for a page in which the introspector has shown interest
+(ie. has previously touched it by adjusting the spte permissions).
+
+The shadow page tables can be used by the introspection tool to guarantee
+the purpose of code areas inside the guest (code, rodata, stack, heap
+etc.) Each attempt at an operation unfitting for a certain memory
+range (eg. execute code in heap) triggers a page fault and gives the
+introspection tool the chance to audit the code attempting the operation.
+
+``kvmi_event``, guest virtual address, guest physical address and the
+exit qualification (mode) are sent to the introspector.
+
+The *CONTINUE* action will continue the page fault handling via emulation
+(with custom input if ``ctx_size`` > 0). The use of custom input is
+to trick the guest software into believing it has read certain data,
+in order to hide the content of certain memory areas (eg. hide injected
+code from integrity checkers). If ``rep_complete`` is not zero, the REP
+prefixed instruction should be emulated just once (or at least no other
+*KVMI_EVENT_PF* event should be sent for the current instruction).
+
+The *RETRY* action is used by the introspector to retry the execution of
+the current instruction. Either using single-step (if ``singlestep`` is
+not zero) or return to guest (if the introspector changed the instruction
+pointer or the page restrictions).
+
+7. KVMI_EVENT_TRAP
+------------------
+
+:Architectures: x86
+:Versions: >= 1
+:Actions: CONTINUE, CRASH
+:Parameters:
+
+::
+
+	struct kvmi_event;
+	struct kvmi_event_trap {
+		__u32 vector;
+		__u32 type;
+		__u32 error_code;
+		__u32 padding;
+		__u64 cr2;
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_event_reply;
+
+This event is sent if a previous *KVMI_INJECT_EXCEPTION* command has
+been overwritten by an interrupt picked up during guest reentry and the
+introspection has been enabled for this event (see *KVMI_CONTROL_EVENTS*).
+
+``kvmi_event``, exception/interrupt number (vector), exception/interrupt
+type, exception code (``error_code``) and CR2 are sent to the introspector.
+
+8. KVMI_EVENT_CREATE_VCPU
+-------------------------
+
+:Architectures: all
+:Versions: >= 1
+:Actions: CONTINUE, CRASH
+:Parameters:
+
+::
+
+	struct kvmi_event
+
+:Returns:
+
+::
+
+	struct kvmi_event_reply
+
+This event is sent when a new vCPU is created and the introspection has
+been enabled for this event (see *KVMI_CONTROL_VM_EVENTS*).
+
+9. KVMI_EVENT_DESCRIPTOR
+-------------------------
+
+:Architecture: x86
+:Versions: >= 1
+:Actions: CONTINUE, CRASH
+:Parameters:
+
+::
+
+	struct kvmi_event
+	struct kvmi_event_descriptor {
+		union {
+			struct {
+				__u32 instr_info;
+				__u32 padding;
+				__u64 exit_qualification;
+			} vmx;
+			struct {
+				__u64 exit_info;
+				__u64 padding;
+			} svm;
+		} arch;
+		__u8 descriptor;
+		__u8 write;
+		__u8 padding[6];
+	};
+
+:Returns:
+
+::
+
+	struct kvmi_event_reply
+
+This event is sent when a descriptor table register is accessed and the
+introspection has been enabled for this event (see *KVMI_CONTROL_EVENTS*
+and *KVMI_EVENT_DESCRIPTOR_FLAG*).
+
+``kvmi_event`` and ``kvmi_event_descriptor`` are sent to the introspector.
+
+``descriptor`` can be one of::
+
+	KVMI_DESC_IDTR
+	KVMI_DESC_GDTR
+	KVMI_DESC_LDTR
+	KVMI_DESC_TR
+
+``write`` is 1 if the descriptor was written, 0 otherwise.
+
+10. KVMI_EVENT_UNHOOK
+---------------------
+
+:Architecture: all
+:Versions: >= 1
+:Actions: CONTINUE, CRASH
+:Parameters:
+
+::
+
+	struct kvmi_event
+
+:Returns:
+
+::
+
+	struct kvmi_event_reply
+
+This event is sent when the device manager (ie. QEMU) has to
+pause/stop/migrate the guest (see **Unhooking**) and the introspection
+has been enabled for this event (see **KVMI_CONTROL_VM_EVENTS**).
+The introspection tool has a chance to unhook and close the KVMI channel
+(signaling that the operation can proceed).

From patchwork Thu Dec 20 18:28:32 2018
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: =?utf-8?q?Adalbert_Laz=C4=83r?=
 <alazar@bitdefender.com>
X-Patchwork-Id: 10739285
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 16F0717E1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Dec 2018 18:36:06 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 07D0B28E58
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Dec 2018 18:36:06 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id F06E028F39; Thu, 20 Dec 2018 18:36:05 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id AAE7C28E58
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu, 20 Dec 2018 18:36:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389326AbeLTSgE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 20 Dec 2018 13:36:04 -0500
Received: from mx01.bbu.dsd.mx.bitdefender.com ([91.199.104.161]:44332 "EHLO
        mx01.bbu.dsd.mx.bitdefender.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2389303AbeLTSgD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 20 Dec 2018 13:36:03 -0500
Received: from smtp.bitdefender.com (smtp02.buh.bitdefender.net [10.17.80.76])
        by mx01.bbu.dsd.mx.bitdefender.com (Postfix) with ESMTPS id
 697AB305FFAF;
        Thu, 20 Dec 2018 20:29:37 +0200 (EET)
Received: from host.bbu.bitdefender.biz (unknown [10.10.193.111])
        by smtp.bitdefender.com (Postfix) with ESMTPSA id 627DF306E47A;
        Thu, 20 Dec 2018 20:29:37 +0200 (EET)
From: =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>, =?utf-8?q?Mihai_Don?=
	=?utf-8?q?=C8=9Bu?= <mdontu@bitdefender.com>,
 =?utf-8?q?Adalbert_Laz=C4=83r?= <alazar@bitdefender.com>
Subject: [RFC PATCH v5 02/20] kvm: document the VM introspection ioctl-s and
 capability
Date: Thu, 20 Dec 2018 20:28:32 +0200
Message-Id: <20181220182850.4579-3-alazar@bitdefender.com>
In-Reply-To: <20181220182850.4579-1-alazar@bitdefender.com>
References: <20181220182850.4579-1-alazar@bitdefender.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

The uuid member of struct kvm_introspection is used to show
the guest id in the error messages.

Signed-off-by: Adalbert Lazăr <alazar@bitdefender.com>
---
 Documentation/virtual/kvm/api.txt | 59 +++++++++++++++++++++++++++++++
 1 file changed, 59 insertions(+)

```
