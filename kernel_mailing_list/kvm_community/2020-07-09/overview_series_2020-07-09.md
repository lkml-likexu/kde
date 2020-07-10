#### [PATCH v3 1/9] KVM: nSVM: split kvm_init_shadow_npt_mmu() from kvm_init_shadow_mmu()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11654547
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 12873618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 14:54:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E91CD20767
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 14:54:57 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="f+Sz+vlF"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727932AbgGIOyN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 10:54:13 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:23879 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726475AbgGIOyM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jul 2020 10:54:12 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594306450;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=kJ/JziJt1YuU460LMs6g6+REDy7/ZU1qE5RQxXXNeeA=;
        b=f+Sz+vlFb3K9ItVrlZpk5YA3xfU6nCZA+V4S3TzGjSB06vYkugvFPGTHLMcirzFlzELCyK
        iSwhNr5khGTF2u3BNmSv6kRq2Z054lZLK61N1+YQEKq1gW/CA5A438e5pbLpiVWKDBmH50
        gSps0yOtPzrTG+GK2On5GKQR3C6VRgo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-386-62vV49FLPPmc-33nPrQ-Rw-1; Thu, 09 Jul 2020 10:54:08 -0400
X-MC-Unique: 62vV49FLPPmc-33nPrQ-Rw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 68F2F107ACCA;
        Thu,  9 Jul 2020 14:54:07 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.35])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3DBBC60E1C;
        Thu,  9 Jul 2020 14:54:05 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Junaid Shahid <junaids@google.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH v3 1/9] KVM: nSVM: split kvm_init_shadow_npt_mmu() from
 kvm_init_shadow_mmu()
Date: Thu,  9 Jul 2020 16:53:50 +0200
Message-Id: <20200709145358.1560330-2-vkuznets@redhat.com>
In-Reply-To: <20200709145358.1560330-1-vkuznets@redhat.com>
References: <20200709145358.1560330-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
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
#### [PATCH] KVM: nSVM: vmentry ignores EFER.LMA and possibly RFLAGS.VM
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11653933
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2EB8D618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 09:55:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 16F4420708
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 09:55:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HcqfDFfB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726599AbgGIJzd (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 05:55:33 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:23764 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726302AbgGIJzc (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Jul 2020 05:55:32 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594288531;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=+QkB6q0IleNCeMNuLc6HQc2fnr/8fIqlOT0WR/KosmA=;
        b=HcqfDFfBs6tycicHFbwh5Xe+dvRIOnT6x5yrg/hLMjPTJy6WHilDFtq2TtmUan5AT5ut2O
        QizsXsg46o5InGUTs8pODg7yoxW26KRZK+YzV/QvMaNlQwH1otvg2ZFe+azMsFF0laKDtl
        ZkOETvcXqQf5MGBAqghzI5xmQap2G7E=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-335-kJuyZFEHNp-ZFuzIv0Ac1w-1; Thu, 09 Jul 2020 05:55:27 -0400
X-MC-Unique: kJuyZFEHNp-ZFuzIv0Ac1w-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E979B1083;
        Thu,  9 Jul 2020 09:55:26 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 965B210013D0;
        Thu,  9 Jul 2020 09:55:26 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: nSVM: vmentry ignores EFER.LMA and possibly RFLAGS.VM
Date: Thu,  9 Jul 2020 05:55:25 -0400
Message-Id: <20200709095525.907771-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

AMD doesn't specify (unlike Intel) that EFER.LME, CR0.PG and
EFER.LMA must be consistent, and for SMM state restore they say that
"The EFER.LMA register bit is set to the value obtained by logically
ANDing the SMRAM values of EFER.LME, CR0.PG, and CR4.PAE".  It turns
out that this is also true for vmentry: the EFER.LMA value in the VMCB
is completely ignored, and so is EFLAGS.VM if the processor is in
long mode or real mode.

Implement these quirks; the EFER.LMA part is needed because svm_set_efer
looks at the LMA bit in order to support EFER.NX=0, while the EFLAGS.VM
part is just because we can.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 20 +++++++++++++++++++-
 1 file changed, 19 insertions(+), 1 deletion(-)

```
#### [PATCH] KVM: nVMX: fixes for preemption timer migration
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11654781
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A441913
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 17:15:20 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4EFCF206DF
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 17:15:20 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Fw/KKrPX"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728048AbgGIRPS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 13:15:18 -0400
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:60336 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726758AbgGIRPR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Jul 2020 13:15:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594314916;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=rxmyluFqhYgjlE8gknBB9LIu9DuavODGBVATYaytN8k=;
        b=Fw/KKrPXCsMBCym8yze/fJOhxcpIMJKHYTrB6z+1zIyHX3Mfu1ugE6fCGPKQnWVAlifgmn
        Da0Uo9E9ZoWgjpL+hjiYD+HDE30eXtn9QCst2gAoiJhJAM8p9MBcPfMVdvmQXlp0H0WtB7
        9Yf1a5OBOoiD7LiGOY01Uf7GySszTDg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-157-yE6sFXMCM8qmyFHsuVY5lw-1; Thu, 09 Jul 2020 13:15:14 -0400
X-MC-Unique: yE6sFXMCM8qmyFHsuVY5lw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2C3E810059A2;
        Thu,  9 Jul 2020 17:15:13 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C4CF8610F2;
        Thu,  9 Jul 2020 17:15:08 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: bsd@redhat.com, Makarand Sonare <makarandsonare@google.com>
Subject: [PATCH] KVM: nVMX: fixes for preemption timer migration
Date: Thu,  9 Jul 2020 13:15:07 -0400
Message-Id: <20200709171507.1819-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 850448f35aaf ("KVM: nVMX: Fix VMX preemption timer migration",
2020-06-01) accidentally broke nVMX live migration from older version
by changing the userspace ABI.  Restore it and, while at it, ensure
that vmx->nested.has_preemption_timer_deadline is always initialized
according to the KVM_STATE_VMX_PREEMPTION_TIMER_DEADLINE flag.

Cc: Makarand Sonare <makarandsonare@google.com>
Fixes: 850448f35aaf ("KVM: nVMX: Fix VMX preemption timer migration")
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
Reviewed-by: Bandan Das <bsd@redhat.com>
---
 arch/x86/include/uapi/asm/kvm.h | 5 +++--
 arch/x86/kvm/vmx/nested.c       | 3 ++-
 2 files changed, 5 insertions(+), 3 deletions(-)

```
#### [kvm-unit-tests PATCH v11 2/9] s390x: I/O interrupt registration
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11653707
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 35554618
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 08:07:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1FD4A2070E
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 08:07:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726475AbgGIIH5 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 04:07:57 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:14546 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726311AbgGIIH4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jul 2020 04:07:56 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06982Zsd012968;
        Thu, 9 Jul 2020 04:07:55 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 325r2c9pay-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 04:07:55 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06982fGB013546;
        Thu, 9 Jul 2020 04:07:55 -0400
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0b-001b2d01.pphosted.com with ESMTP id 325r2c9pa3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 04:07:55 -0400
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0698649H007141;
        Thu, 9 Jul 2020 08:07:53 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma03fra.de.ibm.com with ESMTP id 325k2c0a8h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 08:07:53 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06987p8I62062956
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 9 Jul 2020 08:07:51 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 42E39A405B;
        Thu,  9 Jul 2020 08:07:51 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C3DA6A4060;
        Thu,  9 Jul 2020 08:07:50 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.34.67])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  9 Jul 2020 08:07:50 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v11 2/9] s390x: I/O interrupt registration
Date: Thu,  9 Jul 2020 10:07:41 +0200
Message-Id: <1594282068-11054-3-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594282068-11054-1-git-send-email-pmorel@linux.ibm.com>
References: <1594282068-11054-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-09_04:2020-07-08,2020-07-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 mlxscore=0 bulkscore=0
 priorityscore=1501 impostorscore=0 spamscore=0 phishscore=0 adultscore=0
 lowpriorityscore=0 malwarescore=0 clxscore=1015 mlxlogscore=725
 suspectscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007090059
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's make it possible to add and remove a custom io interrupt handler,
that can be used instead of the normal one.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 lib/s390x/interrupt.c | 23 ++++++++++++++++++++++-
 lib/s390x/interrupt.h |  8 ++++++++
 2 files changed, 30 insertions(+), 1 deletion(-)
 create mode 100644 lib/s390x/interrupt.h

```
#### [PATCH v4 1/5] KVM: x86: Introduce kvm_check_cpuid()
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11653317
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A1AA914E3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 04:34:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 94E502074A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 04:34:35 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726345AbgGIEef (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 00:34:35 -0400
Received: from mga14.intel.com ([192.55.52.115]:10037 "EHLO mga14.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726064AbgGIEed (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Jul 2020 00:34:33 -0400
IronPort-SDR: 
 sMSv29CgqYvNu8i9zT9mpfrXgfsD6rKRNxOtAUrepesbR6yxb4B64XJ7RhdePWJmAFKZLnTDRN
 kYT8AWPJRMbA==
X-IronPort-AV: E=McAfee;i="6000,8403,9676"; a="147011557"
X-IronPort-AV: E=Sophos;i="5.75,330,1589266800";
   d="scan'208";a="147011557"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga002.jf.intel.com ([10.7.209.21])
  by fmsmga103.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 Jul 2020 21:34:32 -0700
IronPort-SDR: 
 s5+Nc2Hd4qIoq29QJ3YPqtF4T0P4sFUnBje4bUB87DrB+/Dq6dAtnKB+G5BwWge7/k+LhroWw3
 DlG/tg/jKq1w==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,330,1589266800";
   d="scan'208";a="297942864"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by orsmga002.jf.intel.com with ESMTP; 08 Jul 2020 21:34:30 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v4 1/5] KVM: x86: Introduce kvm_check_cpuid()
Date: Thu,  9 Jul 2020 12:34:22 +0800
Message-Id: <20200709043426.92712-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200709043426.92712-1-xiaoyao.li@intel.com>
References: <20200709043426.92712-1-xiaoyao.li@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Use kvm_check_cpuid() to validate if userspace provides legal cpuid
settings and call it before KVM take any action to update CPUID or
update vcpu states based on given CPUID settings.

Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/cpuid.c | 55 ++++++++++++++++++++++++++++----------------
 arch/x86/kvm/cpuid.h |  2 +-
 2 files changed, 36 insertions(+), 21 deletions(-)

```
#### [PATCH v5 1/2] virtio: let arch validate VIRTIO features
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11653787
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4B90314DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 08:39:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 3C6CD207C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 08:39:51 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726523AbgGIIjg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 04:39:36 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:41962 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726456AbgGIIjf (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jul 2020 04:39:35 -0400
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0698WMR9001243;
        Thu, 9 Jul 2020 04:39:27 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 325n5xfr89-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 04:39:27 -0400
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0698WtY7004285;
        Thu, 9 Jul 2020 04:39:27 -0400
Received: from ppma03ams.nl.ibm.com (62.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 325n5xfr7h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 04:39:27 -0400
Received: from pps.filterd (ppma03ams.nl.ibm.com [127.0.0.1])
        by ppma03ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0698a6Jp031658;
        Thu, 9 Jul 2020 08:39:25 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma03ams.nl.ibm.com with ESMTP id 325k1vgm6c-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 08:39:25 +0000
Received: from d06av24.portsmouth.uk.ibm.com (mk.ibm.com [9.149.105.60])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0698c0Nu62456312
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 9 Jul 2020 08:38:01 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6EDA04204B;
        Thu,  9 Jul 2020 08:39:22 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9FA6942049;
        Thu,  9 Jul 2020 08:39:21 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.34.67])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  9 Jul 2020 08:39:21 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com
Subject: [PATCH v5 1/2] virtio: let arch validate VIRTIO features
Date: Thu,  9 Jul 2020 10:39:18 +0200
Message-Id: <1594283959-13742-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594283959-13742-1-git-send-email-pmorel@linux.ibm.com>
References: <1594283959-13742-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-09_04:2020-07-08,2020-07-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 suspectscore=1 bulkscore=0 impostorscore=0 malwarescore=0
 lowpriorityscore=0 mlxlogscore=999 clxscore=1015 phishscore=0 spamscore=0
 mlxscore=0 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2007090064
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An architecture may need to validate the VIRTIO devices features
based on architecture specifics.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/virtio/virtio.c       | 19 +++++++++++++++++++
 include/linux/virtio_config.h |  1 +
 2 files changed, 20 insertions(+)

```
#### [kvm-unit-tests PATCH v11 1/9] s390x: saving regs for interrupts
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11653713
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6A48860D
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 08:08:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5B3EC2073A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 08:08:01 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726590AbgGIIIA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 04:08:00 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:56960 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726139AbgGIIH5 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Thu, 9 Jul 2020 04:07:57 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 06981c1a141413;
        Thu, 9 Jul 2020 04:07:56 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 325p3hmn7h-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 04:07:56 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 06981ilh141837;
        Thu, 9 Jul 2020 04:07:56 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 325p3hmn5x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 04:07:56 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 06987LMH025673;
        Thu, 9 Jul 2020 08:07:53 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma06ams.nl.ibm.com with ESMTP id 325k0crkcu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Thu, 09 Jul 2020 08:07:52 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 06987oFW15335672
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Thu, 9 Jul 2020 08:07:50 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id ABE58A405B;
        Thu,  9 Jul 2020 08:07:50 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 31D37A4060;
        Thu,  9 Jul 2020 08:07:50 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.34.67])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Thu,  9 Jul 2020 08:07:50 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com, cohuck@redhat.com,
        drjones@redhat.com
Subject: [kvm-unit-tests PATCH v11 1/9] s390x: saving regs for interrupts
Date: Thu,  9 Jul 2020 10:07:40 +0200
Message-Id: <1594282068-11054-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1594282068-11054-1-git-send-email-pmorel@linux.ibm.com>
References: <1594282068-11054-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-07-09_04:2020-07-08,2020-07-09 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 malwarescore=0
 spamscore=0 mlxscore=0 lowpriorityscore=0 clxscore=1015 mlxlogscore=999
 bulkscore=0 phishscore=0 priorityscore=1501 suspectscore=1 impostorscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2007090059
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we use multiple source of interrupts, for example, using SCLP
console to print information while using I/O interrupts, we need
to have a re-entrant register saving interruption handling.

Instead of saving at a static memory address, let's save the base
registers, the floating point registers and the floating point
control register on the stack in case of I/O interrupts

Note that we keep the static register saving to recover from the
RESET tests.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Acked-by: Janosch Frank <frankja@linux.ibm.com>
Acked-by: Thomas Huth <thuth@redhat.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 s390x/cstart64.S | 41 +++++++++++++++++++++++++++++++++++++++--
 1 file changed, 39 insertions(+), 2 deletions(-)

```
#### [PATCH v1] vfio/pci: Refine Intel IGD OpRegion support
##### From: Fred Gao <fred.gao@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Fred Gao <fred.gao@intel.com>
X-Patchwork-Id: 11653925
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9AFA192A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 09:40:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8D719206C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 09:40:37 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726517AbgGIJkg (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 05:40:36 -0400
Received: from mga05.intel.com ([192.55.52.43]:64250 "EHLO mga05.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726140AbgGIJkg (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Jul 2020 05:40:36 -0400
IronPort-SDR: 
 TUkDxrYm0K5oUPtaq4IjJlPWrmr7Z9kdYaogTLtZhsel16XKu0DS6MKH5u8uqFvEX2ty1QEgP9
 CsMWhuSGhqNw==
X-IronPort-AV: E=McAfee;i="6000,8403,9676"; a="232839669"
X-IronPort-AV: E=Sophos;i="5.75,331,1589266800";
   d="scan'208";a="232839669"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga006.fm.intel.com ([10.253.24.20])
  by fmsmga105.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 09 Jul 2020 02:40:35 -0700
IronPort-SDR: 
 BQZMK4+YVHFcQ3SFU++emTwOsWZRlVqRXLbj84UqiIH3Y0eiw1WJ6TBuC6RgMHZkLrrJnSsrRw
 nCR8s9KvXOQQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.75,331,1589266800";
   d="scan'208";a="483735424"
Received: from cfl-host.sh.intel.com ([10.239.158.139])
  by fmsmga006.fm.intel.com with ESMTP; 09 Jul 2020 02:40:33 -0700
From: Fred Gao <fred.gao@intel.com>
To: fred.gao@intel.com, kvm@vger.kernel.org,
        intel-gfx@lists.freedesktop.org
Cc: Zhenyu Wang <zhenyuw@linux.intel.com>,
        Xiong Zhang <xiong.y.zhang@intel.com>,
        Hang Yuan <hang.yuan@linux.intel.com>,
        Stuart Summers <stuart.summers@intel.com>,
        Lucas De Marchi <lucas.demarchi@intel.com>
Subject: [PATCH v1] vfio/pci: Refine Intel IGD OpRegion support
Date: Fri, 10 Jul 2020 01:37:07 +0800
Message-Id: <20200709173707.29808-1-fred.gao@intel.com>
X-Mailer: git-send-email 2.24.1.1.gb6d4d82bd5
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Bypass the IGD initialization for Intel's dgfx devices with own expansion
ROM and the host/LPC bridge config space are no longer accessed.

Cc: Zhenyu Wang <zhenyuw@linux.intel.com>
Cc: Xiong Zhang <xiong.y.zhang@intel.com>
Cc: Hang Yuan <hang.yuan@linux.intel.com>
Cc: Stuart Summers <stuart.summers@intel.com>
Signed-off-by: Lucas De Marchi <lucas.demarchi@intel.com>
Signed-off-by: Fred Gao <fred.gao@intel.com>
---
 drivers/vfio/pci/vfio_pci.c | 11 ++++++++++-
 1 file changed, 10 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: nVMX: fixes for preemption timer migration
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11654785
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DF0BC92A
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 17:28:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C571C207D0
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 17:28:10 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bscbuXmL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727972AbgGIR2G (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 13:28:06 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:52720 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726758AbgGIR2G (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Jul 2020 13:28:06 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594315685;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=GfadFP0vLdHdZ4FwpCfHglgC68S6cIQIOSckhJEfNgY=;
        b=bscbuXmLi5cOdh2umI/+VRfpmr3m/zw8iLlklYNuATHw69nZpGWeJ/KxXa5RBhnls7oao9
        cFpj5Kj7/IUowM6mBJ984WnIU1XpjiiHUggicicZxQonAHQVZgnIkddUWPEyswgaXOx7sG
        xEXBBQZqKTIifEOVEa+8VCsqReNTbJc=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-254-ZW040yRZNMCJDXcieKH_eQ-1; Thu, 09 Jul 2020 13:28:03 -0400
X-MC-Unique: ZW040yRZNMCJDXcieKH_eQ-1
Received: from smtp.corp.redhat.com (int-mx05.intmail.prod.int.phx2.redhat.com
 [10.5.11.15])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 354DF1081;
        Thu,  9 Jul 2020 17:28:02 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CB6477F8C2;
        Thu,  9 Jul 2020 17:28:01 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Makarand Sonare <makarandsonare@google.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH v2] KVM: nVMX: fixes for preemption timer migration
Date: Thu,  9 Jul 2020 13:28:01 -0400
Message-Id: <20200709172801.2697-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.15
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 850448f35aaf ("KVM: nVMX: Fix VMX preemption timer migration",
2020-06-01) accidentally broke nVMX live migration from older version
by changing the userspace ABI.  Restore it and, while at it, ensure
that vmx->nested.has_preemption_timer_deadline is always initialized
according to the KVM_STATE_VMX_PREEMPTION_TIMER_DEADLINE flag.

Cc: Makarand Sonare <makarandsonare@google.com>
Fixes: 850448f35aaf ("KVM: nVMX: Fix VMX preemption timer migration")
Reviewed-by: Jim Mattson <jmattson@google.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
v1->v2: coding style [Jim]

 arch/x86/include/uapi/asm/kvm.h | 5 +++--
 arch/x86/kvm/vmx/nested.c       | 1 +
 2 files changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH v3] kvm,x86: Exit to user space in case of page fault error
##### From: Vivek Goyal <vgoyal@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vivek Goyal <vgoyal@redhat.com>
X-Patchwork-Id: 11654363
Return-Path: <SRS0=D4j5=AU=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CE72814DD
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 12:54:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AF258207C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Thu,  9 Jul 2020 12:54:55 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="AYjZKOpo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726908AbgGIMyy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Thu, 9 Jul 2020 08:54:54 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:56245 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726471AbgGIMyx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Thu, 9 Jul 2020 08:54:53 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1594299291;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=Hq4oPiiTwiHyTHGICkYN64XjAj5RigbTr2qxmRvB+t8=;
        b=AYjZKOpoqGDH2ZcRYp6KyejU1isLJ1BQOxaEyDGUr9ECOKYD7VrNBnxR6zHb56ycsj5CmX
        WqeEBQdn3LTSo+DHOV10xzY9QRwu1aLGg+wFr7hslVpliuAaNE82ztjw2s5wxF2BCqkJ41
        V1IEWXqRBw5RP142LBwq8eU3+H4AE98=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-200-v_eDUcFROluT8bYxVM2glA-1; Thu, 09 Jul 2020 08:54:47 -0400
X-MC-Unique: v_eDUcFROluT8bYxVM2glA-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 6891080BCA1;
        Thu,  9 Jul 2020 12:54:46 +0000 (UTC)
Received: from horse.redhat.com (ovpn-115-114.rdu2.redhat.com [10.10.115.114])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 627032C24F;
        Thu,  9 Jul 2020 12:54:43 +0000 (UTC)
Received: by horse.redhat.com (Postfix, from userid 10451)
        id DC029220689; Thu,  9 Jul 2020 08:54:42 -0400 (EDT)
Date: Thu, 9 Jul 2020 08:54:42 -0400
From: Vivek Goyal <vgoyal@redhat.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: virtio-fs-list <virtio-fs@redhat.com>, vkuznets@redhat.com,
        pbonzini@redhat.com, sean.j.christopherson@intel.com
Subject: [PATCH v3] kvm,x86: Exit to user space in case of page fault error
Message-ID: <20200709125442.GA150543@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Page fault error handling behavior in kvm seems little inconsistent when
page fault reports error. If we are doing fault synchronously
then we capture error (-EFAULT) returned by __gfn_to_pfn_memslot() and
exit to user space and qemu reports error, "error: kvm run failed Bad address".

But if we are doing async page fault, then async_pf_execute() will simply
ignore the error reported by get_user_pages_remote() or
by kvm_mmu_do_page_fault(). It is assumed that page fault was successful
and either a page ready event is injected in guest or guest is brought
out of artificial halt state and run again. In both the cases when guest
retries the instruction, it takes exit again as page fault was not
successful in previous attempt. And then this infinite loop continues
forever.

Trying fault in a loop will make sense if error is temporary and will
be resolved on retry. But I don't see any intention in the code to
determine if error is temporary or not.  Whether to do fault synchronously
or asynchronously, depends on so many variables but none of the varibales
is whether error is temporary or not. (kvm_can_do_async_pf()).

And that makes it very inconsistent or unpredictable to figure out whether
kvm will exit to qemu with error or it will just retry and go into an
infinite loop.

This patch tries to make this behavior consistent. That is instead of
getting into infinite loop of retrying page fault, exit to user space
and stop VM if page fault error happens.

In future this can be improved by injecting errors into guest. As of
now we don't have any race free method to inject errors in guest.

When page fault error happens in async path save that pfn and when next
time guest retries, do a sync fault instead of async fault. So that if error
is encountered, we exit to qemu and avoid infinite loop.

We maintain a cache of error gfns and force sync fault if a gfn is
found in cache of error gfn. There is a small possibility that we
miss an error gfn (as it got overwritten by a new error gfn). But
its just a hint and sooner or later some error pfn will match
and we will force sync fault and exit to user space.

Change from v2:
- Fixed a warning by converting kvm_find_error_gfn() static.

Change from v1:
- Maintain a cache of error gfns, instead of single gfn. (Vitaly)

Signed-off-by: Vivek Goyal <vgoyal@redhat.com>
---
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/mmu.h              |  2 +-
 arch/x86/kvm/mmu/mmu.c          |  2 +-
 arch/x86/kvm/x86.c              | 61 +++++++++++++++++++++++++++++++--
 4 files changed, 62 insertions(+), 5 deletions(-)

```
