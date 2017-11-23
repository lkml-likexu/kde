
static int mdpy_fb_setcolreg(u_int regno, u_int red, u_int green, u_int blue, u_int transp, struct fb_info *info)
static void mdpy_fb_destroy(struct fb_info *info)
static int mdpy_fb_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
static void mdpy_fb_remove(struct pci_dev *pdev)
static int __init mdpy_fb_init(void)
   2 struct pci_dev *pdev
   2 struct fb_info *info
   1 void
   1 u_int transp
   1 u_int regno
   1 u_int red
   1 u_int green
   1 u_int blue
   1 const struct pci_device_id *ent
