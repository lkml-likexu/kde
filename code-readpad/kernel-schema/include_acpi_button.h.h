
\n
extern int acpi_lid_notifier_register(struct notifier_block *nb)
; extern int acpi_lid_notifier_unregister(struct notifier_block *nb)
; extern int acpi_lid_open(void)
; static inline int acpi_lid_notifier_register(struct notifier_block *nb)
extern int acpi_lid_notifier_register(struct notifier_block *nb)
; extern int acpi_lid_notifier_unregister(struct notifier_block *nb)
; extern int acpi_lid_open(void)
; static inline int acpi_lid_notifier_register(struct notifier_block *nb)
return 0; } static inline int acpi_lid_notifier_unregister(struct notifier_block *nb)
extern int acpi_lid_notifier_register(struct notifier_block *nb)
; extern int acpi_lid_notifier_unregister(struct notifier_block *nb)
; extern int acpi_lid_open(void)
; static inline int acpi_lid_notifier_register(struct notifier_block *nb)
return 0; } static inline int acpi_lid_notifier_unregister(struct notifier_block *nb)
return 0; } static inline int acpi_lid_open(void)
\n
     11 struct notifier_block *nb
      4 void
