#### [PATCH v2 1/1] s390/vfio-ap: fix circular lockdep when setting/clearing crypto masks
##### From: Tony Krowiak <akrowiak@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tony Krowiak <akrowiak@linux.ibm.com>
X-Patchwork-Id: 12089327
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CAAC2C433E0
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 01:16:59 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7D87664DAF
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 01:16:59 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229811AbhBPBQm (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Feb 2021 20:16:42 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:32442 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S229497AbhBPBQl (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 15 Feb 2021 20:16:41 -0500
Received: from pps.filterd (m0098419.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 11G1BhFd093422;
        Mon, 15 Feb 2021 20:15:57 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=2zmfOkwHspTC+4nneis9TIZfAG6p6yIf3vHNJZAKKNw=;
 b=huRpHfJIwnztssJv8WW2ZBPY7rnG8nviI7Bk3KvYmW7x4aotNIrhptZVbDV4l+9uM2cf
 nhuVxx8ieohKDlx9z1XhDhhVsAwFt0AtZe7cSnKlQBYM8pqp/62+1ycLQ1YlTyqr9Z/3
 uYsGRbAB4+yT9IPPAyQ3FUZw1GKVgsRemDZ5b1jXDkFXVTU7VnZFxUTue77S7/DXmZtP
 87jVrZvzE1lD6TFw01kUh8r06rip/wgpm8/CIW00KBeZrKKWqSQnWPfeR7XoRjxqpkf6
 aQSvk7JvtNXf6gxlqbZ5tKhUA5a2pf4YmfrH3NNQDKoSN1NbG+jH8ThfMeU3qEgksqrl 9g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36r45sr2rc-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Feb 2021 20:15:57 -0500
Received: from m0098419.ppops.net (m0098419.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 11G1D40q100022;
        Mon, 15 Feb 2021 20:15:57 -0500
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0b-001b2d01.pphosted.com with ESMTP id 36r45sr2r3-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 15 Feb 2021 20:15:57 -0500
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 11G1CYnC020662;
        Tue, 16 Feb 2021 01:15:56 GMT
Received: from b01cxnp22033.gho.pok.ibm.com (b01cxnp22033.gho.pok.ibm.com
 [9.57.198.23])
        by ppma02dal.us.ibm.com with ESMTP id 36p6d9fmww-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Tue, 16 Feb 2021 01:15:56 +0000
Received: from b01ledav001.gho.pok.ibm.com (b01ledav001.gho.pok.ibm.com
 [9.57.199.106])
        by b01cxnp22033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 11G1Ftc933358314
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Tue, 16 Feb 2021 01:15:55 GMT
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 76EDC28059;
        Tue, 16 Feb 2021 01:15:55 +0000 (GMT)
Received: from b01ledav001.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CDAFD28058;
        Tue, 16 Feb 2021 01:15:54 +0000 (GMT)
Received: from cpe-66-24-58-13.stny.res.rr.com.com (unknown [9.85.203.235])
        by b01ledav001.gho.pok.ibm.com (Postfix) with ESMTP;
        Tue, 16 Feb 2021 01:15:54 +0000 (GMT)
From: Tony Krowiak <akrowiak@linux.ibm.com>
To: linux-s390@vger.kernel.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org
Cc: stable@vger.kernel.org, borntraeger@de.ibm.com, cohuck@redhat.com,
        kwankhede@nvidia.com, pbonzini@redhat.com,
        alex.williamson@redhat.com, pasic@linux.vnet.ibm.com,
        Tony Krowiak <akrowiak@linux.ibm.com>
Subject: [PATCH v2 1/1] s390/vfio-ap: fix circular lockdep when
 setting/clearing crypto masks
Date: Mon, 15 Feb 2021 20:15:47 -0500
Message-Id: <20210216011547.22277-2-akrowiak@linux.ibm.com>
X-Mailer: git-send-email 2.21.1
In-Reply-To: <20210216011547.22277-1-akrowiak@linux.ibm.com>
References: <20210216011547.22277-1-akrowiak@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.369,18.0.761
 definitions=2021-02-15_16:2021-02-12,2021-02-15 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 adultscore=0 priorityscore=1501 malwarescore=0 mlxlogscore=999 mlxscore=0
 phishscore=0 impostorscore=0 suspectscore=0 bulkscore=0 clxscore=1015
 spamscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2102160003
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This patch fixes a circular locking dependency in the CI introduced by
commit f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM
pointer invalidated"). The lockdep only occurs when starting a Secure
Execution guest. Crypto virtualization (vfio_ap) is not yet supported for
SE guests; however, in order to avoid CI errors, this fix is being
provided.

The circular lockdep was introduced when the masks in the guest's APCB
were taken under the matrix_dev->lock. While the lock is definitely
needed to protect the setting/unsetting of the KVM pointer, it is not
necessarily critical for setting the masks, so this will not be done under
protection of the matrix_dev->lock.

Fixes: f21916ec4826 ("s390/vfio-ap: clean up vfio_ap resources when KVM pointer invalidated")
Cc: stable@vger.kernel.org
Signed-off-by: Tony Krowiak <akrowiak@linux.ibm.com>
---
 drivers/s390/crypto/vfio_ap_ops.c | 119 +++++++++++++++++++++---------
 1 file changed, 84 insertions(+), 35 deletions(-)

```
#### [RFC PATCH 01/23] target/i386: Expose x86_cpu_get_supported_feature_word() for TDX
##### From: Isaku Yamahata <isaku.yamahata@intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Isaku Yamahata <isaku.yamahata@intel.com>
X-Patchwork-Id: 12089421
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,
	HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_CR_TRAILER,INCLUDES_PATCH,
	MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,URIBL_BLOCKED,USER_AGENT_GIT
	autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id C58C6C433DB
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 02:16:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 9C61964DF0
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 02:16:07 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S229807AbhBPCQF (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Mon, 15 Feb 2021 21:16:05 -0500
Received: from mga06.intel.com ([134.134.136.31]:39370 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S229912AbhBPCPy (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 15 Feb 2021 21:15:54 -0500
IronPort-SDR: 
 DZFrCxXJs72A1do3ciVcgfv+SjtomPHFFjDsGAjo2hnNn5wgbXBYyCiCZXeMDVgoT8R9CGS9av
 z3bI6GLh04uQ==
X-IronPort-AV: E=McAfee;i="6000,8403,9896"; a="244270194"
X-IronPort-AV: E=Sophos;i="5.81,182,1610438400";
   d="scan'208";a="244270194"
Received: from fmsmga005.fm.intel.com ([10.253.24.32])
  by orsmga104.jf.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Feb 2021 18:14:50 -0800
IronPort-SDR: 
 BJ3gNTgiWLJnlFPV3wYnA31/SdKC5ZlJvs2lJHh+FIN+u4RmZgSORWxYKOdFF/KvHziTN38xa7
 fSJ9YSdH/zJg==
X-IronPort-AV: E=Sophos;i="5.81,182,1610438400";
   d="scan'208";a="591705383"
Received: from ls.sc.intel.com (HELO localhost) ([143.183.96.54])
  by fmsmga005-auth.fm.intel.com with ESMTP/TLS/ECDHE-RSA-AES256-GCM-SHA384;
 15 Feb 2021 18:14:50 -0800
From: Isaku Yamahata <isaku.yamahata@intel.com>
To: qemu-devel@nongnu.org, pbonzini@redhat.com, alistair@alistair23.me,
        ehabkost@redhat.com, marcel.apfelbaum@gmail.com, mst@redhat.com,
        cohuck@redhat.com, mtosatti@redhat.com, xiaoyao.li@intel.com,
        seanjc@google.com
Cc: kvm@vger.kernel.org, isaku.yamahata@gmail.com,
        isaku.yamahata@intel.com,
        Sean Christopherson <sean.j.christopherson@intel.com>
Subject: [RFC PATCH 01/23] target/i386: Expose
 x86_cpu_get_supported_feature_word() for TDX
Date: Mon, 15 Feb 2021 18:12:57 -0800
Message-Id: 
 <c77664a9e03d53ed870635064551caa663b3dfc4.1613188118.git.isaku.yamahata@intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <cover.1613188118.git.isaku.yamahata@intel.com>
References: <cover.1613188118.git.isaku.yamahata@intel.com>
In-Reply-To: <cover.1613188118.git.isaku.yamahata@intel.com>
References: <cover.1613188118.git.isaku.yamahata@intel.com>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Sean Christopherson <sean.j.christopherson@intel.com>

Expose x86_cpu_get_supported_feature_word() outside of cpu.c so that it
can be used by TDX to setup the VM-wide CPUID configuration.

Signed-off-by: Sean Christopherson <sean.j.christopherson@intel.com>
Reviewed-by: Philippe Mathieu-Daudé <philmd@redhat.com>
---
 target/i386/cpu.c | 4 ++--
 target/i386/cpu.h | 3 +++
 2 files changed, 5 insertions(+), 2 deletions(-)

```
#### [PATCH v2] vfio/type1: Use follow_pte()From: Alex Williamson <alex.williamson@redhat.com>
##### From: Alex Williamson <alex.williamson@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alex Williamson <alex.williamson@redhat.com>
X-Patchwork-Id: 12090705
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,
	URIBL_BLOCKED autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 55506C433DB
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 22:51:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1833264E79
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 22:51:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S231300AbhBPWvL (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Feb 2021 17:51:11 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:45750 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230477AbhBPWvK (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Feb 2021 17:51:10 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613515784;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:content-type:content-type:
         content-transfer-encoding:content-transfer-encoding;
        bh=TatDQ+EGIrCOoR5SAERr+J/vDI7pt6Z6c0khRs5KElQ=;
        b=LYXIJEPtKOPY0NSJgVXVs/N3qPUoOyXm1pE4U1CAt4LB+imiVhoSgxR5W+HnhFe8ORp8gK
        3VySS3/ej9xnU4xQQae+BAYuhhvRTilJOcd8XTrfvqA67WiYn288OrxfmYaEpjNxoRcY+Y
        cIP99N32V4dplBRDErXX2nA8OICGTMo=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-562-2HtE5Td1M_Cd317-Aw3xtw-1; Tue, 16 Feb 2021 17:49:42 -0500
X-MC-Unique: 2HtE5Td1M_Cd317-Aw3xtw-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id AE77D1E563;
        Tue, 16 Feb 2021 22:49:41 +0000 (UTC)
Received: from gimli.home (ovpn-112-255.phx2.redhat.com [10.3.112.255])
        by smtp.corp.redhat.com (Postfix) with ESMTP id D274960C5F;
        Tue, 16 Feb 2021 22:49:34 +0000 (UTC)
Subject: [PATCH v2] vfio/type1: Use follow_pte()
From: Alex Williamson <alex.williamson@redhat.com>
To: alex.williamson@redhat.com
Cc: cohuck@redhat.com, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, pbonzini@redhat.com, jgg@nvidia.com,
        peterx@redhat.com
Date: Tue, 16 Feb 2021 15:49:34 -0700
Message-ID: <161351571186.15573.5602248562129684350.stgit@gimli.home>
User-Agent: StGit/0.21-dirty
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

follow_pfn() doesn't make sure that we're using the correct page
protections, get the pte with follow_pte() so that we can test
protections and get the pfn from the pte.

Fixes: 5cbf3264bc71 ("vfio/type1: Fix VA->PA translation for PFNMAP VMAs in vaddr_get_pfn()")
Reviewed-by: Jason Gunthorpe <jgg@nvidia.com>
Reviewed-by: Cornelia Huck <cohuck@redhat.com>
Signed-off-by: Alex Williamson <alex.williamson@redhat.com>
---

v2: Update to current follow_pte() API, add Reviews

 drivers/vfio/vfio_iommu_type1.c |   14 ++++++++++++--
 1 file changed, 12 insertions(+), 2 deletions(-)

```
#### [PATCH v2] virtio/s390: implement virtio-ccw revision 2 correctly
##### From: Cornelia Huck <cohuck@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cornelia Huck <cohuck@redhat.com>
X-Patchwork-Id: 12089829
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 50A8DC433DB
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 11:09:19 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1A3AA64DF0
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 11:09:19 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230158AbhBPLJD (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Feb 2021 06:09:03 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:36759 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S230000AbhBPLIU (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Feb 2021 06:08:20 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613473614;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=IpPnQESKftP4YmMf+TpJQvg8smPe15Q/eS96QieNViM=;
        b=d2duA8GUjYgHLclbFEwC+hB+E8rdlWrZ8piRfI5P50IdsBcgC+AO7HccBRogaRYeHniX0A
        1No3OPNEMQuzStv0c1ygGtFBhrNvbyKvEo593nIQchZciaA3+KJ6z7Lsow08ek6IgG0SY6
        wyrsMrXfRnMPPB4dIb1RMhVI1cdxRU4=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-581-ib7Oj_NUMRODwPrYhZOZvA-1; Tue, 16 Feb 2021 06:06:52 -0500
X-MC-Unique: ib7Oj_NUMRODwPrYhZOZvA-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 06BF3107ACF7;
        Tue, 16 Feb 2021 11:06:51 +0000 (UTC)
Received: from gondolin.redhat.com (ovpn-113-145.ams2.redhat.com
 [10.36.113.145])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 727F45D9CC;
        Tue, 16 Feb 2021 11:06:49 +0000 (UTC)
From: Cornelia Huck <cohuck@redhat.com>
To: Halil Pasic <pasic@linux.ibm.com>
Cc: Pierre Morel <pmorel@linux.ibm.com>, linux-s390@vger.kernel.org,
        virtualization@lists.linux-foundation.org, kvm@vger.kernel.org,
        Cornelia Huck <cohuck@redhat.com>, stable@vger.kernel.org
Subject: [PATCH v2] virtio/s390: implement virtio-ccw revision 2 correctly
Date: Tue, 16 Feb 2021 12:06:45 +0100
Message-Id: <20210216110645.1087321-1-cohuck@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

CCW_CMD_READ_STATUS was introduced with revision 2 of virtio-ccw,
and drivers should only rely on it being implemented when they
negotiated at least that revision with the device.

However, virtio_ccw_get_status() issued READ_STATUS for any
device operating at least at revision 1. If the device accepts
READ_STATUS regardless of the negotiated revision (which some
implementations like QEMU do, even though the spec currently does
not allow it), everything works as intended. While a device
rejecting the command should also be handled gracefully, we will
not be able to see any changes the device makes to the status,
such as setting NEEDS_RESET or setting the status to zero after
a completed reset.

We negotiated the revision to at most 1, as we never bumped the
maximum revision; let's do that now and properly send READ_STATUS
only if we are operating at least at revision 2.

Cc: stable@vger.kernel.org
Fixes: 7d3ce5ab9430 ("virtio/s390: support READ_STATUS command for virtio-ccw")
Reviewed-by: Halil Pasic <pasic@linux.ibm.com>
Signed-off-by: Cornelia Huck <cohuck@redhat.com>
---

v1->v2:
  tweak patch description and cc:stable

---
 drivers/s390/virtio/virtio_ccw.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [RFC PATCH 01/10] vdpa: add get_config_size callback in vdpa_config_ops
##### From: Stefano Garzarella <sgarzare@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Stefano Garzarella <sgarzare@redhat.com>
X-Patchwork-Id: 12089709
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-15.8 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_CR_TRAILER,INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id CF5CDC433E0
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 09:46:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 976C764DDA
	for <kvm@archiver.kernel.org>; Tue, 16 Feb 2021 09:46:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S230014AbhBPJqu (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 16 Feb 2021 04:46:50 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:33576 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S229923AbhBPJqh (ORCPT
        <rfc822;kvm@vger.kernel.org>); Tue, 16 Feb 2021 04:46:37 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1613468711;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding:
         in-reply-to:in-reply-to:references:references;
        bh=DCpAAD0R3f5DpHYdniOmpnpZ0gH4EPVC6kj5APUQyNw=;
        b=ZERLiRIaklb9TzbbDmWFdbD0eGRfnqBXNmfnoL9cq+Xmla/0WUC/igKMpiGRKoi3E9LT5f
        3Ye6MMMFndvpgHelPFbG5S4NZJGnvAtyfbNQ9wbDGs0YNjW+DPygk4v2aohysEEGQzSboU
        zPjQi7nUSYEE8bV9/28ETIJugaSK8zU=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-252-Hw12bHLRO-2iSN7t9QeHiw-1; Tue, 16 Feb 2021 04:45:07 -0500
X-MC-Unique: Hw12bHLRO-2iSN7t9QeHiw-1
Received: from smtp.corp.redhat.com (int-mx04.intmail.prod.int.phx2.redhat.com
 [10.5.11.14])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 95A9D801965;
        Tue, 16 Feb 2021 09:45:06 +0000 (UTC)
Received: from steredhat.redhat.com (ovpn-113-212.ams2.redhat.com
 [10.36.113.212])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 609555D9C0;
        Tue, 16 Feb 2021 09:45:03 +0000 (UTC)
From: Stefano Garzarella <sgarzare@redhat.com>
To: virtualization@lists.linux-foundation.org
Cc: kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        "Michael S. Tsirkin" <mst@redhat.com>,
        Jason Wang <jasowang@redhat.com>
Subject: [RFC PATCH 01/10] vdpa: add get_config_size callback in
 vdpa_config_ops
Date: Tue, 16 Feb 2021 10:44:45 +0100
Message-Id: <20210216094454.82106-2-sgarzare@redhat.com>
In-Reply-To: <20210216094454.82106-1-sgarzare@redhat.com>
References: <20210216094454.82106-1-sgarzare@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.14
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

This new callback is used to get the size of the configuration space
of vDPA devices.

Signed-off-by: Stefano Garzarella <sgarzare@redhat.com>
---
 include/linux/vdpa.h              | 4 ++++
 drivers/vdpa/ifcvf/ifcvf_main.c   | 6 ++++++
 drivers/vdpa/mlx5/net/mlx5_vnet.c | 6 ++++++
 drivers/vdpa/vdpa_sim/vdpa_sim.c  | 9 +++++++++
 4 files changed, 25 insertions(+)

```
