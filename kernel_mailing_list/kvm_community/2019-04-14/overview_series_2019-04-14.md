#### [PATCH 1/2] include: linux: Regularise the use of FIELD_SIZEOF macro
##### From: Shyam Saini <shyam.saini@amarulasolutions.com>

```c
Currently, there are 3 different macros, namely sizeof_field, SIZEOF_FIELD
and FIELD_SIZEOF which are used to calculate the size of a member of
structure, so to bring uniformity in entire kernel source tree lets use
FIELD_SIZEOF and replace all occurrences of other two macros with this.

For this purpose, redefine FIELD_SIZEOF in include/linux/stddef.h and
tools/testing/selftests/bpf/bpf_util.h and remove its defination from
include/linux/kernel.h

Signed-off-by: Shyam Saini <shyam.saini@amarulasolutions.com>
---
 arch/arm64/include/asm/processor.h                 | 10 +++++-----
 arch/mips/cavium-octeon/executive/cvmx-bootmem.c   |  2 +-
 drivers/gpu/drm/i915/gvt/scheduler.c               |  2 +-
 drivers/net/ethernet/mellanox/mlxsw/spectrum_fid.c |  4 ++--
 fs/befs/linuxvfs.c                                 |  2 +-
 fs/ext2/super.c                                    |  2 +-
 fs/ext4/super.c                                    |  2 +-
 fs/freevxfs/vxfs_super.c                           |  2 +-
 fs/orangefs/super.c                                |  2 +-
 fs/ufs/super.c                                     |  2 +-
 include/linux/kernel.h                             |  9 ---------
 include/linux/slab.h                               |  2 +-
 include/linux/stddef.h                             | 11 ++++++++++-
 kernel/fork.c                                      |  2 +-
 kernel/utsname.c                                   |  2 +-
 net/caif/caif_socket.c                             |  2 +-
 net/core/skbuff.c                                  |  2 +-
 net/ipv4/raw.c                                     |  2 +-
 net/ipv6/raw.c                                     |  2 +-
 net/sctp/socket.c                                  |  4 ++--
 tools/testing/selftests/bpf/bpf_util.h             | 11 ++++++++++-
 virt/kvm/kvm_main.c                                |  2 +-
 22 files changed, 45 insertions(+), 36 deletions(-)

```
