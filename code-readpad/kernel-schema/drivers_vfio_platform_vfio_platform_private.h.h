
\n
define module_vfio_reset_handler(compat, reset)
\ MODULE_ALIAS("vfio-reset:" compat)
;\ static int __init reset_module_init(void)
\define module_vfio_reset_handler(compat, reset)
\ MODULE_ALIAS("vfio-reset:" compat)
;\ static int __init reset_module_init(void)
\vfio_platform_register_reset(compat, reset)
;\return 0;\ };\ static void __exit reset_module_exit(void)
\ \n
      3 void
      3 reset
      3 compat
      2 "vfio-reset:" compat
