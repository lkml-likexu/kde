
static bool amd_check_current_patch_level(void)
static bool __init check_loader_disabled_bsp(void)
bool get_builtin_firmware(struct cpio_data *cd, const char *name)
void __init load_ucode_bsp(void)
static bool check_loader_disabled_ap(void)
void load_ucode_ap(void)
static int __init save_microcode_in_initrd(void)
struct cpio_data find_microcode_in_initrd(const char *path, bool use_pa)
void reload_early_microcode(void)
static void collect_cpu_info_local(void *arg)
static int collect_cpu_info_on_target(int cpu, struct cpu_signature *cpu_sig)
static int collect_cpu_info(int cpu)
static void apply_microcode_local(void *arg)
static int apply_microcode_on_target(int cpu)
static int do_microcode_update(const void __user *buf, size_t size)
static int microcode_open(struct inode *inode, struct file *file)
static ssize_t microcode_write(struct file *file, const char __user *buf, size_t len, loff_t *ppos)
static int __init microcode_dev_init(void)
static void __exit microcode_dev_exit(void)
static int check_online_cpus(void)
static int __wait_for_cpus(atomic_t *t, long long timeout)
static int __reload_late(void *info)
static int microcode_reload_late(void)
static ssize_t reload_store(struct device *dev, struct device_attribute *attr, const char *buf, size_t size)
static ssize_t version_show(struct device *dev, struct device_attribute *attr, char *buf)
static ssize_t pf_show(struct device *dev, struct device_attribute *attr, char *buf)
static void microcode_fini_cpu(int cpu)
static enum ucode_state microcode_resume_cpu(int cpu)
static enum ucode_state microcode_init_cpu(int cpu, bool refresh_fw)
static enum ucode_state microcode_update_cpu(int cpu)
static int mc_device_add(struct device *dev, struct subsys_interface *sif)
static void mc_device_remove(struct device *dev, struct subsys_interface *sif)
static void mc_bp_resume(void)
static int mc_cpu_online(unsigned int cpu)
static int mc_cpu_down_prep(unsigned int cpu)
int __init microcode_init(void)
  13 void
   7 int cpu
   5 struct device *dev
   3 struct device_attribute *attr
   2 void *arg
   2 unsigned int cpu
   2 struct subsys_interface *sif
   2 struct file *file
   2 size_t size
   2 char *buf
   1 void *info
   1 struct inode *inode
   1 struct cpu_signature *cpu_sig
   1 struct cpio_data *cd
   1 size_t len
   1 long long timeout
   1 loff_t *ppos
   1 const void __user *buf
   1 const char __user *buf
   1 const char *path
   1 const char *name
   1 const char *buf
   1 bool use_pa
   1 bool refresh_fw
   1 atomic_t *t
