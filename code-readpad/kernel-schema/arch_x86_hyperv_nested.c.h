
EXPORT_SYMBOL_GPL(hyperv_flush_guest_mapping);
EXPORT_SYMBOL_GPL(hyperv_fill_flush_guest_mapping_list);
EXPORT_SYMBOL_GPL(hyperv_flush_guest_mapping_range);
\n
int hyperv_flush_guest_mapping(u64 as)
int hyperv_fill_flush_guest_mapping_list( struct hv_guest_mapping_flush_list *flush, u64 start_gfn, u64 pages)
int hyperv_flush_guest_mapping_range(u64 as, hyperv_fill_flush_list_func fill_flush_list_func, void *data)
\n
      2 u64 as
      1 void *data
      1 u64 start_gfn
      1 u64 pages
      1 struct hv_guest_mapping_flush_list *flush
      1 hyperv_flush_guest_mapping_range
      1 hyperv_flush_guest_mapping
      1 hyperv_fill_flush_list_func fill_flush_list_func
      1 hyperv_fill_flush_guest_mapping_list
