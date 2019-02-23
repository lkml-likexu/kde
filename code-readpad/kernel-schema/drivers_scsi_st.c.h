
\n
static struct scsi_tape *scsi_tape_get(int dev)
static void scsi_tape_put(struct scsi_tape *STp)
static char * st_incompatible(struct scsi_device* SDp)
static inline char *tape_name(struct scsi_tape *tape)
static void st_analyze_sense(struct st_request *SRpnt, struct st_cmdstatus *s)
static int st_chk_result(struct scsi_tape *STp, struct st_request * SRpnt)
static struct st_request *st_allocate_request(struct scsi_tape *stp)
static void st_release_request(struct st_request *streq)
static void st_do_stats(struct scsi_tape *STp, struct request *req)
static void st_scsi_execute_end(struct request *req, blk_status_t status)
static int st_scsi_execute(struct st_request *SRpnt, const unsigned char *cmd, int data_direction, void *buffer, unsigned bufflen, int timeout, int retries)
static struct st_request * st_do_scsi(struct st_request * SRpnt, struct scsi_tape * STp, unsigned char *cmd, int bytes, int direction, int timeout, int retries, int do_wait)
static int write_behind_check(struct scsi_tape * STp)
static int cross_eof(struct scsi_tape * STp, int forward)
static int st_flush_write_buffer(struct scsi_tape * STp)
static int flush_buffer(struct scsi_tape *STp, int seek_next)
} static int set_mode_densblk(struct scsi_tape * STp, struct st_modedef * STm)
static int do_door_lock(struct scsi_tape * STp, int do_lock)
static void reset_state(struct scsi_tape *STp)
static int test_ready(struct scsi_tape *STp, int do_wait)
static int check_tape(struct scsi_tape *STp, struct file *filp)
 static int st_open(struct inode *inode, struct file *filp)
static int st_flush(struct file *filp, fl_owner_t id)
static int st_release(struct inode *inode, struct file *filp)
return result; } static ssize_t rw_checks(struct scsi_tape *STp, struct file *filp, size_t count)
static int setup_buffering(struct scsi_tape *STp, const char __user *buf, size_t count, int is_read)
static void release_buffering(struct scsi_tape *STp, int is_read)
static ssize_t st_write(struct file *filp, const char __user *buf, size_t count, loff_t * ppos)
Does release user buffer mapping if it is set. */ static long read_tape(struct scsi_tape *STp, long count, struct st_request ** aSRpnt)
static ssize_t st_read(struct file *filp, char __user *buf, size_t count, loff_t * ppos)
DEB(static void st_log_options(struct scsi_tape * STp, struct st_modedef * STm)
static int st_set_options(struct scsi_tape *STp, long options)
static int read_mode_page(struct scsi_tape *STp, int page, int omit_block_descs)
static int write_mode_page(struct scsi_tape *STp, int page, int slow)
static int st_compression(struct scsi_tape * STp, int state)
static int do_load_unload(struct scsi_tape *STp, struct file *filp, int load_code)
return retval; } define ST_DEB_FORWARD0define ST_DEB_BACKWARD 1 static void deb_space_print(struct scsi_tape *STp, int direction, char *units, unsigned char *cmd)
static int st_int_ioctl(struct scsi_tape *STp, unsigned int cmd_in, unsigned long arg)
static int get_location(struct scsi_tape *STp, unsigned int *block, int *partition, int logical)
static int set_location(struct scsi_tape *STp, unsigned int block, int partition, int logical)
static int find_partition(struct scsi_tape *STp)
static int switch_partition(struct scsi_tape *STp)
static int nbr_partitions(struct scsi_tape *STp)
static int format_medium(struct scsi_tape *STp, int format)
For drives that advertize SCSI-3 or newer, use the SSC-3 methods.*/ static int partition_tape(struct scsi_tape *STp, int size)
static long st_ioctl(struct file *file, unsigned int cmd_in, unsigned long arg)
static long st_compat_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
static struct st_buffer *new_tape_buffer(int need_dma, int max_sg)
static int enlarge_buffer(struct st_buffer * STbuffer, int new_size, int need_dma)
static void clear_buffer(struct st_buffer * st_bp)
static void normalize_buffer(struct st_buffer * STbuffer)
static int append_to_buffer(const char __user *ubp, struct st_buffer * st_bp, int do_count)
static int from_buffer(struct st_buffer * st_bp, char __user *ubp, int do_count)
static void move_buffer_data(struct st_buffer * st_bp, int offset)
static void validate_options(void)
static int __init st_setup(char *str)
static const struct file_operations st_fops = static int create_one_cdev(struct scsi_tape *tape, int mode, int rew)
static int create_cdevs(struct scsi_tape *tape)
static void remove_cdevs(struct scsi_tape *tape)
static int st_probe(struct device *dev)
static int st_remove(struct device *dev)
static void scsi_tape_release(struct kref *kref)
static int __init init_st(void)
static void __exit exit_st(void)
static ssize_t try_direct_io_show(struct device_driver *ddp, char *buf)
static ssize_t fixed_buffer_size_show(struct device_driver *ddp, char *buf)
static ssize_t max_sg_segs_show(struct device_driver *ddp, char *buf)
static ssize_t version_show(struct device_driver *ddd, char *buf)
static ssize_t debug_flag_store(struct device_driver *ddp, const char *buf, size_t count)
static ssize_t debug_flag_show(struct device_driver *ddp, char *buf)
static ssize_t defined_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t default_blksize_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t default_density_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t default_compression_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t options_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t read_cnt_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t read_byte_cnt_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t read_ns_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t write_cnt_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t write_byte_cnt_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t write_ns_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t in_flight_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t io_ns_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t other_cnt_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t resid_cnt_show(struct device *dev, struct device_attribute *attr, char *buf)
static int sgl_map_user_pages(struct st_buffer *STbp, const unsigned int max_pages, unsigned long uaddr, size_t count, int rw)
static int sgl_unmap_user_pages(struct st_buffer *STbp, const unsigned int nr_pages, int dirtied)
\n
     24 struct scsi_tape *STp
     20 char *buf
     17 struct device *dev
     15 struct device_attribute *attr
      8 struct file *filp
      7 struct scsi_tape * STp
      6 size_t count
      5 struct device_driver *ddp
      4 struct st_buffer * st_bp
      4 struct scsi_tape *tape
      3 void
      3 unsigned long arg
      2 unsigned int cmd_in
      2 unsigned char *cmd
      2 struct st_request * SRpnt
      2 struct st_request *SRpnt
      2 struct st_modedef * STm
      2 struct st_buffer * STbuffer
      2 struct st_buffer *STbp
      2 struct request *req
      2 struct inode *inode
      2 struct file *file
      2 loff_t * ppos
      2 int timeout
      2 int retries
      2 int page
      2 int need_dma
      2 int logical
      2 int is_read
      2 int do_wait
      2 int do_count
      2 int direction
      2 const char __user *buf
      1 void *buffer
      1 unsigned long uaddr
      1 unsigned int cmd
      1 unsigned int *block
      1 unsigned int block
      1 unsigned bufflen
      1 struct st_request *streq
      1 struct st_request ** aSRpnt
      1 struct st_cmdstatus *s
      1 struct scsi_tape *stp
      1 struct scsi_device* SDp
      1 struct kref *kref
      1 struct device_driver *ddd
      1 static void st_log_optionsstruct scsi_tape * STp
      1 long options
      1 long count
      1 int state
      1 int slow
      1 int size
      1 int seek_next
      1 int rw
      1 int rew
      1 int *partition
      1 int partition
      1 int omit_block_descs
      1 int offset
      1 int new_size
      1 int mode
      1 int max_sg
      1 int load_code
      1 int forward
      1 int format
      1 int do_lock
      1 int dirtied
      1 int dev
      1 int data_direction
      1 int bytes
      1 fl_owner_t id
      1 const unsigned int nr_pages
      1 const unsigned int max_pages
      1 const unsigned char *cmd
      1 const char __user *ubp
      1 const char *buf
      1 char __user *ubp
      1 char __user *buf
      1 char *units
      1 char *str
      1 blk_status_t status
