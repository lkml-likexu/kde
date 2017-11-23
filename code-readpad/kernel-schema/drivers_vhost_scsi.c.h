
static void vhost_scsi_done_inflight(struct kref *kref)
static void vhost_scsi_init_inflight(struct vhost_scsi *vs, struct vhost_scsi_inflight *old_inflight[])
static struct vhost_scsi_inflight * vhost_scsi_get_inflight(struct vhost_virtqueue *vq)
static void vhost_scsi_put_inflight(struct vhost_scsi_inflight *inflight)
static int vhost_scsi_check_true(struct se_portal_group *se_tpg)
static int vhost_scsi_check_false(struct se_portal_group *se_tpg)
static char *vhost_scsi_get_fabric_name(void)
static char *vhost_scsi_get_fabric_wwn(struct se_portal_group *se_tpg)
static u16 vhost_scsi_get_tpgt(struct se_portal_group *se_tpg)
static int vhost_scsi_check_prot_fabric_only(struct se_portal_group *se_tpg)
static u32 vhost_scsi_tpg_get_inst_index(struct se_portal_group *se_tpg)
static void vhost_scsi_release_cmd(struct se_cmd *se_cmd)
static u32 vhost_scsi_sess_get_index(struct se_session *se_sess)
static int vhost_scsi_write_pending(struct se_cmd *se_cmd)
static int vhost_scsi_write_pending_status(struct se_cmd *se_cmd)
static void vhost_scsi_set_default_node_attrs(struct se_node_acl *nacl)
static int vhost_scsi_get_cmd_state(struct se_cmd *se_cmd)
static void vhost_scsi_complete_cmd(struct vhost_scsi_cmd *cmd)
static int vhost_scsi_queue_data_in(struct se_cmd *se_cmd)
static int vhost_scsi_queue_status(struct se_cmd *se_cmd)
static void vhost_scsi_queue_tm_rsp(struct se_cmd *se_cmd)
static void vhost_scsi_aborted_task(struct se_cmd *se_cmd)
static void vhost_scsi_free_evt(struct vhost_scsi *vs, struct vhost_scsi_evt *evt)
static struct vhost_scsi_evt * vhost_scsi_allocate_evt(struct vhost_scsi *vs, u32 event, u32 reason)
static void vhost_scsi_free_cmd(struct vhost_scsi_cmd *cmd)
static int vhost_scsi_check_stop_free(struct se_cmd *se_cmd)
static void vhost_scsi_do_evt_work(struct vhost_scsi *vs, struct vhost_scsi_evt *evt)
static void vhost_scsi_evt_work(struct vhost_work *work)
static void vhost_scsi_complete_cmd_work(struct vhost_work *work)
static struct vhost_scsi_cmd * vhost_scsi_get_tag(struct vhost_virtqueue *vq, struct vhost_scsi_tpg *tpg, unsigned char *cdb, u64 scsi_tag, u16 lun, u8 task_attr, u32 exp_data_len, int data_direction)
static int vhost_scsi_map_to_sgl(struct vhost_scsi_cmd *cmd, struct iov_iter *iter, struct scatterlist *sgl, bool write)
static int vhost_scsi_calc_sgls(struct iov_iter *iter, size_t bytes, int max_sgls)
static int vhost_scsi_iov_to_sgl(struct vhost_scsi_cmd *cmd, bool write, struct iov_iter *iter, struct scatterlist *sg, int sg_count)
static int vhost_scsi_mapal(struct vhost_scsi_cmd *cmd, size_t prot_bytes, struct iov_iter *prot_iter, size_t data_bytes, struct iov_iter *data_iter)
static int vhost_scsi_to_tcm_attr(int attr)
static void vhost_scsi_submission_work(struct work_struct *work)
static void vhost_scsi_send_bad_target(struct vhost_scsi *vs, struct vhost_virtqueue *vq, int head, unsigned out)
static void vhost_scsi_handle_vq(struct vhost_scsi *vs, struct vhost_virtqueue *vq)
static void vhost_scsi_ctl_handle_kick(struct vhost_work *work)
static void vhost_scsi_send_evt(struct vhost_scsi *vs, struct vhost_scsi_tpg *tpg, struct se_lun *lun, u32 event, u32 reason)
static void vhost_scsi_evt_handle_kick(struct vhost_work *work)
static void vhost_scsi_handle_kick(struct vhost_work *work)
static void vhost_scsi_flush_vq(struct vhost_scsi *vs, int index)
static void vhost_scsi_flush(struct vhost_scsi *vs)
static int vhost_scsi_set_endpoint(struct vhost_scsi *vs, struct vhost_scsi_target *t)
static int vhost_scsi_clear_endpoint(struct vhost_scsi *vs, struct vhost_scsi_target *t)
static int vhost_scsi_set_features(struct vhost_scsi *vs, u64 features)
static int vhost_scsi_open(struct inode *inode, struct file *f)
static int vhost_scsi_release(struct inode *inode, struct file *f)
static long vhost_scsi_ioctl(struct file *f, unsigned int ioctl, unsigned long arg)
static long vhost_scsi_compat_ioctl(struct file *f, unsigned int ioctl, unsigned long arg)
static int __init vhost_scsi_register(void)
static void vhost_scsi_deregister(void)
static char *vhost_scsi_dump_proto_id(struct vhost_scsi_tport *tport)
static void vhost_scsi_do_plug(struct vhost_scsi_tpg *tpg, struct se_lun *lun, bool plug)
static void vhost_scsi_hotplug(struct vhost_scsi_tpg *tpg, struct se_lun *lun)
static void vhost_scsi_hotunplug(struct vhost_scsi_tpg *tpg, struct se_lun *lun)
static int vhost_scsi_port_link(struct se_portal_group *se_tpg, struct se_lun *lun)
static void vhost_scsi_port_unlink(struct se_portal_group *se_tpg, struct se_lun *lun)
static void vhost_scsi_free_cmd_map_res(struct se_session *se_sess)
static ssize_t vhost_scsi_tpg_attrib_fabric_prot_type_store( struct config_item *item, const char *page, size_t count)
static ssize_t vhost_scsi_tpg_attrib_fabric_prot_type_show( struct config_item *item, char *page)
static int vhost_scsi_nexus_cb(struct se_portal_group *se_tpg, struct se_session *se_sess, void *p)
static int vhost_scsi_make_nexus(struct vhost_scsi_tpg *tpg, const char *name)
static int vhost_scsi_drop_nexus(struct vhost_scsi_tpg *tpg)
static ssize_t vhost_scsi_tpg_nexus_show(struct config_item *item, char *page)
static ssize_t vhost_scsi_tpg_nexus_store(struct config_item *item, const char *page, size_t count)
static struct se_portal_group * vhost_scsi_make_tpg(struct se_wwn *wwn, const char *name)
static void vhost_scsi_drop_tpg(struct se_portal_group *se_tpg)
static struct se_wwn * vhost_scsi_make_tport(struct target_fabric_configfs *tf, struct config_group *group, const char *name)
static void vhost_scsi_drop_tport(struct se_wwn *wwn)
static ssize_t vhost_scsi_wwn_version_show(struct config_item *item, char *page)
static int __init vhost_scsi_init(void)
static void vhost_scsi_exit(void)
  12 struct vhost_scsi *vs
  10 struct se_portal_group *se_tpg
   9 struct se_cmd *se_cmd
   7 struct vhost_scsi_tpg *tpg
   6 struct se_lun *lun
   5 void
   5 struct vhost_work *work
   5 struct vhost_scsi_cmd *cmd
   5 struct config_item *item
   4 struct vhost_virtqueue *vq
   4 struct file *f
   3 struct se_session *se_sess
   3 struct iov_iter *iter
   3 const char *name
   3 char *page
   2 unsigned long arg
   2 unsigned int ioctl
   2 u32 reason
   2 u32 event
   2 struct vhost_scsi_target *t
   2 struct vhost_scsi_evt *evt
   2 struct se_wwn *wwn
   2 struct inode *inode
   2 size_t count
   2 const char *page
   2 bool write
   1 void *p
   1 unsigned out
   1 unsigned char *cdb
   1 u8 task_attr
   1 u64 scsi_tag
   1 u64 features
   1 u32 exp_data_len
   1 u16 lun
   1 struct work_struct *work
   1 struct vhost_scsi_tport *tport
   1 struct vhost_scsi_inflight *old_inflight[]
   1 struct vhost_scsi_inflight *inflight
   1 struct target_fabric_configfs *tf
   1 struct se_node_acl *nacl
   1 struct scatterlist *sgl
   1 struct scatterlist *sg
   1 struct kref *kref
   1 struct iov_iter *prot_iter
   1 struct iov_iter *data_iter
   1 struct config_group *group
   1 size_t prot_bytes
   1 size_t data_bytes
   1 size_t bytes
   1 int sg_count
   1 int max_sgls
   1 int index
   1 int head
   1 int data_direction
   1 int attr
   1 bool plug
