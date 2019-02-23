
\n
static u32 page_to_balloon_pfn(struct page *page)
static void balloon_ack(struct virtqueue *vq)
static void tell_host(struct virtio_balloon *vb, struct virtqueue *vq)
static void set_page_pfns(struct virtio_balloon *vb, __virtio32 pfns[], struct page *page)
static unsigned fill_balloon(struct virtio_balloon *vb, size_t num)
static void release_pages_balloon(struct virtio_balloon *vb, struct list_head *pages)
static unsigned leak_balloon(struct virtio_balloon *vb, size_t num)
static inline void update_stat(struct virtio_balloon *vb, int idx, u16 tag, u64 val)
static unsigned int update_balloon_stats(struct virtio_balloon *vb)
static void stats_request(struct virtqueue *vq)
static void stats_handle_request(struct virtio_balloon *vb)
static inline s64 towards_target(struct virtio_balloon *vb)
static unsigned long return_free_pages_to_mm(struct virtio_balloon *vb, unsigned long num_to_return)
static void virtio_balloon_queue_free_page_work(struct virtio_balloon *vb)
static void virtballoon_changed(struct virtio_device *vdev)
static void update_balloon_size(struct virtio_balloon *vb)
static void update_balloon_stats_func(struct work_struct *work)
static void update_balloon_size_func(struct work_struct *work)
static int init_vqs(struct virtio_balloon *vb)
static u32 virtio_balloon_cmd_id_received(struct virtio_balloon *vb)
static int send_cmd_id_start(struct virtio_balloon *vb)
static int send_cmd_id_stop(struct virtio_balloon *vb)
static int get_free_page_and_send(struct virtio_balloon *vb)
static int send_free_pages(struct virtio_balloon *vb)
static void virtio_balloon_report_free_page(struct virtio_balloon *vb)
static void report_free_page_func(struct work_struct *work)
static int virtballoon_migratepage(struct balloon_dev_info *vb_dev_info, struct page *newpage, struct page *page, enum migrate_mode mode)
static struct dentry *balloon_mount(struct file_system_type *fs_type, int flags, const char *dev_name, void *data)
static unsigned long shrink_free_pages(struct virtio_balloon *vb, unsigned long pages_to_free)
static unsigned long shrink_balloon_pages(struct virtio_balloon *vb, unsigned long pages_to_free)
static unsigned long virtio_balloon_shrinker_scan(struct shrinker *shrinker, struct shrink_control *sc)
static unsigned long virtio_balloon_shrinker_count(struct shrinker *shrinker, struct shrink_control *sc)
static void virtio_balloon_unregister_shrinker(struct virtio_balloon *vb)
static int virtio_balloon_register_shrinker(struct virtio_balloon *vb)
static int virtballoon_probe(struct virtio_device *vdev)
static void remove_common(struct virtio_balloon *vb)
static void virtballoon_remove(struct virtio_device *vdev)
static int virtballoon_freeze(struct virtio_device *vdev)
static int virtballoon_restore(struct virtio_device *vdev)
static int virtballoon_validate(struct virtio_device *vdev)
\n
     24 struct virtio_balloon *vb
      6 struct virtio_device *vdev
      3 struct work_struct *work
      3 struct virtqueue *vq
      3 struct page *page
      2 unsigned long pages_to_free
      2 struct shrinker *shrinker
      2 struct shrink_control *sc
      2 size_t num
      1 void *data
      1 __virtio32 pfns[]
      1 unsigned long num_to_return
      1 u64 val
      1 u16 tag
      1 struct page *newpage
      1 struct list_head *pages
      1 struct file_system_type *fs_type
      1 struct balloon_dev_info *vb_dev_info
      1 int idx
      1 int flags
      1 enum migrate_mode mode
      1 const char *dev_name
