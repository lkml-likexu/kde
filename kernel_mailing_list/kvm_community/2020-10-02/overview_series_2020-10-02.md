#### [PATCH] Documentation: kvm: fix a typo
##### From: Li Qiang <liq3ea@163.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Li Qiang <liq3ea@163.com>
X-Patchwork-Id: 11813781
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3E00C6CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 15:04:45 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 1DCDA20719
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 15:04:45 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=163.com header.i=@163.com
 header.b="IRbhaL9q"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388223AbgJBPEm (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 11:04:42 -0400
Received: from mail-m971.mail.163.com ([123.126.97.1]:52908 "EHLO
        mail-m971.mail.163.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1726017AbgJBPEm (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Oct 2020 11:04:42 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=163.com;
        s=s110527; h=From:Subject:Date:Message-Id:MIME-Version; bh=vw4BK
        ZeWGdQzXY4U/kB8MPQGDeBG0VY8mfLs5IuUnEc=; b=IRbhaL9qdd03/iJRVZV5Q
        sc1LgpbRKiUp4csPMr25gqa08PXi0JHD2fzdlwakwMcaZq4Tyx+agHCJWM0q3vQd
        5yqUH4uaXJreTfFNm0jwIqGK2nB5wfqjrf43deTikXkTW6UvNOGCQwRL5Z07G7J/
        O4G+uLgEwrMeKRGHskP8ps=
Received: from ubuntu.localdomain (unknown [125.120.102.69])
        by smtp1 (Coremail) with SMTP id GdxpCgB3Scp5QXdfpcjqAg--.3258S4;
        Fri, 02 Oct 2020 23:04:26 +0800 (CST)
From: Li Qiang <liq3ea@163.com>
To: pbonzini@redhat.com, corbet@lwn.net, kvm@vger.kernel.org,
        linux-doc@vger.kernel.org, linux-kernel@vger.kernel.org
Cc: liq3ea@gmail.com, Li Qiang <liq3ea@163.com>
Subject: [PATCH] Documentation: kvm: fix a typo
Date: Fri,  2 Oct 2020 08:04:22 -0700
Message-Id: <20201002150422.6267-1-liq3ea@163.com>
X-Mailer: git-send-email 2.25.1
MIME-Version: 1.0
X-CM-TRANSID: GdxpCgB3Scp5QXdfpcjqAg--.3258S4
X-Coremail-Antispam: 1Uf129KBjvdXoWrZr4UXw1kuFyxXFy5tFW3GFg_yoW3WrgEvw
        1UJFsYyr1xtryIvw4UWFZ5XF1fXa1ruFW8Cws7JrZ5Aay3AwsY9F97A3s0kw1UWFsxur4r
        JFZxZrW5Gr1S9jkaLaAFLSUrUUUUUb8apTn2vfkv8UJUUUU8Yxn0WfASr-VFAUDa7-sFnT
        9fnUUvcSsGvfC2KfnxnUUI43ZEXa7xRRTa0PUUUUU==
X-Originating-IP: [125.120.102.69]
X-CM-SenderInfo: 5oltjvrd6rljoofrz/xtbBZhqxbVaD6Ear8gAAsC
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Fixes: 9824c83f92bc8 ("Documentation: kvm: document CPUID bit for MSR_KVM_POLL_CONTROL")
Signed-off-by: Li Qiang <liq3ea@163.com>
---
 Documentation/virt/kvm/cpuid.rst | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [PATCH 2/6] docs: vcpu.rst: fix some build warnings
##### From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
X-Patchwork-Id: 11812873
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id AECBF6CB
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 05:50:14 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 921142145D
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 05:50:14 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
	s=default; t=1601617814;
	bh=W+WftqWQvk0umhBnRI3lw/fTCzD2Ao+YYmSzLVqon2g=;
	h=From:To:Cc:Subject:Date:In-Reply-To:References:List-ID:From;
	b=oyxVEm9+KM0gi+dDNjC0ykZ2zQnlN6GMJRNOzod5XJ2H05uyW/aLh1zdTvkEYxQ+A
	 +Ev0e7BWAb4CFkbKoeWIRGBbUHzwaOYrD0W7tX7yHDRsk+PSA59HgYsP9gWpoResjw
	 0GgbnMupCjLGkBVeL/Ubf+NlZUug2sVVBYxLcQog=
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726164AbgJBFuH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 01:50:07 -0400
Received: from mail.kernel.org ([198.145.29.99]:59824 "EHLO mail.kernel.org"
        rhost-flags-OK-OK-OK-OK) by vger.kernel.org with ESMTP
        id S1725983AbgJBFt7 (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Oct 2020 01:49:59 -0400
Received: from mail.kernel.org (ip5f5ad59f.dynamic.kabel-deutschland.de
 [95.90.213.159])
        (using TLSv1.2 with cipher ECDHE-RSA-AES256-GCM-SHA384 (256/256 bits))
        (No client certificate requested)
        by mail.kernel.org (Postfix) with ESMTPSA id 83ACB208B6;
        Fri,  2 Oct 2020 05:49:58 +0000 (UTC)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/simple; d=kernel.org;
        s=default; t=1601617798;
        bh=W+WftqWQvk0umhBnRI3lw/fTCzD2Ao+YYmSzLVqon2g=;
        h=From:To:Cc:Subject:Date:In-Reply-To:References:From;
        b=CzKP5ruiYQlxyOj9hJ23C9smv3IqrqMPl7+kBSTPF5bZQhFaYVkCIsuZrc7cxDPQt
         zD1oOYVmUpvYtK3MocRa6VRT9OJNpneVd9iB8SG0ww9jY2kOmLqxHC7v0ke7xqrm/6
         HfZBh2E45NdgW4IbfPG98PyFT6X+mv8rmv8tKquw=
Received: from mchehab by mail.kernel.org with local (Exim 4.94)
        (envelope-from <mchehab@kernel.org>)
        id 1kODx6-006hin-9U; Fri, 02 Oct 2020 07:49:56 +0200
From: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
To: Linux Doc Mailing List <linux-doc@vger.kernel.org>
Cc: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>,
        "Jonathan Corbet" <corbet@lwn.net>,
        Alexandru Elisei <alexandru.elisei@arm.com>,
        Andrew Jones <drjones@redhat.com>,
        Marc Zyngier <maz@kernel.org>,
        Mathieu Poirier <mathieu.poirier@linaro.org>,
        Paolo Bonzini <pbonzini@redhat.com>, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH 2/6] docs: vcpu.rst: fix some build warnings
Date: Fri,  2 Oct 2020 07:49:46 +0200
Message-Id: 
 <b5385dd0213f1f070667925bf7a807bf5270ba78.1601616399.git.mchehab+huawei@kernel.org>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <cover.1601616399.git.mchehab+huawei@kernel.org>
References: <cover.1601616399.git.mchehab+huawei@kernel.org>
MIME-Version: 1.0
Sender: Mauro Carvalho Chehab <mchehab@kernel.org>
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

As warned with make htmldocs:

	.../Documentation/virt/kvm/devices/vcpu.rst:70: WARNING: Malformed table.
	Text in column margin in table line 2.

	=======  ======================================================
	-ENODEV: PMUv3 not supported or GIC not initialized
	-ENXIO:  PMUv3 not properly configured or in-kernel irqchip not
	         configured as required prior to calling this attribute
	-EBUSY:  PMUv3 already initialized
	-EINVAL: Invalid filter range
	=======  ======================================================

The ':' character for two lines are above the size of the column.
Besides that, other tables at the file doesn't use ':', so
just drop them.

While here, also fix this warning also introduced at the same patch:

	.../Documentation/virt/kvm/devices/vcpu.rst:88: WARNING: Block quote ends without a blank line; unexpected unindent.

By marking the C code as a literal block.

Fixes: 8be86a5eec04 ("KVM: arm64: Document PMU filtering API")
Signed-off-by: Mauro Carvalho Chehab <mchehab+huawei@kernel.org>
Acked-by: Paolo Bonzini <pbonzini@redhat.com>
---
 Documentation/virt/kvm/devices/vcpu.rst | 26 ++++++++++++-------------
 1 file changed, 13 insertions(+), 13 deletions(-)

```
#### [PATCH v2 1/5] s390/pci: stash version in the zpci_dev
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11814549
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 8FE4F139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 20:01:07 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 7478D20758
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 20:01:07 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="QSgXq5ep"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725794AbgJBUBA (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 16:01:00 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:40476 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725300AbgJBUA4 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 2 Oct 2020 16:00:56 -0400
Received: from pps.filterd (m0098399.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 092JtdeL184727;
        Fri, 2 Oct 2020 16:00:55 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=qwyKtTUgEZyoCRJjBqLKwxEQ4USWfunQbmB6tnOBH9k=;
 b=QSgXq5epWiXVLyHHKzwy9aDeGWI6D2xOEprhcoZiqDOuJc01oV1iqN76WOHx1jvh28i+
 JvwrZlcjgM3GnGllxaMzwu2TbVIztGuMDv5D4K5BgGWieqUGIoyjR2h5Fa524ZAE6rPe
 3kxDUN0KpEH20ypvt+CyP2+xQuPKbJzGYr3B8v24i2nPosOvozPL3pLnm2W8SbN0cblX
 DV9K7BUWhmBzkLJeh2VBZ8iANzWbYBo6KFT5jGBai1OvthnQPcoPmcuIRx2EZUhnf02g
 9ZMdCVRSAlKiVdjFTWsiommKLLdWNAfMfRfamitlcAftFnuxuoDGMOtm4VAwZ0BpPM1s Vw==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33xasvr2h7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 16:00:55 -0400
Received: from m0098399.ppops.net (m0098399.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 092Jw1KD189052;
        Fri, 2 Oct 2020 16:00:54 -0400
Received: from ppma01dal.us.ibm.com (83.d6.3fa9.ip4.static.sl-reverse.com
 [169.63.214.131])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33xasvr2gg-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 16:00:54 -0400
Received: from pps.filterd (ppma01dal.us.ibm.com [127.0.0.1])
        by ppma01dal.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 092JlCfL011608;
        Fri, 2 Oct 2020 20:00:53 GMT
Received: from b03cxnp07029.gho.boulder.ibm.com
 (b03cxnp07029.gho.boulder.ibm.com [9.17.130.16])
        by ppma01dal.us.ibm.com with ESMTP id 33sw9aearw-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 20:00:53 +0000
Received: from b03ledav001.gho.boulder.ibm.com
 (b03ledav001.gho.boulder.ibm.com [9.17.130.232])
        by b03cxnp07029.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 092K0ovK50921892
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 2 Oct 2020 20:00:50 GMT
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id C6CE46E054;
        Fri,  2 Oct 2020 20:00:49 +0000 (GMT)
Received: from b03ledav001.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id BE2B96E052;
        Fri,  2 Oct 2020 20:00:48 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.4.25])
        by b03ledav001.gho.boulder.ibm.com (Postfix) with ESMTP;
        Fri,  2 Oct 2020 20:00:48 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: alex.williamson@redhat.com, cohuck@redhat.com,
        schnelle@linux.ibm.com
Cc: pmorel@linux.ibm.com, borntraeger@de.ibm.com, hca@linux.ibm.com,
        gor@linux.ibm.com, gerald.schaefer@linux.ibm.com,
        linux-s390@vger.kernel.org, kvm@vger.kernel.org,
        linux-kernel@vger.kernel.org
Subject: [PATCH v2 1/5] s390/pci: stash version in the zpci_dev
Date: Fri,  2 Oct 2020 16:00:40 -0400
Message-Id: <1601668844-5798-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1601668844-5798-1-git-send-email-mjrosato@linux.ibm.com>
References: <1601668844-5798-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-02_14:2020-10-02,2020-10-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0
 lowpriorityscore=0 malwarescore=0 spamscore=0 suspectscore=0 phishscore=0
 priorityscore=1501 impostorscore=0 adultscore=0 mlxlogscore=975
 clxscore=1011 mlxscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2010020141
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

In preparation for passing the info on to vfio-pci devices, stash the
supported PCI version for the target device in the zpci_dev.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
Acked-by: Niklas Schnelle <schnelle@linux.ibm.com>
Acked-by: Christian Borntraeger <borntraeger@de.ibm.com>
Acked-by: Cornelia Huck <cohuck@redhat.com>
---
 arch/s390/include/asm/pci.h | 1 +
 arch/s390/pci/pci_clp.c     | 1 +
 2 files changed, 2 insertions(+)

```
#### [PATCH v2 1/9] s390x/pci: Move header files to include/hw/s390x
##### From: Matthew Rosato <mjrosato@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Matthew Rosato <mjrosato@linux.ibm.com>
X-Patchwork-Id: 11814571
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 94F7F112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 20:07:15 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 64BEF2072E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 20:07:15 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="r5/u56vL"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1725801AbgJBUHO (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 16:07:14 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:46902 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1725355AbgJBUHN (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 2 Oct 2020 16:07:13 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 092K2IgL045958;
        Fri, 2 Oct 2020 16:06:40 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references; s=pp1;
 bh=6ZW/41ftrmBxNwLC6nTaLXjFv/PX4Uzy6FoZPgJfKHM=;
 b=r5/u56vL99nbO4nlM6wFd31SkxYBj/SIaWgy09D7zwJ+QQVrx8E/eL4/gjK8hhvZfYRE
 nCAUH6TnJ4hmSW9SYEIoRCmMsqH6MNqGnqG05kqSxRV2DxmBHmo4dI2YJf7gfXLKJKaV
 sR8POSqiMTRQ6uXktERB1TyvzJ85QCv1jEgsZD74vEc/SG3rMWIhwaseRVX409fqS8pJ
 2Atf6R1wHLlEZyQddxR2fqMMXk+xwbh39LvhHv83KoeXwJhUyrYsHbx0EhE5NS514kS5
 sE8HW1MeWsTScWW1K/A58nmig+gz+oJgaueyRd/hPDJ22XOD/pQyfUbbbbR52oIyUkxr zA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33xaks8hc0-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 16:06:40 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 092K305K048436;
        Fri, 2 Oct 2020 16:06:39 -0400
Received: from ppma01wdc.us.ibm.com (fd.55.37a9.ip4.static.sl-reverse.com
 [169.55.85.253])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33xaks8hb7-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 16:06:39 -0400
Received: from pps.filterd (ppma01wdc.us.ibm.com [127.0.0.1])
        by ppma01wdc.us.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 092JmDHq007928;
        Fri, 2 Oct 2020 20:06:38 GMT
Received: from b03cxnp08026.gho.boulder.ibm.com
 (b03cxnp08026.gho.boulder.ibm.com [9.17.130.18])
        by ppma01wdc.us.ibm.com with ESMTP id 33sw9a0996-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 20:06:38 +0000
Received: from b03ledav005.gho.boulder.ibm.com
 (b03ledav005.gho.boulder.ibm.com [9.17.130.236])
        by b03cxnp08026.gho.boulder.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 092K6UC72753254
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 2 Oct 2020 20:06:30 GMT
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id D81B9BE051;
        Fri,  2 Oct 2020 20:06:36 +0000 (GMT)
Received: from b03ledav005.gho.boulder.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 69AC7BE04F;
        Fri,  2 Oct 2020 20:06:35 +0000 (GMT)
Received: from oc4221205838.ibm.com (unknown [9.163.4.25])
        by b03ledav005.gho.boulder.ibm.com (Postfix) with ESMTP;
        Fri,  2 Oct 2020 20:06:35 +0000 (GMT)
From: Matthew Rosato <mjrosato@linux.ibm.com>
To: cohuck@redhat.com, thuth@redhat.com
Cc: pmorel@linux.ibm.com, schnelle@linux.ibm.com, rth@twiddle.net,
        david@redhat.com, pasic@linux.ibm.com, borntraeger@de.ibm.com,
        mst@redhat.com, pbonzini@redhat.com, alex.williamson@redhat.com,
        qemu-s390x@nongnu.org, qemu-devel@nongnu.org, kvm@vger.kernel.org
Subject: [PATCH v2 1/9] s390x/pci: Move header files to include/hw/s390x
Date: Fri,  2 Oct 2020 16:06:23 -0400
Message-Id: <1601669191-6731-2-git-send-email-mjrosato@linux.ibm.com>
X-Mailer: git-send-email 1.8.3.1
In-Reply-To: <1601669191-6731-1-git-send-email-mjrosato@linux.ibm.com>
References: <1601669191-6731-1-git-send-email-mjrosato@linux.ibm.com>
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-02_14:2020-10-02,2020-10-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 bulkscore=0 phishscore=0
 spamscore=0 clxscore=1015 adultscore=0 priorityscore=1501 mlxscore=0
 suspectscore=2 impostorscore=0 malwarescore=0 lowpriorityscore=0
 mlxlogscore=999 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2010020142
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Seems a more appropriate location for them.

Signed-off-by: Matthew Rosato <mjrosato@linux.ibm.com>
---
 hw/s390x/s390-pci-bus.c          |   4 +-
 hw/s390x/s390-pci-bus.h          | 372 ---------------------------------------
 hw/s390x/s390-pci-inst.c         |   4 +-
 hw/s390x/s390-pci-inst.h         | 312 --------------------------------
 hw/s390x/s390-virtio-ccw.c       |   2 +-
 include/hw/s390x/s390-pci-bus.h  | 372 +++++++++++++++++++++++++++++++++++++++
 include/hw/s390x/s390-pci-inst.h | 312 ++++++++++++++++++++++++++++++++
 7 files changed, 689 insertions(+), 689 deletions(-)
 delete mode 100644 hw/s390x/s390-pci-bus.h
 delete mode 100644 hw/s390x/s390-pci-inst.h
 create mode 100644 include/hw/s390x/s390-pci-bus.h
 create mode 100644 include/hw/s390x/s390-pci-inst.h

```
#### [kvm-unit-tests PATCH v2 1/7] lib/list: Add double linked list management functions
##### From: Claudio Imbrenda <imbrenda@linux.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11813887
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 330E113B2
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 15:44:37 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 15C2B2085B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 15:44:37 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="iPAuiy0N"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388082AbgJBPof (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 11:44:35 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:64604 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388042AbgJBPo2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 2 Oct 2020 11:44:28 -0400
Received: from pps.filterd (m0098396.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 092FgwPJ170905
        for <kvm@vger.kernel.org>; Fri, 2 Oct 2020 11:44:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=WZCOOR6Tso02f7vzcm7TNgr9Sxlc2Kv8yjQ1TOfgxzk=;
 b=iPAuiy0NWB3yq//sdPSVnvGBUYRVwt4CO4UqZ0PlJ6RTsd1dlrQ0DClmxFQ4nCuqk7fN
 3lgpvzuhyi4+OU+3z/FwolXeDid8bd0qC448yMyWCd9SOrHwu5lWENYAOmoc1/tAqebO
 FEEYpUfWsuRZdMq8IWrvVaUdvq7MOk2e1iowYIs3GGuNcJHANGz1Xb+wdLSftPak5soa
 SVZ4/98OEEPtgFux+fQG9QlYseLP77TQxA/c+lG5x7H/VLbhmV14yZ9BeOWiHjOySJHl
 gXMfh01RLBPmdXLHDF8eSQwR42fWrb5ABKq34IRkT/gMQkYE6ArCx8vQmLzYiNAYIFJY qg==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33x73900ya-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 02 Oct 2020 11:44:27 -0400
Received: from m0098396.ppops.net (m0098396.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 092FiM3n174298
        for <kvm@vger.kernel.org>; Fri, 2 Oct 2020 11:44:27 -0400
Received: from ppma01fra.de.ibm.com (46.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.70])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33x73900x2-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 11:44:27 -0400
Received: from pps.filterd (ppma01fra.de.ibm.com [127.0.0.1])
        by ppma01fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 092FiOwr003243;
        Fri, 2 Oct 2020 15:44:24 GMT
Received: from b06cxnps4076.portsmouth.uk.ibm.com
 (d06relay13.portsmouth.uk.ibm.com [9.149.109.198])
        by ppma01fra.de.ibm.com with ESMTP id 33sw98bgyk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 15:44:24 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06cxnps4076.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 092FiLS432244042
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 2 Oct 2020 15:44:22 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id DC1AD42047;
        Fri,  2 Oct 2020 15:44:21 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 7BF2942041;
        Fri,  2 Oct 2020 15:44:21 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.14.90])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri,  2 Oct 2020 15:44:21 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, lvivier@redhat.com
Subject: [kvm-unit-tests PATCH v2 1/7] lib/list: Add double linked list
 management functions
Date: Fri,  2 Oct 2020 17:44:14 +0200
Message-Id: <20201002154420.292134-2-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201002154420.292134-1-imbrenda@linux.ibm.com>
References: <20201002154420.292134-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-02_10:2020-10-02,2020-10-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0
 priorityscore=1501 impostorscore=0 malwarescore=0 mlxscore=0 bulkscore=0
 phishscore=0 clxscore=1015 adultscore=0 mlxlogscore=944 spamscore=0
 suspectscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2010020119
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add simple double linked lists.

Apart from the struct itself, there are functions to add and remove
items, and check for emptyness.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 lib/list.h | 53 +++++++++++++++++++++++++++++++++++++++++++++++++++++
 1 file changed, 53 insertions(+)
 create mode 100644 lib/list.h

diff --git a/lib/list.h b/lib/list.h
new file mode 100644
index 0000000..702a78c
--- /dev/null
+++ b/lib/list.h
@@ -0,0 +1,53 @@
+#ifndef LIST_H
+#define LIST_H
+
+#include <stdbool.h>
+
+/*
+ * Simple double linked list. The pointer to the list is a list item itself,
+ * like in the kernel implementation.
+ */
+struct linked_list {
+	struct linked_list *prev;
+	struct linked_list *next;
+};
+
+/*
+ * An empty list is a list item whose prev and next both point to itself.
+ * Returns true if the list is empty.
+ */
+static inline bool is_list_empty(struct linked_list *p)
+{
+	return !p->next || !p->prev || p == p->next || p == p->prev;
+}
+
+/*
+ * Remove the given element from the list, if the list is not already empty.
+ * The removed element is returned.
+ */
+static inline struct linked_list *list_remove(struct linked_list *l)
+{
+	if (is_list_empty(l))
+		return NULL;
+
+	l->prev->next = l->next;
+	l->next->prev = l->prev;
+	l->prev = l->next = NULL;
+
+	return l;
+}
+
+/*
+ * Add the given element after the given list head.
+ */
+static inline void list_add(struct linked_list *head, struct linked_list *li)
+{
+	assert(li);
+	assert(head);
+	li->prev = head;
+	li->next = head->next;
+	head->next->prev = li;
+	head->next = li;
+}
+
+#endif

From patchwork Fri Oct  2 15:44:15 2020
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Claudio Imbrenda <imbrenda@linux.ibm.com>
X-Patchwork-Id: 11813895
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 6DC8D92C
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 15:44:42 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id 4FB0320795
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 15:44:42 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=ibm.com header.i=@ibm.com
 header.b="OHzto9H0"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388062AbgJBPod (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 11:44:33 -0400
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:26278 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2388040AbgJBPo2 (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 2 Oct 2020 11:44:28 -0400
Received: from pps.filterd (m0098394.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 092FWm4M142555
        for <kvm@vger.kernel.org>; Fri, 2 Oct 2020 11:44:27 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=ibm.com;
 h=from : to : cc : subject
 : date : message-id : in-reply-to : references : mime-version :
 content-transfer-encoding; s=pp1;
 bh=XbOg4Q6+DrwFlErUmMzG4UbfnyVXPsTfI5UU2re81SM=;
 b=OHzto9H0s1U+KqqjKnVf52eL1H7zCoduu5indWGH7QGGuP6pwvd6QatgcW6sA9MrNmZr
 fMXTKhpoMzvCZTRHL9wmUSlvWUJ2RVSyU2lLEeE7serLEgg0eoJwweIIzwRZegJ1e8hq
 /2jT13CCFpOmuXiALnzvcSeMAwFVEi6g5nAHG4f2zv1+vCyFlhbH5SKQrAvHCDpqVZm0
 S2eQqOq8L4AtX9WdhMpoYFptDnG5LUk3JwrgyMnKWtKkeVhGXoDmO9Pu7WSM2KBPduTb
 GLJAzHmYoN4ugRpzG3G43H+QlyyfgHGBVemUQKampd4xsAiEOi1fqMrjErbb0ZkbTYUU yA==
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33x6sv0m3m-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT)
        for <kvm@vger.kernel.org>; Fri, 02 Oct 2020 11:44:27 -0400
Received: from m0098394.ppops.net (m0098394.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 092FXscf150831
        for <kvm@vger.kernel.org>; Fri, 2 Oct 2020 11:44:27 -0400
Received: from ppma06fra.de.ibm.com (48.49.7a9f.ip4.static.sl-reverse.com
 [159.122.73.72])
        by mx0a-001b2d01.pphosted.com with ESMTP id 33x6sv0m2r-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 11:44:26 -0400
Received: from pps.filterd (ppma06fra.de.ibm.com [127.0.0.1])
        by ppma06fra.de.ibm.com (8.16.0.42/8.16.0.42) with SMTP id
 092FhF23011091;
        Fri, 2 Oct 2020 15:44:24 GMT
Received: from b06avi18878370.portsmouth.uk.ibm.com
 (b06avi18878370.portsmouth.uk.ibm.com [9.149.26.194])
        by ppma06fra.de.ibm.com with ESMTP id 33svwguhm5-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Fri, 02 Oct 2020 15:44:24 +0000
Received: from d06av24.portsmouth.uk.ibm.com (d06av24.portsmouth.uk.ibm.com
 [9.149.105.60])
        by b06avi18878370.portsmouth.uk.ibm.com (8.14.9/8.14.9/NCO v10.0) with
 ESMTP id 092FiMfU33817004
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Fri, 2 Oct 2020 15:44:22 GMT
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 5433D4203F;
        Fri,  2 Oct 2020 15:44:22 +0000 (GMT)
Received: from d06av24.portsmouth.uk.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id ED91442041;
        Fri,  2 Oct 2020 15:44:21 +0000 (GMT)
Received: from ibm-vm.ibmuc.com (unknown [9.145.14.90])
        by d06av24.portsmouth.uk.ibm.com (Postfix) with ESMTP;
        Fri,  2 Oct 2020 15:44:21 +0000 (GMT)
From: Claudio Imbrenda <imbrenda@linux.ibm.com>
To: kvm@vger.kernel.org, pbonzini@redhat.com
Cc: frankja@linux.ibm.com, david@redhat.com, thuth@redhat.com,
        cohuck@redhat.com, lvivier@redhat.com
Subject: [kvm-unit-tests PATCH v2 2/7] lib/vmalloc: vmalloc support for
 handling allocation metadata
Date: Fri,  2 Oct 2020 17:44:15 +0200
Message-Id: <20201002154420.292134-3-imbrenda@linux.ibm.com>
X-Mailer: git-send-email 2.26.2
In-Reply-To: <20201002154420.292134-1-imbrenda@linux.ibm.com>
References: <20201002154420.292134-1-imbrenda@linux.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.235,18.0.687
 definitions=2020-10-02_10:2020-10-02,2020-10-02 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 lowpriorityscore=0 mlxscore=0
 clxscore=1015 mlxlogscore=999 adultscore=0 bulkscore=0 spamscore=0
 malwarescore=0 phishscore=0 suspectscore=2 priorityscore=1501
 impostorscore=0 classifier=spam adjust=0 reason=mlx scancount=1
 engine=8.12.0-2006250000 definitions=main-2010020119
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Add allocation metadata handling to vmalloc.

In upcoming patches, allocation metadata will have to be handled
directly bt the lower level allocators, and will not be handled by the
common wrapper.

In this patch, the number of allocated pages plus a magic value are
written immediately before the returned pointer. This means that multi
page allocations will allocate one extra page (which is not worse than
what the current allocator does).

For small allocations there is an optimization: the returned address is
intentionally not page-aligned. This signals that the allocation
spanned one page only. In this case the metadata is only the magic
value, and it is also saved immediately before the returned pointer.
Since the pointer does not point to the begininng of the page, there is
always space in the same page for the magic value.

Signed-off-by: Claudio Imbrenda <imbrenda@linux.ibm.com>
---
 lib/vmalloc.c | 105 +++++++++++++++++++++++++++++++++++++++++++++-----
 1 file changed, 95 insertions(+), 10 deletions(-)

```
#### [RFC PATCH v2 01/33] KVM: SVM: Remove the call to sev_platform_status() during setup
##### From: Tom Lendacky <thomas.lendacky@amd.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tom Lendacky <thomas.lendacky@amd.com>
X-Patchwork-Id: 11814081
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id EDE59139A
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 17:03:28 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id CC7FF2085B
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 17:03:28 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=amdcloud.onmicrosoft.com
 header.i=@amdcloud.onmicrosoft.com header.b="Pmz8pnwl"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2388246AbgJBRDZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 13:03:25 -0400
Received: from mail-eopbgr770073.outbound.protection.outlook.com
 ([40.107.77.73]:20128
        "EHLO NAM02-SN1-obe.outbound.protection.outlook.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726224AbgJBRDZ (ORCPT <rfc822;kvm@vger.kernel.org>);
        Fri, 2 Oct 2020 13:03:25 -0400
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=VykRV1qWItWIFXGKAJlAQ7nJNy5AdEzmQDypGtpxhnLZz/27J6UrFGX+65SlnuDYm1BYtJDQndfJwGYdNerWAnfUSB+CJbsg2fgXOKENLyOiyDHOOpWKlg2VfOCkiGSEoQXN9CkVL4ROxULoMFdT0bWg9gd0k2HhiOfSNbMIqeprhryGKQ3c9Y455pK1+QuqRkIEO6zUQhOqjyeaBNko37D794KG+/QZIWOCA3l/peQSM1Zi7fby8T3fzcMpR8NdB1innesgxSvUGl6lrGe/3hwQQlIS3VS7FlAZPSq73Xcn2m/2wwKW1RA8RoSxXks2FKVz3EH1tgxK7lNTtqZEyg==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=O5dAjRtLqXPCMFK+M/jwLa4b/t2Fn6BY5q79TaGmjCk=;
 b=Hf90HVdjo//8xzhXwjgMnjpWBVqcWNiLPMzcJ6YksjD/BGrshDy3/NVQnMTGoHVUFkajLaE/f0SIhPvEU0oGGmT6QVjQdbI3iuEuPoRVtAw52XwYmS781XW05DyrlAav0VBgxU3PC8totx78EeI2NGLVkWE1pfxV/fpVtD5OF/ChwSwC0qn/7myisFHyXdmuZVpYg3blf12F3T+zUp4lBoYNC4y5bax5jYTn4skkfoyFZgJhR6qDrDCuU92eZXuSwEAT8iGEzbTVZD8ZGQpLjMlqtDS60YgsHVIjwy3NjcZwmiVqmZ43dnMKeuh1BFLBoqb1p24n+trdsgZ7bO0K3A==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=amd.com; dmarc=pass action=none header.from=amd.com; dkim=pass
 header.d=amd.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=amdcloud.onmicrosoft.com; s=selector2-amdcloud-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=O5dAjRtLqXPCMFK+M/jwLa4b/t2Fn6BY5q79TaGmjCk=;
 b=Pmz8pnwlyaMFsUh21g9LiCgZDOaT6V6uzVSud2ubgLCEha9RcfFHvix69LHNc0FTj4D/4kpCF+JMWJQznWVX5rRF/hPje/M7yx6/ktDaJz672AcYD1MA5xY57LDa5IPzolDvL43k+2HdA+N7Kn8m2mE4PdkwxLiKskK3U5VayAM=
Authentication-Results: vger.kernel.org; dkim=none (message not signed)
 header.d=none;vger.kernel.org; dmarc=none action=none header.from=amd.com;
Received: from DM5PR12MB1355.namprd12.prod.outlook.com (2603:10b6:3:6e::7) by
 DM6PR12MB4218.namprd12.prod.outlook.com (2603:10b6:5:21b::16) with Microsoft
 SMTP Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.3433.35; Fri, 2 Oct 2020 17:03:22 +0000
Received: from DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::4d88:9239:2419:7348]) by DM5PR12MB1355.namprd12.prod.outlook.com
 ([fe80::4d88:9239:2419:7348%2]) with mapi id 15.20.3433.039; Fri, 2 Oct 2020
 17:03:22 +0000
From: Tom Lendacky <thomas.lendacky@amd.com>
To: kvm@vger.kernel.org, linux-kernel@vger.kernel.org, x86@kernel.org
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Borislav Petkov <bp@alien8.de>, Ingo Molnar <mingo@redhat.com>,
        Thomas Gleixner <tglx@linutronix.de>,
        Brijesh Singh <brijesh.singh@amd.com>
Subject: [RFC PATCH v2 01/33] KVM: SVM: Remove the call to
 sev_platform_status() during setup
Date: Fri,  2 Oct 2020 12:02:25 -0500
Message-Id: 
 <25be6a2f43efdf8af842c175cbf4d8542a15482d.1601658176.git.thomas.lendacky@amd.com>
X-Mailer: git-send-email 2.28.0
In-Reply-To: <cover.1601658176.git.thomas.lendacky@amd.com>
References: <cover.1601658176.git.thomas.lendacky@amd.com>
X-Originating-IP: [165.204.77.1]
X-ClientProxiedBy: SA0PR11CA0008.namprd11.prod.outlook.com
 (2603:10b6:806:d3::13) To DM5PR12MB1355.namprd12.prod.outlook.com
 (2603:10b6:3:6e::7)
MIME-Version: 1.0
X-MS-Exchange-MessageSentRepresentingType: 1
Received: from tlendack-t1.amd.com (165.204.77.1) by
 SA0PR11CA0008.namprd11.prod.outlook.com (2603:10b6:806:d3::13) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.3433.37 via Frontend
 Transport; Fri, 2 Oct 2020 17:03:21 +0000
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-HT: Tenant
X-MS-Office365-Filtering-Correlation-Id: 8fa4ba96-ec59-41f1-de16-08d866f511cc
X-MS-TrafficTypeDiagnostic: DM6PR12MB4218:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6PR12MB4218F3525C4A8820A69C2178EC310@DM6PR12MB4218.namprd12.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 CNuWyWEutMVYzfKSWshDsa1PZLSTakFAjzr6/4Qq6gmAFizKwOAB22HABDnqI3+FvfyOwf5yd+kAMOzEXDEnDM0IWQG6tugQ9gOEBTCHcgdlmxa+h7vR5rdl0QNbpRSTOhI4qEgriVcuai0EbMXcGbwqQntjJxeGVJp47l1V65HNCkUjz/2f3GTpGpJJIABClY5wFwMRszIHc/Z5VXxA/uAR8hfYMK8LE8JgaIk+UQF/+L1EJpPH10vAVfhMcT8cmP/nr4pOXKrMT/Or1KR6PfZFA1cOuFRo4AmLiUP/OnrCs1Fwu+dmmB7/QONDVQbzSt55d5dUoicudDAW4YnAcA==
X-Forefront-Antispam-Report: 
 CIP:255.255.255.255;CTRY:;LANG:en;SCL:1;SRV:;IPV:NLI;SFV:NSPM;H:DM5PR12MB1355.namprd12.prod.outlook.com;PTR:;CAT:NONE;SFS:(4636009)(396003)(346002)(39860400002)(366004)(136003)(376002)(8676002)(83380400001)(6486002)(2616005)(66556008)(956004)(66476007)(66946007)(52116002)(7696005)(4326008)(36756003)(5660300002)(8936002)(16526019)(186003)(2906002)(54906003)(316002)(26005)(7416002)(478600001)(86362001);DIR:OUT;SFP:1101;
X-MS-Exchange-AntiSpam-MessageData: 
 5qXLSHZTNlyIppQ1SS4iVRp2efIgP9BBF0HM2nqb64xkhGZTMGFPCHMyDCkcZ3f0s8wxig9vOGqip7FuRlDWO6wFXKLaqUP7JvuCeBGUDES8m/6k5N+syP+Eh2uMjijSzyR8ud5lvyLKaMfMnqSi1x4B76s31L/k2bNvnyAMfRE7XxSMV25K1S7CC8T2rC3NzaBMKcLg5Ki5Xr5X0MdYf6Qb5votwyaK0uItQne0tKJ1jsTEm8r5GomHSGI9lOSK3hJaxx9x/nY5GYhz6j0AaBCTBUMXAT6GvUbdJhM4z6/GPwT7SugqtKUD2XTwAAA9lC+2tlkAZ9rCuakbTQP1lZaVJpOToSl0ft/L7zspb1NLjlyvFP9Qm2DV7f5UKh04e0GSlhkQ30bHNkoI9SIoiSDFFzaxvjBB8dUMeIBBYJTSiuf9sk0GA9+wTy/28fMgw/Op8EnPs3HhGFVfrWzZlzj8+Kvw9TZfHOpsmr9FFR1LAip51OfmQeBSdL+QeAtI7OtHIFv6n2SlmKdedDtwGvoHdlCrJPEt50BXQFXU8fqZ8E4R7Lx6tnPGMpklDWIl5L9kqyIIj4kHj4hLA8bBB+uv6ErOggD5mqs2gnux1t0BAoT8ADDUhQYXFFUoReXWX5YlJdRsuPzMZyyZJnFqBQ==
X-OriginatorOrg: amd.com
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 8fa4ba96-ec59-41f1-de16-08d866f511cc
X-MS-Exchange-CrossTenant-AuthSource: DM5PR12MB1355.namprd12.prod.outlook.com
X-MS-Exchange-CrossTenant-AuthAs: Internal
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 02 Oct 2020 17:03:22.6613
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 3dd8961f-e488-4e60-8e11-a82d994e183d
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 pbAXq0h3rUG50CN0XYYxNuUBl7Tb/+1p5LIVgxhEX2dxyXV2oeLbY46R4i+ZetwcXwWR7m4LbbFE6gqoOAPZjQ==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6PR12MB4218
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Tom Lendacky <thomas.lendacky@amd.com>

When both KVM support and the CCP driver are built into the kernel instead
of as modules, KVM initialization happens before CCP initialization. As a
result, sev_platform_status() will return a failure when it is called from
sev_hardware_setup(), when this isn't really an error condition.

Since sev_platform_status() doesn't need to be called at this time anyway,
remove the invocation from sev_hardware_setup().

Signed-off-by: Tom Lendacky <thomas.lendacky@amd.com>
---
 arch/x86/kvm/svm/sev.c | 22 +---------------------
 1 file changed, 1 insertion(+), 21 deletions(-)

```
#### [PATCH] x86/kvm: Update the comment about asynchronous page fault in exc_page_fault()
##### From: Vitaly Kuznetsov <vkuznets@redhat.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Vitaly Kuznetsov <vkuznets@redhat.com>
X-Patchwork-Id: 11813877
Return-Path: <SRS0=ns5b=DJ=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 0E7CA112E
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 15:43:24 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [23.128.96.18])
	by mail.kernel.org (Postfix) with ESMTP id E08DA208B6
	for <patchwork-kvm@patchwork.kernel.org>;
 Fri,  2 Oct 2020 15:43:23 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (1024-bit key) header.d=redhat.com header.i=@redhat.com
 header.b="G2KnIv2L"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S2387939AbgJBPnW (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Fri, 2 Oct 2020 11:43:22 -0400
Received: from us-smtp-delivery-124.mimecast.com ([216.205.24.124]:20865 "EHLO
        us-smtp-delivery-124.mimecast.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S2387777AbgJBPnW (ORCPT
        <rfc822;kvm@vger.kernel.org>); Fri, 2 Oct 2020 11:43:22 -0400
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=redhat.com;
        s=mimecast20190719; t=1601653401;
        h=from:from:reply-to:subject:subject:date:date:message-id:message-id:
         to:to:cc:cc:mime-version:mime-version:
         content-transfer-encoding:content-transfer-encoding;
        bh=4n/vvpNwLnfm6WZ1RtB9x/PAi54sYaqURdYPn6d7brA=;
        b=G2KnIv2LndmWOeb/ZU0BnJtj53Ft5MdJIQx2imdthJSpU7fMSsGM6UeCCmm0flyLtyVb+m
        kphJ4Uh/lvSLpV3znTEgHAhfXlYxlF4lnvGyCV+8ROlPDMp3nKA+Ha4peNSu9JfxfMtlkS
        UobDnv9zOh6T6oMoYzX8Lkj3cT1nFbA=
Received: from mimecast-mx01.redhat.com (mimecast-mx01.redhat.com
 [209.132.183.4]) (Using TLS) by relay.mimecast.com with ESMTP id
 us-mta-325-iiZI2-hePA-Sn87Iz7wFpw-1; Fri, 02 Oct 2020 11:43:19 -0400
X-MC-Unique: iiZI2-hePA-Sn87Iz7wFpw-1
Received: from smtp.corp.redhat.com (int-mx08.intmail.prod.int.phx2.redhat.com
 [10.5.11.23])
        (using TLSv1.2 with cipher AECDH-AES256-SHA (256/256 bits))
        (No client certificate requested)
        by mimecast-mx01.redhat.com (Postfix) with ESMTPS id B300A186DD37;
        Fri,  2 Oct 2020 15:43:17 +0000 (UTC)
Received: from vitty.brq.redhat.com (unknown [10.40.195.161])
        by smtp.corp.redhat.com (Postfix) with ESMTP id 9BDFE19C78;
        Fri,  2 Oct 2020 15:43:14 +0000 (UTC)
From: Vitaly Kuznetsov <vkuznets@redhat.com>
To: x86@kernel.org
Cc: kvm@vger.kernel.org, Andy Lutomirski <luto@kernel.org>,
        Thomas Gleixner <tglx@linutronix.de>,
        Ingo Molnar <mingo@redhat.com>, Borislav Petkov <bp@alien8.de>,
        Dave Hansen <dave.hansen@linux.intel.com>,
        Peter Zijlstra <peterz@infradead.org>,
        Paolo Bonzini <pbonzini@redhat.com>,
        linux-kernel@vger.kernel.org
Subject: [PATCH] x86/kvm: Update the comment about asynchronous page fault in
 exc_page_fault()
Date: Fri,  2 Oct 2020 17:43:13 +0200
Message-Id: <20201002154313.1505327-1-vkuznets@redhat.com>
MIME-Version: 1.0
X-Scanned-By: MIMEDefang 2.84 on 10.5.11.23
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

KVM was switched to interrupt-based mechanism for 'page ready' event
delivery in Linux-5.8 (see commit 2635b5c4a0e4 ("KVM: x86: interrupt based
APF 'page ready' event delivery")) and #PF (ab)use for 'page ready' event
delivery was removed. Linux guest switched to this new mechanism
exclusively in 5.9 (see commit b1d405751cd5 ("KVM: x86: Switch KVM guest to
using interrupts for page ready APF delivery")) so it is not possible to
get older KVM (APF mechanism won't be enabled). Update the comment in
exc_page_fault() to reflect the new reality.

Signed-off-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
 arch/x86/mm/fault.c | 13 ++++++++-----
 1 file changed, 8 insertions(+), 5 deletions(-)

```
