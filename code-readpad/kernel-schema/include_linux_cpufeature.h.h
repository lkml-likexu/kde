
\n
define module_cpu_feature_match(x, __initfunc)
\ static struct cpu_feature const __maybe_unused cpu_feature_match_x[] = \ MODULE_DEVICE_TABLE(cpu, cpu_feature_match_x)
;\ \ static int __init cpu_feature_match_x_init(void)
\ \n
      1 x
      1 void
      1 __initfunc
      1 cpu_feature_match_x
      1 cpu
