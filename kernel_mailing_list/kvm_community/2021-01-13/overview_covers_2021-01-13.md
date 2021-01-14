

#### [PATCH 0/3] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
##### From: Krish Sadhukhan <krish.sadhukhan@oracle.com>

```c
From patchwork Wed Jan 13 02:46:30 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Krish Sadhukhan <krish.sadhukhan@oracle.com>
X-Patchwork-Id: 12015643
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-14.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS,UNPARSEABLE_RELAY,
	USER_AGENT_GIT autolearn=ham autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id 6913FC433E0
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 02:47:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 34DCC207C8
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 02:47:28 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728277AbhAMCr1 (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Tue, 12 Jan 2021 21:47:27 -0500
Received: from aserp2120.oracle.com ([141.146.126.78]:45938 "EHLO
        aserp2120.oracle.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726406AbhAMCr0 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Tue, 12 Jan 2021 21:47:26 -0500
Received: from pps.filterd (aserp2120.oracle.com [127.0.0.1])
        by aserp2120.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10D2iMXY185076;
        Wed, 13 Jan 2021 02:46:42 GMT
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=oracle.com;
 h=from : to : cc :
 subject : date : message-id : mime-version : content-transfer-encoding;
 s=corp-2020-01-29; bh=W7ZvHrqwNaSrlRi/nBaFlLzxuIBB7Lu1nM1UtmASoaI=;
 b=j9+fcXCFA27SEZXRBCz2qBOkUWhH4h/7xzZy2iCDJKcjKEEKqs5p4rOHK5w+LmqYy9Xg
 Er8X0j2SK4PQunwP0XYu13BVkLMfLmRBHwPGMxVhMVI3FWHOK472qTwWFSFd0683u1tF
 lNxwjeLWhjQ1l7aAyUsiRAHxCyWbGPzKhfyvL12d42aF3EGcwIvCfPvTT1hQt3paqCIT
 Xu6ghGglKqmfaC31120XarNukpxtLFJ9j3qqXuMtrCxa4gM6LpGZX5/vqyVfCQyru+Er
 j3vq5TKPZGDnnG6SypikcYU/dwLFoJyCW/sG2/Cp/PTN5recE6SoiHA+VDFSACyp+uNS dg==
Received: from aserp3030.oracle.com (aserp3030.oracle.com [141.146.126.71])
        by aserp2120.oracle.com with ESMTP id 360kcysbt5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 Jan 2021 02:46:42 +0000
Received: from pps.filterd (aserp3030.oracle.com [127.0.0.1])
        by aserp3030.oracle.com (8.16.0.42/8.16.0.42) with SMTP id
 10D2k36t147601;
        Wed, 13 Jan 2021 02:46:42 GMT
Received: from userv0122.oracle.com (userv0122.oracle.com [156.151.31.75])
        by aserp3030.oracle.com with ESMTP id 360keytnkq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 Jan 2021 02:46:42 +0000
Received: from abhmp0002.oracle.com (abhmp0002.oracle.com [141.146.116.8])
        by userv0122.oracle.com (8.14.4/8.14.4) with ESMTP id 10D2kfIq006717;
        Wed, 13 Jan 2021 02:46:41 GMT
Received: from nsvm-sadhukhan.osdevelopmeniad.oraclevcn.com (/100.100.230.216)
        by default (Oracle Beehive Gateway v4.0)
        with ESMTP ; Tue, 12 Jan 2021 18:46:40 -0800
From: Krish Sadhukhan <krish.sadhukhan@oracle.com>
To: kvm@vger.kernel.org
Cc: pbonzini@redhat.com, jmattson@google.com, seanjc@google.com
Subject: [PATCH 0/3] KVM: nSVM: Check addresses of MSR bitmap and IO bitmap
 tables on vmrun of nested guests
Date: Wed, 13 Jan 2021 02:46:30 +0000
Message-Id: <20210113024633.8488-1-krish.sadhukhan@oracle.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9862
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 phishscore=0
 bulkscore=0 malwarescore=0
 suspectscore=0 adultscore=0 spamscore=0 mlxlogscore=999 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2009150000
 definitions=main-2101130014
X-Proofpoint-Virus-Version: vendor=nai engine=6000 definitions=9862
 signatures=668683
X-Proofpoint-Spam-Details: rule=notspam policy=default score=0 spamscore=0
 phishscore=0
 impostorscore=0 bulkscore=0 adultscore=0 suspectscore=0 malwarescore=0
 lowpriorityscore=0 clxscore=1015 mlxlogscore=999 mlxscore=0
 priorityscore=1501 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101130014
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

According to section "Canonicalization and Consistency Checks" in APM vol 2,
the following guest state is illegal:

    "The MSR or IOIO intercept tables extend to a physical address that
     is greater than or equal to the maximum supported physical address."

Patch# 1: Adds the KVM checks.
Patch# 2: Adds a test
Patch# 3: Replaces a hard-coded value with an available macro.


[PATCH 1/3] KVM: nSVM: Check addresses of MSR and IO bitmap
[PATCH 2/3] Test: nSVM: Test MSR and IO bitmap address
[PATCH 3/3] Test: SVM: Use ALIGN macro when aligning 'io_bitmap_area'

 arch/x86/kvm/svm/nested.c | 17 ++++++++++++++---
 1 file changed, 14 insertions(+), 3 deletions(-)

Krish Sadhukhan (1):
      nSVM: Check addresses of MSR and IO bitmap

 x86/svm.c       |  2 +-
 x86/svm_tests.c | 38 ++++++++++++++++++++++++++++++++++++++
 2 files changed, 39 insertions(+), 1 deletion(-)

Krish Sadhukhan (2):
      nSVM: Test MSR and IO bitmap address
      SVM: Use ALIGN macro when aligning 'io_bitmap_area'
```
#### [PATCH 00/14] KVM: s390: Add huge page VSIE support
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
From patchwork Wed Jan 13 09:40:59 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 12016315
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-16.8 required=3.0 tests=BAYES_00,DKIM_SIGNED,
	DKIM_VALID,HEADER_FROM_DIFFERENT_DOMAINS,INCLUDES_PATCH,MAILING_LIST_MULTI,
	MENTIONS_GIT_HOSTING,SPF_HELO_NONE,SPF_PASS,USER_AGENT_GIT autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id B8C71C4321A
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 09:42:43 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 798E8233F8
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 09:42:43 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1727369AbhAMJmX (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 04:42:23 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:41308 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1727031AbhAMJmW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Jan 2021 04:42:22 -0500
Received: from pps.filterd (m0098414.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 10D9XJJG104537;
        Wed, 13 Jan 2021 04:41:41 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : mime-version : content-transfer-encoding; s=pp1;
 bh=UTfW3PlUMvoIPLcnrnxvCiTxzoOlfX2GKTSBqN47GP0=;
 b=fwnzJ1/L8V896/M+qNe5t2iUy86rMlTAWV6Geea4DLlsWZk5935J1JzNu3v7cjGLtJPY
 +Y7ncsgBogJrFhoQag+qL74NpxcNMfuVB3roS91jkEDphf5r9+VTj0bFCpOsf1LiF03j
 WjE+RbYQmu5IIwUDWw2c/n5dIKvCxN3Bo0dFrNHj1vmop5h5IOZAJyexztYV6NM0crxk
 cAbmLvxuIIlkgK4vhLxE9THnwj+Y/zLxSgAbqTP9vHiU2srXJatIkIJS7fm5OeRL7c8w
 JAMA6KpHUc1OdDsemYt7ypZrPjkExa1RvadNY9XRFWXQwPaqj8OQuMNCXkTFZe2G/Gdt Mw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 361wbnt2ac-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 Jan 2021 04:41:41 -0500
Received: from m0098414.ppops.net (m0098414.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 10D9cimc126906;
        Wed, 13 Jan 2021 04:41:40 -0500
Received: from ppma03fra.de.ibm.com (6b.4a.5195.ip4.static.sl-reverse.com
 [149.81.74.107])
        by mx0b-001b2d01.pphosted.com with ESMTP id 361wbnt2a0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 Jan 2021 04:41:40 -0500
Received: from pps.filterd (ppma03fra.de.ibm.com [127.0.0.1])
        by ppma03fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 10D9SL3a022707;
        Wed, 13 Jan 2021 09:41:38 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma03fra.de.ibm.com with ESMTP id 35y448ag56-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Wed, 13 Jan 2021 09:41:38 +0000
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 10D9fZOV31654144
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Wed, 13 Jan 2021 09:41:35 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 4FEA8A4040;
        Wed, 13 Jan 2021 09:41:35 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1DEA1A404D;
        Wed, 13 Jan 2021 09:41:35 +0000 (GMT)
Received: from t46lp67.lnxne.boe (unknown [9.152.108.100])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Wed, 13 Jan 2021 09:41:35 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: borntraeger@de.ibm.com, david@redhat.com,
        linux-s390@vger.kernel.org, imbrenda@linux.ibm.com
Subject: [PATCH 00/14] KVM: s390: Add huge page VSIE support
Date: Wed, 13 Jan 2021 09:40:59 +0000
Message-Id: <20210113094113.133668-1-frankja@linux.ibm.com>
X-Mailer: git-send-email 2.27.0
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.343,18.0.737
 definitions=2021-01-13_03:2021-01-13,2021-01-13 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 clxscore=1011 mlxscore=0 spamscore=0 mlxlogscore=999 phishscore=0
 impostorscore=0 bulkscore=0 suspectscore=0 malwarescore=0 adultscore=0
 lowpriorityscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2009150000 definitions=main-2101130054
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As we finally want to get rid of the nested and hpage s390 KVM module
parameters let's try again to integrate huge page VSIE support.

The following patches have been rebased on 5.11-rc3 and enable us to
start huge page and normal page VSIE guest 3s in a huge page guest 2.

Branch:
https://git.kernel.org/pub/scm/linux/kernel/git/kvms390/linux.git/log/?h=hlp_vsie


Problems that need to be solved:
	* The VSIE guests crash on migration...
	* I have lost most of my knowledge about this topic and I'm
          currently paging back in
	* Lots of testing


Janosch Frank (14):
  s390/mm: Code cleanups
  s390/mm: Improve locking for huge page backings
  s390/mm: Take locking out of gmap_protect_pte
  s390/mm: split huge pages in GMAP when protecting
  s390/mm: Split huge pages when migrating
  s390/mm: Provide vmaddr to pmd notification
  s390/mm: factor out idte global flush into gmap_idte_global
  s390/mm: Make gmap_read_table EDAT1 compatible
  s390/mm: Make gmap_protect_rmap EDAT1 compatible
  s390/mm: Add simple ptep shadow function
  s390/mm: Add gmap shadowing for large pmds
  s390/mm: Add gmap lock classes
  s390/mm: Pull pmd invalid check in gmap_pmd_op_walk
  KVM: s390: Allow the VSIE to be used with huge pages

 Documentation/virt/kvm/api.rst  |   9 +-
 arch/s390/include/asm/gmap.h    |  31 +-
 arch/s390/include/asm/pgtable.h |   5 +
 arch/s390/kvm/gaccess.c         |  52 +-
 arch/s390/kvm/kvm-s390.c        |  14 +-
 arch/s390/mm/gmap.c             | 917 ++++++++++++++++++++++++--------
 arch/s390/mm/pgtable.c          |  61 ++-
 7 files changed, 819 insertions(+), 270 deletions(-)
```
#### [PATCH v2 0/2] ] KVM: SVM: Track physical cpu and asid_generation via
##### From: Cathy Avery <cavery@redhat.com>

```c
From patchwork Wed Jan 13 14:10:17 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Cathy Avery <cavery@redhat.com>
X-Patchwork-Id: 12016885
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS
	autolearn=unavailable autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id A734FC4332D
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 14:12:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7A77323382
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 14:12:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726676AbhAMOMJ (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 09:12:09 -0500
Received: from us-smtp-delivery-124.mimecast.com ([63.128.21.124]:33405 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726618AbhAMOMJ (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Jan 2021 09:12:09 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610547042;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=P+QVIP5CBe/0Vj6KzHneRhHf7M3Qi4BDmgyUB3KmL+k=;
        b=VdHHkccip8Oe85b95w746IKTMsIlhjWcgBJmg003jHaWYqEpb3VIXxGhshZrrqR21irHnv
        TlOX5KTm2CFEoDC/s/ncFRczmjKVKENUo+1dbt3BsxLAX+qKe8ERU4hXjPhQRVcFVW9+nd
        659PinWiWSlWNU4j5l63FNx70fXPq3o=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-230-qnAJmLQsOHyJ8LYym0meCg-1; Wed, 13 Jan 2021 09:10:41 -0500
X-MC-Unique: qnAJmLQsOHyJ8LYym0meCg-1
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id 64AE2B8106;
        Wed, 13 Jan 2021 14:10:20 +0000 (UTC)
Received: from virtlab710.virt.lab.eng.bos.redhat.com
 (virtlab710.virt.lab.eng.bos.redhat.com [10.19.152.252])
        by smtp.corp.redhat.com (Postfix) with ESMTP id C075B60BF1;
        Wed, 13 Jan 2021 14:10:19 +0000 (UTC)
From: Cathy Avery <cavery@redhat.com>
To: linux-kernel@vger.kernel.org, kvm@vger.kernel.org,
        pbonzini@redhat.com
Cc: vkuznets@redhat.com, wei.huang2@amd.com
Subject: [PATCH v2 0/2] ] KVM: SVM: Track physical cpu and asid_generation via
 the vmcb
Date: Wed, 13 Jan 2021 09:10:17 -0500
Message-Id: <20210113141019.5127-1-cavery@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the cases where vmcbs change processors from one vmrun to another updated
information in the vmcb from a prior run can potentially be lost. By tracking
the physical cpu and asid_generation per vmcb instead of svm->vcpu the following
scenario illustrated by Paolo can be avoided.

     ---------------------          ---------------------
     pCPU 1                         pCPU 2
     ---------------------          ---------------------
     run VMCB02
                                    run VMCB02 (*)
                                    run VMCB01
     run VMCB01 (**)
     run VMCB02 (***)
     ---------------------          ---------------------

     After the point marked (*), while L2 runs, some fields change in VMCB02.
     When the processor vmexits back to L0, VMCB02 is marked clean.

     At the point marked (**), svm->vcpu.cpu becomes 1 again.

     Therefore, at the point marked (***) you will get svm->vcpu.cpu == cpu
     and the VMCB02 will not be marked dirty.  The processor can then incorrectly
     use some data that is cached from before point (*).

Theses patches are intended for the kvm nested-svm branch.

The patches have been tested on nested fedora VMs, kvm self tests, and kvm-unit-tests.
They have not been tested on SEV.

Changes v1 -> v2:
- Remove outdated comment from svm_switch_vmcb().

Cathy Avery (2):
  KVM: nSVM: Track the physical cpu of the vmcb vmrun through the vmcb
  KVM: nSVM: Track the ASID generation of the vmcb vmrun through the
    vmcb

 arch/x86/kvm/svm/svm.c | 40 ++++++++++++++++++++--------------------
 arch/x86/kvm/svm/svm.h |  3 ++-
 2 files changed, 22 insertions(+), 21 deletions(-)
```
#### [PATCH 0/7] KVM: x86: Conditional Hyper-V emulation enablement
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
From patchwork Wed Jan 13 14:37:14 2021
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 12016917
Return-Path: <kvm-owner@kernel.org>
X-Spam-Checker-Version: SpamAssassin 3.4.0 (2014-02-07) on
	aws-us-west-2-korg-lkml-1.web.codeaurora.org
X-Spam-Level: 
X-Spam-Status: No, score=-11.0 required=3.0 tests=BAYES_00,DKIMWL_WL_HIGH,
	DKIM_SIGNED,DKIM_VALID,DKIM_VALID_AU,HEADER_FROM_DIFFERENT_DOMAINS,
	INCLUDES_PATCH,MAILING_LIST_MULTI,SPF_HELO_NONE,SPF_PASS autolearn=ham
	autolearn_force=no version=3.4.0
Received: from mail.kernel.org (mail.kernel.org [198.145.29.99])
	by smtp.lore.kernel.org (Postfix) with ESMTP id BFC9CC433DB
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 14:38:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 717A923436
	for <kvm@archiver.kernel.org>; Wed, 13 Jan 2021 14:38:56 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725912AbhAMOiz (ORCPT <rfc822;kvm@archiver.kernel.org>);
        Wed, 13 Jan 2021 09:38:55 -0500
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:53712 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725747AbhAMOiy (ORCPT
        <rfc822;kvm@vger.kernel.org>); Wed, 13 Jan 2021 09:38:54 -0500
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1610548648;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=1oISxi4cwAd1j9TwXCFVU/K5vT9SVgURCoIs14qvGh0=;
        b=UAuUcYgKJRiQgF72o8Lufe5HewGzfxa8LuvxMk15jy3A4CuPdinVpjYHNXgzLco8E5SRDp
        0LKOFw9XVnHS2e5E3SpVGGzOTLUX6+b71sWOzlMSAQ1Z5knF94VToGR4cOmvSBn+jC729y
        8J1jZ3oIm6VTgQStqwYkSPbxV7Ywokw=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-235-FAIIWUrJMuOmrVxrirW_RQ-1; Wed, 13 Jan 2021 09:37:27 -0500
X-MC-Unique: FAIIWUrJMuOmrVxrirW_RQ-1
Received: from smtp.corp.redhat.com (int-mx06.intmail.prod.int.phx2.redhat.com
 [10.5.11.16])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id C14A8C7400;
        Wed, 13 Jan 2021 14:37:24 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.193.20])
        by smtp.corp.redhat.com (Postfix) with ESMTP id E51F674AA0;
        Wed, 13 Jan 2021 14:37:22 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>
Cc: Sean Christopherson <seanjc@google.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Jim Mattson <jmattson@google.com>
Subject: [PATCH 0/7] KVM: x86: Conditional Hyper-V emulation enablement
Date: Wed, 13 Jan 2021 15:37:14 +0100
Message-Id: <20210113143721.328594-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.16
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Hyper-V emulation is enabled in KVM unconditionally even for Linux guests.
This is bad at least from security standpoint as it is an extra attack
surface. Ideally, there should be a per-VM capability explicitly enabled by
VMM but currently it is not the case and we can't mandate one without
breaking backwards compatibility. We can, however, check guest visible CPUIDs
and only enable Hyper-V emulation when "Hv#1" interface was exposed in
HYPERV_CPUID_INTERFACE.
 
Also (and while on it) per-vcpu Hyper-V context ('struct kvm_vcpu_hv') is
currently part of 'struct kvm_vcpu_arch' and thus allocated unconditionally
for each vCPU. The context, however, quite big and accounts for more than
1/4 of 'struct kvm_vcpu_arch' (e.g. 2912/9512 bytes). Switch to allocating
it dynamically. This may come handy if we ever decide to raise KVM_MAX_VCPUS
(and rumor has it some downstream distributions already have more than '288')

Vitaly Kuznetsov (7):
  selftests: kvm: Move kvm_get_supported_hv_cpuid() to common code
  selftests: kvm: Properly set Hyper-V CPUIDs in evmcs_test
  KVM: x86: hyper-v: Always use vcpu_to_hv_vcpu() accessor to get to
    'struct kvm_vcpu_hv'
  KVM: x86: hyper-v: Prepare to meet unallocated Hyper-V context
  KVM: x86: hyper-v: Allocate 'struct kvm_vcpu_hv' dynamically
  KVM: x86: hyper-v: Make Hyper-V emulation enablement conditional
  KVM: x86: hyper-v: Allocate Hyper-V context lazily

 arch/x86/include/asm/kvm_host.h               |   4 +-
 arch/x86/kvm/cpuid.c                          |   2 +
 arch/x86/kvm/hyperv.c                         | 104 +++++++++++++-----
 arch/x86/kvm/hyperv.h                         |  30 +++--
 arch/x86/kvm/lapic.c                          |   6 +-
 arch/x86/kvm/lapic.h                          |   6 +-
 arch/x86/kvm/vmx/vmx.c                        |   7 +-
 arch/x86/kvm/x86.c                            |  17 +--
 .../selftests/kvm/include/x86_64/processor.h  |   3 +
 .../selftests/kvm/lib/x86_64/processor.c      |  33 ++++++
 .../testing/selftests/kvm/x86_64/evmcs_test.c |  39 ++++++-
 .../selftests/kvm/x86_64/hyperv_cpuid.c       |  31 +-----
 12 files changed, 203 insertions(+), 79 deletions(-)
```
