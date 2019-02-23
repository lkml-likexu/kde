
\n
static inline void pvr2fb_set_pal_type(unsigned int type)
static inline void pvr2fb_set_pal_entry(struct pvr2fb_par *par, unsigned int regno, unsigned int val)
static int pvr2fb_blank(int blank, struct fb_info *info)
static inline unsigned long get_line_length(int xres_virtual, int bpp)
static void set_color_bitfields(struct fb_var_screeninfo *var)
static int pvr2fb_setcolreg(unsigned int regno, unsigned int red, unsigned int green, unsigned int blue, unsigned int transp, struct fb_info *info)
static int pvr2fb_set_par(struct fb_info *info)
static int pvr2fb_check_var(struct fb_var_screeninfo *var, struct fb_info *info)
static void pvr2_update_display(struct fb_info *info)
static void pvr2_init_display(struct fb_info *info)
static void pvr2_do_blank(void)
static irqreturn_t pvr2fb_interrupt(int irq, void *dev_id)
static int pvr2_init_cable(void)
static ssize_t pvr2fb_write(struct fb_info *info, const char *buf, size_t count, loff_t *ppos)
static int pvr2fb_common_init(void)
static int __init pvr2fb_dc_init(void)
static void __exit pvr2fb_dc_exit(void)
static int pvr2fb_pci_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
static void pvr2fb_pci_remove(struct pci_dev *pdev)
static int __init pvr2fb_pci_init(void)
static void __exit pvr2fb_pci_exit(void)
static int pvr2_get_param(const struct pvr2_params *p, const char *s, int val, int size)
static int __init pvr2fb_setup(char *options)
static int __init pvr2fb_init(void)
static void __exit pvr2fb_exit(void)
\n
      9 void
      7 struct fb_info *info
      2 unsigned int regno
      2 struct pci_dev *pdev
      2 struct fb_var_screeninfo *var
      1 void *dev_id
      1 unsigned int val
      1 unsigned int type
      1 unsigned int transp
      1 unsigned int red
      1 unsigned int green
      1 unsigned int blue
      1 struct pvr2fb_par *par
      1 size_t count
      1 loff_t *ppos
      1 int xres_virtual
      1 int val
      1 int size
      1 int irq
      1 int bpp
      1 int blank
      1 const struct pvr2_params *p
      1 const struct pci_device_id *ent
      1 const char *s
      1 const char *buf
      1 char *options
