#### [RFC PATCH 1/7] core/metricfs: Create metricfs, standardized files under debugfs.
##### From: Jonathan Adams <jwadams@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jonathan Adams <jwadams@google.com>
X-Patchwork-Id: 11702617
Return-Path: <SRS0=LWg4=BQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C1D4813B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 00:15:54 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9D16522CA1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 00:15:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="d39Oca8G"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726967AbgHFAPy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 5 Aug 2020 20:15:54 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59748 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726055AbgHFAOl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 5 Aug 2020 20:14:41 -0400
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 92A6DC061756
        for <kvm@vger.kernel.org>; Wed,  5 Aug 2020 17:14:40 -0700 (PDT)
Received: by mail-yb1-xb4a.google.com with SMTP id u12so59228846ybj.0
        for <kvm@vger.kernel.org>; Wed, 05 Aug 2020 17:14:40 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=DZ1XcM0cED77A7RVE0g/4nios57x9MDZZ5ZxcwQdk5E=;
        b=d39Oca8GLwY/taEyHsrYci5hopwIgVz3lI2VqwjKa7ia0hXojydxvLLj6YggcSdWA3
         pWaS+v1Y2OqdqM5nBG4aGQaDHsrkqbzonppEFnYCpcb9IK0KBkXldn2uuIEZ51wr94Xh
         YE86hBshzcB/QYncQyOqxX6iojeGrdCSObOjPBKKYDf+V0X4x+KsWexUO1d0jY4nTKLy
         PIWn/HS87AlmB24P92EjYK8BtjoLpR0HEI/x0Tr9lveBguilqoIw8QsCdtNYZl12ACIf
         TaxGXLwN7nyUpt25pAcCe/35hhvapsgyHWiIsPmM/S/IRRhtVOlMT0WQhb7KS4zABdiI
         cCwQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=DZ1XcM0cED77A7RVE0g/4nios57x9MDZZ5ZxcwQdk5E=;
        b=LRfKxgzFZNo5JQNovEF6WPI/J2kEYp38C3/8PLU6cukJ19sPRMvAnY3H1QQErrbSEU
         Y+zIGEaCxROErqHlAD1RLRtgm6riGbu5g2NvD6ydFWiw8++byXoQyXamX2102JZG0Afr
         RrJTQksq6mkJIVj4GlmDXVgEoCTcyGI3+RXmKnKNmC1DiqfTUTJauABX3um9GuVuPe+L
         t6hdqtk+hPrT5DXmtiK+ciXksB93rmVvRapQnlSuTJSnB7TGsS80bwD7CPLLaRQpUkst
         4bt9SE19MDGTQLcms9F00KCinBRcBCyC3eP8lOlFcp8hc7r9Z2hyXpdqj86ZSR63mpl/
         c+Xw==
X-Gm-Message-State: AOAM5328c6pHiVkF833dqzuCn/YYnd2cG1HEYMiCZsVXAMW8yQROK8iQ
        ksICeLk0DdxEyP0FKSvNxZ/iddN+r9E=
X-Google-Smtp-Source: 
 ABdhPJynycbJ8lqzCXeXENKul7VgqmZfOYFB+Wt+eDtT6YBRqqzEo0qUK42X2xdQXNVeOJPBKSHCWVww3Xgf
X-Received: by 2002:a25:61c7:: with SMTP id
 v190mr8185995ybb.168.1596672879787;
 Wed, 05 Aug 2020 17:14:39 -0700 (PDT)
Date: Wed,  5 Aug 2020 17:14:25 -0700
In-Reply-To: <20200806001431.2072150-1-jwadams@google.com>
Message-Id: <20200806001431.2072150-2-jwadams@google.com>
Mime-Version: 1.0
References: <20200806001431.2072150-1-jwadams@google.com>
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [RFC PATCH 1/7] core/metricfs: Create metricfs, standardized files
 under debugfs.
From: Jonathan Adams <jwadams@google.com>
To: linux-kernel@vger.kernel.org
Cc: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        David Rientjes <rientjes@google.com>,
        Jonathan Adams <jwadams@google.com>,
        Justin TerAvest <teravest@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Justin TerAvest <teravest@google.com>

Metricfs is a standardized set of files and directories under debugfs,
with a kernel API designed to be simpler than exporting new files under
sysfs. Type and field information is reported so that a userspace daemon
can easily process the information.

The statistics live under debugfs, in a tree rooted at:

	/sys/kernel/debug/metricfs

Each metric is a directory, with four files in it.  This patch includes
a single "metricfs_presence" metric, whose files look like:
/sys/kernel/debug/metricfs:
 metricfs_presence/annotations
  DESCRIPTION A\ basic\ presence\ metric.
 metricfs_presence/fields
  value
  int
 metricfs_presence/values
  1
 metricfs_presence/version
  1

Statistics can have zero, one, or two 'fields', which are keys for the
table of metric values.  With no fields, you have a simple statistic as
above, with one field you have a 1-dimensional table of string -> value,
and with two fields you have a 2-dimensional table of
{string, string} -> value.

When a statistic's 'values' file is opened, we pre-allocate a 64k buffer
and call the statistic's callback to fill it with data, truncating if
the buffer overflows.

Statistic creators can create a hierarchy for their statistics using
metricfs_create_subsys().

Signed-off-by: Justin TerAvest <teravest@google.com>
[jwadams@google.com: Forward ported to v5.8, cleaned up and modernized
	code significantly]
Signed-off-by: Jonathan Adams <jwadams@google.com>
---

notes:
* To go upstream, this will need documentation and a MAINTAINERS update.
* It's not clear what the "version" file is for; it's vestigial and
should probably be removed.

jwadams@google.com: Forward ported to v5.8, removed some google-isms and
    cleaned up some anachronisms (atomic->refcount, moving to
    kvmalloc(), using POISON_POINTER_DELTA, made more functions static,
    made 'emitter_fn' into an explicit union instead of a void *),
    renamed 'struct emitter -> metric_emitter' and renamed
    some funcs for consistency.
---
 include/linux/metricfs.h   | 103 ++++++
 kernel/Makefile            |   2 +
 kernel/metricfs.c          | 727 +++++++++++++++++++++++++++++++++++++
 kernel/metricfs_examples.c | 151 ++++++++
 lib/Kconfig.debug          |  18 +
 5 files changed, 1001 insertions(+)
 create mode 100644 include/linux/metricfs.h
 create mode 100644 kernel/metricfs.c
 create mode 100644 kernel/metricfs_examples.c

diff --git a/include/linux/metricfs.h b/include/linux/metricfs.h
new file mode 100644
index 000000000000..65a1baa8e8c1
--- /dev/null
+++ b/include/linux/metricfs.h
@@ -0,0 +1,103 @@
+/* SPDX-License-Identifier: GPL-2.0 */
+#ifndef _METRICFS_H_
+#define _METRICFS_H_
+
+#include <linux/kernel.h>
+#include <linux/module.h>
+#include <linux/stringify.h>
+
+struct metric;
+struct metricfs_subsys;
+
+#define METRIC_EXPORT_GENERIC(name, desc, fname0, fname1, fn, is_str, cumulative) \
+static struct metric *metric_##name; \
+void metric_init_##name(struct metricfs_subsys *parent) \
+{ \
+	metric_##name = metric_register(__stringify(name), (parent), (desc), \
+					(fname0), (fname1), (fn), (is_str), \
+					(cumulative), THIS_MODULE); \
+} \
+void metric_exit_##name(void) \
+{ \
+	metric_unregister(metric_##name); \
+}
+
+/*
+ * Metricfs only deals with two types: int64_t and const char*.
+ *
+ * If a metric has fewer than two fields, pass NULL for the field name
+ * arguments.
+ *
+ * The metric does not take ownership of any of the strings passed in.
+ *
+ * See kernel/metricfs_examples.c for a set of example metrics, with
+ * corresponding output.
+ *
+ * METRIC_EXPORT_INT - An integer-valued metric.
+ * METRIC_EXPORT_COUNTER - An integer-valued cumulative metric.
+ * METRIC_EXPORT_STR - A string-valued metric.
+ */
+#define METRIC_EXPORT_INT(name, desc, fname0, fname1, fn) \
+	METRIC_EXPORT_GENERIC(name, (desc), (fname0), (fname1), (fn), \
+				false, false)
+#define METRIC_EXPORT_COUNTER(name, desc, fname0, fname1, fn) \
+	METRIC_EXPORT_GENERIC(name, (desc), (fname0), (fname1), (fn), \
+				false, true)
+#define METRIC_EXPORT_STR(name, desc, fname0, fname1, fn) \
+	METRIC_EXPORT_GENERIC(name, (desc), (fname0), (fname1), (fn), \
+				true, false)
+
+/* Subsystem support. */
+/* Pass NULL as 'parent' to create a new top-level subsystem. */
+struct metricfs_subsys *metricfs_create_subsys(const char *name,
+						struct metricfs_subsys *parent);
+void metricfs_destroy_subsys(struct metricfs_subsys *d);
+
+/*
+ * An opaque struct that metric emit functions use to keep our internal
+ * state.
+ */
+struct metric_emitter;
+
+/* The number of non-NULL arguments passed to EMIT macros must match the number
+ * of arguments passed to the EXPORT macro for a given metric.
+ *
+ * Failure to do so will cause data to be mangled (or dropped) by userspace or
+ * Monarch.
+ */
+#define METRIC_EMIT_INT(e, v, f0, f1) \
+	metric_emit_int_value((e), (v), (f0), (f1))
+#define METRIC_EMIT_STR(e, v, f0, f1) \
+	metric_emit_str_value((e), (v), (f0), (f1))
+
+/* Users don't have to call any functions below;
+ * use the macro definitions above instead.
+ */
+void metric_emit_int_value(struct metric_emitter *e,
+			   int64_t v, const char *f0, const char *f1);
+void metric_emit_str_value(struct metric_emitter *e,
+			   const char *v, const char *f0, const char *f1);
+
+struct metric *metric_register(const char *name,
+			       struct metricfs_subsys *parent,
+			       const char *description,
+			       const char *fname0, const char *fname1,
+			       void (*fn)(struct metric_emitter *e),
+			       bool is_string,
+			       bool is_cumulative,
+			       struct module *owner);
+
+struct metric *metric_register_parm(const char *name,
+				    struct metricfs_subsys *parent,
+			  const char *description,
+				    const char *fname0, const char *fname1,
+				    void (*fn)(struct metric_emitter *e,
+					       void *parm),
+				    void *parm,
+				    bool is_string,
+				    bool is_cumulative,
+				    struct module *owner);
+
+void metric_unregister(struct metric *m);
+
+#endif /* _METRICFS_H_ */
```
#### [PATCH v3 1/4] kvm: x86: encapsulate wrmsr(MSR_KVM_SYSTEM_TIME) emulation in helper fn
##### From: Oliver Upton <oupton@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Oliver Upton <oupton@google.com>
X-Patchwork-Id: 11703783
Return-Path: <SRS0=LWg4=BQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3D82D138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 17:53:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A1C99221E5
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 17:53:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="gUQ8RY84"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729691AbgHFRxb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Aug 2020 13:53:31 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:40174 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727942AbgHFQbD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Aug 2020 12:31:03 -0400
Received: from mail-pg1-x549.google.com (mail-pg1-x549.google.com
 [IPv6:2607:f8b0:4864:20::549])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 1CDC4C0086D5
        for <kvm@vger.kernel.org>; Thu,  6 Aug 2020 08:14:39 -0700 (PDT)
Received: by mail-pg1-x549.google.com with SMTP id z16so33806022pgh.21
        for <kvm@vger.kernel.org>; Thu, 06 Aug 2020 08:14:39 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=IEWKHXgY/FO2Lzh5aFVLQspUpNRT0CohKxffXWIy7MY=;
        b=gUQ8RY84bFEwevqDGstP05e0tNYK5t3p37LAnEQs/IHBUy7tJ+EZqruPebc4p5MFJa
         jkEtEUrXAkLSBMx6Si7aOciUb8RbCUIwvcrr9Dp8q/DrExa1C84XDAmG+uk8sp0Xu5F0
         ZJpSHRSsTEEuSUNI9UELKDoWRfG8KGbfUowUcuc+Z0bn4AMsG+iYFuX+lbRrs48H8rn4
         3Mu6X3a40coIuMqRgvvFopRZkOpfrtC36pZw+Y+1M2ZDVRi6GG5aeI4MaFgSZKoTS82L
         nd2u8NEn5Q51AKPIoePOcSBm+ctACEVgXbzCcWDmSj1zSrMHz1SdEh2ZI9ThnLkptJ6q
         0QQg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=IEWKHXgY/FO2Lzh5aFVLQspUpNRT0CohKxffXWIy7MY=;
        b=jaAbZcREnkatcYYLDl2zmqPtvsdvDaTYTwO2yN4BRnK5iwXUBDmLPUQvKaVE7EoG1o
         jfoWXpXC/X5F07oTCM1iWBVHtM3idaVwRmPzmsoGrdVQhOpuE6XBZIhQ08+YJVcJyVMr
         RIV+gWAYDOD+WmOwX3ohs9yDVlr9srJ7cCJrbHWmJB1DmbFtDrzBnpJUnAaRalGIVl24
         NySsmpv55yjwHjFclE40o6nnKSsUhCp40wtco4qmlSvWFwBK0gqYJu0vnyRG6DsFWpg4
         HxaHA595pIA5uucsRWGQH1AYdUaPMrn0Mp71+r4PHjasaejPWGF8TYwmxUCuU+pGGXb5
         C5dw==
X-Gm-Message-State: AOAM531f84wBpFse0Kefkzj00nwdFwnpqRo4r48N3iRhaezOvw6HbxJ0
        dRGjHUC+w2R80EUvWEin4W+a7v4oTRupeZDYNF9nBHMYxontCq32NtDOf5HpaZU+L6QC9FL4M/O
        a9GiJ2lpxk1j7hyc6WuOzYrcRX7I1Qi6OKBz4+imdJJNJcgfdb/hRk9wbCQ==
X-Google-Smtp-Source: 
 ABdhPJzA7mVX9VGBUysUPwrH7ol7HOsObm8SVAK2HWEx3nzgGFOoreJTSse19pvNlyp40HzwxCy1FUGOKkY=
X-Received: by 2002:a17:90a:2e87:: with SMTP id
 r7mr8814253pjd.137.1596726878152;
 Thu, 06 Aug 2020 08:14:38 -0700 (PDT)
Date: Thu,  6 Aug 2020 15:14:30 +0000
In-Reply-To: <20200806151433.2747952-1-oupton@google.com>
Message-Id: <20200806151433.2747952-2-oupton@google.com>
Mime-Version: 1.0
References: <20200806151433.2747952-1-oupton@google.com>
X-Mailer: git-send-email 2.28.0.236.gb10cc79966-goog
Subject: [PATCH v3 1/4] kvm: x86: encapsulate wrmsr(MSR_KVM_SYSTEM_TIME)
 emulation in helper fn
From: Oliver Upton <oupton@google.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Oliver Upton <oupton@google.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No functional change intended.

Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Peter Shier <pshier@google.com>
Signed-off-by: Oliver Upton <oupton@google.com>
---
 arch/x86/kvm/x86.c | 58 +++++++++++++++++++++++++---------------------
 1 file changed, 32 insertions(+), 26 deletions(-)

```
#### [PATCH v1 1/1] s390: virtio-ccw: PV needs VIRTIO I/O device protection
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11703739
Return-Path: <SRS0=LWg4=BQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0337A138C
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 17:48:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 647FD22CA1
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 17:48:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="Wy/DxXqm"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730398AbgHFRsI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Aug 2020 13:48:08 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:21210 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728935AbgHFQfp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 6 Aug 2020 12:35:45 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 076E296Q092894;
        Thu, 6 Aug 2020 10:23:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=cK+IFbwDsM2m9d21mk++qrDlBgGZFvrkkmzPVkYIzkw=;
 b=Wy/DxXqmIU1/ZqRoHZPqLu9oj7ath30Pv4e1FvQ7vq46Ful0fvenpSQOtpq0EmuF7yqi
 lXH6qTHYc2W4pkoa2gm56Eb0kse8bu7mNntp3WKrKsnk8yILFR4LvmBRKgfoWc2NRK8+
 iD+vzfe4NuI2f+VDseLvdF7i1/njOKnOjE4WU2tZpJ5YNElm5ItAAmqdidGABGuO7xqR
 Td632cBQQ5WLo7ceohtcYfRcu/HvGe8qSBiJW/AeT+umrvjkCO0BTpjRd5Eewudh88Kw
 pAeYb2wxa/w9KxTe/Fy7K0GB0lA3cmUkmrg5BMWSliJX77Rac9FcabcnNJKiWzlWqbDI eQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32qu0w8xkc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 06 Aug 2020 10:23:12 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 076E38m9098055;
        Thu, 6 Aug 2020 10:23:11 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0a-001b2d01.pphosted.com with ESMTP id 32qu0w8xjb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 06 Aug 2020 10:23:11 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 076EGXgN027832;
        Thu, 6 Aug 2020 14:23:08 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma02fra.de.ibm.com with ESMTP id 32n018bda0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 06 Aug 2020 14:23:08 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 076EN59J27721984
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 6 Aug 2020 14:23:05 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7AEA6AE053;
        Thu,  6 Aug 2020 14:23:05 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E8AE7AE04D;
        Thu,  6 Aug 2020 14:23:04 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.149.70])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  6 Aug 2020 14:23:04 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v1 1/1] s390: virtio-ccw: PV needs VIRTIO I/O device
 protection
Date: Thu,  6 Aug 2020 16:23:02 +0200
Message-Id: <1596723782-12798-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1596723782-12798-1-git-send-email-pmorel@linux.ibm.com>
References: <1596723782-12798-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-08-06_09:2020-08-06,2020-08-06 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 malwarescore=0
 clxscore=1015 impostorscore=0 lowpriorityscore=0 suspectscore=3
 phishscore=0 mlxscore=0 bulkscore=0 priorityscore=1501 spamscore=0
 mlxlogscore=999 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2008060096
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If protected virtualization is active on s390, the virtio queues are
not accessible to the host, unless VIRTIO_F_IOMMU_PLATFORM has been
negotiated. Use ccw_transport_features() to fail feature negociation
and consequently probe if that's not the case, preventing a host
error on access attempt.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 drivers/s390/virtio/virtio_ccw.c | 24 +++++++++++++++++++-----
 1 file changed, 19 insertions(+), 5 deletions(-)

```
#### [kvm-unit-tests PATCH 1/3] unittests.cfg: Increase timeout for access test
##### From: Mohammed Gamal <mgamal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mohammed Gamal <mgamal@redhat.com>
X-Patchwork-Id: 11703665
Return-Path: <SRS0=LWg4=BQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5083514B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 17:21:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ABB8E23120
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  6 Aug 2020 17:21:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="DHn4MoUR"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727976AbgHFRVb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 6 Aug 2020 13:21:31 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:35807 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1730267AbgHFRQk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 6 Aug 2020 13:16:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1596734194;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=XFwy7e2/BEqkhEQtkFfwSeARVG8Dp3lgZH+uIout38Q=;
        b=DHn4MoURhq49EqHO1QDNa2kONPcRKjKPddgg36qfaitIM2XSOH6pHuccR3ruFkahLTqZWC
        QTZSbBnlbKKcy0fZki0ZQJ7Bp/c0mUGvrpQzyyvhloOnkLhMMVzXXrGpboH2ACri1m3G8q
        uZuTN8aJx1T8dbDv7luf8OpDdu0xHrY=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-507-an0cKzITPa-P4KJwKUGBlA-1; Thu, 06 Aug 2020 08:44:22 -0400
X-MC-Unique: an0cKzITPa-P4KJwKUGBlA-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 61CFBA4769;
        Thu,  6 Aug 2020 12:44:11 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-114-17.ams2.redhat.com
 [10.36.114.17])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 16B5F5C1BD;
        Thu,  6 Aug 2020 12:44:08 +0000 (UTC)
From: Mohammed Gamal <mgamal@redhat.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: Mohammed Gamal <m.gamal005@gmail.com>
Subject: [kvm-unit-tests PATCH 1/3] unittests.cfg: Increase timeout for access
 test
Date: Thu,  6 Aug 2020 14:43:56 +0200
Message-Id: <20200806124358.4928-2-mgamal@redhat.com>
In-Reply-To: <20200806124358.4928-1-mgamal@redhat.com>
References: <20200806124358.4928-1-mgamal@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Mohammed Gamal <m.gamal005@gmail.com>

In case of npt=0 on kvm_amd, tests run slower and timeout,
so increase the timeout. The tests then do succeed.

Signed-off-by: Mohammed Gamal <m.gamal005@gmail.com>
---
 x86/unittests.cfg | 1 +
 1 file changed, 1 insertion(+)

```
