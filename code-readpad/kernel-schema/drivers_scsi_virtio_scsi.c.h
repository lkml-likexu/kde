
\n
static inline struct Scsi_Host *virtio_scsi_host(struct virtio_device *vdev)
static void virtscsi_compute_resid(struct scsi_cmnd *sc, u32 resid)
static void virtscsi_complete_cmd(struct virtio_scsi *vscsi, void *buf)
static void virtscsi_vq_done(struct virtio_scsi *vscsi, struct virtio_scsi_vq *virtscsi_vq, void (*fn)
(struct virtio_scsi *vscsi, void *buf)
)
static void virtscsi_req_done(struct virtqueue *vq)
static void virtscsi_poll_requests(struct virtio_scsi *vscsi)
static void virtscsi_complete_free(struct virtio_scsi *vscsi, void *buf)
static void virtscsi_ctrl_done(struct virtqueue *vq)
static int virtscsi_kick_event(struct virtio_scsi *vscsi, struct virtio_scsi_event_node *event_node)
static int virtscsi_kick_event_all(struct virtio_scsi *vscsi)
static void virtscsi_cancel_event_work(struct virtio_scsi *vscsi)
static void virtscsi_handle_transport_reset(struct virtio_scsi *vscsi, struct virtio_scsi_event *event)
static void virtscsi_handle_param_change(struct virtio_scsi *vscsi, struct virtio_scsi_event *event)
static void virtscsi_handle_event(struct work_struct *work)
static void virtscsi_complete_event(struct virtio_scsi *vscsi, void *buf)
static void virtscsi_event_done(struct virtqueue *vq)
static int virtscsi_add_cmd(struct virtqueue *vq, struct virtio_scsi_cmd *cmd, size_t req_size, size_t resp_size)
static int virtscsi_kick_cmd(struct virtio_scsi_vq *vq, struct virtio_scsi_cmd *cmd, size_t req_size, size_t resp_size)
static void virtio_scsi_init_hdr(struct virtio_device *vdev, struct virtio_scsi_cmd_req *cmd, struct scsi_cmnd *sc)
static void virtio_scsi_init_hdr_pi(struct virtio_device *vdev, struct virtio_scsi_cmd_req_pi *cmd_pi, struct scsi_cmnd *sc)
static struct virtio_scsi_vq *virtscsi_pick_vq_mq(struct virtio_scsi *vscsi, struct scsi_cmnd *sc)
static int virtscsi_queuecommand(struct Scsi_Host *shost, struct scsi_cmnd *sc)
static int virtscsi_tmf(struct virtio_scsi *vscsi, struct virtio_scsi_cmd *cmd)
static int virtscsi_device_reset(struct scsi_cmnd *sc)
static int virtscsi_device_alloc(struct scsi_device *sdevice)
static int virtscsi_change_queue_depth(struct scsi_device *sdev, int qdepth)
static int virtscsi_abort(struct scsi_cmnd *sc)
static int virtscsi_map_queues(struct Scsi_Host *shost)
static enum blk_eh_timer_return virtscsi_eh_timed_out(struct scsi_cmnd *scmnd)
static void virtscsi_init_vq(struct virtio_scsi_vq *virtscsi_vq, struct virtqueue *vq)
static void virtscsi_remove_vqs(struct virtio_device *vdev)
static int virtscsi_init(struct virtio_device *vdev, struct virtio_scsi *vscsi)
static int virtscsi_probe(struct virtio_device *vdev)
static void virtscsi_remove(struct virtio_device *vdev)
static int virtscsi_freeze(struct virtio_device *vdev)
static int virtscsi_restore(struct virtio_device *vdev)
static int __init init(void)
static void __exit fini(void)
\n
     14 struct virtio_scsi *vscsi
      9 struct virtio_device *vdev
      7 struct scsi_cmnd *sc
      5 struct virtqueue *vq
      4 void *buf
      3 struct virtio_scsi_cmd *cmd
      2 void
      2 struct virtio_scsi_vq *virtscsi_vq
      2 struct virtio_scsi_event *event
      2 struct Scsi_Host *shost
      2 size_t resp_size
      2 size_t req_size
      1 void *fn
      1 u32 resid
      1 struct work_struct *work
      1 struct virtio_scsi_vq *vq
      1 struct virtio_scsi_event_node *event_node
      1 struct virtio_scsi_cmd_req_pi *cmd_pi
      1 struct virtio_scsi_cmd_req *cmd
      1 struct scsi_device *sdevice
      1 struct scsi_device *sdev
      1 struct scsi_cmnd *scmnd
      1 int qdepth
