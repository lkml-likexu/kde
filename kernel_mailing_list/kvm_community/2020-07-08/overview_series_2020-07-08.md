#### [PATCH v11 01/13] KVM: Cache as_id in kvm_memory_slot
##### From: Peter Xu <peterx@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Peter Xu <peterx@redhat.com>
X-Patchwork-Id: 11652375
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 7DF9E618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:35:30 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 655E120720
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:35:30 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="d3tG82PY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727045AbgGHTfY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 15:35:24 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:29212 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726788AbgGHTeZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jul 2020 15:34:25 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594236863;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=hN7D86/UKZ9ErRoXs9fnrDlDCnq5Xvm3yeUIpEDme08=;
        b=d3tG82PYhJ0bDf+ex8D5kPfvYomp0TsTQM2gfbXNU9mDFHcH9VcLA0xucFLy65JVksOGkK
        7jJi8hkzRdLhsPzD31Hyai/m/503HSIzqTQxVRHsfMdIzkXs7jpSOrbvkNYfSXOcruZtIw
        VnoR/IdvHoqhndRkS6bNDTiy7Neg0wo=
Received: from mail-qt1-f198.google.com (mail-qt1-f198.google.com
 [209.85.160.198]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-454-Yl_xmVRwM4O4ApWcHinlKA-1; Wed, 08 Jul 2020 15:34:14 -0400
X-MC-Unique: Yl_xmVRwM4O4ApWcHinlKA-1
Received: by mail-qt1-f198.google.com with SMTP id u93so33861893qtd.8
        for <kvm@vger.kernel.org>; Wed, 08 Jul 2020 12:34:14 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=hN7D86/UKZ9ErRoXs9fnrDlDCnq5Xvm3yeUIpEDme08=;
        b=BD5seqDcw+Mm+Zv4Kpil3W7ASmzTdvlwUYyPH6K9yiKFKRRBhJHXhWiRghPXAxTInE
         kfOIn87kYkqBWQ2BoTCJFHjHgw3xH6xDI1SZj/5elKq7XikOiJH1F3WFfdhY5PnfbKbR
         WtORRYr5H1lwlYBQ7er+1o0V+rHJAzeqg1NuU3BLPtR4V/tb/HygCFnxa9Q3i1fkT23C
         rX7Y8zu86AqPr0p4dsRYCEXc9fI9XL0st8vLazIWB5Nfwtid7z34peJ1y9RJlZ9YYjfu
         THTGMCPrSmQJ/n411sirQocJCVfNSyagBJlbrDkuyXZ0HmQ7A3nda+Sq2F3IJkMnbkTp
         r6lQ==
X-Gm-Message-State: AOAM532LSI6qzr+I3tm1xVI3ar0+CH62elmQ4bLEi2BMP3CnIKP8KrXe
        /YzeE5truZ0k/6jS3bAWkToty44xipc+ZW18NqtpeuLngGQ3mLea4/awNXxqziKo2PXRKGQ6LiH
        7G0jbinJ7KW4W
X-Received: by 2002:a37:b701:: with SMTP id h1mr56064803qkf.335.1594236853828;
        Wed, 08 Jul 2020 12:34:13 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJxd0GzOBMQ1NmDsTj1gJlUvriObJFrFgIgsPO2Y2kMXMZ0+3c7pEyiE7fyyqU0Z8irQDaMDNQ==
X-Received: by 2002:a37:b701:: with SMTP id h1mr56064782qkf.335.1594236853604;
        Wed, 08 Jul 2020 12:34:13 -0700 (PDT)
Received: from xz-x1.redhat.com ([2607:9880:19c8:6f::1f4f])
        by smtp.gmail.com with ESMTPSA id
 f18sm664884qtc.28.2020.07.08.12.34.12
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 08 Jul 2020 12:34:12 -0700 (PDT)
From: Peter Xu <peterx@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: peterx@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        "Dr . David Alan Gilbert" <dgilbert@redhat.com>,
        Andrew Jones <drjones@redhat.com>,
        Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH v11 01/13] KVM: Cache as_id in kvm_memory_slot
Date: Wed,  8 Jul 2020 15:33:56 -0400
Message-Id: <20200708193408.242909-2-peterx@redhat.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200708193408.242909-1-peterx@redhat.com>
References: <20200708193408.242909-1-peterx@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Cache the address space ID just like the slot ID.  It will be used in
order to fill in the dirty ring entries.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Peter Xu <peterx@redhat.com>
---
 include/linux/kvm_host.h | 1 +
 virt/kvm/kvm_main.c      | 6 ++++++
 2 files changed, 7 insertions(+)

```
#### [PATCH 1/3 v4] KVM: x86: Create mask for guest CR4 reserved bits in kvm_update_cpuid()
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11650533
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 877D314B7
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 00:40:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6FF2E2064B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 00:40:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="aipl0Zlz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728856AbgGHAkM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 7 Jul 2020 20:40:12 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:36778 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728447AbgGHAkJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 7 Jul 2020 20:40:09 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0680XL2S010826;
        Wed, 8 Jul 2020 00:40:07 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=0iUB2O6X7+UYwxeAX/7qOrcotrFGN8i4A5AJlqKomiw=;
 b=aipl0ZlzIMQjF9vu5nvS2ijn7qWhbQzDKQth2BBaKMonUVOQ+U7zaU83ESMQ5W0ltlo8
 d0yZiF1boWH1IsOOemmAGe8tFxaNkFr1u6yr1lBBuW5qjQUMCCvSM5gPtFw/WIysbll2
 lFqmqriucmw0yJsWA0xFDF579rQBQK7Y52L6rBxmXZTOQalkQe7UY283CEHc8atV945a
 L+Gg4+4nMiLF2BeuvXzX0L6cutJIpReI6PB1W4V52GWGmxPk+vUcBPT+5nSpDw5/YiGJ
 04Necb/C52xxCl9LpTfqpsBC/cIBR04dCobV9IPBSBdBbkv4FD9cjglZ84/lG6GCGWR4 Kg==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2120.oracle.com with ESMTP id 323sxxuuqc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Wed, 08 Jul 2020 00:40:07 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0680YFOS022330;
        Wed, 8 Jul 2020 00:40:06 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3030.oracle.com with ESMTP id 3233py1sy3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 08 Jul 2020 00:40:06 +0000
Received: from abhmp0008.oracle.com (abhmp0008.oracle.com [141.146.116.14])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0680e5PQ007326;
        Wed, 8 Jul 2020 00:40:05 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.231.196)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 07 Jul 2020 17:40:05 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 1/3 v4] KVM: x86: Create mask for guest CR4 reserved bits in
 kvm_update_cpuid()
Date: Wed,  8 Jul 2020 00:39:55 +0000
Message-Id: <1594168797-29444-2-git-send-email-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594168797-29444-1-git-send-email-krish.sadhukhan@oracle.com>
References: <1594168797-29444-1-git-send-email-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9675
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=1
 adultscore=0 spamscore=0
 mlxscore=0 mlxlogscore=999 bulkscore=0 phishscore=0 malwarescore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2007080000
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9675
 signatures=668680
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 lowpriorityscore=0 mlxlogscore=999
 bulkscore=0 impostorscore=0 adultscore=0 cotscore=-2147483648 phishscore=0
 priorityscore=1501 clxscore=1015 malwarescore=0 suspectscore=1 spamscore=0
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2004280000 definitions=main-2007080000
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instead of creating the mask for guest CR4 reserved bits in kvm_valid_cr4(),
do it in kvm_update_cpuid() so that it can be reused instead of creating it
each time kvm_valid_cr4() is called.

Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/kvm_host.h |  1 +
 arch/x86/kvm/cpuid.c            |  2 ++
 arch/x86/kvm/x86.c              | 24 ++----------------------
 arch/x86/kvm/x86.h              | 21 +++++++++++++++++++++
 4 files changed, 26 insertions(+), 22 deletions(-)

```
#### [PATCH v2 1/3] KVM: nSVM: split kvm_init_shadow_npt_mmu() from kvm_init_shadow_mmu()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11651221
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id F07821709
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 09:36:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id DA59320739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 09:36:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HZr7MO37"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726302AbgGHJgZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 05:36:25 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:58276 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728259AbgGHJgY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jul 2020 05:36:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594200982;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=kALeRmOWsqvS9H2G8O5iL3YR6FPN8mEcBZ5niY5TzRs=;
        b=HZr7MO37D5Ofzg9JRLJlWHX4M8ChMTH5Z4YLUutHW8JSIACLeFSQ6WrJ5U54BiF5tfQeZV
        AHS++rZXVF/1mJQikJ/QPq02H0KJm+QVLDR4ojyUjm+Cd2KH5n9AMXfyEcFRqhxFXWws6d
        nEUqVzJX7kyoc9EXU/AyqlYdW+VU6SE=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-75-xp9Mlz1-P3C9M_UVthjrdg-1; Wed, 08 Jul 2020 05:36:19 -0400
X-MC-Unique: xp9Mlz1-P3C9M_UVthjrdg-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id A92E718CB722;
        Wed,  8 Jul 2020 09:36:17 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 853BD5C221;
        Wed,  8 Jul 2020 09:36:15 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Junaid Shahid <junaids@google.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/3] KVM: nSVM: split kvm_init_shadow_npt_mmu() from
 kvm_init_shadow_mmu()
Date: Wed,  8 Jul 2020 11:36:09 +0200
Message-Id: <20200708093611.1453618-2-vkuznets@redhat.com>
In-Reply-To: <20200708093611.1453618-1-vkuznets@redhat.com>
References: <20200708093611.1453618-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As a preparatory change for moving kvm_mmu_new_pgd() from
nested_prepare_vmcb_save() to nested_svm_init_mmu_context() split
kvm_init_shadow_npt_mmu() from kvm_init_shadow_mmu(). This also makes
the code look more like nVMX (kvm_init_shadow_ept_mmu()).

No functional change intended.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/mmu.h        |  3 ++-
 arch/x86/kvm/mmu/mmu.c    | 31 ++++++++++++++++++++++++-------
 arch/x86/kvm/svm/nested.c |  3 ++-
 3 files changed, 28 insertions(+), 9 deletions(-)

```
#### [PATCH kvm-unit-tests] svm: fix clobbers for svm_vmrun
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11651295
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BAE7913B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 10:35:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A173320739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 10:35:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GXTcItW0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728290AbgGHKfU (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 06:35:20 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:34259 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1725972AbgGHKfU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jul 2020 06:35:20 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594204519;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=trlJtT0rZ2sqGWqmQPOh1MYBjEiBnTH6WW16+k+sSw4=;
        b=GXTcItW0VozRAFdDk4dgxTySjGfI/w9CB41rZQJQ2+crcI0wqQofIeMpxQtzWGMETf2gL+
        T5IXFutak8MhVFsBBkin8S4x37th35ZLMTDPuibmMOXPrxsyVsQdUBNbhM7BZEvxYwlYgv
        0zcJMcBf4C3WT5KMEKs/yzL8pLmo5ig=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-449-k4MIU8deNVSS3Cz85xjFZg-1; Wed, 08 Jul 2020 06:35:16 -0400
X-MC-Unique: k4MIU8deNVSS3Cz85xjFZg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E7CC31080
        for <kvm@vger.kernel.org>; Wed,  8 Jul 2020 10:35:15 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AA24879248
        for <kvm@vger.kernel.org>; Wed,  8 Jul 2020 10:35:15 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] svm: fix clobbers for svm_vmrun
Date: Wed,  8 Jul 2020 06:35:15 -0400
Message-Id: <20200708103515.19477-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

r15 is used by ASM_VMRUN_CMD, so we need to mark it as clobbered.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/svm.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [kvm-unit-tests v3 PATCH] s390x/cpumodel: The missing DFP facility on TCG is expected
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11651777
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B3A1313B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 15:01:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9AC012078D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 15:01:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="DjrQhtU0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730074AbgGHPBD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 11:01:03 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:52853 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729863AbgGHPBD (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 8 Jul 2020 11:01:03 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594220461;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc; bh=xyg56AEaWg6EcPRPyzmB7YBwfS46RhbTFTWb5hVryyY=;
        b=DjrQhtU0+PdysxvU+UeNBExngRKp5+qFBT8adVZn0AwpYeix2aDf7FoJSSJZ0OOb9Fqnhd
        toi8pwb9syJlCEFgbKHtItUEcc69E7kYCQ8elf0W9nlkn9TzpkaVQpj025JcYZWeSjeISL
        FsMenuiesZyvWFz/RlAAxWK/3X5YmY4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-193-aMk1_cTXM1-f_24Y2BcanQ-1; Wed, 08 Jul 2020 11:00:59 -0400
X-MC-Unique: aMk1_cTXM1-f_24Y2BcanQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5F8E2189E55F;
        Wed,  8 Jul 2020 15:00:32 +0000 (UTC)
Received: from thuth.com (ovpn-114-90.ams2.redhat.com [10.36.114.90])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B85A05BAC3;
        Wed,  8 Jul 2020 15:00:27 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: Janosch Frank <frankja@linux.ibm.com>, david@redhat.com,
        kvm@vger.kernel.org
Cc: Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>
Subject: [kvm-unit-tests v3 PATCH] s390x/cpumodel: The missing DFP facility on
 TCG is expected
Date: Wed,  8 Jul 2020 17:00:25 +0200
Message-Id: <20200708150025.20631-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When running the kvm-unit-tests with TCG on s390x, the cpumodel test
always reports the error about the missing DFP (decimal floating point)
facility. This is kind of expected, since DFP is not required for
running Linux and thus nobody is really interested in implementing
this facility in TCG. Thus let's mark this as an expected error instead,
so that we can run the kvm-unit-tests also with TCG without getting
test failures that we do not care about.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: David Hildenbrand <david@redhat.com>
---
 v3:
 - Moved the is_tcg() function to the library so that it can be used
   later by other tests, too
 - Make sure to call alloc_page() and stsi() only once

 v2:
 - Rewrote the logic, introduced expected_tcg_fail flag
 - Use manufacturer string instead of VM name to detect TCG

 lib/s390x/vm.c   | 46 ++++++++++++++++++++++++++++++++++++++++++++++
 lib/s390x/vm.h   | 14 ++++++++++++++
 s390x/Makefile   |  1 +
 s390x/cpumodel.c | 19 +++++++++++++------
 4 files changed, 74 insertions(+), 6 deletions(-)
 create mode 100644 lib/s390x/vm.c
 create mode 100644 lib/s390x/vm.h

diff --git a/lib/s390x/vm.c b/lib/s390x/vm.c
new file mode 100644
index 0000000..c852713
--- /dev/null
+++ b/lib/s390x/vm.c
@@ -0,0 +1,46 @@
+/*
+ * Functions to retrieve VM-specific information
+ *
+ * Copyright (c) 2020 Red Hat Inc
+ *
+ * Authors:
+ *  Thomas Huth <thuth@redhat.com>
+ *
+ * SPDX-License-Identifier: LGPL-2.1-or-later
+ */
+
+#include <libcflat.h>
+#include <alloc_page.h>
+#include <asm/arch_def.h>
+#include "vm.h"
+
+/**
+ * Detect whether we are running with TCG (instead of KVM)
+ */
+bool vm_is_tcg(void)
+{
+	const char qemu_ebcdic[] = { 0xd8, 0xc5, 0xd4, 0xe4 };
+	static bool initialized = false;
+	static bool is_tcg = false;
+	uint8_t *buf;
+
+	if (initialized)
+		return is_tcg;
+
+	buf = alloc_page();
+	if (!buf)
+		return false;
+
+	if (stsi(buf, 1, 1, 1))
+		goto out;
+
+	/*
+	 * If the manufacturer string is "QEMU" in EBCDIC, then we
+	 * are on TCG (otherwise the string is "IBM" in EBCDIC)
+	 */
+	is_tcg = !memcmp(&buf[32], qemu_ebcdic, sizeof(qemu_ebcdic));
+	initialized = true;
+out:
+	free_page(buf);
+	return is_tcg;
+}
diff --git a/lib/s390x/vm.h b/lib/s390x/vm.h
new file mode 100644
index 0000000..33008d8
--- /dev/null
+++ b/lib/s390x/vm.h
@@ -0,0 +1,14 @@
+/*
+ * Functions to retrieve VM-specific information
+ *
+ * Copyright (c) 2020 Red Hat Inc
+ *
+ * SPDX-License-Identifier: LGPL-2.1-or-later
+ */
+
+#ifndef S390X_VM_H
+#define S390X_VM_H
+
+bool vm_is_tcg(void);
+
+#endif  /* S390X_VM_H */
```
#### [PATCH] KVM: x86: Make CR4.VMXE reserved for the guest
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11651345
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 87FF0739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 11:03:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6F9F620739
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 11:03:58 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZNnzLjcr"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728706AbgGHLDz (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 07:03:55 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:41503 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728454AbgGHLDy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 8 Jul 2020 07:03:54 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594206234;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=X7JqGrX6+FRCRSoYELtArJatwC752X2T97lt6/es+Gg=;
        b=ZNnzLjcr1WJMYz5qNvBlcrHtqJymhlP64CopFAXQ6ixHKgQk0nuiWWG3CZZXLkoHTrTMRG
        rqx31CGwyHMwLmurdxDpW3qSwgKwMCqPhsgwXDciWEsKsNIpDVJxleurG3byS22Y0/Cmfe
        9G+GVe7599b1wvxa54I1rfhYKnYIL4c=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-449-89poVGgePnqb6q3haNmrDw-1; Wed, 08 Jul 2020 07:03:52 -0400
X-MC-Unique: 89poVGgePnqb6q3haNmrDw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 91EDD8015F5;
        Wed,  8 Jul 2020 11:03:51 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 402DB7848A;
        Wed,  8 Jul 2020 11:03:51 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86: Make CR4.VMXE reserved for the guest
Date: Wed,  8 Jul 2020 07:03:50 -0400
Message-Id: <20200708110350.848997-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CR4.VMXE is reserved unless the VMX CPUID bit is set.  On Intel,
it is also tested by vmx_set_cr4, but AMD relies on kvm_valid_cr4,
so fix it.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/x86.h | 2 ++
 1 file changed, 2 insertions(+)

```
#### [PATCH] KVM/x86: pmu: Fix #GP condition check for RDPMC emulation
##### From: Like Xu <like.xu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Like Xu <like.xu@linux.intel.com>
X-Patchwork-Id: 11650937
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BA97913B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 07:45:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A5EE220760
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 07:45:53 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726923AbgGHHpr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 03:45:47 -0400
Received: from mga14.intel.com ([192.55.52.115]:6526 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726281AbgGHHpr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jul 2020 03:45:47 -0400
IronPort-SDR: 
 1TH7ZiWnXz6YvyaMjkgMNMKMejproPQnhzLcO2RnaFkmQgl5xtfkO/qmT+fLGejoAWS9CEQUnP
 u/EfmfqJ/o+g==
X-IronPort-AV: E=McAfee;i="6000,8403,9675"; a="146824183"
X-IronPort-AV: E=Sophos;i="5.75,327,1589266800";
   d="scan'208";a="146824183"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga001.jf.intel.com ([10.7.209.18])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Jul 2020 00:45:46 -0700
IronPort-SDR: 
 FipVNnyyiizItsTNhBtmRKLVSIErnlGiOOG8ZI0gQZC9cTVjabJ14eM0tmizH7RYE6Zxi1gFS0
 ljEjTumUXPBQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,327,1589266800";
   d="scan'208";a="358029182"
Received: from sqa-gate.sh.intel.com (HELO clx-ap-likexu.tsp.org)
 ([10.239.48.212])
  by orsmga001.jf.intel.com with ESMTP; 08 Jul 2020 00:45:44 -0700
From: Like Xu <like.xu@linux.intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Joerg Roedel <joro@8bytes.org>, linux-kernel@vger.kernel.org,
        Like Xu <like.xu@linux.intel.com>
Subject: [PATCH] KVM/x86: pmu: Fix #GP condition check for RDPMC emulation
Date: Wed,  8 Jul 2020 15:44:09 +0800
Message-Id: <20200708074409.39028-1-like.xu@linux.intel.com>
X-Mailer: git-send-email 2.21.3
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In guest protected mode, if the current privilege level
is not 0 and the PCE flag in the CR4 register is cleared,
we will inject a #GP for RDPMC usage.

Signed-off-by: Like Xu <like.xu@linux.intel.com>
---
 arch/x86/kvm/pmu.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH] kvm: x86: replace kvm_spec_ctrl_test_value with runtime test on the host
##### From: Maxim Levitsky <mlevitsk@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Maxim Levitsky <mlevitsk@redhat.com>
X-Patchwork-Id: 11651441
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B112C60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 11:57:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 98ED120775
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 11:57:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="RFakt1CJ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728866AbgGHL5q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 07:57:46 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:59794 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728853AbgGHL5p (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 8 Jul 2020 07:57:45 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594209463;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=xxyPm+jDOr7wCv3oAZynzwxs2yrC7rLwPNCtJFDBYtU=;
        b=RFakt1CJRhWuoNj1EB81aUSYqErsO5Rvsd2O25jw/CcBayGcuFsrn6/a7SS6zBqHFftpsW
        080xBcq7G5BfNg2cJLZIKb4LKYCnr/oWTYYm34O/XjWP5yxQapNVdtZhjSs9lwyyLRRkdu
        j5vAz0uaDr3+kDqFaXI4VDQ6MJ7V1Hk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-279-itPGOpVvOzyEQMgo2DBuUg-1; Wed, 08 Jul 2020 07:57:39 -0400
X-MC-Unique: itPGOpVvOzyEQMgo2DBuUg-1
Received: from smtp.corp.redhat.com (int-mx03.intmail.prod.int.phx2.redhat.com
 [10.5.11.13])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 54F221902EA0;
        Wed,  8 Jul 2020 11:57:37 +0000 (UTC)
Received: from starship.redhat.com (unknown [10.35.206.247])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9B60679247;
        Wed,  8 Jul 2020 11:57:32 +0000 (UTC)
From: Maxim Levitsky <mlevitsk@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Ingo Molnar <mingo@redhat.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        linux-kernel@vger.kernel.org (open list:X86 ARCHITECTURE (32-BIT AND
        64-BIT)),
        x86@kernel.org (maintainer:X86 ARCHITECTURE (32-BIT AND 64-BIT)),
        Wanpeng Li <wanpengli@tencent.com>,
        Joerg Roedel <joro@8bytes.org>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Borislav Petkov <bp@alien8.de>,
        Maxim Levitsky <mlevitsk@redhat.com>
Subject: [PATCH] kvm: x86: replace kvm_spec_ctrl_test_value with runtime test
 on the host
Date: Wed,  8 Jul 2020 14:57:31 +0300
Message-Id: <20200708115731.180097-1-mlevitsk@redhat.com>
In-Reply-To: <e49c6f78-ac9a-b001-b3b6-7c7dcccc182c@redhat.com>
References: <e49c6f78-ac9a-b001-b3b6-7c7dcccc182c@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.13
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

To avoid complex and in some cases incorrect logic in
kvm_spec_ctrl_test_value, just try the guest's given value on the host
processor instead, and if it doesn't #GP, allow the guest to set it.

One such case is when host CPU supports STIBP mitigation
but doesn't support IBRS (as is the case with some Zen2 AMD cpus),
and in this case we were giving guest #GP when it tried to use STIBP

The reason why can can do the host test is that IA32_SPEC_CTRL msr is
passed to the guest, after the guest sets it to a non zero value
for the first time (due to performance reasons),
and as as result of this, it is pointless to emulate #GP condition on
this first access, in a different way than what the host CPU does.

This is based on a patch from Sean Christopherson, who suggested this idea.

Fixes: 6441fa6178f5 ("KVM: x86: avoid incorrect writes to host MSR_IA32_SPEC_CTRL")

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Maxim Levitsky <mlevitsk@redhat.com>
---
 arch/x86/kvm/svm/svm.c |  2 +-
 arch/x86/kvm/vmx/vmx.c |  2 +-
 arch/x86/kvm/x86.c     | 38 +++++++++++++++++++++-----------------
 arch/x86/kvm/x86.h     |  2 +-
 4 files changed, 24 insertions(+), 20 deletions(-)

```
#### [PATCH] KVM: x86: take as_id into account when checking PGD
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11651723
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D048F618
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 14:00:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B89692078B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 14:00:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="KLwi9sL3"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729677AbgGHOAk (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 10:00:40 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:30567 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728932AbgGHOAk (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 8 Jul 2020 10:00:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594216838;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=qPr0eL60h+DsRpfuaobt35zdISOXizza2r3opqrQCz0=;
        b=KLwi9sL37dbgYv0VA6tG9WfUosYBtuqJRDgYD/HoP4MidTC/LKSJGMuUhIKLQSUyQ09hm/
        tnnEMxqy88AnLg/pMm9vKAeeAAevzlx745fS4WQfKlt5CVsUiA2JouSQ3JW0hbAWEPxUgM
        ldWkgSIz6yK+5Kz2ynIvz3yBjYghSbA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-214-EiqG4VkKOCG6ODFfeWtUJg-1; Wed, 08 Jul 2020 10:00:37 -0400
X-MC-Unique: EiqG4VkKOCG6ODFfeWtUJg-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2DA8E8015F7;
        Wed,  8 Jul 2020 14:00:34 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3AE6078493;
        Wed,  8 Jul 2020 14:00:25 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>, linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86: take as_id into account when checking PGD
Date: Wed,  8 Jul 2020 16:00:23 +0200
Message-Id: <20200708140023.1476020-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

OVMF booted guest running on shadow pages crashes on TRIPLE FAULT after
enabling paging from SMM. The crash is triggered from mmu_check_root() and
is caused by kvm_is_visible_gfn() searching through memslots with as_id = 0
while vCPU may be in a different context (address space).

Introduce kvm_vcpu_is_visible_gfn() and use it from mmu_check_root().

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/mmu/mmu.c   | 2 +-
 include/linux/kvm_host.h | 1 +
 virt/kvm/kvm_main.c      | 8 ++++++++
 3 files changed, 10 insertions(+), 1 deletion(-)

```
#### [PATCH v3 1/8] KVM: X86: Reset vcpu->arch.cpuid_nent to 0 if SET_CPUID* fails
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11650717
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3F74E13B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 06:51:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2DD5420771
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 06:51:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729875AbgGHGvD (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 02:51:03 -0400
Received: from mga11.intel.com ([192.55.52.93]:5284 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726171AbgGHGvD (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jul 2020 02:51:03 -0400
IronPort-SDR: 
 +oW0ifRZDuYkgnZTFyCKpBQDNq0yX4oRqTYkBSDW8hTRrrdlRcpgczzXlTNSUTqOn/2pLiofv8
 QaLQyDhrCOrA==
X-IronPort-AV: E=McAfee;i="6000,8403,9675"; a="145852063"
X-IronPort-AV: E=Sophos;i="5.75,326,1589266800";
   d="scan'208";a="145852063"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga005.jf.intel.com ([10.7.209.41])
  by fmsmga102.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Jul 2020 23:51:02 -0700
IronPort-SDR: 
 IE1br+pQ/SIt4czU36ckXrrO+vx5wZx8UFMLiqChEc5ziO38xV/44+R6gcLOMYUb3asV4cR4hA
 RUBvWsrFouSA==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,326,1589266800";
   d="scan'208";a="457399090"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by orsmga005.jf.intel.com with ESMTP; 07 Jul 2020 23:50:59 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        linux-doc@vger.kernel.org, Jonathan Corbet <corbet@lwn.net>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Joerg Roedel <joro@8bytes.org>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v3 1/8] KVM: X86: Reset vcpu->arch.cpuid_nent to 0 if
 SET_CPUID* fails
Date: Wed,  8 Jul 2020 14:50:47 +0800
Message-Id: <20200708065054.19713-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200708065054.19713-1-xiaoyao.li@intel.com>
References: <20200708065054.19713-1-xiaoyao.li@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current implementation keeps userspace input of CPUID configuration and
cpuid->nent even if kvm_update_cpuid() fails. Reset vcpu->arch.cpuid_nent
to 0 for the case of failure as a simple fix.

Besides, update the doc to explicitly state that if IOCTL SET_CPUID*
fail KVM gives no gurantee that previous valid CPUID configuration is
kept.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 Documentation/virt/kvm/api.rst | 4 ++++
 arch/x86/kvm/cpuid.c           | 4 ++++
 2 files changed, 8 insertions(+)

```
#### [PATCH v4] x86/speculation/l1tf: Add KConfig for setting the L1D cache flush mode
##### From: Abhishek Bhardwaj <abhishekbh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Abhishek Bhardwaj <abhishekbh@google.com>
X-Patchwork-Id: 11652291
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 82C18913
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:25:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 6BA8B2065D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:25:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="M8YyI1cO"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726121AbgGHTZw (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 15:25:52 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:39658 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725848AbgGHTZv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jul 2020 15:25:51 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 2895BC061A0B
        for <kvm@vger.kernel.org>; Wed,  8 Jul 2020 12:25:51 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id t7so37899085ybk.2
        for <kvm@vger.kernel.org>; Wed, 08 Jul 2020 12:25:51 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=M9lyp9aB5g7rtu5MiUgfbjfYjZdXTeZw0fg1xRRWYVs=;
        b=M8YyI1cOHmEenNKeoDViXyo+AQX0kE3jm3iwIVLWA4P4XH0qdh5ysQ43fTzbQyPFO1
         MnbGya77iRrx6CFhaFI3kZJIVnTEX7bBL294rMqemb+dfKhEnHxAR8WMFhwGJmReM7kB
         ji00aDP4DTe7S5vq/p4kxMEV2m5CnVJx5xZ/25UBgFp3w4ISZyGMhTIftqZRMS1lRnnY
         1CRtpf3JVllxgJcU1jTYPxlTTXNn/OiHaFA+KoY13oBNKKA6mx0OlLrLayW/DKVYPNf3
         wpknbzNy1pWoLwNKWIOH2IaHKLgOF3R6o5cxD6j9tfA7ZJQOnzcgQKGxfufUl0B8rGAx
         FDkg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=M9lyp9aB5g7rtu5MiUgfbjfYjZdXTeZw0fg1xRRWYVs=;
        b=e15Wt5SKpY+uKz/oFNTz9QU8lYkZ8j5kjOkEDg2bia1M5ope6Ku4PlrS2/JFSSP1nv
         u9aniNZfwj9kmsRrNovULyLHk2vRaPTdUvXp6/ZWAvSfD2ALEyP/KUNvNquWWc59xY+g
         PzDPuPP0qh0h4KldK0pxObGBlQUr2iwrg6QwoG4jo91lm+nEuDFGcOvIs1ZyHnBdZmXf
         QvFSdtzbilhgSKcS93O/YaNZ8cvV5j+UGTMMx/PshHZVTDqDrcp3eO3hDgw/CHkNLfEz
         ELFFTwh6/SHt5i5WfAlKi7Ty5teFH86fylH6G7tIj3+HfhKPFuANFJyvs6i/sm7SMZO8
         znOQ==
X-Gm-Message-State: AOAM53379gunz2Dyae4egf2FUYiEGJv33iApca5YtseURwUUZfkaA1jj
        DxrS2avRmgsuV5BvBCUjkSJwkY8x+iize2FL
X-Google-Smtp-Source: 
 ABdhPJyazEsJdyohKqw0P5UhxeRdYkv49fC19GKY5MKzNLPXDWzWA5Q0Qo9y8EnnTzNN13bmHta9B5nyV4WATkYT
X-Received: by 2002:a25:aaf1:: with SMTP id
 t104mr101753518ybi.163.1594236350296;
 Wed, 08 Jul 2020 12:25:50 -0700 (PDT)
Date: Wed,  8 Jul 2020 12:25:46 -0700
Message-Id: <20200708192546.4068026-1-abhishekbh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.27.0.383.g050319c2ae-goog
Subject: [PATCH v4] x86/speculation/l1tf: Add KConfig for setting the L1D
 cache flush mode
From: Abhishek Bhardwaj <abhishekbh@google.com>
To: LKML <linux-kernel@vger.kernel.org>
Cc: Abhishek Bhardwaj <abhishekbh@google.com>,
        Anthony Steinhauser <asteinhauser@google.com>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Mark Gross <mgross@linux.intel.com>,
        Mike Rapoport <rppt@linux.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Pawan Gupta <pawan.kumar.gupta@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Tony Luck <tony.luck@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Waiman Long <longman@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>, kvm@vger.kernel.org,
        x86@kernel.org
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds a new kernel configuration that sets the l1d cache
flush setting at compile time rather than at run time.

The reasons for this change are as follows -

 - Kernel command line arguments are getting unwieldy. These parameters
 are not a scalable way to set the kernel config. They're intended as a
 super limited way for the bootloader to pass info to the kernel and
 also as a way for end users who are not compiling the kernel themselves
 to tweak the kernel behavior.

 - Also, if a user wants this setting from the start. It's a definite
 smell that it deserves to be a compile time thing rather than adding
 extra code plus whatever miniscule time at runtime to pass an
 extra argument.

 - Finally, it doesn't preclude the runtime / kernel command line way.
 Users are free to use those as well.

Signed-off-by: Abhishek Bhardwaj <abhishekbh@google.com>
---

Changes in v4:
- Add motivation for the change in the commit message.

Changes in v3:
- Change depends on to only x86_64.
- Remove copy paste errors at the end of the KConfig.

Changes in v2:
- Fix typo in the help of the new KConfig.

 arch/x86/kernel/cpu/bugs.c |  8 ++++++++
 arch/x86/kvm/Kconfig       | 13 +++++++++++++
 2 files changed, 21 insertions(+)

```
#### [PATCH v5] x86/speculation/l1tf: Add KConfig for setting the L1D cache flush mode
##### From: Abhishek Bhardwaj <abhishekbh@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Abhishek Bhardwaj <abhishekbh@google.com>
X-Patchwork-Id: 11652393
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5C9BB60D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:47:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 44115206DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:47:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="QOUjGeLt"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726065AbgGHTrV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 15:47:21 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43014 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725446AbgGHTrU (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jul 2020 15:47:20 -0400
Received: from mail-pf1-x449.google.com (mail-pf1-x449.google.com
 [IPv6:2607:f8b0:4864:20::449])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 9781CC061A0B
        for <kvm@vger.kernel.org>; Wed,  8 Jul 2020 12:47:20 -0700 (PDT)
Received: by mail-pf1-x449.google.com with SMTP id p127so10976577pfb.18
        for <kvm@vger.kernel.org>; Wed, 08 Jul 2020 12:47:20 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:message-id:mime-version:subject:from:to:cc;
        bh=pljlg3yHFHSvTFF5i62V0f3vLeabEmCDDf596zZbJM8=;
        b=QOUjGeLtOAJD7kgc4YCP+sBsOWR5DJaZmc58t58h2EH8HPeOhHgvihOeBoBz41z+h7
         lk1O16q6sWuFZvb1Kv6sHeJthkBqfgF2qsd/qhvyKS/S5WAaflpfrbqSIBn1+0fa9lyX
         iS4S1CC2nll4cumNd3QhC7BkOedqQRBAgAicF545XYfTjAxsUBUvpBQbUeLyJAsr2f3q
         r270qhAGqPIkeOxlgCn5Wz5tZjJdREM6VuKAjngTgE0lu0qPpnksRkKcwzVtoUrk6sJ5
         5SUR+2PKD8qz79BJ2zuoJ7zlEHWPLVIlUzY8S8GdZPG77LadBr9xaUq0u6Ql9FOwH27X
         TEnw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:message-id:mime-version:subject:from:to:cc;
        bh=pljlg3yHFHSvTFF5i62V0f3vLeabEmCDDf596zZbJM8=;
        b=sQRGBMe2VqwLEbwk9BARG5zNs5Kt7BKaOdH025lQeq/U++F+VJCOngqY8oqcdUGWbF
         x/glto2YPI+LHcU/gJ6fPOAlMV8XSNieU/+ZwGlhQt7D5EUQ62PqzMeKjej+HlS74T8A
         VanBDcQwleLEHhoG4XDrezDvjRCtDqdParjTO7a9ItH/wnZyWEn8n+nUvNH0W/DfdbWp
         9xPTIS7VOmFCaYDzWf86hUIg6rASTwuG429Bt104Ubdrd86C+FindOHykkoJx2i/2DnG
         +O2WVKyRS65AbFO6VrMN/r6rENMaT5vsN8I8AQ3bDDU0nSyMfFchrFePpMoWZze/YEGO
         lJ5A==
X-Gm-Message-State: AOAM531CmvyBT9XXOIV0bD90tKsZAxurIcIx909/fVnyUDY6jvasQV5K
        BAUfQICJ+KUSBMbPTsU/qqHi03Q8bYh+yGFm
X-Google-Smtp-Source: 
 ABdhPJwu+cqA7SFopH7sDGho/uhjflNJjwTBWDtSPL4H1srwzxx+pUWfCqcSwPaH9Fom19mDm0ylxD8+2+ZFHvKK
X-Received: by 2002:a17:902:a60d:: with SMTP id
 u13mr52502800plq.46.1594237639483;
 Wed, 08 Jul 2020 12:47:19 -0700 (PDT)
Date: Wed,  8 Jul 2020 12:47:15 -0700
Message-Id: <20200708194715.4073300-1-abhishekbh@google.com>
Mime-Version: 1.0
X-Mailer: git-send-email 2.27.0.383.g050319c2ae-goog
Subject: [PATCH v5] x86/speculation/l1tf: Add KConfig for setting the L1D
 cache flush mode
From: Abhishek Bhardwaj <abhishekbh@google.com>
To: LKML <linux-kernel@vger.kernel.org>
Cc: Abhishek Bhardwaj <abhishekbh@google.com>,
        Anthony Steinhauser <asteinhauser@google.com>,
        Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>, Ingo Molnar <mingo@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Josh Poimboeuf <jpoimboe@redhat.com>,
        Mark Gross <mgross@linux.intel.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Pawan Gupta <pawan.kumar.gupta@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Tony Luck <tony.luck@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Waiman Long <longman@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>, kvm@vger.kernel.org,
        x86@kernel.org
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This change adds a new kernel configuration that sets the l1d cache
flush setting at compile time rather than at run time.

The reasons for this change are as follows -

 - Kernel command line arguments are getting unwieldy. These parameters
 are not a scalable way to set the kernel config. They're intended as a
 super limited way for the bootloader to pass info to the kernel and
 also as a way for end users who are not compiling the kernel themselves
 to tweak the kernel behavior.

 - Also, if a user wants this setting from the start. It's a definite
 smell that it deserves to be a compile time thing rather than adding
 extra code plus whatever miniscule time at runtime to pass an
 extra argument.

 - Finally, it doesn't preclude the runtime / kernel command line way.
 Users are free to use those as well.

Signed-off-by: Abhishek Bhardwaj <abhishekbh@google.com>
---

Changes in v5:
- Fix indentation of the help text in the KConfig.

Changes in v4:
- Add motivation for the change in the commit message.

Changes in v3:
- Change depends on to only x86_64.
- Remove copy paste errors at the end of the KConfig.

Changes in v2:
- Fix typo in the help of the new KConfig.

 arch/x86/kernel/cpu/bugs.c |  8 ++++++++
 arch/x86/kvm/Kconfig       | 13 +++++++++++++
 2 files changed, 21 insertions(+)

```
#### [patch V2 1/7] x86/kvm: Move context tracking where it belongsReferences: <20200708195153.746357686@linutronix.de>
##### From: Thomas Gleixner <tglx@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Gleixner <tglx@linutronix.de>
X-Patchwork-Id: 11652401
Return-Path: <SRS0=kMba=AT=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1127814DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:53:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id F00542082E
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed,  8 Jul 2020 19:53:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="ZWD4T0pP";
	dkim=permerror (0-bit key) header.d=linutronix.de header.i=@linutronix.de
 header.b="L2TJL1vZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726444AbgGHTxo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 8 Jul 2020 15:53:44 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:43984 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726338AbgGHTxk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 8 Jul 2020 15:53:40 -0400
Received: from galois.linutronix.de (Galois.linutronix.de
 [IPv6:2a0a:51c0:0:12e:550::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 821D9C061A0B;
        Wed,  8 Jul 2020 12:53:40 -0700 (PDT)
Message-Id: <20200708195321.724574345@linutronix.de>
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020; t=1594238018;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
  references:references;
        bh=cW72dPqtZuMh9vmtb+qgVOPPO4Xy97uOj4LUQgr9ay8=;
        b=ZWD4T0pPums1mWXn/Y1A2+KqF94bKL9jeD+LHsCT4ub01yuZQDDT25AFDF7i28Uig4bwV+
        bGaehYaMcAyDu7Jz6T3ANHfylRF86QlDFvzzr+OaiqbARirhAxvn2L60UJALnIhKPLzTK3
        dFSQryKIEQfKHLfUiYzphiHPFKZRa/+gj0RwkvUqykcAotS4XXiAFOjO+OpZdW5IMwVFlt
        KjaRQBu8gRdWqRBJMcb+ORAUyAq+T4PFcJ06qYKZ/wuAgESiKIGrCl/6NDqcC+gnSkHFO7
        sxL8DRWYvy7yKapZd09lg6CEOukrKFtzQkNN6OU4Ep298dWm+xeL9++cpXp5oQ==
DKIM-Signature: v=1; a=ed25519-sha256; c=relaxed/relaxed; d=linutronix.de;
        s=2020e; t=1594238018;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
  references:references;
        bh=cW72dPqtZuMh9vmtb+qgVOPPO4Xy97uOj4LUQgr9ay8=;
        b=L2TJL1vZnF4cYPM/JhiZopc7KpQpgFxAUZlosxop8UxF8/nKKyUwDsR1A4ahInKiSsOj1C
        lyWDtQufAablizBw==
Date: Wed, 08 Jul 2020 21:51:54 +0200
From: Thomas Gleixner <tglx@linutronix.de>
To: LKML <linux-kernel@vger.kernel.org>
Cc: x86@kernel.org, Paolo Bonzini <pbonzini@redhat.com>,
        kvm@vger.kernel.org,
        Alexandre Chartre <alexandre.chartre@oracle.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Juergen Gross <jgross@suse.com>
Subject: [patch V2 1/7] x86/kvm: Move context tracking where it belongs
References: <20200708195153.746357686@linutronix.de>
MIME-Version: 1.0
Content-transfer-encoding: 8-bit
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Thomas Gleixner <tglx@linutronix.de>

Context tracking for KVM happens way too early in the vcpu_run()
code. Anything after guest_enter_irqoff() and before guest_exit_irqoff()
cannot use RCU and should also be not instrumented.

The current way of doing this covers way too much code. Move it closer to
the actual vmenter/exit code.

Signed-off-by: Thomas Gleixner <tglx@linutronix.de>
Reviewed-by: Alexandre Chartre <alexandre.chartre@oracle.com>
Acked-by: Peter Zijlstra <peterz@infradead.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/svm.c |   16 ++++++++++++++++
 arch/x86/kvm/vmx/vmx.c |   10 ++++++++++
 arch/x86/kvm/x86.c     |    2 --
```
