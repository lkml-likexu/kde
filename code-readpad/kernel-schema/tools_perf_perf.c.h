
static int pager_command_config(const char *var, const char *value, void *data)
static int check_pager_config(const char *cmd)
static int browser_command_config(const char *var, const char *value, void *data)
static int check_browser_config(const char *cmd)
static void commit_pager_choice(void)
static int handle_options(const char ***argv, int *argc, int *envchanged)
static int run_builtin(struct cmd_struct *p, int argc, const char **argv)
static void handle_internal_command(int argc, const char **argv)
static void execv_dashed_external(const char **argv)
static int run_argv(int *argcp, const char ***argv)
static void pthread__block_sigwinch(void)
void pthread__unblock_sigwinch(void)
int main(int argc, const char **argv)
   4 const char **argv
   3 void
   3 int argc
   2 void *data
   2 const char *var
   2 const char *value
   2 const char *cmd
   2 const char ***argv
   1 struct cmd_struct *p
   1 int *envchanged
   1 int *argcp
   1 int *argc
