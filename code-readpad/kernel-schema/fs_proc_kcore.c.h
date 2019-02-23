
\n
void __init kclist_add(struct kcore_list *new, void *addr, size_t size, int type)
static size_t get_kcore_size(int *nphdr, size_t *phdrs_len, size_t *notes_len, size_t *data_offset)
static int kcore_ram_list(struct list_head *head)
static int get_sparsemem_vmemmap_info(struct kcore_list *ent, struct list_head *head)
} static int get_sparsemem_vmemmap_info(struct kcore_list *ent, struct list_head *head)
static int kclist_add_private(unsigned long pfn, unsigned long nr_pages, void *arg)
static int kcore_ram_list(struct list_head *list)
static int kcore_update_ram(void)
static void append_kcore_note(char *notes, size_t *i, const char *name, unsigned int type, const void *desc, size_t descsz)
static ssize_t read_kcore(struct file *file, char __user *buffer, size_t buflen, loff_t *fpos)
static int open_kcore(struct inode *inode, struct file *filp)
static int release_kcore(struct inode *inode, struct file *file)
static int __meminit kcore_callback(struct notifier_block *self, unsigned long action, void *arg)
static struct kcore_list kcore_text;static void __init proc_kcore_text_init(void)
static struct kcore_list kcore_text;static void __init proc_kcore_text_init(void)
kclist_add(&kcore_text, _text, _end - _text, KCORE_TEXT)
; } static void __init proc_kcore_text_init(void)
struct kcore_list kcore_modules; static void __init add_modules_range(void)
struct kcore_list kcore_modules; static void __init add_modules_range(void)
kclist_add(&kcore_modules, (void *)
MODULES_VADDR, MODULES_END - MODULES_VADDR, KCORE_VMALLOC)
;} } static void __init add_modules_range(void)
static int __init proc_kcore_init(void)
\n
      8 void
      3 struct list_head *head
      2 void *arg
      2 struct kcore_list *ent
      2 struct inode *inode
      2 struct file *file
      1 void *addr
      1 void *
      1 unsigned long pfn
      1 unsigned long nr_pages
      1 unsigned long action
      1 unsigned int type
      1 _text
      1 struct notifier_block *self
      1 struct list_head *list
      1 struct kcore_list *new
      1 struct file *filp
      1 size_t size
      1 size_t *phdrs_len
      1 size_t *notes_len
      1 size_t *i
      1 size_t descsz
      1 size_t *data_offset
      1 size_t buflen
      1 loff_t *fpos
      1 KCORE_TEXT
      1 &kcore_text
      1 &kcore_modules
      1 int type
      1 int *nphdr
      1 _end - _text
      1 const void *desc
      1 const char *name
      1 char __user *buffer
      1 char *notes
