
\n
static int vfio_user_config_read(struct pci_dev *pdev, int offset, __le32 *val, int count)
static int vfio_user_config_write(struct pci_dev *pdev, int offset, __le32 val, int count)
static int vfio_default_config_read(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 *val)
static int vfio_default_config_write(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 val)
static int vfio_direct_config_read(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 *val)
static int vfio_raw_config_write(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 val)
static int vfio_raw_config_read(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 *val)
static int vfio_virt_config_write(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 val)
static int vfio_virt_config_read(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 *val)
static void free_perm_bits(struct perm_bits *perm)
static int alloc_perm_bits(struct perm_bits *perm, int size)
static inline void p_setb(struct perm_bits *p, int off, u8 virt, u8 write)
static inline void p_setw(struct perm_bits *p, int off, u16 virt, u16 write)
static inline void p_setd(struct perm_bits *p, int off, u32 virt, u32 write)
static void vfio_bar_restore(struct vfio_pci_device *vdev)
static __le32 vfio_generate_bar_flags(struct pci_dev *pdev, int bar)
static void vfio_bar_fixup(struct vfio_pci_device *vdev)
static int vfio_basic_config_read(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 *val)
static bool vfio_need_bar_restore(struct vfio_pci_device *vdev)
static int vfio_basic_config_write(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 val)
static int __init init_pci_cap_basic_perm(struct perm_bits *perm)
static int vfio_pm_config_write(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 val)
static int __init init_pci_cap_pm_perm(struct perm_bits *perm)
static int vfio_vpd_config_write(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 val)
static int __init init_pci_cap_vpd_perm(struct perm_bits *perm)
static int __init init_pci_cap_pcix_perm(struct perm_bits *perm)
static int vfio_exp_config_write(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 val)
static int __init init_pci_cap_exp_perm(struct perm_bits *perm)
static int vfio_af_config_write(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 val)
static int __init init_pci_cap_af_perm(struct perm_bits *perm)
static int __init init_pci_ext_cap_err_perm(struct perm_bits *perm)
static int __init init_pci_ext_cap_pwr_perm(struct perm_bits *perm)
void vfio_pci_uninit_perm_bits(void)
int __init vfio_pci_init_perm_bits(void)
static int vfio_find_cap_start(struct vfio_pci_device *vdev, int pos)
static int vfio_msi_config_read(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 *val)
static int vfio_msi_config_write(struct vfio_pci_device *vdev, int pos, int count, struct perm_bits *perm, int offset, __le32 val)
static int init_pci_cap_msi_perm(struct perm_bits *perm, int len, u16 flags)
static int vfio_msi_cap_len(struct vfio_pci_device *vdev, u8 pos)
static int vfio_vc_cap_len(struct vfio_pci_device *vdev, u16 pos)
static int vfio_cap_len(struct vfio_pci_device *vdev, u8 cap, u8 pos)
static int vfio_ext_cap_len(struct vfio_pci_device *vdev, u16 ecap, u16 epos)
static int vfio_fill_vconfig_bytes(struct vfio_pci_device *vdev, int offset, int size)
static int vfio_cap_init(struct vfio_pci_device *vdev)
static int vfio_ecap_init(struct vfio_pci_device *vdev)
int vfio_config_init(struct vfio_pci_device *vdev)
void vfio_config_free(struct vfio_pci_device *vdev)
static size_t vfio_pci_cap_remaining_dword(struct vfio_pci_device *vdev, loff_t pos)
static ssize_t vfio_config_do_rw(struct vfio_pci_device *vdev, char __user *buf, size_t count, loff_t *ppos, bool iswrite)
ssize_t vfio_pci_config_rw(struct vfio_pci_device *vdev, char __user *buf, size_t count, loff_t *ppos, bool iswrite)
\n
     31 struct vfio_pci_device *vdev
     26 struct perm_bits *perm
     18 int offset
     17 int count
     16 int pos
     10 __le32 val
      7 __le32 *val
      3 struct perm_bits *p
      3 struct pci_dev *pdev
      3 int off
      2 void
      2 u8 pos
      2 size_t count
      2 loff_t *ppos
      2 int size
      2 char __user *buf
      2 bool iswrite
      1 u8 write
      1 u8 virt
      1 u8 cap
      1 u32 write
      1 u32 virt
      1 u16 write
      1 u16 virt
      1 u16 pos
      1 u16 flags
      1 u16 epos
      1 u16 ecap
      1 loff_t pos
      1 int len
      1 int bar
