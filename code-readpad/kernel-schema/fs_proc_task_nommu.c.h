
void task_mem(struct seq_file *m, struct mm_struct *mm)
unsigned long task_vsize(struct mm_struct *mm)
unsigned long task_statm(struct mm_struct *mm, unsigned long *shared, unsigned long *text, unsigned long *data, unsigned long *resident)
static int is_stack(struct vm_area_struct *vma)
static int nommu_vma_show(struct seq_file *m, struct vm_area_struct *vma)
static int show_map(struct seq_file *m, void *_p)
static void *m_start(struct seq_file *m, loff_t *pos)
static void m_stop(struct seq_file *m, void *_vml)
static void *m_next(struct seq_file *m, void *_p, loff_t *pos)
static int maps_open(struct inode *inode, struct file *file, const struct seq_operations *ops)
static int map_release(struct inode *inode, struct file *file)
static int pid_maps_open(struct inode *inode, struct file *file)
   6 struct seq_file *m
   3 struct mm_struct *mm
   3 struct inode *inode
   3 struct file *file
   2 void *_p
   2 struct vm_area_struct *vma
   2 loff_t *pos
   1 void *_vml
   1 unsigned long *text
   1 unsigned long *shared
   1 unsigned long *resident
   1 unsigned long *data
   1 const struct seq_operations *ops
