
\n
static void __init sme_clear_pgd(struct sme_populate_pgd_data *ppd)
static pud_t __init *sme_prepare_pgd(struct sme_populate_pgd_data *ppd)
static void __init sme_populate_pgd_large(struct sme_populate_pgd_data *ppd)
static void __init sme_populate_pgd(struct sme_populate_pgd_data *ppd)
static void __init __sme_map_range_pmd(struct sme_populate_pgd_data *ppd)
static void __init __sme_map_range_pte(struct sme_populate_pgd_data *ppd)
static void __init __sme_map_range(struct sme_populate_pgd_data *ppd, pmdval_t pmd_flags, pteval_t pte_flags)
static void __init sme_map_range_encrypted(struct sme_populate_pgd_data *ppd)
static void __init sme_map_range_decrypted(struct sme_populate_pgd_data *ppd)
static void __init sme_map_range_decrypted_wp(struct sme_populate_pgd_data *ppd)
static unsigned long __init sme_pgtable_calc(unsigned long len)
void __init sme_encrypt_kernel(struct boot_params *bp)
void __init sme_enable(struct boot_params *bp)
\n
     10 struct sme_populate_pgd_data *ppd
      2 struct boot_params *bp
      1 unsigned long len
      1 pteval_t pte_flags
      1 pmdval_t pmd_flags
