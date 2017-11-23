
static int nommu_region_show(struct seq_file *m, struct vm_region *region)
static int nommu_region_list_show(struct seq_file *m, void *_p)
static void *nommu_region_list_start(struct seq_file *m, loff_t *_pos)
static void nommu_region_list_stop(struct seq_file *m, void *v)
static void *nommu_region_list_next(struct seq_file *m, void *v, loff_t *pos)
static int __init proc_nommu_init(void)
   5 struct seq_file *m
   2 void *v
   1 void *_p
   1 void
   1 struct vm_region *region
   1 loff_t *pos
   1 loff_t *_pos
