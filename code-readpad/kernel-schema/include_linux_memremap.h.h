
\n
unsigned long vmem_altmap_offset(struct vmem_altmap *altmap)
; void vmem_altmap_free(struct vmem_altmap *altmap, unsigned long nr_pfns)
; static inline void *devm_memremap_pages(struct device *dev, struct dev_pagemap *pgmap)
static inline struct dev_pagemap *get_dev_pagemap(unsigned long pfn, struct dev_pagemap *pgmap)
static inline unsigned long vmem_altmap_offset(struct vmem_altmap *altmap)
static inline void vmem_altmap_free(struct vmem_altmap *altmap, unsigned long nr_pfns)
static inline void put_dev_pagemap(struct dev_pagemap *pgmap)
\n
      4 struct vmem_altmap *altmap
      3 struct dev_pagemap *pgmap
      2 unsigned long nr_pfns
      1 unsigned long pfn
      1 struct device *dev
