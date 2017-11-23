
void perf_env__exit(struct perf_env *env)
int perf_env__set_cmdline(struct perf_env *env, int argc, const char *argv[])
int perf_env__read_cpu_topology_map(struct perf_env *env)
static int perf_env__read_arch(struct perf_env *env)
static int perf_env__read_nr_cpus_avail(struct perf_env *env)
const char *perf_env__raw_arch(struct perf_env *env)
int perf_env__nr_cpus_avail(struct perf_env *env)
void cpu_cache_level__free(struct cpu_cache_level *cache)
static const char *normalize_arch(char *arch)
const char *perf_env__arch(struct perf_env *env)
   8 struct perf_env *env
   1 struct cpu_cache_level *cache
   1 int argc
   1 const char *argv[]
   1 char *arch
