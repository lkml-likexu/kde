
\n
static inline void *acpi_os_allocate(acpi_size size)
static inline void *acpi_os_allocate_zeroed(acpi_size size)
static inline void acpi_os_free(void *memory)
static inline void *acpi_os_acquire_object(acpi_cache_t * cache)
static inline acpi_thread_id acpi_os_get_thread_id(void)
static inline acpi_cpu_flags acpi_os_acquire_raw_lock(acpi_raw_spinlock lockp)
static inline void acpi_os_release_raw_lock(acpi_raw_spinlock lockp, acpi_cpu_flags flags)
static inline void acpi_os_delete_raw_lock(acpi_raw_spinlock handle)
static inline u8 acpi_os_readable(void *pointer, acpi_size length)
static inline acpi_status acpi_os_initialize_debugger(void)
static inline void acpi_os_terminate_debugger(void)
\n
      3 void
      2 acpi_size size
      2 acpi_raw_spinlock lockp
      1 void *pointer
      1 void *memory
      1 acpi_size length
      1 acpi_raw_spinlock handle
      1 acpi_cpu_flags flags
      1 acpi_cache_t * cache
