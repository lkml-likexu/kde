#### [PATCH 01/12] Documentation: move architectures together
##### From: Alex Shi <alex.shi@linux.alibaba.com>

```c
There are many different archs in Documentation/ dir, it's better to
move them together in 'Documentation/arch' which follows from kernel source.

Signed-off-by: Alex Shi <alex.shi@linux.alibaba.com>
Cc: Jonathan Corbet <corbet@lwn.net>
Cc: linux-doc@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: linux-stm32@st-md-mailman.stormreply.com
Cc: linux-arm-kernel@lists.infradead.org
Cc: linuxppc-dev@lists.ozlabs.org
Cc: linux-riscv@lists.infradead.org
Cc: linux-omap@vger.kernel.org
Cc: linux-fbdev@vger.kernel.org
Cc: linux-samsung-soc@vger.kernel.org
Cc: linux-ia64@vger.kernel.org
Cc: linux-mips@vger.kernel.org
Cc: linux-parisc@vger.kernel.org
Cc: linux-scsi@vger.kernel.org
Cc: linux-s390@vger.kernel.org
Cc: kvm@vger.kernel.org
Cc: linux-sh@vger.kernel.org
---
 Documentation/{ => arch}/arm/Booting                             | 0
 Documentation/{ => arch}/arm/IXP4xx                              | 0
 Documentation/{ => arch}/arm/Interrupts                          | 0
 Documentation/{ => arch}/arm/Marvell/README                      | 0
 Documentation/{ => arch}/arm/Microchip/README                    | 0
 Documentation/{ => arch}/arm/Netwinder                           | 0
 Documentation/{ => arch}/arm/OMAP/DSS                            | 0
 Documentation/{ => arch}/arm/OMAP/README                         | 0
 Documentation/{ => arch}/arm/OMAP/omap_pm                        | 0
 Documentation/{ => arch}/arm/Porting                             | 0
 Documentation/{ => arch}/arm/README                              | 0
 Documentation/{ => arch}/arm/SA1100/ADSBitsy                     | 0
 Documentation/{ => arch}/arm/SA1100/Assabet                      | 0
 Documentation/{ => arch}/arm/SA1100/Brutus                       | 0
 Documentation/{ => arch}/arm/SA1100/CERF                         | 0
 Documentation/{ => arch}/arm/SA1100/FreeBird                     | 0
 Documentation/{ => arch}/arm/SA1100/GraphicsClient               | 0
 Documentation/{ => arch}/arm/SA1100/GraphicsMaster               | 0
 Documentation/{ => arch}/arm/SA1100/HUW_WEBPANEL                 | 0
 Documentation/{ => arch}/arm/SA1100/Itsy                         | 0
 Documentation/{ => arch}/arm/SA1100/LART                         | 0
 Documentation/{ => arch}/arm/SA1100/PLEB                         | 0
 Documentation/{ => arch}/arm/SA1100/Pangolin                     | 0
 Documentation/{ => arch}/arm/SA1100/Tifon                        | 0
 Documentation/{ => arch}/arm/SA1100/Yopy                         | 0
 Documentation/{ => arch}/arm/SA1100/empeg                        | 0
 Documentation/{ => arch}/arm/SA1100/nanoEngine                   | 0
 Documentation/{ => arch}/arm/SA1100/serial_UART                  | 0
 Documentation/{ => arch}/arm/SH-Mobile/.gitignore                | 0
 Documentation/{ => arch}/arm/SPEAr/overview.txt                  | 0
 Documentation/{ => arch}/arm/Samsung-S3C24XX/CPUfreq.txt         | 0
 Documentation/{ => arch}/arm/Samsung-S3C24XX/EB2410ITX.txt       | 0
 Documentation/{ => arch}/arm/Samsung-S3C24XX/GPIO.txt            | 0
 Documentation/{ => arch}/arm/Samsung-S3C24XX/H1940.txt           | 0
 Documentation/{ => arch}/arm/Samsung-S3C24XX/NAND.txt            | 0
 Documentation/{ => arch}/arm/Samsung-S3C24XX/Overview.txt        | 0
 Documentation/{ => arch}/arm/Samsung-S3C24XX/S3C2412.txt         | 0
 Documentation/{ => arch}/arm/Samsung-S3C24XX/S3C2413.txt         | 0
 Documentation/{ => arch}/arm/Samsung-S3C24XX/SMDK2440.txt        | 0
 Documentation/{ => arch}/arm/Samsung-S3C24XX/Suspend.txt         | 0
 Documentation/{ => arch}/arm/Samsung-S3C24XX/USB-Host.txt        | 0
 Documentation/{ => arch}/arm/Samsung/Bootloader-interface.txt    | 0
 Documentation/{ => arch}/arm/Samsung/GPIO.txt                    | 0
 Documentation/{ => arch}/arm/Samsung/Overview.txt                | 0
 Documentation/{ => arch}/arm/Samsung/clksrc-change-registers.awk | 0
 Documentation/{ => arch}/arm/Setup                               | 0
 Documentation/{ => arch}/arm/VFP/release-notes.txt               | 0
 Documentation/{ => arch}/arm/cluster-pm-race-avoidance.txt       | 0
 Documentation/{ => arch}/arm/firmware.txt                        | 0
 Documentation/{ => arch}/arm/kernel_mode_neon.txt                | 0
 Documentation/{ => arch}/arm/kernel_user_helpers.txt             | 0
 Documentation/{ => arch}/arm/keystone/Overview.txt               | 0
 Documentation/{ => arch}/arm/keystone/knav-qmss.txt              | 0
 Documentation/{ => arch}/arm/mem_alignment                       | 0
 Documentation/{ => arch}/arm/memory.txt                          | 0
 Documentation/{ => arch}/arm/nwfpe/NOTES                         | 0
 Documentation/{ => arch}/arm/nwfpe/README                        | 0
 Documentation/{ => arch}/arm/nwfpe/README.FPE                    | 0
 Documentation/{ => arch}/arm/nwfpe/TODO                          | 0
 Documentation/{ => arch}/arm/pxa/mfp.txt                         | 0
 Documentation/{ => arch}/arm/sti/overview.txt                    | 0
 Documentation/{ => arch}/arm/sti/stih407-overview.txt            | 0
 Documentation/{ => arch}/arm/sti/stih415-overview.txt            | 0
 Documentation/{ => arch}/arm/sti/stih416-overview.txt            | 0
 Documentation/{ => arch}/arm/sti/stih418-overview.txt            | 0
 Documentation/{ => arch}/arm/stm32/overview.rst                  | 0
 Documentation/{ => arch}/arm/stm32/stm32f429-overview.rst        | 0
 Documentation/{ => arch}/arm/stm32/stm32f746-overview.rst        | 0
 Documentation/{ => arch}/arm/stm32/stm32f769-overview.rst        | 0
 Documentation/{ => arch}/arm/stm32/stm32h743-overview.rst        | 0
 Documentation/{ => arch}/arm/stm32/stm32mp157-overview.rst       | 0
 Documentation/{ => arch}/arm/sunxi/README                        | 0
 Documentation/{ => arch}/arm/sunxi/clocks.txt                    | 0
 Documentation/{ => arch}/arm/swp_emulation                       | 0
 Documentation/{ => arch}/arm/tcm.txt                             | 0
 Documentation/{ => arch}/arm/uefi.txt                            | 0
 Documentation/{ => arch}/arm/vlocks.txt                          | 0
 Documentation/{ => arch}/arm64/acpi_object_usage.rst             | 0
 Documentation/{ => arch}/arm64/arm-acpi.rst                      | 0
 Documentation/{ => arch}/arm64/booting.rst                       | 0
 Documentation/{ => arch}/arm64/cpu-feature-registers.rst         | 0
 Documentation/{ => arch}/arm64/elf_hwcaps.rst                    | 0
 Documentation/{ => arch}/arm64/hugetlbpage.rst                   | 0
 Documentation/{ => arch}/arm64/index.rst                         | 0
 Documentation/{ => arch}/arm64/legacy_instructions.rst           | 0
 Documentation/{ => arch}/arm64/memory.rst                        | 0
 Documentation/{ => arch}/arm64/perf.txt                          | 0
 Documentation/{ => arch}/arm64/pointer-authentication.rst        | 0
 Documentation/{ => arch}/arm64/silicon-errata.rst                | 0
 Documentation/{ => arch}/arm64/sve.rst                           | 0
 Documentation/{ => arch}/arm64/tagged-pointers.rst               | 0
 Documentation/{ => arch}/ia64/IRQ-redir.txt                      | 0
 Documentation/{ => arch}/ia64/README                             | 0
 Documentation/{ => arch}/ia64/aliasing.txt                       | 0
 Documentation/{ => arch}/ia64/efirtc.txt                         | 0
 Documentation/{ => arch}/ia64/err_inject.txt                     | 0
 Documentation/{ => arch}/ia64/fsys.txt                           | 0
 Documentation/{ => arch}/ia64/mca.txt                            | 0
 Documentation/{ => arch}/ia64/serial.txt                         | 0
 Documentation/{ => arch}/ia64/xen.txt                            | 0
 Documentation/{ => arch}/m68k/README.buddha                      | 0
 Documentation/{ => arch}/m68k/kernel-options.txt                 | 0
 Documentation/{ => arch}/mips/AU1xxx_IDE.README                  | 0
 Documentation/{ => arch}/nios2/README                            | 0
 Documentation/{ => arch}/parisc/debugging                        | 0
 Documentation/{ => arch}/parisc/registers                        | 0
 Documentation/{ => arch}/powerpc/DAWR-POWER9.txt                 | 0
 Documentation/{ => arch}/powerpc/bootwrapper.txt                 | 0
 Documentation/{ => arch}/powerpc/cpu_families.txt                | 0
 Documentation/{ => arch}/powerpc/cpu_features.txt                | 0
 Documentation/{ => arch}/powerpc/cxl.txt                         | 0
 Documentation/{ => arch}/powerpc/cxlflash.txt                    | 0
 Documentation/{ => arch}/powerpc/dscr.txt                        | 0
 Documentation/{ => arch}/powerpc/eeh-pci-error-recovery.txt      | 0
 Documentation/{ => arch}/powerpc/firmware-assisted-dump.txt      | 0
 Documentation/{ => arch}/powerpc/hvcs.txt                        | 0
 Documentation/{ => arch}/powerpc/isa-versions.rst                | 0
 Documentation/{ => arch}/powerpc/mpc52xx.txt                     | 0
 Documentation/{ => arch}/powerpc/pci_iov_resource_on_powernv.txt | 0
 Documentation/{ => arch}/powerpc/pmu-ebb.txt                     | 0
 Documentation/{ => arch}/powerpc/ptrace.txt                      | 0
 Documentation/{ => arch}/powerpc/qe_firmware.txt                 | 0
 Documentation/{ => arch}/powerpc/syscall64-abi.txt               | 0
 Documentation/{ => arch}/powerpc/transactional_memory.txt        | 0
 Documentation/{ => arch}/riscv/index.rst                         | 0
 Documentation/{ => arch}/riscv/pmu.rst                           | 0
 Documentation/{ => arch}/s390/3270.ChangeLog                     | 0
 Documentation/{ => arch}/s390/3270.rst                           | 0
 Documentation/{ => arch}/s390/cds.rst                            | 0
 Documentation/{ => arch}/s390/common_io.rst                      | 0
 Documentation/{ => arch}/s390/config3270.sh                      | 0
 Documentation/{ => arch}/s390/dasd.rst                           | 0
 Documentation/{ => arch}/s390/debugging390.rst                   | 0
 Documentation/{ => arch}/s390/driver-model.rst                   | 0
 Documentation/{ => arch}/s390/index.rst                          | 0
 Documentation/{ => arch}/s390/monreader.rst                      | 0
 Documentation/{ => arch}/s390/qeth.rst                           | 0
 Documentation/{ => arch}/s390/s390dbf.rst                        | 0
 Documentation/{ => arch}/s390/text_files.rst                     | 0
 Documentation/{ => arch}/s390/vfio-ap.rst                        | 0
 Documentation/{ => arch}/s390/vfio-ccw.rst                       | 0
 Documentation/{ => arch}/s390/zfcpdump.rst                       | 0
 Documentation/{ => arch}/sh/conf.py                              | 0
 Documentation/{ => arch}/sh/index.rst                            | 0
 Documentation/{ => arch}/sh/new-machine.txt                      | 0
 Documentation/{ => arch}/sh/register-banks.txt                   | 0
 Documentation/{ => arch}/sparc/adi.rst                           | 0
 Documentation/{ => arch}/sparc/console.rst                       | 0
 Documentation/{ => arch}/sparc/index.rst                         | 0
 Documentation/{ => arch}/sparc/oradax/dax-hv-api.txt             | 0
 Documentation/{ => arch}/sparc/oradax/oracle-dax.rst             | 0
 Documentation/{ => arch}/x86/amd-memory-encryption.rst           | 0
 Documentation/{ => arch}/x86/boot.rst                            | 0
 Documentation/{ => arch}/x86/conf.py                             | 0
 Documentation/{ => arch}/x86/earlyprintk.rst                     | 0
 Documentation/{ => arch}/x86/entry_64.rst                        | 0
 Documentation/{ => arch}/x86/exception-tables.rst                | 0
 Documentation/{ => arch}/x86/i386/IO-APIC.rst                    | 0
 Documentation/{ => arch}/x86/i386/index.rst                      | 0
 Documentation/{ => arch}/x86/index.rst                           | 0
 Documentation/{ => arch}/x86/intel_mpx.rst                       | 0
 Documentation/{ => arch}/x86/kernel-stacks.rst                   | 0
 Documentation/{ => arch}/x86/mds.rst                             | 0
 Documentation/{ => arch}/x86/microcode.rst                       | 0
 Documentation/{ => arch}/x86/mtrr.rst                            | 0
 Documentation/{ => arch}/x86/orc-unwinder.rst                    | 0
 Documentation/{ => arch}/x86/pat.rst                             | 0
 Documentation/{ => arch}/x86/pti.rst                             | 0
 Documentation/{ => arch}/x86/resctrl_ui.rst                      | 0
 Documentation/{ => arch}/x86/tlb.rst                             | 0
 Documentation/{ => arch}/x86/topology.rst                        | 0
 Documentation/{ => arch}/x86/usb-legacy-support.rst              | 0
 Documentation/{ => arch}/x86/x86_64/5level-paging.rst            | 0
 Documentation/{ => arch}/x86/x86_64/boot-options.rst             | 0
 Documentation/{ => arch}/x86/x86_64/cpu-hotplug-spec.rst         | 0
 Documentation/{ => arch}/x86/x86_64/fake-numa-for-cpusets.rst    | 0
 Documentation/{ => arch}/x86/x86_64/index.rst                    | 0
 Documentation/{ => arch}/x86/x86_64/machinecheck.rst             | 0
 Documentation/{ => arch}/x86/x86_64/mm.rst                       | 0
 Documentation/{ => arch}/x86/x86_64/uefi.rst                     | 0
 Documentation/{ => arch}/x86/zero-page.rst                       | 0
 Documentation/{ => arch}/xtensa/atomctl.txt                      | 0
 Documentation/{ => arch}/xtensa/booting.txt                      | 0
 Documentation/{ => arch}/xtensa/mmu.txt                          | 0
 184 files changed, 0 insertions(+), 0 deletions(-)
 rename Documentation/{ => arch}/arm/Booting (100%)
 rename Documentation/{ => arch}/arm/IXP4xx (100%)
 rename Documentation/{ => arch}/arm/Interrupts (100%)
 rename Documentation/{ => arch}/arm/Marvell/README (100%)
 rename Documentation/{ => arch}/arm/Microchip/README (100%)
 rename Documentation/{ => arch}/arm/Netwinder (100%)
 rename Documentation/{ => arch}/arm/OMAP/DSS (100%)
 rename Documentation/{ => arch}/arm/OMAP/README (100%)
 rename Documentation/{ => arch}/arm/OMAP/omap_pm (100%)
 rename Documentation/{ => arch}/arm/Porting (100%)
 rename Documentation/{ => arch}/arm/README (100%)
 rename Documentation/{ => arch}/arm/SA1100/ADSBitsy (100%)
 rename Documentation/{ => arch}/arm/SA1100/Assabet (100%)
 rename Documentation/{ => arch}/arm/SA1100/Brutus (100%)
 rename Documentation/{ => arch}/arm/SA1100/CERF (100%)
 rename Documentation/{ => arch}/arm/SA1100/FreeBird (100%)
 rename Documentation/{ => arch}/arm/SA1100/GraphicsClient (100%)
 rename Documentation/{ => arch}/arm/SA1100/GraphicsMaster (100%)
 rename Documentation/{ => arch}/arm/SA1100/HUW_WEBPANEL (100%)
 rename Documentation/{ => arch}/arm/SA1100/Itsy (100%)
 rename Documentation/{ => arch}/arm/SA1100/LART (100%)
 rename Documentation/{ => arch}/arm/SA1100/PLEB (100%)
 rename Documentation/{ => arch}/arm/SA1100/Pangolin (100%)
 rename Documentation/{ => arch}/arm/SA1100/Tifon (100%)
 rename Documentation/{ => arch}/arm/SA1100/Yopy (100%)
 rename Documentation/{ => arch}/arm/SA1100/empeg (100%)
 rename Documentation/{ => arch}/arm/SA1100/nanoEngine (100%)
 rename Documentation/{ => arch}/arm/SA1100/serial_UART (100%)
 rename Documentation/{ => arch}/arm/SH-Mobile/.gitignore (100%)
 rename Documentation/{ => arch}/arm/SPEAr/overview.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung-S3C24XX/CPUfreq.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung-S3C24XX/EB2410ITX.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung-S3C24XX/GPIO.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung-S3C24XX/H1940.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung-S3C24XX/NAND.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung-S3C24XX/Overview.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung-S3C24XX/S3C2412.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung-S3C24XX/S3C2413.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung-S3C24XX/SMDK2440.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung-S3C24XX/Suspend.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung-S3C24XX/USB-Host.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung/Bootloader-interface.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung/GPIO.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung/Overview.txt (100%)
 rename Documentation/{ => arch}/arm/Samsung/clksrc-change-registers.awk (100%)
 rename Documentation/{ => arch}/arm/Setup (100%)
 rename Documentation/{ => arch}/arm/VFP/release-notes.txt (100%)
 rename Documentation/{ => arch}/arm/cluster-pm-race-avoidance.txt (100%)
 rename Documentation/{ => arch}/arm/firmware.txt (100%)
 rename Documentation/{ => arch}/arm/kernel_mode_neon.txt (100%)
 rename Documentation/{ => arch}/arm/kernel_user_helpers.txt (100%)
 rename Documentation/{ => arch}/arm/keystone/Overview.txt (100%)
 rename Documentation/{ => arch}/arm/keystone/knav-qmss.txt (100%)
 rename Documentation/{ => arch}/arm/mem_alignment (100%)
 rename Documentation/{ => arch}/arm/memory.txt (100%)
 rename Documentation/{ => arch}/arm/nwfpe/NOTES (100%)
 rename Documentation/{ => arch}/arm/nwfpe/README (100%)
 rename Documentation/{ => arch}/arm/nwfpe/README.FPE (100%)
 rename Documentation/{ => arch}/arm/nwfpe/TODO (100%)
 rename Documentation/{ => arch}/arm/pxa/mfp.txt (100%)
 rename Documentation/{ => arch}/arm/sti/overview.txt (100%)
 rename Documentation/{ => arch}/arm/sti/stih407-overview.txt (100%)
 rename Documentation/{ => arch}/arm/sti/stih415-overview.txt (100%)
 rename Documentation/{ => arch}/arm/sti/stih416-overview.txt (100%)
 rename Documentation/{ => arch}/arm/sti/stih418-overview.txt (100%)
 rename Documentation/{ => arch}/arm/stm32/overview.rst (100%)
 rename Documentation/{ => arch}/arm/stm32/stm32f429-overview.rst (100%)
 rename Documentation/{ => arch}/arm/stm32/stm32f746-overview.rst (100%)
 rename Documentation/{ => arch}/arm/stm32/stm32f769-overview.rst (100%)
 rename Documentation/{ => arch}/arm/stm32/stm32h743-overview.rst (100%)
 rename Documentation/{ => arch}/arm/stm32/stm32mp157-overview.rst (100%)
 rename Documentation/{ => arch}/arm/sunxi/README (100%)
 rename Documentation/{ => arch}/arm/sunxi/clocks.txt (100%)
 rename Documentation/{ => arch}/arm/swp_emulation (100%)
 rename Documentation/{ => arch}/arm/tcm.txt (100%)
 rename Documentation/{ => arch}/arm/uefi.txt (100%)
 rename Documentation/{ => arch}/arm/vlocks.txt (100%)
 rename Documentation/{ => arch}/arm64/acpi_object_usage.rst (100%)
 rename Documentation/{ => arch}/arm64/arm-acpi.rst (100%)
 rename Documentation/{ => arch}/arm64/booting.rst (100%)
 rename Documentation/{ => arch}/arm64/cpu-feature-registers.rst (100%)
 rename Documentation/{ => arch}/arm64/elf_hwcaps.rst (100%)
 rename Documentation/{ => arch}/arm64/hugetlbpage.rst (100%)
 rename Documentation/{ => arch}/arm64/index.rst (100%)
 rename Documentation/{ => arch}/arm64/legacy_instructions.rst (100%)
 rename Documentation/{ => arch}/arm64/memory.rst (100%)
 rename Documentation/{ => arch}/arm64/perf.txt (100%)
 rename Documentation/{ => arch}/arm64/pointer-authentication.rst (100%)
 rename Documentation/{ => arch}/arm64/silicon-errata.rst (100%)
 rename Documentation/{ => arch}/arm64/sve.rst (100%)
 rename Documentation/{ => arch}/arm64/tagged-pointers.rst (100%)
 rename Documentation/{ => arch}/ia64/IRQ-redir.txt (100%)
 rename Documentation/{ => arch}/ia64/README (100%)
 rename Documentation/{ => arch}/ia64/aliasing.txt (100%)
 rename Documentation/{ => arch}/ia64/efirtc.txt (100%)
 rename Documentation/{ => arch}/ia64/err_inject.txt (100%)
 rename Documentation/{ => arch}/ia64/fsys.txt (100%)
 rename Documentation/{ => arch}/ia64/mca.txt (100%)
 rename Documentation/{ => arch}/ia64/serial.txt (100%)
 rename Documentation/{ => arch}/ia64/xen.txt (100%)
 rename Documentation/{ => arch}/m68k/README.buddha (100%)
 rename Documentation/{ => arch}/m68k/kernel-options.txt (100%)
 rename Documentation/{ => arch}/mips/AU1xxx_IDE.README (100%)
 rename Documentation/{ => arch}/nios2/README (100%)
 rename Documentation/{ => arch}/parisc/debugging (100%)
 rename Documentation/{ => arch}/parisc/registers (100%)
 rename Documentation/{ => arch}/powerpc/DAWR-POWER9.txt (100%)
 rename Documentation/{ => arch}/powerpc/bootwrapper.txt (100%)
 rename Documentation/{ => arch}/powerpc/cpu_families.txt (100%)
 rename Documentation/{ => arch}/powerpc/cpu_features.txt (100%)
 rename Documentation/{ => arch}/powerpc/cxl.txt (100%)
 rename Documentation/{ => arch}/powerpc/cxlflash.txt (100%)
 rename Documentation/{ => arch}/powerpc/dscr.txt (100%)
 rename Documentation/{ => arch}/powerpc/eeh-pci-error-recovery.txt (100%)
 rename Documentation/{ => arch}/powerpc/firmware-assisted-dump.txt (100%)
 rename Documentation/{ => arch}/powerpc/hvcs.txt (100%)
 rename Documentation/{ => arch}/powerpc/isa-versions.rst (100%)
 rename Documentation/{ => arch}/powerpc/mpc52xx.txt (100%)
 rename Documentation/{ => arch}/powerpc/pci_iov_resource_on_powernv.txt (100%)
 rename Documentation/{ => arch}/powerpc/pmu-ebb.txt (100%)
 rename Documentation/{ => arch}/powerpc/ptrace.txt (100%)
 rename Documentation/{ => arch}/powerpc/qe_firmware.txt (100%)
 rename Documentation/{ => arch}/powerpc/syscall64-abi.txt (100%)
 rename Documentation/{ => arch}/powerpc/transactional_memory.txt (100%)
 rename Documentation/{ => arch}/riscv/index.rst (100%)
 rename Documentation/{ => arch}/riscv/pmu.rst (100%)
 rename Documentation/{ => arch}/s390/3270.ChangeLog (100%)
 rename Documentation/{ => arch}/s390/3270.rst (100%)
 rename Documentation/{ => arch}/s390/cds.rst (100%)
 rename Documentation/{ => arch}/s390/common_io.rst (100%)
 rename Documentation/{ => arch}/s390/config3270.sh (100%)
 rename Documentation/{ => arch}/s390/dasd.rst (100%)
 rename Documentation/{ => arch}/s390/debugging390.rst (100%)
 rename Documentation/{ => arch}/s390/driver-model.rst (100%)
 rename Documentation/{ => arch}/s390/index.rst (100%)
 rename Documentation/{ => arch}/s390/monreader.rst (100%)
 rename Documentation/{ => arch}/s390/qeth.rst (100%)
 rename Documentation/{ => arch}/s390/s390dbf.rst (100%)
 rename Documentation/{ => arch}/s390/text_files.rst (100%)
 rename Documentation/{ => arch}/s390/vfio-ap.rst (100%)
 rename Documentation/{ => arch}/s390/vfio-ccw.rst (100%)
 rename Documentation/{ => arch}/s390/zfcpdump.rst (100%)
 rename Documentation/{ => arch}/sh/conf.py (100%)
 rename Documentation/{ => arch}/sh/index.rst (100%)
 rename Documentation/{ => arch}/sh/new-machine.txt (100%)
 rename Documentation/{ => arch}/sh/register-banks.txt (100%)
 rename Documentation/{ => arch}/sparc/adi.rst (100%)
 rename Documentation/{ => arch}/sparc/console.rst (100%)
 rename Documentation/{ => arch}/sparc/index.rst (100%)
 rename Documentation/{ => arch}/sparc/oradax/dax-hv-api.txt (100%)
 rename Documentation/{ => arch}/sparc/oradax/oracle-dax.rst (100%)
 rename Documentation/{ => arch}/x86/amd-memory-encryption.rst (100%)
 rename Documentation/{ => arch}/x86/boot.rst (100%)
 rename Documentation/{ => arch}/x86/conf.py (100%)
 rename Documentation/{ => arch}/x86/earlyprintk.rst (100%)
 rename Documentation/{ => arch}/x86/entry_64.rst (100%)
 rename Documentation/{ => arch}/x86/exception-tables.rst (100%)
 rename Documentation/{ => arch}/x86/i386/IO-APIC.rst (100%)
 rename Documentation/{ => arch}/x86/i386/index.rst (100%)
 rename Documentation/{ => arch}/x86/index.rst (100%)
 rename Documentation/{ => arch}/x86/intel_mpx.rst (100%)
 rename Documentation/{ => arch}/x86/kernel-stacks.rst (100%)
 rename Documentation/{ => arch}/x86/mds.rst (100%)
 rename Documentation/{ => arch}/x86/microcode.rst (100%)
 rename Documentation/{ => arch}/x86/mtrr.rst (100%)
 rename Documentation/{ => arch}/x86/orc-unwinder.rst (100%)
 rename Documentation/{ => arch}/x86/pat.rst (100%)
 rename Documentation/{ => arch}/x86/pti.rst (100%)
 rename Documentation/{ => arch}/x86/resctrl_ui.rst (100%)
 rename Documentation/{ => arch}/x86/tlb.rst (100%)
 rename Documentation/{ => arch}/x86/topology.rst (100%)
 rename Documentation/{ => arch}/x86/usb-legacy-support.rst (100%)
 rename Documentation/{ => arch}/x86/x86_64/5level-paging.rst (100%)
 rename Documentation/{ => arch}/x86/x86_64/boot-options.rst (100%)
 rename Documentation/{ => arch}/x86/x86_64/cpu-hotplug-spec.rst (100%)
 rename Documentation/{ => arch}/x86/x86_64/fake-numa-for-cpusets.rst (100%)
 rename Documentation/{ => arch}/x86/x86_64/index.rst (100%)
 rename Documentation/{ => arch}/x86/x86_64/machinecheck.rst (100%)
 rename Documentation/{ => arch}/x86/x86_64/mm.rst (100%)
 rename Documentation/{ => arch}/x86/x86_64/uefi.rst (100%)
 rename Documentation/{ => arch}/x86/zero-page.rst (100%)
 rename Documentation/{ => arch}/xtensa/atomctl.txt (100%)
 rename Documentation/{ => arch}/xtensa/booting.txt (100%)
 rename Documentation/{ => arch}/xtensa/mmu.txt (100%)

diff --git a/Documentation/arm/Booting b/Documentation/arch/arm/Booting
similarity index 100%
rename from Documentation/arm/Booting
rename to Documentation/arch/arm/Booting
diff --git a/Documentation/arm/IXP4xx b/Documentation/arch/arm/IXP4xx
similarity index 100%
rename from Documentation/arm/IXP4xx
rename to Documentation/arch/arm/IXP4xx
diff --git a/Documentation/arm/Interrupts b/Documentation/arch/arm/Interrupts
similarity index 100%
rename from Documentation/arm/Interrupts
rename to Documentation/arch/arm/Interrupts
diff --git a/Documentation/arm/Marvell/README b/Documentation/arch/arm/Marvell/README
similarity index 100%
rename from Documentation/arm/Marvell/README
rename to Documentation/arch/arm/Marvell/README
diff --git a/Documentation/arm/Microchip/README b/Documentation/arch/arm/Microchip/README
similarity index 100%
rename from Documentation/arm/Microchip/README
rename to Documentation/arch/arm/Microchip/README
diff --git a/Documentation/arm/Netwinder b/Documentation/arch/arm/Netwinder
similarity index 100%
rename from Documentation/arm/Netwinder
rename to Documentation/arch/arm/Netwinder
diff --git a/Documentation/arm/OMAP/DSS b/Documentation/arch/arm/OMAP/DSS
similarity index 100%
rename from Documentation/arm/OMAP/DSS
rename to Documentation/arch/arm/OMAP/DSS
diff --git a/Documentation/arm/OMAP/README b/Documentation/arch/arm/OMAP/README
similarity index 100%
rename from Documentation/arm/OMAP/README
rename to Documentation/arch/arm/OMAP/README
diff --git a/Documentation/arm/OMAP/omap_pm b/Documentation/arch/arm/OMAP/omap_pm
similarity index 100%
rename from Documentation/arm/OMAP/omap_pm
rename to Documentation/arch/arm/OMAP/omap_pm
diff --git a/Documentation/arm/Porting b/Documentation/arch/arm/Porting
similarity index 100%
rename from Documentation/arm/Porting
rename to Documentation/arch/arm/Porting
diff --git a/Documentation/arm/README b/Documentation/arch/arm/README
similarity index 100%
rename from Documentation/arm/README
rename to Documentation/arch/arm/README
diff --git a/Documentation/arm/SA1100/ADSBitsy b/Documentation/arch/arm/SA1100/ADSBitsy
similarity index 100%
rename from Documentation/arm/SA1100/ADSBitsy
rename to Documentation/arch/arm/SA1100/ADSBitsy
diff --git a/Documentation/arm/SA1100/Assabet b/Documentation/arch/arm/SA1100/Assabet
similarity index 100%
rename from Documentation/arm/SA1100/Assabet
rename to Documentation/arch/arm/SA1100/Assabet
diff --git a/Documentation/arm/SA1100/Brutus b/Documentation/arch/arm/SA1100/Brutus
similarity index 100%
rename from Documentation/arm/SA1100/Brutus
rename to Documentation/arch/arm/SA1100/Brutus
diff --git a/Documentation/arm/SA1100/CERF b/Documentation/arch/arm/SA1100/CERF
similarity index 100%
rename from Documentation/arm/SA1100/CERF
rename to Documentation/arch/arm/SA1100/CERF
diff --git a/Documentation/arm/SA1100/FreeBird b/Documentation/arch/arm/SA1100/FreeBird
similarity index 100%
rename from Documentation/arm/SA1100/FreeBird
rename to Documentation/arch/arm/SA1100/FreeBird
diff --git a/Documentation/arm/SA1100/GraphicsClient b/Documentation/arch/arm/SA1100/GraphicsClient
similarity index 100%
rename from Documentation/arm/SA1100/GraphicsClient
rename to Documentation/arch/arm/SA1100/GraphicsClient
diff --git a/Documentation/arm/SA1100/GraphicsMaster b/Documentation/arch/arm/SA1100/GraphicsMaster
similarity index 100%
rename from Documentation/arm/SA1100/GraphicsMaster
rename to Documentation/arch/arm/SA1100/GraphicsMaster
diff --git a/Documentation/arm/SA1100/HUW_WEBPANEL b/Documentation/arch/arm/SA1100/HUW_WEBPANEL
similarity index 100%
rename from Documentation/arm/SA1100/HUW_WEBPANEL
rename to Documentation/arch/arm/SA1100/HUW_WEBPANEL
diff --git a/Documentation/arm/SA1100/Itsy b/Documentation/arch/arm/SA1100/Itsy
similarity index 100%
rename from Documentation/arm/SA1100/Itsy
rename to Documentation/arch/arm/SA1100/Itsy
diff --git a/Documentation/arm/SA1100/LART b/Documentation/arch/arm/SA1100/LART
similarity index 100%
rename from Documentation/arm/SA1100/LART
rename to Documentation/arch/arm/SA1100/LART
diff --git a/Documentation/arm/SA1100/PLEB b/Documentation/arch/arm/SA1100/PLEB
similarity index 100%
rename from Documentation/arm/SA1100/PLEB
rename to Documentation/arch/arm/SA1100/PLEB
diff --git a/Documentation/arm/SA1100/Pangolin b/Documentation/arch/arm/SA1100/Pangolin
similarity index 100%
rename from Documentation/arm/SA1100/Pangolin
rename to Documentation/arch/arm/SA1100/Pangolin
diff --git a/Documentation/arm/SA1100/Tifon b/Documentation/arch/arm/SA1100/Tifon
similarity index 100%
rename from Documentation/arm/SA1100/Tifon
rename to Documentation/arch/arm/SA1100/Tifon
diff --git a/Documentation/arm/SA1100/Yopy b/Documentation/arch/arm/SA1100/Yopy
similarity index 100%
rename from Documentation/arm/SA1100/Yopy
rename to Documentation/arch/arm/SA1100/Yopy
diff --git a/Documentation/arm/SA1100/empeg b/Documentation/arch/arm/SA1100/empeg
similarity index 100%
rename from Documentation/arm/SA1100/empeg
rename to Documentation/arch/arm/SA1100/empeg
diff --git a/Documentation/arm/SA1100/nanoEngine b/Documentation/arch/arm/SA1100/nanoEngine
similarity index 100%
rename from Documentation/arm/SA1100/nanoEngine
rename to Documentation/arch/arm/SA1100/nanoEngine
diff --git a/Documentation/arm/SA1100/serial_UART b/Documentation/arch/arm/SA1100/serial_UART
similarity index 100%
rename from Documentation/arm/SA1100/serial_UART
rename to Documentation/arch/arm/SA1100/serial_UART
diff --git a/Documentation/arm/SH-Mobile/.gitignore b/Documentation/arch/arm/SH-Mobile/.gitignore
similarity index 100%
rename from Documentation/arm/SH-Mobile/.gitignore
rename to Documentation/arch/arm/SH-Mobile/.gitignore
diff --git a/Documentation/arm/SPEAr/overview.txt b/Documentation/arch/arm/SPEAr/overview.txt
similarity index 100%
rename from Documentation/arm/SPEAr/overview.txt
rename to Documentation/arch/arm/SPEAr/overview.txt
diff --git a/Documentation/arm/Samsung-S3C24XX/CPUfreq.txt b/Documentation/arch/arm/Samsung-S3C24XX/CPUfreq.txt
similarity index 100%
rename from Documentation/arm/Samsung-S3C24XX/CPUfreq.txt
rename to Documentation/arch/arm/Samsung-S3C24XX/CPUfreq.txt
diff --git a/Documentation/arm/Samsung-S3C24XX/EB2410ITX.txt b/Documentation/arch/arm/Samsung-S3C24XX/EB2410ITX.txt
similarity index 100%
rename from Documentation/arm/Samsung-S3C24XX/EB2410ITX.txt
rename to Documentation/arch/arm/Samsung-S3C24XX/EB2410ITX.txt
diff --git a/Documentation/arm/Samsung-S3C24XX/GPIO.txt b/Documentation/arch/arm/Samsung-S3C24XX/GPIO.txt
similarity index 100%
rename from Documentation/arm/Samsung-S3C24XX/GPIO.txt
rename to Documentation/arch/arm/Samsung-S3C24XX/GPIO.txt
diff --git a/Documentation/arm/Samsung-S3C24XX/H1940.txt b/Documentation/arch/arm/Samsung-S3C24XX/H1940.txt
similarity index 100%
rename from Documentation/arm/Samsung-S3C24XX/H1940.txt
rename to Documentation/arch/arm/Samsung-S3C24XX/H1940.txt
diff --git a/Documentation/arm/Samsung-S3C24XX/NAND.txt b/Documentation/arch/arm/Samsung-S3C24XX/NAND.txt
similarity index 100%
rename from Documentation/arm/Samsung-S3C24XX/NAND.txt
rename to Documentation/arch/arm/Samsung-S3C24XX/NAND.txt
diff --git a/Documentation/arm/Samsung-S3C24XX/Overview.txt b/Documentation/arch/arm/Samsung-S3C24XX/Overview.txt
similarity index 100%
rename from Documentation/arm/Samsung-S3C24XX/Overview.txt
rename to Documentation/arch/arm/Samsung-S3C24XX/Overview.txt
diff --git a/Documentation/arm/Samsung-S3C24XX/S3C2412.txt b/Documentation/arch/arm/Samsung-S3C24XX/S3C2412.txt
similarity index 100%
rename from Documentation/arm/Samsung-S3C24XX/S3C2412.txt
rename to Documentation/arch/arm/Samsung-S3C24XX/S3C2412.txt
diff --git a/Documentation/arm/Samsung-S3C24XX/S3C2413.txt b/Documentation/arch/arm/Samsung-S3C24XX/S3C2413.txt
similarity index 100%
rename from Documentation/arm/Samsung-S3C24XX/S3C2413.txt
rename to Documentation/arch/arm/Samsung-S3C24XX/S3C2413.txt
diff --git a/Documentation/arm/Samsung-S3C24XX/SMDK2440.txt b/Documentation/arch/arm/Samsung-S3C24XX/SMDK2440.txt
similarity index 100%
rename from Documentation/arm/Samsung-S3C24XX/SMDK2440.txt
rename to Documentation/arch/arm/Samsung-S3C24XX/SMDK2440.txt
diff --git a/Documentation/arm/Samsung-S3C24XX/Suspend.txt b/Documentation/arch/arm/Samsung-S3C24XX/Suspend.txt
similarity index 100%
rename from Documentation/arm/Samsung-S3C24XX/Suspend.txt
rename to Documentation/arch/arm/Samsung-S3C24XX/Suspend.txt
diff --git a/Documentation/arm/Samsung-S3C24XX/USB-Host.txt b/Documentation/arch/arm/Samsung-S3C24XX/USB-Host.txt
similarity index 100%
rename from Documentation/arm/Samsung-S3C24XX/USB-Host.txt
rename to Documentation/arch/arm/Samsung-S3C24XX/USB-Host.txt
diff --git a/Documentation/arm/Samsung/Bootloader-interface.txt b/Documentation/arch/arm/Samsung/Bootloader-interface.txt
similarity index 100%
rename from Documentation/arm/Samsung/Bootloader-interface.txt
rename to Documentation/arch/arm/Samsung/Bootloader-interface.txt
diff --git a/Documentation/arm/Samsung/GPIO.txt b/Documentation/arch/arm/Samsung/GPIO.txt
similarity index 100%
rename from Documentation/arm/Samsung/GPIO.txt
rename to Documentation/arch/arm/Samsung/GPIO.txt
diff --git a/Documentation/arm/Samsung/Overview.txt b/Documentation/arch/arm/Samsung/Overview.txt
similarity index 100%
rename from Documentation/arm/Samsung/Overview.txt
rename to Documentation/arch/arm/Samsung/Overview.txt
diff --git a/Documentation/arm/Samsung/clksrc-change-registers.awk b/Documentation/arch/arm/Samsung/clksrc-change-registers.awk
similarity index 100%
rename from Documentation/arm/Samsung/clksrc-change-registers.awk
rename to Documentation/arch/arm/Samsung/clksrc-change-registers.awk
diff --git a/Documentation/arm/Setup b/Documentation/arch/arm/Setup
similarity index 100%
rename from Documentation/arm/Setup
rename to Documentation/arch/arm/Setup
diff --git a/Documentation/arm/VFP/release-notes.txt b/Documentation/arch/arm/VFP/release-notes.txt
similarity index 100%
rename from Documentation/arm/VFP/release-notes.txt
rename to Documentation/arch/arm/VFP/release-notes.txt
diff --git a/Documentation/arm/cluster-pm-race-avoidance.txt b/Documentation/arch/arm/cluster-pm-race-avoidance.txt
similarity index 100%
rename from Documentation/arm/cluster-pm-race-avoidance.txt
rename to Documentation/arch/arm/cluster-pm-race-avoidance.txt
diff --git a/Documentation/arm/firmware.txt b/Documentation/arch/arm/firmware.txt
similarity index 100%
rename from Documentation/arm/firmware.txt
rename to Documentation/arch/arm/firmware.txt
diff --git a/Documentation/arm/kernel_mode_neon.txt b/Documentation/arch/arm/kernel_mode_neon.txt
similarity index 100%
rename from Documentation/arm/kernel_mode_neon.txt
rename to Documentation/arch/arm/kernel_mode_neon.txt
diff --git a/Documentation/arm/kernel_user_helpers.txt b/Documentation/arch/arm/kernel_user_helpers.txt
similarity index 100%
rename from Documentation/arm/kernel_user_helpers.txt
rename to Documentation/arch/arm/kernel_user_helpers.txt
diff --git a/Documentation/arm/keystone/Overview.txt b/Documentation/arch/arm/keystone/Overview.txt
similarity index 100%
rename from Documentation/arm/keystone/Overview.txt
rename to Documentation/arch/arm/keystone/Overview.txt
diff --git a/Documentation/arm/keystone/knav-qmss.txt b/Documentation/arch/arm/keystone/knav-qmss.txt
similarity index 100%
rename from Documentation/arm/keystone/knav-qmss.txt
rename to Documentation/arch/arm/keystone/knav-qmss.txt
diff --git a/Documentation/arm/mem_alignment b/Documentation/arch/arm/mem_alignment
similarity index 100%
rename from Documentation/arm/mem_alignment
rename to Documentation/arch/arm/mem_alignment
diff --git a/Documentation/arm/memory.txt b/Documentation/arch/arm/memory.txt
similarity index 100%
rename from Documentation/arm/memory.txt
rename to Documentation/arch/arm/memory.txt
diff --git a/Documentation/arm/nwfpe/NOTES b/Documentation/arch/arm/nwfpe/NOTES
similarity index 100%
rename from Documentation/arm/nwfpe/NOTES
rename to Documentation/arch/arm/nwfpe/NOTES
diff --git a/Documentation/arm/nwfpe/README b/Documentation/arch/arm/nwfpe/README
similarity index 100%
rename from Documentation/arm/nwfpe/README
rename to Documentation/arch/arm/nwfpe/README
diff --git a/Documentation/arm/nwfpe/README.FPE b/Documentation/arch/arm/nwfpe/README.FPE
similarity index 100%
rename from Documentation/arm/nwfpe/README.FPE
rename to Documentation/arch/arm/nwfpe/README.FPE
diff --git a/Documentation/arm/nwfpe/TODO b/Documentation/arch/arm/nwfpe/TODO
similarity index 100%
rename from Documentation/arm/nwfpe/TODO
rename to Documentation/arch/arm/nwfpe/TODO
diff --git a/Documentation/arm/pxa/mfp.txt b/Documentation/arch/arm/pxa/mfp.txt
similarity index 100%
rename from Documentation/arm/pxa/mfp.txt
rename to Documentation/arch/arm/pxa/mfp.txt
diff --git a/Documentation/arm/sti/overview.txt b/Documentation/arch/arm/sti/overview.txt
similarity index 100%
rename from Documentation/arm/sti/overview.txt
rename to Documentation/arch/arm/sti/overview.txt
diff --git a/Documentation/arm/sti/stih407-overview.txt b/Documentation/arch/arm/sti/stih407-overview.txt
similarity index 100%
rename from Documentation/arm/sti/stih407-overview.txt
rename to Documentation/arch/arm/sti/stih407-overview.txt
diff --git a/Documentation/arm/sti/stih415-overview.txt b/Documentation/arch/arm/sti/stih415-overview.txt
similarity index 100%
rename from Documentation/arm/sti/stih415-overview.txt
rename to Documentation/arch/arm/sti/stih415-overview.txt
diff --git a/Documentation/arm/sti/stih416-overview.txt b/Documentation/arch/arm/sti/stih416-overview.txt
similarity index 100%
rename from Documentation/arm/sti/stih416-overview.txt
rename to Documentation/arch/arm/sti/stih416-overview.txt
diff --git a/Documentation/arm/sti/stih418-overview.txt b/Documentation/arch/arm/sti/stih418-overview.txt
similarity index 100%
rename from Documentation/arm/sti/stih418-overview.txt
rename to Documentation/arch/arm/sti/stih418-overview.txt
diff --git a/Documentation/arm/stm32/overview.rst b/Documentation/arch/arm/stm32/overview.rst
similarity index 100%
rename from Documentation/arm/stm32/overview.rst
rename to Documentation/arch/arm/stm32/overview.rst
diff --git a/Documentation/arm/stm32/stm32f429-overview.rst b/Documentation/arch/arm/stm32/stm32f429-overview.rst
similarity index 100%
rename from Documentation/arm/stm32/stm32f429-overview.rst
rename to Documentation/arch/arm/stm32/stm32f429-overview.rst
diff --git a/Documentation/arm/stm32/stm32f746-overview.rst b/Documentation/arch/arm/stm32/stm32f746-overview.rst
similarity index 100%
rename from Documentation/arm/stm32/stm32f746-overview.rst
rename to Documentation/arch/arm/stm32/stm32f746-overview.rst
diff --git a/Documentation/arm/stm32/stm32f769-overview.rst b/Documentation/arch/arm/stm32/stm32f769-overview.rst
similarity index 100%
rename from Documentation/arm/stm32/stm32f769-overview.rst
rename to Documentation/arch/arm/stm32/stm32f769-overview.rst
diff --git a/Documentation/arm/stm32/stm32h743-overview.rst b/Documentation/arch/arm/stm32/stm32h743-overview.rst
similarity index 100%
rename from Documentation/arm/stm32/stm32h743-overview.rst
rename to Documentation/arch/arm/stm32/stm32h743-overview.rst
diff --git a/Documentation/arm/stm32/stm32mp157-overview.rst b/Documentation/arch/arm/stm32/stm32mp157-overview.rst
similarity index 100%
rename from Documentation/arm/stm32/stm32mp157-overview.rst
rename to Documentation/arch/arm/stm32/stm32mp157-overview.rst
diff --git a/Documentation/arm/sunxi/README b/Documentation/arch/arm/sunxi/README
similarity index 100%
rename from Documentation/arm/sunxi/README
rename to Documentation/arch/arm/sunxi/README
diff --git a/Documentation/arm/sunxi/clocks.txt b/Documentation/arch/arm/sunxi/clocks.txt
similarity index 100%
rename from Documentation/arm/sunxi/clocks.txt
rename to Documentation/arch/arm/sunxi/clocks.txt
diff --git a/Documentation/arm/swp_emulation b/Documentation/arch/arm/swp_emulation
similarity index 100%
rename from Documentation/arm/swp_emulation
rename to Documentation/arch/arm/swp_emulation
diff --git a/Documentation/arm/tcm.txt b/Documentation/arch/arm/tcm.txt
similarity index 100%
rename from Documentation/arm/tcm.txt
rename to Documentation/arch/arm/tcm.txt
diff --git a/Documentation/arm/uefi.txt b/Documentation/arch/arm/uefi.txt
similarity index 100%
rename from Documentation/arm/uefi.txt
rename to Documentation/arch/arm/uefi.txt
diff --git a/Documentation/arm/vlocks.txt b/Documentation/arch/arm/vlocks.txt
similarity index 100%
rename from Documentation/arm/vlocks.txt
rename to Documentation/arch/arm/vlocks.txt
diff --git a/Documentation/arm64/acpi_object_usage.rst b/Documentation/arch/arm64/acpi_object_usage.rst
similarity index 100%
rename from Documentation/arm64/acpi_object_usage.rst
rename to Documentation/arch/arm64/acpi_object_usage.rst
diff --git a/Documentation/arm64/arm-acpi.rst b/Documentation/arch/arm64/arm-acpi.rst
similarity index 100%
rename from Documentation/arm64/arm-acpi.rst
rename to Documentation/arch/arm64/arm-acpi.rst
diff --git a/Documentation/arm64/booting.rst b/Documentation/arch/arm64/booting.rst
similarity index 100%
rename from Documentation/arm64/booting.rst
rename to Documentation/arch/arm64/booting.rst
diff --git a/Documentation/arm64/cpu-feature-registers.rst b/Documentation/arch/arm64/cpu-feature-registers.rst
similarity index 100%
rename from Documentation/arm64/cpu-feature-registers.rst
rename to Documentation/arch/arm64/cpu-feature-registers.rst
diff --git a/Documentation/arm64/elf_hwcaps.rst b/Documentation/arch/arm64/elf_hwcaps.rst
similarity index 100%
rename from Documentation/arm64/elf_hwcaps.rst
rename to Documentation/arch/arm64/elf_hwcaps.rst
diff --git a/Documentation/arm64/hugetlbpage.rst b/Documentation/arch/arm64/hugetlbpage.rst
similarity index 100%
rename from Documentation/arm64/hugetlbpage.rst
rename to Documentation/arch/arm64/hugetlbpage.rst
diff --git a/Documentation/arm64/index.rst b/Documentation/arch/arm64/index.rst
similarity index 100%
rename from Documentation/arm64/index.rst
rename to Documentation/arch/arm64/index.rst
diff --git a/Documentation/arm64/legacy_instructions.rst b/Documentation/arch/arm64/legacy_instructions.rst
similarity index 100%
rename from Documentation/arm64/legacy_instructions.rst
rename to Documentation/arch/arm64/legacy_instructions.rst
diff --git a/Documentation/arm64/memory.rst b/Documentation/arch/arm64/memory.rst
similarity index 100%
rename from Documentation/arm64/memory.rst
rename to Documentation/arch/arm64/memory.rst
diff --git a/Documentation/arm64/perf.txt b/Documentation/arch/arm64/perf.txt
similarity index 100%
rename from Documentation/arm64/perf.txt
rename to Documentation/arch/arm64/perf.txt
diff --git a/Documentation/arm64/pointer-authentication.rst b/Documentation/arch/arm64/pointer-authentication.rst
similarity index 100%
rename from Documentation/arm64/pointer-authentication.rst
rename to Documentation/arch/arm64/pointer-authentication.rst
diff --git a/Documentation/arm64/silicon-errata.rst b/Documentation/arch/arm64/silicon-errata.rst
similarity index 100%
rename from Documentation/arm64/silicon-errata.rst
rename to Documentation/arch/arm64/silicon-errata.rst
diff --git a/Documentation/arm64/sve.rst b/Documentation/arch/arm64/sve.rst
similarity index 100%
rename from Documentation/arm64/sve.rst
rename to Documentation/arch/arm64/sve.rst
diff --git a/Documentation/arm64/tagged-pointers.rst b/Documentation/arch/arm64/tagged-pointers.rst
similarity index 100%
rename from Documentation/arm64/tagged-pointers.rst
rename to Documentation/arch/arm64/tagged-pointers.rst
diff --git a/Documentation/ia64/IRQ-redir.txt b/Documentation/arch/ia64/IRQ-redir.txt
similarity index 100%
rename from Documentation/ia64/IRQ-redir.txt
rename to Documentation/arch/ia64/IRQ-redir.txt
diff --git a/Documentation/ia64/README b/Documentation/arch/ia64/README
similarity index 100%
rename from Documentation/ia64/README
rename to Documentation/arch/ia64/README
diff --git a/Documentation/ia64/aliasing.txt b/Documentation/arch/ia64/aliasing.txt
similarity index 100%
rename from Documentation/ia64/aliasing.txt
rename to Documentation/arch/ia64/aliasing.txt
diff --git a/Documentation/ia64/efirtc.txt b/Documentation/arch/ia64/efirtc.txt
similarity index 100%
rename from Documentation/ia64/efirtc.txt
rename to Documentation/arch/ia64/efirtc.txt
diff --git a/Documentation/ia64/err_inject.txt b/Documentation/arch/ia64/err_inject.txt
similarity index 100%
rename from Documentation/ia64/err_inject.txt
rename to Documentation/arch/ia64/err_inject.txt
diff --git a/Documentation/ia64/fsys.txt b/Documentation/arch/ia64/fsys.txt
similarity index 100%
rename from Documentation/ia64/fsys.txt
rename to Documentation/arch/ia64/fsys.txt
diff --git a/Documentation/ia64/mca.txt b/Documentation/arch/ia64/mca.txt
similarity index 100%
rename from Documentation/ia64/mca.txt
rename to Documentation/arch/ia64/mca.txt
diff --git a/Documentation/ia64/serial.txt b/Documentation/arch/ia64/serial.txt
similarity index 100%
rename from Documentation/ia64/serial.txt
rename to Documentation/arch/ia64/serial.txt
diff --git a/Documentation/ia64/xen.txt b/Documentation/arch/ia64/xen.txt
similarity index 100%
rename from Documentation/ia64/xen.txt
rename to Documentation/arch/ia64/xen.txt
diff --git a/Documentation/m68k/README.buddha b/Documentation/arch/m68k/README.buddha
similarity index 100%
rename from Documentation/m68k/README.buddha
rename to Documentation/arch/m68k/README.buddha
diff --git a/Documentation/m68k/kernel-options.txt b/Documentation/arch/m68k/kernel-options.txt
similarity index 100%
rename from Documentation/m68k/kernel-options.txt
rename to Documentation/arch/m68k/kernel-options.txt
diff --git a/Documentation/mips/AU1xxx_IDE.README b/Documentation/arch/mips/AU1xxx_IDE.README
similarity index 100%
rename from Documentation/mips/AU1xxx_IDE.README
rename to Documentation/arch/mips/AU1xxx_IDE.README
diff --git a/Documentation/nios2/README b/Documentation/arch/nios2/README
similarity index 100%
rename from Documentation/nios2/README
rename to Documentation/arch/nios2/README
diff --git a/Documentation/parisc/debugging b/Documentation/arch/parisc/debugging
similarity index 100%
rename from Documentation/parisc/debugging
rename to Documentation/arch/parisc/debugging
diff --git a/Documentation/parisc/registers b/Documentation/arch/parisc/registers
similarity index 100%
rename from Documentation/parisc/registers
rename to Documentation/arch/parisc/registers
diff --git a/Documentation/powerpc/DAWR-POWER9.txt b/Documentation/arch/powerpc/DAWR-POWER9.txt
similarity index 100%
rename from Documentation/powerpc/DAWR-POWER9.txt
rename to Documentation/arch/powerpc/DAWR-POWER9.txt
diff --git a/Documentation/powerpc/bootwrapper.txt b/Documentation/arch/powerpc/bootwrapper.txt
similarity index 100%
rename from Documentation/powerpc/bootwrapper.txt
rename to Documentation/arch/powerpc/bootwrapper.txt
diff --git a/Documentation/powerpc/cpu_families.txt b/Documentation/arch/powerpc/cpu_families.txt
similarity index 100%
rename from Documentation/powerpc/cpu_families.txt
rename to Documentation/arch/powerpc/cpu_families.txt
diff --git a/Documentation/powerpc/cpu_features.txt b/Documentation/arch/powerpc/cpu_features.txt
similarity index 100%
rename from Documentation/powerpc/cpu_features.txt
rename to Documentation/arch/powerpc/cpu_features.txt
diff --git a/Documentation/powerpc/cxl.txt b/Documentation/arch/powerpc/cxl.txt
similarity index 100%
rename from Documentation/powerpc/cxl.txt
rename to Documentation/arch/powerpc/cxl.txt
diff --git a/Documentation/powerpc/cxlflash.txt b/Documentation/arch/powerpc/cxlflash.txt
similarity index 100%
rename from Documentation/powerpc/cxlflash.txt
rename to Documentation/arch/powerpc/cxlflash.txt
diff --git a/Documentation/powerpc/dscr.txt b/Documentation/arch/powerpc/dscr.txt
similarity index 100%
rename from Documentation/powerpc/dscr.txt
rename to Documentation/arch/powerpc/dscr.txt
diff --git a/Documentation/powerpc/eeh-pci-error-recovery.txt b/Documentation/arch/powerpc/eeh-pci-error-recovery.txt
similarity index 100%
rename from Documentation/powerpc/eeh-pci-error-recovery.txt
rename to Documentation/arch/powerpc/eeh-pci-error-recovery.txt
diff --git a/Documentation/powerpc/firmware-assisted-dump.txt b/Documentation/arch/powerpc/firmware-assisted-dump.txt
similarity index 100%
rename from Documentation/powerpc/firmware-assisted-dump.txt
rename to Documentation/arch/powerpc/firmware-assisted-dump.txt
diff --git a/Documentation/powerpc/hvcs.txt b/Documentation/arch/powerpc/hvcs.txt
similarity index 100%
rename from Documentation/powerpc/hvcs.txt
rename to Documentation/arch/powerpc/hvcs.txt
diff --git a/Documentation/powerpc/isa-versions.rst b/Documentation/arch/powerpc/isa-versions.rst
similarity index 100%
rename from Documentation/powerpc/isa-versions.rst
rename to Documentation/arch/powerpc/isa-versions.rst
diff --git a/Documentation/powerpc/mpc52xx.txt b/Documentation/arch/powerpc/mpc52xx.txt
similarity index 100%
rename from Documentation/powerpc/mpc52xx.txt
rename to Documentation/arch/powerpc/mpc52xx.txt
diff --git a/Documentation/powerpc/pci_iov_resource_on_powernv.txt b/Documentation/arch/powerpc/pci_iov_resource_on_powernv.txt
similarity index 100%
rename from Documentation/powerpc/pci_iov_resource_on_powernv.txt
rename to Documentation/arch/powerpc/pci_iov_resource_on_powernv.txt
diff --git a/Documentation/powerpc/pmu-ebb.txt b/Documentation/arch/powerpc/pmu-ebb.txt
similarity index 100%
rename from Documentation/powerpc/pmu-ebb.txt
rename to Documentation/arch/powerpc/pmu-ebb.txt
diff --git a/Documentation/powerpc/ptrace.txt b/Documentation/arch/powerpc/ptrace.txt
similarity index 100%
rename from Documentation/powerpc/ptrace.txt
rename to Documentation/arch/powerpc/ptrace.txt
diff --git a/Documentation/powerpc/qe_firmware.txt b/Documentation/arch/powerpc/qe_firmware.txt
similarity index 100%
rename from Documentation/powerpc/qe_firmware.txt
rename to Documentation/arch/powerpc/qe_firmware.txt
diff --git a/Documentation/powerpc/syscall64-abi.txt b/Documentation/arch/powerpc/syscall64-abi.txt
similarity index 100%
rename from Documentation/powerpc/syscall64-abi.txt
rename to Documentation/arch/powerpc/syscall64-abi.txt
diff --git a/Documentation/powerpc/transactional_memory.txt b/Documentation/arch/powerpc/transactional_memory.txt
similarity index 100%
rename from Documentation/powerpc/transactional_memory.txt
rename to Documentation/arch/powerpc/transactional_memory.txt
diff --git a/Documentation/riscv/index.rst b/Documentation/arch/riscv/index.rst
similarity index 100%
rename from Documentation/riscv/index.rst
rename to Documentation/arch/riscv/index.rst
diff --git a/Documentation/riscv/pmu.rst b/Documentation/arch/riscv/pmu.rst
similarity index 100%
rename from Documentation/riscv/pmu.rst
rename to Documentation/arch/riscv/pmu.rst
diff --git a/Documentation/s390/3270.ChangeLog b/Documentation/arch/s390/3270.ChangeLog
similarity index 100%
rename from Documentation/s390/3270.ChangeLog
rename to Documentation/arch/s390/3270.ChangeLog
diff --git a/Documentation/s390/3270.rst b/Documentation/arch/s390/3270.rst
similarity index 100%
rename from Documentation/s390/3270.rst
rename to Documentation/arch/s390/3270.rst
diff --git a/Documentation/s390/cds.rst b/Documentation/arch/s390/cds.rst
similarity index 100%
rename from Documentation/s390/cds.rst
rename to Documentation/arch/s390/cds.rst
diff --git a/Documentation/s390/common_io.rst b/Documentation/arch/s390/common_io.rst
similarity index 100%
rename from Documentation/s390/common_io.rst
rename to Documentation/arch/s390/common_io.rst
diff --git a/Documentation/s390/config3270.sh b/Documentation/arch/s390/config3270.sh
similarity index 100%
rename from Documentation/s390/config3270.sh
rename to Documentation/arch/s390/config3270.sh
diff --git a/Documentation/s390/dasd.rst b/Documentation/arch/s390/dasd.rst
similarity index 100%
rename from Documentation/s390/dasd.rst
rename to Documentation/arch/s390/dasd.rst
diff --git a/Documentation/s390/debugging390.rst b/Documentation/arch/s390/debugging390.rst
similarity index 100%
rename from Documentation/s390/debugging390.rst
rename to Documentation/arch/s390/debugging390.rst
diff --git a/Documentation/s390/driver-model.rst b/Documentation/arch/s390/driver-model.rst
similarity index 100%
rename from Documentation/s390/driver-model.rst
rename to Documentation/arch/s390/driver-model.rst
diff --git a/Documentation/s390/index.rst b/Documentation/arch/s390/index.rst
similarity index 100%
rename from Documentation/s390/index.rst
rename to Documentation/arch/s390/index.rst
diff --git a/Documentation/s390/monreader.rst b/Documentation/arch/s390/monreader.rst
similarity index 100%
rename from Documentation/s390/monreader.rst
rename to Documentation/arch/s390/monreader.rst
diff --git a/Documentation/s390/qeth.rst b/Documentation/arch/s390/qeth.rst
similarity index 100%
rename from Documentation/s390/qeth.rst
rename to Documentation/arch/s390/qeth.rst
diff --git a/Documentation/s390/s390dbf.rst b/Documentation/arch/s390/s390dbf.rst
similarity index 100%
rename from Documentation/s390/s390dbf.rst
rename to Documentation/arch/s390/s390dbf.rst
diff --git a/Documentation/s390/text_files.rst b/Documentation/arch/s390/text_files.rst
similarity index 100%
rename from Documentation/s390/text_files.rst
rename to Documentation/arch/s390/text_files.rst
diff --git a/Documentation/s390/vfio-ap.rst b/Documentation/arch/s390/vfio-ap.rst
similarity index 100%
rename from Documentation/s390/vfio-ap.rst
rename to Documentation/arch/s390/vfio-ap.rst
diff --git a/Documentation/s390/vfio-ccw.rst b/Documentation/arch/s390/vfio-ccw.rst
similarity index 100%
rename from Documentation/s390/vfio-ccw.rst
rename to Documentation/arch/s390/vfio-ccw.rst
diff --git a/Documentation/s390/zfcpdump.rst b/Documentation/arch/s390/zfcpdump.rst
similarity index 100%
rename from Documentation/s390/zfcpdump.rst
rename to Documentation/arch/s390/zfcpdump.rst
diff --git a/Documentation/sh/conf.py b/Documentation/arch/sh/conf.py
similarity index 100%
rename from Documentation/sh/conf.py
rename to Documentation/arch/sh/conf.py
diff --git a/Documentation/sh/index.rst b/Documentation/arch/sh/index.rst
similarity index 100%
rename from Documentation/sh/index.rst
rename to Documentation/arch/sh/index.rst
diff --git a/Documentation/sh/new-machine.txt b/Documentation/arch/sh/new-machine.txt
similarity index 100%
rename from Documentation/sh/new-machine.txt
rename to Documentation/arch/sh/new-machine.txt
diff --git a/Documentation/sh/register-banks.txt b/Documentation/arch/sh/register-banks.txt
similarity index 100%
rename from Documentation/sh/register-banks.txt
rename to Documentation/arch/sh/register-banks.txt
diff --git a/Documentation/sparc/adi.rst b/Documentation/arch/sparc/adi.rst
similarity index 100%
rename from Documentation/sparc/adi.rst
rename to Documentation/arch/sparc/adi.rst
diff --git a/Documentation/sparc/console.rst b/Documentation/arch/sparc/console.rst
similarity index 100%
rename from Documentation/sparc/console.rst
rename to Documentation/arch/sparc/console.rst
diff --git a/Documentation/sparc/index.rst b/Documentation/arch/sparc/index.rst
similarity index 100%
rename from Documentation/sparc/index.rst
rename to Documentation/arch/sparc/index.rst
diff --git a/Documentation/sparc/oradax/dax-hv-api.txt b/Documentation/arch/sparc/oradax/dax-hv-api.txt
similarity index 100%
rename from Documentation/sparc/oradax/dax-hv-api.txt
rename to Documentation/arch/sparc/oradax/dax-hv-api.txt
diff --git a/Documentation/sparc/oradax/oracle-dax.rst b/Documentation/arch/sparc/oradax/oracle-dax.rst
similarity index 100%
rename from Documentation/sparc/oradax/oracle-dax.rst
rename to Documentation/arch/sparc/oradax/oracle-dax.rst
diff --git a/Documentation/x86/amd-memory-encryption.rst b/Documentation/arch/x86/amd-memory-encryption.rst
similarity index 100%
rename from Documentation/x86/amd-memory-encryption.rst
rename to Documentation/arch/x86/amd-memory-encryption.rst
diff --git a/Documentation/x86/boot.rst b/Documentation/arch/x86/boot.rst
similarity index 100%
rename from Documentation/x86/boot.rst
rename to Documentation/arch/x86/boot.rst
diff --git a/Documentation/x86/conf.py b/Documentation/arch/x86/conf.py
similarity index 100%
rename from Documentation/x86/conf.py
rename to Documentation/arch/x86/conf.py
diff --git a/Documentation/x86/earlyprintk.rst b/Documentation/arch/x86/earlyprintk.rst
similarity index 100%
rename from Documentation/x86/earlyprintk.rst
rename to Documentation/arch/x86/earlyprintk.rst
diff --git a/Documentation/x86/entry_64.rst b/Documentation/arch/x86/entry_64.rst
similarity index 100%
rename from Documentation/x86/entry_64.rst
rename to Documentation/arch/x86/entry_64.rst
diff --git a/Documentation/x86/exception-tables.rst b/Documentation/arch/x86/exception-tables.rst
similarity index 100%
rename from Documentation/x86/exception-tables.rst
rename to Documentation/arch/x86/exception-tables.rst
diff --git a/Documentation/x86/i386/IO-APIC.rst b/Documentation/arch/x86/i386/IO-APIC.rst
similarity index 100%
rename from Documentation/x86/i386/IO-APIC.rst
rename to Documentation/arch/x86/i386/IO-APIC.rst
diff --git a/Documentation/x86/i386/index.rst b/Documentation/arch/x86/i386/index.rst
similarity index 100%
rename from Documentation/x86/i386/index.rst
rename to Documentation/arch/x86/i386/index.rst
diff --git a/Documentation/x86/index.rst b/Documentation/arch/x86/index.rst
similarity index 100%
rename from Documentation/x86/index.rst
rename to Documentation/arch/x86/index.rst
diff --git a/Documentation/x86/intel_mpx.rst b/Documentation/arch/x86/intel_mpx.rst
similarity index 100%
rename from Documentation/x86/intel_mpx.rst
rename to Documentation/arch/x86/intel_mpx.rst
diff --git a/Documentation/x86/kernel-stacks.rst b/Documentation/arch/x86/kernel-stacks.rst
similarity index 100%
rename from Documentation/x86/kernel-stacks.rst
rename to Documentation/arch/x86/kernel-stacks.rst
diff --git a/Documentation/x86/mds.rst b/Documentation/arch/x86/mds.rst
similarity index 100%
rename from Documentation/x86/mds.rst
rename to Documentation/arch/x86/mds.rst
diff --git a/Documentation/x86/microcode.rst b/Documentation/arch/x86/microcode.rst
similarity index 100%
rename from Documentation/x86/microcode.rst
rename to Documentation/arch/x86/microcode.rst
diff --git a/Documentation/x86/mtrr.rst b/Documentation/arch/x86/mtrr.rst
similarity index 100%
rename from Documentation/x86/mtrr.rst
rename to Documentation/arch/x86/mtrr.rst
diff --git a/Documentation/x86/orc-unwinder.rst b/Documentation/arch/x86/orc-unwinder.rst
similarity index 100%
rename from Documentation/x86/orc-unwinder.rst
rename to Documentation/arch/x86/orc-unwinder.rst
diff --git a/Documentation/x86/pat.rst b/Documentation/arch/x86/pat.rst
similarity index 100%
rename from Documentation/x86/pat.rst
rename to Documentation/arch/x86/pat.rst
diff --git a/Documentation/x86/pti.rst b/Documentation/arch/x86/pti.rst
similarity index 100%
rename from Documentation/x86/pti.rst
rename to Documentation/arch/x86/pti.rst
diff --git a/Documentation/x86/resctrl_ui.rst b/Documentation/arch/x86/resctrl_ui.rst
similarity index 100%
rename from Documentation/x86/resctrl_ui.rst
rename to Documentation/arch/x86/resctrl_ui.rst
diff --git a/Documentation/x86/tlb.rst b/Documentation/arch/x86/tlb.rst
similarity index 100%
rename from Documentation/x86/tlb.rst
rename to Documentation/arch/x86/tlb.rst
diff --git a/Documentation/x86/topology.rst b/Documentation/arch/x86/topology.rst
similarity index 100%
rename from Documentation/x86/topology.rst
rename to Documentation/arch/x86/topology.rst
diff --git a/Documentation/x86/usb-legacy-support.rst b/Documentation/arch/x86/usb-legacy-support.rst
similarity index 100%
rename from Documentation/x86/usb-legacy-support.rst
rename to Documentation/arch/x86/usb-legacy-support.rst
diff --git a/Documentation/x86/x86_64/5level-paging.rst b/Documentation/arch/x86/x86_64/5level-paging.rst
similarity index 100%
rename from Documentation/x86/x86_64/5level-paging.rst
rename to Documentation/arch/x86/x86_64/5level-paging.rst
diff --git a/Documentation/x86/x86_64/boot-options.rst b/Documentation/arch/x86/x86_64/boot-options.rst
similarity index 100%
rename from Documentation/x86/x86_64/boot-options.rst
rename to Documentation/arch/x86/x86_64/boot-options.rst
diff --git a/Documentation/x86/x86_64/cpu-hotplug-spec.rst b/Documentation/arch/x86/x86_64/cpu-hotplug-spec.rst
similarity index 100%
rename from Documentation/x86/x86_64/cpu-hotplug-spec.rst
rename to Documentation/arch/x86/x86_64/cpu-hotplug-spec.rst
diff --git a/Documentation/x86/x86_64/fake-numa-for-cpusets.rst b/Documentation/arch/x86/x86_64/fake-numa-for-cpusets.rst
similarity index 100%
rename from Documentation/x86/x86_64/fake-numa-for-cpusets.rst
rename to Documentation/arch/x86/x86_64/fake-numa-for-cpusets.rst
diff --git a/Documentation/x86/x86_64/index.rst b/Documentation/arch/x86/x86_64/index.rst
similarity index 100%
rename from Documentation/x86/x86_64/index.rst
rename to Documentation/arch/x86/x86_64/index.rst
diff --git a/Documentation/x86/x86_64/machinecheck.rst b/Documentation/arch/x86/x86_64/machinecheck.rst
similarity index 100%
rename from Documentation/x86/x86_64/machinecheck.rst
rename to Documentation/arch/x86/x86_64/machinecheck.rst
diff --git a/Documentation/x86/x86_64/mm.rst b/Documentation/arch/x86/x86_64/mm.rst
similarity index 100%
rename from Documentation/x86/x86_64/mm.rst
rename to Documentation/arch/x86/x86_64/mm.rst
diff --git a/Documentation/x86/x86_64/uefi.rst b/Documentation/arch/x86/x86_64/uefi.rst
similarity index 100%
rename from Documentation/x86/x86_64/uefi.rst
rename to Documentation/arch/x86/x86_64/uefi.rst
diff --git a/Documentation/x86/zero-page.rst b/Documentation/arch/x86/zero-page.rst
similarity index 100%
rename from Documentation/x86/zero-page.rst
rename to Documentation/arch/x86/zero-page.rst
diff --git a/Documentation/xtensa/atomctl.txt b/Documentation/arch/xtensa/atomctl.txt
similarity index 100%
rename from Documentation/xtensa/atomctl.txt
rename to Documentation/arch/xtensa/atomctl.txt
diff --git a/Documentation/xtensa/booting.txt b/Documentation/arch/xtensa/booting.txt
similarity index 100%
rename from Documentation/xtensa/booting.txt
rename to Documentation/arch/xtensa/booting.txt
diff --git a/Documentation/xtensa/mmu.txt b/Documentation/arch/xtensa/mmu.txt
similarity index 100%
rename from Documentation/xtensa/mmu.txt
rename to Documentation/arch/xtensa/mmu.txt

From patchwork Fri Jul 12 02:20:08 2019
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Alex Shi <alex.shi@linux.alibaba.com>
X-Patchwork-Id: 11041057
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1E7E714E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 12 Jul 2019 02:20:49 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 0EEF72892E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 12 Jul 2019 02:20:49 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 02A6C2894B; Fri, 12 Jul 2019 02:20:48 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-7.9 required=2.0 tests=BAYES_00,MAILING_LIST_MULTI,
	RCVD_IN_DNSWL_HI,UNPARSEABLE_RELAY autolearn=unavailable version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 25B4028985
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 12 Jul 2019 02:20:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729282AbfGLCUm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 11 Jul 2019 22:20:42 -0400
Received: from out30-57.freemail.mail.aliyun.com ([115.124.30.57]:54515 "EHLO
        out30-57.freemail.mail.aliyun.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728866AbfGLCUi (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 11 Jul 2019 22:20:38 -0400
X-Alimail-AntiSpam: 
 AC=PASS;BC=-1|-1;BR=01201311R151e4;CH=green;DM=||false|;FP=0|-1|-1|-1|0|-1|-1|-1;HT=e01e04395;MF=alex.shi@linux.alibaba.com;NM=1;PH=DS;RN=23;SR=0;TI=SMTPD_---0TWfTwyQ_1562898030;
Received: from localhost(mailfrom:alex.shi@linux.alibaba.com
 fp:SMTPD_---0TWfTwyQ_1562898030)
          by smtp.aliyun-inc.com(127.0.0.1);
          Fri, 12 Jul 2019 10:20:30 +0800
From: Alex Shi <alex.shi@linux.alibaba.com>
To: linux-doc@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>
Cc: Alex Shi <alex.shi@linux.alibaba.com>,
        linux-kernel@vger.kernel.org,
        linux-stm32@st-md-mailman.stormreply.com,
        linux-arm-kernel@lists.infradead.org,
        linuxppc-dev@lists.ozlabs.org, linux-riscv@lists.infradead.org,
        linux-omap@vger.kernel.org, linux-fbdev@vger.kernel.org,
        linux-samsung-soc@vger.kernel.org, linux-ia64@vger.kernel.org,
        linux-mips@vger.kernel.org, linux-parisc@vger.kernel.org,
        linux-scsi@vger.kernel.org, linux-s390@vger.kernel.org,
        kvm@vger.kernel.org, linux-sh@vger.kernel.org,
        Kukjin Kim <kgene@kernel.org>,
        Krzysztof Kozlowski <krzk@kernel.org>,
        linux-crypto@vger.kernel.org, linux-input@vger.kernel.org,
        linux-serial@vger.kernel.org
Subject: [PATCH 02/12] Documentation/arm: repointer docs to
 Documentation/arch/arm
Date: Fri, 12 Jul 2019 10:20:08 +0800
Message-Id: <20190712022018.27989-2-alex.shi@linux.alibaba.com>
X-Mailer: git-send-email 2.19.1.856.g8858448bb
In-Reply-To: <20190712022018.27989-1-alex.shi@linux.alibaba.com>
References: <20190712022018.27989-1-alex.shi@linux.alibaba.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

Since we move 'arm/arm64' docs to Documentation/arch/{arm,arm64} dir,
redirect the doc pointer to them.

Signed-off-by: Alex Shi <alex.shi@linux.alibaba.com>
Cc: Jonathan Corbet <corbet@lwn.net>
Cc: Kukjin Kim <kgene@kernel.org>
Cc: Krzysztof Kozlowski <krzk@kernel.org>
Cc: linux-doc@vger.kernel.org
Cc: linux-kernel@vger.kernel.org
Cc: linux-arm-kernel@lists.infradead.org
Cc: linux-samsung-soc@vger.kernel.org
Cc: linux-crypto@vger.kernel.org
Cc: linux-input@vger.kernel.org
Cc: linux-serial@vger.kernel.org
---
 Documentation/arch/arm/Samsung-S3C24XX/GPIO.txt    |  2 +-
 .../arch/arm/Samsung-S3C24XX/Overview.txt          |  6 +++---
 Documentation/arch/arm/Samsung/GPIO.txt            |  2 +-
 Documentation/arch/arm/Samsung/Overview.txt        |  4 ++--
 Documentation/devicetree/bindings/arm/xen.txt      |  2 +-
 Documentation/devicetree/booting-without-of.txt    |  4 ++--
 Documentation/translations/zh_CN/arm/Booting       |  4 ++--
 .../translations/zh_CN/arm/kernel_user_helpers.txt |  4 ++--
 MAINTAINERS                                        |  6 +++---
 arch/arm/Kconfig                                   |  2 +-
 arch/arm/common/mcpm_entry.c                       |  2 +-
 arch/arm/common/mcpm_head.S                        |  2 +-
 arch/arm/common/vlock.S                            |  2 +-
 arch/arm/include/asm/setup.h                       |  2 +-
 arch/arm/include/uapi/asm/setup.h                  |  2 +-
 arch/arm/kernel/entry-armv.S                       |  2 +-
 arch/arm/mach-exynos/common.h                      |  2 +-
 arch/arm/mach-ixp4xx/Kconfig                       | 14 +++++++-------
 arch/arm/mach-s3c24xx/pm.c                         |  2 +-
 arch/arm/mach-sti/Kconfig                          |  2 +-
 arch/arm/mm/Kconfig                                |  4 ++--
 arch/arm/plat-samsung/Kconfig                      |  6 +++---
 arch/arm/tools/mach-types                          |  2 +-
 arch/arm64/Kconfig                                 |  2 +-
 arch/arm64/kernel/kuser32.S                        |  2 +-
 arch/mips/bmips/setup.c                            |  2 +-
 drivers/crypto/sunxi-ss/sun4i-ss-cipher.c          |  2 +-
 drivers/crypto/sunxi-ss/sun4i-ss-core.c            |  2 +-
 drivers/crypto/sunxi-ss/sun4i-ss-hash.c            |  2 +-
 drivers/crypto/sunxi-ss/sun4i-ss.h                 |  2 +-
 drivers/input/touchscreen/sun4i-ts.c               |  2 +-
 drivers/tty/serial/Kconfig                         |  2 +-
 32 files changed, 49 insertions(+), 49 deletions(-)

```
#### [PATCH 1/2] KVM: LAPIC: Add pv ipi tracepoint
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Add pv ipi tracepoint.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c |  2 ++
 arch/x86/kvm/trace.h | 25 +++++++++++++++++++++++++
 2 files changed, 27 insertions(+)

```
#### [PATCH 1/2] x86: kvm: avoid -Wsometimes-uninitized warning
##### From: Arnd Bergmann <arnd@arndb.de>

```c
clang points out that running a 64-bit guest on a 32-bit host
would lead to uninitialized variables:

arch/x86/kvm/hyperv.c:1610:6: error: variable 'ingpa' is used uninitialized whenever 'if' condition is false [-Werror,-Wsometimes-uninitialized]
        if (!longmode) {
            ^~~~~~~~~
arch/x86/kvm/hyperv.c:1632:55: note: uninitialized use occurs here
        trace_kvm_hv_hypercall(code, fast, rep_cnt, rep_idx, ingpa, outgpa);
                                                             ^~~~~
arch/x86/kvm/hyperv.c:1610:2: note: remove the 'if' if its condition is always true
        if (!longmode) {
        ^~~~~~~~~~~~~~~
arch/x86/kvm/hyperv.c:1595:18: note: initialize the variable 'ingpa' to silence this warning
        u64 param, ingpa, outgpa, ret = HV_STATUS_SUCCESS;
                        ^
                         = 0
arch/x86/kvm/hyperv.c:1610:6: error: variable 'outgpa' is used uninitialized whenever 'if' condition is false [-Werror,-Wsometimes-uninitialized]
arch/x86/kvm/hyperv.c:1610:6: error: variable 'param' is used uninitialized whenever 'if' condition is false [-Werror,-Wsometimes-uninitialized]

Since that combination is not supported anyway, change the condition
to tell the compiler how the code is actually executed.

Signed-off-by: Arnd Bergmann <arnd@arndb.de>
---
 arch/x86/kvm/hyperv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [GIT PULL] First batch of KVM changes for Linux 5.3
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Linus,

The following changes since commit 4b972a01a7da614b4796475f933094751a295a2f:

  Linux 5.2-rc6 (2019-06-22 16:01:36 -0700)

are available in the git repository at:

  https://git.kernel.org/pub/scm/virt/kvm/kvm.git tags/for-linus

for you to fetch changes up to a45ff5994c9cde41af627c46abb9f32beae68943:

  Merge tag 'kvm-arm-for-5.3' of git://git.kernel.org/pub/scm/linux/kernel/git/kvmarm/kvmarm into HEAD (2019-07-11 15:14:16 +0200)

----------------------------------------------------------------

ARM:
* support for chained PMU counters in guests
* improved SError handling
* handle Neoverse N1 erratum #1349291
* allow side-channel mitigation status to be migrated
* standardise most AArch64 system register accesses to msr_s/mrs_s
* fix host MPIDR corruption on 32bit
* selftests ckleanups

x86:
* PMU event {white,black}listing
* ability for the guest to disable host-side interrupt polling
* fixes for enlightened VMCS (Hyper-V pv nested virtualization),
* new hypercall to yield to IPI target
* support for passing cstate MSRs through to the guest
* lots of cleanups and optimizations

Generic:
* Some txt->rST conversions for the documentation

----------------------------------------------------------------

There are two trivial conflicts in ARM64 docs and includes.

Andre Przywara (3):
      arm64: KVM: Propagate full Spectre v2 workaround state to KVM guests
      KVM: arm/arm64: Add save/restore support for firmware workaround state
      KVM: doc: Add API documentation on the KVM_REG_ARM_WORKAROUNDS register

Andrew Jones (3):
      kvm: selftests: ucall improvements
      kvm: selftests: introduce aarch64_vcpu_setup
      kvm: selftests: introduce aarch64_vcpu_add_default

Andrew Murray (5):
      KVM: arm/arm64: Rename kvm_pmu_{enable/disable}_counter functions
      KVM: arm/arm64: Extract duplicated code to own function
      KVM: arm/arm64: Re-create event when setting counter value
      KVM: arm/arm64: Remove pmc->bitmask
      KVM: arm/arm64: Support chained PMU counters

Dave Martin (1):
      KVM: arm64: Migrate _elx sysreg accessors to msr_s/mrs_s

Eric Hankland (1):
      KVM: x86: PMU Event Filter

Eugene Korenevsky (2):
      kvm: vmx: fix limit checking in get_vmx_mem_address()
      kvm: vmx: segment limit check: use access length

Gustavo A. R. Silva (1):
      KVM: irqchip: Use struct_size() in kzalloc()

James Morse (8):
      arm64: assembler: Switch ESB-instruction with a vanilla nop if !ARM64_HAS_RAS
      KVM: arm64: Abstract the size of the HYP vectors pre-amble
      KVM: arm64: Make indirect vectors preamble behaviour symmetric
      KVM: arm64: Consume pending SError as early as possible
      KVM: arm64: Defer guest entry when an asynchronous exception is pending
      arm64: Update silicon-errata.txt for Neoverse-N1 #1349291
      KVM: arm64: Re-mask SError after the one instruction window
      KVM: arm64: Skip more of the SError vaxorcism

Jan Beulich (1):
      x86/kvm/VMX: drop bad asm() clobber from nested_vmx_check_vmentry_hw()

Jim Mattson (2):
      kvm: nVMX: Remove unnecessary sync_roots from handle_invept
      kvm: x86: Pass through AMD_STIBP_ALWAYS_ON in GET_SUPPORTED_CPUID

Junaid Shahid (2):
      kvm: Convert kvm_lock to a mutex
      kvm: x86: Do not release the page inside mmu_set_spte()

Kai Huang (2):
      kvm: x86: Move kvm_set_mmio_spte_mask() from x86.c to mmu.c
      kvm: x86: Fix reserved bits related calculation errors caused by MKTME

KarimAllah Ahmed (1):
      KVM: Properly check if "page" is valid in kvm_vcpu_unmap

Krish Sadhukhan (1):
      KVM nVMX: Check Host Segment Registers and Descriptor Tables on vmentry of nested guests

Like Xu (1):
      KVM: x86: Add Intel CPUID.1F cpuid emulation support

Liran Alon (1):
      KVM: x86: Use DR_TRAP_BITS instead of hard-coded 15

Luke Nowakowski-Krijger (3):
      Documentation: virtual: Convert paravirt_ops.txt to .rst
      Documentation: kvm: Convert cpuid.txt to .rst
      Documentation: virtual: Add toctree hooks

Marc Zyngier (1):
      KVM: arm/arm64: Initialise host's MPIDRs by reading the actual register

Marcelo Tosatti (1):
      kvm: x86: add host poll control msrs

Paolo Bonzini (25):
      kvm: selftests: hide vcpu_setup in processor code
      KVM: x86: clean up conditions for asynchronous page fault handling
      KVM: x86: move MSR_IA32_POWER_CTL handling to common code
      kvm: nVMX: small cleanup in handle_exception
      KVM: nVMX: Rename prepare_vmcs02_*_full to prepare_vmcs02_*_rare
      KVM: VMX: simplify vmx_prepare_switch_to_{guest,host}
      KVM: x86: introduce is_pae_paging
      KVM: nVMX: shadow pin based execution controls
      KVM: nVMX: include conditional controls in /dev/kvm KVM_GET_MSRS
      KVM: nVMX: allow setting the VMFUNC controls MSR
      KVM: nVMX: list VMX MSRs in KVM_GET_MSR_INDEX_LIST
      Documentation: kvm: document CPUID bit for MSR_KVM_POLL_CONTROL
      KVM: svm: add nrips module parameter
      KVM: cpuid: do_cpuid_ent works on a whole CPUID function
      KVM: cpuid: extract do_cpuid_7_mask and support multiple subleafs
      KVM: cpuid: set struct kvm_cpuid_entry2 flags in do_cpuid_1_ent
      KVM: cpuid: rename do_cpuid_1_ent
      KVM: cpuid: remove has_leaf_count from struct kvm_cpuid_param
      KVM: x86: make FNAME(fetch) and __direct_map more similar
      KVM: x86: remove now unneeded hugepage gfn adjustment
      KVM: x86: change kvm_mmu_page_get_gfn BUG_ON to WARN_ON
      KVM: x86: add tracepoints around __direct_map and FNAME(fetch)
      KVM: LAPIC: ARBPRI is a reserved register for x2APIC
      kvm: LAPIC: write down valid APIC registers
      Merge tag 'kvm-arm-for-5.3' of git://git.kernel.org/.../kvmarm/kvmarm into HEAD

Saar Amar (1):
      KVM: x86: Fix apic dangling pointer in vcpu

Sean Christopherson (41):
      KVM: Directly return result from kvm_arch_check_processor_compat()
      KVM: VMX: Fix handling of #MC that occurs during VM-Entry
      KVM: VMX: Read cached VM-Exit reason to detect external interrupt
      KVM: VMX: Store the host kernel's IDT base in a global variable
      KVM: x86: Move kvm_{before,after}_interrupt() calls to vendor code
      KVM: VMX: Handle NMIs, #MCs and async #PFs in common irqs-disabled fn
      KVM: nVMX: Intercept VMWRITEs to read-only shadow VMCS fields
      KVM: nVMX: Intercept VMWRITEs to GUEST_{CS,SS}_AR_BYTES
      KVM: nVMX: Track vmcs12 offsets for shadowed VMCS fields
      KVM: nVMX: Lift sync_vmcs12() out of prepare_vmcs12()
      KVM: nVMX: Use descriptive names for VMCS sync functions and flags
      KVM: nVMX: Add helpers to identify shadowed VMCS fields
      KVM: nVMX: Sync rarely accessed guest fields only when needed
      KVM: VMX: Always signal #GP on WRMSR to MSR_IA32_CR_PAT with bad value
      KVM: nVMX: Always sync GUEST_BNDCFGS when it comes from vmcs01
      KVM: nVMX: Write ENCLS-exiting bitmap once per vmcs02
      KVM: nVMX: Don't rewrite GUEST_PML_INDEX during nested VM-Entry
      KVM: nVMX: Don't "put" vCPU or host state when switching VMCS
      KVM: nVMX: Don't reread VMCS-agnostic state when switching VMCS
      KVM: nVMX: Don't dump VMCS if virtual APIC page can't be mapped
      KVM: nVMX: Don't speculatively write virtual-APIC page address
      KVM: nVMX: Don't speculatively write APIC-access page address
      KVM: nVMX: Update vmcs12 for MSR_IA32_CR_PAT when it's written
      KVM: nVMX: Update vmcs12 for SYSENTER MSRs when they're written
      KVM: nVMX: Update vmcs12 for MSR_IA32_DEBUGCTLMSR when it's written
      KVM: nVMX: Don't update GUEST_BNDCFGS if it's clean in HV eVMCS
      KVM: nVMX: Copy PDPTRs to/from vmcs12 only when necessary
      KVM: nVMX: Use adjusted pin controls for vmcs02
      KVM: VMX: Add builder macros for shadowing controls
      KVM: VMX: Shadow VMCS pin controls
      KVM: VMX: Shadow VMCS primary execution controls
      KVM: VMX: Shadow VMCS secondary execution controls
      KVM: nVMX: Shadow VMCS controls on a per-VMCS basis
      KVM: nVMX: Don't reset VMCS controls shadow on VMCS switch
      KVM: VMX: Explicitly initialize controls shadow at VMCS allocation
      KVM: nVMX: Preserve last USE_MSR_BITMAPS when preparing vmcs02
      KVM: nVMX: Preset *DT exiting in vmcs02 when emulating UMIP
      KVM: VMX: Drop hv_timer_armed from 'struct loaded_vmcs'
      KVM: VMX: Leave preemption timer running when it's disabled
      KVM: nVMX: Stash L1's CR3 in vmcs01.GUEST_CR3 on nested entry w/o EPT
      KVM: x86: Unconditionally enable irqs in guest context

Suthikulpanit, Suravee (1):
      kvm: svm/avic: Do not send AVIC doorbell to self

Uros Bizjak (1):
      KVM: VMX: remove unneeded 'asm volatile ("")' from vmcs_write64

Vitaly Kuznetsov (3):
      KVM/nSVM: properly map nested VMCB
      x86/KVM/nVMX: don't use clean fields data on enlightened VMLAUNCH
      x86/kvm/nVMX: fix VMCLEAR when Enlightened VMCS is in use

Wanpeng Li (12):
      KVM: LAPIC: Extract adaptive tune timer advancement logic
      KVM: LAPIC: Delay trace_kvm_wait_lapic_expire tracepoint to after vmexit
      KVM: LAPIC: Optimize timer latency further
      KVM: Documentation: Add disable pause exits to KVM_CAP_X86_DISABLE_EXITS
      KVM: X86: Provide a capability to disable cstate msr read intercepts
      KVM: X86: Emulate MSR_IA32_MISC_ENABLE MWAIT bit
      KVM: VMX: check CPUID before allowing read/write of IA32_XSS
      KVM: X86: Yield to IPI target if necessary
      KVM: X86: Implement PV sched yield hypercall
      KVM: X86: Expose PV_SCHED_YIELD CPUID feature bit to guest
      KVM: LAPIC: remove the trailing newline used in the fmt parameter of TP_printk
      KVM: LAPIC: Retry tune per-vCPU timer_advance_ns if adaptive tuning goes insane

Wei Yang (3):
      kvm: x86: check kvm_apic_sw_enabled() is enough
      kvm: x86: use same convention to name kvm_lapic_{set,clear}_vector()
      kvm: x86: offset is ensure to be in range

Xiaoyao Li (1):
      kvm: x86: refine kvm_get_arch_capabilities()

Yi Wang (1):
      kvm: x86: Fix -Wmissing-prototypes warnings

 Documentation/arm64/silicon-errata.txt             |   1 +
 Documentation/virtual/index.rst                    |  18 +
 Documentation/virtual/kvm/api.txt                  |  28 +
 Documentation/virtual/kvm/arm/psci.txt             |  31 +
 Documentation/virtual/kvm/cpuid.rst                | 107 +++
 Documentation/virtual/kvm/cpuid.txt                |  83 ---
 Documentation/virtual/kvm/hypercalls.txt           |  11 +
 Documentation/virtual/kvm/index.rst                |  11 +
 Documentation/virtual/kvm/locking.txt              |   4 +-
 Documentation/virtual/kvm/msr.txt                  |   9 +
 .../virtual/{paravirt_ops.txt => paravirt_ops.rst} |  19 +-
 arch/arm/include/asm/kvm_emulate.h                 |  10 +
 arch/arm/include/asm/kvm_host.h                    |  18 +-
 arch/arm/include/asm/kvm_hyp.h                     |  13 +-
 arch/arm/include/uapi/asm/kvm.h                    |  12 +
 arch/arm64/include/asm/assembler.h                 |   4 +
 arch/arm64/include/asm/cpufeature.h                |   6 +
 arch/arm64/include/asm/kvm_asm.h                   |   6 +
 arch/arm64/include/asm/kvm_emulate.h               |  30 +-
 arch/arm64/include/asm/kvm_host.h                  |  23 +-
 arch/arm64/include/asm/kvm_hyp.h                   |  50 +-
 arch/arm64/include/asm/sysreg.h                    |  35 +-
 arch/arm64/include/uapi/asm/kvm.h                  |  10 +
 arch/arm64/kernel/cpu_errata.c                     |  23 +-
 arch/arm64/kernel/traps.c                          |   4 +
 arch/arm64/kvm/hyp/entry.S                         |  36 +-
 arch/arm64/kvm/hyp/hyp-entry.S                     |  30 +-
 arch/arm64/kvm/hyp/switch.c                        |  14 +-
 arch/arm64/kvm/hyp/sysreg-sr.c                     |  78 +--
 arch/arm64/kvm/hyp/tlb.c                           |  12 +-
 arch/arm64/kvm/hyp/vgic-v2-cpuif-proxy.c           |   2 +-
 arch/arm64/kvm/regmap.c                            |   4 +-
 arch/arm64/kvm/sys_regs.c                          |  60 +-
 arch/arm64/kvm/va_layout.c                         |   7 +-
 arch/mips/kvm/mips.c                               |   4 +-
 arch/powerpc/kvm/powerpc.c                         |   4 +-
 arch/s390/include/asm/kvm_host.h                   |   1 -
 arch/s390/kvm/kvm-s390.c                           |   9 +-
 arch/x86/include/asm/kvm_host.h                    |  11 +-
 arch/x86/include/uapi/asm/kvm.h                    |  19 +-
 arch/x86/include/uapi/asm/kvm_para.h               |   3 +
 arch/x86/include/uapi/asm/vmx.h                    |   1 -
 arch/x86/kernel/kvm.c                              |  21 +
 arch/x86/kvm/Kconfig                               |   1 +
 arch/x86/kvm/cpuid.c                               | 247 ++++---
 arch/x86/kvm/emulate.c                             |   2 +-
 arch/x86/kvm/irq.h                                 |   1 -
 arch/x86/kvm/irq_comm.c                            |   2 +-
 arch/x86/kvm/lapic.c                               | 123 ++--
 arch/x86/kvm/lapic.h                               |   8 +-
 arch/x86/kvm/mmu.c                                 | 182 +++--
 arch/x86/kvm/mmutrace.h                            |  59 ++
 arch/x86/kvm/paging_tmpl.h                         |  42 +-
 arch/x86/kvm/pmu.c                                 |  63 ++
 arch/x86/kvm/pmu.h                                 |   1 +
 arch/x86/kvm/svm.c                                 |  51 +-
 arch/x86/kvm/trace.h                               |   2 +-
 arch/x86/kvm/vmx/evmcs.c                           |  18 +
 arch/x86/kvm/vmx/evmcs.h                           |   1 +
 arch/x86/kvm/vmx/nested.c                          | 763 +++++++++++++--------
 arch/x86/kvm/vmx/nested.h                          |   4 +-
 arch/x86/kvm/vmx/ops.h                             |   1 -
 arch/x86/kvm/vmx/vmcs.h                            |  17 +-
 arch/x86/kvm/vmx/vmcs12.h                          |  57 +-
 arch/x86/kvm/vmx/vmcs_shadow_fields.h              |  79 ++-
 arch/x86/kvm/vmx/vmx.c                             | 449 ++++++------
 arch/x86/kvm/vmx/vmx.h                             | 124 ++--
 arch/x86/kvm/x86.c                                 | 229 +++++--
 arch/x86/kvm/x86.h                                 |  10 +
 include/kvm/arm_pmu.h                              |  11 +-
 include/linux/kvm_host.h                           |   5 +-
 include/uapi/linux/kvm.h                           |   7 +-
 include/uapi/linux/kvm_para.h                      |   1 +
 tools/include/uapi/linux/kvm.h                     |   4 +-
 tools/testing/selftests/kvm/dirty_log_test.c       |   3 +-
 .../selftests/kvm/include/aarch64/processor.h      |   4 +
 tools/testing/selftests/kvm/include/kvm_util.h     |   3 +-
 .../testing/selftests/kvm/lib/aarch64/processor.c  |  50 +-
 tools/testing/selftests/kvm/lib/kvm_util.c         |   9 +-
 .../testing/selftests/kvm/lib/kvm_util_internal.h  |   2 -
 tools/testing/selftests/kvm/lib/ucall.c            |  19 +-
 tools/testing/selftests/kvm/lib/x86_64/processor.c |   5 +-
 tools/testing/selftests/kvm/x86_64/evmcs_test.c    |   2 +-
 .../selftests/kvm/x86_64/kvm_create_max_vcpus.c    |   2 +-
 tools/testing/selftests/kvm/x86_64/smm_test.c      |   2 +-
 tools/testing/selftests/kvm/x86_64/state_test.c    |   2 +-
 virt/kvm/arm/arch_timer.c                          |  24 +-
 virt/kvm/arm/arm.c                                 |   7 +-
 virt/kvm/arm/pmu.c                                 | 350 ++++++++--
 virt/kvm/arm/psci.c                                | 149 +++-
 virt/kvm/irqchip.c                                 |   4 +-
 virt/kvm/kvm_main.c                                |  41 +-
 92 files changed, 2692 insertions(+), 1432 deletions(-)
 create mode 100644 Documentation/virtual/index.rst
 create mode 100644 Documentation/virtual/kvm/cpuid.rst
 delete mode 100644 Documentation/virtual/kvm/cpuid.txt
 create mode 100644 Documentation/virtual/kvm/index.rst
 rename Documentation/virtual/{paravirt_ops.txt => paravirt_ops.rst} (65%)
```
#### [PATCH] KVM: Boosting vCPUs that are delivering interrupts
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Inspired by commit 9cac38dd5d (KVM/s390: Set preempted flag during vcpu wakeup 
and interrupt delivery), except the lock holder, we want to also boost vCPUs 
that are delivering interrupts. Actually most smp_call_function_many calls are 
synchronous ipi calls, the ipi target vCPUs are also good yield candidates. 
This patch sets preempted flag during wakeup and interrupt delivery time.

Testing on 80 HT 2 socket Xeon Skylake server, with 80 vCPUs VM 80GB RAM:
ebizzy -M

            vanilla     boosting    improved
1VM          23000       21232        -9%                      
2VM           2800        8000       180%
3VM           1800        3100        72%

Testing on my Haswell desktop 8 HT, with 8 vCPUs VM 8GB RAM, two VMs, 
one running ebizzy -M, the other running 'stress --cpu 2':

w/ boosting + w/o pv sched yield(vanilla)   

            vanilla     boosting   improved 
   			 1570         4000       55%

w/ boosting + w/ pv sched yield(vanilla)

			vanilla     boosting   improved 
             1844         5157       79%   

w/o boosting, perf top in VM:

 72.33%  [kernel]       [k] smp_call_function_many
  4.22%  [kernel]       [k] call_function_i
  3.71%  [kernel]       [k] async_page_fault

w/ boosting, perf top in VM:

 38.43%  [kernel]       [k] smp_call_function_many
  6.31%  [kernel]       [k] async_page_fault
  6.13%  libc-2.23.so   [.] __memcpy_avx_unaligned
  4.88%  [kernel]       [k] call_function_interrupt

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 virt/kvm/kvm_main.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests v2] arm: Add PL031 test
##### From: Alexander Graf <graf@amazon.com>

```c
This patch adds a unit test for the PL031 RTC that is used in the virt machine.
It just pokes basic functionality. I've mostly written it to familiarize myself
with the device, but I suppose having the test around does not hurt, as it also
exercises the GIC SPI interrupt path.

Signed-off-by: Alexander Graf <graf@amazon.com>
---

v1 -> v2:

  - Use FDT to find base, irq and existence
  - Put isb after timer read
  - Use dist_base for gicv3
---
 arm/Makefile.common |   1 +
 arm/pl031.c         | 265 ++++++++++++++++++++++++++++++++++++++++++++
 lib/arm/asm/gic.h   |   1 +
 3 files changed, 267 insertions(+)
 create mode 100644 arm/pl031.c

```
#### [PATCH v7 1/3] KVM: x86: add support for user wait instructions
##### From: Tao Xu <tao3.xu@intel.com>

```c
UMONITOR, UMWAIT and TPAUSE are a set of user wait instructions.
This patch adds support for user wait instructions in KVM. Availability
of the user wait instructions is indicated by the presence of the CPUID
feature flag WAITPKG CPUID.0x07.0x0:ECX[5]. User wait instructions may
be executed at any privilege level, and use IA32_UMWAIT_CONTROL MSR to
set the maximum time.

The behavior of user wait instructions in VMX non-root operation is
determined first by the setting of the "enable user wait and pause"
secondary processor-based VM-execution control bit 26.
	If the VM-execution control is 0, UMONITOR/UMWAIT/TPAUSE cause
an invalid-opcode exception (#UD).
	If the VM-execution control is 1, treatment is based on the
setting of the “RDTSC exiting” VM-execution control. Because KVM never
enables RDTSC exiting, if the instruction causes a delay, the amount of
time delayed is called here the physical delay. The physical delay is
first computed by determining the virtual delay. If
IA32_UMWAIT_CONTROL[31:2] is zero, the virtual delay is the value in
EDX:EAX minus the value that RDTSC would return; if
IA32_UMWAIT_CONTROL[31:2] is not zero, the virtual delay is the minimum
of that difference and AND(IA32_UMWAIT_CONTROL,FFFFFFFCH).

Because umwait and tpause can put a (psysical) CPU into a power saving
state, by default we dont't expose it to kvm and enable it only when
guest CPUID has it.

Detailed information about user wait instructions can be found in the
latest Intel 64 and IA-32 Architectures Software Developer's Manual.

Co-developed-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Jingqi Liu <jingqi.liu@intel.com>
Signed-off-by: Tao Xu <tao3.xu@intel.com>
---

Changes in v7:
    - Add nested support for user wait instructions (Paolo)
---
 arch/x86/include/asm/vmx.h |  1 +
 arch/x86/kvm/cpuid.c       |  2 +-
 arch/x86/kvm/vmx/nested.c  |  1 +
 arch/x86/kvm/vmx/vmx.c     | 20 ++++++++++++++++++++
 4 files changed, 23 insertions(+), 1 deletion(-)

```
#### [PULL 01/19] migration: fix multifd_recv event typo
##### From: Juan Quintela <quintela@redhat.com>

```c
It uses num in multifd_send().  Make it coherent.

Signed-off-by: Juan Quintela <quintela@redhat.com>
Reviewed-by: Dr. David Alan Gilbert <dgilbert@redhat.com>
Reviewed-by: Wei Yang <richardw.yang@linux.intel.com>
Signed-off-by: Juan Quintela <quintela@redhat.com>
---
 migration/trace-events | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH RESEND 1/2] KVM: LAPIC: Add pv ipi tracepoint
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Add pv ipi tracepoint.

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/lapic.c |  2 ++
 arch/x86/kvm/trace.h | 25 +++++++++++++++++++++++++
 2 files changed, 27 insertions(+)

```
#### [PATCH RESEND] KVM: Boosting vCPUs that are delivering interrupts
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
From: Wanpeng Li <wanpengli@tencent.com>

Inspired by commit 9cac38dd5d (KVM/s390: Set preempted flag during vcpu wakeup 
and interrupt delivery), except the lock holder, we want to also boost vCPUs 
that are delivering interrupts. Actually most smp_call_function_many calls are 
synchronous ipi calls, the ipi target vCPUs are also good yield candidates. 
This patch sets preempted flag during wakeup and interrupt delivery time.

Testing on 80 HT 2 socket Xeon Skylake server, with 80 vCPUs VM 80GB RAM:
ebizzy -M

            vanilla     boosting    improved
1VM          23000       21232        -9%                      
2VM           2800        8000       180%
3VM           1800        3100        72%

Testing on my Haswell desktop 8 HT, with 8 vCPUs VM 8GB RAM, two VMs, 
one running ebizzy -M, the other running 'stress --cpu 2':

w/ boosting + w/o pv sched yield(vanilla)   

            vanilla     boosting   improved 
              1570         4000       55%

w/ boosting + w/ pv sched yield(vanilla)

            vanilla     boosting   improved 
              1844         5157       79%   

w/o boosting, perf top in VM:

 72.33%  [kernel]       [k] smp_call_function_many
  4.22%  [kernel]       [k] call_function_i
  3.71%  [kernel]       [k] async_page_fault

w/ boosting, perf top in VM:

 38.43%  [kernel]       [k] smp_call_function_many
  6.31%  [kernel]       [k] async_page_fault
  6.13%  libc-2.23.so   [.] __memcpy_avx_unaligned
  4.88%  [kernel]       [k] call_function_interrupt

Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Radim Krčmář <rkrcmar@redhat.com>
Cc: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 virt/kvm/kvm_main.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 1/3] tscdeadline_latency: Check condition first before loop
##### From: Peter Xu <zhexu@redhat.com>

```c
This patch fixes a tscdeadline_latency hang when specifying a very
small breakmax value.  It's easily reproduced on my host when set
breakmax to e.g. 10 TSC clocks.

The problem is test_tsc_deadline_timer() can be very slow because
we've got printf() in there.  So when reach the main loop we might
have already triggered the IRQ handler for multiple times and we might
have triggered the hitmax condition which will turn IRQ off.  Then
with no IRQ that first HLT instruction can last forever.

Fix this by don't enable irq and use safe_halt() as suggested by Sean
Christopherson.

Signed-off-by: Peter Xu <peterx@redhat.com>
---
 x86/tscdeadline_latency.c | 5 +----
 1 file changed, 1 insertion(+), 4 deletions(-)

```
#### [PATCH] [v2] x86: kvm: avoid -Wsometimes-uninitized warning
##### From: Arnd Bergmann <arnd@arndb.de>

```c
clang points out that running a 64-bit guest on a 32-bit host
would lead to uninitialized variables:

arch/x86/kvm/hyperv.c:1610:6: error: variable 'ingpa' is used uninitialized whenever 'if' condition is false [-Werror,-Wsometimes-uninitialized]
        if (!longmode) {
            ^~~~~~~~~
arch/x86/kvm/hyperv.c:1632:55: note: uninitialized use occurs here
        trace_kvm_hv_hypercall(code, fast, rep_cnt, rep_idx, ingpa, outgpa);
                                                             ^~~~~
arch/x86/kvm/hyperv.c:1610:2: note: remove the 'if' if its condition is always true
        if (!longmode) {
        ^~~~~~~~~~~~~~~
arch/x86/kvm/hyperv.c:1595:18: note: initialize the variable 'ingpa' to silence this warning
        u64 param, ingpa, outgpa, ret = HV_STATUS_SUCCESS;
                        ^
                         = 0
arch/x86/kvm/hyperv.c:1610:6: error: variable 'outgpa' is used uninitialized whenever 'if' condition is false [-Werror,-Wsometimes-uninitialized]
arch/x86/kvm/hyperv.c:1610:6: error: variable 'param' is used uninitialized whenever 'if' condition is false [-Werror,-Wsometimes-uninitialized]

Since that combination is not supported anyway, change the condition
to tell the compiler how the code is actually executed.

Signed-off-by: Arnd Bergmann <arnd@arndb.de>
Reviewed-by: Roman Kagan <rkagan@virtuozzo.com>
---
v2: make the change inside of is_64_bit_mode().
---
 arch/x86/kvm/hyperv.c | 6 ++----
 arch/x86/kvm/x86.h    | 4 ++++
 2 files changed, 6 insertions(+), 4 deletions(-)

```
#### [PATCH] [v3] x86: kvm: avoid -Wsometimes-uninitized warning
##### From: Arnd Bergmann <arnd@arndb.de>

```c
Clang notices a code path in which some variables are never
initialized, but fails to figure out that this can never happen
on i386 because is_64_bit_mode() always returns false.

arch/x86/kvm/hyperv.c:1610:6: error: variable 'ingpa' is used uninitialized whenever 'if' condition is false [-Werror,-Wsometimes-uninitialized]
        if (!longmode) {
            ^~~~~~~~~
arch/x86/kvm/hyperv.c:1632:55: note: uninitialized use occurs here
        trace_kvm_hv_hypercall(code, fast, rep_cnt, rep_idx, ingpa, outgpa);
                                                             ^~~~~
arch/x86/kvm/hyperv.c:1610:2: note: remove the 'if' if its condition is always true
        if (!longmode) {
        ^~~~~~~~~~~~~~~
arch/x86/kvm/hyperv.c:1595:18: note: initialize the variable 'ingpa' to silence this warning
        u64 param, ingpa, outgpa, ret = HV_STATUS_SUCCESS;
                        ^
                         = 0
arch/x86/kvm/hyperv.c:1610:6: error: variable 'outgpa' is used uninitialized whenever 'if' condition is false [-Werror,-Wsometimes-uninitialized]
arch/x86/kvm/hyperv.c:1610:6: error: variable 'param' is used uninitialized whenever 'if' condition is false [-Werror,-Wsometimes-uninitialized]

Flip the condition around to avoid the conditional execution on i386.

Signed-off-by: Arnd Bergmann <arnd@arndb.de>
Reviewed-by: Roman Kagan <rkagan@virtuozzo.com>
Reviewed-by: Nathan Chancellor <natechancellor@gmail.com>
---
v3: reword commit log, simplify patch again
v2: make the change inside of is_64_bit_mode().
---
 arch/x86/kvm/hyperv.c | 20 +++++++++-----------
 1 file changed, 9 insertions(+), 11 deletions(-)

```
