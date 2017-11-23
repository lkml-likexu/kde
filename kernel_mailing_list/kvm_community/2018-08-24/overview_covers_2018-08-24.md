

#### [PATCH V3 0/2] introduce coalesced pio support
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c

Coalesced pio is base on coalesced mmio and can be used for some port
like rtc port, pci-host config port, virtio-pci config port and so on.

Specially in case of rtc as coalesced pio, some versions of windows guest
access rtc frequently because of rtc as system tick. guest access rtc like
this: write register index to 0x70, then write or read data from 0x71.
writing 0x70 port is just as index and do nothing else. So we can use
coalesced pio to handle this scene to reduce VM-EXIT time.

When it starts and closes the virtual machine, it will access pci-host config 
port or virtio-pci config port frequently. So setting these port as 
coalesced pio can reduce startup and shutdown time. In qemu I just realize
piixfx's pci-host, it is convenient for other pci-host type implementations.

without my patch, get the vm-exit time of accessing rtc 0x70 and piix 0xcf8
using perf tools: (guest OS : windows 7 64bit)
IO Port Access  Samples Samples%  Time%  Min Time  Max Time  Avg time
0x70:POUT        86     30.99%    74.59%   9us      29us    10.75us (+- 3.41%)
0xcf8:POUT     1119     2.60%     2.12%   2.79us    56.83us 3.41us (+- 2.23%)

with my patch
IO Port Access  Samples Samples%  Time%   Min Time  Max Time   Avg time
0x70:POUT       106    32.02%    29.47%    0us      10us     1.57us (+- 7.38%)
0xcf8:POUT      1065    1.67%     0.28%   0.41us    65.44us   0.66us (+- 10.55%)

I think there is a need for further consideration in changing coalesecd_mmio's
naming in kernel and qemu together.So maybe another patch does it.


Peng Hao (2):
  kvm/x86 : add coalesced pio support
  kvm/x86 : add document for coalesced pio

 Documentation/virtual/kvm/00-INDEX          |  4 ++++
 Documentation/virtual/kvm/coalesced-pio.txt | 14 ++++++++++++++
 include/uapi/linux/kvm.h                    |  5 +++--
 virt/kvm/coalesced_mmio.c                   |  8 +++++---
 virt/kvm/kvm_main.c                         |  2 ++
 5 files changed, 28 insertions(+), 5 deletions(-)
 create mode 100644 Documentation/virtual/kvm/coalesced-pio.txt
```
#### [PATCH kvm-unit-tests v1 0/4] s390x: simple DXC test
##### From: David Hildenbrand <david@redhat.com>

```c

The DXC was not handled by TCG correctly (and I have a patch series on
the QEMU list, which fixes that).

Add a simple test case that forces a DATA exception and verifies that
the DXC (0xff) is written to the right locations. One time with and
one time without AFP.

While at it, I found one bug related to storing/saving floating point
registers during interrupts and added one cleanup.

Tested under KVM and under TCG.

David Hildenbrand (4):
  s390x: user ctl_set/clear_bit for low address protection
  s390x: fix storing/loading fregs to right address
  s390x: save/restore cr0 in IRQ handlers
  s390x: test if the DXC is correctly stored

 lib/s390x/asm-offsets.c   |  1 +
 lib/s390x/asm/arch_def.h  |  4 ++-
 lib/s390x/asm/float.h     | 51 +++++++++++++++++++++++++++++++++++++++
 lib/s390x/asm/interrupt.h | 12 ++-------
 s390x/cstart64.S          | 11 +++++++--
 s390x/emulator.c          | 35 +++++++++++++++++++++++++++
 6 files changed, 101 insertions(+), 13 deletions(-)
 create mode 100644 lib/s390x/asm/float.h
```
#### [PATCH v1 0/7] tools/kvm_stat: misc patches
##### From: Stefan Raspl <raspl@linux.ibm.com>

```c

A couple of patches, mostly dealing with handling of guests that are
shut down while kvm_stat is running.
However, was sadly pulled into the tedious Python3 area, so had to
pick up some flotsam on the way :/   

Stefan Raspl (7):
  tools/kvm_stat: fix python3 issues
  tools/kvm_stat: fix handling of invalid paths in debugfs provider
  tools/kvm_stat: fix updates for dead guests
  tools/kvm_stat: don't reset stats when setting PID filter for debugfs
  tools/kvm_stat: handle guest removals more gracefully
  tools/kvm_stat: indicate dead guests as such
  tools/kvm_stat: re-animate display of dead guests

 tools/kvm/kvm_stat/kvm_stat | 59 +++++++++++++++++++++++++++++++++++++--------
 1 file changed, 49 insertions(+), 10 deletions(-)
Signed-off-by: Stefan Raspl <raspl@linux.ibm.com>
```
