
\n
void __init init_vdso_image(const struct vdso_image *image)
static vm_fault_t vdso_fault(const struct vm_special_mapping *sm, struct vm_area_struct *vma, struct vm_fault *vmf)
static void vdso_fix_landing(const struct vdso_image *image, struct vm_area_struct *new_vma)
static int vdso_mremap(const struct vm_special_mapping *sm, struct vm_area_struct *new_vma)
static vm_fault_t vvar_fault(const struct vm_special_mapping *sm, struct vm_area_struct *vma, struct vm_fault *vmf)
static int map_vdso(const struct vdso_image *image, unsigned long addr)
static unsigned long vdso_addr(unsigned long start, unsigned len)
static int map_vdso_randomized(const struct vdso_image *image)
int map_vdso_once(const struct vdso_image *image, unsigned long addr)
static int load_vdso32(void)
int arch_setup_additional_pages(struct linux_binprm *bprm, int uses_interp)
int compat_arch_setup_additional_pages(struct linux_binprm *bprm, int uses_interp)
int compat_arch_setup_additional_pages(struct linux_binprm *bprm, int uses_interp)
if (!vdso64_enabled)
return 0; return map_vdso_randomized(&vdso_image_x32)
;}endifreturn load_vdso32()
;return 0;endif }endif int arch_setup_additional_pages(struct linux_binprm *bprm, int uses_interp)
static __init int vdso_setup(char *s)
static int __init init_vdso(void)
\n
      5 const struct vdso_image *image
      4 struct linux_binprm *bprm
      4 int uses_interp
      3 const struct vm_special_mapping *sm
      2 void
      2 unsigned long addr
      2 struct vm_fault *vmf
      2 struct vm_area_struct *vma
      2 struct vm_area_struct *new_vma
      1 &vdso_image_x32
      1 !vdso64_enabled
      1 unsigned long start
      1 unsigned len
      1 char *s
      1 
