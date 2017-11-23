
EXPORT_SYMBOL_GPL(edid_info);
struct edd edd; EXPORT_SYMBOL(edd)
;endifstatic inline void __init copy_edd(void)
struct edd edd; EXPORT_SYMBOL(edd)
;endifstatic inline void __init copy_edd(void)
memcpy(edd.mbr_signature, boot_params.edd_mbr_sig_buffer, sizeof(edd.mbr_signature)
)
;memcpy(edd.edd_info, boot_params.eddbuf, sizeof(edd.edd_info)
)
;edd.mbr_signature_nr = boot_params.edd_mbr_sig_buf_entries;edd.edd_info_nr = boot_params.eddbuf_entries; } static inline void __init copy_edd(void)
void * __init extend_brk(size_t size, size_t align)
static void __init cleanup_highmap(void)
static void __init reserve_brk(void)
static u64 __init get_ramdisk_image(void)
return ramdisk_image; } static u64 __init get_ramdisk_size(void)
static void __init relocate_initrd(void)
static void __init early_reserve_initrd(void)
memblock_reserve(ramdisk_image, ramdisk_end - ramdisk_image)
; } static void __init reserve_initrd(void)
static void __init early_reserve_initrd(void)
static void __init early_reserve_initrd(void)
} static void __init reserve_initrd(void)
static void __init parse_setup_data(void)
static void __init memblock_x86_reserve_range_setup_data(void)
static int __init reserve_crashkernel_low(void)
static void __init reserve_crashkernel(void)
crashk_res.start = crash_base;crashk_res.end = crash_base + crash_size - 1;insert_resource(&iomem_resource, &crashk_res)
; } static void __init reserve_crashkernel(void)
void __init reserve_standard_io_resources(void)
static __init void reserve_ibft_region(void)
static bool __init snb_gfx_workaround_needed(void)
static void __init trim_snb_memory(void)
static void __init trim_platform_memory_ranges(void)
static void __init trim_bios_range(void)
static void __init e820_add_kernel_range(void)
static int __init parse_reservelow(char *p)
static void __init trim_low_memory_range(void)
static void __init trim_low_memory_range(void)
memblock_reserve(0, ALIGN(reserve_low, PAGE_SIZE)
)
; }static int dump_kernel_offset(struct notifier_block *self, unsigned long v, void *p)
void __init setup_arch(char **cmdline_p)
void __init x86_verify_bootdata_version(void)
void __init i386_reserve_resources(void)
static int __init register_kernel_offset_dumper(void)
  30 void
   2 edd
   1 void *p
   1 unsigned long v
   1 struct notifier_block *self
   1 sizeofedd.mbr_signature
   1 sizeofedd.edd_info
   1 size_t size
   1 size_t align
   1 ramdisk_image
   1 ramdisk_end - ramdisk_image
   1 edid_info
   1 edd.mbr_signature
   1 edd.edd_info
   1 char *p
   1 char **cmdline_p
   1 boot_params.eddbuf
   1 boot_params.edd_mbr_sig_buffer
   1 PAGE_SIZE
   1 ALIGNreserve_low
   1 0
   1 &iomem_resource
   1 &crashk_res
