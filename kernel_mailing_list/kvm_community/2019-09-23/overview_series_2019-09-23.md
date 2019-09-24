#### [PATCH 1/1] powerpc: kvm: Reduce calls to get current->mm by storing the value locally
##### From: Leonardo Bras <leonardo@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Leonardo Bras <leonardo@linux.ibm.com>
X-Patchwork-Id: 11157675
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3A7561668
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 21:30:58 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1834B206C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 21:30:58 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2389673AbfIWVay (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 17:30:54 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:49972 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1732345AbfIWVay (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 23 Sep 2019 17:30:54 -0400
Received: from pps.filterd (m0098410.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8NLN3AP091077;
        Mon, 23 Sep 2019 17:30:42 -0400
Received: from ppma04dal.us.ibm.com (7a.29.35a9.ip4.static.sl-reverse.com
 [169.53.41.122])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2v740wkjnj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 23 Sep 2019 17:30:42 -0400
Received: from pps.filterd (ppma04dal.us.ibm.com [127.0.0.1])
        by ppma04dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 x8NLPiYH027618;
        Mon, 23 Sep 2019 21:30:41 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma04dal.us.ibm.com with ESMTP id 2v5bg74hy0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 23 Sep 2019 21:30:41 +0000
Received: from b03ledav006.gho.boulder.ibm.com
 (b03ledav006.gho.boulder.ibm.com [9.17.130.237])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8NLUdXr30015898
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 23 Sep 2019 21:30:40 GMT
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C75A8C6059;
        Mon, 23 Sep 2019 21:30:39 +0000 (GMT)
Received: from b03ledav006.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 2C759C6057;
        Mon, 23 Sep 2019 21:30:38 +0000 (GMT)
Received: from LeoBras.aus.stglabs.ibm.com (unknown [9.18.235.184])
        by b03ledav006.gho.boulder.ibm.com (Postfix) with ESMTP;
        Mon, 23 Sep 2019 21:30:37 +0000 (GMT)
From: Leonardo Bras <leonardo@linux.ibm.com>
To: linuxppc-dev@lists.ozlabs.org, linux-kernel@vger.kernel.org,
        kvm@vger.kernel.org, kvm-ppc@vger.kernel.org
Cc: Leonardo Bras <leonardo@linux.ibm.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Michael Ellerman <mpe@ellerman.id.au>
Subject: [PATCH 1/1] powerpc: kvm: Reduce calls to get current->mm by storing
 the value locally
Date: Mon, 23 Sep 2019 18:30:23 -0300
Message-Id: <20190923213022.7740-1-leonardo@linux.ibm.com>
X-Mailer: git-send-email 2.20.1
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-23_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=0 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=351 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909230179
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Reduces the number of calls to get_current() in order to get the value of
current->mm by doing it once and storing the value, since it is not
supposed to change inside the same process).

Signed-off-by: Leonardo Bras <leonardo@linux.ibm.com>
---
Re-sending to all lists involved. (I missed kvm ones)

 arch/powerpc/kvm/book3s_64_mmu_hv.c | 11 ++++++-----
 1 file changed, 6 insertions(+), 5 deletions(-)

```
#### [PATCH kvmtool 01/16] arm: Allow use of hugepage with 16K pagesize host
##### From: Alexandru Elisei <alexandru.elisei@arm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexandru Elisei <alexandru.elisei@arm.com>
X-Patchwork-Id: 11156913
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C597514ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 13:35:39 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AF67820882
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 13:35:39 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2408098AbfIWNfi (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 09:35:38 -0400
Received: from foss.arm.com ([217.140.110.172]:42284 "EHLO foss.arm.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S2404581AbfIWNfi (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Sep 2019 09:35:38 -0400
Received: from usa-sjc-imap-foss1.foss.arm.com (unknown [10.121.207.14])
        by usa-sjc-mx-foss1.foss.arm.com (Postfix) with ESMTP id 36AE81576;
        Mon, 23 Sep 2019 06:35:38 -0700 (PDT)
Received: from e121566-lin.cambridge.arm.com (e121566-lin.cambridge.arm.com
 [10.1.196.217])
        by usa-sjc-imap-foss1.foss.arm.com (Postfix) with ESMTPA id
 F0E783F694;
        Mon, 23 Sep 2019 06:35:36 -0700 (PDT)
From: Alexandru Elisei <alexandru.elisei@arm.com>
To: kvm@vger.kernel.org, will@kernel.org, julien.thierry.kdev@gmail.com
Cc: maz@kernel.org, suzuki.poulose@arm.com, julien.grall@arm.com,
        andre.przywara@arm.com, Marc Zyngier <marc.zyngier@arm.com>,
        Will Deacon <will.deacon@arm.com>
Subject: [PATCH kvmtool 01/16] arm: Allow use of hugepage with 16K pagesize
 host
Date: Mon, 23 Sep 2019 14:35:07 +0100
Message-Id: <1569245722-23375-2-git-send-email-alexandru.elisei@arm.com>
X-Mailer: git-send-email 2.7.4
In-Reply-To: <1569245722-23375-1-git-send-email-alexandru.elisei@arm.com>
References: <1569245722-23375-1-git-send-email-alexandru.elisei@arm.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Suzuki K Poulose <suzuki.poulose@arm.com>

With 16K pagesize, the hugepage size is 32M. Align the guest
memory to the hugepagesize for 16K.

To query the host page size, we use sysconf(_SC_PAGESIZE) instead of
getpagesize, as suggested by man 2 getpagesize for portable applications.
Also use the sysconf function instead of getpagesize when setting
kvm->ram_pagesize.

Cc: Marc Zyngier <marc.zyngier@arm.com>
Cc: Andre Przywara <andre.przywara@arm.com>
Cc: Will Deacon <will.deacon@arm.com>
Signed-off-by: Suzuki K Poulose <suzuki.poulose@arm.com>
Signed-off-by: Julien Grall <julien.grall@arm.com>
Tested-by: Alexandru Elisei <alexandru.elisei@arm.com>
Signed-off-by: Alexandru Elisei <alexandru.elisei@arm.com>
---
 arm/kvm.c     | 36 +++++++++++++++++++++++++++++-------
 builtin-run.c |  4 ++--
 util/util.c   |  2 +-
 3 files changed, 32 insertions(+), 10 deletions(-)

```
#### [PATCH 1/6] KVM: PPC: Book3S HV: XIVE: initialize private pointer when VPs are allocated
##### From: Greg Kurz <groug@kaod.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 8bit
X-Patchwork-Submitter: Greg Kurz <groug@kaod.org>
X-Patchwork-Id: 11157155
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 157C71668
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 15:43:48 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id F1D1B207FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 15:43:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732543AbfIWPnr (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 11:43:47 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:23720 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1732544AbfIWPnq (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 23 Sep 2019 11:43:46 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8NFg7Ai076599
        for <kvm@vger.kernel.org>; Mon, 23 Sep 2019 11:43:45 -0400
Received: from e06smtp01.uk.ibm.com (e06smtp01.uk.ibm.com [195.75.94.97])
        by mx0b-001b2d01.pphosted.com with ESMTP id 2v6ydumg5u-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 23 Sep 2019 11:43:45 -0400
Received: from localhost
        by e06smtp01.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <groug@kaod.org>;
        Mon, 23 Sep 2019 16:43:43 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp01.uk.ibm.com (192.168.101.131) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 23 Sep 2019 16:43:39 +0100
Received: from d06av26.portsmouth.uk.ibm.com (d06av26.portsmouth.uk.ibm.com
 [9.149.105.62])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8NFhBfA33685764
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 23 Sep 2019 15:43:11 GMT
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 1A020AE057;
        Mon, 23 Sep 2019 15:43:38 +0000 (GMT)
Received: from d06av26.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B11FDAE045;
        Mon, 23 Sep 2019 15:43:37 +0000 (GMT)
Received: from bahia.lan (unknown [9.145.22.84])
        by d06av26.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 23 Sep 2019 15:43:37 +0000 (GMT)
Subject: [PATCH 1/6] KVM: PPC: Book3S HV: XIVE: initialize private pointer
 when VPs are allocated
From: Greg Kurz <groug@kaod.org>
To: Paul Mackerras <paulus@ozlabs.org>
Cc: Michael Ellerman <mpe@ellerman.id.au>,
 Benjamin Herrenschmidt <benh@kernel.crashing.org>,
 =?utf-8?q?C=C3=A9dric?= Le Goater <clg@kaod.org>,
 David Gibson <david@gibson.dropbear.id.au>,
 Paolo Bonzini <pbonzini@redhat.com>,
 Radim =?utf-8?b?S3LEjW3DocWZ?= <rkrcmar@redhat.com>, kvm-ppc@vger.kernel.org,
 kvm@vger.kernel.org, linuxppc-dev@lists.ozlabs.org
Date: Mon, 23 Sep 2019 17:43:37 +0200
In-Reply-To: <156925341155.974393.11681611197111945710.stgit@bahia.lan>
References: <156925341155.974393.11681611197111945710.stgit@bahia.lan>
User-Agent: StGit/unknown-version
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
X-TM-AS-GCONF: 00
x-cbid: 19092315-4275-0000-0000-0000036A1A52
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19092315-4276-0000-0000-0000387C8F5E
Message-Id: <156925341736.974393.18379970954169086891.stgit@bahia.lan>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-23_05:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=2 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1034 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909230148
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Cédric Le Goater <clg@kaod.org>

Do not assign the device private pointer before making sure the XIVE
VPs are allocated in OPAL and test pointer validity when releasing
the device.

Fixes: 5422e95103cf ("KVM: PPC: Book3S HV: XIVE: Replace the 'destroy' method by a 'release' method")
Signed-off-by: Cédric Le Goater <clg@kaod.org>
Signed-off-by: Greg Kurz <groug@kaod.org>
---
 arch/powerpc/kvm/book3s_xive.c        |   13 +++++++++++--
 arch/powerpc/kvm/book3s_xive_native.c |   13 +++++++++++--
 2 files changed, 22 insertions(+), 4 deletions(-)

```
#### [kvm-unit-tests PATCH] s390x: Add initial smp code
##### From: Janosch Frank <frankja@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Janosch Frank <frankja@linux.ibm.com>
X-Patchwork-Id: 11157073
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E29A7112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 14:16:27 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B558320820
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 14:16:27 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1730583AbfIWOQ0 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 10:16:26 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:28066 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728575AbfIWOQ0 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 23 Sep 2019 10:16:26 -0400
Received: from pps.filterd (m0098404.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8NEATNj054568
        for <kvm@vger.kernel.org>; Mon, 23 Sep 2019 10:16:25 -0400
Received: from e06smtp02.uk.ibm.com (e06smtp02.uk.ibm.com [195.75.94.98])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2v6x4g473f-1
        (version=TLSv1.2 cipher=AES256-GCM-SHA384 bits=256 verify=NOT)
        for <kvm@vger.kernel.org>; Mon, 23 Sep 2019 10:16:20 -0400
Received: from localhost
        by e06smtp02.uk.ibm.com with IBM ESMTP SMTP Gateway: Authorized Use
 Only! Violators will be prosecuted
        for <kvm@vger.kernel.org> from <frankja@linux.ibm.com>;
        Mon, 23 Sep 2019 15:16:09 +0100
Received: from b06avi18626390.portsmouth.uk.ibm.com (9.149.26.192)
        by e06smtp02.uk.ibm.com (192.168.101.132) with IBM ESMTP SMTP Gateway:
 Authorized Use Only! Violators will be prosecuted;
        (version=TLSv1/SSLv3 cipher=AES256-GCM-SHA384 bits=256/256)
        Mon, 23 Sep 2019 15:16:05 +0100
Received: from d06av23.portsmouth.uk.ibm.com (d06av23.portsmouth.uk.ibm.com
 [9.149.105.59])
        by b06avi18626390.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8NEFbJ930343512
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 23 Sep 2019 14:15:37 GMT
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C3056A4051;
        Mon, 23 Sep 2019 14:16:04 +0000 (GMT)
Received: from d06av23.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C1A77A4040;
        Mon, 23 Sep 2019 14:16:03 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.145.36.175])
        by d06av23.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Mon, 23 Sep 2019 14:16:03 +0000 (GMT)
From: Janosch Frank <frankja@linux.ibm.com>
To: kvm@vger.kernel.org
Cc: linux-s390@vger.kernel.org, david@redhat.com, thuth@redhat.com
Subject: [kvm-unit-tests PATCH] s390x: Add initial smp code
Date: Mon, 23 Sep 2019 16:15:58 +0200
X-Mailer: git-send-email 2.17.2
In-Reply-To: <b60eee55-f013-411a-0e52-3f40a990b1c4@redhat.com>
References: <b60eee55-f013-411a-0e52-3f40a990b1c4@redhat.com>
X-TM-AS-GCONF: 00
x-cbid: 19092314-0008-0000-0000-00000319F784
X-IBM-AV-DETECTION: SAVI=unused REMOTE=unused XFE=unused
x-cbparentid: 19092314-0009-0000-0000-00004A38876B
Message-Id: <20190923141558.3032-1-frankja@linux.ibm.com>
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-23_05:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=3 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909230139
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Let's add a rudimentary SMP library, which will scan for cpus and has
helper functions that manage the cpu state.

Signed-off-by: Janosch Frank <frankja@linux.ibm.com>
---

I left the setup code untouched, as I didn't want to indent too many
lines.

---
 lib/s390x/asm/arch_def.h |   8 ++
 lib/s390x/asm/sigp.h     |  28 ++++-
 lib/s390x/io.c           |   5 +-
 lib/s390x/sclp.h         |   1 +
 lib/s390x/smp.c          | 252 +++++++++++++++++++++++++++++++++++++++
 lib/s390x/smp.h          |  51 ++++++++
 s390x/Makefile           |   1 +
 s390x/cstart64.S         |   7 ++
 8 files changed, 347 insertions(+), 6 deletions(-)
 create mode 100644 lib/s390x/smp.c
 create mode 100644 lib/s390x/smp.h

```
#### [kvm-unit-tests PATCH] x86/unittests.cfg: Increase the timeout of the sieve test to 180s
##### From: Thomas Huth <thuth@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Thomas Huth <thuth@redhat.com>
X-Patchwork-Id: 11156619
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E9C6D13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 11:12:16 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id D10DE206C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 11:12:16 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729550AbfIWLMP (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 07:12:15 -0400
Received: from mx1.redhat.com ([209.132.183.28]:62308 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1728576AbfIWLMP (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Sep 2019 07:12:15 -0400
Received: from smtp.corp.redhat.com (int-mx02.intmail.prod.int.phx2.redhat.com
 [10.5.11.12])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 9CF8B10CC1F4
        for <kvm@vger.kernel.org>; Mon, 23 Sep 2019 11:12:15 +0000 (UTC)
Received: from thuth.com (ovpn-116-120.ams2.redhat.com [10.36.116.120])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 8E95360BF7;
        Mon, 23 Sep 2019 11:12:14 +0000 (UTC)
From: Thomas Huth <thuth@redhat.com>
To: kvm@vger.kernel.org, Paolo Bonzini <pbonzini@redhat.com>, =?utf-8?b?UmFk?=
	=?utf-8?b?aW0gS3LEjW3DocWZ?= <rkrcmar@redhat.com>
Subject: [kvm-unit-tests PATCH] x86/unittests.cfg: Increase the timeout of the
 sieve test to 180s
Date: Mon, 23 Sep 2019 13:12:10 +0200
Message-Id: <20190923111210.9495-1-thuth@redhat.com>
X-Scanned-By: MIMEDefang 2.79 on 10.5.11.12
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.6.2 (mx1.redhat.com [10.5.110.65]);
 Mon, 23 Sep 2019 11:12:15 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In the gitlab-CI (where we are running the tests with TCG), the sieve
test sometimes takes more than 90s to finish, and thus fails due
to the 90s timeout from scripts/runtime.bash. Increase the timeout
for this test to make it always succeed.

Signed-off-by: Thomas Huth <thuth@redhat.com>
---
 See for example this run here where it took more than 90s:
 
  https://gitlab.com/huth/kvm-unit-tests/-/jobs/301407814
 
 If you don't like the change in unittests.cfg, I can also tweak
 the (global) timeout in .gitlab-ci.yml instead.

 x86/unittests.cfg | 1 +
 1 file changed, 1 insertion(+)

```
#### [PATCH 1/6] mdev: class id support
##### From: Jason Wang <jasowang@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Jason Wang <jasowang@redhat.com>
X-Patchwork-Id: 11156845
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8D6171668
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 13:04:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 62F98207FD
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 13:04:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2395132AbfIWNEY (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 09:04:24 -0400
Received: from mx1.redhat.com ([209.132.183.28]:41774 "EHLO mx1.redhat.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1727438AbfIWNEY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Sep 2019 09:04:24 -0400
Received: from smtp.corp.redhat.com (int-mx07.intmail.prod.int.phx2.redhat.com
 [10.5.11.22])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mx1.redhat.com (Postfix) with ESMTPS id 7856330A7B81;
        Mon, 23 Sep 2019 13:04:23 +0000 (UTC)
Received: from jason-ThinkPad-X1-Carbon-6th.redhat.com
 (ovpn-12-93.pek2.redhat.com [10.72.12.93])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 2A12810013D9;
        Mon, 23 Sep 2019 13:03:56 +0000 (UTC)
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
        freude@linux.ibm.com, lingshan.zhu@intel.com, idos@mellanox.com,
        eperezma@redhat.com, lulu@redhat.com, parav@mellanox.com,
        Jason Wang <jasowang@redhat.com>
Subject: [PATCH 1/6] mdev: class id support
Date: Mon, 23 Sep 2019 21:03:26 +0800
Message-Id: <20190923130331.29324-2-jasowang@redhat.com>
In-Reply-To: <20190923130331.29324-1-jasowang@redhat.com>
References: <20190923130331.29324-1-jasowang@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.22
X-Greylist: Sender IP whitelisted,
 not delayed by milter-greylist-4.5.16 (mx1.redhat.com [10.5.110.47]);
 Mon, 23 Sep 2019 13:04:23 +0000 (UTC)
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Mdev bus only supports vfio driver right now, so it doesn't implement
match method. But in the future, we may add drivers other than vfio,
one example is virtio-mdev[1] driver. This means we need to add device
class id support in bus match method to pair the mdev device and mdev
driver correctly.

So this patch adds id_table to mdev_driver and class_id for mdev
parent with the match method for mdev bus.

Signed-off-by: Jason Wang <jasowang@redhat.com>
---
 Documentation/driver-api/vfio-mediated-device.rst |  7 +++++--
 drivers/gpu/drm/i915/gvt/kvmgt.c                  |  2 +-
 drivers/s390/cio/vfio_ccw_ops.c                   |  2 +-
 drivers/s390/crypto/vfio_ap_ops.c                 |  3 ++-
 drivers/vfio/mdev/mdev_core.c                     | 14 ++++++++++++--
 drivers/vfio/mdev/mdev_driver.c                   | 14 ++++++++++++++
 drivers/vfio/mdev/mdev_private.h                  |  1 +
 drivers/vfio/mdev/vfio_mdev.c                     |  6 ++++++
 include/linux/mdev.h                              |  7 ++++++-
 include/linux/mod_devicetable.h                   |  8 ++++++++
 samples/vfio-mdev/mbochs.c                        |  2 +-
 samples/vfio-mdev/mdpy.c                          |  2 +-
 samples/vfio-mdev/mtty.c                          |  2 +-
 13 files changed, 59 insertions(+), 11 deletions(-)

```
#### [PATCH 1/3] powerpc/kvm/book3s: Replace current->mm by kvm->mm
##### From: Leonardo Bras <leonardo@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Leonardo Bras <leonardo@linux.ibm.com>
X-Patchwork-Id: 11157667
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id B165A1599
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 21:24:29 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 8ED1B222C2
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 21:24:29 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2503040AbfIWVY2 (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 17:24:28 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:18462 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388395AbfIWVY2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 23 Sep 2019 17:24:28 -0400
Received: from pps.filterd (m0098393.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8NLN9YD067979;
        Mon, 23 Sep 2019 17:24:21 -0400
Received: from ppma04dal.us.ibm.com (7a.29.35a9.ip4.static.sl-reverse.com
 [169.53.41.122])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2v73bn4qcq-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 23 Sep 2019 17:24:21 -0400
Received: from pps.filterd (ppma04dal.us.ibm.com [127.0.0.1])
        by ppma04dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 x8NLJN1Y020927;
        Mon, 23 Sep 2019 21:24:20 GMT
Received: from b03cxnp08025.gho.boulder.ibm.com
 (b03cxnp08025.gho.boulder.ibm.com [9.17.130.17])
        by ppma04dal.us.ibm.com with ESMTP id 2v5bg74ge8-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 23 Sep 2019 21:24:20 +0000
Received: from b03ledav005.gho.boulder.ibm.com
 (b03ledav005.gho.boulder.ibm.com [9.17.130.236])
        by b03cxnp08025.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id x8NLOJJb45220270
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 23 Sep 2019 21:24:19 GMT
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 23C7EBE054;
        Mon, 23 Sep 2019 21:24:19 +0000 (GMT)
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CA919BE051;
        Mon, 23 Sep 2019 21:24:17 +0000 (GMT)
Received: from LeoBras.aus.stglabs.ibm.com (unknown [9.18.235.184])
        by b03ledav005.gho.boulder.ibm.com (Postfix) with ESMTP;
        Mon, 23 Sep 2019 21:24:17 +0000 (GMT)
From: Leonardo Bras <leonardo@linux.ibm.com>
To: kvm@vger.kernel.org, kvm-ppc@vger.kernel.org
Cc: Leonardo Bras <leonardo@linux.ibm.com>,
        Paul Mackerras <paulus@ozlabs.org>,
        Benjamin Herrenschmidt <benh@kernel.crashing.org>,
        Michael Ellerman <mpe@ellerman.id.au>
Subject: [PATCH 1/3] powerpc/kvm/book3s: Replace current->mm by kvm->mm
Date: Mon, 23 Sep 2019 18:24:07 -0300
Message-Id: <20190923212409.7153-2-leonardo@linux.ibm.com>
X-Mailer: git-send-email 2.20.1
In-Reply-To: <20190923212409.7153-1-leonardo@linux.ibm.com>
References: <20190923212409.7153-1-leonardo@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-23_08:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=8 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=846 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1908290000 definitions=main-1909230179
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Given that in kvm_create_vm() there is:
kvm->mm = current->mm;

And that on every kvm_*_ioctl we have:
if (kvm->mm != current->mm)
	return -EIO;

I see no reason to keep using current->mm instead of kvm->mm.

By doing so, we would reduce the use of 'global' variables on code, relying
more in the contents of kvm struct.

Signed-off-by: Leonardo Bras <leonardo@linux.ibm.com>
---
 arch/powerpc/kvm/book3s_64_mmu_hv.c |  4 ++--
 arch/powerpc/kvm/book3s_64_vio.c    |  6 +++---
 arch/powerpc/kvm/book3s_hv.c        | 10 +++++-----
 3 files changed, 10 insertions(+), 10 deletions(-)

```
#### [RFC PATCH 1/4] iommu/vt-d: Move domain_flush_cache helper into header
##### From: Lu Baolu <baolu.lu@linux.intel.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Lu Baolu <baolu.lu@linux.intel.com>
X-Patchwork-Id: 11156691
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id CB67B13B1
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 12:27:25 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B28D320882
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 12:27:25 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732339AbfIWM1W (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 08:27:22 -0400
Received: from mga06.intel.com ([134.134.136.31]:4334 "EHLO mga06.intel.com"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1730399AbfIWM1V (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Sep 2019 08:27:21 -0400
X-Amp-Result: SKIPPED(no attachment in message)
X-Amp-File-Uploaded: False
Received: from fmsmga001.fm.intel.com ([10.253.24.23])
  by orsmga104.jf.intel.com with ESMTP/TLS/DHE-RSA-AES256-GCM-SHA384;
 23 Sep 2019 05:27:21 -0700
X-ExtLoop1: 1
X-IronPort-AV: E=Sophos;i="5.64,539,1559545200";
   d="scan'208";a="203116661"
Received: from allen-box.sh.intel.com ([10.239.159.136])
  by fmsmga001.fm.intel.com with ESMTP; 23 Sep 2019 05:27:19 -0700
From: Lu Baolu <baolu.lu@linux.intel.com>
To: Joerg Roedel <joro@8bytes.org>,
        David Woodhouse <dwmw2@infradead.org>,
        Alex Williamson <alex.williamson@redhat.com>
Cc: ashok.raj@intel.com, sanjay.k.kumar@intel.com,
        jacob.jun.pan@linux.intel.com, kevin.tian@intel.com,
        yi.l.liu@intel.com, yi.y.sun@intel.com,
        iommu@lists.linux-foundation.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org, Lu Baolu <baolu.lu@linux.intel.com>,
        Yi Sun <yi.y.sun@linux.intel.com>
Subject: [RFC PATCH 1/4] iommu/vt-d: Move domain_flush_cache helper into
 header
Date: Mon, 23 Sep 2019 20:24:51 +0800
Message-Id: <20190923122454.9888-2-baolu.lu@linux.intel.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20190923122454.9888-1-baolu.lu@linux.intel.com>
References: <20190923122454.9888-1-baolu.lu@linux.intel.com>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

So that it could be used in other source files as well.

Cc: Ashok Raj <ashok.raj@intel.com>
Cc: Jacob Pan <jacob.jun.pan@linux.intel.com>
Cc: Kevin Tian <kevin.tian@intel.com>
Cc: Liu Yi L <yi.l.liu@intel.com>
Cc: Yi Sun <yi.y.sun@linux.intel.com>
Signed-off-by: Lu Baolu <baolu.lu@linux.intel.com>
---
 drivers/iommu/intel-iommu.c | 7 -------
 include/linux/intel-iommu.h | 7 +++++++
 2 files changed, 7 insertions(+), 7 deletions(-)

```
#### [PATCH] vhost: It's better to use size_t for the 3rd parameter of vhost_exceeds_weight()
##### From: wangxu <wangxu72@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: "wangxu (AE)" <wangxu72@huawei.com>
X-Patchwork-Id: 11156183
Return-Path: <SRS0=yuxV=XS=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 2EADC14ED
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 07:50:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 1633020882
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 23 Sep 2019 07:50:23 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2405163AbfIWHuS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 23 Sep 2019 03:50:18 -0400
Received: from szxga06-in.huawei.com ([45.249.212.32]:57472 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S2404826AbfIWHuR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 23 Sep 2019 03:50:17 -0400
Received: from DGGEMS404-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id D70204B363A47E3BE127;
        Mon, 23 Sep 2019 15:50:15 +0800 (CST)
Received: from use12-sp2.huawei.com (10.67.188.167) by
 DGGEMS404-HUB.china.huawei.com (10.3.19.204) with Microsoft SMTP Server id
 14.3.439.0; Mon, 23 Sep 2019 15:50:14 +0800
From: wangxu <wangxu72@huawei.com>
To: <jasowang@redhat.com>, <mst@redhat.com>
CC: <kvm@vger.kernel.org>, <virtualization@lists.linux-foundation.org>,
        <netdev@vger.kernel.org>, <linux-kernel@vger.kernel.org>
Subject: [PATCH] vhost: It's better to use size_t for the 3rd parameter of
 vhost_exceeds_weight()
Date: Mon, 23 Sep 2019 15:46:41 +0800
Message-ID: <1569224801-101248-1-git-send-email-wangxu72@huawei.com>
X-Mailer: git-send-email 1.8.5.6
MIME-Version: 1.0
Content-Type: text/plain
X-Originating-IP: [10.67.188.167]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wang Xu <wangxu72@huawei.com>

Caller of vhost_exceeds_weight(..., total_len) in drivers/vhost/net.c
usually pass size_t total_len, which may be affected by rx/tx package.

Signed-off-by: Wang Xu <wangxu72@huawei.com>
---
 drivers/vhost/vhost.c | 4 ++--
 drivers/vhost/vhost.h | 7 ++++---
 2 files changed, 6 insertions(+), 5 deletions(-)

```
