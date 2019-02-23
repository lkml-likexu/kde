
\n
define MAX_PCC_SUBSPACES 256 extern struct mbox_chan *pcc_mbox_request_channel(struct mbox_client *cl, int subspace_id)
; extern void pcc_mbox_free_channel(struct mbox_chan *chan)
; static inline struct mbox_chan *pcc_mbox_request_channel(struct mbox_client *cl, int subspace_id)
\n
      2 struct mbox_client *cl
      2 int subspace_id
      1 struct mbox_chan *chan
