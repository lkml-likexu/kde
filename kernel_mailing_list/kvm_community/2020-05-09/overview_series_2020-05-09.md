#### [PATCH v9 1/8] x86/split_lock: Rename TIF_SLD to TIF_SLD_DISABLED
##### From: Xiaoyao Li <xiaoyao.li@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Xiaoyao Li <xiaoyao.li@intel.com>
X-Patchwork-Id: 11537905
Return-Path: <SRS0=tS7s=6X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6545B15E6
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 03:03:46 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 57AE120731
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 03:03:46 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728716AbgEIDDm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 23:03:42 -0400
Received: from mga12.intel.com ([192.55.52.136]:55091 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728717AbgEIDDl (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 May 2020 23:03:41 -0400
IronPort-SDR: 
 6IdfPla3FRkc4FPFOD0QtnxxSJl30OeBEwGedyHKryGypgKS7La4MDhVSGEIJPIYEX+YdIbF/R
 xWktQxW1ieQg==
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga004.jf.intel.com ([10.7.209.38])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 08 May 2020 20:03:41 -0700
IronPort-SDR: 
 Te3FU+RtqOez0or2hntj7545tNBrvWOGgVG24krYgjWFaGqy7B0EK7TZtJO51Z7r9x5oijbjOI
 DyiahqZURsTg==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.73,370,1583222400";
   d="scan'208";a="408310990"
Received: from lxy-dell.sh.intel.com ([10.239.159.21])
  by orsmga004.jf.intel.com with ESMTP; 08 May 2020 20:03:35 -0700
From: Xiaoyao Li <xiaoyao.li@intel.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, x86@kernel.org,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        "H. Peter Anvin" <hpa@zytor.com>,
        Andy Lutomirski <luto@kernel.org>, peterz@infradead.org,
        Arvind Sankar <nivedita@alum.mit.edu>,
        Tony Luck <tony.luck@intel.com>,
        Fenghua Yu <fenghua.yu@intel.com>,
        Xiaoyao Li <xiaoyao.li@intel.com>
Subject: [PATCH v9 1/8] x86/split_lock: Rename TIF_SLD to TIF_SLD_DISABLED
Date: Sat,  9 May 2020 19:05:35 +0800
Message-Id: <20200509110542.8159-2-xiaoyao.li@intel.com>
X-Mailer: git-send-email 2.18.2
In-Reply-To: <20200509110542.8159-1-xiaoyao.li@intel.com>
References: <20200509110542.8159-1-xiaoyao.li@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

TIF_SLD can only be set if a user space thread hits split lock and
sld_state == sld_warn. This flag is set to indicate SLD (split lock
detection) is turned off for the thread, so rename it to
TIF_SLD_DISABLED, which is pretty self explaining.

Suggested-by: Sean Christopherson <sean.j.christopherson@intel.com>
Suggested-by: Thomas Gleixner <tglx@linutronix.de>
Signed-off-by: Xiaoyao Li <xiaoyao.li@intel.com>
---
 arch/x86/include/asm/thread_info.h | 6 +++---
 arch/x86/kernel/cpu/intel.c        | 6 +++---
 arch/x86/kernel/process.c          | 2 +-
 3 files changed, 7 insertions(+), 7 deletions(-)

```
#### [PATCH 1/3 v2] KVM: x86: Create mask for guest CR4 reserved bits in kvm_update_cpuid()
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11537843
Return-Path: <SRS0=tS7s=6X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 92378912
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 01:17:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 75D2820746
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 01:17:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="BY/Ft8PZ"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728415AbgEIBR1 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 8 May 2020 21:17:27 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:51026 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1728158AbgEIBR0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 8 May 2020 21:17:26 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0491DlLB179111;
        Sat, 9 May 2020 01:17:24 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=P5OT0dElPxTY+wegEjp0z6l3XfLXM2labOkeNgvtY64=;
 b=BY/Ft8PZW1z0RzTZHlDbfKx5yYenikZ1+QwaABGLke/JfRqV/5j/ez9xMQz2wnrpMfBw
 IvqWzGix++dYjir5ggVNhHb/9jwx/4zI2V/6mhJ/rSoMEqUM5NDNfB6xAL9C5b4o6Al0
 bU1TkxmC0hst/+ZX95BrSpLDOFPKAtJjJjK8bq0IzLSH0dYxBLFJ1IblPQgPJVXg8/5h
 TRXBFjffpBBnV+1EkO2eVkRb4aSn4VPDbXrb2oAHVQfT1EYCEdGIil8kdkpq5ZiTxTa1
 rWsHCZqYIGvW/FYCUarERaMzMlmYEjtWnajL55E3gynozIwjvugu7hEaPAGMNLziFShn rg==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 30vtepnw2x-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 09 May 2020 01:17:24 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04917cB1048349;
        Sat, 9 May 2020 01:17:24 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 30vte1p7tk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 09 May 2020 01:17:23 +0000
Received: from abhmp0010.oracle.com (abhmp0010.oracle.com [141.146.116.16])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0491HM4O009186;
        Sat, 9 May 2020 01:17:22 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 08 May 2020 18:17:22 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 1/3 v2] KVM: x86: Create mask for guest CR4 reserved bits in
 kvm_update_cpuid()
Date: Fri,  8 May 2020 20:36:50 -0400
Message-Id: <20200509003652.25178-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200509003652.25178-1-krish.sadhukhan@oracle.com>
References: <20200509003652.25178-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9615
 signatures=668687
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=999
 phishscore=0
 bulkscore=0 malwarescore=0 suspectscore=1 adultscore=0 mlxscore=0
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2003020000 definitions=main-2005090008
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9615
 signatures=668687
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 adultscore=0
 spamscore=0
 impostorscore=0 phishscore=0 clxscore=1015 priorityscore=1501
 lowpriorityscore=0 malwarescore=0 suspectscore=1 mlxscore=0
 mlxlogscore=999 bulkscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2003020000 definitions=main-2005090008
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
 arch/x86/kvm/cpuid.c |  3 +++
 arch/x86/kvm/x86.c   | 24 ++----------------------
 arch/x86/kvm/x86.h   | 21 +++++++++++++++++++++
 3 files changed, 26 insertions(+), 22 deletions(-)

```
#### [PATCH kvm-unit-tests] svm_tests: add RSM intercept test
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11538299
Return-Path: <SRS0=tS7s=6X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A2F1481
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 14:06:35 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8A42621655
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 14:06:35 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="f9Dwad1P"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727106AbgEIOGV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 9 May 2020 10:06:21 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:35211 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727092AbgEIOGV (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 9 May 2020 10:06:21 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589033180;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc; bh=4i8mGUWttw4oOkp1Jk8ARsgUGl5YbWkieitfPAJSHiA=;
        b=f9Dwad1P+RYqIw5nX752alfqLv973EZ0/LtImKphsLelKKG2opSy3TpP+J3UHLFr5nrc7t
        lkWMAmBpMt2dcAC3c4sBKlXezYFZ9IdzOoxR6UuJxpjbG1POS5DyvmUzH0Vu1NFM8OZqJ7
        bUTlcg/50gWfKtr1SRTnlyeWm97db9k=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-468-11Dnuj8vNXqWR5uP-mxXTQ-1; Sat, 09 May 2020 10:06:16 -0400
X-MC-Unique: 11Dnuj8vNXqWR5uP-mxXTQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id EA7751895A3F
        for <kvm@vger.kernel.org>; Sat,  9 May 2020 14:06:15 +0000 (UTC)
Received: from virtlab511.virt.lab.eng.bos.redhat.com
 (virtlab511.virt.lab.eng.bos.redhat.com [10.19.152.198])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 95FB219C58
        for <kvm@vger.kernel.org>; Sat,  9 May 2020 14:06:15 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] svm_tests: add RSM intercept test
Date: Sat,  9 May 2020 10:06:14 -0400
Message-Id: <20200509140614.531850-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This test is currently broken, but it passes under QEMU.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 x86/svm_tests.c | 49 +++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 49 insertions(+)

```
#### [PATCH kvm-unit-tests] svm: Test V_IRQ injection
##### From: Cathy Avery <cavery@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 11538221
Return-Path: <SRS0=tS7s=6X=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D60D5912
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 11:16:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id AFD602495B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  9 May 2020 11:16:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="bWiaLslB"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728635AbgEILQl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 9 May 2020 07:16:41 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:41124 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1728260AbgEILQ3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 9 May 2020 07:16:29 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589022987;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=i65u0loZ+URx1fB/wqG6cjTO7Ynjzo+5bpMPHJof7I0=;
        b=bWiaLslBj1Kchbzs7zG+iZoX2vp7C5AUXeot6X23NiroeRP3JYjzsAVzXn0GBY97GeJhWb
        lKk5sXRglyni6i2fw8om42sxq57V5g/oATg1D+6RT1siy+yk10p24gNI7XtZCPtIdA3Jqa
        0xGrUXOkaiqtmpC2QNtYAmeGYUjSQsM=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-78-pgXS5jojMwenKNne6iLgaA-1; Sat, 09 May 2020 07:16:24 -0400
X-MC-Unique: pgXS5jojMwenKNne6iLgaA-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2E42A80058A;
        Sat,  9 May 2020 11:16:23 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 998DA61982;
        Sat,  9 May 2020 11:16:22 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Subject: [PATCH kvm-unit-tests] svm: Test V_IRQ injection
Date: Sat,  9 May 2020 07:16:22 -0400
Message-Id: <20200509111622.2184-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Test V_IRQ injection from L1 to L2 with V_TPR less
than or greater than V_INTR_PRIO. Also test VINTR
intercept with differing V_TPR and V_INTR_PRIO.

Signed-off-by: Cathy Avery <cavery@redhat.com>
---
 x86/svm_tests.c | 150 ++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 150 insertions(+)

```
