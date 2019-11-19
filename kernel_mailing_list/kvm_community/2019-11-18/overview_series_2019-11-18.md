#### [PATCH 14/15] sample/vfio-mdev/mbocs: Remove dma_buf_k(un)map support
##### From: Daniel Vetter <daniel.vetter@ffwll.ch>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Daniel Vetter <daniel.vetter@ffwll.ch>
X-Patchwork-Id: 11249333
Return-Path: <SRS0=wTpQ=ZK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 01BE218B8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 10:36:03 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D206420730
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 10:36:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=ffwll.ch header.i=@ffwll.ch
 header.b="EDk8Fod4"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726600AbfKRKgC (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 Nov 2019 05:36:02 -0500
Received: from mail-wr1-f68.google.com ([209.85.221.68]:47030 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726490AbfKRKgB (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 Nov 2019 05:36:01 -0500
Received: by mail-wr1-f68.google.com with SMTP id b3so18783667wrs.13
        for <kvm@vger.kernel.org>; Mon, 18 Nov 2019 02:36:00 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=ffwll.ch; s=google;
        h=from:to:cc:subject:date:message-id:in-reply-to:references
         :mime-version:content-transfer-encoding;
        bh=O6snPj4zRF7PnmdnvOs9XQoZqp3Knhprhwo6jIsI7pk=;
        b=EDk8Fod4KYVy3Ku3JKZWOBfrr3rK7aA/YCCASUklWuJkEwjDeojA2EuQOaogcy1Ce4
         91VzGpCS11mVTlMh97BzYznrWt0ZB0pWImcJc1CMhWmZWbJJK7kBQS/ukmqK7LhSRM+k
         FuxXis9+tN4+RJ/2LWZVcQL+JLlu725EEPJ/k=
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:in-reply-to
         :references:mime-version:content-transfer-encoding;
        bh=O6snPj4zRF7PnmdnvOs9XQoZqp3Knhprhwo6jIsI7pk=;
        b=mDswTYucywRuOlZ7PiexvQp8FZzF1oRpeIh7EMmhpRG7HxnI10foX487uRTrFD+rxy
         GpTCqmk1OxLOx5mBYrRaZZbb4d9W3TSWvtcO/SO5D2yfTTLvLkF0mnm+Z1Id07GaXhx6
         KFj1/571QVWKEdc9Gg8RImn39uwOeC61zCfdla1BOUHyWKsA1R3qYeRZ213D5pYyoPHy
         zFLJ6OLN3cxVwBBh3gfNUmxjAEraoch1ao8+BOTlV7y4aFfO6+ytgxNL35GZmouoLw7l
         kdnXIog6Aut6rex5giR751scvTB/nk4AxP69d2CaqQ8HnWDTc+yiEOD24+zb9zxkJD04
         Jd9Q==
X-Gm-Message-State: APjAAAU7ZvaBy1lHLCEeXP9EuDDx8LJlHu95pVd6GBBD29e19shuZkgQ
        N5O35Cr6LGkRFUImIil3lHBYtg==
X-Google-Smtp-Source: 
 APXvYqxwliWhIEUAO9jqkKlsD9SR6F/Gar8dxbJUUc2j0kGt2YK8h8lt3xuihOzMEA3CN5LZFOMWFw==
X-Received: by 2002:adf:ec42:: with SMTP id w2mr15988758wrn.32.1574073359659;
        Mon, 18 Nov 2019 02:35:59 -0800 (PST)
Received: from phenom.ffwll.local (212-51-149-96.fiber7.init7.net.
 [212.51.149.96])
        by smtp.gmail.com with ESMTPSA id
 j2sm22749200wrt.61.2019.11.18.02.35.58
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 18 Nov 2019 02:35:58 -0800 (PST)
From: Daniel Vetter <daniel.vetter@ffwll.ch>
To: DRI Development <dri-devel@lists.freedesktop.org>
Cc: Intel Graphics Development <intel-gfx@lists.freedesktop.org>,
        Daniel Vetter <daniel.vetter@ffwll.ch>,
        Daniel Vetter <daniel.vetter@intel.com>,
        Kirti Wankhede <kwankhede@nvidia.com>, kvm@vger.kernel.org
Subject: [PATCH 14/15] sample/vfio-mdev/mbocs: Remove dma_buf_k(un)map support
Date: Mon, 18 Nov 2019 11:35:35 +0100
Message-Id: <20191118103536.17675-15-daniel.vetter@ffwll.ch>
X-Mailer: git-send-email 2.24.0
In-Reply-To: <20191118103536.17675-1-daniel.vetter@ffwll.ch>
References: <20191118103536.17675-1-daniel.vetter@ffwll.ch>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

No in-tree users left.

Signed-off-by: Daniel Vetter <daniel.vetter@intel.com>
Cc: Kirti Wankhede <kwankhede@nvidia.com>
Cc: kvm@vger.kernel.org
Acked-by: Gerd Hoffmann <kraxel@redhat.com>
---
Ack for merging this through drm trees very much appreciated.
-Daniel
---
 samples/vfio-mdev/mbochs.c | 16 ----------------
 1 file changed, 16 deletions(-)

```
#### [GIT PULL 1/5] KVM: s390: Remove unused parameter from __inject_sigp_restart()
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11249079
Return-Path: <SRS0=wTpQ=ZK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 859741393
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 08:36:11 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 6BCA0206A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 08:36:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726635AbfKRIgL (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 Nov 2019 03:36:11 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:60146 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726464AbfKRIgK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 18 Nov 2019 03:36:10 -0500
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 xAI8WDmY124939
        for <kvm@vger.kernel.org>; Mon, 18 Nov 2019 03:36:09 -0500
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2waeh82d16-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 18 Nov 2019 03:36:09 -0500
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <borntraeger@de.ibm.com>;
        Mon, 18 Nov 2019 08:36:07 -0000
Received: from b06cxnps4074.portsmouth.uk.ibm.com (9.149.109.196)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 18 Nov 2019 08:36:04 -0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id xAI8a3dV50462852
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 18 Nov 2019 08:36:03 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 9F47942049;
        Mon, 18 Nov 2019 08:36:03 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 8AA214204B;
        Mon, 18 Nov 2019 08:36:03 +0000 (GMT)
Received: from tuxmaker.boeblingen.de.ibm.com (unknown [9.152.85.9])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTPS;
        Mon, 18 Nov 2019 08:36:03 +0000 (GMT)
Received: by tuxmaker.boeblingen.de.ibm.com (Postfix, from userid 25651)
        id 3FDCEE02D4; Mon, 18 Nov 2019 09:36:03 +0100 (CET)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Cc: KVM <kvm@vger.kernel.org>, Cornelia Huck <cohuck@redhat.com>,
        Christian Borntraeger <borntraeger@de.ibm.com>,
        linux-s390 <linux-s390@vger.kernel.org>,
        Janosch Frank <frankja@linux.vnet.ibm.com>,
        David Hildenbrand <david@redhat.com>
Subject: [GIT PULL 1/5] KVM: s390: Remove unused parameter from
 __inject_sigp_restart()
Date: Mon, 18 Nov 2019 09:35:58 +0100
X-Mailer: git-send-email 2.21.0
In-Reply-To: <20191118083602.15835-1-borntraeger@de.ibm.com>
References: <20191118083602.15835-1-borntraeger@de.ibm.com>
X-TM-AS-GCONF: 00
x-cbid: 19111808-4275-0000-0000-00000380A771
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19111808-4276-0000-0000-000038941601
Message-Id: <20191118083602.15835-2-borntraeger@de.ibm.com>
X-Proofpoint-UnRewURL: 0 URL was un-rewritten
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.95,18.0.572
 definitions=2019-11-18_01:2019-11-15,2019-11-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 clxscore=1015
 phishscore=0 impostorscore=0 bulkscore=0 suspectscore=0 adultscore=0
 lowpriorityscore=0 priorityscore=1501 malwarescore=0 mlxlogscore=999
 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-1910280000 definitions=main-1911180077
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Thomas Huth <thuth@redhat.com>

It's not required, so drop it to make it clear that this interrupt
does not have any extra parameters.

Signed-off-by: Thomas Huth <thuth@redhat.com>
Link: https://lore.kernel.org/kvm/20190912070250.15131-1-thuth@redhat.com
Reviewed-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: David Hildenbrand <david@redhat.com>
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/interrupt.c | 5 ++---
 1 file changed, 2 insertions(+), 3 deletions(-)

```
#### [PATCH] KVM: nVMX: Use semi-colon instead of comma for exit-handlers initialization
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11250173
Return-Path: <SRS0=wTpQ=ZK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 09428930
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 19:11:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id DDE9E22300
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 19:11:44 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="IN9Rq1Cz"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726536AbfKRTLo (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 Nov 2019 14:11:44 -0500
Received: from userp2130.oracle.com ([156.151.31.86]:48718 "EHLO
        userp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726427AbfKRTLn (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 Nov 2019 14:11:43 -0500
Received: from pps.filterd (userp2130.oracle.com [127.0.0.1])
        by userp2130.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAIJ4QBo069769;
        Mon, 18 Nov 2019 19:11:37 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=jqntQIYG1FyyXBP32zeHpN8TlRj0EAJHe6PAVy5wr/8=;
 b=IN9Rq1CzqwihzGmKHXqcvKmlLsHVUGfVlHjBKJa11eMsvB9j3RuBU2gyjb2avDnmRniF
 QKDpie2150Eu8h4yo/nmNuNb9HVezqzXqA5cVJ+Ripyf7DWq6j2YhtVl2hFu4tSQzoiR
 QBJ48D42me74nwRKz5aCAbzQ3+aKR8hQcbRO5S/KVqGkPkXtQxAauoYD21LU+VgKHmuF
 QQIWsXr9J5KKQIRLKZGUKFffGAeMiH5Y9eUQ/bnj6sbSrAmQm/Sw//dRnCppbjLcWLma
 kskObHkwztzM0+VibZ8s2O5iPoVhwZFYmU025Z+p0rVhgfix6+ayS1R4Iv2wlKKZwg8D jw==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by userp2130.oracle.com with ESMTP id 2wa8htjbxn-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 18 Nov 2019 19:11:37 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAIJ940Z062644;
        Mon, 18 Nov 2019 19:11:37 GMT
Received: from aserv0122.oracle.com (aserv0122.oracle.com [141.146.126.236])
        by userp3030.oracle.com with ESMTP id 2wc0af2rmb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 18 Nov 2019 19:11:37 +0000
Received: from abhmp0005.oracle.com (abhmp0005.oracle.com [141.146.116.11])
        by aserv0122.oracle.com (8.14.4/8.14.4) with ESMTP id xAIJBZIC028813;
        Mon, 18 Nov 2019 19:11:35 GMT
Received: from Lirans-MBP.Home (/79.181.226.113)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 18 Nov 2019 11:11:35 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Mark Kanda <mark.kanda@oracle.com>
Subject: [PATCH] KVM: nVMX: Use semi-colon instead of comma for exit-handlers
 initialization
Date: Mon, 18 Nov 2019 21:11:21 +0200
Message-Id: <20191118191121.43440-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9445
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=724
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1911140001 definitions=main-1911180162
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9445
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=784 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1911140001
 definitions=main-1911180162
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/vmx/nested.c | 26 +++++++++++++-------------
 1 file changed, 13 insertions(+), 13 deletions(-)

```
#### [kvm-unit-tests PATCH] arm: Add missing test name prefix for pl031 and spinlock
##### From: <kuhn.chenqun@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: kuhn.chenqun@huawei.com
X-Patchwork-Id: 11248789
Return-Path: <SRS0=wTpQ=ZK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BBFB91599
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 02:27:33 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9D8F8206D9
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 02:27:33 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726442AbfKRC1c (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 17 Nov 2019 21:27:32 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:41164 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726325AbfKRC1c (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 17 Nov 2019 21:27:32 -0500
Received: from DGGEMS413-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id D71B4E117DC0D4651E24;
        Mon, 18 Nov 2019 10:27:30 +0800 (CST)
Received: from HGHY4C002233111.china.huawei.com (10.133.205.93) by
 DGGEMS413-HUB.china.huawei.com (10.3.19.213) with Microsoft SMTP Server id
 14.3.439.0; Mon, 18 Nov 2019 10:27:23 +0800
From: <kuhn.chenqun@huawei.com>
To: <kvm@vger.kernel.org>, <kvmarm@lists.cs.columbia.edu>,
        <drjones@redhat.com>
CC: <kenny.zhangjun@huawei.com>, <kuhn.chenqun@huawei.com>,
        <pannengyuan@huawei.com>, <zhang.zhanghailiang@huawei.com>
Subject: [kvm-unit-tests PATCH] arm: Add missing test name prefix for pl031
 and spinlock
Date: Mon, 18 Nov 2019 10:27:20 +0800
Message-ID: <20191118022720.17488-1-kuhn.chenqun@huawei.com>
X-Mailer: git-send-email 2.14.1.windows.1
MIME-Version: 1.0
X-Originating-IP: [10.133.205.93]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Chen Qun <kuhn.chenqun@huawei.com>

pl031 and spinlock testcase without prefix, when running
the unit tests in TAP mode (./run_tests.sh -t), it is
difficult to the test results.

The test results：
ok 13 - Periph/PCell IDs match
ok 14 - R/O fields are R/O
ok 15 - RTC ticks at 1HZ
ok 16 - RTC IRQ not pending yet
...
ok 24 -   RTC IRQ not pending anymore
ok 25 - CPU1: Done - Errors: 0
ok 26 - CPU0: Done - Errors: 0

It should be like this：
ok 13 - pl031: Periph/PCell IDs match
ok 14 - pl031: R/O fields are R/O
ok 15 - pl031: RTC ticks at 1HZ
ok 16 - pl031: RTC IRQ not pending yet
...
ok 24 - pl031:   RTC IRQ not pending anymore
ok 25 - spinlock: CPU0: Done - Errors: 0
ok 26 - spinlock: CPU1: Done - Errors: 0

Signed-off-by: Chen Qun <kuhn.chenqun@huawei.com>
---
 arm/pl031.c         | 1 +
 arm/spinlock-test.c | 1 +
 2 files changed, 2 insertions(+)

```
#### [kvm-unit-tests PULL 01/12] s390x: Use loop to save and restore fprs
##### From: David Hildenbrand <david@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: David Hildenbrand <david@redhat.com>
X-Patchwork-Id: 11249249
Return-Path: <SRS0=wTpQ=ZK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 48E7B14C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 10:07:52 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2786F20748
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 10:07:52 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="C8s91vIo"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726578AbfKRKHv (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 Nov 2019 05:07:51 -0500
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:29534 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1726490AbfKRKHv (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 Nov 2019 05:07:51 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574071670;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=ycY2H6t9OzJIOigDNMwvvZn5InpDjzanbHdcM8sdl9k=;
        b=C8s91vIo0nFh2UHdFzBQ1lHsDUFjMVs4Wodc2kxpX3DUDc9/S9MqB4jJkBg3d+YBSbCS2/
        qolztN2fev/FDQS3WNHT0kNPaZ5JQO1KAv9IZGEUunRQJNgqoT/awY+R5dGo9x7W9NVCKt
        apo4uVo/jzq9wH3uYYdP+JFJZJumBAk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-228-FYiHeIxqMvSai-K4wDRg5g-1; Mon, 18 Nov 2019 05:07:46 -0500
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 5E2FD107ACE4;
        Mon, 18 Nov 2019 10:07:45 +0000 (UTC)
Received: from t460s.redhat.com (unknown [10.36.118.85])
        by smtp.corp.redhat.com (Postfix) with ESMTP id AF65C75E30;
        Mon, 18 Nov 2019 10:07:32 +0000 (UTC)
From: David Hildenbrand <david@redhat.com>
To: kvm@vger.kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
 =?utf-8?b?UmFkaW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>,
 Thomas Huth <thuth@redhat.com>,
 Christian Borntraeger <borntraeger@de.ibm.com>,
 Cornelia Huck <cohuck@redhat.com>, Janosch Frank <frankja@linux.ibm.com>,
 David Hildenbrand <david@redhat.com>
Subject: [kvm-unit-tests PULL 01/12] s390x: Use loop to save and restore fprs
Date: Mon, 18 Nov 2019 11:07:08 +0100
Message-Id: <20191118100719.7968-2-david@redhat.com>
In-Reply-To: <20191118100719.7968-1-david@redhat.com>
References: <20191118100719.7968-1-david@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
X-MC-Unique: FYiHeIxqMvSai-K4wDRg5g-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Janosch Frank <frankja@linux.ibm.com>

Let's save some lines in the assembly by using a loop to save and
restore the fprs.

Tested-by: Thomas Huth <thuth@redhat.com>
Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Message-Id: <20191104085533.2892-1-frankja@linux.ibm.com>
Signed-off-by: David Hildenbrand <david@redhat.com>
---
 s390x/cstart64.S | 38 ++++++--------------------------------
 1 file changed, 6 insertions(+), 32 deletions(-)

```
#### [PATCH kvm-unit-tests] x86: add tests for MSR_IA32_TSX_CTRL
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11250061
Return-Path: <SRS0=wTpQ=ZK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0A29C1390
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 17:29:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D2D5C2192B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 17:29:04 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="iNWZXzyI"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726704AbfKRR3D (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 Nov 2019 12:29:03 -0500
Received: from mail-wr1-f68.google.com ([209.85.221.68]:46230 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726317AbfKRR3D (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 Nov 2019 12:29:03 -0500
Received: by mail-wr1-f68.google.com with SMTP id b3so20498286wrs.13
        for <kvm@vger.kernel.org>; Mon, 18 Nov 2019 09:29:00 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:subject:date:message-id;
        bh=YND6Zs40Ln4MrQ8TnFNfSflQxBifvkVl4mTVEIrw30s=;
        b=iNWZXzyIqChjfu1CKskiQERSMg1DM8i/ElBUDIbUch/frdAEaU+w9bsFPvo+cKqust
         SCSByoxOFKEQ+GJFRL2ckuqDXOu/2idaq5+tcmQunsQe8NjfuXT0yyu98wuwzdHqA5DU
         vl3gInqz0Y0Os7Ekq5zplKmOy0oYEDwlXdZ05qKLruVE/RX0+selsw4H7ZTdixPQIaqJ
         RHnCuDsxNmSiSmh8OljdCXuFoTvrWBcLiIeWrJiET9pCkEi2kh+HWveNE2SKby2F9VmI
         /DRrDJHuW6m78JklShiwjFW9p7h/7BJ2tvu0dFoy5knOl1JZGPFKq2BJRfXCqCnKQGy9
         t5RQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:subject:date:message-id;
        bh=YND6Zs40Ln4MrQ8TnFNfSflQxBifvkVl4mTVEIrw30s=;
        b=luGaqjs3mi8LkoU+NrUaJoAtfI9jj76+evRHXBHYMTRtCQwUeHIMxoVkY+DBBU1LlW
         9epNOU3zYWssOxQkq4UbHDfcYvPce4iWxIymeGcfVMSkiw0kMmgzCv5LsBzxWx+ZIw7+
         4urs69dCi+XbxhYeg6Q/zzw5eG2u6MdIzSAyFaO4a2vCfVugvLonUOtEPsVCEiRj0jDu
         lsW71SZ3pfuPICc/g31HkLmm/jRgQ/5CPipMj4OnMhApwMW/J9smctonc9dUHt/FQdH+
         WXA4gucqjRpz8nIqNFhXGcUNhX3wrfjlX5x5lCPyvaggwHtO+L71qskp/P5fNhnirRi2
         9qAA==
X-Gm-Message-State: APjAAAWVrmFU8CrEvcuYj0x1+Kyff5kV243hbJBqHXhDwmQ1QYhoN4vD
        P0pcloJ2IvuWyTbcaahh2oBY6a/L
X-Google-Smtp-Source: 
 APXvYqxjTTXs5htt1a65KzbwzRu0fdwhMYscANOlfzQ8yMquP/GqV5fV2VapRuW8JrHMKNL3KJA5lA==
X-Received: by 2002:adf:edc5:: with SMTP id v5mr16374652wro.322.1574098139378;
        Mon, 18 Nov 2019 09:28:59 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id b3sm21837wmj.44.2019.11.18.09.28.58
        for <kvm@vger.kernel.org>
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 18 Nov 2019 09:28:58 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: kvm@vger.kernel.org
Subject: [PATCH kvm-unit-tests] x86: add tests for MSR_IA32_TSX_CTRL
Date: Mon, 18 Nov 2019 18:28:56 +0100
Message-Id: <1574098136-48779-1-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
---
 lib/x86/msr.h       | 14 +++++++++++++
 lib/x86/processor.h |  2 ++
 x86/Makefile.common |  2 +-
 x86/tsx-ctrl.c      | 60 +++++++++++++++++++++++++++++++++++++++++++++++++++++
 x86/vmexit.c        | 12 +++++++++++
 5 files changed, 89 insertions(+), 1 deletion(-)
 create mode 100644 x86/tsx-ctrl.c

```
#### [PATCH 1/5] KVM: x86: fix presentation of TSX feature in ARCH_CAPABILITIES
##### From: Paolo Bonzini <pbonzini@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Paolo Bonzini <pbonzini@redhat.com>
X-Patchwork-Id: 11250105
Return-Path: <SRS0=wTpQ=ZK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 9A5091599
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 18:18:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 7929C222B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 18:18:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=fail reason="signature verification failed" (2048-bit key)
 header.d=gmail.com header.i=@gmail.com header.b="F9NFiZtC"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726760AbfKRSR6 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 Nov 2019 13:17:58 -0500
Received: from mail-wr1-f68.google.com ([209.85.221.68]:42038 "EHLO
        mail-wr1-f68.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726541AbfKRSRy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 Nov 2019 13:17:54 -0500
Received: by mail-wr1-f68.google.com with SMTP id a15so20684366wrf.9;
        Mon, 18 Nov 2019 10:17:53 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=sender:from:to:cc:subject:date:message-id:in-reply-to:references;
        bh=xuKE2SmFgctrg1WssQn4ZdOCP9av/DCBktsiIBAJY9w=;
        b=F9NFiZtCXptg/YQCw2GdCexki51nGWmL9R85iUJUQlm25ZJZ0EF27N1UBN8Tpg1mUr
         aJ9eH6X3u4U7SmVKsgajMNGmLGI9m2Gu1vgjObhH1splv5g3BLgVYpAmnk59RxQUb2Vd
         e7wG+rYJs1VEC7XIRMt7ZIlZ1S/x8qI5uBmgvjFTiMoEL7srgfquLW+t3ou+wJGN/Us2
         zKL/A/IgIbNgVRRrJjyWifAP7eSLJ2A9K0nW/g8Gq+29IyHa0FXLGgSqWHVwnWUWps+A
         nK8DlqgcvFFJcx8i/cK+zTEZoMk5NYdtXN1X1YKkUmiUFmxnOJ1UXPvsjUrkLPFDeDnn
         c5Kg==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:sender:from:to:cc:subject:date:message-id
         :in-reply-to:references;
        bh=xuKE2SmFgctrg1WssQn4ZdOCP9av/DCBktsiIBAJY9w=;
        b=HijLB4nVT0NgIfiBiwaUYzmEMJrjmld/ZAxi6p9Jdbh3V8oMTHmy/+ELkunxy2eck5
         pgWPFCxxsx6JgVD1CbLF4jkEnQwnjFpndLa238h2Q80ch89Epn/FC0p5t4Pc9yU7Xkam
         OW5HIXe2SAx/Q70Ze+kA8bUBzSJ0JDvBCRm4apV4SkUmZIxqLZWvwRa+2nDwM5rfVqLy
         z2/CrhJY5JzS4cv7ME+LvAblzDjrRxp5HrglZyLOojYxIHciZ+Hr7IKGvTQTO4mNA+Nd
         nb7DbS+0+wK7y0FIvQv8txGveJ5P77pxGs2j4VOuwFOxjQNpmL9ixk2mFqDVvWE09vpN
         TqRQ==
X-Gm-Message-State: APjAAAXDGApqXAz5ReObmJJmQAVNAwk3mvxaKPH1CuVTVcITjAtaUIgh
        3VZZMej+p5Cfa/yPz4Q0htdxx0Yx
X-Google-Smtp-Source: 
 APXvYqzhyJ4Kh/a6galI0gjAkld4KLQic+pfcqsfZ4JLq3E9hN5NJdv2AysoklmRZ65fyziweX6Jqw==
X-Received: by 2002:adf:f445:: with SMTP id f5mr33093504wrp.193.1574101072269;
        Mon, 18 Nov 2019 10:17:52 -0800 (PST)
Received: from 640k.localdomain.com ([93.56.166.5])
        by smtp.gmail.com with ESMTPSA id v81sm233794wmg.4.2019.11.18.10.17.51
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 18 Nov 2019 10:17:51 -0800 (PST)
From: Paolo Bonzini <pbonzini@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org
Cc: jmattson@google.com,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        stable@vger.kernel.org
Subject: [PATCH 1/5] KVM: x86: fix presentation of TSX feature in
 ARCH_CAPABILITIES
Date: Mon, 18 Nov 2019 19:17:43 +0100
Message-Id: <1574101067-5638-2-git-send-email-pbonzini@redhat.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1574101067-5638-1-git-send-email-pbonzini@redhat.com>
References: <1574101067-5638-1-git-send-email-pbonzini@redhat.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM does not implement MSR_IA32_TSX_CTRL, so it must not be presented
to the guests.  It is also confusing to have !ARCH_CAP_TSX_CTRL_MSR &&
!RTM && ARCH_CAP_TAA_NO: lack of MSR_IA32_TSX_CTRL suggests TSX was not
hidden (it actually was), yet the value says that TSX is not vulnerable
to microarchitectural data sampling.  Fix both.

Cc: stable@vger.kernel.org
Signed-off-by: Paolo Bonzini <pbonzini@redhat.com>
Reviewed-by: Jim Mattson <jmattson@google.com>
---
 arch/x86/kvm/x86.c | 10 ++++++++--
 1 file changed, 8 insertions(+), 2 deletions(-)

```
#### [PATCH] KVM: x86: Unexport kvm_vcpu_reload_apic_access_page()
##### From: Liran Alon <liran.alon@oracle.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Liran Alon <liran.alon@oracle.com>
X-Patchwork-Id: 11250059
Return-Path: <SRS0=wTpQ=ZK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CEAB71390
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 17:27:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AD6E221934
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 17:27:47 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=oracle.com header.i=@oracle.com
 header.b="LRv+lsQp"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726370AbfKRR1q (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 Nov 2019 12:27:46 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:56286 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726068AbfKRR1q (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 18 Nov 2019 12:27:46 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAIHODXr167194;
        Mon, 18 Nov 2019 17:27:41 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2019-08-05; bh=wfuyICAdhcwLIbYRdGhzGj7QT4StLnJ6nCsiEQtmtg8=;
 b=LRv+lsQpb6qtutXfj4SYvdrJKXhb/Cf7GnRcMvFZscTTzgn2lQ19Aj65tyRHvyIeE21C
 T8sAVXo98X4f0ka98KeQsgXS1aCetPD6fiXTy/u/KHDHkaJ2/NbL+NtcSU/CbjU4//ga
 4Rm3hn/sRmBKVNithGDW9cekpRHNQsT5IBQ+c718udRdjndUyzfr/f/yMl8lndmsfGPm
 IYbLcf6CN6arqQkGy0I3mGzBo/DljyU/RGRRoraYwcSdLzFJUz9wOyd0Cyq9pn1ib4yw
 u4lbkiG8lc9rnvO5H4yk1UfjcEAGFBYB6cJTH6mV9mCsOYD73TKvYm/a6BjU92za4Nso tQ==
Received: from aserp3020.oracle.com (aserp3020.oracle.com [141.146.126.70])
        by aserp2120.oracle.com with ESMTP id 2wa92phpv6-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 18 Nov 2019 17:27:40 +0000
Received: from pps.filterd (aserp3020.oracle.com [127.0.0.1])
        by aserp3020.oracle.com (8.16.0.27/8.16.0.27) with SMTP id
 xAIHOiIC032890;
        Mon, 18 Nov 2019 17:27:40 GMT
Received: from userv0121.oracle.com (userv0121.oracle.com [156.151.31.72])
        by aserp3020.oracle.com with ESMTP id 2wbxgau1k9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 18 Nov 2019 17:27:40 +0000
Received: from abhmp0014.oracle.com (abhmp0014.oracle.com [141.146.116.20])
        by userv0121.oracle.com (8.14.4/8.13.8) with ESMTP id xAIHRcGm013196;
        Mon, 18 Nov 2019 17:27:38 GMT
Received: from Lirans-MBP.Home (/79.181.226.113)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Mon, 18 Nov 2019 09:27:38 -0800
From: Liran Alon <liran.alon@oracle.com>
To: pbonzini@redhat.com, rkrcmar@redhat.com, kvm@vger.kernel.org
Cc: sean.j.christopherson@intel.com, jmattson@google.com,
        vkuznets@redhat.com, Liran Alon <liran.alon@oracle.com>,
        Mark Kanda <mark.kanda@oracle.com>
Subject: [PATCH] KVM: x86: Unexport kvm_vcpu_reload_apic_access_page()
Date: Mon, 18 Nov 2019 19:27:02 +0200
Message-Id: <20191118172702.42200-1-liran.alon@oracle.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9445
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 suspectscore=0
 malwarescore=0
 phishscore=0 bulkscore=0 spamscore=0 mlxscore=0 mlxlogscore=804
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.0.1-1911140001 definitions=main-1911180150
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9445
 signatures=668685
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0
 priorityscore=1501 malwarescore=0
 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0 clxscore=1015
 lowpriorityscore=0 mlxscore=0 impostorscore=0 mlxlogscore=889 adultscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.0.1-1911140001
 definitions=main-1911180150
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The function is only used in kvm.ko module.

Reviewed-by: Mark Kanda <mark.kanda@oracle.com>
Signed-off-by: Liran Alon <liran.alon@oracle.com>
---
 arch/x86/kvm/x86.c | 1 -
 1 file changed, 1 deletion(-)

```
#### [PATCH V12 1/6] mdev: make mdev bus agnostic
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11248917
Return-Path: <SRS0=wTpQ=ZK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AF8BA14C0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 06:19:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 72B5E206D4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 06:19:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="OWa+B+tc"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726638AbfKRGSu (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 Nov 2019 01:18:50 -0500
Received: from us-smtp-2.mimecast.com ([205.139.110.61]:42819 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726595AbfKRGSt (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 18 Nov 2019 01:18:49 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574057926;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=/XNAWBJl9HYd58zJCbVCxLRJrBu8qH2nBLBROQScSb0=;
        b=OWa+B+tc8ft3wuxO/3yVmcCBcuW/pBF1zzxrQUEI+bFLW+eFaay5iT3DHYuwZ4sDUJEUb4
        ww5g8xXG+dcTrIp2akElctgoCHL70kLn0K4LM7rQvBkKTWoa3ldX36pF4sSISAdbPRJFgT
        rbJdW2DZkm/PNn33VZsv6uZtol1t69w=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-152-tD3vmjQuNrO9sCAztXnV0A-1; Mon, 18 Nov 2019 01:18:42 -0500
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 0A81D9125A;
        Mon, 18 Nov 2019 06:18:38 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-215.pek2.redhat.com [10.72.12.215])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 3C0A961070;
        Mon, 18 Nov 2019 06:17:40 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        cohuck@redhat.com, maxime.coquelin@redhat.com,
        cunming.liang@intel.com, zhihong.wang@intel.com,
        rob.miller@broadcom.com, xiao.w.wang@intel.com,
        haotian.wang@sifive.com, zhenyuw@linux.intel.com,
        zhi.a.wang@intel.com, jani.nikula@linux.intel.com,
        joonas.lahtinen@linux.intel.com, rodrigo.vivi@intel.com,
        airlied@linux.ie, daniel@ffwll.ch, farman@linux.ibm.com,
        pasic@linux.ibm.com, sebott@linux.ibm.com, oberpar@linux.ibm.com,
        heiko.carstens@de.ibm.com, gor@linux.ibm.com,
        borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        freude@linux.ibm.com, lingshan.zhu@intel.com, eperezma@redhat.com,
        lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        stefanha@redhat.com, rdunlap@infradead.org, hch@infradead.org,
        gregkh@linuxfoundation.org, jgg@mellanox.com,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH V12 1/6] mdev: make mdev bus agnostic
Date: Mon, 18 Nov 2019 14:16:58 +0800
Message-Id: <20191118061703.8669-2-jasowang@redhat.com>
In-Reply-To: <20191118061703.8669-1-jasowang@redhat.com>
References: <20191118061703.8669-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-MC-Unique: tD3vmjQuNrO9sCAztXnV0A-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current mdev is tied to a VFIO specific "mdev" bus. This prevent mdev
from being used by other types of API/buses. So this patch tries to make
mdev bus agnostic through making a mdev core a thin module:

- decouple VFIO bus specific bits from mdev_core.c to mdev_vfio.c and
  introduce mdev_vfio module
- require to specify the type of bus when registering mdev device and
  mdev driver

With those modifications mdev become a generic module that could be
used by multiple types of virtual buses and devices.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 .../driver-api/vfio-mediated-device.rst       |  68 ++++++------
 MAINTAINERS                                   |   1 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |  10 +-
 drivers/s390/cio/vfio_ccw_ops.c               |   6 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  21 ++--
 drivers/s390/crypto/vfio_ap_private.h         |   2 +-
 drivers/vfio/mdev/Kconfig                     |  17 ++-
 drivers/vfio/mdev/Makefile                    |   4 +-
 drivers/vfio/mdev/mdev_core.c                 | 104 +++++++++++++-----
 drivers/vfio/mdev/mdev_driver.c               |  29 ++---
 drivers/vfio/mdev/mdev_private.h              |  13 ++-
 drivers/vfio/mdev/mdev_vfio.c                 |  48 ++++++++
 drivers/vfio/mdev/vfio_mdev.c                 |   5 +-
 drivers/vfio/vfio_iommu_type1.c               |   6 +-
 include/linux/mdev.h                          |  16 ++-
 include/linux/mdev_vfio.h                     |  25 +++++
 samples/vfio-mdev/mbochs.c                    |   8 +-
 samples/vfio-mdev/mdpy.c                      |   8 +-
 samples/vfio-mdev/mtty.c                      |   8 +-
 19 files changed, 270 insertions(+), 129 deletions(-)
 create mode 100644 drivers/vfio/mdev/mdev_vfio.c
 create mode 100644 include/linux/mdev_vfio.h

```
#### [PATCH V13 1/6] mdev: make mdev bus agnostic
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11249453
Return-Path: <SRS0=wTpQ=ZK=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DFE1D13A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 11:01:02 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 9A55220730
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 18 Nov 2019 11:01:02 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="CbF6Nngi"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727014AbfKRLBB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 18 Nov 2019 06:01:01 -0500
Received: from us-smtp-2.mimecast.com ([207.211.31.81]:37355 "EHLO
        us-smtp-delivery-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727018AbfKRLAu (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 18 Nov 2019 06:00:50 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1574074849;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=GW2I8rJWN+PV2Ds7/69tjjdp7rnxBA4D3F92LuzCKF4=;
        b=CbF6Nngi5qTESPlFlyM5wkHqOvHEeVouD1Mth9p0pXcygYrxoLpHjLjoGvHnwjwfTtPSce
        6vGAQ82a2uzS4Mxs7GppZJAbjKdLe0yAHKuJzmrI5JOofvu20Sxka8MCz8/V3r9uo5uTh3
        YXJLKfpMBsor1QNETv6/+2/d3Kgtq74=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-33-AzOnWVXKMjqEvZxESlZV3Q-1; Mon, 18 Nov 2019 06:00:47 -0500
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id CCE5B18A5DDC;
        Mon, 18 Nov 2019 11:00:41 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-65.pek2.redhat.com [10.72.12.65])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 1644260BE1;
        Mon, 18 Nov 2019 10:59:58 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        linux-kernel@vger.kernel.org, dri-devel@lists.freedesktop.org,
        intel-gfx@lists.freedesktop.org,
        intel-gvt-dev@lists.freedesktop.org, kwankhede@nvidia.com,
        alex.williamson@redhat.com, mst@redhat.com, tiwei.bie@intel.com,
        gregkh@linuxfoundation.org, jgg@mellanox.com
Cc: netdev@vger.kernel.org, cohuck@redhat.com,
        maxime.coquelin@redhat.com, cunming.liang@intel.com,
        zhihong.wang@intel.com, rob.miller@broadcom.com,
        xiao.w.wang@intel.com, haotian.wang@sifive.com,
        zhenyuw@linux.intel.com, zhi.a.wang@intel.com,
        jani.nikula@linux.intel.com, joonas.lahtinen@linux.intel.com,
        rodrigo.vivi@intel.com, airlied@linux.ie, daniel@ffwll.ch,
        farman@linux.ibm.com, pasic@linux.ibm.com, sebott@linux.ibm.com,
        oberpar@linux.ibm.com, heiko.carstens@de.ibm.com,
        gor@linux.ibm.com, borntraeger@de.ibm.com, akrowiak@linux.ibm.com,
        freude@linux.ibm.com, lingshan.zhu@intel.com, eperezma@redhat.com,
        lulu@redhat.com, parav@mellanox.com,
        christophe.de.dinechin@gmail.com, kevin.tian@intel.com,
        stefanha@redhat.com, rdunlap@infradead.org, hch@infradead.org,
        aadam@redhat.com, jakub.kicinski@netronome.com, jiri@mellanox.com,
        jeffrey.t.kirsher@intel.com, Jason Wang <jasowang@redhat.com>
Subject: [PATCH V13 1/6] mdev: make mdev bus agnostic
Date: Mon, 18 Nov 2019 18:59:18 +0800
Message-Id: <20191118105923.7991-2-jasowang@redhat.com>
In-Reply-To: <20191118105923.7991-1-jasowang@redhat.com>
References: <20191118105923.7991-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-MC-Unique: AzOnWVXKMjqEvZxESlZV3Q-1
X-Mimecast-Spam-Score: 0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Current mdev is tied to a VFIO specific "mdev" bus. This prevent mdev
from being used by other types of API/buses. So this patch tries to make
mdev bus agnostic through making a mdev core a thin module:

- decouple VFIO bus specific bits from mdev_core.c to mdev_vfio.c and
  introduce mdev_vfio module
- require to specify the type of bus when registering mdev device and
  mdev driver

With those modifications mdev become a generic module that could be
used by multiple types of virtual buses and devices.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 .../driver-api/vfio-mediated-device.rst       |  68 ++++++------
 MAINTAINERS                                   |   1 +
 drivers/gpu/drm/i915/gvt/kvmgt.c              |   8 +-
 drivers/s390/cio/vfio_ccw_ops.c               |   6 +-
 drivers/s390/crypto/vfio_ap_ops.c             |  21 ++--
 drivers/s390/crypto/vfio_ap_private.h         |   2 +-
 drivers/vfio/mdev/Kconfig                     |  17 ++-
 drivers/vfio/mdev/Makefile                    |   4 +-
 drivers/vfio/mdev/mdev_core.c                 | 104 +++++++++++++-----
 drivers/vfio/mdev/mdev_driver.c               |  29 ++---
 drivers/vfio/mdev/mdev_private.h              |  13 ++-
 drivers/vfio/mdev/mdev_vfio.c                 |  48 ++++++++
 drivers/vfio/mdev/vfio_mdev.c                 |   5 +-
 drivers/vfio/vfio_iommu_type1.c               |   6 +-
 include/linux/mdev.h                          |  16 ++-
 include/linux/mdev_vfio.h                     |  25 +++++
 samples/vfio-mdev/mbochs.c                    |   8 +-
 samples/vfio-mdev/mdpy.c                      |   8 +-
 samples/vfio-mdev/mtty.c                      |   8 +-
 19 files changed, 269 insertions(+), 128 deletions(-)
 create mode 100644 drivers/vfio/mdev/mdev_vfio.c
 create mode 100644 include/linux/mdev_vfio.h

```
