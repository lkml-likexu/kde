
\n
struct page **ceph_get_direct_page_vector(const void __user *data, int num_pages, bool write_page)
void ceph_put_page_vector(struct page **pages, int num_pages, bool dirty)
void ceph_release_page_vector(struct page **pages, int num_pages)
struct page **ceph_alloc_page_vector(int num_pages, gfp_t flags)
int ceph_copy_user_to_page_vector(struct page **pages, const void __user *data, loff_t off, size_t len)
void ceph_copy_to_page_vector(struct page **pages, const void *data, loff_t off, size_t len)
void ceph_copy_from_page_vector(struct page **pages, void *data, loff_t off, size_t len)
void ceph_zero_page_vector_range(int off, int len, struct page **pages)
\n
      6 struct page **pages
      4 int num_pages
      3 size_t len
      3 loff_t off
      2 const void __user *data
      1 void *data
      1 int off
      1 int len
      1 gfp_t flags
      1 const void *data
      1 bool write_page
      1 bool dirty
