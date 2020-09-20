#### [PATCH 1/4] s390/pci: stash version in the zpci_dev
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11787033
Return-Path: <SRS0=KWAa=C4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 1EF8D6CA
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Sep 2020 15:28:55 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 03B1721741
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Sep 2020 15:28:54 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="b6BjJfuL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726635AbgISP2x (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 19 Sep 2020 11:28:53 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:39920 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1726590AbgISP2s (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 19 Sep 2020 11:28:48 -0400
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08JF2WE9189365;
        Sat, 19 Sep 2020 11:28:47 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=Zlwp6w1I0aP10xjqqHZZM9lxlCxlhdIk2wX+FJwZSd0=;
 b=b6BjJfuLY5Gy3xmnfFV+a0+ZSB3DhZIQZmwi7FVfXtyqFxY7INFCegcy5WfQlSJxWwFP
 0VSTcTB8VG47YrKjxm4yzXERedPaAjGG7WbBivLDNafzGM8gJgQgppRjtLHIEQ7zkCHN
 0+ow9BYgQIb04SsFFS6tsxVqNgQF1oJswWCZA31SO5m8I88tLjrCMfL9k8Sh4osAmhYv
 M4zZtGnw2AWiuOwTKPk/TC/BkNbBod/zx49T1Xn52lj3MY79H8UP3V7OSroSdmyX7JXz
 2kLshOBOZzM53yupsryAdWJF1qmWYwuM2Wbr5+ir23LT4KobKauSi8HNOzl3AneNtw46 TA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33nkqdh0sm-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 11:28:47 -0400
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08JF5YbG000606;
        Sat, 19 Sep 2020 11:28:47 -0400
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33nkqdh0s9-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 11:28:47 -0400
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08JFQYY6019127;
        Sat, 19 Sep 2020 15:28:46 GMT
Received: from b03cxnp08027.gho.boulder.ibm.com
 (b03cxnp08027.gho.boulder.ibm.com [9.17.130.19])
        by ppma02wdc.us.ibm.com with ESMTP id 33n9m8b6sa-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 15:28:46 +0000
Received: from b03ledav005.gho.boulder.ibm.com
 (b03ledav005.gho.boulder.ibm.com [9.17.130.236])
        by b03cxnp08027.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08JFSdxn28705310
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 19 Sep 2020 15:28:39 GMT
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0F6CDBE051;
        Sat, 19 Sep 2020 15:28:43 +0000 (GMT)
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id CA1D2BE04F;
        Sat, 19 Sep 2020 15:28:41 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.74.107])
        by b03ledav005.gho.boulder.ibm.com (Postfix) with ESMTP;
        Sat, 19 Sep 2020 15:28:41 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com,
        schnelle@linux.ibm.com
Cc: pmorel@linux.ibm.com, borntraeger@de.ibm.com, hca@linux.ibm.com,
        gor@linux.ibm.com, gerald.schaefer@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 1/4] s390/pci: stash version in the zpci_dev
Date: Sat, 19 Sep 2020 11:28:35 -0400
Message-Id: <1600529318-8996-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1600529318-8996-1-git-send-email-mjrosato@linux.ibm.com>
References: <1600529318-8996-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-19_05:2020-09-16,2020-09-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 spamscore=0 phishscore=0
 mlxscore=0 lowpriorityscore=0 bulkscore=0 adultscore=0 malwarescore=0
 mlxlogscore=999 clxscore=1015 priorityscore=1501 suspectscore=0
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2009190131
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In preparation for passing the info on to vfio-pci devices, stash the
supported PCI version for the target device in the zpci_dev.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 arch/s390/include/asm/pci.h | 1 +
 arch/s390/pci/pci_clp.c     | 1 +
 2 files changed, 2 insertions(+)

```
#### [RESEND PATCH] KVM: use struct_size() and flex_array_size() helpers in kvm_io_bus_unregister_dev()
##### From: Rustam Kovhaev <rkovhaev@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Rustam Kovhaev <rkovhaev@gmail.com>
X-Patchwork-Id: 11786675
Return-Path: <SRS0=KWAa=C4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3D0B16CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Sep 2020 07:21:34 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1421F20DD4
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Sep 2020 07:21:34 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="GA753YAh"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726192AbgISHVS (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 19 Sep 2020 03:21:18 -0400
Received: from lindbergh.monkeyblade.net ([23.128.96.19]:42234 "EHLO
        lindbergh.monkeyblade.net" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726054AbgISHVS (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sat, 19 Sep 2020 03:21:18 -0400
Received: from mail-pf1-x442.google.com (mail-pf1-x442.google.com
 [IPv6:2607:f8b0:4864:20::442])
        by lindbergh.monkeyblade.net (Postfix) with ESMTPS id F3B64C0613CE;
        Sat, 19 Sep 2020 00:21:17 -0700 (PDT)
Received: by mail-pf1-x442.google.com with SMTP id x123so4914556pfc.7;
        Sat, 19 Sep 2020 00:21:17 -0700 (PDT)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4kK+jQKJbbHZJYLj3SecCh6+KVR55OeofhrlQ+EkZss=;
        b=GA753YAh76vWLQcwOFASJ9BZ7g+zdnQQoMVOQrXZHs/C0Eg4PK6Umrp1ADlo2Vq89g
         D4Gaa9BGT8T4xTkFUfijllWjJYWyqAW2+U1Cx/J+qeY3Wa1TisVzMbKTY2l7eUSesexs
         /1iaKaWSLblxm1K6q/DHu0SvVeAJ0DWgXVB6CPQHwy/5wG6AL2CFSR0/PKg0/bgUJYG/
         1C0T9jynyBItTyggRzDH4+argbTS/ceQpfAyWXfSQCtGn/YQW9QftQgGR+gUpCIu7/6Q
         ubCSL++9Zmy5f0v51LySeuxHPyqfnh0s66G48yJ2rnAdbnlVNsFNg4Evs3g11puSjaeI
         JUXw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id:mime-version
         :content-transfer-encoding;
        bh=4kK+jQKJbbHZJYLj3SecCh6+KVR55OeofhrlQ+EkZss=;
        b=QRZ6g/N7FpXOv6fIkXgVtOzZWOBdqVGT+EqllpEdbBmftzhZsx8lOJxW/1KkEJJ44Q
         brHN2TJ9qBeAIMBlZneko427NJLr5brCDJfI+lqttjCqsWR3GAeexuamTTft7arrJFRO
         Bf5DhqO607pCgd6fnqUmhFJdOgrzGFb/pONBos9bU0cHaTfzwUM2uoD0oHQkvjVY2/u5
         OXlsESPZMHuPVmkqQKG6G5nXAjy3JVIlnZdYZSat/jJn/h+xvlAmYkmuW7Ugu2Svk+l6
         pvsSvjLnEepsmW1du2Mvhg7JZeF0bi7uQiUKew84hE2+1U2kUKo9lCC5mVI287KODd/A
         EZlA==
X-Gm-Message-State: AOAM5332Veuc7FwxIsRCPYeu122EygVR4XIO6NJzHaO3l6QxvIklkoWd
        +Z8cd/YUOTSnfXCfsPmSOvE=
X-Google-Smtp-Source: 
 ABdhPJxmZXahfmIqaEqkFnTtyceIDfSg3X1q7TQ60WFIuTxrN5r9F3pocJ2zeq108Wum7M+297Id8Q==
X-Received: by 2002:a62:5586:0:b029:13e:d13d:a12c with SMTP id
 j128-20020a6255860000b029013ed13da12cmr34972311pfb.20.1600500077185;
        Sat, 19 Sep 2020 00:21:17 -0700 (PDT)
Received: from localhost.localdomain (104.36.148.139.aurocloud.com.
 [104.36.148.139])
        by smtp.gmail.com with ESMTPSA id
 ge12sm4713261pjb.26.2020.09.19.00.21.13
        (version=TLS1_3 cipher=TLS_AES_256_GCM_SHA384 bits=256/256);
        Sat, 19 Sep 2020 00:21:16 -0700 (PDT)
From: Rustam Kovhaev <rkovhaev@gmail.com>
To: pbonzini@redhat.com, vkuznets@redhat.com, gustavoars@kernel.org,
        kvm@vger.kernel.org
Cc: linux-kernel@vger.kernel.org, gregkh@linuxfoundation.org,
        Rustam Kovhaev <rkovhaev@gmail.com>
Subject: [RESEND PATCH] KVM: use struct_size() and flex_array_size() helpers
 in kvm_io_bus_unregister_dev()
Date: Sat, 19 Sep 2020 00:21:55 -0700
Message-Id: <20200919072155.1195714-1-rkovhaev@gmail.com>
X-Mailer: git-send-email 2.28.0
MIME-Version: 1.0
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Make use of the struct_size() helper to avoid any potential type
mistakes and protect against potential integer overflows
Make use of the flex_array_size() helper to calculate the size of a
flexible array member within an enclosing structure

Suggested-by: Gustavo A. R. Silva <gustavoars@kernel.org>
Signed-off-by: Rustam Kovhaev <rkovhaev@gmail.com>
Reviewed-by: Gustavo A. R. Silva <gustavoars@kernel.org>
---
 virt/kvm/kvm_main.c | 4 ++--
 1 file changed, 2 insertions(+), 2 deletions(-)

```
#### [PATCH 1/7] update-linux-headers: Add vfio_zdev.h
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11787041
Return-Path: <SRS0=KWAa=C4=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 60FA3618
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Sep 2020 15:35:05 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 46BC821741
	for <patchwork-kvm@patchwork.kernel.org>;
 Sat, 19 Sep 2020 15:35:05 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="R2aBgqnV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726590AbgISPfE (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sat, 19 Sep 2020 11:35:04 -0400
Received: from mx0b-001b2d01.pphosted.com ([148.163.158.5]:28938 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-FAIL)
        by vger.kernel.org with ESMTP id S1726493AbgISPfE (ORCPT
        <rfc822;kvm@vger.kernel.org>); Sat, 19 Sep 2020 11:35:04 -0400
Received: from pps.filterd (m0098413.ppops.net [127.0.0.1])
        by mx0b-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 08JFWRA7122404;
        Sat, 19 Sep 2020 11:34:41 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=WK8gF4N9HS62KlaG4AFwexv7peq6mKBPRGLNCAZO4F8=;
 b=R2aBgqnVt267CHCjv/FEf0ulu5/0+RwnESwFaZS2sRJGKiPB1gWsf55ptElzltwM0tDF
 GSu2s6MGxNCsMKZ87EcwCwu3ifNfe6ze6ZYNi/6/8WN9E1Ml1PnP7ZXavsoHi2VkNhCw
 e40GrkdoIB/j66cs5FJNsUGIb2j8ktA7nyFEcC2LwkJ/atlJ3ZWyt9n8F/b9J8bW5B+5
 SLQw9b320g1e+ypJ0n1IpaBkhSD12ds9Pgrez2HpXFee9dePCieirurBo1CHgR2LcMmJ
 99tkzV5zEK0AvAFqH9/+FsTzB/wrJbJALoKGUuyzOcdO60vFxFv6dtDTv1gEViQr6k5U 4g==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33ng7h4t6q-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 11:34:41 -0400
Received: from m0098413.ppops.net (m0098413.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 08JFYftW128544;
        Sat, 19 Sep 2020 11:34:41 -0400
Received: from ppma02wdc.us.ibm.com (aa.5b.37a9.ip4.static.sl-reverse.com
 [169.55.91.170])
        by mx0b-001b2d01.pphosted.com with ESMTP id 33ng7h4t6e-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 11:34:41 -0400
Received: from pps.filterd (ppma02wdc.us.ibm.com [127.0.0.1])
        by ppma02wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 08JFQaBP019138;
        Sat, 19 Sep 2020 15:34:40 GMT
Received: from b03cxnp08026.gho.boulder.ibm.com
 (b03cxnp08026.gho.boulder.ibm.com [9.17.130.18])
        by ppma02wdc.us.ibm.com with ESMTP id 33n9m8b7hu-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Sat, 19 Sep 2020 15:34:40 +0000
Received: from b03ledav004.gho.boulder.ibm.com
 (b03ledav004.gho.boulder.ibm.com [9.17.130.235])
        by b03cxnp08026.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 08JFYXuD49414546
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Sat, 19 Sep 2020 15:34:33 GMT
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 0ABEE7805F;
        Sat, 19 Sep 2020 15:34:39 +0000 (GMT)
Received: from b03ledav004.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B7F7D7805C;
        Sat, 19 Sep 2020 15:34:37 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.211.74.107])
        by b03ledav004.gho.boulder.ibm.com (Postfix) with ESMTP;
        Sat, 19 Sep 2020 15:34:37 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: cohuck@redhat.com, thuth@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, pasic@linux.ibm.com, borntraeger@de.ibm.com,
        mst@redhat.com, pbonzini@redhat.com, alex.williamson@redhat.com,
        qemu-s390x@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org
Subject: [PATCH 1/7] update-linux-headers: Add vfio_zdev.h
Date: Sat, 19 Sep 2020 11:34:26 -0400
Message-Id: <1600529672-10243-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1600529672-10243-1-git-send-email-mjrosato@linux.ibm.com>
References: <1600529672-10243-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-09-19_05:2020-09-16,2020-09-19 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 malwarescore=0 phishscore=0
 mlxlogscore=999 mlxscore=0 clxscore=1015 lowpriorityscore=0 spamscore=0
 priorityscore=1501 suspectscore=0 impostorscore=0 adultscore=0 bulkscore=0
 classifier=spam adjust=0 reason=mlx scancount=1 engine=8.12.0-2006250000
 definitions=main-2009190131
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

vfio_zdev.h is used by s390x zPCI support to pass device-specific
CLP information between host and userspace.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 scripts/update-linux-headers.sh | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
