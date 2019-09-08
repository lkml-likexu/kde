#### [PATCH v4 1/4] s390: pci: Exporting access to CLP PCI function and PCI group
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11136159
Return-Path: <SRS0=kw8a=XC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id DBF16112B
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  7 Sep 2019 00:14:17 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id BF1872178F
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  7 Sep 2019 00:14:17 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2406169AbfIGAOO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 6 Sep 2019 20:14:14 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:29268 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2393514AbfIGAOM (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 6 Sep 2019 20:14:12 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.27/8.16.0.27) with SMTP id
 x8707Ngh113588;
        Fri, 6 Sep 2019 20:13:58 -0400
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2uuwu0evgm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 06 Sep 2019 20:13:58 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.27/8.16.0.27) with SMTP id x8707aUl115701;
        Fri, 6 Sep 2019 20:13:57 -0400
Received: from ppma02dal.us.ibm.com (a.bd.3ea9.ip4.static.sl-reverse.com
 [169.62.189.10])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2uuwu0evg9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 06 Sep 2019 20:13:57 -0400
Received: from pps.filterd (ppma02dal.us.ibm.com [127.0.0.1])
        by ppma02dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 x8709N3j004282;
        Sat, 7 Sep 2019 00:13:56 GMT
Received: from b01cxnp23033.gho.pok.ibm.com (b01cxnp23033.gho.pok.ibm.com
 [9.57.198.28])
        by ppma02dal.us.ibm.com with ESMTP id 2uqgh8285u-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 07 Sep 2019 00:13:56 +0000
Received: from b01ledav002.gho.pok.ibm.com (b01ledav002.gho.pok.ibm.com
 [9.57.199.107])
        by b01cxnp23033.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id x870DroP47513980
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 7 Sep 2019 00:13:54 GMT
Received: from b01ledav002.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DC556124054;
        Sat,  7 Sep 2019 00:13:53 +0000 (GMT)
Received: from b01ledav002.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 55829124052;
        Sat,  7 Sep 2019 00:13:53 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.85.134.207])
        by b01ledav002.gho.pok.ibm.com (Postfix) with ESMTP;
        Sat,  7 Sep 2019 00:13:53 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: sebott@linux.ibm.com
Cc: gerald.schaefer@de.ibm.com, pasic@linux.ibm.com,
        borntraeger@de.ibm.com, walling@linux.ibm.com,
        linux-s390@vger.kernel.org, iommu@lists.linux-foundation.org,
        joro@8bytes.org, linux-kernel@vger.kernel.org,
        alex.williamson@redhat.com, kvm@vger.kernel.org,
        heiko.carstens@de.ibm.com, robin.murphy@arm.com, gor@linux.ibm.com,
        cohuck@redhat.com, pmorel@linux.ibm.com
Subject: [PATCH v4 1/4] s390: pci: Exporting access to CLP PCI function and
 PCI group
Date: Fri,  6 Sep 2019 20:13:48 -0400
Message-Id: <1567815231-17940-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1567815231-17940-1-git-send-email-mjrosato@linux.ibm.com>
References: <1567815231-17940-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:,,
 definitions=2019-09-06_11:,,
 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 suspectscore=3 phishscore=0 bulkscore=0 spamscore=0
 clxscore=1015 lowpriorityscore=0 mlxscore=0 impostorscore=0
 mlxlogscore=999 adultscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.0.1-1906280000 definitions=main-1909070000
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Pierre Morel <pmorel@linux.ibm.com>

For the generic implementation of VFIO PCI we need to retrieve
the hardware configuration for the PCI functions and the
PCI function groups.

We modify the internal function using CLP Query PCI function and
CLP query PCI function group so that they can be called from
outside the S390 architecture PCI code and prefix the two
functions with "zdev" to make clear that they can be called
knowing only the associated zdevice.

Signed-off-by: Pierre Morel <pmorel@linux.ibm.com>
Reviewed-by: Sebastian Ott <sebott@linux.ibm.com>
---
 arch/s390/include/asm/pci.h |  3 ++
 arch/s390/pci/pci_clp.c     | 71 +++++++++++++++++++++++----------------------
 2 files changed, 40 insertions(+), 34 deletions(-)

```
#### [PATCH v9 1/8] mm: Add per-cpu logic to page shufflingFrom: Alexander Duyck <alexander.duyck@gmail.com>
##### From: Alexander Duyck <alexander.duyck@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Alexander Duyck <alexander.duyck@gmail.com>
X-Patchwork-Id: 11136575
Return-Path: <SRS0=kw8a=XC=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 440681708
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  7 Sep 2019 17:25:23 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 19A3F208C3
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat,  7 Sep 2019 17:25:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="YVxuP3Qw"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2392981AbfIGRZR (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 7 Sep 2019 13:25:17 -0400
Received: from mail-oi1-f194.google.com ([209.85.167.194]:33230 "EHLO
        mail-oi1-f194.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S2392548AbfIGRZR (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 7 Sep 2019 13:25:17 -0400
Received: by mail-oi1-f194.google.com with SMTP id e12so7303887oie.0;
        Sat, 07 Sep 2019 10:25:16 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=subject:from:to:cc:date:message-id:in-reply-to:references
         :user-agent:mime-version:content-transfer-encoding;
        bh=rtCJ9oXMvzyqzSO/6+XMP8VFA+c1bypJ2A9Wi4tC2B0=;
        b=YVxuP3Qw60ve+K16OV/2OTXTVXsnZSGiw8yXWOnvCSAPW2RJsbvv9esY2jbVJk+MTd
         gZaFZgeUDSH31cxpn+4ACT+RtrLyEzlpB9CSFSKqcLbBdu5k7zv4t9ddGWWi0TGCGwiu
         gFWbCI/pIFOqwAWmWO0aBRiIEO3n1vCRrqraKqGz8fVFzLWJMKaeT4nkP76nJ9dVqS5M
         mGxpfLI0pp+7NdvVFdGAITNx/Whl+E8KWWUR6DpIaXjDSmYY2Hh+szZWNaDpLgznhs4Y
         DGw/CpIO4ALtMzKoFiREaJMW+0Vo1vWKa+L+gYpEaIJGJWvuU4XIhs/WSIDDM2sUHuCP
         a9dA==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:subject:from:to:cc:date:message-id:in-reply-to
         :references:user-agent:mime-version:content-transfer-encoding;
        bh=rtCJ9oXMvzyqzSO/6+XMP8VFA+c1bypJ2A9Wi4tC2B0=;
        b=PS58XQ9jAcbwuo3QBBoNSSqjFVMN5GvkdpuoMRdREfxkyF8OTHmBdVwfuMsPxYVaKT
         8jqf7lwzxeIOEiNexjLIcBPZct0lRPrVd0qJgSoSE92/pfFXGWufgxwqunRzjro++XZ3
         3Gaitecd9vfXwlgASMG71ho74sltMbOF4dXVHp/OoE+ghNQ/njxuzC8SNAs8cnFaIcME
         NzS2Qt0Dm+hJiGyNDyB/JenNZbKy3/9Ofh3RZeGfyCO/NA87sZfxaxYsM2/H8Ar0IPhd
         dhDnq04e3yJOnXkffN/QSCxB/ZUghXJRA3foaTL+Bi1VmyFTNvKv8pq9BcSsH6JfffHx
         1o6A==
X-Gm-Message-State: APjAAAVBjfhwC/t8yUNeWFuYe1DWTzplf0PJFBSmHYmpvljuLCc4S52O
        Nko6g0LtcvL8E11PGMsBQrk=
X-Google-Smtp-Source: 
 APXvYqx76pbWI8aVf7Yn3gxH+LEAS1HoAzYWQhYG1OYCBkmvO+49isQhgNq9dB292v9n9IEZQlObWg==
X-Received: by 2002:aca:b388:: with SMTP id
 c130mr12021078oif.27.1567877115467;
        Sat, 07 Sep 2019 10:25:15 -0700 (PDT)
Received: from localhost.localdomain ([2001:470:b:9c3:9e5c:8eff:fe4f:f2d0])
        by smtp.gmail.com with ESMTPSA id
 h5sm3898728oth.29.2019.09.07.10.25.13
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Sat, 07 Sep 2019 10:25:15 -0700 (PDT)
Subject: [PATCH v9 1/8] mm: Add per-cpu logic to page shuffling
From: Alexander Duyck <alexander.duyck@gmail.com>
To: virtio-dev@lists.oasis-open.org, kvm@vger.kernel.org,
        mst@redhat.com, catalin.marinas@arm.com, david@redhat.com,
        dave.hansen@intel.com, linux-kernel@vger.kernel.org,
        willy@infradead.org, mhocko@kernel.org, linux-mm@kvack.org,
        akpm@linux-foundation.org, will@kernel.org,
        linux-arm-kernel@lists.infradead.org, osalvador@suse.de
Cc: yang.zhang.wz@gmail.com, pagupta@redhat.com,
        konrad.wilk@oracle.com, nitesh@redhat.com, riel@surriel.com,
        lcapitulino@redhat.com, wei.w.wang@intel.com, aarcange@redhat.com,
        ying.huang@intel.com, pbonzini@redhat.com,
        dan.j.williams@intel.com, fengguang.wu@intel.com,
        alexander.h.duyck@linux.intel.com, kirill.shutemov@linux.intel.com
Date: Sat, 07 Sep 2019 10:25:12 -0700
Message-ID: <20190907172512.10910.74435.stgit@localhost.localdomain>
In-Reply-To: <20190907172225.10910.34302.stgit@localhost.localdomain>
References: <20190907172225.10910.34302.stgit@localhost.localdomain>
User-Agent: StGit/0.17.1-dirty
MIME-Version: 1.0
Content-Type: text/plain; charset="utf-8"
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Alexander Duyck <alexander.h.duyck@linux.intel.com>

Change the logic used to generate randomness in the suffle path so that we
can avoid cache line bouncing. The previous logic was sharing the offset
and entropy word between all CPUs. As such this can result in cache line
bouncing and will ultimately hurt performance when enabled.

To resolve this I have moved to a per-cpu logic for maintaining a unsigned
long containing some amount of bits, and an offset value for which bit we
can use for entropy with each call.

Reviewed-by: Dan Williams <dan.j.williams@intel.com>
Signed-off-by: Alexander Duyck <alexander.h.duyck@linux.intel.com>
---
 mm/shuffle.c |   33 +++++++++++++++++++++++----------
 1 file changed, 23 insertions(+), 10 deletions(-)

```
