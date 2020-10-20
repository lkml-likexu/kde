#### [PATCH 1/2] KVM: not register a IRQ bypass producer if unsupported or disabled
##### From: Zhenzhong Duan <zhenzhong.duan@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhenzhong Duan <zhenzhong.duan@gmail.com>
X-Patchwork-Id: 11843865
Return-Path: <SRS0=8juW=D2=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.6 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,FREEMAIL_FORGED_FROMDOMAIN,FREEMAIL_FROM,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,
	SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=unavailable
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 0C992C433DF
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 09:07:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AC2062225F
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 09:07:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="UJPKh1Ot"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730060AbgJSJHV (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Oct 2020 05:07:21 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:47626 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728064AbgJSJHV (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Oct 2020 05:07:21 -0400
Received: from mail-pg1-x544.google.com (mail-pg1-x544.google.com
 [IPv6:2607:f8b0:4864:20::544])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 13CDEC0613CE;
        Mon, 19 Oct 2020 02:07:21 -0700 (PDT)
Received: by mail-pg1-x544.google.com with SMTP id b23so5655635pgb.3;
        Mon, 19 Oct 2020 02:07:21 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=OYVQGqeoUsyygZEDJbsttq3Q79Q31R4DhEWJATOHDyo=;
        b=UJPKh1Ot7CsnAgaopJKem4Czo9cR5N+HS+cErFD1/h65tMj7tTSVXNy4WPLu5pNcAE
         SWnX5N0/822hEslNViFWWIMoqE9NSiD0ojggL5Ryw2F5M0YF/xip/4kpExLRv8L89n1B
         IU8P/IoH9lANK5Ko833aYINWTheWdBFBdksLSwJ73ckRA9PVtES1cR76AWVdbMaHP/j/
         SudfspxxZBmJYlpfRaf3CPWKVl2aQ2q3JY/yVat8tEhhqIJQcLgZt8JFjSYqOordc0AF
         aIGHQaREB0/sKeaCYIj7y4OCGkKk/PbRdm/QV54QS0UmtO2yhW+1TPlFsEWi5zHOps4d
         FgbQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=OYVQGqeoUsyygZEDJbsttq3Q79Q31R4DhEWJATOHDyo=;
        b=lX5MhQaN70QtijSRIVr06uCuh+Vv/xTMgvA7/0qmNY7p3B+YzmK/maByQ54cYcBDqY
         J5LQBEph6vvg5aJ4G547Rf3Qb0QryyZP+2Eisu8UuS/38kPyh/VzK8z9zBE4vCry9+2p
         JRlokpEODBCu8k7wIzcf8Dhsbb1lLflSKNhoKWl1tRmW7VU3FNjgVuVU3oXxCG5H/toN
         C+AzK1k8V+fBVMSgIz5bJrc1Ad4BlPNP52y8H9FGgk/1JNbZqkJWi5xm6tm1zDt2Ds4V
         prJ9TUQLNjr9dKPxq7SAh+SJT9hq2iDOIx+7/2ZR8G24myzcLu7CbIaoHfFELASuT4s7
         ++GA==
X-Gm-Message-State: AOAM531aKdIc2FMF5iKZLQ3MVJIU5fJ+LL7GmCN7T5+Jo7nEGaFQ3S9C
        rKsbKIF4XUL+IR0Rd55i9uu6QT/0TSI=
X-Google-Smtp-Source: 
 ABdhPJwKwqiTnb6aTiekUrUU1EAbnHPb2lAhuehaaEZngU1Dh1m6mNeXPLFqtvWtJAjeDQiI5juhlw==
X-Received: by 2002:a62:37c4:0:b029:155:ebd8:304c with SMTP id
 e187-20020a6237c40000b0290155ebd8304cmr16112104pfa.73.1603098440227;
        Mon, 19 Oct 2020 02:07:20 -0700 (PDT)
Received: from ZB-PF0YQ8ZU.360buyad.local ([137.116.162.235])
        by smtp.gmail.com with ESMTPSA id
 e1sm11263016pfd.198.2020.10.19.02.07.15
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 19 Oct 2020 02:07:19 -0700 (PDT)
From: Zhenzhong Duan <zhenzhong.duan@gmail.com>
To: linux-kernel@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org
Cc: netdev@vger.kernel.org, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        tglx@linutronix.de, mingo@redhat.com, bp@alien8.de, mst@redhat.com,
        jasowang@redhat.com, Zhenzhong Duan <zhenzhong.duan@gmail.com>
Subject: [PATCH 1/2] KVM: not register a IRQ bypass producer if unsupported or
 disabled
Date: Mon, 19 Oct 2020 17:06:56 +0800
Message-Id: <20201019090657.131-1-zhenzhong.duan@gmail.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If Post interrupt is disabled due to hardware limit or forcely disabled
by "intremap=nopost" parameter, return -EINVAL so that the legacy mode IRQ
isn't registered as IRQ bypass producer.

With this change, below message is printed:
"vfio-pci 0000:db:00.0: irq bypass producer (token 0000000060c8cda5) registration fails: -22"

..which also hints us if a vfio or vdpa device works in PI mode or legacy
remapping mode.

Add a print to vdpa code just like what vfio_msi_set_vector_signal() does.

Signed-off-by: Zhenzhong Duan <zhenzhong.duan@gmail.com>
---
 arch/x86/kvm/svm/avic.c | 3 +--
 arch/x86/kvm/vmx/vmx.c  | 5 ++---
 drivers/vhost/vdpa.c    | 5 +++++
 3 files changed, 8 insertions(+), 5 deletions(-)

```
#### [PATCH 1/2 v2] KVM: nSVM: Check reserved values for 'Type' and invalid vectors in EVENTINJ
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11845373
Return-Path: <SRS0=8juW=D2=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-12.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	UNPARSEABLE_RELAY,USER_AGENT_GIT autolearn=ham autolearn_force=no
	version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id DA5C9C433DF
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 22:38:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8114D223FD
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 22:38:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="PyNzN+2J"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728513AbgJSWiW (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Oct 2020 18:38:22 -0400
Received: from userp2120.oracle.com ([156.151.31.85]:40084 "EHLO
        userp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726199AbgJSWiW (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Oct 2020 18:38:22 -0400
Received: from pps.filterd (userp2120.oracle.com [127.0.0.1])
        by userp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 09JMKJt1068795;
        Mon, 19 Oct 2020 22:38:18 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references; s=corp-2020-01-29;
 bh=WuWq34kkxX2RV/tWqIFlgyd5ZnXq0sK9LT4MF9ifw/g=;
 b=PyNzN+2J0qSdxt8wlPOT14167nn2R5cEJ37UEF/FlidWQ8ZDeTShsK5XISwRtcPVqIEm
 BHLK4s8YigwLC+prypK5cXuQhDIRubUwMN2h84bGY3BlvP6AfXYE6t2Rn7r93G+3jkWd
 5l80zugt5JurGdfZJClnkfgxUV2XvxHK9jq6GGUO0jqwncGqQEje6Bg+MmeutBGXgYnX
 Ql9JV7m/0eC31hL1+zMbvTVsZJMuEcuKd7IsG/ZYFOfe3UsFgbbFT2EX+BIHSVcdsFnk
 XtEtfxHepUndYYXj5SotJvH4nV5R4fcB995i5BMYSsnbLNQygk+FoXN/1m3ghmjhansp Ig==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by userp2120.oracle.com with ESMTP id 347s8mr00f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Mon, 19 Oct 2020 22:38:17 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 09JMLkMe096243;
        Mon, 19 Oct 2020 22:36:17 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 348agwpe0q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 19 Oct 2020 22:36:17 +0000
Received: from abhmp0020.oracle.com (abhmp0020.oracle.com [141.146.116.26])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 09JMaFQQ005176;
        Mon, 19 Oct 2020 22:36:16 GMT
Received: from nsvm-sadhukhan-1.osdevelopmeniad.oraclevcn.com
 (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 19 Oct 2020 15:36:15 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com,
        sean.j.christopherson@intel.com
Subject: [PATCH 1/2 v2] KVM: nSVM: Check reserved values for 'Type' and
 invalid vectors in EVENTINJ
Date: Mon, 19 Oct 2020 22:35:56 +0000
Message-Id: <20201019223557.36491-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20201019223557.36491-1-krish.sadhukhan@oracle.com>
References: <20201019223557.36491-1-krish.sadhukhan@oracle.com>
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9779
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 mlxscore=0 phishscore=0
 malwarescore=0 spamscore=0 suspectscore=1 bulkscore=0 mlxlogscore=999
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2010190150
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9779
 signatures=668682
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxscore=0
 suspectscore=1
 lowpriorityscore=0 mlxlogscore=999 priorityscore=1501 spamscore=0
 phishscore=0 clxscore=1015 bulkscore=0 impostorscore=0 adultscore=0
 malwarescore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2010190150
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to sections "Canonicalization and Consistency Checks" and "Event
Injection" in APM vol 2

    VMRUN exits with VMEXIT_INVALID error code if either:
      - Reserved values of TYPE have been specified, or
      - TYPE = 3 (exception) has been specified with a vector that does not
	correspond to an exception (this includes vector 2, which is an NMI,
	not an exception).

Signed-off-by: Krish Sadhukhan <krish.sadhukhan@oracle.com>
---
 arch/x86/include/asm/svm.h |  4 ++++
 arch/x86/kvm/svm/nested.c  | 14 ++++++++++++++
 2 files changed, 18 insertions(+)

```
#### [PATCH] KVM: VMX: Forbid userspace MSR filters for x2APIC
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11844789
Return-Path: <SRS0=8juW=D2=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B708BC433DF
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 17:05:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 51CC8205ED
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 17:05:33 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="NFwUCbZ4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730897AbgJSRFc (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Oct 2020 13:05:32 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:43801 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1730635AbgJSRFb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 19 Oct 2020 13:05:31 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603127130;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=8T33BC/57dNGym7wEnyJvGdAxGs0P1jblpQACkcYHg0=;
        b=NFwUCbZ4jj4P5XxAO2BtNK7+hyi13lr2nyUtEJ+q3tHEuNSSK8q3QHtPtPtjdzdf7yp78K
        GRjATeZTDyOqPEbGNU97tvBLPdaFAZVN9sqZHcJmibdZ+z7pVSMr3K1z45hj1zcsQY61Uv
        oDNV2+97Y691Q/V1Xy0H/bHglExSees=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-162-tOZTp_APOFifK1536HR7MQ-1; Mon, 19 Oct 2020 13:05:26 -0400
X-MC-Unique: tOZTp_APOFifK1536HR7MQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 52903D6883;
        Mon, 19 Oct 2020 17:05:25 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9E78F5C22A;
        Mon, 19 Oct 2020 17:05:19 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Alexander Graf <graf@amazon.com>,
        Aaron Lewis <aaronlewis@google.com>,
        Peter Xu <peterx@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [PATCH] KVM: VMX: Forbid userspace MSR filters for x2APIC
Date: Mon, 19 Oct 2020 13:05:19 -0400
Message-Id: <20201019170519.1855564-1-pbonzini@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Allowing userspace to intercept reads to x2APIC MSRs when APICV is
fully enabled for the guest simply can't work.   But more in general,
if the LAPIC is in-kernel, allowing accessed by userspace would be very
confusing.  If userspace wants to intercept x2APIC MSRs, then it should
first disable in-kernel APIC.

We could in principle allow userspace to intercept reads and writes to TPR,
and writes to EOI and SELF_IPI, but while that could be made it work, it
would still be silly.

Cc: Alexander Graf <graf@amazon.com>
Cc: Aaron Lewis <aaronlewis@google.com>
Cc: Peter Xu <peterx@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Acked-by: Peter Xu <peterx@redhat.com>
---
 arch/x86/kvm/x86.c | 17 +++++++++++++++++
 1 file changed, 17 insertions(+)

```
#### [PATCH] vfio/pci: Clear token on bypass registration failureFrom: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 11844389
Return-Path: <SRS0=8juW=D2=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-9.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 33F70C433E7
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 13:30:53 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id C8655222E8
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 13:30:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="GCCuXnZs"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728310AbgJSNav (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Oct 2020 09:30:51 -0400
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:59508 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728300AbgJSNas (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 19 Oct 2020 09:30:48 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1603114247;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=aDNhLJRM/nT1vY+letQJHejcGlh5BSbNPHby1Nx3QTw=;
        b=GCCuXnZsPCBazEtlFI4QyOwvERJRxzl6mGKqsVHRhqhEU/ml1vco6tzE0+t4vbEO9E8wYQ
        t14ibqbnyEjJMCXCTWNxPpSGSaa5XMOlNlic2f987EzSnRca5YZsd3KZHWfjvT2/VaISEN
        p+ExlF4j/OpmrgixUClIFOm/c0oAvMs=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-226-DMC7xye6Pm6bjRiyB6VbNw-1; Mon, 19 Oct 2020 09:30:44 -0400
X-MC-Unique: DMC7xye6Pm6bjRiyB6VbNw-1
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C868F876E3F;
        Mon, 19 Oct 2020 13:30:42 +0000 (UTC)
Received: from gimli.home (ovpn-112-77.phx2.redhat.com [10.3.112.77])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 36C345B4AD;
        Mon, 19 Oct 2020 13:30:37 +0000 (UTC)
Subject: [PATCH] vfio/pci: Clear token on bypass registration failure
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        guomin_chen@sina.com, gchen.guomin@gmail.com
Date: Mon, 19 Oct 2020 07:30:37 -0600
Message-ID: <160311419702.25406.2436004222669241097.stgit@gimli.home>
User-Agent: StGit/0.21-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The eventfd context is used as our irqbypass token, therefore if an
eventfd is re-used, our token is the same.  The irqbypass code will
return an -EBUSY in this case, but we'll still attempt to unregister
the producer, where if that duplicate token still exists, results in
removing the wrong object.  Clear the token of failed producers so
that they harmlessly fall out when unregistered.

Fixes: 6d7425f109d2 ("vfio: Register/unregister irq_bypass_producer")
Reported-by: guomin chen <guomin_chen@sina.com>
Tested-by: guomin chen <guomin_chen@sina.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---
 drivers/vfio/pci/vfio_pci_intrs.c |    4 +++-
 1 file changed, 3 insertions(+), 1 deletion(-)

```
#### [PATCH] x86/kvm: Reserve KVM_FEATURE_MSI_EXT_DEST_IDFrom: David Woodhouse <dwmw2@infradead.org>
##### From: David Woodhouse <dwmw2@infradead.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Woodhouse <dwmw2@infradead.org>
X-Patchwork-Id: 11844583
Return-Path: <SRS0=8juW=D2=vger.kernel.org=kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.3 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SIGNED_OFF_BY,SPF_HELO_NONE,SPF_PASS,USER_AGENT_SANE_2
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 3844AC433E7
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 14:56:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8A550222EB
	for <kvm@archiver.kernel.org>; Mon, 19 Oct 2020 14:56:08 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=infradead.org header.i=@infradead.org
 header.b="Jnu2Wbah"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729644AbgJSO4H (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 19 Oct 2020 10:56:07 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:45554 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728311AbgJSO4H (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 19 Oct 2020 10:56:07 -0400
Received: from merlin.infradead.org (merlin.infradead.org
 [IPv6:2001:8b0:10b:1231::1])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 27F5BC0613CE
        for <kvm@vger.kernel.org>; Mon, 19 Oct 2020 07:56:07 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=merlin.20170209;
 h=Mime-Version:Content-Type:References:
        In-Reply-To:Date:Cc:To:From:Subject:Message-ID:Sender:Reply-To:
        Content-Transfer-Encoding:Content-ID:Content-Description;
        bh=lHQLuEgjod4cyXYlZj/yJTiArJ/+9ZerdGqKAnA8VYo=;
 b=Jnu2WbahNop0HfV1fdMqGviLJ6
        Spb3PDqo4g0N3UcA7JieoCpn10FwR6YTy31mZa+MctEtvhWLHNpja5cnGCFVu+64mi/8xdaJxWUAB
        mVCnRiIWL+fIByyj1NGRJ00rn79dYGUUtw/qfX95B/v7ukZnFCSNi6UdRkIiOTVtM5C94f046i3XA
        NF0ENe+WlmvtgjQemwSWqnaMIOCTiEQn2upirW8y+OPyxBFxfFh8pCd4+hrfC2N7dGAXnzX6Qt073
        jQVez8AOrnIDUWTG/o4qdTEh4ZImLqIu+9W+umlh5p7uiJeVIkI+H7NnhoPPVaXSgg0fzN8K6tOfM
        BMT4Vufg==;
Received: from 54-240-197-236.amazon.com ([54.240.197.236]
 helo=freeip.amazon.com)
        by merlin.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat Linux))
        id 1kUWZq-0007g0-2z; Mon, 19 Oct 2020 14:55:58 +0000
Message-ID: <4cd59bed05f4b7410d3d1ffd1e997ab53683874d.camel@infradead.org>
Subject: [PATCH] x86/kvm: Reserve KVM_FEATURE_MSI_EXT_DEST_ID
From: David Woodhouse <dwmw2@infradead.org>
To: Paolo Bonzini <pbonzini@redhat.com>,
        qemu-devel <qemu-devel@nongnu.org>
Cc: x86 <x86@kernel.org>, kvm <kvm@vger.kernel.org>
Date: Mon, 19 Oct 2020 15:55:56 +0100
In-Reply-To: <4d820db0-be0d-d47d-7a8a-874fb481a2ce@redhat.com>
References: <78097f9218300e63e751e077a0a5ca029b56ba46.camel@infradead.org>
         <6f8704bf-f832-9fcc-5d98-d8e8b562fe2f@redhat.com>
         <698c8ab6783a3113d90d8435d07a2dce6a2e2ec9.camel@infradead.org>
         <7b9c8ca4-e89e-e140-d591-76dcb2cad485@redhat.com>
         <c337e15dec18e291399b294823dccbdb63976a38.camel@infradead.org>
         <4d820db0-be0d-d47d-7a8a-874fb481a2ce@redhat.com>
X-Mailer: Evolution 3.28.5-0ubuntu0.18.04.2 
Mime-Version: 1.0
X-SRS-Rewrite: SMTP reverse-path rewritten from <dwmw2@infradead.org> by
 merlin.infradead.org. See http://www.infradead.org/rpr.html
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: David Woodhouse <dwmw@amazon.co.uk>

No functional change; just reserve the feature bit for now so that VMMs
can start to implement it.

This will allow the host to indicate that MSI emulation supports 15-bit
destination IDs, allowing up to 32768 CPUs without interrupt remapping.

cf. https://patchwork.kernel.org/patch/11816693/ for qemu

Signed-off-by: David Woodhouse <dwmw@amazon.co.uk>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/cpuid.rst     | 4 ++++
 arch/x86/include/uapi/asm/kvm_para.h | 1 +
 2 files changed, 5 insertions(+)

```
