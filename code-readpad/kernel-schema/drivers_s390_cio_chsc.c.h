
EXPORT_SYMBOL_GPL(chsc_error_from_response);
EXPORT_SYMBOL_GPL(chsc_ssqd);
EXPORT_SYMBOL_GPL(chsc_sadc);
EXPORT_SYMBOL_GPL(chsc_determine_channel_path_desc);
EXPORT_SYMBOL_GPL(css_general_characteristics);
EXPORT_SYMBOL_GPL(css_chsc_characteristics);
EXPORT_SYMBOL_GPL(chsc_siosl);
EXPORT_SYMBOL_GPL(chsc_scm_info);
EXPORT_SYMBOL_GPL(chsc_pnso_brinfo);
\n
int chsc_error_from_response(int response)
int chsc_get_ssd_info(struct subchannel_id schid, struct chsc_ssd_info *ssd)
int chsc_ssqd(struct subchannel_id schid, struct chsc_ssqd_area *ssqd)
int chsc_sadc(struct subchannel_id schid, struct chsc_scssc_area *scssc, u64 summary_indicator_addr, u64 subchannel_indicator_addr)
static int s390_subchannel_remove_chpid(struct subchannel *sch, void *data)
void chsc_chp_offline(struct chp_id chpid)
static int __s390_process_res_acc(struct subchannel *sch, void *data)
static void s390_process_res_acc(struct chp_link *link)
static char *store_ebcdic(char *dest, const char *src, unsigned long len, char delim)
static void format_node_data(char *params, char *id, struct node_descriptor *nd)
static void chsc_process_sei_link_incident(struct chsc_sei_nt0_area *sei_area)
static void chsc_process_sei_res_acc(struct chsc_sei_nt0_area *sei_area)
static void chsc_process_sei_chp_avail(struct chsc_sei_nt0_area *sei_area)
static void chsc_process_sei_chp_config(struct chsc_sei_nt0_area *sei_area)
static void chsc_process_sei_scm_change(struct chsc_sei_nt0_area *sei_area)
static void chsc_process_sei_scm_avail(struct chsc_sei_nt0_area *sei_area)
static void chsc_process_sei_nt2(struct chsc_sei_nt2_area *sei_area)
static void chsc_process_sei_nt0(struct chsc_sei_nt0_area *sei_area)
static void chsc_process_event_information(struct chsc_sei *sei, u64 ntsm)
static void chsc_process_crw(struct crw *crw0, struct crw *crw1, int overflow)
void chsc_chp_online(struct chp_id chpid)
static void __s390_subchannel_vary_chpid(struct subchannel *sch, struct chp_id chpid, int on)
static int s390_subchannel_vary_chpid_off(struct subchannel *sch, void *data)
static int s390_subchannel_vary_chpid_on(struct subchannel *sch, void *data)
int chsc_chp_vary(struct chp_id chpid, int on)
static void chsc_remove_cmg_attr(struct channel_subsystem *css)
static int chsc_add_cmg_attr(struct channel_subsystem *css)
int __chsc_do_secm(struct channel_subsystem *css, int enable)
int chsc_secm(struct channel_subsystem *css, int enable)
int chsc_determine_channel_path_desc(struct chp_id chpid, int fmt, int rfmt, int c, int m, void *page)
define chsc_det_chp_desc(FMT, c)
\ int chsc_determine_fmtFMT_channel_path_desc( \struct chp_id chpid, struct channel_path_desc_fmtFMT *desc)
\ static void chsc_initialize_cmg_chars(struct channel_path *chp, u8 cmcv, struct cmg_chars *chars)
int chsc_get_channel_measurement_chars(struct channel_path *chp)
int __init chsc_init(void)
void __init chsc_init_cleanup(void)
int __chsc_enable_facility(struct chsc_sda_area *sda_area, int operation_code)
int chsc_enable_facility(int operation_code)
int __init chsc_get_cssid(int idx)
int __init chsc_determine_css_characteristics(void)
int chsc_sstpc(void *page, unsigned int op, u16 ctrl, u64 *clock_delta)
int chsc_sstpi(void *page, void *result, size_t size)
int chsc_siosl(struct subchannel_id schid)
int chsc_scm_info(struct chsc_scm_info *scm_area, u64 token)
int chsc_pnso_brinfo(struct subchannel_id schid, struct chsc_pnso_area *brinfo_area, struct chsc_brinfo_resume_token resume_token, int cnc)
\n
      7 struct chsc_sei_nt0_area *sei_area
      5 struct subchannel *sch
      5 struct subchannel_id schid
      5 struct chp_id chpid
      4 void *data
      4 struct channel_subsystem *css
      3 void *page
      3 void
      2 struct channel_path *chp
      2 int operation_code
      2 int on
      2 int enable
      1 void *result
      1 unsigned long len
      1 unsigned int op
      1 u8 cmcv
      1 u64 token
      1 u64 summary_indicator_addr
      1 u64 subchannel_indicator_addr
      1 u64 ntsm
      1 u64 *clock_delta
      1 u16 ctrl
      1 struct node_descriptor *nd
      1 struct crw *crw1
      1 struct crw *crw0
      1 struct cmg_chars *chars
      1 struct chsc_ssqd_area *ssqd
      1 struct chsc_ssd_info *ssd
      1 struct chsc_sei *sei
      1 struct chsc_sei_nt2_area *sei_area
      1 struct chsc_sda_area *sda_area
      1 struct chsc_scssc_area *scssc
      1 struct chsc_scm_info *scm_area
      1 struct chsc_pnso_area *brinfo_area
      1 struct chsc_brinfo_resume_token resume_token
      1 struct chp_link *link
      1 \struct chp_id chpid
      1 struct channel_path_desc_fmtFMT *desc
      1 size_t size
      1 int rfmt
      1 int response
      1 int overflow
      1 int m
      1 int idx
      1 int fmt
      1 int cnc
      1 int c
      1 FMT
      1 css_general_characteristics
      1 css_chsc_characteristics
      1 const char *src
      1 chsc_ssqd
      1 chsc_siosl
      1 chsc_scm_info
      1 chsc_sadc
      1 chsc_pnso_brinfo
      1 chsc_error_from_response
      1 chsc_determine_channel_path_desc
      1 char *params
      1 char *id
      1 char *dest
      1 char delim
      1 c
