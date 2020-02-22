#### [PATCH v3.1 02/37] KVM: s390/interrupt: do not pin adapter interrupt pages
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11395759
Return-Path: <SRS0=50DH=4J=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id BCB8A930
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Feb 2020 08:09:50 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 93AB62467A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri, 21 Feb 2020 08:09:50 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1732427AbgBUIJt (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 21 Feb 2020 03:09:49 -0500
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:14380 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1731637AbgBUIJs (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 21 Feb 2020 03:09:48 -0500
Received: from pps.filterd (m0098417.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01L891px047493;
        Fri, 21 Feb 2020 03:09:47 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y8ubqqkxj-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 21 Feb 2020 03:09:46 -0500
Received: from m0098417.ppops.net (m0098417.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01L89k06049713;
        Fri, 21 Feb 2020 03:09:46 -0500
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y8ubqqkx9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 21 Feb 2020 03:09:46 -0500
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01L86j5U022370;
        Fri, 21 Feb 2020 08:09:46 GMT
Received: from b01cxnp23032.gho.pok.ibm.com (b01cxnp23032.gho.pok.ibm.com
 [9.57.198.27])
        by ppma02wdc.us.ibm.com with ESMTP id 2y68973b9y-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 21 Feb 2020 08:09:46 +0000
Received: from b01ledav002.gho.pok.ibm.com (b01ledav002.gho.pok.ibm.com
 [9.57.199.107])
        by b01cxnp23032.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 01L89iUd54001958
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 21 Feb 2020 08:09:44 GMT
Received: from b01ledav002.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0D977124052;
        Fri, 21 Feb 2020 08:09:44 +0000 (GMT)
Received: from b01ledav002.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id E899A124053;
        Fri, 21 Feb 2020 08:09:43 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav002.gho.pok.ibm.com (Postfix) with ESMTP;
        Fri, 21 Feb 2020 08:09:43 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: borntraeger@de.ibm.com
Cc: Ulrich.Weigand@de.ibm.com, cohuck@redhat.com, david@redhat.com,
        frankja@linux.vnet.ibm.com, gor@linux.ibm.com,
        imbrenda@linux.ibm.com, kvm@vger.kernel.org,
        linux-s390@vger.kernel.org, mimu@linux.ibm.com, thuth@redhat.com
Subject: [PATCH v3.1 02/37] KVM: s390/interrupt: do not pin adapter interrupt
 pages
Date: Fri, 21 Feb 2020 03:09:42 -0500
Message-Id: <20200221080942.10334-1-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200220104020.5343-3-borntraeger@de.ibm.com>
References: <20200220104020.5343-3-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-21_02:2020-02-19,2020-02-21 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 adultscore=0 clxscore=1015
 priorityscore=1501 suspectscore=4 spamscore=0 bulkscore=0 impostorscore=0
 mlxlogscore=776 lowpriorityscore=0 malwarescore=0 phishscore=0 mlxscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2001150001
 definitions=main-2002210060
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Ulrich Weigand <Ulrich.Weigand@de.ibm.com>

The adapter interrupt page containing the indicator bits is currently
pinned. That means that a guest with many devices can pin a lot of
memory pages in the host. This also complicates the reference tracking
which is needed for memory management handling of protected virtual
machines. It might also have some strange side effects for madvise
MADV_DONTNEED and other things.

We can simply try to get the userspace page set the bits and free the
page. By storing the userspace address in the irq routing entry instead
of the guest address we can actually avoid many lookups and list walks
so that this variant is very likely not slower.

If userspace messes around with the memory slots the worst thing that
can happen is that we write to some other memory within that process.
As we get the the page with FOLL_WRITE this can also not be used to
write to shared read-only pages.

Signed-off-by: Ulrich Weigand <Ulrich.Weigand@de.ibm.com>
[borntraeger@de.ibm.com: patch simplification]
Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: David Hildenbrand <david@redhat.com>
---
 Documentation/virt/kvm/devices/s390_flic.rst |  11 +-
 arch/s390/include/asm/kvm_host.h             |   3 -
 arch/s390/kvm/interrupt.c                    | 172 ++++++-------------
 3 files changed, 52 insertions(+), 134 deletions(-)

```
