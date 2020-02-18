#### [PATCH RESEND v23 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a common macro
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongjiu Geng <gengdongjiu@huawei.com>
X-Patchwork-Id: 11384873
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A5D521820
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 01:25:26 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 91CF924125
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 01:25:26 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726259AbgBQBZZ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Sun, 16 Feb 2020 20:25:25 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:37282 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726183AbgBQBZY (ORCPT <rfc822;kvm@vger.kernel.org>);
        Sun, 16 Feb 2020 20:25:24 -0500
Received: from DGGEMS405-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id DBF56E9DBFF1A9862BA4;
        Mon, 17 Feb 2020 09:25:22 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS405-HUB.china.huawei.com
 (10.3.19.205) with Microsoft SMTP Server id 14.3.439.0; Mon, 17 Feb 2020
 09:25:16 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <mst@redhat.com>, <imammedo@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <shannon.zhaosl@gmail.com>,
        <peter.maydell@linaro.org>, <fam@euphon.net>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <mtosatti@redhat.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <qemu-arm@nongnu.org>, <pbonzini@redhat.com>,
        <james.morse@arm.com>, <lersek@redhat.com>,
        <jonathan.cameron@huawei.com>,
        <shameerali.kolothum.thodi@huawei.com>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>
Subject: [PATCH RESEND v23 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a
 common macro
Date: Mon, 17 Feb 2020 09:27:28 +0800
Message-ID: <20200217012737.30231-2-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.18.0.huawei.25
In-Reply-To: <20200217012737.30231-1-gengdongjiu@huawei.com>
References: <20200217012737.30231-1-gengdongjiu@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.151.151.243]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The little end UUID is used in many places, so make
NVDIMM_UUID_LE to a common macro to convert the UUID
to a little end array.

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
Reviewed-by: Xiang Zheng <zhengxiang9@huawei.com>
---
 hw/acpi/nvdimm.c    | 8 ++------
 include/qemu/uuid.h | 5 +++++
 2 files changed, 7 insertions(+), 6 deletions(-)

```
#### [PATCH v24 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a common macro
##### From: Dongjiu Geng <gengdongjiu@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Dongjiu Geng <gengdongjiu@huawei.com>
X-Patchwork-Id: 11386337
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C105C159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 13:10:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AAB262070B
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 13:10:41 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1728091AbgBQNKl (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 08:10:41 -0500
Received: from szxga06-in.huawei.com ([45.249.212.32]:45264 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1726797AbgBQNKk (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Feb 2020 08:10:40 -0500
Received: from DGGEMS410-HUB.china.huawei.com (unknown [172.30.72.58])
        by Forcepoint Email with ESMTP id 3D8A360CF7DC4101A5CE;
        Mon, 17 Feb 2020 21:10:36 +0800 (CST)
Received: from huawei.com (10.151.151.243) by DGGEMS410-HUB.china.huawei.com
 (10.3.19.210) with Microsoft SMTP Server id 14.3.439.0; Mon, 17 Feb 2020
 21:10:28 +0800
From: Dongjiu Geng <gengdongjiu@huawei.com>
To: <mst@redhat.com>, <imammedo@redhat.com>,
        <xiaoguangrong.eric@gmail.com>, <shannon.zhaosl@gmail.com>,
        <peter.maydell@linaro.org>, <fam@euphon.net>, <rth@twiddle.net>,
        <ehabkost@redhat.com>, <mtosatti@redhat.com>,
        <qemu-devel@nongnu.org>, <kvm@vger.kernel.org>,
        <qemu-arm@nongnu.org>, <pbonzini@redhat.com>,
        <james.morse@arm.com>, <lersek@redhat.com>,
        <jonathan.cameron@huawei.com>,
        <shameerali.kolothum.thodi@huawei.com>
CC: <gengdongjiu@huawei.com>, <zhengxiang9@huawei.com>
Subject: [PATCH v24 01/10] acpi: nvdimm: change NVDIMM_UUID_LE to a common
 macro
Date: Mon, 17 Feb 2020 21:12:39 +0800
Message-ID: <20200217131248.28273-2-gengdongjiu@huawei.com>
X-Mailer: git-send-email 2.18.0.huawei.25
In-Reply-To: <20200217131248.28273-1-gengdongjiu@huawei.com>
References: <20200217131248.28273-1-gengdongjiu@huawei.com>
MIME-Version: 1.0
X-Originating-IP: [10.151.151.243]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The little end UUID is used in many places, so make
NVDIMM_UUID_LE to a common macro to convert the UUID
to a little end array.

Signed-off-by: Dongjiu Geng <gengdongjiu@huawei.com>
Reviewed-by: Xiang Zheng <zhengxiang9@huawei.com>
---
 hw/acpi/nvdimm.c    | 8 ++------
 include/qemu/uuid.h | 5 +++++
 2 files changed, 7 insertions(+), 6 deletions(-)

```
#### [PATCH 1/2] lock changes
##### From: Christian Borntraeger <borntraeger@de.ibm.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Christian Borntraeger <borntraeger@de.ibm.com>
X-Patchwork-Id: 11386569
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id A72DB17F0
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 14:53:09 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 80C7A22464
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 14:53:09 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729301AbgBQOxJ (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 09:53:09 -0500
Received: from mx0a-001b2d01.pphosted.com ([148.163.156.1]:6204 "EHLO
        mx0a-001b2d01.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1729043AbgBQOxI (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 17 Feb 2020 09:53:08 -0500
Received: from pps.filterd (m0098409.ppops.net [127.0.0.1])
        by mx0a-001b2d01.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01HEoCG6166657;
        Mon, 17 Feb 2020 09:53:07 -0500
Received: from pps.reinject (localhost [127.0.0.1])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y6cu1thvx-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 Feb 2020 09:53:07 -0500
Received: from m0098409.ppops.net (m0098409.ppops.net [127.0.0.1])
        by pps.reinject (8.16.0.36/8.16.0.36) with SMTP id 01HEr7gR196140;
        Mon, 17 Feb 2020 09:53:07 -0500
Received: from ppma01dal.us.ibm.com (83.d6.3fa9.ip4.static.sl-reverse.com
 [169.63.214.131])
        by mx0a-001b2d01.pphosted.com with ESMTP id 2y6cu1thve-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 Feb 2020 09:53:07 -0500
Received: from pps.filterd (ppma01dal.us.ibm.com [127.0.0.1])
        by ppma01dal.us.ibm.com (8.16.0.27/8.16.0.27) with SMTP id
 01HEph07028422;
        Mon, 17 Feb 2020 14:53:06 GMT
Received: from b01cxnp22036.gho.pok.ibm.com (b01cxnp22036.gho.pok.ibm.com
 [9.57.198.26])
        by ppma01dal.us.ibm.com with ESMTP id 2y6896730j-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-GCM-SHA384 bits=256
 verify=NOT);
        Mon, 17 Feb 2020 14:53:06 +0000
Received: from b01ledav005.gho.pok.ibm.com (b01ledav005.gho.pok.ibm.com
 [9.57.199.110])
        by b01cxnp22036.gho.pok.ibm.com (8.14.9/8.14.9/NCO v10.0) with ESMTP
 id 01HEr36G34537888
        (version=TLSv1/SSLv3 cipher=DHE-RSA-AES256-GCM-SHA384 bits=256
 verify=OK);
        Mon, 17 Feb 2020 14:53:03 GMT
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id B7B2FAE063;
        Mon, 17 Feb 2020 14:53:03 +0000 (GMT)
Received: from b01ledav005.gho.pok.ibm.com (unknown [127.0.0.1])
        by IMSVA (Postfix) with ESMTP id 948BDAE064;
        Mon, 17 Feb 2020 14:53:03 +0000 (GMT)
Received: from localhost.localdomain (unknown [9.114.17.106])
        by b01ledav005.gho.pok.ibm.com (Postfix) with ESMTP;
        Mon, 17 Feb 2020 14:53:03 +0000 (GMT)
From: Christian Borntraeger <borntraeger@de.ibm.com>
To: david@redhat.com
Cc: Ulrich.Weigand@de.ibm.com, borntraeger@de.ibm.com,
        cohuck@redhat.com, frankja@linux.ibm.com,
        frankja@linux.vnet.ibm.com, gor@linux.ibm.com,
        imbrenda@linux.ibm.com, kvm@vger.kernel.org,
        linux-s390@vger.kernel.org, mimu@linux.ibm.com, thuth@redhat.com
Subject: [PATCH 1/2] lock changes
Date: Mon, 17 Feb 2020 09:53:01 -0500
Message-Id: <20200217145302.19085-2-borntraeger@de.ibm.com>
X-Mailer: git-send-email 2.25.0
In-Reply-To: <20200217145302.19085-1-borntraeger@de.ibm.com>
References: <c77dbb1b-0f4b-e40a-52a4-7110aec75e32@redhat.com>
 <20200217145302.19085-1-borntraeger@de.ibm.com>
MIME-Version: 1.0
X-TM-AS-GCONF: 00
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-17_08:2020-02-17,2020-02-17 signatures=0
X-Proofpoint-Spam-Details: rule=outbound_notspam policy=outbound score=0
 priorityscore=1501
 malwarescore=0 mlxscore=0 suspectscore=3 bulkscore=0 spamscore=0
 lowpriorityscore=0 impostorscore=0 adultscore=0 clxscore=1015
 mlxlogscore=913 phishscore=0 classifier=spam adjust=0 reason=mlx
 scancount=1 engine=8.12.0-2001150001 definitions=main-2002170123
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

Signed-off-by: Christian Borntraeger <borntraeger@de.ibm.com>
---
 arch/s390/kvm/intercept.c |  6 +++---
 arch/s390/kvm/interrupt.c | 35 +++++++++++++++++++++--------------
 arch/s390/kvm/kvm-s390.c  | 28 +++++++++++++---------------
 arch/s390/kvm/kvm-s390.h  | 18 +++++++++++++-----
 arch/s390/kvm/priv.c      |  4 ++--
 5 files changed, 52 insertions(+), 39 deletions(-)

```
#### [PATCH 1/2] KVM: arm/arm64: Fix spurious htimer setup for emulated timer
##### From: Tomasz Nowicki <tnowicki@marvell.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Tomasz Nowicki <tnowicki@marvell.com>
X-Patchwork-Id: 11386577
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id C8DB217E8
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 14:55:32 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id A8DC720679
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 14:55:32 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=marvell.com header.i=@marvell.com
 header.b="p0HEbZG+";
	dkim=pass (1024-bit key) header.d=marvell.onmicrosoft.com
 header.i=@marvell.onmicrosoft.com header.b="awuFQAkj"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729233AbgBQOzc (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 09:55:32 -0500
Received: from mx0b-0016f401.pphosted.com ([67.231.156.173]:13722 "EHLO
        mx0b-0016f401.pphosted.com" rhost-flags-OK-OK-OK-OK)
        by vger.kernel.org with ESMTP id S1728845AbgBQOzb (ORCPT
        <rfc822;kvm@vger.kernel.org>); Mon, 17 Feb 2020 09:55:31 -0500
Received: from pps.filterd (m0045851.ppops.net [127.0.0.1])
        by mx0b-0016f401.pphosted.com (8.16.0.42/8.16.0.42) with SMTP id
 01HEjBKn001236;
        Mon, 17 Feb 2020 06:55:24 -0800
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=marvell.com;
 h=from : to : cc :
 subject : date : message-id : in-reply-to : references : content-type :
 mime-version; s=pfpt0818; bh=5mcqY449zy3Zfkv3CBJ8BylamkNGI5puC3rFXUTvS1I=;
 b=p0HEbZG+OnlN6/T8DkgM+yeFi1xgu5lswMM++zLvl9c4VMThMPS/hhvKyYSORcUUj0W5
 YwZLH0J5jlkdMy7p0WKaceTjfiWYd9qBMqUxQL9NKklN9K0NK1Ac+z4VyLDSUBw+BOgc
 lgRjTcUmJQozGPZNwMld+8VI1WNiiEo4tdZkF9wb/eUrar5oR+Z/4zcEc6YZRw3YXfPk
 0bYmQmoZxH8S6tarrsa0IynijlVp/O9HeWHBHTMcbQkwpWD+S8ThP/9SY9A6PTcmB6hf
 36oXPmeyzHFp3fb5weoL/qFo/VG4CaPg0qX5h8dgZOIsUe5HCl9JlB16AJ6Eg8A+hhC1 fg==
Received: from sc-exch03.marvell.com ([199.233.58.183])
        by mx0b-0016f401.pphosted.com with ESMTP id 2y6h1sychk-1
        (version=TLSv1.2 cipher=ECDHE-RSA-AES256-SHA384 bits=256 verify=NOT);
        Mon, 17 Feb 2020 06:55:23 -0800
Received: from DC5-EXCH02.marvell.com (10.69.176.39) by SC-EXCH03.marvell.com
 (10.93.176.83) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Mon, 17 Feb
 2020 06:55:21 -0800
Received: from SC-EXCH01.marvell.com (10.93.176.81) by DC5-EXCH02.marvell.com
 (10.69.176.39) with Microsoft SMTP Server (TLS) id 15.0.1497.2; Mon, 17 Feb
 2020 06:55:21 -0800
Received: from NAM11-BN8-obe.outbound.protection.outlook.com (104.47.58.174)
 by SC-EXCH01.marvell.com (10.93.176.81) with Microsoft SMTP Server (TLS) id
 15.0.1497.2 via Frontend Transport; Mon, 17 Feb 2020 06:55:21 -0800
ARC-Seal: i=1; a=rsa-sha256; s=arcselector9901; d=microsoft.com; cv=none;
 b=K0hRcbAI8oCRtPNHjHrdIBxt8Ovj6/zpLAlneQUiLu7NiNJx5OnbrUDvsFh81zN0BTwmTfrWArAjjTvRrHxSz7KswrbKp9Neire1h1tL8gCVYuIy07+yD364hYQoz1ZJutxdFsgx7h5CUPSvR0th7lfzig3i5BxhMZUufjYlqoVzJQu3LFPYvqkM37gJCZQwp4YarJbm1PSAvV5ZgxEWcvVN4tJlbFXQmBqfIuqF10N/km0bbrJqLyuBwqebMIUuayQ1ndX62uCdRJSmqO8SN2IihBAoT2fq6EP9jNsvftutow3zp7CwhCuS1ImSWI0//YHgaBOd/NJ+259mwMJhwQ==
ARC-Message-Signature: i=1; a=rsa-sha256; c=relaxed/relaxed; d=microsoft.com;
 s=arcselector9901;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=5mcqY449zy3Zfkv3CBJ8BylamkNGI5puC3rFXUTvS1I=;
 b=Szmxw+e5y3CXVuQZ5y0S7yU3wFikS1HWXeybe4cihR6cuHOWuY3WjsGqegJ/9tovtKdp5b90oIpUK4swfNjjRzDI6mrwUwiezCygl/AVS1Y5BNCuzl6tFtO1rztq1ewCV8t8UfF6EVYz4ggvXA1VdRkpBFVXg4+mATZf4bymJmPhnDPLQCbZewg8SLm3QDNRosEGeeUm8zYP9wD2sK0N38rBi0KoWpwpKHgzLrtqKqtoqpkbrzkr6hrwEs+9/X0DYaSwzNkkCPN1HfpS9Rqy9qjDYx2yceC/Ysh1wnj5rQIwOdTr04weFjeh3mS4lPgaWuIF6WSIVoHGXpyt8EYNDA==
ARC-Authentication-Results: i=1; mx.microsoft.com 1; spf=pass
 smtp.mailfrom=marvell.com; dmarc=pass action=none header.from=marvell.com;
 dkim=pass header.d=marvell.com; arc=none
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
 d=marvell.onmicrosoft.com; s=selector1-marvell-onmicrosoft-com;
 h=From:Date:Subject:Message-ID:Content-Type:MIME-Version:X-MS-Exchange-SenderADCheck;
 bh=5mcqY449zy3Zfkv3CBJ8BylamkNGI5puC3rFXUTvS1I=;
 b=awuFQAkjOufsUhMVwKyl+mN+kkvVAliRHGXqtBRIk6frB9VEbxQdCEBMur8OKvxK11jCyYYI7K0P3TioBfZbtwmvv9CXkW+23wG7XjqY52zOZkaHvFDF3nT1D6Xqim97tVDPje+tOeXjwURKO6pyKRl7kj+HQSKH8SftUjtlqKY=
Received: from DM6PR18MB2969.namprd18.prod.outlook.com (20.179.52.17) by
 DM6SPR01MB0045.namprd18.prod.outlook.com (20.176.120.140) with Microsoft SMTP
 Server (version=TLS1_2, cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id
 15.20.2729.22; Mon, 17 Feb 2020 14:55:19 +0000
Received: from DM6PR18MB2969.namprd18.prod.outlook.com
 ([fe80::d890:b3b7:629e:352c]) by DM6PR18MB2969.namprd18.prod.outlook.com
 ([fe80::d890:b3b7:629e:352c%6]) with mapi id 15.20.2729.031; Mon, 17 Feb 2020
 14:55:19 +0000
From: Tomasz Nowicki <tnowicki@marvell.com>
To: <kvmarm@lists.cs.columbia.edu>,
        <linux-arm-kernel@lists.infradead.org>
CC: <kvm@vger.kernel.org>, <christoffer.dall@arm.com>,
        <maz@kernel.org>, <james.morse@arm.com>,
        <julien.thierry.kdev@gmail.com>, <gkulkarni@marvell.com>,
        <rrichter@marvell.com>, Tomasz Nowicki <tnowicki@marvell.com>
Subject: [PATCH 1/2] KVM: arm/arm64: Fix spurious htimer setup for emulated
 timer
Date: Mon, 17 Feb 2020 15:54:37 +0100
Message-ID: <20200217145438.23289-2-tnowicki@marvell.com>
X-Mailer: git-send-email 2.17.1
In-Reply-To: <20200217145438.23289-1-tnowicki@marvell.com>
References: <20200217145438.23289-1-tnowicki@marvell.com>
X-ClientProxiedBy: AM6P192CA0037.EURP192.PROD.OUTLOOK.COM
 (2603:10a6:209:82::14) To DM6PR18MB2969.namprd18.prod.outlook.com
 (2603:10b6:5:170::17)
MIME-Version: 1.0
Received: from localhost.localdomain (83.68.95.66) by
 AM6P192CA0037.EURP192.PROD.OUTLOOK.COM (2603:10a6:209:82::14) with Microsoft
 SMTP Server (version=TLS1_2,
 cipher=TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384) id 15.20.2729.22 via Frontend
 Transport; Mon, 17 Feb 2020 14:55:17 +0000
X-Mailer: git-send-email 2.17.1
X-Originating-IP: [83.68.95.66]
X-MS-PublicTrafficType: Email
X-MS-Office365-Filtering-Correlation-Id: 5b926705-8cd8-4822-ea1f-08d7b3b9684a
X-MS-TrafficTypeDiagnostic: DM6SPR01MB0045:
X-MS-Exchange-Transport-Forked: True
X-Microsoft-Antispam-PRVS: 
 <DM6SPR01MB00453CC949B7572373E5587FD2160@DM6SPR01MB0045.namprd18.prod.outlook.com>
X-MS-Oob-TLC-OOBClassifiers: OLM:7691;
X-Forefront-PRVS: 0316567485
X-Forefront-Antispam-Report: 
 SFV:NSPM;SFS:(10009020)(4636009)(136003)(39850400004)(366004)(376002)(346002)(396003)(189003)(199004)(69590400006)(4326008)(5660300002)(36756003)(26005)(4744005)(107886003)(478600001)(2906002)(16526019)(186003)(8936002)(52116002)(2616005)(81156014)(8676002)(81166006)(316002)(6666004)(6486002)(86362001)(956004)(66946007)(6512007)(1076003)(6506007)(66476007)(66556008);DIR:OUT;SFP:1101;SCL:1;SRVR:DM6SPR01MB0045;H:DM6PR18MB2969.namprd18.prod.outlook.com;FPR:;SPF:None;LANG:en;PTR:InfoNoRecords;MX:1;A:1;
Received-SPF: None (protection.outlook.com: marvell.com does not designate
 permitted sender hosts)
X-MS-Exchange-SenderADCheck: 1
X-Microsoft-Antispam: BCL:0;
X-Microsoft-Antispam-Message-Info: 
 WsKcU1OX0ML7qdNl9OGEry8QqVRhd+SkfgQorKzjvVuovJTKpi6AAFBJYhNtdgYKdEbQ2Nxigk+tL/i009ChCo5rF5nYrB2JR393Y0Oa4H636ykoUwT/YGp2UUE4DrKEvbNeDU5udTjRC5bd5AFaFQWvVpPm3evLFn2KM5jQYjcmH7E5g0LgJtC9gNbQfbqauGgA3A/DVpRwy3DnSaTAvLifntn3WQ0MYcPhJKBhihBm/09muf0f4YH2VLwzFQyLaZ0tmbMpyq0ufy97uQgzJvwtQqb1dAVbpZd/15ebKAeYLNj/6fopIWBA72evBVOerHwlDuE++k4au9LC6z8NshpOzLrbhTTcPnw14oda3sovwTn7HyTgWvfm12qZuRE6yms70RPVNwmu17/5LCHJvAiUMV4LmCgOZalYqHYAq+dRUC4qZuP3tlqsmFAZgDxD29tMeZmIdG1kaLfav7kWBckQupDFyLl+ntcrycSG3Tx6A/s6IJws36UD4wJbeFXaJS9FaQVrOZe7K24RYEiv+Qxz+Iq2XAfcukYBEtQnVII=
X-MS-Exchange-AntiSpam-MessageData: 
 ZdmZoE99DzZSkJSVLyzfWxltWKCeUEXZrnreFEdlrMPixPjEkVDXalGs9u3pLZliRYKHF1vHZlM/Af4GWpHCjP3MJ5cCxW5mgz4YkdeFqqkAKJlRA0MfhG1pjKz1bzSSAylB712bfsrDZLer1JpqJg==
X-MS-Exchange-CrossTenant-Network-Message-Id: 
 5b926705-8cd8-4822-ea1f-08d7b3b9684a
X-MS-Exchange-CrossTenant-OriginalArrivalTime: 17 Feb 2020 14:55:19.9054
 (UTC)
X-MS-Exchange-CrossTenant-FromEntityHeader: Hosted
X-MS-Exchange-CrossTenant-Id: 70e1fb47-1155-421d-87fc-2e58f638b6e0
X-MS-Exchange-CrossTenant-MailboxType: HOSTED
X-MS-Exchange-CrossTenant-UserPrincipalName: 
 vlZ2WJ8zZ32j2FY+1v61+70NMK8g4cjpwY0AlUkJdSmX3ZN2HkcOyIMQ+8h+PIGXjt8DCWn0Gwa9fScoHRFIbw==
X-MS-Exchange-Transport-CrossTenantHeadersStamped: DM6SPR01MB0045
X-OriginatorOrg: marvell.com
X-Proofpoint-Virus-Version: vendor=fsecure engine=2.50.10434:6.0.138,18.0.572
 definitions=2020-02-17_08:2020-02-17,2020-02-17 signatures=0
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The emulated timer needs no further software timer if the timer should fire
now and there is no change in irq line level: (should_fire == 1 &&
should_fire == ctx->irq.level). In that case htimer should be simply
canceled.

Fixes: bee038a674875 ("KVM: arm/arm64: Rework the timer code to use a timer_map")
Signed-off-by: Tomasz Nowicki <tnowicki@marvell.com>
---
 virt/kvm/arm/arch_timer.c | 2 +-
 1 file changed, 1 insertion(+), 1 deletion(-)

```
#### [tip: x86/cleanups] x86/cpu: Move prototype for get_umwait_control_msr() to a global location
##### From: "tip-bot2 for Benjamin Thiel" <tip-bot2@linutronix.de>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: tip-bot2 for Benjamin Thiel <tip-bot2@linutronix.de>
X-Patchwork-Id: 11387171
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id E5676930
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 18:38:47 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id CF21521D7D
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 18:38:47 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729567AbgBQSio (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 13:38:44 -0500
Received: from Galois.linutronix.de ([193.142.43.55]:34317 "EHLO
        Galois.linutronix.de" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727601AbgBQSio (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Feb 2020 13:38:44 -0500
Received: from [5.158.153.53] (helo=tip-bot2.lab.linutronix.de)
        by Galois.linutronix.de with esmtpsa
 (TLS1.2:DHE_RSA_AES_256_CBC_SHA256:256)
        (Exim 4.80)
        (envelope-from <tip-bot2@linutronix.de>)
        id 1j3lHz-0005C0-7x; Mon, 17 Feb 2020 19:38:39 +0100
Received: from [127.0.1.1] (localhost [IPv6:::1])
        by tip-bot2.lab.linutronix.de (Postfix) with ESMTP id CC90D1C20B4;
        Mon, 17 Feb 2020 19:38:38 +0100 (CET)
Date: Mon, 17 Feb 2020 18:38:38 -0000
From: "tip-bot2 for Benjamin Thiel" <tip-bot2@linutronix.de>
Reply-to: linux-kernel@vger.kernel.org
To: linux-tip-commits@vger.kernel.org
Subject: [tip: x86/cleanups] x86/cpu: Move prototype for
 get_umwait_control_msr() to a global location
Cc: Benjamin Thiel <b.thiel@posteo.de>, Borislav Petkov <bp@suse.de>,
        kvm@vger.kernel.org, x86 <x86@kernel.org>,
        LKML <linux-kernel@vger.kernel.org>
In-Reply-To: <20200123172945.7235-1-b.thiel@posteo.de>
References: <20200123172945.7235-1-b.thiel@posteo.de>
MIME-Version: 1.0
Message-ID: <158196471850.13786.2863222761853021206.tip-bot2@tip-bot2>
X-Mailer: tip-git-log-daemon
Robot-ID: <tip-bot2.linutronix.de>
Robot-Unsubscribe: Contact <mailto:tglx@linutronix.de> to get blacklisted from
 these emails
X-Linutronix-Spam-Score: -1.0
X-Linutronix-Spam-Level: -
X-Linutronix-Spam-Status: No , -1.0 points, 5.0 required,
  ALL_TRUSTED=-1,SHORTCIRCUIT=-0.0001
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

The following commit has been merged into the x86/cleanups branch of tip:

Commit-ID:     b10c307f6f314c068814d0e23c86f06d5d57004b
Gitweb:        https://git.kernel.org/tip/b10c307f6f314c068814d0e23c86f06d5d57004b
Author:        Benjamin Thiel <b.thiel@posteo.de>
AuthorDate:    Thu, 23 Jan 2020 18:29:45 +01:00
Committer:     Borislav Petkov <bp@suse.de>
CommitterDate: Mon, 17 Feb 2020 19:32:45 +01:00

x86/cpu: Move prototype for get_umwait_control_msr() to a global location

.. in order to fix a -Wmissing-prototypes warning.

No functional change.

Signed-off-by: Benjamin Thiel <b.thiel@posteo.de>
Signed-off-by: Borislav Petkov <bp@suse.de>
Cc: kvm@vger.kernel.org
Link: https://lkml.kernel.org/r/20200123172945.7235-1-b.thiel@posteo.de
---
 arch/x86/include/asm/mwait.h | 2 ++
 arch/x86/kernel/cpu/umwait.c | 1 +
 arch/x86/kvm/vmx/vmx.c       | 1 +
 arch/x86/kvm/vmx/vmx.h       | 2 --
 4 files changed, 4 insertions(+), 2 deletions(-)

```
#### [PATCH v2] kvm/emulate: fix a -Werror=cast-function-type
##### From: Qian Cai <cai@lca.pw>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Qian Cai <cai@lca.pw>
X-Patchwork-Id: 11386889
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D7AF692A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 16:48:41 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id AE32924656
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 16:48:41 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=lca.pw header.i=@lca.pw header.b="MsltEajV"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729413AbgBQQsj (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 11:48:39 -0500
Received: from mail-qt1-f195.google.com ([209.85.160.195]:37597 "EHLO
        mail-qt1-f195.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1727545AbgBQQsj (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Feb 2020 11:48:39 -0500
Received: by mail-qt1-f195.google.com with SMTP id w47so12457860qtk.4
        for <kvm@vger.kernel.org>; Mon, 17 Feb 2020 08:48:38 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=lca.pw; s=google;
        h=from:to:cc:subject:date:message-id;
        bh=et9GtBlMwNyxXKtY81oCoU0p2n7F0NO/hCNz4eL9vi4=;
        b=MsltEajVC7Lm/8rj+VK0/bBou9ueubcoYM1ggoVVaK1xxTGTPTHah7qcq/2NnPYrQn
         3v+ldGqaICuedwbPKZnqJFID347yBwxclCc/mlWjX02kVSDodn5UZpjJCZtJeiEZ9iV1
         PK2z2pLj9gMhtNlfP7D/DwsUhx0dT18QaY1PAOTTDuEivFQwmiioNAf3pygnOgIQsQxG
         BwxGL95/gwlXDxc1aKE5nn9VQE045CxPeVeVQk0IcoUf0vLgDBzZmvOUd/E5MAKSbcvp
         hOKKYsUTYmXpaWBg9lNmk7+ETCeBEeyPhVl+8a+wRJx/UB5gCWEHwNk8yhG5Z2dnX9C4
         XRnw==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:from:to:cc:subject:date:message-id;
        bh=et9GtBlMwNyxXKtY81oCoU0p2n7F0NO/hCNz4eL9vi4=;
        b=dv9cz6YPVvLMaCVCf6KYoJ1ZzHm7x2OCsJVyyWt5hw0xfCyHiSQK8ZYjMJ9KWf55+z
         mexzk5ELmjEtz6qBz3XrhCJXBMmpu1TRWT+yj6+VL3o4pg7Ofh4R2/bM4kNfwgGZZvDT
         jxUY3Y7kWkyR9mZUjYSPFK3y5806lWpax8FDanStiFSZ+gtzvrYv8ACGwtYhjTCg2/E4
         OHr2SO38+H8dUiG64EG4zmgTqzi4bSKBUX3f9EWzf3O80AHqYepBlxDG9+1A4uZgc12E
         HtboddKGBcdIVJFvt49dbhRgxTZOqR3M96kbzNL3MeVSwMpXZKKCbJJAMz2ZowN6Sf1r
         Uldg==
X-Gm-Message-State: APjAAAWysxcQvdhg2upC6KaQ/I/iJM3y5VxDeZvOWwCR0Hk7vFiam26E
        DFN/sGq2H+USL1iI92/c7VPZcQ==
X-Google-Smtp-Source: 
 APXvYqxrKwMoVogoFbUxH1yhlHkDUk5WxvIvhRaGwwYyjVjQnDoFqAia0cI5ZzRTsqQHqmWwYcFzEQ==
X-Received: by 2002:ac8:3fa9:: with SMTP id
 d38mr13115689qtk.333.1581958118352;
        Mon, 17 Feb 2020 08:48:38 -0800 (PST)
Received: from qcai.nay.com (nat-pool-bos-t.redhat.com. [66.187.233.206])
        by smtp.gmail.com with ESMTPSA id b12sm476086qkl.0.2020.02.17.08.48.37
        (version=TLS1_2 cipher=ECDHE-RSA-AES128-GCM-SHA256 bits=128/128);
        Mon, 17 Feb 2020 08:48:37 -0800 (PST)
From: Qian Cai <cai@lca.pw>
To: pbonzini@redhat.com
Cc: sean.j.christopherson@intel.com, vkuznets@redhat.com,
        wanpengli@tencent.com, jmattson@google.com, joro@8bytes.org,
        kvm@vger.kernel.org, linux-kernel@vger.kernel.org,
        Qian Cai <cai@lca.pw>
Subject: [PATCH v2] kvm/emulate: fix a -Werror=cast-function-type
Date: Mon, 17 Feb 2020 11:48:26 -0500
Message-Id: <1581958106-16668-1-git-send-email-cai@lca.pw>
X-Mailer: git-send-email 1.8.3.1
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

arch/x86/kvm/emulate.c: In function 'x86_emulate_insn':
arch/x86/kvm/emulate.c:5686:22: error: cast between incompatible
function types from 'int (*)(struct x86_emulate_ctxt *)' to 'void
(*)(struct fastop *)' [-Werror=cast-function-type]
    rc = fastop(ctxt, (fastop_t)ctxt->execute);

Fix it by using an unnamed union of a (*execute) function pointer and a
(*fastop) function pointer.

Fixes: 3009afc6e39e ("KVM: x86: Use a typedef for fastop functions")
Suggested-by: Paolo Bonzini <pbonzini@redhat.com>
Signed-off-by: Qian Cai <cai@lca.pw>
---

v2: use an unnamed union.

 arch/x86/include/asm/kvm_emulate.h | 13 ++++++++++++-
 arch/x86/kvm/emulate.c             | 36 ++++++++++++++----------------------
 2 files changed, 26 insertions(+), 23 deletions(-)

```
#### [PATCH v2] KVM: VMX: Add 'else' to split mutually exclusive case
##### From: linmiaohe <linmiaohe@huawei.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: linmiaohe <linmiaohe@huawei.com>
X-Patchwork-Id: 11386587
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id 3C382159A
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 15:01:10 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id 2676D24125
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 15:01:10 +0000 (UTC)
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1729361AbgBQPBH (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 10:01:07 -0500
Received: from szxga04-in.huawei.com ([45.249.212.190]:10632 "EHLO huawei.com"
        rhost-flags-OK-OK-OK-FAIL) by vger.kernel.org with ESMTP
        id S1729315AbgBQPBH (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Feb 2020 10:01:07 -0500
Received: from DGGEMS408-HUB.china.huawei.com (unknown [172.30.72.59])
        by Forcepoint Email with ESMTP id A2B23B6A8D864C6AB5DD;
        Mon, 17 Feb 2020 23:01:01 +0800 (CST)
Received: from huawei.com (10.175.105.18) by DGGEMS408-HUB.china.huawei.com
 (10.3.19.208) with Microsoft SMTP Server id 14.3.439.0; Mon, 17 Feb 2020
 23:00:53 +0800
From: linmiaohe <linmiaohe@huawei.com>
To: <pbonzini@redhat.com>, <rkrcmar@redhat.com>,
        <sean.j.christopherson@intel.com>, <vkuznets@redhat.com>,
        <wanpengli@tencent.com>, <jmattson@google.com>, <joro@8bytes.org>,
        <tglx@linutronix.de>, <mingo@redhat.com>, <bp@alien8.de>,
        <hpa@zytor.com>
CC: <linmiaohe@huawei.com>, <kvm@vger.kernel.org>,
        <linux-kernel@vger.kernel.org>, <x86@kernel.org>
Subject: [PATCH v2] KVM: VMX: Add 'else' to split mutually exclusive case
Date: Mon, 17 Feb 2020 23:02:30 +0800
Message-ID: <1581951750-17854-1-git-send-email-linmiaohe@huawei.com>
X-Mailer: git-send-email 1.8.3.1
MIME-Version: 1.0
X-Originating-IP: [10.175.105.18]
X-CFilter-Loop: Reflected
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Miaohe Lin <linmiaohe@huawei.com>

Each if branch in handle_external_interrupt_irqoff() is mutually
exclusive. Add 'else' to make it clear and also avoid some unnecessary
check.

Signed-off-by: Miaohe Lin <linmiaohe@huawei.com>
Reviewed-by: Vitaly Kuznetsov <vkuznets@redhat.com>
---
v1->v2:
add braces to all if branches
---
 arch/x86/kvm/vmx/vmx.c | 8 +++-----
 1 file changed, 3 insertions(+), 5 deletions(-)

```
#### [PATCH v3 1/2] KVM: X86: Less kvmclock sync induced vmexits after VM boots
##### From: Wanpeng Li <kernellwp@gmail.com>

```c
Content-Type: text/plain; charset="utf-8"
MIME-Version: 1.0
Content-Transfer-Encoding: 7bit
X-Patchwork-Submitter: Wanpeng Li <kernellwp@gmail.com>
X-Patchwork-Id: 11386069
Return-Path: <SRS0=fZmU=4F=vger.kernel.org=kvm-owner@kernel.org>
Received: from mail.kernel.org (pdx-korg-mail-1.web.codeaurora.org
 [172.30.200.123])
	by pdx-korg-patchwork-2.web.codeaurora.org (Postfix) with ESMTP id D4D5D924
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 10:36:56 +0000 (UTC)
Received: from vger.kernel.org (vger.kernel.org [209.132.180.67])
	by mail.kernel.org (Postfix) with ESMTP id B5E4420836
	for <patchwork-kvm@patchwork.kernel.org>;
 Mon, 17 Feb 2020 10:36:56 +0000 (UTC)
Authentication-Results: mail.kernel.org;
	dkim=pass (2048-bit key) header.d=gmail.com header.i=@gmail.com
 header.b="NJoGVxJg"
Received: (majordomo@vger.kernel.org) by vger.kernel.org via listexpand
        id S1726797AbgBQKgy (ORCPT
        <rfc822;patchwork-kvm@patchwork.kernel.org>);
        Mon, 17 Feb 2020 05:36:54 -0500
Received: from mail-ot1-f67.google.com ([209.85.210.67]:35589 "EHLO
        mail-ot1-f67.google.com" rhost-flags-OK-OK-OK-OK) by vger.kernel.org
        with ESMTP id S1725972AbgBQKgx (ORCPT <rfc822;kvm@vger.kernel.org>);
        Mon, 17 Feb 2020 05:36:53 -0500
Received: by mail-ot1-f67.google.com with SMTP id r16so15637143otd.2;
        Mon, 17 Feb 2020 02:36:53 -0800 (PST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=gmail.com; s=20161025;
        h=mime-version:from:date:message-id:subject:to:cc;
        bh=ur/ztzg097hNdiOqNl8MURR6+AytvFPiL8IkE10Yl1Q=;
        b=NJoGVxJgA8Ke2CHUVj9hmcpI5GSEOxBa9au4sw2v0wW7hnClOJbAG2aCuVfJV7cJep
         CxKMl62BY6MY+WpZPIcbnvj5We8vw5q1pZNSenF4Xx7QpXnItnQyE5nJY0qC7hmdvvj3
         ITLmRwT3U41EBZds1mbQRQ63N7eOFzhAiI/gMJtDUQIH8DZPPe4o/L51/kLfYQrFyJo+
         JNoCN4TLAFPc4FT38cG9moYmFtzUvDNSU4bNfZcmz8zS/QPNSg6vge66CPPaL40DIQw9
         EDsNxTzzIkBrHMyyrxv+cak+suv4+jRWRvPNG4sVoteghhIN1Kj+pie6zjV4bF0nj59c
         cl1Q==
X-Google-DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed;
        d=1e100.net; s=20161025;
        h=x-gm-message-state:mime-version:from:date:message-id:subject:to:cc;
        bh=ur/ztzg097hNdiOqNl8MURR6+AytvFPiL8IkE10Yl1Q=;
        b=NOYC6RuPWxB5ZpyYR0+pF7pAebqG5MZ3xKKGCX7XmwnoXBlACKL66KjmOW1f0/D95+
         P20VZGgpKEY90FleyJI7Niso2ikMa2+OxPM2DvWaAkwkzgZ2/NnFLLbhlTiTAzmBQvqm
         sDB94XwcNL4uhhsAP0FzxXwVctRp7NqlGqWAUZq6x+tryu8xyHXH2/JT8lBbL+5UZaRE
         Yki8DA8RjbGrJiLww8znlT04ED8PsdRdkAYkbAF5ngT5Yv00N49FLrVzDFcmQ2xTthBZ
         vSBl4piy54v4oFPBavor/0e2iYVf+vsIeXvfpz2i4tCRASHBHIEh4Cbyw3kL9rKdRyZn
         i/bQ==
X-Gm-Message-State: APjAAAUpo3MxvczLtDJB3s4yT1Vfm6vgBgsS10lgPA63Ov/ubO0UIPrA
        agKtpFMeHA1wmhpeRFC7mdNu7XcRakWiAbm3MTxrtujQmS6l5Q==
X-Google-Smtp-Source: 
 APXvYqx+pB+sFO42DRkAL0RCvyTGIbk1nCpM3Rl6C4VZ+Q++st91JjnhSvk4mXvlkrf0/U07A7VQF4bh5F4pNz5qn7I=
X-Received: by 2002:a9d:63d6:: with SMTP id
 e22mr11830539otl.185.1581935812830;
 Mon, 17 Feb 2020 02:36:52 -0800 (PST)
MIME-Version: 1.0
From: Wanpeng Li <kernellwp@gmail.com>
Date: Mon, 17 Feb 2020 18:36:41 +0800
Message-ID: 
 <CANRm+Cz6Es1TLFdGxz_65i-4osE6=67J=noqWC6n09TeXSJ5SA@mail.gmail.com>
Subject: [PATCH v3 1/2] KVM: X86: Less kvmclock sync induced vmexits after VM
 boots
To: LKML <linux-kernel@vger.kernel.org>, kvm <kvm@vger.kernel.org>
Cc: Paolo Bonzini <pbonzini@redhat.com>,
        Sean Christopherson <sean.j.christopherson@intel.com>,
        Wanpeng Li <wanpengli@tencent.com>,
        Vitaly Kuznetsov <vkuznets@redhat.com>,
        Jim Mattson <jmattson@google.com>,
        Joerg Roedel <joro@8bytes.org>
Sender: kvm-owner@vger.kernel.org
Precedence: bulk
List-ID: <kvm.vger.kernel.org>
X-Mailing-List: kvm@vger.kernel.org

From: Wanpeng Li <wanpengli@tencent.com>

In the progress of vCPUs creation, it queues a kvmclock sync worker to
the global
workqueue before each vCPU creation completes. Each worker will be scheduled
after 300 * HZ delay and request a kvmclock update for all vCPUs and kick them
out. This is especially worse when scaling to large VMs due to a lot of vmexits.
Just one worker as a leader to trigger the kvmclock sync request for
all vCPUs is
enough.

Signed-off-by: Wanpeng Li <wanpengli@tencent.com>
---
 arch/x86/kvm/x86.c | 5 +++--
 1 file changed, 3 insertions(+), 2 deletions(-)

--
2.7.4

```
