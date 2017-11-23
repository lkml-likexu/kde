
static inline void flush_tce(void* tceaddr)
void tce_build(struct iommu_table *tbl, unsigned long index, unsigned int npages, unsigned long uaddr, int direction)
void tce_free(struct iommu_table *tbl, long index, unsigned int npages)
static inline unsigned int table_size_to_number_of_entries(unsigned char size)
static int tce_table_setparms(struct pci_dev *dev, struct iommu_table *tbl)
int __init build_tce_table(struct pci_dev *dev, void __iomem *bbar)
void * __init alloc_tce_table(void)
void __init free_tce_table(void *tbl)
   3 struct iommu_table *tbl
   2 unsigned int npages
   2 struct pci_dev *dev
   1 void* tceaddr
   1 void __iomem *bbar
   1 void *tbl
   1 void
   1 unsigned long uaddr
   1 unsigned long index
   1 unsigned char size
   1 long index
   1 int direction
