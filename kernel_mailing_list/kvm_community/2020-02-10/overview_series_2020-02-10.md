#### [PATCH 01/28] docs: kvm: add arm/pvtime.rst to index.rst
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11372549
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6774914B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 06:03:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 3D4182465A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 06:03:40 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581314620;
	bh=RQJBSrCBQoRjRPzNpPiEOUwoi4zmhWHM5Ddo22O4ojU=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=WTXFz0h0NxScoe6NZy15P9DDutiQPHhEqJNbJ0CFd27XmmgdCdkOFz9htT9lOBaSS
	 nG6FDBmtgoWMcx8ipJyrKdFzGGCIj2FRpcsvzGLWNx+rbU/lIPwhUGt2NoRQFCmfCA
	 jL8sHAwT4eDsUG3f9rByqfmAe5R8oS4iQu1vp9mk=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727556AbgBJGDM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Feb 2020 01:03:12 -0500
Received: from bombadil.infradead.org ([198.137.202.133]:36292 "EHLO
        bombadil.infradead.org" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727437AbgBJGDM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Feb 2020 01:03:12 -0500
DKIM-Signature: v=1; a=rsa-sha256; q=dns/txt; c=relaxed/relaxed;
        d=infradead.org; s=bombadil.20170209;
 h=Sender:Content-Transfer-Encoding:
        MIME-Version:References:In-Reply-To:Message-Id:Date:Subject:Cc:To:From:
        Reply-To:Content-Type:Content-ID:Content-Description;
        bh=/hfBTm+pwI/qMUzI6610HUXH01FV0FRb49kTIzGz0Ww=;
 b=YY9qMpTF6MirjG2R1XRdVVXM/9
        N2+i4gF3kDFNMMHfPjhir+tVy3kgLQ2Y+BluhTTxFRka0VQmvRE9kvlYdNwX60GvAGy/CrPTLRlt9
        G42D6+D8EE+h8b2yY9SuOheFq81KCSUVgwX6VnNm1a3DdIu35kocWvdgtUb3vivkZJ4fw+jsSuXj1
        6NVt2lsSLNxH3HZ0gS/XvEVQB8+So8pcGKeOFTN2xgRb8YwxL0qYpeXWbc160C13lCiJXmSsTkQcN
        v3PUJPxMfjgpG7WxZsBlHCZRnnX9V9gF2ckDxXPT83FRs5I92MJEEemVUZrZgkqSMvsH5AlSBMAJE
        6idRmYSg==;
Received: from [80.156.29.194] (helo=bombadil.infradead.org)
        by bombadil.infradead.org with esmtpsa (Exim 4.92.3 #3 (Red Hat
 Linux))
        id 1j12A3-0006Tb-DC; Mon, 10 Feb 2020 06:03:11 +0000
Received: from mchehab by bombadil.infradead.org with local (Exim 4.92.3)
        (envelope-from <mchehab@bombadil.infradead.org>)
        id 1j12A1-00C2Ud-Nl; Mon, 10 Feb 2020 07:03:09 +0100
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Media Mailing List <linux-media@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        Mauro Carvalho Chehab <mchehab@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Jonathan Corbet <corbet@lwn.net>, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org
Subject: [PATCH 01/28] docs: kvm: add arm/pvtime.rst to index.rst
Date: Mon, 10 Feb 2020 07:02:39 +0100
Message-Id: 
 <cdea3a1899e21395073b8e4a02fb3db88dc63974.1581314316.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.24.1
In-Reply-To: <cover.1581314316.git.mchehab+huawei@kernel.org>
References: <cover.1581314316.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add this file to a new kvm/arm index.rst, in order for it to
be shown as part of the virt book.

Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
---
 Documentation/virt/kvm/arm/index.rst | 10 ++++++++++
 Documentation/virt/kvm/index.rst     |  2 ++
 2 files changed, 12 insertions(+)
 create mode 100644 Documentation/virt/kvm/arm/index.rst

diff --git a/Documentation/virt/kvm/arm/index.rst b/Documentation/virt/kvm/arm/index.rst
new file mode 100644
index 000000000000..e039d9b1e076
--- /dev/null
+++ b/Documentation/virt/kvm/arm/index.rst
@@ -0,0 +1,10 @@
+.. SPDX-License-Identifier: GPL-2.0
+
+===
+ARM
+===
+
+.. toctree::
+   :maxdepth: 2
+
+   pvtime
```
#### [RFC PATCH 1/9] psci: export psci conduit get helper.
##### From: Jianyong Wu <jianyong.wu@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jianyong Wu <jianyong.wu@arm.com>
X-Patchwork-Id: 11372745
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 81D3A14B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 08:49:36 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6C1FB20733
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 08:49:36 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727556AbgBJItc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Feb 2020 03:49:32 -0500
Received: from foss.arm.com ([217.140.110.172]:57446 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727429AbgBJItb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Feb 2020 03:49:31 -0500
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id EF2DE328;
        Mon, 10 Feb 2020 00:49:30 -0800 (PST)
Received: from entos-d05.shanghai.arm.com (entos-d05.shanghai.arm.com
 [10.169.40.35])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 8844B3F68F;
        Mon, 10 Feb 2020 00:49:25 -0800 (PST)
From: Jianyong Wu <jianyong.wu@arm.com>
To: netdev@vger.kernel.org, yangbo.lu@nxp.com, john.stultz@linaro.org,
        tglx@linutronix.de, pbonzini@redhat.com,
        sean.j.christopherson@intel.com, maz@kernel.org,
        richardcochran@gmail.com, Mark.Rutland@arm.com, will@kernel.org,
        suzuki.poulose@arm.com, steven.price@arm.com
Cc: linux-kernel@vger.kernel.org, linux-arm-kernel@lists.infradead.org,
        kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org,
        Steve.Capper@arm.com, Kaly.Xin@arm.com, justin.he@arm.com,
        jianyong.wu@arm.com, nd@arm.com
Subject: [RFC PATCH 1/9] psci: export psci conduit get helper.
Date: Mon, 10 Feb 2020 16:48:58 +0800
Message-Id: <20200210084906.24870-2-jianyong.wu@arm.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200210084906.24870-1-jianyong.wu@arm.com>
References: <20200210084906.24870-1-jianyong.wu@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Export arm_smccc_1_1_get_conduit then modules can use smccc helper which
adopts it.

Signed-off-by: Jianyong Wu <jianyong.wu@arm.com>
---
 drivers/firmware/psci/psci.c | 1 +
 1 file changed, 1 insertion(+)

```
#### [kvm-unit-tests v2 PATCH] Fixes for the umip test
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11373389
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A4DB914B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 14:35:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8608D2082F
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 14:35:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ZuKhOp3o"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727775AbgBJOf0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Feb 2020 09:35:26 -0500
Received: from us-smtp-delivery-1.mimecast.com ([207.211.31.120]:21388 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726961AbgBJOf0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Feb 2020 09:35:26 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581345325;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=wxwzfEhD9lbwARMsqltvsS9V4fe5j1xN/yz0t79bhtk=;
        b=ZuKhOp3ofanW/GjapSxcDh4UnINJWFu4lSOi8ORlSmZgcxvAoP4KO47NTc3QuPV55ZX28u
        dSIyt+Doc8MivMt/aITzF/5nrl5yY9CEDAIXT23xYyD2hM8hKclbG51enfuAX1PBSJA+Ml
        70RVa7A90oRy17lExIIA1lxAYj59/pg=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-365-eIlyUFOpOBCarOq_q-uY1w-1; Mon, 10 Feb 2020 09:35:21 -0500
X-MC-Unique: eIlyUFOpOBCarOq_q-uY1w-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BEC008017CC
        for <kvm@vger.kernel.org>; Mon, 10 Feb 2020 14:35:20 +0000 (UTC)
Received: from thuth.com (ovpn-116-219.ams2.redhat.com [10.36.116.219])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AFCA760BF1;
        Mon, 10 Feb 2020 14:35:19 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Vitaly Kuznetsov <vkuznets@redhat.com>
Subject: [kvm-unit-tests v2 PATCH] Fixes for the umip test
Date: Mon, 10 Feb 2020 15:35:14 +0100
Message-Id: <20200210143514.5347-1-thuth@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

When compiling umip.c with -O2 instead of -O1, there are currently
two problems. First, the compiler complains:

 x86/umip.c: In function ‘do_ring3’:
 x86/umip.c:162:37: error: array subscript 4096 is above array bounds of
    ‘unsigned char[4096]’ [-Werror=array-bounds]
       [user_stack_top]"m"(user_stack[sizeof user_stack]),
                           ~~~~~~~~~~^~~~~~~~~~~~~~~~~~~

This can be fixed by initializing the stack to point to one of the last
bytes of the array instead.

The second problem is that some tests are failing - and this is due
to the fact that the GP_ASM macro uses inline asm without the "volatile"
keyword - so that the compiler reorders this code in certain cases
where it should not. Fix it by adding "volatile" here.

Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 v2: Add parentheses and fix doubled whitespace as requested by Vitaly

 x86/umip.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

```
#### [PATCH/RFC] KVM: s390: protvirt: pass-through rc and rrc
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11373075
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D5E1514B4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 11:45:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AF72A20842
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 11:45:34 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727437AbgBJLpe (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Feb 2020 06:45:34 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:60768 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726950AbgBJLpd (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 Feb 2020 06:45:33 -0500
Received: from pps.filterd (m0098421.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01ABiJjJ062110;
        Mon, 10 Feb 2020 06:45:31 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y1tp147w3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Feb 2020 06:45:31 -0500
Received: from m0098421.ppops.net (m0098421.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01ABiTVx062650;
        Mon, 10 Feb 2020 06:45:31 -0500
Received: from ppma04wdc.us.ibm.com (1a.90.2fa9.ip4.static.sl-reverse.com
 [169.47.144.26])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y1tp147vs-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Feb 2020 06:45:31 -0500
Received: from pps.filterd (ppma04wdc.us.ibm.com [127.0.0.1])
        by ppma04wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01ABj8X5006826;
        Mon, 10 Feb 2020 11:45:30 GMT
Received: from b01cxnp23032.gho.pok.ibm.com (b01cxnp23032.gho.pok.ibm.com
 [9.57.198.27])
        by ppma04wdc.us.ibm.com with ESMTP id 2y1mm68rn2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Feb 2020 11:45:30 +0000
Received: from b01ledav002.gho.pok.ibm.com (b01ledav002.gho.pok.ibm.com
 [9.57.199.107])
        by b01cxnp23032.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 01ABjSX353608932
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 Feb 2020 11:45:28 GMT
Received: from b01ledav002.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6F7F3124053;
        Mon, 10 Feb 2020 11:45:28 +0000 (GMT)
Received: from b01ledav002.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5567D124052;
        Mon, 10 Feb 2020 11:45:28 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav002.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon, 10 Feb 2020 11:45:28 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: borntraeger@de.ibm.com
Cc: Ulrich.Weigand@de.ibm.com, aarcange@redhat.com, cohuck@redhat.com,
        david@redhat.com, frankja@linux.ibm.com,
        frankja@linux.vnet.ibm.com, gor@linux.ibm.com,
        imbrenda@linux.ibm.com, kvm@vger.kernel.org,
        linux-s390@vger.kernel.org, mimu@linux.ibm.com, thuth@redhat.com
Subject: [PATCH/RFC] KVM: s390: protvirt: pass-through rc and rrc
Date: Mon, 10 Feb 2020 06:45:26 -0500
Message-Id: <20200210114526.134769-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <62d5cd46-93d7-e272-f9bb-d4ec3c7a1f71@de.ibm.com>
References: <62d5cd46-93d7-e272-f9bb-d4ec3c7a1f71@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-10_02:2020-02-10,2020-02-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0
 mlxlogscore=999 spamscore=0 clxscore=1015 bulkscore=0 phishscore=0
 mlxscore=0 lowpriorityscore=0 suspectscore=3 adultscore=0 impostorscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002100093
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This would be one variant to get the RC/RRC to userspace.

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/kvm-s390.c | 34 +++++++++++++++++++++++++---------
 arch/s390/kvm/kvm-s390.h | 15 ++++++++-------
 arch/s390/kvm/pv.c       | 30 ++++++++++++++++++++++--------
 include/uapi/linux/kvm.h |  4 ++--
 4 files changed, 57 insertions(+), 26 deletions(-)

```
#### [RFC PATCH 1/5] arm: Unplug KVM from the build system
##### From: Marc Zyngier <maz@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Marc Zyngier <maz@kernel.org>
X-Patchwork-Id: 11373355
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0C352186E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 14:13:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DD83E2168B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 14:13:32 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1581344012;
	bh=1Ksq9sSntq5AlQyVIEEudZ7m8YBzrTT24xuJB8Lv5Pg=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=A/bUnJMIgj9InE55RB177b6Ye2pwdXg7lgAmuwc/q218NUBDfGaM3kDLj1IOiYP6N
	 46iRBRl3ttklLF/GYQa+g3WkKLZBfK1CxZ465Zrs97Zd06h6rmqdcxT2D2YK27StoA
	 91VaX7wr9O0pg6N4hk0VAfGdz/79UJ1Kg6111eBc=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728579AbgBJONc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Feb 2020 09:13:32 -0500
Received: from mail.kernel.org ([198.145.29.99]:49092 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727563AbgBJONb (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Feb 2020 09:13:31 -0500
Received: from disco-boy.misterjones.org (disco-boy.misterjones.org
 [51.254.78.96])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id AFBC42082F;
        Mon, 10 Feb 2020 14:13:30 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1581344010;
        bh=1Ksq9sSntq5AlQyVIEEudZ7m8YBzrTT24xuJB8Lv5Pg=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=LM9MCmEPfyhMuJLD1nzYm2cfEhexKk8SzZby6gvTHoGhCO5wKlOE/Kbntnom+E0Bk
         ITBn7lkyrK3xhdulzbRWKSiNSQI0Mw0XvK7yIBJckYJUi2u++musH7NYWPYfTVBoY4
         zrFz/kA/vJQ72F09KjUr0vkI2XircEJcQkRy/HSw=
Received: from 78.163-31-62.static.virginmediabusiness.co.uk ([62.31.163.78]
 helo=why.lan)
        by disco-boy.misterjones.org with esmtpsa
 (TLS1.3:ECDHE_RSA_AES_256_GCM_SHA384:256)
        (Exim 4.92)
        (envelope-from <maz@kernel.org>)
        id 1j19oX-0048kH-1T; Mon, 10 Feb 2020 14:13:29 +0000
From: Marc Zyngier <maz@kernel.org>
To: linux-arm-kernel@lists.infradead.org, kvmarm@lists.cs.columbia.edu,
        kvm@vger.kernel.org
Cc: James Morse <james.morse@arm.com>,
        Julien Thierry <julien.thierry.kdev@gmail.com>,
        Suzuki K Poulose <suzuki.poulose@arm.com>,
        Paolo Bonzini <pbonzini@redhat.com>,
        Christoffer Dall <Christoffer.Dall@arm.com>,
        Will Deacon <will@kernel.org>,
        Quentin Perret <qperret@google.com>,
        Russell King <linux@arm.linux.org.uk>,
        Vladimir Murzin <vladimir.murzin@arm.com>,
        Anders Berg <anders.berg@lsi.com>,
        Arnd Bergmann <arnd@arndb.de>
Subject: [RFC PATCH 1/5] arm: Unplug KVM from the build system
Date: Mon, 10 Feb 2020 14:13:20 +0000
Message-Id: <20200210141324.21090-2-maz@kernel.org>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200210141324.21090-1-maz@kernel.org>
References: <20200210141324.21090-1-maz@kernel.org>
MIME-Version: 1.0
X-SA-Exim-Connect-IP: 62.31.163.78
X-SA-Exim-Rcpt-To: linux-arm-kernel@lists.infradead.org,
 kvmarm@lists.cs.columbia.edu, kvm@vger.kernel.org, james.morse@arm.com,
 julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com, pbonzini@redhat.com,
 Christoffer.Dall@arm.com, will@kernel.org, qperret@google.com,
 linux@arm.linux.org.uk, vladimir.murzin@arm.com, anders.berg@lsi.com,
 arnd@arndb.de
X-SA-Exim-Mail-From: maz@kernel.org
X-SA-Exim-Scanned: No (on disco-boy.misterjones.org);
 SAEximRunCond expanded to false
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As we're about to drop KVM/arm on the floor, carefully unplug
it from the build system.

Signed-off-by: Marc Zyngier <maz@kernel.org>
---
 arch/arm/Kconfig             | 2 --
 arch/arm/Makefile            | 1 -
 arch/arm/mach-exynos/Kconfig | 2 +-
 3 files changed, 1 insertion(+), 4 deletions(-)

```
#### [PATCH 1/1] s390/uv: Fix handling of length extensions
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11373631
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0631D109A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 16:54:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id E459920838
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 16:54:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727881AbgBJQyq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Feb 2020 11:54:46 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:42002 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1727860AbgBJQyp (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 10 Feb 2020 11:54:45 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01AGrOTu061893;
        Mon, 10 Feb 2020 11:54:44 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y1u2dxesy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Feb 2020 11:54:44 -0500
Received: from m0098410.ppops.net (m0098410.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01AGrctG063026;
        Mon, 10 Feb 2020 11:54:44 -0500
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y1u2dxesa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Feb 2020 11:54:44 -0500
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01AGrOuh024135;
        Mon, 10 Feb 2020 16:54:43 GMT
Received: from b03cxnp07028.gho.boulder.ibm.com
 (b03cxnp07028.gho.boulder.ibm.com [9.17.130.15])
        by ppma02wdc.us.ibm.com with ESMTP id 2y1mm6bfky-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 10 Feb 2020 16:54:42 +0000
Received: from b03ledav001.gho.boulder.ibm.com
 (b03ledav001.gho.boulder.ibm.com [9.17.130.232])
        by b03cxnp07028.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 01AGsfIi11862510
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 10 Feb 2020 16:54:41 GMT
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6B6866E05E;
        Mon, 10 Feb 2020 16:54:41 +0000 (GMT)
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D3EE06E056;
        Mon, 10 Feb 2020 16:54:40 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b03ledav001.gho.boulder.ibm.com (Postfix) with ESMTP;
        Mon, 10 Feb 2020 16:54:40 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Christian Borntraeger <borntraeger@de.ibm.com>,
        Janosch Frank <frankja@linux.vnet.ibm.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        David Hildenbrand <david@redhat.com>,
        Thomas Huth <thuth@redhat.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Vasily Gorbik <gor@linux.ibm.com>
Subject: [PATCH 1/1] s390/uv: Fix handling of length extensions
Date: Mon, 10 Feb 2020 11:54:39 -0500
Message-Id: <20200210165439.3767-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20200210165439.3767-1-borntraeger@de.ibm.com>
References: <20200210165439.3767-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-10_06:2020-02-10,2020-02-10 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 phishscore=0 malwarescore=0 adultscore=0 mlxlogscore=985 bulkscore=0
 spamscore=0 impostorscore=0 lowpriorityscore=0 mlxscore=0 suspectscore=0
 clxscore=1015 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2001150001 definitions=main-2002100126
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The query parameter block might contain additional information and can
be extended in the future. If the size of the block does not suffice we
get an error code of rc=0x100.  The buffer will contain all information
up to the specified size and the hypervisor/guest simply do not need the
additional information as they do not know about the new data.  That
means that we can (and must) accept rc=0x100 as success.

Cc: stable@vger.kernel.org
Fixes: 5abb9351dfd9 ("s390/uv: introduce guest side ultravisor code")
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/boot/uv.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH v2 1/2] KVM: Introduce pv check helpersTo: LKML <linux-kernel@vger.kernel.org>, kvm <kvm@vger.kernel.org>
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11372629
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 41EB592A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 06:37:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 203C222464
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 06:37:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="Mxve/0KY"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726376AbgBJGhm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 10 Feb 2020 01:37:42 -0500
Received: from mail-oi1-f195.google.com ([209.85.167.195]:33227 "EHLO
        mail-oi1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726061AbgBJGhm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 10 Feb 2020 01:37:42 -0500
Received: by mail-oi1-f195.google.com with SMTP id q81so8234585oig.0;
        Sun, 09 Feb 2020 22:37:42 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=mime-version:from:date:message-id:subject:to:cc;
        bh=sKP+BJ8wBjzEgCx/CYPr7X88CtkSZccKI/5Y02IAgCw=;
        b=Mxve/0KYXH5nHyM1kFSEhNJmYGTlousTYlbYqS1jOPMFF5Veo/9Y2Jz1JOPiMBxd9F
         OYJp9/qUWlj1VlP5SVdNPe3cDJp8BRmqXRUc+QirNj1+jVPKR/LaoO0FKG8JjiD+U8C2
         t/V0PS0BVV4yqtu836kFnbTc2GIylo8fX1pZijFgOvBNGt69qJjka+wCv4XH7ngpfNbA
         7qKphDgW2Ylk7KYUJxic314TvJcqfmzbmHImnajj6+LLQpl2XF7ceLHcpuCVjocUpF4x
         qgjSpPAbumAqrOU5NtK5x7k+FtzTzhUMguu9pukthdhin5KYXOcjaz9I4j09j36Svtyq
         uQqg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:mime-version:from:date:message-id:subject:to:cc;
        bh=sKP+BJ8wBjzEgCx/CYPr7X88CtkSZccKI/5Y02IAgCw=;
        b=q4I+u0kM7VPW0F+4tpv66M4fq4iF0jK6Ydp/dtkfjRSpLWEWcc3TdfQ9kmolDqM1/D
         D97b/isQ41OQB2X5C5RorWNYAz3ySeURpy+XYhWwP487JQLIDpx2UwDyDpmoyj6rOkFB
         6j57CAzBvXEIYxhy+D2RyqfaKJbdZwmPaQVkPIXCBV4bsi9Wc7BgcQ+CcxtZ1iuqvFpl
         KedUnjmnEH+ytrSadgrZgKJaSJ0J6EeA1VXVq7A92oXR7AiYzakGAu/AHHRVYZ5CjPX2
         Mn5DQQckPwfmYzf3KAtw1KCOu8zxvoCnAZSh0fFgectpeGoSj9bmUDdLWPwScPIAflMp
         Am+w==
X-Gm-Message-State: APjAAAWNcM3DM1QK0hKfE9rHA7HoHI8x+EkTfWWxhRR92+d9vHnneGK0
        cEHat6utClocboYd7S5vPPpPCtw3HxOgSb/P6ud5mKYtyP/Xpw==
X-Google-Smtp-Source: 
 APXvYqz1VjnaGereiNdTBdBdTbpaWc/Yme4gnjBca8gp58S465ODJyip6auKSicR/eGvEjwcpEpXy4CtvheHR9SeKG0=
X-Received: by 2002:aca:f305:: with SMTP id r5mr10049656oih.174.1581316661703;
 Sun, 09 Feb 2020 22:37:41 -0800 (PST)
MIME-Version: 1.0
From: Wanpeng Li <kernellwp@gmail.com>
Date: Mon, 10 Feb 2020 14:37:30 +0800
Message-ID: 
 <CANRm+Cxd55Sqi4anpXD_Urmx8BV=R9ZDUwejChJHLBsZeGoWbw@mail.gmail.com>
Subject: [PATCH v2 1/2] KVM: Introduce pv check helpers
To: LKML <linux-kernel@vger.kernel.org>, kvm <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

Introduce some pv check helpers for consistency.

Suggested-by: Vitaly Kuznetsov <vkuznets@redhat.com>
Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
Reviewed-by: Konrad Rzeszutek Wilk <konrad.wilk@oracle.com>
---
 arch/x86/kernel/kvm.c | 34 ++++++++++++++++++++++++----------
 1 file changed, 24 insertions(+), 10 deletions(-)

--
2.7.4

```
#### [PATCH V2 1/5] vhost: factor out IOTLB
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11372417
Return-Path: <SRS0=Y5yW=36=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 754BE13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 03:58:38 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2B7AF208C4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 10 Feb 2020 03:58:38 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="P06PX5+X"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727507AbgBJD6h (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 9 Feb 2020 22:58:37 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:33094 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1727029AbgBJD6g (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 9 Feb 2020 22:58:36 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1581307114;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=Kpv3bBGF0E+FDDFMIK1dsa1lVOjX2mb5tVfmSaJJef4=;
        b=P06PX5+XKolbNo6soPmvBw4QQBYTyzVC+W2B4OtzOlxuPD3ImXWKe4wB0+GsVel4R+ByGj
        XPywMNN6D+pFkseUDM+jVkp88Ha24s1o+YkqHMzOgZCiVseENMt64u7YdJuLDq3ubbIzYg
        GJPaJGR6NLvuawpZ9vZameSM9ggkGNQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-250-yi6gLG5eP8WhCsevVKVpNw-1; Sun, 09 Feb 2020 22:58:32 -0500
X-MC-Unique: yi6gLG5eP8WhCsevVKVpNw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C9C61477;
        Mon, 10 Feb 2020 03:58:29 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-13-219.pek2.redhat.com [10.72.13.219])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 475411001B23;
        Mon, 10 Feb 2020 03:57:28 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Cc: tiwei.bie@intel.com, jgg@mellanox.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, lingshan.zhu@intel.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        kevin.tian@intel.com, stefanha@redhat.com, rdunlap@infradead.org,
        hch@infradead.org, aadam@redhat.com, jiri@mellanox.com,
        shahafs@mellanox.com, hanand@xilinx.com, mhabets@solarflare.com,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V2 1/5] vhost: factor out IOTLB
Date: Mon, 10 Feb 2020 11:56:04 +0800
Message-Id: <20200210035608.10002-2-jasowang@redhat.com>
In-Reply-To: <20200210035608.10002-1-jasowang@redhat.com>
References: <20200210035608.10002-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch factors out IOTLB into a dedicated module in order to be
reused by other modules like vringh. User may choose to enable the
automatic retiring by specifying VHOST_IOTLB_FLAG_RETIRE flag to fit
for the case of vhost device IOTLB implementation.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 MAINTAINERS                 |   1 +
 drivers/vhost/Kconfig       |   7 ++
 drivers/vhost/Makefile      |   2 +
 drivers/vhost/net.c         |   2 +-
 drivers/vhost/vhost.c       | 221 +++++++++++-------------------------
 drivers/vhost/vhost.h       |  36 ++----
 drivers/vhost/vhost_iotlb.c | 171 ++++++++++++++++++++++++++++
 include/linux/vhost_iotlb.h |  45 ++++++++
 8 files changed, 304 insertions(+), 181 deletions(-)
 create mode 100644 drivers/vhost/vhost_iotlb.c
 create mode 100644 include/linux/vhost_iotlb.h

```
