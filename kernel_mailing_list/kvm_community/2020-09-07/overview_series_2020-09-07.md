#### [PATCH 1/2] vhost: remove mutex ops in vhost_set_backend_features
##### From: Zhu Lingshan <lingshan.zhu@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Zhu Lingshan <lingshan.zhu@intel.com>
X-Patchwork-Id: 11760589
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 07F3659D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 10:56:57 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id EACE22166E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 10:56:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728987AbgIGK4i (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 06:56:38 -0400
Received: from mga12.intel.com ([192.55.52.136]:22272 "EHLO mga12.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728956AbgIGK4Z (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Sep 2020 06:56:25 -0400
IronPort-SDR: 
 ecpX33UHRVEzHaSabuW1+xN9eA5VcsJuIEQubFYY10aBjyd2GDfDk0F0ltNbWMwV9McTxz7U77
 q8Z/R8m9LYrg==
X-IronPort-AV: E=McAfee;i="6000,8403,9736"; a="137503292"
X-IronPort-AV: E=Sophos;i="5.76,401,1592895600";
   d="scan'208";a="137503292"
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from orsmga006.jf.intel.com ([10.7.209.51])
  by fmsmga106.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 07 Sep 2020 03:56:25 -0700
IronPort-SDR: 
 RlfK2hmzUDMq+BUJoWCcda1pTnQZOYWGwj+y9pd31yA7kQp25F1DXYKFPrfHNlh8MGAP7Pp6kO
 2zdmw6sVhMAQ==
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.76,401,1592895600";
   d="scan'208";a="303698276"
Received: from unknown (HELO localhost.localdomain.bj.intel.com)
 ([10.240.192.131])
  by orsmga006.jf.intel.com with ESMTP; 07 Sep 2020 03:56:22 -0700
From: Zhu Lingshan <lingshan.zhu@intel.com>
To: jasowang@redhat.com, mst@redhat.com
Cc: virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        kvm@vger.kernel.org, Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH 1/2] vhost: remove mutex ops in vhost_set_backend_features
Date: Mon,  7 Sep 2020 18:52:19 +0800
Message-Id: <20200907105220.27776-2-lingshan.zhu@intel.com>
X-Mailer: git-send-email 2.18.4
In-Reply-To: <20200907105220.27776-1-lingshan.zhu@intel.com>
References: <20200907105220.27776-1-lingshan.zhu@intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In vhost_vdpa ioctl SET_BACKEND_FEATURES path, currect code
would try to acquire vhost dev mutex twice
(first shown in vhost_vdpa_unlocked_ioctl), which can lead
to a dead lock issue.
This commit removed mutex operations in vhost_set_backend_features.
As a compensation for vhost_net, a followinig commit will add
needed mutex lock/unlock operations in a new function
vhost_net_set_backend_features() which is a wrap of
vhost_set_backend_features().

Signed-off-by: Zhu Lingshan <lingshan.zhu@intel.com>
---
 drivers/vhost/vhost.c | 2 --
 1 file changed, 2 deletions(-)

```
#### [PATCH] KVM: s390: Introduce storage key removal facility
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11761801
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 490E659D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 17:46:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1448B2137B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 17:46:19 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="PcYpCD7m"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730750AbgIGRqM (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 13:46:12 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:19478 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729394AbgIGNO0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 09:14:26 -0400
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 087D4UNn167875;
        Mon, 7 Sep 2020 09:14:24 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=qAM6XSxtNjfqGEthn7zWqzDo3LY9WO8P+0xYllpgUh8=;
 b=PcYpCD7mhcMlTayQdJaSb50I2Gi7UCBmOD+4dFPd1fpS0n/f8fV7FtjeehFK55+/CNjv
 jSv/XoP8bMGGpEXEEleROj5FW4hlFV3+BVq3A3fIQQkRyQyLedbo4GPaxnlT2P4f1Hzy
 ZWdaly6emoVKSNWRn7dUO8soqfXC5KcmRFGndQ4qm/tfh97labf683d1qMjj4ZKTUNrc
 w16K8p1uwQi4fcqXKJYElv7SmX8WE3suGw9nJRddRYpusgdQuVGSIi3VelW1SH+J/u6j
 eljFVWmiAD2Rg5ecsBLzr9NT6kgVkPqHH1o2Hpy0T7L9mvjQSKvppbFK/3qEnA/zfupD 2Q==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33dkc4bq76-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 09:14:24 -0400
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 087D53TK170637;
        Mon, 7 Sep 2020 09:14:24 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33dkc4bq6s-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 09:14:24 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 087DCSLF029546;
        Mon, 7 Sep 2020 13:14:22 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma04ams.nl.ibm.com with ESMTP id 33c2a8adyy-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 13:14:22 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 087DClrJ29295024
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 7 Sep 2020 13:12:47 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 6F167A4040;
        Mon,  7 Sep 2020 13:14:19 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C4BEDA405B;
        Mon,  7 Sep 2020 13:14:18 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  7 Sep 2020 13:14:18 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: borntraeger@de.ibm.com, imbrenda@linux.ibm.com, david@redhat.com,
        linux-s390@vger.kernel.org
Subject: [PATCH] KVM: s390: Introduce storage key removal facility
Date: Mon,  7 Sep 2020 09:14:10 -0400
Message-Id: <20200907131410.11474-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-07_07:2020-09-07,2020-09-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015 mlxscore=0
 adultscore=0 suspectscore=1 malwarescore=0 priorityscore=1501
 impostorscore=0 lowpriorityscore=0 mlxlogscore=999 bulkscore=0 spamscore=0
 phishscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009070128
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The storage key removal facility makes skey related instructions
result in special operation program exceptions. It is based on the
Keyless Subset Facility.

The usual suspects are iske, sske, rrbe and their respective
variants. lpsw(e), pfmf and tprot can also specify a key and essa with
an ORC of 4 will consult the change bit, hence they all result in
exceptions.

Unfortunately storage keys were so essential to the architecture, that
there is no facility bit that we could deactivate. That's why the
removal facility (bit 169) was introduced which makes it necessary,
that, if active, the skey related facilities 10, 14, 66, 145 and 149
are zero. Managing this requirement and migratability has to be done
in userspace, as KVM does not check the facilities it receives to be
able to easily implement userspace emulation.

Removing storage key support allows us to circumvent complicated
emulation code and makes huge page support tremendously easier.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---
 arch/s390/kvm/intercept.c | 40 ++++++++++++++++++++++++++++++++++++++-
 arch/s390/kvm/kvm-s390.c  |  5 +++++
 arch/s390/kvm/priv.c      | 26 ++++++++++++++++++++++---
 3 files changed, 67 insertions(+), 4 deletions(-)

```
#### [RESEND PATCH v2] KVM: fix memory leak in kvm_io_bus_unregister_dev()
##### From: Rustam Kovhaev <rkovhaev@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Rustam Kovhaev <rkovhaev@gmail.com>
X-Patchwork-Id: 11762115
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A7B851599
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 18:56:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 8C3472067C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 18:56:13 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="LzYUAim1"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729950AbgIGS4L (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 14:56:11 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:56128 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1729472AbgIGSzJ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Sep 2020 14:55:09 -0400
Received: from mail-pf1-x441.google.com (mail-pf1-x441.google.com
 [IPv6:2607:f8b0:4864:20::441])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id 106D6C061573;
        Mon,  7 Sep 2020 11:55:09 -0700 (PDT)
Received: by mail-pf1-x441.google.com with SMTP id b124so8994122pfg.13;
        Mon, 07 Sep 2020 11:55:08 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=dawj1SMvdQbml5uHKFi5qJIO1Xksj7iCEcoBAXgXEuI=;
        b=LzYUAim1sww5RSYzIbFyJZ7GkaZRwpjcPpZ2OaI+rE7BDVh1A0Ni+qbUi1gDaqtK+2
         eGsCrnL1B32m+PDpBd+969FoZj+Tu9KXd9QCQb35FDrmfZbM88KAAHX/Z4YzDEy3iRdw
         +31fkC97nJDFvW5V5XIMDPfr+INVFkFbcmZkzV4TCT2L3uL403QE/hwW5BTUDeNlVtg7
         rWLXQlvXhbhsAjuJEEP/oYZ8Ocsy2nx/6MI5finWZTcs01lk270uL8ElQyKKRaxKrX5E
         SSVvM4G4hScGD5BYtQreQ0uBdHyV4nH5Ad5jM61SexmSmZK26CYCBOlBVhPE+gEykIIK
         5tcQ==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=dawj1SMvdQbml5uHKFi5qJIO1Xksj7iCEcoBAXgXEuI=;
        b=YFk4cwGmtM63kaWQJN7oESua55pyL7m7oNNMKunNv9m5v45YW6RuUYCHYrMxYXQrkB
         X2p1mXKjyh6azWk0AJu9ETi3F+vcU1/GuuG6AKxIWzo20nv8ElYTk82qYdsU7SNu6VPy
         vcQkmt/0fri/S7ovXaJgPB6stRry5rV6DNbYO1Ia/gYYf1fEeU1zz7IUXNSaPPRrjcFZ
         6BIqXcwWSAvv/uha0sPAl/yKsSGDANDLTftxf/6fEzyjomlzPda9F3+JgIbGYEY/WUgJ
         2dp7eNkEX6ZK1fbeDjrMKSeGMWy1Kvpqq4OL4TYIsAOHGcxs1mtNZpwAwKnPIWDK3yIO
         3TzQ==
X-Gm-Message-State: AOAM531kg5n0/fKsvh0CvRZCiMXFvUDEI4u47SGYt+ramNbJNQR9VW98
        imNbzc2HJSeKELLPAbw2JSU=
X-Google-Smtp-Source: 
 ABdhPJxay8d9Q5I7t6iNt4rnkHhZw2gW/vAIWCtXS76rfVzqgleboOPliRkM/UDIXkwoe5DpbcNg9g==
X-Received: by 2002:aa7:9991:0:b029:13c:1611:6530 with SMTP id
 k17-20020aa799910000b029013c16116530mr19254157pfh.16.1599504908391;
        Mon, 07 Sep 2020 11:55:08 -0700 (PDT)
Received: from localhost.localdomain (104.36.148.139.aurocloud.com.
 [104.36.148.139])
        by smtp.gmail.com with ESMTPSA id
 p190sm16178304pfp.9.2020.09.07.11.55.04
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Mon, 07 Sep 2020 11:55:07 -0700 (PDT)
From: Rustam Kovhaev <rkovhaev@gmail.com>
To: pbonzini@redhat.com, vkuznets@redhat.com, gustavoars@kernel.org,
        kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, gregkh@linuxfoundation.org,
        stable@vger.kernel.org, Rustam Kovhaev <rkovhaev@gmail.com>
Subject: [RESEND PATCH v2] KVM: fix memory leak in kvm_io_bus_unregister_dev()
Date: Mon,  7 Sep 2020 11:55:35 -0700
Message-Id: <20200907185535.233114-1-rkovhaev@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

when kmalloc() fails in kvm_io_bus_unregister_dev(), before removing
the bus, we should iterate over all other devices linked to it and call
kvm_iodevice_destructor() for them

Fixes: 90db10434b16 ("KVM: kvm_io_bus_unregister_dev() should never fail")
Cc: stable@vger.kernel.org
Reported-and-tested-by: syzbot+f196caa45793d6374707@syzkaller.appspotmail.com
Link: https://syzkaller.appspot.com/bug?extid=f196caa45793d6374707
Signed-off-by: Rustam Kovhaev <rkovhaev@gmail.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
v2:
- remove redundant whitespace
- remove goto statement and use if/else
- add Fixes tag
---
 virt/kvm/kvm_main.c | 21 ++++++++++++---------
 1 file changed, 12 insertions(+), 9 deletions(-)

```
#### [PATCH v11 1/2] virtio: let arch advertise guest's memory access restrictions
##### From: Pierre Morel <pmorel@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Pierre Morel <pmorel@linux.ibm.com>
X-Patchwork-Id: 11760331
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CFF1A59D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 09:39:51 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A260121481
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 09:39:51 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="or5Yam2q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728503AbgIGJjb (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 05:39:31 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:4850 "EHLO
        mx0b-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728333AbgIGJja (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 05:39:30 -0400
Received: from pps.filterd (m0127361.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 0879WP3j162588;
        Mon, 7 Sep 2020 05:39:17 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=5vVyn/VEe6Gx+GNDMxeR+LiTeTBWESsSZ3pi73AegSs=;
 b=or5Yam2qzYABu+F+Xo1XwJVAVjFKCAiHYupbhgDBVklmpHLTZAYkjwkyzEIHAI7tcLVl
 9HT2dR5LwSTOqmGXVxi6SEYjJs6Z8yBzPcoKnRY3S8ruj12Qka1wH9PMgEUP7lBFYcim
 9ylpRLNhB7uXoOXQBgWEy0MvlkeQCTtBWCO6aPdTrfW3X4H5m0+mb9V73+NZm7IJpfco
 ZTCqwb8iaTIIJdGduedhTCrS5pYOEjnOvsDzuT48pP+LcZC9HChKzoTgb0fJ01WBEDRp
 tg4MFnkqY0FvnUjV/akrBV+lkOMbuIH3LNHrubxDMzKOTOCJ18+fcJgkYIuQM3WNQZTN UA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33dhnrh857-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 05:39:17 -0400
Received: from m0127361.ppops.net (m0127361.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 0879WZ6n163168;
        Mon, 7 Sep 2020 05:39:16 -0400
Received: from ppma06ams.nl.ibm.com (66.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.102])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33dhnrh848-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 05:39:16 -0400
Received: from pps.filterd (ppma06ams.nl.ibm.com [127.0.0.1])
        by ppma06ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 0879bpuO013779;
        Mon, 7 Sep 2020 09:39:14 GMT
Received: from b06cxnps3074.portsmouth.uk.ibm.com
 (d06relay09.portsmouth.uk.ibm.com [9.149.109.194])
        by ppma06ams.nl.ibm.com with ESMTP id 33cyq50ycb-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 09:39:14 +0000
Received: from b06wcsmtp001.portsmouth.uk.ibm.com
 (b06wcsmtp001.portsmouth.uk.ibm.com [9.149.105.160])
        by b06cxnps3074.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 0879dBKj38142398
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 7 Sep 2020 09:39:11 GMT
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1E150A4066;
        Mon,  7 Sep 2020 09:39:11 +0000 (GMT)
Received: from b06wcsmtp001.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4D609A4060;
        Mon,  7 Sep 2020 09:39:10 +0000 (GMT)
Received: from oc3016276355.ibm.com (unknown [9.145.86.222])
        by b06wcsmtp001.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  7 Sep 2020 09:39:10 +0000 (GMT)
From: Pierre Morel <pmorel@linux.ibm.com>
To: linux-kernel@vger.kernel.org
Cc: pasic@linux.ibm.com, borntraeger@de.ibm.com, frankja@linux.ibm.com,
        mst@redhat.com, jasowang@redhat.com, cohuck@redhat.com,
        kvm@vger.kernel.org, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, thomas.lendacky@amd.com,
        david@gibson.dropbear.id.au, linuxram@us.ibm.com,
        hca@linux.ibm.com, gor@linux.ibm.com
Subject: [PATCH v11 1/2] virtio: let arch advertise guest's memory access
 restrictions
Date: Mon,  7 Sep 2020 11:39:06 +0200
Message-Id: <1599471547-28631-2-git-send-email-pmorel@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1599471547-28631-1-git-send-email-pmorel@linux.ibm.com>
References: <1599471547-28631-1-git-send-email-pmorel@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-07_04:2020-09-07,2020-09-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 impostorscore=0 bulkscore=0
 mlxlogscore=999 spamscore=0 lowpriorityscore=0 phishscore=0 malwarescore=0
 adultscore=0 clxscore=1015 mlxscore=0 suspectscore=1 priorityscore=1501
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009070093
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

An architecture may restrict host access to guest memory,
e.g. IBM s390 Secure Execution or AMD SEV.

Provide a new Kconfig entry the architecture can select,
CONFIG_ARCH_HAS_RESTRICTED_VIRTIO_MEMORY_ACCESS, when it provides
the arch_has_restricted_virtio_memory_access callback to advertise
to VIRTIO common code when the architecture restricts memory access
from the host.

The common code can then fail the probe for any device where
VIRTIO_F_ACCESS_PLATFORM is required, but not set.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
---
 drivers/virtio/Kconfig        |  6 ++++++
 drivers/virtio/virtio.c       | 15 +++++++++++++++
 include/linux/virtio_config.h | 10 ++++++++++
 3 files changed, 31 insertions(+)

```
#### [PATCH v2 1/2] s390x: uv: Add destroy page call
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11761825
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6605959D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 17:48:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 38DCF21556
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 17:48:48 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="NEH/kg/T"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729360AbgIGRsq (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 13:48:46 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:27602 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729238AbgIGMr3 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 08:47:29 -0400
Received: from pps.filterd (m0187473.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 087CWdIw024609;
        Mon, 7 Sep 2020 08:47:11 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=MXMq3EmkqOvtG8HsBJAUtPbkO0CM2bugFDChG4+GSeM=;
 b=NEH/kg/TSMRXRYh3YFrwVkE7okPhAG8ng3zURpgXCpboCHCEBCDUkK5z1ipGjCNZrfCF
 9gTlGJsW4P/aUoIT4nB2U98dHiD7V8SAD/u/0EAf4Ojga1U7r6cXCH9yNgB0xwsFY1wm
 OI9cULaqABMUahIRVwBNZg36zoikDfGKpSESwtmFvsHRl0dSsm8rfFXDx7gaxfcfKImr
 zB0wPinBfPlfH+Ih0REkqIztmJXYf0gdZINXgpnZCWoY9c7SCtfkF8bfwiulR6ZtzA86
 Y3N/UNB8G/bqr2rad+BisesKFW94QuBaEuZSFkgOhvkPU0w2KuH+TidhmvqSYgczC09/ RQ==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33dmv28ecm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 08:47:10 -0400
Received: from m0187473.ppops.net (m0187473.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 087CXtkY027855;
        Mon, 7 Sep 2020 08:47:10 -0400
Received: from ppma05fra.de.ibm.com (6c.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.108])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33dmv28ebu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 08:47:10 -0400
Received: from pps.filterd (ppma05fra.de.ibm.com [127.0.0.1])
        by ppma05fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 087Ch8TM011540;
        Mon, 7 Sep 2020 12:47:07 GMT
Received: from b06avi18626390.portsmouth.uk.ibm.com
 (b06avi18626390.portsmouth.uk.ibm.com [9.149.26.192])
        by ppma05fra.de.ibm.com with ESMTP id 33c2a89f20-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 12:47:07 +0000
Received: from d06av22.portsmouth.uk.ibm.com (d06av22.portsmouth.uk.ibm.com
 [9.149.105.58])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 087CjWTx41746832
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 7 Sep 2020 12:45:32 GMT
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id AA5134C046;
        Mon,  7 Sep 2020 12:47:04 +0000 (GMT)
Received: from d06av22.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E46184C04A;
        Mon,  7 Sep 2020 12:47:03 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av22.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  7 Sep 2020 12:47:03 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: linux-s390@vger.kernel.org
Cc: borntraeger@de.ibm.com, gor@linux.ibm.com, imbrenda@linux.ibm.com,
        kvm@vger.kernel.org, david@redhat.com, hca@linux.ibm.com
Subject: [PATCH v2 1/2] s390x: uv: Add destroy page call
Date: Mon,  7 Sep 2020 08:46:59 -0400
Message-Id: <20200907124700.10374-2-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <20200907124700.10374-1-frankja@linux.ibm.com>
References: <20200907124700.10374-1-frankja@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-07_06:2020-09-07,2020-09-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 malwarescore=0
 priorityscore=1501 impostorscore=0 lowpriorityscore=0 clxscore=1015
 mlxlogscore=999 phishscore=0 mlxscore=0 bulkscore=0 spamscore=0
 suspectscore=1 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009070123
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

We don't need to export pages if we destroy the VM configuration
afterwards anyway. Instead we can destroy the page which will zero it
and then make it accessible to the host.

Destroying is about twice as fast as the export.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
Reviewed-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
Reviewed-by: Thomas Huth <thuth@redhat.com>
---
 arch/s390/include/asm/uv.h |  7 +++++++
 arch/s390/kernel/uv.c      | 20 ++++++++++++++++++++
 arch/s390/mm/gmap.c        |  2 +-
 3 files changed, 28 insertions(+), 1 deletion(-)

```
#### [PATCH v2] KVM: s390: Introduce storage key removal facility
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11761375
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CF602138E
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 16:12:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id A89EB21789
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 16:12:27 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="cgyM0qlH"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730237AbgIGQKV (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 12:10:21 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:58326 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1729934AbgIGOeL (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 10:34:11 -0400
Received: from pps.filterd (m0098420.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 087EW4lL066563;
        Mon, 7 Sep 2020 10:33:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=S9tU1TOVSI89giof7IcVLe/S/zlB9Bfyg223BMu75Gs=;
 b=cgyM0qlHzwHfrnCqR5VD45ggNuJ2rT/spIQ39ZksoFJpxorf8zatHxT5UsAJxiEw2+kI
 iVsQlizLS+SxTzYSMCuxvJ+DMy9uc099MCNHXYW5NRUTwgoFGlHUTfZGl4dTHtA4BU6W
 k4JLfQX0fzTuuAaSke7rY0vOcZUrifsd+3kJeqH01iZLnUUisn2SgGGgVj0WYXApayyW
 EMVBh6rs3nROrJYQ6HmOBY8lAn/5/tPadA4b4FbQtKKUdQ7tr3YC/PysK7QtwvXlxE+z
 caxm3fBw0vPLtZvKO2nXa1bxWMFEA/9RNFPAQMxmrR/qytwlwmRQ39RAtkIDtnH4O1OI Yg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33dpea0ffj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 10:33:59 -0400
Received: from m0098420.ppops.net (m0098420.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 087EWEDT067263;
        Mon, 7 Sep 2020 10:33:59 -0400
Received: from ppma04ams.nl.ibm.com (63.31.33a9.ip4.static.sl-reverse.com
 [169.51.49.99])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33dpea0feu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 10:33:58 -0400
Received: from pps.filterd (ppma04ams.nl.ibm.com [127.0.0.1])
        by ppma04ams.nl.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 087EW3bd030664;
        Mon, 7 Sep 2020 14:33:57 GMT
Received: from b06cxnps4075.portsmouth.uk.ibm.com
 (d06relay12.portsmouth.uk.ibm.com [9.149.109.197])
        by ppma04ams.nl.ibm.com with ESMTP id 33c2a8ag3u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 07 Sep 2020 14:33:57 +0000
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06cxnps4075.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 087EXs8K33882412
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 7 Sep 2020 14:33:54 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7C497AE055;
        Mon,  7 Sep 2020 14:33:54 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CE74EAE057;
        Mon,  7 Sep 2020 14:33:53 +0000 (GMT)
Received: from linux01.pok.stglabs.ibm.com (unknown [9.114.17.81])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon,  7 Sep 2020 14:33:53 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: borntraeger@de.ibm.com, imbrenda@linux.ibm.com, david@redhat.com,
        linux-s390@vger.kernel.org
Subject: [PATCH v2] KVM: s390: Introduce storage key removal facility
Date: Mon,  7 Sep 2020 10:33:52 -0400
Message-Id: <20200907143352.96618-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.25.1
In-Reply-To: <b34e559a-8292-873f-8d33-1e7ce819f4d5@de.ibm.com>
References: <b34e559a-8292-873f-8d33-1e7ce819f4d5@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-07_07:2020-09-07,2020-09-07 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 clxscore=1015
 lowpriorityscore=0 adultscore=0 spamscore=0 bulkscore=0 malwarescore=0
 priorityscore=1501 impostorscore=0 mlxscore=0 suspectscore=1
 mlxlogscore=987 phishscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2006250000 definitions=main-2009070139
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The storage key removal facility makes skey related instructions
result in special operation program exceptions. It is based on the
Keyless Subset Facility.

The usual suspects are iske, sske, rrbe and their respective
variants. lpsw(e), pfmf and tprot can also specify a key and essa with
an ORC of 4 will consult the change bit, hence they all result in
exceptions.

Unfortunately storage keys were so essential to the architecture, that
there is no facility bit that we could deactivate. That's why the
removal facility (bit 169) was introduced which makes it necessary,
that, if active, the skey related facilities 10, 14, 66, 145 and 149
are zero. Managing this requirement and migratability has to be done
in userspace, as KVM does not check the facilities it receives to be
able to easily implement userspace emulation.

Removing storage key support allows us to circumvent complicated
emulation code and makes huge page support tremendously easier.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---

v2:
	* Removed the likely
	* Updated and re-shuffeled the comments which had the wrong information

---
 arch/s390/kvm/intercept.c | 40 ++++++++++++++++++++++++++++++++++++++-
 arch/s390/kvm/kvm-s390.c  |  5 +++++
 arch/s390/kvm/priv.c      | 26 ++++++++++++++++++++++---
 3 files changed, 67 insertions(+), 4 deletions(-)

```
#### [PATCH v4.14.y 1/3] vfio/type1: Support faulting PFNMAP vmas
##### From: Ajay Kaher <akaher@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ajay Kaher <akaher@vmware.com>
X-Patchwork-Id: 11762181
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 82CE113B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 20:21:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 70FFF21556
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 20:21:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729550AbgIGUVI (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 16:21:08 -0400
Received: from ex13-edg-ou-002.vmware.com ([208.91.0.190]:12698 "EHLO
        EX13-EDG-OU-002.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729184AbgIGUVI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 16:21:08 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-002.vmware.com (10.113.208.156) with Microsoft SMTP Server id
 15.0.1156.6; Mon, 7 Sep 2020 13:21:07 -0700
Received: from akaher-virtual-machine.eng.vmware.com (unknown
 [10.197.103.239])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id BDD3C4072D;
        Mon,  7 Sep 2020 13:21:07 -0700 (PDT)
From: Ajay Kaher <akaher@vmware.com>
To: <gregkh@linuxfoundation.org>, <sashal@kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <peterx@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <stable@vger.kernel.org>,
        <srivatsab@vmware.com>, <srivatsa@csail.mit.edu>,
        <vsirnapalli@vmware.com>, <akaher@vmware.com>
Subject: [PATCH v4.14.y 1/3] vfio/type1: Support faulting PFNMAP vmas
Date: Tue, 8 Sep 2020 01:47:05 +0530
Message-ID: <1599509828-23596-1-git-send-email-akaher@vmware.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-002.vmware.com: akaher@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alex Williamson <alex.williamson@redhat.com>

commit 41311242221e3482b20bfed10fa4d9db98d87016 upstream.

With conversion to follow_pfn(), DMA mapping a PFNMAP range depends on
the range being faulted into the vma.  Add support to manually provide
that, in the same way as done on KVM with hva_to_pfn_remapped().

Reviewed-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
[Ajay: Regenerated the patch for v4.14]
Signed-off-by: Ajay Kaher <akaher@vmware.com>
---
 drivers/vfio/vfio_iommu_type1.c | 36 +++++++++++++++++++++++++++++++++---
 1 file changed, 33 insertions(+), 3 deletions(-)

```
#### [PATCH v4.19.y 1/3] vfio/type1: Support faulting PFNMAP vmas
##### From: Ajay Kaher <akaher@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ajay Kaher <akaher@vmware.com>
X-Patchwork-Id: 11760449
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C6CB113B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 10:23:06 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id B621321473
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 10:23:06 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728849AbgIGKXE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 06:23:04 -0400
Received: from ex13-edg-ou-002.vmware.com ([208.91.0.190]:56107 "EHLO
        EX13-EDG-OU-002.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728637AbgIGKVj (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 06:21:39 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-002.vmware.com (10.113.208.156) with Microsoft SMTP Server id
 15.0.1156.6; Mon, 7 Sep 2020 03:21:21 -0700
Received: from akaher-virtual-machine.eng.vmware.com (unknown
 [10.197.103.239])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id E71C240271;
        Mon,  7 Sep 2020 03:21:21 -0700 (PDT)
From: Ajay Kaher <akaher@vmware.com>
To: <gregkh@linuxfoundation.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <peterx@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <stable@vger.kernel.org>,
        <srivatsab@vmware.com>, <srivatsa@csail.mit.edu>,
        <vsirnapalli@vmware.com>, <akaher@vmware.com>
Subject: [PATCH v4.19.y 1/3] vfio/type1: Support faulting PFNMAP vmas
Date: Mon, 7 Sep 2020 15:47:20 +0530
Message-ID: <1599473843-34234-1-git-send-email-akaher@vmware.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-002.vmware.com: akaher@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alex Williamson <alex.williamson@redhat.com>

commit 41311242221e3482b20bfed10fa4d9db98d87016 upstream.

With conversion to follow_pfn(), DMA mapping a PFNMAP range depends on
the range being faulted into the vma.  Add support to manually provide
that, in the same way as done on KVM with hva_to_pfn_remapped().

Reviewed-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
[Ajay: Regenerated the patch for v4.19]
Signed-off-by: Ajay Kaher <akaher@vmware.com>
---
 drivers/vfio/vfio_iommu_type1.c | 36 +++++++++++++++++++++++++++++++++---
 1 file changed, 33 insertions(+), 3 deletions(-)

```
#### [PATCH v4.9.y 1/3] vfio/type1: Support faulting PFNMAP vmas
##### From: Ajay Kaher <akaher@vmware.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Ajay Kaher <akaher@vmware.com>
X-Patchwork-Id: 11762221
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8C7AE92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 20:40:13 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7427A21582
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 20:40:13 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727095AbgIGUjX (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 16:39:23 -0400
Received: from ex13-edg-ou-001.vmware.com ([208.91.0.189]:9185 "EHLO
        EX13-EDG-OU-001.vmware.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726962AbgIGUjW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 7 Sep 2020 16:39:22 -0400
Received: from sc9-mailhost3.vmware.com (10.113.161.73) by
 EX13-EDG-OU-001.vmware.com (10.113.208.155) with Microsoft SMTP Server id
 15.0.1156.6; Mon, 7 Sep 2020 13:39:20 -0700
Received: from akaher-virtual-machine.eng.vmware.com (unknown
 [10.197.103.239])
        by sc9-mailhost3.vmware.com (Postfix) with ESMTP id 6F07240385;
        Mon,  7 Sep 2020 13:39:21 -0700 (PDT)
From: Ajay Kaher <akaher@vmware.com>
To: <gregkh@linuxfoundation.org>, <sashal@kernel.org>
CC: <alex.williamson@redhat.com>, <cohuck@redhat.com>,
        <peterx@redhat.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <stable@vger.kernel.org>,
        <srivatsab@vmware.com>, <srivatsa@csail.mit.edu>,
        <vsirnapalli@vmware.com>, <akaher@vmware.com>
Subject: [PATCH v4.9.y 1/3] vfio/type1: Support faulting PFNMAP vmas
Date: Tue, 8 Sep 2020 02:05:14 +0530
Message-ID: <1599510917-23734-1-git-send-email-akaher@vmware.com>
X-Mailer: git-send-email 2.7.4
MIME-Version: 1.0
Received-SPF: None (EX13-EDG-OU-001.vmware.com: akaher@vmware.com does not
 designate permitted sender hosts)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alex Williamson <alex.williamson@redhat.com>

commit 41311242221e3482b20bfed10fa4d9db98d87016 upstream.

With conversion to follow_pfn(), DMA mapping a PFNMAP range depends on
the range being faulted into the vma.  Add support to manually provide
that, in the same way as done on KVM with hva_to_pfn_remapped().

Reviewed-by: Peter Xu <peterx@redhat.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
[Ajay: Regenerated the patch for v4.9]
Signed-off-by: Ajay Kaher <akaher@vmware.com>
---
 drivers/vfio/vfio_iommu_type1.c | 36 +++++++++++++++++++++++++++++++++---
 1 file changed, 33 insertions(+), 3 deletions(-)

```
#### 
##### 

```c
```
#### 
##### 

```c
```
#### 
##### 

```c
```
#### [PATCH] vhost-vdpa: fix backend feature ioctls
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11760575
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A098659D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 10:44:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 84EE620738
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 10:44:17 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="c+5E/3yD"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728669AbgIGKoB (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 06:44:01 -0400
Received: from us-smtp-delivery-1.mimecast.com ([205.139.110.120]:35282 "EHLO
        us-smtp-1.mimecast.com" rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org
        with ESMTP id S1728622AbgIGKn7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Sep 2020 06:43:59 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1599475437;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=c1vAH2sOnIecyBuC1bgws2niE0JgFrbZ244nIj8c+DU=;
        b=c+5E/3yDO70ZbiPkNa4L/2zeH2iwZBcd7wMROQUnARLBqwCuoRIH1UmMPM9MaCyL6hygbc
        /gKJh82BFaNuxRl/5qRvxwWHSpVbUVADcKZ4Q86TFfCxKrtESJvR0mnPyo1Wvcb10B72Sf
        om54B/+N5s8aC/YlCJ5Iy8E+eQPqFIk=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-404-uykzQjHlNiu2lD-lNSLY4w-1; Mon, 07 Sep 2020 06:43:54 -0400
X-MC-Unique: uykzQjHlNiu2lD-lNSLY4w-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id BA64E1084CA6;
        Mon,  7 Sep 2020 10:43:52 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-108.pek2.redhat.com [10.72.12.108])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 4BEAA60C0F;
        Mon,  7 Sep 2020 10:43:45 +0000 (UTC)
From: Jason Wang <jasowang@redhat.com>
To: mst@redhat.com, jasowang@redhat.com, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org, netdev@vger.kernel.org,
        linux-kernel@vger.kernel.org
Cc: lulu@redhat.com, Eli Cohen <elic@nvidia.com>,
        Zhu Lingshan <lingshan.zhu@intel.com>
Subject: [PATCH] vhost-vdpa: fix backend feature ioctls
Date: Mon,  7 Sep 2020 18:43:43 +0800
Message-Id: <20200907104343.31141-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Commit 653055b9acd4 ("vhost-vdpa: support get/set backend features")
introduces two malfunction backend features ioctls:

1) the ioctls was blindly added to vring ioctl instead of vdpa device
   ioctl
2) vhost_set_backend_features() was called when dev mutex has already
   been held which will lead a deadlock

This patch fixes the above issues.

Cc: Eli Cohen <elic@nvidia.com>
Reported-by: Zhu Lingshan <lingshan.zhu@intel.com>
Fixes: 653055b9acd4 ("vhost-vdpa: support get/set backend features")
Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 drivers/vhost/vdpa.c | 30 ++++++++++++++++--------------
 1 file changed, 16 insertions(+), 14 deletions(-)

```
#### [PATCH v7 01/72] KVM: SVM: nested: Don't allocate VMCB structures on stack
##### From: Joerg Roedel <joro@8bytes.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Joerg Roedel <joro@8bytes.org>
X-Patchwork-Id: 11761787
Return-Path: <SRS0=b9Ea=CQ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AE1A6746
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 17:43:40 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9FC3B215A4
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon,  7 Sep 2020 17:43:40 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1731349AbgIGRnj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 7 Sep 2020 13:43:39 -0400
Received: from 8bytes.org ([81.169.241.247]:41500 "EHLO theia.8bytes.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1729368AbgIGNRr (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 7 Sep 2020 09:17:47 -0400
Received: from cap.home.8bytes.org (p549add56.dip0.t-ipconnect.de
 [84.154.221.86])
        (using TLSv1.3 with cipher TLS_AES_256_GCM_SHA384 (256/256 bits))
        (No client certificate requested)
        by theia.8bytes.org (Postfix) with ESMTPSA id AF0E334A;
        Mon,  7 Sep 2020 15:16:42 +0200 (CEST)
From: Joerg Roedel <joro@8bytes.org>
To: x86@kernel.org
Cc: Joerg Roedel <joro@8bytes.org>, Joerg Roedel <jroedel@suse.de>,
        hpa@zytor.com, Andy Lutomirski <luto@kernel.org>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Jiri Slaby <jslaby@suse.cz>,
        Dan Williams <dan.j.williams@intel.com>,
        Tom Lendacky <thomas.lendacky@amd.com>,
        Juergen Gross <jgross@suse.com>,
        Kees Cook <keescook@chromium.org>,
        David Rientjes <rientjes@google.com>,
        Cfir Cohen <cfir@google.com>,
        Erdem Aktas <erdemaktas@google.com>,
        Masami Hiramatsu <mhiramat@kernel.org>,
        Mike Stunes <mstunes@vmware.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Martin Radev <martin.b.radev@gmail.com>,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        virtualization@lists.linux-foundation.org
Subject: [PATCH v7 01/72] KVM: SVM: nested: Don't allocate VMCB structures on
 stack
Date: Mon,  7 Sep 2020 15:15:02 +0200
Message-Id: <20200907131613.12703-2-joro@8bytes.org>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <20200907131613.12703-1-joro@8bytes.org>
References: <20200907131613.12703-1-joro@8bytes.org>
MIME-Version: 1.0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Joerg Roedel <jroedel@suse.de>

Do not allocate a vmcb_control_area and a vmcb_save_area on the stack,
as these structures will become larger with future extenstions of
SVM and thus the svm_set_nested_state() function will become a too large
stack frame.

Signed-off-by: Joerg Roedel <jroedel@suse.de>
---
 arch/x86/kvm/svm/nested.c | 47 +++++++++++++++++++++++++++------------
 1 file changed, 33 insertions(+), 14 deletions(-)

```
