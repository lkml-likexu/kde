
\n
static inline union acpi_object * acpi_evaluate_dsm_typed(acpi_handle handle, const guid_t *guid, u64 rev, u64 func, union acpi_object *argv4, acpi_object_type type)
static inline struct acpi_hotplug_profile *to_acpi_hotplug_profile( struct kobject *kobj)
static inline bool is_acpi_node(const struct fwnode_handle *fwnode)
static inline bool is_acpi_static_node(const struct fwnode_handle *fwnode)
static inline bool acpi_data_node_match(const struct fwnode_handle *fwnode, const char *name)
static inline struct fwnode_handle *acpi_fwnode_handle(struct acpi_device *adev)
static inline void *acpi_driver_data(struct acpi_device *d)
static inline void acpi_set_device_status(struct acpi_device *adev, u32 sta)
static inline void acpi_set_hp_context(struct acpi_device *adev, struct acpi_hotplug_context *hp)
static inline bool acpi_device_enumerated(struct acpi_device *adev)
bool acpi_device_always_present(struct acpi_device *adev)
; static inline bool acpi_device_always_present(struct acpi_device *adev)
void acpi_pm_wakeup_event(struct device *dev)
; acpi_status acpi_add_pm_notifier(struct acpi_device *adev, struct device *dev, void (*func)
(struct acpi_device_wakeup_context *context)
)
; acpi_status acpi_remove_pm_notifier(struct acpi_device *adev)
; bool acpi_pm_device_can_wakeup(struct device *dev)
; int acpi_pm_device_sleep_state(struct device *, int *, int)
; int acpi_pm_set_device_wakeup(struct device *dev, bool enable)
; int acpi_pm_set_bridge_wakeup(struct device *dev, bool enable)
; static inline void acpi_pm_wakeup_event(struct device *dev)
void acpi_pm_wakeup_event(struct device *dev)
; acpi_status acpi_add_pm_notifier(struct acpi_device *adev, struct device *dev, void (*func)
(struct acpi_device_wakeup_context *context)
)
; acpi_status acpi_remove_pm_notifier(struct acpi_device *adev)
; bool acpi_pm_device_can_wakeup(struct device *dev)
; int acpi_pm_device_sleep_state(struct device *, int *, int)
; int acpi_pm_set_device_wakeup(struct device *dev, bool enable)
; int acpi_pm_set_bridge_wakeup(struct device *dev, bool enable)
; static inline void acpi_pm_wakeup_event(struct device *dev)
} static inline acpi_status acpi_add_pm_notifier(struct acpi_device *adev, struct device *dev, void (*func)
(struct acpi_device_wakeup_context *context)
)
void acpi_pm_wakeup_event(struct device *dev)
; acpi_status acpi_add_pm_notifier(struct acpi_device *adev, struct device *dev, void (*func)
(struct acpi_device_wakeup_context *context)
)
; acpi_status acpi_remove_pm_notifier(struct acpi_device *adev)
; bool acpi_pm_device_can_wakeup(struct device *dev)
; int acpi_pm_device_sleep_state(struct device *, int *, int)
; int acpi_pm_set_device_wakeup(struct device *dev, bool enable)
; int acpi_pm_set_bridge_wakeup(struct device *dev, bool enable)
; static inline void acpi_pm_wakeup_event(struct device *dev)
} static inline acpi_status acpi_add_pm_notifier(struct acpi_device *adev, struct device *dev, void (*func)
(struct acpi_device_wakeup_context *context)
)
return AE_SUPPORT; } static inline acpi_status acpi_remove_pm_notifier(struct acpi_device *adev)
void acpi_pm_wakeup_event(struct device *dev)
; acpi_status acpi_add_pm_notifier(struct acpi_device *adev, struct device *dev, void (*func)
(struct acpi_device_wakeup_context *context)
)
; acpi_status acpi_remove_pm_notifier(struct acpi_device *adev)
; bool acpi_pm_device_can_wakeup(struct device *dev)
; int acpi_pm_device_sleep_state(struct device *, int *, int)
; int acpi_pm_set_device_wakeup(struct device *dev, bool enable)
; int acpi_pm_set_bridge_wakeup(struct device *dev, bool enable)
; static inline void acpi_pm_wakeup_event(struct device *dev)
} static inline acpi_status acpi_add_pm_notifier(struct acpi_device *adev, struct device *dev, void (*func)
(struct acpi_device_wakeup_context *context)
)
return AE_SUPPORT; } static inline acpi_status acpi_remove_pm_notifier(struct acpi_device *adev)
return AE_SUPPORT; } static inline bool acpi_pm_device_can_wakeup(struct device *dev)
void acpi_pm_wakeup_event(struct device *dev)
; acpi_status acpi_add_pm_notifier(struct acpi_device *adev, struct device *dev, void (*func)
(struct acpi_device_wakeup_context *context)
)
; acpi_status acpi_remove_pm_notifier(struct acpi_device *adev)
; bool acpi_pm_device_can_wakeup(struct device *dev)
; int acpi_pm_device_sleep_state(struct device *, int *, int)
; int acpi_pm_set_device_wakeup(struct device *dev, bool enable)
; int acpi_pm_set_bridge_wakeup(struct device *dev, bool enable)
; static inline void acpi_pm_wakeup_event(struct device *dev)
} static inline acpi_status acpi_add_pm_notifier(struct acpi_device *adev, struct device *dev, void (*func)
(struct acpi_device_wakeup_context *context)
)
return AE_SUPPORT; } static inline acpi_status acpi_remove_pm_notifier(struct acpi_device *adev)
return AE_SUPPORT; } static inline bool acpi_pm_device_can_wakeup(struct device *dev)
return false; } static inline int acpi_pm_device_sleep_state(struct device *d, int *p, int m)
return (m >= ACPI_STATE_D0 && m <= ACPI_STATE_D3_COLD)
? m : ACPI_STATE_D0; } static inline int acpi_pm_set_device_wakeup(struct device *dev, bool enable)
return (m >= ACPI_STATE_D0 && m <= ACPI_STATE_D3_COLD)
? m : ACPI_STATE_D0; } static inline int acpi_pm_set_device_wakeup(struct device *dev, bool enable)
return -ENODEV; } static inline int acpi_pm_set_bridge_wakeup(struct device *dev, bool enable)
static inline bool acpi_device_power_manageable(struct acpi_device *adev)
static inline bool acpi_device_can_wakeup(struct acpi_device *adev)
static inline bool acpi_device_can_poweroff(struct acpi_device *adev)
\n
     39 struct device *dev
     26 struct acpi_device *adev
     13 bool enable
      9 void *func
      9 struct acpi_device_wakeup_context *context
      5 struct device *
      5 int *
      5 int
      3 const struct fwnode_handle *fwnode
      2 m >= ACPI_STATE_D0 && m <= ACPI_STATE_D3_COLD
      1 union acpi_object *argv4
      1 u64 rev
      1 u64 func
      1 u32 sta
      1 struct kobject *kobj
      1 struct device *d
      1 struct acpi_hotplug_context *hp
      1 struct acpi_device *d
      1 int *p
      1 int m
      1 const guid_t *guid
      1 const char *name
      1 acpi_object_type type
      1 acpi_handle handle
