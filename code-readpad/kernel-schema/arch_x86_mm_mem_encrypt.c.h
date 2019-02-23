
EXPORT_SYMBOL_GPL(sev_enable_key);
\n
static void __init __sme_early_enc_dec(resource_size_t paddr, unsigned long size, bool enc)
void __init sme_early_encrypt(resource_size_t paddr, unsigned long size)
void __init sme_early_decrypt(resource_size_t paddr, unsigned long size)
static void __init __sme_early_map_unmap_mem(void *vaddr, unsigned long size, bool map)
void __init sme_unmap_bootdata(char *real_mode_data)
void __init sme_map_bootdata(char *real_mode_data)
void __init sme_early_init(void)
static void __init __set_clr_pte_enc(pte_t *kpte, int level, bool enc)
static int __init early_set_memory_enc_dec(unsigned long vaddr, unsigned long size, bool enc)
int __init early_set_memory_decrypted(unsigned long vaddr, unsigned long size)
int __init early_set_memory_encrypted(unsigned long vaddr, unsigned long size)
bool sme_active(void)
bool sev_active(void)
void __init mem_encrypt_free_decrypted_mem(void)
void __init mem_encrypt_init(void)
\n
      7 unsigned long size
      5 void
      3 unsigned long vaddr
      3 resource_size_t paddr
      3 bool enc
      2 char *real_mode_data
      1 void *vaddr
      1 sev_enable_key
      1 pte_t *kpte
      1 int level
      1 bool map
