
\n
static inline bool efi_is_native(void)
static inline bool efi_runtime_supported(void)
extern void efi_thunk_runtime_setup(void)
; extern efi_status_t efi_thunk_set_virtual_address_map(void *phys_set_virtual_address_map, unsigned long memory_map_size, unsigned long descriptor_size, u32 descriptor_version, efi_memory_desc_t *virtual_map)
; static inline efi_status_t efi_thunk_set_virtual_address_map(void *phys_set_virtual_address_map, unsigned long memory_map_size, unsigned long descriptor_size, u32 descriptor_version, efi_memory_desc_t *virtual_map)
static inline bool efi_is_64bit(void)
static inline bool efi_reboot_required(void)
\n
      5 void
      2 void *phys_set_virtual_address_map
      2 unsigned long memory_map_size
      2 unsigned long descriptor_size
      2 u32 descriptor_version
      2 efi_memory_desc_t *virtual_map
