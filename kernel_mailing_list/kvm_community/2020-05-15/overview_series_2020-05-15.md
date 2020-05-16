#### [PATCH Kernel v21 1/8] vfio: UAPI for migration interface for device state
##### From: Kirti Wankhede <kwankhede@nvidia.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Kirti Wankhede <kwankhede@nvidia.com>
X-Patchwork-Id: 11553077
Return-Path: <SRS0=+vSx=65=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 161BC138A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 21:46:44 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E9C192070A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 21:46:43 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=nvidia.com header.i=@nvidia.com
 header.b="Og8UVEgG"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727779AbgEOVqn (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 May 2020 17:46:43 -0400
Received: from hqnvemgate24.nvidia.com ([216.228.121.143]:9449 "EHLO
        hqnvemgate24.nvidia.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726228AbgEOVqm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 May 2020 17:46:42 -0400
Received: from hqpgpgate102.nvidia.com (Not Verified[216.228.121.13]) by
 hqnvemgate24.nvidia.com (using TLS: TLSv1.2, DES-CBC3-SHA)
        id <B5ebf0d370000>; Fri, 15 May 2020 14:44:23 -0700
Received: from hqmail.nvidia.com ([172.20.161.6])
  by hqpgpgate102.nvidia.com (PGP Universal service);
  Fri, 15 May 2020 14:46:42 -0700
X-PGP-Universal: processed;
        by hqpgpgate102.nvidia.com on Fri, 15 May 2020 14:46:42 -0700
Received: from HQMAIL105.nvidia.com (172.20.187.12) by HQMAIL101.nvidia.com
 (172.20.187.10) with Microsoft SMTP Server (TLS) id 15.0.1473.3; Fri, 15 May
 2020 21:46:42 +0000
Received: from kwankhede-dev.nvidia.com (10.124.1.5) by HQMAIL105.nvidia.com
 (172.20.187.12) with Microsoft SMTP Server (TLS) id 15.0.1473.3 via Frontend
 Transport; Fri, 15 May 2020 21:46:35 +0000
From: Kirti Wankhede <kwankhede@nvidia.com>
To: <alex.williamson@redhat.com>, <cjia@nvidia.com>
CC: <kevin.tian@intel.com>, <ziye.yang@intel.com>,
        <changpeng.liu@intel.com>, <yi.l.liu@intel.com>,
        <mlevitsk@redhat.com>, <eskultet@redhat.com>, <cohuck@redhat.com>,
        <dgilbert@redhat.com>, <jonathan.davies@nutanix.com>,
        <eauger@redhat.com>, <aik@ozlabs.ru>, <pasic@linux.ibm.com>,
        <felipe@nutanix.com>, <Zhengxiao.zx@Alibaba-inc.com>,
        <shuangtai.tst@alibaba-inc.com>, <Ken.Xue@amd.com>,
        <zhi.a.wang@intel.com>, <yan.y.zhao@intel.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        "Kirti Wankhede" <kwankhede@nvidia.com>
Subject: [PATCH Kernel v21 1/8] vfio: UAPI for migration interface for device
 state
Date: Sat, 16 May 2020 02:43:16 +0530
Message-ID: <1589577203-20640-2-git-send-email-kwankhede@nvidia.com>
X-Mailer: git-send-email 2.7.0
In-Reply-To: <1589577203-20640-1-git-send-email-kwankhede@nvidia.com>
References: <1589577203-20640-1-git-send-email-kwankhede@nvidia.com>
X-NVConfidentiality: public
MIME-Version: 1.0
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=nvidia.com; s=n1;
        t=1589579063; bh=s4Iv0GJDj+1bhl4jbE8YcxRvsfl81dyjXBeOzB1RdI0=;
        h=X-PGP-Universal:From:To:CC:Subject:Date:Message-ID:X-Mailer:
         In-Reply-To:References:X-NVConfidentiality:MIME-Version:
         Content-Type;
        b=Og8UVEgG5Prk8SjfXHsjhIbm204q1RLVn9226/aKjJRRwFDp0xlo8RGvnuFEZ2vzX
         dZF/enCIf/qqNpv2IgQnMNQ8KH8BlhZl9adzUHh9AGN4X9l6i0S4w4XiD5SZZ9dx2Q
         5rwfnNW89Agcep6ZotZSnKaVplbemgIlDdJKZtHj/P5BVSPV8zWIdBTf/jDvNmtUV0
         fGSEvez1CgEbvmvhZmfUMr+UyUph2KWQKU23yvCvgInd4AwADCvyk6mO5AThF7Oqr+
         JEthkR6aukZr5d9LLcCo4Fn/2lZKytYHS4HvNp8dpbYlQu4mpRyt3qE/44Yalimh6Q
         /8LbAgMt3QPow==
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

- Defined MIGRATION region type and sub-type.

- Defined vfio_device_migration_info structure which will be placed at the
  0th offset of migration region to get/set VFIO device related
  information. Defined members of structure and usage on read/write access.

- Defined device states and state transition details.

- Defined sequence to be followed while saving and resuming VFIO device.

Signed-off-by: Kirti Wankhede <kwankhede@nvidia.com>
Reviewed-by: Neo Jia <cjia@nvidia.com>
---
 include/uapi/linux/vfio.h | 228 ++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 228 insertions(+)

```
#### [PATCH 1/3 v3] KVM: x86: Create mask for guest CR4 reserved bits in kvm_update_cpuid()
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11550707
Return-Path: <SRS0=+vSx=65=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3120959D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 08:17:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 133D5206B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 08:17:26 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="qZEe2MZ1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726725AbgEOIRZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 May 2020 04:17:25 -0400
Received: from aserp2120.oracle.com ([141.146.126.78]:46342 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726648AbgEOIRY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 May 2020 04:17:24 -0400
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04F6HPZH067429;
        Fri, 15 May 2020 06:18:46 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=corp-2020-01-29;
 bh=vIWcjKr3Hp+eKqElLLlfr4wJStdIyecKEB+daQEXgr0=;
 b=qZEe2MZ1rC8tBhTDoBGz72pPU82Z39TqQa14dTY89rZ5ksqOLwvaHGrx++xoENmZETNe
 SgbWblxPYCbl6x2Fpdo7RNYS1XGhuOfa+/bo5Qu8Bf9cj10+H5hCeXTHUWveuvzdVwkw
 rTFDIjPfYsV43wb6XCGr7zggKavYk+suQ3cPQl+pKoXYt1sRyFuHqw6qk2wQklW08K3+
 iS9Ggj7JM5kv0er51tticmhuKfdfbWuUqMaPzA6Mb9eW09/CSzEVYfPG6tBNV7NV2g9b
 9vaM3WmXFoJZYIM9E941u2IiIa6HjatLmtJcjrE05GhfzOHGVXAmRkL57nRIch4uGFR7 7Q==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 3100xwqsnn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Fri, 15 May 2020 06:18:46 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 04F68Cns139397;
        Fri, 15 May 2020 06:16:46 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 3100ye571y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 15 May 2020 06:16:45 +0000
Received: from abhmp0003.oracle.com (abhmp0003.oracle.com [141.146.116.9])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 04F6Gilu026688;
        Fri, 15 May 2020 06:16:44 GMT
Received: from ban25x6uut29.us.oracle.com (/10.153.73.29)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Thu, 14 May 2020 23:16:44 -0700
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com
Subject: [PATCH 1/3 v3] KVM: x86: Create mask for guest CR4 reserved bits in
 kvm_update_cpuid()
Date: Fri, 15 May 2020 01:36:07 -0400
Message-Id: <20200515053609.3347-2-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20200515053609.3347-1-krish.sadhukhan@oracle.com>
References: <20200515053609.3347-1-krish.sadhukhan@oracle.com>
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9621
 signatures=668687
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 malwarescore=0 phishscore=0
 adultscore=0 suspectscore=1 mlxscore=0 mlxlogscore=999 spamscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2004280000
 definitions=main-2005150052
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9621
 signatures=668687
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 lowpriorityscore=0
 suspectscore=1 mlxlogscore=999 clxscore=1015 cotscore=-2147483648
 mlxscore=0 phishscore=0 adultscore=0 impostorscore=0 bulkscore=0
 malwarescore=0 priorityscore=1501 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2005150053
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
 arch/x86/include/asm/kvm_host.h |  2 ++
 arch/x86/kvm/cpuid.c            |  2 ++
 arch/x86/kvm/x86.c              | 24 ++----------------------
 arch/x86/kvm/x86.h              | 21 +++++++++++++++++++++
 4 files changed, 27 insertions(+), 22 deletions(-)

```
#### [PATCH 1/7] KVM: SVM: move map argument out of enter_svm_guest_mode
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11552839
Return-Path: <SRS0=+vSx=65=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6517814C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 17:42:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 50BBF2076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 17:42:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="ShnRSmvL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726313AbgEORlx (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 May 2020 13:41:53 -0400
Received: from us-smtp-1.mimecast.com ([205.139.110.61]:38166 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726179AbgEORlw (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 May 2020 13:41:52 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589564511;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:in-reply-to:in-reply-to:references:references;
        bh=obvdaqrDmOo0TZ7H8EUPrGh8lXy9dD8Hldwr4knbgD0=;
        b=ShnRSmvLeXh64VW5XDoTeIZrrEQvJBzCj6wLSV9bHNcPjRcExZU1L4rjJsxIwG9DaoRf6r
        vQPTmHhjLMt9+p/De0qPpJc5siJXaP/s0/FwWJMjEyNN4MJ1xDCCgI09v7DcnZubedvYiv
        Hu05w7YH2tTrT3Dsyb4a9b5qZLR5sSw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-142-FwbIl2CVOiiBBWetwE2nzw-1; Fri, 15 May 2020 13:41:48 -0400
X-MC-Unique: FwbIl2CVOiiBBWetwE2nzw-1
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 43DEA83DE2B;
        Fri, 15 May 2020 17:41:47 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 979C210002CD;
        Fri, 15 May 2020 17:41:46 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: Cathy Avery <cavery@redhat.com>,
        Liran Alon <liran.alon@oracle.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH 1/7] KVM: SVM: move map argument out of enter_svm_guest_mode
Date: Fri, 15 May 2020 13:41:38 -0400
Message-Id: <20200515174144.1727-2-pbonzini@redhat.com>
In-Reply-To: <20200515174144.1727-1-pbonzini@redhat.com>
References: <20200515174144.1727-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Unmapping the nested VMCB in enter_svm_guest_mode is a bit of a wart,
since the map is not used elsewhere in the function.  There are
just two calls, so move it there.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/svm/nested.c | 14 ++++++--------
 arch/x86/kvm/svm/svm.c    |  3 ++-
 arch/x86/kvm/svm/svm.h    |  2 +-
 3 files changed, 9 insertions(+), 10 deletions(-)

```
#### [PATCH] KVM: x86: emulate reserved nops from 0f/18 to 0f/1f
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11552495
Return-Path: <SRS0=+vSx=65=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 171F9912
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 16:19:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 007C220787
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 16:19:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="HmK6qg17"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726283AbgEOQTY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 May 2020 12:19:24 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:27396 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726162AbgEOQTY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 15 May 2020 12:19:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589559563;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc; bh=jyrqhLt/j8WM6W25F/4nHaguhXzjEnraWUNGaaQDntQ=;
        b=HmK6qg17Ccbj1VqTmlNjtnQIF62j/aZJt7g2A7B96DNMXHykGZx6GOZf8igysrGDFQCpf6
        Gzk6bbGqh6yLOJ4SAjSzZVq5jFJr+W6SvoJ+wYEQc7Vlh++cIx9TXbNrKNqOvdHr1dkGPE
        BtE6CSWily9GSYA/kLFOiOyJy6zydkI=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-112-bqPGaupuNxmS7POCrWErMQ-1; Fri, 15 May 2020 12:19:21 -0400
X-MC-Unique: bqPGaupuNxmS7POCrWErMQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 2079818FF661;
        Fri, 15 May 2020 16:19:20 +0000 (UTC)
Received: from virtlab701.virt.lab.eng.bos.redhat.com
 (virtlab701.virt.lab.eng.bos.redhat.com [10.19.152.228])
        by smtp.corp.redhat.com (Postfix) with ESMTP id CF12A79B6;
        Fri, 15 May 2020 16:19:19 +0000 (UTC)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Subject: [PATCH] KVM: x86: emulate reserved nops from 0f/18 to 0f/1f
Date: Fri, 15 May 2020 12:19:19 -0400
Message-Id: <20200515161919.29249-1-pbonzini@redhat.com>
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Instructions starting with 0f18 up to 0f1f are reserved nops, except those
that were assigned to MPX.  These include the endbr markers used by CET.
List them correctly in the opcode table.

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 arch/x86/kvm/emulate.c | 8 ++++++--
 1 file changed, 6 insertions(+), 2 deletions(-)

```
#### [PATCH v7 1/3] s390/setup: diag 318: refactor struct
##### From: Collin Walling <walling@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Collin Walling <walling@linux.ibm.com>
X-Patchwork-Id: 11553147
Return-Path: <SRS0=+vSx=65=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 68953913
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 22:20:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5828C2076A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 22:20:05 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726703AbgEOWUE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 May 2020 18:20:04 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:13198 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726212AbgEOWUE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 May 2020 18:20:04 -0400
Received: from pps.filterd (m0098416.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 04FM2xmR177812;
        Fri, 15 May 2020 18:20:03 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 310x57pncu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 May 2020 18:20:02 -0400
Received: from m0098416.ppops.net (m0098416.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 04FMK20T030775;
        Fri, 15 May 2020 18:20:02 -0400
Received: from ppma03wdc.us.ibm.com (ba.79.3fa9.ip4.static.sl-reverse.com
 [169.63.121.186])
        by mx0b-001b2d01.pphosted.com with ESMTP id 310x57pnce-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 May 2020 18:20:02 -0400
Received: from pps.filterd (ppma03wdc.us.ibm.com [127.0.0.1])
        by ppma03wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 04FMImZD009966;
        Fri, 15 May 2020 22:20:01 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma03wdc.us.ibm.com with ESMTP id 3100ubtfv5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 15 May 2020 22:20:01 +0000
Received: from b03ledav006.gho.boulder.ibm.com
 (b03ledav006.gho.boulder.ibm.com [9.17.130.237])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 04FMJuiW5964500
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 15 May 2020 22:19:57 GMT
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CE918C6055;
        Fri, 15 May 2020 22:19:57 +0000 (GMT)
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 26054C6057;
        Fri, 15 May 2020 22:19:57 +0000 (GMT)
Received: from localhost.localdomain.com (unknown [9.85.146.125])
        by b03ledav006.gho.boulder.ibm.com (Postfix) with ESMTP;
        Fri, 15 May 2020 22:19:56 +0000 (GMT)
From: Collin Walling <walling@linux.ibm.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org
Cc: pbonzini@redhat.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        david@redhat.com, cohuck@redhat.com, imbrenda@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v7 1/3] s390/setup: diag 318: refactor struct
Date: Fri, 15 May 2020 18:19:33 -0400
Message-Id: <20200515221935.18775-2-walling@linux.ibm.com>
X-Mailer: git-send-email 2.21.3
In-Reply-To: <20200515221935.18775-1-walling@linux.ibm.com>
References: <20200515221935.18775-1-walling@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.216,18.0.676
 definitions=2020-05-15_07:2020-05-15,2020-05-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 spamscore=0
 mlxscore=0 bulkscore=0 priorityscore=1501 mlxlogscore=999 impostorscore=0
 adultscore=0 clxscore=1015 cotscore=-2147483648 lowpriorityscore=0
 suspectscore=0 phishscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2004280000 definitions=main-2005150181
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The diag 318 struct introduced in include/asm/diag.h can be
reused in KVM, so let's condense the version code fields in the
diag318_info struct for easier usage and simplify it until we
can determine how the data should be formatted.

Signed-off-by: Collin Walling <walling@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/include/asm/diag.h | 6 ++----
 arch/s390/kernel/setup.c     | 3 +--
 2 files changed, 3 insertions(+), 6 deletions(-)

```
#### [PATCH] vhost: missing __user tags
##### From: "Michael S. Tsirkin" <mst@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "Michael S. Tsirkin" <mst@redhat.com>
X-Patchwork-Id: 11552467
Return-Path: <SRS0=+vSx=65=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 746F2739
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 15:34:01 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 5D9AA20671
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 15 May 2020 15:34:01 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="b9EMjRgT"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727076AbgEOPeA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 15 May 2020 11:34:00 -0400
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:21189 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726239AbgEOPd7 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 15 May 2020 11:33:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1589556838;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type;
        bh=0q1Y8ePvKhM4R3+rVYPWm7Pu+FP0VGkrqM/os2Y0oAI=;
        b=b9EMjRgTzPUFgG1eoXpAe/aO+zKGyB3oPvR18cCaFgx9QNB4lCBCQf57zudQIn0tddzsXp
        dbO5892QRkwEqe2XIuc2wYbWlaApmNRyzyhFvHRY/LrVoiQetUB4tQXlVZHls86fKNkfl7
        6uF4hofZfqeYDS1euZ9jMymztp0kaOA=
Received: from mail-wm1-f69.google.com (mail-wm1-f69.google.com
 [209.85.128.69]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-326-6dK4yNHzNU2i7PFZi5h6Ew-1; Fri, 15 May 2020 11:33:56 -0400
X-MC-Unique: 6dK4yNHzNU2i7PFZi5h6Ew-1
Received: by mail-wm1-f69.google.com with SMTP id v23so1164276wmj.0
        for <kvm@vger.kernel.org>; Fri, 15 May 2020 08:33:56 -0700 (PDT)
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:date:from:to:cc:subject:message-id:mime-version
         :content-disposition;
        bh=0q1Y8ePvKhM4R3+rVYPWm7Pu+FP0VGkrqM/os2Y0oAI=;
        b=bq/MfASSzMKj3oFf67+WBc5vnHJJVvuSkfDHhJYvD5/MJcDWtLk/X6aJ21zDQGZhex
         zUxaqh96EHKYZJE29aqQUybXOCCkO0Bq0E8V6BB/WZHQdReb8Oy6Ua/nGBgu5yv1kVwr
         LycJWs/5jWeCRri5MP5xDAMrty2KuvmruU/ksiDT1Nq7P7QtYvupR1QYyM+kHALmCKLe
         SMGJd7ODVnvp9P1rrG7UKmrlaoSaL4u5sYDTSZdxlZ4idEfEOc/gvddM/sTWosS8sc3P
         5XzznBPRjLUOvEVLjXaXRZ6xWKnhzAZtHl+bw+7X44vUDmeaa9H7RmxXPtk1CI0saIIC
         y2xA==
X-Gm-Message-State: AOAM530uNVA/7wQhXyMH0LiMVWhEOj76j+VEUBNTRXhywd1/kjRG9MfE
        fBLxL4ITSxRrzLiNkFN4px8duHSisiBFSKFmNWqsf9lj0nrC3LdzkzWkg6ut2RG8LvXk4ItjXb+
        W1iJhcVaJuS3T
X-Received: by 2002:a1c:2087:: with SMTP id
 g129mr4503995wmg.126.1589556832765;
        Fri, 15 May 2020 08:33:52 -0700 (PDT)
X-Google-Smtp-Source: 
 ABdhPJwz/KlciQFx1rHU1J+UL9igbunQtTe0UZESWhBj7gKnvBR65GITM/RzOMxXTQwccrKqsnawtA==
X-Received: by 2002:a1c:2087:: with SMTP id
 g129mr4503978wmg.126.1589556832581;
        Fri, 15 May 2020 08:33:52 -0700 (PDT)
Received: from redhat.com (bzq-79-179-68-225.red.bezeqint.net.
 [79.179.68.225])
        by smtp.gmail.com with ESMTPSA id
 c16sm4048373wrv.62.2020.05.15.08.33.51
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Fri, 15 May 2020 08:33:51 -0700 (PDT)
Date: Fri, 15 May 2020 11:33:50 -0400
From: "Michael S. Tsirkin" <mst@redhat.com>
To: linux-kernel@vger.kernel.org
Cc: kbuild test robot <lkp@intel.com>,
        Jason Wang <jasowang@redhat.com>, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org
Subject: [PATCH] vhost: missing __user tags
Message-ID: <20200515153347.1092235-1-mst@redhat.com>
MIME-Version: 1.0
Content-Disposition: inline
X-Mailer: git-send-email 2.24.1.751.gd10ce2899c
X-Mutt-Fcc: =sent
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

sparse warns about converting void * to void __user *. This is not new
but only got noticed now that vhost is built on more systems.
This is just a question of __user tags missing in a couple of places,
so fix it up.

Fixes: f88949138058 ("vhost: introduce O(1) vq metadata cache")
Reported-by: kbuild test robot <lkp@intel.com>
Signed-off-by: Michael S. Tsirkin <mst@redhat.com>
---
 drivers/vhost/vhost.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
