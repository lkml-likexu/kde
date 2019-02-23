
\n
define nodemask_pr_args(maskp)
__nodemask_pr_numnodes(maskp)
, \ __nodemask_pr_bits(maskp)
static inline unsigned int __nodemask_pr_numnodes(const nodemask_t *m)
define nodemask_pr_args(maskp)
__nodemask_pr_numnodes(maskp)
, \ __nodemask_pr_bits(maskp)
static inline unsigned int __nodemask_pr_numnodes(const nodemask_t *m)
return m ? MAX_NUMNODES : 0; } static inline const unsigned long *__nodemask_pr_bits(const nodemask_t *m)
define node_set(node, dst)
__node_set((node)
, &(dst)
)
static __always_inline void __node_set(int node, volatile nodemask_t *dstp)
define node_clear(node, dst)
__node_clear((node)
, &(dst)
)
static inline void __node_clear(int node, volatile nodemask_t *dstp)
define nodes_setall(dst)
__nodes_setall(&(dst)
, MAX_NUMNODES)
static inline void __nodes_setall(nodemask_t *dstp, unsigned int nbits)
define nodes_clear(dst)
__nodes_clear(&(dst)
, MAX_NUMNODES)
static inline void __nodes_clear(nodemask_t *dstp, unsigned int nbits)
define node_test_and_set(node, nodemask)
\__node_test_and_set((node)
, &(nodemask)
)
static inline int __node_test_and_set(int node, nodemask_t *addr)
define nodes_and(dst, src1, src2)
\__nodes_and(&(dst)
, &(src1)
, &(src2)
, MAX_NUMNODES)
static inline void __nodes_and(nodemask_t *dstp, const nodemask_t *src1p, const nodemask_t *src2p, unsigned int nbits)
define nodes_or(dst, src1, src2)
\__nodes_or(&(dst)
, &(src1)
, &(src2)
, MAX_NUMNODES)
static inline void __nodes_or(nodemask_t *dstp, const nodemask_t *src1p, const nodemask_t *src2p, unsigned int nbits)
define nodes_xor(dst, src1, src2)
\__nodes_xor(&(dst)
, &(src1)
, &(src2)
, MAX_NUMNODES)
static inline void __nodes_xor(nodemask_t *dstp, const nodemask_t *src1p, const nodemask_t *src2p, unsigned int nbits)
define nodes_andnot(dst, src1, src2)
\__nodes_andnot(&(dst)
, &(src1)
, &(src2)
, MAX_NUMNODES)
static inline void __nodes_andnot(nodemask_t *dstp, const nodemask_t *src1p, const nodemask_t *src2p, unsigned int nbits)
define nodes_complement(dst, src)
\__nodes_complement(&(dst)
, &(src)
, MAX_NUMNODES)
static inline void __nodes_complement(nodemask_t *dstp, const nodemask_t *srcp, unsigned int nbits)
define nodes_equal(src1, src2)
\__nodes_equal(&(src1)
, &(src2)
, MAX_NUMNODES)
static inline int __nodes_equal(const nodemask_t *src1p, const nodemask_t *src2p, unsigned int nbits)
define nodes_intersects(src1, src2)
\__nodes_intersects(&(src1)
, &(src2)
, MAX_NUMNODES)
static inline int __nodes_intersects(const nodemask_t *src1p, const nodemask_t *src2p, unsigned int nbits)
define nodes_subset(src1, src2)
\__nodes_subset(&(src1)
, &(src2)
, MAX_NUMNODES)
static inline int __nodes_subset(const nodemask_t *src1p, const nodemask_t *src2p, unsigned int nbits)
define nodes_empty(src)
__nodes_empty(&(src)
, MAX_NUMNODES)
static inline int __nodes_empty(const nodemask_t *srcp, unsigned int nbits)
define nodes_full(nodemask)
__nodes_full(&(nodemask)
, MAX_NUMNODES)
static inline int __nodes_full(const nodemask_t *srcp, unsigned int nbits)
define nodes_weight(nodemask)
__nodes_weight(&(nodemask)
, MAX_NUMNODES)
static inline int __nodes_weight(const nodemask_t *srcp, unsigned int nbits)
define nodes_shift_right(dst, src, n)
\__nodes_shift_right(&(dst)
, &(src)
, (n)
, MAX_NUMNODES)
static inline void __nodes_shift_right(nodemask_t *dstp, const nodemask_t *srcp, int n, int nbits)
define nodes_shift_left(dst, src, n)
\__nodes_shift_left(&(dst)
, &(src)
, (n)
, MAX_NUMNODES)
static inline void __nodes_shift_left(nodemask_t *dstp, const nodemask_t *srcp, int n, int nbits)
define first_node(src)
__first_node(&(src)
)
static inline int __first_node(const nodemask_t *srcp)
define next_node(n, src)
__next_node((n)
, &(src)
)
static inline int __next_node(int n, const nodemask_t *srcp)
static inline void init_nodemask_of_node(nodemask_t *mask, int node)
define first_unset_node(mask)
__first_unset_node(&(mask)
)
static inline int __first_unset_node(const nodemask_t *maskp)
define nodemask_parse_user(ubuf, ulen, dst)
\ __nodemask_parse_user((ubuf)
, (ulen)
, &(dst)
, MAX_NUMNODES)
static inline int __nodemask_parse_user(const char __user *buf, int len, nodemask_t *dstp, int nbits)
define nodelist_parse(buf, dst)
__nodelist_parse((buf)
, &(dst)
, MAX_NUMNODES)
static inline int __nodelist_parse(const char *buf, nodemask_t *dstp, int nbits)
define node_remap(oldbit, old, new)
\ __node_remap((oldbit)
, &(old)
, &(new)
, MAX_NUMNODES)
static inline int __node_remap(int oldbit, const nodemask_t *oldp, const nodemask_t *newp, int nbits)
define nodes_remap(dst, src, old, new)
\ __nodes_remap(&(dst)
, &(src)
, &(old)
, &(new)
, MAX_NUMNODES)
static inline void __nodes_remap(nodemask_t *dstp, const nodemask_t *srcp, const nodemask_t *oldp, const nodemask_t *newp, int nbits)
define nodes_onto(dst, orig, relmap)
\ __nodes_onto(&(dst)
, &(orig)
, &(relmap)
, MAX_NUMNODES)
static inline void __nodes_onto(nodemask_t *dstp, const nodemask_t *origp, const nodemask_t *relmapp, int nbits)
define nodes_fold(dst, orig, sz)
\ __nodes_fold(&(dst)
, &(orig)
, sz, MAX_NUMNODES)
static inline void __nodes_fold(nodemask_t *dstp, const nodemask_t *origp, int sz, int nbits)
static inline int node_state(int node, enum node_states state)
static inline void node_set_state(int node, enum node_states state)
static inline void node_clear_state(int node, enum node_states state)
static inline int num_node_state(enum node_states state)
define first_online_node first_node(node_states[N_ONLINE])
define first_memory_node first_node(node_states[N_MEMORY])
static inline int next_online_node(int nid)
define first_online_node first_node(node_states[N_ONLINE])
define first_memory_node first_node(node_states[N_MEMORY])
static inline int next_online_node(int nid)
return next_node(nid, node_states[N_ONLINE])
; } static inline int next_memory_node(int nid)
static inline void node_set_online(int nid)
static inline void node_set_offline(int nid)
static inline int node_state(int node, enum node_states state)
static inline void node_set_state(int node, enum node_states state)
static inline void node_clear_state(int node, enum node_states state)
static inline int num_node_state(enum node_states state)
extern int node_random(const nodemask_t *maskp)
; static inline int node_random(const nodemask_t *mask)
\n
     20 dst
     14 src2
     14 nodemask_t *dstp
     13 unsigned int nbits
     12 src
     12 &dst
     11 src1
     10 int node
      9 const nodemask_t *srcp
      8 int nbits
      8 enum node_states state
      7 const nodemask_t *src2p
      7 const nodemask_t *src1p
      6 node
      6 n
      6 maskp
      5 int nid
      4 orig
      4 old
      4 nodemask
      4 new
      3 &src1
      3 node_states[N_ONLINE]
      3 int n
      3 const nodemask_t *m
      2 volatile nodemask_t *dstp
      2 ulen
      2 ubuf
      2 &src
      2 relmap
      2 oldbit
      2 node_states[N_MEMORY]
      2 &nodemask
      2 const nodemask_t *origp
      2 const nodemask_t *oldp
      2 const nodemask_t *newp
      2 const nodemask_t *maskp
      2 buf
      1 sz
      1 nodemask_t *mask
      1 nodemask_t *addr
      1 nid
      1 &mask
      1 mask
      1 int sz
      1 int oldbit
      1 int len
      1 const nodemask_t *relmapp
      1 const nodemask_t *mask
      1 const char __user *buf
      1 const char *buf
