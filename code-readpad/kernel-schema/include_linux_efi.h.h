
\n
static inline int efi_guidcmp (efi_guid_t left, efi_guid_t right)
static inline char * efi_guid_to_str(efi_guid_t *guid, char *out)
static inline efi_status_t efi_query_variable_store(u32 attributes, unsigned long size, bool nonblocking)
static inline int efi_range_is_wc(unsigned long start, unsigned long len)
static inline bool efi_enabled(int feature)
extern bool efi_is_table_address(unsigned long phys_addr)
; static inline bool efi_enabled(int feature)
static inline bool efi_capsule_pending(int *reset_type)
static inline bool efi_is_table_address(unsigned long phys_addr)
static inline void memrange_efi_to_native(u64 *addr, u64 *npages)
static inline void efivar_unregister(struct efivar_entry *var)
int efi_runtime_map_init(struct kobject *)
; int efi_get_runtime_map_size(void)
; int efi_get_runtime_map_desc_size(void)
; int efi_runtime_map_copy(void *buf, size_t bufsz)
; static inline int efi_runtime_map_init(struct kobject *kobj)
static inline int efi_get_runtime_map_size(void)
static inline int efi_get_runtime_map_desc_size(void)
static inline int efi_runtime_map_copy(void *buf, size_t bufsz)
\n
      4 void
      2 void *buf
      2 unsigned long phys_addr
      2 size_t bufsz
      2 int feature
      1 unsigned long start
      1 unsigned long size
      1 unsigned long len
      1 u64 *npages
      1 u64 *addr
      1 u32 attributes
      1 struct kobject *kobj
      1 struct kobject *
      1 struct efivar_entry *var
      1 int *reset_type
      1 efi_guid_t right
      1 efi_guid_t left
      1 efi_guid_t *guid
      1 char *out
      1 bool nonblocking
