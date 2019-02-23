
\n
static inline bool ap_instructions_available(void)
static inline struct ap_queue_status ap_tapq(ap_qid_t qid, unsigned long *info)
static inline struct ap_queue_status ap_test_queue(ap_qid_t qid, int tbit, unsigned long *info)
static inline struct ap_queue_status ap_rapq(ap_qid_t qid)
static inline struct ap_queue_status ap_zapq(ap_qid_t qid)
static inline int ap_qci(struct ap_config_info *config)
static inline struct ap_queue_status ap_aqic(ap_qid_t qid, struct ap_qirq_ctrl qirqctrl, void *ind)
static inline struct ap_queue_status ap_qact(ap_qid_t qid, int ifbit, union ap_qact_ap_info *apinfo)
static inline struct ap_queue_status ap_nqap(ap_qid_t qid, unsigned long long psmid, void *msg, size_t length)
static inline struct ap_queue_status ap_dqap(ap_qid_t qid, unsigned long long *psmid, void *msg, size_t length)
\n
      8 ap_qid_t qid
      2 void *msg
      2 unsigned long *info
      2 size_t length
      1 void *ind
      1 void
      1 unsigned long long *psmid
      1 unsigned long long psmid
      1 union ap_qact_ap_info *apinfo
      1 struct ap_qirq_ctrl qirqctrl
      1 struct ap_config_info *config
      1 int tbit
      1 int ifbit
