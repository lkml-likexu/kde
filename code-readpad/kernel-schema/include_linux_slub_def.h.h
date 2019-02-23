
\n
define SLAB_SUPPORTS_SYSFS void sysfs_slab_unlink(struct kmem_cache *)
; void sysfs_slab_release(struct kmem_cache *)
; static inline void sysfs_slab_unlink(struct kmem_cache *s)
define SLAB_SUPPORTS_SYSFS void sysfs_slab_unlink(struct kmem_cache *)
; void sysfs_slab_release(struct kmem_cache *)
; static inline void sysfs_slab_unlink(struct kmem_cache *s)
} static inline void sysfs_slab_release(struct kmem_cache *s)
\n
      4 struct kmem_cache *
      3 struct kmem_cache *s
