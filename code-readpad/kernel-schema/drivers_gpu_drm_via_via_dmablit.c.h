
\n
static void via_unmap_blit_from_device(struct pci_dev *pdev, drm_via_sg_info_t *vsg)
static void via_map_blit_for_device(struct pci_dev *pdev, const drm_via_dmablit_t *xfer, drm_via_sg_info_t *vsg, int mode)
static void via_free_sg_info(struct pci_dev *pdev, drm_via_sg_info_t *vsg)
static void via_fire_dmablit(struct drm_device *dev, drm_via_sg_info_t *vsg, int engine)
static int via_lock_all_dma_pages(drm_via_sg_info_t *vsg, drm_via_dmablit_t *xfer)
static int via_alloc_desc_pages(drm_via_sg_info_t *vsg)
static void via_abort_dmablit(struct drm_device *dev, int engine)
static void via_dmablit_engine_off(struct drm_device *dev, int engine)
void via_dmablit_handler(struct drm_device *dev, int engine, int from_irq)
static int via_dmablit_active(drm_via_blitq_t *blitq, int engine, uint32_t handle, wait_queue_head_t **queue)
static int via_dmablit_sync(struct drm_device *dev, uint32_t handle, int engine)
static void via_dmablit_timer(struct timer_list *t)
static void via_dmablit_workqueue(struct work_struct *work)
void via_init_dmablit(struct drm_device *dev)
static int via_build_sg_info(struct drm_device *dev, drm_via_sg_info_t *vsg, drm_via_dmablit_t *xfer)
static int via_dmablit_grab_slot(drm_via_blitq_t *blitq, int engine)
static void via_dmablit_release_slot(drm_via_blitq_t *blitq)
static int via_dmablit(struct drm_device *dev, drm_via_dmablit_t *xfer)
int via_dma_blit_sync(struct drm_device *dev, void *data, struct drm_file *file_priv)
int via_dma_blit(struct drm_device *dev, void *data, struct drm_file *file_priv)
\n
     10 struct drm_device *dev
      7 int engine
      7 drm_via_sg_info_t *vsg
      3 struct pci_dev *pdev
      3 drm_via_dmablit_t *xfer
      3 drm_via_blitq_t *blitq
      2 void *data
      2 uint32_t handle
      2 struct drm_file *file_priv
      1 wait_queue_head_t **queue
      1 struct work_struct *work
      1 struct timer_list *t
      1 int mode
      1 int from_irq
      1 const drm_via_dmablit_t *xfer
