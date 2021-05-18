#### [PATCH v7 01/12] iova: Export alloc_iova_fast()
##### From: Xie Yongji <xieyongji@bytedance.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xie Yongji <xieyongji@bytedance.com>
X-Patchwork-Id: 12261395
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 95B50C43461
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 09:56:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6B95C6128B
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 09:56:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236078AbhEQJ5V (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 17 May 2021 05:57:21 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:35142 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S236114AbhEQJ5R (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 May 2021 05:57:17 -0400
Received: from mail-pj1-x102b.google.com (mail-pj1-x102b.google.com
 [IPv6:2607:f8b0:4864:20::102b])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id ADD01C06174A
        for <kvm@vger.kernel.org>; Mon, 17 May 2021 02:56:00 -0700 (PDT)
Received: by mail-pj1-x102b.google.com with SMTP id
 ep16-20020a17090ae650b029015d00f578a8so3400976pjb.2
        for <kvm@vger.kernel.org>; Mon, 17 May 2021 02:56:00 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=bytedance-com.20150623.gappssmtp.com; s=20150623;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=Ygd6Y3pMMIE3RUljThmAuE4r52Kqy5h8O2JQV7ru1VE=;
        b=CfGZ0PIMRYu4HZPQTqyHPr1YCzbRVLXIMfeN4edm7scYV+U9MYChU0jqbjBaSYww8W
         x34cC9/BMlqozDzEDG8ux9bhvujMR9dQUSals7Y5Q6Z1Ic9ux5H7kh6skw81G6vCSEuj
         qvAj7zfktNXLCd1rUIgxI87C26tOnzC7+pVGuD1g/0Lv5qn8oiSuf1+7+eWR6D+6V+Us
         mf1DA4vTKCekvwxQldEXP7DGoACUCXG3tr2GgElhChFw367kHCgwfpQSfxiMYchniS3x
         3QikwhZOKWcBciqgNHjjH9ktT79H4PFjZ9sUPr0lm6w4kGIx2J2u98pIhDIqi7lIhPpV
         gsYg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=Ygd6Y3pMMIE3RUljThmAuE4r52Kqy5h8O2JQV7ru1VE=;
        b=C3bXz24enaqSKSumcQWQEU9d8uD20b0ussJ+/7j6QuCrnzakayYqHxBhbrIxVjcafy
         aCaUk8WBjYkwXevhiTWBCQSPwFXGKulE9nnZOI4z+/IxABcATEImErROoicQxOT57wMS
         /eZslpr2fDF9+wUJrgYH6EBME/QS0SoL7QYlLCtOmuJCD3dM87/18m4xlDDjwzhpTqWa
         Bg07lSxi8hZf0aGI4gzq4xwoPItwF15I9umUiOHrWPRYKmIMiL9GJqzQNO76s4anEFFw
         SeAwYHGpSpzEhGNgjpBRHr2Bg+NCiQu48LSTZmo9apfeuhi0o0p2Bm2fAuYqqmSpUOL3
         MFnQ==
X-Gm-Message-State: AOAM532i9XVMgd9PDXWMnm7lFyRYySpgtreBc1pL4YdIp3/daPG9OxMd
        E+AdBBRmsvXaM1SY53yqtzW3
X-Google-Smtp-Source: 
 ABdhPJxcu8VbEVbQ6UidxIbU5FzeWTHg5acjJx2pdfr2qW4l4EQrVjPUuXEDDezt/Znh1VwtXb7+/w==
X-Received: by 2002:a17:90a:6c23:: with SMTP id
 x32mr30960965pjj.228.1621245360342;
        Mon, 17 May 2021 02:56:00 -0700 (PDT)
Received: from localhost ([139.177.225.253])
        by smtp.gmail.com with ESMTPSA id
 q24sm10233373pjp.6.2021.05.17.02.55.59
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 17 May 2021 02:56:00 -0700 (PDT)
From: Xie Yongji <xieyongji@bytedance.com>
To: mst@redhat.com, jasowang@redhat.com, stefanha@redhat.com,
        sgarzare@redhat.com, parav@nvidia.com, hch@infradead.org,
        christian.brauner@canonical.com, rdunlap@infradead.org,
        willy@infradead.org, viro@zeniv.linux.org.uk, axboe@kernel.dk,
        bcrl@kvack.org, corbet@lwn.net, mika.penttila@nextfour.com,
        dan.carpenter@oracle.com, joro@8bytes.org
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, linux-fsdevel@vger.kernel.org,
        iommu@lists.linux-foundation.org, linux-kernel@vger.kernel.org
Subject: [PATCH v7 01/12] iova: Export alloc_iova_fast()
Date: Mon, 17 May 2021 17:55:02 +0800
Message-Id: <20210517095513.850-2-xieyongji@bytedance.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20210517095513.850-1-xieyongji@bytedance.com>
References: <20210517095513.850-1-xieyongji@bytedance.com>
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Export alloc_iova_fast() so that some modules can use it
to improve iova allocation efficiency.

Signed-off-by: Xie Yongji <xieyongji@bytedance.com>
---
 drivers/iommu/iova.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH v2 1/7] KVM: nVMX: Introduce nested_evmcs_is_used()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12262037
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 8119BC433B4
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 13:51:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 660F6611C2
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 13:51:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237568AbhEQNwX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 17 May 2021 09:52:23 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:28837 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S234049AbhEQNwW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 17 May 2021 09:52:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1621259465;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=N/5KkPOa7BDmJ61fDZWG5U+qX0pyk+buTzYClLDRiEU=;
        b=c6Zs9MTBvv89CPGkJ52eWDeyxKDslAz2tZTJMspn2vsGkw+OhXQO15S6LRyri6vcJXIyWy
        QDGUGbqdHarKjxZJF9n/OXCxHEh5ooySR2WjPzETTZ/T7lvvTBkDQeSJgB4IhmJJUnsFhZ
        RC3/OQtVHsgeIDRra23Tzak8UnTFpZM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-459-exbYJMcbPCW3WBQjIQk5Hg-1; Mon, 17 May 2021 09:51:02 -0400
X-MC-Unique: exbYJMcbPCW3WBQjIQk5Hg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 4C69B8042A9;
        Mon, 17 May 2021 13:51:00 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.194.112])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 36B3F5C1A1;
        Mon, 17 May 2021 13:50:58 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Maxim Levitsky <mlevitsk@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/7] KVM: nVMX: Introduce nested_evmcs_is_used()
Date: Mon, 17 May 2021 15:50:48 +0200
Message-Id: <20210517135054.1914802-2-vkuznets@redhat.com>
In-Reply-To: <20210517135054.1914802-1-vkuznets@redhat.com>
References: <20210517135054.1914802-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Unlike regular set_current_vmptr(), nested_vmx_handle_enlightened_vmptrld()
can not be called directly from vmx_set_nested_state() as KVM may not have
all the information yet (e.g. HV_X64_MSR_VP_ASSIST_PAGE MSR may not be
restored yet). Enlightened VMCS is mapped later while getting nested state
pages. In the meantime, vmx->nested.hv_evmcs remains NULL and using it
for various checks is incorrect. In particular, if KVM_GET_NESTED_STATE is
called right after KVM_SET_NESTED_STATE, KVM_STATE_NESTED_EVMCS flag in the
resulting state will be unset (and such state will later fail to load).

Introduce nested_evmcs_is_used() and use 'is_guest_mode(vcpu) &&
vmx->nested.current_vmptr == -1ull' check to detect not-yet-mapped eVMCS
after restore.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/vmx/nested.c | 31 ++++++++++++++++++++++++++-----
 1 file changed, 26 insertions(+), 5 deletions(-)

```
#### [PATCH v1 01/11] KVM: s390: pv: leak the ASCE page when destroy fails
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 12263057
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 5B3E7C43462
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 20:08:08 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3932B6128E
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 20:08:08 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S236354AbhEQUJX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 17 May 2021 16:09:23 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:30730 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S236497AbhEQUJW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 17 May 2021 16:09:22 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.43/8.16.0.43) with SMTP id
 14HK4v2l019616;
        Mon, 17 May 2021 16:08:05 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=Dq8CDOmkbZsAISdoFN/+ceHwBaHeZdaj9ZesXmFNfbM=;
 b=DtvQ6GVeVfSN5oK8osdoK+S5t40IfjHeXs3d/NGD146PzDeF1u28sKB+1OmyYxpfNW0b
 HijdPwhlTtWm4rd7/8Iba3Vv0lEUEJxYzgf0wPKvAA9aRyZRyprWUO7NoS4xez9FHvQZ
 1SkAKT4krtilROZRryDJ2OGRAUmAZ0yMAFVupQTYQAlw8iBz9Ui6Me4MGkgykIKlmYIG
 5PWzxQiWrwsmg6QWVx7v1EEOciEOEaTHxfDKPOhioSdM+QgOY97VrL+wGTaYLlUlAf3w
 pM+nqCKENhGA9Je5mJNHAVHRqnK3dnT1p5ZK7fz868u3CGnltrlzxf9N7Ra8d8WghEQ0 fQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38kxqkgt86-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 May 2021 16:08:05 -0400
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.43/8.16.0.43) with SMTP id 14HK5qiM023248;
        Mon, 17 May 2021 16:08:04 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 38kxqkgt7m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 May 2021 16:08:04 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.43/8.16.0.43) with SMTP id
 14HK821M005715;
        Mon, 17 May 2021 20:08:02 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03ams.nl.ibm.com with ESMTP id 38j5x7s2nr-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 May 2021 20:08:02 +0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 14HK7W6H14090574
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 17 May 2021 20:07:32 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E0A545204F;
        Mon, 17 May 2021 20:07:59 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.14.34])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id 7C5F752057;
        Mon, 17 May 2021 20:07:59 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: cohuck@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        thuth@redhat.com, pasic@linux.ibm.com, david@redhat.com,
        linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org
Subject: [PATCH v1 01/11] KVM: s390: pv: leak the ASCE page when destroy fails
Date: Mon, 17 May 2021 22:07:48 +0200
Message-Id: <20210517200758.22593-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.31.1
In-Reply-To: <20210517200758.22593-1-imbrenda@linux.ibm.com>
References: <20210517200758.22593-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-GUID: 0rB_ZRJ35arQylfAE42yIiqigOF-bIpe
X-Proofpoint-ORIG-GUID: Rwe51-haDvvLR1BBUuc8nIfAQykemdKl
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.391,18.0.761
 definitions=2021-05-17_08:2021-05-17,2021-05-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 suspectscore=0
 phishscore=0 lowpriorityscore=0 adultscore=0 spamscore=0 mlxscore=0
 impostorscore=0 priorityscore=1501 bulkscore=0 mlxlogscore=999
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2104190000 definitions=main-2105170140
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When the destroy configuration UVC fails, the page pointed to by the
ASCE of the VM becomes poisoned, and, to avoid issues it must not be
used again.

Since the page becomes in practice unusable, we set it aside and leak it.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 arch/s390/kvm/pv.c | 53 +++++++++++++++++++++++++++++++++++++++++++++-
 1 file changed, 52 insertions(+), 1 deletion(-)

```
#### [PATCH v5 1/4] KVM: stats: Separate common stats from architecture specific ones
##### From: Jing Zhang <jingzhangos@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jing Zhang <jingzhangos@google.com>
X-Patchwork-Id: 12262415
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-26.3 required=3.0 tests=BAYES_00,DKIMWL_WL_MED,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	USER_AGENT_GIT,USER_IN_DEF_DKIM_WL autolearn=unavailable autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 37913C43470
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 16:23:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 19FE2610A0
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 16:23:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S244951AbhEQQZO (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 17 May 2021 12:25:14 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:37232 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S243444AbhEQQYj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 May 2021 12:24:39 -0400
Received: from mail-pj1-x104a.google.com (mail-pj1-x104a.google.com
 [IPv6:2607:f8b0:4864:20::104a])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9AED7C030CC3
        for <kvm@vger.kernel.org>; Mon, 17 May 2021 07:53:21 -0700 (PDT)
Received: by mail-pj1-x104a.google.com with SMTP id
 f8-20020a17090a9b08b0290153366612f7so3481663pjp.1
        for <kvm@vger.kernel.org>; Mon, 17 May 2021 07:53:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=XH5NpPcNmd+gxQVfKPe6WDEzNvEQPniKjccpZx6vsBc=;
        b=EhZ5Bm33HJcnmSl7OvV5eM6PMoo9LVlyuj032wMIRtjSZz4ral9Asnk/5ozY8tEpns
         nv2lyODijPsysasqQ7xP/wyBAm8bGSY2frpQ9gCGBkdpfvct2sHdux+CLENrR08CvNXU
         gomcNwpfAuxoWUiVn8PBqpXVQsDukbJ1mpPBGE5b2iHYR85NLDY9Q+OLyzdnvCSwDeI0
         0IfMedWm5bfvBWmuksE6su9iE3k86pvEcbmJWpkqvkKwDYb/09/VunIT7eR9ssWi3jgP
         bu+ROs/UpdRtTow3j0oMbwYYKiA/dMq57quL6CNnZ3Bx4L/e+i2qVtPB/3AgMXOCRbcl
         1T8A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=XH5NpPcNmd+gxQVfKPe6WDEzNvEQPniKjccpZx6vsBc=;
        b=pIFNcY5MvOuAJ2JUHt0Yc/7A92IXdRF4SyNo25IIH4rOi5aRot33BwFWcBNMh+8b9f
         FMdRjgyOoz7Gzzyca5Qpk7SrzQNlsCoLQDA7btlfVVGzyGIuyc1YknRrKA5GO0MeMg4p
         G83tDyviNHDMzrOqj0TmdSEuZlHHbYo5+zsnNme84waPAM2Bs9LIxejmnUg6alsQM9Si
         KaVlBlr45s0q2sY8tHyLhRcciJCjcOZGb35PVHSg85sofwfZVPyiwmK/8kjjF92Hve0v
         nXHQtmfo5BtNetyEYzTwwjAykH8iFB1TADJiw0JaGocYr4C4Ez78QOhrZfqEZlhznMZv
         X5fA==
X-Gm-Message-State: AOAM532Al9u8zJW6WfOuhmEPg0f3Vz8OvF1jDyu6UJInkZQPvb4MHXLK
        hnw0k5kZzq5ZAl/SMXZ7p7DnN35L2PsiA2uSwl51qETEl1WuiVyf2RNkS4QJFguKVAooDFnU5DR
        N9zGUku217EIFy29yT2pKzn4M6dtFZhzruWVsHab/IXKkp1YzkaO+yr3MUvEsmi2ersKvcQo=
X-Google-Smtp-Source: 
 ABdhPJz1suw0yiPNmuxZny/qTOQ/OihMsN6xmSBYrutps7+7/1PsUbjecZ4U202xwHry6d0gLhtXmFlD5FntmB85WQ==
X-Received: from jgzg.c.googlers.com ([fda3:e722:ac3:10:7f:e700:c0a8:1acf])
 (user=jingzhangos job=sendgmr) by 2002:a17:902:b592:b029:ee:9128:f53f with
 SMTP id a18-20020a170902b592b02900ee9128f53fmr414192pls.32.1621263201328;
 Mon, 17 May 2021 07:53:21 -0700 (PDT)
Date: Mon, 17 May 2021 14:53:11 +0000
In-Reply-To: <20210517145314.157626-1-jingzhangos@google.com>
Message-Id: <20210517145314.157626-2-jingzhangos@google.com>
Mime-Version: 1.0
References: <20210517145314.157626-1-jingzhangos@google.com>
X-Mailer: git-send-email 2.31.1.751.gd2f1c929bd-goog
Subject: [PATCH v5 1/4] KVM: stats: Separate common stats from architecture
 specific ones
From: Jing Zhang <jingzhangos@google.com>
To: KVM <kvm@vger.kernel.org>, KVMARM <kvmarm@lists.cs.columbia.edu>,
        LinuxMIPS <linux-mips@vger.kernel.org>,
        KVMPPC <kvm-ppc@vger.kernel.org>,
        LinuxS390 <linux-s390@vger.kernel.org>,
        Linuxkselftest <linux-kselftest@vger.kernel.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Will Deacon <will@kernel.org>,
        Huacai Chen <chenhuacai@kernel.org>,
        Aleksandar Markovic <aleksandar.qemu.devel@gmail.com>,
        Thomas Bogendoerfer <tsbogend@alpha.franken.de>,
        Paul Mackerras <paulus@ozlabs.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Peter Shier <pshier@google.com>,
        Oliver Upton <oupton@google.com>,
        David Rientjes <rientjes@google.com>,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Cc: Jing Zhang <jingzhangos@google.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Put all common statistics in a separate structure to ease
statistics handling for the incoming new statistics API.

No functional change intended.

Signed-off-by: Jing Zhang <jingzhangos@google.com>
---
 arch/arm64/include/asm/kvm_host.h   |  9 ++-------
 arch/arm64/kvm/guest.c              | 12 ++++++------
 arch/mips/include/asm/kvm_host.h    |  9 ++-------
 arch/mips/kvm/mips.c                | 12 ++++++------
 arch/powerpc/include/asm/kvm_host.h |  9 ++-------
 arch/powerpc/kvm/book3s.c           | 12 ++++++------
 arch/powerpc/kvm/book3s_hv.c        | 12 ++++++------
 arch/powerpc/kvm/book3s_pr.c        |  2 +-
 arch/powerpc/kvm/book3s_pr_papr.c   |  2 +-
 arch/powerpc/kvm/booke.c            | 14 +++++++-------
 arch/s390/include/asm/kvm_host.h    |  9 ++-------
 arch/s390/kvm/kvm-s390.c            | 12 ++++++------
 arch/x86/include/asm/kvm_host.h     |  9 ++-------
 arch/x86/kvm/x86.c                  | 14 +++++++-------
 include/linux/kvm_host.h            |  9 +++++++--
 include/linux/kvm_types.h           | 12 ++++++++++++
 virt/kvm/kvm_main.c                 | 14 +++++++-------
 17 files changed, 82 insertions(+), 90 deletions(-)

```
#### [PULL kvm-unit-tests 01/10] configure: arm: Replace --vmm with --target
##### From: Andrew Jones <drjones@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Andrew Jones <drjones@redhat.com>
X-Patchwork-Id: 12262211
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.1 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 037BCC433ED
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 14:45:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DFADA61D50
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 14:45:45 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S240792AbhEQOrA (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 17 May 2021 10:47:00 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:45294 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S240152AbhEQOlM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 17 May 2021 10:41:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1621262395;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=9L3g3g1Sx+I4MEP7LsP3h+zYRpkAOZj41Z4y7VlGuuU=;
        b=eV+ovan0JQd6vokeKBB0GQxE6iSHA9iqRrfwfWoYiSOL/vZqH5Wm6LYKjIR5XyBYFtAMLz
        uuLsJzEkxdYRllWb+/wWkC7N90urWeBEXsC3QcJmItnVlg84XzBTMRYV+3Ci6TI3YF/yOD
        mP83HlfMa9Xhzs1MquHXcVyum/S8lGo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-485-9v0jaNvoMBSP88oauL-vRQ-1; Mon, 17 May 2021 10:39:51 -0400
X-MC-Unique: 9v0jaNvoMBSP88oauL-vRQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BBB95C73A4;
        Mon, 17 May 2021 14:39:04 +0000 (UTC)
Received: from gator.redhat.com (unknown [10.40.192.248])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 940255D6D7;
        Mon, 17 May 2021 14:39:03 +0000 (UTC)
From: Andrew Jones <drjones@redhat.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, Alexandru Elisei <alexandru.elisei@arm.com>
Subject: [PULL kvm-unit-tests 01/10] configure: arm: Replace --vmm with
 --target
Date: Mon, 17 May 2021 16:38:51 +0200
Message-Id: <20210517143900.747013-2-drjones@redhat.com>
In-Reply-To: <20210517143900.747013-1-drjones@redhat.com>
References: <20210517143900.747013-1-drjones@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexandru Elisei <alexandru.elisei@arm.com>

The --vmm configure option was added to distinguish between the two virtual
machine managers that kvm-unit-tests supports for the arm and arm64
architectures, qemu or kvmtool. There are plans to make kvm-unit-tests work
as an EFI app, which will require changes to the way tests are compiled.
Instead of adding a new configure option specifically for EFI and have it
coexist with --vmm, or overloading the semantics of the existing --vmm
option, let's replace --vmm with the more generic name --target.

Since --target is only valid for arm and arm64, reject the option when it's
specified for another architecture, which is how --vmm should have behaved
from the start.

Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Andrew Jones <drjones@redhat.com>
---
 configure | 30 +++++++++++++++++++++---------
 1 file changed, 21 insertions(+), 9 deletions(-)

```
#### [PATCH v3 1/5] KVM: exit halt polling on need_resched() for both book3s and generic halt-polling
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 12262053
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.7 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 385B6C433ED
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 14:01:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 17E6E611BF
	for <kvm@archiver.kernel.org>; Mon, 17 May 2021 14:01:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S237584AbhEQOCn (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 17 May 2021 10:02:43 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:34664 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S237568AbhEQOCi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 May 2021 10:02:38 -0400
Received: from mail-pg1-x52f.google.com (mail-pg1-x52f.google.com
 [IPv6:2607:f8b0:4864:20::52f])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 77BCDC061756;
        Mon, 17 May 2021 07:01:21 -0700 (PDT)
Received: by mail-pg1-x52f.google.com with SMTP id 27so3416715pgy.3;
        Mon, 17 May 2021 07:01:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id;
        bh=OXpOhNWfIpuhpnHdPJrluE5Py5GUd57HQ7WW+PgXS2c=;
        b=ajL8VZkyPWHRi81eL4m4qbx/XsNbUiH/XOIqcU9VNghE0X8fkTeVlF8Q5rgmQBb9mx
         WeSoobDW7gQ2QXTgFE8iy+Uy+AnPcmuDU5J+86toTiU28EjGs0Wyczr1kCRGIex8awP0
         6IBYMfWUrNCZHQ0+6BeQOo0lFfJuWTQazVCm6cOGR4m5qNa6B944km18Mfr9ptqmZ6PU
         QG8Gb6ikoUgFmDYDT8J+0VhBapuj38UxDEFLn86hrdCjBL3/kQQ4XyhoFrRJ2lkAYAT1
         dzpAvPz6sr0D7XJRCwd8HUROK1P3tZCoLq9KfjstjvpjZzS7lV1kGh1TPflhdI/7axyO
         E94A==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=OXpOhNWfIpuhpnHdPJrluE5Py5GUd57HQ7WW+PgXS2c=;
        b=eFrBCw4iaHxh/s4IAIunVoUFx/56zBZIsQZuPMpv/pLmA0txvh3GM+inOb6aqg8SWm
         7PxTyjyf+oUgGaVdWagv0OzkK/mwXBnGilAnvo3p1T2/VtSfwNwbLk0A0ckbPxeOD5YM
         iX1q+j7HCSODkrlcfIqkpMe3g4sKiggwyrGLjMXwdt689AuqyvthcDhDEJ7Ixt5MYo+A
         HjbNSGvQpL16m5V8ohm+neIqf0vNoR65IRpXhQwZ/0R/p6RWNUx9daBaEQjJ8HXVhlDT
         CLJx7qHRN3TZ7pbCewGDOrl7JUFNMIhKbvOqzynOecm5eMVwBl8LelEnKgzxhozjwXF/
         5a1A==
X-Gm-Message-State: AOAM533XtuW84s3KOS0/VpypdlhxkQEDR4ivsKmPk8kTG/lugRjVyxET
        cSd47484g8HJOv8Wa+8FY6Own07/Ss4=
X-Google-Smtp-Source: 
 ABdhPJwHxSzExHpL+57mfMVKEs8ePvUwo63gs+VDRh9qqggeYBWmNPE1HPIzDUpx8Ac16na1HngHlw==
X-Received: by 2002:a65:5bc6:: with SMTP id o6mr993570pgr.364.1621260080787;
        Mon, 17 May 2021 07:01:20 -0700 (PDT)
Received: from localhost.localdomain ([203.205.141.61])
        by smtp.googlemail.com with ESMTPSA id
 k10sm3074229pfu.175.2021.05.17.07.01.17
        (version=TLS1_2 cipher=ECDHE-ECDSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 17 May 2021 07:01:20 -0700 (PDT)
From: Wanpeng Li <kernellwp@gmail.com>
X-Google-Original-From: Wanpeng Li <wanpengli@tencent.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <seanjc@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Ben Segall <bsegall@google.com>,
        Venkatesh Srinivas <venkateshs@chromium.org>,
        David Matlack <dmatlack@google.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Subject: [PATCH v3 1/5] KVM: exit halt polling on need_resched() for both
 book3s and generic halt-polling
Date: Mon, 17 May 2021 07:00:24 -0700
Message-Id: <1621260028-6467-1-git-send-email-wanpengli@tencent.com>
X-Mailer: git-send-email 2.7.4
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Inspired by commit 262de4102c7bb8 (kvm: exit halt polling on need_resched()
as well), CFS_BANDWIDTH throttling will use resched_task() when there is just
one task to get the task to block. It was likely allowing VMs to overrun their
quota when halt polling. Due to PPC implements an arch specific halt polling
logic, we should add the need_resched() checking there as well. This
patch adds a helper function that to be shared between book3s and generic
halt-polling loop.

Cc: Ben Segall <bsegall@google.com>
Cc: Venkatesh Srinivas <venkateshs@chromium.org>
Cc: Jim Mattson <jmattson@google.com> 
Cc: David Matlack <dmatlack@google.com>
Cc: Paul Mackerras <paulus@ozlabs.org>
Cc: Suraj Jitindar Singh <sjitindarsingh@gmail.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Reviewed-by: David Matlack <dmatlack@google.com>
Reviewed-by: Venkatesh Srinivas <venkateshs@chromium.org>
---
v2 -> v3:
 * add a helper function
v1 -> v2:
 * update patch description

 arch/powerpc/kvm/book3s_hv.c | 2 +-
 include/linux/kvm_host.h     | 2 ++
 virt/kvm/kvm_main.c          | 9 +++++++--
 3 files changed, 10 insertions(+), 3 deletions(-)

```
