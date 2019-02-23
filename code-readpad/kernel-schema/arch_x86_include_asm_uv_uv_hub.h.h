
\n
extern void **__uv_hub_info_list; static inline struct uv_hub_info_s *uv_hub_info_list(int node)
static inline struct uv_hub_info_s *_uv_hub_info(void)
static inline struct uv_hub_info_s *uv_cpu_hub_info(int cpu)
define UV_HUB_INFO_VERSION 0x7150 extern int uv_hub_info_version(void)
; static inline int uv_hub_info_check(int version)
static inline int is_uv1_hub(void)
static inline int is_uv1_hub(void)
return uv_hub_info->hub_revision < UV2_HUB_REVISION_BASE; } static inline int is_uv1_hub(void)
static inline int is_uv2_hub(void)
static inline int is_uv2_hub(void)
return ((uv_hub_info->hub_revision >= UV2_HUB_REVISION_BASE)
&& (uv_hub_info->hub_revision < UV3_HUB_REVISION_BASE)
)
; } static inline int is_uv2_hub(void)
static inline int is_uv3_hub(void)
static inline int is_uv3_hub(void)
return ((uv_hub_info->hub_revision >= UV3_HUB_REVISION_BASE)
&& (uv_hub_info->hub_revision < UV4_HUB_REVISION_BASE)
)
; } static inline int is_uv3_hub(void)
static inline int is_uv4a_hub(void)
static inline int is_uv4a_hub(void)
return (uv_hub_info->hub_revision >= UV4A_HUB_REVISION_BASE)
; } static inline int is_uv4a_hub(void)
static inline int is_uv4_hub(void)
static inline int is_uv4_hub(void)
return uv_hub_info->hub_revision >= UV4_HUB_REVISION_BASE; } static inline int is_uv4_hub(void)
static inline int is_uvx_hub(void)
static inline int is_uv_hub(void)
static inline unsigned int uv_gpa_shift(void)
static inline struct uv_gam_range_s *uv_gam_range(unsigned long pa)
static inline unsigned long uv_gam_range_base(unsigned long pa)
static inline unsigned long uv_soc_phys_ram_to_nasid(unsigned long paddr)
static inline unsigned long uv_gpa_nasid(void *v)
static inline unsigned long uv_soc_phys_ram_to_gpa(unsigned long paddr)
static inline unsigned long uv_gpa(void *v)
static inline int uv_gpa_in_mmr_space(unsigned long gpa)
static inline unsigned long uv_gpa_to_soc_phys_ram(unsigned long gpa)
static inline unsigned long uv_gpa_to_gnode(unsigned long gpa)
static inline int uv_gpa_to_pnode(unsigned long gpa)
static inline unsigned long uv_gpa_to_offset(unsigned long gpa)
static inline int _uv_socket_to_node(int socket, unsigned short *s2nid)
static inline int uv_socket_to_node(int socket)
static inline void *uv_pnode_offset_to_vaddr(int pnode, unsigned long offset)
static inline int uv_apicid_to_pnode(int apicid)
static inline int uv_apicid_to_socket(int apicid)
static inline unsigned long *uv_global_mmr32_address(int pnode, unsigned long offset)
static inline void uv_write_global_mmr32(int pnode, unsigned long offset, unsigned long val)
static inline unsigned long uv_read_global_mmr32(int pnode, unsigned long offset)
static inline volatile void __iomem *uv_global_mmr64_address(int pnode, unsigned long offset)
static inline void uv_write_global_mmr64(int pnode, unsigned long offset, unsigned long val)
static inline unsigned long uv_read_global_mmr64(int pnode, unsigned long offset)
static inline void uv_write_global_mmr8(int pnode, unsigned long offset, unsigned char val)
static inline unsigned char uv_read_global_mmr8(int pnode, unsigned long offset)
static inline unsigned long *uv_local_mmr_address(unsigned long offset)
static inline unsigned long uv_read_local_mmr(unsigned long offset)
static inline void uv_write_local_mmr(unsigned long offset, unsigned long val)
static inline unsigned char uv_read_local_mmr8(unsigned long offset)
static inline void uv_write_local_mmr8(unsigned long offset, unsigned char val)
static inline int uv_blade_processor_id(void)
static inline int uv_cpu_blade_processor_id(int cpu)
static inline int uv_blade_to_node(int blade)
static inline int uv_numa_blade_id(void)
static inline int uv_node_to_blade_id(int nid)
static inline int uv_cpu_to_blade_id(int cpu)
static inline int uv_blade_to_pnode(int bid)
static inline int uv_blade_to_memory_nid(int bid)
static inline int uv_blade_nr_possible_cpus(int bid)
static inline int uv_blade_nr_online_cpus(int bid)
static inline int uv_cpu_to_pnode(int cpu)
static inline int uv_node_to_pnode(int nid)
extern short uv_possible_blades; static inline int uv_num_possible_blades(void)
static inline void uv_set_scir_bits(unsigned char value)
static inline unsigned long uv_scir_offset(int apicid)
static inline void uv_set_cpu_scir_bits(int cpu, unsigned char value)
extern unsigned int uv_apicid_hibits; static unsigned long uv_hub_ipi_value(int apicid, int vector, int mode)
static inline void uv_hub_send_ipi(int pnode, int apicid, int vector)
static inline int uv_get_min_hub_revision_id(void)
\n
     24 void
     14 unsigned long offset
     10 int pnode
      5 unsigned long gpa
      5 int cpu
      5 int apicid
      4 int bid
      3 unsigned long val
      2 void *v
      2 unsigned long paddr
      2 unsigned long pa
      2 unsigned char value
      2 unsigned char val
      2 int vector
      2 int socket
      2 int nid
      1 uv_hub_info->hub_revision < UV4_HUB_REVISION_BASE
      1 uv_hub_info->hub_revision >= UV4A_HUB_REVISION_BASE
      1 uv_hub_info->hub_revision >= UV3_HUB_REVISION_BASE
      1 uv_hub_info->hub_revision < UV3_HUB_REVISION_BASE
      1 uv_hub_info->hub_revision >= UV2_HUB_REVISION_BASE
      1 unsigned short *s2nid
      1 int version
      1 int node
      1 int mode
      1 int blade
