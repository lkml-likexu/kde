

#### [PATCH 0/2 v5] KVM: nSVM: Check reserved values for 'Type' and
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Sat Dec 12 00:50:17 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 11969783
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-13.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 12B77C4361B
	for <kvm@archiver.kernel.org>; Sat, 12 Dec 2020 00:57:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id D4AA92336F
	for <kvm@archiver.kernel.org>; Sat, 12 Dec 2020 00:57:11 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2437960AbgLLAvN (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Fri, 11 Dec 2020 19:51:13 -0500
Received: from aserp2130.oracle.com ([141.146.126.79]:42106 "EHLO
        aserp2130.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2437958AbgLLAvM (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 11 Dec 2020 19:51:12 -0500
Received: from pps.filterd (aserp2130.oracle.com [127.0.0.1])
        by aserp2130.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0BC0niHA166558;
        Sat, 12 Dec 2020 00:50:28 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=igKxMZyLu4/sV0lA9v0QTSehubi/Tj7ZO0Kl+RVJikM=;
 b=xPzhO1XEw7PcZ6c+gUdIiCgLy+IwCDx/t0OfQMKKpNfeBD09IewqPzBJIQWZ3eDMyJ+M
 4NbSBj3wX710kyyHgNKTmIdyWdOqGTZCsxb+/CityEMDCN1R++NbN8VnyA3mgg/HMFbI
 ZKbirmauk10hnAOJNr9849sUima9IcE+B//VBeBurBr87KuENXWJpaxnci3ExjtEvmHy
 iHTzc3+Yyk+DbC55F59S1hTaUPplTjOATkxsXQEKZhKYBwNtnzKWYOgjznkQHDp2ztFB
 CzCrhtT1PFy1iecR4oD+piSLwcTWQt0EBVkBYVz5wE2lWnRq9w/racY4+waegT+adxWM 6Q==
Received: from userp3030.oracle.com (userp3030.oracle.com [156.151.31.80])
        by aserp2130.oracle.com with ESMTP id 35ckcb00ve-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=FAIL);
        Sat, 12 Dec 2020 00:50:28 +0000
Received: from pps.filterd (userp3030.oracle.com [127.0.0.1])
        by userp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 0BC0nsC3099681;
        Sat, 12 Dec 2020 00:50:27 GMT
Received: from aserv0121.oracle.com (aserv0121.oracle.com [141.146.126.235])
        by userp3030.oracle.com with ESMTP id 35cjyqsb5f-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 12 Dec 2020 00:50:27 +0000
Received: from abhmp0019.oracle.com (abhmp0019.oracle.com [141.146.116.25])
        by aserv0121.oracle.com (8.14.4/8.13.8) with ESMTP id 0BC0oQCi028640;
        Sat, 12 Dec 2020 00:50:26 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Fri, 11 Dec 2020 16:50:26 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, seanjc@google.com, jmattson@google.com
Subject: [PATCH 0/2 v5] KVM: nSVM: Check reserved values for 'Type' and
 invalid vectors in EVENTINJ
Date: Sat, 12 Dec 2020 00:50:17 +0000
Message-Id: <20201212005019.6807-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9832
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 mlxlogscore=769
 malwarescore=0
 phishscore=0 suspectscore=0 mlxscore=0 bulkscore=0 spamscore=0
 adultscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012120004
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9832
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 bulkscore=0
 mlxlogscore=783
 priorityscore=1501 mlxscore=0 suspectscore=0 adultscore=0 phishscore=0
 malwarescore=0 impostorscore=0 lowpriorityscore=0 clxscore=1015
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2012120004
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

v4 -> v5:
	1. In patch# 1, the storage for the 'type' variable has been changed
	   back to u32.
	2. In patch# 1, the two 'if' conditions in the second check have been
	   merged into one.


[PATCH 1/2 v5] KVM: nSVM: Check reserved values for 'Type' and invalid
[PATCH 2/2 v5] nSVM: Test reserved values for 'Type' and invalid vectors in

 arch/x86/include/asm/svm.h |  4 ++++
 arch/x86/kvm/svm/nested.c  | 15 +++++++++++++++
 2 files changed, 19 insertions(+)

Krish Sadhukhan (1):
      KVM: nSVM: Check reserved values for 'Type' and invalid vectors in EVENTINJ

 x86/svm_tests.c | 38 ++++++++++++++++++++++++++++++++++++++
 1 file changed, 38 insertions(+)

Krish Sadhukhan (1):
      nSVM: Test reserved values for 'Type' and invalid vectors in EVENTINJ
```
#### [PATCH 0/9] KVM/ARM: Some vgic fixes and init sequence KVM selftests
##### From: Eric Auger <eric.auger@redhat.com>

```c
From patchwork Sat Dec 12 18:50:01 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Eric Auger <eric.auger@redhat.com>
X-Patchwork-Id: 11970319
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id AD76AC4361B
	for <kvm@archiver.kernel.org>; Sat, 12 Dec 2020 18:52:12 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 768A7207B0
	for <kvm@archiver.kernel.org>; Sat, 12 Dec 2020 18:52:12 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2407704AbgLLSv4 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Sat, 12 Dec 2020 13:51:56 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:50169 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726167AbgLLSv4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 12 Dec 2020 13:51:56 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1607799029;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=+8PgvJ932tyD+kO+UM8no2CrJ/budWb9RkQW3XvAXW0=;
        b=YTBz67tS3WZyrosk8S0kfB68Unl9Ul6S7aGh9SsQzHmE9Psnwh/4ShiM3gC6rzhSGDaKkp
        +JeBJyQ0zQxB5SO/Z3iF6KpYG1R3UQoYi9sdtXpXtfUXaDkYy3MmmAmWFSygXrTlkDP44H
        cZgII/C9ZUoEqGllAl77a5yZ4tF7BIQ=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-577-UfkopIKKNhqhAsb6XnWmPQ-1; Sat, 12 Dec 2020 13:50:27 -0500
X-MC-Unique: UfkopIKKNhqhAsb6XnWmPQ-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id E2716180A087;
        Sat, 12 Dec 2020 18:50:25 +0000 (UTC)
Received: from laptop.redhat.com (ovpn-115-41.ams2.redhat.com [10.36.115.41])
        by smtp.corp.redhat.com (Postfix) with ESMTP id B91CC1F45B;
        Sat, 12 Dec 2020 18:50:19 +0000 (UTC)
From: Eric Auger <eric.auger@redhat.com>
To: eric.auger.pro@gmail.com, eric.auger@redhat.com,
        linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        kvmarm@lists.cs.columbia.edu, maz@kernel.org, drjones@redhat.com
Cc: alexandru.elisei@arm.com, james.morse@arm.com,
        julien.thierry.kdev@gmail.com, suzuki.poulose@arm.com,
        shuah@kernel.org, pbonzini@redhat.com
Subject: [PATCH 0/9] KVM/ARM: Some vgic fixes and init sequence KVM selftests
Date: Sat, 12 Dec 2020 19:50:01 +0100
Message-Id: <20201212185010.26579-1-eric.auger@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

While writting vgic v3 init sequence KVM selftests I noticed some
relatively minor issues. This was also the opportunity to try to
fix the issue laterly reported by Zenghui, related to the RDIST_TYPER
last bit emulation. The final patch is a first batch of VGIC init
sequence selftests. Of course they can be augmented with a lot more
register access tests, but let's try to move forward incrementally ...

Best Regards

Eric

This series can be found at:
https://github.com/eauger/linux/tree/vgic-selftests-and-fixes-v1

Eric Auger (9):
  KVM: arm64: vgic-v3: Fix some error codes when setting RDIST base
  KVM: arm64: Fix KVM_VGIC_V3_ADDR_TYPE_REDIST_REGION read
  KVM: arm64: vgic-v3: Fix error handling in vgic_v3_set_redist_base()
  KVM: arm/arm64: vgic: Reset base address on kvm_vgic_dist_destroy()
  KVM: arm: move has_run_once after the map_resources
  docs: kvm: devices/arm-vgic-v3: enhance KVM_DEV_ARM_VGIC_CTRL_INIT doc
  KVM: arm64: Simplify argument passing to vgic_uaccess_[read|write]
  KVM: arm64: vgic-v3: Expose GICR_TYPER.Last for userspace
  KVM: selftests: aarch64/vgic-v3 init sequence tests

 .../virt/kvm/devices/arm-vgic-v3.rst          |   2 +-
 arch/arm64/kvm/arm.c                          |   4 +-
 arch/arm64/kvm/vgic/vgic-init.c               |   7 +-
 arch/arm64/kvm/vgic/vgic-kvm-device.c         |   3 +
 arch/arm64/kvm/vgic/vgic-mmio-v3.c            |  24 +-
 arch/arm64/kvm/vgic/vgic-mmio.c               |  10 +-
 include/kvm/arm_vgic.h                        |   1 +
 tools/testing/selftests/kvm/Makefile          |   1 +
 .../testing/selftests/kvm/aarch64/vgic_init.c | 453 ++++++++++++++++++
 .../testing/selftests/kvm/include/kvm_util.h  |   5 +
 tools/testing/selftests/kvm/lib/kvm_util.c    |  51 ++
 11 files changed, 546 insertions(+), 15 deletions(-)
 create mode 100644 tools/testing/selftests/kvm/aarch64/vgic_init.c
```
