#### [PATCH] Fix unpack
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11241965
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9FBE115AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 14:03:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8A7D52245B
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 14:03:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727406AbfKMODm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 09:03:42 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:31048 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726190AbfKMODm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Nov 2019 09:03:42 -0500
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xADE06Xj090710
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 09:03:40 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2w8j0fbgpm-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 09:03:39 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 13 Nov 2019 14:02:01 -0000
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 13 Nov 2019 14:01:59 -0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xADE1xCB47120574
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 Nov 2019 14:01:59 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id EDBF3A4062;
        Wed, 13 Nov 2019 14:01:58 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CA9F2A405F;
        Wed, 13 Nov 2019 14:01:57 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 13 Nov 2019 14:01:57 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [PATCH] Fix unpack
Date: Wed, 13 Nov 2019 09:03:06 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <07705597-8e8f-28d4-f9a1-d3d5dc9a4555@redhat.com>
References: <07705597-8e8f-28d4-f9a1-d3d5dc9a4555@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19111314-0008-0000-0000-0000032EAE77
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111314-0009-0000-0000-00004A4DB88A
Message-Id: <20191113140306.2952-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-13_03:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=797 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1910280000 definitions=main-1911130130
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

That should be easier to read :)

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/kvm/pv.c | 60 +++++++++++++++++++++++++++-------------------
 1 file changed, 35 insertions(+), 25 deletions(-)

```
#### [kvm-unit-test PATCH 1/5] travis.yml: Re-arrange the test matrix
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11241737
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4A8F515AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 11:27:04 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2C52B22459
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 11:27:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="esns6A4a"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727927AbfKML1D (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 06:27:03 -0500
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:53000 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727733AbfKML1C (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Nov 2019 06:27:02 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573644421;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=d6Riu+/ym+X+cIktyE0yWSvwwZI/0+zJLjKnzOMk7Hw=;
        b=esns6A4a18lSwEOwaSIBh7mruK5zGCNh1jRdVixu2XTgic+vhvYR101Y59Ph1OQNX7NHSB
        N++8s4Udq3CNo6yqpPSQR5JhzdKsh0WtepsrPPzVgfUwnyb1fnb6cgmI+/cKUJoBLQYY5k
        +vWXJLCPaSWRdFGTTeQiBqo6l8m+rpo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-176-gv5n0D3tOR6tk2aQof73Ig-1; Wed, 13 Nov 2019 06:27:00 -0500
Received: from smtp.corp.redhat.com (int-mx01.intmail.prod.int.phx2.redhat.com
 [10.5.11.11])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 527691005509;
        Wed, 13 Nov 2019 11:26:59 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-116-183.ams2.redhat.com
 [10.36.116.183])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 38F0D60464;
        Wed, 13 Nov 2019 11:26:56 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: David Hildenbrand <david@redhat.com>,
 =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
Subject: [kvm-unit-test PATCH 1/5] travis.yml: Re-arrange the test matrix
Date: Wed, 13 Nov 2019 12:26:45 +0100
Message-Id: <20191113112649.14322-2-thuth@redhat.com>
In-Reply-To: <20191113112649.14322-1-thuth@redhat.com>
References: <20191113112649.14322-1-thuth@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.11
X-MC-Unique: gv5n0D3tOR6tk2aQof73Ig-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We will soon need more control over the individual test matrix
entries, so we should not limit the matrix to "env" sections,
i.e. put the "matrix:" keyword on the top, not the "env:".

Signed-off-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Alex Bennée <alex.bennee@linaro.org>
---
 .travis.yml | 92 ++++++++++++++++++++++++++++++++---------------------
 1 file changed, 56 insertions(+), 36 deletions(-)

```
#### [PATCH] KVM: Forbid /dev/kvm being opened by a compat task when CONFIG_KVM_COMPAT=n
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11242221
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0A0FD14ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 16:05:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DC53823884
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 16:05:43 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1573661143;
	bh=iY5PhTGu2coVo7jUZ3Q9y2uX1/vtwFNWflIGXFte6hw=;
	h=From:To:Cc:Subject:Date:List-ID:From;
	b=DN8cYLLg8BugMORYyf1Fus3SM5aQTQNkOr4FXLHeE2kyeP2TXeS6jtfs41mRVEbuE
	 RR5RK2zC/nd76O4edXXnu6RU1wGU59vOTKul+M44Tv1vmEB6RJitYqiAebGcjS++0m
	 5eUriQpLeXXYGjKnk+R/cSR51hTbVjQqOtc1h7XE=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728222AbfKMQFn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 11:05:43 -0500
Received: from inca-roads.misterjones.org ([213.251.177.50]:35648 "EHLO
        inca-roads.misterjones.org" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727528AbfKMQFm (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Nov 2019 11:05:42 -0500
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by cheepnis.misterjones.org with esmtpsa
 (TLSv1.2:DHE-RSA-AES128-GCM-SHA256:128)
        (Exim 4.80)
        (envelope-from <maz@kernel.org>)
        id 1iUv9D-0003v1-9C; Wed, 13 Nov 2019 17:05:35 +0100
From: Marc Zyngier <maz@kernel.org>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 James Morse <james.morse@arm.com>,
 Julien Thierry <julien.thierry.kdev@gmail.com>,
 Suzuki K Poulose <suzuki.poulose@arm.com>, James Hogan <jhogan@kernel.org>,
 Paul Mackerras <paulus@ozlabs.org>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Janosch Frank <frankja@linux.ibm.com>, David Hildenbrand <david@redhat.com>,
 Cornelia Huck <cohuck@redhat.com>,
 Sean Christopherson <sean.j.christopherson@intel.com>,
 Vitaly Kuznetsov <vkuznets@redhat.com>, Wanpeng Li <wanpengli@tencent.com>,
 Jim Mattson <jmattson@google.com>, Joerg Roedel <joro@8bytes.org>,
 Peter Maydell <peter.maydell@linaro.org>
Subject: [PATCH] KVM: Forbid /dev/kvm being opened by a compat task when
 CONFIG_KVM_COMPAT=n
Date: Wed, 13 Nov 2019 16:05:23 +0000
Message-Id: <20191113160523.16130-1-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: kvm@vger.kernel.org, pbonzini@redhat.com,
 rkrcmar@redhat.com, james.morse@arm.com, julien.thierry.kdev@gmail.com,
 suzuki.poulose@arm.com, jhogan@kernel.org, paulus@ozlabs.org,
 borntraeger@de.ibm.com, frankja@linux.ibm.com, david@redhat.com,
 cohuck@redhat.com, sean.j.christopherson@intel.com, vkuznets@redhat.com,
 wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
 peter.maydell@linaro.org
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on cheepnis.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On a system without KVM_COMPAT, we prevent IOCTLs from being issued
by a compat task. Although this prevents most silly things from
happening, it can still confuse a 32bit userspace that is able
to open the kvm device (the qemu test suite seems to be pretty
mad with this behaviour).

Take a more radical approach and return a -ENODEV to the compat
task.

Reported-by: Peter Maydell <peter.maydell@linaro.org>
Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 virt/kvm/kvm_main.c | 8 +++++++-
 1 file changed, 7 insertions(+), 1 deletion(-)

```
#### [PATCH kvm-unit-tests] svm: run tests with host IF=1
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11242163
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 5A0761390
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 15:50:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3895C22CEB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 15:50:16 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="U62KbEfD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727986AbfKMPuP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 10:50:15 -0500
Received: from mail-wr1-f68.google.com ([209.85.221.68]:39493 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726276AbfKMPuP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 Nov 2019 10:50:15 -0500
Received: by mail-wr1-f68.google.com with SMTP id l7so2937352wrp.6
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 07:50:13 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id;
        bh=krjU2hd3ztP4woKuJblHI3QSV2BYpHLjvcUu9d/lsaQ=;
        b=U62KbEfDIt3WvEiheY2lcYb/enkEtZlPwnKf0Mq+wdLpaXfRIMM0nHpTsFlR3J1YDl
         8nrL8GLPfjRVb80/RIUYbuWzOaVHC6P7G3qJALuRJbjSuWzjniv1R/+Yas38N5uYOBJF
         Mh2d6q4zyumHh0qdn/2meStlvd/EVO4N5kaoweGSOdCVGycD4WVyAN1lIBMd8S9EEO5H
         Cq1gQwAucima49HsKI3IZ92ppjlOXe3RX+ZvainSh1pYUHch0YQlv1S8OUcnuqFH2RP8
         xMtYjPVrlUhsLIlqog94BrTtvulR6c+cBxz3bxsCBEyMVlOsE9h8H9v6tmYAb6bHc+Tr
         1xSg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id;
        bh=krjU2hd3ztP4woKuJblHI3QSV2BYpHLjvcUu9d/lsaQ=;
        b=cC+UfG3XTiq7Vhg74ka8uKbeFEgtClTDs3Mg/q5B01bDeUWsWJpffOZa+fOvZesZ7Z
         4LTod4rXxtvJTJu8CEJfktPE5O+iDaoQBQUYKwDPJ1XkCPzZgHDE+vNSpZRvQ2WwIadd
         k8LKpDOtx0sbK9dNkE3dtZ/mau/kWi5cKikP90a7RNgIKvObUIzxO6OSny+6Q7iB9UiF
         3Fy+vENyA1Go0sAoIy5BB+9Ao6hwIIgQtl0kF2XKyN+F4mFUfG8Pxfa85d83O8yhECOh
         3JF9mYXby4kj024N3nU6bvmdQOBKq3lUj927IBjHibwIRK8wFyKoGt0X24L2/LJeS6N/
         Iq4w==
X-Gm-Message-State: APjAAAW2/Dqc89IVwh+74KeHNbP+SXDyo+uBIdzZ5XXVdGrGCx4G+CtZ
        tlP0k+RVrloYtNKTYTNgpzmJukPp
X-Google-Smtp-Source: 
 APXvYqxiQMJNxDNZkEFnRUM1RCnttAfg3vmIqygChNm2My+pAYzU2l3qB4hSOA9t/jneqeaMH/x0GA==
X-Received: by 2002:adf:8543:: with SMTP id 61mr3693887wrh.171.1573660212458;
        Wed, 13 Nov 2019 07:50:12 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 t134sm2992999wmt.24.2019.11.13.07.50.11
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 13 Nov 2019 07:50:11 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Cc: cavery@redhat.com
Subject: [PATCH kvm-unit-tests] svm: run tests with host IF=1
Date: Wed, 13 Nov 2019 16:50:09 +0100
Message-Id: <1573660209-26331-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Tests should in general call VMRUN with EFLAGS.IF=1 (if there are
exceptions in the future we can add a cmp/jz in test_run).  This is
because currently interrupts are masked during all of VMRUN, while
we usually want interrupts during a test to cause a vmexit.
This is similar to how PIN_EXTINT and PIN_NMI are included by
default in the VMCS used by vmx.flat.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Cathy Avery <cavery@redhat.com>
---
 x86/svm.c | 5 ++++-
 1 file changed, 4 insertions(+), 1 deletion(-)

```
#### [kvm-unit-tests PATCH v2] travis.yml: Test with KVM instead of TCG (on x86)
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11242393
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 47EFD930
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 17:48:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 0A9F7206ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 17:48:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="F2s3c7oL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727112AbfKMRsu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 12:48:50 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:32392 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726105AbfKMRst (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Nov 2019 12:48:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573667328;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=DqDxQKf1L8BXZYWjyfeQ7+2ppmpxNqc2YxrLPzA1JJ4=;
        b=F2s3c7oLQHlkR8HYojmrDTcspNhouauwUJ6dbfZBb4CPSvYCNk51YT3UpR68kOGaQZ3Oah
        aRB8AKMyDfTGK4OidMxlt36Oy8arfVK76xilEXwLneGGNoSHyRhRvyW5f1nebAYPgGCWpG
        fCCgzb1odqYB+o1mG27whxhUjjr6yzQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-82-pnp35ybBPzO5UVgfncamIg-1; Wed, 13 Nov 2019 12:48:47 -0500
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 3D2268048EC;
        Wed, 13 Nov 2019 17:48:46 +0000 (UTC)
Received: from localhost.localdomain.com (ovpn-116-183.ams2.redhat.com
 [10.36.116.183])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 5754B10374B9;
        Wed, 13 Nov 2019 17:48:45 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: =?utf-8?q?Alex_Benn=C3=A9e?= <alex.bennee@linaro.org>
Subject: [kvm-unit-tests PATCH v2] travis.yml: Test with KVM instead of TCG
 (on x86)
Date: Wed, 13 Nov 2019 18:48:42 +0100
Message-Id: <20191113174842.20759-1-thuth@redhat.com>
In-Reply-To: <e7246b2d-e76a-1302-513b-30cbfacdd4c6@redhat.com>
References: <e7246b2d-e76a-1302-513b-30cbfacdd4c6@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-MC-Unique: pnp35ybBPzO5UVgfncamIg-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Travis nowadays supports KVM in their CI pipelines, so we can finally
run the kvm-unit-tests with KVM instead of TCG here. Unfortunately, there
are some quirks:

First, /dev/kvm is not accessible on Ubuntu by default. You have to be
"root" or in the "kvm" group to access it. But changing the group of the
current user is not taking into account for the current shell process, so
that would need some indirections in the yml file. Thus the yml script now
rather changes the group and "g+s" permission of the qemu binary instead.

Second, not all x86 tests are working in this environment, so we still
have to manually select the test set here (but the amount of tests is
definitely higher now than what we were able to run with TCG before).

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 v2: Use chgrp + "chmod g+s" instead "chmod u+s" to get it running

 .travis.yml | 19 ++++++++++++++-----
 1 file changed, 14 insertions(+), 5 deletions(-)

```
#### [kvm-unit-tests PATCH v4] s390x: Load reset psw on diag308 reset
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11241733
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 61AD21515
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 11:24:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 4AAD821783
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 11:24:14 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727852AbfKMLYN (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 06:24:13 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:65020 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726339AbfKMLYN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Nov 2019 06:24:13 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xADBO5oA066414
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 06:24:11 -0500
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2w8gmhgt32-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 06:24:11 -0500
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Wed, 13 Nov 2019 11:24:09 -0000
Received: from b06cxnps4076.portsmouth.uk.ibm.com (9.149.109.198)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 13 Nov 2019 11:24:07 -0000
Received: from d06av21.portsmouth.uk.ibm.com (d06av21.portsmouth.uk.ibm.com
 [9.149.105.232])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xADBO6PJ35979346
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 Nov 2019 11:24:06 GMT
Received: from d06av21.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7DC765204E;
        Wed, 13 Nov 2019 11:24:06 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.152.224.131])
        by d06av21.portsmouth.uk.ibm.com (Postfix) with ESMTP id BE45F5204F;
        Wed, 13 Nov 2019 11:24:05 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH v4] s390x: Load reset psw on diag308 reset
Date: Wed, 13 Nov 2019 06:24:03 -0500
X-Mailer: git-send-email 2.20.1
In-Reply-To: <e54ce8f8-7ed5-3eee-6715-8b5051cb49fb@redhat.com>
References: <e54ce8f8-7ed5-3eee-6715-8b5051cb49fb@redhat.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
x-cbid: 19111311-0008-0000-0000-0000032EA507
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111311-0009-0000-0000-00004A4DAE2B
Message-Id: <20191113112403.7664-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-13_03:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1910280000 definitions=main-1911130108
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

On a diag308 subcode 0 CRs will be reset, so we need a PSW mask
without DAT. Also we need to set the short psw indication to be
compliant with the architecture.

Let's therefore define a reset PSW mask with 64 bit addressing and
short PSW indication that is compliant with architecture and use it.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 lib/s390x/asm-offsets.c  |  1 +
 lib/s390x/asm/arch_def.h |  4 +++-
 s390x/cstart64.S         | 24 +++++++++++++++++-------
 3 files changed, 21 insertions(+), 8 deletions(-)

```
#### [PATCH] kvm: x86: disable shattered huge page recovery for PREEMPT_RT.
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11242035
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AADAB1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 14:47:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8AD29222CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 14:47:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="vZuLGk/n"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727792AbfKMOrX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 09:47:23 -0500
Received: from mail-wr1-f66.google.com ([209.85.221.66]:42519 "EHLO
        mail-wr1-f66.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727427AbfKMOrX (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 Nov 2019 09:47:23 -0500
Received: by mail-wr1-f66.google.com with SMTP id a15so2664378wrf.9;
        Wed, 13 Nov 2019 06:47:22 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id;
        bh=qTf6OInkFeP/tR4a5XNbnzc1z5smkpFf/IpOmURtbuc=;
        b=vZuLGk/nVtijHr9Kilg6ZBK895kTu/XM7cKyHKf9COBFgxzrbQr1CjqtyKhRJtF4P+
         IRa7btP+Z+0cR6dgHFYgwYKm87q7pzXKpJTJ2h0GzWm9nzD6CYCg5fp1mg0Z6j7k6Atx
         rQjBOee1tpDjsW7R2gBEypGysSfCruxIJIFWY0+Gtg0hPTk9g4wzlR7XdYGKYdj7JEpm
         3HHN/tl+sYVcmkbPzVbfr7XpobEjGuY3ox4pcFAU69DglvdfDEO/IJTURFpCKS2qW2On
         am9TgSJ7bb/PItdJ93PZ8sS57wU+Qcub/xeOeQF4d+Q0OZ8qrP/BMxabGbYD240odgEb
         olVg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id;
        bh=qTf6OInkFeP/tR4a5XNbnzc1z5smkpFf/IpOmURtbuc=;
        b=Rp6Djwi2h0zPrITPtrLVNDhjAgDrV/wiT2gM2iIG/x+tAidXcHWnkk/6nRtp3cAbLY
         IIwrRyLLPfbn8vTpXPgQfVZGhR+uwH9RQQVeZul1MpU/kskiVWo43RJJIJKRbLjUJinn
         t/RzFc3k7xnpjXqCnk3Lq8j+mYUJF4cveVIjVRpx25nn2Xq8YxYVS1X9ioe3q/IunUuY
         J3SKKC4XLXN8bXAijnwZnvUDpL22lREH2WGEHeF1o3v6Eo8NhO/ZlxYhIX3o7o0g6jaP
         GdnR0/eHYZWZ0Nknlc37w9bcSTVyB5K0R2xCPP6dJ0OrdJVJ7u3EwVVlS33zyU4WQRIK
         K1Jw==
X-Gm-Message-State: APjAAAXgruR1uaHKk9VSWKdRrAcc206RKNb28+74rz88elCDmo9aET+8
        r9ufjYfw2hidX2uu20GkdgfbB9zG
X-Google-Smtp-Source: 
 APXvYqzo/tFGlzvRU9JFceav+G+zHg9Teitj9o8fi17xEh3Hfl1qOfNKyMDpGEHPNxCZPr4ImVLvEA==
X-Received: by 2002:adf:c449:: with SMTP id a9mr3097160wrg.240.1573656440997;
        Wed, 13 Nov 2019 06:47:20 -0800 (PST)
Received: from 640k.lan ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id
 189sm2807631wme.28.2019.11.13.06.47.20
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Wed, 13 Nov 2019 06:47:20 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] kvm: x86: disable shattered huge page recovery for
 PREEMPT_RT.
Date: Wed, 13 Nov 2019 15:47:19 +0100
Message-Id: <1573656439-16252-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If a huge page is recovered (and becomes no executable) while another
thread is executing it, the resulting contention on mmu_lock can cause
latency spikes.  Disabling recovery for PREEMPT_RT kernels fixes this
issue.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/mmu.c | 5 +++++
 1 file changed, 5 insertions(+)

```
#### [PATCH] KVM: x86/mmu: Take slots_lock when using kvm_mmu_zap_all_fast()
##### From: Sean Christopherson <sean.j.christopherson@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Sean Christopherson <sean.j.christopherson@intel.com>
X-Patchwork-Id: 11242719
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 05845930
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 19:30:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C9329206E1
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 19:30:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726597AbfKMTaf (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 14:30:35 -0500
Received: from mga06.intel.com ([134.134.136.31]:58143 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726120AbfKMTaf (ORCPT <rfc822;kvm@vger.kernel.org>);
        Wed, 13 Nov 2019 14:30:35 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 13 Nov 2019 11:30:34 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,301,1569308400";
   d="scan'208";a="214379277"
Received: from sjchrist-coffee.jf.intel.com ([10.54.74.41])
  by fmsmga001.fm.intel.com with ESMTP; 13 Nov 2019 11:30:33 -0800
From: Sean Christopherson <sean.j.christopherson@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH] KVM: x86/mmu: Take slots_lock when using
 kvm_mmu_zap_all_fast()
Date: Wed, 13 Nov 2019 11:30:32 -0800
Message-Id: <20191113193032.12912-1-sean.j.christopherson@intel.com>
X-Mailer: git-send-email 2.24.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Acquire the per-VM slots_lock when zapping all shadow pages as part of
toggling nx_huge_pages.  The fast zap algorithm relies on exclusivity
(via slots_lock) to identify obsolete vs. valid shadow pages, e.g. it
uses a single bit for its generation number.  Holding slots_lock also
obviates the need to acquire a read lock on the VM's srcu.

Failing to take slots_lock when toggling nx_huge_pages allows multiple
instances of kvm_mmu_zap_all_fast() to run concurrently, as the other
user, KVM_SET_USER_MEMORY_REGION, does not take the global kvm_lock.
Concurrent fast zap instances causes obsolete shadow pages to be
incorrectly identified as valid due to the single bit generation number
wrapping, which results in stale shadow pages being left in KVM's MMU
and leads to all sorts of undesirable behavior.

The bug is easily confirmed by running with CONFIG_PROVE_LOCKING and
toggling nx_huge_pages via its module param.

Note, the fast zap algorithm could use a 64-bit generation instead of
relying on exclusivity for correctness, but all callers except the
recently added set_nx_huge_pages() need to hold slots_lock anyways.
Given that toggling nx_huge_pages is by no means a fast path, force it
to conform to the current approach instead of reworking the algorithm to
support concurrent calls.

Fixes: b8e8c8303ff28 ("kvm: mmu: ITLB_MULTIHIT mitigation")
Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
---
 arch/x86/kvm/mmu.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: X86: Reset the three MSR list number variables to 0 in kvm_init_msr_list()
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11240641
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E2B0B13BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 01:31:31 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CB5D62084F
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 01:31:31 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727063AbfKMBb3 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 20:31:29 -0500
Received: from mga11.intel.com ([192.55.52.93]:55392 "EHLO mga11.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1726936AbfKMBb2 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 20:31:28 -0500
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga002.fm.intel.com ([10.253.24.26])
  by fmsmga102.fm.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 12 Nov 2019 17:31:27 -0800
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.68,298,1569308400";
   d="scan'208";a="235090663"
Received: from lxy-clx-4s.sh.intel.com ([10.239.43.57])
  by fmsmga002.fm.intel.com with ESMTP; 12 Nov 2019 17:31:25 -0800
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm@vger.kernel.org,
 linux-kernel@vger.kernel.org
Cc: Xiaoyao Li <xiaoyao.li@intel.com>,
        Chenyi Qiang <chenyi.qiang@intel.com>
Subject: [PATCH] KVM: X86: Reset the three MSR list number variables to 0 in
 kvm_init_msr_list()
Date: Wed, 13 Nov 2019 09:15:21 +0800
Message-Id: <20191113011521.32255-1-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.19.1
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When applying commit 7a5ee6edb42e ("KVM: X86: Fix initialization of MSR
lists"), it forgot to reset the three MSR lists number varialbes to 0
while removing the useless conditionals.

Fixes: 7a5ee6edb42e (KVM: X86: Fix initialization of MSR lists)
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/kvm/x86.c | 4 ++++
 1 file changed, 4 insertions(+)

```
#### [PATCH v4 01/23] mm/gup: pass flags arg to __gup_device_* functions
##### From: John Hubbard <jhubbard@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: John Hubbard <jhubbard@nvidia.com>
X-Patchwork-Id: 11240947
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 4BEA11850
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 04:29:21 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 242CB2245D
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 04:29:21 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="qE3W8s6A"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727711AbfKME1W (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Tue, 12 Nov 2019 23:27:22 -0500
Received: from hqemgate14.nvidia.com ([216.228.121.143]:18577 "EHLO
        hqemgate14.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727445AbfKME1T (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Nov 2019 23:27:19 -0500
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqemgate14.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5dcb86230000>; Tue, 12 Nov 2019 20:27:15 -0800
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Tue, 12 Nov 2019 20:27:12 -0800
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Tue, 12 Nov 2019 20:27:12 -0800
Received: from HQMAIL109.nvidia.com (172.20.187.15) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Wed, 13 Nov
 2019 04:27:11 +0000
Received: from hqnvemgw03.nvidia.com (10.124.88.68) by HQMAIL109.nvidia.com
 (172.20.187.15) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Wed, 13 Nov 2019 04:27:11 +0000
Received: from blueforge.nvidia.com (Not Verified[10.110.48.28]) by
 hqnvemgw03.nvidia.com with Trustwave SEG (v7,5,8,10121)
        id <B5dcb861f0002>; Tue, 12 Nov 2019 20:27:11 -0800
From: John Hubbard <jhubbard@nvidia.com>
To: Andrew Morton <akpm@linux-foundation.org>
CC: Al Viro <viro@zeniv.linux.org.uk>,
 Alex Williamson <alex.williamson@redhat.com>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>, =?utf-8?b?QmrDtnJuIFQ=?=
	=?utf-8?b?w7ZwZWw=?= <bjorn.topel@intel.com>,
 Christoph Hellwig <hch@infradead.org>,
 Dan Williams <dan.j.williams@intel.com>, Daniel Vetter <daniel@ffwll.ch>,
 Dave Chinner <david@fromorbit.com>, David Airlie <airlied@linux.ie>,
 "David S . Miller" <davem@davemloft.net>, Ira Weiny <ira.weiny@intel.com>,
 Jan Kara <jack@suse.cz>, Jason Gunthorpe <jgg@ziepe.ca>,
 Jens Axboe <axboe@kernel.dk>, Jonathan Corbet <corbet@lwn.net>,
	=?utf-8?b?SsOpcsO0bWUgR2xpc3Nl?= <jglisse@redhat.com>,
 Magnus Karlsson <magnus.karlsson@intel.com>,
 Mauro Carvalho Chehab <mchehab@kernel.org>,
 Michael Ellerman <mpe@ellerman.id.au>, Michal Hocko <mhocko@suse.com>,
 Mike Kravetz <mike.kravetz@oracle.com>, Paul Mackerras <paulus@samba.org>,
 Shuah Khan <shuah@kernel.org>, Vlastimil Babka <vbabka@suse.cz>,
 <bpf@vger.kernel.org>, <dri-devel@lists.freedesktop.org>,
 <kvm@vger.kernel.org>, <linux-block@vger.kernel.org>,
 <linux-doc@vger.kernel.org>, <linux-fsdevel@vger.kernel.org>,
 <linux-kselftest@vger.kernel.org>, <linux-media@vger.kernel.org>,
 <linux-rdma@vger.kernel.org>, <linuxppc-dev@lists.ozlabs.org>,
 <netdev@vger.kernel.org>, <linux-mm@kvack.org>,
 LKML <linux-kernel@vger.kernel.org>, John Hubbard <jhubbard@nvidia.com>,
 "Kirill A . Shutemov" <kirill.shutemov@linux.intel.com>
Subject: [PATCH v4 01/23] mm/gup: pass flags arg to __gup_device_* functions
Date: Tue, 12 Nov 2019 20:26:48 -0800
Message-ID: <20191113042710.3997854-2-jhubbard@nvidia.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191113042710.3997854-1-jhubbard@nvidia.com>
References: <20191113042710.3997854-1-jhubbard@nvidia.com>
MIME-Version: 1.0
X-NVConfidentiality: public
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1573619235; bh=/JjGbVZJ8qaDHiJyVc8rKJC41LC1ZjvKm126SlEIWtY=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:MIME-Version:X-NVConfidentiality:
         Content-Type:Content-Transfer-Encoding;
        b=qE3W8s6AqwD6cbgLdwzqUNc7SbUs7GA5YfV2t3XnxVB+QWgUTu9PcyBCJDtXYzlSO
         9sx7oJK8l6XoAbnVFWvp8F21EfdhzKQ31VLor1dYrhOrHdjLgCw0qZTsgqAYn2tiD2
         Mt5HPobCijhYjB4iCp8RIWvxNYHqa7d8l+kJ7ONWx7tHU7Spu/shFjIg6Mz+Gf+th/
         5cpt8JEivM2KK3isbB9p2uQvJqTBBILskZUHGdl0xjszHoDa0nwNL1YWZZbuQD04O9
         ArEJvkjovL1Nw7ySC8HXkRJcbRuds14S39DM9Ey3VYb6j8ir9g4NCGiblUu8EjH04x
         VXZwHqY/YO6ug==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

A subsequent patch requires access to gup flags, so
pass the flags argument through to the __gup_device_*
functions.

Also placate checkpatch.pl by shortening a nearby line.

Reviewed-by: Jérôme Glisse <jglisse@redhat.com>
Reviewed-by: Ira Weiny <ira.weiny@intel.com>
Cc: Kirill A. Shutemov <kirill.shutemov@linux.intel.com>
Signed-off-by: John Hubbard <jhubbard@nvidia.com>
Reviewed-by: Jan Kara <jack@suse.cz>
---
 mm/gup.c | 28 ++++++++++++++++++----------
 1 file changed, 18 insertions(+), 10 deletions(-)

```
#### [PATCH v1 2/4] s390x: Define the PSW bits
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11241795
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D679013BD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 12:23:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id C1780222D0
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 12:23:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727216AbfKMMX2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 07:23:28 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:16022 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727187AbfKMMX1 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Nov 2019 07:23:27 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xADCIDv1092780
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 07:23:26 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2w8gmhk0ux-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 07:23:26 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <pmorel@linux.ibm.com>;
        Wed, 13 Nov 2019 12:23:24 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 13 Nov 2019 12:23:21 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xADCMirn39256380
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 Nov 2019 12:22:44 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C577D4C044;
        Wed, 13 Nov 2019 12:23:20 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8FDBE4C04A;
        Wed, 13 Nov 2019 12:23:20 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.152.222.55])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 13 Nov 2019 12:23:20 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com
Subject: [PATCH v1 2/4] s390x: Define the PSW bits
Date: Wed, 13 Nov 2019 13:23:17 +0100
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1573647799-30584-1-git-send-email-pmorel@linux.ibm.com>
References: <1573647799-30584-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19111312-4275-0000-0000-0000037D5F43
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111312-4276-0000-0000-00003890C0A0
Message-Id: <1573647799-30584-3-git-send-email-pmorel@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-13_03:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=532 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1910280000 definitions=main-1911130116
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instead of assigning obfuscated masks to the PSW dedicated to the
exceptions, let's define the masks explicitely, it will clarify the
usage.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 lib/s390x/asm/arch_bits.h | 32 ++++++++++++++++++++++++++++++++
 lib/s390x/asm/arch_def.h  |  6 ++----
 s390x/cstart64.S          | 13 +++++++------
 3 files changed, 41 insertions(+), 10 deletions(-)
 create mode 100644 lib/s390x/asm/arch_bits.h

diff --git a/lib/s390x/asm/arch_bits.h b/lib/s390x/asm/arch_bits.h
new file mode 100644
index 0000000..0521125
--- /dev/null
+++ b/lib/s390x/asm/arch_bits.h
@@ -0,0 +1,32 @@
+
+/*
+ * Copyright (c) 2019 IBM Corp
+ *
+ * Authors:
+ *  Pierre Morel <pmorel@linux.ibm.com>
+ *
+ * This code is free software; you can redistribute it and/or modify it
+ * under the terms of the GNU Library General Public License version 2.
+ */
+#ifndef _ASM_S390X_ARCH_BITS_H_
+#define _ASM_S390X_ARCH_BITS_H_
+
+#define PSW_MASK_PER		0x4000000000000000
+#define PSW_MASK_DAT		0x0400000000000000
+#define PSW_MASK_IO		0x0200000000000000
+#define PSW_MASK_EXT		0x0100000000000000
+#define PSW_MASK_BASE		0x0000000000000000
+#define PSW_MASK_KEY		0x00F0000000000000
+#define PSW_MASK_MCHECK		0x0004000000000000
+#define PSW_MASK_WAIT		0x0002000000000000
+#define PSW_MASK_PSTATE		0x0001000000000000
+#define PSW_MASK_ASC		0x0000C00000000000
+#define PSW_MASK_CC		0x0000300000000000
+#define PSW_MASK_PM		0x00000F0000000000
+#define PSW_MASK_RI		0x0000008000000000
+#define PSW_MASK_EA		0x0000000100000000
+#define PSW_MASK_BA		0x0000000080000000
+
+#define PSW_EXCEPTION_MASK (PSW_MASK_EA|PSW_MASK_BA)
+
+#endif
```
#### [PATCH] selftests: kvm: fix build with glibc >= 2.30
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11241855
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1BFCB15AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 12:51:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F079C21A49
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 12:51:25 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="Qv+QCjhn"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726982AbfKMMvV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 07:51:21 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:22546 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1725908AbfKMMvV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Nov 2019 07:51:21 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1573649480;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=AEYP6d5aalZAfcFv0NrW7o6lXGeRFq/9ZDlpjwAiWdQ=;
        b=Qv+QCjhnD0UYP1bY+Kn48W8Oq7s9S8TJhyjSW1zZuujL9TXIx9/zIIG+waOwfzar/822JM
        KYJHDl19bNL5B5XRx32Z1tO5s4pURIIQWDnXimGAwxXD6ljIKzPHlz3YSYd7ZfPtfqYl7/
        pu1ZYZNjyxIEYkbfn3qmvIC7qwLlN6I=
Received: from mail-wr1-f70.google.com (mail-wr1-f70.google.com
 [209.85.221.70]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-171-y6qiLg7VOXSE0hHxz9-XTw-1; Wed, 13 Nov 2019 07:51:19 -0500
Received: by mail-wr1-f70.google.com with SMTP id c16so1560134wro.1
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 04:51:19 -0800 (PST)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=miLVHytVLBaZY4qRF4Hh54R/kGdync3E1wgmyFgh4so=;
        b=BRL+covJS63WbcxaMyZlCtyhZI2LxwUP14IP+QSt7vM1xCYsKBXJGn+fWA8s6TOcOH
         s9Nrx+EpzTZAxqbdJHoqa2tOePICmxm3Ppmh4F+eN3mOypuuBpr4NVHrRrQIpj7GcvIk
         wYr0iiVUqjyQbJgZlHcuRn8+8t5GZtPE0dB/MsYfk1TbehH3bDU1G/GeNyozBEF3CEB5
         fOIL2U7QHKgBKql1/ztuGuTpauo6FctTifpA0IUl2QI2dThdrAzCxw9ueWiV7+aTwkH4
         NMVJ532nwv1MdSxcLVjSSN8GsUjHa+QGTDMI5Q5Lov+WeDx/EW612QcVZvm+Hs8eGSUg
         HO6Q==
X-Gm-Message-State: APjAAAVySW/Zuug2/GBZz7as1M4tNGqjRJGjo2AGcSKxLHXc3PPslByn
        0Y0SHL+MEz8OguiLZk0O6G3VNJ94419I6jcHtswDUHSef4QTA2TuFHaASlyWDug4Qvgr0b5mg6I
        utbDR3yo9trlR
X-Received: by 2002:adf:dc8d:: with SMTP id r13mr2582106wrj.391.1573649477835;
        Wed, 13 Nov 2019 04:51:17 -0800 (PST)
X-Google-Smtp-Source: 
 APXvYqwqi8MVjGYsZE1Fd2uuOZsh+3k4ruvI3QhtSRwtPfnv/LsKOAMb2NX00BIk78fbl0gKHRqQHQ==
X-Received: by 2002:adf:dc8d:: with SMTP id r13mr2582087wrj.391.1573649477582;
        Wed, 13 Nov 2019 04:51:17 -0800 (PST)
Received: from vitty.brq.redhat.com (nat-pool-brq-t.redhat.com.
 [213.175.37.10])
        by smtp.gmail.com with ESMTPSA id
 u26sm2207436wmj.9.2019.11.13.04.51.16
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Wed, 13 Nov 2019 04:51:16 -0800 (PST)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Subject: [PATCH] selftests: kvm: fix build with glibc >= 2.30
Date: Wed, 13 Nov 2019 13:51:15 +0100
Message-Id: <20191113125115.23100-1-vkuznets@redhat.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-MC-Unique: y6qiLg7VOXSE0hHxz9-XTw-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Glibc-2.30 gained gettid() wrapper, selftests fail to compile:

lib/assert.c:58:14: error: static declaration of ‘gettid’ follows non-static declaration
   58 | static pid_t gettid(void)
      |              ^~~~~~
In file included from /usr/include/unistd.h:1170,
                 from include/test_util.h:18,
                 from lib/assert.c:10:
/usr/include/bits/unistd_ext.h:34:16: note: previous declaration of ‘gettid’ was here
   34 | extern __pid_t gettid (void) __THROW;
      |                ^~~~~~

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 tools/testing/selftests/kvm/lib/assert.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH v1 1/4] s390x: saving regs for interrupts
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11241791
Return-Path: <SRS0=b7qh=ZF=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B02B815AB
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 12:23:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 90E04222CD
	for <patchwork-kvm@patchwork.kernel.org>;
 Wed, 13 Nov 2019 12:23:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727121AbfKMMX0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Wed, 13 Nov 2019 07:23:26 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:59194 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726449AbfKMMX0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Nov 2019 07:23:26 -0500
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 xADCIG5N111667
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 07:23:24 -0500
Received: from e06smtp07.uk.ibm.com (e06smtp07.uk.ibm.com [195.75.94.103])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2w8hdn93ux-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Wed, 13 Nov 2019 07:23:24 -0500
Received: from localhost
        by e06smtp07.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <pmorel@linux.ibm.com>;
        Wed, 13 Nov 2019 12:23:22 -0000
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp07.uk.ibm.com (192.168.101.137) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Wed, 13 Nov 2019 12:23:21 -0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xADCMil528901810
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 Nov 2019 12:22:44 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 849714C044;
        Wed, 13 Nov 2019 12:23:20 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4810A4C046;
        Wed, 13 Nov 2019 12:23:20 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.152.222.55])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 13 Nov 2019 12:23:20 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, frankja@linux.ibm.com,
        david@redhat.com, thuth@redhat.com
Subject: [PATCH v1 1/4] s390x: saving regs for interrupts
Date: Wed, 13 Nov 2019 13:23:16 +0100
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1573647799-30584-1-git-send-email-pmorel@linux.ibm.com>
References: <1573647799-30584-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19111312-0028-0000-0000-000003B686E9
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111312-0029-0000-0000-000024798E7F
Message-Id: <1573647799-30584-2-git-send-email-pmorel@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-11-13_03:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=1 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=693 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1910280000 definitions=main-1911130116
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

If we use multiple source of interrupts, for exemple, using SCLP console
to print information while using I/O interrupts or during exceptions, we
need to have a re-entrant register saving interruption handling.

Instead of saving at a static place, let's save the base registers on
the stack.

Note that we keep the static register saving that we need for the RESET
tests.

We also care to give the handlers a pointer to the save registers in
case the handler needs it (fixup_pgm_int needs the old psw address).

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
---
 lib/s390x/asm/interrupt.h | 15 ++++++++++-----
 lib/s390x/interrupt.c     | 16 ++++++++--------
 s390x/cstart64.S          | 17 ++++++++++++++---
 3 files changed, 32 insertions(+), 16 deletions(-)

```
