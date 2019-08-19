

#### [PATCH v4 00/15] hw/i386/pc: Do not restrict the fw_cfg functions to
##### From: =?utf-8?q?Philippe_Mathieu-Daud=C3=A9?= <philmd@redhat.com>

```c

Hi,

This is my take at salvaging some NEMU good work.
Samuel worked in adding the fw_cfg device to the x86-virt NEMU machine.
This series is inspired by NEMU's commit 3cb92d080835 [0] and adapted
to upstream style. The result makes the upstream codebase more
modularizable.
There are very little logical changes, this is mostly a cleanup
refactor.

Since v3 [3]:
- Addressed Christophe suggestion (patch #8)
- Rebased patch #15 since Eduardo merged Like Xu's work between.

Since v2 [2]:
- Addressed MST comments from v2 (only patch #2 modified)
  - do not use unsigned for enum
  - do not add unuseful documentation

Since v1 [1]:
- Addressed Li and MST comments

$ git backport-diff -u v3
Key:
[----] : patches are identical
[####] : number of functional differences between upstream/downstream patch
[down] : patch is downstream-only
The flags [FC] indicate (F)unctional and (C)ontextual differences, respectively

001/15:[----] [--] 'hw/i386/pc: Use e820_get_num_entries() to access e820_entries'
002/15:[----] [-C] 'hw/i386/pc: Extract e820 memory layout code'
003/15:[----] [--] 'hw/i386/pc: Use address_space_memory in place'
004/15:[----] [-C] 'hw/i386/pc: Rename bochs_bios_init as more generic fw_cfg_arch_create'
005/15:[----] [--] 'hw/i386/pc: Pass the boot_cpus value by argument'
006/15:[----] [--] 'hw/i386/pc: Pass the apic_id_limit value by argument'
007/15:[0002] [FC] 'hw/i386/pc: Pass the CPUArchIdList array by argument'
008/15:[down] 'hw/i386/pc: Remove unused PCMachineState argument in fw_cfg_arch_create'
009/15:[----] [-C] 'hw/i386/pc: Let pc_build_smbios() take a FWCfgState argument'
010/15:[----] [-C] 'hw/i386/pc: Let pc_build_smbios() take a generic MachineState argument'
011/15:[----] [-C] 'hw/i386/pc: Rename pc_build_smbios() as generic fw_cfg_build_smbios()'
012/15:[----] [--] 'hw/i386/pc: Let pc_build_feature_control() take a FWCfgState argument'
013/15:[----] [--] 'hw/i386/pc: Let pc_build_feature_control() take a MachineState argument'
014/15:[----] [--] 'hw/i386/pc: Rename pc_build_feature_control() as generic fw_cfg_build_*'
015/15:[0017] [FC] 'hw/i386/pc: Extract the x86 generic fw_cfg code'

Regards,

Phil.

[0] https://github.com/intel/nemu/commit/3cb92d080835ac8d47c8b713156338afa33cff5c
[1] https://lists.gnu.org/archive/html/qemu-devel/2019-05/msg05759.html
[2] https://lists.gnu.org/archive/html/qemu-devel/2019-06/msg02786.html
[3] https://lists.gnu.org/archive/html/qemu-devel/2019-07/msg00193.html

Philippe Mathieu-Daudé (15):
  hw/i386/pc: Use e820_get_num_entries() to access e820_entries
  hw/i386/pc: Extract e820 memory layout code
  hw/i386/pc: Use address_space_memory in place
  hw/i386/pc: Rename bochs_bios_init as more generic fw_cfg_arch_create
  hw/i386/pc: Pass the boot_cpus value by argument
  hw/i386/pc: Pass the apic_id_limit value by argument
  hw/i386/pc: Pass the CPUArchIdList array by argument
  hw/i386/pc: Remove unused PCMachineState argument in
    fw_cfg_arch_create
  hw/i386/pc: Let pc_build_smbios() take a FWCfgState argument
  hw/i386/pc: Let pc_build_smbios() take a generic MachineState argument
  hw/i386/pc: Rename pc_build_smbios() as generic fw_cfg_build_smbios()
  hw/i386/pc: Let pc_build_feature_control() take a FWCfgState argument
  hw/i386/pc: Let pc_build_feature_control() take a MachineState
    argument
  hw/i386/pc: Rename pc_build_feature_control() as generic
    fw_cfg_build_*
  hw/i386/pc: Extract the x86 generic fw_cfg code

 hw/i386/Makefile.objs        |   2 +-
 hw/i386/e820_memory_layout.c |  59 ++++++++++
 hw/i386/e820_memory_layout.h |  42 ++++++++
 hw/i386/fw_cfg.c             | 136 +++++++++++++++++++++++
 hw/i386/fw_cfg.h             |   7 ++
 hw/i386/pc.c                 | 202 ++---------------------------------
 include/hw/i386/pc.h         |  11 --
 target/i386/kvm.c            |   1 +
 8 files changed, 254 insertions(+), 206 deletions(-)
 create mode 100644 hw/i386/e820_memory_layout.c
 create mode 100644 hw/i386/e820_memory_layout.h
```
