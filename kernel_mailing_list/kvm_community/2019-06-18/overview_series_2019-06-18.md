#### [PATCH v1 12/22] docs: driver-api: add .rst files from the main dir
##### From: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>

```c
Those files belong to the driver-api guide. Add them to the
driver-api book.

Signed-off-by: Mauro Carvalho Chehab <mchehab+samsung@kernel.org>
---

I had to remove the long list of maintainers got by
getpatch.pl, as it was too long. I opted to keep only the
mailing lists.

 Documentation/ABI/removed/sysfs-class-rfkill  |  2 +-
 Documentation/ABI/stable/sysfs-class-rfkill   |  2 +-
 .../ABI/testing/sysfs-class-switchtec         |  2 +-
 Documentation/PCI/pci.rst                     |  2 +-
 Documentation/admin-guide/hw-vuln/l1tf.rst    |  2 +-
 .../admin-guide/kernel-parameters.txt         |  4 +-
 .../admin-guide/kernel-per-cpu-kthreads.rst   |  2 +-
 .../{ => driver-api}/atomic_bitops.rst        |  2 -
 Documentation/{ => driver-api}/bt8xxgpio.rst  |  2 -
 .../bus-virt-phys-mapping.rst                 |  2 -
 .../{connector => driver-api}/connector.rst   |  2 -
 .../{console => driver-api}/console.rst       |  2 -
 Documentation/{ => driver-api}/crc32.rst      |  2 -
 Documentation/{ => driver-api}/dcdbas.rst     |  2 -
 .../{ => driver-api}/debugging-modules.rst    |  2 -
 .../debugging-via-ohci1394.rst                |  2 -
 Documentation/{ => driver-api}/dell_rbu.rst   |  2 -
 Documentation/{ => driver-api}/digsig.rst     |  2 -
 .../{EDID/howto.rst => driver-api/edid.rst}   |  2 -
 Documentation/{ => driver-api}/eisa.rst       |  2 -
 .../{ => driver-api}/futex-requeue-pi.rst     |  2 -
 .../{ => driver-api}/gcc-plugins.rst          |  2 -
 Documentation/{ => driver-api}/hwspinlock.rst |  2 -
 Documentation/driver-api/index.rst            | 66 +++++++++++++++++++
 Documentation/{ => driver-api}/io-mapping.rst |  2 -
 .../{ => driver-api}/io_ordering.rst          |  2 -
 .../{IPMI.rst => driver-api/ipmi.rst}         |  2 -
 .../irq-affinity.rst}                         |  2 -
 .../irq-domain.rst}                           |  2 -
 Documentation/{IRQ.rst => driver-api/irq.rst} |  2 -
 .../{ => driver-api}/irqflags-tracing.rst     |  2 -
 Documentation/{ => driver-api}/isa.rst        |  2 -
 Documentation/{ => driver-api}/isapnp.rst     |  2 -
 Documentation/{ => driver-api}/kobject.rst    |  4 +-
 Documentation/{ => driver-api}/kprobes.rst    |  2 -
 Documentation/{ => driver-api}/kref.rst       |  2 -
 .../pblk.txt => driver-api/lightnvm-pblk.rst} |  0
 Documentation/{ => driver-api}/lzo.rst        |  2 -
 Documentation/{ => driver-api}/mailbox.rst    |  2 -
 .../{ => driver-api}/men-chameleon-bus.rst    |  2 -
 Documentation/{ => driver-api}/nommu-mmap.rst |  2 -
 Documentation/{ => driver-api}/ntb.rst        |  2 -
 Documentation/{nvmem => driver-api}/nvmem.rst |  2 -
 Documentation/{ => driver-api}/padata.rst     |  2 -
 .../{ => driver-api}/parport-lowlevel.rst     |  2 -
 .../{ => driver-api}/percpu-rw-semaphore.rst  |  2 -
 Documentation/{ => driver-api}/pi-futex.rst   |  2 -
 Documentation/driver-api/pps.rst              |  2 -
 .../{ => driver-api}/preempt-locking.rst      |  2 -
 .../{pti => driver-api}/pti_intel_mid.rst     |  2 -
 Documentation/driver-api/ptp.rst              |  2 -
 Documentation/{ => driver-api}/pwm.rst        |  2 -
 Documentation/{ => driver-api}/rbtree.rst     |  2 -
 Documentation/{ => driver-api}/remoteproc.rst |  4 +-
 Documentation/{ => driver-api}/rfkill.rst     |  2 -
 .../{ => driver-api}/robust-futex-ABI.rst     |  2 -
 .../{ => driver-api}/robust-futexes.rst       |  2 -
 Documentation/{ => driver-api}/rpmsg.rst      |  2 -
 Documentation/{ => driver-api}/sgi-ioc4.rst   |  2 -
 .../{SM501.rst => driver-api/sm501.rst}       |  2 -
 .../{ => driver-api}/smsc_ece1099.rst         |  2 -
 .../{ => driver-api}/speculation.rst          |  8 +--
 .../{ => driver-api}/static-keys.rst          |  2 -
 Documentation/{ => driver-api}/switchtec.rst  |  4 +-
 Documentation/{ => driver-api}/sync_file.rst  |  2 -
 Documentation/{ => driver-api}/tee.rst        |  2 -
 .../{ => driver-api}/this_cpu_ops.rst         |  2 -
 .../unaligned-memory-access.rst               |  2 -
 .../{ => driver-api}/vfio-mediated-device.rst |  4 +-
 Documentation/{ => driver-api}/vfio.rst       |  2 -
 Documentation/{ => driver-api}/xillybus.rst   |  2 -
 Documentation/{ => driver-api}/xz.rst         |  2 -
 Documentation/{ => driver-api}/zorro.rst      |  2 -
 Documentation/driver-model/device.rst         |  2 +-
 Documentation/fb/fbcon.rst                    |  4 +-
 Documentation/filesystems/sysfs.txt           |  2 +-
 Documentation/gpu/drm-mm.rst                  |  2 +-
 Documentation/ia64/irq-redir.rst              |  2 +-
 Documentation/laptops/thinkpad-acpi.rst       |  6 +-
 Documentation/locking/rt-mutex.rst            |  2 +-
 Documentation/networking/scaling.rst          |  4 +-
 Documentation/s390/vfio-ccw.rst               |  6 +-
 Documentation/sysctl/kernel.rst               |  2 +-
 Documentation/sysctl/vm.rst                   |  2 +-
 Documentation/trace/kprobetrace.rst           |  2 +-
 Documentation/translations/zh_CN/IRQ.txt      |  4 +-
 .../translations/zh_CN/filesystems/sysfs.txt  |  2 +-
 .../translations/zh_CN/io_ordering.txt        |  4 +-
 Documentation/w1/w1.netlink                   |  2 +-
 Documentation/watchdog/hpwdt.rst              |  2 +-
 MAINTAINERS                                   | 46 ++++++-------
 arch/Kconfig                                  |  4 +-
 arch/unicore32/include/asm/io.h               |  2 +-
 drivers/base/core.c                           |  2 +-
 drivers/char/ipmi/Kconfig                     |  2 +-
 drivers/char/ipmi/ipmi_si_hotmod.c            |  2 +-
 drivers/char/ipmi/ipmi_si_intf.c              |  2 +-
 drivers/dma-buf/Kconfig                       |  2 +-
 drivers/gpio/Kconfig                          |  2 +-
 drivers/gpu/drm/Kconfig                       |  2 +-
 drivers/pci/switch/Kconfig                    |  2 +-
 drivers/platform/x86/Kconfig                  |  4 +-
 drivers/platform/x86/dcdbas.c                 |  2 +-
 drivers/platform/x86/dell_rbu.c               |  2 +-
 drivers/pnp/isapnp/Kconfig                    |  2 +-
 drivers/tty/Kconfig                           |  2 +-
 drivers/vfio/Kconfig                          |  2 +-
 drivers/vfio/mdev/Kconfig                     |  2 +-
 drivers/w1/Kconfig                            |  2 +-
 include/asm-generic/bitops/atomic.h           |  2 +-
 include/linux/io-mapping.h                    |  2 +-
 include/linux/jump_label.h                    |  2 +-
 include/linux/kobject.h                       |  2 +-
 include/linux/kobject_ns.h                    |  2 +-
 include/linux/rbtree.h                        |  2 +-
 include/linux/rbtree_augmented.h              |  2 +-
 init/Kconfig                                  |  2 +-
 kernel/padata.c                               |  2 +-
 lib/Kconfig                                   |  2 +-
 lib/Kconfig.debug                             |  2 +-
 lib/crc32.c                                   |  2 +-
 lib/kobject.c                                 |  4 +-
 lib/lzo/lzo1x_decompress_safe.c               |  2 +-
 lib/xz/Kconfig                                |  2 +-
 mm/Kconfig                                    |  2 +-
 mm/nommu.c                                    |  2 +-
 samples/Kconfig                               |  2 +-
 samples/kprobes/kprobe_example.c              |  2 +-
 samples/kprobes/kretprobe_example.c           |  2 +-
 scripts/gcc-plugins/Kconfig                   |  2 +-
 tools/include/linux/rbtree.h                  |  2 +-
 tools/include/linux/rbtree_augmented.h        |  2 +-
 132 files changed, 173 insertions(+), 235 deletions(-)
 rename Documentation/{ => driver-api}/atomic_bitops.rst (99%)
 rename Documentation/{ => driver-api}/bt8xxgpio.rst (99%)
 rename Documentation/{ => driver-api}/bus-virt-phys-mapping.rst (99%)
 rename Documentation/{connector => driver-api}/connector.rst (99%)
 rename Documentation/{console => driver-api}/console.rst (99%)
 rename Documentation/{ => driver-api}/crc32.rst (99%)
 rename Documentation/{ => driver-api}/dcdbas.rst (99%)
 rename Documentation/{ => driver-api}/debugging-modules.rst (98%)
 rename Documentation/{ => driver-api}/debugging-via-ohci1394.rst (99%)
 rename Documentation/{ => driver-api}/dell_rbu.rst (99%)
 rename Documentation/{ => driver-api}/digsig.rst (99%)
 rename Documentation/{EDID/howto.rst => driver-api/edid.rst} (99%)
 rename Documentation/{ => driver-api}/eisa.rst (99%)
 rename Documentation/{ => driver-api}/futex-requeue-pi.rst (99%)
 rename Documentation/{ => driver-api}/gcc-plugins.rst (99%)
 rename Documentation/{ => driver-api}/hwspinlock.rst (99%)
 rename Documentation/{ => driver-api}/io-mapping.rst (99%)
 rename Documentation/{ => driver-api}/io_ordering.rst (99%)
 rename Documentation/{IPMI.rst => driver-api/ipmi.rst} (99%)
 rename Documentation/{IRQ-affinity.rst => driver-api/irq-affinity.rst} (99%)
 rename Documentation/{IRQ-domain.rst => driver-api/irq-domain.rst} (99%)
 rename Documentation/{IRQ.rst => driver-api/irq.rst} (99%)
 rename Documentation/{ => driver-api}/irqflags-tracing.rst (99%)
 rename Documentation/{ => driver-api}/isa.rst (99%)
 rename Documentation/{ => driver-api}/isapnp.rst (98%)
 rename Documentation/{ => driver-api}/kobject.rst (99%)
 rename Documentation/{ => driver-api}/kprobes.rst (99%)
 rename Documentation/{ => driver-api}/kref.rst (99%)
 rename Documentation/{lightnvm/pblk.txt => driver-api/lightnvm-pblk.rst} (100%)
 rename Documentation/{ => driver-api}/lzo.rst (99%)
 rename Documentation/{ => driver-api}/mailbox.rst (99%)
 rename Documentation/{ => driver-api}/men-chameleon-bus.rst (99%)
 rename Documentation/{ => driver-api}/nommu-mmap.rst (99%)
 rename Documentation/{ => driver-api}/ntb.rst (99%)
 rename Documentation/{nvmem => driver-api}/nvmem.rst (99%)
 rename Documentation/{ => driver-api}/padata.rst (99%)
 rename Documentation/{ => driver-api}/parport-lowlevel.rst (99%)
 rename Documentation/{ => driver-api}/percpu-rw-semaphore.rst (99%)
 rename Documentation/{ => driver-api}/pi-futex.rst (99%)
 rename Documentation/{ => driver-api}/preempt-locking.rst (99%)
 rename Documentation/{pti => driver-api}/pti_intel_mid.rst (99%)
 rename Documentation/{ => driver-api}/pwm.rst (99%)
 rename Documentation/{ => driver-api}/rbtree.rst (99%)
 rename Documentation/{ => driver-api}/remoteproc.rst (99%)
 rename Documentation/{ => driver-api}/rfkill.rst (99%)
 rename Documentation/{ => driver-api}/robust-futex-ABI.rst (99%)
 rename Documentation/{ => driver-api}/robust-futexes.rst (99%)
 rename Documentation/{ => driver-api}/rpmsg.rst (99%)
 rename Documentation/{ => driver-api}/sgi-ioc4.rst (99%)
 rename Documentation/{SM501.rst => driver-api/sm501.rst} (99%)
 rename Documentation/{ => driver-api}/smsc_ece1099.rst (99%)
 rename Documentation/{ => driver-api}/speculation.rst (99%)
 rename Documentation/{ => driver-api}/static-keys.rst (99%)
 rename Documentation/{ => driver-api}/switchtec.rst (97%)
 rename Documentation/{ => driver-api}/sync_file.rst (99%)
 rename Documentation/{ => driver-api}/tee.rst (99%)
 rename Documentation/{ => driver-api}/this_cpu_ops.rst (99%)
 rename Documentation/{ => driver-api}/unaligned-memory-access.rst (99%)
 rename Documentation/{ => driver-api}/vfio-mediated-device.rst (99%)
 rename Documentation/{ => driver-api}/vfio.rst (99%)
 rename Documentation/{ => driver-api}/xillybus.rst (99%)
 rename Documentation/{ => driver-api}/xz.rst (99%)
 rename Documentation/{ => driver-api}/zorro.rst (99%)

```
#### [RFC PATCH v1 1/5] vfio-ccw: Move guest_cp storage into common struct
##### From: Eric Farman <farman@linux.ibm.com>

```c
Rather than allocating/freeing a piece of memory every time
we try to figure out how long a CCW chain is, let's use a piece
of memory allocated for each device.

The io_mutex added with commit 4f76617378ee9 ("vfio-ccw: protect
the I/O region") is held for the duration of the VFIO_CCW_EVENT_IO_REQ
event that accesses/uses this space, so there should be no race
concerns with another CPU attempting an (unexpected) SSCH for the
same device.

Suggested-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Eric Farman <farman@linux.ibm.com>
---
Conny, your suggestion [1] did not go unnoticed.  :)

[1] https://patchwork.kernel.org/comment/22312659/
---
 drivers/s390/cio/vfio_ccw_cp.c  | 23 ++++-------------------
 drivers/s390/cio/vfio_ccw_cp.h  |  7 +++++++
 drivers/s390/cio/vfio_ccw_drv.c |  7 +++++++
 3 files changed, 18 insertions(+), 19 deletions(-)

```
#### [PATCH v2] KVM: x86: Modify struct kvm_nested_state to have explicit fields for data
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
From: Liran Alon <liran.alon@oracle.com>

Improve the KVM_{GET,SET}_NESTED_STATE structs by detailing the format
of VMX nested state data in a struct.

In order to avoid changing the ioctl values of
KVM_{GET,SET}_NESTED_STATE, there is a need to preserve
sizeof(struct kvm_nested_state). This is done by defining the data
struct as "data.vmx[0]". It was the most elegant way I found to
preserve struct size while still keeping struct readable and easy to
maintain. It does have a misfortunate side-effect that now it has to be
accessed as "data.vmx[0]" rather than just "data.vmx".

Because we are already modifying these structs, I also modified the
following:
* Define the "format" field values as macros.
* Rename vmcs_pa to vmcs12_pa for better readability.

Signed-off-by: Liran Alon <liran.alon@oracle.com>
[Remove SVM stubs, add KVM_STATE_NESTED_VMX_VMCS12_SIZE. - Paolo]
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virtual/kvm/api.txt     | 46 +++++++++++++-------
 arch/x86/include/uapi/asm/kvm.h       | 33 ++++++++++-----
 arch/x86/kvm/vmx/nested.c             | 79 +++++++++++++++++++----------------
 arch/x86/kvm/vmx/vmcs12.h             |  5 ++-
 tools/arch/x86/include/uapi/asm/kvm.h |  2 +-
 5 files changed, 101 insertions(+), 64 deletions(-)

```
#### [PATCH v9 01/17] x86/common: Align cpu_caps_cleared and cpu_caps_set to unsigned long
##### From: Fenghua Yu <fenghua.yu@intel.com>

```c
cpu_caps_cleared[] and cpu_caps_set[] may not be aligned to unsigned long.
Atomic operations (i.e. set_bit() and clear_bit()) on the bitmaps may
access two cache lines (a.k.a. split lock) and cause the CPU to do a bus
lock to block all memory accesses from other processors to ensure
atomicity.

To avoid the overall performance degradation from the bus locking, align
the two variables to unsigned long.

Defining the variables as unsigned long may also fix the issue because
they will be naturally aligned to unsigned long. But that needs additional
code changes. Adding __aligned(unsigned long) is a simpler fix.

Signed-off-by: Fenghua Yu <fenghua.yu@intel.com>
Reviewed-by: Borislav Petkov <bp@suse.de>
---
 arch/x86/kernel/cpu/common.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
