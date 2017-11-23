
EXPORT_SYMBOL_GPL(of_modalias_node);
EXPORT_SYMBOL_GPL(of_phandle_iterator_init);
EXPORT_SYMBOL_GPL(of_phandle_iterator_next);
EXPORT_SYMBOL_GPL(of_alias_get_id);
EXPORT_SYMBOL_GPL(of_alias_get_highest_id);
EXPORT_SYMBOL_GPL(of_console_check);
EXPORT_SYMBOL_GPL(of_map_rid);
bool of_node_name_eq(const struct device_node *np, const char *name)
bool of_node_name_prefix(const struct device_node *np, const char *prefix)
int of_n_addr_cells(struct device_node *np)
int of_n_size_cells(struct device_node *np)
int __weak of_node_to_nid(struct device_node *np)
void of_populate_phandle_cache(void)
int of_free_phandle_cache(void)
void __init of_core_init(void)
static struct property *__of_find_property(const struct device_node *np, const char *name, int *lenp)
struct property *of_find_property(const struct device_node *np, const char *name, int *lenp)
struct device_node *__of_find_all_nodes(struct device_node *prev)
struct device_node *of_find_all_nodes(struct device_node *prev)
const void *__of_get_property(const struct device_node *np, const char *name, int *lenp)
const void *of_get_property(const struct device_node *np, const char *name, int *lenp)
bool __weak arch_match_cpu_phys_id(int cpu, u64 phys_id)
static bool __of_find_n_match_cpu_property(struct device_node *cpun, const char *prop_name, int cpu, unsigned int *thread)
bool __weak arch_find_n_match_cpu_physical_id(struct device_node *cpun, int cpu, unsigned int *thread)
struct device_node *of_get_cpu_node(int cpu, unsigned int *thread)
int of_cpu_node_to_id(struct device_node *cpu_node)
static int __of_device_is_compatible(const struct device_node *device, const char *compat, const char *type, const char *name)
int of_device_is_compatible(const struct device_node *device, const char *compat)
int of_device_compatible_match(struct device_node *device, const char *const *compat)
int of_machine_is_compatible(const char *compat)
static bool __of_device_is_available(const struct device_node *device)
bool of_device_is_available(const struct device_node *device)
bool of_device_is_big_endian(const struct device_node *device)
struct device_node *of_get_parent(const struct device_node *node)
struct device_node *of_get_next_parent(struct device_node *node)
static struct device_node *__of_get_next_child(const struct device_node *node, struct device_node *prev)
struct device_node *of_get_next_child(const struct device_node *node, struct device_node *prev)
struct device_node *of_get_next_available_child(const struct device_node *node, struct device_node *prev)
struct device_node *of_get_next_cpu_node(struct device_node *prev)
struct device_node *of_get_compatible_child(const struct device_node *parent, const char *compatible)
struct device_node *of_get_child_by_name(const struct device_node *node, const char *name)
struct device_node *__of_find_node_by_path(struct device_node *parent, const char *path)
struct device_node *__of_find_node_by_full_path(struct device_node *node, const char *path)
struct device_node *of_find_node_opts_by_path(const char *path, const char **opts)
struct device_node *of_find_node_by_name(struct device_node *from, const char *name)
struct device_node *of_find_node_by_type(struct device_node *from, const char *type)
struct device_node *of_find_compatible_node(struct device_node *from, const char *type, const char *compatible)
struct device_node *of_find_node_with_property(struct device_node *from, const char *prop_name)
static const struct of_device_id *__of_match_node(const struct of_device_id *matches, const struct device_node *node)
const struct of_device_id *of_match_node(const struct of_device_id *matches, const struct device_node *node)
struct device_node *of_find_matching_node_and_match(struct device_node *from, const struct of_device_id *matches, const struct of_device_id **match)
int of_modalias_node(struct device_node *node, char *modalias, int len)
struct device_node *of_find_node_by_phandle(phandle handle)
void of_print_phandle_args(const char *msg, const struct of_phandle_args *args)
int of_phandle_iterator_init(struct of_phandle_iterator *it, const struct device_node *np, const char *list_name, const char *cells_name, int cell_count)
int of_phandle_iterator_next(struct of_phandle_iterator *it)
int of_phandle_iterator_args(struct of_phandle_iterator *it, uint32_t *args, int size)
static int __of_parse_phandle_with_args(const struct device_node *np, const char *list_name, const char *cells_name, int cell_count, int index, struct of_phandle_args *out_args)
struct device_node *of_parse_phandle(const struct device_node *np, const char *phandle_name, int index)
int of_parse_phandle_with_args(const struct device_node *np, const char *list_name, const char *cells_name, int index, struct of_phandle_args *out_args)
int of_parse_phandle_with_args_map(const struct device_node *np, const char *list_name, const char *stem_name, int index, struct of_phandle_args *out_args)
int of_parse_phandle_with_fixed_args(const struct device_node *np, const char *list_name, int cell_count, int index, struct of_phandle_args *out_args)
int of_count_phandle_with_args(const struct device_node *np, const char *list_name, const char *cells_name)
int __of_add_property(struct device_node *np, struct property *prop)
int of_add_property(struct device_node *np, struct property *prop)
int __of_remove_property(struct device_node *np, struct property *prop)
int of_remove_property(struct device_node *np, struct property *prop)
int __of_update_property(struct device_node *np, struct property *newprop, struct property **oldpropp)
int of_update_property(struct device_node *np, struct property *newprop)
static void of_alias_add(struct alias_prop *ap, struct device_node *np, int id, const char *stem, int stem_len)
void of_alias_scan(void * (*dt_alloc)
(u64 size, u64 align)
)
int of_alias_get_id(struct device_node *np, const char *stem)
int of_alias_get_highest_id(const char *stem)
bool of_console_check(struct device_node *dn, char *name, int index)
struct device_node *of_find_next_cache_node(const struct device_node *np)
int of_find_last_cache_level(unsigned int cpu)
int of_map_rid(struct device_node *np, u32 rid, const char *map_name, const char *map_mask_name, struct device_node **target, u32 *id_out)
  14 const struct device_node *np
  12 struct device_node *np
   8 const char *name
   7 const struct device_node *node
   6 struct device_node *prev
   6 int index
   6 const char *list_name
   5 struct device_node *from
   5 const struct device_node *device
   4 struct property *prop
   4 struct of_phandle_args *out_args
   4 int cpu
   4 int *lenp
   4 const char *cells_name
   3 void
   3 unsigned int *thread
   3 struct of_phandle_iterator *it
   3 struct device_node *node
   3 int cell_count
   3 const struct of_device_id *matches
   3 const char *type
   3 const char *stem
   3 const char *path
   3 const char *compat
   2 struct property *newprop
   2 struct device_node *cpun
   2 const char *prop_name
   2 const char *compatible
   1 void * *dt_alloc
   1 unsigned int cpu
   1 uint32_t *args
   1 u64 size
   1 u64 phys_id
   1 u64 align
   1 u32 rid
   1 u32 *id_out
   1 struct property **oldpropp
   1 struct device_node *parent
   1 struct device_node *dn
   1 struct device_node *device
   1 struct device_node *cpu_node
   1 struct device_node **target
   1 struct alias_prop *ap
   1 phandle handle
   1 of_phandle_iterator_next
   1 of_phandle_iterator_init
   1 of_modalias_node
   1 of_map_rid
   1 of_console_check
   1 of_alias_get_id
   1 of_alias_get_highest_id
   1 int stem_len
   1 int size
   1 int len
   1 int id
   1 const struct of_phandle_args *args
   1 const struct of_device_id **match
   1 const struct device_node *parent
   1 const char *stem_name
   1 const char *prefix
   1 const char *phandle_name
   1 const char *msg
   1 const char *map_name
   1 const char *map_mask_name
   1 const char *const *compat
   1 const char **opts
   1 char *name
   1 char *modalias
