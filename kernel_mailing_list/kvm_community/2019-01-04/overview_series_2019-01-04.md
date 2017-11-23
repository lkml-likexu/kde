#### [PATCH] kvm: Use struct_size() in kmalloc()
##### From: "Gustavo A. R. Silva" <gustavo@embeddedor.com>

```c
One of the more common cases of allocation size calculations is finding
the size of a structure that has a zero-sized array at the end, along
with memory for some number of elements for that array. For example:

struct foo {
    int stuff;
    void *entry[];
};

instance = kmalloc(sizeof(struct foo) + sizeof(void *) * count, GFP_KERNEL);

Instead of leaving these open-coded and prone to type mistakes, we can
now use the new struct_size() helper:

instance = kmalloc(struct_size(instance, entry, count), GFP_KERNEL);

This code was detected with the help of Coccinelle.

Signed-off-by: Gustavo A. R. Silva <gustavo@embeddedor.com>
---
 virt/kvm/kvm_main.c | 8 ++++----
 1 file changed, 4 insertions(+), 4 deletions(-)

```
#### [PATCH] KVM/VMX: Avoid return error when flush tlb successfully in the hv_remote_flush_tlb_with_range()
##### From: lantianyu1986@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

The "ret" is initialized to be ENOTSUPP. The return value of
__hv_remote_flush_tlb_with_range() will be Or with "ret" when ept
table potiners are mismatched. This will cause return ENOTSUPP even if
flush tlb successfully. This patch is to fix the issue and set
"ret" to 0.

Fix: a5c214da("KVM/VMX: Change hv flush logic when ept tables are mismatched.")
Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
 arch/x86/kvm/vmx/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2] x86: kvmguest: use TSC clocksource if invariant TSC is exposed
##### From: Marcelo Tosatti <mtosatti@redhat.com>

```c
The invariant TSC bit has the following meaning:

"The time stamp counter in newer processors may support an enhancement,
referred to as invariant TSC. Processor's support for invariant TSC
is indicated by CPUID.80000007H:EDX[8]. The invariant TSC will run
at a constant rate in all ACPI P-, C-. and T-states. This is the
architectural behavior moving forward. On processors with invariant TSC
support, the OS may use the TSC for wall clock timer services (instead
of ACPI or HPET timers). TSC reads are much more efficient and do not
incur the overhead associated with a ring transition or access to a
platform resource."

IOW, TSC does not change frequency. In such case, and with
TSC scaling hardware available to handle migration, it is possible
to use the TSC clocksource directly, whose system calls are
faster.

Reduce the rating of kvmclock clocksource to allow TSC clocksource
to be the default if invariant TSC is exposed.

Signed-off-by: Marcelo Tosatti <mtosatti@redhat.com>

v2: Use feature bits and tsc_unstable() check (Sean Christopherson)

```
#### [PATCH] vfio_pci: Add local source directory as include
##### From: Laura Abbott <labbott@redhat.com>

```c
Commit 7f92891778df ("vfio_pci: Add NVIDIA GV100GL [Tesla V100 SXM2]
subdriver") introduced a trace.h file in the local directory but
missed adding the local include path, resulting in compilation
failures with tracepoints:

In file included from drivers/vfio/pci/trace.h:102,
                 from drivers/vfio/pci/vfio_pci_nvlink2.c:29:
./include/trace/define_trace.h:89:42: fatal error: ./trace.h: No such file or directory
 #include TRACE_INCLUDE(TRACE_INCLUDE_FILE)

Fix this by adjusting the include path.

Fixes: 7f92891778df ("vfio_pci: Add NVIDIA GV100GL [Tesla V100 SXM2] subdriver")
Signed-off-by: Laura Abbott <labbott@redhat.com>
Reviewed-by: Alexey Kardashevskiy <aik@ozlabs.ru>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
I'd still like to echo my sentiment that this should not be a def_bool.
We hit this error on our internal testing and we couldn't even turn
off the driver until we fixed this.
---
 drivers/vfio/pci/Makefile | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v2 1/2] virtio-balloon: tweak config_changed implementation
##### From: Wei Wang <wei.w.wang@intel.com>

```c
virtio-ccw has deadlock issues with reading the config space inside the
interrupt context, so we tweak the virtballoon_changed implementation
by moving the config read operations into the related workqueue contexts.
The config_read_bitmap is used as a flag to the workqueue callbacks
about the related config fields that need to be read.

Reported-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Wei Wang <wei.w.wang@intel.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/virtio/virtio_balloon.c | 81 +++++++++++++++++++++++++++--------------
 1 file changed, 53 insertions(+), 28 deletions(-)

```
#### [PATCH 1/11] X86/Hyper-V: Add parameter offset for hyperv_fill_flush_guest_mapping_list()
##### From: lantianyu1986@gmail.com

```c
From: Lan Tianyu <Tianyu.Lan@microsoft.com>

Add parameter offset to specify start position to add flush ranges in
guest address list of struct hv_guest_mapping_flush_list.

Signed-off-by: Lan Tianyu <Tianyu.Lan@microsoft.com>
---
 arch/x86/hyperv/nested.c        | 4 ++--
 arch/x86/include/asm/mshyperv.h | 2 +-
 arch/x86/kvm/vmx/vmx.c          | 2 +-
 3 files changed, 4 insertions(+), 4 deletions(-)

```
