#### [PATCH  1/2 v5] KVM: nVMX: Fix VMX preemption timer migrationFrom: Makarand Sonare <makarandsonare@google.com>
##### From: Makarand Sonare <makarandsonare@google.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Makarand Sonare <makarandsonare@google.com>
X-Patchwork-Id: 11571413
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 682F9739
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 21:51:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4AAF1208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 21:51:24 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=google.com header.i=@google.com
 header.b="MhqEZpLG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389442AbgEZVvX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 17:51:23 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:59486 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2389149AbgEZVvW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 May 2020 17:51:22 -0400
Received: from mail-yb1-xb49.google.com (mail-yb1-xb49.google.com
 [IPv6:2607:f8b0:4864:20::b49])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 97CB1C03E96D
        for <kvm@vger.kernel.org>; Tue, 26 May 2020 14:51:21 -0700 (PDT)
Received: by mail-yb1-xb49.google.com with SMTP id f187so1146220ybc.2
        for <kvm@vger.kernel.org>; Tue, 26 May 2020 14:51:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=google.com; s=20161025;
        h=date:in-reply-to:message-id:mime-version:references:subject:from:to
         :cc;
        bh=JWHMF6JVg9lYwlo4tr9+Htsvw+KzVzNxLnrw8YBwH6c=;
        b=MhqEZpLG03Wq1E83RP3x30fTHcGwsPZ/E+OFRrDz0noKa0hIrFa99Hd71ByeBL1Cbo
         skGcdkFfUaDG+XD+CZPR1NrkGKK5n0IDXQto3vjkd+cM+eZucb0W9gHreDIsnRwU1NsI
         SadoAPlpi9WBkiE3Ebn2PV4rVfOPJlSQqovp/BB7kS1CBGhwNDyNCTOQI53ruwyd/fa2
         eTYD/qfstMsrL3NNoyeYePnJiYj3r5vAWl6JMEh0X+G8iuCJDCwWP/PgWfImpxB2eCKZ
         Ok2P07olFErkrxgeRS1nhSpSGhYPRZUevMYsNF9CGXlETCViqI0AYUfHDpXhAjA8rdp/
         F4DA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:in-reply-to:message-id:mime-version
         :references:subject:from:to:cc;
        bh=JWHMF6JVg9lYwlo4tr9+Htsvw+KzVzNxLnrw8YBwH6c=;
        b=WLt1H+u4xpWOnMxIWHsjZtNfzaVWes74TiMRkDIJHrwwSuEvTh8qFAiAxxetmxt5lJ
         ySchVb3gWxbu6nwlFQc3dEsUGLKm9xavlWnel1oNZ0P1VjtE9T5uIUHrMuMms2o0qvWa
         TDOfmm597f7tKtHR/87kUZBN5WiTYvaWfkOv2y03ApiDb8+tBkAvaaRv+OWysonoNo7a
         zTItT0+pvxYAdS+GD90FJkLj1jxqtNP+mKJ7ViiV/a7ukASIr7Tmg9x3HE6FBVm+7TvE
         W7VcofLuQ+1GwdnCZW/TLZ4UPYaxtCXrD7/EzQx6T8cYj6cvuaY9NEgMCMKJ/ywVUytn
         YzBg==
X-Gm-Message-State: AOAM533fMbxKKJ2YzjYGbZoZ5214quW0Lg1CLdIBMYyOPc5mInB6FFl0
        VuzFsZUEiDW5q54RGQ1wyVfTjPB1NUrlKxOSgip53wmnB1CJSt2HcdBKBSTCVysPbR6m8v2n0B/
        peXwAlMqzG4t6LFacbQKyBA03tKSxLIuuJc9mfHSlWN0D5G0AfUuiy9w5MYsJmWRt8JpEi9DhYZ
        HcfMY=
X-Google-Smtp-Source: 
 ABdhPJxg3x4U0WIFdPA4MmlaQ/QG/G6ofjN4hRENHhXBx5fBqV7hcnty4PB2VL+O5fedW4m4w+5aAAU1tJKslM8sW0Gspw==
X-Received: by 2002:a25:b70b:: with SMTP id t11mr5071882ybj.171.1590529880720;
 Tue, 26 May 2020 14:51:20 -0700 (PDT)
Date: Tue, 26 May 2020 14:51:06 -0700
In-Reply-To: <20200526215107.205814-1-makarandsonare@google.com>
Message-Id: <20200526215107.205814-2-makarandsonare@google.com>
Mime-Version: 1.0
References: <20200526215107.205814-1-makarandsonare@google.com>
X-Mailer: git-send-email 2.27.0.rc0.183.gde8f92d652-goog
Subject: [PATCH  1/2 v5] KVM: nVMX: Fix VMX preemption timer migration
From: Makarand Sonare <makarandsonare@google.com>
To: kvm@vger.kernel.org, pshier@google.com, jmattson@google.com
Cc: Makarand Sonare <makarandsonare@google.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Peter Shier <pshier@google.com>

Add new field to hold preemption timer expiration deadline
appended to struct kvm_vmx_nested_state_hdr. This is to prevent
the first VM-Enter after migration from incorrectly restarting the timer
with the full timer value instead of partially decayed timer value.
KVM_SET_NESTED_STATE restarts timer using migrated state regardless
of whether L1 sets VM_EXIT_SAVE_VMX_PREEMPTION_TIMER.

Fixes: cf8b84f48a593 ("kvm: nVMX: Prepare for checkpointing L2 state")

Signed-off-by: Peter Shier <pshier@google.com>
Signed-off-by: Makarand Sonare <makarandsonare@google.com>
---
 Documentation/virt/kvm/api.rst  |  4 +++
 arch/x86/include/uapi/asm/kvm.h |  4 +++
 arch/x86/kvm/vmx/nested.c       | 55 ++++++++++++++++++++++++++++-----
 arch/x86/kvm/vmx/vmx.h          |  2 ++
 4 files changed, 57 insertions(+), 8 deletions(-)

--
2.27.0.rc0.183.gde8f92d652-goog

```
#### [GIT PULL 1/3] KVM: s390: vsie: Move conditional reschedule
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11570181
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4341813B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 09:33:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 2F037207CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 09:33:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728844AbgEZJdW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 05:33:22 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:15918 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728568AbgEZJdV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 26 May 2020 05:33:21 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 04Q9WUZY116029;
        Tue, 26 May 2020 05:33:20 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 316yqhxna6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 26 May 2020 05:33:20 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04Q9WutA117731;
        Tue, 26 May 2020 05:33:19 -0400
Received: from ppma02fra.de.ibm.com (47.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.71])
        by mx0a-001b2d01.pphosted.com with ESMTP id 316yqhxn9g-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 26 May 2020 05:33:19 -0400
Received: from pps.filterd (ppma02fra.de.ibm.com [127.0.0.1])
        by ppma02fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 04Q9VQ7t028746;
        Tue, 26 May 2020 09:33:18 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma02fra.de.ibm.com with ESMTP id 316uf8t91m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 26 May 2020 09:33:17 +0000
Received: from d06av25.portsmouth.uk.ibm.com (d06av25.portsmouth.uk.ibm.com
 [9.149.105.61])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 04Q9XFJD7799170
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 26 May 2020 09:33:15 GMT
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 32F3611C04A;
        Tue, 26 May 2020 09:33:15 +0000 (GMT)
Received: from d06av25.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1ECC011C058;
        Tue, 26 May 2020 09:33:15 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av25.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Tue, 26 May 2020 09:33:15 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id CF788E0260; Tue, 26 May 2020 11:33:14 +0200 (CEST)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>
Cc: KVM <kvm@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>,
        Cornelia Huck <cohuck@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        Claudio Imbrenda <imbrenda@linux.ibm.com>
Subject: [GIT PULL 1/3] KVM: s390: vsie: Move conditional reschedule
Date: Tue, 26 May 2020 11:33:11 +0200
Message-Id: <20200526093313.77976-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20200526093313.77976-1-borntraeger@de.ibm.com>
References: <20200526093313.77976-1-borntraeger@de.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.687
 definitions=2020-05-25_12:2020-05-25,2020-05-25 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0
 malwarescore=0 suspectscore=0 clxscore=1015 priorityscore=1501 bulkscore=0
 lowpriorityscore=0 mlxlogscore=963 phishscore=0 adultscore=0 mlxscore=0
 spamscore=0 cotscore=-2147483648 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2005260072
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Hildenbrand <david@redhat.com>

Let's move it to the outer loop, in case we ever run again into long
loops, trying to map the prefix. While at it, convert it to cond_resched().

Signed-off-by: David Hildenbrand <david@redhat.com>
Link: https://lore.kernel.org/r/20200403153050.20569-5-david@redhat.com
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Christian Borntraeger <borntraeger@de.ibm.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/vsie.c | 3 +--
 1 file changed, 1 insertion(+), 2 deletions(-)

```
#### [PATCH] KVM: arm64: Allow in-atomic injection of SPIs
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11570799
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AB25B1392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 16:11:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 94568207D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 16:11:44 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1590509504;
	bh=OfzjQ6qwUkq4xj9uEs3icHSWi5yhPJTMuRBRnHcDMOc=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=GNSmSFBw/EyyzhnZpQr39ehX68MdPOrRmqi1NhuVNFXRz9p9uDewMC4ivVoRIyEsD
	 JE0mtm7UPZPAD/nT6O9ERn+obq9i10fSwK02aMGBxBd6FpFV+kaGTTd//G8mxvl6Mv
	 Coajs5H5l+Y0jeGyEm0BcEggFnkk/Z252CCrpE5M=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388477AbgEZQLn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 12:11:43 -0400
Received: from mail.kernel.org ([198.145.29.99]:48432 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2388412AbgEZQLn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 May 2020 12:11:43 -0400
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 6FA9520787;
        Tue, 26 May 2020 16:11:42 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1590509502;
        bh=OfzjQ6qwUkq4xj9uEs3icHSWi5yhPJTMuRBRnHcDMOc=;
        h=From:To:Cc:Subject:Date:From;
        b=fwYJhxyhXbpAP1azX/w1PSR3utcinTPR1su9+GiO8MIfNEDZExGMTSpjkcG/4N41M
         /yrkF+/edaOXHMp3wdst4J7xljimX5w3liEMGCjoprGhsFbuQ/ERJ8N+VfnQ+koC+X
         82uEgf5J5x9qWjUn9U5RjhVVOdhOtZt4v4DFZREc=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1jdcB2-00FQrL-JD; Tue, 26 May 2020 17:11:40 +0100
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Eric Auger <eric.auger@redhat.com>, kernel-team@android.com
Subject: [PATCH] KVM: arm64: Allow in-atomic injection of SPIs
Date: Tue, 26 May 2020 17:11:36 +0100
Message-Id: <20200526161136.451312-1-maz@kernel.org>
X-Mailer: git-send-email 2.26.2
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, eric.auger@redhat.com,
 kernel-team@android.com
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On a system that uses SPIs to implement MSIs (as it would be
the case on a GICv2 system exposing a GICv2m to its guests),
we deny the possibility of injecting SPIs on the in-atomic
fast-path.

This results in a very large amount of context-switches
(roughly equivalent to twice the interrupt rate) on the host,
and suboptimal performance for the guest (as measured with
a test workload involving a virtio interface backed by vhost-net).
Given that GICv2 systems are usually on the low-end of the spectrum
performance wise, they could do without the aggravation.

We solved this for GICv3+ITS by having a translation cache. But
SPIs do not need any extra infrastructure, and can be immediately
injected in the virtual distributor as the locking is already
heavy enough that we don't need to worry about anything.

This halves the number of context switches for the same workload.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm64/kvm/vgic/vgic-irqfd.c | 20 ++++++++++++++++----
 arch/arm64/kvm/vgic/vgic-its.c   |  3 +--
 2 files changed, 17 insertions(+), 6 deletions(-)

```
#### [PATCH 01/28] KVM: x86: track manually whether an event has been injected
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11570955
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AD0001392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 17:25:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 962EE20823
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 17:25:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HjN0IlNb"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389056AbgEZRXR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 13:23:17 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:44456 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388944AbgEZRXQ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 May 2020 13:23:16 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590513795;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=zsEdUKbb64cuYor8Oe940GH4M856nl/MDSfp4PY7VdM=;
        b=HjN0IlNb3D57p6MKhmLNP2tEotSWIAcWfxh1cdshQbwbeGNwx3R20oU2cAyJ3SxN8wYlCM
        zDR/tRK7Z980XhPrsGW6XbRjQGGoWaxHxdt5FMgbVUxBcvo7Nm4HjdMUAv+Mc0/gJmQH9k
        1koKNjBiXs6uj1GUNxUtX0nvgnycWSk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-166-tDkVSMwVPNyrTROUAdq4iA-1; Tue, 26 May 2020 13:23:11 -0400
X-MC-Unique: tDkVSMwVPNyrTROUAdq4iA-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 41CBB835B43;
        Tue, 26 May 2020 17:23:10 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9F2441001B07;
        Tue, 26 May 2020 17:23:09 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: vkuznets@redhat.com, mlevitsk@redhat.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH 01/28] KVM: x86: track manually whether an event has been
 injected
Date: Tue, 26 May 2020 13:22:41 -0400
Message-Id: <20200526172308.111575-2-pbonzini@redhat.com>
In-Reply-To: <20200526172308.111575-1-pbonzini@redhat.com>
References: <20200526172308.111575-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instead of calling kvm_event_needs_reinjection, track its
future return value in a variable.  This will be useful in
the next patch.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/x86.c | 17 ++++++++++++-----
 1 file changed, 12 insertions(+), 5 deletions(-)

```
#### [PATCH 1/2] KVM: SVM: fix svn_pin_memory()'s use of get_user_pages_fast()
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11569947
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 22A9D913
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 06:22:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 06FCF207D8
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 06:22:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="dpvKsqJh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729016AbgEZGWO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 02:22:14 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:13893 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725271AbgEZGWN (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 May 2020 02:22:13 -0400
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5eccb53a0001>; Mon, 25 May 2020 23:20:42 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Mon, 25 May 2020 23:22:10 -0700
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Mon, 25 May 2020 23:22:10 -0700
Received: from HQMAIL101.nvidia.com (172.20.187.10) by HQMAIL111.nvidia.com
 (172.20.187.18) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Tue, 26 May
 2020 06:22:10 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Tue, 26 May 2020 06:22:10 +0000
Received: from sandstorm.nvidia.com (Not Verified[10.2.58.199]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5eccb5920002>; Mon, 25 May 2020 23:22:10 -0700
From: John Hubbard <jhubbard@nvidia.com>
To: LKML <linux-kernel@vger.kernel.org>
CC: Souptick Joarder <jrdr.linux@gmail.com>,
        John Hubbard <jhubbard@nvidia.com>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Thomas Gleixner <tglx@linutronix.de>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        "H . Peter Anvin" <hpa@zytor.com>, <x86@kernel.org>,
        <kvm@vger.kernel.org>
Subject: [PATCH 1/2] KVM: SVM: fix svn_pin_memory()'s use of
 get_user_pages_fast()
Date: Mon, 25 May 2020 23:22:06 -0700
Message-ID: <20200526062207.1360225-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20200526062207.1360225-1-jhubbard@nvidia.com>
References: <20200526062207.1360225-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1590474042; bh=AzbBhbmfNLGU9QQd3KrM41vIMJiGiViVOVN10y9DMkc=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Transfer-Encoding:Content-Type;
        b=dpvKsqJh4h5Z2BhpqEVc3v6UcgU5o/vCA95fTXvUOxYoScXTrr9Lg4O3ueM29978W
         4BLIV+gymq+4pv+u32F3pE98YnnwMlbCBi8nUAfIBb5BQ2srnsx2E/De5o3rUbTN0r
         yqiQDfmNk//62pRKdG76kAB2cKscT0ZjPabQkHn2lxzGmQ8J9912mcvZ8Ou9ENo/j7
         X1129T1qjZClMHyuBgxwQpv9HMJ2SDURPlXWVxKX4QEsNb6f4HZRk3folnOwMTaKDY
         ncopQzo4p78OypaWdCb9t4C+hrm3gwJj9tRxpZTI5yQBMI0ECuIsdQDwuSEsJCw/BF
         sXOuL3NvR/fGg==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

There are two problems in svn_pin_memory():

1) The return value of get_user_pages_fast() is stored in an
unsigned long, although the declared return value is of type int.
This will not cause any symptoms, but it is misleading.
Fix this by changing the type of npinned to "int".

2) The number of pages passed into get_user_pages_fast() is stored
in an unsigned long, even though get_user_pages_fast() accepts an
int. This means that it is possible to silently overflow the number
of pages.

Fix this by adding a WARN_ON_ONCE() and an early error return. The
npages variable is left as an unsigned long for convenience in
checking for overflow.

Fixes: 89c505809052 ("KVM: SVM: Add support for KVM_SEV_LAUNCH_UPDATE_DATA command")
Cc: Ingo Molnar <mingo@redhat.com>
Cc: Borislav Petkov <bp@alien8.de>
Cc: Thomas Gleixner <tglx@linutronix.de>
Cc: Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Cc: Wanpeng Li <wanpengli@tencent.com>
Cc: Jim Mattson <jmattson@google.com>
Cc: Joerg Roedel <joro@8bytes.org>
Cc: H. Peter Anvin <hpa@zytor.com>
Cc: x86@kernel.org
Cc: kvm@vger.kernel.org
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/kvm/svm/sev.c | 6 +++++-
 1 file changed, 5 insertions(+), 1 deletion(-)

```
#### [PATCH] s390/virtio: remove unused pm callbacks
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 11570189
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EC8C41392
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 09:36:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CA6B5207ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 09:36:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="PWR7Cth9"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728750AbgEZJgi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 05:36:38 -0400
Received: from us-smtp-1.mimecast.com ([207.211.31.81]:30416 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728746AbgEZJgh (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 26 May 2020 05:36:37 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590485796;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=N9CrJGv37BpytimFY2SmZJooBun68CG0VTdXjYuGNU0=;
        b=PWR7Cth9u07JrBgfSp56LV8VnaHP7N0mMke59WoSm7H16g3T8NJJlZgJcVELktaM9iIpmQ
        gInkGf/Pi55RaK6Oxy3TK4cdcwc2rf7QzfXtUM30Y3ee6jAMjG2Z2VpGnuOFiO4aMs3dmG
        SYWoMWDt5iOks2ltqcL55g8xKO6g5lo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-135-LiCUBOrPOJ2m6HPSepfNzQ-1; Tue, 26 May 2020 05:36:34 -0400
X-MC-Unique: LiCUBOrPOJ2m6HPSepfNzQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 46F80100A8F2;
        Tue, 26 May 2020 09:36:33 +0000 (UTC)
Received: from localhost (ovpn-113-77.ams2.redhat.com [10.36.113.77])
        by smtp.corp.redhat.com (Postfix) with ESMTPS id D96596EF8C;
        Tue, 26 May 2020 09:36:32 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Halil Pasic <pasic@linux.ibm.com>
Cc: linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Cornelia Huck <cohuck@redhat.com>
Subject: [PATCH] s390/virtio: remove unused pm callbacks
Date: Tue, 26 May 2020 11:36:29 +0200
Message-Id: <20200526093629.257649-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Support for hibernation on s390 has been recently been removed with
commit 394216275c7d ("s390: remove broken hibernate / power management
support"), no need to keep unused code around.

Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---
 drivers/s390/virtio/virtio_ccw.c | 26 --------------------------
 1 file changed, 26 deletions(-)

```
#### [PATCH v3 1/7] stats_fs API: create, add and remove stats_fs sources and values
##### From: Emanuele Giuseppe Esposito <eesposit@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Emanuele Giuseppe Esposito <eesposit@redhat.com>
X-Patchwork-Id: 11570333
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B181C90
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 11:04:00 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 89A802089D
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 11:04:00 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="hQtEJxFN"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388905AbgEZLD7 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 07:03:59 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:46504 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S2388858AbgEZLD6 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 May 2020 07:03:58 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1590491035;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=tHhJ8BBQRZ0iPlyD+IrpnOZUd0hkhRFRJvdSxd1ueEk=;
        b=hQtEJxFN3+Hf8AyAA1dBkorXLKzBrPf8wBtGolRQspkXsdKg42MUzNp1IRgJISp1UcpzNk
        PDomgU07L5LBizyzql7FIFQoVesWVDADsiyFs1XS7eyCaFeDGgafbXL1MyOA+U/QLc6I6H
        2NEd1L0ziDCaBRgyun/N9oJjn47m+es=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-52-UUhEF1YZOVetz3z_187sxg-1; Tue, 26 May 2020 07:03:53 -0400
X-MC-Unique: UUhEF1YZOVetz3z_187sxg-1
Received: by mail-wm1-f69.google.com with SMTP id l2so951374wmi.2
        for <kvm@vger.kernel.org>; Tue, 26 May 2020 04:03:53 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=tHhJ8BBQRZ0iPlyD+IrpnOZUd0hkhRFRJvdSxd1ueEk=;
        b=ubykoDycU1OS8/tx7Vt/IfWYW773xK3rwUwMStiGbmPdSJ9vc/mRa9Lh4P4H/gqE53
         9GAUPv0AG+C2n78ITzWfmfj0gtqtounxs5zPVG7oe25rBAaLnGf/DV+f9uvxSzK0GZjv
         xWBUz6sdmAdOjf0hPO3l0pbne4YmKTOvixLXWhcaErxpiznyWtvpqgjPW6eHX1Il6atT
         ymk4h14+lDslH/mJGq223E3owYf/daaPS6KdbSEky9RZ2QHw9gv9kg+i6CSxpuinP1Ox
         q4eUmy/nWj5Gj6HK0rApUMJSV/Vgc5yqcvYW4azNDl4Q6lV6kVlq8UAtw7wbpI+9vlrD
         a+Jg==
X-Gm-Message-State: AOAM531O6Ah4MfICFGBu8EUrbZAArGkD298A6BgGjOA87ILl8xX6Bjjv
        PdMfeWceZ1dMkONMR9CgetFh4mcROXh8pGetFkH8JqpiZgVV6jYkvsyFXzzfIiIV4rNTLcAqFwW
        NZSTPSF+pL4pG
X-Received: by 2002:a5d:6145:: with SMTP id y5mr18412225wrt.195.1590491031228;
        Tue, 26 May 2020 04:03:51 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwOY0Un9v5V7lkYHdpZvdgxIzFdEx42az92mapDCM2lLdpSXBwr8ImUoRA4WoT7/mpKmTjABA==
X-Received: by 2002:a5d:6145:: with SMTP id y5mr18412163wrt.195.1590491030475;
        Tue, 26 May 2020 04:03:50 -0700 (PDT)
Received: from localhost.localdomain.com ([194.230.155.118])
        by smtp.gmail.com with ESMTPSA id
 d6sm22928240wrj.90.2020.05.26.04.03.42
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Tue, 26 May 2020 04:03:44 -0700 (PDT)
From: Emanuele Giuseppe Esposito <eesposit@redhat.com>
To: kvm@vger.kernel.org
Cc: Christian Borntraeger <borntraeger@de.ibm.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Alexander Viro <viro@zeniv.linux.org.uk>,
        Emanuele Giuseppe Esposito <e.emanuelegiuseppe@gmail.com>,
        David Rientjes <rientjes@google.com>,
        Jonathan Adams <jwadams@google.com>, linux-doc@vger.kernel.org,
        linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        linux-mips@vger.kernel.org, kvm-ppc@vger.kernel.org,
        linuxppc-dev@lists.ozlabs.org, linux-s390@vger.kernel.org,
        linux-fsdevel@vger.kernel.org, netdev@vger.kernel.org,
        Emanuele Giuseppe Esposito <eesposit@redhat.com>
Subject: [PATCH v3 1/7] stats_fs API: create,
 add and remove stats_fs sources and values
Date: Tue, 26 May 2020 13:03:11 +0200
Message-Id: <20200526110318.69006-2-eesposit@redhat.com>
X-Mailer: git-send-email 2.25.4
In-Reply-To: <20200526110318.69006-1-eesposit@redhat.com>
References: <20200526110318.69006-1-eesposit@redhat.com>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Introduction to the stats_fs API, that allows to easily create, add
and remove stats_fs sources and values. The API allows to easily building
the statistics directory tree to automatically gather them for the linux
kernel. The main functionalities are: create a source, add child
sources/values/aggregates, register it to the root source (that on
the virtual fs would be /sys/kernel/stats), ad perform a search for
a value/aggregate.

Each source and value has an optional flag parameter:
in a value, it represent whether the statistic is cumulative or floating, in a
source whether it should be visible from the filesystem or not.
Defaults are respectively cumulative and visible.
Both flags fields are represented as an uint32_t to offer portability for
future flags.

Each value also takes a struct stats_fs_type pointer that defines
get and clear function for that stat, allowing custom
types handling. The API also  provides default get and clear types for
the supported standard types (stats_fs_type_*).

The API representation is only logical and will be backed up
by a virtual file system in patch 4.
Its usage will be shared between the stats_fs file system
and the end-users like kvm, the former calling it when it needs to
display and clear statistics, the latter to add values and sources.

Signed-off-by: Emanuele Giuseppe Esposito <eesposit@redhat.com>
---
 MAINTAINERS              |   7 +
 fs/Kconfig               |  14 +
 fs/Makefile              |   1 +
 fs/stats_fs/Makefile     |   5 +
 fs/stats_fs/internal.h   |  19 ++
 fs/stats_fs/stats_fs.c   | 552 +++++++++++++++++++++++++++++++++++++++
 fs/stats_fs/stub.c       |  13 +
 include/linux/stats_fs.h | 363 +++++++++++++++++++++++++
 8 files changed, 974 insertions(+)
 create mode 100644 fs/stats_fs/Makefile
 create mode 100644 fs/stats_fs/internal.h
 create mode 100644 fs/stats_fs/stats_fs.c
 create mode 100644 fs/stats_fs/stub.c
 create mode 100644 include/linux/stats_fs.h

```
#### [PATCH] vdpa: bypass waking up vhost_woker for vdpa vq kick
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11569933
Return-Path: <SRS0=g4lY=7I=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8BEA8159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 05:36:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 73F6F20776
	for <patchwork-kvm@patchwork.kernel.org>;
 Tue, 26 May 2020 05:36:15 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726207AbgEZFf4 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 26 May 2020 01:35:56 -0400
Received: from mga14.intel.com ([192.55.52.115]:20009 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725773AbgEZFf4 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 26 May 2020 01:35:56 -0400
IronPort-SDR: 
 75n97el5uGZTIObyAj1H5ptVwaYdYcv8hOXWx2zz6NKYERpz+GSPgwrYW63A4YoJut68MC1SQg
 SMwqrYADHwTA==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga008.fm.intel.com ([10.253.24.58])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 25 May 2020 22:35:56 -0700
IronPort-SDR: 
 8GuUvj2YEZwOCH+zeBzQGzidx1tkcc1NTDlrvncBzRNXwbmzFfOQ4wMAbrOH0d3XjFBsPvnH75
 aWpwPrG8sZfQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,436,1583222400";
   d="scan'208";a="256368416"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.193.54])
  by fmsmga008.fm.intel.com with ESMTP; 25 May 2020 22:35:53 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: mst@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org,
        linux-kernel@vger.kernel.org, netdev@vger.kernel.org,
        jasowang@redhat.com
Cc: lulu@redhat.com, dan.daly@intel.com, cunming.liang@intel.com,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH] vdpa: bypass waking up vhost_woker for vdpa vq kick
Date: Tue, 26 May 2020 13:32:25 +0800
Message-Id: <1590471145-4436-1-git-send-email-lingshan.zhu@intel.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Standard vhost devices rely on waking up a vhost_worker to kick
a virtquque. However vdpa devices have hardware backends, so it
does not need this waking up routin. In this commit, vdpa device
will kick a virtqueue directly, reduce the performance overhead
caused by waking up a vhost_woker.

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
Suggested-by: Jason Wang <jasowang@redhat.com>
Reported-by: kbuild test robot <lkp@intel.com>
---
 drivers/vhost/vdpa.c | 100 +++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 100 insertions(+)

```
