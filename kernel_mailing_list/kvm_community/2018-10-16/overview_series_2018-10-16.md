#### [RFC PATCH v1 1/4] VFIO KABI for migration interface
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
- Added vfio_device_migration_info structure to use interact with vendor
  driver.
- Different flags are used to get or set migration related information
  from/to vendor driver.
Flag VFIO_MIGRATION_PROBE: To query if feature is supported
Flag VFIO_MIGRATION_GET_REGION: To get migration region info
Flag VFIO_MIGRATION_SET_STATE: To convey device state in vendor driver
Flag VFIO_MIGRATION_GET_PENDING: To get pending bytes yet to be migrated
  from vendor driver
Flag VFIO_MIGRATION_GET_BUFFER: On this flag, vendor driver should write
  data to migration region and return number of bytes written in the region
Flag VFIO_MIGRATION_SET_BUFFER: In migration resume path, user space app
  writes to migration region and communicates it to vendor driver with
  this ioctl with this flag.
Flag VFIO_MIGRATION_GET_DIRTY_PFNS: Get bitmap of dirty pages from vendor
  driver from given start address

- Added enum for possible device states.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 linux-headers/linux/vfio.h | 91 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 91 insertions(+)

```
#### [PATCH] KVM: VMX: enable nested virtualization by default
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
With live migration support and finally a good solution for CR2/DR6
exception payloads, nested VMX should finally be ready for having a stable
userspace ABI.  The results of syzkaller fuzzing are not perfect but not
horrible either (and might be partially due to running on GCE, so that
effectively we're testing three-level nesting on a fork of upstream KVM!).
Enabling it by default seems like a nice way to conclude the 4.20
pull request. :)

Unfortunately, enabling nested SVM in 2009 was a bit premature.  However,
until live migration support is in place we can reasonably expect that
it does not offer much in terms of ABI guarantees.  Therefore we are
still in time to break things and conform as much as possible to the
interface used for VMX.

Suggested-by: Jim Mattson <jmattson@google.com>
Suggested-by: Liran Alon <liran.alon@oracle.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/vmx.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v6 01/13] KVM: hyperv: define VP assist page helpers
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From: Ladi Prosek <lprosek@redhat.com>

The state related to the VP assist page is still managed by the LAPIC
code in the pv_eoi field.

Signed-off-by: Ladi Prosek <lprosek@redhat.com>
Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Reviewed-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/hyperv.c | 23 +++++++++++++++++++++--
 arch/x86/kvm/hyperv.h |  4 ++++
 arch/x86/kvm/lapic.c  |  4 ++--
 arch/x86/kvm/lapic.h  |  2 +-
 arch/x86/kvm/x86.c    |  2 +-
 5 files changed, 29 insertions(+), 6 deletions(-)

```
#### [PATCH 1/4] ptr_ring: port ptr_ring from linux kernel to QEMU
##### From: guangrong.xiao@gmail.com

```c
From: Xiao Guangrong <xiaoguangrong@tencent.com>

ptr_ring is good to minimize cache-contention and has the simple model
of memory barrier which will be used by lockless threads model to pass
requests between main migration thread and compression threads

Some changes are made:
1) drop unnecessary APIs, e.g, for _irq, _bh APIs
2) the resize APIs has not been ported
3) drop the locks
4) adjust some comments
5) new API, ptr_ring_disable_batch, has been introduced

Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
---
 include/qemu/ptr_ring.h | 235 ++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 235 insertions(+)
 create mode 100644 include/qemu/ptr_ring.h

diff --git a/include/qemu/ptr_ring.h b/include/qemu/ptr_ring.h
new file mode 100644
index 0000000000..d8266d45f6
--- /dev/null
+++ b/include/qemu/ptr_ring.h
@@ -0,0 +1,235 @@
+/*
+ *    Definitions for the 'struct ptr_ring' datastructure.
+ *
+ *    Author:
+ *        Michael S. Tsirkin <mst@redhat.com>
+ *        Xiao Guangrong <xiaoguangrong@tencent.com>
+ *
+ *    Copyright (C) 2018 Red Hat, Inc.
+ *    Copyright (C) 2018 Tencent, Inc.
+ *
+ *    This program is free software; you can redistribute it and/or modify it
+ *    under the terms of the GNU General Public License as published by the
+ *    Free Software Foundation; either version 2 of the License, or (at your
+ *    option) any later version.
+ *
+ *    This is a limited-size FIFO maintaining pointers in FIFO order, with
+ *    one CPU producing entries and another consuming entries from a FIFO.
+ *
+ *    This implementation tries to minimize cache-contention when there is a
+ *    single producer and a single consumer CPU.
+ */
+
+#ifndef _QEMU_PTR_RING_H
+#define _QEMU_PTR_RING_H 1
+
+#include "qemu/compiler.h"
+#include "qemu/atomic.h"
+
+#define SMP_CACHE_BYTES      64
+#define ____cacheline_aligned_in_smp \
+        __attribute__((__aligned__(SMP_CACHE_BYTES)))
+
+#define WRITE_ONCE(ptr, val) \
+    (*((volatile typeof(ptr) *)(&(ptr))) = (val))
+#define READ_ONCE(ptr) (*((volatile typeof(ptr) *)(&(ptr))))
+
+struct ptr_ring {
+    int producer ____cacheline_aligned_in_smp;
+    int consumer_head ____cacheline_aligned_in_smp; /* next valid entry */
+    int consumer_tail; /* next entry to invalidate */
+    /* Shared consumer/producer data */
+    /* Read-only by both the producer and the consumer */
+    int size ____cacheline_aligned_in_smp; /* max entries in queue */
+    int batch; /* number of entries to consume in a batch */
+    void **queue;
+};
+typedef struct ptr_ring Ptr_Ring;
+
+/*
+ * Note: callers invoking this in a loop must use a compiler barrier,
+ * for example cpu_relax().
+ */
+static inline bool ptr_ring_full(struct ptr_ring *r)
+{
+    return r->queue[r->producer];
+}
+
+/*
+ * Note: callers invoking this in a loop must use a compiler barrier,
+ * for example cpu_relax().
+ *
+ * Callers are responsible for making sure pointer that is being queued
+ * points to a valid data.
+ */
+static inline int ptr_ring_produce(struct ptr_ring *r, void *ptr)
+{
+    if (unlikely(!r->size) || r->queue[r->producer])
+        return -ENOSPC;
+
+    /* Make sure the pointer we are storing points to a valid data. */
+    /* Pairs with READ_ONCE in ptr_ring_consume. */
+    smp_wmb();
+
+    WRITE_ONCE(r->queue[r->producer++], ptr);
+    if (unlikely(r->producer >= r->size))
+        r->producer = 0;
+    return 0;
+}
+
+static inline void *__ptr_ring_peek(struct ptr_ring *r)
+{
+    if (likely(r->size))
+        return READ_ONCE(r->queue[r->consumer_head]);
+    return NULL;
+}
+
+/*
+ * Test ring empty status.
+ *
+ * However, if some other CPU consumes ring entries at the same time,
+ * the value returned is not guaranteed to be correct.
+ *
+ * In this case - to avoid incorrectly detecting the ring
+ * as empty - the CPU consuming the ring entries is responsible
+ * for either consuming all ring entries until the ring is empty,
+ * or synchronizing with some other CPU and causing it to
+ * re-test ptr_ring_empty and/or consume the ring enteries
+ * after the synchronization point.
+ *
+ * Note: callers invoking this in a loop must use a compiler barrier,
+ * for example cpu_relax().
+ */
+static inline bool ptr_ring_empty(struct ptr_ring *r)
+{
+    if (likely(r->size))
+        return !r->queue[READ_ONCE(r->consumer_head)];
+    return true;
+}
+
+/* Must only be called after __ptr_ring_peek returned !NULL */
+static inline void __ptr_ring_discard_one(struct ptr_ring *r)
+{
+    /* Fundamentally, what we want to do is update consumer
+     * index and zero out the entry so producer can reuse it.
+     * Doing it naively at each consume would be as simple as:
+     *       consumer = r->consumer;
+     *       r->queue[consumer++] = NULL;
+     *       if (unlikely(consumer >= r->size))
+     *               consumer = 0;
+     *       r->consumer = consumer;
+     * but that is suboptimal when the ring is full as producer is writing
+     * out new entries in the same cache line.  Defer these updates until a
+     * batch of entries has been consumed.
+     */
+    /* Note: we must keep consumer_head valid at all times for ptr_ring_empty
+     * to work correctly.
+     */
+    int consumer_head = r->consumer_head;
+    int head = consumer_head++;
+
+    /* Once we have processed enough entries invalidate them in
+     * the ring all at once so producer can reuse their space in the ring.
+     * We also do this when we reach end of the ring - not mandatory
+     * but helps keep the implementation simple.
+     */
+    if (unlikely(consumer_head - r->consumer_tail >= r->batch ||
+             consumer_head >= r->size)) {
+        /* Zero out entries in the reverse order: this way we touch the
+         * cache line that producer might currently be reading the last;
+         * producer won't make progress and touch other cache lines
+         * besides the first one until we write out all entries.
+         */
+        while (likely(head >= r->consumer_tail))
+            r->queue[head--] = NULL;
+        r->consumer_tail = consumer_head;
+    }
+    if (unlikely(consumer_head >= r->size)) {
+        consumer_head = 0;
+        r->consumer_tail = 0;
+    }
+    /* matching READ_ONCE in ptr_ring_empty for lockless tests */
+    WRITE_ONCE(r->consumer_head, consumer_head);
+}
+
+static inline void *ptr_ring_consume(struct ptr_ring *r)
+{
+    void *ptr;
+
+    /* The READ_ONCE in __ptr_ring_peek guarantees that anyone
+     * accessing data through the pointer is up to date. Pairs
+     * with smp_wmb in ptr_ring_produce.
+     */
+    ptr = __ptr_ring_peek(r);
+    if (ptr)
+        __ptr_ring_discard_one(r);
+
+    return ptr;
+}
+
+static inline int ptr_ring_consume_batched(struct ptr_ring *r,
+                         void **array, int n)
+{
+    void *ptr;
+    int i;
+
+    for (i = 0; i < n; i++) {
+        ptr = ptr_ring_consume(r);
+        if (!ptr)
+            break;
+        array[i] = ptr;
+    }
+
+    return i;
+}
+
+static inline void **__ptr_ring_init_queue_alloc(unsigned int size)
+{
+    return g_try_malloc0_n(size, sizeof(void *));
+}
+
+static inline void __ptr_ring_set_size(struct ptr_ring *r, int size)
+{
+    r->size = size;
+    r->batch = SMP_CACHE_BYTES * 2 / sizeof(*(r->queue));
+    /* We need to set batch at least to 1 to make logic
+     * in __ptr_ring_discard_one work correctly.
+     * Batching too much (because ring is small) would cause a lot of
+     * burstiness. Needs tuning, for now disable batching.
+     */
+    if (r->batch > r->size / 2 || !r->batch)
+        r->batch = 1;
+}
+
+/*
+ * Disable batching so that there is no consumered entry in the ring.
+ *
+ * It is convenient if it makes sure that the ring is large enough to
+ * contain all requests, i.e, ptr_ring_produce can not fail.
+ */
+static inline void ptr_ring_disable_batch(struct ptr_ring *r)
+{
+    r->batch = 1;
+}
+
+static inline int ptr_ring_init(struct ptr_ring *r, int size)
+{
+    r->queue = __ptr_ring_init_queue_alloc(size);
+    if (!r->queue)
+        return -ENOMEM;
+
+    __ptr_ring_set_size(r, size);
+    r->producer = r->consumer_head = r->consumer_tail = 0;
+    return 0;
+}
+
+static inline void ptr_ring_cleanup(struct ptr_ring *r, void (*destroy)(void *))
+{
+    void *ptr;
+
+    if (destroy)
+        while ((ptr = ptr_ring_consume(r)))
+            destroy(ptr);
+    g_free(r->queue);
+}
+#endif

From patchwork Tue Oct 16 11:10:04 2018
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Xiao Guangrong <guangrong.xiao@gmail.com>
X-Patchwork-Id: 10643433
Return-Path: <kvm-owner@kernel.org>
Received: from mail.wl.linuxfoundation.org (pdx-wl-mail.web.codeaurora.org
 [172.30.200.125])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9981A13AD
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Oct 2018 11:10:27 +0000 (UTC)
Received: from mail.wl.linuxfoundation.org (localhost [127.0.0.1])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 714CA2987D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Oct 2018 11:10:27 +0000 (UTC)
Received: by mail.wl.linuxfoundation.org (Postfix, from userid 486)
	id 6579029883; Tue, 16 Oct 2018 11:10:27 +0000 (UTC)
X-Spam-Checker-Version: SpamAssassin 3.3.1 (2010-03-16) on
	pdx-wl-mail.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-8.0 required=2.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FROM,MAILING_LIST_MULTI,RCVD_IN_DNSWL_HI
	autolearn=ham version=3.3.1
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.wl.linuxfoundation.org (Postfix) with ESMTP id 6B05A2987D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 16 Oct 2018 11:10:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727157AbeJPTAU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 16 Oct 2018 15:00:20 -0400
Received: from mail-pf1-f195.google.com ([209.85.210.195]:42171 "EHLO
        mail-pf1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727155AbeJPTAT (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 16 Oct 2018 15:00:19 -0400
Received: by mail-pf1-f195.google.com with SMTP id f26-v6so11280263pfn.9
        for <kvm@vger.kernel.org>; Tue, 16 Oct 2018 04:10:24 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=tB7Ty9oQ2GaY9HnWrswi6LHJqfKiDo0AC2wzD0+POHc=;
        b=XCCOsY9FaX7PbQAD+iX1DDs5369X6zHSa9XVFft9el1/fvcW2Yxne7ZPKHWwvqW1Il
         2eTjbEr6XC34sT3CVCTWNIv8CHBaDRAN1D1O1LXNx5o9AHKwIdh/cekB8NsmaJNiUe7q
         L7QLsK+V6xrF29cboipFXNAgl7+kkiWRDhJfP2/YK5zxNhBVhQ8B1d8JcC9USEP6WRsD
         uPC31K5+yy0ylKqJ/A4CUo42Zogt0AcC3673noFmPffzGAwJ8EbbaK40Ja/PvylBZWcG
         bwPw+eJI66bLsnFdp4IUOE5m1LAgY1W8kbiRfIqWucZ1kQjb5wvX40jLurvpzonE0qYQ
         mH9Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=tB7Ty9oQ2GaY9HnWrswi6LHJqfKiDo0AC2wzD0+POHc=;
        b=aQk6O7VDbleHjoN2wmSL70olnFDUQVLrmTmhJ2bfrkfNWfZxIm0EFrpB7prDdxYnFx
         i8GN+jRUkaN9PE1mybxTDODs+cxk87epzAzWv/AGJHF/lzs7ocbL4pGIaQ49f6uUe+vc
         AWf2jxQu6AuRwAaBeFE7JpTZ5+AW1QZohcFDbzeUwOI7ctkNPZSewg0e6gyVxtPfHyzH
         VYkxNShyGMgXSv7AvIo6A3t0/3Xg4pRhY6lu1sxX4Is1ztcARatgp7ejPCyWsCh8FjTB
         8Ekabuhak69tcxUOdFSOoOszo+UlHUXirT9WaAbmMTFxuVi1oOhSSHCWb/ACBYRMkFqc
         wAmQ==
X-Gm-Message-State: ABuFfojyP3GCBmrmgDCLAgyLciQDM2WQi3n/zIE76pKc8dsPJoo1bzCG
        /phBPAq1VraHe2ceIu04rbc=
X-Google-Smtp-Source: 
 ACcGV63VvVB60dxegf70vEULFS6mUUXZeOCUo16rd/bZhH9IYJdGLRWx9o8uIM4uQWofjmA/ephdnA==
X-Received: by 2002:a63:fb09:: with SMTP id
 o9-v6mr19844971pgh.333.1539688223645;
        Tue, 16 Oct 2018 04:10:23 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.40])
        by smtp.gmail.com with ESMTPSA id
 p24-v6sm18054927pgm.70.2018.10.16.04.10.19
        (version=TLS1_2 cipher=ECDHE-RSA-CHACHA20-POLY1305 bits=256/256);
        Tue, 16 Oct 2018 04:10:23 -0700 (PDT)
From: guangrong.xiao@gmail.com
X-Google-Original-From: xiaoguangrong@tencent.com
To: pbonzini@redhat.com, mst@redhat.com, mtosatti@redhat.com
Cc: qemu-devel@nongnu.org, kvm@vger.kernel.org, dgilbert@redhat.com,
        peterx@redhat.com, wei.w.wang@intel.com, jiang.biao2@zte.com.cn,
        eblake@redhat.com, quintela@redhat.com,
        Xiao Guangrong <xiaoguangrong@tencent.com>
Subject: [PATCH 2/4] migration: introduce lockless multithreads model
Date: Tue, 16 Oct 2018 19:10:04 +0800
Message-Id: <20181016111006.629-3-xiaoguangrong@tencent.com>
X-Mailer: git-send-email 2.14.4
In-Reply-To: <20181016111006.629-1-xiaoguangrong@tencent.com>
References: <20181016111006.629-1-xiaoguangrong@tencent.com>
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org
X-Virus-Scanned: ClamAV using ClamSMTP

From: Xiao Guangrong <xiaoguangrong@tencent.com>

Current implementation of compression and decompression are very
hard to be enabled on productions. We noticed that too many wait-wakes
go to kernel space and CPU usages are very low even if the system
is really free

The reasons are:
1) there are two many locks used to do synchronous，there
　　is a global lock and each single thread has its own lock,
　　migration thread and work threads need to go to sleep if
　　these locks are busy

2) migration thread separately submits request to the thread
   however, only one request can be pended, that means, the
   thread has to go to sleep after finishing the request

To make it work better, we introduce a lockless multithread model,
the user, currently it is the migration thread, submits request
to each thread which has its own ring whose capacity is 4 and
puts the result to a global ring where the user fetches result
out and do remaining operations for the request, e.g, posting the
compressed data out for migration on the source QEMU

Signed-off-by: Xiao Guangrong <xiaoguangrong@tencent.com>
---
 include/qemu/lockless-threads.h |  63 +++++++
 util/Makefile.objs              |   1 +
 util/lockless-threads.c         | 373 ++++++++++++++++++++++++++++++++++++++++
 3 files changed, 437 insertions(+)
 create mode 100644 include/qemu/lockless-threads.h
 create mode 100644 util/lockless-threads.c

diff --git a/include/qemu/lockless-threads.h b/include/qemu/lockless-threads.h
new file mode 100644
index 0000000000..9340d3a748
--- /dev/null
+++ b/include/qemu/lockless-threads.h
@@ -0,0 +1,63 @@
+/*
+ * Lockless Multithreads Abstraction
+ *
+ * This is the abstraction layer for lockless multithreads management.
+ *
+ * Note: currently only one producer is allowed.
+ *
+ * Copyright(C) 2018 Tencent Corporation.
+ *
+ * Author:
+ *   Xiao Guangrong <xiaoguangrong@tencent.com>
+ *
+ * This work is licensed under the terms of the GNU LGPL, version 2.1 or later.
+ * See the COPYING.LIB file in the top-level directory.
+ */
+
+#ifndef QEMU_LOCKLESS_THREAD_H
+#define QEMU_LOCKLESS_THREAD_H
+
+#include "qemu/queue.h"
+#include "qemu/thread.h"
+#include "qemu/ptr_ring.h"
+
+/*
+ * the request representation which contains the internally used mete data,
+ * it can be embedded to user's self-defined data struct and the user can
+ * use container_of() to get the self-defined data
+ */
+struct ThreadRequest {
+    QSLIST_ENTRY(ThreadRequest) node;
+    unsigned int thread_index;
+};
+typedef struct ThreadRequest ThreadRequest;
+
+typedef struct Threads Threads;
+
+/* the size of thread local request ring on default */
+#define DEFAULT_THREAD_RING_SIZE 4
+
+Threads *threads_create(unsigned int threads_nr, const char *name,
+                        int thread_ring_size,
+                        ThreadRequest *(*thread_request_init)(void),
+                        void (*thread_request_uninit)(ThreadRequest *request),
+                        void (*thread_request_handler)(ThreadRequest *request),
+                        void (*thread_request_done)(ThreadRequest *request));
+void threads_destroy(Threads *threads);
+
+/*
+ * find a free request and associate it with a free thread.
+ * If no request or no thread is free, return NULL
+ */
+ThreadRequest *threads_submit_request_prepare(Threads *threads);
+/*
+ * push the request to its thread's local ring and notify the thread
+ */
+void threads_submit_request_commit(Threads *threads, ThreadRequest *request);
+
+/*
+ * wait all threads to complete the request filled in their local rings
+ * to make sure there is no previous request exists.
+ */
+void threads_wait_done(Threads *threads);
+#endif
```
#### [PATCH v2 1/7] KVM: Documentation: Fix omission in struct kvm_vcpu_events
##### From: Jim Mattson <jmattson@google.com>

```c
The header file indicates that there are 36 reserved bytes at the end
of this structure. Adjust the documentation to agree with the header
file.

Signed-off-by: Jim Mattson <jmattson@google.com>
---
 Documentation/virtual/kvm/api.txt | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v2]  kvm:x86 :remove unnecessary recalculate_apic_map
##### From: Peng Hao <peng.hao2@zte.com.cn>

```c
In the previous code, the variable sw_apic_disabled influences
recalculate_apic_map. But in "KVM: x86: simplify kvm_apic_map"
(commit:3b5a5ffa928a3f875b0d5dd284eeb7c322e1688a),
the access to sw_apic_disabled in recalculate_apic_map has been
deleted.

Signed-off-by: Peng Hao <peng.hao2@zte.com.cn>
---
 arch/x86/kvm/lapic.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH v4 4.4 1/4] KVM: x86: remove eager_fpu field of struct kvm_vcpu_arch
##### From: Daniel Sangorrin <daniel.sangorrin@toshiba.co.jp>

```c
From: Paolo Bonzini <pbonzini@redhat.com>

commit 5a5fbdc0e3f1159a734f1890da60fce70e98271d upstream.

It is now equal to use_eager_fpu(), which simply tests a cpufeature bit.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Daniel Sangorrin <daniel.sangorrin@toshiba.co.jp>
---
 arch/x86/include/asm/kvm_host.h | 1 -
 arch/x86/kvm/cpuid.c            | 3 +--
 arch/x86/kvm/x86.c              | 2 +-
 3 files changed, 2 insertions(+), 4 deletions(-)

```
