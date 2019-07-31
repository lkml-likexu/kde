

#### [PATCH 0/2] KVM: selftests: Enable ucall and dirty_log_test on s390x
##### From: Thomas Huth <thuth@redhat.com>

```c

Implement the ucall() interface on s390x to be able to use the
dirty_log_test KVM selftest on s390x, too.

Thomas Huth (2):
  KVM: selftests: Implement ucall() for s390x
  KVM: selftests: Enable dirty_log_test on s390x

 tools/testing/selftests/kvm/Makefile          |  1 +
 tools/testing/selftests/kvm/dirty_log_test.c  | 70 +++++++++++++++++--
 .../testing/selftests/kvm/include/kvm_util.h  |  2 +-
 tools/testing/selftests/kvm/lib/ucall.c       | 34 +++++++--
 .../selftests/kvm/s390x/sync_regs_test.c      |  6 +-
 5 files changed, 98 insertions(+), 15 deletions(-)
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
```
#### [PATCH net-next v5 0/5] vsock/virtio: optimizations to increase the
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c

This series tries to increase the throughput of virtio-vsock with slight
changes.
While I was testing the v2 of this series I discovered an huge use of memory,
so I added patch 1 to mitigate this issue. I put it in this series in order
to better track the performance trends.

v5:
- rebased all patches on net-next
- added Stefan's R-b and Michael's A-b

v4: https://patchwork.kernel.org/cover/11047717
v3: https://patchwork.kernel.org/cover/10970145
v2: https://patchwork.kernel.org/cover/10938743
v1: https://patchwork.kernel.org/cover/10885431

Below are the benchmarks step by step. I used iperf3 [1] modified with VSOCK
support. As Michael suggested in the v1, I booted host and guest with 'nosmap'.

A brief description of patches:
- Patches 1:   limit the memory usage with an extra copy for small packets
- Patches 2+3: reduce the number of credit update messages sent to the
               transmitter
- Patches 4+5: allow the host to split packets on multiple buffers and use
               VIRTIO_VSOCK_MAX_PKT_BUF_SIZE as the max packet size allowed

                    host -> guest [Gbps]
pkt_size before opt   p 1     p 2+3    p 4+5

32         0.032     0.030    0.048    0.051
64         0.061     0.059    0.108    0.117
128        0.122     0.112    0.227    0.234
256        0.244     0.241    0.418    0.415
512        0.459     0.466    0.847    0.865
1K         0.927     0.919    1.657    1.641
2K         1.884     1.813    3.262    3.269
4K         3.378     3.326    6.044    6.195
8K         5.637     5.676   10.141   11.287
16K        8.250     8.402   15.976   16.736
32K       13.327    13.204   19.013   20.515
64K       21.241    21.341   20.973   21.879
128K      21.851    22.354   21.816   23.203
256K      21.408    21.693   21.846   24.088
512K      21.600    21.899   21.921   24.106

                    guest -> host [Gbps]
pkt_size before opt   p 1     p 2+3    p 4+5

32         0.045     0.046    0.057    0.057
64         0.089     0.091    0.103    0.104
128        0.170     0.179    0.192    0.200
256        0.364     0.351    0.361    0.379
512        0.709     0.699    0.731    0.790
1K         1.399     1.407    1.395    1.427
2K         2.670     2.684    2.745    2.835
4K         5.171     5.199    5.305    5.451
8K         8.442     8.500   10.083    9.941
16K       12.305    12.259   13.519   15.385
32K       11.418    11.150   11.988   24.680
64K       10.778    10.659   11.589   35.273
128K      10.421    10.339   10.939   40.338
256K      10.300     9.719   10.508   36.562
512K       9.833     9.808   10.612   35.979

As Stefan suggested in the v1, I measured also the efficiency in this way:
    efficiency = Mbps / (%CPU_Host + %CPU_Guest)

The '%CPU_Guest' is taken inside the VM. I know that it is not the best way,
but it's provided for free from iperf3 and could be an indication.

        host -> guest efficiency [Mbps / (%CPU_Host + %CPU_Guest)]
pkt_size before opt   p 1     p 2+3    p 4+5

32         0.35      0.45     0.79     1.02
64         0.56      0.80     1.41     1.54
128        1.11      1.52     3.03     3.12
256        2.20      2.16     5.44     5.58
512        4.17      4.18    10.96    11.46
1K         8.30      8.26    20.99    20.89
2K        16.82     16.31    39.76    39.73
4K        30.89     30.79    74.07    75.73
8K        53.74     54.49   124.24   148.91
16K       80.68     83.63   200.21   232.79
32K      132.27    132.52   260.81   357.07
64K      229.82    230.40   300.19   444.18
128K     332.60    329.78   331.51   492.28
256K     331.06    337.22   339.59   511.59
512K     335.58    328.50   331.56   504.56

        guest -> host efficiency [Mbps / (%CPU_Host + %CPU_Guest)]
pkt_size before opt   p 1     p 2+3    p 4+5

32         0.43      0.43     0.53     0.56
64         0.85      0.86     1.04     1.10
128        1.63      1.71     2.07     2.13
256        3.48      3.35     4.02     4.22
512        6.80      6.67     7.97     8.63
1K        13.32     13.31    15.72    15.94
2K        25.79     25.92    30.84    30.98
4K        50.37     50.48    58.79    59.69
8K        95.90     96.15   107.04   110.33
16K      145.80    145.43   143.97   174.70
32K      147.06    144.74   146.02   282.48
64K      145.25    143.99   141.62   406.40
128K     149.34    146.96   147.49   489.34
256K     156.35    149.81   152.21   536.37
512K     151.65    150.74   151.52   519.93

[1] https://github.com/stefano-garzarella/iperf/

Stefano Garzarella (5):
  vsock/virtio: limit the memory used per-socket
  vsock/virtio: reduce credit update messages
  vsock/virtio: fix locking in virtio_transport_inc_tx_pkt()
  vhost/vsock: split packets to send using multiple buffers
  vsock/virtio: change the maximum packet size allowed

 drivers/vhost/vsock.c                   | 68 ++++++++++++-----
 include/linux/virtio_vsock.h            |  4 +-
 net/vmw_vsock/virtio_transport.c        |  1 +
 net/vmw_vsock/virtio_transport_common.c | 99 ++++++++++++++++++++-----
 4 files changed, 134 insertions(+), 38 deletions(-)
Acked-by: Michael S. Tsirkin <mst@redhat.com>
```
#### [PATCH 0/3] Reduce the number of Valgrind reports in unit tests.
##### From: Andrey Shinkevich <andrey.shinkevich@virtuozzo.com>

```c

Running unit tests under the Valgrind may help to detect QEMU memory issues
(suggested by Denis V. Lunev). Some of the Valgrind reports relate to the
unit test code itself. Let's eliminate the detected memory issues to ease
locating critical ones.

Andrey Shinkevich (3):
  test-throttle: Fix uninitialized use of burst_length
  tests: Fix uninitialized byte in test_visitor_in_fuzz
  i386/kvm: initialize struct at full before ioctl call

 target/i386/kvm.c                 | 3 +++
 tests/test-string-input-visitor.c | 8 +++-----
 tests/test-throttle.c             | 2 ++
 3 files changed, 8 insertions(+), 5 deletions(-)
```
#### [PATCH 0/2] kvm-unit-test: x86: Implement a generic wrapper for
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c

This patch-set implements a generic wrapper for the cpuid/cpuid_index calls in
the kvm-unit-test source code. This is similar to what we have in the kernel
source code except that here we retrieve the data on the fly.
This implementation makes it convenient to define various CPUID feature bits
in one place and re-use them in places which need to check if a given CPUID
feature bit is supported by the current CPU.


[PATCH 1/2] kvm-unit-test: x86: Implement a generic wrapper for cpuid/cpuid_indexed
[PATCH 2/2] kvm-unit-test: x86: Replace cpuid/cpuid_indexed calls with

 lib/x86/processor.h       | 147 +++++++++++++++++++++++++++++++++++-----------
 x86/access.c              |  13 ++--
 x86/apic.c                |   8 +--
 x86/emulator.c            |   4 +-
 x86/memory.c              |  16 ++---
 x86/pcid.c                |  10 +---
 x86/pku.c                 |   3 +-
 x86/smap.c                |   4 +-
 x86/svm.c                 |   6 +-
 x86/tsc.c                 |  16 +----
 x86/tsc_adjust.c          |   2 +-
 x86/tscdeadline_latency.c |   2 +-
 x86/umip.c                |   6 +-
 x86/vmexit.c              |   6 +-
 x86/vmx.c                 |   2 +-
 x86/vmx_tests.c           |  11 ++--
 x86/xsave.c               |  15 ++---
 17 files changed, 153 insertions(+), 118 deletions(-)

Krish Sadhukhan (2):
      x86: Implement a generic wrapper for cpuid/cpuid_indexed functions
      x86: Replace cpuid/cpuid_indexed calls with this_cpu_has()
```
