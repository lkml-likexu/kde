
\n
static struct acpi_subtable_header *fetch_pptt_subtable(struct acpi_table_header *table_hdr, u32 pptt_ref)
static struct acpi_pptt_processor *fetch_pptt_node(struct acpi_table_header *table_hdr, u32 pptt_ref)
static struct acpi_pptt_cache *fetch_pptt_cache(struct acpi_table_header *table_hdr, u32 pptt_ref)
static struct acpi_subtable_header *acpi_get_pptt_resource(struct acpi_table_header *table_hdr, struct acpi_pptt_processor *node, int resource)
static inline bool acpi_pptt_match_type(int table_type, int type)
static int acpi_pptt_walk_cache(struct acpi_table_header *table_hdr, int local_level, struct acpi_subtable_header *res, struct acpi_pptt_cache **found, int level, int type)
static struct acpi_pptt_cache *acpi_find_cache_level(struct acpi_table_header *table_hdr, struct acpi_pptt_processor *cpu_node, int *starting_level, int level, int type)
static int acpi_count_levels(struct acpi_table_header *table_hdr, struct acpi_pptt_processor *cpu_node)
static int acpi_pptt_leaf_node(struct acpi_table_header *table_hdr, struct acpi_pptt_processor *node)
static struct acpi_pptt_processor *acpi_find_processor_node(struct acpi_table_header *table_hdr, u32 acpi_cpu_id)
static int acpi_find_cache_levels(struct acpi_table_header *table_hdr, u32 acpi_cpu_id)
static u8 acpi_cache_type(enum cache_type type)
static struct acpi_pptt_cache *acpi_find_cache_node(struct acpi_table_header *table_hdr, u32 acpi_cpu_id, enum cache_type type, unsigned int level, struct acpi_pptt_processor **node)
static void update_cache_properties(struct cacheinfo *this_leaf, struct acpi_pptt_cache *found_cache, struct acpi_pptt_processor *cpu_node)
static void cache_setup_acpi_cpu(struct acpi_table_header *table, unsigned int cpu)
static struct acpi_pptt_processor *acpi_find_processor_package_id(struct acpi_table_header *table_hdr, struct acpi_pptt_processor *cpu, int level, int flag)
static int topology_get_acpi_cpu_tag(struct acpi_table_header *table, unsigned int cpu, int level, int flag)
static int find_acpi_cpu_topology_tag(unsigned int cpu, int level, int flag)
int acpi_find_last_cache_level(unsigned int cpu)
int cache_setup_acpi(unsigned int cpu)
int find_acpi_cpu_topology(unsigned int cpu, int level)
int find_acpi_cpu_cache_topology(unsigned int cpu, int level)
int find_acpi_cpu_topology_package(unsigned int cpu)
\n
     12 struct acpi_table_header *table_hdr
      8 unsigned int cpu
      7 int level
      3 u32 pptt_ref
      3 u32 acpi_cpu_id
      3 struct acpi_pptt_processor *cpu_node
      3 int type
      3 int flag
      2 struct acpi_table_header *table
      2 struct acpi_pptt_processor *node
      2 enum cache_type type
      1 unsigned int level
      1 struct cacheinfo *this_leaf
      1 struct acpi_subtable_header *res
      1 struct acpi_pptt_processor **node
      1 struct acpi_pptt_processor *cpu
      1 struct acpi_pptt_cache *found_cache
      1 struct acpi_pptt_cache **found
      1 int table_type
      1 int *starting_level
      1 int resource
      1 int local_level
