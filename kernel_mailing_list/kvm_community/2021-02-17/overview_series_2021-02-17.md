#### [PATCH 1/7] KVM: VMX: read idt_vectoring_info a bit earlier
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 12091747
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6054FC43381
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 14:59:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 265D364E28
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 14:59:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233653AbhBQO7A (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Feb 2021 09:59:00 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:49233 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S232034AbhBQO66 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Feb 2021 09:58:58 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613573852;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=LN2px05F08WrD3YKLDLusn49XXFwsDBda/Tl6rjbljY=;
        b=eO/BZyxzJfYj59+l6ZWim8dhogslADYkD/AWUBE6c7kuJmwhoG/rQRWg4baZBRCBEJ9DgR
        gfFVB8C1sJw+8GFA/L0EIkSs/I6AiW4fFI4sWMJ73DSuKlO2do22hjriFRQWwluyv1q8TJ
        92VnTy8tEpz0tN7OXd3cEY1U4D80Zss=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-421-aC41oIWZNXCRCwhLfsdBdg-1; Wed, 17 Feb 2021 09:57:28 -0500
X-MC-Unique: aC41oIWZNXCRCwhLfsdBdg-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 80193801979;
        Wed, 17 Feb 2021 14:57:26 +0000 (UTC)
Received: from localhost.localdomain (unknown [10.35.206.33])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3226C10016FF;
        Wed, 17 Feb 2021 14:57:22 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Joerg Roedel <joro@8bytes.org>,
        Jim Mattson <jmattson@google.com>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Sean Christopherson <seanjc@google.com>,
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Thomas Gleixner <tglx@linutronix.de>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Ingo Molnar <mingo@redhat.com>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH 1/7] KVM: VMX: read idt_vectoring_info a bit earlier
Date: Wed, 17 Feb 2021 16:57:12 +0200
Message-Id: <20210217145718.1217358-2-mlevitsk@redhat.com>
In-Reply-To: <20210217145718.1217358-1-mlevitsk@redhat.com>
References: <20210217145718.1217358-1-mlevitsk@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

trace_kvm_exit prints this value (using vmx_get_exit_info)
so it makes sense to read it before the trace point.

Fixes: dcf068da7eb2 ("KVM: VMX: Introduce generic fastpath handler")

Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/vmx/vmx.c | 4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2 1/8] s390x: Fix fpc store address in RESTORE_REGS_STACK
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12091727
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 23F15C43331
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 14:43:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id ED1A164DFF
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 14:43:24 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233578AbhBQOnO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Feb 2021 09:43:14 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:35300 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S233425AbhBQOnJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 17 Feb 2021 09:43:09 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11HEYtG6184900;
        Wed, 17 Feb 2021 09:42:26 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=vuRLhnrN0FZn6h/Va0uxgrip9AUObOGa8pIcB5cKFpY=;
 b=qMSgP7TorMu+UzqkQsLjJnL+/9ZWGY1VjQ9RIlonHQtwusqZwe558x0fCOe+iYe7/VIF
 fPIunl26cKw2knLnTYdEFievX7QUiSuGRjxfkQFlYhqhxv+4y0sAkMmDJizGtiFx5Ivl
 h0C68qV4p4vLr1QylIDGWDqL6kwnmKdH8zvQSt5no6xEK/HAPeyQwblojv6CU7iWMZZ5
 GsyIxc4uE52urNe1rAEH2CRSQDyFOQf0yZE/lNXThWj49x+gwBHDzk9wKTIw/nnYI9GN
 0dEZzbDJTm1uSu891wr96/CL808gUHV26bmSyRMBHv6KLHlcSSYsQsuEeel7Y/Hj6cbK tQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36s4v40mgb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Feb 2021 09:42:25 -0500
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11HEZqhB189874;
        Wed, 17 Feb 2021 09:42:25 -0500
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36s4v40mf8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Feb 2021 09:42:25 -0500
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11HEgNnH030069;
        Wed, 17 Feb 2021 14:42:23 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma06fra.de.ibm.com with ESMTP id 36p61ha00g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 17 Feb 2021 14:42:23 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 11HEgKdk63898108
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 17 Feb 2021 14:42:20 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6473311C04C;
        Wed, 17 Feb 2021 14:42:20 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id A79D411C04A;
        Wed, 17 Feb 2021 14:42:19 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 17 Feb 2021 14:42:19 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, imbrenda@linux.ibm.com,
        pmorel@linux.ibm.com, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v2 1/8] s390x: Fix fpc store address in
 RESTORE_REGS_STACK
Date: Wed, 17 Feb 2021 09:41:09 -0500
Message-Id: <20210217144116.3368-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210217144116.3368-1-frankja@linux.ibm.com>
References: <20210217144116.3368-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-17_11:2021-02-16,2021-02-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 malwarescore=0
 mlxlogscore=999 spamscore=0 impostorscore=0 mlxscore=0 suspectscore=0
 clxscore=1015 priorityscore=1501 phishscore=0 bulkscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102170109
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The efpc stores in bits 32-63 of a register and we store a full 8
bytes to have the stack 8 byte aligned. This means that the fpc is
stored at offset 4 but we load it from offset 0. Lets replace efpc
with stfpc and get rid of the stg to store at offset 0.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 s390x/macros.S | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH v2] selftests: kvm: Mmap the entire vcpu mmap areaFrom: Aaron Lewis <aaronlewis@google.com>
##### From: Aaron Lewis <aaronlewis@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Aaron Lewis <aaronlewis@google.com>
X-Patchwork-Id: 12091953
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C64BDC43381
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 17:31:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9393264DCF
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 17:31:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S233571AbhBQRbY (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Feb 2021 12:31:24 -0500
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59312 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S232222AbhBQRbN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Feb 2021 12:31:13 -0500
Received: from mail-yb1-xb4a.google.com (mail-yb1-xb4a.google.com
 [IPv6:2607:f8b0:4864:20::b4a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id B1F8DC061574
        for <kvm@vger.kernel.org>; Wed, 17 Feb 2021 09:30:33 -0800 (PST)
Received: by mail-yb1-xb4a.google.com with SMTP id 194so12809858ybl.5
        for <kvm@vger.kernel.org>; Wed, 17 Feb 2021 09:30:33 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=sender:date:message-id:mime-version:subject:from:to:cc;
        bh=jHfqonvlMKl1wsgB/F2W/qoXTxBiDKQ8+KEhAtz6vqY=;
        b=PzcnGWb+9YlawHHBzCy0ixjJsg6CAcCZLbYZJPCjxkNLvmnH4MzE58JTFFCBzx1IoZ
         IeMKw+kpNLMNSMaqCBQd6PH+TUwrSLCXGcqfEvUXmNgdEPa21PmkkBqpLDwA/tC2uRGT
         1K66VUnyqGxYkxZ5qtIR5idf035Rwo2ROgzhEX8FdTuLBSqXUhuA23b+JqhrIkpiXtyz
         S1SG6kOWbk7rby4JMKYwTC4ABRaFmev+e8uYejP3K2HVjawu/km+bOD3WdGemy3jWIwG
         azGtQzru9zBdL4aO3SIeZMTEF6qz4z9vbHtTSyyQle9J+BMqBV2d9BhXclosuYX3JFcQ
         8pgg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:date:message-id:mime-version:subject:from
         :to:cc;
        bh=jHfqonvlMKl1wsgB/F2W/qoXTxBiDKQ8+KEhAtz6vqY=;
        b=dzszYmk/Rvw6krRkJgsEn5FVnmY1XmfvQC91w0rOc1RaWZ3b8WU2aFz3OiFc53jcq+
         vrjl1ebke9hfBj+YAf3lpPFfoweloW6ccx6Qs6MFnz5eeqPIF8EallqUeN3lbpXV4PEU
         LCqnJkv3PwXyOV0gt0Ec21tCaGgE/EKfw+H7B07+wDQuvK7emDxgVtkHpDuAL35/RdCe
         kzztOtMDPOp0D/OExIiE/1tR+1OKS2dWESjqAPke5Wr5Zja8XfQVIl773SqofY0ngHs9
         07TV2bvQLnb9BwiGF4+VGBvJ1TXUwRbIyd50AXY3hrVLnmGV2ICX4gf08ALPkq4acn1E
         qXtw==
X-Gm-Message-State: AOAM53158gOSFt5jzi+RQJ7dBR+H9NbXFmw/UgMYiI69XMhEY+d8p03x
        7wnNPCVxs6qeVXk7Ic+WoVLFsrLM69hc7TkECDTzJKaZMP1RIUcV/w1S8IA9K3X36tShh+QT7/J
        jqrY1HahNR7WzPWtEmGZCLswJLGVwEA5Nj02mT6XbFpJ7G6UJy1bTvebdWRlZ7GKsosGy
X-Google-Smtp-Source: 
 ABdhPJykAOfKVkSiVgyo1aPX35HYdsLlFd9CbcWO7jIpaPUMALw7DAoA8kQIytI/+7X/9Sh/PjZB7o9j2mN6JY1f
Sender: "aaronlewis via sendgmr" <aaronlewis@aaronlewis1.sea.corp.google.com>
X-Received: from aaronlewis1.sea.corp.google.com
 ([2620:15c:100:202:95fa:4161:5a32:e12])
 (user=aaronlewis job=sendgmr) by 2002:a25:af52:: with SMTP id
 c18mr761621ybj.196.1613583032910; Wed, 17 Feb 2021 09:30:32 -0800 (PST)
Date: Wed, 17 Feb 2021 09:27:31 -0800
Message-Id: <20210217172730.1521644-1-aaronlewis@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.30.0.478.g8a0d178c01-goog
Subject: [PATCH v2] selftests: kvm: Mmap the entire vcpu mmap area
From: Aaron Lewis <aaronlewis@google.com>
To: kvm@vger.kernel.org
Cc: seanjc@google.com, Aaron Lewis <aaronlewis@google.com>,
        Steve Rutherford <srutherford@google.com>,
        Andrew Jones <drjones@redhat.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The vcpu mmap area may consist of more than just the kvm_run struct.
Allocate enough space for the entire vcpu mmap area. Without this, on
x86, the PIO page, for example, will be missing.  This is problematic
when dealing with an unhandled exception from the guest as the exception
vector will be incorrectly reported as 0x0.

Co-developed-by: Steve Rutherford <srutherford@google.com>
Signed-off-by: Steve Rutherford <srutherford@google.com>
Signed-off-by: Aaron Lewis <aaronlewis@google.com>
Reviewed-by: Andrew Jones <drjones@redhat.com>
---
 tools/testing/selftests/kvm/lib/kvm_util.c | 66 +++++++++++-----------
 1 file changed, 33 insertions(+), 33 deletions(-)

```
#### [PATCH 1/3] x86/sev-es: Introduce from_syscall_gap() helper
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 12091505
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.7 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 76984C433DB
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 12:04:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4062864E57
	for <kvm@archiver.kernel.org>; Wed, 17 Feb 2021 12:04:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S232593AbhBQMDl (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 17 Feb 2021 07:03:41 -0500
Received: from 8bytes.org ([81.169.241.247]:55970 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S232584AbhBQMDA (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 17 Feb 2021 07:03:00 -0500
Received: from cap.home.8bytes.org (p549adcf6.dip0.t-ipconnect.de
 [84.154.220.246])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id AD110344;
        Wed, 17 Feb 2021 13:02:08 +0100 (CET)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        stable@vger.kernel.org, hpa@zytor.com,
        Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <seanjc@google.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        Arvind Sankar <nivedita@alum.mit.edu>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH 1/3] x86/sev-es: Introduce from_syscall_gap() helper
Date: Wed, 17 Feb 2021 13:01:41 +0100
Message-Id: <20210217120143.6106-2-joro@8bytes.org>
X-Mailer: git-send-email 2.30.0
In-Reply-To: <20210217120143.6106-1-joro@8bytes.org>
References: <20210217120143.6106-1-joro@8bytes.org>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Introduce a helper to check whether an exception came from the syscall
gap and use it in the SEV-ES code

Fixes: 315562c9af3d5 ("x86/sev-es: Adjust #VC IST Stack on entering NMI handler")
Cc: stable@vger.kernel.org # 5.10+
Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/include/asm/ptrace.h | 8 ++++++++
 arch/x86/kernel/traps.c       | 3 +--
 2 files changed, 9 insertions(+), 2 deletions(-)

```
