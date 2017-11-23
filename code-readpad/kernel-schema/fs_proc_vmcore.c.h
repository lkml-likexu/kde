
EXPORT_SYMBOL_GPL(register_oldmem_pfn_is_ram);
EXPORT_SYMBOL_GPL(unregister_oldmem_pfn_is_ram);
int register_oldmem_pfn_is_ram(int (*fn)
(unsigned long pfn)
)
void unregister_oldmem_pfn_is_ram(void)
static int pfn_is_ram(unsigned long pfn)
static ssize_t read_from_oldmem(char *buf, size_t count, u64 *ppos, int userbuf, bool encrypted)
int __weak elfcorehdr_alloc(unsigned long long *addr, unsigned long long *size)
void __weak elfcorehdr_free(unsigned long long addr)
ssize_t __weak elfcorehdr_read(char *buf, size_t count, u64 *ppos)
ssize_t __weak elfcorehdr_read_notes(char *buf, size_t count, u64 *ppos)
int __weak remap_oldmem_pfn_range(struct vm_area_struct *vma, unsigned long from, unsigned long pfn, unsigned long size, pgprot_t prot)
ssize_t __weak copy_oldmem_page_encrypted(unsigned long pfn, char *buf, size_t csize, unsigned long offset, int userbuf)
static int copy_to(void *target, void *src, size_t size, int userbuf)
static int vmcoredd_copy_dumps(void *dst, u64 start, size_t size, int userbuf)
static int vmcoredd_mmap_dumps(struct vm_area_struct *vma, unsigned long dst, u64 start, size_t size)
static ssize_t __read_vmcore(char *buffer, size_t buflen, loff_t *fpos, int userbuf)
static ssize_t read_vmcore(struct file *file, char __user *buffer, size_t buflen, loff_t *fpos)
static vm_fault_t mmap_vmcore_fault(struct vm_fault *vmf)
static inline char *vmcore_alloc_buf(size_t size)
static int remap_oldmem_pfn_checked(struct vm_area_struct *vma, unsigned long from, unsigned long pfn, unsigned long size, pgprot_t prot)
static int vmcore_remap_oldmem_pfn(struct vm_area_struct *vma, unsigned long from, unsigned long pfn, unsigned long size, pgprot_t prot)
static int mmap_vmcore(struct file *file, struct vm_area_struct *vma)
return 0; fail:do_munmap(vma->vm_mm, vma->vm_start, len, NULL)
;return -EAGAIN; } static int mmap_vmcore(struct file *file, struct vm_area_struct *vma)
static struct vmcore* __init get_new_element(void)
static u64 get_vmcore_size(size_t elfsz, size_t elfnotesegsz, struct list_head *vc_list)
static int __init update_note_header_size_elf64(const Elf64_Ehdr *ehdr_ptr)
static int __init get_note_number_and_size_elf64(const Elf64_Ehdr *ehdr_ptr, int *nr_ptnote, u64 *sz_ptnote)
static int __init copy_notes_elf64(const Elf64_Ehdr *ehdr_ptr, char *notes_buf)
static int __init merge_note_headers_elf64(char *elfptr, size_t *elfsz, char **notes_buf, size_t *notes_sz)
static int __init update_note_header_size_elf32(const Elf32_Ehdr *ehdr_ptr)
static int __init get_note_number_and_size_elf32(const Elf32_Ehdr *ehdr_ptr, int *nr_ptnote, u64 *sz_ptnote)
static int __init copy_notes_elf32(const Elf32_Ehdr *ehdr_ptr, char *notes_buf)
static int __init merge_note_headers_elf32(char *elfptr, size_t *elfsz, char **notes_buf, size_t *notes_sz)
static int __init process_ptload_program_headers_elf64(char *elfptr, size_t elfsz, size_t elfnotes_sz, struct list_head *vc_list)
static int __init process_ptload_program_headers_elf32(char *elfptr, size_t elfsz, size_t elfnotes_sz, struct list_head *vc_list)
static void set_vmcore_list_offsets(size_t elfsz, size_t elfnotes_sz, struct list_head *vc_list)
static void free_elfcorebuf(void)
static int __init parse_crash_elf64_headers(void)
static int __init parse_crash_elf32_headers(void)
static int __init parse_crash_elf_headers(void)
static void vmcoredd_write_header(void *buf, struct vmcoredd_data *data, u32 size)
static void vmcoredd_update_program_headers(char *elfptr, size_t elfnotesz, size_t vmcoreddsz)
static void vmcoredd_update_size(size_t dump_size)
int vmcore_add_device_dump(struct vmcoredd_data *data)
static void vmcore_free_device_dumps(void)
static int __init vmcore_init(void)
void vmcore_cleanup(void)
   9 void
   6 unsigned long pfn
   6 struct vm_area_struct *vma
   5 int userbuf
   5 char *elfptr
   4 struct list_head *vc_list
   4 size_t size
   4 size_t elfsz
   4 char *buf
   3 unsigned long size
   3 unsigned long from
   3 u64 *ppos
   3 struct file *file
   3 size_t elfnotes_sz
   3 size_t count
   3 pgprot_t prot
   3 const Elf64_Ehdr *ehdr_ptr
   3 const Elf32_Ehdr *ehdr_ptr
   2 u64 start
   2 u64 *sz_ptnote
   2 struct vmcoredd_data *data
   2 size_t buflen
   2 size_t *notes_sz
   2 size_t *elfsz
   2 loff_t *fpos
   2 int *nr_ptnote
   2 char *notes_buf
   2 char **notes_buf
   1 void *target
   1 void *src
   1 void *dst
   1 void *buf
   1 vma->vm_start
   1 vma->vm_mm
   1 unsigned long offset
   1 unsigned long long addr
   1 unsigned long long *size
   1 unsigned long long *addr
   1 unsigned long dst
   1 unregister_oldmem_pfn_is_ram
   1 u32 size
   1 struct vm_fault *vmf
   1 size_t vmcoreddsz
   1 size_t elfnotesz
   1 size_t elfnotesegsz
   1 size_t dump_size
   1 size_t csize
   1 register_oldmem_pfn_is_ram
   1 len
   1 int *fn
   1 char __user *buffer
   1 char *buffer
   1 bool encrypted
   1 NULL
