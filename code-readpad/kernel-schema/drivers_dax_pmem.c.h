
\n
static struct dax_pmem *to_dax_pmem(struct percpu_ref *ref)
static void dax_pmem_percpu_release(struct percpu_ref *ref)
static void dax_pmem_percpu_exit(void *data)
static void dax_pmem_percpu_kill(struct percpu_ref *ref)
static int dax_pmem_probe(struct device *dev)
\n
      3 struct percpu_ref *ref
      1 void *data
      1 struct device *dev
